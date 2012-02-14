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
// headers inclusions
//-----------------------------------------------------------------------------
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include "productivity_link.h"
#include "productivity_link_helper.h"
#include "unit_tests.h"
#include "unit_tests_tools.h"
#include "unit_tests_framework.h"
#ifdef __PL_WINDOWS__
	#include <tchar.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// pl table pointer
//-----------------------------------------------------------------------------
extern PPL_TABLE ppl_table;
#ifdef __PL_WINDOWS__
	extern BOOL pl_table_initialized;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	extern int pl_table_initialized;
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

/*-----------------------------------------------------------------------------
Function: plt_tools_set_pl_table_state
Purpose : set pl table state
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
extern void plt_tools_set_pl_table_state(BOOL s) {
	assert(
		(s == TRUE) || 
		(s == FALSE)
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
extern void plt_tools_set_pl_table_state(int s) {
	assert(
		(s == 1) || 
		(s == 0)
	);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	pl_table_initialized = s;
}

/*-----------------------------------------------------------------------------
Function: plt_tools_get_pl_table_state
Purpose : get pl table as uninitialized
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
extern BOOL plt_tools_get_pl_table_state(void) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
extern int plt_tools_get_pl_table_state(void) {
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	return(pl_table_initialized);
}

/*-----------------------------------------------------------------------------
Function: plt_tools_get_pl_counter_name
Purpose : return in the provided buffer the name of counter index
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_tools_get_pl_counter_name(unsigned int index, char *buffer) {

	PLH_CONFIG_INFO pl_info;
	PLH_PL_FOLDER_INFO pl_folder_info;
	PL_STATUS ret = PL_FAILURE;
	int position = -1;
	unsigned int i = 0;
	char pl_config[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	char temp[PL_MAX_PATH] = { '\0' };
#endif // __PL_WINDOWS__

	assert(buffer != 0);
	assert(index >= 0);
	assert(index < PL_MAX_COUNTERS_PER_LINK);

	//-------------------------------------------------------------------------
	// get PL_FOLDER content and infos
	//-------------------------------------------------------------------------
	ret = plh_read_pl_folder(&pl_folder_info);
	assert(ret == PL_SUCCESS);

	//----------------------------------------------------------------------
	// search the PL_UNIT_TESTS_APPLICATION_NAME PL (defined in unit_tests..
	// _framework.h)
	//----------------------------------------------------------------------
	for(i = 0; i < pl_folder_info.max_uuids; i++) {
#ifdef __PL_WINDOWS__
		if(
			_tcsncmp(
				&pl_folder_info.application_names[i][0], 
				PL_UNIT_TESTS_APPLICATION_TNAME, 
				_tcslen(PL_UNIT_TESTS_APPLICATION_TNAME)
			) == 0
		) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		if(
			strncmp(
				&pl_folder_info.application_names[i][0], 
				PL_UNIT_TESTS_APPLICATION_NAME, 
				strlen(PL_UNIT_TESTS_APPLICATION_NAME)
			) == 0
		) {
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			position = (int)i;
		}
	}
	assert(position != -1);

	//-------------------------------------------------------------------------
	// build pl_config.ini and get infos
	//-------------------------------------------------------------------------
#ifdef __PL_UNDEF_T__
	#undef _T
	#define _T(x) (x)
#endif // __PL_UNDEF_T__
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	strncpy(
		pl_config, 
		PL_FOLDER, 
		strlen(PL_FOLDER)
	);
	strncat(
		pl_config, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
#ifdef __PL_WINDOWS__
	memset(
		temp, 
		0, 
		sizeof(temp)
	);
	wcstombs(
		temp, 
		pl_folder_info.full_uuids[position], 
		PL_MAX_PATH
	);
	strncat(
		pl_config, 
		temp, 
		strlen(temp)
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	strncat(
		pl_config, 
		pl_folder_info.full_uuids[position], 
		strlen(pl_folder_info.full_uuids[position])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	strncat(
		pl_config, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		pl_config, 
		PL_CONFIG_FILE_NAME, 
		strlen(PL_CONFIG_FILE_NAME)
	);
#ifdef __PL_UNDEF_T__
	#undef _T
	#define _T(x) __T(x)
#endif // __PL_UNDEF_T__
	ret = plh_read_pl_config_ini_file(
		pl_config, 
		&pl_info
	);

	assert(ret == PL_SUCCESS);
	assert(index < pl_info.max_counters);

	//-------------------------------------------------------------------------
	// return the counter name
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE
	);
#ifdef __PL_WINDOWS__
	memset(
		temp, 
		0, 
		sizeof(temp)
	);
	wcstombs(
		temp, 
		pl_info.counter_names[index], 
		PL_MAX_PATH
	);
	strncpy(
		buffer, 
		temp, 
		strlen(temp)
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	strncpy(
		buffer, 
		pl_info.counter_names[index], 
		strlen(pl_info.counter_names[index])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
Function: plt_tools_get_pl_application_name
Purpose : return in the provided buffer the application name
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_tools_get_pl_application_name(char *buffer) {

	PLH_PL_FOLDER_INFO pl_folder_info;
	PL_STATUS ret = PL_FAILURE;

	assert(buffer != 0);

	//-------------------------------------------------------------------------
	// assume PL_FOLDER was deleted and re-created before a call to this
	// function.  Therefore, the first PL is the one of interest
	// get PL_FOLDER content and infos
	//-------------------------------------------------------------------------
	ret = plh_read_pl_folder(&pl_folder_info);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// return the application name
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE
	);
#ifdef __PL_WINDOWS__
	wcstombs(
		buffer, 
		pl_folder_info.application_names[0], 
		PL_MAX_PATH
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	strncpy(
		buffer, 
		pl_folder_info.application_names[0], 
		PL_MAX_PATH
	);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
Function: plt_tools_get_pl_config_full_file_name
Purpose : return in the provided buffer the pl_config.ini full file name
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_tools_get_pl_config_full_file_name(char *buffer) {

	PLH_PL_FOLDER_INFO pl_folder_info;
	PL_STATUS ret = PL_FAILURE;
	char pl_config[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	char temp[PL_MAX_PATH] = { '\0' };
#endif // __PL_WINDOWS__

	assert(buffer != 0);

	//-------------------------------------------------------------------------
	// assume PL_FOLDER was deleted and re-created before a call to this
	// function.  Therefore, the first PL is the one of interest
	// get PL_FOLDER content and infos
	//-------------------------------------------------------------------------
	ret = plh_read_pl_folder(&pl_folder_info);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// build pl_config.ini and get infos
	//-------------------------------------------------------------------------
#ifdef __PL_UNDEF_T__
	#undef _T
	#define _T(x) (x)
#endif // __PL_UNDEF_T__
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	strncpy(
		pl_config, 
		PL_FOLDER, 
		strlen(PL_FOLDER)
	);
	strncat(
		pl_config, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
#ifdef __PL_WINDOWS__
	memset(
		temp, 
		0, 
		sizeof(buffer)
	);
	wcstombs(
		temp, 
		pl_folder_info.full_uuids[0], 
		PL_MAX_PATH
	);
	strncat(
		pl_config, 
		temp, 
		strlen(temp)
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	strncat(
		pl_config, 
		pl_folder_info.full_uuids[0], 
		strlen(pl_folder_info.full_uuids[0])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	strncat(
		pl_config, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		pl_config, 
		PL_CONFIG_FILE_NAME, 
		strlen(PL_CONFIG_FILE_NAME)
	);
#ifdef __PL_UNDEF_T__
	#undef _T
	#define _T(x) __T(x)
#endif // __PL_UNDEF_T__

	//-------------------------------------------------------------------------
	// return the counter name
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE
	);
	strncpy(
		buffer, 
		pl_config, 
		strlen(pl_config)
	);
}

/*-----------------------------------------------------------------------------
Function: plt_tools_get_pl_counter_counts
Purpose : return the first PL's number of counters
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/extern unsigned int plt_tools_get_pl_counter_counts(void) {

	PLH_CONFIG_INFO pl_info;
	PLH_PL_FOLDER_INFO pl_folder_info;
	PL_STATUS ret = PL_FAILURE;
	int position = 0;
	char pl_config[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	char temp[PL_MAX_PATH] = { '\0' };
	char buffer[PL_MAX_PATH] = { '\0' };
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// get PL_FOLDER content and infos
	//-------------------------------------------------------------------------
	ret = plh_read_pl_folder(&pl_folder_info);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// build pl_config.ini and get infos
	//-------------------------------------------------------------------------
#ifdef __PL_UNDEF_T__
	#undef _T
	#define _T(x) (x)
#endif // __PL_UNDEF_T__
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	strncpy(
		pl_config, 
		PL_FOLDER, 
		strlen(PL_FOLDER)
	);
	strncat(
		pl_config, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
#ifdef __PL_WINDOWS__
	memset(
		temp, 
		0, 
		sizeof(buffer)
	);
	wcstombs(
		temp, 
		pl_folder_info.full_uuids[position], 
		PL_MAX_PATH
	);
	strncat(
		pl_config, 
		temp, 
		strlen(temp)
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	strncat(
		pl_config, 
		pl_folder_info.full_uuids[position], 
		strlen(pl_folder_info.full_uuids[position])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	strncat(
		pl_config, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		pl_config, 
		PL_CONFIG_FILE_NAME, 
		strlen(PL_CONFIG_FILE_NAME)
	);
#ifdef __PL_UNDEF_T__
	#undef _T
	#define _T(x) __T(x)
#endif // __PL_UNDEF_T__
	ret = plh_read_pl_config_ini_file(
		pl_config, 
		&pl_info
	);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// return the counters count
	//-------------------------------------------------------------------------
	return(pl_info.max_counters);
}

/*-----------------------------------------------------------------------------
Function: plt_tools_get_pl_counter_value
Purpose : return in index counter value
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
unsigned long long plt_tools_get_pl_counter_value(unsigned int index) {

	PLH_PL_FOLDER_INFO pl_folder_info;
	PL_STATUS ret = PL_FAILURE;
	int position = 0;
	char buffer[PL_MAX_BUFFER_SIZE] = { '\0' };
	char *pl_offending_char = NULL;
	unsigned long long value = 0;
#ifdef __PL_WINDOWS__
	TCHAR *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_TNAMES
	;
	HANDLE hf = NULL;
	TCHAR counter_file_name[PL_MAX_PATH] = { _T('\0') };
	BOOL b_ret = FALSE;
	errno_t et_ret = 0;
	DWORD bytes_read = 0;
	DWORD bytes_to_read = (DWORD)sizeof(buffer);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char counter_file_name[PL_MAX_PATH] = { '\0' };
	int hf = -1;
	size_t bytes_read = 0;
	size_t bytes_to_read = sizeof(buffer);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(index >= 0);
	assert(index < PL_MAX_COUNTERS_PER_LINK);

	//-------------------------------------------------------------------------
	// get PL_FOLDER content and infos
	//-------------------------------------------------------------------------
	ret = plh_read_pl_folder(&pl_folder_info);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// build counter file name
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	memset(
		counter_file_name, 
		0, 
		sizeof(counter_file_name)
	);
	_tcsncpy(
		counter_file_name, 
		PL_FOLDER, 
		_tcslen(PL_FOLDER)
	);
	_tcsncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		_tcslen(PL_PATH_SEPARATOR)
	);
	_tcsncat(
		counter_file_name, 
		pl_folder_info.full_uuids[position], 
		_tcslen(pl_folder_info.full_uuids[position])
	);
	_tcsncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		_tcslen(PL_PATH_SEPARATOR)
	);
	_tcsncat(
		counter_file_name, 
		counters[index], 
		_tcslen(counters[index])
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	memset(
		counter_file_name, 
		0, 
		sizeof(counter_file_name)
	);
	strncpy(
		counter_file_name, 
		PL_FOLDER, 
		strlen(PL_FOLDER)
	);
	strncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		counter_file_name, 
		pl_folder_info.full_uuids[position], 
		strlen(pl_folder_info.full_uuids[position])
	);
	strncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		counter_file_name, 
		counters[index], 
		strlen(counters[index])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// open counter file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	hf = CreateFile(
		counter_file_name, 
		GENERIC_READ, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		SECURITY_ANONYMOUS
	);
	assert(hf != INVALID_HANDLE_VALUE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	hf = open(
		counter_file_name, 
		O_RDONLY
	);
	assert(hf != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// read counter data string
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
#ifdef __PL_WINDOWS__
	b_ret = ReadFile(
		hf, 
		buffer, 
		bytes_to_read, 
		&bytes_read, 
		NULL
	);
	assert(b_ret != FALSE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	bytes_read = read(
		hf, 
		buffer, 
		bytes_to_read
	);
	assert(bytes_read != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// convert counter data string into counter value
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	value = _strtoui64(
		buffer, 
		&pl_offending_char, 
		PL_COUNTER_BASE
	);
	//assert(errno != ERANGE);
	assert(
		(pl_offending_char != NULL) && 
		(*pl_offending_char == '\0')
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	value = strtoull(
		buffer, 
		&pl_offending_char, 
		PL_COUNTER_BASE
	);
	//assert(errno != ERANGE);
	assert(
		(pl_offending_char != NULL) && 
		(*pl_offending_char == '\0')
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// close counter file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	b_ret = CloseHandle(hf);
	assert(b_ret != 0);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	ret = close(hf);
	assert(ret != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// return counter value
	//-------------------------------------------------------------------------
	return(value);
}

/*-----------------------------------------------------------------------------
Function: plt_tools_set_pl_counter_value
Purpose : set index counter value (not using pl_write)
          NOTE: the values are predefined per index.
		  See unit_tests_framework.h for definitions.
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_tools_set_pl_counter_value(unsigned int index) {

	PLH_PL_FOLDER_INFO pl_folder_info;
	PL_STATUS ret = PL_FAILURE;
	int position = 0;
	char buffer[PL_MAX_BUFFER_SIZE] = { '\0' };
	unsigned long long values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;
#ifdef __PL_WINDOWS__
	TCHAR *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_TNAMES
	;
	HANDLE hf = NULL;
	TCHAR counter_file_name[PL_MAX_PATH] = { _T('\0') };
	BOOL b_ret = FALSE;
	errno_t et_ret = 0;
	DWORD bytes_written = 0;
	DWORD bytes_to_write = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char counter_file_name[PL_MAX_PATH] = { '\0' };
	int hf = -1;
	size_t bytes_written = 0;
	size_t bytes_to_write = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(index >= 0);
	assert(index < PL_MAX_COUNTERS_PER_LINK);
	assert(index < PL_UNIT_TESTS_COUNTERS_COUNT);

	//-------------------------------------------------------------------------
	// get PL_FOLDER content and infos
	//-------------------------------------------------------------------------
	ret = plh_read_pl_folder(&pl_folder_info);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// build counter file name
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	memset(
		counter_file_name, 
		0, 
		sizeof(counter_file_name)
	);
	_tcsncpy(
		counter_file_name, 
		PL_FOLDER, 
		_tcslen(PL_FOLDER)
	);
	_tcsncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		_tcslen(PL_PATH_SEPARATOR)
	);
	_tcsncat(
		counter_file_name, 
		pl_folder_info.full_uuids[position], 
		_tcslen(pl_folder_info.full_uuids[position])
	);
	_tcsncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		_tcslen(PL_PATH_SEPARATOR)
	);
	_tcsncat(
		counter_file_name, 
		counters[index], 
		_tcslen(counters[index])
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	memset(
		counter_file_name, 
		0, 
		sizeof(counter_file_name)
	);
	strncpy(
		counter_file_name, 
		PL_FOLDER, 
		strlen(PL_FOLDER)
	);
	strncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		counter_file_name, 
		pl_folder_info.full_uuids[position], 
		strlen(pl_folder_info.full_uuids[position])
	);
	strncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		counter_file_name, 
		counters[index], 
		strlen(counters[index])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// open counter file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	hf = CreateFile(
		counter_file_name, 
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		SECURITY_ANONYMOUS
	);
	assert(hf != INVALID_HANDLE_VALUE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	hf = open(
		counter_file_name, 
		O_RDWR
	);
	assert(hf != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// convert value data into string.
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
#ifdef __PL_WINDOWS__
	et_ret = _ui64toa_s(
		values[index], 
		buffer, 
		PL_MAX_BUFFER_SIZE, 
		PL_COUNTER_BASE
	);
	assert(et_ret == 0);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	ret = sprintf(
		buffer, 
		"%llu", 
		values[index]
	);
	assert(ret >= 0);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// write value ASCII string into file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	bytes_to_write = (DWORD)strlen(buffer);
	buffer[bytes_to_write + 1] = PL_EOF;
	bytes_to_write += 2;
	b_ret = WriteFile(
		hf, 
		buffer, 
		bytes_to_write, 
		&bytes_written, 
		NULL
	);
	assert (b_ret != FALSE);
	assert(bytes_to_write == bytes_written);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	bytes_to_write = strlen(buffer);
	buffer[bytes_to_write + 1] = PL_EOF;
	bytes_to_write += 2;
	bytes_written = write(
		hf, 
		buffer, 
		bytes_to_write
	);
	assert (bytes_written != -1);
	assert(bytes_to_write == bytes_written);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// close counter file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	b_ret = CloseHandle(hf);
	assert(b_ret != 0);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	ret = close(hf);
	assert(ret != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
Function: plt_tools_set_pl_corrupt_counter_file_value
Purpose : set index counter file value to corrupt data (not using pl_write)
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_tools_set_pl_corrupt_counter_file_value(unsigned int index) {

	PLH_PL_FOLDER_INFO pl_folder_info;
	PL_STATUS ret = PL_FAILURE;
	int position = 0;
	char buffer[PL_MAX_BUFFER_SIZE] = { '\0' };
#ifdef __PL_WINDOWS__
	TCHAR *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_TNAMES
	;
	HANDLE hf = NULL;
	TCHAR counter_file_name[PL_MAX_PATH] = { _T('\0') };
	BOOL b_ret = FALSE;
	errno_t et_ret = 0;
	DWORD bytes_written = 0;
	DWORD bytes_to_write = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char counter_file_name[PL_MAX_PATH] = { '\0' };
	int hf = -1;
	size_t bytes_written = 0;
	size_t bytes_to_write = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(index >= 0);
	assert(index < PL_MAX_COUNTERS_PER_LINK);
	assert(index < PL_UNIT_TESTS_COUNTERS_COUNT);

	//-------------------------------------------------------------------------
	// get PL_FOLDER content and infos
	//-------------------------------------------------------------------------
	ret = plh_read_pl_folder(&pl_folder_info);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// build counter file name
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	memset(
		counter_file_name, 
		0, 
		sizeof(counter_file_name)
	);
	_tcsncpy(
		counter_file_name, 
		PL_FOLDER, 
		_tcslen(PL_FOLDER)
	);
	_tcsncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		_tcslen(PL_PATH_SEPARATOR)
	);
	_tcsncat(
		counter_file_name, 
		pl_folder_info.full_uuids[position], 
		_tcslen(pl_folder_info.full_uuids[position])
	);
	_tcsncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		_tcslen(PL_PATH_SEPARATOR)
	);
	_tcsncat(
		counter_file_name, 
		counters[index], 
		_tcslen(counters[index])
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	memset(
		counter_file_name, 
		0, 
		sizeof(counter_file_name)
	);
	strncpy(
		counter_file_name, 
		PL_FOLDER, 
		strlen(PL_FOLDER)
	);
	strncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		counter_file_name, 
		pl_folder_info.full_uuids[position], 
		strlen(pl_folder_info.full_uuids[position])
	);
	strncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		counter_file_name, 
		counters[index], 
		strlen(counters[index])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// open counter file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	hf = CreateFile(
		counter_file_name, 
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		SECURITY_ANONYMOUS
	);
	assert(hf != INVALID_HANDLE_VALUE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	hf = open(
		counter_file_name, 
		O_RDWR
	);
	assert(hf != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// prepare corrupt data.
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
	strncpy(
		buffer, 
		PL_UNIT_TESTS_COUNTER_CORRUPT_TEST_ASCII_VALUES, 
		strlen(PL_UNIT_TESTS_COUNTER_CORRUPT_TEST_ASCII_VALUES)
	);

	//-------------------------------------------------------------------------
	// write value ASCII string into file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	bytes_to_write = (DWORD)strlen(buffer);
	buffer[bytes_to_write + 1] = PL_EOF;
	bytes_to_write += 2;
	b_ret = WriteFile(
		hf, 
		buffer, 
		bytes_to_write, 
		&bytes_written, 
		NULL
	);
	assert (b_ret != FALSE);
	assert(bytes_to_write == bytes_written);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	bytes_to_write = strlen(buffer);
	buffer[bytes_to_write + 1] = PL_EOF;
	bytes_to_write += 2;
	bytes_written = write(
		hf, 
		buffer, 
		bytes_to_write
	);
	assert (bytes_written != -1);
	assert(bytes_to_write == bytes_written);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// close counter file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	b_ret = CloseHandle(hf);
	assert(b_ret != 0);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	ret = close(hf);
	assert(ret != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
Function: plt_tools_set_pl_overflow_counter_value
Purpose : set index counter value to overflow data (not using pl_write)
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_tools_set_pl_overflow_counter_value(unsigned int index) {

	PLH_PL_FOLDER_INFO pl_folder_info;
	PL_STATUS ret = PL_FAILURE;
	int position = 0;
	char buffer[PL_MAX_BUFFER_SIZE] = { '\0' };
#ifdef __PL_WINDOWS__
	TCHAR *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_TNAMES
	;
	HANDLE hf = NULL;
	TCHAR counter_file_name[PL_MAX_PATH] = { _T('\0') };
	BOOL b_ret = FALSE;
	errno_t et_ret = 0;
	DWORD bytes_written = 0;
	DWORD bytes_to_write = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char counter_file_name[PL_MAX_PATH] = { '\0' };
	int hf = -1;
	size_t bytes_written = 0;
	size_t bytes_to_write = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(index >= 0);
	assert(index < PL_MAX_COUNTERS_PER_LINK);
	assert(index < PL_UNIT_TESTS_COUNTERS_COUNT);

	//-------------------------------------------------------------------------
	// get PL_FOLDER content and infos
	//-------------------------------------------------------------------------
	ret = plh_read_pl_folder(&pl_folder_info);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// build counter file name
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	memset(
		counter_file_name, 
		0, 
		sizeof(counter_file_name)
	);
	_tcsncpy(
		counter_file_name, 
		PL_FOLDER, 
		_tcslen(PL_FOLDER)
	);
	_tcsncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		_tcslen(PL_PATH_SEPARATOR)
	);
	_tcsncat(
		counter_file_name, 
		pl_folder_info.full_uuids[position], 
		_tcslen(pl_folder_info.full_uuids[position])
	);
	_tcsncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		_tcslen(PL_PATH_SEPARATOR)
	);
	_tcsncat(
		counter_file_name, 
		counters[index], 
		_tcslen(counters[index])
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	memset(
		counter_file_name, 
		0, 
		sizeof(counter_file_name)
	);
	strncpy(
		counter_file_name, 
		PL_FOLDER, 
		strlen(PL_FOLDER)
	);
	strncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		counter_file_name, 
		pl_folder_info.full_uuids[position], 
		strlen(pl_folder_info.full_uuids[position])
	);
	strncat(
		counter_file_name, 
		PL_PATH_SEPARATOR, 
		strlen(PL_PATH_SEPARATOR)
	);
	strncat(
		counter_file_name, 
		counters[index], 
		strlen(counters[index])
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// open counter file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	hf = CreateFile(
		counter_file_name, 
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		SECURITY_ANONYMOUS
	);
	assert(hf != INVALID_HANDLE_VALUE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	hf = open(
		counter_file_name, 
		O_RDWR
	);
	assert(hf != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// prepare corrupt data.
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
	strncpy(
		buffer, 
		PL_UNIT_TESTS_COUNTER_OVERFLOW_TEST_ASCII_VALUES, 
		strlen(PL_UNIT_TESTS_COUNTER_OVERFLOW_TEST_ASCII_VALUES)
	);

	//-------------------------------------------------------------------------
	// write value ASCII string into file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	bytes_to_write = (DWORD)strlen(buffer);
	buffer[bytes_to_write + 1] = PL_EOF;
	bytes_to_write += 2;
	b_ret = WriteFile(
		hf, 
		buffer, 
		bytes_to_write, 
		&bytes_written, 
		NULL
	);
	assert (b_ret != FALSE);
	assert(bytes_to_write == bytes_written);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	bytes_to_write = strlen(buffer);
	buffer[bytes_to_write + 1] = PL_EOF;
	bytes_to_write += 2;
	bytes_written = write(
		hf, 
		buffer, 
		bytes_to_write
	);
	assert (bytes_written != -1);
	assert(bytes_to_write == bytes_written);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// close counter file
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	b_ret = CloseHandle(hf);
	assert(b_ret != 0);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	ret = close(hf);
	assert(ret != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
Function: plt_tools_set_pl_overflow_counter_value
Purpose : set index counter cache value to generate a pl_write cache hit
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_tools_set_pl_counter_write_cache_hit(unsigned int index) {

	unsigned long long hit_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	assert(index >= 0);
	assert(index < PL_MAX_COUNTERS_PER_LINK);
	assert(index < PL_UNIT_TESTS_COUNTERS_COUNT);

	//-------------------------------------------------------------------------
	// set counter index cache value to the reference value
	// fixed and defined in unit_tests_framework.h
	//-------------------------------------------------------------------------
	ppl_table->pl_array[0].pl_write_cache[index] = hit_values[index];
}

/*-----------------------------------------------------------------------------
Function: plt_tools_set_pl_counter_write_cache_miss
Purpose : set index counter cache value to generate a pl_write cache miss
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_tools_set_pl_counter_write_cache_miss(unsigned int index) {

	unsigned long long miss_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_CACHE_MISS_TEST_VALUES
	;

	assert(index >= 0);
	assert(index < PL_MAX_COUNTERS_PER_LINK);
	assert(index < PL_UNIT_TESTS_COUNTERS_COUNT);

	//-------------------------------------------------------------------------
	// set counter index cache value to the reference value
	// fixed and defined in unit_tests_framework.h
	//-------------------------------------------------------------------------
	ppl_table->pl_array[0].pl_write_cache[index] = miss_values[index];
}

/*-----------------------------------------------------------------------------
Function: ptl_replace_byte_in_file_with_byte
Purpose : replace the byte at line / column in file to byte
In      : file name string, line and column position and byte
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void ptl_replace_byte_in_file_with_byte(
	char *file_name, 
	size_t line, 
	size_t column, 
	unsigned char byte
) {

	//-------------------------------------------------------------------------
	// generic variables.
	//-------------------------------------------------------------------------
	int iret = -1;
	unsigned char *pc = NULL;

	//-------------------------------------------------------------------------
	// file buffer variables.
	//-------------------------------------------------------------------------
	unsigned char *file_buffer = NULL;
	size_t file_buffer_size = 0;
	size_t line_in_file = 0;
	size_t column_in_file = 0;

	//-------------------------------------------------------------------------
	// file handling variables.
	//-------------------------------------------------------------------------
	FILE* file = NULL;
	unsigned char c = '\0';
	size_t bytes_in_file = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t bytes_written = 0;

	//-------------------------------------------------------------------------

	assert(file_name != NULL);
	assert(line != 0);
	assert(column != 0);

	//-------------------------------------------------------------------------
	// open the file in read mode.
	//-------------------------------------------------------------------------
	file = fopen(
		file_name,
		"r"
	);
	assert(file != NULL);

	//-------------------------------------------------------------------------
	// get file size.
	//-------------------------------------------------------------------------
	bytes_to_read = sizeof(char);
	do {
		bytes_read = fread(
			&c, 
			sizeof(unsigned char), 
			bytes_to_read, 
			file
		);
		bytes_in_file++;
	} while(!feof(file));
	assert(bytes_in_file != 0);

	//-------------------------------------------------------------------------
	// allocate file buffer.
	//-------------------------------------------------------------------------
	file_buffer_size = sizeof(unsigned char) * bytes_in_file;
	file_buffer = (unsigned char *)malloc(file_buffer_size);
	assert(file_buffer != NULL);
	memset(
		file_buffer,
		0,
		file_buffer_size
	);

	//-------------------------------------------------------------------------
	// reset file and load file content into buffer and close file.
	//-------------------------------------------------------------------------
	iret = fseek(
		file,
		0,
		0
	);
	assert(iret == 0);
	bytes_read = fread(
		file_buffer, 
		sizeof(unsigned char), 
		file_buffer_size, 
		file
	);
	assert(bytes_read == file_buffer_size - 1);
	iret = fclose(file);
	assert(iret == 0);

	//-------------------------------------------------------------------------
	// search line (line).
	//-------------------------------------------------------------------------
	pc = file_buffer;
	line_in_file = 1;
	do {
		if(*pc == PL_LF) {
			line_in_file++;
		}
	} while(
		((char)(*pc++) != EOF) &&
		(line_in_file < line)
	);
	assert(line_in_file == line);

	//-------------------------------------------------------------------------
	// search column (line).
	//-------------------------------------------------------------------------
	column_in_file = 1;
	while(
		(*pc != PL_LF) &&
		(column_in_file < column)
	) {
		pc++;
		column_in_file++;
	}
	assert(column_in_file == column);

	//-------------------------------------------------------------------------
	// set character to its replacement.
	//-------------------------------------------------------------------------
	*pc = byte;

	//-------------------------------------------------------------------------
	// overwrite file with new content.
	//-------------------------------------------------------------------------
	file = fopen(
		file_name,
		"w"
	);
	assert(file != NULL);
	bytes_written = fwrite(
		file_buffer, 
		sizeof(unsigned char), 
		file_buffer_size, 
		file
	);
	assert(bytes_written == file_buffer_size);
	iret = fclose(file);
	assert(iret == 0);

	//-------------------------------------------------------------------------
	// house cleaning.
	//-------------------------------------------------------------------------
	free(file_buffer);
	file_buffer = NULL;
}

/*-----------------------------------------------------------------------------
Function: ptl_replace_byte_in_file_with_byte_string
Purpose : replace the byte at line / column in file with byte string of a given 
          length
In      : file name string, line and column position and byte string and size
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void ptl_replace_byte_in_file_with_byte_string(
	char *file_name, 
	size_t line, 
	size_t column, 
	unsigned char *byte_string,
	size_t byte_string_length
) {

	//-------------------------------------------------------------------------
	// generic variables.
	//-------------------------------------------------------------------------
	int iret = -1;
	unsigned char *pc = NULL;

	//-------------------------------------------------------------------------
	// file buffer variables.
	//-------------------------------------------------------------------------
	unsigned char *file_buffer = NULL;
	unsigned char *expanded_file_buffer = NULL;
	size_t file_buffer_size = 0;
	size_t expanded_file_buffer_size = 0;
	size_t line_in_file = 0;
	size_t column_in_file = 0;
	size_t bytes_count = 0;

	//-------------------------------------------------------------------------
	// file handling variables.
	//-------------------------------------------------------------------------
	FILE* file = NULL;
	unsigned char c = '\0';
	size_t bytes_in_file = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t bytes_written = 0;

	//-------------------------------------------------------------------------

	assert(file_name != NULL);
	assert(line != 0);
	assert(column != 0);
	assert(byte_string != NULL);
	assert(byte_string_length != 0);

	//-------------------------------------------------------------------------
	// open the file in read mode.
	//-------------------------------------------------------------------------
	file = fopen(
		file_name,
		"r"
	);
	assert(file != NULL);

	//-------------------------------------------------------------------------
	// get file size.
	//-------------------------------------------------------------------------
	bytes_to_read = sizeof(char);
	do {
		bytes_read = fread(
			&c, 
			sizeof(unsigned char), 
			bytes_to_read, 
			file
		);
		bytes_in_file++;
	} while(!feof(file));
	assert(bytes_in_file != 0);

	//-------------------------------------------------------------------------
	// allocate file buffer.
	//-------------------------------------------------------------------------
	file_buffer_size = sizeof(unsigned char) * bytes_in_file;
	file_buffer = (unsigned char *)malloc(file_buffer_size);
	assert(file_buffer != NULL);
	memset(
		file_buffer,
		0,
		file_buffer_size
	);

	//-------------------------------------------------------------------------
	// allocate expanded file buffer.
	//-------------------------------------------------------------------------
	expanded_file_buffer_size = 
		sizeof(unsigned char) * 
		(
			bytes_in_file +
			byte_string_length
		)
	;
	expanded_file_buffer = (unsigned char *)malloc(expanded_file_buffer_size);
	assert(expanded_file_buffer != NULL);
	memset(
		expanded_file_buffer,
		0,
		expanded_file_buffer_size
	);

	//-------------------------------------------------------------------------
	// reset file and load file content into buffer and close file.
	//-------------------------------------------------------------------------
	iret = fseek(
		file,
		0,
		0
	);
	assert(iret == 0);
	bytes_read = fread(
		file_buffer, 
		sizeof(unsigned char), 
		file_buffer_size, 
		file
	);
	assert(bytes_read == file_buffer_size - 1);
	iret = fclose(file);
	assert(iret == 0);

	//-------------------------------------------------------------------------
	// search line (line).
	//-------------------------------------------------------------------------
	bytes_count = 0;
	pc = file_buffer;
	line_in_file = 1;
	do {
		bytes_count++;
		if(*pc == PL_LF) {
			line_in_file++;
		}
	} while(
		((char)(*pc++) != EOF) &&
		(line_in_file < line)
	);
	assert(line_in_file == line);

	//-------------------------------------------------------------------------
	// search column (line).
	//-------------------------------------------------------------------------
	column_in_file = 1;
	while(
		(*pc != PL_LF) &&
		(column_in_file < column)
	) {
		pc++;
		bytes_count++;
		column_in_file++;
	}
	assert(column_in_file == column);

	//-------------------------------------------------------------------------
	// copy bytes before replacelent position into the new file buffer.
	//-------------------------------------------------------------------------
	memcpy(
		expanded_file_buffer,
		file_buffer,
		bytes_count
	);

	//-------------------------------------------------------------------------
	// insert replacement byte string into the new file buffer.
	//-------------------------------------------------------------------------
	memcpy(
		&expanded_file_buffer[bytes_count],
		byte_string,
		byte_string_length
	);

	//-------------------------------------------------------------------------
	// copy bytes after replacelent position into the new file buffer.
	//-------------------------------------------------------------------------
	memcpy(
		&expanded_file_buffer[bytes_count + byte_string_length],
		++pc,
		bytes_in_file - bytes_count - 1
	);

	//-------------------------------------------------------------------------
	// overwrite file with new content.
	//-------------------------------------------------------------------------
	file = fopen(
		file_name,
		"w"
	);
	assert(file != NULL);
	bytes_written = fwrite(
		expanded_file_buffer, 
		sizeof(unsigned char), 
		expanded_file_buffer_size, 
		file
	);
	assert(bytes_written == expanded_file_buffer_size);
	iret = fclose(file);
	assert(iret == 0);

	//-------------------------------------------------------------------------
	// house cleaning.
	//-------------------------------------------------------------------------
	free(file_buffer);
	file_buffer = NULL;
	free(expanded_file_buffer);
	expanded_file_buffer = NULL;
}
