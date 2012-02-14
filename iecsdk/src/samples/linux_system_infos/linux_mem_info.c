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
#define APPLICATION_NAME "Linux Mem Info"
#define DATA_SOURCE "/proc/meminfo"
#define COUNTERS_COUNT 28
#define BUFFER_SIZE 4096

#define STARTUP_MESSAGE_LINES_COUNT 9
#define STARTUP_MESSAGE_LINES \
	"\n", \
	" @      @@@@@  @    @ @    @ @   @         @    @ @@@@@@ @    @        @@@@@  @    @ @@@@@@  @@@@\n", \
	" @        @    @@   @ @    @  @ @          @@  @@ @      @@  @@          @    @@   @ @      @    @\n", \
	" @        @    @ @  @ @    @   @           @ @@ @ @      @ @@ @          @    @ @  @ @      @    @\n", \
	" @        @    @ @  @ @    @   @           @    @ @@@@@@ @    @          @    @ @  @ @@@@@  @    @\n", \
	" @        @    @  @ @ @    @   @           @    @ @      @    @          @    @  @ @ @      @    @\n", \
	" @        @    @   @@ @    @  @ @          @    @ @      @    @          @    @   @@ @      @    @\n", \
	" @@@@@@ @@@@@  @    @  @@@@  @   @         @    @ @@@@@@ @    @        @@@@@  @    @ @       @@@@\n", \
	"\n"

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

	int f = 0;
	int i = 0;
	int bret = -1;
	ssize_t sret = 0;
	char separators[] = " \t\n:kB";
	char buffer[BUFFER_SIZE] = { '\0' };
	char *token = NULL;
	unsigned long long value = 0;

	struct sigaction sa;

	char *startup[STARTUP_MESSAGE_LINES_COUNT] = { STARTUP_MESSAGE_LINES };
	unsigned long long samples = 0;
	int chars_displayed = 0;

	PL_STATUS ret = PL_FAILURE;
	int pld = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	char application_name[] = APPLICATION_NAME;
	const char *counters_names[COUNTERS_COUNT] = { 
		"MemTotal", "MemFree", "Buffers", "Cached", "SwapCached", "Active",
		"Inactive", "HighTotal", "HighFree", "LowTotal", "LowFree", "SwapTotal",
		"SwapFree", "Dirty", "Writeback", "AnonPages", "Mapped", "Slab",
		"CommitLimit", "Committed_AS", "PageTables", "VmallocTotal", "VmallocUsed",
		"VmallocChunk", "HugePages_Total", "HugePages_Free", "HugePages_Rsvd", "Hugepagesize"
	};
	enum counters_indexes { 
		MEMTOTAL_INDEX = 0, MEMFREE_INDEX, BUFFERS_INDEX, CACHED_INDEX, SWAPCACHED_INDEX, ACTIVE_INDEX,
		INACTIVE_INDEX, HIGHTOTAL_INDEX, HIGHFREE_INDEX, LOWTOTAL_INDEX, LOWFREE_INDEX, SWAPTOTAL_INDEX,
		SWAPFREE_INDEX, DIRTY_INDEX, WRITEBACK_INDEX, ANONPAGES_INDEX, MAPPED_INDEX, SLAB_INDEX,
		COMMITLIMIT_INDEX, COMMITTED_AS_INDEX, PAGETABLES_INDEX, VMALLOCTOTAL_INDEX, VMALLOCUSED_INDEX,
		VMALLOCCHUNK_INDEX, HUGEPAGES_TOTAL_INDEX, HUGEPAGES_FREE_INDEX, HUGEPAGES_RSVD_INDEX, HUGEPAGESIZE_INDEX
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
	// read and export data every second
	//------------------------------------------------------------------------
	while(stop == 0) {
		f = open(DATA_SOURCE, O_RDONLY);
		assert(f != -1);
		memset(buffer, 0,  BUFFER_SIZE);
		sret = read(f, buffer, BUFFER_SIZE);
		assert(sret != -1);
		token = strtok(buffer, separators);
		while(token != NULL) {
			for(i = 0; i < COUNTERS_COUNT; i++) {
				if(strcmp(token, counters_names[i]) == 0) { 
					token = strtok(NULL, separators);
					value = (unsigned long long)atoi(token);
					ret = pl_write(pld, &value, i); ASSERT;
					goto found;
				}
			}
found:
			token = strtok(NULL, separators);
		}
		bret = close(f);
		assert(bret != -1);

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
