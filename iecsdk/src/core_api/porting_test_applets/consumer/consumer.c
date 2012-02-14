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
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
#ifdef __PL_WINDOWS__
	#include <windows.h>
	#include <tchar.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	#include <string.h>
	#include <unistd.h>
	#include <errno.h>
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"
#include "common.h"

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// check function.
//-----------------------------------------------------------------------------
void check(int ret) {
#ifdef __PL_WINDOWS__
	if(ret != PL_SUCCESS) {	
		assert(
			GetLastError() == 
			PL_COUNTER_FILE_ALREADY_LOCKED
		); 
	}
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	if(ret != PL_SUCCESS) {	
		assert(
			errno == 
			PL_COUNTER_FILE_ALREADY_LOCKED
		); 
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

//-----------------------------------------------------------------------------
// Program entry point - main
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

	//-------------------------------------------------------------------------
	// Generic variables.
	//-------------------------------------------------------------------------
	int i = 0;
	int ret = PL_FAILURE;
#ifdef __PL_WINDOWS__
	BOOL b_ret = FALSE;
	size_t st_ret = 0;
	#ifdef __PL_FILESYSTEM_LESS__
		DWORD dw_ret = 0;
	#endif // __PL_FILESYSTEM_LESS__
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// PL management variables.
	//-------------------------------------------------------------------------
	int pld = PL_INVALID_DESCRIPTOR;

	//-------------------------------------------------------------------------
	// File operation management variables.
	//-------------------------------------------------------------------------
	char file[PL_MAX_PATH];
#if defined (__PL_WINDOWS__) && !defined (__PL_FILESYSTEM_LESS__)
	OPENFILENAME ofn;
	TCHAR t_file[PL_MAX_PATH];
#endif // __PL_WINDOWS__ && !__PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Counter data management variables.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	ULONGLONG performance = 0;
	ULONGLONG work_units = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	unsigned long long performance = 0;
	unsigned long long work_units = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------

#if defined (__PL_WINDOWS__) && !defined (__PL_FILESYSTEM_LESS__)

	//-------------------------------------------------------------------------
	// Open a file selection dialog box.
	//-------------------------------------------------------------------------
	ZeroMemory(
		t_file, 
		sizeof(t_file)
	);
	ZeroMemory(
		&ofn, 
		sizeof(ofn)
	);
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = t_file;
	ofn.nMaxFile = sizeof(t_file);
	ofn.lpstrFilter = _T("Productivity Link Configuration File\0*.INI\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = PL_FOLDER;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	b_ret = GetOpenFileName(&ofn);
	if(!b_ret) {
		return(1); // signal error
	}
	ZeroMemory(
		file, 
		sizeof(file)
	);
	wcstombs_s(
		&st_ret, 
		file, 
		sizeof(file), 
		ofn.lpstrFile, 
		_TRUNCATE
	);
#endif // __PL_WINDOWS__ && !__PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Check input arguments count and retrive file name (no checks on name).
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	if(argc != 2) {
		fprintf(
			stderr, 
			"\nUsage: %s <pl_config_file>\n\n", 
			argv[0]
		);
		exit(1); // signal error
	}
	memset(
		file, 
		0, 
		sizeof(file)
	);
	strncpy(
		file, 
		argv[1],
		strlen(argv[1])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#if defined (__PL_WINDOWS__) && defined (__PL_FILESYSTEM_LESS__)
	if(argc != 2) {
		fprintf(
			stderr, 
			"\nUsage: %s <pl_config_file>\n\n", 
			argv[0]
		);
		exit(1); // signal error
	}
	memset(
		file, 
		0, 
		sizeof(file)
	);
	strncpy(
		file, 
		argv[1],
		strlen(argv[1])
	);
#endif // __PL_WINDOWS__ && __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Display PL directory.
	//-------------------------------------------------------------------------
	printf("\n*******************************************************\n");
	printf("Using productivity link directory: %s\n", file);
	printf("*******************************************************\n\n");

	//-------------------------------------------------------------------------
	// Attach to PL.
	//-------------------------------------------------------------------------
	pld = pl_attach(file);
	if(pld == PL_INVALID_DESCRIPTOR) {
#ifdef __PL_WINDOWS__
		fprintf(
			stdout,
			"pl_attach() error: [%d]d - [%x]h\n", 
			GetLastError(),
			GetLastError()
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
		fprintf(
			stdout,
			"pl_attach() error: [%d]d - [%x]h\n", 
			errno,
			errno
		);
		fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		assert(0);
	}

	//-------------------------------------------------------------------------
	// Read PL counters ITERATIONS times.
	//-------------------------------------------------------------------------
	for(i = 0; i < ITERATIONS; i++) {
		printf(
			"Iteration %d\t", 
			i
		);
#ifndef __PL_BLOCKING_COUNTER_FILE_LOCK__
		ret = pl_read(
			pld, 
			&performance, 
			PERFORMANCE
		); 
		check(ret);
		ret = pl_read(
			pld, 
			&work_units, 
			WORK_UNITS
		);  
		check(ret);
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__
		ret = pl_read(
			pld, 
			&performance, 
			PERFORMANCE
		); 
		if(ret != PL_SUCCESS) {
#ifdef __PL_WINDOWS__
			fprintf(
				stdout,
				"pl_read() error: [%d]d - [%x]h\n", 
				GetLastError(),
				GetLastError()
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			fprintf(
				stdout,
				"pl_read() error: [%d]d - [%x]h\n", 
				errno,
				errno
			);
			fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			assert(0);
		}
		ret = pl_read(
			pld, 
			&work_units, 
			WORK_UNITS
		); 
		assert(ret == PL_SUCCESS);

#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__

	//-------------------------------------------------------------------------
	// Pause and echo counters values.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		Sleep(PAUSE);
		printf(
			"performance: %I64u, work_units: %I64u\n", 
			performance, 
			work_units
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
		sleep(PAUSE);
		printf(
			"performance: %lld, work_units: %lld\n", 
			performance, 
			work_units
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	} // for i

	//-------------------------------------------------------------------------
	// Clean-up.
	//-------------------------------------------------------------------------
	ret = pl_close(pld);
	if(ret != PL_SUCCESS) {
#ifdef __PL_WINDOWS__
		fprintf(
			stdout,
			"pl_close() error: [%d]d - [%x]h\n", 
			GetLastError(),
			GetLastError()
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
		fprintf(
			stdout,
			"pl_close() error: [%d]d - [%x]h\n", 
			errno,
			errno
		);
		fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		assert(0);
	} else {
		pld = PL_INVALID_DESCRIPTOR;
	}
	return(0);
}
