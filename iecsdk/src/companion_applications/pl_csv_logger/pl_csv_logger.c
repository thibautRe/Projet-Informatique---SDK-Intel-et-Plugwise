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
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "productivity_link.h"
#include "productivity_link_helper.h"
#include "pl_csv_logger.h"
#ifdef __PL_WINDOWS__
	#include <tchar.h>
	#pragma comment (lib, "Winmm")
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include <string.h>
	#include <signal.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// global(s)
//-----------------------------------------------------------------------------
int log_flag = 1;
int process_flag = 0;
unsigned int pl_count = 0;
unsigned int counter_count = 0;
char *pl_inis[PL_CSV_LOGGER_MAX_PLS] = { NULL };
int pause_time = PL_CSV_LOGGER_DEFAULT_PAUSE;
char *log_file_name = NULL;

/*-----------------------------------------------------------------------------
Function: main
Purpose : logger entry point
In      : array of pointers to null terminated strings and string count
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/26/2009    Jamel Tayeb             Creation.
*/
int main(int argc, char *argv[]) {

	PL_STATUS ret = PL_FAILURE;
	FILE *f = NULL;
	PLH_CONFIG_INFO pl_info;
	time_t log_time;
	char *px = NULL;
	char counter_name_root[PL_MAX_PATH] = { '\0' };
	char log_line[PL_CSV_LOGGER_LOG_ENTRY_SIZE] = { '\0' };
	char *log_header = NULL;
	char *tmp_log_header = NULL;
	size_t length = 0;
	size_t memory_size = 0;
	size_t new_memory_size = 0;

	char *startup[PL_CSV_LOGGER_STARTUP_MESSAGE_LINES_COUNT] = { 
		PL_CSV_LOGGER_STARTUP_MESSAGE_LINES 
	};
	char cvt_buffer[PL_CSV_LOGGER_CVT_BUFFER_SIZE] = { '\0' };
	char time_buffer[PL_CSV_LOGGER_TIME_BUFFER_SIZE] = { '\0' };
	int plds[PL_CSV_LOGGER_MAX_PLS] = { PL_INVALID_DESCRIPTOR };
	unsigned int plds_counters_counts[PL_CSV_LOGGER_MAX_PLS] = { '\0' };
	unsigned int chars_displayed = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned long long v = 0;
	unsigned long long samples = 1;
	int f_log_error = 0;
	long double processed_value;
	unsigned long long counter = 0;
	unsigned long long counter_scalar = 1;
	unsigned long long counter_scalar_decimals = 0;
	unsigned long long counter_decimals = 0;
	unsigned long long counter_sign = 0;
	unsigned long long counter_offset = 0;
	unsigned long long counter_offset_decimals = 0;
	unsigned long long counter_offset_sign = 0;
	PPL_CSV_LOGGER_COUNTER_DATA p_counters_data[PL_CSV_LOGGER_MAX_PLS] = { '\0' };
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
	char buffer[PL_CSV_LOGGER_BUFFER_SIZE] = { '\0' };
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	struct sigaction sa;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// timing data
	//-------------------------------------------------------------------------
	double time_to_sleep_in_ms = 0.0;
	double total_duration_in_ms = 0.0;
	double actual_measurement_time_in_ms = 0.0;
	double maximum_allowed_measurement_time_in_ms = 0.0;
#ifdef __PL_WINDOWS__
	LARGE_INTEGER frequency;
	LARGE_INTEGER start_time;
	LARGE_INTEGER end_time;
	MMRESULT mmret = 0;
	UINT resolution = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	struct timespec time_spec;
	struct timeval start_time;
	struct timeval end_time;
	int time_to_sleep_in_s = 0.0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------- end of declarations --------------------------

	/*
	 @@@@  @@@@@@  @@@@@ @    @ @@@@@   @@@@
	@    @ @         @   @    @ @    @ @    @
	@      @         @   @    @ @    @ @
	 @@@@  @@@@@@    @   @    @ @@@@@   @@@@
		 @ @         @   @    @ @           @
		 @ @         @   @    @ @           @
	@@@@@  @@@@@@    @    @@@@  @      @@@@@
	*/
	//-------------------------------------------------------------------------
	// prepare precision timer
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// set highest possible timer resolution 
	//-------------------------------------------------------------------------
	resolution = 1; // in ms
	do {
		mmret = timeBeginPeriod(resolution++);
	} while(mmret != TIMERR_NOERROR);
	pl_csv_logger_info_int(
		"Timer Resolution Set To [%u] ms.\n", 
		resolution
	);

	//-------------------------------------------------------------------------
	// setup hp timer
	//-------------------------------------------------------------------------
	bret = QueryPerformanceFrequency(&frequency);
	if(
		(bret == FALSE) || 
		(frequency.QuadPart == 0)
	) {
		pl_csv_logger_error(
			"Unable To Setup High-Precision Timer. Check High Resolution Performance Counter Availability.\n"
		);
	}
#endif // __PL_WINDOWS__
	maximum_allowed_measurement_time_in_ms = pause_time * 1000.0;

	//-------------------------------------------------------------------------
	// initialize data structures
	//-------------------------------------------------------------------------
	memset(
		pl_inis, 
		0, 
		sizeof(pl_inis)
	);
	memset(
		plds_counters_counts, 
		0, 
		sizeof(plds_counters_counts)
	);
	memset(
		p_counters_data, 
		0, 
		sizeof(p_counters_data)
	);

	//-------------------------------------------------------------------------
	// parse cli arguments
	//-------------------------------------------------------------------------
	pl_csv_logger_debug("Checking CLI Arguments.");
	ret = pl_csv_logger_cli_parser(
		argc, 
		argv
	);
	// should never happen - catched in pl_csv_logger_cli_parser 
	assert(ret != PL_FAILURE); 

	//-------------------------------------------------------------------------
	// print startup message
	//-------------------------------------------------------------------------
	for(i = 0; i < PL_CSV_LOGGER_STARTUP_MESSAGE_LINES_COUNT; i++) {
		fprintf(
			stderr, 
			"%s", 
			startup[i]
		);
	}
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	fprintf(stderr, "\n");
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	for(i = 0; i < pl_count; i++) {
		pl_csv_logger_info(
			"Using PL.........: ", 
			pl_inis[i]
		);
	}

	//-------------------------------------------------------------------------
	// install the signal handler routine
	//-------------------------------------------------------------------------
	pl_csv_logger_debug("Installing Signal Handler.");
#ifdef __PL_WINDOWS__
	bret = SetConsoleCtrlHandler(
		(PHANDLER_ROUTINE)signal_handler, 
		TRUE
	);
	if(bret == 0) {
		pl_csv_logger_error(PL_CSV_LOGGER_ERROR_UNABLE_TO_SET_SIGNAL_HANDLER);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags = 0;
	ret = sigaction(
		SIGINT, 
		&sa, 
		NULL
	);
	if(ret == -1) {
		pl_csv_logger_error(PL_CSV_LOGGER_ERROR_UNABLE_TO_SET_SIGNAL_HANDLER);
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// load PLs config contents and build log_header
	//-------------------------------------------------------------------------
	pl_csv_logger_debug(
		"Loading PL_CSV PL Configuration And Building Log File Header Line."
	);
	for(i = 0; i < pl_count; i++) { // for each PL

		//---------------------------------------------------------------------
		// load PLs config contents
		//---------------------------------------------------------------------
		memset(
			&pl_info, 
			0, 
			sizeof(pl_info)
		);
		ret = plh_read_pl_config_ini_file(
			pl_inis[i], 
			&pl_info
		);
		if(ret == PL_FAILURE) {
			pl_csv_logger_error(
				PL_CSV_LOGGER_ERROR_UNABLE_TO_READ_PL_INI_DATA
			);
		}
		plds_counters_counts[i] = pl_info.max_counters;

		//---------------------------------------------------------------------
		// build log_header
		//---------------------------------------------------------------------
		PL_CSV_LOGGER_LOG_HEADER_APPEND(PL_CSV_LOGGER_TIME_STAMP_HEADER);
#ifdef __PL_WINDOWS__
		memset(
			buffer, 
			0, 
			sizeof(buffer)
		);
		wcstombs(
			buffer, 
			pl_info.application_name, 
			PL_CSV_LOGGER_BUFFER_SIZE
		); 
		pl_csv_logger_info(
			"Application......: ", 
			buffer
		);
		pl_csv_logger_info(
			"Counter(s).......: ", 
			"..."
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		pl_csv_logger_info(
			"Application......: ", 
			pl_info.application_name
		);
		pl_csv_logger_info(
			"Counter(s).......: ", 
			"..."
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// allocate data for counter processing
		//---------------------------------------------------------------------
		if(process_flag == 1) {
			p_counters_data[i] = (PPL_CSV_LOGGER_COUNTER_DATA)malloc(
				sizeof(PL_CSV_LOGGER_COUNTER_DATA) * 
				pl_info.max_counters
			);
			if(p_counters_data[i] == NULL) {
				pl_csv_logger_error(PL_CSV_LOGGER_ERROR_MALLOC_FAIL);
			}
			memset(
				p_counters_data[i], 
				0, 
				sizeof(PL_CSV_LOGGER_COUNTER_DATA) * pl_info.max_counters
			);
		}
		
		// for each counter in Pl[i]
		for(j = 0; j < pl_info.max_counters; j++) { 

			//-----------------------------------------------------------------
			// for each counter in the PL
			//-----------------------------------------------------------------
#ifdef __PL_WINDOWS__
			memset(
				buffer, 
				0, 
				sizeof(buffer)
			);
			wcstombs(
				buffer, 
				pl_info.full_counter_names[j],
				PL_CSV_LOGGER_BUFFER_SIZE
			);
			PL_CSV_LOGGER_LOG_HEADER_APPEND(PL_CSV_LOGGER_QUOTES);
			PL_CSV_LOGGER_LOG_HEADER_APPEND(buffer);
			PL_CSV_LOGGER_LOG_HEADER_APPEND(PL_CSV_LOGGER_QUOTES);
			pl_csv_logger_info(
				".................: ", 
				buffer
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			PL_CSV_LOGGER_LOG_HEADER_APPEND(PL_CSV_LOGGER_QUOTES);
			PL_CSV_LOGGER_LOG_HEADER_APPEND(pl_info.full_counter_names[j]);
			PL_CSV_LOGGER_LOG_HEADER_APPEND(PL_CSV_LOGGER_QUOTES);
			pl_csv_logger_info(
				".................: ", 
				pl_info.full_counter_names[j]
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			PL_CSV_LOGGER_LOG_HEADER_APPEND(PL_CSV_LOGGER_LOG_SEPARATOR);

			//-----------------------------------------------------------------
			// counter processing
			//-----------------------------------------------------------------
			if(process_flag == 1) {

				/*
				 @@@@   @@@@  @    @ @    @  @@@@@ @@@@@@ @@@@@           @@   @    @   @@   @       @  @   @@@@  @@@@@   @@@@
				@    @ @    @ @    @ @@   @    @   @      @    @         @  @  @@   @  @  @  @       @  @  @    @   @    @    @
				@      @    @ @    @ @ @  @    @   @      @    @        @    @ @ @  @ @    @ @       @  @  @        @    @
				@      @    @ @    @ @ @  @    @   @@@@@@ @@@@@         @    @ @ @  @ @    @ @        @     @@@@    @     @@@@
				@      @    @ @    @ @  @ @    @   @      @  @          @@@@@@ @  @ @ @@@@@@ @        @         @   @         @
				@    @ @    @ @    @ @   @@    @   @      @   @         @    @ @   @@ @    @ @        @         @   @         @
				 @@@@   @@@@   @@@@  @    @    @   @@@@@@ @    @        @    @ @    @ @    @ @@@@@@   @    @@@@@  @@@@@  @@@@@
				*/

				//-------------------------------------------------------------
				// save counter name - memory was already allocated and cleared
				// for all counter of PL[i]
				//-------------------------------------------------------------
#ifdef __PL_WINDOWS__
				memset(
					buffer, 
					0, 
					sizeof(buffer)
				);
				wcstombs(
					buffer, 
					pl_info.counter_names[j], 
					PL_CSV_LOGGER_BUFFER_SIZE
				); 
				strncpy(
					p_counters_data[i][j].name, 
					buffer, 
					strlen(buffer)
				);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
				strncpy(
					p_counters_data[i][j].name, 
					pl_info.counter_names[j], 
					strlen(pl_info.counter_names[j])
				);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

				//-------------------------------------------------------------
				// search for various counter suffixs. if found, set the 
				// indexes to those counters and mark the counter as processed.
				// also mark suffix counters as processing data and not as a 
				// counter.
				//-------------------------------------------------------------

				/*
						@@@@  @@@@@@ @@@@@@  @@@@  @@@@@@  @@@@@        @@@@@  @@@@@@  @@@@  @@@@@  @    @   @@   @       @@@@
					   @    @ @      @      @    @ @         @          @    @ @      @    @   @    @@  @@  @  @  @      @    @
					   @    @ @      @      @      @         @          @    @ @      @        @    @ @@ @ @    @ @      @
					   @    @ @@@@@  @@@@@   @@@@  @@@@@@    @          @    @ @@@@@@ @        @    @    @ @    @ @       @@@@
					   @    @ @      @           @ @         @          @    @ @      @        @    @    @ @@@@@@ @           @
				  @@   @    @ @      @           @ @         @     @@   @    @ @      @    @   @    @    @ @    @ @           @
				  @@    @@@@  @      @      @@@@@  @@@@@@    @     @@   @@@@@  @@@@@@  @@@@  @@@@@  @    @ @    @ @@@@@@ @@@@@
				*/
				px = strstr(
					p_counters_data[i][j].name, 
					PL_CSV_LOGGER_COUNTER_OFFSET_DECIMALS_SUFFIX
				);
				if(px != NULL) {
					memset(
						counter_name_root, 
						0, 
						sizeof(counter_name_root)
					);
					strncpy(
						counter_name_root, 
						p_counters_data[i][j].name, 
						(px - p_counters_data[i][j].name)
					);

					//---------------------------------------------------------
					// search and link this .offset.decimals counter to the 
					// root counter
					//---------------------------------------------------------
					for(k = 0; k < j; k++) {
						if(
							(
								p_counters_data[i][k].processed != 
								PROCESSING_DATA
							) &&
							(strncmp(
								counter_name_root, 
								p_counters_data[i][k].name, 
								strlen(counter_name_root)
							) == 0)
						) {
							p_counters_data[i][k].i_offset_decimals = j;
							p_counters_data[i][k].processed |= 
								OFFSET_DECIMALS_PROCESSING;
							p_counters_data[i][j].processed = 
								PROCESSING_DATA;
							counter_count--;
							pl_csv_logger_debug(
								"This Counter Is Flagged As .offset.decimals Counter."
							);
							goto main_counter_processing_skip;
						}
					} // for k
				} // if .offset.decimals found

				/*
						@@@@  @@@@@@ @@@@@@  @@@@  @@@@@@  @@@@@         @@@@  @@@@@   @@@@  @    @
					   @    @ @      @      @    @ @         @          @    @   @    @    @ @@   @
					   @    @ @      @      @      @         @          @        @    @      @ @  @
					   @    @ @@@@@  @@@@@   @@@@  @@@@@@    @           @@@@    @    @      @ @  @
					   @    @ @      @           @ @         @               @   @    @  @@@ @  @ @
				  @@   @    @ @      @           @ @         @     @@        @   @    @    @ @   @@
				  @@    @@@@  @      @      @@@@@  @@@@@@    @     @@   @@@@@  @@@@@   @@@@  @    @
				*/
				px = strstr(
					p_counters_data[i][j].name, 
					PL_CSV_LOGGER_COUNTER_OFFSET_SIGN_SUFFIX
				);
				if(px != NULL) {
					memset(
						counter_name_root, 
						0, 
						sizeof(counter_name_root)
					);
					strncpy(
						counter_name_root, 
						p_counters_data[i][j].name,
						(px - p_counters_data[i][j].name)
					);

					//---------------------------------------------------------
					// search and link this .offset.sign counter to the 
					// root counter
					//---------------------------------------------------------
					for(k = 0; k < j; k++) {
						if(
							(
								p_counters_data[i][k].processed != 
								PROCESSING_DATA
							) &&
							(strncmp(
								counter_name_root, 
								p_counters_data[i][k].name, 
								strlen(counter_name_root)
							) == 0)
						) {
							p_counters_data[i][k].i_offset_sign = j;
							p_counters_data[i][k].processed |= 
								OFFSET_SIGN_PROCESSING;
							p_counters_data[i][j].processed = 
								PROCESSING_DATA;
							counter_count--;
							pl_csv_logger_debug(
								"This Counter Is Flagged As .offset.sign Counter."
							);
							goto main_counter_processing_skip;
						}
					} // for k
				} // if .offset.sign found

				/*
					   @@@@@  @@@@@@  @@@@  @@@@@  @    @   @@   @       @@@@
					   @    @ @      @    @   @    @@  @@  @  @  @      @    @
					   @    @ @      @        @    @ @@ @ @    @ @      @
					   @    @ @@@@@@ @        @    @    @ @    @ @       @@@@
					   @    @ @      @        @    @    @ @@@@@@ @           @
				  @@   @    @ @      @    @   @    @    @ @    @ @           @
				  @@   @@@@@  @@@@@@  @@@@  @@@@@  @    @ @    @ @@@@@@ @@@@@
				*/
				px = strstr(
					p_counters_data[i][j].name, 
					PL_CSV_LOGGER_COUNTER_DECIMALS_SUFFIX
				);
				if(px != NULL) {
					memset(
						counter_name_root, 
						0, 
						sizeof(counter_name_root)
					);
					strncpy(
						counter_name_root, 
						p_counters_data[i][j].name, 
						(px - p_counters_data[i][j].name)
					);

					//---------------------------------------------------------
					// search and link this .decimals counter to the 
					// root counter
					//---------------------------------------------------------
					for(k = 0; k < j; k++) {
						if(
							(
								p_counters_data[i][k].processed != 
								PROCESSING_DATA
							) &&
							(strncmp(
								counter_name_root, 
								p_counters_data[i][k].name, 
								strlen(counter_name_root)
							) == 0)
						) {
							p_counters_data[i][k].i_decimals = j;
							p_counters_data[i][k].processed |= 
								DECIMALS_PROCESSING;
							p_counters_data[i][j].processed = 
								PROCESSING_DATA;
							counter_count--;
							pl_csv_logger_debug(
								"This Counter Is Flagged As .decimals Counter."
							);
							goto main_counter_processing_skip;
						}
					} // for k
				} // if .decimals found

				/*
						@@@@  @@@@@@ @@@@@@  @@@@  @@@@@@  @@@@@
					   @    @ @      @      @    @ @         @
					   @    @ @      @      @      @         @
					   @    @ @@@@@  @@@@@   @@@@  @@@@@@    @
					   @    @ @      @           @ @         @
				  @@   @    @ @      @           @ @         @
				  @@    @@@@  @      @      @@@@@  @@@@@@    @
				*/
				px = strstr(
					p_counters_data[i][j].name, 
					PL_CSV_LOGGER_COUNTER_OFFSET_SUFFIX
				);
				if(px != NULL) {
					memset(
						counter_name_root, 
						0, 
						sizeof(counter_name_root)
					);
					strncpy(
						counter_name_root, 
						p_counters_data[i][j].name, 
						(px - p_counters_data[i][j].name)
					);

					//---------------------------------------------------------
					// search and link this .offset counter to the root counter
					//---------------------------------------------------------
					for(k = 0; k < j; k++) {
						if(
							(
								p_counters_data[i][k].processed != 
								PROCESSING_DATA
							) &&
							(strncmp(
								counter_name_root, 
								p_counters_data[i][k].name, 
								strlen(counter_name_root)
							) == 0)
						) {
							p_counters_data[i][k].i_offset = j;
							p_counters_data[i][k].processed |= 
								OFFSET_PROCESSING;
							p_counters_data[i][j].processed = 
								PROCESSING_DATA;
							counter_count--;
							pl_csv_logger_debug(
								"This Counter Is Flagged As .offset Counter."
							);
							goto main_counter_processing_skip;
						}
					} // for k
				} // if .offset found

				/*
						@@@@   @@@@    @@   @        @@   @@@@@         @@@@@  @@@@@@  @@@@  @@@@@  @    @   @@   @       @@@@
					   @    @ @    @  @  @  @       @  @  @    @        @    @ @      @    @   @    @@  @@  @  @  @      @    @
					   @      @      @    @ @      @    @ @    @        @    @ @      @        @    @ @@ @ @    @ @      @
						@@@@  @      @    @ @      @    @ @@@@@         @    @ @@@@@@ @        @    @    @ @    @ @       @@@@
							@ @      @@@@@@ @      @@@@@@ @  @          @    @ @      @        @    @    @ @@@@@@ @           @
				  @@        @ @    @ @    @ @      @    @ @   @    @@   @    @ @      @    @   @    @    @ @    @ @           @
				  @@   @@@@@   @@@@  @    @ @@@@@@ @    @ @    @   @@   @@@@@  @@@@@@  @@@@  @@@@@  @    @ @    @ @@@@@@ @@@@@
				*/
				px = strstr(
					p_counters_data[i][j].name, 
					PL_CSV_LOGGER_COUNTER_SCALAR_DECIMALS_SUFFIX
				);
				if(px != NULL) {
					memset(
						counter_name_root, 
						0, 
						sizeof(counter_name_root)
					);
					strncpy(
						counter_name_root, 
						p_counters_data[i][j].name, 
						(px - p_counters_data[i][j].name)
					);

					//-----------------------------------------------------------
					// search and link this .scalar.decimals counter to the root counter
					//-----------------------------------------------------------
					for(k = 0; k < j; k++) {
						if(
							(
								p_counters_data[i][k].processed != 
								PROCESSING_DATA
							) &&
							(strncmp(
								counter_name_root, 
								p_counters_data[i][k].name, 
								strlen(counter_name_root)
							) == 0)
						) {
							p_counters_data[i][k].i_scalar_decimals = j;
							p_counters_data[i][k].processed |= 
								SCALAR_DECIMALS_PROCESSING;
							p_counters_data[i][j].processed = 
								PROCESSING_DATA;
							counter_count--;
							pl_csv_logger_debug(
								"This Counter Is Flagged As .scalar.decimals Counter."
							);
							goto main_counter_processing_skip;
						}
					} // for k
				} // if .scalar.decimals found

				/*
						@@@@   @@@@    @@   @        @@   @@@@@
					   @    @ @    @  @  @  @       @  @  @    @
					   @      @      @    @ @      @    @ @    @
						@@@@  @      @    @ @      @    @ @@@@@
							@ @      @@@@@@ @      @@@@@@ @  @
				  @@        @ @    @ @    @ @      @    @ @   @
				  @@   @@@@@   @@@@  @    @ @@@@@@ @    @ @    @
				*/
				px = strstr(
					p_counters_data[i][j].name, 
					PL_CSV_LOGGER_COUNTER_SCALAR_SUFFIX
				);
				if(px != NULL) {
					memset(
						counter_name_root, 
						0, 
						sizeof(counter_name_root)
					);
					strncpy(
						counter_name_root, 
						p_counters_data[i][j].name, 
						(px - p_counters_data[i][j].name)
					);

					//---------------------------------------------------------
					// search and link this .scalar counter to the root counter
					//---------------------------------------------------------
					for(k = 0; k < j; k++) {
						if(
							(
								p_counters_data[i][k].processed != 
								PROCESSING_DATA
							) &&
							(strncmp(
								counter_name_root, 
								p_counters_data[i][k].name, 
								strlen(counter_name_root)
							) == 0)
						) {
							p_counters_data[i][k].i_scalar = j;
							p_counters_data[i][k].processed |= 
								SCALAR_PROCESSING;
							p_counters_data[i][j].processed = 
								PROCESSING_DATA;
							counter_count--;
							pl_csv_logger_debug(
								"This Counter Is Flagged As .scalar Counter."
							);
							goto main_counter_processing_skip;
						}
					} // for k
				} // if .scalar found

				/*
						@@@@  @@@@@   @@@@  @    @
					   @    @   @    @    @ @@   @
					   @        @    @      @ @  @
						@@@@    @    @      @ @  @
							@   @    @  @@@ @  @ @
				  @@        @   @    @    @ @   @@
				  @@   @@@@@  @@@@@   @@@@  @    @
				*/
				px = strstr(
					p_counters_data[i][j].name, 
					PL_CSV_LOGGER_COUNTER_SIGN_SUFFIX
				);
				if(px != NULL) {
					memset(
						counter_name_root, 
						0, 
						sizeof(counter_name_root)
					);
					strncpy(
						counter_name_root, 
						p_counters_data[i][j].name, 
						(px - p_counters_data[i][j].name)
					);

					//---------------------------------------------------------
					// search and link this .sign counter to the root counter
					//---------------------------------------------------------
					for(k = 0; k < j; k++) {
						if(
							(
								p_counters_data[i][k].processed != 
								PROCESSING_DATA
							) &&
							(strncmp(
								counter_name_root, 
								p_counters_data[i][k].name, 
								strlen(counter_name_root)
							) == 0)
						) {
							p_counters_data[i][k].i_sign = j;
							p_counters_data[i][k].processed |= 
								SIGN_PROCESSING;
							p_counters_data[i][j].processed = 
								PROCESSING_DATA;
							counter_count--;
							pl_csv_logger_debug(
								"This Counter Is Flagged As .sign Counter."
							);
							goto main_counter_processing_skip;
						}
					} // for k
				} // if .sign found
			} // if --process
main_counter_processing_skip:
			counter_count++;
		} // for j
	} // for i
	PL_CSV_LOGGER_LOG_HEADER_APPEND(PL_CSV_LOGGER_SAMPLE_HEADER);

	//-------------------------------------------------------------------------
	// display log and user provided config infos
	//-------------------------------------------------------------------------
	pl_csv_logger_info_int(
		"Pause Time       : ", 
		pause_time
	);
	if(process_flag == 1) { 
		pl_csv_logger_info(
			"Processing       : ", 
			"YES"
		); 
	} else { 
		pl_csv_logger_info(
			"Processing       : ", 
			"NO"
		); 
	}
	pl_csv_logger_info_int(
		"Logged PL(s)     : ", 
		pl_count
	);
	pl_csv_logger_info_int(
		"Logged Counter(s): ", 
		counter_count
	);

	//-------------------------------------------------------------------------
	// open log file
	//-------------------------------------------------------------------------
	pl_csv_logger_debug(
		"Opening Log File."
	);
	if(log_file_name != 0) {
		f = fopen(
			log_file_name, 
			PL_CSV_LOGGER_LOG_FILE_ACCESS_MODE
		);
		if(!f) {
			pl_csv_logger_error(
				PL_CSV_LOGGER_ERROR_UNABLE_TO_CREATE_LOG_FILE
			);
		}
		pl_csv_logger_info(
			"Saving Log Into  : ", 
			log_file_name
		);	
	} else {
		f = stdout;
		pl_csv_logger_info(
			"Saving Log Into  : ", 
			"stdout"
		);
	}

	//-------------------------------------------------------------------------
	// write log_header
	//-------------------------------------------------------------------------
	pl_csv_logger_debug(
		"Writing Openning Log File."
	);
	ret = fwrite(
		log_header, 
		strlen(log_header), 
		sizeof(char), 
		f
	);
	if(ret == 0) {
		pl_csv_logger_error(
			PL_CSV_LOGGER_ERROR_UNABLE_TO_WRITE_LOG_FILE_HEADER
		);
	}

	//-------------------------------------------------------------------------
	// open PLs
	//-------------------------------------------------------------------------
	pl_csv_logger_debug(
		"Attaching To PLs."
	);
	for(i = 0; i < pl_count; i++) {
		plds[i] = pl_attach(pl_inis[i]);
		if(plds[i] == PL_INVALID_DESCRIPTOR) {
			pl_csv_logger_error(
				PL_CSV_LOGGER_ERROR_UNABLE_TO_ATTACH_TO_PL
			);
		}
	}

	//-------------------------------------------------------------------------
	// log until logger is interrupted (CTRL+C)
	//-------------------------------------------------------------------------
	pl_csv_logger_debug(
		"Starting Logging."
	);
	pl_csv_logger_info(
		"To Stop Logging  : ", 
		"<CRTL>+<C>"
	);

	/*
	@    @   @@   @@@@@  @    @        @       @@@@   @@@@  @@@@@
	@@  @@  @  @    @    @@   @        @      @    @ @    @ @    @
	@ @@ @ @    @   @    @ @  @        @      @    @ @    @ @    @
	@    @ @    @   @    @ @  @        @      @    @ @    @ @@@@@
	@    @ @@@@@@   @    @  @ @        @      @    @ @    @ @
	@    @ @    @   @    @   @@        @      @    @ @    @ @
	@    @ @    @ @@@@@  @    @        @@@@@@  @@@@   @@@@  @
	*/
	while(log_flag) {

		//---------------------------------------------------------------------
		// prepare collection time check
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = QueryPerformanceCounter(&start_time);
		if(bret == FALSE) {
			pl_csv_logger_error(
				"Unable To Read HP Timer"
			);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = gettimeofday(
			&start_time, 
			NULL
		);
		if(ret != 0) {
			pl_csv_logger_error(
				"Unable To Read HP Timer"
			);
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//-------------------------------------------------------------------
		// log file structurte:
		// Time stamp, [pl counters, ], ... [pl counters, ]\n
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		// add time stamp to log_line
		//-------------------------------------------------------------------
		memset(
			log_line, 
			0, 
			sizeof(log_line)
		);
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
			PL_CSV_LOGGER_TIME_BUFFER_SIZE
		);
#else // __PL_SOLARIS__
		ctime_r(
			&log_time, 
			time_buffer
		);
#endif // __PL_SOLARIS__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		strncpy(
			&time_buffer[PL_CSV_LOGGER_TIME_STAMP_OFFSET], 
			PL_CSV_LOGGER_LOG_SEPARATOR, 
			strlen(PL_CSV_LOGGER_LOG_SEPARATOR)
		);
		time_buffer[PL_CSV_LOGGER_TIME_STAMP_END_OFFSET] = '\0';
		strncat(
			log_line, 
			time_buffer, 
			sizeof(time_buffer)
		);

		//---------------------------------------------------------------------
		// read pls' counter(s) and append data to log_line
		//---------------------------------------------------------------------
		for(i = 0; i < pl_count; i++) {

			if(process_flag == 1) {

				//-------------------------------------------------------------
				// processing of counters
				//-------------------------------------------------------------
				for(j = 0; j < plds_counters_counts[i]; j++) {

					if(p_counters_data[i][j].processed != PROCESSING_DATA) {

						//-----------------------------------------------------
						// read counter j in PL i
						//-----------------------------------------------------
						ret = pl_read(
							plds[i], 
							&v, 
							j
						);
						if(ret == PL_FAILURE) {
							if(ret == PL_FAILURE) {
								pl_csv_logger_error(
									PL_CSV_LOGGER_ERROR_UNABLE_TO_READ_PL
								);
							}
						}

						if(p_counters_data[i][j].processed == NO_PROCESSING) {

							//-------------------------------------------------
							// no processing applied
							//-------------------------------------------------
							memset(
								cvt_buffer, 
								0, 
								sizeof(cvt_buffer)
							);
							sprintf(
								cvt_buffer, 
								PL_CSV_LOGGER_FORMAT, 
								v
							);
							strncat(
								log_line, 
								cvt_buffer, 
								strlen(cvt_buffer)
							);
							strncat(
								log_line, 
								PL_CSV_LOGGER_LOG_SEPARATOR, 
								strlen(PL_CSV_LOGGER_LOG_SEPARATOR)
							);

						} else { // processing has to be applied to this counter

							/*
							 @@@@   @@@@  @    @ @    @  @@@@@ @@@@@@ @@@@@         @@@@@  @@@@@   @@@@   @@@@  @@@@@@  @@@@   @@@@  @@@@@  @    @  @@@@
							@    @ @    @ @    @ @@   @    @   @      @    @        @    @ @    @ @    @ @    @ @      @    @ @    @   @    @@   @ @    @
							@      @    @ @    @ @ @  @    @   @      @    @        @    @ @    @ @    @ @      @      @      @        @    @ @  @ @
							@      @    @ @    @ @ @  @    @   @@@@@@ @@@@@         @@@@@  @@@@@  @    @ @      @@@@@@  @@@@   @@@@    @    @ @  @ @
							@      @    @ @    @ @  @ @    @   @      @  @          @      @  @   @    @ @      @           @      @   @    @  @ @ @  @@@
							@    @ @    @ @    @ @   @@    @   @      @   @         @      @   @  @    @ @    @ @           @      @   @    @   @@ @    @
							 @@@@   @@@@   @@@@  @    @    @   @@@@@@ @    @        @      @    @  @@@@   @@@@  @@@@@@ @@@@@  @@@@@  @@@@@  @    @  @@@@
							*/

							//-------------------------------------------------
							// set default sufix counter values, will be 
							// overwritten if counter exist.
							//-------------------------------------------------
							counter = v;
							counter_scalar = 1;
							counter_scalar_decimals = 0;
							counter_decimals = 0;
							counter_sign = 0;
							counter_offset = 0;
							counter_offset_decimals = 0;
							counter_offset_sign = 0;

							/*
								   @@@@@  @@@@@@  @@@@  @@@@@  @    @   @@   @       @@@@
								   @    @ @      @    @   @    @@  @@  @  @  @      @    @
								   @    @ @      @        @    @ @@ @ @    @ @      @
								   @    @ @@@@@@ @        @    @    @ @    @ @       @@@@
								   @    @ @      @        @    @    @ @@@@@@ @           @
							  @@   @    @ @      @    @   @    @    @ @    @ @           @
							  @@   @@@@@  @@@@@@  @@@@  @@@@@  @    @ @    @ @@@@@@ @@@@@
							*/
							if(
								p_counters_data[i][j].processed & 
								DECIMALS_PROCESSING
							) {
								ret = pl_read(
									plds[i], 
									&counter_decimals, 
									p_counters_data[i][j].i_decimals
								);
								if(ret == PL_FAILURE) {
									f_log_error = 1;
									goto main_compute_processed_counter_value;
								}
							}

							/*
									@@@@  @@@@@@ @@@@@@  @@@@  @@@@@@  @@@@@
								   @    @ @      @      @    @ @         @
								   @    @ @      @      @      @         @
								   @    @ @@@@@  @@@@@   @@@@  @@@@@@    @
								   @    @ @      @           @ @         @
							  @@   @    @ @      @           @ @         @
							  @@    @@@@  @      @      @@@@@  @@@@@@    @
							*/
							if(
								p_counters_data[i][j].processed & 
								OFFSET_PROCESSING
							) {

								//---------------------------------------------
								// read .offset counter first
								//---------------------------------------------
								ret = pl_read(
									plds[i], 
									&counter_offset, 
									p_counters_data[i][j].i_offset
								);
								if(ret == PL_FAILURE) {
									f_log_error = 1;
									goto main_compute_processed_counter_value;
								}

								/*
										@@@@  @@@@@@ @@@@@@  @@@@  @@@@@@  @@@@@        @@@@@  @@@@@@  @@@@  @@@@@  @    @   @@   @       @@@@
									   @    @ @      @      @    @ @         @          @    @ @      @    @   @    @@  @@  @  @  @      @    @
									   @    @ @      @      @      @         @          @    @ @      @        @    @ @@ @ @    @ @      @
									   @    @ @@@@@  @@@@@   @@@@  @@@@@@    @          @    @ @@@@@@ @        @    @    @ @    @ @       @@@@
									   @    @ @      @           @ @         @          @    @ @      @        @    @    @ @@@@@@ @           @
								  @@   @    @ @      @           @ @         @     @@   @    @ @      @    @   @    @    @ @    @ @           @
								  @@    @@@@  @      @      @@@@@  @@@@@@    @     @@   @@@@@  @@@@@@  @@@@  @@@@@  @    @ @    @ @@@@@@ @@@@@
								*/
								if(
									p_counters_data[i][j].processed & 
									OFFSET_DECIMALS_PROCESSING
								) {
									ret = pl_read(
										plds[i], 
										&counter_offset_decimals, 
										p_counters_data[i][j].i_offset_decimals
									);
									if(ret == PL_FAILURE) {
										f_log_error = 1;
										goto main_compute_processed_counter_value;
									}
								}

								/*
										@@@@  @@@@@@ @@@@@@  @@@@  @@@@@@  @@@@@         @@@@  @@@@@   @@@@  @    @
									   @    @ @      @      @    @ @         @          @    @   @    @    @ @@   @
									   @    @ @      @      @      @         @          @        @    @      @ @  @
									   @    @ @@@@@  @@@@@   @@@@  @@@@@@    @           @@@@    @    @      @ @  @
									   @    @ @      @           @ @         @               @   @    @  @@@ @  @ @
								  @@   @    @ @      @           @ @         @     @@        @   @    @    @ @   @@
								  @@    @@@@  @      @      @@@@@  @@@@@@    @     @@   @@@@@  @@@@@   @@@@  @    @
								*/
								if(
									p_counters_data[i][j].processed & 
									OFFSET_SIGN_PROCESSING
								) {
									ret = pl_read(
										plds[i], 
										&counter_offset_sign, 
										p_counters_data[i][j].i_offset_sign
									);
									if(ret == PL_FAILURE) {
										f_log_error = 1;
										goto main_compute_processed_counter_value;
									}
								}
							}

							/*
									@@@@   @@@@    @@   @        @@   @@@@@
								   @    @ @    @  @  @  @       @  @  @    @
								   @      @      @    @ @      @    @ @    @
									@@@@  @      @    @ @      @    @ @@@@@
										@ @      @@@@@@ @      @@@@@@ @  @
							  @@        @ @    @ @    @ @      @    @ @   @
							  @@   @@@@@   @@@@  @    @ @@@@@@ @    @ @    @
							*/
							if(
								p_counters_data[i][j].processed & 
								SCALAR_PROCESSING
							) {
								ret = pl_read(
									plds[i], 
									&counter_scalar, 
									p_counters_data[i][j].i_scalar
								);
								if(ret == PL_FAILURE) {
									f_log_error = 1;
									goto main_compute_processed_counter_value;
								}

								//---------------------------------------------
								// read .scalar.decimals counter
								//---------------------------------------------

								/*
										@@@@   @@@@    @@   @        @@   @@@@@         @@@@@  @@@@@@  @@@@  @@@@@  @    @   @@   @       @@@@
									   @    @ @    @  @  @  @       @  @  @    @        @    @ @      @    @   @    @@  @@  @  @  @      @    @
									   @      @      @    @ @      @    @ @    @        @    @ @      @        @    @ @@ @ @    @ @      @
										@@@@  @      @    @ @      @    @ @@@@@         @    @ @@@@@@ @        @    @    @ @    @ @       @@@@
											@ @      @@@@@@ @      @@@@@@ @  @          @    @ @      @        @    @    @ @@@@@@ @           @
								  @@        @ @    @ @    @ @      @    @ @   @    @@   @    @ @      @    @   @    @    @ @    @ @           @
								  @@   @@@@@   @@@@  @    @ @@@@@@ @    @ @    @   @@   @@@@@  @@@@@@  @@@@  @@@@@  @    @ @    @ @@@@@@ @@@@@
								*/
								if(
									p_counters_data[i][j].processed & 
									SCALAR_DECIMALS_PROCESSING
								) {
									ret = pl_read(
										plds[i], 
										&counter_scalar_decimals, 
										p_counters_data[i][j].i_scalar_decimals
									);
									if(ret == PL_FAILURE) {
										f_log_error = 1;
										goto main_compute_processed_counter_value;
									}
								}
							}

							/*
									@@@@  @@@@@   @@@@  @    @
								   @    @   @    @    @ @@   @
								   @        @    @      @ @  @
									@@@@    @    @      @ @  @
										@   @    @  @@@ @  @ @
							  @@        @   @    @    @ @   @@
							  @@   @@@@@  @@@@@   @@@@  @    @
							*/
							if(
								p_counters_data[i][j].processed & 
								SIGN_PROCESSING
							) {
								ret = pl_read(
									plds[i], 
									&counter_sign, 
									p_counters_data[i][j].i_sign
								);
								if(ret == PL_FAILURE) {
									f_log_error = 1;
									goto main_compute_processed_counter_value;
								}
							}

main_compute_processed_counter_value:

							memset(
								cvt_buffer, 
								0, 
								sizeof(cvt_buffer)
							);
							if(f_log_error == 0) {

								//---------------------------------------------
								// compute counter real value
								//---------------------------------------------
								processed_value = 
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

								//---------------------------------------------
								// append processed counter value to log line
								//---------------------------------------------
								sprintf(
									cvt_buffer, 
									PL_CSV_LOGGER_FP_FORMAT, 
									(int)counter_decimals, 
									processed_value
								);
							} else {
								strncpy(
									cvt_buffer, 
									PL_CSV_LOGGER_SAMPLE_FAIL, 
									strlen(PL_CSV_LOGGER_SAMPLE_FAIL)
								);
								f_log_error = 0;
							}
							strncat(
								log_line, 
								cvt_buffer, 
								strlen(cvt_buffer)
							);
							strncat(
								log_line, 
								PL_CSV_LOGGER_LOG_SEPARATOR, 
								strlen(PL_CSV_LOGGER_LOG_SEPARATOR)
							);
						}
					} else {

						//-----------------------------------------------------
						// this counter is used in another counter processing
						//-----------------------------------------------------
						strncat(
							log_line, 
							PL_CSV_LOGGER_PROCESSING_DATA_MARKER, 
							strlen(PL_CSV_LOGGER_PROCESSING_DATA_MARKER)
						);
					}
				} // for j

			} else {

				//-------------------------------------------------------------
				// no processing of counters
				//-------------------------------------------------------------
				for(j = 0; j < plds_counters_counts[i]; j++) {
					memset(
						cvt_buffer, 
						0, 
						sizeof(cvt_buffer)
					);
					ret = pl_read(
						plds[i], 
						&v, 
						j
					);
					if(ret == PL_FAILURE) {
						strncpy(
							cvt_buffer, 
							PL_CSV_LOGGER_SAMPLE_FAIL, 
							strlen(PL_CSV_LOGGER_SAMPLE_FAIL)
						);
					} else {
						sprintf(
							cvt_buffer, 
							PL_CSV_LOGGER_FORMAT, 
							v
						);
					}
					strncat(
						log_line, 
						cvt_buffer, 
						strlen(cvt_buffer)
					);
					strncat(
						log_line, 
						PL_CSV_LOGGER_LOG_SEPARATOR, 
						strlen(PL_CSV_LOGGER_LOG_SEPARATOR)
					);
				}
			}
		}

		//---------------------------------------------------------------------
		// append sample(s) count
		//---------------------------------------------------------------------
		memset(
			cvt_buffer, 
			0, 
			sizeof(cvt_buffer)
		);
		sprintf(
			cvt_buffer, 
			PL_CSV_LOGGER_SAMPLE_FORMAT, 
			samples
		);
		strncat(
			log_line, 
			cvt_buffer, 
			strlen(cvt_buffer)
		);

		//---------------------------------------------------------------------
		// write log_line
		//---------------------------------------------------------------------
		ret = fwrite(
			log_line, 
			strlen(log_line), 
			sizeof(char), 
			f
		);
		if(ret == 0) {
			pl_csv_logger_error(
				PL_CSV_LOGGER_ERROR_UNABLE_TO_WRITE_LOG_ENTRY
			);
		}

		//-------------------------------------------------------------------
		// increment sample(s) count
		//-------------------------------------------------------------------
		samples++;

		//-------------------------------------------------------------------
		// print the sample count to stdout 
		//-------------------------------------------------------------------
		if(log_file_name != 0) {
#ifdef __PL_WINDOWS__
			chars_displayed = fprintf(
				stdout, 
				"Samples          : [%I64u]", 
				samples
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
			chars_displayed = fprintf(
				stdout, 
				"Samples          : [%llu]", 
				samples
			);
			fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			for(i = 0; i < chars_displayed; i++) { 
				fprintf(stdout, "\b"); 
			}
		}

		//---------------------------------------------------------------------------
		// compute time to sleep based on actual data collection & computation time
		//---------------------------------------------------------------------------
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
			(
				(end_time.tv_sec - start_time.tv_sec) * 
				(double)1000.0
			) + // 1 second = 1000 milliseconds
			(
				(end_time.tv_usec - start_time.tv_usec) / 
				(double)1000.0
			) // 1 microsecond = 0.001 milliseconds 
			// or 1 millisecond = 1000 microseconds
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		time_to_sleep_in_ms = 
			maximum_allowed_measurement_time_in_ms - 
			actual_measurement_time_in_ms
		;

		//---------------------------------------------------------------------
		// pause
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		Sleep((DWORD)time_to_sleep_in_ms);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		time_to_sleep_in_s = (int)(
			time_to_sleep_in_ms / 
			(double)1000.0
		);
		time_spec.tv_sec = time_to_sleep_in_s;
		time_spec.tv_nsec = (long int)(
			(time_to_sleep_in_ms - 
			(
				time_to_sleep_in_s * 
				(double)1000.0)
			) * 
			(double)1000000.0
		); // 1 millisecond = 1 000 000 nanoseconds
		ret = nanosleep(
			&time_spec, 
			NULL
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// check collection time
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = QueryPerformanceCounter(&end_time);
		if(bret == FALSE) {
			pl_csv_logger_error(
				PL_CSV_LOGGER_ERROR_UNABLE_TO_READ_SYSTEM_TIME
			);
		}
		total_duration_in_ms = (
			(double)(
				(
					end_time.QuadPart - 
					start_time.QuadPart
				) * 
				(double)1000.0 /
				(double)frequency.QuadPart
			)
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = gettimeofday(
			&end_time, 
			NULL
		);
		if(ret == -1) {
			pl_csv_logger_error(
				PL_CSV_LOGGER_ERROR_UNABLE_TO_READ_SYSTEM_TIME
			);
		}
		total_duration_in_ms = (double)( 
			(
				(end_time.tv_sec - start_time.tv_sec) * 
				(double)1000.0
			) + // 1 second = 1000 milliseconds
			(
				(end_time.tv_usec - start_time.tv_usec) / 
				(double)1000.0
			) // 1 microsecond = 0.001 milliseconds 
			// or 1 millisecond = 1000 microseconds
		);
#ifndef __PL_MACOSX__
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef _DEBUG
		fprintf(
			stdout,
			"Log Total Time: [%+8.2f] ms -> M: [%+8.2f] ms + S: [%+8.2f] ms.\n",
			total_duration_in_ms,
			actual_measurement_time_in_ms,
			time_to_sleep_in_ms
		);
#endif // _DEBUG

		if(
			total_duration_in_ms > 
			maximum_allowed_measurement_time_in_ms + ALLOWED_TIME_MARGIN_IN_MS
		) {
			fprintf(
				stdout, 
				"log Took [%+8.2f] ms instead of <= [%+8.2f] ms (M: [%+8.2f] ms + S: [%+8.2f] ms).\n",
				total_duration_in_ms,
					maximum_allowed_measurement_time_in_ms + 
					ALLOWED_TIME_MARGIN_IN_MS,
				actual_measurement_time_in_ms,
				time_to_sleep_in_ms
			);
		}
	} // while

	//-----------------------------------------------------------------------
	// free data for counter processing
	//-----------------------------------------------------------------------
	if(process_flag == 1) {
		for(i = 0; i < pl_count; i++) {
			if(p_counters_data[i] != NULL) {
				free(p_counters_data[i]);
				p_counters_data[i] = NULL;
			}
		}
	}

	//-----------------------------------------------------------------------
	// close log file
	//-----------------------------------------------------------------------
	pl_csv_logger_debug(
		"Closing Log File."
	);
	ret = fclose(f);
	if(ret != 0) {
		pl_csv_logger_error(
			PL_CSV_LOGGER_ERROR_UNABLE_TO_CLOSE_LOG_FILE
		);
	}

	//-----------------------------------------------------------------------
	// close PLs
	//-----------------------------------------------------------------------
	pl_csv_logger_debug(
		"Closing PLs."
	);
	for(i = 0; i < pl_count; i++) {
		ret = pl_close(plds[i]);
		if(ret == PL_FAILURE) {
			pl_csv_logger_error(
				PL_CSV_LOGGER_ERROR_UNABLE_TO_CLOSE_PL
			);
		}
	}

	//-----------------------------------------------------------------------
	// free memory used to store log header
	//-----------------------------------------------------------------------
	if(log_header != NULL) {
		memset(
			log_header,
			0,
			strlen(log_header)
		);
		free(log_header);
		log_header = NULL;
	}

#ifdef __PL_WINDOWS__
	//-------------------------------------------------------------------------
	// restore timer resolution 
	//-------------------------------------------------------------------------
	mmret = timeEndPeriod(--resolution);
	assert(mmret == TIMERR_NOERROR );
#endif // __PL_WINDOWS__

	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: signal_handler
Purpose : logger interrupt signal handler
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/26/2009    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
BOOL signal_handler(DWORD c) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
void signal_handler(int c) { 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	switch(c) { 

#ifdef __PL_WINDOWS__
		case CTRL_C_EVENT: 

			//-----------------------------------------------------------------
			// interrupt logger
			//-----------------------------------------------------------------
			log_flag = 0;
			return(TRUE);

		default: 
			return(FALSE); 
	} 
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		case SIGINT:

			//-----------------------------------------------------------------
			// interrupt logger
			//-----------------------------------------------------------------
			log_flag = 0;
			break;
	} 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
} 

/*-----------------------------------------------------------------------------
Function: pl_csv_logger_debug
Purpose : display a message
In      : pointer to string to display
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/26/2009    Jamel Tayeb             Creation.
*/
extern void pl_csv_logger_debug(char *s) {
	
	assert(s != NULL);

#ifdef _DEBUG
	fprintf(
		stdout, 
		"[DEBUG]: %s\n", 
		s
	);
#else // _DEBUG
	;
#endif // _DEBUG
}

/*-----------------------------------------------------------------------------
Function: pl_csv_logger_info
Purpose : display a message
In      : pointer to two strings to display
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/26/2009    Jamel Tayeb             Creation.
*/
extern void pl_csv_logger_info(char *s1, char *s2) {
	
	assert(s1 != NULL);
	assert(s2 != NULL);

	fprintf(
		stdout, 
		"%s[%s]\n", 
		s1, 
		s2
	);
}

/*--------------------------------------------------------------------------
Function: pl_csv_logger_info_int
Purpose : display a message with an integer
In      : pointer to two strings to display
Out     : none
Return  : none

History
------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/29/2009    Jamel Tayeb             Creation.
*/
void pl_csv_logger_info_int(char *s, int d) {
	
	assert(s != NULL);

	fprintf(
		stdout, 
		"%s[%d]\n", 
		s, 
		d
	);
}

/*-----------------------------------------------------------------------------
Function: pl_csv_logger_cli_parsero
Purpose : parse the cli
In      : main's arguments
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/29/2009    Jamel Tayeb             Creation.
*/
int pl_csv_logger_cli_parser(int argc, char *argv[]) {

	static char *cli_tokens[PL_CSV_LOGGER_CLI_MAX_TOKENS] = {
		PL_CSV_LOGGER_PROCESS,
		PL_CSV_LOGGER_TIME,
		PL_CSV_LOGGER_OUTPUT,
		PL_CSV_LOGGER_CLI_HELP,
		PL_CSV_LOGGER_VERSION
	};

	int i = 0;
	int t = 0;
	unsigned int j = 0;
	char *p1 = NULL;
	char *p2 = NULL;
	char s[PL_MAX_PATH];
	char *help[PL_CSV_LOGGER_HELP_MESSAGE_LINES_COUNT] = { 
		PL_CSV_LOGGER_HELP_MESSAGE_LINES 
	};
	char *suffixes_help[PL_CSV_LOGGER_SUFFIXES_HELP_MESSAGE_LINES_COUNT] = { 
		PL_CSV_LOGGER_SUFFIXES_HELP_MESSAGE_LINES 
	};

	//-------------------------------------------------------------------------
	// perfom pre-parsing checks
	//-------------------------------------------------------------------------
	if(argc <= 1) {
		goto pl_csv_logger_cli_parser_help;
	}

	//-------------------------------------------------------------------------
	// parse cli and setup PESRV structure
	//-------------------------------------------------------------------------
	for(i = 1; i < argc; i++) { // for each argument on the cli
		memset(
			s, 
			0, 
			sizeof(s)
		);
		strncpy(
			s, 
			argv[i], 
			strlen(argv[i])
		);
		plh_upper_string(s);
		// for each possible cli token
		for(t = 0; t < PL_CSV_LOGGER_CLI_MAX_TOKENS; t++) { 
			if(strncmp(
				s, 
				cli_tokens[t], 
				strlen(cli_tokens[t])
			) == 0) {
				switch(t) {

					case PL_CSV_LOGGER_PROCESS_TOKEN_ID:

						//-----------------------------------------------------
						// process --process option
						//-----------------------------------------------------
						process_flag = 1;
						goto pl_csv_logger_cli_parser_skip;
						break;

					case PL_CSV_LOGGER_TIME_TOKEN_ID:

						//-----------------------------------------------------
						// process --t [n] option
						//-----------------------------------------------------
						if(i < argc) {
							pause_time = atoi(argv[++i]);
							if(pause_time < 1) {
								pl_csv_logger_error(
									PL_CSV_LOGGER_ERROR_INVALID_PARAMETERS
								);
							}
							goto pl_csv_logger_cli_parser_skip;
						} else {
							goto pl_csv_logger_cli_parser_error;
						}
						break;

					case PL_CSV_LOGGER_OUTPUT_TOKEN_ID:

						//-----------------------------------------------------
						// process --output [file name] option
						//-----------------------------------------------------
						if(i < argc) {
							log_file_name = argv[++i];
							goto pl_csv_logger_cli_parser_skip;
						}
						break;

					case PL_CSV_LOGGER_VERSION_TOKEN_ID:

						//-----------------------------------------------------
						// process --version option and exit
						//-----------------------------------------------------
						print_version_info(
							PL_CSV_LOGGER_NAME, 
							PL_CSV_LOGGER_VERSION_MAJOR, 
							PL_CSV_LOGGER_VERSION_MINOR, 
							PL_CSV_LOGGER_VERSION_REVISION
						);
						exit(PL_SUCCESS);
						break;

					case PL_CSV_LOGGER_CLI_HELP_TOKEN_ID:

						//-----------------------------------------------------
						// process --help options and exit
						//-----------------------------------------------------
						if(process_flag == 0) { // --help alone
pl_csv_logger_cli_parser_help:
							for(
								i = 0; 
								i < PL_CSV_LOGGER_HELP_MESSAGE_LINES_COUNT; 
								i++
							) {
								fprintf(
									stderr, 
									"%s", 
									help[i]
								);
							}
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
							fprintf(
								stderr, 
								"\n"
							);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						} else { // --help with --process
							for(
								i = 0; 
								i < PL_CSV_LOGGER_SUFFIXES_HELP_MESSAGE_LINES_COUNT; 
								i++
							) {
								fprintf(
									stderr, 
									"%s", 
									suffixes_help[i]
								);
							}
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
							fprintf(
								stderr, 
								"\n"
							);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						}
						exit(PL_SUCCESS);
						break;

					default:
						break;
				}
			}
		}

		//---------------------------------------------------------------------
		// perform some - minimal - security checks
		//---------------------------------------------------------------------
		p1 = strstr(
			argv[i], 
			PL_CSV_LOGGER_PL_FOLDER
		);
		p2 = strstr(
			argv[i], 
			PL_CSV_LOGGER_PL_CONFIG_FILE_NAME
		);
		if(
			(p1 == NULL) || 
			(p2 == NULL)
		) {
			pl_csv_logger_error(
				PL_CSV_LOGGER_ERROR_SUSPICIOUS_PL_INI
			);
		}

		//---------------------------------------------------------------------
		// check if PL ini was not already provided
		//---------------------------------------------------------------------
		for(j = 0; j < pl_count; j++) {
			if(strncmp(
				argv[i], 
				pl_inis[j], 
				strlen(argv[i])
			) == 0) {
				goto pl_csv_logger_cli_parser_skip;
			}
		}

		//---------------------------------------------------------------------
		// save PL ini option
		//---------------------------------------------------------------------
		pl_inis[pl_count++] = argv[i];

pl_csv_logger_cli_parser_skip:
		;
	}

	//-------------------------------------------------------------------------
	// perfom post-parsing checks
	//-------------------------------------------------------------------------
	if(pl_count == PL_CSV_CONFIG_MIN_PL_INIS) {
		goto pl_csv_logger_cli_parser_help;
	}
	return(PL_SUCCESS);
pl_csv_logger_cli_parser_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: pl_csv_logger_error
Purpose : print error message and exit with error code
In      : pointer to error string
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/29/2009    Jamel Tayeb             Creation.
*/
void pl_csv_logger_error(char *e) {
	
	assert(e);

	fprintf(
		stderr, 
		"\n%s\n", 
		e
	);
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	fprintf(
		stderr, 
		"\n"
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	exit(PL_FAILURE);
}
