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
#define APPLICATION_NAME "Linux VM Stat Info"
#define DATA_SOURCE "/proc/vmstat"
#define COUNTERS_COUNT 44
#define BUFFER_SIZE 4096

#define STARTUP_MESSAGE_LINES_COUNT 9
#define STARTUP_MESSAGE_LINES \
	"\n", \
	" @      @@@@@  @    @ @    @ @   @         @    @ @    @         @@@@   @@@@@   @@    @@@@@        @@@@@  @    @ @@@@@@  @@@@\n", \
	" @        @    @@   @ @    @  @ @          @    @ @@  @@        @    @    @    @  @     @            @    @@   @ @      @    @\n", \
	" @        @    @ @  @ @    @   @           @    @ @ @@ @        @         @   @    @    @            @    @ @  @ @      @    @\n", \
	" @        @    @ @  @ @    @   @           @    @ @    @         @@@@     @   @    @    @            @    @ @  @ @@@@@  @    @\n", \
	" @        @    @  @ @ @    @   @            @   @ @    @             @    @   @@@@@@    @            @    @  @ @ @      @    @\n", \
	" @        @    @   @@ @    @  @ @            @ @  @    @             @    @   @    @    @            @    @   @@ @      @    @\n", \
	" @@@@@@ @@@@@  @    @  @@@@  @   @            @   @    @        @@@@@     @   @    @    @          @@@@@  @    @ @       @@@@\n", \
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
	char separators[] = " \t\n";
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
		"nr_dirty", "nr_writeback", "nr_unstable", "nr_page_table_pages", "nr_anon_pages", "nr_mapped",
		"nr_slab", "pgpgin", "pgpgout", "pswpin", "pswpout", "pgalloc_high",
		"pgalloc_normal", "pgalloc_dma32", "pgalloc_dma", "pgfree", "pgactivate", "pgdeactivate",
		"pgfault", "pgmajfault", "pgrefill_high", "pgrefill_normal", "pgrefill_dma32", "pgrefill_dma",
		"pgsteal_high", "pgsteal_normal", "pgsteal_dma32", "pgsteal_dma", "pgscan_kswapd_high", "pgscan_kswapd_normal",
		"pgscan_kswapd_dma32", "pgscan_kswapd_dma", "pgscan_direct_high", "pgscan_direct_normal", "pgscan_direct_dma32", "pgscan_direct_dma",
		"pginodesteal", "slabs_scanned", "kswapd_steal", "kswapd_inodesteal", "pageoutrun", "allocstall",
		"pgrotated", "nr_bounce"
	};
	enum counters_indexes { 
		NR_DIRTY_INDEX, NR_WRITEBACK_INDEX, NR_UNSTABLE_INDEX, NR_PAGE_TABLE_PAGES_INDEX, NR_ANON_PAGES_INDEX, NR_MAPPED_INDEX,
		NR_SLAB_INDEX, PGPGIN_INDEX, PGPGOUT_INDEX, PSWPIN_INDEX, PSWPOUT_INDEX, PGALLOC_HIGH_INDEX,
		PGALLOC_NORMAL_INDEX, PGALLOC_DMA32_INDEX, PGALLOC_DMA_INDEX, PGFREE_INDEX, PGACTIVATE_INDEX, PGDEACTIVATE_INDEX,
		PGFAULT_INDEX, PGMAJFAULT_INDEX, PGREFILL_HIGH_INDEX, PGREFILL_NORMAL_INDEX, PGREFILL_DMA32_INDEX, PGREFILL_DMA_INDEX,
		PGSTEAL_HIGH_INDEX, PGSTEAL_NORMAL_INDEX, PGSTEAL_DMA32_INDEX, PGSTEAL_DMA_INDEX, PGSCAN_KSWAPD_HIGH_INDEX, PGSCAN_KSWAPD_NORMAL_INDEX,
		PGSCAN_KSWAPD_DMA32_INDEX, PGSCAN_KSWAPD_DMA_INDEX, PGSCAN_DIRECT_HIGH_INDEX, PGSCAN_DIRECT_NORMAL_INDEX, PGSCAN_DIRECT_DMA32_INDEX, PGSCAN_DIRECT_DMA_INDEX,
		PGINODESTEAL_INDEX, SLABS_SCANNED_INDEX, KSWAPD_STEAL_INDEX, KSWAPD_INODESTEAL_INDEX, PAGEOUTRUN_INDEX, ALLOCSTALL_INDEX,
		PGROTATED_INDEX, NR_BOUNCE_INDEX
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
