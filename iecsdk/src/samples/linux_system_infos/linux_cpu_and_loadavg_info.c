/**
*** INTEL CONFIDENTIAL
*** 
*** Copyright (October 2008) (October 2008) Intel Corporation All Rights Reserved. 
*** The source code contained or described herein and all documents related to the
*** source code ("Material") are owned by Intel Corporation or its suppliers or 
*** licensors. Title to the Material remains with Intel Corporation or its 
*** suppliers and licensors. The Material contains trade secrets and proprietary 
*** and confidential information of Intel or its suppliers and licensors. 
*** The Material is protected by worldwide copyright and trade secret laws 
*** and treaty provisions. No part of the Material may be used, copied, 
*** reproduced, modified, published, uploaded, posted, transmitted, distributed,
*** or disclosed in any way without Intel’s prior express written permission.
***
*** No license under any patent, copyright, trade secret or other intellectual
*** property right is granted to or conferred upon you by disclosure or delivery
*** of the Materials, either expressly, by implication, inducement, estoppel or
*** otherwise. Any license under such intellectual property rights must be 
*** express and approved by Intel in writing.
**/

#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <uuid/uuid.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <productivity_link.h>

//-----------------------------------------------------------------------------
// configuration defines
//-----------------------------------------------------------------------------
#define APPLICATION_NAME "Linux CPU and Load Info"
#define DATA_SOURCE_LOAD "/proc/loadavg"
#define DATA_SOURCE_CPU "/proc/stat"
#define CPU_TO_MONITOR "cpu"
#define COUNTERS_COUNT_CPU_USAGE 2
#define COUNTERS_COUNT_LOAD 9
#define COUNTERS_COUNT_CPU 8
#define COUNTERS_COUNT (COUNTERS_COUNT_CPU_USAGE + COUNTERS_COUNT_LOAD + COUNTERS_COUNT_CPU)
#define BUFFER_SIZE 4096
#define SCALING 100.0

#define STARTUP_MESSAGE_LINES_COUNT 9
#define STARTUP_MESSAGE_LINES \
	"\n", \
	" @      @@@@@  @    @ @    @ @   @          @@@@  @@@@@  @    @          @@   @    @ @@@@@         @       @@@@    @@   @@@@@         @@@@@  @    @ @@@@@@  @@@@\n", \
	" @        @    @@   @ @    @  @ @          @    @ @    @ @    @         @  @  @@   @ @    @        @      @    @  @  @  @    @          @    @@   @ @      @    @\n", \
	" @        @    @ @  @ @    @   @           @      @    @ @    @        @    @ @ @  @ @    @        @      @    @ @    @ @    @          @    @ @  @ @      @    @\n", \
	" @        @    @ @  @ @    @   @           @      @@@@@  @    @        @    @ @ @  @ @    @        @      @    @ @    @ @    @          @    @ @  @ @@@@@  @    @\n", \
	" @        @    @  @ @ @    @   @           @      @      @    @        @@@@@@ @  @ @ @    @        @      @    @ @@@@@@ @    @          @    @  @ @ @      @    @\n", \
	" @        @    @   @@ @    @  @ @          @    @ @      @    @        @    @ @   @@ @    @        @      @    @ @    @ @    @          @    @   @@ @      @    @\n", \
	" @@@@@@ @@@@@  @    @  @@@@  @   @          @@@@  @       @@@@         @    @ @    @ @@@@@         @@@@@@  @@@@  @    @ @@@@@         @@@@@  @    @ @       @@@@\n", \
	"\n"

#define CPU_USAGE_COUNTERS \
	"CPU usage (percentage)", \
	"CPU usage (percentage).decimals"

#define LOAD_COUNTERS \
	"Utilization of the last minute period", \
	"Utilization of the last minute period.decimals", \
	"Utilization of the last 5 minutes period", \
	"Utilization of the last 5 minutes period.decimals", \
	"Utilization of the last 10 minutes period", \
	"Utilization of the last 10 minutes period.decimals", \
	"# of currently running processe(s)", \
	"Total number of processes", \
	"Last process ID used"

#define CPU_COUNTERS \
	"jiffies in user mode (jiffy = ~4ms)", \
	"jiffies in low priority user mode - nice - (jiffy = ~4ms)", \
	"jiffies in system mode mode (jiffy = ~4ms)", \
	"jiffies in idle task mode (jiffy = ~4ms)", \
	"jiffies in IO wait (jiffy = ~4ms)", \
	"jiffies in hard IRQ - hardirq - (jiffy = ~4ms)", \
	"jiffies in soft IRQ - softirq - (jiffy = ~4ms)", \
	"jiffies in steal (jiffy = ~4ms)"

#define ASSERT \
	if(ret != PL_SUCCESS) { \
		fprintf(stderr, "PL Error code = %d\n", errno); \
		assert(0); \
	} \

//-----------------------------------------------------------------------------
// program global(s)
//-----------------------------------------------------------------------------
int stop = 0;

/*---------------------------------------------------------------------------
Function: signal_handler
Purpose : signal handler
In      : none
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
07/08/2009    Jamel Tayeb             Creation.
*/
void signal_handler(int c) { 
	switch(c) { 
	case SIGINT:
		stop = 1;
	}
} 

/*---------------------------------------------------------------------------
Function: main
Purpose : statistic collector entry point
In      : none
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
07/08/2009    Jamel Tayeb             Creation.
*/
int main(void) {

	int f_load = 0;
	int f_cpu = 0;
	int bret = -1;
	ssize_t sret = 0;
	char separators_load[] = " /\t\n";
	char separators_cpu[] = " \t\n";
	char buffer[BUFFER_SIZE] = { '\0' };
	char *token = NULL;
	unsigned long long value = 0;

	struct sigaction sa;

	char *startup[STARTUP_MESSAGE_LINES_COUNT] = { STARTUP_MESSAGE_LINES };
	unsigned long long samples = 0;
	int chars_displayed = 0;
	int i = 0;

	unsigned long long user_last = 0;
	unsigned long long nice_last = 0;
	unsigned long long system_last = 0;
	unsigned long long idle_last = 0;
	unsigned long long io_wait_last = 0;
	unsigned long long soft_irq_last = 0;
	unsigned long long hard_irq_last = 0;
	unsigned long long steal_last = 0;
	unsigned long long user = 0;
	unsigned long long nice = 0;
	unsigned long long system = 0;
	unsigned long long idle = 0;
	unsigned long long io_wait = 0;
	unsigned long long soft_irq = 0;
	unsigned long long hard_irq = 0;
	unsigned long long steal = 0;

	unsigned long long usage_percentage = 0;
	long double usage_time = 0;
	long double total_time = 0;

	PL_STATUS ret = PL_FAILURE;
	int pld = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	char application_name[] = APPLICATION_NAME;

	const char *counters_names[COUNTERS_COUNT] = { 
		CPU_USAGE_COUNTERS, 
		LOAD_COUNTERS, 
		CPU_COUNTERS, 
	};

	enum counters_indexes { 
		CPU_USAGE_PERCENTAGE_INDEX = 0, 
		CPU_USAGE_PERCENTAGE_DECIMALS_INDEX,

		CPU_AND_IO_UTILIZATION_OF_THE_LAST_MINUTE_PERIOD_INDEX, 
		CPU_AND_IO_UTILIZATION_OF_THE_LAST_MINUTE_PERIOD_DECIMALS_INDEX,
		CPU_AND_IO_UTILIZATION_OF_THE_LAST_FIVE_MINUTES_PERIOD_INDEX, 
		CPU_AND_IO_UTILIZATION_OF_THE_LAST_FIVE_MINUTES_PERIOD_DECIMALS_INDEX, 
		CPU_AND_IO_UTILIZATION_OF_THE_LAST_TEN_MINUTES_PERIOD_INDEX, 
		CPU_AND_IO_UTILIZATION_OF_THE_LAST_TEN_MINUTES_PERIOD_DECIMALS_INDEX,
		NUMBER_OF_CURRENTLY_RUNNING_PROCESSES_INDEX, 
		TOTAL_NUMBER_OF_PROCESSES_INDEX, 
		LAST_PROCESS_ID_USED_INDEX,
		
		JIFFIES_IN_USER_MODE_INDEX,
		JIFFIES_IN_LOW_PRIORITY_USER_MODE_INDEX, 
		JIFFIES_IN_SYSTEM_MODE_MODE_INDEX,
		JIFFIES_IN_IDLE_TASK_MODE_INDEX, 
		JIFFIES_IN_IO_WAIT_INDEX, 
		JIFFIES_IN_HARDIRQ_INDEX,
		JIFFIES_IN_SOFTIRQ_INDEX, 
		JIFFIES_IN_STEAL_INDEX
	};

	//------------------------------------------------------------------------
	// print startup message to stdout
	//------------------------------------------------------------------------
	for(i = 0; i < STARTUP_MESSAGE_LINES_COUNT; i++) {
		fprintf(stdout, "%s", startup[i]);
	}

	//------------------------------------------------------------------------
	// instal signal handler
	//------------------------------------------------------------------------
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags = 0;
	bret = sigaction(SIGINT, &sa, NULL);
	assert(bret != -1);

	//------------------------------------------------------------------------
	// open PL
	//------------------------------------------------------------------------
	pld = pl_open(application_name, COUNTERS_COUNT, counters_names, &uuid);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//------------------------------------------------------------------------
	// print PL and use message to stdout
	//------------------------------------------------------------------------
	memset(buffer, 0, sizeof(buffer));
	uuid_unparse(uuid, buffer);
	fprintf(stdout, "Using PL.........: [%s]\n", buffer);
	fprintf(stdout, "Exporting........:\n");
	for(i = 0; i < COUNTERS_COUNT; i++) {
		fprintf(stdout, ".................: [%s]\n", counters_names[i]);
	}
	fprintf(stdout, "To Stop Logging  : [<CRTL>+<C>]\n");

	//------------------------------------------------------------------------
	// write static PL counters
	//------------------------------------------------------------------------
	value = 2;
	ret = pl_write(pld, &value, CPU_USAGE_PERCENTAGE_DECIMALS_INDEX); ASSERT;
	ret = pl_write(pld, &value, CPU_AND_IO_UTILIZATION_OF_THE_LAST_MINUTE_PERIOD_DECIMALS_INDEX); ASSERT;
	ret = pl_write(pld, &value, CPU_AND_IO_UTILIZATION_OF_THE_LAST_FIVE_MINUTES_PERIOD_DECIMALS_INDEX); ASSERT;
	ret = pl_write(pld, &value, CPU_AND_IO_UTILIZATION_OF_THE_LAST_TEN_MINUTES_PERIOD_DECIMALS_INDEX); ASSERT;

	//------------------------------------------------------------------------
	// read and export data every second
	//------------------------------------------------------------------------
	while(stop == 0) {

		//--------------------------------------------------------------------
		// start with load data
		//--------------------------------------------------------------------
		f_load = open(DATA_SOURCE_LOAD, O_RDONLY);
		assert(f_load != -1);
		memset(buffer, 0,  BUFFER_SIZE);
		sret = read(f_load, buffer, BUFFER_SIZE);
		assert(sret != -1);
		// last minute load
		token = strtok(buffer, separators_load);
		if(token != NULL) {		
			value = (unsigned long long)(atof(token) * SCALING);
			ret = pl_write(pld, &value, CPU_AND_IO_UTILIZATION_OF_THE_LAST_MINUTE_PERIOD_INDEX); ASSERT;
		}
		// last five minutes load
		token = strtok(NULL, separators_load);
		if(token != NULL) {				
			value = (unsigned long long)(atof(token) * SCALING);
			ret = pl_write(pld, &value, CPU_AND_IO_UTILIZATION_OF_THE_LAST_FIVE_MINUTES_PERIOD_INDEX); ASSERT;
		}
		// last ten minutes load
		token = strtok(NULL, separators_load);
		if(token != NULL) {				
			value = (unsigned long long)(atof(token) * SCALING);
			ret = pl_write(pld, &value, CPU_AND_IO_UTILIZATION_OF_THE_LAST_TEN_MINUTES_PERIOD_INDEX); ASSERT;
		}
		// running processes
		token = strtok(NULL, separators_load);
		if(token != NULL) {				
			value = (unsigned long long)atoi(token);
			ret = pl_write(pld, &value, NUMBER_OF_CURRENTLY_RUNNING_PROCESSES_INDEX); ASSERT;
		}
		// total number of precesses
		token = strtok(NULL, separators_load);
		if(token != NULL) {				
			value = (unsigned long long)atoi(token);
			ret = pl_write(pld, &value, TOTAL_NUMBER_OF_PROCESSES_INDEX); ASSERT;
		}
		// last process id used
		token = strtok(NULL, separators_load);
		if(token != NULL) {				
			value = (unsigned long long)atoi(token);
			ret = pl_write(pld, &value, LAST_PROCESS_ID_USED_INDEX); ASSERT;
		}
		bret = close(f_load);
		assert(bret != -1);

		//--------------------------------------------------------------------
		// continue with cpu data
		//--------------------------------------------------------------------
		f_cpu = open(DATA_SOURCE_CPU, O_RDONLY);
		assert(f_cpu != -1);
		memset(buffer, 0,  BUFFER_SIZE);
		sret = read(f_cpu, buffer, BUFFER_SIZE);
		assert(sret != -1);
		token = strtok(buffer, separators_cpu);
		while(token != NULL) {
			if(strcmp(token, CPU_TO_MONITOR) == 0) {
				// jiffies in user mode
				token = strtok(NULL, separators_cpu);
				if(token != NULL) {				
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, JIFFIES_IN_USER_MODE_INDEX); ASSERT;
					user_last = user;
					user = value;
				}
				// jiffies in low priority user mode - nice
				token = strtok(NULL, separators_cpu);
				if(token != NULL) {				
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, JIFFIES_IN_LOW_PRIORITY_USER_MODE_INDEX); ASSERT;
					nice_last = nice;
					nice = value;
				}
				// jiffies in system mode mode
				token = strtok(NULL, separators_cpu);
				if(token != NULL) {				
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, JIFFIES_IN_SYSTEM_MODE_MODE_INDEX); ASSERT;
					system_last = system;
					system = value;
				}
				// jiffies in idle task mode
				token = strtok(NULL, separators_cpu);
				if(token != NULL) {				
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, JIFFIES_IN_IDLE_TASK_MODE_INDEX); ASSERT;
					idle_last = idle;
					idle = value;
				}
				// jiffies in IO wait
				token = strtok(NULL, separators_cpu);
				if(token != NULL) {				
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, JIFFIES_IN_IO_WAIT_INDEX); ASSERT;
					io_wait_last = io_wait;
					io_wait = value;
				}
				// jiffies in IRQ - hardirq
				token = strtok(NULL, separators_cpu);
				if(token != NULL) {				
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, JIFFIES_IN_HARDIRQ_INDEX); ASSERT;
					hard_irq_last = hard_irq;
					hard_irq = value;
				}
				// jiffies in IRQ - softirq
				token = strtok(NULL, separators_cpu);
				if(token != NULL) {				
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, JIFFIES_IN_SOFTIRQ_INDEX); ASSERT;
					soft_irq_last = soft_irq;
					soft_irq = value;
				}
				// jiffies in steal
				token = strtok(NULL, separators_cpu);
				if(token != NULL) {				
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, JIFFIES_IN_STEAL_INDEX); ASSERT;
					steal_last = steal;
					steal = value;
				}
				goto found;
			}
			token = strtok(NULL, separators_cpu);
		}
found:
		bret = close(f_cpu);
		assert(bret != -1);

		//-------------------------------------------------------------------
		// compute cpu utilization %
		//-------------------------------------------------------------------
		usage_time = (long double)(
			(user - user_last) + 
			(nice - nice_last) + 
			(system - system_last) + 
			(soft_irq - soft_irq_last) +
			(hard_irq - hard_irq_last) +
			(steal - steal_last)
		);
		total_time = (long double)(
			usage_time + 
			(idle - idle_last) +
			(io_wait - io_wait_last)
		);
		usage_percentage = (unsigned long long)(100.0 * usage_time / total_time) * 100;
		ret = pl_write(pld, &usage_percentage, CPU_USAGE_PERCENTAGE_INDEX); ASSERT;

		//-------------------------------------------------------------------
		// increment sample(s) count
		//-------------------------------------------------------------------
		samples++;

		//-------------------------------------------------------------------
		// print to stdout the sample count
		//-------------------------------------------------------------------
		chars_displayed = fprintf(stdout, "Samples          : [%llu]", samples);
		fflush(stdout);
		for(i = 0; i < chars_displayed; i++) { fprintf(stdout, "\b"); }

		//-------------------------------------------------------------------
		// sleep for a second
		//-------------------------------------------------------------------
		sleep(1);
	}

	//------------------------------------------------------------------------
	// close PL
	//------------------------------------------------------------------------
	ret = pl_close(pld); ASSERT;
	return(PL_SUCCESS);
}
