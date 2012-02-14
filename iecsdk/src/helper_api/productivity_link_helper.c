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
// Productivity Link helper Version Alpha 0.1
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>

#ifdef __PL_WINDOWS__
	#include <tchar.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#include <string.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <dirent.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <ctype.h>
	#include <errno.h> // compile with -D_LIBC_REENTRANT
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#include "productivity_link_helper.h"

/*-----------------------------------------------------------------------------
@@@@@  @@@@@@  @@@@   @@@@  @@@@@  @@@@@@        @@@@@@ @@@@@  @@@@@   @@@@  @@@@@
@    @ @      @    @ @    @ @    @ @             @      @    @ @    @ @    @ @    @
@    @ @      @      @    @ @    @ @             @      @    @ @    @ @    @ @    @
@    @ @@@@@@ @      @    @ @    @ @@@@@@        @@@@@@ @@@@@  @@@@@  @    @ @@@@@
@    @ @      @      @    @ @    @ @             @      @  @   @  @   @    @ @  @
@    @ @      @    @ @    @ @    @ @             @      @   @  @   @  @    @ @   @
@@@@@  @@@@@@  @@@@   @@@@  @@@@@  @@@@@@        @@@@@@ @    @ @    @  @@@@  @    @
                                          @@@@@@
Function: plh_decode_error
Purpose : prints error message to stderr.
In      : error code
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/06/2009    Jamel Tayeb             Creation.
*/
PL_API void plh_decode_error(PL_ERROR pl_error_code) {

/*
+-----------+----------+------------------------------------------------------+
| Decimal   | Hex      | Symbol                                               |
+-----------+----------+------------------------------------------------------+
| 268435456 | 10000000 | PL_INVALID_DESCRIPTOR                                |
| 268435457 | 10000001 | PL_BYPASSED                                          |
| 268435458 | 10000002 | PL_INVALID_PARAMETERS                                |
| 268435459 | 10000003 | PL_SYNCHRONIZATION_FAILED                            |
| 268435460 | 10000004 | PL_MISSING_DIRECTORY                                 |
| 268435461 | 10000005 | PL_NOT_A_DIRECTORY                                   |
| 268435462 | 10000006 | PL_DIRECTORY_CREATION_FAILED                         |
| 268435463 | 10000007 | PL_DIRECTORY_ALREADY_EXISTS                          |
| 268435464 | 10000008 | PL_PATH_NOT_FOUND                                    |
| 268435465 | 10000009 | PL_DESCRIPTOR_TABLE_FULL                             |
| 268435466 | 1000000a | PL_DESCRIPTOR_TABLE_UNINITIALIZED                    |
| 268435467 | 1000000b | PL_NON_GLOBAL_UUID_DESCRIPTOR                        |
| 268435468 | 1000000c | PL_NON_GLOBAL_UUID_DESCRIPTOR_NO_ADDRESS             |
| 268435469 | 1000000d | PL_GLOBAL_UUID_DESCRIPTOR_CREATION_FAILED            |
| 268435470 | 1000000e | PL_GLOBAL_UUID_DESCRIPTOR_TO_STRING_FAILED           |
| 268435471 | 1000000f | PL_CRITICAL_FAILURE                                  |
| 268435472 | 10000010 | PL_CONFIG_FILE_GENERATION_FAILED                     |
| 268435473 | 10000011 | PL_CONFIG_FILE_OPENING_FAILED                        |
| 268435474 | 10000012 | PL_COUNTER_CREATION_FAILED                           |
| 268435475 | 10000013 | PL_COUNTER_SEMAPHORE_CREATION_FAILED                 |
| 268435476 | 10000014 | PL_COUNTER_ATTACH_FAILED                             |
| 268435477 | 10000015 | PL_COUNTER_TO_STRING_FAILED                          |
| 268435478 | 10000016 | PL_COUNTER_WRITE_FAILED                              |
| 268435479 | 10000017 | PL_COUNTER_FILE_RESET_FILE_POINTER_FAILED            |
| 268435480 | 10000018 | PL_COUNTER_READ_FAILED                               |
| 268435481 | 10000019 | PL_COUNTER_FILE_LOCK_FAILED                          |
| 268435482 | 1000001a | PL_COUNTER_FILE_ALREADY_LOCKED                       |
| 268435483 | 1000001b | PL_COUNTER_FILE_UNLOCK_FAILED                        |
| 268435484 | 1000001c | PL_COUNTER_VALUE_OUT_OF_RANGE                        |
| 268435485 | 1000001d | PL_OUT_OF_MEMORY                                     |
| 268435486 | 1000001e | PL_OUT_OF_BUFFER_SPACE                               |
| 268435487 | 1000001f | PL_BLOCKING_PL_READ_INSTANCE_CREATION_FAILED         |
| 268435488 | 10000020 | PL_BLOCKING_PL_READ_INSTANCE_DESTRUCTION_FAILED      |
| 268435489 | 10000021 | PL_BLOCKING_PL_READ_HANDLE_CREATION_FAILED           |
| 268435490 | 10000022 | PL_BLOCKING_PL_READ_HANDLE_DESTRUCTION_FAILED        |
| 268435491 | 10000023 | PL_BLOCKING_PL_READ_HANDLE_RENEWING_FAILED           |
| 268435492 | 10000024 | PL_BLOCKING_PL_READ_WAITING_NOTIFICATION_FAILED      |
| 268435493 | 10000025 | PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE           |
| 268435494 | 10000026 | PL_FILESYSTEM_LESS_INITIALIZATION_FAILED             |
| 268435495 | 10000027 | PL_FILESYSTEM_LESS_NETWORK_ADDRESS_RESOLUTION_FAILED |
| 268435496 | 10000028 | PL_FILESYSTEM_LESS_SOCKET_FAILED                     |
| 268435497 | 10000029 | PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED               |
| 268435498 | 1000002a | PL_FILESYSTEM_LESS_CONNECTION_FAILED                 |
| 268435499 | 1000002b | PL_FILESYSTEM_LESS_SEND_FAILED                       |
| 268435500 | 1000002c | PL_FILESYSTEM_LESS_RECV_FAILED                       |
| 268435501 | 1000002d | PL_FILESYSTEM_LESS_INVALID_IPV4_ADDRESS              |
| 268435502 | 1000002e | PL_FILESYSTEM_LESS_INVALID_PORT                      |
| 268435503 | 1000002f | PL_COUNTER_WRITE_CACHE_HIT                           |
| 268435504 | 10000030 | PL_COUNTER_WRITE_CACHE_MISS                          |
| 268435505 | 10000031 | PL_NO_ERROR                                          |
+-----------+----------+------------------------------------------------------+
*/
	switch(pl_error_code) {
		case PL_INVALID_DESCRIPTOR:
			fprintf(
				stderr, 
				"Invalid PL Descriptor.\n"
			);
			break;

		case PL_BYPASSED:
			fprintf(
				stderr, 
				"PL Bypass.\n"
			);
			break;

		case PL_INVALID_PARAMETERS:
			fprintf(
				stderr, 
				"Invalid Parameters.\n"
			);
			break;

		case PL_SYNCHRONIZATION_FAILED:
			fprintf(
				stderr, 
				"Synchronization failed.\n"
			);
			break;

		case PL_MISSING_DIRECTORY:
			fprintf(
				stderr, 
				"Missing Directory.\n"
			);
			break;

		case PL_NOT_A_DIRECTORY:
			fprintf(
				stderr, 
				"Not A Directory.\n"
			);
			break;

		case PL_DIRECTORY_CREATION_FAILED:
			fprintf(
				stderr, 
				"Directory Creation Failed.\n"
			);
			break;

		case PL_DIRECTORY_ALREADY_EXISTS:
			fprintf(
				stderr, 
				"Existing Directory.\n"
			);
			break;

		case PL_PATH_NOT_FOUND:
			fprintf(
				stderr, 
				"Path Not Found.\n"
			);
			break;

		case PL_DESCRIPTOR_TABLE_FULL:
			fprintf(
				stderr, 
				"Full PL Descriptors Table.\n"
			);
			break;

		case PL_DESCRIPTOR_TABLE_UNINITIALIZED:
			fprintf(
				stderr, 
				"PL Descriptors Table Uninitialized.\n"
			);
			break;

		case PL_NON_GLOBAL_UUID_DESCRIPTOR:
			fprintf(
				stderr, 
				"Non Global Uuid.\n"
			);
			break;

		case PL_NON_GLOBAL_UUID_DESCRIPTOR_NO_ADDRESS:
			fprintf(
				stderr, 
				"No Address For Uuid.\n"
			);
			break;

		case PL_GLOBAL_UUID_DESCRIPTOR_CREATION_FAILED:
			fprintf(
				stderr, 
				"Uuid Creation Failed.\n"
			);
			break;

		case PL_GLOBAL_UUID_DESCRIPTOR_TO_STRING_FAILED:
			fprintf(
				stderr, 
				"Uuid conversion To String Failed.\n"
			);
			break;

		case PL_CRITICAL_FAILURE:
			fprintf(
				stderr, 
				"PL Critical Failure. Please Repport Issue to Intel Corporation.\n"
			);
			break;

		case PL_CONFIG_FILE_GENERATION_FAILED:
			fprintf(
				stderr, 
				"PL Configuration File Creation Failed.\n"
			);
			break;

		case PL_CONFIG_FILE_OPENING_FAILED:
			fprintf(
				stderr, 
				"PL Configuration File Open Failed.\n"
			);
			break;

		case PL_COUNTER_CREATION_FAILED:
			fprintf(
				stderr, 
				"PL Counter Creation Failed.\n"
			);
			break;

		case PL_COUNTER_SEMAPHORE_CREATION_FAILED:
			fprintf(
				stderr, 
				"PL Counter Semaphore Creation Failed.\n"
			);
			break;

		case PL_COUNTER_ATTACH_FAILED:
			fprintf(
				stderr, 
				"Unable To Attach To Counter.\n"
			);
			break;

		case PL_COUNTER_TO_STRING_FAILED:
			fprintf(
				stderr, 
				"PL Counter Value conversion To String Failed.\n"
			);
			break;

		case PL_COUNTER_WRITE_FAILED:
			fprintf(
				stderr, 
				"PL Counter Write Failed.\n"
			);
			break;

		case PL_COUNTER_FILE_RESET_FILE_POINTER_FAILED:
			fprintf(
				stderr, 
				"PL Counter Container Pointer Reset Failed.\n"
			);
			break;

		case PL_COUNTER_READ_FAILED:
			fprintf(
				stderr, 
				"PL Counter Read Failed.\n"
			);
			break;

		case PL_COUNTER_FILE_LOCK_FAILED:
			fprintf(
				stderr, 
				"PL Counter Lock Failed.\n"
			);
			break;

		case PL_COUNTER_FILE_ALREADY_LOCKED:
			fprintf(
				stderr, 
				"PL Counter Container Already Exist.\n"
			);
			break;

		case PL_COUNTER_FILE_UNLOCK_FAILED:
			fprintf(
				stderr, 
				"PL Counter Unlock Failed.\n"
			);
			break;

		case PL_COUNTER_VALUE_OUT_OF_RANGE:
			fprintf(
				stderr, 
				"PL Counter Value Out Of Range.\n"
			);
			break;

		case PL_OUT_OF_MEMORY:
			fprintf(
				stderr, 
				"Our Of Memory.\n"
			);
			break;

		case PL_OUT_OF_BUFFER_SPACE:
			fprintf(
				stderr, 
				"Our Of Buffer Space.\n"
			);
			break;

		case PL_BLOCKING_PL_READ_INSTANCE_CREATION_FAILED:
			fprintf(
				stderr, 
				"Blocking PL Creation Failed.\n"
			);
			break;

		case PL_BLOCKING_PL_READ_INSTANCE_DESTRUCTION_FAILED:
			fprintf(
				stderr, 
				"Blocking PL Destruction Failed.\n"
			);
			break;

		case PL_BLOCKING_PL_READ_HANDLE_CREATION_FAILED:
			fprintf(
				stderr, 
				"Blocking Pl Handle Creation Failed.\n"
			);
			break;

		case PL_BLOCKING_PL_READ_HANDLE_DESTRUCTION_FAILED:
			fprintf(
				stderr, 
				"Blockin PL Handle Destruction Failed.\n"
			);
			break;

		case PL_BLOCKING_PL_READ_HANDLE_RENEWING_FAILED:
			fprintf(
				stderr, 
				"Blocking PL Handle Read Failed.\n"
			);
			break;

		case PL_BLOCKING_PL_READ_WAITING_NOTIFICATION_FAILED:
			fprintf(
				stderr, 
				"Blocking PL Notification Wait Failed.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE:
			fprintf(
				stderr, 
				"File System-less Remote Critical Failure.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_INITIALIZATION_FAILED:
			fprintf(
				stderr, 
				"File System-less Initialization Failed.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_NETWORK_ADDRESS_RESOLUTION_FAILED:
			fprintf(
				stderr, 
				"File System-less Address Resolution Failed.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_SOCKET_FAILED:
			fprintf(
				stderr, 
				"File System-less Socket Creation Failed.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED:
			fprintf(
				stderr, 
				"File System-less Socket Destruction Failed.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_CONNECTION_FAILED:
			fprintf(
				stderr, 
				"File System-less Connection Failed.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_SEND_FAILED:
			fprintf(
				stderr, 
				"File System-less Send Failed.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_RECV_FAILED:
			fprintf(
				stderr, 
				"File System-less Receive Failed.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_INVALID_IPV4_ADDRESS:
			fprintf(
				stderr, 
				"File System-less Invalid IPV4 Address.\n"
			);
			break;

		case PL_FILESYSTEM_LESS_INVALID_PORT:
			fprintf(
				stderr, 
				"File System-less Invalid Port Number.\n"
			);
			break;

		case PL_COUNTER_WRITE_CACHE_HIT:
			fprintf(
				stderr, 
				"Write Cache Hit.\n"
			);
			break;

		case PL_COUNTER_WRITE_CACHE_MISS:
			fprintf(
				stderr, 
				"Write Cache Miss.\n"
			);
			break;

		case PL_NO_ERROR:
			fprintf(
				stderr, 
				"No Error.\n"
			);
			break;

		default:
			fprintf(
				stderr, 
				"Undefined Error.\n"
			);
			break;
	}
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	fprintf(
		stderr, 
		"\n"
	);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @@@@@  @@@@@@   @@   @@@@@         @@@@@  @              @@@@   @@@@  @    @ @@@@@@ @@@@@   @@@@         @@@@@  @    @ @@@@@         @@@@@@ @@@@@  @      @@@@@@
@    @ @      @    @        @    @ @       @  @  @    @        @    @ @             @    @ @    @ @@   @ @        @    @    @          @    @@   @   @           @        @    @      @
@    @ @      @    @        @    @ @      @    @ @    @        @    @ @             @      @    @ @ @  @ @        @    @               @    @ @  @   @           @        @    @      @
@@@@@  @      @@@@@@        @@@@@  @@@@@@ @    @ @    @        @@@@@  @             @      @    @ @ @  @ @@@@@    @    @               @    @ @  @   @           @@@@@    @    @      @@@@@@
@      @      @    @        @  @   @      @@@@@@ @    @        @      @             @      @    @ @  @ @ @        @    @  @@@          @    @  @ @   @           @        @    @      @
@      @      @    @        @   @  @      @    @ @    @        @      @             @    @ @    @ @   @@ @        @    @    @          @    @   @@   @           @        @    @      @
@      @@@@@@ @    @        @    @ @@@@@@ @    @ @@@@@         @      @@@@@@         @@@@   @@@@  @    @ @      @@@@@   @@@@         @@@@@  @    @ @@@@@         @      @@@@@  @@@@@@ @@@@@@
                     @@@@@@                             @@@@@@               @@@@@@                                           @@@@@@                      @@@@@@
Function: plh_read_pl_config_ini_file
Purpose : reads the specified pl configuration file.
In      : error code
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/06/2009    Jamel Tayeb             Creation.
*/
PL_API int plh_read_pl_config_ini_file(
	char *pl_config_file_name, 
	PPLH_CONFIG_INFO pconfig
) {

	unsigned int i = 0;
	unsigned int j = 0;
	int lines = 0;
	int pl_counters_count = 0;
	size_t length = 0;
	size_t initial_length = 0;
	char pl_buffer[PL_MAX_PATH] = { '\0' };
	char *p = NULL;

	char *pl_folder_substitute = NULL;
	char pl_local_pl_folder[PL_MAX_PATH] = { '\0' };
	int pl_folder_substitution = 0;
	char pl_temp[PL_MAX_PATH] = { '\0' };
	char *px = NULL;
	int char_count = 0;

#ifdef __PL_WINDOWS__
	size_t st_ret = 0;
	BOOL b_ret = FALSE;
	HANDLE pl_config_file = NULL;
	DWORD pl_config_file_bytes_to_read = 0;
	DWORD pl_config_file_bytes_read = 0;
	TCHAR pl_path[PL_MAX_PATH] = { '\0' };
	TCHAR pl_cvt_buffer[PL_MAX_PATH] = { '\0' };
	DWORD last_error = PL_NO_ERROR;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int b_ret = -1;
	int last_error = PL_NO_ERROR;
	int pl_config_file = -1;
	int pl_config_file_bytes_to_read = 0;
	int pl_config_file_bytes_read = 0;
	char pl_path[PL_MAX_PATH] = { '\0' };
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// check calling arguments.
	//-------------------------------------------------------------------------
	if(
		(pl_config_file_name == NULL) ||
		(pconfig == NULL)
	) {
		last_error = PL_INVALID_PARAMETERS;
		goto plh_read_pl_config_ini_file_return;
	}

	//-------------------------------------------------------------------------
	// open productivity link configuration file.
	//-------------------------------------------------------------------------
	memset(
		pl_path, 
		0, 
		sizeof(pl_path)
	);
#ifdef __PL_WINDOWS__
	mbstowcs_s(
		&st_ret, 
		pl_path, 
		strlen(pl_config_file_name) + 1, 
		pl_config_file_name, 
		_TRUNCATE
	);
	pl_config_file = CreateFile(
		pl_path, 
			GENERIC_READ, FILE_SHARE_READ | 
			FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		SECURITY_ANONYMOUS
	);
	if(pl_config_file == INVALID_HANDLE_VALUE) {
		last_error = PL_CONFIG_FILE_OPENING_FAILED;
		goto plh_read_pl_config_ini_file_return;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	strncpy(
		pl_path, 
		pl_config_file_name, 
		strlen(pl_config_file_name)
	);
	pl_config_file = open(
		pl_path, 
		O_RDONLY
	);
	if(pl_config_file == -1) {
		last_error = PL_CONFIG_FILE_OPENING_FAILED;
		goto plh_read_pl_config_ini_file_return;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// read-in the data stored in the productivity link configuration file.
	//-------------------------------------------------------------------------
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	pl_config_file_bytes_to_read = sizeof(char);
	p = pl_buffer;
	do {
#ifdef __PL_WINDOWS__
		b_ret = ReadFile(
			pl_config_file, 
			p, 
			pl_config_file_bytes_to_read, 
			&pl_config_file_bytes_read, 
			NULL
		);
		if(b_ret == FALSE) {
			if(pl_config_file_bytes_read == 0) {
				goto plh_read_pl_config_ini_file_eof;
			}
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		pl_config_file_bytes_read = read(
			pl_config_file, 
			p, 
			pl_config_file_bytes_to_read
		);
		if(pl_config_file_bytes_read == -1) {
			if(pl_config_file_bytes_read == 0) {
				goto plh_read_pl_config_ini_file_eof;
			}
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		switch(*p) {
#ifdef __PL_WINDOWS__
			case PL_LF: 
				*p = '\0'; 
				break;

			case PL_CR: 
				*p = '\0'; 
				lines++;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
			case PL_CR: 
				*p = '\0'; 
				break;

			case PL_LF: 
				*p = '\0'; 
				lines++;
#endif // __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
			case PL_LF: 
				*p = '\0'; 
				break;

			case PL_CR: 
				*p = '\0'; 
				lines++;
#endif // __PL_MACOSX__
		 		switch(lines) {

					//---------------------------------------------------------
					// collect application name.
					//---------------------------------------------------------
					case PL_CONFIGURATION_FILE_APPLICATION_NAME_LINE:
#ifdef __PL_WINDOWS__
						ZeroMemory(
							pl_cvt_buffer, 
							PL_MAX_PATH
						);
						mbstowcs_s(
							&st_ret, 
							pl_cvt_buffer, 
							sizeof(pl_cvt_buffer) / 2,pl_buffer, 
							strlen(pl_buffer)
						);
						wcsncpy_s(
							pconfig->application_name, 
							PL_MAX_PATH, 
							pl_cvt_buffer, 
							_TRUNCATE
						);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
						strncpy(
							pconfig->application_name, 
							pl_buffer, 
							strlen(pl_buffer)
						);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						break;

					//---------------------------------------------------------
					// collect uuid.
					//---------------------------------------------------------
					case PL_CONFIGURATION_FILE_UUID_STRING_LINE:
#ifdef __PL_WINDOWS__
						ZeroMemory(
							pl_cvt_buffer, 
							PL_MAX_PATH
						);
						mbstowcs_s(
							&st_ret, 
							pl_cvt_buffer, 
							sizeof(pl_cvt_buffer) / 2,pl_buffer, 
							strlen(pl_buffer)
						);
						wcsncpy_s(
							pconfig->uuid, 
							PL_MAX_PATH, 
							pl_cvt_buffer, 
							_TRUNCATE
						);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
						strncpy(
							pconfig->uuid, 
							pl_buffer, 
							strlen(pl_buffer)
						);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						break;

					//---------------------------------------------------------
					// collet pl root location.
					//---------------------------------------------------------
					case PL_CONFIGURATION_FILE_LOCATION_LINE:
#ifdef __PL_WINDOWS__
						ZeroMemory(
							pl_cvt_buffer, 
							PL_MAX_PATH
						);
						mbstowcs_s(
							&st_ret, 
							pl_cvt_buffer, 
							sizeof(pl_cvt_buffer) / 2,
							pl_buffer, 
							strlen(pl_buffer)
						);
						wcsncpy_s(
							pconfig->pl_root, 
							PL_MAX_PATH, 
							pl_cvt_buffer, 
							_TRUNCATE
						);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
						strncpy(
							pconfig->pl_root, 
							pl_buffer, 
							strlen(pl_buffer)
						);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						break;

					//---------------------------------------------------------
					// collect counters number.
					//---------------------------------------------------------
					case PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE:
						pl_counters_count = atoi(pl_buffer);
						pconfig->max_counters = pl_counters_count;
						break;

					//---------------------------------------------------------
					// collect and process each counter.
					//---------------------------------------------------------
					default:
#ifdef __PL_WINDOWS__

						//-----------------------------------------------------
						// perform PL_FOLDER substitution if required.
						//-----------------------------------------------------
						ZeroMemory(
							pl_cvt_buffer, 
							PL_MAX_PATH
						);
						pl_folder_substitute = strstr(
							pl_buffer, 
							PL_INI_NIX_FOLDER
						);
						// a pl_folder substitution is required for this counter
						if(pl_folder_substitute != NULL) { 
							// is it the first counter to be substituted?
							if(pl_folder_substitution == 0) { 
								// collect the local pl folder, do it once now
								px = strstr(
									pl_config_file_name, 
									PL_INI_CONFIG_FILE_NAME
								) - 2;
								while(
									*px-- != 
									PL_INI_WINDOWS_PATH_SEPARATOR_CHAR
								) { 
									char_count++; 
								};
								px += 2;
								strncpy_s(
									pl_local_pl_folder, 
									sizeof(pl_local_pl_folder), 
									pl_config_file_name, 
									(size_t)(px - pl_config_file_name)
								);
								pl_folder_substitution = 1;
							}
							ZeroMemory(
								pl_temp, 
								PL_MAX_PATH
							);
							strncpy_s(
								pl_temp, 
								sizeof(pl_temp), 
								pl_local_pl_folder, 
								strlen(pl_local_pl_folder)
							);
							strncat_s(
								pl_temp, 
								sizeof(pl_temp), 
									pl_folder_substitute + 
									strlen(PL_INI_NIX_FOLDER) + 
									1, 
								strlen(pl_folder_substitute)
							);
							px = strstr(
								pl_temp, 
								PL_INI_NIX_PATH_SEPARATOR
							);
							*px = PL_INI_WINDOWS_PATH_SEPARATOR_CHAR;
							mbstowcs_s(
								&st_ret, 
								pl_cvt_buffer, 
								sizeof(pl_cvt_buffer) / 2, 
								pl_temp, 
								strlen(pl_temp)
							);
						} else {
							mbstowcs_s(
								&st_ret, 
								pl_cvt_buffer, 
								sizeof(pl_cvt_buffer) / 2, 
								pl_buffer, 
								strlen(pl_buffer)
							);
						}
						wcsncpy_s(
							&pconfig->full_counter_names[i][0], 
							PL_MAX_PATH, 
							pl_cvt_buffer, 
							_TRUNCATE
						);
						initial_length = _tcslen(pl_cvt_buffer);
						length = initial_length;
						while(length) {
							if(
								pl_cvt_buffer[length--] != 
								PLH_DIR_SEPARATOR
							) {
							} else break;
						}
						for(
							j = 0; 
							j <= 
								(initial_length - length) - 
								sizeof(PLH_CHAR); 
							j++
						) {
							pconfig->counter_names[i][j] = 
								pl_cvt_buffer[
									length + 
									j + 
									sizeof(PLH_CHAR)
								];
						}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  

						//-----------------------------------------------------
						// perform PL_FOLDER substitution if required.
						//-----------------------------------------------------
						pl_folder_substitute = strstr(
							pl_buffer, 
							PL_INI_WINDOWS_FOLDER
						);
						// a pl_folder substitution is required for this counter
						if(pl_folder_substitute != NULL) { 
							// is it the first counter to be substituted?
							if(pl_folder_substitution == 0) { 
								// collect the local pl folder, do it once now
								px = strstr(
									pl_config_file_name, 
									PL_INI_CONFIG_FILE_NAME
								) - 2;
								while(
									*px-- != 
									PL_INI_NIX_PATH_SEPARATOR_CHAR
								) { 
									char_count++; 
								};
								px += 2;
								strncpy(
									pl_local_pl_folder, 
									pl_config_file_name, 
									(size_t)(px - pl_config_file_name)
								);
								pl_folder_substitution = 1;
							}
							memset(
								pl_temp, 
								0, 
								PL_MAX_PATH
							);
							strncpy(
								pl_temp, 
								pl_local_pl_folder, 
								strlen(pl_local_pl_folder)
							);
							strncat(
								pl_temp, 
									pl_folder_substitute + 
									strlen(PL_INI_NIX_FOLDER) - 
									1, 
								strlen(pl_folder_substitute)
							);
							px = strstr(
								pl_temp, 
								PL_INI_WINDOWS_PATH_SEPARATOR
							);
							*px = PL_INI_NIX_PATH_SEPARATOR_CHAR;
							memset(
								pl_buffer, 
								0, 
								PL_MAX_PATH
							);
							strncpy(
								pl_buffer, 
								pl_temp, 
								strlen(pl_temp)
							);
						}
						initial_length = strlen(pl_buffer);
						strncpy(
							&pconfig->full_counter_names[i][0], 
							pl_buffer, 
							initial_length
						);
						length = initial_length;
						while(length) {
							if(
								pl_buffer[length--] != 
								PLH_DIR_SEPARATOR
							) {
							} else { 
								length++; 
								break; 
							}
						}
						for(
							j = 0; 
							j <= 
								(initial_length - length) - 
								sizeof(PLH_CHAR); 
							j++
						) {
							pconfig->counter_names[i][j] = 
								pl_buffer[
									length + 
									j + 
									sizeof(PLH_CHAR)
								];
						}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						i++;
						if(
							i == 
							pconfig->max_counters
						) {
							// skip tagging data if any
							goto plh_read_pl_config_ini_file_eof;
						}
						pl_counters_count--;
						break;
				} // switch (lines)
				memset(
					pl_buffer, 
					0, 
					sizeof(pl_buffer)
				);
				p = pl_buffer;
				break;

#ifdef __PL_MACOSX__

				//-------------------------------------------------------------
				// PL_SOH found.
				//-------------------------------------------------------------
				case PL_SOH:
				case PL_EOT:
					break;
#endif // __PL_MACOSX__

			default:
				p++;
				break;
			} // switch (*p)
	} while(
		pl_config_file_bytes_read == 
		pl_config_file_bytes_to_read
	);

plh_read_pl_config_ini_file_eof:

	//-------------------------------------------------------------------------
	// close productivity link configuration file.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	b_ret = CloseHandle(pl_config_file);
	if(!b_ret) {
		last_error = PL_CRITICAL_FAILURE;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	b_ret = close(pl_config_file);
	if(b_ret == -1) {
		last_error = PL_CRITICAL_FAILURE;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

plh_read_pl_config_ini_file_return:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @@@@@   @  @  @    @   @@   @    @ @@@@@   @@@@         @@@@@  @@@@@@   @@   @@@@@         @@@@@  @              @@@@   @@@@  @    @ @@@@@@ @@@@@   @@@@         @@@@@  @    @ @@@@@         @@@@@@ @@@@@  @      @@@@@@
@    @ @      @    @        @    @  @  @  @@   @  @  @  @@  @@   @    @    @        @    @ @       @  @  @    @        @    @ @             @    @ @    @ @@   @ @        @    @    @          @    @@   @   @           @        @    @      @
@    @ @      @    @        @    @  @  @  @ @  @ @    @ @ @@ @   @    @             @    @ @      @    @ @    @        @    @ @             @      @    @ @ @  @ @        @    @               @    @ @  @   @           @        @    @      @
@@@@@  @      @@@@@@        @    @   @    @ @  @ @    @ @    @   @    @             @@@@@  @@@@@@ @    @ @    @        @@@@@  @             @      @    @ @ @  @ @@@@@    @    @               @    @ @  @   @           @@@@@    @    @      @@@@@@
@      @      @    @        @    @   @    @  @ @ @@@@@@ @    @   @    @             @  @   @      @@@@@@ @    @        @      @             @      @    @ @  @ @ @        @    @  @@@          @    @  @ @   @           @        @    @      @
@      @      @    @        @    @   @    @   @@ @    @ @    @   @    @    @        @   @  @      @    @ @    @        @      @             @    @ @    @ @   @@ @        @    @    @          @    @   @@   @           @        @    @      @
@      @@@@@@ @    @        @@@@@    @    @    @ @    @ @    @ @@@@@   @@@@         @    @ @@@@@@ @    @ @@@@@         @      @@@@@@         @@@@   @@@@  @    @ @      @@@@@   @@@@         @@@@@  @    @ @@@@@         @      @@@@@  @@@@@@ @@@@@@
                     @@@@@@                                                  @@@@@@                             @@@@@@               @@@@@@                                           @@@@@@                      @@@@@@
Function: plh_dynamic_read_pl_config_ini_file
Purpose : reads the specified pl configuration file and allocates memory
          to store counter data.
          it is the caller's responsibility to free memory allocated to
		  store the counter entries.
In      : error code
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
02/03/2010    Jamel Tayeb             Creation.
*/
PL_API int plh_dynamic_read_pl_config_ini_file(
	char *pl_config_file_name, 
	PPLH_DYNAMIC_CONFIG_INFO pconfig
) {

	unsigned int i = 0;
	unsigned int j = 0;
	int lines = 0;
	int pl_counters_count = 0;
	size_t length = 0;
	size_t initial_length = 0;
	char pl_buffer[PL_MAX_PATH] = { '\0' };
	char *p = NULL;

	char *pl_folder_substitute = NULL;
	char pl_local_pl_folder[PL_MAX_PATH] = { '\0' };
	int pl_folder_substitution = 0;
	char pl_temp[PL_MAX_PATH] = { '\0' };
	char *px = NULL;
	int char_count = 0;

#ifdef __PL_WINDOWS__
	size_t st_ret = 0;
	BOOL b_ret = FALSE;
	HANDLE pl_config_file = NULL;
	DWORD pl_config_file_bytes_to_read = 0;
	DWORD pl_config_file_bytes_read = 0;
	TCHAR pl_path[PL_MAX_PATH] = { '\0' };
	TCHAR pl_cvt_buffer[PL_MAX_PATH] = { '\0' };
	DWORD last_error = PL_NO_ERROR;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int b_ret = -1;
	int last_error = PL_NO_ERROR;
	int pl_config_file = -1;
	int pl_config_file_bytes_to_read = 0;
	int pl_config_file_bytes_read = 0;
	char pl_path[PL_MAX_PATH] = { '\0' };
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// check calling arguments.
	//-------------------------------------------------------------------------
	if(
		(pl_config_file_name == NULL) ||
		(pconfig == NULL)
	) {
		last_error = PL_INVALID_PARAMETERS;
		goto plh_read_pl_config_ini_file_return;
	}

	//-------------------------------------------------------------------------
	// open productivity link configuration file.
	//-------------------------------------------------------------------------
	memset(
		pl_path, 
		0, 
		sizeof(pl_path)
	);
#ifdef __PL_WINDOWS__
	mbstowcs_s(
		&st_ret, 
		pl_path, 
		strlen(pl_config_file_name) + 1, 
		pl_config_file_name, 
		_TRUNCATE
	);
	pl_config_file = CreateFile(
		pl_path, 
			GENERIC_READ, FILE_SHARE_READ | 
			FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		SECURITY_ANONYMOUS
	);
	if(pl_config_file == INVALID_HANDLE_VALUE) {
		last_error = PL_CONFIG_FILE_OPENING_FAILED;
		goto plh_read_pl_config_ini_file_return;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	strncpy(
		pl_path, 
		pl_config_file_name, 
		strlen(pl_config_file_name)
	);
	pl_config_file = open(
		pl_path, 
		O_RDONLY
	);
	if(pl_config_file == -1) {
		last_error = PL_CONFIG_FILE_OPENING_FAILED;
		goto plh_read_pl_config_ini_file_return;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-----------------------------------------------------------------------------
	// read-in the data stored in the productivity link configuration file.
	//-----------------------------------------------------------------------------
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	pl_config_file_bytes_to_read = sizeof(char);
	p = pl_buffer;
	do {
#ifdef __PL_WINDOWS__
		b_ret = ReadFile(
			pl_config_file, 
			p, 
			pl_config_file_bytes_to_read, 
			&pl_config_file_bytes_read, 
			NULL
		);
		if(b_ret == FALSE) {
			if(pl_config_file_bytes_read == 0) {
				goto plh_read_pl_config_ini_file_eof;
			}
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		pl_config_file_bytes_read = read(
			pl_config_file, 
			p, 
			pl_config_file_bytes_to_read
		);
		if(pl_config_file_bytes_read == -1) {
			if(pl_config_file_bytes_read == 0) {
				goto plh_read_pl_config_ini_file_eof;
			}
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		switch(*p) {
#ifdef __PL_WINDOWS__
			case PL_LF: 
				*p = '\0'; 
				break;

			case PL_CR: 
				*p = '\0'; 
				lines++;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
			case PL_CR: 
				*p = '\0'; 
				break;

			case PL_LF: 
				*p = '\0'; 
				lines++;
#endif // __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
			case PL_LF: 
				*p = '\0'; 
				break;

			case PL_CR: 
				*p = '\0'; 
				lines++;
#endif // __PL_MACOSX__
		 		switch(lines) {

					//---------------------------------------------------------
					// collect application name.
					//---------------------------------------------------------
					case PL_CONFIGURATION_FILE_APPLICATION_NAME_LINE:
#ifdef __PL_WINDOWS__
						ZeroMemory(
							pl_cvt_buffer, 
							PL_MAX_PATH
						);
						mbstowcs_s(
							&st_ret, 
							pl_cvt_buffer, 
							sizeof(pl_cvt_buffer) / 2,
							pl_buffer, 
							strlen(pl_buffer)
						);
						wcsncpy_s(
							pconfig->application_name, 
							PL_MAX_PATH, 
							pl_cvt_buffer, 
							_TRUNCATE
						);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
						strncpy(
							pconfig->application_name, 
							pl_buffer, 
							strlen(pl_buffer)
						);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						break;

					//---------------------------------------------------------
					// collect uuid.
					//---------------------------------------------------------
					case PL_CONFIGURATION_FILE_UUID_STRING_LINE:
#ifdef __PL_WINDOWS__
						ZeroMemory(
							pl_cvt_buffer, 
							PL_MAX_PATH
						);
						mbstowcs_s(
							&st_ret, 
							pl_cvt_buffer, 
							sizeof(pl_cvt_buffer) / 2,
							pl_buffer, 
							strlen(pl_buffer)
						);
						wcsncpy_s(
							pconfig->uuid, 
							PL_MAX_PATH, 
							pl_cvt_buffer, 
							_TRUNCATE
						);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
						strncpy(
							pconfig->uuid, 
							pl_buffer, 
							strlen(pl_buffer)
						);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						break;

					//-------------------------------------------------------------
					// collet pl root location.
					//-------------------------------------------------------------
					case PL_CONFIGURATION_FILE_LOCATION_LINE:
#ifdef __PL_WINDOWS__
						ZeroMemory(
							pl_cvt_buffer, 
							PL_MAX_PATH
						);
						mbstowcs_s(
							&st_ret, 
							pl_cvt_buffer, 
							sizeof(pl_cvt_buffer) / 2,
							pl_buffer, 
							strlen(pl_buffer)
						);
						wcsncpy_s(
							pconfig->pl_root, 
							PL_MAX_PATH, 
							pl_cvt_buffer, 
							_TRUNCATE
						);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
						strncpy(
							pconfig->pl_root, 
							pl_buffer, 
							strlen(pl_buffer)
						);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						break;

					//---------------------------------------------------------
					// collect counters number.
					//---------------------------------------------------------
					case PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE:
						pl_counters_count = atoi(pl_buffer);
						pconfig->max_counters = pl_counters_count;

						//-----------------------------------------------------
						// allocate memory to store the counters' data.
						//-----------------------------------------------------
						pconfig->entries = 
							(PPLH_DYNAMIC_CONFIG_INFO_ENTRY)malloc(
								sizeof(PLH_DYNAMIC_CONFIG_INFO_ENTRY) * 
								pconfig->max_counters
							);
						if(pconfig->entries == NULL) {
							last_error = PL_OUT_OF_MEMORY;
							goto plh_read_pl_config_ini_file_return;
						}
						memset(
							pconfig->entries, 
							0, 
								sizeof(PLH_DYNAMIC_CONFIG_INFO_ENTRY) * 
								pconfig->max_counters
						);
						break;

					//---------------------------------------------------------
					// collect and process each counter.
					//---------------------------------------------------------
					default:
#ifdef __PL_WINDOWS__

						//-----------------------------------------------------
						// perform PL_FOLDER substitution if required.
						//-----------------------------------------------------
						ZeroMemory(
							pl_cvt_buffer, 
							PL_MAX_PATH
						);
						pl_folder_substitute = strstr(
							pl_buffer, 
							PL_INI_NIX_FOLDER
						);
						// a pl_folder substitution is required for this counter
						if(pl_folder_substitute != NULL) { 
							// is it the first counter to be substituted?
							if(pl_folder_substitution == 0) { 
								// collect the local pl folder, do it once now
								px = strstr(
									pl_config_file_name, 
									PL_INI_CONFIG_FILE_NAME
								) - 2;
								while(
									*px-- != 
									PL_INI_WINDOWS_PATH_SEPARATOR_CHAR
								) { 
									char_count++; 
								};
								px += 2;
								strncpy_s(
									pl_local_pl_folder, 
									sizeof(pl_local_pl_folder), 
									pl_config_file_name, 
									(size_t)(px - pl_config_file_name)
								);
								pl_folder_substitution = 1;
							}
							ZeroMemory(
								pl_temp, 
								PL_MAX_PATH
							);
							strncpy_s(
								pl_temp, 
								sizeof(pl_temp), 
								pl_local_pl_folder, 
								strlen(pl_local_pl_folder)
							);
							strncat_s(
								pl_temp, 
								sizeof(pl_temp), 
									pl_folder_substitute + 
									strlen(PL_INI_NIX_FOLDER) + 
									1, 
								strlen(pl_folder_substitute)
							);
							px = strstr(
								pl_temp, 
								PL_INI_NIX_PATH_SEPARATOR
							);
							*px = PL_INI_WINDOWS_PATH_SEPARATOR_CHAR;
							mbstowcs_s(
								&st_ret, 
								pl_cvt_buffer, 
								sizeof(pl_cvt_buffer) / 2, 
								pl_temp, 
								strlen(pl_temp)
							);
						} else {
							mbstowcs_s(
								&st_ret, 
								pl_cvt_buffer, 
								sizeof(pl_cvt_buffer) / 2, 
								pl_buffer, 
								strlen(pl_buffer)
							);
						}
						wcsncpy_s(
							pconfig->entries[i].full_counter_names, 
							PL_MAX_PATH, 
							pl_cvt_buffer, 
							_TRUNCATE
						);
						initial_length = _tcslen(pl_cvt_buffer);
						length = initial_length;
						while(length) {
							if(
								pl_cvt_buffer[length--] != 
								PLH_DIR_SEPARATOR
							) {
							} else break;
						}
						for(
							j = 0; 
							j <= (initial_length - length) - sizeof(PLH_CHAR); 
							j++
						) {
							pconfig->entries[i].counter_names[j] = 
								pl_cvt_buffer[
									length + 
										j + 
										sizeof(PLH_CHAR)
								];
						}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  

						//-----------------------------------------------------
						// perform PL_FOLDER substitution if required.
						//-----------------------------------------------------
						pl_folder_substitute = strstr(
							pl_buffer, 
							PL_INI_WINDOWS_FOLDER
						);
						// a pl_folder substitution is required for this counter
						if(pl_folder_substitute != NULL) { 
							// is it the first counter to be substituted?
							if(pl_folder_substitution == 0) { 
								// collect the local pl folder, do it once now
								px = strstr(
									pl_config_file_name, 
									PL_INI_CONFIG_FILE_NAME) - 2
								;
								while(
									*px-- != 
									PL_INI_NIX_PATH_SEPARATOR_CHAR
								) { 
									char_count++; 
								};
								px += 2;
								strncpy(
									pl_local_pl_folder, 
									pl_config_file_name, 
									(size_t)(px - pl_config_file_name)
								);
								pl_folder_substitution = 1;
							}
							memset(
								pl_temp, 
								0, 
								PL_MAX_PATH
							);
							strncpy(
								pl_temp, 
								pl_local_pl_folder, 
								strlen(pl_local_pl_folder)
							);
							strncat(
								pl_temp, 
									pl_folder_substitute + 
									strlen(PL_INI_NIX_FOLDER) - 
									1, 
								strlen(pl_folder_substitute)
							);
							px = strstr(
								pl_temp, 
								PL_INI_WINDOWS_PATH_SEPARATOR
							);
							*px = PL_INI_NIX_PATH_SEPARATOR_CHAR;
							memset(
								pl_buffer, 
								0, 
								PL_MAX_PATH
							);
							strncpy(
								pl_buffer, 
								pl_temp, 
								strlen(pl_temp)
							);
						}
						initial_length = strlen(pl_buffer);
						strncpy(
							pconfig->entries[i].full_counter_names, 
							pl_buffer, 
							initial_length
						);
						length = initial_length;
						while(length) {
							if(
								pl_buffer[length--] != 
								PLH_DIR_SEPARATOR
							) {
							} else { 
								length++; 
								break; 
							}
						}
						for(
							j = 0; 
							j <= (initial_length - length) - sizeof(PLH_CHAR); 
							j++
						) {
							pconfig->entries[i].counter_names[j] =
								pl_buffer[
									length + 
									j + 
									sizeof(PLH_CHAR)
								];
						}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						i++;
						if(i == pconfig->max_counters) {
							// skip tagging data if any
							goto plh_read_pl_config_ini_file_eof; 
						}
						pl_counters_count--;
						break;
				} // switch (lines)
				memset(
					pl_buffer, 
					0, 
					sizeof(pl_buffer)
				);
				p = pl_buffer;
				break;
			
			default:
				p++;
				break;
			} // switch (*p)
	} while(
		pl_config_file_bytes_read == 
		pl_config_file_bytes_to_read
	);

plh_read_pl_config_ini_file_eof:

	//-------------------------------------------------------------------------
	// close productivity link configuration file.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	b_ret = CloseHandle(pl_config_file);
	if(!b_ret) {
		last_error = PL_CRITICAL_FAILURE;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	b_ret = close(pl_config_file);
	if(b_ret == -1) {
		last_error = PL_CRITICAL_FAILURE;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

plh_read_pl_config_ini_file_return:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @@@@@  @@@@@@   @@   @@@@@         @@@@@  @             @@@@@@  @@@@  @      @@@@@  @@@@@@ @@@@@
@    @ @      @    @        @    @ @       @  @  @    @        @    @ @             @      @    @ @      @    @ @      @    @
@    @ @      @    @        @    @ @      @    @ @    @        @    @ @             @      @    @ @      @    @ @      @    @
@@@@@  @      @@@@@@        @@@@@  @@@@@@ @    @ @    @        @@@@@  @             @@@@@  @    @ @      @    @ @@@@@@ @@@@@
@      @      @    @        @  @   @      @@@@@@ @    @        @      @             @      @    @ @      @    @ @      @  @
@      @      @    @        @   @  @      @    @ @    @        @      @             @      @    @ @      @    @ @      @   @
@      @@@@@@ @    @        @    @ @@@@@@ @    @ @@@@@         @      @@@@@@        @       @@@@  @@@@@@ @@@@@  @@@@@@ @    @
                     @@@@@@                             @@@@@@               @@@@@@
Function: plh_read_pl_folder
Purpose : reads the specified PL_FOLDER.
In      : error code
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/06/2009    Jamel Tayeb             Creation.
*/
PL_API int plh_read_pl_folder(PPLH_PL_FOLDER_INFO pconfig) {

	size_t lenght = 0;

#ifdef __PL_WINDOWS__
	DWORD last_error = PL_NO_ERROR;
	WIN32_FIND_DATA file_data;
	HANDLE file = NULL;
	BOOL b_ret = TRUE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	DIR *directory = NULL;
	struct dirent *file = NULL;
	int last_error = PL_NO_ERROR;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	memset(
		pconfig, 
		0, 
		sizeof(PLH_PL_FOLDER_INFO)
	);
#ifdef __PL_WINDOWS__
	memset(
		&file_data, 
		0, 
		sizeof(&file_data)
	);
	file = FindFirstFile(
		PLH_FOLDER_SEARCH, 
		&file_data
	);
	if(file != INVALID_HANDLE_VALUE) {
		do {
			lenght = _tcslen(file_data.cFileName);
			if(lenght > PLH_DESC_SCRIPT_UUID_STRING_SIZE) {
				_tcsncpy_s(
					pconfig->full_uuids[pconfig->max_uuids], 
					PL_MAX_PATH, 
					file_data.cFileName, 
					_TRUNCATE
				);
				_tcsncpy_s(
					pconfig->uuids[pconfig->max_uuids], 
					PL_MAX_PATH,
					&file_data.cFileName[
						lenght - 
						PLH_DESC_SCRIPT_UUID_STRING_SIZE
					], 
					(size_t)PLH_DESC_SCRIPT_UUID_STRING_SIZE
				);
				_tcsncpy_s(
					pconfig->application_names[pconfig->max_uuids], 
					PL_MAX_PATH, 
					file_data.cFileName, 
					(size_t)(
						lenght - 
						PLH_DESC_SCRIPT_UUID_STRING_SIZE - 
						1
					)
				);
				pconfig->max_uuids++;
			}
			b_ret = FindNextFile(
				file, 
				&file_data
			);
		} while(b_ret);
		FindClose(file);
	} else {
		last_error = GetLastError();
		goto plh_read_pl_folder_return;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	directory = opendir(PLH_FOLDER_SEARCH);
	if(directory != NULL) {
		file = readdir(directory);
		while(file != NULL) {
			lenght = strlen(file->d_name);
			if(lenght > PLH_DESC_SCRIPT_UUID_STRING_SIZE) {
				strncpy(
					pconfig->full_uuids[pconfig->max_uuids], 
					file->d_name, 
					strlen(file->d_name)
				);
				strncpy(
					pconfig->uuids[pconfig->max_uuids], 
					&file->d_name[
						lenght - 
						PLH_DESC_SCRIPT_UUID_STRING_SIZE
					], 
					(size_t)PLH_DESC_SCRIPT_UUID_STRING_SIZE
				);
				strncpy(
					pconfig->application_names[pconfig->max_uuids], 
					file->d_name, 
					(size_t)(
						lenght - 
						PLH_DESC_SCRIPT_UUID_STRING_SIZE - 
						1
					)
				);
				pconfig->max_uuids++;
			}
			file = readdir(directory);
		}
		closedir(directory);
	} else {
		last_error = errno;
		goto plh_read_pl_folder_return;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

plh_read_pl_folder_return:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @@@@@   @  @  @    @   @@   @    @ @@@@@   @@@@         @@@@@  @@@@@@   @@   @@@@@         @@@@@  @             @@@@@@  @@@@  @      @@@@@  @@@@@@ @@@@@
@    @ @      @    @        @    @  @  @  @@   @  @  @  @@  @@   @    @    @        @    @ @       @  @  @    @        @    @ @             @      @    @ @      @    @ @      @    @
@    @ @      @    @        @    @  @  @  @ @  @ @    @ @ @@ @   @    @             @    @ @      @    @ @    @        @    @ @             @      @    @ @      @    @ @      @    @
@@@@@  @      @@@@@@        @    @   @    @ @  @ @    @ @    @   @    @             @@@@@  @@@@@@ @    @ @    @        @@@@@  @             @@@@@  @    @ @      @    @ @@@@@@ @@@@@
@      @      @    @        @    @   @    @  @ @ @@@@@@ @    @   @    @             @  @   @      @@@@@@ @    @        @      @             @      @    @ @      @    @ @      @  @
@      @      @    @        @    @   @    @   @@ @    @ @    @   @    @    @        @   @  @      @    @ @    @        @      @             @      @    @ @      @    @ @      @   @
@      @@@@@@ @    @        @@@@@    @    @    @ @    @ @    @ @@@@@   @@@@         @    @ @@@@@@ @    @ @@@@@         @      @@@@@@        @       @@@@  @@@@@@ @@@@@  @@@@@@ @    @
                     @@@@@@                                                  @@@@@@                             @@@@@@               @@@@@@
Function: plh_dynamic_read_pl_folder
Purpose : reads - and allocates memory - the specified PL_FOLDER.
          the caller must free the allocated memory.
In      : error code
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
02/01/2010    Jamel Tayeb             Creation.
*/
PL_API int plh_dynamic_read_pl_folder(PPLH_DYNAMIC_PL_FOLDER_INFO pconfig) {

#ifdef __PL_WINDOWS__
	DWORD last_error = PL_NO_ERROR;
	WIN32_FIND_DATA file_data;
	HANDLE file = NULL;
	BOOL b_ret = TRUE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	DIR *directory = NULL;
	struct dirent *file = NULL;
	int last_error = PL_NO_ERROR;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	size_t lenght = 0;
	PPLH_DYNAMIC_PL_FOLDER_INFO_ENTRY p = NULL;
	size_t max_entries = PLH_MAX_UUIDS;

	assert(pconfig != NULL);

	memset(
		pconfig, 
		0, 
		sizeof(pconfig)
	);
	p = (PPLH_DYNAMIC_PL_FOLDER_INFO_ENTRY)malloc(
		sizeof(PLH_DYNAMIC_PL_FOLDER_INFO_ENTRY) * 
		max_entries
	);
	if(p == NULL) {
		last_error = PL_OUT_OF_MEMORY;
		goto plh_dynamic_read_pl_folder_return;
	}
	memset(
		p, 
		0, 
			sizeof(PLH_DYNAMIC_PL_FOLDER_INFO_ENTRY) * 
			max_entries
	);
	pconfig->entries = p;

#ifdef __PL_WINDOWS__
	memset(
		&file_data, 
		0, 
		sizeof(&file_data)
	);
	file = FindFirstFile(
		PLH_FOLDER_SEARCH, 
		&file_data
	);
	if(file != INVALID_HANDLE_VALUE) {
		do {
			lenght = _tcslen(file_data.cFileName);
			if(lenght > PLH_DESC_SCRIPT_UUID_STRING_SIZE) {
				if(pconfig->max_uuids >= max_entries) {
					p = NULL;
					p = 
						(PPLH_DYNAMIC_PL_FOLDER_INFO_ENTRY)realloc(
							pconfig->entries, 
								sizeof(PLH_DYNAMIC_PL_FOLDER_INFO_ENTRY) * 
								max_entries * 
								2
						);
					if(p == NULL) {
						free(pconfig->entries);
						pconfig->entries = NULL;
						pconfig->max_uuids = 0;
						last_error = PL_OUT_OF_MEMORY;
						goto plh_dynamic_read_pl_folder_return;
					}
					pconfig->entries = p;
					memset(
						&pconfig->entries[pconfig->max_uuids], 
						0, 
							sizeof(PLH_DYNAMIC_PL_FOLDER_INFO_ENTRY) * 
							max_entries
					);
					max_entries *= 2;
				}
				_tcsncpy_s(
					pconfig->entries[pconfig->max_uuids].full_uuid, 
					PL_MAX_PATH, 
					file_data.cFileName, 
					_TRUNCATE
				);
				_tcsncpy_s(
					pconfig->entries[pconfig->max_uuids].uuid, 
					PL_MAX_PATH, 
					&file_data.cFileName[
						lenght - 
						PLH_DESC_SCRIPT_UUID_STRING_SIZE
					], 
					(size_t)PLH_DESC_SCRIPT_UUID_STRING_SIZE
				);
				_tcsncpy_s(
					pconfig->entries[pconfig->max_uuids].application_name, 
					PL_MAX_PATH, 
					file_data.cFileName, 
					(size_t)(
						lenght - 
						PLH_DESC_SCRIPT_UUID_STRING_SIZE - 
						1
					)
				);
				pconfig->max_uuids++;
			}
			b_ret = FindNextFile(
				file, 
				&file_data
			);
		} while(b_ret);
		FindClose(file);
	} else {
		last_error = GetLastError();
		goto plh_dynamic_read_pl_folder_return;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	directory = opendir(PLH_FOLDER_SEARCH);
	if(directory != NULL) {
		file = readdir(directory);
		while(file != NULL) {
			lenght = strlen(file->d_name);
			if(lenght > PLH_DESC_SCRIPT_UUID_STRING_SIZE) {
				if(pconfig->max_uuids >= max_entries) {
					p = NULL;
					p = (PPLH_DYNAMIC_PL_FOLDER_INFO_ENTRY)realloc(
						pconfig->entries, 
							sizeof(PLH_DYNAMIC_PL_FOLDER_INFO_ENTRY) * 
							max_entries * 
							2
					);
					if(p == NULL) {
						free(pconfig->entries);
						pconfig->entries = NULL;
						pconfig->max_uuids = 0;
						last_error = PL_OUT_OF_MEMORY;
						goto plh_dynamic_read_pl_folder_return;
					}
					pconfig->entries = p;
					memset(
						&pconfig->entries[pconfig->max_uuids], 
						0, 
							sizeof(PLH_DYNAMIC_PL_FOLDER_INFO_ENTRY) * 
							max_entries
					);
					max_entries *= 2;
				}
				strncpy(
					pconfig->entries[pconfig->max_uuids].full_uuid, 
					file->d_name, 
					strlen(file->d_name)
				);
				strncpy(
					pconfig->entries[pconfig->max_uuids].uuid, 
					&file->d_name[
						lenght - 
						PLH_DESC_SCRIPT_UUID_STRING_SIZE
					], 
					(size_t)PLH_DESC_SCRIPT_UUID_STRING_SIZE
				);
				strncpy(
					pconfig->entries[pconfig->max_uuids].application_name, 
					file->d_name, 
					(size_t)(
						lenght - 
						PLH_DESC_SCRIPT_UUID_STRING_SIZE - 
						1
					)
				);
				pconfig->max_uuids++;
			}
			file = readdir(directory);
		}
		closedir(directory);
	} else {
		last_error = errno;
		goto plh_dynamic_read_pl_folder_return;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

plh_dynamic_read_pl_folder_return:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		pconfig = NULL;
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @@@@@@ @@@@@  @       @@@@@ @@@@@@ @@@@@          @@@@   @@@@@ @@@@@  @@@@@  @    @  @@@@
@    @ @      @    @        @        @    @         @   @      @    @        @    @    @   @    @   @    @@   @ @    @
@    @ @      @    @        @        @    @         @   @      @    @        @         @   @    @   @    @ @  @ @
@@@@@  @      @@@@@@        @@@@@    @    @         @   @@@@@@ @@@@@          @@@@     @   @@@@@    @    @ @  @ @
@      @      @    @        @        @    @         @   @      @  @               @    @   @  @     @    @  @ @ @  @@@
@      @      @    @        @        @    @         @   @      @   @              @    @   @   @    @    @   @@ @    @
@      @@@@@@ @    @        @      @@@@@  @@@@@@    @   @@@@@@ @    @        @@@@@     @   @    @ @@@@@  @    @  @@@@
                     @@@@@@                                           @@@@@@
Function: plh_filter_string
Purpose : detect un authorized characters in a string.
In      : pointer to a zero terminated string
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/06/2009    Jamel Tayeb             Creation.
*/
PL_API int plh_filter_string(char *p) {

#ifdef __PL_WINDOWS__
	DWORD last_error = PL_NO_ERROR;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int last_error = PL_NO_ERROR;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	size_t l = 0;
	int i = 0;
	int j = 0;
	static char reserved_characters[MAX_RESERVED_CHARACTERS] = { 
		RESERVED_CHARACTERS 
	};

	assert(p);

	l = strlen(p);
	assert(l);

	//-------------------------------------------------------------------------
	// search illegal character.
	//-------------------------------------------------------------------------
	for(i = 0; i < (int)l; i++) {
		for(j = 0; j < MAX_RESERVED_CHARACTERS; j++) {
			if(p[i] == reserved_characters[j]) {
				last_error = PL_INVALID_PARAMETERS;
				goto plh_filter_string_error;
			}
		}
	}

plh_filter_string_error:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @@@@@@ @@@@@  @       @@@@@ @@@@@@ @@@@@         @    @ @    @ @@@@@  @@@@@          @@@@   @@@@@ @@@@@  @@@@@  @    @  @@@@
@    @ @      @    @        @        @    @         @   @      @    @        @    @ @    @   @    @    @        @    @    @   @    @   @    @@   @ @    @
@    @ @      @    @        @        @    @         @   @      @    @        @    @ @    @   @    @    @        @         @   @    @   @    @ @  @ @
@@@@@  @      @@@@@@        @@@@@    @    @         @   @@@@@@ @@@@@         @    @ @    @   @    @    @         @@@@     @   @@@@@    @    @ @  @ @
@      @      @    @        @        @    @         @   @      @  @          @    @ @    @   @    @    @             @    @   @  @     @    @  @ @ @  @@@
@      @      @    @        @        @    @         @   @      @   @         @    @ @    @   @    @    @             @    @   @   @    @    @   @@ @    @
@      @@@@@@ @    @        @      @@@@@  @@@@@@    @   @@@@@@ @    @         @@@@   @@@@  @@@@@  @@@@@         @@@@@     @   @    @ @@@@@  @    @  @@@@
                     @@@@@@                                           @@@@@@                             @@@@@@
Function: plh_filter_uuid_string
Purpose : detect un invalid uuid string - format only.
In      : pointer to a zero terminated string
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/18/2009    Jamel Tayeb             Creation.
*/
PL_API int plh_filter_uuid_string(char *p) {

#ifdef __PL_WINDOWS__
	DWORD last_error = PL_NO_ERROR;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int last_error = PL_NO_ERROR;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	size_t l = 0;
	int i = 0;
	int j = 0;
	static char allowed_uuid_characters[MAX_ALLOWED_UUID_CHARACTERS] = { 
		ALLOWED_UUID_CHARACTERS 
	};

	assert(p);

	l = strlen(p);
	assert(l);

	//-------------------------------------------------------------------------
	// check uuid string lenght
	//-------------------------------------------------------------------------
	if(l != 36) {
		last_error = PL_INVALID_PARAMETERS;
		goto plh_filter_uuid_string_error;
	}

	//-------------------------------------------------------------------------
	// search illegal character.
	//-------------------------------------------------------------------------
	for(i = 0; i < (int)l; i++) {
		for(j = 0; j < MAX_ALLOWED_UUID_CHARACTERS; j++) {
			if(p[i] == allowed_uuid_characters[j]) {
				goto plh_filter_uuid_string_next;
			}
		}
		last_error = PL_INVALID_PARAMETERS;
		goto plh_filter_uuid_string_error;
plh_filter_uuid_string_next:
		;
	}

plh_filter_uuid_string_error:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @@@@@@ @@@@@  @       @@@@@ @@@@@@ @@@@@         @    @ @    @ @    @ @@@@@  @@@@@@ @@@@@          @@@@   @@@@@ @@@@@  @@@@@  @    @  @@@@
@    @ @      @    @        @        @    @         @   @      @    @        @@   @ @    @ @@  @@ @    @ @      @    @        @    @    @   @    @   @    @@   @ @    @
@    @ @      @    @        @        @    @         @   @      @    @        @ @  @ @    @ @ @@ @ @    @ @      @    @        @         @   @    @   @    @ @  @ @
@@@@@  @      @@@@@@        @@@@@    @    @         @   @@@@@@ @@@@@         @ @  @ @    @ @    @ @@@@@  @@@@@@ @@@@@          @@@@     @   @@@@@    @    @ @  @ @
@      @      @    @        @        @    @         @   @      @  @          @  @ @ @    @ @    @ @    @ @      @  @               @    @   @  @     @    @  @ @ @  @@@
@      @      @    @        @        @    @         @   @      @   @         @   @@ @    @ @    @ @    @ @      @   @              @    @   @   @    @    @   @@ @    @
@      @@@@@@ @    @        @      @@@@@  @@@@@@    @   @@@@@@ @    @        @    @  @@@@  @    @ @@@@@  @@@@@@ @    @        @@@@@     @   @    @ @@@@@  @    @  @@@@
                     @@@@@@                                           @@@@@@                                           @@@@@@
Function: plh_filter_number_string
Purpose : detect un invalid number string - format only.
In      : pointer to a zero terminated string
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/18/2009    Jamel Tayeb             Creation.
*/
PL_API int plh_filter_number_string(char *p) {

#ifdef __PL_WINDOWS__
	DWORD last_error = PL_NO_ERROR;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int last_error = PL_NO_ERROR;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	size_t l = 0;
	int i = 0;
	int j = 0;
	static char allowed_number_characters[MAX_ALLOWED_NUMBER_CHARACTERS] = { 
		ALLOWED_NUMBER_CHARACTERS 
	};

	assert(p);

	l = strlen(p);
	assert(l);

	//-------------------------------------------------------------------------
	// search illegal character.
	//-------------------------------------------------------------------------
	for(i = 0; i < (int)l; i++) {
		for(j = 0; j < MAX_ALLOWED_NUMBER_CHARACTERS; j++) {
			if(p[i] == allowed_number_characters[j]) {
				goto plh_filter_number_string_next;
			}
		}
		last_error = PL_INVALID_PARAMETERS;
		goto plh_filter_number_string_error;
plh_filter_number_string_next:
		;
	}

plh_filter_number_string_error:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @@@@@@ @@@@@  @       @@@@@ @@@@@@ @@@@@         @    @ @@@@@@  @@@@    @@    @@@@@ @@@@@  @    @ @@@@@@        @    @ @    @ @    @ @@@@@  @@@@@@ @@@@@          @@@@   @@@@@ @@@@@  @@@@@  @    @  @@@@
@    @ @      @    @        @        @    @         @   @      @    @        @@   @ @      @    @  @  @     @     @    @    @ @             @@   @ @    @ @@  @@ @    @ @      @    @        @    @    @   @    @   @    @@   @ @    @
@    @ @      @    @        @        @    @         @   @      @    @        @ @  @ @      @      @    @    @     @    @    @ @             @ @  @ @    @ @ @@ @ @    @ @      @    @        @         @   @    @   @    @ @  @ @
@@@@@  @      @@@@@@        @@@@@    @    @         @   @@@@@@ @@@@@         @ @  @ @@@@@@ @      @    @    @     @    @    @ @@@@@@        @ @  @ @    @ @    @ @@@@@  @@@@@@ @@@@@          @@@@     @   @@@@@    @    @ @  @ @
@      @      @    @        @        @    @         @   @      @  @          @  @ @ @      @  @@@ @@@@@@    @     @     @   @ @             @  @ @ @    @ @    @ @    @ @      @  @               @    @   @  @     @    @  @ @ @  @@@
@      @      @    @        @        @    @         @   @      @   @         @   @@ @      @    @ @    @    @     @      @ @  @             @   @@ @    @ @    @ @    @ @      @   @              @    @   @   @    @    @   @@ @    @
@      @@@@@@ @    @        @      @@@@@  @@@@@@    @   @@@@@@ @    @        @    @ @@@@@@  @@@@  @    @    @   @@@@@     @   @@@@@@        @    @  @@@@  @    @ @@@@@  @@@@@@ @    @        @@@@@     @   @    @ @@@@@  @    @  @@@@
                     @@@@@@                                           @@@@@@                                                         @@@@@@                                           @@@@@@
Function: plh_filter_negative_number_string
Purpose : detect an invalid negative (or not) number string - format only.
In      : pointer to a zero terminated string
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/18/2009    Jamel Tayeb             Creation.
*/
PL_API int plh_filter_negative_number_string(char *p) {

#ifdef __PL_WINDOWS__
	DWORD last_error = PL_NO_ERROR;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int last_error = PL_NO_ERROR;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	size_t l = 0;
	int i = 0;
	int j = 0;
	static char allowed_negative_number_characters[
		MAX_ALLOWED_NEGATIVE_NUMBER_CHARACTERS
	] = { ALLOWED_NEGATIVE_NUMBER_CHARACTERS };

	assert(p);

	l = strlen(p);
	assert(l);

	//-------------------------------------------------------------------------
	// search illegal character.
	//-------------------------------------------------------------------------
	for(i = 0; i < (int)l; i++) {
		for(j = 0; j < MAX_ALLOWED_NEGATIVE_NUMBER_CHARACTERS; j++) {
			if(p[i] == allowed_negative_number_characters[j]) {
				goto plh_filter_negative_number_string_next;
			}
		}
		last_error = PL_INVALID_PARAMETERS;
		goto plh_filter_negative_number_string_error;
plh_filter_negative_number_string_next:
		;
	}

plh_filter_negative_number_string_error:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @        @    @ @@@@@  @@@@@  @@@@@@ @@@@@          @@@@   @@@@@ @@@@@  @@@@@  @    @  @@@@
@    @ @      @    @        @    @ @    @ @    @ @      @    @        @    @    @   @    @   @    @@   @ @    @
@    @ @      @    @        @    @ @    @ @    @ @      @    @        @         @   @    @   @    @ @  @ @
@@@@@  @      @@@@@@        @    @ @@@@@  @@@@@  @@@@@@ @@@@@          @@@@     @   @@@@@    @    @ @  @ @
@      @      @    @        @    @ @      @      @      @  @               @    @   @  @     @    @  @ @ @  @@@
@      @      @    @        @    @ @      @      @      @   @              @    @   @   @    @    @   @@ @    @
@      @@@@@@ @    @         @@@@  @      @      @@@@@@ @    @        @@@@@     @   @    @ @@@@@  @    @  @@@@
                     @@@@@@                                    @@@@@@
Function: plh_upper_string
Purpose : convert a string into upper case.
In      : pointer to a zero terminated string
Out     : Status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/06/2009    Jamel Tayeb             Creation.
*/
PL_API int plh_upper_string(char *p) {
	
	int i = 0;
	size_t l = 0;
	char c = '\0';

	assert(p);

	l = strlen(p);
	assert(l);

	for(i = 0; i < (int)l; i++) {
		c = *p;
		*p++ = (char)toupper(c);
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
@@@@@  @@@@@  @@@@@  @    @  @@@@@        @    @ @@@@@@ @@@@@   @@@@  @@@@@   @@@@  @    @
@    @ @    @   @    @@   @    @          @    @ @      @    @ @    @   @    @    @ @@   @
@    @ @    @   @    @ @  @    @          @    @ @      @    @ @        @    @    @ @ @  @
@@@@@  @@@@@    @    @ @  @    @          @    @ @@@@@@ @@@@@   @@@@    @    @    @ @ @  @
@      @  @     @    @  @ @    @           @   @ @      @  @        @   @    @    @ @  @ @
@      @   @    @    @   @@    @            @ @  @      @   @       @   @    @    @ @   @@
@      @    @ @@@@@  @    @    @             @   @@@@@@ @    @ @@@@@  @@@@@   @@@@  @    @
                                   @@@@@@
Function: print_version
Purpose : print version and PL used versions to stdout end exit
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/29/2009    Jamel Tayeb             Creation.
*/
PL_API void print_version_info(
	const char *name, 
	const char *VERSION_MAJOR, 
	const char *VERSION_MINOR, 
	const char *VERSION_REVISION
) {
	fprintf(
		stdout, 
		"\n%s: version %s.%s.%s\n", 
		name, 
		VERSION_MAJOR, 
		VERSION_MINOR, 
		VERSION_REVISION
	);
	fprintf(
		stdout, 
		"using PL helper version %s.%s.%s\n", 
		PL_HELPER_VERSION_MAJOR, 
		PL_HELPER_VERSION_MINOR, 
		PL_HELPER_VERSION_REVISION
	);
	fprintf(
		stdout, 
		"using PL version %s.%s.%s(%s)\n", 
		PL_VERSION_MAJOR, 
		PL_VERSION_MINOR, 
		PL_VERSION_REVISION, 
		PL_VERSION_OS
	);
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	fprintf(stdout, "\n");
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
@@@@@  @      @    @         @@@@  @@@@@@  @@@@@         @  @   @@@@  @    @ @    @  @@@@         @@@@@  @             @@@@@   @  @           @@   @@@@@  @@@@@  @      @@@@@   @@@@    @@    @@@@@ @@@@@   @@@@  @    @        @    @   @@   @    @ @@@@@@
@    @ @      @    @        @    @ @         @           @  @  @    @ @    @ @@   @ @    @        @    @ @             @    @  @  @          @  @  @    @ @    @ @        @    @    @  @  @     @     @    @    @ @@   @        @@   @  @  @  @@  @@ @
@    @ @      @    @        @      @         @           @  @  @    @ @    @ @ @  @ @             @    @ @             @    @  @  @         @    @ @    @ @    @ @        @    @      @    @    @     @    @    @ @ @  @        @ @  @ @    @ @ @@ @ @
@@@@@  @      @@@@@@        @      @@@@@@    @            @    @    @ @    @ @ @  @ @             @@@@@  @             @@@@@    @           @    @ @@@@@  @@@@@  @        @    @      @    @    @     @    @    @ @ @  @        @ @  @ @    @ @    @ @@@@@@
@      @      @    @        @  @@@ @         @            @    @    @ @    @ @  @ @ @  @@@        @      @             @    @   @           @@@@@@ @      @      @        @    @      @@@@@@    @     @    @    @ @  @ @        @  @ @ @@@@@@ @    @ @
@      @      @    @        @    @ @         @            @    @    @ @    @ @   @@ @    @        @      @             @    @   @           @    @ @      @      @        @    @    @ @    @    @     @    @    @ @   @@        @   @@ @    @ @    @ @
@      @@@@@@ @    @         @@@@  @@@@@@    @            @     @@@@   @@@@  @    @  @@@@         @      @@@@@@        @@@@@    @           @    @ @      @      @@@@@@ @@@@@   @@@@  @    @    @   @@@@@   @@@@  @    @        @    @ @    @ @    @ @@@@@@
                     @@@@@@                      @@@@@@                                    @@@@@@               @@@@@@               @@@@@@                                                                              @@@@@@
Function: plh_get_young_pl_by_application_name
Purpose : return in the passed buffer the latest - as per file system date - PL for 
          the application name provided as first argument.
In      : pointer to a string containing the application name to search and 
          a pointer to a pointer to a string - buffer - to receive the result
          buffer MUST BE PL_MAX_PATH length (all strings are ASCII nul terminated) 
Out     : modified buffer
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/29/2009    Jamel Tayeb             Creation.
*/
PL_API int plh_get_young_pl_by_application_name(char *a, char *p) {

	int ret = PL_FAILURE;
	unsigned int i = 0;
	int young_index = -1;
	PLH_CHAR young_buffer[PL_MAX_PATH] = { '\0' };
	PLH_PL_FOLDER_INFO config;
	PLH_CHAR pl_buffer[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
	DWORD last_error = PL_NO_ERROR;
	HANDLE pl_config_file = NULL;
	FILETIME young_file_creation_time;
	FILETIME pl_config_file_creation_time;
	FILETIME pl_config_file_last_access_time;
	FILETIME pl_config_file_last_write_time;
	PLH_CHAR application[PL_MAX_PATH] = { '\0' };
	size_t st_ret = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int last_error = PL_NO_ERROR;
	struct stat pl_config_file_stat;
	time_t young_file_creation_time = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(a != NULL);
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// collect PL data.
	//-------------------------------------------------------------------------
	memset(
		&config, 
		0, 
		sizeof(config)
	);
	ret = plh_read_pl_folder(&config);
	if(
		(ret != PL_SUCCESS) ||
		(config.max_uuids == 0)
	) {
		last_error = PL_FAILURE;
		goto plh_get_young_pl_by_application_name_return;
	}

#ifdef __PL_WINDOWS__
	memset(
		application, 
		0, 
		sizeof(application)
	);
	mbstowcs_s(
		&st_ret, 
		application, 
		sizeof(application) / 2, 
		a, 
		strlen(a)
	);
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// search PLs related to application.
	//-------------------------------------------------------------------------
	for(i = 0; i < config.max_uuids; i++) {
#ifdef __PL_WINDOWS__
		if(_tcsncmp(
			config.application_names[i], 
			application, 
			max(
				_tcslen(config.application_names[i]), 
				_tcslen(application)
			)
		) == 0) { 
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		if(strncmp(
			a, 
			config.application_names[i], 
			strlen(a)
		) == 0) {
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			//-----------------------------------------------------------------
			// build the PL config file
			//-----------------------------------------------------------------
			memset(
				pl_buffer, 
				0, 
				sizeof(pl_buffer)
			);
#ifdef __PL_WINDOWS__
			_tcsncpy_s(
				pl_buffer, 
				PL_MAX_PATH, 
				PL_FOLDER, 
				_TRUNCATE
			);
			_tcsncat_s(
				pl_buffer, 
				PL_MAX_PATH, 
				PL_PATH_SEPARATOR, 
				_TRUNCATE
			);
			_tcsncat_s(
				pl_buffer, 
				PL_MAX_PATH, 
				config.full_uuids[i], 
				_TRUNCATE
			);
			_tcsncat_s(
				pl_buffer, 
				PL_MAX_PATH, 
				PL_PATH_SEPARATOR, 
				_TRUNCATE
			);
			_tcsncat_s(
				pl_buffer, 
				PL_MAX_PATH, 
				PL_CONFIG_FILE_NAME,
				_TRUNCATE
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			strncpy(
				pl_buffer, 
				PL_FOLDER, 
				strlen(PL_FOLDER)
			);
			strncat(
				pl_buffer, 
				PL_PATH_SEPARATOR, 
				strlen(PL_PATH_SEPARATOR)
			);
			strncat(
				pl_buffer, 
				config.full_uuids[i], 
				strlen(config.full_uuids[i])
			);
			strncat(
				pl_buffer, 
				PL_PATH_SEPARATOR, 
				strlen(PL_PATH_SEPARATOR)
			);
			strncat(
				pl_buffer, 
				PL_CONFIG_FILE_NAME, 
				strlen(PL_CONFIG_FILE_NAME)
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			//--------------------------------------------------------------
			// get the date from file system.
			//--------------------------------------------------------------
#ifdef __PL_WINDOWS__
			pl_config_file = CreateFile(
				pl_buffer, 
				GENERIC_READ, 
				FILE_SHARE_READ, 
				NULL, 
				OPEN_EXISTING, 
				FILE_ATTRIBUTE_NORMAL, 
				SECURITY_ANONYMOUS
			);
			if(pl_config_file == INVALID_HANDLE_VALUE) {
				last_error = PL_CONFIG_FILE_OPENING_FAILED;
				goto plh_get_young_pl_by_application_name_return;
			}
			bret = GetFileTime(
				pl_config_file, 
				&pl_config_file_creation_time, 
				&pl_config_file_last_access_time, 
				&pl_config_file_last_write_time
			);
			CloseHandle(pl_config_file);
			if(bret == FALSE) {
				last_error = PL_FAILURE;
				goto plh_get_young_pl_by_application_name_return;
			};
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			ret = stat(
				pl_buffer, 
				&pl_config_file_stat
			);
			if(ret == -1) {
				last_error = PL_FAILURE;
				goto plh_get_young_pl_by_application_name_return;
			}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			//--------------------------------------------------------------
			// update young index if required.
			//--------------------------------------------------------------
#ifdef __PL_WINDOWS__
			if(
				(young_index == -1) ||
				(CompareFileTime(
					&pl_config_file_creation_time, 
					&young_file_creation_time
				) == -1)
			) {
				young_index = i;
				young_file_creation_time.dwHighDateTime = 
					pl_config_file_creation_time.dwHighDateTime;
				young_file_creation_time.dwLowDateTime = 
					pl_config_file_creation_time.dwLowDateTime;
				memset(
					young_buffer, 
					0, 
					sizeof(young_buffer)
				);
				_tcsncpy_s(
					young_buffer, 
					PL_MAX_PATH, 
					pl_buffer, 
					_TRUNCATE
				);
			}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			if(
				(young_index == -1) ||
				(difftime(
					young_file_creation_time, 
					pl_config_file_stat.st_mtime
				) < 0)
			) {
				young_index = i;
				memcpy(
					&young_file_creation_time, 
					&pl_config_file_stat.st_mtime, 
					sizeof(time_t)
				);
				memset(
					young_buffer, 
					0, 
					sizeof(young_buffer)
				);
				strncpy(
					young_buffer, 
					pl_buffer, 
					strlen(pl_buffer)
				);
			}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		} // if app name found
	} // for i

	//-------------------------------------------------------------------------
	// return young PL config file name in buffer.
	//-------------------------------------------------------------------------
	memset(
		p, 
		0, 
		PL_MAX_PATH
	);
#ifdef __PL_WINDOWS__
	wcstombs_s(
		&st_ret, 
		p, 
		PL_MAX_PATH, 
		young_buffer, 
		_TRUNCATE
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	strncpy(
		p, 
		young_buffer, 
		strlen(young_buffer)
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

plh_get_young_pl_by_application_name_return:

	//-------------------------------------------------------------------------
	// return status.
	//-------------------------------------------------------------------------
	if(last_error != PL_NO_ERROR) {
		return(PL_FAILURE);
	}
	return(PL_SUCCESS);
}
