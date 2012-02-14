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

/**
*** This sample imports a Microsoft Windows hosted counter and axports it 
*** using Productivity Link.
***
**/

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <assert.h>
#include <pdh.h>
#include "productivity_link.h"

#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "Rpcrt4.lib")

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define UPDATE_FREQUENCY 1000 // 1 second
#define APPLICATION_NAME "CPU_Utilization_Histogram"
#define MAX_COUNTERS 103
#define MAX_CPU_UTILIZATION_COUNTERS 101
#define CPU_UTILIZATION_MIN MAX_CPU_UTILIZATION_COUNTERS
#define CPU_UTILIZATION_MAX MAX_CPU_UTILIZATION_COUNTERS + 1
#define COUNTERS_NAMES { \
	"CPU_Utilization_000", \
	"CPU_Utilization_001", \
	"CPU_Utilization_002", \
	"CPU_Utilization_003", \
	"CPU_Utilization_004", \
	"CPU_Utilization_005", \
	"CPU_Utilization_006", \
	"CPU_Utilization_007", \
	"CPU_Utilization_008", \
	"CPU_Utilization_009", \
	"CPU_Utilization_010", \
	"CPU_Utilization_011", \
	"CPU_Utilization_012", \
	"CPU_Utilization_013", \
	"CPU_Utilization_014", \
	"CPU_Utilization_015", \
	"CPU_Utilization_016", \
	"CPU_Utilization_017", \
	"CPU_Utilization_018", \
	"CPU_Utilization_019", \
	"CPU_Utilization_020", \
	"CPU_Utilization_021", \
	"CPU_Utilization_022", \
	"CPU_Utilization_023", \
	"CPU_Utilization_024", \
	"CPU_Utilization_025", \
	"CPU_Utilization_026", \
	"CPU_Utilization_027", \
	"CPU_Utilization_028", \
	"CPU_Utilization_029", \
	"CPU_Utilization_030", \
	"CPU_Utilization_031", \
	"CPU_Utilization_032", \
	"CPU_Utilization_033", \
	"CPU_Utilization_034", \
	"CPU_Utilization_035", \
	"CPU_Utilization_036", \
	"CPU_Utilization_037", \
	"CPU_Utilization_038", \
	"CPU_Utilization_039", \
	"CPU_Utilization_040", \
	"CPU_Utilization_041", \
	"CPU_Utilization_042", \
	"CPU_Utilization_043", \
	"CPU_Utilization_044", \
	"CPU_Utilization_045", \
	"CPU_Utilization_046", \
	"CPU_Utilization_047", \
	"CPU_Utilization_048", \
	"CPU_Utilization_049", \
	"CPU_Utilization_050", \
	"CPU_Utilization_051", \
	"CPU_Utilization_052", \
	"CPU_Utilization_053", \
	"CPU_Utilization_054", \
	"CPU_Utilization_055", \
	"CPU_Utilization_056", \
	"CPU_Utilization_057", \
	"CPU_Utilization_058", \
	"CPU_Utilization_059", \
	"CPU_Utilization_060", \
	"CPU_Utilization_061", \
	"CPU_Utilization_062", \
	"CPU_Utilization_063", \
	"CPU_Utilization_064", \
	"CPU_Utilization_065", \
	"CPU_Utilization_066", \
	"CPU_Utilization_067", \
	"CPU_Utilization_068", \
	"CPU_Utilization_069", \
	"CPU_Utilization_070", \
	"CPU_Utilization_071", \
	"CPU_Utilization_072", \
	"CPU_Utilization_073", \
	"CPU_Utilization_074", \
	"CPU_Utilization_075", \
	"CPU_Utilization_076", \
	"CPU_Utilization_077", \
	"CPU_Utilization_078", \
	"CPU_Utilization_079", \
	"CPU_Utilization_080", \
	"CPU_Utilization_081", \
	"CPU_Utilization_082", \
	"CPU_Utilization_083", \
	"CPU_Utilization_084", \
	"CPU_Utilization_085", \
	"CPU_Utilization_086", \
	"CPU_Utilization_087", \
	"CPU_Utilization_088", \
	"CPU_Utilization_089", \
	"CPU_Utilization_090", \
	"CPU_Utilization_091", \
	"CPU_Utilization_092", \
	"CPU_Utilization_093", \
	"CPU_Utilization_094", \
	"CPU_Utilization_095", \
	"CPU_Utilization_096", \
	"CPU_Utilization_097", \
	"CPU_Utilization_098", \
	"CPU_Utilization_099", \
	"CPU_Utilization_100", \
	"CPU_Utilization_Min", \
	"CPU_Utilization_Max" \
}

//-----------------------------------------------------------------------------
// functions prototypes
//-----------------------------------------------------------------------------
BOOL control_handler(DWORD);

//-----------------------------------------------------------------------------
// program globals
//-----------------------------------------------------------------------------
int pld = PL_INVALID_DESCRIPTOR;
HQUERY hquery = NULL;
unsigned long long cpu_utilization[MAX_CPU_UTILIZATION_COUNTERS];
unsigned long long cpu_utilization_min = _UI64_MAX;
unsigned long long cpu_utilization_max = 0;

//-----------------------------------------------------------------------------
// program entry point
//-----------------------------------------------------------------------------
int main(void) {

	int ret = 0;
	uuid_t pl;
	BOOL bret = FALSE;
	RPC_STATUS rpc_status = RPC_S_OK;
	PDH_STATUS status = 0;
	HCOUNTER handle = NULL;
	PDH_FMT_COUNTERVALUE counter_value;

	char *counters[MAX_COUNTERS] = COUNTERS_NAMES;
	TCHAR windows_counter[] = _T("\\Processor(_Total)\\% Processor Time");

	//-----------------------------------------------------------------------------
	// clear cpu utilization data
	//-----------------------------------------------------------------------------
	ZeroMemory(cpu_utilization, sizeof(cpu_utilization));

	//-----------------------------------------------------------------------------
	// install the event handler routine
	//-----------------------------------------------------------------------------
	bret = SetConsoleCtrlHandler((PHANDLER_ROUTINE)control_handler, TRUE);
	assert(bret);

	//---------------------------------------------------------------------
	// open query (Windows side)
	//---------------------------------------------------------------------
	status = PdhOpenQuery(NULL, 0, &hquery);
	assert(status == ERROR_SUCCESS);

	//-----------------------------------------------------------------
	// add counter to the query (Windows side)
	//-----------------------------------------------------------------
	status = PdhAddCounter(hquery, windows_counter, 0, &handle);
	assert(status == ERROR_SUCCESS);

	//-----------------------------------------------------------------------------
	// open a Productivity Link
	//-----------------------------------------------------------------------------
	pld = pl_open(APPLICATION_NAME, MAX_COUNTERS, counters, &pl);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------------
	// direction on how to stop monitoring.
	//-----------------------------------------------------------------------------
	fprintf(stdout, "Capturing CPU utilization.\n<CTRL>+<C> to stop monitoring and print data.\n");

	//-----------------------------------------------------------------------------
	// loop while interrupted by user
	//-----------------------------------------------------------------------------
	while(TRUE) {

		Sleep(UPDATE_FREQUENCY);

		//-----------------------------------------------------------------------------
		// read CPU utilization from the query (Windows side)
		//-----------------------------------------------------------------------------
		status = PdhCollectQueryData(hquery);
		assert(status == ERROR_SUCCESS);

		//-----------------------------------------------------------------------------
		// interprete data (Windows side)
		//-----------------------------------------------------------------------------
		status = PdhGetFormattedCounterValue(handle, PDH_FMT_LARGE, NULL, &counter_value);
		assert(status == ERROR_SUCCESS);

		//-----------------------------------------------------------------------------
		// update histogram data
		//-----------------------------------------------------------------------------
		cpu_utilization[(int)counter_value.longValue] += 1;

		//-----------------------------------------------------------------------------
		// write updated counter in the Productivity Link
		//-----------------------------------------------------------------------------
		ret = pl_write(pld, &(cpu_utilization[(int)counter_value.longValue]), counter_value.longValue);
		assert(ret == PL_SUCCESS);

		//-----------------------------------------------------------------------------
		// check min & max - update counter if changed
		//-----------------------------------------------------------------------------
		if(counter_value.longValue < cpu_utilization_min) {
			cpu_utilization_min = counter_value.longValue;
			ret = pl_write(pld, &cpu_utilization_min, CPU_UTILIZATION_MIN);
			assert(ret == PL_SUCCESS);
		}
		if(counter_value.longValue > cpu_utilization_max) {
			cpu_utilization_max = counter_value.longValue;
			ret = pl_write(pld, &cpu_utilization_max, CPU_UTILIZATION_MAX);
			assert(ret == PL_SUCCESS);
		}
	}

	//-----------------------------------------------------------------------------
	// house keeping is done in the event controller
	//-----------------------------------------------------------------------------
	return(0);
}

//-----------------------------------------------------------------------------
// event handler
//-----------------------------------------------------------------------------
BOOL control_handler(DWORD c) {

	int ret = 0;
	int i = 0;
	PDH_STATUS status = 0;

	switch(c) { 

		case CTRL_C_EVENT: 

			//-----------------------------------------------------------------------------
			// process user requested abort
			//-----------------------------------------------------------------------------
			fprintf(stdout, "Stopping Converter.\n");

			//-----------------------------------------------------------------------------
			// close query (Windows side)
			//-----------------------------------------------------------------------------
			if(hquery) {
				status = PdhCloseQuery(hquery);
				assert(status == ERROR_SUCCESS);
			}

			//-----------------------------------------------------------------------------
			// close Productivity Link
			//-----------------------------------------------------------------------------
			ret = pl_close(pld);
			assert(ret == PL_SUCCESS);

			//-----------------------------------------------------------------------------
			// dump CPU utilization data
			//-----------------------------------------------------------------------------
			fprintf(stdout, "CPU Utilization %%, Samples\n");
			fprintf(stdout, "CPU Utilization Min,%10I64u\n", cpu_utilization_min);
			fprintf(stdout, "CPU Utilization Max,%10I64u\n", cpu_utilization_max);
			for(i = 0; i < MAX_CPU_UTILIZATION_COUNTERS; i++) {
				fprintf(stdout, "%2d, %10I64u\n", i, cpu_utilization[i]);
			}
			return(FALSE);

		default: 
			return(FALSE); 
	}
}
