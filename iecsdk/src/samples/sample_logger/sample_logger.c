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

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <windows.h>
#include <tchar.h>
#include "productivity_link.h"

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define MAX_COUNTERS 2
#define MAX_BUFFER_SIZE 1024
#define ASCIITIME_NEWLINE_POS 24
#define SAMPLING_FREQUENCY 1000
#define FLUSH_TRIGGER 10
#define WORK 0
#define ENERGY 0

//-----------------------------------------------------------------------------
// functions prototypes
//-----------------------------------------------------------------------------
BOOL control_handler(DWORD);

//-----------------------------------------------------------------------------
// program globals
//-----------------------------------------------------------------------------
int pld_work = PL_INVALID_DESCRIPTOR;
int pld_energy = PL_INVALID_DESCRIPTOR;
FILE* log_file = NULL;

//-----------------------------------------------------------------------------
// program entry point
//-----------------------------------------------------------------------------
int main(void) {

	int i = 0;
	int ret = PL_FAILURE;
	char file_work[PL_MAX_PATH];
	char file_energy[PL_MAX_PATH];
	char log_file_file[PL_MAX_PATH];
	char buffer[MAX_BUFFER_SIZE];
	struct tm *l_time;
	size_t st_ret = 0;
	BOOL bret = FALSE;
	time_t clock;
	OPENFILENAME ofn;
	TCHAR t_file[PL_MAX_PATH];

	ULONGLONG work = 0;
	ULONGLONG energy = 0;
	ULONGLONG sample = 0;

	ZeroMemory(t_file, sizeof(t_file));
	ZeroMemory(&ofn, sizeof(ofn));
	ZeroMemory(file_work, sizeof(file_work));
	ZeroMemory(file_energy, sizeof(file_energy));
	ZeroMemory(log_file_file, sizeof(log_file_file));

	fprintf(stdout, "Select the PL configuration file for the work counter.\n");

	//-----------------------------------------------------------------------------
	// browse for the PL config file (PL) - work counter source
	//-----------------------------------------------------------------------------
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = t_file;
	ofn.nMaxFile = sizeof(t_file);
	ofn.lpstrFilter = _T("PL Configuration File\0*.INI\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	bret = GetOpenFileName(&ofn);
	assert(bret);
	wcstombs_s(&st_ret, file_work, sizeof(file_work), ofn.lpstrFile, _TRUNCATE);

	//-----------------------------------------------------------------------------
	// attach to the counters (PL)
	//-----------------------------------------------------------------------------
	pld_work = pl_attach(file_work);
	assert(pld_work != PL_INVALID_DESCRIPTOR);

	ZeroMemory(t_file, sizeof(t_file));
	ZeroMemory(&ofn, sizeof(ofn));

	fprintf(stdout, "Select the PL configuration file for the energy counter.\n");

	//-----------------------------------------------------------------------------
	// browse for the PL config file (PL) - energy counter source
	//-----------------------------------------------------------------------------
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = t_file;
	ofn.nMaxFile = sizeof(t_file);
	ofn.lpstrFilter = _T("PL Configuration File\0*.INI\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	bret = GetOpenFileName(&ofn);
	assert(bret);
	wcstombs_s(&st_ret, file_energy, sizeof(file_energy), ofn.lpstrFile, _TRUNCATE);

	//-----------------------------------------------------------------------------
	// attach to the counters (PL)
	//-----------------------------------------------------------------------------
	pld_energy = pl_attach(file_energy);
	assert(pld_work != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------------
	// install the event handler routine
	//-----------------------------------------------------------------------------
	bret = SetConsoleCtrlHandler((PHANDLER_ROUTINE)control_handler, TRUE);
	assert(bret);

	ZeroMemory(t_file, sizeof(t_file));
	ZeroMemory(&ofn, sizeof(ofn));

	fprintf(stdout, "Select the log_file file name and location.\n");

	//-----------------------------------------------------------------------------
	// browse for log_file file (save)
	//-----------------------------------------------------------------------------
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = t_file;
	ofn.nMaxFile = sizeof(t_file);
	ofn.lpstrFilter = _T("Comma Separated Value File\0*.CSV\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	bret = GetSaveFileName(&ofn);
	assert(bret);
	wcstombs_s(&st_ret, log_file_file, sizeof(log_file_file), ofn.lpstrFile, _TRUNCATE);

	//-----------------------------------------------------------------------------
	// open the log_file file
	//-----------------------------------------------------------------------------
	log_file = fopen(log_file_file, "w+");
	assert(log_file);

	//-----------------------------------------------------------------------------
	// direction on how to stop log_fileging.
	//-----------------------------------------------------------------------------
	fprintf(stdout, "Logging. <CTRL>+<C> to stop log_fileging.\n");
	fprintf(stdout, "Using [%s] + [%s] -> [%s]\n", file_work, file_energy, log_file_file);

	//-----------------------------------------------------------------------------
	// write log_file file header
	//-----------------------------------------------------------------------------
	ZeroMemory(buffer, sizeof(buffer));
	sprintf(buffer, "Time Stamps, Sample Count, Work, Energy\n");
	fwrite(buffer, sizeof(char), strlen(buffer), log_file);

	//-----------------------------------------------------------------------------
	// loop while interrupted by user
	//-----------------------------------------------------------------------------
	while(TRUE) {
		
		Sleep(SAMPLING_FREQUENCY);

		//-----------------------------------------------------------------------------
		// fliush the log_file file
		//-----------------------------------------------------------------------------
		if(i++ == FLUSH_TRIGGER) {
			i = 0;
			fflush(log_file);
		}

		//-----------------------------------------------------------------------------
		// read counters from the PL
		//-----------------------------------------------------------------------------
		ret = pl_read(pld_work, &work, WORK); assert(ret == PL_SUCCESS);
		ret = pl_read(pld_energy, &energy, ENERGY); assert(ret == PL_SUCCESS);

		//-----------------------------------------------------------------------------
		// prepare time stamp
		//-----------------------------------------------------------------------------
		time(&clock);
		l_time = localtime(&clock);

		//-----------------------------------------------------------------------------
		// write record into the log_file file
		//-----------------------------------------------------------------------------
		ZeroMemory(buffer, sizeof(buffer));
		sprintf(buffer, "%s %I64u, %I64u, %I64u\n", asctime(l_time), sample++, work, energy);
		buffer[ASCIITIME_NEWLINE_POS] = ',';
		fwrite(buffer, sizeof(char), strlen(buffer), log_file);

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

	switch(c) { 

		case CTRL_C_EVENT: 

			//-----------------------------------------------------------------------------
			// measure energy consumed at the end of the run and display it
			//-----------------------------------------------------------------------------
			fprintf(stdout, "Stopping Logger.\n");

			//-----------------------------------------------------------------------------
			// close Productivity Link
			//-----------------------------------------------------------------------------
			ret = pl_close(pld_work);
			assert(ret == PL_SUCCESS);
			ret = pl_close(pld_energy);
			assert(ret == PL_SUCCESS);

			//-----------------------------------------------------------------------------
			// house keeping
			//-----------------------------------------------------------------------------
			fclose(log_file);
			return(FALSE);

		default: 
			return(FALSE); 
	} 
}
