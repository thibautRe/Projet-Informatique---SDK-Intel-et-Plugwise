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
#include <assert.h>
#include <stdio.h>
#ifdef __PL_WINDOWS__
	#include <windows.h>
	#include <tchar.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
	#include <string.h>
	#include <unistd.h>
	#include <errno.h>
	#include <uuid/uuid.h>
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
int main(void) {

	//-------------------------------------------------------------------------
	// Generic variables.
	//-------------------------------------------------------------------------
	int i = 0;
	int ret;

	//-------------------------------------------------------------------------
	// PL management variables.
	//-------------------------------------------------------------------------
	uuid_t pl;
	int pld = PL_INVALID_DESCRIPTOR;

	//-------------------------------------------------------------------------
	// UUID unpase data
	//-------------------------------------------------------------------------
	char data[PL_UUID_MAX_CHARS + 1] = { '\0' };
#ifdef __PL_WINDOWS__
	char *p = NULL;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
	char buffer[MAX_BUFFER_SIZE] = { '\0' };
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Counter data management variables.
	//-------------------------------------------------------------------------
	const char *my_counters[MAX_COUNTERS] = COUNTER_STRINGS;
#ifdef __PL_WINDOWS__
	ULONGLONG performance = 0;
	ULONGLONG work_units = 0;
	ULONGLONG counter_1 = 0;
	ULONGLONG counter_2 = 0;
	ULONGLONG counter_3 = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
	unsigned long long performance = 0;
	unsigned long long work_units = 0;
	unsigned long long counter_1 = 0;
	unsigned long long counter_2 = 0;
	unsigned long long counter_3 = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Open PL.
	//-------------------------------------------------------------------------
	pld = pl_open(
		APPLICATION_NAME_STRING, 
		MAX_COUNTERS, 
		my_counters, 
		&pl
	);
	if(pld == PL_INVALID_DESCRIPTOR) {
#ifdef __PL_WINDOWS__
		fprintf(
			stdout,
			"pl_open() error: [%d]d - [%x]h\n", 
			GetLastError(),
			GetLastError()
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
		fprintf(
			stdout,
			"pl_open() error: [%d]d - [%x]h\n", 
			errno,
			errno
		);
		fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		assert(0);
	}

	//-------------------------------------------------------------------------
	// Unparse UUID.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	UuidToString(
		&pl, 
		(RPC_WSTR *)&p
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
	uuid_unparse(
		pl, 
		buffer
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Display PL UUID.
	//-------------------------------------------------------------------------
	printf("\n*******************************************************\n");
#ifdef __PL_WINDOWS__
	wprintf(
		_T(
		"Using power link directory: %s\n"), 
		p
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
	printf(
		"Using power link directory: %s\n", 
		buffer
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// HEX dump UUID.
	//-------------------------------------------------------------------------
	memcpy(
		data,
		&pl,
		16
	);
	printf("UUID: [ ");
	for(i = 0; i < 16; i++) {
		printf(
			"%02X ", 
			(unsigned char)data[i]
		);
	}
	printf("\b]\n");
	printf("*******************************************************\n\n");

	//-------------------------------------------------------------------------
	// Write PL counters ITERATIONS times.
	//-------------------------------------------------------------------------
	for(i = 0; i < ITERATIONS; i++) {

		//---------------------------------------------------------------------
		// Update counter data.
		//---------------------------------------------------------------------
		work_units++;
		performance++;
		counter_1++;
		counter_2++;
		counter_3++;

		//---------------------------------------------------------------------
		// Pause and echo iteration and work data.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		Sleep(PAUSE);
		printf(
			"Iteration %d\twork units: %I64u\n", 
			i, 
			work_units
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
		sleep(PAUSE);
		printf(
			"Iteration %d\twork units: %llu\n", 
			i, 
			work_units
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Write counters.
		//---------------------------------------------------------------------
#ifndef __PL_BLOCKING_COUNTER_FILE_LOCK__
		ret = pl_write(
			pld, 
			&performance, 
			PERFORMANCE
		); 
		check(ret);
		ret = pl_write(
			pld, 
			&counter_1, 
			UNNAMED_1
		); 
		check(ret);
		ret = pl_write(
			pld, 
			&work_units, 
			WORK_UNITS
		); 
		check(ret);
		ret = pl_write(
			pld, 
			&counter_2, 
			UNNAMED_2
		); 
		check(ret);
		ret = pl_write(
			pld, 
			&counter_3, 
			UNNAMED_3
		); 
		check(ret);
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__
		ret = pl_write(
			pld, 
			&performance, 
			PERFORMANCE
		);
		if(ret != PL_SUCCESS) {
#ifdef __PL_WINDOWS__
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				GetLastError(),
				GetLastError()
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				errno,
				errno
			);
			fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			assert(0);
		}
		ret = pl_write(
			pld, 
			&counter_1, 
			UNNAMED_1
		); 
		if(ret != PL_SUCCESS) {
#ifdef __PL_WINDOWS__
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				GetLastError(),
				GetLastError()
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				errno,
				errno
			);
			fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			assert(0);
		}
		ret = pl_write(
			pld, 
			&work_units, 
			WORK_UNITS
		); 
		if(ret != PL_SUCCESS) {
#ifdef __PL_WINDOWS__
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				GetLastError(),
				GetLastError()
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				errno,
				errno
			);
			fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			assert(0);
		}
		ret = pl_write(
			pld, 
			&counter_2, 
			UNNAMED_2
		); 
		if(ret != PL_SUCCESS) {
#ifdef __PL_WINDOWS__
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				GetLastError(),
				GetLastError()
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				errno,
				errno
			);
			fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			assert(0);
		}
		ret = pl_write(
			pld, 
			&counter_3, 
			UNNAMED_3
		); 
		if(ret != PL_SUCCESS) {
#ifdef __PL_WINDOWS__
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				GetLastError(),
				GetLastError()
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			fprintf(
				stdout,
				"pl_write() error: [%d]d - [%x]h\n", 
				errno,
				errno
			);
			fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			assert(0);
		}
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
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
#ifdef __PL_WINDOWS
	RpcStringFree(&p);
#endif // __PL_WINDOWS__
	return(0);
}
