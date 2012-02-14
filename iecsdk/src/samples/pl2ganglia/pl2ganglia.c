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

//--force_use_gmetric --force_to_double --filter --process --decorate --boost --application esrv --guid 0a67355c-3762-4322-93df-64dfdf1b6012
//--force_use_gmetric --filter --process --decorate --boost --application esrv --guid 4dac53ab-cd29-479e-9c00-fed186d80836

//-----------------------------------------------------------------------------
// Note:
//    Build with following symboles defined.
//       __PL_WINDOWS__ | __PL_LINUX__ | __PL_SOLARIS__ | __PL_MACOSX__
//       __PL_GENERATE_INI__
//       __PL_BLOCKING_COUNTER_FILE_LOCK__
//       __PL_DYNAMIC_COUNTERS_ALLOCATION__
//       __PL_GENERATE_INI_VERSION_TAGGING__
//       __PL_GENERATE_INI_BUILD_TAGGING__
//       __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
//       __PL_EXTRA_INPUT_CHECKS__
//       (Windows: _CRT_SECURE_NO_DEPRECATE)
//       (Windows: __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___)
//-----------------------------------------------------------------------------
#include <limits.h>
#include <float.h>
#ifdef __PL_WINDOWS__
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	#include <windows.h>
	#ifdef _MSC_VER
		#pragma	message ("//-----------------------------------------------------------------------------")
		#pragma	message ("// Ganglia* is not supported on native Windows* platforms.")
		#pragma	message ("// * Third-party trademarks are the property of their respective owners.")
		#pragma	message ("//-----------------------------------------------------------------------------")
	#endif // _MSC_VER
	#ifdef __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
		#pragma comment (lib, "Winmm")
	#endif // __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
#endif // __PL_WINDOWS__

//-----------------------------------------------------------------------------
// Ganglia* is suported on:
//    Linux (Fedora/RedHat/CentOS, Debian, Gentoo, SuSE/OpenSuSE)
//    [Open]Solaris
//    FreeBSD
//    NetBSD
//    OpenBSD
//    DragonflyBSD
//    Cygwin
//    AIX
// Therefore, there is no such thing as a full Windows* or MacOS X* version.
// However, this source code provides for an hypothetic Windows and MacOS X
// version which will generate gmetric equivalent commands
// * Third-party trademarks are the property of their respective owners.
//-----------------------------------------------------------------------------
#include <assert.h>
#include <stdio.h>
#include <math.h> // for pow
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include <signal.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <pthread.h>
	#include <errno.h> // for ETIMEDOUT and EINVAL
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"
#include "productivity_link_helper.h"
#include "pl2ganglia.h"

//-----------------------------------------------------------------------------
// Globals.
//-----------------------------------------------------------------------------
PL2GANGLIA_DATA data;
PPL2GANGLIA_DATA p = &data;

/*-----------------------------------------------------------------------------
Function: main
Purpose : pl2ganglia entry point
In      : commad line arguments
Out     : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/30/2010    Jamel Tayeb             Creation.
*/
int main(int argc, char *argv[]) {
	
	//-------------------------------------------------------------------------
	// All purpose data.
	//-------------------------------------------------------------------------
	unsigned int i = 0;
	PL_STATUS ret = PL_FAILURE;
	unsigned long long samples_collected = 0;
	size_t chars_displayed = 0;
	char message_buffer[PL_MAX_PATH] = { '\0' };
	const char* banner[PL2GANGLIA_STARTUP_MESSAGE_LINES_COUNT] = {
		PL2GANGLIA_STARTUP_MESSAGE_LINES
	};

	//-------------------------------------------------------------------------
	// Timing and priority data.
	//-------------------------------------------------------------------------
	double time_to_sleep_in_ms = 0.0;
	double total_duration_in_ms = 0.0;
	double actual_measurement_time_in_ms = 0.0;
	double maximum_allowed_measurement_time_in_ms = 0.0;
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
	LARGE_INTEGER frequency;
	LARGE_INTEGER start_time;
	LARGE_INTEGER end_time;
#ifdef __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
	MMRESULT mmret = 0;
	UINT resolution = 0;
#endif // __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	pthread_t tid;
	struct sched_param param;
	struct timespec time_spec;
	struct timeval start_time;
	struct timeval end_time;
	int time_to_sleep_in_s = 0.0;
	struct timespec duration;
	struct timeval tv;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Signal handling data.
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int iret = -1;
	struct sigaction sa;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// PL and counter handling data.
	//-------------------------------------------------------------------------
	unsigned int k = 0;
	char *px = NULL;
	char counter_name_root[PL_MAX_PATH] = { '\0' };
	char pl_config_buffer[PL_MAX_PATH] = { '\0' };
	int f_error = 0;
	unsigned long long counter = 0;
	unsigned long long counter_scalar = 1;
	unsigned long long counter_scalar_decimals = 0;
	unsigned long long counter_decimals = 0;
	unsigned long long counter_sign = 0;
	unsigned long long counter_offset = 0;
	unsigned long long counter_offset_decimals = 0;
	unsigned long long counter_offset_sign = 0;
	char buffer[PL_MAX_PATH] = { '\0' };

	//-------------------------------------------------------------------------
	// Counter names filtering data.
	//-------------------------------------------------------------------------
	unsigned int j = 0;
	size_t l = 0;
	char forbidden_chars[PL2GANFLIA_COUNTER_FOBIDDEN_CHARS_COUNT] = {
		PL2GANFLIA_COUNTER_FOBIDDEN_CHARS
	};
	char allowed_chars[PL2GANFLIA_COUNTER_FOBIDDEN_CHARS_COUNT] = {
		PL2GANFLIA_COUNTER_ALLOWED_CHARS
	};
#ifdef __PL_WINDOWS__
	DWORD dw_ret = -1;
#ifdef _DEBUG

	//-------------------------------------------------------------------------

	#pragma	message("NOTE: Building a Debug version with memory leak detection.")

	//-------------------------------------------------------------------------
	// Dump memory leak info on any exit.
	//-------------------------------------------------------------------------
	dw_ret = _CrtSetDbgFlag(
		_CRTDBG_ALLOC_MEM_DF | 
		_CRTDBG_LEAK_CHECK_DF
	);
	if(dw_ret == -1) {
		p->last_error = PL2GANGLIA_UNABLE_TO_SET_MEMORY_DEBUG;
		goto pl2ganglia_error; 
	}

	//-------------------------------------------------------------------------
	// Redirect dump to stdout.
	//-------------------------------------------------------------------------
	_CrtSetReportMode(
		_CRT_WARN, 
		_CRTDBG_MODE_FILE
	);
	_CrtSetReportFile(
		_CRT_WARN, 
		_CRTDBG_FILE_STDOUT
	);
	_CrtSetReportMode(
		_CRT_ERROR, 
		_CRTDBG_MODE_FILE
	);
	_CrtSetReportFile(
		_CRT_ERROR, 
		_CRTDBG_FILE_STDOUT
	);
	_CrtSetReportMode(
		_CRT_ASSERT, 
		_CRTDBG_MODE_FILE
	);
	_CrtSetReportFile(
		_CRT_ASSERT, 
		_CRTDBG_FILE_STDOUT
	);

#endif // _DEBUG
#endif // __PL_WINDOWS__

    //-------------------------------------------------------------------------
    // Initialize data with default values.
    //-------------------------------------------------------------------------
	memset(
		&data, 
		0, 
		sizeof(data)
	);
	assert(p != NULL);
	p->f_convert = 1;
	p->pause_time = PL2GANGLIA_DEFAULT_UPDATE_INTERVAL_IN_MS;
	p->f_boost = 0;
	p->f_decorate = 0;
	p->last_error = PL2GANGLIA_NO_ERROR;
	p->pld = PL_INVALID_DESCRIPTOR;
#if defined (__PL_WINDOWS__) || (__PL_MACOSX__)

	//-------------------------------------------------------------------------
	// Note:
	//    On Windows* and MacOS* X, we force the use of gmetric since Ganglia*
	//    is not ported on them.  In this case, the gmetric command is printed
	//    to stdout for information purposes only.  The command is NOT executed.
	//    Under supported Ganglia systems, if the use of gmetric is requested by
	//    user, then the cammand is executed with no echo.  Otherwise, pl2gan-
	//    -glia will communicate directly with gmond.
	//-------------------------------------------------------------------------
	p->f_force_use_gmetric = 1;
#endif // __PL_WINDOWS__ || __PL_MACOSX__

    //-------------------------------------------------------------------------
    // Parse command line.
    //-------------------------------------------------------------------------
	ret = pl2ganglia_parse_cli(
		p, 
		argc, 
		argv
	);
	if(ret != PL_SUCCESS) {
		if(
			(p->f_help == 0) && 
			(p->f_version == 0)
		) {
			pl2ganglia_decode_error(p->last_error);
			p->last_error = PL2GANGLIA_INVALID_PARAMETERS;
			goto pl2ganglia_error;
		} else {
			goto pl2ganglia_exit;
		}
	}

    //-------------------------------------------------------------------------
    // Build the pl_config.ini file if required.
    //-------------------------------------------------------------------------
	if(
		(p->f_config == 0) &&
		(p->f_application_name == 1) &&
		(p->f_guid == 1)
	) {
		memcpy(
			pl_config_buffer, 
			PL2GANGLIA_BUILD_PL_CONFIG_FILE_ROOT, 
			strlen(PL2GANGLIA_BUILD_PL_CONFIG_FILE_ROOT)
		);
		strncat(
			pl_config_buffer, 
			p->application_name, 
			strlen(p->application_name)
		);
		strncat(
			pl_config_buffer, 
			PL2GANGLIA_BUILD_PL_CONFIG_FILE_UNDERSCORE, 
			strlen(PL2GANGLIA_BUILD_PL_CONFIG_FILE_UNDERSCORE)
		);
		strncat(
			pl_config_buffer, 
			p->guid, 
			strlen(p->guid)
		);
		strncat(
			pl_config_buffer, 
			PL2GANGLIA_BUILD_PL_CONFIG_FILE_NAME, 
			strlen(PL2GANGLIA_BUILD_PL_CONFIG_FILE_NAME)
		);
		p->config = pl_config_buffer;
		p->f_config = 1;
		p->application_name = NULL;
		p->f_application_name = 0;
		p->guid = NULL;
		p->f_guid = 0;
	}

    //-------------------------------------------------------------------------
    // Display startup banner and version info.
    //-------------------------------------------------------------------------
	for(i = 0; i < PL2GANGLIA_STARTUP_MESSAGE_LINES_COUNT; i++) {
		fprintf(
			stdout,
			banner[i]
		);
	}
	print_version_info(
		PL2GANGLIA_NAME,
		PL2GANGLIA_VERSION_MAJOR,
		PL2GANGLIA_VERSION_MINOR,
		PL2GANGLIA_VERSION_REVISION
	);
	sprintf(
		message_buffer,
		"Using Ganglia* - and gmetric if requested by user - version %s\n* Third-party trademarks are the property of their respective owners.",
		PL2GANGLIA_GANGLIA_VERSION
	);
	pl2ganglia_display(message_buffer);

	//-------------------------------------------------------------------------
	// Prepare precision timer.
	//-------------------------------------------------------------------------
#ifdef __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
	pl2ganglia_diagnostic("...High-Precision Timer Setup.");
#else // __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
	pl2ganglia_diagnostic("...Timer Setup.");
#endif // __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___

#ifdef __PL_WINDOWS__
#ifdef __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
	//-------------------------------------------------------------------------
	// Set highest possible timer resolution.
	// Note:
	//    This is not recommended option since you will generate power 
	//    hungry code
	//-------------------------------------------------------------------------
	resolution = 1; // in ms
	do {
		mmret = timeBeginPeriod(resolution++);
	} while(mmret != TIMERR_NOERROR);
	sprintf(
		message_buffer,
		"...Timer Resolution Set To [%u] ms.", 
		resolution
	);
	pl2ganglia_diagnostic(message_buffer);
#endif // __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___

	//-------------------------------------------------------------------------
	// Setup high-precision timer.
	//-------------------------------------------------------------------------
	bret = QueryPerformanceFrequency(&frequency);
	if(
		(bret == FALSE) || 
		(frequency.QuadPart == 0)
	) {
		p->last_error = PL2GANGLIA_UNABLE_TO_SETUP_HP_TIMER;
		goto pl2ganglia_error;
	} else {
		sprintf(
			message_buffer,
			"...High-Precision Timer Frequency = [%I64d] Counts Per Second.", 
			frequency.QuadPart
		);
		pl2ganglia_diagnostic(message_buffer);
	}
#endif // __PL_WINDOWS__
	maximum_allowed_measurement_time_in_ms = p->pause_time;
	sprintf(
		message_buffer,
		"...Maximum Allowed Measurement Time = [%+8.6f] ms.", 
		maximum_allowed_measurement_time_in_ms
	);
	pl2ganglia_diagnostic(message_buffer);

	//-------------------------------------------------------------------------
	// Boost pl2ganglia priority if requested by user.
	//-------------------------------------------------------------------------
	if(p->f_boost == 1) {
		pl2ganglia_diagnostic("...Boosting Priority.");
#ifdef __PL_WINDOWS__
		bret = SetThreadPriority(
			GetCurrentThread(), 
			PL2GANGLIA_BOOST_PRIORITY
		);
		if(bret == FALSE) {
			p->last_error = PL2GANGLIA_UNABLE_TO_BOOST_PRIORITY;
			goto pl2ganglia_error;
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		tid = pthread_self();
		param.sched_priority = PL2GANGLIA_BOOST_PRIORITY;
		ret = pthread_setschedparam(
			tid, 
			SCHED_RR,
			&param
		);
		if(ret == -1) {
			p->last_error = PL2GANGLIA_UNABLE_TO_BOOST_PRIORITY;
			goto pl2ganglia_error;
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	}

    //-------------------------------------------------------------------------
    // Read-in PL data.
	// Note:
	//    Passing this point, memory is dynamically allocated and error paths
	//    branches to clean-up code.
    //-------------------------------------------------------------------------
	ret = plh_dynamic_read_pl_config_ini_file(
		p->config, 
		&p->pl_data
	);
	if(ret != PL_SUCCESS) {
		p->last_error = PL2GANGLIA_UNABLE_TO_GET_PL_DATA;
		goto pl2ganglia_error; 
	}

	//-------------------------------------------------------------------------
	// Echo PL info to user.
	//-------------------------------------------------------------------------
	pl2ganglia_display(PL2GANGLIA_DASHES);
#ifdef __PL_WINDOWS__
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
	wcstombs(
		buffer, 
		p->pl_data.application_name,
		PL_MAX_PATH
	);
	sprintf(
		message_buffer,
		"...Application Name: [%s]", 
		buffer
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	sprintf(
		message_buffer,
		"...Application Name: [%s]",
		p->pl_data.application_name
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	pl2ganglia_display(message_buffer);

#ifdef __PL_WINDOWS__
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
	wcstombs(
		buffer, 
		p->pl_data.uuid,
		PL_MAX_PATH
	);
	sprintf(
		message_buffer,
		"...Application Instance UUID: [%s]", 
		buffer
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	sprintf(
		message_buffer,
		"...Application Instance UUID: [%s]",
		p->pl_data.uuid
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	pl2ganglia_display(message_buffer);

#ifdef __PL_WINDOWS__
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
	wcstombs(
		buffer, 
		p->pl_data.pl_root,
		PL_MAX_PATH
	);
	sprintf(
		message_buffer,
		"...Application PL Root: [%s]", 
		buffer
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	sprintf(
		message_buffer,
		"...Application PL Root: [%s]",
		p->pl_data.pl_root
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	pl2ganglia_diagnostic(message_buffer); // no display
	sprintf(
		message_buffer,
		"...Unprocessed Counters Count: [%d]",
		p->pl_data.max_counters
	);
	pl2ganglia_display(message_buffer);

	//-------------------------------------------------------------------------
	// Allocate memory to store counter value and processing data pointer array.
	//-------------------------------------------------------------------------
	p->pl_counters_data = (PL2GANGLIA_COUNTER_DATA *)malloc(
		sizeof(PL2GANGLIA_COUNTER_DATA) * p->pl_data.max_counters
	);
	if(p->pl_counters_data == NULL) {
		p->last_error = PL2GANGLIA_OUT_OF_MEMORY;
		goto pl2ganglia_clean_up; 
	}
	memset(
		p->pl_counters_data, 
		0, 
		sizeof(PL2GANGLIA_COUNTER_DATA) * p->pl_data.max_counters
	);

    //-------------------------------------------------------------------------
    // For each counter found in the PL, store the counter data (name) in the
	// counters data structure allocated previously.  If counter processing is
	// requested bu the user, then counter dependency data will be added to 
	// this structure.
    //-------------------------------------------------------------------------
	// for each counter in the PL
	for(i = 0; i < p->pl_data.max_counters; i++) { 

		//---------------------------------------------------------------------
		// Echo counter i full name to user.
		// Note:
		//    Since we are using pl2ganglia_diagnostic(), this display will 
		//    happen only if the _DEBUG symbol is defined.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		memset(
			buffer, 
			0, 
			sizeof(buffer)
		);
		wcstombs(
			buffer, 
			p->pl_data.entries[i].full_counter_names,
			PL_MAX_PATH
		);
		sprintf(
			message_buffer,
			"...Counter [%d]: [%s]",
			i,
			buffer
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		sprintf(
			message_buffer,
			"...Counter [%d]: [%s]", 
			i,
			p->pl_data.entries[i].full_counter_names
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		pl2ganglia_diagnostic(message_buffer);

		//-----------------------------------------------------------------------
		// Store the counter name.
		//-----------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		memset(
			buffer, 
			0, 
			sizeof(buffer)
		);
		wcstombs(
			buffer, 
			p->pl_data.entries[i].counter_names,
			PL_MAX_PATH
		); 
		strncpy(
			p->pl_counters_data[i].name,
			buffer, 
			strlen(buffer)
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		strncpy(
			p->pl_counters_data[i].name,
			p->pl_data.entries[i].counter_names, 
			strlen(p->pl_data.entries[i].counter_names)
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//-----------------------------------------------------------------------
		// Store the counter decorated name if requested by user.
		//-----------------------------------------------------------------------
		if(p->f_decorate == 1) {
#ifdef __PL_WINDOWS__
			strncpy(
				p->pl_counters_data[i].decorated_name,
				buffer, 
				strlen(buffer)
			);
			memset(
				buffer, 
				0, 
				sizeof(buffer)
			);
			wcstombs(
				buffer, 
				p->pl_data.uuid,
				PL_MAX_PATH
			);
			strncat(
				p->pl_counters_data[i].decorated_name,
				PL2GANGLIA_DECORATED_COUNTER_NAME_SEPARATOR, 
				strlen(PL2GANGLIA_DECORATED_COUNTER_NAME_SEPARATOR)
			);
			strncat(
				p->pl_counters_data[i].decorated_name,
				buffer, 
				strlen(buffer)
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			strncpy(
				p->pl_counters_data[i].decorated_name,
				p->pl_data.entries[i].counter_names, 
				strlen(p->pl_data.entries[i].counter_names)
			);
			strncat(
				p->pl_counters_data[i].decorated_name,
				PL2GANGLIA_DECORATED_COUNTER_NAME_SEPARATOR, 
				strlen(PL2GANGLIA_DECORATED_COUNTER_NAME_SEPARATOR)
			);
			strncat(
				p->pl_counters_data[i].decorated_name,
				p->pl_data.uuid, 
				strlen(p->pl_data.uuid)
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		} // if decorated

		//---------------------------------------------------------------------
		// Search for counter dependencies if processing was requested by user.
		// Note:
		//    Counter analyzis for dependencies detection is done by searching 
		//    for each non-suffixed counter a matching suffix counter in the
		//    counters data structure.  For example, search x.decimals for an
		//    x counter, etc.
		//---------------------------------------------------------------------
		if(p->f_process == 1) {

			/*
			  @@   @    @   @@   @       @  @   @@@@  @@@@@   @@@@
			 @  @  @@   @  @  @  @       @  @  @    @   @    @    @
			@    @ @ @  @ @    @ @       @  @  @        @    @
			@    @ @ @  @ @    @ @        @     @@@@    @     @@@@
			@@@@@@ @  @ @ @@@@@@ @        @         @   @         @
			@    @ @   @@ @    @ @        @         @   @         @
			@    @ @    @ @    @ @@@@@@   @    @@@@@  @@@@@  @@@@@			
			*/
			//-----------------------------------------------------------------
			// Search for various counter suffixs.  If found, set the indexes
			// to those counters and mark the counter as processed.
			// Also mark suffix counters as processing data and not as a coun-
			// ter.
			// Note:
			//    Suffixes are searched in the following order:
			//       * .offset.decimals
			//       * .offset.sign
			//       * .decimals
			//       * .offset
			//       * .scalar.decimals
			//       * .scalar
			//       * .sign
			//-----------------------------------------------------------------
			// .offset.decimals
			//-----------------------------------------------------------------
			px = strstr(
				p->pl_counters_data[i].name, 
				PL2GANGLIA_COUNTER_OFFSET_DECIMALS_SUFFIX
			);
			if(px != NULL) {
				memset(
					counter_name_root, 
					0, 
					sizeof(counter_name_root)
				);
				strncpy(
					counter_name_root, 
					p->pl_counters_data[i].name, 
					(px - p->pl_counters_data[i].name)
				);

				//-------------------------------------------------------------
				// Search and link this .offset.decimals counter to the root
				// counter.
				//-------------------------------------------------------------
				for(k = 0; k < i; k++) {
					if(
						(p->pl_counters_data[k].processed != PROCESSING_DATA) &&
						(strncmp(
							counter_name_root, 
							p->pl_counters_data[k].name, 
							strlen(counter_name_root)) == 0
						)
					) {
						p->pl_counters_data[k].i_offset_decimals = i;
						p->pl_counters_data[k].processed |= OFFSET_DECIMALS_PROCESSING;
						p->pl_counters_data[i].processed = PROCESSING_DATA;
						p->processed_counters_count--;
						goto pl2ganglia_counter_processing_skip;
					}
				} // for k
			} // if .offset.decimals found

			//-----------------------------------------------------------------
			// .offset.sign
			//-----------------------------------------------------------------
			px = strstr(
				p->pl_counters_data[i].name, 
				PL2GANGLIA_COUNTER_OFFSET_SIGN_SUFFIX
			);
			if(px != NULL) {
				memset(
					counter_name_root, 
					0, 
					sizeof(counter_name_root)
				);
				strncpy(
					counter_name_root, 
					p->pl_counters_data[i].name, 
					(px - p->pl_counters_data[i].name)
				);

				//-------------------------------------------------------------
				// Search and link this .offset.sign counter to the root 
				// counter
				//-------------------------------------------------------------
				for(k = 0; k < i; k++) {
					if(
						(p->pl_counters_data[k].processed != PROCESSING_DATA) &&
						(strncmp(
							counter_name_root, 
							p->pl_counters_data[k].name, 
							strlen(counter_name_root)) == 0
						)
					) {
						p->pl_counters_data[k].i_offset_sign = i;
						p->pl_counters_data[k].processed |= OFFSET_SIGN_PROCESSING;
						p->pl_counters_data[i].processed = PROCESSING_DATA;
						p->processed_counters_count--;
						goto pl2ganglia_counter_processing_skip;
					}
				} // for k
			} // if .offset.sign found

			//-----------------------------------------------------------------
			// .decimals
			//-----------------------------------------------------------------
			px = strstr(
				p->pl_counters_data[i].name, 
				PL2GANGLIA_COUNTER_DECIMALS_SUFFIX
			);
			if(px != NULL) {
				memset(
					counter_name_root, 
					0, 
					sizeof(counter_name_root)
				);
				strncpy(
					counter_name_root, 
					p->pl_counters_data[i].name, 
					(px - p->pl_counters_data[i].name)
				);

				//-------------------------------------------------------------
				// Search and link this .decimals counter to the root counter
				//-------------------------------------------------------------
				for(k = 0; k < i; k++) {
					if(
						(p->pl_counters_data[k].processed != PROCESSING_DATA) &&
						(strncmp(
							counter_name_root, 
							p->pl_counters_data[k].name, 
							strlen(counter_name_root)) == 0
						)

					) {
						p->pl_counters_data[k].i_decimals = i;
						p->pl_counters_data[k].processed |= DECIMALS_PROCESSING;
						p->pl_counters_data[i].processed = PROCESSING_DATA;
						p->processed_counters_count--;
						goto pl2ganglia_counter_processing_skip;
					}
				} // for k
			} // if .decimals found

			//-----------------------------------------------------------------
			// .offset
			//-----------------------------------------------------------------
			px = strstr(
				p->pl_counters_data[i].name, 
				PL2GANGLIA_COUNTER_OFFSET_SUFFIX
			);
			if(px != NULL) {
				memset(
					counter_name_root, 
					0, 
					sizeof(counter_name_root)
				);
				strncpy(
					counter_name_root, 
					p->pl_counters_data[i].name, 
					(px - p->pl_counters_data[i].name)
				);

				//-------------------------------------------------------------
				// Search and link this .offset counter to the root counter.
				//-------------------------------------------------------------
				for(k = 0; k < i; k++) {
					if(
						(p->pl_counters_data[k].processed != PROCESSING_DATA) &&
						(strncmp(
							counter_name_root, 
							p->pl_counters_data[k].name, 
							strlen(counter_name_root)) == 0
						)
					) {
						p->pl_counters_data[k].i_offset = i;
						p->pl_counters_data[k].processed |= OFFSET_PROCESSING;
						p->pl_counters_data[i].processed = PROCESSING_DATA;
						p->processed_counters_count--;
						goto pl2ganglia_counter_processing_skip;
					}
				} // for k
			} // if .offset found

			//-----------------------------------------------------------------
			// .scalar.decimals
			//-----------------------------------------------------------------
			px = strstr(
				p->pl_counters_data[i].name, 
				PL2GANGLIA_COUNTER_SCALAR_DECIMALS_SUFFIX
			);
			if(px != NULL) {
				memset(
					counter_name_root, 
					0, 
					sizeof(counter_name_root)
				);
				strncpy(
					counter_name_root, 
					p->pl_counters_data[i].name, 
					(px - p->pl_counters_data[i].name)
				);

				//-------------------------------------------------------------
				// Search and link this .scalar.decimals counter to the root 
				// counter
				//--------------------------------------------------------------
				for(k = 0; k < i; k++) {
					if(
						(p->pl_counters_data[k].processed != PROCESSING_DATA) &&
						(strncmp(
							counter_name_root, 
							p->pl_counters_data[k].name, 
							strlen(counter_name_root)) == 0
						)
					) {
						p->pl_counters_data[k].i_scalar_decimals = i;
						p->pl_counters_data[k].processed |= SCALAR_DECIMALS_PROCESSING;
						p->pl_counters_data[i].processed = PROCESSING_DATA;
						p->processed_counters_count--;
						goto pl2ganglia_counter_processing_skip;
					}
				} // for k
			} // if .scalar.decimals found

			//-----------------------------------------------------------------
			// .scalar
			//-----------------------------------------------------------------
			px = strstr(
				p->pl_counters_data[i].name, 
				PL2GANGLIA_COUNTER_SCALAR_SUFFIX
			);
			if(px != NULL) {
				memset(
					counter_name_root, 
					0, 
					sizeof(counter_name_root)
				);
				strncpy(
					counter_name_root, 
					p->pl_counters_data[i].name, 
					(px - p->pl_counters_data[i].name)
				);

				//-------------------------------------------------------------
				// Search and link this .scalar counter to the root counter.
				//-------------------------------------------------------------
				for(k = 0; k < i; k++) {
					if(
						(p->pl_counters_data[k].processed != PROCESSING_DATA) &&
						(strncmp(
							counter_name_root, 
							p->pl_counters_data[k].name, 
							strlen(counter_name_root)) == 0
						)
					) {
						p->pl_counters_data[k].i_scalar = i;
						p->pl_counters_data[k].processed |= SCALAR_PROCESSING;
						p->pl_counters_data[i].processed = PROCESSING_DATA;
						p->processed_counters_count--;
						goto pl2ganglia_counter_processing_skip;
					}
				} // for k
			} // if .scalar found

			//-----------------------------------------------------------------
			// .sign
			//-----------------------------------------------------------------
			px = strstr(
				p->pl_counters_data[i].name, 
				PL2GANGLIA_COUNTER_SIGN_SUFFIX
			);
			if(px != NULL) {
				memset(
					counter_name_root, 
					0, 
					sizeof(counter_name_root)
				);
				strncpy(
					counter_name_root, 
					p->pl_counters_data[i].name, 
					(px - p->pl_counters_data[i].name)
				);

				//-------------------------------------------------------------
				// Search and link this .sign counter to the root counter.
				//-------------------------------------------------------------
				for(k = 0; k < i; k++) {
					if(
						(p->pl_counters_data[k].processed != PROCESSING_DATA) &&
						(strncmp(
							counter_name_root, 
							p->pl_counters_data[k].name, 
							strlen(counter_name_root)) == 0
						)
					) {
						p->pl_counters_data[k].i_sign = i;
						p->pl_counters_data[k].processed |= SIGN_PROCESSING;
						p->pl_counters_data[i].processed = PROCESSING_DATA;
						p->processed_counters_count--;
						goto pl2ganglia_counter_processing_skip;
					}
				} // for k
			} // if .sign found
		} // if --process
pl2ganglia_counter_processing_skip:
			p->processed_counters_count++;

		//---------------------------------------------------------------------
		// Set by default the counter as selected, a.k.a. the counter will be
		// converted.  If the user has specified a subset of counters to 
		// convert only, then this flag will be cleared later on.
		//---------------------------------------------------------------------
		if(p->f_process == 0) {
			p->pl_counters_data[i].f_selected = 1;
		} else {
			if(p->pl_counters_data[i].processed != PROCESSING_DATA) {
				p->pl_counters_data[i].f_selected = 1;
			} else {
				p->pl_counters_data[i].f_selected = 0;
			}
		}

	} // end for each counter in the PL (for i)

    //-------------------------------------------------------------------------
    // If user requested it, we stop execution after listing the PL counters.
	// This is done by providing --list_counters.  Usually, the user will 
	// next re-run the code and replace the --list_counters with --counters
	// followed by a counter list to indicate which counters are to be
	// converted.  By default all counters are converted.  FOr now, if this
	// options was specified, we end the execution.
    //-------------------------------------------------------------------------
	if(p->f_list_counters == 1) {

		//---------------------------------------------------------------------
		// List the counters - only name is listed.
		//---------------------------------------------------------------------
		pl2ganglia_display(PL2GANGLIA_DASHES);
		for(i = 0, j = 0; i < p->pl_data.max_counters; i++) { // for each counter in the PL
			if(p->pl_counters_data[i].processed != PROCESSING_DATA) {
#ifdef __PL_WINDOWS__
				memset(
					buffer, 
					0, 
					sizeof(buffer)
				);
				wcstombs(
					buffer, 
					p->pl_data.entries[i].counter_names,
					PL_MAX_PATH
				);
				sprintf(
					message_buffer,
					"...Counter [%d]: [%s]",
					++j,
					buffer
				);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
				sprintf(
					message_buffer,
					"...Counter [%d]: [%s]", 
					++j,
					p->pl_data.entries[i].counter_names
				);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
				pl2ganglia_display(message_buffer);
			}
		} // for i
		pl2ganglia_display(PL2GANGLIA_DASHES);

		//---------------------------------------------------------------------
		// Exit.
		//---------------------------------------------------------------------
		p->last_error = PL2GANGLIA_NO_ERROR;
		goto pl2ganglia_clean_up;
	}

	//-------------------------------------------------------------------------
    // If user requested it, process the counter subset list and update the
	// counter data so only the subset will be converted.
    //-------------------------------------------------------------------------
	if(p->f_counters == 1) {
		
		//---------------------------------------------------------------------
		// Get the counter map based on user input
		//---------------------------------------------------------------------
		ret = pl2ganglia_parse_counter_list(
			p, 
			p->counters
		);
		if(ret != PL_SUCCESS) {
			//pl2ganglia_decode_error(p->last_error);
			p->last_error = PL2GANGLIA_INVALID_PARAMETERS;
			goto pl2ganglia_clean_up;
		}

		//---------------------------------------------------------------------
		// Update counter selection using the counter map.
		//---------------------------------------------------------------------
		// for each counter in the PL
		for(i = 0, j = 0; i < p->pl_data.max_counters; i++) { 
			if(p->pl_counters_data[i].processed != PROCESSING_DATA) {
				j++;
				if(p->counters_map[j] == 0) {
					p->pl_counters_data[i].f_selected = 0;
				}
			}
		}
	}

    //-------------------------------------------------------------------------
    // If user requested it, filter counters' names and decorated names to 
	// avoid potential issues in Ganglia and reporting tools.
	// Note:
	//    An assertion is done on PL_MAX_PATH since this is the size of the char
	//    arrays used to store the counters' name and decorated names.
    //-------------------------------------------------------------------------
	if(p->f_filter == 1) {
		for(i = 0; i < p->pl_data.max_counters; i++) { // for each counter
			
			//-----------------------------------------------------------------
			// Filter the name.
			//-----------------------------------------------------------------
			l = strlen(p->pl_counters_data[i].name);
			if(l > PL2GANFLIA_COUNTER_MAX_LENGTH) {
				assert(PL2GANFLIA_COUNTER_MAX_LENGTH <= PL_MAX_PATH);
				p->pl_counters_data[i].name[
					PL2GANFLIA_COUNTER_MAX_LENGTH
				] = '\0';
			}
			for(j = 0; j < l; j++) {
				for(k = 0; k < PL2GANFLIA_COUNTER_FOBIDDEN_CHARS_COUNT; k++) {
					if(p->pl_counters_data[i].name[j] == forbidden_chars[k]) {
						p->pl_counters_data[i].name[j] = allowed_chars[k];
					}
				} // for k
			} // for j

			if(p->f_decorate == 1) {

				//-------------------------------------------------------------
				// Filter the decorated name.
				//-------------------------------------------------------------
				l = strlen(p->pl_counters_data[i].decorated_name);
				if(l > PL2GANFLIA_COUNTER_MAX_LENGTH) {
					assert(PL2GANFLIA_COUNTER_MAX_LENGTH <= PL_MAX_PATH);
					p->pl_counters_data[i].decorated_name[
						PL2GANFLIA_COUNTER_MAX_LENGTH
					] = '\0';
				}
				for(j = 0; j < l; j++) {
					for(
						k = 0; 
						k < PL2GANFLIA_COUNTER_FOBIDDEN_CHARS_COUNT; 
						k++
					) {
						if(
							p->pl_counters_data[i].decorated_name[j] == 
							forbidden_chars[k]
						) {
							p->pl_counters_data[i].decorated_name[j] = 
								allowed_chars[k]
							;
						}
					} // for k
				} // for j
			} // if decorate
		} // for i
	}

	//-------------------------------------------------------------------------
	// Echo post-PL analyzis and settings info to user.
	//-------------------------------------------------------------------------
	pl2ganglia_display(PL2GANGLIA_DASHES);
	if(p->f_process == 1) {
		sprintf(
			message_buffer,
			"...Processed Counters Count: [%d]",
			p->processed_counters_count
		);
		pl2ganglia_display(message_buffer);
	}
	sprintf(
		message_buffer, 
		"...Pause Interval (in ms): [%d]", 
		p->pause_time
	);
	pl2ganglia_display(message_buffer);
	sprintf(
		message_buffer, 
		"...Counter Processing: ["
	);
	if(p->f_process == 1) {
		strcat(
			message_buffer, 
			"YES]"
		);
	} else {
		strcat(
			message_buffer, 
			"NO]"
		);
	}
	pl2ganglia_display(message_buffer);
	sprintf(
		message_buffer, 
		"...Counter Name Decoration: ["
	);
	if(p->f_decorate == 1) {
		strcat(
			message_buffer, 
			"YES]"
		);
	} else {
		strcat(
			message_buffer, 
			"NO]"
		);
	}
	pl2ganglia_display(message_buffer);
	sprintf(
		message_buffer, 
		"...Counter Name Filtering: ["
	);
	if(p->f_filter == 1) {
		strcat(
			message_buffer, 
			"YES]"
		);
	} else {
		strcat(
			message_buffer, 
			"NO]"
		);
	}
	pl2ganglia_display(message_buffer);
	sprintf(
		message_buffer, 
		"...Forced To Double: ["
	);
	if(p->f_force_to_double == 1) {
		strcat(
			message_buffer, 
			"YES]"
		);
	} else {
		strcat(
			message_buffer, 
			"NO]"
		);
	}
	pl2ganglia_display(message_buffer);
	sprintf(
		message_buffer, 
		"...Forced To Use gmetric: ["
	);
	if(p->f_force_use_gmetric == 1) {
		strcat(
			message_buffer, 
			"YES]"
		);
	} else {
		strcat(
			message_buffer, 
			"NO]"
		);
	}
	pl2ganglia_display(message_buffer);
	sprintf(
		message_buffer, 
		"...Priority Boost: ["
	);
	if(p->f_boost == 1) {
		strcat(
			message_buffer, 
			"YES]"
		);
	} else {
		strcat(
			message_buffer, 
			"NO]"
		);
	}
	pl2ganglia_display(message_buffer);
	sprintf(
		message_buffer, 
		"...Partial Counter Convertion: ["
	);
	if(p->f_counters == 1) {
		strcat(
			message_buffer, 
			"YES]"
		);
		pl2ganglia_display(message_buffer);
		sprintf(
			message_buffer,
			"......Selected Counters Count: [%d]",
			p->requested_counters_count
		);
		pl2ganglia_display(message_buffer);
		sprintf(
			message_buffer,
			"......Selected Counters: [\"%s\"]",
			p->counters
		);
	} else {
		strcat(
			message_buffer, 
			"NO]"
		);
	}
	pl2ganglia_display(message_buffer);
	pl2ganglia_display(PL2GANGLIA_DASHES);

    //-------------------------------------------------------------------------
    // Setup interrupt signal handler.
    //-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	p->sleep_event = CreateEvent(
		NULL, 
		FALSE, 
		FALSE, 
		NULL
	);
	if(p->sleep_event == NULL) {
		p->last_error = PL2GANGLIA_UNABLE_TO_INSTALL_EVENT_HANDLER;
		goto pl2ganglia_clean_up; 
	}
	bret = SetConsoleCtrlHandler(
		(PHANDLER_ROUTINE)signal_handler, 
		TRUE
	);
	if(bret == FALSE) {
		p->last_error = PL2GANGLIA_UNABLE_TO_INSTALL_EVENT_HANDLER;
		goto pl2ganglia_clean_up; 
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	iret = pthread_cond_init(
		&p->sleep_condition_variable, 
		NULL
	);
	if(iret != 0) {
		p->last_error = PL2GANGLIA_UNABLE_TO_INSTALL_EVENT_HANDLER;
		goto pl2ganglia_clean_up; 
	}
	iret = pthread_mutex_lock(&p->sleep_mutex);
	if(iret != 0) {
		p->last_error = PL2GANGLIA_UNABLE_TO_INSTALL_EVENT_HANDLER;
		goto pl2ganglia_clean_up; 
	}
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags = 0;
	iret = sigaction(
		SIGINT, 
		&sa, 
		NULL
	);
	if(iret != 0) { 
		p->last_error = PL2GANGLIA_UNABLE_TO_INSTALL_EVENT_HANDLER;
		goto pl2ganglia_clean_up; 
	}
	p->f_sleep_event_created = 1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	pl2ganglia_display("Installed Interrupt Signal Handler.");

    //-------------------------------------------------------------------------
    // Create Ganglia global context.
    //-------------------------------------------------------------------------
	if(p->f_force_use_gmetric == 0) {
#if defined (__PL_WINDOWS__) || (__PL_MACOSX__)
		assert(0); // should never happen, trap it!
#endif // __PL_WINDOWS__ || __PL_MACOSX__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
		p->global_context = Ganglia_pool_create(NULL);
		if(p->global_context == NULL) {
			p->last_error = PL2GANGLIA_UNABLE_TO_CREATE_GANGLIA_POOL;
			goto pl2ganglia_clean_up;
		}
		pl2ganglia_display("Created Ganglia Global Context.");
#endif// __PL_LINUX__ || __PL_SOLARIS__
	}

    //-------------------------------------------------------------------------
    // Build the configuration using the default gmond configuration file.
    //-------------------------------------------------------------------------
	if(p->f_force_use_gmetric == 0) {
#if defined (__PL_WINDOWS__) || (__PL_MACOSX__)
		assert(0); // should never happen, trap it!
#endif // __PL_WINDOWS__ || __PL_MACOSX__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
		p->gmond_config = Ganglia_gmond_config_create(
			p->gmond_configuration_file_name, 
			1
		);
		if(p->gmond_config == NULL) {
			p->last_error = PL2GANGLIA_UNABLE_TO_CONFIGURE_GMOND;
			goto pl2ganglia_clean_up;
		}
		sprintf(
			message_buffer,
			"Created Ganglia Gmond Configuration Using [%s].",
			p->gmond_configuration_file_name
		);
		pl2ganglia_display(message_buffer);
#endif// __PL_LINUX__ || __PL_SOLARIS__
	}

    //-------------------------------------------------------------------------
    // Build UDP channels used to send metric updates to smond.
    //-------------------------------------------------------------------------
	if(p->f_force_use_gmetric == 0) {
#if defined (__PL_WINDOWS__) || (__PL_MACOSX__)
		assert(0); // should never happen, trap it!
#endif // __PL_WINDOWS__ || __PL_MACOSX__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
		p->send_channels = Ganglia_udp_send_channels_create(
			p->global_context, 
			p->gmond_config
		);
		if(p->send_channels == NULL) {
			p->last_error = PL2GANGLIA_UNABLE_TO_CREATE_UDP_CHANNELS;
			goto pl2ganglia_clean_up;
		}
		pl2ganglia_display("Created Ganglia UDP Channels.");
#endif// __PL_LINUX__ || __PL_SOLARIS__
	}

    //-------------------------------------------------------------------------
    // Create metric update message.
    //-------------------------------------------------------------------------
	if(p->f_force_use_gmetric == 0) {
#if defined (__PL_WINDOWS__) || (__PL_MACOSX__)
		assert(0); // should never happen, trap it!
#endif // __PL_WINDOWS__ || __PL_MACOSX__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
		p->gmetric = Ganglia_metric_create(
			p->global_context
		);
		if(p->gmetric == NULL) {
			p->last_error = PL2GANGLIA_UNABLE_TO_CREATE_UPDATE_MESSAGE;
			goto pl2ganglia_clean_up;
		}
		pl2ganglia_display("Created Ganglia Update Metric Message.");
#endif// __PL_LINUX__ || __PL_SOLARIS__
	}

	//-------------------------------------------------------------------------
	// Attach to the PL.
	//-------------------------------------------------------------------------
	p->pld = pl_attach(p->config);
	if(p->pld == PL_INVALID_DESCRIPTOR) {
		p->last_error = PL2GANGLIA_UNABLE_TO_ATTACH_TO_PL;
		goto pl2ganglia_clean_up;
	}

	/*
	@    @   @@   @@@@@  @    @        @       @@@@   @@@@  @@@@@
	@@  @@  @  @    @    @@   @        @      @    @ @    @ @    @
	@ @@ @ @    @   @    @ @  @        @      @    @ @    @ @    @
	@    @ @    @   @    @ @  @        @      @    @ @    @ @@@@@
	@    @ @@@@@@   @    @  @ @        @      @    @ @    @ @
	@    @ @    @   @    @   @@        @      @    @ @    @ @
	@    @ @    @ @@@@@  @    @        @@@@@@  @@@@   @@@@  @
	*/
	while(p->f_convert) {

		//---------------------------------------------------------------------
		// Prepare counter collection time check.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = QueryPerformanceCounter(&start_time);
		if(bret == FALSE) {
			p->last_error = PL2GANGLIA_UNABLE_TO_MEASURE_TIME;
			goto pl2ganglia_clean_up;
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = gettimeofday(
			&start_time, 
			NULL
		);
		if(ret == -1) {
			p->last_error = PL2GANGLIA_UNABLE_TO_MEASURE_TIME;
			goto pl2ganglia_clean_up;
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Collect counters and send metric update message to the local
		// gmond instance.  Note that one PL counter is associated to a
		// Ganglia metric (using the same name - possibly decorated with the
		// PL instance UUID).  Note also that the metric message is sent in 3
		// different locations.  Any other error path doesn't send update mes-
		// -sages since RRTool* used by Ganglia will inject a "no value" data
		// into the database.
		//---------------------------------------------------------------------
		if(p->f_process == 1) {

			//-----------------------------------------------------------------
			// Processed counters path.
			//-----------------------------------------------------------------
			for(i = 0; i < p->pl_data.max_counters; i++) { // for each counter

				if(p->pl_counters_data[i].processed != PROCESSING_DATA) {

					//---------------------------------------------------------
					// Read ith counter in the PL.
					//---------------------------------------------------------
					ret = pl_read(
						p->pld, 
						&p->pl_counters_data[i].ull_value, 
						i
					);
					if(ret == PL_FAILURE) {
						if(ret != PL_SUCCESS) {
							p->last_error = PL2GANGLIA_UNABLE_TO_READ_PL;
							goto pl2ganglia_clean_up;
						}
					}

					if(p->pl_counters_data[i].processed == NO_PROCESSING) {

						//-----------------------------------------------------
						// Send counter associated metric update message to
						// gmond - or via gmetric.
						//-----------------------------------------------------
						if(p->f_force_to_double == 1) {
							if((double)p->pl_counters_data[i].ull_value <= DBL_MAX) {
								p->pl_counters_data[i].double_value = 
									(double)p->pl_counters_data[i].ull_value
								;
							} else {
								memset(
									buffer, 
									0, 
									sizeof(buffer)
								);
								sprintf(
									buffer,
									"...WARNING: counter [%d] overflow!", 
									i
								);
								pl2ganglia_display(buffer);
								p->pl_counters_data[i].double_value = 
									PL2GANGLIA_DOUBLE_OVERFLOW_VALUE
								;
							}
							ret = pl2ganglia_send_metric_update(
								p, 
								i, 
								PL2GANGLIA_DOUBLE
							);
						} else {
#ifdef __PL2GANGLIA_WITH_ULL_SUPPORT__
							ret = pl2ganglia_send_metric_update(
								p, 
								i, 
								PL2GANGLIA_ULL
							);
#else // __PL2GANGLIA_WITH_ULL_SUPPORT__
							if(p->pl_counters_data[i].ull_value <= UINT_MAX) {
								p->pl_counters_data[i].ui_value = 
									(unsigned int)p->pl_counters_data[i].ull_value
								;
							} else {
								memset(
									buffer, 
									0, 
									sizeof(buffer)
								);
								sprintf(
									buffer,
									"...WARNING: counter [%d] overflow!", 
									i
								);
								pl2ganglia_display(buffer);
								p->pl_counters_data[i].ui_value = 
									PL2GANGLIA_UINT_OVERFLOW_VALUE
								;
							}
							ret = pl2ganglia_send_metric_update(
								p, 
								i, 
								PL2GANGLIA_UINT32
							);
#endif // __PL2GANGLIA_WITH_ULL_SUPPORT__
						}
						if(ret != PL_SUCCESS) {
							p->last_error = 
								PL2GANGLIA_UNABLE_TO_COMMUNICATE_WITH_GMOND
							;
							goto pl2ganglia_clean_up;
						}

					} else { // processing has to be applied to this counter

						//-----------------------------------------------------
						// Set default sufix counter values, will be overwrit-
						// -ten if counter exist.
						//-----------------------------------------------------
						counter = p->pl_counters_data[i].ull_value;
						counter_scalar = 1;
						counter_scalar_decimals = 0;
						counter_decimals = 0;
						counter_sign = 0;
						counter_offset = 0;
						counter_offset_decimals = 0;
						counter_offset_sign = 0;

						//-----------------------------------------------------
						// Read counter .decimals if associated to this counter
						// (ith).
						//-----------------------------------------------------
						if(
							p->pl_counters_data[i].processed & 
							DECIMALS_PROCESSING
						) {
							ret = pl_read(
								p->pld, 
								&counter_decimals, 
								p->pl_counters_data[i].i_decimals
							);
							if(ret != PL_SUCCESS) {
								f_error = 1;
								p->last_error = 
									PL2GANGLIA_UNABLE_TO_READ_PL
								;
								goto pl2ganglia_compute_processed_counter_value;
							}
						}

						//-----------------------------------------------------
						// Read counter .offset if associated to this counter
						// (ith).
						//-----------------------------------------------------
						if(
							p->pl_counters_data[i].processed & 
							OFFSET_PROCESSING
						) {

							//-------------------------------------------------
							// read .offset counter first
							//-------------------------------------------------
							ret = pl_read(
								p->pld, 
								&counter_offset, 
								p->pl_counters_data[i].i_offset
							);
							if(ret != PL_SUCCESS) {
								f_error = 1;
								p->last_error = 
									PL2GANGLIA_UNABLE_TO_READ_PL
								;
								goto pl2ganglia_compute_processed_counter_value;
							}

							//-------------------------------------------------
							// Read counter .offset.decimals if associated to
							// this counter (ith).
							//-------------------------------------------------
							if(
								p->pl_counters_data[i].processed & 
								OFFSET_DECIMALS_PROCESSING
							) {
								ret = pl_read(
									p->pld, 
									&counter_offset_decimals, 
									p->pl_counters_data[i].i_offset_decimals
								);
								if(ret != PL_SUCCESS) {
									f_error = 1;
									p->last_error = 
										PL2GANGLIA_UNABLE_TO_READ_PL
									;
									goto pl2ganglia_compute_processed_counter_value;
								}
							}

							//-------------------------------------------------
							// Read counter .offset.sign if associated to this
							// counter (ith).
							//-------------------------------------------------
							if(
								p->pl_counters_data[i].processed & 
								OFFSET_SIGN_PROCESSING
							) {
								ret = pl_read(
									p->pld, 
									&counter_offset_sign, 
									p->pl_counters_data[i].i_offset_sign
								);
								if(ret != PL_SUCCESS) {
									f_error = 1;
									p->last_error = 
										PL2GANGLIA_UNABLE_TO_READ_PL
									;
									goto pl2ganglia_compute_processed_counter_value;
								}
							}
						}

						//-----------------------------------------------------
						// Read counter .scalar if associated to this counter
						// (ith).
						//-----------------------------------------------------
						if(
							p->pl_counters_data[i].processed & 
							SCALAR_PROCESSING
						) {
							ret = pl_read(
								p->pld, 
								&counter_scalar, 
								p->pl_counters_data[i].i_scalar
							);
							if(ret != PL_SUCCESS) {
								f_error = 1;
								p->last_error = 
									PL2GANGLIA_UNABLE_TO_READ_PL
								;
								goto pl2ganglia_compute_processed_counter_value;
							}

							//-------------------------------------------------
							// Read counter .scalar.decimals if associated to
							// this counter (ith).
							//-------------------------------------------------
							if(
								p->pl_counters_data[i].processed & 
								SCALAR_DECIMALS_PROCESSING
							) {
								ret = pl_read(
									p->pld, 
									&counter_scalar_decimals, 
									p->pl_counters_data[i].i_scalar_decimals
								);
								if(ret != PL_SUCCESS) {
									f_error = 1;
									p->last_error = 
										PL2GANGLIA_UNABLE_TO_READ_PL
									;
									goto pl2ganglia_compute_processed_counter_value;
								}
							}
						}

						//-----------------------------------------------------
						// Read counter .sign if associated to this counter
						// (ith).
						//-----------------------------------------------------
						if(
							p->pl_counters_data[i].processed & 
							SIGN_PROCESSING
						) {
							ret = pl_read(
								p->pld, 
								&counter_sign, 
								p->pl_counters_data[i].i_sign
							);
							if(ret != PL_SUCCESS) {
								f_error = 1;
								p->last_error = 
									PL2GANGLIA_UNABLE_TO_READ_PL
								;
								goto pl2ganglia_compute_processed_counter_value;
							}
						}

pl2ganglia_compute_processed_counter_value:
						if(f_error == 0) {

							//-------------------------------------------------
							// Compute counter real value.
							//-------------------------------------------------
							p->pl_counters_data[i].double_value =
								  (long double)counter 
								/ (long double)pow(
									10.0, 
									(double)counter_decimals
								) 
								* (long double)counter_scalar
								/ (long double)pow(
									10.0, 
									(double)counter_scalar_decimals
								)
								* (counter_sign ? -1.0 : 1.0) 
								+ (long double)counter_offset 
								/ (long double)pow(
									10.0, 
									(double)counter_offset_decimals
								) 
								* (counter_offset_sign ? -1.0 : 1.0)
							;

							//-------------------------------------------------
							// Send counter associated metric update message 
							// to gmond.
							//-------------------------------------------------
							ret = pl2ganglia_send_metric_update(
								p, 
								i, 
								PL2GANGLIA_DOUBLE
							);
							if(ret != PL_SUCCESS) {
								p->last_error = 
									PL2GANGLIA_UNABLE_TO_COMMUNICATE_WITH_GMOND
								;
								goto pl2ganglia_clean_up;
							}

						} else {
							//p->pl_counters_data[i].double_value = 0.0;
							f_error = 0;
						}
					}

				} else {

					//---------------------------------------------------------
					// this counter is used in another counter processing, do
					// nothing since processing was required by user.
					//---------------------------------------------------------
					;
				}
			} // for i

		} else {

			//-----------------------------------------------------------------
			// Non processed counter path.
			//-----------------------------------------------------------------
			for(i = 0; i < p->pl_data.max_counters; i++) {

				if(p->pl_counters_data[i].f_selected == 1) {

					//---------------------------------------------------------
					// Real counter value.
					//---------------------------------------------------------
					ret = pl_read(
						p->pld, 
						&p->pl_counters_data[i].ull_value, 
						i
					);
					if(ret != PL_SUCCESS) {
						p->last_error = PL2GANGLIA_UNABLE_TO_READ_PL;
						goto pl2ganglia_clean_up;
					}

					//---------------------------------------------------------
					// Send counter associated metric update message to gmond
					// or via gmetric.
					//---------------------------------------------------------
					if(p->f_force_to_double == 1) {
						if((double)p->pl_counters_data[i].ull_value <= DBL_MAX) {
							p->pl_counters_data[i].double_value = 
								(double)p->pl_counters_data[i].ull_value
							;
						} else {
							memset(
								buffer, 
								0, 
								sizeof(buffer)
							);
							sprintf(
								buffer,
								"...WARNING: counter [%d] overflow!", 
								i
							);
							pl2ganglia_display(buffer);
							p->pl_counters_data[i].double_value = 
								PL2GANGLIA_DOUBLE_OVERFLOW_VALUE
							;
						}
						ret = pl2ganglia_send_metric_update(
							p, 
							i, 
							PL2GANGLIA_DOUBLE
						);
					} else {
#ifdef __PL2GANGLIA_WITH_ULL_SUPPORT__
						ret = pl2ganglia_send_metric_update(
							p, 
							i, 
							PL2GANGLIA_ULL
						);
#else // __PL2GANGLIA_WITH_ULL_SUPPORT__
						if(p->pl_counters_data[i].ull_value <= (unsigned long long)UINT_MAX) {
							p->pl_counters_data[i].ui_value = 
								(unsigned int)p->pl_counters_data[i].ull_value
							;
						} else {
							memset(
								buffer, 
								0, 
								sizeof(buffer)
							);
							sprintf(
								buffer,
								"...WARNING: counter [%d] overflow!", 
								i
							);
							pl2ganglia_display(buffer);
							p->pl_counters_data[i].ui_value = 
								PL2GANGLIA_UINT_OVERFLOW_VALUE
							;
						}
						ret = pl2ganglia_send_metric_update(
							p, 
							i, 
							PL2GANGLIA_UINT32
						);
#endif // __PL2GANGLIA_WITH_ULL_SUPPORT__
					}
					if(ret != PL_SUCCESS) {
						p->last_error = 
							PL2GANGLIA_UNABLE_TO_COMMUNICATE_WITH_GMOND
						;
						goto pl2ganglia_clean_up;
					}
				}
			}
		}

		//---------------------------------------------------------------------
		// Print to stdout the sample count.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		chars_displayed = fprintf(
			stdout, 
			"Samples:        [%I64u]", 
			++samples_collected
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
		chars_displayed = fprintf(
			stdout, 
			"Samples:        [%llu]", 
			++samples_collected
		);
		fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		for(i = 0; i < chars_displayed; i++) { 
			fprintf(stdout, "\b"); 
		}

		//---------------------------------------------------------------------
		// compute time to sleep based on actual data collection 
		// & computation time
		// 1 second = 1000 milliseconds
		// 1 microsecond = 0.001 milliseconds or 1 millisecond = 1000 micros-
		// econds
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = QueryPerformanceCounter(&end_time);
		assert(bret != FALSE);
		actual_measurement_time_in_ms = (double)(
			(end_time.QuadPart - start_time.QuadPart) * 
			(double)1000.0/(double)frequency.QuadPart
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
		ret = gettimeofday(
			&end_time, 
			NULL
		); 
		assert(ret == 0);
		actual_measurement_time_in_ms = (double)( 
			((end_time.tv_sec - start_time.tv_sec) * (double)1000.0) + 
			((end_time.tv_usec - start_time.tv_usec) / (double)1000.0) 
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		time_to_sleep_in_ms = 
			maximum_allowed_measurement_time_in_ms - 
			actual_measurement_time_in_ms
		;

		//---------------------------------------------------------------------
		// Check for slow convertion.
		// Note, if this happens, then a multi-threaded converter should be
		// written to parallelize the task.
		//---------------------------------------------------------------------
		if(time_to_sleep_in_ms < 0.0) {
			pl2ganglia_diagnostic("Too slow to convert counters.");
			time_to_sleep_in_ms = 0.0;
		}

		//---------------------------------------------------------------------
		// Pause.
		// 1 millisecond = 1 000 000 nanoseconds
		// Note:
		//   Since sleep blocks and is not interrupted, if the pause time is
		//   long - it could be hours... - this application could take... hours
		//   to end gracefully.  To avoid this situation, sleep is replaced by
		//   a timed wait on a synchonization objetc.  This object is signaled
		//   either by the OS or by the signal handler routine, which is run
		//   in a different thread spawned by the OS.  Commented Sleep and 
		//   nanosleep calls are let for illustration purpose only.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		dw_ret = WaitForSingleObject(
			p->sleep_event, 
			(DWORD)time_to_sleep_in_ms
		);
		switch(dw_ret) {
			case WAIT_TIMEOUT:
			case WAIT_OBJECT_0: // interrupted & time-out conditions
				break; 
			case WAIT_ABANDONED:
			case WAIT_FAILED:
			default:
				assert(0); // should never happen, trap it!
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		time_to_sleep_in_s = (int)(time_to_sleep_in_ms / (double)1000.0);
		time_spec.tv_sec = time_to_sleep_in_s;
		time_spec.tv_nsec = (long int)(
			(time_to_sleep_in_ms - 
				(time_to_sleep_in_s * (double)1000.0)
			) * (double)1000000.0
		);
		iret = gettimeofday(
			&tv, 
			NULL
		);
		if(iret != 0) {
			p->last_error = PL2GANGLIA_UNABLE_TO_SLEEP;
			goto pl2ganglia_error;
		}
		duration.tv_sec = tv.tv_sec + time_to_sleep_in_s;
		duration.tv_nsec = time_spec.tv_nsec;
		iret = pthread_cond_timedwait(
			&p->sleep_condition_variable, 
			&p->sleep_mutex, 
			&duration
		);
		switch(iret) {
			case 0:
			case ETIMEDOUT: // interrupted & time-out conditions
				iret = pthread_mutex_unlock(&p->sleep_mutex);
				if(iret != 0) {
					p->last_error = PL2GANGLIA_UNABLE_TO_SLEEP;
					goto pl2ganglia_error;
				}
				break;
			case EINVAL:
			default:
				assert(0); // should never happen, trap it!
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Check collection time.
		// 1 second = 1000 milliseconds
		// 1 microsecond = 0.001 milliseconds or 1 millisecond = 1000 micros-
		// econds
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = QueryPerformanceCounter(&end_time);
		if(bret == FALSE) {
			p->last_error = PL2GANGLIA_UNABLE_TO_MEASURE_TIME;
			goto pl2ganglia_error;
		}
		total_duration_in_ms = ((double)(
			(end_time.QuadPart - start_time.QuadPart) * 
			(double)1000.0/(double)frequency.QuadPart)
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = gettimeofday(
			&end_time, 
			NULL
		);
		if(ret == -1) {
			p->last_error = PL2GANGLIA_UNABLE_TO_MEASURE_TIME;
			goto pl2ganglia_error;
		}
		total_duration_in_ms = (double)( 
			((end_time.tv_sec - start_time.tv_sec) * (double)1000.0) + 
			((end_time.tv_usec - start_time.tv_usec) / (double)1000.0) 
		);
#ifndef __PL_MACOSX__
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef _DEBUG
		sprintf(
			message_buffer,
			"...Sample Total Time: [%+8.2f] ms -> M: [%+8.2f] ms + S: [%+8.2f] ms.",
			total_duration_in_ms,
			actual_measurement_time_in_ms,
			time_to_sleep_in_ms
		);
		pl2ganglia_diagnostic(message_buffer);
#endif // _DEBUG
		if(
			total_duration_in_ms > 
			maximum_allowed_measurement_time_in_ms + 
			PL2GANGLIA_DEFAULT_UPDATE_INTERVAL_IN_MS
		) {
			if(p->f_boost == 1) {
				sprintf(
					message_buffer,
					"...Ran in [%+8.2f] ms instead of <= [%+8.2f] ms (M: [%+8.2f] ms + S: [%+8.2f] ms).",
					total_duration_in_ms,
					maximum_allowed_measurement_time_in_ms + 
					PL2GANGLIA_DEFAULT_UPDATE_INTERVAL_IN_MS,
					actual_measurement_time_in_ms,
					time_to_sleep_in_ms
				);
			} else {
				sprintf(
					message_buffer,
					"...Ran in [%+8.2f] ms instead of <= [%+8.2f] ms (M: [%+8.2f] ms + S: [%+8.2f] ms). Try Option [%s].",
					total_duration_in_ms,
					maximum_allowed_measurement_time_in_ms + 
					PL2GANGLIA_DEFAULT_UPDATE_INTERVAL_IN_MS,
					actual_measurement_time_in_ms,
					time_to_sleep_in_ms,
					PL2GANGLIA_PRIORITY_BOOST
				);
			}
			pl2ganglia_diagnostic(message_buffer);
		}
	} // while

    //-------------------------------------------------------------------------
    // Close PL.
    //-------------------------------------------------------------------------
	if(p->pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(p->pld);
		if(ret != PL_SUCCESS) {
			p->last_error = PL2GANGLIA_UNABLE_TO_CLOSE_PL;
			goto pl2ganglia_clean_up;
		}
		p->pld = PL_INVALID_DESCRIPTOR;
	}

pl2ganglia_clean_up:

	/*
	@@@@@@ @    @ @@@@@
	@      @@   @ @    @
	@      @ @  @ @    @
	@@@@@@ @ @  @ @    @
	@      @  @ @ @    @
	@      @   @@ @    @
	@@@@@@ @    @ @@@@@
	*/
	//-------------------------------------------------------------------------
	// Clean-up memory.
	//-------------------------------------------------------------------------
	ret = pl2ganglia_clean_up(p);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// Clean-up Ganglia metric and global context.
	//-------------------------------------------------------------------------
	if(p->f_force_use_gmetric == 0) {
#if defined (__PL_WINDOWS__) || (__PL_MACOSX__)
		assert(0); // should never happen, trap it!
#endif // __PL_WINDOWS__ || __PL_MACOSX__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
		if(p->gmetric != NULL) {
			Ganglia_metric_destroy(p->gmetric);
			p->gmetric = NULL;
		}
		if(p->global_context != NULL) {
			Ganglia_pool_destroy(p->global_context);
			p->global_context = NULL;
		}
#endif// __PL_LINUX__ || __PL_SOLARIS__
	}

#ifdef __PL_WINDOWS__
#ifdef __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
	
	//-------------------------------------------------------------------------
	// Restore timer resolution.
	//-------------------------------------------------------------------------
	mmret = timeEndPeriod(--resolution);
	if(mmret != TIMERR_NOERROR) {
		; // ERROR
	}
	pl2ganglia_diagnostic("...Timer Resolution Restored.");
#endif // __PL2GANGLIA_TRADE_POWER_DRAW_FOR_PRECISION___
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
    // Teardown interrupt signal handler.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	if(p->sleep_event != NULL) {
		bret = CloseHandle(p->sleep_event);
		if(bret == FALSE) {
			p->last_error = PL2GANGLIA_UNABLE_TO_REMOVE_EVENT_HANDLER;
			goto pl2ganglia_exit;
		}
		p->sleep_event = NULL;
		pl2ganglia_display("Uninstalled Interrupt Signal Handler.");
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	if(p->f_sleep_event_created == 1) {
		iret = pthread_mutex_unlock(&p->sleep_mutex);
		if(iret != 0) {
			p->last_error = PL2GANGLIA_UNABLE_TO_REMOVE_EVENT_HANDLER;
			goto pl2ganglia_exit;
		}
		iret = pthread_mutex_destroy(&p->sleep_mutex);
		if((iret != 0) && (iret != EBUSY)) {
			p->last_error = PL2GANGLIA_UNABLE_TO_REMOVE_EVENT_HANDLER;
			goto pl2ganglia_exit;
		}
		iret = pthread_cond_destroy(&p->sleep_condition_variable);
		if(iret != 0) {
			p->last_error = PL2GANGLIA_UNABLE_TO_REMOVE_EVENT_HANDLER;
			goto pl2ganglia_exit;
		}
		p->f_sleep_event_created = 0;
		pl2ganglia_display("Uninstalled Interrupt Signal Handler.");
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

    //-------------------------------------------------------------------------
    // Exit status.
	// Note:
	//    Since clean-up has to be performed on several error conditions, we
	//    may very well be in this path on error-condition.  The test allows
	//    for correct status reporting.
    //-------------------------------------------------------------------------
pl2ganglia_exit:
	if(p->last_error == PL2GANGLIA_NO_ERROR) {
		memset(
			p, 
			0, 
			sizeof(data)
		);
		pl2ganglia_display("Done.");
		return(PL_SUCCESS);
	}
pl2ganglia_error:
	pl2ganglia_decode_error(p->last_error);
	memset(
		p, 
		0, 
		sizeof(data)
	);
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: pl2ganglia_parse_cli
Purpose : parse user options passed via CLI and set data structure elements.
In      : arguments count, arguments and pointer to pl2ganglia data stricture.
Out     : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/PL_STATUS pl2ganglia_parse_cli(PPL2GANGLIA_DATA p, int argc, char **argv) {

	int i = 0;
	int t = 0;
	char *p1 = NULL;
	char *p2 = NULL;
	const char *pl2ganglia_options_tokens[PL2GANGLIA_MAX_TOKENS] = {
		PL2GANGLIA_TOKENS
	};
	const char *help[PL2GANGLIA_HELP_MESSAGE_LINES_COUNT] = {
		PL2GANGLIA_HELP_MESSAGE_LINES
	};
	const char *counter_help[PL2GANGLIA_SUFFIXES_HELP_MESSAGE_LINES_COUNT] = {
		PL2GANGLIA_SUFFIXES_HELP_MESSAGE_LINES
	};
	int configs_count = 0;
	char buffer[PL_MAX_PATH] = { '\0' };
	PL_STATUS ret = PL_FAILURE;

	assert(p != NULL);
	assert(argv != NULL);

    //-------------------------------------------------------------------------
    // Analyze user input.
    //-------------------------------------------------------------------------
	for(i = 1; i < argc; i++) { // for each argument
		strncpy(
			buffer, 
			argv[i], 
			sizeof(buffer)
		);
		plh_upper_string(buffer);
		for(t = 0; t < PL2GANGLIA_MAX_TOKENS; t++) { 
			if(
				strncmp(buffer,
				pl2ganglia_options_tokens[t], 
				strlen(buffer)
			) == 0) {
				switch(t) {

					//---------------------------------------------------------
					// Process --boost option.
					//---------------------------------------------------------
					case PL2GANGLIA_PRIORITY_BOOST_TOKEN_ID:
						p->f_boost = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --process option.
					//---------------------------------------------------------
					case PL2GANGLIA_PROCESS_TOKEN_ID:
						p->f_process = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --decorate option.
					//---------------------------------------------------------
					case PL2GANGLIA_DECORATE_TOKEN_ID:
						p->f_decorate = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --filter option.
					//---------------------------------------------------------
					case PL2GANGLIA_FILTER_TOKEN_ID:
						p->f_filter = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --force_to_double option.
					//---------------------------------------------------------
					case PL2GANGLIA_FORCE_TO_DOUBLE_TOKEN_ID:
						p->f_force_to_double = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --force_use_gmetric option.
					//---------------------------------------------------------
					case PL2GANGLIA_FORCE_USE_GMETRIC_TOKEN_ID:
						p->f_force_use_gmetric = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --version option.
					//---------------------------------------------------------
					case PL2GANGLIA_VERSION_TOKEN_ID:
						print_version_info(
							PL2GANGLIA_NAME,
							PL2GANGLIA_VERSION_MAJOR,
							PL2GANGLIA_VERSION_MINOR,
							PL2GANGLIA_VERSION_REVISION
						);
						p->f_version = 1;
						goto pl2ganglia_parse_cli_error;
						break;

					//---------------------------------------------------------
					// Process --help option.
					//---------------------------------------------------------
					case PL2GANGLIA_HELP_TOKEN_ID:
						if(p->f_process == 1) {
							for(
								i = 0; 
								i < PL2GANGLIA_SUFFIXES_HELP_MESSAGE_LINES_COUNT; 
								i++
							) {
								fprintf(
									stdout,
									counter_help[i]
								);
							}
						} else {
							for(
								i = 0; 
								i < PL2GANGLIA_HELP_MESSAGE_LINES_COUNT; 
								i++
							) {
								fprintf(
									stdout,
									help[i]
								);
							}
						}
						p->f_help = 1;
						goto pl2ganglia_parse_cli_error;
						break;

					//---------------------------------------------------------
					// Process --pause option.
					//---------------------------------------------------------
					case PL2GANGLIA_PAUSE_TOKEN_ID:
						if(i + 1 >= argc) {
							p->last_error = PL2GANGLIA_MISSING_PAUSE_TIME;
							goto pl2ganglia_parse_cli_error; 
						} 
						p->pause_time = atoi(argv[++i]);
						if(
							(p->pause_time < 
							P2GANGLIA_MIN_PAUSE_INTERVAL_IN_S) ||
							(p->pause_time > 
							P2GANGLIA_MAX_PAUSE_INTERVAL_IN_S)
						) {
							p->last_error = PL2GANGLIA_INVALID_PAUSE_TIME;
							goto pl2ganglia_parse_cli_error; 
						}
						p->pause_time_in_s = p->pause_time;
						p->pause_time = p->pause_time * 1000;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --gmond_config option.
					//---------------------------------------------------------
					case PL2GANGLIA_GMOND_CONFIG_FILE_NAME_TOKEN_ID:
						if(i + 1 >= argc) {
							p->last_error = 
								PL2GANGLIA_MISSING_GMOND_CONFIGURATION_FILE_NAME
							;
							goto pl2ganglia_parse_cli_error; 
						}
						i++;
						strncpy(
							p->gmond_configuration_file_name,
							argv[i],
							strlen(argv[i])
						);
						p->f_gmond_coniguration_file_name = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --application option.
					//---------------------------------------------------------
					case PL2GANGLIA_APPLICATION_TOKEN_ID:
						if(i + 1 >= argc) {
							p->last_error = 
								PL2GANGLIA_MISSING_APPLICATION_NAME
							;
							goto pl2ganglia_parse_cli_error; 
						}
						i++;
						p->application_name = argv[i];
						p->f_application_name = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --guid option.
					//---------------------------------------------------------
					case PL2GANGLIA_GUID_TOKEN_ID:
						if(i + 1 >= argc) {
							p->last_error = PL2GANGLIA_MISSING_GUID;
							goto pl2ganglia_parse_cli_error; 
						}
						i++;
						ret = plh_filter_uuid_string(argv[i]);
						if(ret != PL_SUCCESS) {
							p->last_error = PL2GANGLIA_SUSPICIOUS_GUID;
							goto pl2ganglia_parse_cli_error; 
						}
						p->guid = argv[i];
						p->f_guid = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --list_counters option.
					//---------------------------------------------------------
					case PL2GANGLIA_LIST_COUNTERS_TOKEN_ID:
						p->f_list_counters = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

					//---------------------------------------------------------
					// Process --counters option.
					//---------------------------------------------------------
					case PL2GANGLIA_COUNTERS_TOKEN_ID:
						if(i + 1 >= argc) {
							p->last_error = PL2GANGLIA_MISSING_COUNTERS;
							goto pl2ganglia_parse_cli_error; 
						}
						i++;
						p->counters = argv[i];
						p->f_counters = 1;
						goto pl2ganglia_parse_cli_next_argument;
						break;

				} // switch
			} // if token recognized
		} // for each allowed option token (t)

		//---------------------------------------------------------------------
		// Process potential PL config file name.
		// Check if PL config was not already provided.
		//---------------------------------------------------------------------
		if(p->f_config == 0) {			

			//-----------------------------------------------------------------
			// perform some - minimal - security checks
			//-----------------------------------------------------------------
			p1 = strstr(
				argv[i], 
				PL2GANGLIA_PL_FOLDER
			);
			p2 = strstr(
				argv[i], 
				PL2GANGLIA_PL_CONFIG_FILE_NAME
			);
			if(
				(p1 == NULL) || 
				(p2 == NULL)
			) {
				p->last_error = PL2GANGLIA_SUSPICIOUS_PL_INI;
				goto pl2ganglia_parse_cli_error;
			}
			p->config = argv[i];
			p->f_config = 1;
			configs_count++;
		}
		if(configs_count > 1) {
			p->last_error = PL2GANGLIA_TOO_MANY_PL_INI;
			goto pl2ganglia_parse_cli_error;
		}

pl2ganglia_parse_cli_next_argument:
		;
	} // for for each argument (i)

    //-------------------------------------------------------------------------
    // Check inconsistent input.
    //-------------------------------------------------------------------------
	if(p->last_error == PL2GANGLIA_NO_ERROR) {
		
		//---------------------------------------------------------------------
		// Check for inconsistent PL specification.
		//---------------------------------------------------------------------
		if(
			(
				(p->f_config == 1) &&
				(p->f_application_name == 0) &&
				(p->f_guid == 0)
			) || (
				(p->f_config == 0) &&
				(p->f_application_name == 1) &&
				(p->f_guid == 1)
			)
		) {

			//---------------------------------------------------------------------
			// This is a correct configuration, go ahead!
			//---------------------------------------------------------------------
				; // do nothing
		} else {

			//---------------------------------------------------------------------
			// This is an icorrect configuration, let's tell the user why.
			//---------------------------------------------------------------------
			if( // we are in a redundent configuration
				(p->f_config == 1) &&
				(p->f_application_name == 1) &&
				(p->f_guid == 1)
			) {
					p->last_error = PL2GANGLIA_TOO_MANY_PL_PARAMETERS;
					goto pl2ganglia_parse_cli_error;
			}
			if( // missing PL info
				(p->f_config == 0) &&
				(p->f_application_name == 0) &&
				(p->f_guid == 0)
			) {
					p->last_error = PL2GANGLIA_MISSING_PL_PARAMETERS;
					goto pl2ganglia_parse_cli_error;
			}
			if( // we are in a config file name configuration
				(p->f_config == 1) &&
				(p->f_application_name == 0) &&
				(p->f_guid == 0)
			) {
				if(
					(p->f_application_name == 1) ||
					(p->f_guid == 1)
				) {
					p->last_error = PL2GANGLIA_TOO_MANY_PL_PARAMETERS;
					goto pl2ganglia_parse_cli_error;
				}
			} else { // we are in an application name + guid configuration

				if(p->f_application_name == 1) {
					p->last_error = PL2GANGLIA_MISSING_GUID;
				} else {
					p->last_error = PL2GANGLIA_MISSING_APPLICATION_NAME;
				}
				goto pl2ganglia_parse_cli_error; 
			}
		}

		//---------------------------------------------------------------------
		// Check for inconsistent counter list options.
		//---------------------------------------------------------------------
		if(
			(p->f_list_counters == 1) &&
			(p->f_counters == 1)
		) {
			p->last_error = PL2GANGLIA_CONFLICTING_OPTIONS;
			goto pl2ganglia_parse_cli_error; 
		}
	}

    //-------------------------------------------------------------------------
    // Set defaults if required.
    //-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	if(p->f_gmond_coniguration_file_name == 0) {
		strncpy(
			p->gmond_configuration_file_name,
			PL2GANGLIA_DEFAULT_GMOND_CONFIG_FILE,
			strlen(PL2GANGLIA_DEFAULT_GMOND_CONFIG_FILE)
		);
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

    //-------------------------------------------------------------------------
    // Exit status.
    //-------------------------------------------------------------------------
	return(PL_SUCCESS);
pl2ganglia_parse_cli_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: pl2ganglia_parse_counter_list
Purpose : parse the counter list provided by user and create a counter map.
In      : pointer to pl2ganglia data and to counter list string
Out     : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
PL_STATUS pl2ganglia_parse_counter_list(PPL2GANGLIA_DATA p, char *s) {

	int i = 0;
	int index = 0;
	int index_end = 0;
	char *px = NULL;
	char *py = NULL;
	char *token = NULL;
	char token_separators[] = " \t";
	size_t memory_size = 0;
	unsigned int counters_count = 0;
	char *buffer = NULL;
	size_t l = 0;
		
	assert(p != NULL);
	assert(s != NULL);
	assert(p->pl_data.max_counters > 0);

	//-------------------------------------------------------------------------
    // Allocate memory to store a copy of the counter list string.
    //-------------------------------------------------------------------------
	l = strlen(s);
	buffer = (char *)malloc(sizeof(char) * l);
	if(buffer == NULL) {
		p->last_error = PL2GANGLIA_OUT_OF_MEMORY;
		goto pl2ganglia_parse_counter_list_error;
	}
	strncpy(buffer, s, l);

	//-------------------------------------------------------------------------
    // Allocate memory to store counters map.
    //-------------------------------------------------------------------------
	if(p->f_process == 1) {
		counters_count = p->processed_counters_count;
	} else {
		counters_count = p->pl_data.max_counters;
	}
	memory_size = sizeof(int) * counters_count;
	p->counters_map = (int *)malloc(memory_size);
	if(p->counters_map == NULL) {
		p->last_error = PL2GANGLIA_OUT_OF_MEMORY;
		goto pl2ganglia_parse_counter_list_error;
	}
	memset(
		p->counters_map, 
		0, 
		memory_size
	);

	//-------------------------------------------------------------------------
	// Tokenize options string into sub-tokens.
	//-------------------------------------------------------------------------
	p->requested_counters_count = 0;
	token = strtok(
		buffer, 
		token_separators
	);
	while(token != NULL) {
		px = strstr(
			token, 
			PL2GANGLIA_COUNTER_RANGE_SEPARATOR
		);
		if(px != NULL) {
			py = px + 1;
			if(*py != '\0') {
				index_end = atoi(py);
				if(
					(index_end == 0) ||
					(index_end > (int)counters_count)
				) {
					p->last_error = PL2GANGLIA_INVALID_PARAMETERS;
					goto pl2ganglia_parse_counter_list_error;
				}
			}
			*px = '\0';
			index = atoi(token);
			if(
				(index == 0) ||
				(index > (int)counters_count)
			) {
				p->last_error = PL2GANGLIA_INVALID_PARAMETERS;
				goto pl2ganglia_parse_counter_list_error;
			}
			index--;
			index_end--;
			if(index_end < index) {
				index_end = index_end ^ index;
				index = index ^ index_end;
				index_end = index_end ^ index;
			}
			for(i = index; i <= index_end; i++) {
				p->counters_map[i] = 1;
				p->requested_counters_count++;
			}
		} else {
			index = atoi(token);
			if(
				(index == 0) ||
				(index > (int)counters_count)
			) {
				p->last_error = PL2GANGLIA_INVALID_PARAMETERS;
				goto pl2ganglia_parse_counter_list_error;
			}
			p->counters_map[index - 1] = 1;
			p->requested_counters_count++;
		} // while
		token = strtok(NULL, token_separators);
	}

	//-------------------------------------------------------------------------
    // Check counts for coherency.
    //-------------------------------------------------------------------------
	if(p->requested_counters_count > counters_count) {
		p->last_error = PL2GANGLIA_INVALID_PARAMETERS;
		goto pl2ganglia_parse_counter_list_error;
	}

	//-------------------------------------------------------------------------
    // Exit status.
    //-------------------------------------------------------------------------
	if(buffer != NULL) {
		free(buffer);
	}
	return(PL_SUCCESS);
pl2ganglia_parse_counter_list_error:
	if(buffer != NULL) {
		free(buffer);
	}
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: signal_handler
Purpose : handles user signals
In      : message and pointer to pl2ganglia data
Out     : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
BOOL signal_handler(DWORD c) {
	BOOL bret = FALSE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
void signal_handler(int c) {
	int iret = -1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	assert(p != NULL);
	switch(c) {

#ifdef __PL_WINDOWS__

		case CTRL_C_EVENT:
		case CTRL_CLOSE_EVENT: 
		case CTRL_BREAK_EVENT: 
		case CTRL_LOGOFF_EVENT: 
		case CTRL_SHUTDOWN_EVENT: 

			//-----------------------------------------------------------------
			// Interrupt convertion.
			//-----------------------------------------------------------------
			p->f_convert = 0;
			bret = SetEvent(p->sleep_event);
			if(bret == FALSE) {
				p->last_error = PL2GANGLIA_UNABLE_TO_SIGNAL_INTERRUPT;
				pl2ganglia_decode_error(p->last_error);
			}
			return(TRUE);
		default: 
			return(FALSE); 
	} 
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 

		case SIGINT:

			//-----------------------------------------------------------------
			// Interrupt convertion.
			//-----------------------------------------------------------------
			p->f_convert = 0;
			iret = pthread_mutex_lock(&p->sleep_mutex);
			if(iret != 0) {
				p->last_error = PL2GANGLIA_UNABLE_TO_SIGNAL_INTERRUPT;
				goto signal_handler_error;
			}
			iret = pthread_cond_signal(&p->sleep_condition_variable);
			if(iret != 0) {
				p->last_error = PL2GANGLIA_UNABLE_TO_SIGNAL_INTERRUPT;
				goto signal_handler_error;
			}
			iret = pthread_mutex_unlock(&p->sleep_mutex);
			if(iret != 0) {
				p->last_error = PL2GANGLIA_UNABLE_TO_SIGNAL_INTERRUPT;
				goto signal_handler_error;
			}
			break;

signal_handler_error:
			pl2ganglia_decode_error(p->last_error);
			break;
} 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
} 

/*-----------------------------------------------------------------------------
Function: pl2ganglia_clean_up
Purpose : free allocated memory.
In      : pointer to pl2ganglia data structure
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
PL_STATUS pl2ganglia_clean_up(PPL2GANGLIA_DATA p) {

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Clean-up.
	// Note:
	//    * PL counters data structures.
	//    * Counters map
	//    * PL folder content data structure.
	//-------------------------------------------------------------------------
	if(p->pl_counters_data != NULL) {
		memset(
			p->pl_counters_data, 
			0, 
			sizeof(PL2GANGLIA_COUNTER_DATA) * p->pl_data.max_counters
		);
		free(p->pl_counters_data);
		p->pl_counters_data = NULL;
	}

	if(p->counters_map != NULL) {
		if(p->f_process == 1) {
			memset(
				p->counters_map,
				0,
				sizeof(int) * p->processed_counters_count
			);
		} else {
			memset(
				p->counters_map,
				0,
				sizeof(int) * p->pl_data.max_counters
			);
		}
		free(p->counters_map);
		p->counters_map = NULL;
	}

	if(p->pl_data.entries != NULL) {
		free(p->pl_data.entries);
		p->pl_data.entries = NULL;
	}
	memset(
		&p->pl_data, 
		0, 
		sizeof(p->pl_data)
	);
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: pl2ganglia_decode_error
Purpose : prints error message to stdout.
In      : error code
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
void pl2ganglia_decode_error(PL2GANGLIA_ERROR error_code) {

	char message_buffer[PL_MAX_PATH] = { '\0' };

	switch(error_code) {

		//---------------------------------------------------------------------
		// Generic error messages.
		//---------------------------------------------------------------------
		case PL2GANGLIA_INVALID_PARAMETERS:
			sprintf(
				message_buffer,
				"Invalid Parameters - use %s --help for help.", 
				PL2GANGLIA_NAME
			);
			pl2ganglia_error(message_buffer);
			break;
		case PL2GANGLIA_UNABLE_TO_SET_MEMORY_DEBUG:
			pl2ganglia_error("Unable To Setup Memory Degug.");
			break;
		case PL2GANGLIA_UNABLE_TO_INSTALL_EVENT_HANDLER:
			pl2ganglia_error("Unable To Install The Interrupt Signal Handler.");
			break;
		case PL2GANGLIA_UNABLE_TO_REMOVE_EVENT_HANDLER:
			pl2ganglia_error("Unable To Uninstall The Interrupt Signal Handler");
			break;
		case PL2GANGLIA_UNABLE_TO_SIGNAL_INTERRUPT:
			pl2ganglia_error("Unable To Signal End Of Run.");
			break;
		case PL2GANGLIA_INVALID_PAUSE_TIME:
			pl2ganglia_error("Invalid Time Interval Value.");
			break;
		case PL2GANGLIA_MISSING_PAUSE_TIME:
			pl2ganglia_error("Missing Time Interval Value.");
			break;
		case PL2GANGLIA_UNABLE_TO_SETUP_HP_TIMER:
			pl2ganglia_error("Unable To Setup High-Precision Timer. Check High Resolution Performance Counter Availability.");
			break;
		case PL2GANGLIA_UNABLE_TO_MEASURE_TIME:
			pl2ganglia_error("Unable To Read Timer.");
			break;
		case PL2GANGLIA_UNABLE_TO_SLEEP:
			pl2ganglia_error("Unable To Sleep.");
			break;
		case PL2GANGLIA_UNABLE_TO_BOOST_PRIORITY:
			pl2ganglia_error("Unable To Boost Kernel Thread's Priority. Check Privileges.");
			break;
		case PL2GANGLIA_SUSPICIOUS_PL_INI:
			pl2ganglia_error("Suspicious PL Config File.");
			break;
		case PL2GANGLIA_TOO_MANY_PL_INI:
			pl2ganglia_error("Too Many PL Config Files Provided.");
			break;
		case PL2GANGLIA_MISSING_COUNTERS:
			pl2ganglia_error("Missing Counters List.");
			break;
		case PL2GANGLIA_CONFLICTING_OPTIONS:
			pl2ganglia_error("Conflicting Options.");
			break;

		//---------------------------------------------------------------------
		// PL related error messages.
		//---------------------------------------------------------------------
		case PL2GANGLIA_TOO_MANY_PL_PARAMETERS:
			pl2ganglia_error("Too Many Command Line Options Provided To Specify the PL To Convert.");
			break;
		case PL2GANGLIA_MISSING_PL_PARAMETERS:
			pl2ganglia_error("Missing Command Line Option(s) To Specify the PL To Convert.");
			break;
		case PL2GANGLIA_MISSING_APPLICATION_NAME:
			pl2ganglia_error("Missing Application Name.");
			break;
		case PL2GANGLIA_MISSING_GUID:
			pl2ganglia_error("Missing GUID.");
			break;
		case PL2GANGLIA_SUSPICIOUS_GUID:
			pl2ganglia_error("Suspicious GUID.");
			break;
		case PL2GANGLIA_MISSING_PL_CONFIG_FILE_NAME:
			pl2ganglia_error("Missing PL Configuration File Name.");
			break;
		case PL2GANGLIA_UNABLE_TO_GET_PL_DATA:
			pl2ganglia_error("Unable To Read PL Data.");
			break;
		case PL2GANGLIA_UNABLE_TO_OPEN_PL:
			pl2ganglia_error("Unable To Open PL.");
			break;
		case PL2GANGLIA_UNABLE_TO_ATTACH_TO_PL:
			pl2ganglia_error("Unable To Attach To The PL.");
			break;
		case PL2GANGLIA_UNABLE_TO_CLOSE_PL:
			pl2ganglia_error("Unable To Close The PL.");
			break;
		case PL2GANGLIA_UNABLE_TO_READ_PL:
			pl2ganglia_error("Unable To Read The PL.");
			break;

		//---------------------------------------------------------------------
		// Ganglia* related error messages.
		//---------------------------------------------------------------------
		case PL2GANGLIA_MISSING_GMOND_CONFIGURATION_FILE_NAME:
			pl2ganglia_error("Missing Gmond Configuration File Name.");
			break;
		case PL2GANGLIA_UNABLE_TO_CREATE_GANGLIA_POOL:
			pl2ganglia_error("Unable To Create Pool.");
			break;
		case PL2GANGLIA_UNABLE_TO_CONFIGURE_GMOND:
			pl2ganglia_error("Unable To Configure Gmond Using gmond.conf.");
			break;
		case PL2GANGLIA_UNABLE_TO_CREATE_UDP_CHANNELS:
			sprintf(
				message_buffer,
				"Unable To Create UDP Channels Using [%s].", 
				p->gmond_configuration_file_name
			);
			pl2ganglia_error(message_buffer);
			break;
		case PL2GANGLIA_UNABLE_TO_CREATE_UPDATE_MESSAGE:
			pl2ganglia_error("Unable To Create Metric Update Message.");
			break;
		case PL2GANGLIA_INVALID_METRIC_PARAMETERS:
			pl2ganglia_error("Invalid Metric Parameters.");
			break;
		case PL2GANGLIA_INVALID_METRIC_CHARACTER:
			pl2ganglia_error("Invalid Character In Metric Parameters.");
			break;
		case PL2GANGLIA_UNABLE_TO_COMMUNICATE_WITH_GMOND:
			pl2ganglia_error("Unable To Send Metric Update Message To Gmond.");
			break;
		case PL2GANGLIA_UNABLE_TO_RUN_GMETRIC:
			pl2ganglia_error("Unable To Run Gmetric.");
			break;
		case PL2GANGLIA_UNABLE_TO_SEND_METRIC_UPDATE_MESSAGE:
			pl2ganglia_error("Unable To Send Metric Update Message.");
			break;

		//---------------------------------------------------------------------
		// Default error messages -- should never happen.
		//---------------------------------------------------------------------
		default:
			pl2ganglia_error("Undefined Error.");
			break;
	}
}

/*-----------------------------------------------------------------------------
Function: pl2ganglia_time_stamp
Purpose : generate a time stamp and store into received buffer.
In      : pointer to buffer to receive time_stamp and size of the buffer in bytes.
Out     : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
void pl2ganglia_time_stamp(char *p, size_t s) {

	char time_buffer[P2GANGLIA_TIME_STAMP_BUFFER_SIZE] = { '\0' };
	time_t log_time;
	size_t length = 0;
	
	assert(p);
	assert(s >= P2GANGLIA_TIME_STAMP_BUFFER_SIZE);

	//-------------------------------------------------------------------------
	// Collect time information and convert it into text
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	time(&log_time);
	ctime_s(
		time_buffer, 
		sizeof(time_buffer), 
		&log_time
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	time(&log_time);
#ifdef __PL_SOLARIS__
	ctime_r(
		&log_time, 
		time_buffer, 
		P2GANGLIA_TIME_STAMP_BUFFER_SIZE
	);
#else // __PL_SOLARIS__
	ctime_r(
		&log_time, 
		time_buffer
	);
#endif // __PL_SOLARIS__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Errase newline added by libc in time buffer.
	//-------------------------------------------------------------------------
	length = strlen(time_buffer) - 1;
	time_buffer[length] = '\0';

	//-------------------------------------------------------------------------
	// Copy time stamp to destination buffer.
	//-------------------------------------------------------------------------
	memcpy(
		p, 
		time_buffer, 
		strlen(time_buffer)
	);
}

/*-----------------------------------------------------------------------------
Function: pl2ganglia_display
Purpose : prints message to stdout.
In      : pointer to message string
Out     : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
void pl2ganglia_display(char *s) {
	
	char line[PL_MAX_PATH * 2] = P2GANGLIA_TIME_STAMP_BEGIN;
	
	assert(s != NULL);
	
	pl2ganglia_time_stamp(
		&line[strlen(P2GANGLIA_TIME_STAMP_BEGIN)], 
		sizeof(line)
	);
	strcat(
		line, 
		P2GANGLIA_TIME_STAMP_END
	);
	strcat(
		line, 
		s
	);
	fprintf(
		stdout, 
		"%s\n", 
		line
	);
}

/*-----------------------------------------------------------------------------
Function: pl2ganglia_diagnostic
Purpose : prints diagnostic message to stdout.
In      : pointer to message string
Out     : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
void pl2ganglia_diagnostic(char *s) {
#ifdef _DEBUG
	char line[PL_MAX_PATH * 2] = P2GANGLIA_TIME_STAMP_BEGIN;
	
	assert(s != NULL);
	
	pl2ganglia_time_stamp(
		&line[strlen(P2GANGLIA_TIME_STAMP_BEGIN)], 
		sizeof(line)
	);
	strcat(
		line, 
		P2GANGLIA_TIME_STAMP_END
	);
	strcat(
		line, 
		s
	);
	fprintf(
		stdout, 
		"%s\n", 
		line
	);
#else // _DEBUG
	;
#endif // _DEBUG
}

/*-----------------------------------------------------------------------------
Function: pl2ganglia_error
Purpose : prints error message to stderr.
In      : pointer to message string
Out     : non

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
void pl2ganglia_error(char *s) {
	
	char line[PL_MAX_PATH * 2] = P2GANGLIA_TIME_STAMP_BEGIN;
	
	assert(s != NULL);
	
	pl2ganglia_time_stamp(
		&line[strlen(P2GANGLIA_TIME_STAMP_BEGIN)], 
		sizeof(line)
	);
	strcat(
		line, 
		P2GANGLIA_TIME_STAMP_END
	);
	strcat(
		line, 
		s
	);
	fprintf(
		stderr, 
		"%s\n", 
		line
	);
}

/*-----------------------------------------------------------------------------
Function: pl2ganglia_send_metric_update
Purpose : send metric update.
In      : pointer to message string
Out     : non

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/29/2010    Jamel Tayeb             Creation.
*/
PL_STATUS pl2ganglia_send_metric_update(
	PPL2GANGLIA_DATA p, 
	unsigned int index, 
	PL2GANGLIA_COUNTER_TYPE_CODES type
) {

	int iret = -1;
	char *p_counter_name = NULL;
	char command_buffer[PL_MAX_PATH] = { '\0' };
	char value_buffer[PL_MAX_PATH] = { '\0' };

	assert(p != NULL);

	//------------------------------------------------------------------------
	// Select the right metric name based on user input.
	//------------------------------------------------------------------------
	if(p->f_decorate == 1) {
		p_counter_name = p->pl_counters_data[index].decorated_name;
	} else {
		p_counter_name = p->pl_counters_data[index].name;
	}
	assert(p_counter_name != NULL);

	if(p->f_force_use_gmetric) {

		//--------------------------------------------------------------------
		// Use of gmetric to update metric data was requested by user.
		//--------------------------------------------------------------------
		switch(type) {

			case PL2GANGLIA_DOUBLE:
				sprintf(
					command_buffer,
					PL2GANGLIA_DOUBLE_GANGLIA_COMMAND_STRING,
					p_counter_name,
					p->pl_counters_data[index].double_value
				);
				break;

			case PL2GANGLIA_ULL:
#ifdef __PL2GANGLIA_WITH_ULL_SUPPORT__
				if(p->f_force_to_double == 1) {
					sprintf(
						command_buffer,
						PL2GANGLIA_DOUBLE_GANGLIA_COMMAND_STRING,
						p_counter_name,
						(long double)p->pl_counters_data[index].ull_value
					);
				} else {
					sprintf(
						command_buffer,
						PL2GANGLIA_ULL_GANGLIA_COMMAND_STRING,
						p_counter_name,
						p->pl_counters_data[index].ull_value
					);
				}
#else // __PL2GANGLIA_WITH_ULL_SUPPORT__
				assert(0); // should never happen, trap it!
#endif // __PL2GANGLIA_WITH_ULL_SUPPORT__
				break;

			case PL2GANGLIA_UINT32:
				sprintf(
					command_buffer,
					PL2GANGLIA_UINT_GANGLIA_COMMAND_STRING,
					p_counter_name,
					p->pl_counters_data[index].ui_value
				);
				break;

			case PL2GANGLIA_STRING:
			case PL2GANGLIA_INT8:
			case PL2GANGLIA_UINT8:
			case PL2GANGLIA_INT16:
			case PL2GANGLIA_UINT16:
			case PL2GANGLIA_INT32:
			case PL2GANGLIA_FLOAT:
			default:
				assert(0); // should never happen, trap it!
		}
#if defined (__PL_WINDOWS__) || (__PL_MACOSX__)

		//--------------------------------------------------------------------
		// Echo gmetric command - informational only under Windows*.
		//--------------------------------------------------------------------
		pl2ganglia_display(command_buffer);
#endif // __PL_WINDOWS__ || __PL_MACOSX__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)

		//--------------------------------------------------------------------
		// Run gmetric command.  Echo is commented, remove for debug only.
		//--------------------------------------------------------------------
		//pl2ganglia_diagnostic(command_buffer);
		iret = system(command_buffer);
		if(iret == -1) {
			p->last_error = PL2GANGLIA_UNABLE_TO_RUN_GMETRIC;
			goto pl2ganglia_send_metric_update_error;
		}
#endif// __PL_LINUX__ || __PL_SOLARIS__
	
	} else { // not forced to use gmetric

		//--------------------------------------------------------------------
		// pl2ganglia will communicate directly with gmond as requested by user.
		//--------------------------------------------------------------------
#if defined (__PL_WINDOWS__) || (__PL_MACOSX__)
		// should never happen, trap it!
		assert(0);
		// this is to silence the compiler warning only.
		goto pl2ganglia_send_metric_update_error; 
#endif // __PL_WINDOWS__ || __PL_MACOSX__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)

		//--------------------------------------------------------------------
		// Build metric update message data.
		//--------------------------------------------------------------------
		switch(type) {

			case PL2GANGLIA_DOUBLE:
				sprintf(
					value_buffer,
					PL2GANGLIA_DOUBLE_FORMAT_STRING,
					p->pl_counters_data[index].double_value
				);
				iret = Ganglia_metric_set(
					p->gmetric, 
					p_counter_name, 
					value_buffer,
					PL2GANGLIA_DOUBLE_TYPE_STRING, 
					PL2GANGLIA_UNIT_STRING, 
					PL2GANGLIA_SLOPE_BOTH_INT,
					p->pause_time_in_s, 
					PL2GANGLIA_DMAX_INT
				);
				break;

			case PL2GANGLIA_ULL:
#ifdef __PL2GANGLIA_WITH_ULL_SUPPORT__
				if(p->f_force_to_double == 1) {
					sprintf(
						value_buffer,
						PL2GANGLIA_DOUBLE_FORMAT_STRING,
						(long double)p->pl_counters_data[index].ull_value
					);
					iret = Ganglia_metric_set(
						p->gmetric, 
						p_counter_name, 
						value_buffer,
						PL2GANGLIA_DOUBLE_TYPE_STRING, 
						PL2GANGLIA_UNIT_STRING, 
						PL2GANGLIA_SLOPE_BOTH_INT,
						p->pause_time_in_s, 
						PL2GANGLIA_DMAX_INT
					);
				} else {
					sprintf(
						value_buffer,
						PL2GANGLIA_ULL_FORMAT_STRING,
						p->pl_counters_data[index].ull_value
					);
					iret = Ganglia_metric_set(
						p->gmetric, 
						p_counter_name, 
						value_buffer,
						PL2GANGLIA_ULL_TYPE_STRING, 
						PL2GANGLIA_UNIT_STRING, 
						PL2GANGLIA_SLOPE_BOTH_INT,
						p->pause_time_in_s, 
						PL2GANGLIA_DMAX_INT
					);
				}
#else // __PL2GANGLIA_WITH_ULL_SUPPORT__
				assert(0); // should never happen, trap it!
#endif // __PL2GANGLIA_WITH_ULL_SUPPORT__
				break;

			case PL2GANGLIA_UINT32:
				sprintf(
					value_buffer,
					PL2GANGLIA_UINT_FORMAT_STRING,
					p->pl_counters_data[index].ui_value
				);
				iret = Ganglia_metric_set(
					p->gmetric, 
					p_counter_name, 
					value_buffer,
					PL2GANGLIA_UINT_TYPE_STRING, 
					PL2GANGLIA_UNIT_STRING, 
					PL2GANGLIA_SLOPE_BOTH_INT,
					p->pause_time_in_s, 
					PL2GANGLIA_DMAX_INT
				);
				break;

			case PL2GANGLIA_STRING:
			case PL2GANGLIA_INT8:
			case PL2GANGLIA_UINT8:
			case PL2GANGLIA_INT16:
			case PL2GANGLIA_UINT16:
			case PL2GANGLIA_INT32:
			case PL2GANGLIA_FLOAT:
			default:
				assert(0); // should never happen, trap it!
		} // switch

		//--------------------------------------------------------------------
		// Detect and process error.
		//--------------------------------------------------------------------
		switch(iret) {
			case 1:
				p->last_error = PL2GANGLIA_INVALID_METRIC_PARAMETERS;
				goto pl2ganglia_send_metric_update_error;
			case 2:
				p->last_error = PL2GANGLIA_INVALID_METRIC_CHARACTER;
				goto pl2ganglia_send_metric_update_error;
			case 3:
				p->last_error = PL2GANGLIA_INVALID_METRIC_TYPE;
				goto pl2ganglia_send_metric_update_error;
			case 4:
				p->last_error = PL2GANGLIA_INVALID_METRIC_VALUE;
				goto pl2ganglia_send_metric_update_error;
		} // switch

		//--------------------------------------------------------------------
		// Send the metric update message.
		//--------------------------------------------------------------------
		iret = Ganglia_metric_send(
			p->gmetric, 
			p->send_channels
		);
		if(iret != 0) {
			p->last_error = PL2GANGLIA_UNABLE_TO_SEND_METRIC_UPDATE_MESSAGE;
			goto pl2ganglia_send_metric_update_error;
		}
#endif// __PL_LINUX__ || __PL_SOLARIS__
	} // if forced to use gmetric

	return(PL_SUCCESS);
pl2ganglia_send_metric_update_error:
	return(PL_FAILURE);
}
