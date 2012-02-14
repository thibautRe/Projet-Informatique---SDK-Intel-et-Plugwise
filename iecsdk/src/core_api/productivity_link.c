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
// Catch configuration errors
//-----------------------------------------------------------------------------
#if defined (__PL_IOS__) && !defined (__PL_FILESYSTEM_LESS__)
	#error "Productivity Links are NOT stored on IOS devices."
	#error "Only __PL_FILESYSTEM_LESS__ mode is allowed."
#endif // (__PL_IOS__) && !(__PL_FILESYSTEM_LESS__)

//-----------------------------------------------------------------------------
// PL Build configuration report
//-----------------------------------------------------------------------------
#ifdef _MSC_VER

	#pragma	message ("//-----------------------------------------------------------------------------")
	#pragma	message ("// PL Build configuration report.")
	#pragma	message ("//-----------------------------------------------------------------------------")

	//-------------------------------------------------------------------------
	// Generic build configuration reporting.
	//-------------------------------------------------------------------------
	#ifdef _DEBUG
		#pragma	message ("NOTE: Building using _DEBUG.")
	#endif // _DEBUG
	#ifdef _RELEASE
		#pragma	message ("NOTE: Building using _RELEASE.")
	#endif // _RELEASE
	#ifdef _CONSOLE
		#pragma	message ("NOTE: Building using _CONSOLE.")
	#endif // _CONSOLE
	#ifdef _UNICODE
		#pragma	message ("NOTE: Building using _UNICODE.")
	#endif // _UNICODE
	#ifdef UNICODE
		#pragma	message ("NOTE: Building using UNICODE.")
	#endif // UNICODE
	#ifdef _ATL_STATIC_REGISTRY
		#pragma	message ("NOTE: Building using _ATL_STATIC_REGISTRY.")
	#endif // _ATL_STATIC_REGISTRY
	#ifdef __PL_LITTLE_ENDIAN__
		#pragma	message ("NOTE: Building using __PL_LITTLE_ENDIAN__.")
	#endif // __PL_LITTLE_ENDIAN__
	#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		#pragma	message ("NOTE: Building using __PL_DYNAMIC_COUNTERS_ALLOCATION__.")
	#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	#ifdef __PL_BLOCKING_PL_READ__
		#pragma	message ("NOTE: Building using __PL_BLOCKING_PL_READ__.")
	#endif // __PL_LOGGER_ONLY__
	#ifdef __PL_FILESYSTEM_LESS__
		#pragma	message ("NOTE: Building using __PL_FILESYSTEM_LESS__.")
	#endif // __PL_FILESYSTEM_LESS__
	#ifdef __PL_IN_MEMORY__
		#pragma	message ("NOTE: Building using __PL_IN_MEMORY__.")
	#endif // __PL_IN_MEMORY__
	#ifdef __PL_AGENT__
		#pragma	message ("NOTE: Building using __PL_AGENT__.")
	#endif // __PL_AGENT__
	#ifdef __PL_EXTRA_INPUT_CHECKS__
		#pragma	message ("NOTE: Building using __PL_EXTRA_INPUT_CHECKS__.")
	#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// OS build configuration reporting.
	//-------------------------------------------------------------------------
	#ifdef __PL_WINDOWS__
		#pragma	message ("NOTE: Building using __PL_WINDOWS__.")
	#endif // __PL_WINDOWS__
	#ifdef __PL_LINUX__
		#pragma	message ("NOTE: Building using __PL_LINUX__.")
	#endif // __PL_LINUX__
	#ifdef __PL_SOLARIS__
		#pragma	message ("NOTE: Building using __PL_SOLARIS__.")
	#endif // __PL_SOLARIS__
	#ifdef __PL_MACOSX__
		#pragma	message ("NOTE: Building using __PL_MACOSX__.")
	#endif // __PL_MACOSX__
	#ifdef __PL_IOS__
		#pragma	message ("NOTE: Building using __PL_IOS__.")
	#endif // __PL_IOS__

	//-------------------------------------------------------------------------
	// Dynamic library build configuration reporting.
	//-------------------------------------------------------------------------
	#ifdef _WINDLL
		#pragma	message ("NOTE: Building using _WINDLL.")
	#endif // _WINDLL
	#ifdef _USRDLL
		#pragma	message ("NOTE: Building using _USRDLL.")
	#endif // _USRDLL
	#ifdef __PL_WINDOWS_DLL_EXPORTS__
		#pragma	message ("NOTE: Building using __PL_WINDOWS_DLL_EXPORTS__.")
	#endif // __PL_WINDOWS_DLL_EXPORTS__
	#ifdef __PL_LINUX_SO_EXPORTS__
		#pragma	message ("NOTE: Building using __PL_LINUX_SO_EXPORTS__.")
	#endif // __PL_LINUX_SO_EXPORTS__
	#ifdef __PL_SOLARIS_SO_EXPORTS__
		#pragma	message ("NOTE: Building using __PL_SOLARIS_SO_EXPORTS__.")
	#endif // __PL_SOLARIS_SO_EXPORTS__
	#ifdef __PL_MACOSX_SO_EXPORTS__
		#pragma	message ("NOTE: Building using __PL_MACOSX_SO_EXPORTS__.")
	#endif // __PL_MACOSX_SO_EXPORTS__
	#ifdef __PL_IOS_SO_EXPORTS__
		#pragma	message ("NOTE: Building using __PL_IOS_SO_EXPORTS__.")
	#endif // __PL_IOS_SO_EXPORTS__
	#ifdef __PL_JNI_EXPORTS__
		#pragma	message ("NOTE: Building using __PL_JNI_EXPORTS__.")
	#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// PL functional build configuration reporting.
	//-------------------------------------------------------------------------
	#ifdef __PL_BYPASS__
		#pragma	message ("NOTE: Building using __PL_BYPASS__.")
	#endif // __PL_BYPASS__
	#ifdef __PL_GENERATE_INI__
		#pragma	message ("NOTE: Building using __PL_GENERATE_INI__.")
	#endif // __PL_GENERATE_INI__
	#ifdef __PL_GENERATE_INI_VERSION_TAGGING__
		#pragma	message ("NOTE: Building using __PL_GENERATE_INI_VERSION_TAGGING__.")
	#endif // __PL_GENERATE_INI_VERSION_TAGGING__
	#ifdef __PL_GENERATE_INI_BUILD_TAGGING__
		#pragma	message ("NOTE: Building using __PL_GENERATE_INI_BUILD_TAGGING__.")
	#endif // __PL_GENERATE_INI_BUILD_TAGGING__
	#ifdef __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
		#pragma	message ("NOTE: Building using __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__.")
	#endif // __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
		#pragma	message ("NOTE: Building using __PL_BLOCKING_COUNTER_FILE_LOCK__.")
	#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
	#ifdef __PL_ATTACH_SCRIPT_SUPPORT__
		#pragma	message ("NOTE: Building using __PL_ATTACH_SCRIPT_SUPPORT__.")
	#endif // __PL_ATTACH_SCRIPT_SUPPORT__
	#ifdef __PL_UNDEF_T__
		#pragma	message ("NOTE: Building using __PL_UNDEF_T__.")
	#endif // __PL_UNDEF_T__
	#ifdef __PL_TIMESTAMPING__
		#pragma	message ("NOTE: Building using __PL_TIMESTAMPING__.")
	#endif // __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// PL configuration reporting (use of forbidden mode in customer available 
	// software is not allowed) - with __PL_AGENT__ exception.
	//-------------------------------------------------------------------------
	#ifdef __PL_CONSTANT_UUID__
		#pragma	message ("NOTE: Building using __PL_CONSTANT_UUID__ (*FORBIDDEN* in customer available software).")
	#endif // __PL_CONSTANT_UUID__
	#ifdef __PL_BINARY_COUNTER__
		#pragma	message ("NOTE: Building using __PL_BINARY_COUNTER__ (*FORBIDDEN* in customer available software).")
	#endif // __PL_BINARY_COUNTER__
	#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
		#ifdef __PL_AGENT__
			#pragma	message ("NOTE: Building using __PL_DYNAMIC_TABLE_ALLOCATION__.")
		#else // __PL_AGENT__
			#pragma	message ("NOTE: Building using __PL_DYNAMIC_TABLE_ALLOCATION__ (*FORBIDDEN* in customer available software).")
		#endif // __PL_AGENT__
	#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
	#ifdef __PL_UNIT_TESTS__
		#pragma	message ("NOTE: Building using __PL_UNIT_TESTS__ (*FORBIDDEN* in customer available software).")
	#endif // __PL_UNIT_TESTS__
	#ifdef __PL_LOGGER_ONLY__
		#pragma	message ("NOTE: Building using __PL_LOGGER_ONLY__ (*FORBIDDEN* in customer available software).")
	#endif // __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// Architecture specific build configuration reporting.
	//-------------------------------------------------------------------------
	#ifdef __PL_NO_SSE_PAUSE_SUPPORT__
		#pragma	message ("NOTE: Building using __PL_NO_SSE_PAUSE_SUPPORT__.")
	#endif // __PL_NO_SSE_PAUSE_SUPPORT__

#endif // _MSC_VER

//-----------------------------------------------------------------------------
// Headers inclusions.
//-----------------------------------------------------------------------------
#include "productivity_link.h"
#include <errno.h>
#ifdef __PL_WINDOWS__
	#include <tchar.h>
	#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
		#include <intrin.h> // for _mm_pause
	#endif // __PL_NO_SSE_PAUSE_SUPPORT__
	#pragma comment (lib, "Rpcrt4")
	#ifdef _DEBUG
		#include <assert.h>
		#include <crtdbg.h>
	#endif // _DEBUG
	#ifdef __PL_EXTRA_INPUT_CHECKS__
		#include <stdio.h>
	#endif // __PL_EXTRA_INPUT_CHECKS__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <semaphore.h>
	#include <uuid/uuid.h>
	#include <errno.h> // compile with -D_LIBC_REENTRANT
	#include <ctype.h>
	#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
		#include <xmmintrin.h> // for _mm_pause, need -msse gcc flag
	#endif // __PL_NO_SSE_PAUSE_SUPPORT__
	#include <netinet/tcp.h> // for TCP_NODELAY
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_BLOCKING_PL_READ__
	#ifdef __PL_LINUX__
		#include <sys/inotify.h>
	#endif // __PL_LINUX__
	#ifdef __PL_MACOSX__
		#include <sys/event.h>
	#endif // __PL_MACOSX__
	#ifdef __PL_SOLARIS__
		#include <aio.h>
		#include <port.h>
	#endif // __PL_SOLARIS__
#endif // __PL_BLOCKING_PL_READ__
#if defined (__PL_TIMESTAMPING__) || (__PL_LOGGER_ONLY__) || (__PL_GENERATE_INI_DATE_AND_TIME_TAGGING__)
	#include <time.h>
#endif // __PL_TIMESTAMPING__ || __PL_LOGGER_ONLY__ || __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__

//-------------------- Begin of global variables ------------------------------

//-----------------------------------------------------------------------------
// Productivity links table (global - semaphore protected against other 
// threads).
//-----------------------------------------------------------------------------
#ifndef __PL_BYPASS__
	PL_TABLE pl_table;
	#ifdef __PL_UNIT_TESTS__
		PPL_TABLE ppl_table = &pl_table;
	#endif // __PL_UNIT_TESTS__
	#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
		unsigned int pl_max_productivity_links = PL_MAX_PRODUCTIVITY_LINKS;
	#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
#endif // __PL_BYPASS__

//-----------------------------------------------------------------------------
// Productivity links table initialization flag (global).
//-----------------------------------------------------------------------------
#ifdef __PL_UNIT_TESTS__
	#ifdef __PL_WINDOWS__
		BOOL pl_table_initialized = FALSE;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		int pl_table_initialized = 0;
	#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#else // __PL_UNIT_TESTS__
	#ifdef __PL_WINDOWS__
		static BOOL pl_table_initialized = FALSE;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		#ifndef __PL_BYPASS__
			static int pl_table_initialized = 0;
		#endif // __PL_BYPASS__
	#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // __PL_UNIT_TESTS__

//---------------------- End of global variables ------------------------------

#if defined (__PL_WINDOWS__) && (_USRDLL) && (__PL_WINDOWS_DLL_EXPORTS__)

/*-----------------------------------------------------------------------------
@@@@@  @      @      @    @   @@   @@@@@  @    @
@    @ @      @      @@  @@  @  @    @    @@   @
@    @ @      @      @ @@ @ @    @   @    @ @  @
@    @ @      @      @    @ @    @   @    @ @  @
@    @ @      @      @    @ @@@@@@   @    @  @ @
@    @ @      @      @    @ @    @   @    @   @@
@@@@@  @@@@@@ @@@@@@ @    @ @    @ @@@@@  @    @

Function: DllMain
Purpose : Dll entry point
In      : usual Windows stuff
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/01/2008    Jamel Tayeb             Creation.
*/
BOOL APIENTRY DllMain(
	HMODULE hModule, 
	DWORD ul_reason_for_call, 
	LPVOID lpReserved
) {

	switch(ul_reason_for_call)	{

		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return(TRUE);
}
#endif // #if defined __PL_WINDOWS__ && _USRDLL && __PL_WINDOWS_DLL_EXPORTS__

/*-----------------------------------------------------------------------------
@@@@@  @              @@@@  @@@@@  @@@@@@ @    @
@    @ @             @    @ @    @ @      @@   @
@    @ @             @    @ @    @ @      @ @  @
@@@@@  @             @    @ @@@@@  @@@@@@ @ @  @
@      @             @    @ @      @      @  @ @
@      @             @    @ @      @      @   @@
@      @@@@@@         @@@@  @      @@@@@@ @    @
              @@@@@@
Function: pl_open
Purpose : create and open a productivity link
In      : array of pointers to null terminated strings to counters' names
		: number of counters to be created
Out     : productivity link uui descriptor (to be shared with other 
          applications for attach)
Return  : productivity link descriptor and last error set if invalid 
          descriptor returned

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/01/2008    Jamel Tayeb             Creation.
06/04/2010    Jamel Tayeb             Added __PL_FILESYSTEM_LESS__ support.
10/21/2010    Jamel Tayeb             Added __PL_EXTRA_INPUT_CHECKS__ support.
*/
#ifdef __PL_JNI_EXPORTS__
JNIEXPORT jint JNICALL Java_ProductivityLink_pl_1open(
	JNIEnv *interface_pointer, 
	jobject caller_reference, 
	jstring java_pl_application_name, 
	jint java_pl_counters_count, 
	jobjectArray java_pl_counters_names, 
	jobject java_puuid
) {

	jfieldID uuid_msb_field_id = NULL;
	jfieldID uuid_lsb_field_id = NULL;
	jclass uuid_class = NULL;

	const char *pl_application_name = NULL;
	unsigned int pl_counters_count = PL_INVALID_DESCRIPTOR;
	const char **pl_counters_names = NULL;

	const char *native_string = NULL;
	uuid_t *puuid = NULL;
	char uuid_bytes[16];
	char *pbyte = NULL;

	unsigned int i = 0;
	jobject string_object = NULL;
	jsize object_array_size = 0;

#else // __PL_JNI_EXPORTS__
PL_API int pl_open(
	char *pl_application_name, 
	unsigned int pl_counters_count, 
	const char *pl_counters_names[], 
	uuid_t *puuid
) {
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// if __PL_BYPASS__ is defined, set system's last error code to 
	// PL_BYPASSED and return.
	//-------------------------------------------------------------------------
#ifdef __PL_BYPASS__
#ifdef __PL_WINDOWS__
	SetLastError(PL_BYPASSED);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	errno = PL_BYPASSED;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
return(PL_INVALID_DESCRIPTOR);
#else // __PL_BYPASS__
	unsigned int j = 0;
	unsigned int index = 0;
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
	unsigned int pl_old_max_productivity_links = 0;
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
#if defined (__PL_DYNAMIC_COUNTERS_ALLOCATION__) || (__PL_DYNAMIC_TABLE_ALLOCATION__)
	size_t memory_size = 0;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__ || __PL_DYNAMIC_TABLE_ALLOCATION__
#ifdef __PL_FILESYSTEM_LESS__
	int one = 1;
	char *message = NULL;
	char *p_string = NULL;
	const char *pp_string = NULL;
	char buffer[PL_MAX_PATH] = { '\0' };
	char pl_input_buffer[PL_MAX_INPUT_BUFFER_SIZE] = { '\0' };
	char pl_output_buffer[PL_MAX_OUTPUT_BUFFER_SIZE] = { '\0' };
	SOCKET pl_socket = INVALID_SOCKET;
	PL_PROTOCOL_STATUS pret = PL_PROTOCOL_FAILURE;
	int connection_attempt_count = 0;
	PL_PROTOCOL_SIZET message_size = 0;
#ifdef __PL_WINDOWS__
	ADDRINFO *pa = NULL;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	struct addrinfo *pa = NULL;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_EXTRA_INPUT_CHECKS__

		//---------------------------------------------------------------------
		// Generic variables used for checks.
		//---------------------------------------------------------------------
		int value = -1;

		//---------------------------------------------------------------------
		// Variables used to check validity of IPV4 address.
		//---------------------------------------------------------------------
		int dot_count = 0;
		int digit_count = 0;
		char ip_v4_address_value_string[
			PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_BUFFER_SIZE
		] = { '\0' };
		PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_CLASSES ip_v4_class = 
			PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A
		;
		static char allowed_characters_in_ip_v4_address[
			PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS_COUNT
		] = { PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS };

		//---------------------------------------------------------------------
		// Variables used to check validity of port.
		//---------------------------------------------------------------------
		char port_value_string[
			PL_EXTRA_INPUT_CHECKS_PORT_MAX_BUFFER_SIZE
		] = { '\0' };
		static char allowed_characters_in_port[
			PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS_COUNT
		] = { PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS };

	#endif // __PL_EXTRA_INPUT_CHECKS__
#else  // __PL_FILESYSTEM_LESS__
	#ifdef __PL_GENERATE_INI__
		char pl_eol_buffer[] = PL_END_OF_LINE;
	#endif // __PL_GENERATE_INI__
	#ifdef __PL_GENERATE_INI_BUILD_TAGGING__
		char *pl_build_tags[] = { PL_BUILD_TAGS };
	#endif // __PL_GENERATE_INI_BUILD_TAGGING__
	#ifdef __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__ 
		time_t pl_ini_time;
	#endif // __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
#endif // __PL_FILESYSTEM_LESS__

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Generic variables used to checks.
	//-------------------------------------------------------------------------
	int m = 0;
	int n = 0;
	const char *pchar = NULL;
	size_t bytes_count = 0;
	char convert_buffer[PL_MAX_BUFFER_SIZE] = { '\0' };
	size_t bytes_left_in_convert_buffer = 0;

	//-------------------------------------------------------------------------
	// Variables used to check application and counter(s) names.
	//-------------------------------------------------------------------------
	size_t pl_root_name_length = 0;
	size_t pl_counter_name_length = 0;
	size_t application_name_length = 0;
	size_t counter_name_length = 0;
	static char allowed_characters_in_application_name[
		PL_EXTRA_INPUT_CHECKS_APPLICATION_NAME_ALLOWED_CHARACTERS_COUNT
	] = { PL_EXTRA_INPUT_CHECKS_APPLICATION_NAME_ALLOWED_CHARACTERS };
	static char allowed_characters_in_counter_name[
		PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT
	] = { PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS };
	
#endif // __PL_EXTRA_INPUT_CHECKS__
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// @    @ @@@@@  @    @ @@@@@   @@@@  @    @  @@@@
	// @    @   @    @@   @ @    @ @    @ @    @ @    @
	// @  @ @   @    @ @  @ @    @ @    @ @  @ @  @@@@
	//  @ @ @   @    @   @@ @    @ @    @  @ @ @      @
	//   @ @  @@@@@  @    @ @@@@@   @@@@    @ @  @@@@@
	//-------------------------------------------------------------------------
	int ret = 0;
	size_t st_ret = 0;
	RPC_STATUS rpc_ret = 0;	
	DWORD dw_ret = 0;
	DWORD pl_last_error = PL_NO_ERROR;
	BOOL b_ret = FALSE;
	TCHAR *p = NULL;
	TCHAR pl_root[PL_MAX_PATH] = { _T('\0') };
	TCHAR pl_path[PL_MAX_PATH] = { _T('\0') };
	TCHAR pl_buffer[PL_MAX_PATH] = { _T('\0') };
	TCHAR pl_cvt_buffer[PL_MAX_BUFFER_SIZE] = { _T('\0') };
	char pl_ini_path[PL_MAX_PATH] = { _T('\0') };
	char pl_ini_buffer[PL_MAX_PATH] = { _T('\0') };
	char pl_ini_cvt_buffer[PL_MAX_BUFFER_SIZE] = { _T('\0') };
#ifdef __PL_GENERATE_INI__
	HANDLE pl_config_file = NULL;
	DWORD pl_config_file_bytes_to_write = 0;
	DWORD pl_config_file_bytes_written = 0;
#endif // __PL_GENERATE_INI__
#ifdef __PL_FILESYSTEM_LESS__
	errno_t eno_ret = -1;
	size_t length = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;
	char *env_port = NULL;
	char *env_address = NULL;
	WSADATA windows_socket_data;
	static BOOL fw_initialized = FALSE;
	DWORD dwret = 0;
#endif // __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Variables used for buffer and input checks.
	//-------------------------------------------------------------------------
	size_t bytes_left_in_buffer = 0;

#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Get the uuid class and field id.
	//-------------------------------------------------------------------------
	uuid_class = (*interface_pointer)->GetObjectClass(
		interface_pointer, java_puuid
	);
	if(uuid_class == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}
	uuid_msb_field_id = (*interface_pointer)->GetFieldID(
		interface_pointer, 
		uuid_class, 
		"mostSigBits", 
		"J"
	);
	if(uuid_msb_field_id == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}
	uuid_lsb_field_id = (*interface_pointer)->GetFieldID(
		interface_pointer, 
		uuid_class, 
		"leastSigBits", 
		"J"
	);
	if(uuid_lsb_field_id == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}

	//-------------------------------------------------------------------------
	// Get the java arguments & initializations.
	//-------------------------------------------------------------------------
	pl_application_name = (*interface_pointer)->GetStringUTFChars(
		interface_pointer, 
		java_pl_application_name, 
		NULL
	);

	//-------------------------------------------------------------------------
	// Get and check the counter count.
	//-------------------------------------------------------------------------
	pl_counters_count = (unsigned int)java_pl_counters_count;
	object_array_size = (*interface_pointer)->GetArrayLength(
		interface_pointer, 
		java_pl_counters_names
	);
	if(object_array_size != pl_counters_count) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}

	//-------------------------------------------------------------------------
	// Get and store the counter names.
	//-------------------------------------------------------------------------
	pl_counters_names = (char **)malloc(sizeof(char *) * pl_counters_count);
	if(pl_counters_names == NULL) {
		pl_last_error = PL_CRITICAL_FAILURE;
		goto pl_open_return;
	}
	for(i = 0; i < pl_counters_count; i++) {
		string_object = (*interface_pointer)->GetObjectArrayElement(
			interface_pointer, 
			java_pl_counters_names, 
			i
		);
		native_string = (*interface_pointer)->GetStringUTFChars(
			interface_pointer, 
			string_object, 
			NULL
		);
		pl_counters_names[i] = native_string;
	}

	//-------------------------------------------------------------------------
	// Allocate temp uuid.
	//-------------------------------------------------------------------------
	puuid = (uuid_t *)malloc(sizeof(uuid_t));
	if(puuid == NULL) {
		pl_last_error = PL_CRITICAL_FAILURE;
		goto pl_open_return;
	}
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Check calling arguments.
	// Note:
	//    Since application name pointer can be NULL, it is not tested.
	//-------------------------------------------------------------------------
	if(
		(pl_counters_names == NULL) ||
		(puuid == NULL)
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		|| (pl_counters_count > PL_MAX_COUNTERS_PER_LINK)
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Perform the following input data checking:
	//   - Only allowed characters are used in application and counter(s) names
	//   - The length of application and counter(s) names allow fully qualified
	//   counter file names having a maximum of PL_MAX_PATH characters.
	// Note:
	//    <PL_FOLDER>/<application_name>_<UUID>/<counter_name>
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Check application name.
	//-------------------------------------------------------------------------
	if(pl_application_name != NULL) {

		//---------------------------------------------------------------------
		// Get application name length and check value.
		//---------------------------------------------------------------------
		pchar = pl_application_name;
		bytes_count = 0;
		while(
			(bytes_count < PL_MAX_PATH) &&
			(*pchar != '\0')
		) {
				bytes_count++;
				pchar++;
		}
		if(bytes_count >= PL_MAX_PATH) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_open_return;
		}
		application_name_length = bytes_count;
		if(
			(application_name_length <= 0) ||
			(application_name_length >= PL_MAX_PATH)
		) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_open_return;
		}

		//---------------------------------------------------------------------
		// Check that only allowed characters are used in the application name.
		//---------------------------------------------------------------------
		for(
			n = 0; 
			n < (int)application_name_length; 
			n++
		) {
			for(
				m = 0; 
				m < PL_EXTRA_INPUT_CHECKS_APPLICATION_NAME_ALLOWED_CHARACTERS_COUNT; 
				m++
			) {
				if(
					pl_application_name[n] == 
					allowed_characters_in_application_name[m]
				) {
					goto pl_open_check_application_name_next;
				}
			} // m
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_open_return;
pl_open_check_application_name_next:
			;
		} // n
	} else {
		application_name_length = strlen(PL_INI_ANONYMOUS_APPLICATION_NAME);
	}

	//-------------------------------------------------------------------------
	// Compute and check control length.
	// Note:
	//    Fully qualified counter file name must have a character count of less
	//    or PL_MAX_PATH characters.
	//-------------------------------------------------------------------------
	pl_root_name_length = strlen(PL_FOLDER_STRING);
	pl_root_name_length += strlen(PL_PATH_SEPARATOR_STRING);
	pl_root_name_length += application_name_length;
	pl_root_name_length += strlen(PL_APPLICATION_NAME_SEPARATOR_STRING);
	pl_root_name_length += PL_UUID_MAX_CHARS;
	pl_root_name_length += strlen(PL_PATH_SEPARATOR_STRING);
	if(pl_root_name_length >= PL_MAX_PATH) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}

	//-------------------------------------------------------------------------
	// Check counter(s) name.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_counters_count; j++) {

		//---------------------------------------------------------------------
		// Check counter name.
		//---------------------------------------------------------------------
		if(pl_counters_names[j] != NULL) {

			//-----------------------------------------------------------------
			// Get counter name length and check value.
			//-----------------------------------------------------------------
			pchar = (char *)pl_counters_names[j];
			bytes_count = 0;
			while(
				(bytes_count < PL_MAX_PATH) &&
				(*pchar != '\0')
			) {
					bytes_count++;
					pchar++;
			}
			if(bytes_count >= PL_MAX_PATH) {
				pl_last_error = PL_INVALID_PARAMETERS;
				goto pl_open_return;
			}
			counter_name_length = bytes_count;
			if(
				(counter_name_length <= 0) ||
				(counter_name_length >= PL_MAX_PATH)
			) {
				pl_last_error = PL_INVALID_PARAMETERS;
				goto pl_open_return;
			}

			//-----------------------------------------------------------------
			// Check that only allowed characters are used in the counter name.
			//-----------------------------------------------------------------
			for(
				n = 0; 
				n < (int)counter_name_length; 
				n++
			) {
				for(
					m = 0; 
					m < PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT; 
					m++
				) {
					if(
						pl_counters_names[j][n] == 
						allowed_characters_in_counter_name[m]
					) {
						goto pl_open_check_counter_name_next;
					}
				} // m
				pl_last_error = PL_INVALID_PARAMETERS;
				goto pl_open_return;
pl_open_check_counter_name_next:
				;
			} // n
		} else {

			//-----------------------------------------------------------------
			// Anonymous counter.
			// Note:
			//    <anonymous><n>
			//-----------------------------------------------------------------
			counter_name_length = strlen(PL_INI_GENERIC_COUNTER_NAME);

			//-----------------------------------------------------------------
			// Generate counter rank for anonymous counter and get its length.
			// Note:
			//    Max value for unsigned int is 4,294,967,295
			//-----------------------------------------------------------------
			bytes_left_in_convert_buffer = sizeof(convert_buffer);
			bytes_left_in_convert_buffer -= 
				strlen(PL_MAX_UNSIGNED_INTEGER_STRING)
			;
			if(bytes_left_in_convert_buffer > PL_STRNCPY_MIN_BYTES) {
				memset(
					convert_buffer, 
					0, 
					sizeof(convert_buffer)
				);
				ret = sprintf_s(
					convert_buffer, 
					bytes_left_in_convert_buffer,
					"%d",
					j
				);
				if(ret < 0) {
					pl_last_error = PL_COUNTER_TO_STRING_FAILED;
					goto pl_open_return;
				}
			} else {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_return;
			}
			counter_name_length += strlen(convert_buffer);
		}

		//---------------------------------------------------------------------
		// Compute and check control length.
		// Note:
		//    Fully qualified counter file name must have a character count of 
		//    less or PL_MAX_PATH characters.
		//---------------------------------------------------------------------
		pl_counter_name_length = pl_root_name_length;
		pl_counter_name_length += counter_name_length;
		if(pl_counter_name_length >= PL_MAX_PATH) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_open_return;
		}
	} // for j

#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// First pl_open call takes the pl_table initialization penalty.
	//-------------------------------------------------------------------------
	if(pl_table_initialized == FALSE) {
#ifdef _DEBUG
#pragma	message ("NOTE: Building a Debug version with memory leak detection.")

		//---------------------------------------------------------------------
		// Dump memory leak info on any exit.
		//---------------------------------------------------------------------
		dw_ret = _CrtSetDbgFlag(
			_CRTDBG_ALLOC_MEM_DF | 
			_CRTDBG_LEAK_CHECK_DF
		);
		assert(dw_ret != -1);

		//---------------------------------------------------------------------
		// Redirect dump to stdout.
		//---------------------------------------------------------------------
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
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Allocate dynamically the pl_table -- fixed to default size.
		// This size will de expanded if needed later on and during each future 
		// call to pl_attach/pl_open.
		// Caution: this memory will not be freed! (__PL_DYNAMIC_TABLE_ALLOCA-
		// TION__).  Therefore it should never be defined or you can take 
		// responsibility to free it up (as in the PL Agent).
		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ defined
		// --------------------------------------------
		//
		//                                  |<----- LIMITED BY AVAILABLE MEMORY ---->|
		// +-----------------+------+       +------+------+--        --+------+------+
		// |                 |      |       |      |      |            |      |      |
		// | PL table access | *PL -+-----> | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |      |       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |       |      |      |            |      |      |
		// +-----------------+------+       +------+------+--        --+------+------+
		//---------------------------------------------------------------------
		ZeroMemory(
			&pl_table, 
			sizeof(pl_table)
		);
		memory_size = 
			sizeof(PRODUCTIVITY_LINK) * 
			PL_MAX_PRODUCTIVITY_LINKS
		;
		pl_table.pl_array = (PPRODUCTIVITY_LINK)malloc(memory_size);
		if(pl_table.pl_array == NULL) {
			pl_last_error = PL_OUT_OF_MEMORY;
			goto pl_open_return;
		}
		// next nulls in-use flags and the handle pointers
		ZeroMemory(
			pl_table.pl_array, 
			memory_size
		); 
		pl_max_productivity_links = PL_MAX_PRODUCTIVITY_LINKS;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ NOT defined
		// ------------------------------------------------
		//
		//                   |<----- PL_MAX_PRODUCTIVITY_LINKS ------>|
		// +-----------------+------+------+--        --+------+------+
		// |                 |      |      |            |      |      |
		// | PL Table access | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |      |            |      |      |
		// +-----------------+------+------+--        --+------+------+
		//---------------------------------------------------------------------
		// next nulls in-use flags and the handles
		ZeroMemory(
			&pl_table, 
			sizeof(PL_TABLE)
		); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Create PL Table semaphore.
		// --------------------------------------------------------------------
		pl_table.semaphore = CreateSemaphore(
			NULL, 
			(LONG)1, 
			(LONG)1, 
			NULL
		);
		if(pl_table.semaphore == NULL) {
			pl_last_error = PL_SYNCHRONIZATION_FAILED;
			goto pl_open_return;
		}
#ifdef __PL_FILESYSTEM_LESS__

		//---------------------------------------------------------------------
		// In file system-less mode, the PL protocol is used to send a pl_open
		// request to a PL agent (identified via the default agent IP @ / port
		// or user provided environment variables.  The remote agent will carry
		// out the pl_open API call and will return the remote pld, uuid and
		// status.  The remote pld will be stored into the PL table and a local
		// pld is returned with the uuid to the calling process.
		// --------------------------------------------------------------------
		if(fw_initialized == FALSE) {

			//-----------------------------------------------------------------
			// Initialize Winsoks to communicate with the agent.
			//-----------------------------------------------------------------
			ret = WSAStartup(
				MAKEWORD(2, 2), 
				&windows_socket_data
			);
			if(ret != 0) {
				pl_last_error = PL_FILESYSTEM_LESS_INITIALIZATION_FAILED;
				goto pl_open_return;
			}
			fw_initialized = TRUE;
		}
		pl_table_initialized = TRUE;
	} // if pl_table_initialized == FALSE

	//-------------------------------------------------------------------------
	// Lock the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
	dw_ret = WaitForSingleObject(
		pl_table.semaphore, 
		INFINITE
	);
	if(dw_ret != WAIT_OBJECT_0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_open_return;
	}
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < PL_MAX_PRODUCTIVITY_LINKS; index++) {
		if(pl_table.pl_array[index].pl_in_use == FALSE) {
			goto pl_open_found;
		}
	}
	// pl_table full
	pl_last_error = PL_DESCRIPTOR_TABLE_FULL;
	goto pl_open_unlock_table;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < pl_max_productivity_links; index++) {
		if(pl_table.pl_array[index].pl_in_use == FALSE) {
			goto pl_open_found;
		}
	}

	//-------------------------------------------------------------------------
	// No room in the table, lets double dynamically the pl_table size and
	// create the additional counters.
	//-------------------------------------------------------------------------
	pl_old_max_productivity_links = pl_max_productivity_links; 
	pl_max_productivity_links *= 2;
	pl_table.pl_array = (PPRODUCTIVITY_LINK)realloc(
		pl_table.pl_array, 
		sizeof(PRODUCTIVITY_LINK) * pl_max_productivity_links
	);
	if(pl_table.pl_array == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	// clear newly allocated memory
	ZeroMemory(
		&pl_table.pl_array[index], 
		sizeof(PRODUCTIVITY_LINK) * pl_old_max_productivity_links
	); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
pl_open_found:
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Allocate memory for the write cache.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(unsigned long long) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_write_cache = 
		(unsigned long long *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_write_cache == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_write_cache, 
		memory_size
	);
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate timestamps memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(time_t) * 
		pl_counters_count
	;
	pl_table.pl_array[index].open_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].open_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].open_time, 
		memory_size
	);
	pl_table.pl_array[index].last_attach_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_attach_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_attach_time, 
		memory_size
	);
	pl_table.pl_array[index].last_read_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_read_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_read_time, 
		memory_size
	);
	pl_table.pl_array[index].last_write_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_write_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_write_time, 
		memory_size
	);
	pl_table.pl_array[index].last_close_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_close_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_close_time, 
		memory_size
	);
#endif // __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate semaphore memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(HANDLE) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(HANDLE *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_handles_semaphores == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_counter_handles_semaphores, 
		memory_size
	);

	//-------------------------------------------------------------------------
	// Allocate socket memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(SOCKET) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_sockets = 
		(SOCKET *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_sockets == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_counter_sockets, 
		memory_size
	);
	pl_table.pl_array[index].pl_counters_count = 0;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	pl_table.pl_array[index].pl_in_use = TRUE;

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_ADDRESS environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	bytes_left_in_buffer = sizeof(pl_table.pl_array[index].pl_address);
	eno_ret = _dupenv_s(
		&env_address,
		&length,
		PL_DEFAULT_PL_AGENT_ADDRESS_ENVAR_NAME
	);
	if(bytes_left_in_buffer < length) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_return;
	}
	if(
		(eno_ret != 0) ||
		(length == 0)
	) {
		strncpy_s(
			pl_table.pl_array[index].pl_address,
			bytes_left_in_buffer,
			PL_DEFAULT_PL_AGENT_ADDRESS,
			_TRUNCATE
		);
		length = strlen(PL_DEFAULT_PL_AGENT_ADDRESS);
	} else {
		strncpy_s(
			pl_table.pl_array[index].pl_address,
			bytes_left_in_buffer,
			env_address,
			_TRUNCATE
		);
		free(env_address);
		env_address = NULL;
	}
	bytes_left_in_buffer -= length;
	if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Check the validity of the IPV4 address.
	// Note:
	//    Class A: 000.000.000.000 to 127.255.255.255
	//    Class B: 128.000.000.000 to 191.255.255.255
	//    Class C: 192.000.000.000 to 223.255.255.255
	//    Class D: 224.000.000.000 to 239.255.255.255
	//    Class E: 240.000.000.000 to 255.255.255.255
	//-------------------------------------------------------------------------
	length--;
	for(m = 0; m < (int)length; m++) {

		//---------------------------------------------------------------------
		// Ckeck that only legal characters are used.
		//---------------------------------------------------------------------
		if(
			pl_table.pl_array[index].pl_address[m] == 
			PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_DOT_CHARACTER
		) { 
			if(digit_count == 0) {

				//-------------------------------------------------------------
				// No address can start without a digit.
				//-------------------------------------------------------------
				goto pl_open_check_ip_v4_address_error; 
			}

			//-----------------------------------------------------------------
			// A dot was found, let's process the address value as stored.
			//-----------------------------------------------------------------
			dot_count++;
			digit_count = 0;
			ip_v4_address_value_string[
				PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE
			] = '\0';
			value = atoi(ip_v4_address_value_string);
			memset(
				ip_v4_address_value_string, 
				0, 
				sizeof(ip_v4_address_value_string)
			);
			
			//-----------------------------------------------------------------
			// Use the . character count to check address value ranges.
			//-----------------------------------------------------------------
			switch(dot_count) {

				case 1:

					//---------------------------------------------------------
					// This is the first address value (nnn.xxx.xxx.xxx).
					// Assign a class to the address based on the first address
					// value.
					//---------------------------------------------------------
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E; 
						break; 
					}
					goto pl_open_check_ip_v4_address_error;
					break;

				case 2:

					//---------------------------------------------------------
					// This is the second address value (xxx.nnn.xxx.xxx).
					// Check the second address value based on the class 
					// assigned using the first address value
					//---------------------------------------------------------
					switch(ip_v4_class) {
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						default:

							//-------------------------------------------------
							// Invalid second address value.
							//-------------------------------------------------
							goto pl_open_check_ip_v4_address_error;
					} // switch
					break;

				case 3: // third number

					//---------------------------------------------------------
					// This is the third address value (xxx.xxx.nnn.xxx).
					// Check the third address value based on the class 
					// assigned using the first address value
					//---------------------------------------------------------
					switch(ip_v4_class) {
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						default:

							//-------------------------------------------------
							// Invalid second address value.
							//-------------------------------------------------
							goto pl_open_check_ip_v4_address_error;
					} // switch
					break;

				default:

					//---------------------------------------------------------
					// This is the fourth address value (xxx.xxx.xxx.nnn).
					// Note:
					//    Fourth address value is tested later on, however if 
					//    we are here, it is an error.
					//---------------------------------------------------------
					goto pl_open_check_ip_v4_address_error;
			}

		} else {

			//-----------------------------------------------------------------
			// This is not a dot (.) character, check if it is an allowed one.
			//-----------------------------------------------------------------
			for(
				n = 0; 
				n < PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS_COUNT; 
				n++
			) {
				if(
					pl_table.pl_array[index].pl_address[m] == 
					allowed_characters_in_ip_v4_address[n]
				) {
					ip_v4_address_value_string[digit_count++] = 
						pl_table.pl_array[index].pl_address[m]
					;
					if(
						digit_count > 
						PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DIGITS_IN_ADDRESS_VALUE
					) { 
						goto pl_open_check_ip_v4_address_error; 
					}
					goto pl_open_check_ip_v4_address_next;
				}
			} // for n
			goto pl_open_check_ip_v4_address_error;
		}
pl_open_check_ip_v4_address_next:
		;
	} // for m

	//-------------------------------------------------------------------------
	// check if after the last dot (.) we have at least one digit as this 
	// cannot be trapped in the loop above.
	//-------------------------------------------------------------------------
	if(digit_count == 0) { 
		goto pl_open_check_ip_v4_address_error; 
	}

	//-------------------------------------------------------------------------
	// check ip address string has three (3) dots (.)
	//-------------------------------------------------------------------------
	if(
		dot_count != 
		PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DOT_CHARACTERS_IN_ADDRESS
	) { 
		goto pl_open_check_ip_v4_address_error; 
	}

	//-------------------------------------------------------------------------
	// check fouth number's range
	//-------------------------------------------------------------------------
	ip_v4_address_value_string[
		PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE
	] = '\0';
	value = atoi(ip_v4_address_value_string);
	
	//-------------------------------------------------------------------------
	// This is the fourth address value (xxx.xxx.xxx.nnn).
	// Check the fourth address value based on the class assigned using the 
	// first address value.
	//-------------------------------------------------------------------------
	switch(ip_v4_class) {
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		default:

			//-----------------------------------------------------------------
			// Invalid second address value.
			//-----------------------------------------------------------------
			goto pl_open_check_ip_v4_address_error;
	} // switch
	goto pl_open_check_ip_v4_address_ok;
pl_open_check_ip_v4_address_error:
	pl_last_error = PL_FILESYSTEM_LESS_INVALID_IPV4_ADDRESS;
	goto pl_open_return;
pl_open_check_ip_v4_address_ok:
	;
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_PL_PORT environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	bytes_left_in_buffer = sizeof(pl_table.pl_array[index].pl_port);
	eno_ret = _dupenv_s(
		&env_port,
		&length,
		PL_DEFAULT_PL_PORT_ENVAR_NAME
	);
	if(bytes_left_in_buffer < length) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_return;
	}
	if(
		(eno_ret != 0) ||
		(length == 0)
	) {
		strncpy_s(
			pl_table.pl_array[index].pl_port,
			bytes_left_in_buffer,
			PL_DEFAULT_PL_AGENT_PL_PORT,
			_TRUNCATE
		);
		length = strlen(pl_table.pl_array[index].pl_port);
	} else {
		strncpy_s(
			pl_table.pl_array[index].pl_port,
			bytes_left_in_buffer,
			env_port,
			_TRUNCATE
		);
		free(env_port);
		env_port = NULL;
	}
	bytes_left_in_buffer -= length;
	if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Check the validity of the port.
	// Note:
	//    Valid port number is in the 1-65535 range
	//    PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE
	//    PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE
	//-------------------------------------------------------------------------
	digit_count = 0;
	for(m = 0; m < (int)length; m++) {
		for(
			n = 0; 
			n < PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS_COUNT; 
			n++
		) {
			if(
				pl_table.pl_array[index].pl_port[m] == 
				allowed_characters_in_port[n]
			) {
				port_value_string[digit_count++] = 
					pl_table.pl_array[index].pl_port[m]
				;
				if(
					digit_count > 
					PL_EXTRA_INPUT_CHECKS_PORT_MAX_DIGITS_IN_PORT_VALUE
				) { 
					goto pl_open_check_port_error; 
				}
				goto pl_open_check_port_next;
			}
		} // for n
		goto pl_open_check_port_error;
pl_open_check_port_next:
		;
	} // for m

	//-------------------------------------------------------------------------
	// Check port value range.
	//-------------------------------------------------------------------------
	port_value_string[
		PL_EXTRA_INPUT_CHECKS_PORT_BUFFER_LAST_BYTE
	] = '\0';
	value = atoi(port_value_string);
	if(
		(value < PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE) || 
		(value > PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE)
	) {
		goto pl_open_check_port_error;
	}
	goto pl_open_check_port_ok;
pl_open_check_port_error:
	pl_last_error = PL_FILESYSTEM_LESS_INVALID_PORT;
	goto pl_open_return;
pl_open_check_port_ok:
	;
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Initialize address data.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_table.pl_array[index].address_info_hint, 
		sizeof(pl_table.pl_array[index].address_info_hint)
	);
	pl_table.pl_array[index].address_info_hint.ai_family = 
		PL_ADDRESS_INFO_HINT_AI_FAMILY
	;
	pl_table.pl_array[index].address_info_hint.ai_socktype = 
		PL_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	pl_table.pl_array[index].address_info_hint.ai_protocol = 
		PL_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	pl_table.pl_array[index].address_info_hint.ai_flags = 
		PL_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve agent address and port.
	//-------------------------------------------------------------------------
	ret = getaddrinfo(
		pl_table.pl_array[index].pl_address,
		pl_table.pl_array[index].pl_port, 
		&pl_table.pl_array[index].address_info_hint, 
		&pl_table.pl_array[index].address_info
	);
	if(ret != 0) { 
		pl_last_error = 
			PL_FILESYSTEM_LESS_NETWORK_ADDRESS_RESOLUTION_FAILED
		;
		goto pl_open_return;
	}

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_OPEN command.
	//-------------------------------------------------------------------------
	// pl_open()
	// +-----------+-----------+-----------+------------+--     --+---------------+
	// | OPERATION | COUNTERS  |  <string> | <string>   |         | <string>      |
	// | CODE      | COUNT (N) | APP NAME  | COUNTER 0  |   ...   | COUNTER (N-1) |
	// |           |           |           | NAME       |         | NAME          |
	// +---------- +-----------+-----------+------------+--     --+---------------+
	// ^           ^ (LSB-MSB) ^           
	// |           |           |           
	// |<--- A --->|<--- B --->|<--- C ---> <--------------- D ------------------>
	// |           |           |
	// |           |           |
	// |           |           +--- PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX
	// |           +--------------- PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX
	// +--------------------------- PL_PROTOCOL_PL_OPEN_INPUT_OPCODE_INDEX 
	//
	// Note:
	//    A = PL_PROTOCOL_OPCODE_SIZE
	//    B = PL_PROTOCOL_COUNTERS_COUNT_SIZE
	//    C = variable = (PL_PROTOCOL_SIZET_SIZE + characters count)
	//    D = variable = PL_PROTOCOL_COUNTERS_COUNT_SIZE * 
	//                   (PL_PROTOCOL_SIZET_SIZE + characters count)
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_OPEN_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_OPEN;
	memcpy(
		&message[PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX],
		&pl_counters_count,
		PL_PROTOCOL_UINT_SIZE
	);
	if(pl_application_name != NULL) {
		p_string = pl_application_name;
	} else {
		p_string = PL_INI_ANONYMOUS_APPLICATION_NAME;
	}
	length = strlen(p_string);
	message_size = (PL_PROTOCOL_SIZET)length;
	memcpy(
		&message[PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	sprintf(
		&message[
			PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX + 
			PL_PROTOCOL_SIZET_SIZE
		],
		"%s",
		p_string
	);
	p_string = &message[
		PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX + 
		PL_PROTOCOL_SIZET_SIZE +
		length
	];
	bytes_to_send = 
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_COUNTERS_COUNT_SIZE +
		PL_PROTOCOL_SIZET_SIZE +
		length
	;
	for(j = 0; j < pl_counters_count; j++) {
		if(pl_counters_names[j] != NULL) {
			pp_string = pl_counters_names[j];
		} else {
			pp_string = buffer;
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				"%s%d",
				PL_INI_GENERIC_COUNTER_NAME,
				j
			);
		}
		length = strlen(pp_string);
		message_size = (PL_PROTOCOL_SIZET)length;
		memcpy(
			p_string,
			&message_size,
			PL_PROTOCOL_SIZET_SIZE
		);
		sprintf(
			p_string + PL_PROTOCOL_SIZET_SIZE,
			"%s",
			pp_string
		);
		p_string += length + PL_PROTOCOL_SIZET_SIZE;
		bytes_to_send += 
			PL_PROTOCOL_SIZET_SIZE +
			length
		;
	} // for j
	*p_string = PL_PROTOCOL_EOR;
	bytes_to_send = (
		p_string - 
		pl_output_buffer
	);
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_open_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[index].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_socket = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(pl_socket == INVALID_SOCKET) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_socket,
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_socket,
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = closesocket(
				pl_socket
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_open_unlock_table;
			}
			continue;
		}
		goto pl_open_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on WSAEADDRINUSE:
	//    If you call pl_write at a too high frequency, you may exhaust the
	//    short lived TCP ports.  The default range of short lived ports is 
	//    from 1025 to 5000. Ways to workaround are to increase the dynamic port 
	//    range (to 65534) by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\MaxUserPort;
	//    or by reducing TIME_WAIT from the default 240s (4 minutes) to 30s
	//    by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\TCPTimedWaitDelay
	//-------------------------------------------------------------------------
	dwret = GetLastError();
	if(dwret == WSAEADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_open_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_open_unlock_table;

pl_open_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_OPEN command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_socket,
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_open_unlock_table;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer
	//-------------------------------------------------------------------------
	// pl_open() return
	// +----------+-----------+----------+
	// | STATUS   | UUID      | PLD      |
	// | CODE     |           |          |
	// +----------+-----------+----------+ <-- PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX
	// ^          ^ (LSB-MSB) ^ (LSB-MSB)
	// |          |           |
	// |<-- A --->|<--- B --->|<-- C --->
	// |          |           |
	// |          |           +---- PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX
	// |          +---------------- PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX
	// +--------------------------- PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_input_buffer, 
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_open_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (PL_PROTOCOL_SIZET)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_open_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close PL socket.
	//-------------------------------------------------------------------------
	ret = closesocket(
		pl_socket
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_open_unlock_table;
	}
	pl_socket = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Extract agent's answer.
	//-------------------------------------------------------------------------
	memcpy(
		puuid,
		&pl_input_buffer[PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX],
		PL_PROTOCOL_UUID_SIZE
	 );
	memcpy(
		&pl_table.pl_array[index].uuid,
		puuid,
		PL_PROTOCOL_UUID_SIZE
	 );
	memcpy(
		&pl_table.pl_array[index].remote_pld,
		&pl_input_buffer[PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX],
		PL_PROTOCOL_PLD_SIZE
	);

	//-------------------------------------------------------------------------
	// Create counters semaphores, initialize counters write cache and socket.
	// Note:
	//    index points to the free slot found in the pl_table
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_counters_count; j++) { 
		pl_table.pl_array[index].pl_counter_handles_semaphores[j] = 
			CreateSemaphore(
				NULL, 
				(LONG)1, 
				(LONG)1, 
				NULL
			);
		if(
			pl_table.pl_array[index].pl_counter_handles_semaphores[j] == 
			NULL
		) {
			pl_last_error = PL_COUNTER_SEMAPHORE_CREATION_FAILED;
			goto pl_open_unlock_table;
		}
		pl_table.pl_array[index].pl_write_cache[j] = PL_MAX_COUNTER_VALUE - 1;
		pl_table.pl_array[index].pl_counter_sockets[j] = INVALID_SOCKET;
	} // for j
	pl_table.pl_array[index].pl_counters_count = pl_counters_count;
#else // __PL_FILESYSTEM_LESS__

		//---------------------------------------------------------------------
		// In file system mode of operation, the pl_open API call is carried-
		// out locally using the PL_FOLDER.
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		// Check if the PL_FOLDER folder exist.
		//---------------------------------------------------------------------
		dw_ret = GetFileAttributes((LPCWSTR)PL_FOLDER);
		if(dw_ret == INVALID_FILE_ATTRIBUTES) {
			dw_ret = GetLastError();
			if(dw_ret == ERROR_FILE_NOT_FOUND) {
				pl_last_error = PL_MISSING_DIRECTORY;
			} else {
				pl_last_error = PL_CRITICAL_FAILURE;
			}
			goto pl_open_return;
		}
		if((dw_ret & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			pl_last_error = PL_NOT_A_DIRECTORY;
			goto pl_open_return;
		}
		pl_table_initialized = TRUE;
	} // if pl_table_initialized == FALSE

	//-------------------------------------------------------------------------
	// Lock the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
	dw_ret = WaitForSingleObject(
		pl_table.semaphore, 
		INFINITE
	);
	if(dw_ret != WAIT_OBJECT_0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_open_return;
	}
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < PL_MAX_PRODUCTIVITY_LINKS; index++) {
		if(pl_table.pl_array[index].pl_in_use == FALSE) {
			goto pl_open_found;
		}
	}
	// pl_table full
	pl_last_error = PL_DESCRIPTOR_TABLE_FULL;
	goto pl_open_unlock_table;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < pl_max_productivity_links; index++) {
		if(pl_table.pl_array[index].pl_in_use == FALSE) {
			goto pl_open_found;
		}
	}

	//-------------------------------------------------------------------------
	// No room in the table, lets double dynamically the pl_table size and
	// create the additional counters.
	//-------------------------------------------------------------------------
	pl_old_max_productivity_links = pl_max_productivity_links; 
	pl_max_productivity_links *= 2;
	pl_table.pl_array = (PPRODUCTIVITY_LINK)realloc(
		pl_table.pl_array, 
		sizeof(PRODUCTIVITY_LINK) * pl_max_productivity_links
	);
	if(pl_table.pl_array == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		&pl_table.pl_array[index], 
		sizeof(PRODUCTIVITY_LINK) * pl_old_max_productivity_links
	); // clear newly allocated memory
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
pl_open_found:
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Allocate memory for the write cache.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(unsigned long long) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_write_cache = 
		(unsigned long long *)malloc(memory_size);
	if(pl_table.pl_array[index].pl_write_cache == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_write_cache, 
		memory_size
	);
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate timestamps memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(time_t) * 
		pl_counters_count
	;
	pl_table.pl_array[index].open_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].open_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].open_time, 
		memory_size
	);
	pl_table.pl_array[index].last_attach_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_attach_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_attach_time, 
		memory_size
	);
	pl_table.pl_array[index].last_read_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_read_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_read_time, 
		memory_size
	);
	pl_table.pl_array[index].last_write_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_write_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_write_time, 
		memory_size
	);
	pl_table.pl_array[index].last_close_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_close_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_close_time, 
		memory_size
	);
#endif // __PL_TIMESTAMPING__
	memory_size = 
		sizeof(HANDLE) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles = 
		(HANDLE *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_handles == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_counter_handles, 
		memory_size
	);

	//-------------------------------------------------------------------------
	// Allocate semaphore memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(HANDLE) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(HANDLE *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_handles_semaphores == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles);
		pl_table.pl_array[index].pl_counter_handles = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_counter_handles_semaphores, 
		memory_size
	);
	pl_table.pl_array[index].pl_counters_count = 0;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	pl_table.pl_array[index].pl_in_use = TRUE;

	//-------------------------------------------------------------------------
	// Generate the uuid for the new productivity link.
	//-------------------------------------------------------------------------
#ifndef __PL_CONSTANT_UUID__
	rpc_ret = UuidCreate(puuid);
	if(rpc_ret != RPC_S_OK) {
		if(rpc_ret == RPC_S_UUID_LOCAL_ONLY) {
			pl_last_error = PL_NON_GLOBAL_UUID_DESCRIPTOR;
			goto pl_open_unlock_table;
		}
		if(rpc_ret == RPC_S_UUID_NO_ADDRESS) {
			pl_last_error = PL_NON_GLOBAL_UUID_DESCRIPTOR_NO_ADDRESS;
			goto pl_open_unlock_table;
		}
		pl_last_error = PL_GLOBAL_UUID_DESCRIPTOR_CREATION_FAILED;
		goto pl_open_unlock_table;
	}
	memcpy(
		&pl_table.pl_array[index].uuid,
		puuid,
		PL_UUID_SIZE
	 );
#else // !__PL_CONSTANT_UUID__
	ZeroMemory(
		puuid, 
		sizeof(uuid_t)
	); 
#endif // !__PL_CONSTANT_UUID__

	//-------------------------------------------------------------------------
	// Sample pl_config.ini file (generated by esrv).
	//-------------------------------------------------------------------------
	// esrv
	// 76a145e6-6ea4-47ad-a783-60821b353236
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236 (Note: terminal back slash removed for GCC warning)
	// 63
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (Joule)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (Joule).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (kWh)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (kWh).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy Overflows (no unit)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Update Frequency (second)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Channel(s)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Status
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Version
	// 2010.01.18.(W)
	// _DEBUG
	// _UNICODE
	// UNICODE
	// __PL_DYNAMIC_COUNTERS_ALLOCATION__
	// __PL_WINDOWS__
	// __PL_GENERATE_INI__
	// __PL_GENERATE_INI_VERSION_TAGGING__
	// __PL_GENERATE_INI_BUILD_TAGGING__
	// __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	// __PL_BLOCKING_COUNTER_FILE_LOCK__
	// PL created on Wed Jul 21 12:26:14 2010
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Create the PL_FOLDER/application_name_uuid/ folder.
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_root, 
		sizeof(pl_root)
	);
	ZeroMemory(
		pl_path, 
		sizeof(pl_path)
	);
	rpc_ret = UuidToString(
		puuid, 
		&p
	);
	if(rpc_ret != RPC_S_OK) {
		if(rpc_ret == RPC_S_OUT_OF_MEMORY) {
			pl_last_error = PL_GLOBAL_UUID_DESCRIPTOR_CREATION_FAILED;
			goto pl_open_unlock_table;
		}
		pl_last_error = PL_GLOBAL_UUID_DESCRIPTOR_TO_STRING_FAILED;
		goto pl_open_unlock_table;
	}
	if(p == NULL) {
		pl_last_error = PL_CRITICAL_FAILURE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// pl_path = c:/productivity_link
	//-------------------------------------------------------------------------
	_tcsncpy_s(
		pl_path, 
		PL_MAX_PATH, 
		PL_FOLDER, 
		_TRUNCATE
	);

	//-------------------------------------------------------------------------
	// pl_path = c:/productivity_link/
	//-------------------------------------------------------------------------
	_tcsncat_s(
		pl_path, 
		PL_MAX_PATH, 
		PL_PATH_SEPARATOR, 
		sizeof(PL_PATH_SEPARATOR)
	); 
	if(pl_application_name != NULL) {
		ZeroMemory(
			pl_buffer, 
			sizeof(pl_buffer)
		);
		mbstowcs_s(
			&st_ret, 
			pl_buffer, 
			strlen(pl_application_name) + 1, 
			pl_application_name, 
			_TRUNCATE
		);

		//---------------------------------------------------------------------
		// pl_path = c:/productivity_link/<application_name>
		//---------------------------------------------------------------------
		_tcsncat_s(
			pl_path, 
			PL_MAX_PATH, 
			pl_buffer, 
			_TRUNCATE
		); 
	} else {

		//---------------------------------------------------------------------
		// pl_path = c:/productivity_link/<anonymous>
		//---------------------------------------------------------------------
		_tcsncat_s(
			pl_path, 
			PL_MAX_PATH, 
			PL_ANONYMOUS_APPLICATION_NAME, 
			_TRUNCATE
		);
	}

	//-------------------------------------------------------------------------
	// pl_path = c:/productivity_link/<x>_
	//-------------------------------------------------------------------------
	_tcsncat_s(
		pl_path, 
		PL_MAX_PATH, 
		PL_APPLICATION_NAME_SEPARATOR, 
		sizeof(PL_APPLICATION_NAME_SEPARATOR)
	);

	//-------------------------------------------------------------------------
	// pl_path = c:/productivity_link/<x>_<uuid>
	//-------------------------------------------------------------------------
	_tcsncat_s(
		pl_path, 
		PL_MAX_PATH, 
		p, 
		_tcslen(p)
	);

	//-------------------------------------------------------------------------
	// pl_root = c:/productivity_link/<x>_<uuid>
	//-------------------------------------------------------------------------
	_tcsncpy_s(
		pl_root, 
		PL_MAX_PATH, 
		pl_path, 
		_tcslen(pl_path)
	); 

	//-------------------------------------------------------------------------
	// pl_root = c:/productivity_link/<x>_<uuid>/
	//-------------------------------------------------------------------------
	_tcsncat_s(
		pl_root, 
		PL_MAX_PATH, 
		PL_PATH_SEPARATOR, 
		sizeof(PL_PATH_SEPARATOR)
	);

	//-------------------------------------------------------------------------
	// Create pl_root (c:/productivity_link/<x>_<uuid>/) directory
	//-------------------------------------------------------------------------
	b_ret = CreateDirectory(
		pl_path, 
		NULL
	);
	if(b_ret == FALSE) {
		dw_ret = GetLastError();
		if(dw_ret == ERROR_ALREADY_EXISTS) {
			pl_last_error = PL_DIRECTORY_ALREADY_EXISTS;
			goto pl_open_unlock_table;
		}
		if(dw_ret == ERROR_PATH_NOT_FOUND) {
			pl_last_error = PL_PATH_NOT_FOUND;
			goto pl_open_unlock_table;
		}
		pl_last_error = PL_DIRECTORY_CREATION_FAILED;
		goto pl_open_unlock_table;
 	}

	//-------------------------------------------------------------------------
	// Create the counter files in c:/productivity_link/<x>_<uuid>/, the 
	// associated semaphores and write cache.
	// Note:
	//    index points to the free slot found in pl_table
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_counters_count; j++) {

		//---------------------------------------------------------------------
		// Clear working buffers.
		//---------------------------------------------------------------------
		ZeroMemory(
			pl_path, 
			sizeof(pl_path)
		);
		ZeroMemory(
			pl_buffer, 
			sizeof(pl_buffer)
		);

		//---------------------------------------------------------------------
		// Create jth counter name <y>.
		//---------------------------------------------------------------------
		if(pl_counters_names[j] != NULL) {

			//-----------------------------------------------------------------
			// User provided counter name.
			// pl_buffer = <counter>
			//-----------------------------------------------------------------
			mbstowcs_s(
				&st_ret, 
				pl_buffer, 
				strlen(pl_counters_names[j]) + 1, 
				pl_counters_names[j], 
				_TRUNCATE
			);

		} else {

			//-----------------------------------------------------------------
			// Anonymous counter.
			// pl_buffer = <anonymous>
			//-----------------------------------------------------------------
			_tcsncat_s(
				pl_buffer, 
				PL_MAX_PATH, 
				PL_GENERIC_COUNTER_NAME, 
				_tcslen(PL_GENERIC_COUNTER_NAME)
			);

			//-----------------------------------------------------------------
			// Append counter rank for anonymous counter.
			// pl_buffer = <anonymous>
			// pl_cvt_buffer = <n>
			// Note:
			//    Max value for unsigned int is 4,294,967,295
			//-----------------------------------------------------------------
			ZeroMemory(
				pl_cvt_buffer, 
				sizeof(pl_cvt_buffer)
			);
			_itot_s(
				j, 
				pl_cvt_buffer, 
				PL_MAX_BUFFER_SIZE, 
				PL_COUNTER_NAME_BASE
			);
			_tcsncat_s(
				pl_buffer, 
				PL_MAX_PATH, 
				pl_cvt_buffer, 
				_tcslen(pl_cvt_buffer)
			);
		}
		_tcsncpy_s(
			pl_path, 
			PL_MAX_PATH, 
			pl_root, 
			_tcslen(pl_root)
		);
		_tcsncat_s(
			pl_path, 
			PL_MAX_PATH, 
			pl_buffer, 
			_tcslen(pl_buffer)
		);

		//---------------------------------------------------------------------
		// Open counter.
		//---------------------------------------------------------------------
		pl_table.pl_array[index].pl_counter_handles[j] = 
			CreateFile(
				pl_path, 
				GENERIC_READ | GENERIC_WRITE, 
				FILE_SHARE_READ | FILE_SHARE_WRITE, 
				NULL, 
				CREATE_ALWAYS, 
				FILE_ATTRIBUTE_NORMAL, 
				SECURITY_ANONYMOUS
			);
		if(
			pl_table.pl_array[index].pl_counter_handles[j] == 
			INVALID_HANDLE_VALUE
		) {
			pl_last_error = PL_COUNTER_CREATION_FAILED;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// Create counter semaphore.
		//---------------------------------------------------------------------
		pl_table.pl_array[index].pl_counter_handles_semaphores[j] = 
			CreateSemaphore(
				NULL, 
				(LONG)1, 
				(LONG)1, 
				NULL
			);
		if(
			pl_table.pl_array[index].pl_counter_handles_semaphores[j] == 
			NULL
		) {
			pl_last_error = PL_COUNTER_SEMAPHORE_CREATION_FAILED;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// Set default cache value.
		//---------------------------------------------------------------------
		pl_table.pl_array[index].pl_write_cache[j] = 
			PL_MAX_COUNTER_VALUE - 1
		;
	} // for j
	pl_table.pl_array[index].pl_counters_count = pl_counters_count;
#ifdef __PL_GENERATE_INI__

	//-------------------------------------------------------------------------
	// Write the productivity link configuration file in /PL_FOLDER/puuid/ - 
	// required to attach.
	//-------------------------------------------------------------------------
	// file structure:
	//
	// 001: application name
	// 002: uuid
	// 003: path to uuid (full path)
	// 004: counters count (N)
	// 005: counter 1 (full path name)
	// ...
	// 00x: counter n (full path name)
	// if __PL_GENERATE_INI_VERSION_TAGGING__
	//    00x + 1: version tag
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// create the productivity link configuration file.
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_path, 
		sizeof(pl_path)
	);

	//-------------------------------------------------------------------------
	// pl_path = c:/productivity_link/<x>_<uuid>/
	//-------------------------------------------------------------------------
	_tcsncpy_s(
		pl_path, 
		PL_MAX_PATH, 
		pl_root, 
		_tcslen(pl_root)
	);

	//-------------------------------------------------------------------------
	// pl_path = c:/productivity_link/<x>_<uuid>/pl_config.ini
	//-------------------------------------------------------------------------
	_tcsncat_s(
		pl_path, 
		PL_MAX_PATH, 
		PL_CONFIG_FILE_NAME, 
		_tcslen(PL_CONFIG_FILE_NAME)
	);

	//-------------------------------------------------------------------------
	// Open config file (pl_path)
	//-------------------------------------------------------------------------
	pl_config_file = CreateFile(
		pl_path, 
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		SECURITY_ANONYMOUS
	);
	if(pl_config_file == INVALID_HANDLE_VALUE) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Write the configuration data into the productivity link configuration 
	// file.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// 001: write application name.
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	if(pl_application_name != NULL) {
		strncpy_s(
			pl_ini_buffer, 
			strlen(pl_application_name) + 1, 
			pl_application_name, 
			_TRUNCATE
		);
	} else {
		strncpy_s(
			pl_ini_buffer, 
			strlen(PL_INI_ANONYMOUS_APPLICATION_NAME), 
			PL_INI_ANONYMOUS_APPLICATION_NAME, 
			_TRUNCATE
		);
	}
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)(strlen(pl_ini_buffer));
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// 002: write uuid.
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	wcstombs_s(
		&st_ret, 
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		p, 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)(strlen(pl_ini_buffer));
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// 003: write path to uuids (full path).
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	wcstombs_s(
		&st_ret, 
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_root, 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)(strlen(pl_ini_buffer));
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// 004: write counters count (N).
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	_itoa_s(
		pl_counters_count, 
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		PL_COUNTER_NAME_BASE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)(strlen(pl_ini_buffer));
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Write each counter.
	// 005: counter 1 (full path name)
	// ...
	// 00x: counter n (full path name)
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_counters_count; j++) {
		ZeroMemory(
			pl_ini_buffer, 
			sizeof(pl_ini_buffer)
		);
		ZeroMemory(
			pl_ini_path, 
			sizeof(pl_ini_path)
		);
		if(pl_counters_names[j] != NULL) {
			strncpy_s(
				pl_ini_buffer, 
				strlen(pl_counters_names[j]) + 1, 
				pl_counters_names[j], 
				_TRUNCATE
			);
		} else {
			strncpy_s(
				pl_ini_buffer, 
				strlen(PL_INI_GENERIC_COUNTER_NAME) + 1, 
				PL_INI_GENERIC_COUNTER_NAME, 
				_TRUNCATE
			);
			ZeroMemory(
				pl_ini_cvt_buffer, 
				sizeof(pl_ini_cvt_buffer)
			);
			_itoa_s(
				j, 
				pl_ini_cvt_buffer, 
				PL_MAX_BUFFER_SIZE, 
				PL_COUNTER_NAME_BASE
			);
			strncat_s(
				pl_ini_buffer, 
				sizeof(pl_ini_buffer), 
				pl_ini_cvt_buffer, 
				sizeof(pl_ini_cvt_buffer)
			);
		}
		wcstombs_s(
			&st_ret, 
			pl_ini_path, 
			sizeof(pl_ini_path), 
			pl_root, 
			_TRUNCATE
		);
		strncat_s(
			pl_ini_path, 
			sizeof(pl_ini_path), 
			pl_ini_buffer, 
			sizeof(pl_ini_buffer)
		);
		strncat_s(
			pl_ini_path, 
			sizeof(pl_ini_path), 
			pl_eol_buffer, 
			sizeof(pl_eol_buffer)
		);
		pl_config_file_bytes_to_write = (DWORD)(strlen(pl_ini_path));
		b_ret = WriteFile(
			pl_config_file, 
			pl_ini_path, 
			pl_config_file_bytes_to_write, 
			&pl_config_file_bytes_written, 
			NULL
		);
		if(b_ret == FALSE) {
			pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
			goto pl_open_unlock_table;
		}
	} // for j

/*
 @@@@@   @@    @@@@   @@@@
   @    @  @  @    @ @    @
   @   @    @ @      @
   @   @    @ @       @@@@
   @   @@@@@@ @  @@@      @
   @   @    @ @    @      @
   @   @    @  @@@@  @@@@@
*/
#ifdef __PL_GENERATE_INI_VERSION_TAGGING__
	
	//-------------------------------------------------------------------------
	// Tag the productivity link configuration file with version information.
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(PL_VERSION_TAG) + 1, 
		PL_VERSION_TAG, 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}
#endif // __PL_GENERATE_INI_VERSION_TAGGING__
#ifdef __PL_GENERATE_INI_BUILD_TAGGING__
	
	//-------------------------------------------------------------------------
	// Tag the productivity link configuration file with build information.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Generic build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef _DEBUG

	//-------------------------------------------------------------------------
	// _DEBUG
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[DEBUG_INDEX]) + 1, 
		pl_build_tags[DEBUG_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _DEBUG
#ifdef _RELEASE

	//-------------------------------------------------------------------------
	// _RELEASE
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[RELEASE_INDEX]) + 1, 
		pl_build_tags[RELEASE_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _RELEASE
#ifdef _CONSOLE

	//-------------------------------------------------------------------------
	// _CONSOLE
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[CONSOLE_INDEX]) + 1, 
		pl_build_tags[CONSOLE_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _CONSOLE
#ifdef _UNICODE

	//-------------------------------------------------------------------------
	// _UNICODE
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[_UNICODE_INDEX]) + 1, 
		pl_build_tags[_UNICODE_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _UNICODE
#ifdef UNICODE

	//-------------------------------------------------------------------------
	// UNICODE
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[UNICODE_INDEX]) + 1, 
		pl_build_tags[UNICODE_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // UNICODE
#ifdef _ATL_STATIC_REGISTRY

	//-------------------------------------------------------------------------
	// _ATL_STATIC_REGISTRY
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[ATL_STATIC_REGISTRY_INDEX]) + 1, 
		pl_build_tags[ATL_STATIC_REGISTRY_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _ATL_STATIC_REGISTRY
#ifdef __PL_LITTLE_ENDIAN__

	//-------------------------------------------------------------------------
	// __PL_LITTLE_ENDIAN__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_LITTLE_ENDIAN_INDEX]) + 1, 
		pl_build_tags[PL_LITTLE_ENDIAN_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_LITTLE_ENDIAN__
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// __PL_DYNAMIC_COUNTERS_ALLOCATION__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_DYNAMIC_COUNTERS_ALLOCATION_INDEX]) + 1, 
		pl_build_tags[PL_DYNAMIC_COUNTERS_ALLOCATION_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// __PL_EXTRA_INPUT_CHECKS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_EXTRA_INPUT_CHECKS_INDEX]) + 1, 
		pl_build_tags[PL_EXTRA_INPUT_CHECKS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_EXTRA_INPUT_CHECKS__
#ifdef __PL_AGENT__

	//-------------------------------------------------------------------------
	// __PL_AGENT__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_AGENT_INDEX]) + 1, 
		pl_build_tags[PL_AGENT_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_AGENT__
#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// __PL_FILESYSTEM_LESS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_FILESYSTEM_LESS_INDEX]) + 1, 
		pl_build_tags[PL_FILESYSTEM_LESS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// OS build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// __PL_WINDOWS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_WINDOWS_INDEX]) + 1, 
		pl_build_tags[PL_WINDOWS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_WINDOWS__
#ifdef __PL_LINUX__

	//-------------------------------------------------------------------------
	// __PL_LINUX__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_LINUX_INDEX]) + 1, 
		pl_build_tags[PL_LINUX_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_LINUX__
#ifdef __PL_SOLARIS__

	//-------------------------------------------------------------------------
	// __PL_SOLARIS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_SOLARIS_INDEX]) + 1, 
		pl_build_tags[PL_SOLARIS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_SOLARIS__
#ifdef __PL_MACOSX__

	//-------------------------------------------------------------------------
	// __PL_MACOSX__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
#ifdef __PL_IOS__
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_IOS_INDEX]) + 1, 
		pl_build_tags[PL_IOS_INDEX], 
		_TRUNCATE
	);
#else // __PL_IOS__
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_MACOSX_INDEX]) + 1, 
		pl_build_tags[PL_MACOSX_INDEX], 
		_TRUNCATE
	);
#endif // __PL_IOS__
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Dynamic library build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef _WINDLL

	//-------------------------------------------------------------------------
	// _WINDLL
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[WINDLL_INDEX]) + 1, 
		pl_build_tags[WINDLL_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _WINDLL
#ifdef _USRDLL

	//-------------------------------------------------------------------------
	// _USRDLL
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[USRDLL_INDEX]) + 1, 
		pl_build_tags[USRDLL_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _USRDLL
#ifdef __PL_WINDOWS_DLL_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_WINDOWS_DLL_EXPORTS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_WINDOWS_DLL_EXPORTS_INDEX]) + 1, 
		pl_build_tags[PL_WINDOWS_DLL_EXPORTS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_WINDOWS_DLL_EXPORTS__
#ifdef __PL_LINUX_SO_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_LINUX_SO_EXPORTS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_LINUX_SO_EXPORTS_INDEX]) + 1, 
		pl_build_tags[PL_LINUX_SO_EXPORTS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_LINUX_SO_EXPORTS__
#ifdef __PL_SOLARIS_SO_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_SOLARIS_SO_EXPORTS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_SOLARIS_SO_EXPORTS_INDEX]) + 1, 
		pl_build_tags[PL_SOLARIS_SO_EXPORTS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_SOLARIS_SO_EXPORTS__
#ifdef __PL_MACOSX_SO_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_MACOSX_SO_EXPORTS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_MACOSX_SO_EXPORTS_INDEX]) + 1, 
		pl_build_tags[PL_MACOSX_SO_EXPORTS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_MACOSX_SO_EXPORTS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_JNI_EXPORTS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_JNI_EXPORTS_INDEX]) + 1, 
		pl_build_tags[PL_JNI_EXPORTS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// PL functional build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef __PL_BYPASS__

	//-------------------------------------------------------------------------
	// __PL_BYPASS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_BYPASS_INDEX]) + 1, 
		pl_build_tags[PL_BYPASS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_BYPASS__
#ifdef __PL_GENERATE_INI__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_GENERATE_INI_INDEX]) + 1, 
		pl_build_tags[PL_GENERATE_INI_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI__
#ifdef __PL_GENERATE_INI_VERSION_TAGGING__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI_VERSION_TAGGING__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_GENERATE_INI_VERSION_TAGGING_INDEX]) + 1, 
		pl_build_tags[PL_GENERATE_INI_VERSION_TAGGING_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI_VERSION_TAGGING__
#ifdef __PL_GENERATE_INI_BUILD_TAGGING__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI_BUILD_TAGGING__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_GENERATE_INI_BUILD_TAGGING_INDEX]) + 1, 
		pl_build_tags[PL_GENERATE_INI_BUILD_TAGGING_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI_BUILD_TAGGING__
#ifdef __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_GENERATE_INI_DATE_AND_TIME_TAGGING_INDEX]) + 1, 
		pl_build_tags[PL_GENERATE_INI_DATE_AND_TIME_TAGGING_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__

	//-------------------------------------------------------------------------
	// __PL_BLOCKING_COUNTER_FILE_LOCK__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_BLOCKING_COUNTER_FILE_LOCK_INDEX]) + 1, 
		pl_build_tags[PL_BLOCKING_COUNTER_FILE_LOCK_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
#ifdef __PL_ATTACH_SCRIPT_SUPPORT__

	//-------------------------------------------------------------------------
	// __PL_ATTACH_SCRIPT_SUPPORT__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_ATTACH_SCRIPT_SUPPORT_INDEX]) + 1, 
		pl_build_tags[PL_ATTACH_SCRIPT_SUPPORT_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_ATTACH_SCRIPT_SUPPORT__
#ifdef __PL_UNDEF_T__

	//-------------------------------------------------------------------------
	// __PL_UNDEF_T__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_UNDEF_T_INDEX]) + 1, 
		pl_build_tags[PL_UNDEF_T_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_UNDEF_T__
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// __PL_TIMESTAMPING__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_TIMESTAMPING_INDEX]) + 1, 
		pl_build_tags[PL_TIMESTAMPING_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_TIMESTAMPING__
#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// __PL_BLOCKING_PL_READ__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_BLOCKING_PL_READ_INDEX]) + 1, 
		pl_build_tags[PL_BLOCKING_PL_READ_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// PL configuration reporting (use forbidden in customer available 
	// software is not allowed) - with __PL_AGENT__ exception.
	//-------------------------------------------------------------------------
#ifdef __PL_CONSTANT_UUID__

	//-------------------------------------------------------------------------
	// __PL_CONSTANT_UUID__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_CONSTANT_UUID_INDEX]) + 1, 
		pl_build_tags[PL_CONSTANT_UUID_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_CONSTANT_UUID__
#ifdef __PL_BINARY_COUNTER__

	//-------------------------------------------------------------------------
	// __PL_BINARY_COUNTER__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_BINARY_COUNTER_INDEX]) + 1, 
		pl_build_tags[PL_BINARY_COUNTER_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_BINARY_COUNTER__
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// __PL_DYNAMIC_TABLE_ALLOCATION__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
#ifdef __PL_AGENT__
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_DYNAMIC_TABLE_ALLOCATION_PL_AGENT_INDEX]) + 1, 
		pl_build_tags[PL_DYNAMIC_TABLE_ALLOCATION_PL_AGENT_INDEX], 
		_TRUNCATE
	);
#else // __PL_AGENT__
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_DYNAMIC_TABLE_ALLOCATION_INDEX]) + 1, 
		pl_build_tags[PL_DYNAMIC_TABLE_ALLOCATION_INDEX], 
		_TRUNCATE
	);
#endif // __PL_AGENT__
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
#ifdef __PL_UNIT_TESTS__

	//-------------------------------------------------------------------------
	// __PL_UNIT_TESTS__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_UNIT_TESTS_INDEX]) + 1, 
		pl_build_tags[PL_UNIT_TESTS_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_UNIT_TESTS__
#ifdef __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// __PL_LOGGER_ONLY__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_LOGGER_ONLY_INDEX]) + 1, 
		pl_build_tags[PL_LOGGER_ONLY_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// Architecture specific build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef __PL_NO_SSE_PAUSE_SUPPORT__

	//-------------------------------------------------------------------------
	// __PL_NO_SSE_PAUSE_SUPPORT__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(pl_build_tags[PL_NO_SSE_PAUSE_SUPPORT_INDEX]) + 1, 
		pl_build_tags[PL_NO_SSE_PAUSE_SUPPORT_INDEX], 
		_TRUNCATE
	);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
#endif // __PL_GENERATE_INI_BUILD_TAGGING__
#ifdef __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer)
	);
	strncpy_s(
		pl_ini_buffer, 
		strlen(PL_DATE_AND_TIME_INI_TAGGING_STRING) + 1, 
		PL_DATE_AND_TIME_INI_TAGGING_STRING, 
		_TRUNCATE
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	time(&pl_ini_time);
	ctime_s(
		&pl_ini_buffer[pl_config_file_bytes_to_write], 
			sizeof(pl_ini_buffer) - 
			(strlen(PL_DATE_AND_TIME_INI_TAGGING_STRING) + 1),
		&pl_ini_time
	);
	pl_config_file_bytes_to_write += (DWORD)strlen(pl_ini_buffer);
	strncat_s(
		pl_ini_buffer, 
		sizeof(pl_ini_buffer), 
		pl_eol_buffer, 
		sizeof(pl_eol_buffer)
	);
	pl_config_file_bytes_to_write = (DWORD)strlen(pl_ini_buffer);
	b_ret = WriteFile(
		pl_config_file, 
		pl_ini_buffer, 
		pl_config_file_bytes_to_write, 
		&pl_config_file_bytes_written, 
		NULL
	);
	if(b_ret == FALSE) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__

	//-------------------------------------------------------------------------
	// Close the productivity link configuration file.
	//-------------------------------------------------------------------------
	b_ret = CloseHandle(pl_config_file);
	if(b_ret == FALSE) {
		pl_last_error = PL_CRITICAL_FAILURE;
	}
#endif // __PL_GENERATE_INI__
#endif // __PL_FILESYSTEM_LESS__

pl_open_unlock_table:

	//-------------------------------------------------------------------------
	// Unlock the productivity link table (locked against other threads).
	//-------------------------------------------------------------------------
	b_ret = ReleaseSemaphore(
		pl_table.semaphore, 
		(LONG)1, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}

	//-------------------------------------------------------------------------
	// House keeping.
	//-------------------------------------------------------------------------
#ifndef __PL_FILESYSTEM_LESS__
	if(p != NULL) {
		rpc_ret = RpcStringFree(&p);
		if(rpc_ret != RPC_S_OK) {
			pl_last_error = PL_CRITICAL_FAILURE;
		}
		p = NULL;
	}
#endif // !__PL_FILESYSTEM_LESS__
pl_open_return:
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Return uuid to jvm. Java is big-endian, define __PL_LITTLE_ENDIAN__ if 
	// little-endian cpu.
	//-------------------------------------------------------------------------
	ZeroMemory(
		uuid_bytes, 
		sizeof(uuid_bytes)
	);
	pbyte = (char *)puuid;
#ifdef __PL_LITTLE_ENDIAN__
	uuid_bytes[0] = pbyte[6];
	uuid_bytes[1] = pbyte[7];
	uuid_bytes[2] = pbyte[4];
	uuid_bytes[3] = pbyte[5];
	uuid_bytes[4] = pbyte[0];
	uuid_bytes[5] = pbyte[1];
	uuid_bytes[6] = pbyte[2];
	uuid_bytes[7] = pbyte[3];
#endif // __PL_LITTLE_ENDIAN__
	(*interface_pointer)->SetLongField(
		interface_pointer, 
		java_puuid, 
		uuid_msb_field_id, 
		*(jlong *)uuid_bytes
	);
#ifdef __PL_LITTLE_ENDIAN__
	uuid_bytes[8]  = pbyte[15];
	uuid_bytes[9]  = pbyte[14];
	uuid_bytes[10] = pbyte[13];
	uuid_bytes[11] = pbyte[12];
	uuid_bytes[12] = pbyte[11];
	uuid_bytes[13] = pbyte[10];
	uuid_bytes[14] = pbyte[9];
	uuid_bytes[15] = pbyte[8];
#endif // __PL_LITTLE_ENDIAN__
	(*interface_pointer)->SetLongField(
		interface_pointer, 
		java_puuid, 
		uuid_lsb_field_id, 
		*(jlong *)(&uuid_bytes[8])
	);

	//-------------------------------------------------------------------------
	// Release java arguments.
	//-------------------------------------------------------------------------
	if(pl_application_name != NULL) {
		(*interface_pointer)->ReleaseStringUTFChars(
			interface_pointer, 
			java_pl_application_name, 
			pl_application_name
		);
	}
	for(i = 0; i < pl_counters_count; i++) {
		if(pl_counters_names[i] != NULL) {
			(*interface_pointer)->ReleaseStringUTFChars(
				interface_pointer, 
				string_object, 
				native_string
			); 
		}
	}
	if(pl_counters_names != NULL) {
		free((void *)pl_counters_names);
	}
	if(puuid != NULL) {
		free((void *)puuid);
	}
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Set last error and return status.
	//-------------------------------------------------------------------------
	if(pl_last_error != PL_NO_ERROR) {
		SetLastError(pl_last_error);
		return(PL_INVALID_DESCRIPTOR);
	} else {
		pl_last_error = PL_NO_ERROR;
		SetLastError(pl_last_error);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

	//-------------------------------------------------------------------------
	//   @    @    @ @@@@@  @   @
	// @ @ @  @@   @   @     @ @
	//  @@@   @ @  @   @      @
	// @ @ @  @   @@   @     @ @
	//   @    @    @ @@@@@  @   @
	//-------------------------------------------------------------------------
	int ret = 0;
	int pl_last_error = PL_NO_ERROR;
#if !defined (__PL_FILESYSTEM_LESS__) || defined (__PL_MACOSX__)
	uuid_t pl_uuid;
#endif // !__PL_FILESYSTEM_LESS__ || __PL_MACOSX__
#ifdef __PL_MACOSX__
	char pl_uuid_buffer_semaphore[PL_MAX_PATH] = { '\0' };
#endif // __PL_MACOSX__
#ifdef __PL_FILESYSTEM_LESS__
	char *env_address = NULL;
	char *env_port = NULL;
	size_t length = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;

	//-------------------------------------------------------------------------
	// Variables uesed for buffer and input checks.
	//-------------------------------------------------------------------------
	size_t bytes_left_in_buffer = 0;

#else // __PL_FILESYSTEM_LESS__
	char pl_root[PL_MAX_PATH] = { '\0' };
	char pl_path[PL_MAX_PATH] = { '\0' };
	char pl_buffer[PL_MAX_PATH] = { '\0' };
	char pl_uuid_buffer[PL_MAX_PATH] = { '\0' };
	char pl_cvt_buffer[PL_MAX_BUFFER_SIZE] = { '\0' };
#ifdef __PL_GENERATE_INI__
	int pl_config_file = -1;
	size_t pl_config_file_bytes_to_write = 0;
	size_t pl_config_file_bytes_written = 0;
#endif // __PL_GENERATE_INI__

	//-------------------------------------------------------------------------
	// Variables uesed for buffer and input checks.
	//-------------------------------------------------------------------------
	size_t bytes_left_in_pl_root = 0;
	size_t bytes_left_in_pl_path = 0;
	size_t bytes_left_in_pl_buffer = 0;
	size_t bytes_left_in_pl_cvt_buffer = 0;
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Get the uuid class and field id.
	//-------------------------------------------------------------------------
	uuid_class = (*interface_pointer)->GetObjectClass(
		interface_pointer, 
		java_puuid
	);
	if(uuid_class == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}
	uuid_msb_field_id = (*interface_pointer)->GetFieldID(
		interface_pointer, 
		uuid_class, 
		"mostSigBits", 
		"J"
	);
	if(uuid_msb_field_id == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}
	uuid_lsb_field_id = (*interface_pointer)->GetFieldID(
		interface_pointer, 
		uuid_class, 
		"leastSigBits", 
		"J"
	);
	if(uuid_lsb_field_id == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}

	//-------------------------------------------------------------------------
	// Get the java arguments & initializations.
	//-------------------------------------------------------------------------
	pl_application_name = (*interface_pointer)->GetStringUTFChars(
		interface_pointer, 
		java_pl_application_name, 
		NULL
	);

	//-------------------------------------------------------------------------
	// Get and check the counter count.
	//-------------------------------------------------------------------------
	pl_counters_count = (unsigned int)java_pl_counters_count;
	object_array_size = (*interface_pointer)->GetArrayLength(
		interface_pointer, 
		java_pl_counters_names
	);
	if(object_array_size != pl_counters_count) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}

	//-------------------------------------------------------------------------
	// Get and store the counter names.
	//-------------------------------------------------------------------------
	pl_counters_names = 
		(const char **)malloc(sizeof(char *) * pl_counters_count);
	if(pl_counters_names == NULL) {
		pl_last_error = PL_CRITICAL_FAILURE;
		goto pl_open_return;
	}
	for(i = 0; i < pl_counters_count; i++) {
		string_object = (*interface_pointer)->GetObjectArrayElement(
			interface_pointer, 
			java_pl_counters_names, 
			i
		);
		native_string = (*interface_pointer)->GetStringUTFChars(
			interface_pointer, 
			string_object, 
			NULL
		);
		pl_counters_names[i] = native_string;
	}

	//-------------------------------------------------------------------------
	// Allocate temp uuid.
	//-------------------------------------------------------------------------
	puuid = (uuid_t *)malloc(sizeof(uuid_t));
	if(puuid == NULL) {
		pl_last_error = PL_CRITICAL_FAILURE;
		goto pl_open_return;
	}
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Check calling arguments.
	// Note:
	//    Since application name pointer can be NULL, it is not tested
	//-------------------------------------------------------------------------
	if(
		(pl_counters_names == NULL) ||
		(puuid == NULL)
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		|| (pl_counters_count > PL_MAX_COUNTERS_PER_LINK)
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Perform the following input data checking:
	//   - Only allowed characters are used in application and counter(s) names
	//   - The legth of application and counter(s) names allow fully qualified
	//   counter file names having a maximum of PL_MAX_PATH characters.
	// Note:
	//    <PL_FOLDER>/<application_name>_<UUID>/<counter_name>
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Check application name.
	//-------------------------------------------------------------------------
	if(pl_application_name != NULL) {

		//---------------------------------------------------------------------
		// Get application name length and check value.
		//---------------------------------------------------------------------
		pchar = (char *)pl_application_name;
		bytes_count = 0;
		while(
			(bytes_count < PL_MAX_PATH) &&
			(*pchar != '\0')
		) {
				bytes_count++;
				pchar++;
		}
		if(bytes_count >= PL_MAX_PATH) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_open_return;
		}
		application_name_length = bytes_count;
		if(
			(application_name_length <= 0) ||
			(application_name_length >= PL_MAX_PATH)
		) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_open_return;
		}

		//---------------------------------------------------------------------
		// Check that only allowed characters are used in the application name.
		//---------------------------------------------------------------------
		for(
			n = 0; 
			n < (int)application_name_length; 
			n++
		) {
			for(
				m = 0; 
				m < PL_EXTRA_INPUT_CHECKS_APPLICATION_NAME_ALLOWED_CHARACTERS_COUNT; 
				m++
			) {
				if(
					pl_application_name[n] == 
					allowed_characters_in_application_name[m]
				) {
					goto pl_open_check_application_name_next;
				}
			} // m
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_open_return;
pl_open_check_application_name_next:
			;
		} // n
	} else {
		application_name_length = strlen(PL_ANONYMOUS_APPLICATION_NAME);
	}

	//-------------------------------------------------------------------------
	// Compute and check control length.
	// Note:
	//    Fully qualified counter file name must have a character count of less
	//    or PL_MAX_PATH characters.
	//-------------------------------------------------------------------------
	pl_root_name_length = strlen(PL_FOLDER_STRING);
	pl_root_name_length += strlen(PL_PATH_SEPARATOR_STRING);
	pl_root_name_length += application_name_length;
	pl_root_name_length += strlen(PL_APPLICATION_NAME_SEPARATOR_STRING);
	pl_root_name_length += PL_UUID_MAX_CHARS;
	pl_root_name_length += strlen(PL_PATH_SEPARATOR_STRING);
	if(pl_root_name_length >= PL_MAX_PATH) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_return;
	}

	//-------------------------------------------------------------------------
	// Check counter(s) name.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_counters_count; j++) {

		//---------------------------------------------------------------------
		// Check application name.
		//---------------------------------------------------------------------
		if(pl_counters_names[j] != NULL) {

			//-----------------------------------------------------------------
			// Get application name length and check value.
			//-----------------------------------------------------------------
			pchar = (char *)pl_counters_names[j];
			bytes_count = 0;
			while(
				(bytes_count < PL_MAX_PATH) &&
				(*pchar != '\0')
			) {
					bytes_count++;
					pchar++;
			}
			if(bytes_count >= PL_MAX_PATH) {
				pl_last_error = PL_INVALID_PARAMETERS;
				goto pl_open_return;
			}
			counter_name_length = bytes_count;
			if(
				(counter_name_length <= 0) ||
				(counter_name_length >= PL_MAX_PATH)
			) {
				pl_last_error = PL_INVALID_PARAMETERS;
				goto pl_open_return;
			}

			//-----------------------------------------------------------------
			// Check that only allowed characters are used in the counter name.
			//-----------------------------------------------------------------
			for(
				n = 0; 
				n < (int)counter_name_length; 
				n++
			) {
				for(
					m = 0; 
					m < PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT; 
					m++
				) {
					if(
						pl_counters_names[j][n] == 
						allowed_characters_in_counter_name[m]
					) {
						goto pl_open_check_counter_name_next;
					}
				} // m
				pl_last_error = PL_INVALID_PARAMETERS;
				goto pl_open_return;
pl_open_check_counter_name_next:
				;
			} // n
		} else {

			//-----------------------------------------------------------------
			// Anonymous counter.
			// Note:
			//    <anonymous><n>
			//-----------------------------------------------------------------
			counter_name_length = strlen(PL_GENERIC_COUNTER_NAME);

			//-----------------------------------------------------------------
			// Generate counter rank for anonymous counter and get its length.
			// Note:
			//    Max value for unsigned int is 4,294,967,295
			//-----------------------------------------------------------------
			bytes_left_in_convert_buffer = sizeof(convert_buffer);
			bytes_left_in_convert_buffer -= 
				strlen(PL_MAX_UNSIGNED_INTEGER_STRING)
			;
			if(bytes_left_in_convert_buffer > PL_STRNCPY_MIN_BYTES) {
				memset(
					convert_buffer, 
					0, 
					sizeof(convert_buffer)
				);
				ret = sprintf(
					convert_buffer, 
					"%d",
					j
				);
				if(ret < 0) {
					pl_last_error = PL_COUNTER_TO_STRING_FAILED;
					goto pl_open_return;
				}
			} else {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_return;
			}
			counter_name_length += strlen(convert_buffer);
		}

		//---------------------------------------------------------------------
		// Compute and check control length.
		// Note:
		//    Fully qualified counter file name must have a character count of 
		//    less or PL_MAX_PATH characters.
		//---------------------------------------------------------------------
		pl_counter_name_length = pl_root_name_length;
		pl_counter_name_length += counter_name_length;
		if(pl_counter_name_length >= PL_MAX_PATH) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_open_return;
		}
	} // for j

#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// First pl_open call takes the pl_table initialization penalty.
	//-------------------------------------------------------------------------
	if(pl_table_initialized == 0) {
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Allocate dynamically the pl_table -- fixed to default size.
		// This size will de expanded if needed later on and during each future 
		// call to pl_attach/pl_open.
		// Caution: this memory will not be freed! (__PL_DYNAMIC_TABLE_ALLOCA-
		// TION__).  Therefore it should never be defined or you can take 
		// responsibility to free it up (as in the PL Agent).
		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ defined
		// --------------------------------------------
		//
		//                                  |<----- LIMITED BY AVAILABLE MEMORY ---->|
		// +-----------------+------+       +------+------+--        --+------+------+
		// |                 |      |       |      |      |            |      |      |
		// | PL table access | *PL -+-----> | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |      |       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |       |      |      |            |      |      |
		// +-----------------+------+       +------+------+--        --+------+------+
		//---------------------------------------------------------------------
		memset(
			&pl_table, 
			0,
			sizeof(pl_table)
		);
		memory_size = 
			sizeof(PRODUCTIVITY_LINK) * 
			PL_MAX_PRODUCTIVITY_LINKS
		;
		pl_table.pl_array = (PPRODUCTIVITY_LINK)malloc(memory_size);
		if(pl_table.pl_array == NULL) {
			pl_last_error = PL_OUT_OF_MEMORY;
			goto pl_open_return;
		}
		// nulls in-use flags and the handles
		memset(
			pl_table.pl_array, 
			0, 
			memory_size
		);
		pl_max_productivity_links = PL_MAX_PRODUCTIVITY_LINKS;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ NOT defined
		// ------------------------------------------------
		//
		//                   |<----- PL_MAX_PRODUCTIVITY_LINKS ------>|
		// +-----------------+------+------+--        --+------+------+
		// |                 |      |      |            |      |      |
		// | PL Table access | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |      |            |      |      |
		// +-----------------+------+------+--        --+------+------+
		//---------------------------------------------------------------------
		// nulls in-use flags and the handles
		memset(
			&pl_table, 
			0, 
			sizeof(PL_TABLE)
		); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
#ifdef __PL_MACOSX__

		//---------------------------------------------------------------------
		// Create PL Table semaphore.
		// Note:
		// Semaphore name is required by MacOS X POSIX semaphore implementation.
		// Semaphore name is PL_SEMAPHORE_NAME_MAX_LENGTH characters of a guuid.
		//---------------------------------------------------------------------
		uuid_generate(pl_uuid);
		memset(
			pl_uuid_buffer_semaphore, 
			0, 
			sizeof(pl_uuid_buffer_semaphore)
		);
		uuid_unparse(
			pl_uuid, 
			pl_uuid_buffer_semaphore
		);
		pl_uuid_buffer_semaphore[PL_SEMAPHORE_NAME_MAX_LENGTH] = '\0';
		pl_table.semaphore = sem_open(
			pl_uuid_buffer_semaphore, 
			O_CREAT | O_EXCL, 
			(mode_t)PL_SEMAPHORE_ACCESS_MODE, 
			1
		);
		if(pl_table.semaphore == (sem_t *)SEM_FAILED) {
			ret = -1;
		}
#else // __PL_MACOSX__
		ret = sem_init(
			&pl_table.semaphore, 
			0, 
			1
		);
#endif // __PL_MACOSX__		
		if(ret == -1) {
			pl_last_error = PL_SYNCHRONIZATION_FAILED;
			goto pl_open_return;
		}
#ifdef __PL_FILESYSTEM_LESS__

		//---------------------------------------------------------------------
		// In file system-less mode, the PL protocol is used to send a pl_open
		// request to a PL agent (identified via the default agent IP @ / port
		// or user provided environment variables.  The remote agent will carry
		// out the pl_open API call and will return the remote pld, uuid and
		// status.  The remote pld will be stored into the PL table and a local
		// pld is returned with the uuid to the calling process.
		// --------------------------------------------------------------------
		pl_table_initialized = 1;
	} // if pl_table_initialized == 0

	//-------------------------------------------------------------------------
	// Lock the pl_table against other threads (blocking wait).
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_wait(pl_table.semaphore);
#else // __PL_MACOSX__
	ret = sem_wait(&pl_table.semaphore);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_open_return;
	}
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < PL_MAX_PRODUCTIVITY_LINKS; index++) {
		if(pl_table.pl_array[index].pl_in_use == 0) {
			goto pl_open_found;
		}
	}
	// pl_table full
	pl_last_error = PL_DESCRIPTOR_TABLE_FULL;
	goto pl_open_unlock_table;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < pl_max_productivity_links; index++) {
		if(pl_table.pl_array[index].pl_in_use == 0) {
			goto pl_open_found;
		}
	}

	//-------------------------------------------------------------------------
	// No room in the table, lets double dynamically the pl_table size and
	// create the additional counters.
	//-------------------------------------------------------------------------
	pl_old_max_productivity_links = pl_max_productivity_links; 
	pl_max_productivity_links *= 2;
	pl_table.pl_array =	(PPRODUCTIVITY_LINK)realloc(
		pl_table.pl_array, 
		sizeof(PRODUCTIVITY_LINK) * pl_max_productivity_links
	);
	if(pl_table.pl_array == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	// clear newly allocated memory
	memset(
		&pl_table.pl_array[index], 
		0, 
		sizeof(PRODUCTIVITY_LINK) * pl_old_max_productivity_links
	);
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
pl_open_found:
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Allocate memory for the write cache.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(unsigned long long) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_write_cache = 
		(unsigned long long *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_write_cache == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_write_cache, 
		0, 
		memory_size
	);
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate timestamps memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(time_t) * 
		pl_counters_count
	;
	pl_table.pl_array[index].open_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].open_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].open_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_attach_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_attach_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_attach_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_read_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_read_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_read_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_write_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_write_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_write_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_close_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_close_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_close_time, 
		0,
		memory_size
	);
#endif // __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate semaphore memory.
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
	memory_size = 
		sizeof(sem_t) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(sem_t *)malloc(memory_size)
	;
#endif// __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
	memory_size = 
		sizeof(sem_t *) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(sem_t **)malloc(memory_size)
	;
#endif// __PL_MACOSX__
	if(pl_table.pl_array[index].pl_counter_handles_semaphores == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles);
		pl_table.pl_array[index].pl_counter_handles = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_counter_handles_semaphores, 
		0, 
		memory_size
	);

	//-------------------------------------------------------------------------
	// Allocate socket memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(SOCKET) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_sockets = 
		(SOCKET *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_sockets == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_counter_sockets, 
		0,
		memory_size
	);
	pl_table.pl_array[index].pl_counters_count = 0;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	pl_table.pl_array[index].pl_in_use = 1;

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_ADDRESS environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	bytes_left_in_buffer = sizeof(pl_table.pl_array[index].pl_address);
	env_address = getenv(
		PL_DEFAULT_PL_AGENT_ADDRESS_ENVAR_NAME
	);
	if(env_address == NULL) {
		strncpy(
			pl_table.pl_array[index].pl_address,
			PL_DEFAULT_PL_AGENT_ADDRESS,
			bytes_left_in_buffer
		);
		length = strlen(PL_DEFAULT_PL_AGENT_ADDRESS);
	} else {
		strncpy(
			pl_table.pl_array[index].pl_address,
			env_address,
			bytes_left_in_buffer
		);
		length = strlen(env_address);
		env_address = NULL;
	}
	bytes_left_in_buffer -= length;
	if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Check the validity of the IPV4 address.
	// Note:
	//    Class A: 000.000.000.000 to 127.255.255.255
	//    Class B: 128.000.000.000 to 191.255.255.255
	//    Class C: 192.000.000.000 to 223.255.255.255
	//    Class D: 224.000.000.000 to 239.255.255.255
	//    Class E: 240.000.000.000 to 255.255.255.255
	//-------------------------------------------------------------------------
	for(m = 0; m < (int)length; m++) {

		//---------------------------------------------------------------------
		// Ckeck that only legal characters are used.
		//---------------------------------------------------------------------
		if(
			pl_table.pl_array[index].pl_address[m] == 
			PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_DOT_CHARACTER
		) { 
			if(digit_count == 0) {

				//-------------------------------------------------------------
				// No address can start without a digit.
				//-------------------------------------------------------------
				goto pl_open_check_ip_v4_address_error; 
			}

			//-----------------------------------------------------------------
			// A dot was found, let's process the address value as stored.
			//-----------------------------------------------------------------
			dot_count++;
			digit_count = 0;
			ip_v4_address_value_string[
				PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE
			] = '\0';
			value = atoi(ip_v4_address_value_string);
			memset(
				ip_v4_address_value_string, 
				0, 
				sizeof(ip_v4_address_value_string)
			);
			
			//-----------------------------------------------------------------
			// Use the . character count to check address value ranges.
			//-----------------------------------------------------------------
			switch(dot_count) {

				case 1:

					//---------------------------------------------------------
					// This is the first address value (nnn.xxx.xxx.xxx).
					// Assign a class to the address based on the first address
					// value.
					//---------------------------------------------------------
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E; 
						break; 
					}
					goto pl_open_check_ip_v4_address_error;
					break;

				case 2:

					//---------------------------------------------------------
					// This is the second address value (xxx.nnn.xxx.xxx).
					// Check the second address value based on the class 
					// assigned using the first address value
					//---------------------------------------------------------
					switch(ip_v4_class) {
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						default:

							//-------------------------------------------------
							// Invalid second address value.
							//-------------------------------------------------
							goto pl_open_check_ip_v4_address_error;
					} // switch
					break;

				case 3: // third number

					//---------------------------------------------------------
					// This is the third address value (xxx.xxx.nnn.xxx).
					// Check the third address value based on the class 
					// assigned using the first address value
					//---------------------------------------------------------
					switch(ip_v4_class) {
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MAX_VALUE)
							) { 
								goto pl_open_check_ip_v4_address_error; 
							}
							break;
						default:

							//-------------------------------------------------
							// Invalid second address value.
							//-------------------------------------------------
							goto pl_open_check_ip_v4_address_error;
					} // switch
					break;

				default:

					//---------------------------------------------------------
					// This is the fourth address value (xxx.xxx.xxx.nnn).
					// Note:
					//    Fourth address value is tested later on, however if 
					//    we are here, it is an error.
					//---------------------------------------------------------
					goto pl_open_check_ip_v4_address_error;
			}

		} else {

			//-----------------------------------------------------------------
			// This is not a dot (.) character, check if it is an allowed one.
			//-----------------------------------------------------------------
			for(
				n = 0; 
				n < PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS_COUNT; 
				n++
			) {
				if(
					pl_table.pl_array[index].pl_address[m] == 
					allowed_characters_in_ip_v4_address[n]
				) {
					ip_v4_address_value_string[digit_count++] = 
						pl_table.pl_array[index].pl_address[m]
					;
					if(
						digit_count > 
						PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DIGITS_IN_ADDRESS_VALUE
					) { 
						goto pl_open_check_ip_v4_address_error; 
					}
					goto pl_open_check_ip_v4_address_next;
				}
			} // for n
			goto pl_open_check_ip_v4_address_error;
		}
pl_open_check_ip_v4_address_next:
		;
	} // for m

	//-------------------------------------------------------------------------
	// check if after the last dot (.) we have at least one digit as this 
	// cannot be trapped in the loop above.
	//-------------------------------------------------------------------------
	if(digit_count == 0) { 
		goto pl_open_check_ip_v4_address_error; 
	}

	//-------------------------------------------------------------------------
	// check ip address string has three (3) dots (.)
	//-------------------------------------------------------------------------
	if(
		dot_count != 
		PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DOT_CHARACTERS_IN_ADDRESS
	) { 
		goto pl_open_check_ip_v4_address_error; 
	}

	//-------------------------------------------------------------------------
	// check fouth number's range
	//-------------------------------------------------------------------------
	ip_v4_address_value_string[
		PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE
	] = '\0';
	value = atoi(ip_v4_address_value_string);
	
	//-------------------------------------------------------------------------
	// This is the fourth address value (xxx.xxx.xxx.nnn).
	// Check the fourth address value based on the class assigned using the 
	// first address value.
	//-------------------------------------------------------------------------
	switch(ip_v4_class) {
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MAX_VALUE)
			) { 
				goto pl_open_check_ip_v4_address_error; 
			}
			break;
		default:

			//-----------------------------------------------------------------
			// Invalid second address value.
			//-----------------------------------------------------------------
			goto pl_open_check_ip_v4_address_error;
	} // switch
	goto pl_open_check_ip_v4_address_ok;
pl_open_check_ip_v4_address_error:
	pl_last_error = PL_FILESYSTEM_LESS_INVALID_IPV4_ADDRESS;
	goto pl_open_return;
pl_open_check_ip_v4_address_ok:
	;
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_PL_PORT environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	bytes_left_in_buffer = sizeof(pl_table.pl_array[index].pl_port);
	env_port = getenv(
		PL_DEFAULT_PL_PORT_ENVAR_NAME
	);
	if(env_port == NULL) {
		strncpy(
			pl_table.pl_array[index].pl_port,
			PL_DEFAULT_PL_AGENT_PL_PORT_STRING,
			bytes_left_in_buffer
		);
		length = strlen(PL_DEFAULT_PL_AGENT_PL_PORT_STRING);
	} else {
		strncpy(
			pl_table.pl_array[index].pl_port,
			env_port,
			bytes_left_in_buffer
		);
		length = strlen(env_port);
		env_port = NULL;
	}
	bytes_left_in_buffer -= length;
	if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Check the validity of the port.
	// Note:
	//    Valid port number is in the 1-65535 range
	//    PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE
	//    PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE
	//-------------------------------------------------------------------------
	digit_count = 0;
	for(m = 0; m < (int)length; m++) {
		for(
			n = 0; 
			n < PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS_COUNT; 
			n++
		) {
			if(
				pl_table.pl_array[index].pl_port[m] == 
				allowed_characters_in_port[n]
			) {
				port_value_string[digit_count++] = 
					pl_table.pl_array[index].pl_port[m]
				;
				if(
					digit_count > 
					PL_EXTRA_INPUT_CHECKS_PORT_MAX_DIGITS_IN_PORT_VALUE
				) { 
					goto pl_open_check_port_error; 
				}
				goto pl_open_check_port_next;
			}
		} // for n
		goto pl_open_check_port_error;
pl_open_check_port_next:
		;
	} // for m

	//-------------------------------------------------------------------------
	// Check port value range.
	//-------------------------------------------------------------------------
	port_value_string[
		PL_EXTRA_INPUT_CHECKS_PORT_BUFFER_LAST_BYTE
	] = '\0';
	value = atoi(port_value_string);
	if(
		(value < PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE) || 
		(value > PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE)
	) {
		goto pl_open_check_port_error;
	}
	goto pl_open_check_port_ok;
pl_open_check_port_error:
	pl_last_error = PL_FILESYSTEM_LESS_INVALID_PORT;
	goto pl_open_return;
pl_open_check_port_ok:
	;
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Initialize addres data.
	//-------------------------------------------------------------------------
	memset(
		&pl_table.pl_array[index].address_info_hint, 
		0,
		sizeof(pl_table.pl_array[index].address_info_hint)
	);
	pl_table.pl_array[index].address_info_hint.ai_family = 
		PL_ADDRESS_INFO_HINT_AI_FAMILY
	;
	pl_table.pl_array[index].address_info_hint.ai_socktype = 
		PL_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	pl_table.pl_array[index].address_info_hint.ai_protocol = 
		PL_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	pl_table.pl_array[index].address_info_hint.ai_flags = 
		PL_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve agent address and port.
	//-------------------------------------------------------------------------
	ret = getaddrinfo(
		pl_table.pl_array[index].pl_address,
		pl_table.pl_array[index].pl_port, 
		&pl_table.pl_array[index].address_info_hint, 
		&pl_table.pl_array[index].address_info
	);

	if(ret != 0) { 
		pl_last_error = 
			PL_FILESYSTEM_LESS_NETWORK_ADDRESS_RESOLUTION_FAILED;
		goto pl_open_return;
	}

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_OPEN command.
	//-------------------------------------------------------------------------
	// pl_open()
	// +-----------+-----------+-----------+------------+--     --+---------------+
	// | OPERATION | COUNTERS  |  <string> | <string>   |         | <string>      |
	// | CODE      | COUNT (N) | APP NAME  | COUNTER 0  |   ...   | COUNTER (N-1) |
	// |           |           |           | NAME       |         | NAME          |
	// +---------- +-----------+-----------+------------+--     --+---------------+
	// ^           ^ (LSB-MSB) ^           
	// |           |           |           
	// |<--- A --->|<--- B --->|<--- C ---> <--------------- D ------------------>
	// |           |           |
	// |           |           |
	// |           |           +--- PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX
	// |           +--------------- PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX
	// +--------------------------- PL_PROTOCOL_PL_OPEN_INPUT_OPCODE_INDEX 
	//
	// Note:
	//    A = PL_PROTOCOL_OPCODE_SIZE
	//    B = PL_PROTOCOL_COUNTERS_COUNT_SIZE
	//    C = variable
	//    D = variable
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_OPEN_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_OPEN;
	memcpy(
		&message[PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX],
		&pl_counters_count,
		PL_PROTOCOL_UINT_SIZE
	);
	if(pl_application_name != NULL) {
		p_string = pl_application_name;
	} else {
		p_string = PL_ANONYMOUS_APPLICATION_NAME;
	}
	length = strlen(p_string);
	message_size = (PL_PROTOCOL_SIZET)length;
	memcpy(
		&message[PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	sprintf(
		&message[
			PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX + 
			PL_PROTOCOL_SIZET_SIZE
		],
		"%s",
		p_string
	);
	p_string = &message[
		PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX + 
		PL_PROTOCOL_SIZET_SIZE +
		length
	];
	bytes_to_send = 
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_COUNTERS_COUNT_SIZE +
		PL_PROTOCOL_SIZET_SIZE +
		length
	;
	for(j = 0; j < pl_counters_count; j++) {
		if(pl_counters_names[j] != NULL) {
			pp_string = pl_counters_names[j];
		} else {
			pp_string = buffer;
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				"%s%d",
				PL_GENERIC_COUNTER_NAME,
				j
			);
		}
		length = strlen(pp_string);
		message_size = (PL_PROTOCOL_SIZET)length;
		memcpy(
			p_string,
			&message_size,
			PL_PROTOCOL_SIZET_SIZE
		);
		sprintf(
			p_string + PL_PROTOCOL_SIZET_SIZE,
			"%s",
			pp_string
		);
		p_string += length + PL_PROTOCOL_SIZET_SIZE;
	} // for j
	*p_string = PL_PROTOCOL_EOR;
	bytes_to_send = (
		p_string - 
		pl_output_buffer
	);
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_open_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[index].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_socket = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(pl_socket == INVALID_SOCKET) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_socket,
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_socket,
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = close(
				pl_socket
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_open_unlock_table;
			}
			continue;
		}
		goto pl_open_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on EADDRINUSE:
	//    Address already in use.  This error occurs if an application attempts
	//    to bind to a socket that has already been used for an existing socket,
	//    or a socket that wasn't closed properly, or one that is still in the
	//    process of closing.
	//-------------------------------------------------------------------------
	if(errno == EADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_open_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_open_unlock_table;

pl_open_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_OPEN command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_socket,
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_open_unlock_table;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer
	//-------------------------------------------------------------------------
	// pl_open() return
	// +----------+-----------+----------+
	// | STATUS   | UUID      | PLD      |
	// | CODE     |           |          |
	// +----------+-----------+----------+ <-- PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX
	// ^          ^ (LSB-MSB) ^ (LSB-MSB)
	// |          |           |
	// |<-- A --->|<--- B --->|<-- C --->
	// |          |           |
	// |          |           +---- PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX
	// |          +---------------- PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX
	// +--------------------------- PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	memset(
		&pl_input_buffer, 
		0,
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_open_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (size_t)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_open_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close PL socket.
	//-------------------------------------------------------------------------
	ret = close(
		pl_socket
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Extract agent's answer.
	//-------------------------------------------------------------------------
	memcpy(
		puuid,
		&pl_input_buffer[PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX],
		PL_PROTOCOL_UUID_SIZE
	 );
	memcpy(
		&pl_table.pl_array[index].uuid,
		puuid,
		PL_PROTOCOL_UUID_SIZE
	 );
	memcpy(
		&pl_table.pl_array[index].remote_pld,
		&pl_input_buffer[PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX],
		PL_PROTOCOL_PLD_SIZE
	);

	//-------------------------------------------------------------------------
	// Create counters semaphores, initialize counters write cache and socket.
	//-------------------------------------------------------------------------
	// index = free slot found in the pl_table 
	for(j = 0; j < pl_counters_count; j++) { 
#ifdef __PL_MACOSX__

		//---------------------------------------------------------------------
		// Semaphore name is PL_SEMAPHORE_NAME_MAX_LENGTH characters of a guuid.
		//---------------------------------------------------------------------
		uuid_generate(pl_uuid);
		memset(
			pl_uuid_buffer_semaphore, 
			0, 
			sizeof(pl_uuid_buffer_semaphore)
		);
		uuid_unparse(
			pl_uuid, 
			pl_uuid_buffer_semaphore
		);
		pl_uuid_buffer_semaphore[PL_SEMAPHORE_NAME_MAX_LENGTH] = '\0';
		pl_table.pl_array[index].pl_counter_handles_semaphores[j] = 
			sem_open(
				pl_uuid_buffer_semaphore, 
				O_CREAT | O_EXCL, 
				(mode_t)PL_SEMAPHORE_ACCESS_MODE, 
				1
			);
		if(pl_table.pl_array[index].pl_counter_handles_semaphores[j] == 
			(sem_t *)SEM_FAILED
		) {
			ret = -1;
		}
#else // __PL_MACOSX__		
		ret = sem_init(
			&pl_table.pl_array[index].pl_counter_handles_semaphores[j], 
			0, 
			1
		);
#endif // __PL_MACOSX__	
		pl_table.pl_array[index].pl_write_cache[j] = PL_MAX_COUNTER_VALUE - 1;
		pl_table.pl_array[index].pl_counter_sockets[j] = INVALID_SOCKET;
	} // for j
	pl_table.pl_array[index].pl_counters_count = pl_counters_count;
#else // __PL_FILESYSTEM_LESS__

		//---------------------------------------------------------------------
		// In file system mode of operation, the pl_open API call is carried-
		// out locally using the PL_FOLDER.
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		// Check if the PL_FOLDER folder exist.
		//---------------------------------------------------------------------
		ret = access(PL_FOLDER, F_OK);
		if(ret == -1) {
			pl_last_error = PL_MISSING_DIRECTORY;
			goto pl_open_return;
		}
		pl_table_initialized = 1;
	}

	//-------------------------------------------------------------------------
	// Lock the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_wait(pl_table.semaphore);
#else // __PL_MACOSX__
	ret = sem_wait(&pl_table.semaphore);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_open_return;
	}
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < PL_MAX_PRODUCTIVITY_LINKS; index++) {
		if(pl_table.pl_array[index].pl_in_use == 0) {
			goto pl_open_found;
		}
	}
	// pl_table full
	pl_last_error = PL_DESCRIPTOR_TABLE_FULL;
	goto pl_open_unlock_table;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < pl_max_productivity_links; index++) {
		if(pl_table.pl_array[index].pl_in_use == 0) {
			goto pl_open_found;
		}
	}

	//-------------------------------------------------------------------------
	// No room in the table, lets double dynamically the pl_table size and
	// create the additional counters.
	//-------------------------------------------------------------------------
	pl_old_max_productivity_links = pl_max_productivity_links; 
	pl_max_productivity_links *= 2;
	pl_table.pl_array = (PPRODUCTIVITY_LINK)realloc(
		pl_table.pl_array, 
		sizeof(PRODUCTIVITY_LINK) * pl_max_productivity_links
	);
	if(pl_table.pl_array == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	// clear newly allocated memory
	memset(
		&pl_table.pl_array[index], 
		0, 
		sizeof(PRODUCTIVITY_LINK) * pl_old_max_productivity_links
	);
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
pl_open_found:
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Allocate memory for the write cache.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(unsigned long long) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_write_cache = 
		(unsigned long long *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_write_cache == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_write_cache, 
		0, 
		memory_size
	);
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate timestamps memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(time_t) * 
		pl_counters_count
	;
	pl_table.pl_array[index].open_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].open_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].open_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_attach_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_attach_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_attach_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_read_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_read_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_read_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_write_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_write_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_write_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_close_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_close_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_close_time, 
		0, 
		memory_size
	);
#endif // __PL_TIMESTAMPING__
	memory_size = 
		sizeof(int) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles = 
		(int *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_handles == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_counter_handles, 
		0, 
		memory_size
	);

	//-------------------------------------------------------------------------
	// Allocate semaphore memory.
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
	memory_size = 
		sizeof(sem_t) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(sem_t *)malloc(memory_size)
	;
#endif// __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
	memory_size = 
		sizeof(sem_t *) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(sem_t **)malloc(memory_size)
	;
#endif// __PL_MACOSX__
	if(pl_table.pl_array[index].pl_counter_handles_semaphores == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles);
		pl_table.pl_array[index].pl_counter_handles = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_counter_handles_semaphores, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].pl_counters_count = 0;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	pl_table.pl_array[index].pl_in_use = 1;

	//-------------------------------------------------------------------------
	// Generate the uuid for the new productivity link.
	//-------------------------------------------------------------------------
#ifndef __PL_CONSTANT_UUID__
	uuid_generate(pl_uuid);
	memcpy(
		puuid, 
		pl_uuid, 
		sizeof(uuid_t)
	);
#else // __PL_CONSTANT_UUID__
	memset(
		pl_uuid, 
		0, 
		sizeof(uuid_t)
	);
#endif // __PL_CONSTANT_UUID__

	//-------------------------------------------------------------------------
	// Sample pl_config.ini file (generated by esrv).
	//-------------------------------------------------------------------------
	// esrv
	// 8072f1db-7c51-44c9-9f84-3f118aff2f4a
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/
	// 63
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Energy (Joule)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Energy (Joule).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Energy (kWh)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Energy (kWh).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Energy Overflows (no unit)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Update Frequency (second)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power (Watt)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power (Watt).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power (Watt)--Max
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power (Watt)--Max.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power (Watt)--Min
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power (Watt)--Min.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere).sign
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere)--Max
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere)--Max.sign
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere)--Max.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere)--Min
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere)--Min.sign
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere)--Min.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere seconds)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere seconds).sign
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current (Ampere seconds).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt).sign
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt)--Max
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt)--Max.sign
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt)--Max.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt)--Min
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt)--Min.sign
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt)--Min.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt seconds)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt seconds).sign
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage (Volt seconds).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power Factor (no unit)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power Factor (no unit).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power Factor (no unit)--Max
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power Factor (no unit)--Max.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power Factor (no unit)--Min
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power Factor (no unit)--Min.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power Factor (no unit seconds)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Power Factor (no unit seconds).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current Frequency (Hertz)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current Frequency (Hertz).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current Frequency (Hertz)--Max
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current Frequency (Hertz)--Max.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current Frequency (Hertz)--Min
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current Frequency (Hertz)--Min.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current Frequency (Hertz seconds)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Current Frequency (Hertz seconds).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage Frequency (Hertz)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage Frequency (Hertz).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage Frequency (Hertz)--Max
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage Frequency (Hertz)--Max.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage Frequency (Hertz)--Min
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage Frequency (Hertz)--Min.decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage Frequency (Hertz seconds)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Voltage Frequency (Hertz seconds).decimals
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Channel(s)
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Status
	// /opt/productivity_link/esrv_8072f1db-7c51-44c9-9f84-3f118aff2f4a/[CHANNEL1] - Version
	// 2010.01.18(L)
	// __PL_LINUX__
	// __PL_GENERATE_INI__
	// __PL_GENERATE_INI_VERSION_TAGGING__
	// __PL_GENERATE_INI_BUILD_TAGGING__
	// __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	// __PL_BLOCKING_COUNTER_FILE_LOCK__
	// PL created on Wed Jul 21 12:42:59 2010
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Create the PL_FOLDER/application_name_uuid/ folder.
	// Note:
	//    strcpy() copies the string pointed to by src (including the 
	//    terminating '\0'). strncpy() copies no more than n bytes. Therefore,
	//    if there is no '\0' in the first n source bytes, no '\0' is appended.
	//    If the source bytes count is less than n, then the remainder of dest
	//    is padded with '\0' bytes.
	// Note:
	//    strcat() appends the src string to the dest string 
	//    overwriting the terminating '\0' of dest, and appends a '\0' at the 
	//    end. strncat() uses at most n characters from src. Since the result
	//    is always terminated with '\0', at most n+1 characters are written. 
	//-------------------------------------------------------------------------
	memset(
		pl_root, 
		0, 
		sizeof(pl_root)
	);
	memset(
		pl_path, 
		0, 
		sizeof(pl_path)
	);
	memset(
		pl_uuid_buffer, 
		0, 
		sizeof(pl_uuid_buffer)
	);
	uuid_unparse(
		pl_uuid, 
		pl_uuid_buffer
	);

	//-------------------------------------------------------------------------
	// pl_path = /opt/productivity_link 
	//-------------------------------------------------------------------------
	bytes_left_in_pl_path = sizeof(pl_path);
	strncpy(
		pl_path, 
		PL_FOLDER, 
		bytes_left_in_pl_path
	);
	bytes_left_in_pl_path -= strlen(PL_FOLDER);
	if(bytes_left_in_pl_path <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// pl_path = /opt/productivity_link/
	//-------------------------------------------------------------------------
	strncat(
		pl_path, 
		PL_PATH_SEPARATOR, 
		bytes_left_in_pl_path
	);
	bytes_left_in_pl_path -= strlen(PL_PATH_SEPARATOR);
	if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	if(pl_application_name != NULL) {

		//---------------------------------------------------------------------
		// pl_path = /opt/productivity_link/<application_name> 
		//---------------------------------------------------------------------
		strncat(
			pl_path, 
			pl_application_name, 
			bytes_left_in_pl_path
		); 
		bytes_left_in_pl_path -= strlen(pl_application_name);
		if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
			pl_last_error = PL_OUT_OF_BUFFER_SPACE;
			goto pl_open_unlock_table;
		}
	} else {

		//---------------------------------------------------------------------
		// pl_path = /opt/productivity_link/<anonymous> 
		//---------------------------------------------------------------------
		strncat(
			pl_path, 
			PL_ANONYMOUS_APPLICATION_NAME, 
			bytes_left_in_pl_path
		); 
		bytes_left_in_pl_path -= strlen(PL_ANONYMOUS_APPLICATION_NAME);
		if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
			pl_last_error = PL_OUT_OF_BUFFER_SPACE;
			goto pl_open_unlock_table;
		}
	}

	//-------------------------------------------------------------------------
	// pl_path = /opt/productivity_link/<x>_
	//-------------------------------------------------------------------------
	strncat(
		pl_path, 
		PL_APPLICATION_NAME_SEPARATOR, 
		bytes_left_in_pl_path
	);  
	bytes_left_in_pl_path -= strlen(PL_APPLICATION_NAME_SEPARATOR);
	if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// pl_path = /opt/productivity_link/<x>_<uuid> 
	//-------------------------------------------------------------------------
	strncat(
		pl_path, 
		pl_uuid_buffer, 
		bytes_left_in_pl_path
	); 
	bytes_left_in_pl_path -= strlen(pl_uuid_buffer);
	if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// pl_root = /opt/productivity_link/<x>_<uuid> into pl_root
	//-------------------------------------------------------------------------
	bytes_left_in_pl_root = sizeof(pl_root);
	strncpy(
		pl_root, 
		pl_path, 
		bytes_left_in_pl_root
	);
	bytes_left_in_pl_root -= strlen(pl_path);
	if(bytes_left_in_pl_root <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// pl_root = /opt/productivity_link/<x>_<uuid>/
	//-------------------------------------------------------------------------
	strncat(
		pl_root, 
		PL_PATH_SEPARATOR, 
		bytes_left_in_pl_root
	);
	bytes_left_in_pl_root -= strlen(PL_PATH_SEPARATOR);
	if(bytes_left_in_pl_root <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Create pl_path directory.
	//-------------------------------------------------------------------------
	ret = mkdir(
		pl_path, 
		PL_FOLDER_ACCESS_MODE
	);
	if(ret == -1) {
		pl_last_error = PL_DIRECTORY_CREATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Create the counter files in PL_FOLDER/<x>_<uuid>/, the associated 
	// semaphores and write cache.
	// Note:
	//    index points to the free slot found in pl_table
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_counters_count; j++) {

		//---------------------------------------------------------------------
		// Clear working buffers.
		//---------------------------------------------------------------------
		bytes_left_in_pl_path = sizeof(pl_path);
		bytes_left_in_pl_buffer = sizeof(pl_buffer);
		memset(
			pl_path,
			0,
			sizeof(pl_path)
		);
		memset(
			pl_buffer,
			0,
			sizeof(pl_buffer)
		);

		//---------------------------------------------------------------------
		// Create jth counter name <y>.
		//---------------------------------------------------------------------
		if(pl_counters_names[j] != NULL) {

			//-----------------------------------------------------------------
			// User provided counter name.
			// pl_buffer = <counter>
			//-----------------------------------------------------------------
			strncpy(
				pl_buffer, 
				pl_counters_names[j], 
				bytes_left_in_pl_buffer
			);
			bytes_left_in_pl_buffer -= strlen(pl_counters_names[j]);
			if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_unlock_table;
			}

		} else {

			//-----------------------------------------------------------------
			// Anonymous counter.
			// pl_buffer = <anonymous>
			//-----------------------------------------------------------------
			strncpy(
				pl_buffer, 
				PL_GENERIC_COUNTER_NAME, 
				bytes_left_in_pl_buffer
			);
			bytes_left_in_pl_buffer -= strlen(PL_GENERIC_COUNTER_NAME);
			if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_unlock_table;
			}

			//-----------------------------------------------------------------
			// Append counter rank for anonymous counter.
			// pl_buffer = <anonymous>
			// pl_cvt_buffer = <n>
			// Note:
			//    Max value for unsigned int is 4,294,967,295
			//-----------------------------------------------------------------
			bytes_left_in_pl_cvt_buffer = sizeof(pl_cvt_buffer);
			bytes_left_in_pl_cvt_buffer -= 
				strlen(PL_MAX_UNSIGNED_INTEGER_STRING)
			;
			if(bytes_left_in_pl_cvt_buffer > PL_STRNCPY_MIN_BYTES) {
				memset(
					pl_cvt_buffer, 
					0, 
					sizeof(pl_cvt_buffer)
				);
				ret = sprintf(
					pl_cvt_buffer, 
					"%d",
					j
				);
				if(ret < 0) {
					pl_last_error = PL_COUNTER_TO_STRING_FAILED;
					goto pl_open_unlock_table;
				}
			} else {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_unlock_table;
			}

			//-----------------------------------------------------------------
			// pl_buffer = <anonymous><n>
			//-----------------------------------------------------------------
			strncat(
				pl_buffer, 
				pl_cvt_buffer, 
				bytes_left_in_pl_buffer
			);
			bytes_left_in_pl_buffer -= strlen(pl_cvt_buffer);
			if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_unlock_table;
			}
		}

		//---------------------------------------------------------------------
		// pl_path = /opt/productivity_link/<x>_<uuid>/
		//---------------------------------------------------------------------
		strncpy(
			pl_path, 
			pl_root, 
			bytes_left_in_pl_path
		);
		bytes_left_in_pl_path -= strlen(pl_root);
		if(bytes_left_in_pl_path <= PL_STRNCPY_MIN_BYTES) {
			pl_last_error = PL_OUT_OF_BUFFER_SPACE;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// pl_path = /opt/productivity_link/<x>_<uuid>/<y>
		//---------------------------------------------------------------------
		strncat(
			pl_path, 
			pl_buffer, 
			bytes_left_in_pl_path
		);
		bytes_left_in_pl_path -= strlen(pl_buffer);
		if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
			pl_last_error = PL_OUT_OF_BUFFER_SPACE;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// Open counter
		//---------------------------------------------------------------------
		pl_table.pl_array[index].pl_counter_handles[j] = open(
			pl_path, 
			O_RDWR | O_CREAT, 
			PL_COUNTER_FILES_ACCESS_MODE
		);
		if(pl_table.pl_array[index].pl_counter_handles[j] == -1) {
			pl_last_error = PL_COUNTER_CREATION_FAILED;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// Create counter semaphore.
		//---------------------------------------------------------------------
#ifdef __PL_MACOSX__

		//---------------------------------------------------------------------
		// Semaphore name is PL_SEMAPHORE_NAME_MAX_LENGTH characters of a guuid.
		//---------------------------------------------------------------------
		uuid_generate(pl_uuid);
		memset(
			pl_uuid_buffer_semaphore, 
			0, 
			sizeof(pl_uuid_buffer_semaphore)
		);
		uuid_unparse(
			pl_uuid, 
			pl_uuid_buffer_semaphore
		);
		pl_uuid_buffer_semaphore[PL_SEMAPHORE_NAME_MAX_LENGTH] = '\0';
		pl_table.pl_array[index].pl_counter_handles_semaphores[j] = 
			sem_open(
				pl_uuid_buffer_semaphore, 
				O_CREAT | O_EXCL, 
				(mode_t)PL_SEMAPHORE_ACCESS_MODE, 
				1
			);
		if(pl_table.pl_array[index].pl_counter_handles_semaphores[j] == 
			(sem_t *)SEM_FAILED
		) {
			ret = -1;
		}
#else // __PL_MACOSX__		
		ret = sem_init(
			&pl_table.pl_array[index].pl_counter_handles_semaphores[j], 
			0, 
			1
		);
#endif // __PL_MACOSX__
		if(ret == -1) {
			pl_last_error = PL_COUNTER_SEMAPHORE_CREATION_FAILED;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// Set default cache value.
		//---------------------------------------------------------------------
		pl_table.pl_array[index].pl_write_cache[j] = 
			PL_MAX_COUNTER_VALUE - 1
		;
	} // for j
	pl_table.pl_array[index].pl_counters_count = pl_counters_count;

#ifdef __PL_GENERATE_INI__

	//-------------------------------------------------------------------------
	// Write the productivity link configuration file in /PL_FOLDER/puuid/ - 
	// required to attach.
	//-------------------------------------------------------------------------
	// file structure:
	//
	// 001: application name
	// 002: uuid
	// 003: path to uuid (full path)
	// 004: counters count (N)
	// 005: counter 1 (full path name)
	// ...
	// 00x: counter n (full path name)
	// if __PL_GENERATE_INI_VERSION_TAGGING__
	//    00x + 1: version tag
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	// Create the productivity link configuration file.
	//-------------------------------------------------------------------------
	bytes_left_in_pl_path = sizeof(pl_path);
	memset(
		pl_path, 
		0, 
		sizeof(pl_path)
	);

	//-------------------------------------------------------------------------
	// pl_path = /opt/productivity_link/<x>_<uuid>/
	//-------------------------------------------------------------------------
	strncpy(
		pl_path,
		pl_root, 
		bytes_left_in_pl_path
	);
	bytes_left_in_pl_path -= strlen(pl_root);
	if(bytes_left_in_pl_path <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// pl_path = /opt/productivity_link/<x>_<uuid>/pl_config.ini
	//-------------------------------------------------------------------------
	strncat(
		pl_path, 
		PL_CONFIG_FILE_NAME, 
		bytes_left_in_pl_path
	);
	bytes_left_in_pl_path -= strlen(PL_CONFIG_FILE_NAME);
	if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Open config file (pl_path)
	//-------------------------------------------------------------------------
	pl_config_file = open(
		pl_path, 
		O_RDWR | O_CREAT, 
		PL_CONFIG_FILE_ACCESS_MODE
	);
	if(pl_config_file == -1) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Write the configuration data into the productivity link configuration 
	// file.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// 001: write application name.
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	if(pl_application_name != NULL) {
		strncpy(
			pl_buffer, 
			pl_application_name, 
			bytes_left_in_pl_buffer
		);
		bytes_left_in_pl_buffer -= strlen(pl_application_name);
	} else {
		strncpy(
			pl_buffer, 
			PL_ANONYMOUS_APPLICATION_NAME, 
			bytes_left_in_pl_buffer
		);
		bytes_left_in_pl_buffer -= strlen(PL_ANONYMOUS_APPLICATION_NAME);
	}
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// 002: write uuid.
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_uuid_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_uuid_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// 003: write path to uuids (full path).
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_root, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_root);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);	
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// 004: write counters count (N).
	//-------------------------------------------------------------------------
	bytes_left_in_pl_cvt_buffer = sizeof(pl_cvt_buffer);
	ret = sprintf(
		pl_cvt_buffer, 
		"%d", 
		pl_counters_count
	);
	if(ret < 0) {
		pl_last_error = PL_COUNTER_TO_STRING_FAILED;
		goto pl_open_unlock_table;
	}
	bytes_left_in_pl_cvt_buffer -= ret;
	if(bytes_left_in_pl_cvt_buffer < 0) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_cvt_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_cvt_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);	
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Write each counter.
	// 005: counter 1 (full path name)
	// ...
	// 00x: counter n (full path name)
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_counters_count; j++) {

		//---------------------------------------------------------------------
		// Clear working buffers.
		//---------------------------------------------------------------------
		bytes_left_in_pl_path = sizeof(pl_path);
		bytes_left_in_pl_buffer = sizeof(pl_buffer);
		memset(
			pl_path, 
			0, 
			sizeof(pl_path)
		);
		memset(
			pl_buffer, 
			0, 
			sizeof(pl_buffer)
		);

		//---------------------------------------------------------------------
		// Create jth counter name <y>.
		//---------------------------------------------------------------------
		if(pl_counters_names[j] != NULL) {

			//-----------------------------------------------------------------
			// User provided counter name.
			// pl_buffer = <counter>
			//-----------------------------------------------------------------
			strncpy(
				pl_buffer, 
				pl_counters_names[j], 
				bytes_left_in_pl_buffer
			);
			bytes_left_in_pl_buffer -= strlen(pl_counters_names[j]);
			if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_unlock_table;
			}

		} else {
			
			//-----------------------------------------------------------------
			// Anonymous counter.
			// pl_buffer = <anonymous>
			//-----------------------------------------------------------------
			strncpy(
				pl_buffer, 
				PL_GENERIC_COUNTER_NAME, 
				bytes_left_in_pl_buffer
			);
			bytes_left_in_pl_buffer -= strlen(PL_GENERIC_COUNTER_NAME);
			if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_unlock_table;
			}

			//-----------------------------------------------------------------
			// Append counter rank for anonymous counter.
			// pl_buffer = <anonymous>
			// pl_cvt_buffer = <n>
			// Note:
			//    Max value for unsigned int is 4,294,967,295
			//-----------------------------------------------------------------
			bytes_left_in_pl_cvt_buffer = sizeof(pl_cvt_buffer);
			bytes_left_in_pl_cvt_buffer -= 
				strlen(PL_MAX_UNSIGNED_INTEGER_STRING)
			;
			if(bytes_left_in_pl_cvt_buffer > PL_STRNCPY_MIN_BYTES) {
				memset(
					pl_cvt_buffer, 
					0, 
					sizeof(pl_cvt_buffer)
				);
				ret = sprintf(
					pl_cvt_buffer, 
					"%d", 
					j
				); 	
				if(ret < 0) {
					pl_last_error = PL_COUNTER_TO_STRING_FAILED;
					goto pl_open_unlock_table;
				}
			} else {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_unlock_table;
			}

			//-----------------------------------------------------------------
			// pl_buffer = <anonymous><n>
			//-----------------------------------------------------------------
			strncat(
				pl_buffer, 
				pl_cvt_buffer, 
				bytes_left_in_pl_buffer
			);
			bytes_left_in_pl_buffer -= strlen(pl_cvt_buffer);
			if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
				pl_last_error = PL_OUT_OF_BUFFER_SPACE;
				goto pl_open_unlock_table;
			}

		}

		//---------------------------------------------------------------------
		// pl_path = /opt/productivity_link/<x>_<uuid>/
		//---------------------------------------------------------------------
		strncpy(
			pl_path, 
			pl_root, 
			bytes_left_in_pl_path
		);
		bytes_left_in_pl_path -= strlen(pl_root);
		if(bytes_left_in_pl_path <= PL_STRNCPY_MIN_BYTES) {
			pl_last_error = PL_OUT_OF_BUFFER_SPACE;
			goto pl_open_unlock_table;
		}

		//---------------------------------------------------------------------
		// pl_path = /opt/productivity_link/<x>_<uuid>/<y>
		//---------------------------------------------------------------------
		strncat(
			pl_path, 
			pl_buffer, 
			bytes_left_in_pl_path
		);
		bytes_left_in_pl_path -= strlen(pl_buffer);
		if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
			pl_last_error = PL_OUT_OF_BUFFER_SPACE;
			goto pl_open_unlock_table;
		}
		strncat(
			pl_path, 
			pl_eol_buffer, 
			bytes_left_in_pl_path
		);
		bytes_left_in_pl_path -= strlen(pl_eol_buffer);
		if(bytes_left_in_pl_path <= PL_STRNCAT_MIN_BYTES) {
			pl_last_error = PL_OUT_OF_BUFFER_SPACE;
			goto pl_open_unlock_table;
		}
		pl_config_file_bytes_to_write = strlen(pl_path);
		pl_config_file_bytes_written = write(
			pl_config_file, 
			pl_path, 
			pl_config_file_bytes_to_write
		);	
		if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) {
			pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
			goto pl_open_unlock_table;
		}
	} // for j

/*
 @@@@@   @@    @@@@   @@@@
   @    @  @  @    @ @    @
   @   @    @ @      @
   @   @    @ @       @@@@
   @   @@@@@@ @  @@@      @
   @   @    @ @    @      @
   @   @    @  @@@@  @@@@@
*/

#ifdef __PL_GENERATE_INI_VERSION_TAGGING__
	
	//-------------------------------------------------------------------------
	// Tag the productivity link configuration file with version information.
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		PL_VERSION_MAJOR, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_VERSION_MAJOR);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		PL_VERSION_TAG_SEPARATOR, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_VERSION_TAG_SEPARATOR);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		PL_VERSION_MINOR, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_VERSION_MINOR);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		PL_VERSION_TAG_SEPARATOR, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_VERSION_TAG_SEPARATOR);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		PL_VERSION_REVISION, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_VERSION_REVISION);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		PL_VERSION_TAG_OPEN, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_VERSION_TAG_OPEN);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		PL_VERSION_OS, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_VERSION_OS);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		PL_VERSION_TAG_CLOSE, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_VERSION_TAG_CLOSE);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);	
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) {
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED;
		goto pl_open_unlock_table;
	}
#endif // __PL_GENERATE_INI_VERSION_TAGGING__
#ifdef __PL_GENERATE_INI_BUILD_TAGGING__
	
	//-------------------------------------------------------------------------
	// Tag the productivity link configuration file with build information.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Generic build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef _DEBUG

	//-------------------------------------------------------------------------
	// _DEBUG
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[DEBUG_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[DEBUG_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _DEBUG
#ifdef _RELEASE

	//-------------------------------------------------------------------------
	// _RELEASE
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[RELEASE_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[RELEASE_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _RELEASE
#ifdef _CONSOLE

	//-------------------------------------------------------------------------
	// _CONSOLE
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[CONSOLE_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[CONSOLE_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _CONSOLE
#ifdef _UNICODE

	//-------------------------------------------------------------------------
	// _UNICODE
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[_UNICODE_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[_UNICODE_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _UNICODE
#ifdef UNICODE

	//-------------------------------------------------------------------------
	// UNICODE
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[UNICODE_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[UNICODE_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // UNICODE
#ifdef _ATL_STATIC_REGISTRY

	//-------------------------------------------------------------------------
	// _ATL_STATIC_REGISTRY
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[ATL_STATIC_REGISTRY_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[ATL_STATIC_REGISTRY_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _ATL_STATIC_REGISTRY
#ifdef __PL_LITTLE_ENDIAN__

	//-------------------------------------------------------------------------
	// __PL_LITTLE_ENDIAN__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_LITTLE_ENDIAN_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_LITTLE_ENDIAN_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_LITTLE_ENDIAN__
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// __PL_DYNAMIC_COUNTERS_ALLOCATION__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_DYNAMIC_COUNTERS_ALLOCATION_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_DYNAMIC_COUNTERS_ALLOCATION_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// __PL_EXTRA_INPUT_CHECKS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_EXTRA_INPUT_CHECKS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_EXTRA_INPUT_CHECKS_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_EXTRA_INPUT_CHECKS__
#ifdef __PL_AGENT__

	//-------------------------------------------------------------------------
	// __PL_AGENT__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_AGENT_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_AGENT_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_AGENT__
#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// __PL_FILESYSTEM_LESS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_FILESYSTEM_LESS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_FILESYSTEM_LESS_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// OS build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// __PL_WINDOWS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_WINDOWS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_WINDOWS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_WINDOWS__
#ifdef __PL_LINUX__

	//-------------------------------------------------------------------------
	// __PL_LINUX__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_LINUX_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_LINUX_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_LINUX__
#ifdef __PL_SOLARIS__

	//-------------------------------------------------------------------------
	// __PL_SOLARIS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_SOLARIS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_SOLARIS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_SOLARIS__
#ifdef __PL_MACOSX__

	//-------------------------------------------------------------------------
	// __PL_MACOSX__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
#ifdef __PL_IOS__
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_IOS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_IOS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
#else // __PL_IOS__
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_MACOSX_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_MACOSX_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
#endif // __PL_IOS__
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Dynamic library build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef _WINDLL

	//-------------------------------------------------------------------------
	// _WINDLL
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[WINDLL_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[WINDLL_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _WINDLL
#ifdef _USRDLL

	//-------------------------------------------------------------------------
	// _USRDLL
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[USRDLL_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[USRDLL_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // _USRDLL
#ifdef __PL_WINDOWS_DLL_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_WINDOWS_DLL_EXPORTS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_WINDOWS_DLL_EXPORTS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_WINDOWS_DLL_EXPORTS_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_WINDOWS_DLL_EXPORTS__
#ifdef __PL_LINUX_SO_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_LINUX_SO_EXPORTS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_LINUX_SO_EXPORTS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_LINUX_SO_EXPORTS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_LINUX_SO_EXPORTS__
#ifdef __PL_SOLARIS_SO_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_SOLARIS_SO_EXPORTS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_SOLARIS_SO_EXPORTS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_SOLARIS_SO_EXPORTS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_SOLARIS_SO_EXPORTS__
#ifdef __PL_MACOSX_SO_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_MACOSX_SO_EXPORTS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_MACOSX_SO_EXPORTS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_MACOSX_SO_EXPORTS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_MACOSX_SO_EXPORTS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// __PL_JNI_EXPORTS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_JNI_EXPORTS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_JNI_EXPORTS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// PL functional build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef __PL_BYPASS__

	//-------------------------------------------------------------------------
	// __PL_BYPASS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_BYPASS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_BYPASS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_BYPASS__
#ifdef __PL_GENERATE_INI__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_GENERATE_INI_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_GENERATE_INI_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI__
#ifdef __PL_GENERATE_INI_VERSION_TAGGING__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI_VERSION_TAGGING__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_GENERATE_INI_VERSION_TAGGING_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_GENERATE_INI_VERSION_TAGGING_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI_VERSION_TAGGING__
#ifdef __PL_GENERATE_INI_BUILD_TAGGING__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI_BUILD_TAGGING__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_GENERATE_INI_BUILD_TAGGING_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_GENERATE_INI_BUILD_TAGGING_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI_BUILD_TAGGING__
#ifdef __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_GENERATE_INI_DATE_AND_TIME_TAGGING_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_GENERATE_INI_DATE_AND_TIME_TAGGING_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__

	//-------------------------------------------------------------------------
	// __PL_BLOCKING_COUNTER_FILE_LOCK__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_BLOCKING_COUNTER_FILE_LOCK_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_BLOCKING_COUNTER_FILE_LOCK_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
#ifdef __PL_ATTACH_SCRIPT_SUPPORT__

	//-------------------------------------------------------------------------
	// __PL_ATTACH_SCRIPT_SUPPORT__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_ATTACH_SCRIPT_SUPPORT_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_ATTACH_SCRIPT_SUPPORT_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_ATTACH_SCRIPT_SUPPORT__
#ifdef __PL_UNDEF_T__

	//-------------------------------------------------------------------------
	// __PL_UNDEF_T__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_UNDEF_T_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_UNDEF_T_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_UNDEF_T__
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// __PL_TIMESTAMPING__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_TIMESTAMPING_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_TIMESTAMPING_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_TIMESTAMPING__
#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// __PL_BLOCKING_PL_READ__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_BLOCKING_PL_READ_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_BLOCKING_PL_READ_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_BLOCKING_PL_READ__

	//----------------------------------------------------------------------------
	// PL configuration reporting (use of forbidden modes in customer available
	// software is not allowed) - with __PL_AGENT__ exception.
	//----------------------------------------------------------------------------
#ifdef __PL_CONSTANT_UUID__

	//-------------------------------------------------------------------------
	// __PL_CONSTANT_UUID__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_CONSTANT_UUID_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_CONSTANT_UUID_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_CONSTANT_UUID__
#ifdef __PL_BINARY_COUNTER__

	//-------------------------------------------------------------------------
	// __PL_BINARY_COUNTER__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_BINARY_COUNTER_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_BINARY_COUNTER_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_BINARY_COUNTER__
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// __PL_DYNAMIC_TABLE_ALLOCATION__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
#ifdef __PL_AGENT__
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_DYNAMIC_TABLE_ALLOCATION_PL_AGENT_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_DYNAMIC_TABLE_ALLOCATION_PL_AGENT_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
#else // __PL_AGENT__
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_DYNAMIC_TABLE_ALLOCATION_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= 
		strlen(pl_build_tags[PL_DYNAMIC_TABLE_ALLOCATION_INDEX])
	;
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
#endif // __PL_AGENT__
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
#ifdef __PL_UNIT_TESTS__

	//-------------------------------------------------------------------------
	// __PL_UNIT_TESTS__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_UNIT_TESTS_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_UNIT_TESTS_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_UNIT_TESTS__
#ifdef __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// __PL_LOGGER_ONLY__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_LOGGER_ONLY_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_LOGGER_ONLY_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// Architecture specific build configuration reporting.
	//-------------------------------------------------------------------------
#ifdef __PL_NO_SSE_PAUSE_SUPPORT__

	//-------------------------------------------------------------------------
	// __PL_NO_SSE_PAUSE_SUPPORT__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		pl_build_tags[PL_NO_SSE_PAUSE_SUPPORT_INDEX], 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_build_tags[PL_NO_SSE_PAUSE_SUPPORT_INDEX]);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	strncat(
		pl_buffer, 
		pl_eol_buffer, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(pl_eol_buffer);
	if(bytes_left_in_pl_buffer <= PL_STRNCAT_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
#endif // __PL_GENERATE_INI_BUILD_TAGGING__
#ifdef __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__

	//-------------------------------------------------------------------------
	// __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	strncpy(
		pl_buffer, 
		PL_DATE_AND_TIME_INI_TAGGING_STRING, 
		bytes_left_in_pl_buffer
	);
	bytes_left_in_pl_buffer -= strlen(PL_DATE_AND_TIME_INI_TAGGING_STRING);
	if(bytes_left_in_pl_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_open_unlock_table;
	}
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	time(&pl_ini_time);
#ifdef __PL_SOLARIS__
	#ifdef __cplusplus
		ctime_r(
			&pl_ini_time, 
			&pl_buffer[pl_config_file_bytes_to_write]
		);
	#else // __cplusplus
		ctime_r(
			&pl_ini_time, 
			&pl_buffer[pl_config_file_bytes_to_write], 
			sizeof(pl_buffer) - strlen(PL_DATE_AND_TIME_INI_TAGGING_STRING)
		);
	#endif // __cplusplus
#else // __PL_SOLARIS__
	ctime_r(
		&pl_ini_time, 
		&pl_buffer[pl_config_file_bytes_to_write]
	);
#endif // __PL_SOLARIS__
	pl_config_file_bytes_to_write = strlen(pl_buffer);
	pl_config_file_bytes_written = write(
		pl_config_file, 
		pl_buffer, 
		pl_config_file_bytes_to_write
	);
	if(pl_config_file_bytes_written != pl_config_file_bytes_to_write) { 
		pl_last_error = PL_CONFIG_FILE_GENERATION_FAILED; 
		goto pl_open_unlock_table; 
	}
#endif // __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__

	//-------------------------------------------------------------------------
	// Close the productivity link configuration file.
	//-------------------------------------------------------------------------
	ret = close(pl_config_file);
	if(ret == -1) {
		pl_last_error = PL_CRITICAL_FAILURE;
	}
#endif // __PL_GENERATE_INI__
#endif // __PL_FILESYSTEM_LESS__

pl_open_unlock_table:

	//-------------------------------------------------------------------------
	// Unlock the productivity link table (locked against other threads).
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_post(pl_table.semaphore);
#else // __PL_MACOSX__
	ret = sem_post(&pl_table.semaphore);
#endif // __PL_MACOSX__
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}
pl_open_return:
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Return uuid to jvm. Java is big-endian, define __PL_LITTLE_ENDIAN__ if 
	// little-endian cpu.
	//-------------------------------------------------------------------------
	memset(
		uuid_bytes, 
		0, 
		sizeof(uuid_bytes)
	);
	pbyte = (char *)puuid;
#ifdef __PL_LITTLE_ENDIAN__
	uuid_bytes[0] = pbyte[6];
	uuid_bytes[1] = pbyte[7];
	uuid_bytes[2] = pbyte[4];
	uuid_bytes[3] = pbyte[5];
	uuid_bytes[4] = pbyte[0];
	uuid_bytes[5] = pbyte[1];
	uuid_bytes[6] = pbyte[2];
	uuid_bytes[7] = pbyte[3];
#endif // __PL_LITTLE_ENDIAN__
	(*interface_pointer)->SetLongField(
		interface_pointer, 
		java_puuid, 
		uuid_msb_field_id, 
		*(jlong *)uuid_bytes
	);
#ifdef __PL_LITTLE_ENDIAN__
	uuid_bytes[8]  = pbyte[15];
	uuid_bytes[9]  = pbyte[14];
	uuid_bytes[10] = pbyte[13];
	uuid_bytes[11] = pbyte[12];
	uuid_bytes[12] = pbyte[11];
	uuid_bytes[13] = pbyte[10];
	uuid_bytes[14] = pbyte[9];
	uuid_bytes[15] = pbyte[8];
#endif // __PL_LITTLE_ENDIAN__
	(*interface_pointer)->SetLongField(
		interface_pointer, 
		java_puuid, 
		uuid_lsb_field_id, 
		*(jlong *)(&uuid_bytes[8])
	);

	//-------------------------------------------------------------------------
	// Release java arguments.
	//-------------------------------------------------------------------------
	if(pl_application_name != NULL) {
		(*interface_pointer)->ReleaseStringUTFChars(
			interface_pointer, 
			java_pl_application_name, 
			pl_application_name
		);
	}
	for(i = 0; i < pl_counters_count; i++) {
		if(pl_counters_names[i] != NULL) {
			(*interface_pointer)->ReleaseStringUTFChars(
				interface_pointer, 
				string_object, 
				native_string
			); 
		}
	}
	if(pl_counters_names != NULL) {
		free((void *)pl_counters_names);
	}
	if(puuid != NULL) {
		free((void *)puuid);
	}
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Set last error and return status.
	//-------------------------------------------------------------------------
	if(pl_last_error != PL_NO_ERROR) {
		errno = pl_last_error;
		return(PL_INVALID_DESCRIPTOR);
	} else {
		pl_last_error = PL_NO_ERROR;
		errno = pl_last_error;
	}
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Timestamp all counters of the opened PL.
	// Open timestamp is set.
	// Last attach timestamp is reset.
	// Last read timestamp is reset.
	// Last write timestamp is reset.
	// Last close timestamp is reset - all reset done at init time.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[index].pl_counters_count; j++) {
		pl_table.pl_array[index].open_time[j] = time(NULL);
	}
#endif // __PL_TIMESTAMPING__
	return(index);
#endif // __PL_BYPASS__
}

/*-----------------------------------------------------------------------------
@@@@@  @               @@    @@@@@  @@@@@   @@    @@@@  @    @
@    @ @              @  @     @      @    @  @  @    @ @    @
@    @ @             @    @    @      @   @    @ @      @    @
@@@@@  @             @    @    @      @   @    @ @      @@@@@@
@      @             @@@@@@    @      @   @@@@@@ @      @    @
@      @             @    @    @      @   @    @ @    @ @    @
@      @@@@@@        @    @    @      @   @    @  @@@@  @    @
              @@@@@@
Function: pl_attach
Purpose : attaches to an existig productivity link
In      : pointer to a productivity link configuration file name
Out     : none
Return  : productivity link descriptor and last error set if invalid descriptor
          returned

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/01/2008    Jamel Tayeb             Creation.
06/04/2010    Jamel Tayeb             Added __PL_FILESYSTEM_LESS__ support.
10/21/2010    Jamel Tayeb             Added __PL_EXTRA_INPUT_CHECKS__ support.
*/
#ifdef __PL_JNI_EXPORTS__
JNIEXPORT jint JNICALL Java_ProductivityLink_pl_1attach(
	JNIEnv *interface_pointer, 
	jobject caller_reference, 
	jstring java_pl_config_file_name
) {

	const char *pl_config_file_name = NULL;
#else // __PL_JNI_EXPORTS__
PL_API int pl_attach(const char *pl_config_file_name) {
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// If __PL_BYPASS__ is defined, set system's last error code to 
	// PL_BYPASSED and return.
	//-------------------------------------------------------------------------
#if defined (__PL_BYPASS__) || (__PL_LOGGER_ONLY__)
#ifdef __PL_WINDOWS__
	SetLastError(PL_BYPASSED);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	errno = PL_BYPASSED;
#endif // __PL_LINUX__ || __PL_SOLARIS || __PL_MACOSX__
	return(PL_INVALID_DESCRIPTOR);
#else // __PL_BYPASS__ || __PL_LOGGER_ONLY__
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
	unsigned int pl_old_max_productivity_links = 0;
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
#if defined (__PL_DYNAMIC_COUNTERS_ALLOCATION__) || (__PL_DYNAMIC_TABLE_ALLOCATION__)
	size_t memory_size = 0;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__ || __PL_DYNAMIC_TABLE_ALLOCATION__
	unsigned int index = 0;
	size_t bytes_count = 0;
	size_t bytes_left_in_buffer = 0;

#ifdef __PL_FILESYSTEM_LESS__
	int one = 1;
	unsigned int j = 0;
	char *message = NULL;
	char *p_string = NULL;
	char pl_input_buffer[PL_MAX_INPUT_BUFFER_SIZE] = { '\0' };
	char pl_output_buffer[PL_MAX_OUTPUT_BUFFER_SIZE] = { '\0' };
	SOCKET pl_socket = INVALID_SOCKET;
	size_t total_bytes_to_read = 0;
	PL_PROTOCOL_STATUS pret = PL_PROTOCOL_FAILURE;
	PL_PROTOCOL_SIZET message_size = 0;
	int connection_attempt_count = 0;
	#ifdef __PL_WINDOWS__
		ADDRINFO *pa = NULL;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		struct addrinfo *pa = NULL;
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	#ifdef __PL_EXTRA_INPUT_CHECKS__

		//---------------------------------------------------------------------
		// Generic variables used to checks.
		//---------------------------------------------------------------------
		int value = -1;

		//---------------------------------------------------------------------
		// Variables used to check validity of IPV4 address.
		//---------------------------------------------------------------------
		int dot_count = 0;
		int digit_count = 0;
		char ip_v4_address_value_string[
			PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_BUFFER_SIZE
		] = { '\0' };
		PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_CLASSES ip_v4_class = 
			PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A
		;
		static char allowed_characters_in_ip_v4_address[
			PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS_COUNT
		] = { PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS };

		//---------------------------------------------------------------------
		// Variables used to check validity of port.
		//---------------------------------------------------------------------
		char port_value_string[
			PL_EXTRA_INPUT_CHECKS_PORT_MAX_BUFFER_SIZE
		] = { '\0' };
		static char allowed_characters_in_port[
			PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS_COUNT
		] = { PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS };
	#endif // __PL_EXTRA_INPUT_CHECKS__
#else // __PL_FILESYSTEM_LESS__ 
	char *px = NULL;
	unsigned int j = 0;
	int lines = 0;
	int pl_counters_count = 0;
	char *pl_folder_substitute = NULL;
	char pl_local_pl_folder[PL_MAX_PATH] = { '\0' };
	int pl_folder_substitution = 0;
	char pl_temp[PL_MAX_PATH] = { '\0' };
	char pl_buffer[PL_MAX_PATH] = { '\0' };
	char *p = NULL;
	int char_count = 0;
	size_t bytes_left_in_pl_buffer = 0;
	char *config_file_name = NULL;
	char *uuid = NULL;
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		char uuid_cvt_buffer[PL_MAX_PATH] = { '\0' };
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	#ifdef __PL_EXTRA_INPUT_CHECKS__

		//---------------------------------------------------------------------
		// Variables used for buffer and input checks.
		//---------------------------------------------------------------------
		char reference_application_name[PL_MAX_PATH] = { '\0' };
		char reference_uuid[PL_UUID_MAX_CHARS + 1] = { '\0' };
		char reference_path[PL_MAX_PATH] = { '\0' };
		char character = '\0';
		size_t bytes_in_reference_path = 0;
	#endif // __PL_EXTRA_INPUT_CHECKS__
#endif // __PL_FILESYSTEM_LESS__

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Generic variables uesed for buffer and input checks.
	//-------------------------------------------------------------------------
	char *pchar = NULL;
	int m = 0;
	int n = 0;
	#ifndef __PL_FILESYSTEM_LESS__

		//---------------------------------------------------------------------
		// Variables used to check validity of PL configuration file counter.
		//---------------------------------------------------------------------
		size_t buffer_index = 0;
		char *application_name = NULL;
		size_t pl_buffer_length = 0;
		char *pl_buffer_end = NULL;
		
		//---------------------------------------------------------------------
		// Variables used to check validity of UUID, application name, counter
		// count.
		//---------------------------------------------------------------------
		int dash_count = 0;
		int block_byte_count = 0;
		static char allowed_characters_in_uuid[
			PL_EXTRA_INPUT_CHECKS_UUID_ALLOWED_CHARACTERS_COUNT
		] = { PL_EXTRA_INPUT_CHECKS_UUID_ALLOWED_CHARACTERS };
		static char allowed_characters_in_counter_name[
			PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT
		] = { PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS };
		static char allowed_characters_in_application_name[
			PL_EXTRA_INPUT_CHECKS_APPLICATION_NAME_ALLOWED_CHARACTERS_COUNT
		] = { PL_EXTRA_INPUT_CHECKS_APPLICATION_NAME_ALLOWED_CHARACTERS };
		static char allowed_characters_in_counters_count[
			PL_EXTRA_INPUT_CHECKS_COUNTERS_COUNT_ALLOWED_CHARACTERS_COUNT
		] = { PL_EXTRA_INPUT_CHECKS_COUNTERS_COUNT_ALLOWED_CHARACTERS };
	#endif // !__PL_FILESYSTEM_LESS__
#endif // __PL_EXTRA_INPUT_CHECKS__

#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// @    @ @@@@@  @    @ @@@@@   @@@@  @    @  @@@@
	// @    @   @    @@   @ @    @ @    @ @    @ @    @
	// @  @ @   @    @ @  @ @    @ @    @ @  @ @  @@@@
	//  @ @ @   @    @   @@ @    @ @    @  @ @ @      @
	//   @ @  @@@@@  @    @ @@@@@   @@@@    @ @  @@@@@
	//-------------------------------------------------------------------------
	int ret = 0;
	size_t st_ret = 0;
	RPC_STATUS rpc_ret = 0;	
	DWORD dw_ret = 0;
	DWORD pl_last_error = PL_NO_ERROR;
	BOOL b_ret = FALSE;
	HANDLE pl_config_file = NULL;
	DWORD pl_config_file_bytes_to_read = 0;
	DWORD pl_config_file_bytes_read = 0;
	TCHAR pl_path[PL_MAX_PATH] = { 0 };
	TCHAR pl_cvt_buffer[PL_MAX_PATH] = { 0 };
#ifdef __PL_BLOCKING_PL_READ__
	TCHAR pl_folder[PL_MAX_PATH] = { 0 };
	char pl_folder_buffer[PL_MAX_PATH] = { 0 };
	size_t pl_lenght = 0;
#endif // __PL_BLOCKING_PL_READ__
#ifdef __PL_FILESYSTEM_LESS__
	static BOOL fw_initialized = FALSE;
	char *env_address = NULL;
	char *env_port = NULL;
	WSADATA windows_socket_data;
	errno_t eno_ret = -1;
	size_t length = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	DWORD dwret = 0;
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Get the java arguments.
	//-------------------------------------------------------------------------
	pl_config_file_name = (*interface_pointer)->GetStringUTFChars(
		interface_pointer, 
		java_pl_config_file_name, 
		NULL
	);
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Check calling arguments.
	//-------------------------------------------------------------------------
	if(pl_config_file_name == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Perform the following input data checking:
	//   - PL configuration file name length is less than PL_MAX_PATH.
	//   - <PL_FOLDER> is present at the beginning of the input string.
	//   - PL_INI_NIX_PATH_SEPARATOR follows <PL_FOLDER> in the input string.
	//   - <PL_INI_CONFIG_FILE_NAME> at the end of the input string.
	//   - NULL follows <PL_INI_CONFIG_FILE_NAME> at the end of the input 
	//     string.
	//   - <UUID> has a correct structure:
	//      - <UUID> has only allowed characters.
	//      - <UUID> has 4 dashes and five character blocks.
	//      - <UUID> 1st block has 8 characters.
	//      - <UUID> 2nd block has 4 characters.
	//      - <UUID> 3rd block has 4 characters.
	//      - <UUID> 4st block has 4 characters.
	//      - <UUID> 5th block has 12 characters.
	// Note:
	//    <PL_FOLDER>/<application_name>_<UUID>/<PL_INI_CONFIG_FILE_NAME>
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Check PL configuration file name length.
	//-------------------------------------------------------------------------
	pchar = (char *)pl_config_file_name;
	bytes_count = 0;
	while(
		(bytes_count < PL_MAX_PATH) &&
		(*pchar != '\0')
	) {
			bytes_count++;
			pchar++;
	}
	if(bytes_count >= PL_MAX_PATH) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	bytes_left_in_buffer = bytes_count;
	if(bytes_left_in_buffer >= PL_MAX_PATH) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}

#ifndef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Note:
	//    in filesystem-less mode, the configuration ini file can be provided
	//    in both, Windows or *NIX format.  Therefore, the location testing
	//    is skipped at this stage.  It should be performed by the agent, or
	//    it will be performed if the agent uses pl_attach in file system mode.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Check <PL_FOLDER>/
	//-------------------------------------------------------------------------
	buffer_index = strlen(PL_INI_WINDOWS_ROOTLESS_FOLDER);
	if(bytes_left_in_buffer < buffer_index) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		(*pl_config_file_name != PL_INI_WINDOWS_PL_FOLDER_ROOT_CHAR) &&
		(*pl_config_file_name != PL_INI_WINDOWS_PL_FOLDER_ROOT_UPPER_CHAR)
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		strncmp(
			pl_config_file_name + 1,
			PL_INI_WINDOWS_ROOTLESS_FOLDER,
			buffer_index
		) != 0
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		pl_config_file_name[++buffer_index] !=
		PL_INI_WINDOWS_PATH_SEPARATOR_CHAR
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	application_name = (char *)&pl_config_file_name[++buffer_index];

	//-------------------------------------------------------------------------
	// Check for <PL_INI_CONFIG_FILE_NAME> presence.
	//-------------------------------------------------------------------------
	config_file_name = strstr(
		pl_config_file_name,
		PL_INI_CONFIG_FILE_NAME
	);
	if(config_file_name == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(config_file_name <= pl_config_file_name) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		*(config_file_name + strlen(PL_INI_CONFIG_FILE_NAME)) != 
		'\0'
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	config_file_name--;
	if(
		*config_file_name != 
		PL_INI_WINDOWS_PATH_SEPARATOR_CHAR
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	
	//-------------------------------------------------------------------------
	// Find the UUID.
	//-------------------------------------------------------------------------
	uuid = config_file_name - PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS;
	if(uuid <= pl_config_file_name) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(uuid <= application_name) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		*(uuid - 1) !=
		PL_INI_APPLICATION_NAME_SEPARATOR_CHAR
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}

	//-------------------------------------------------------------------------
	// Search illegal character in UUID and obvious bad format.
	//-------------------------------------------------------------------------
	for(n = 0; n < PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS; n++) {
		if(uuid[n] == PL_EXTRA_INPUT_CHECKS_UUID_DASH_CHARACTER) {
			dash_count++; 
			switch(dash_count) {

				case 1:

					//---------------------------------------------------------
					// First UUID block (nnnnnnnn-0000-0000-0000-000000000000).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK1_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					block_byte_count = 0;
					goto pl_attach_check_uuid_next;

				case 2:

					//---------------------------------------------------------
					// Second UUID block (00000000-nnnn-0000-0000-000000000000).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK2_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					block_byte_count = 0;
					goto pl_attach_check_uuid_next;

				case 3:

					//---------------------------------------------------------
					// Third UUID block (00000000-0000-nnnn-0000-000000000000).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK3_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					block_byte_count = 0;
					goto pl_attach_check_uuid_next;

				case 4:

					//---------------------------------------------------------
					// Fourth UUID block (00000000-0000-0000-nnnn-000000000000).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK4_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					block_byte_count = 0;
					goto pl_attach_check_uuid_next;

				default:
					pl_last_error = PL_INVALID_PARAMETERS;
					goto pl_attach_return;
			} // switch
		}
		for(
			m = 0; 
			m < PL_EXTRA_INPUT_CHECKS_UUID_ALLOWED_CHARACTERS_COUNT; 
			m++
		) {
			if(uuid[n] == allowed_characters_in_uuid[m]) {
				block_byte_count++;
				goto pl_attach_check_uuid_next;
			}
		}
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_check_uuid_error;
pl_attach_check_uuid_next:
		;
	}

	//-------------------------------------------------------------------------
	// Fifth UUID block (00000000-0000-0000-0000-nnnnnnnnnnnn).
	//-------------------------------------------------------------------------
	if(
		block_byte_count != 
		PL_EXTRA_INPUT_CHECKS_UUID_BLOCK5_SIZE
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	goto pl_attach_check_uuid_ok;
pl_attach_check_uuid_error:
	goto pl_attach_return;
pl_attach_check_uuid_ok:
	;
#endif // !__PL_FILESYSTEM_LESS__
#endif // __PL_EXTRA_INPUT_CHECKS__

#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// In file system-less mode, a pl_attach is carried-out in two steps.  Fir-
	// st step uses the PL protocol to send a pl_attach request to a PL agent 
	// (identified via the default agent IP @ / port or user provided environm-
	// ent variables.  The remote agent will carry out the pl_attach API call 
	// and will return the remote pld and status.  The remote pld will be stored
	// into the PL table and a local pld is returned with the uuid to the 
	// calling process and a uuid is generated on the local system for the 
	// remote PL.  The protocol requires that the agent returns also the coun-
	// ters count.  This count is then used to locally create the counters
	// entries in the local PL table.
	// Note:
	//    Locally, with the exception of the two-step process, pl_attach beha-
	//    ves as a pl_open in this mode.
	// ------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// First pl_attach call takes the pl_table initialization penalty.
	//-------------------------------------------------------------------------
	if(pl_table_initialized == FALSE) {
#ifdef _DEBUG

		//---------------------------------------------------------------------
		// Dump memory leak info on any exit.
		//---------------------------------------------------------------------
		dw_ret = _CrtSetDbgFlag(
			_CRTDBG_ALLOC_MEM_DF | 
			_CRTDBG_LEAK_CHECK_DF
		);
		assert(dw_ret != -1);

		//---------------------------------------------------------------------
		// Redirect dump to stdout.
		//---------------------------------------------------------------------
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
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Allocate dynamically the pl_table -- fixed to default size.
		// This size will de expanded if needed later on and during each future 
		// call to pl_attach/pl_open.
		// Caution: this memory will not be freed! (__PL_DYNAMIC_TABLE_ALLOCA-
		// TION__).  Therefore it should never be defined or you can take 
		// responsibility to free it up (as in the PL Agent).
		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ defined
		// --------------------------------------------
		//
		//                                  |<----- LIMITED BY AVAILABLE MEMORY ---->|
		// +-----------------+------+       +------+------+--        --+------+------+
		// |                 |      |       |      |      |            |      |      |
		// | PL table access | *PL -+-----> | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |      |       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |       |      |      |            |      |      |
		// +-----------------+------+       +------+------+--        --+------+------+
		//---------------------------------------------------------------------
		ZeroMemory(
			&pl_table, 
			sizeof(pl_table)
		);
		memory_size = 
			sizeof(PRODUCTIVITY_LINK) * 
			PL_MAX_PRODUCTIVITY_LINKS
		;
		pl_table.pl_array = (PPRODUCTIVITY_LINK)malloc(memory_size);
		if(pl_table.pl_array == NULL) {
			pl_last_error = PL_OUT_OF_MEMORY;
			goto pl_attach_return;
		}
		// next nulls in-use flags and the handle pointers
		ZeroMemory(
			pl_table.pl_array, 
			memory_size
		); 
		pl_max_productivity_links = PL_MAX_PRODUCTIVITY_LINKS;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ NOT defined
		// ------------------------------------------------
		//
		//                   |<----- PL_MAX_PRODUCTIVITY_LINKS ------>|
		// +-----------------+------+------+--        --+------+------+
		// |                 |      |      |            |      |      |
		// | PL Table access | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |      |            |      |      |
		// +-----------------+------+------+--        --+------+------+
		//---------------------------------------------------------------------
		// next nulls in-use flags and the all handles
		ZeroMemory(
			&pl_table, 
			sizeof(PL_TABLE)
		); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Create PL Table semaphore.
		// --------------------------------------------------------------------
		pl_table.semaphore = CreateSemaphore(
			NULL, 
			(LONG)1, 
			(LONG)1, 
			NULL
		);
		if(pl_table.semaphore == NULL) {
			pl_last_error = PL_SYNCHRONIZATION_FAILED;
			goto pl_attach_return;
		}

		//---------------------------------------------------------------------
		// Initialize Winsoks to communicate with the agent.
		//---------------------------------------------------------------------
		if(fw_initialized == FALSE) {
			ret = WSAStartup(
				MAKEWORD(2, 2), 
				&windows_socket_data
			);
			if(ret != 0) {
				pl_last_error = PL_FILESYSTEM_LESS_INITIALIZATION_FAILED;
				goto pl_attach_return;
			}
			fw_initialized = TRUE;
		}
		pl_table_initialized = TRUE;
	} // if pl_table_initialized == FALSE

	//-------------------------------------------------------------------------
	// Lock the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
	dw_ret = WaitForSingleObject(
		pl_table.semaphore, 
		INFINITE
	);
	if(dw_ret != WAIT_OBJECT_0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_attach_return;
	}
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < PL_MAX_PRODUCTIVITY_LINKS; index++) {
		if(pl_table.pl_array[index].pl_in_use == FALSE) {
			goto pl_attach_found;
		}
	}
	// pl_table full
	pl_last_error = PL_DESCRIPTOR_TABLE_FULL;
	goto pl_attach_unlock_table;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < pl_max_productivity_links; index++) {
		if(pl_table.pl_array[index].pl_in_use == FALSE) {
			goto pl_attach_found;
		}
	}

	//-------------------------------------------------------------------------
	// No room in the table, lets double dynamically the pl_table size and
	// create the additional counters.
	//-------------------------------------------------------------------------
	pl_old_max_productivity_links = pl_max_productivity_links; 
	pl_max_productivity_links *= 2;
	pl_table.pl_array = (PPRODUCTIVITY_LINK)realloc(
		pl_table.pl_array, 
		sizeof(PRODUCTIVITY_LINK) * pl_max_productivity_links
	);
	if(pl_table.pl_array == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	// clear newly allocated memory
	ZeroMemory(
		&pl_table.pl_array[index], 
		sizeof(PRODUCTIVITY_LINK) * pl_old_max_productivity_links
	);
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
pl_attach_found:
	pl_table.pl_array[index].pl_in_use = TRUE;

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_ADDRESS environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	bytes_left_in_buffer = sizeof(pl_table.pl_array[index].pl_address);
	eno_ret = _dupenv_s(
		&env_address,
		&length,
		PL_DEFAULT_PL_AGENT_ADDRESS_ENVAR_NAME
	);
	if(bytes_left_in_buffer < length) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_attach_return;
	}
	if(
		(eno_ret != 0) ||
		(length == 0)
	) {
		strncpy_s(
			pl_table.pl_array[index].pl_address,
			bytes_left_in_buffer,
			PL_DEFAULT_PL_AGENT_ADDRESS,
			_TRUNCATE
		);
		length = strlen(PL_DEFAULT_PL_AGENT_ADDRESS);
	} else {
		strncpy_s(
			pl_table.pl_array[index].pl_address,
			bytes_left_in_buffer,
			env_address,
			_TRUNCATE
		);
		free(env_address);
		env_address = NULL;
	}
	bytes_left_in_buffer -= length;
	if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_attach_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Check the validity of the IPV4 address.
	// Note:
	//    Class A: 000.000.000.000 to 127.255.255.255
	//    Class B: 128.000.000.000 to 191.255.255.255
	//    Class C: 192.000.000.000 to 223.255.255.255
	//    Class D: 224.000.000.000 to 239.255.255.255
	//    Class E: 240.000.000.000 to 255.255.255.255
	//-------------------------------------------------------------------------
	length--;
	for(m = 0; m < (int)length; m++) {

		//---------------------------------------------------------------------
		// Ckeck that only legal characters are used.
		//---------------------------------------------------------------------
		if(
			pl_table.pl_array[index].pl_address[m] == 
			PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_DOT_CHARACTER
		) { 
			if(digit_count == 0) {

				//-------------------------------------------------------------
				// No address can start without a digit.
				//-------------------------------------------------------------
				goto pl_attach_check_ip_v4_address_error; 
			}

			//-----------------------------------------------------------------
			// A dot was found, let's process the address value as stored.
			//-----------------------------------------------------------------
			dot_count++;
			digit_count = 0;
			ip_v4_address_value_string[
				PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE
			] = '\0';
			value = atoi(ip_v4_address_value_string);
			memset(
				ip_v4_address_value_string, 
				0, 
				sizeof(ip_v4_address_value_string)
			);
			
			//-----------------------------------------------------------------
			// Use the . character count to check address value ranges.
			//-----------------------------------------------------------------
			switch(dot_count) {

				case 1:

					//---------------------------------------------------------
					// This is the first address value (nnn.xxx.xxx.xxx).
					// Assign a class to the address based on the first address
					// value.
					//---------------------------------------------------------
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E; 
						break; 
					}
					goto pl_attach_check_ip_v4_address_error;
					break;

				case 2:

					//---------------------------------------------------------
					// This is the second address value (xxx.nnn.xxx.xxx).
					// Check the second address value based on the class 
					// assigned using the first address value
					//---------------------------------------------------------
					switch(ip_v4_class) {
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						default:

							//-------------------------------------------------
							// Invalid second address value.
							//-------------------------------------------------
							goto pl_attach_check_ip_v4_address_error;
					} // switch
					break;

				case 3: // third number

					//---------------------------------------------------------
					// This is the third address value (xxx.xxx.nnn.xxx).
					// Check the third address value based on the class 
					// assigned using the first address value
					//---------------------------------------------------------
					switch(ip_v4_class) {
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						default:

							//-------------------------------------------------
							// Invalid second address value.
							//-------------------------------------------------
							goto pl_attach_check_ip_v4_address_error;
					} // switch
					break;

				default:

					//---------------------------------------------------------
					// This is the fourth address value (xxx.xxx.xxx.nnn).
					// Note:
					//    Fourth address value is tested later on, however if 
					//    we are here, it is an error.
					//---------------------------------------------------------
					goto pl_attach_check_ip_v4_address_error;
			}

		} else {

			//-----------------------------------------------------------------
			// This is not a dot (.) character, check if it is an allowed one.
			//-----------------------------------------------------------------
			for(
				n = 0; 
				n < PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS_COUNT; 
				n++
			) {
				if(
					pl_table.pl_array[index].pl_address[m] == 
					allowed_characters_in_ip_v4_address[n]
				) {
					ip_v4_address_value_string[digit_count++] = 
						pl_table.pl_array[index].pl_address[m]
					;
					if(
						digit_count > 
						PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DIGITS_IN_ADDRESS_VALUE
					) { 
						goto pl_attach_check_ip_v4_address_error; 
					}
					goto pl_attach_check_ip_v4_address_next;
				}
			} // for n
			goto pl_attach_check_ip_v4_address_error;
		}
pl_attach_check_ip_v4_address_next:
		;
	} // for m

	//-------------------------------------------------------------------------
	// check if after the last dot (.) we have at least one digit as this 
	// cannot be trapped in the loop above.
	//-------------------------------------------------------------------------
	if(digit_count == 0) { 
		goto pl_attach_check_ip_v4_address_error; 
	}

	//-------------------------------------------------------------------------
	// check ip address string has three (3) dots (.)
	//-------------------------------------------------------------------------
	if(
		dot_count != 
		PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DOT_CHARACTERS_IN_ADDRESS
	) { 
		goto pl_attach_check_ip_v4_address_error; 
	}

	//-------------------------------------------------------------------------
	// check fouth number's range
	//-------------------------------------------------------------------------
	ip_v4_address_value_string[
		PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE
	] = '\0';
	value = atoi(ip_v4_address_value_string);
	
	//-------------------------------------------------------------------------
	// This is the fourth address value (xxx.xxx.xxx.nnn).
	// Check the fourth address value based on the class assigned using the 
	// first address value.
	//-------------------------------------------------------------------------
	switch(ip_v4_class) {
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		default:

			//-----------------------------------------------------------------
			// Invalid second address value.
			//-----------------------------------------------------------------
			goto pl_attach_check_ip_v4_address_error;
	} // switch
	goto pl_attach_check_ip_v4_address_ok;
pl_attach_check_ip_v4_address_error:
	pl_last_error = PL_FILESYSTEM_LESS_INVALID_IPV4_ADDRESS;
	goto pl_attach_return;
pl_attach_check_ip_v4_address_ok:
	;
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_PL_PORT environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	bytes_left_in_buffer = sizeof(pl_table.pl_array[index].pl_port);
	eno_ret = _dupenv_s(
		&env_port,
		&length,
		PL_DEFAULT_PL_PORT_ENVAR_NAME
	);
	if(bytes_left_in_buffer < length) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_attach_return;
	}
	if(
		(eno_ret != 0) ||
		(length == 0)
	) {
		strncpy_s(
			pl_table.pl_array[index].pl_port,
			bytes_left_in_buffer,
			PL_DEFAULT_PL_AGENT_PL_PORT,
			_TRUNCATE
		);
		length = strlen(pl_table.pl_array[index].pl_port);
	} else {
		strncpy_s(
			pl_table.pl_array[index].pl_port,
			bytes_left_in_buffer,
			env_port,
			_TRUNCATE
		);
		free(env_port);
		env_port = NULL;
	}
	bytes_left_in_buffer -= length;
	if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_attach_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Check the validity of the port.
	// Note:
	//    Valid port number is in the 1-65535 range
	//    PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE
	//    PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE
	//-------------------------------------------------------------------------
	digit_count = 0;
	for(m = 0; m < (int)length; m++) {
		for(
			n = 0; 
			n < PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS_COUNT; 
			n++
		) {
			if(
				pl_table.pl_array[index].pl_port[m] == 
				allowed_characters_in_port[n]
			) {
				port_value_string[digit_count++] = 
					pl_table.pl_array[index].pl_port[m]
				;
				if(
					digit_count > 
					PL_EXTRA_INPUT_CHECKS_PORT_MAX_DIGITS_IN_PORT_VALUE
				) { 
					goto pl_attach_check_port_error; 
				}
				goto pl_attach_check_port_next;
			}
		} // for n
		goto pl_attach_check_port_error;
pl_attach_check_port_next:
		;
	} // for m

	//-------------------------------------------------------------------------
	// Check port value range.
	//-------------------------------------------------------------------------
	port_value_string[
		PL_EXTRA_INPUT_CHECKS_PORT_BUFFER_LAST_BYTE
	] = '\0';
	value = atoi(port_value_string);
	if(
		(value < PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE) || 
		(value > PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE)
	) {
		goto pl_attach_check_port_error;
	}
	goto pl_attach_check_port_ok;
pl_attach_check_port_error:
	pl_last_error = PL_FILESYSTEM_LESS_INVALID_PORT;
	goto pl_attach_return;
pl_attach_check_port_ok:
	;
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Initialize address data.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_table.pl_array[index].address_info_hint, 
		sizeof(pl_table.pl_array[index].address_info_hint)
	);
	pl_table.pl_array[index].address_info_hint.ai_family = 
		PL_ADDRESS_INFO_HINT_AI_FAMILY
	;
	pl_table.pl_array[index].address_info_hint.ai_socktype = 
		PL_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	pl_table.pl_array[index].address_info_hint.ai_protocol = 
		PL_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	pl_table.pl_array[index].address_info_hint.ai_flags = 
		PL_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve agent address and port.
	//-------------------------------------------------------------------------
	ret = getaddrinfo(
		pl_table.pl_array[index].pl_address,
		pl_table.pl_array[index].pl_port, 
		&pl_table.pl_array[index].address_info_hint, 
		&pl_table.pl_array[index].address_info
	);
	if(ret != 0) { 
		pl_last_error = 
			PL_FILESYSTEM_LESS_NETWORK_ADDRESS_RESOLUTION_FAILED;
		goto pl_attach_return;
	}

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_ATTACH command.
	//-------------------------------------------------------------------------
	// pl_attach()
	// +-----------+-------------------------------------------------------------+
	// | OPERATION | <string>                                                    |
	// | CODE      | PL CONFIG INI                                               |
	// |           | ABSOLUTE PATH                                               |
	// +---------- +-------------------------------------------------------------+
	// ^           ^
	// |           |
	// |<--- A --->|<---------------------- B ---------------------------------->
	// |           |
	// |           +--------------- PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX
	// +--------------------------- PL_PROTOCOL_PL_ATTACH_INPUT_OPCODE_INDEX
	//
	// Note:
	//    A = PL_PROTOCOL_OPCODE_SIZE
	//    B = variable
	// Note:
	//    PL_FOLDER transposition - if required - is performed by the agent.
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_ATTACH_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_ATTACH;
	p_string = (char *)pl_config_file_name;
	length = strlen(p_string);
	message_size = (PL_PROTOCOL_SIZET)length;
	memcpy(
		&message[PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	sprintf(
		&message[
			PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX +
			PL_PROTOCOL_SIZET_SIZE
		],
		"%s",
		p_string
	);
	p_string = &message[
		PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX +
		PL_PROTOCOL_SIZET_SIZE +
		length
	];
	*p_string = PL_PROTOCOL_EOR;
	bytes_to_send +=
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_SIZET_SIZE +
		length +
		PL_PROTOCOL_EOR_SIZE
	;
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_attach_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[index].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_socket = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(pl_socket == INVALID_SOCKET) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_attach_unlock_table;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_socket,
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_attach_unlock_table;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_socket,
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, closethe socket.
			//-----------------------------------------------------------------
			ret = closesocket(
				pl_socket
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_attach_unlock_table;
			}
			continue;
		}
		goto pl_attach_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on WSAEADDRINUSE:
	//    If you call pl_write at a too high frequency, you may exhaust the
	//    short lived TCP ports.  The default range of short lived ports is 
	//    from 1025 to 5000. Ways to workaround are to increase the dynamic port 
	//    range (to 65534) by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\MaxUserPort;
	//    or by reducing TIME_WAIT from the default 240s (4 minutes) to 30s
	//    by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\TCPTimedWaitDelay
	//-------------------------------------------------------------------------
	dwret = GetLastError();
	if(dwret == WSAEADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_attach_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_attach_unlock_table;

pl_attach_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_ATTACH command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_socket,
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_attach_unlock_table;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer
	//-------------------------------------------------------------------------
	// pl_attach() return
	// +----------+-----------+-----------+----------+
	// | STATUS   | UUID      | PLD       | COUNTERS |
	// | CODE     |           |           | COUNT    |
	// +----------+-----------+-----------+----------+ <-- PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX
	// ^          ^ (LSB-MSB) ^ (LSB-MSB) ^ (LSB-MSB)         
	// |          |           |           |
	// |<-- A --->|<--- B --->|<--- C --->|<-- D --->
	// |          |           |           +--- PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX
	// |          |           +--------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX
	// |          +--------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX
	// +-------------------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//   D = PL_PROTOCOL_COUNTERS_COUNT_SIZE
	// Note:
	//   The uuid is created by the agent and is not exposed to the client.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_input_buffer, 
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_attach_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (PL_PROTOCOL_SIZET)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_attach_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close PL socket.
	//-------------------------------------------------------------------------
	ret = closesocket(
		pl_socket
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_attach_unlock_table;
	}
	pl_socket = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Extract agent's answer (including the counters count).
	//-------------------------------------------------------------------------
	memcpy(
		&pl_table.pl_array[index].uuid,
		&pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX],
		PL_PROTOCOL_UUID_SIZE
	 );
	memcpy(
		&pl_table.pl_array[index].remote_pld,
		&pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX],
		PL_PROTOCOL_PLD_SIZE
	);
	memcpy(
		&pl_table.pl_array[index].pl_counters_count,
		&pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX],
		PL_PROTOCOL_COUNTERS_COUNT_SIZE
	);
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// At this stage the counters count for the attached PL is known.
	// Allocate memory for the number of counters for the write cache, the
	// the time stamps (if any), the counter access semaphores and sockets.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Allocate memory for the write cache.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(unsigned long long) * 
		pl_table.pl_array[index].pl_counters_count
	;
	pl_table.pl_array[index].pl_write_cache = 
		(unsigned long long *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_write_cache == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_write_cache, 
		memory_size
	);
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate timestamps memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(time_t) * 
		pl_table.pl_array[index].pl_counters_count
	;
	pl_table.pl_array[index].open_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].open_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].open_time, 
		memory_size
	);
	pl_table.pl_array[index].last_attach_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_attach_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_attach_time, 
		memory_size
	);
	pl_table.pl_array[index].last_read_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_read_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_open_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_read_time, 
		memory_size
	);
	pl_table.pl_array[index].last_write_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_write_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_write_time, 
		memory_size
	);
	pl_table.pl_array[index].last_close_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_close_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].last_close_time, 
		memory_size
	);
#endif // __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate semaphore memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(HANDLE *) * 
		pl_table.pl_array[index].pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(HANDLE *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_handles_semaphores == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_counter_handles_semaphores, 
		memory_size
	);

	//-------------------------------------------------------------------------
	// Allocate socket memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(SOCKET) * 
		pl_table.pl_array[index].pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_sockets = 
		(SOCKET *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_sockets == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	ZeroMemory(
		pl_table.pl_array[index].pl_counter_sockets, 
		memory_size
	);
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Create counters socket, access semaphores and initialize the write cache.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[index].pl_counters_count; j++) { 
		pl_table.pl_array[index].pl_counter_handles_semaphores[j] = 
			CreateSemaphore(
				NULL, 
				(LONG)1, 
				(LONG)1, 
				NULL
			);
		if(
			pl_table.pl_array[index].pl_counter_handles_semaphores[j] == 
			NULL
		) {
			pl_last_error = PL_COUNTER_SEMAPHORE_CREATION_FAILED;
			goto pl_attach_unlock_table;
		}
		pl_table.pl_array[index].pl_write_cache[j] = PL_MAX_COUNTER_VALUE - 1;
		pl_table.pl_array[index].pl_counter_sockets[j] = INVALID_SOCKET;
	} // for j
#else // __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// In file system mode of operation, the pl_attach API call is carried
	// -out locally using the PL_FOLDER.
	//-------------------------------------------------------------------------
#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Extract productivity link folder.
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_folder_buffer, 
		sizeof(pl_folder_buffer)
	);
	pl_lenght = strlen(pl_config_file_name);
	strncpy(
		pl_folder_buffer, 
		pl_config_file_name, 
		pl_lenght - PL_CONFIG_FILE_NAME_LENGHT
	);
	mbstowcs_s(
		&st_ret, 
		pl_folder, 
		strlen(pl_folder_buffer) + 1, 
		pl_folder_buffer, 
		_TRUNCATE
	);
#endif // __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Sample pl_config.ini file (generated by esrv).
	//-------------------------------------------------------------------------
	// esrv
	// 76a145e6-6ea4-47ad-a783-60821b353236
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236 (Note: terminal back slash removed for GCC warning)
	// 63
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (Joule)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (Joule).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (kWh)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (kWh).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy Overflows (no unit)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Update Frequency (second)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Channel(s)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Status
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Version
	// 2010.01.18.(W)
	// _DEBUG
	// _UNICODE
	// UNICODE
	// __PL_DYNAMIC_COUNTERS_ALLOCATION__
	// __PL_WINDOWS__
	// __PL_GENERATE_INI__
	// __PL_GENERATE_INI_VERSION_TAGGING__
	// __PL_GENERATE_INI_BUILD_TAGGING__
	// __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	// __PL_BLOCKING_COUNTER_FILE_LOCK__
	// PL created on Wed Jul 21 12:26:14 2010
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Open productivity link configuration file.
	//-------------------------------------------------------------------------
	mbstowcs_s(
		&st_ret, 
		pl_path, 
		strlen(pl_config_file_name) + 1, 
		pl_config_file_name, 
		_TRUNCATE
	);
	pl_config_file = CreateFile(
		pl_path, 
		GENERIC_READ, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		SECURITY_ANONYMOUS
	);
	if(pl_config_file == INVALID_HANDLE_VALUE) {
		pl_last_error = PL_CONFIG_FILE_OPENING_FAILED;
		goto pl_attach_return;
	}

	//-------------------------------------------------------------------------
	// First pl_attach call *may* take the pl_table initialization penalty.
	//-------------------------------------------------------------------------
	if(pl_table_initialized == FALSE) {
#ifdef _DEBUG

		//---------------------------------------------------------------------
		// Dump memory leak info on any exit.
		//---------------------------------------------------------------------
		dw_ret = _CrtSetDbgFlag(
			_CRTDBG_ALLOC_MEM_DF | 
			_CRTDBG_LEAK_CHECK_DF
		);
		assert(dw_ret != -1);

		//---------------------------------------------------------------------
		// Redirect dump to stdout.
		//---------------------------------------------------------------------
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
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Allocate dynamically the pl_table -- fixed to default size.
		// This size will be expanded if needed later on and during each future 
		// call to pl_attach/pl_open.
		// Caution: this memory will not be freed! (__PL_DYNAMIC_TABLE_ALLOCA-
		// TION__).  Therefore it should never be defined or you can take 
		// responsibility to free it up (as in the PL Agent).
		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ defined
		// --------------------------------------------
		//
		//                                  |<----- LIMITED BY AVAILABLE MEMORY ---->|
		// +-----------------+------+       +------+------+--        --+------+------+
		// |                 |      |       |      |      |            |      |      |
		// | PL table access | *PL -+-----> | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |      |       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |       |      |      |            |      |      |
		// +-----------------+------+       +------+------+--        --+------+------+
		//---------------------------------------------------------------------
		ZeroMemory(
			&pl_table, 
			sizeof(pl_table)
		);
		memory_size = 
			sizeof(PRODUCTIVITY_LINK) * 
			PL_MAX_PRODUCTIVITY_LINKS
		;
		pl_table.pl_array = (PPRODUCTIVITY_LINK)malloc(memory_size);
		if(pl_table.pl_array == NULL) {
			pl_last_error = PL_OUT_OF_MEMORY;
			goto pl_attach_return;
		}
		// nulls in-use flags and the handle pointers
		ZeroMemory(
			pl_table.pl_array, 
			memory_size
		); 
		pl_max_productivity_links = PL_MAX_PRODUCTIVITY_LINKS;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ NOT defined
		// ------------------------------------------------
		//
		//                   |<----- PL_MAX_PRODUCTIVITY_LINKS ------>|
		// +-----------------+------+------+--        --+------+------+
		// |                 |      |      |            |      |      |
		// | PL Table access | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |      |            |      |      |
		// +-----------------+------+------+--        --+------+------+
		//---------------------------------------------------------------------
		// nulls in-use flags and the handles
		ZeroMemory(
			&pl_table, 
			sizeof(PL_TABLE)
		); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Create PL Table semaphore.
		// --------------------------------------------------------------------
		pl_table.semaphore = CreateSemaphore(
			NULL, 
			(LONG)1, 
			(LONG)1, 
			NULL
		);
		if(pl_table.semaphore == NULL) {
			pl_last_error = PL_SYNCHRONIZATION_FAILED;
			goto pl_attach_return;
		}
		pl_table_initialized = TRUE;
	}

	//-------------------------------------------------------------------------
	// Read-in the data stored in the productivity link configuration file.
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	pl_config_file_bytes_to_read = sizeof(char);
	ZeroMemory(
		pl_buffer, 
		sizeof(pl_buffer)
	);
	p = pl_buffer;
	do {

		//---------------------------------------------------------------------
		// Read one byte of the productivity link configuration file.
		//---------------------------------------------------------------------
		b_ret = ReadFile(
			pl_config_file, 
			p, 
			pl_config_file_bytes_to_read, 
			&pl_config_file_bytes_read, 
			NULL
		);
		if(b_ret == FALSE) {
			if(pl_config_file_bytes_read == 0) {
				goto pl_attach_eof;
			}
		}

		//---------------------------------------------------------------------
		// Analyze the read byte.
		//---------------------------------------------------------------------
		switch(*p) {

			//-----------------------------------------------------------------
			// LF found.
			//-----------------------------------------------------------------
			case PL_LF:
				*p = '\0';
				break;

			//-----------------------------------------------------------------
			// CR found.
			//-----------------------------------------------------------------
			case PL_CR:
				*p = '\0';
				if(
					strlen(pl_buffer) == 
					0
				) {

					//---------------------------------------------------------
					// Skip empty lines -- in case of *NIX interop.
					//---------------------------------------------------------
					goto pl_attach_blank_line;
				}

				//-------------------------------------------------------------
				// Process this line (was populated in the switch default).
				//-------------------------------------------------------------
				lines++;
				if(pl_counters_count != 0) {

					//---------------------------------------------------------
					// Perform PL_FOLDER substitution if required.  Detection
					// of substitution is performed by searching for the
					// PL_INI_NIX_FOLDER substring.
					// Note:
					//    The table is locked, index points to pl_table entry
					//    to use processing counters.
					// Note:
					//    The line stored in pl_buffer is a counter file at
					//    this stage (since pl_counters_count != 0).
					//---------------------------------------------------------
					ZeroMemory(
						pl_cvt_buffer, 
						PL_MAX_PATH
					);
					pl_folder_substitute = strstr(
						pl_buffer, 
						PL_INI_NIX_FOLDER
					);

					//---------------------------------------------------------
					// A PL_FOLDER substitution is required for this counter.
					//---------------------------------------------------------
					if(pl_folder_substitute != NULL) {
						
						//-----------------------------------------------------
						// Is it the first counter to be substituted? 
						//-----------------------------------------------------
						if(pl_folder_substitution == 0) { 

							//-------------------------------------------------
							// Collect the local PL folder, do it once now.
							//-------------------------------------------------
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

						//-----------------------------------------------------
						// Perform PL_FOLDER substitution. 
						//-----------------------------------------------------
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
							pl_folder_substitute + strlen(PL_INI_NIX_FOLDER) + 1, 
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

#ifdef __PL_EXTRA_INPUT_CHECKS__

					//---------------------------------------------------------
					// Ckeck the counter file name for validity in pl_buffer.
					// Perform the following checkings:
					//   - <PL_FOLDER> is present at the begin of the input
					//     string.
					//   - PL_INI_NIX_PATH_SEPARATOR follows <PL_FOLDER> in the
					//     input string.
					//   - <PL_INI_CONFIG_FILE_NAME> at the end of the input 
					//     string.
					//   - NULL follows <PL_INI_CONFIG_FILE_NAME> at the end of
					//     the input string.
					//   - <UUID> has a correct structure:
					//      - <UUID> has only allowed characters.
					//      - <UUID> has 4 dashes and five character blocks.
					//      - <UUID> 1st block has 8 characters.
					//      - <UUID> 2nd block has 4 characters.
					//      - <UUID> 3rd block has 4 characters.
					//      - <UUID> 4st block has 4 characters.
					//      - <UUID> 5th block has 12 characters.
					//   - counter name has only allowed characters.
					//   - application name has only allowed characters.
					//   - application name is the same as the reference.
					//   - UUID is the same as the reference.
					//   - counters found count doesn't exceed the reference.
					//   - counters path is the same as the reference.
					// Note:
					//    <PL_FOLDER>/<application_name>_<UUID>/<PL_INI_CONFIG_
					//    FILE_NAME>
					//---------------------------------------------------------

					//---------------------------------------------------------
					// Check if this counter doesn't exceed the reference count. 
					//---------------------------------------------------------
					if(pl_counters_count < 0) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Check if path is the same as the reference.
					//---------------------------------------------------------
					ret = strncmp(
						pl_buffer,
						reference_path,
						bytes_in_reference_path
					);
					if(ret != 0) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Check <PL_FOLDER>/
					//---------------------------------------------------------
					if(pl_folder_substitution == 0) {

						//-----------------------------------------------------
						// No substitution.
						//-----------------------------------------------------
						character = PL_INI_WINDOWS_PATH_SEPARATOR_CHAR;
						bytes_left_in_buffer = strlen(pl_buffer);
						pl_buffer_end = &pl_buffer[bytes_left_in_buffer - 1];
						buffer_index = strlen(PL_INI_WINDOWS_ROOTLESS_FOLDER);
						if(bytes_left_in_buffer < buffer_index) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							(
								*pl_buffer != 
								PL_INI_WINDOWS_PL_FOLDER_ROOT_CHAR
							) &&
							(
								*pl_buffer != 
								PL_INI_WINDOWS_PL_FOLDER_ROOT_UPPER_CHAR
							)
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							strncmp(
								pl_buffer + 1,
								PL_INI_WINDOWS_ROOTLESS_FOLDER,
								buffer_index
							) != 0
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							pl_buffer[++buffer_index] !=
							PL_INI_WINDOWS_PATH_SEPARATOR_CHAR
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
					} else {

						//-----------------------------------------------------
						// Substitution.
						//-----------------------------------------------------
						character = PL_INI_NIX_PATH_SEPARATOR_CHAR;
						bytes_left_in_buffer = strlen(pl_buffer);
						pl_buffer_end = &pl_buffer[bytes_left_in_buffer - 1];
						buffer_index = strlen(PL_INI_NIX_FOLDER);
						if(bytes_left_in_buffer < buffer_index) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							strncmp(
								pl_buffer,
								PL_INI_NIX_FOLDER,
								buffer_index
							) != 0
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							pl_buffer[buffer_index] !=
							PL_INI_NIX_PATH_SEPARATOR_CHAR
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
					}
					application_name = 
						(char *)&pl_buffer[++buffer_index]
					;

					//---------------------------------------------------------
					// Search for counter name (by finding the first 
					// PL_INI_WINDOWS_PATH_SEPARATOR_CHAR from the end of the
					// pl_buffer.  We use the opportunity to check that only
					// allowed characters are used in the counter name.
					//---------------------------------------------------------
					do {
						for(
							m = 0;
							m < PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT;
							m++
						) {
							if(
								(
									*pl_buffer_end ==
									character
								) ||
								(
									*pl_buffer_end ==
									allowed_characters_in_counter_name[m]
								)
							) {
								goto pl_attach_check_counter_name_character_ok;
							}
						} // for m
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
pl_attach_check_counter_name_character_ok:
						;
					} while(
						(
							pl_buffer <
							pl_buffer_end
						) &&
						(
							*pl_buffer_end-- != 
							character
						)
					);

					//---------------------------------------------------------
					// Extract the UUID.
					//---------------------------------------------------------
					uuid = 
						pl_buffer_end - 
						PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS +
						1
					;
					if(uuid <= pl_buffer) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}
					if(
						*(uuid - 1) !=
						PL_INI_APPLICATION_NAME_SEPARATOR_CHAR
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Check if application name is the same as the reference.
					//---------------------------------------------------------
					bytes_count = (uuid - application_name) - 1;
					ret = strncmp(
						application_name,
						reference_application_name,
						bytes_count
					);
					if(ret != 0) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Check if UUID is the same as the reference.
					//---------------------------------------------------------
					bytes_count = sizeof(reference_uuid) - 1;
					ret = strncmp(
						uuid,
						reference_uuid,
						bytes_count
					);
					if(ret != 0) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Search illegal character in UUID and obvious bad format.
					//---------------------------------------------------------
					dash_count = 0;
					block_byte_count = 0;
					for(
						n = 0; 
						n < PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS; 
						n++
					) {
						if(
							uuid[n] == 
							PL_EXTRA_INPUT_CHECKS_UUID_DASH_CHARACTER
						) {
							dash_count++; 
							switch(dash_count) {

								case 1:

									//-----------------------------------------
									// First UUID block 
									// (nnnnnnnn-0000-0000-0000-000000000000).
									//-----------------------------------------
									if(
										block_byte_count != 
										PL_EXTRA_INPUT_CHECKS_UUID_BLOCK1_SIZE
									) {
										pl_last_error = PL_INVALID_PARAMETERS;
										goto pl_attach_unlock_table;
									}
									block_byte_count = 0;
									goto pl_attach_check_pl_buffer_uuid_next;

								case 2:

									//-----------------------------------------
									// Second UUID block 
									// (00000000-nnnn-0000-0000-000000000000).
									//-----------------------------------------
									if(
										block_byte_count != 
										PL_EXTRA_INPUT_CHECKS_UUID_BLOCK2_SIZE
									) {
										pl_last_error = PL_INVALID_PARAMETERS;
										goto pl_attach_unlock_table;
									}
									block_byte_count = 0;
									goto pl_attach_check_pl_buffer_uuid_next;

								case 3:

									//-----------------------------------------
									// Third UUID block 
									// (00000000-0000-nnnn-0000-000000000000).
									//-----------------------------------------
									if(
										block_byte_count != 
										PL_EXTRA_INPUT_CHECKS_UUID_BLOCK3_SIZE
									) {
										pl_last_error = PL_INVALID_PARAMETERS;
										goto pl_attach_unlock_table;
									}
									block_byte_count = 0;
									goto pl_attach_check_pl_buffer_uuid_next;

								case 4:

									//-----------------------------------------
									// Fourth UUID block 
									// (00000000-0000-0000-nnnn-000000000000).
									//-----------------------------------------
									if(
										block_byte_count != 
										PL_EXTRA_INPUT_CHECKS_UUID_BLOCK4_SIZE
									) {
										pl_last_error = PL_INVALID_PARAMETERS;
										goto pl_attach_unlock_table;
									}
									block_byte_count = 0;
									goto pl_attach_check_pl_buffer_uuid_next;

								default:
									pl_last_error = PL_INVALID_PARAMETERS;
									goto pl_attach_unlock_table;
							} // switch
						}
						for(
							m = 0; 
							m < PL_EXTRA_INPUT_CHECKS_UUID_ALLOWED_CHARACTERS_COUNT; 
							m++
						) {
							if(
								uuid[n] == 
								allowed_characters_in_uuid[m]
							) {
								block_byte_count++;
								goto pl_attach_check_pl_buffer_uuid_next;
							}
						}
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_check_pl_buffer_uuid_error;
pl_attach_check_pl_buffer_uuid_next:
						;
					}

					//---------------------------------------------------------
					// Fifth UUID block (00000000-0000-0000-0000-nnnnnnnnnnnn).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK5_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}
					goto pl_attach_check_pl_buffer_uuid_ok;
pl_attach_check_pl_buffer_uuid_error:
					goto pl_attach_unlock_table;
pl_attach_check_pl_buffer_uuid_ok:
					;

					//---------------------------------------------------------
					// Check that only allowed characters are used in the 
					// application name.
					//---------------------------------------------------------
					uuid--;
					do {
						for(
							m = 0;
							m < PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT;
							m++
						) {
							if(
								*application_name ==
								allowed_characters_in_application_name[m]
							) {
								goto pl_attach_check_application_name_character_ok;
							}
						} // for m
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
pl_attach_check_application_name_character_ok:
						;
					} while (
						application_name++ <
						uuid
					);
#endif // __PL_EXTRA_INPUT_CHECKS__

					//---------------------------------------------------------
					// Open counter file and create associated semaphore.
					//---------------------------------------------------------
#ifdef __PL_ATTACH_SCRIPT_SUPPORT__
					pl_table.pl_array[index].pl_counter_handles[j] = CreateFile(
						pl_cvt_buffer, 
						GENERIC_READ | GENERIC_WRITE, 
						FILE_SHARE_READ | FILE_SHARE_WRITE, 
						NULL, 
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL, 
						SECURITY_ANONYMOUS
					);
#else // __PL_ATTACH_SCRIPT_SUPPORT__
					pl_table.pl_array[index].pl_counter_handles[j] = CreateFile(
						pl_cvt_buffer, 
						GENERIC_READ, 
						FILE_SHARE_READ | FILE_SHARE_WRITE, 
						NULL, 
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL, 
						SECURITY_ANONYMOUS
					);
#endif // __PL_ATTACH_SCRIPT_SUPPORT__
					if(pl_table.pl_array[index].pl_counter_handles[j] == 
						INVALID_HANDLE_VALUE
					) {
						pl_last_error = PL_CONFIG_FILE_OPENING_FAILED;
						goto pl_attach_unlock_table;
					}
					pl_table.pl_array[index].pl_counter_handles_semaphores[j] = 
						CreateSemaphore(
							NULL, 
							(LONG)1, 
							(LONG)1, 
							NULL
						)
					;
					if(
						pl_table.pl_array[index].pl_counter_handles_semaphores[j] == 
						NULL
					) {
						pl_last_error = PL_COUNTER_SEMAPHORE_CREATION_FAILED;
						goto pl_attach_unlock_table;
					}
					j++;
					pl_table.pl_array[index].pl_counters_count++;
					pl_counters_count--;
				}

#ifdef __PL_EXTRA_INPUT_CHECKS__

				//-------------------------------------------------------------
				// Storing reference application name.
				// Note:
				//    No checkings are performed since we do not use this data.
				//    However, we store it so we can compare with each counter
				//    data if it matches the reference data.
				//-------------------------------------------------------------
				if(lines == PL_CONFIGURATION_FILE_APPLICATION_NAME_LINE) {
					bytes_count = strlen(pl_buffer);
					if(bytes_count < PL_MAX_PATH) {
						bytes_left_in_buffer = sizeof(reference_application_name);
						memset(
							reference_application_name,
							0,
							bytes_left_in_buffer
						);
						strncpy_s(
							reference_application_name,
							bytes_left_in_buffer,
							pl_buffer,
							bytes_left_in_buffer
						);
					} else {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
				}

				//-------------------------------------------------------------
				// Storing UUID. 
				// Note:
				//    No checkings are performed since we do not use this data.
				//    However, we store it so we can compare with each counter
				//    data if it matches the reference data.
				//-------------------------------------------------------------
				if(lines == PL_CONFIGURATION_FILE_UUID_STRING_LINE) {
					bytes_count = strlen(pl_buffer);
					if(bytes_count <= PL_UUID_MAX_CHARS) {
						bytes_left_in_buffer = sizeof(reference_uuid);
						memset(
							reference_uuid,
							0,
							bytes_left_in_buffer
						);
						strncpy_s(
							reference_uuid,
							bytes_left_in_buffer,
							pl_buffer,
							bytes_left_in_buffer
						);
					} else {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
				}

				//-------------------------------------------------------------
				// Storing location. 
				// Note:
				//    No checkings are performed since we do not use this data.
				//    However, we store it so we can compare with each counter
				//    data if it matches the reference data.
				//-------------------------------------------------------------
				if(lines == PL_CONFIGURATION_FILE_LOCATION_LINE) {
					bytes_count = strlen(pl_buffer);
					if(bytes_count < PL_MAX_PATH) {
						bytes_left_in_buffer = sizeof(reference_path);
						memset(
							reference_path,
							0,
							bytes_left_in_buffer
						);
						strncpy_s(
							reference_path,
							bytes_left_in_buffer,
							pl_buffer,
							bytes_left_in_buffer
						);
					} else {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					bytes_in_reference_path = bytes_count;
				}
#endif // __PL_EXTRA_INPUT_CHECKS__

				//-------------------------------------------------------------
				// At this stage, no counter file has been found and we are
				// still expecting the non-counter related files.
				//-------------------------------------------------------------
				if(lines == PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE) {

					//---------------------------------------------------------
					// This line contains the number of counters in the PL.
					// Note:
					//    The table is not locked yet.
					//---------------------------------------------------------
#ifdef __PL_EXTRA_INPUT_CHECKS__
					pl_buffer_length = strlen(pl_buffer);
					if(
						pl_buffer_length > 
						strlen(PL_MAX_UNSIGNED_INTEGER_STRING)
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					for(n = 0; n < (int)pl_buffer_length; n++) {
						for(
							m = 0;
							m < PL_EXTRA_INPUT_CHECKS_COUNTERS_COUNT_ALLOWED_CHARACTERS_COUNT;
							m++
						) {
							if(
								pl_buffer[n] ==
								allowed_characters_in_counters_count[m]
							) {
								goto pl_attach_check_counter_count_character_next;
							}
						} // for m
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
pl_attach_check_counter_count_character_next:
						;
					} // for n
#endif // __PL_EXTRA_INPUT_CHECKS__

					//---------------------------------------------------------
					// Collect and check the counter count.
					// Note:
					//    The table is not locked yet.
					//---------------------------------------------------------
					pl_counters_count = atoi(pl_buffer);
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
					if(pl_counters_count > PL_MAX_COUNTERS_PER_LINK) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

					//---------------------------------------------------------
					// Lock the pl_table against other threads. blocking wait.
					//---------------------------------------------------------
					dw_ret = WaitForSingleObject(
						pl_table.semaphore, 
						INFINITE
					);
					if(dw_ret != WAIT_OBJECT_0) {
						pl_last_error = PL_SYNCHRONIZATION_FAILED;
						goto pl_attach_return;
					}
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__

					//---------------------------------------------------------
					// Search the first unused entry in the pl_table. index 
					// holds the position.
					//---------------------------------------------------------
					for(index = 0; index < PL_MAX_PRODUCTIVITY_LINKS; index++) {
						if(pl_table.pl_array[index].pl_in_use == FALSE) {
							goto pl_attach_found;
						}
					}
					// pl_table full
					pl_last_error = PL_DESCRIPTOR_TABLE_FULL;
					goto pl_attach_unlock_table;					
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

					//---------------------------------------------------------
					// Search the first unused entry in the pl_table. index 
					// holds the position.
					//---------------------------------------------------------
					for(index = 0; index < pl_max_productivity_links; index++) {
						if(pl_table.pl_array[index].pl_in_use == FALSE) {
							goto pl_attach_found;
						}
					}

					//---------------------------------------------------------
					// No room in the table, lets double dynamically the pl_ta-
					// ble size and create the additional counters.
					//---------------------------------------------------------
					pl_old_max_productivity_links = pl_max_productivity_links; 
					pl_max_productivity_links *= 2;
					pl_table.pl_array = 
						(PPRODUCTIVITY_LINK)realloc(
							pl_table.pl_array, 
								sizeof(PRODUCTIVITY_LINK) * 
								pl_max_productivity_links
						);
					if(pl_table.pl_array == NULL) {
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					// clear newly allocated memory
					ZeroMemory(
						&pl_table.pl_array[index], 
							sizeof(PRODUCTIVITY_LINK) * 
							pl_old_max_productivity_links
					); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
pl_attach_found:
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

					//---------------------------------------------------------
					// Allocate the found number of counters.
					//---------------------------------------------------------
					memory_size = 
						sizeof(unsigned long long) * 
						pl_counters_count
					;
					pl_table.pl_array[index].pl_write_cache = 
						(unsigned long long *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].pl_write_cache == NULL) {
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					ZeroMemory(
						pl_table.pl_array[index].pl_write_cache, 
						memory_size
					);
#ifdef __PL_TIMESTAMPING__
					memory_size = 
						sizeof(time_t) * 
						pl_counters_count
					;
					pl_table.pl_array[index].open_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].open_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					ZeroMemory(
						pl_table.pl_array[index].open_time, 
						memory_size
					);
					pl_table.pl_array[index].last_attach_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].last_attach_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					ZeroMemory(
						pl_table.pl_array[index].last_attach_time, 
						memory_size
					);
					pl_table.pl_array[index].last_read_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].last_read_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					ZeroMemory(
						pl_table.pl_array[index].last_read_time, 
						memory_size
					);
					pl_table.pl_array[index].last_write_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].last_write_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						free(pl_table.pl_array[index].last_read_time);
						pl_table.pl_array[index].last_read_time = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					ZeroMemory(
						pl_table.pl_array[index].last_write_time, 
						memory_size
					);
					pl_table.pl_array[index].last_close_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].last_close_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						free(pl_table.pl_array[index].last_read_time);
						pl_table.pl_array[index].last_read_time = NULL;
						free(pl_table.pl_array[index].last_write_time);
						pl_table.pl_array[index].last_write_time = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					ZeroMemory(
						pl_table.pl_array[index].last_close_time, 
						memory_size
					);
#endif // __PL_TIMESTAMPING__
					memory_size = 
						sizeof(HANDLE) * 
						pl_counters_count
					;
					pl_table.pl_array[index].pl_counter_handles = 
						(HANDLE *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].pl_counter_handles == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						free(pl_table.pl_array[index].last_read_time);
						pl_table.pl_array[index].last_read_time = NULL;
						free(pl_table.pl_array[index].last_write_time);
						pl_table.pl_array[index].last_write_time = NULL;
						free(pl_table.pl_array[index].last_close_time);
						pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					ZeroMemory(
						pl_table.pl_array[index].pl_counter_handles, 
						memory_size
					);
					pl_table.pl_array[index].pl_counter_handles_semaphores = 
						(HANDLE *)malloc(memory_size)
					;
					if(
						pl_table.pl_array[index].pl_counter_handles_semaphores == 
						NULL
					) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						free(pl_table.pl_array[index].last_read_time);
						pl_table.pl_array[index].last_read_time = NULL;
						free(pl_table.pl_array[index].last_write_time);
						pl_table.pl_array[index].last_write_time = NULL;
						free(pl_table.pl_array[index].last_close_time);
						pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
						free(pl_table.pl_array[index].pl_counter_handles);
						pl_table.pl_array[index].pl_counter_handles = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					ZeroMemory(
						pl_table.pl_array[index].pl_counter_handles_semaphores, 
						memory_size
					);
					pl_table.pl_array[index].pl_counters_count = 0;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
					pl_table.pl_array[index].pl_in_use = TRUE;
				}

				//-------------------------------------------------------------
				// Reset pl_buffer for next PL configuration file.
				//-------------------------------------------------------------
				bytes_left_in_pl_buffer = sizeof(pl_buffer);
				ZeroMemory(
					pl_buffer, 
					sizeof(pl_buffer)
				);
				p = pl_buffer;
				break;
			
			//-----------------------------------------------------------------
			// Not a CR or LF found.
			//-----------------------------------------------------------------
			default:
				p++;
				bytes_left_in_pl_buffer--;
				if(bytes_left_in_pl_buffer <= 0) {
					pl_last_error = PL_OUT_OF_BUFFER_SPACE;
					goto pl_attach_return;
				}
				break;
			}
pl_attach_blank_line:
			;
	} while(pl_config_file_bytes_read == pl_config_file_bytes_to_read);

pl_attach_eof:

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//---------------------------------------------------------
	// Check if the counters count matches the reference count. 
	//---------------------------------------------------------
	if(pl_counters_count != 0) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_unlock_table;
	}
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Close productivity link configuration file.
	//-------------------------------------------------------------------------
	b_ret = CloseHandle(pl_config_file);
	if(b_ret == FALSE) {
		pl_last_error = PL_CRITICAL_FAILURE;
		goto pl_attach_unlock_table;
	}
#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Setup the file system notification handle for the PL.
	//-------------------------------------------------------------------------
	pl_table.pl_array[index].pl_read_notify_handle = 
		FindFirstChangeNotification(
			pl_folder, 
			FALSE, 
			FILE_NOTIFY_CHANGE_LAST_WRITE
		);
	if(pl_table.pl_array[index].pl_read_notify_handle == INVALID_HANDLE_VALUE) {
		pl_last_error = PL_BLOCKING_PL_READ_HANDLE_CREATION_FAILED;
		goto pl_attach_unlock_table;
	}
	pl_table.pl_array[index].pl_attach_flag = 1;
#endif // __PL_BLOCKING_PL_READ__
#endif // __PL_FILESYSTEM_LESS__

pl_attach_unlock_table:

#if defined (__PL_EXTRA_INPUT_CHECKS__) && ! defined(__PL_FILESYSTEM_LESS__)
	
	if(pl_last_error == PL_INVALID_PARAMETERS) {

		//---------------------------------------------------------------------
		// Destroy all partially allocated elements.
		// Close counter files handles and semaphores.
		//---------------------------------------------------------------------
		for(j = 0; j < pl_table.pl_array[index].pl_counters_count; j++) {
			b_ret = CloseHandle(
				pl_table.pl_array[index].pl_counter_handles[j]
			);
			if(b_ret == 0) {
				pl_last_error = PL_CRITICAL_FAILURE;
				goto pl_attach_unlock_table;
			}
			b_ret = CloseHandle(
				pl_table.pl_array[index].pl_counter_handles_semaphores[j]
			);
			if(b_ret == 0) {
				pl_last_error = PL_CRITICAL_FAILURE;
				goto pl_attach_unlock_table;
			}
		} // for j
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

		//---------------------------------------------------------------------
		// Free counter cache, handle and semaphore memory.
		//---------------------------------------------------------------------
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles);
		pl_table.pl_array[index].pl_counter_handles = NULL;
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		
		//---------------------------------------------------------------------
		// Mark PL slot as unused.
		//---------------------------------------------------------------------
		ZeroMemory(
			&pl_table.pl_array[index], 
			sizeof(PRODUCTIVITY_LINK)
		);
		pl_table.pl_array[index].pl_in_use = FALSE;
	}

#endif // __PL_EXTRA_INPUT_CHECKS__ && !__PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Unlock the productivity link table (locked against other threads).
	//-------------------------------------------------------------------------
	b_ret = ReleaseSemaphore(
		pl_table.semaphore,
		(LONG)1, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}

pl_attach_return:

#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Release java arguments
	//-------------------------------------------------------------------------
	(*interface_pointer)->ReleaseStringUTFChars(
		interface_pointer, 
		java_pl_config_file_name, 
		pl_config_file_name
	);

#endif // __PL_JNI_EXPORTS__

#ifdef __PL_EXTRA_INPUT_CHECKS__
	
	if(pl_last_error == PL_INVALID_PARAMETERS) {

		//---------------------------------------------------------------------
		// Close productivity link configuration file.
		//---------------------------------------------------------------------
		ret = CloseHandle(pl_config_file);
		if(ret == -1) {
			pl_last_error = PL_CRITICAL_FAILURE;
		} else {
			pl_last_error = PL_INVALID_PARAMETERS;
		}
	}

#endif __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Return last error and return status.
	//-------------------------------------------------------------------------
	if(pl_last_error != PL_NO_ERROR) {
		SetLastError(pl_last_error);
		return(PL_INVALID_DESCRIPTOR);
	} else {
		pl_last_error = PL_NO_ERROR;
		SetLastError(pl_last_error);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  

	//-------------------------------------------------------------------------
	//   @    @    @ @@@@@  @   @
	// @ @ @  @@   @   @     @ @
	//  @@@   @ @  @   @      @
	// @ @ @  @   @@   @     @ @
	//   @    @    @ @@@@@  @   @
	//-------------------------------------------------------------------------
	int ret = 0;
	int pl_last_error = PL_NO_ERROR;
	#ifdef __PL_MACOSX__
		uuid_t pl_uuid;
		#ifdef __PL_FILESYSTEM_LESS__
			char pl_uuid_buffer_semaphore[PL_SEMAPHORE_NAME_MAX_LENGTH] = { 0 };
		#else // __PL_FILESYSTEM_LESS__
			char pl_uuid_buffer[PL_MAX_PATH] = { 0 };
		#endif // __PL_FILESYSTEM_LESS__
	#endif // __PL_MACOSX__		
#ifdef __PL_FILESYSTEM_LESS__
	char *env_address = NULL;
	char *env_port = NULL;
	size_t length = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
#else // __PL_FILESYSTEM_LESS__
	int i = 0;
	int pl_config_file = -1;
	unsigned int upper_char_count = 0;
	unsigned int lower_char_count = 0;
	size_t pl_config_file_bytes_to_read = 0;
	size_t pl_config_file_bytes_read = 0;
	size_t bytes_left_in_pl_temp = 0;
	size_t bytes_left_in_pl_local_pl_folder = 0;
	#ifdef __PL_BLOCKING_PL_READ__
		char pl_folder[PL_MAX_PATH] = { 0 };
		char pl_folder_buffer[PL_MAX_PATH] = { 0 };
		size_t pl_lenght = 0;
	#endif // __PL_BLOCKING_PL_READ__
#endif // __PL_FILESYSTEM_LESS__

#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Get the java arguments
	//-------------------------------------------------------------------------
	pl_config_file_name = (*interface_pointer)->GetStringUTFChars(
		interface_pointer, 
		java_pl_config_file_name, 
		NULL
	);
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Check calling argument.
	//-------------------------------------------------------------------------
	if(pl_config_file_name == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Perform the following input data checking:
	//   - PL configuration file name length is less than PL_MAX_PATH.
	//   - <PL_FOLDER> is present at the beginning of the input string.
	//   - PL_INI_NIX_PATH_SEPARATOR follows <PL_FOLDER> in the input string.
	//   - <PL_INI_CONFIG_FILE_NAME> at the end of the input string.
	//   - NULL follows <PL_INI_CONFIG_FILE_NAME> at the end of the input 
	//     string.
	//   - <UUID> has a correct structure:
	//      - <UUID> has only allowed characters.
	//      - <UUID> has 4 dashes and five character blocks.
	//      - <UUID> 1st block has 8 characters.
	//      - <UUID> 2nd block has 4 characters.
	//      - <UUID> 3rd block has 4 characters.
	//      - <UUID> 4st block has 4 characters.
	//      - <UUID> 5th block has 12 characters.
	// Note:
	//    <PL_FOLDER>/<application_name>_<UUID>/<PL_INI_CONFIG_FILE_NAME>
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Check PL configuration file name length.
	//-------------------------------------------------------------------------
	pchar = (char *)pl_config_file_name;
	bytes_count = 0;
	while(
		(bytes_count < PL_MAX_PATH) &&
		(*pchar != '\0')
	) {
			bytes_count++;
			pchar++;
	}
	if(bytes_count >= PL_MAX_PATH) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	bytes_left_in_buffer = bytes_count;
	if(bytes_left_in_buffer >= PL_MAX_PATH) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}

#ifndef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Note:
	//    in filesystem-less mode, the configuration ini file can be provided
	//    in both, Windows or *NIX format.  Therefore, the location testing
	//    is skipped at this stage.  It should be performed by the agent, or
	//    it will be performed if the agent uses pl_attach in file system mode.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Check <PL_FOLDER>/
	//-------------------------------------------------------------------------
	buffer_index = strlen(PL_INI_NIX_FOLDER);
	if(bytes_left_in_buffer < buffer_index) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		strncmp(
			pl_config_file_name,
			PL_INI_NIX_FOLDER,
			buffer_index
		) != 0
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		pl_config_file_name[buffer_index] !=
		PL_INI_NIX_PATH_SEPARATOR_CHAR
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	application_name = (char *)&pl_config_file_name[++buffer_index];

	//-------------------------------------------------------------------------
	// Check for <PL_INI_CONFIG_FILE_NAME> presence.
	//-------------------------------------------------------------------------
	config_file_name = strstr(
		pl_config_file_name,
		PL_INI_CONFIG_FILE_NAME
	);
	if(config_file_name == NULL) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(config_file_name <= pl_config_file_name) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		*(config_file_name + strlen(PL_INI_CONFIG_FILE_NAME)) != 
		'\0'
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	config_file_name--;
	if(
		*config_file_name != 
		PL_INI_NIX_PATH_SEPARATOR_CHAR
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}

	//-------------------------------------------------------------------------
	// Find the UUID.
	//-------------------------------------------------------------------------
	uuid = config_file_name - PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS;
	if(uuid <= pl_config_file_name) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(uuid <= application_name) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	if(
		*(uuid - 1) !=
		PL_INI_APPLICATION_NAME_SEPARATOR_CHAR
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}

	//-------------------------------------------------------------------------
	// Search illegal character in UUID and obvious bad format.
	//-------------------------------------------------------------------------
	for(n = 0; n < PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS; n++) {
		if(uuid[n] == PL_EXTRA_INPUT_CHECKS_UUID_DASH_CHARACTER) {
			dash_count++; 
			switch(dash_count) {

				case 1:

					//---------------------------------------------------------
					// First UUID block (nnnnnnnn-0000-0000-0000-000000000000).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK1_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					block_byte_count = 0;
					goto pl_attach_check_uuid_next;

				case 2:

					//---------------------------------------------------------
					// Second UUID block (00000000-nnnn-0000-0000-000000000000).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK2_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					block_byte_count = 0;
					goto pl_attach_check_uuid_next;

				case 3:

					//---------------------------------------------------------
					// Third UUID block (00000000-0000-nnnn-0000-000000000000).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK3_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					block_byte_count = 0;
					goto pl_attach_check_uuid_next;

				case 4:

					//---------------------------------------------------------
					// Fourth UUID block (00000000-0000-0000-nnnn-000000000000).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK4_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					block_byte_count = 0;
					goto pl_attach_check_uuid_next;

				default:
					pl_last_error = PL_INVALID_PARAMETERS;
					goto pl_attach_return;
			} // switch
		}
		for(
			m = 0; 
			m < PL_EXTRA_INPUT_CHECKS_UUID_ALLOWED_CHARACTERS_COUNT; 
			m++
		) {
			if(uuid[n] == allowed_characters_in_uuid[m]) {
				block_byte_count++;
				goto pl_attach_check_uuid_next;
			}
		}
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_check_uuid_error;
pl_attach_check_uuid_next:
		;
	}

	//---------------------------------------------------------
	// Fifth UUID block (00000000-0000-0000-0000-nnnnnnnnnnnn).
	//---------------------------------------------------------
	if(
		block_byte_count != 
		PL_EXTRA_INPUT_CHECKS_UUID_BLOCK5_SIZE
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_return;
	}
	goto pl_attach_check_uuid_ok;
pl_attach_check_uuid_error:
	goto pl_attach_return;
pl_attach_check_uuid_ok:
	;
#endif // !__PL_FILESYSTEM_LESS__
#endif // __PL_EXTRA_INPUT_CHECKS__

#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// In file system-less mode, a pl_attach is carried-out in two steps.  Fir-
	// st step uses the PL protocol to send a pl_attach request to a PL agent 
	// (identified via the default agent IP @ / port or user provided environm-
	// ent variables.  The remote agent will carry out the pl_attach API call 
	// and will return the remote pld and status.  The remote pld will be stored
	// into the PL table and a local pld is returned with the uuid to the 
	// calling process and a uuid is generated on the local system for the 
	// remote PL.  The protocol requires that the agent returns also the coun-
	// ters count.  This count is then used to locally create the counters
	// entries in the local PL table.
	// Note:
	//    Locally, with the exception of the two-step process, pl_attach beha-
	//    ves as a pl_open in this mode.
	// ------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// First pl_attach call takes the pl_table initialization penalty.
	//-------------------------------------------------------------------------
	if(pl_table_initialized == 0) {

#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Allocate dynamically the pl_table -- fixed to default size.
		// This size will de expanded if needed later on and during each future 
		// call to pl_attach/pl_open.
		// Caution: this memory will not be freed! (__PL_DYNAMIC_TABLE_ALLOCA-
		// TION__).  Therefore it should never be defined or you can take 
		// responsibility to free it up (as in the PL Agent).
		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ defined
		// --------------------------------------------
		//
		//                                  |<----- LIMITED BY AVAILABLE MEMORY ---->|
		// +-----------------+------+       +------+------+--        --+------+------+
		// |                 |      |       |      |      |            |      |      |
		// | PL table access | *PL -+-----> | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |      |       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |       |      |      |            |      |      |
		// +-----------------+------+       +------+------+--        --+------+------+
		//---------------------------------------------------------------------
		memset(
			&pl_table, 
			0,
			sizeof(pl_table)
		);
		memory_size = 
			sizeof(PRODUCTIVITY_LINK) * 
			PL_MAX_PRODUCTIVITY_LINKS
		;
		pl_table.pl_array = (PPRODUCTIVITY_LINK)malloc(memory_size);
		if(pl_table.pl_array == NULL) {
			pl_last_error = PL_OUT_OF_MEMORY;
			goto pl_attach_return;
		}
		// nulls in-use flags and the handles
		memset(
			pl_table.pl_array, 
			0, 
			memory_size
		);
		pl_max_productivity_links = PL_MAX_PRODUCTIVITY_LINKS;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ NOT defined
		// ------------------------------------------------
		//
		//                   |<----- PL_MAX_PRODUCTIVITY_LINKS ------>|
		// +-----------------+------+------+--        --+------+------+
		// |                 |      |      |            |      |      |
		// | PL Table access | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |      |            |      |      |
		// +-----------------+------+------+--        --+------+------+
		//---------------------------------------------------------------------
		// nulls in-use flags and the handles
		memset(
			&pl_table, 
			0, 
			sizeof(PL_TABLE)
		); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Create PL Table semaphore.
		// Note:
		// Semaphore name is required by MacOS X POSIX semaphore implementation.
		// Semaphore name is PL_SEMAPHORE_NAME_MAX_LENGTH characters of a guuid.
		//---------------------------------------------------------------------
#ifdef __PL_MACOSX__
		uuid_generate(pl_uuid);
		memset(
			pl_uuid_buffer_semaphore, 
			0, 
			sizeof(pl_uuid_buffer_semaphore)
		);
		uuid_unparse(
			pl_uuid, 
			pl_uuid_buffer_semaphore
		);
		pl_uuid_buffer_semaphore[PL_SEMAPHORE_NAME_MAX_LENGTH] = '\0';
		pl_table.semaphore = sem_open(
			pl_uuid_buffer_semaphore, 
			O_CREAT | O_EXCL, 
			(mode_t)PL_SEMAPHORE_ACCESS_MODE, 
			1
		);
		if(pl_table.semaphore == (sem_t *)SEM_FAILED) {
			ret = -1;
		}
#else // __PL_MACOSX__
		ret = sem_init(
			&pl_table.semaphore, 
			0, 
			1
		);
#endif // __PL_MACOSX__		
		if(ret == -1) {
			pl_last_error = PL_SYNCHRONIZATION_FAILED;
			goto pl_attach_return;
		}
		pl_table_initialized = 1;
	} // if pl_table_initialized == 0

	//-------------------------------------------------------------------------
	// Lock the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_wait(pl_table.semaphore);
#else // __PL_MACOSX__
	ret = sem_wait(&pl_table.semaphore);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_attach_return;
	}
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < PL_MAX_PRODUCTIVITY_LINKS; index++) {
		if(pl_table.pl_array[index].pl_in_use == 0) {
			goto pl_attach_found;
		}
	}
	// pl_table full
	pl_last_error = PL_DESCRIPTOR_TABLE_FULL;
	goto pl_attach_unlock_table;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// Search the first unused entry in the pl_table. index holds the position.
	//-------------------------------------------------------------------------
	for(index = 0; index < pl_max_productivity_links; index++) {
		if(pl_table.pl_array[index].pl_in_use == 0) {
			goto pl_attach_found;
		}
	}

	//-------------------------------------------------------------------------
	// No room in the table, lets double dynamically the pl_table size and
	// create the additional counters.
	//-------------------------------------------------------------------------
	pl_old_max_productivity_links = pl_max_productivity_links; 
	pl_max_productivity_links *= 2;
	pl_table.pl_array = 
		(PPRODUCTIVITY_LINK)realloc(
			pl_table.pl_array, 
			sizeof(PRODUCTIVITY_LINK) * pl_max_productivity_links
		);
	if(pl_table.pl_array == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	// clear newly allocated memory
	memset(
		&pl_table.pl_array[index], 
		0, 
		sizeof(PRODUCTIVITY_LINK) * pl_old_max_productivity_links
	);
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
pl_attach_found:
	pl_table.pl_array[index].pl_in_use = 1;

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_ADDRESS environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	bytes_left_in_buffer = sizeof(pl_table.pl_array[index].pl_address);
	env_address = getenv(
		PL_DEFAULT_PL_AGENT_ADDRESS_ENVAR_NAME
	);
	if(env_address == NULL) {
		strncpy(
			pl_table.pl_array[index].pl_address,
			PL_DEFAULT_PL_AGENT_ADDRESS,
			bytes_left_in_buffer
		);
		length = strlen(PL_DEFAULT_PL_AGENT_ADDRESS);
	} else {
		strncpy(
			pl_table.pl_array[index].pl_address,
			env_address,
			bytes_left_in_buffer
		);
		length = strlen(env_address);
		env_address = NULL;
	}
	bytes_left_in_buffer -= length;
	if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_attach_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Check the validity of the IPV4 address.
	// Note:
	//    Class A: 000.000.000.000 to 127.255.255.255
	//    Class B: 128.000.000.000 to 191.255.255.255
	//    Class C: 192.000.000.000 to 223.255.255.255
	//    Class D: 224.000.000.000 to 239.255.255.255
	//    Class E: 240.000.000.000 to 255.255.255.255
	//-------------------------------------------------------------------------
	for(m = 0; m < (int)length; m++) {

		//---------------------------------------------------------------------
		// Ckeck that only legal characters are used.
		//---------------------------------------------------------------------
		if(
			pl_table.pl_array[index].pl_address[m] == 
			PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_DOT_CHARACTER
		) { 
			if(digit_count == 0) {

				//-------------------------------------------------------------
				// No address can start without a digit.
				//-------------------------------------------------------------
				goto pl_attach_check_ip_v4_address_error; 
			}

			//-----------------------------------------------------------------
			// A dot was found, let's process the address value as stored.
			//-----------------------------------------------------------------
			dot_count++;
			digit_count = 0;
			ip_v4_address_value_string[
				PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE
			] = '\0';
			value = atoi(ip_v4_address_value_string);
			memset(
				ip_v4_address_value_string, 
				0, 
				sizeof(ip_v4_address_value_string)
			);
			
			//-----------------------------------------------------------------
			// Use the . character count to check address value ranges.
			//-----------------------------------------------------------------
			switch(dot_count) {

				case 1:

					//---------------------------------------------------------
					// This is the first address value (nnn.xxx.xxx.xxx).
					// Assign a class to the address based on the first address
					// value.
					//---------------------------------------------------------
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D; 
						break; 
					}
					if(
						(value >= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MIN_VALUE) && 
						(value <= PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MAX_VALUE)
					) { 
						ip_v4_class = PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E; 
						break; 
					}
					goto pl_attach_check_ip_v4_address_error;
					break;

				case 2:

					//---------------------------------------------------------
					// This is the second address value (xxx.nnn.xxx.xxx).
					// Check the second address value based on the class 
					// assigned using the first address value
					//---------------------------------------------------------
					switch(ip_v4_class) {
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						default:

							//-------------------------------------------------
							// Invalid second address value.
							//-------------------------------------------------
							goto pl_attach_check_ip_v4_address_error;
					} // switch
					break;

				case 3: // third number

					//---------------------------------------------------------
					// This is the third address value (xxx.xxx.nnn.xxx).
					// Check the third address value based on the class 
					// assigned using the first address value
					//---------------------------------------------------------
					switch(ip_v4_class) {
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
							if(
								(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MIN_VALUE) || 
								(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MAX_VALUE)
							) { 
								goto pl_attach_check_ip_v4_address_error; 
							}
							break;
						default:

							//-------------------------------------------------
							// Invalid second address value.
							//-------------------------------------------------
							goto pl_attach_check_ip_v4_address_error;
					} // switch
					break;

				default:

					//---------------------------------------------------------
					// This is the fourth address value (xxx.xxx.xxx.nnn).
					// Note:
					//    Fourth address value is tested later on, however if 
					//    we are here, it is an error.
					//---------------------------------------------------------
					goto pl_attach_check_ip_v4_address_error;
			}

		} else {

			//-----------------------------------------------------------------
			// This is not a dot (.) character, check if it is an allowed one.
			//-----------------------------------------------------------------
			for(
				n = 0; 
				n < PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS_COUNT; 
				n++
			) {
				if(
					pl_table.pl_array[index].pl_address[m] == 
					allowed_characters_in_ip_v4_address[n]
				) {
					ip_v4_address_value_string[digit_count++] = 
						pl_table.pl_array[index].pl_address[m]
					;
					if(
						digit_count > 
						PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DIGITS_IN_ADDRESS_VALUE
					) { 
						goto pl_attach_check_ip_v4_address_error; 
					}
					goto pl_attach_check_ip_v4_address_next;
				}
			} // for n
			goto pl_attach_check_ip_v4_address_error;
		}
pl_attach_check_ip_v4_address_next:
		;
	} // for m

	//-------------------------------------------------------------------------
	// check if after the last dot (.) we have at least one digit as this 
	// cannot be trapped in the loop above.
	//-------------------------------------------------------------------------
	if(digit_count == 0) { 
		goto pl_attach_check_ip_v4_address_error; 
	}

	//-------------------------------------------------------------------------
	// check ip address string has three (3) dots (.)
	//-------------------------------------------------------------------------
	if(
		dot_count != 
		PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DOT_CHARACTERS_IN_ADDRESS
	) { 
		goto pl_attach_check_ip_v4_address_error; 
	}

	//-------------------------------------------------------------------------
	// check fouth number's range
	//-------------------------------------------------------------------------
	ip_v4_address_value_string[
		PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE
	] = '\0';
	value = atoi(ip_v4_address_value_string);
	
	//-------------------------------------------------------------------------
	// This is the fourth address value (xxx.xxx.xxx.nnn).
	// Check the fourth address value based on the class assigned using the 
	// first address value.
	//-------------------------------------------------------------------------
	switch(ip_v4_class) {
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		case PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E: 
			if(
				(value < PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MIN_VALUE) || 
				(value > PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MAX_VALUE)
			) { 
				goto pl_attach_check_ip_v4_address_error; 
			}
			break;
		default:

			//-----------------------------------------------------------------
			// Invalid second address value.
			//-----------------------------------------------------------------
			goto pl_attach_check_ip_v4_address_error;
	} // switch
	goto pl_attach_check_ip_v4_address_ok;
pl_attach_check_ip_v4_address_error:
	pl_last_error = PL_FILESYSTEM_LESS_INVALID_IPV4_ADDRESS;
	goto pl_attach_return;
pl_attach_check_ip_v4_address_ok:
	;
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_PL_PORT environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	bytes_left_in_buffer = sizeof(pl_table.pl_array[index].pl_port);
	env_port = getenv(
		PL_DEFAULT_PL_PORT_ENVAR_NAME
	);
	if(env_port == NULL) {
		strncpy(
			pl_table.pl_array[index].pl_port,
			PL_DEFAULT_PL_AGENT_PL_PORT_STRING,
			bytes_left_in_buffer
		);
		length = strlen(PL_DEFAULT_PL_AGENT_PL_PORT_STRING);
	} else {
		strncpy(
			pl_table.pl_array[index].pl_port,
			env_port,
			bytes_left_in_buffer
		);
		length = strlen(env_port);
		env_port = NULL;
	}
	bytes_left_in_buffer -= length;
	if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
		pl_last_error = PL_OUT_OF_BUFFER_SPACE;
		goto pl_attach_return;
	}

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Check the validity of the port.
	// Note:
	//    Valid port number is in the 1-65535 range
	//    PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE
	//    PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE
	//-------------------------------------------------------------------------
	digit_count = 0;
	for(m = 0; m < (int)length; m++) {
		for(
			n = 0; 
			n < PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS_COUNT; 
			n++
		) {
			if(
				pl_table.pl_array[index].pl_port[m] == 
				allowed_characters_in_port[n]
			) {
				port_value_string[digit_count++] = 
					pl_table.pl_array[index].pl_port[m]
				;
				if(
					digit_count > 
					PL_EXTRA_INPUT_CHECKS_PORT_MAX_DIGITS_IN_PORT_VALUE
				) { 
					goto pl_attach_check_port_error; 
				}
				goto pl_attach_check_port_next;
			}
		} // for n
		goto pl_attach_check_port_error;
pl_attach_check_port_next:
		;
	} // for m

	//-------------------------------------------------------------------------
	// Check port value range.
	//-------------------------------------------------------------------------
	port_value_string[
		PL_EXTRA_INPUT_CHECKS_PORT_BUFFER_LAST_BYTE
	] = '\0';
	value = atoi(port_value_string);
	if(
		(value < PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE) || 
		(value > PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE)
	) {
		goto pl_attach_check_port_error;
	}
	goto pl_attach_check_port_ok;
pl_attach_check_port_error:
	pl_last_error = PL_FILESYSTEM_LESS_INVALID_PORT;
	goto pl_attach_return;
pl_attach_check_port_ok:
	;
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Initialize address data.
	//-------------------------------------------------------------------------
	memset(
		&pl_table.pl_array[index].address_info_hint, 
		0,
		sizeof(pl_table.pl_array[index].address_info_hint)
	);
	pl_table.pl_array[index].address_info_hint.ai_family = 
		PL_ADDRESS_INFO_HINT_AI_FAMILY
	;
	pl_table.pl_array[index].address_info_hint.ai_socktype = 
		PL_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	pl_table.pl_array[index].address_info_hint.ai_protocol = 
		PL_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	pl_table.pl_array[index].address_info_hint.ai_flags = 
		PL_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve agent address and port.
	//-------------------------------------------------------------------------
	ret = getaddrinfo(
		pl_table.pl_array[index].pl_address,
		pl_table.pl_array[index].pl_port, 
		&pl_table.pl_array[index].address_info_hint, 
		&pl_table.pl_array[index].address_info
	);

	if(ret != 0) { 
		pl_last_error = 
			PL_FILESYSTEM_LESS_NETWORK_ADDRESS_RESOLUTION_FAILED;
		goto pl_attach_return;
	}

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_ATTACH command.
	//-------------------------------------------------------------------------
	// pl_attach()
	// +-----------+-------------------------------------------------------------+
	// | OPERATION | <string>                                                    |
	// | CODE      | PL CONFIG INI                                               |
	// |           | ABSOLUTE PATH                                               |
	// +---------- +-------------------------------------------------------------+
	// ^           ^
	// |           |
	// |<--- A --->|<---------------------- B ---------------------------------->
	// |           |
	// |           +--------------- PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX
	// +--------------------------- PL_PROTOCOL_PL_ATTACH_INPUT_OPCODE_INDEX
	//
	// Note:
	//    A = PL_PROTOCOL_OPCODE_SIZE
	//    B = variable
	// Note:
	//    PL_FOLDER transposition - if required - is performed by the agent.
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_ATTACH_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_ATTACH;
	p_string = (char *)pl_config_file_name;
	length = strlen(p_string);
	message_size = (PL_PROTOCOL_SIZET)length;
	memcpy(
		&message[PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	sprintf(
		&message[
			PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX +
			PL_PROTOCOL_SIZET_SIZE
		],
		"%s",
		p_string
	);
	p_string = &message[
		PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX +
		PL_PROTOCOL_SIZET_SIZE +
		length
	];
	*p_string = PL_PROTOCOL_EOR;
	bytes_to_send +=
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_SIZET_SIZE +
		length +
		PL_PROTOCOL_EOR_SIZE
	;
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_attach_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[index].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_socket = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(pl_socket == INVALID_SOCKET) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_attach_unlock_table;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_socket,
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_attach_unlock_table;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_socket,
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = close(
				pl_socket
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_attach_unlock_table;
			}
			continue;
		}
		goto pl_attach_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on EADDRINUSE:
	//    Address already in use.  This error occurs if an application attempts
	//    to bind to a socket that has already been used for an existing socket,
	//    or a socket that wasn't closed properly, or one that is still in the
	//    process of closing.
	//-------------------------------------------------------------------------
	if(errno == EADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_attach_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_attach_unlock_table;

pl_attach_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_ATTACH command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_socket,
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_attach_unlock_table;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer
	//-------------------------------------------------------------------------
	// pl_attach() return
	// +----------+-----------+-----------+----------+
	// | STATUS   | UUID      | PLD       | COUNTERS |
	// | CODE     |           |           | COUNT    |
	// +----------+-----------+-----------+----------+ <-- PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX
	// ^          ^ (LSB-MSB) ^ (LSB-MSB) ^ (LSB-MSB)         
	// |          |           |           |
	// |<-- A --->|<--- B --->|<--- C --->|<-- D --->
	// |          |           |           +--- PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX
	// |          |           +--------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX
	// |          +--------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX
	// +-------------------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//   D = PL_PROTOCOL_COUNTERS_COUNT_SIZE
	// Note:
	//   The uuid is created by the agent and is not exposed to the client.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	memset(
		&pl_input_buffer, 
		0,
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_attach_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (PL_PROTOCOL_SIZET)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_attach_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close PL socket.
	//-------------------------------------------------------------------------
	ret = close(
		pl_socket
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_attach_unlock_table;
	}
	pl_socket = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Extract agent's answer (including the counters count).
	//-------------------------------------------------------------------------
	memcpy(
		&pl_table.pl_array[index].uuid,
		&pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX],
		PL_PROTOCOL_UUID_SIZE
	 );
	memcpy(
		&pl_table.pl_array[index].remote_pld,
		&pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX],
		PL_PROTOCOL_PLD_SIZE
	);
	memcpy(
		&pl_table.pl_array[index].pl_counters_count,
		&pl_input_buffer[PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX],
		PL_PROTOCOL_COUNTERS_COUNT_SIZE
	);
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// At this stage the counters count for the attached PL is known.
	// Allocate memory for the number of counters for the write cache, the
	// the time stamps (if any), the counter access semaphores and sockets.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Allocate memory for the write cache.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(unsigned long long) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_write_cache = 
		(unsigned long long *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_write_cache == NULL) {
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_write_cache, 
		0, 
		memory_size
	);
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate timestamps memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(time_t) * 
		pl_counters_count
	;
	pl_table.pl_array[index].open_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].open_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	memset(
		pl_table.pl_array[index].open_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_attach_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_attach_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_attach_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_read_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_read_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_read_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_write_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_write_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_write_time, 
		0, 
		memory_size
	);
	pl_table.pl_array[index].last_close_time = 
		(time_t *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].last_close_time == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	memset(
		pl_table.pl_array[index].last_close_time, 
		0, 
		memory_size
	);
#endif // __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Allocate semaphore memory.
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
	memory_size = 
		sizeof(sem_t) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(sem_t *)malloc(memory_size)
	;
#endif// __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
	memory_size = 
		sizeof(sem_t *) * 
		pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_handles_semaphores = 
		(sem_t **)malloc(memory_size)
	;
#endif // __PL_MACOSX__
	if(pl_table.pl_array[index].pl_counter_handles_semaphores == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_counter_handles_semaphores, 
		0, 
		memory_size
	);

	//-------------------------------------------------------------------------
	// Allocate socket memory.
	//-------------------------------------------------------------------------
	memory_size = 
		sizeof(SOCKET) * 
		pl_table.pl_array[index].pl_counters_count
	;
	pl_table.pl_array[index].pl_counter_sockets = 
		(SOCKET *)malloc(memory_size)
	;
	if(pl_table.pl_array[index].pl_counter_sockets == NULL) {
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
		pl_last_error = PL_OUT_OF_MEMORY;
		goto pl_attach_unlock_table;
	}
	memset(
		pl_table.pl_array[index].pl_counter_sockets, 
		0,
		memory_size
	);
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Create counters semaphores and initialize and write cache.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[index].pl_counters_count; j++) { 
#ifdef __PL_MACOSX__

		//---------------------------------------------------------------------
		// Semaphore name is PL_SEMAPHORE_NAME_MAX_LENGTH characters of a guuid.
		//---------------------------------------------------------------------
		uuid_generate(pl_uuid);
		memset(
			pl_uuid_buffer_semaphore, 
			0, 
			sizeof(pl_uuid_buffer_semaphore)
		);
		uuid_unparse(
			pl_uuid, 
			pl_uuid_buffer_semaphore
		);
		pl_uuid_buffer_semaphore[PL_SEMAPHORE_NAME_MAX_LENGTH] = '\0';
		pl_table.pl_array[index].pl_counter_handles_semaphores[j] = 
			sem_open(
				pl_uuid_buffer_semaphore, 
				O_CREAT | O_EXCL, 
				(mode_t)PL_SEMAPHORE_ACCESS_MODE, 
				1
			);
		if(pl_table.pl_array[index].pl_counter_handles_semaphores[j] == 
			(sem_t *)SEM_FAILED
		) {
			ret = -1;
		}
#else // __PL_MACOSX__		
		ret = sem_init(
			&pl_table.pl_array[index].pl_counter_handles_semaphores[j], 
			0, 
			1
		);
#endif // __PL_MACOSX__	
		pl_table.pl_array[index].pl_write_cache[j] = PL_MAX_COUNTER_VALUE - 1;
		pl_table.pl_array[index].pl_counter_sockets[j] = INVALID_SOCKET;
	} // for j
#else // __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// In file system mode of operation, the pl_attach API call is carried
	// -out locally using the PL_FOLDER.
	//-------------------------------------------------------------------------
#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Extract productivity link folder.
	//-------------------------------------------------------------------------
	memset(
		pl_folder_buffer, 
		0, 
		sizeof(pl_folder_buffer)
	);
	pl_lenght = strlen(pl_config_file_name);
	strncpy(
		pl_folder, 
		pl_config_file_name, 
		pl_lenght - PL_CONFIG_FILE_NAME_LENGHT
	);
#endif // __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Sample pl_config.ini file (generated by esrv).
	//-------------------------------------------------------------------------
	// esrv
	// 76a145e6-6ea4-47ad-a783-60821b353236
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236 (Note: terminal back slash removed for GCC warning)
	// 63
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (Joule)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (Joule).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (kWh)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy (kWh).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Energy Overflows (no unit)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Update Frequency (second)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power (Watt)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current (Ampere seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min.sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds).sign
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage (Volt seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Power Factor (no unit seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Current Frequency (Hertz seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Max
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Max.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Min
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz)--Min.decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz seconds)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Voltage Frequency (Hertz seconds).decimals
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Channel(s)
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Status
	// C:\productivity_link\esrv_76a145e6-6ea4-47ad-a783-60821b353236\[CHANNEL1] - Version
	// 2010.01.18.(W)
	// _DEBUG
	// _UNICODE
	// UNICODE
	// __PL_DYNAMIC_COUNTERS_ALLOCATION__
	// __PL_WINDOWS__
	// __PL_GENERATE_INI__
	// __PL_GENERATE_INI_VERSION_TAGGING__
	// __PL_GENERATE_INI_BUILD_TAGGING__
	// __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	// __PL_BLOCKING_COUNTER_FILE_LOCK__
	// PL created on Wed Jul 21 12:26:14 2010
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Open productivity link configuration file.
	//-------------------------------------------------------------------------
	pl_config_file = open(
		pl_config_file_name, 
		O_RDONLY
	);
	if(pl_config_file == -1) {

		//---------------------------------------------------------------------
		// Check if the issue could be a UUID case sensitiveness issue.
		// e.g. MacOS X unparses UUID as all upper cases.  Find the UUID.
		//---------------------------------------------------------------------
		memset(
			uuid_cvt_buffer,
			0,
			sizeof(uuid_cvt_buffer)
		);
		memcpy(
			uuid_cvt_buffer,
			pl_config_file_name,
			strlen(pl_config_file_name)
		);
		config_file_name = strstr(
			uuid_cvt_buffer,
			PL_INI_CONFIG_FILE_NAME
		);
		if(config_file_name == NULL) {
			pl_last_error = PL_CONFIG_FILE_OPENING_FAILED;
			goto pl_attach_return;
		}
		uuid = config_file_name - (PL_UUID_MAX_CHARS + 1);
		if(uuid <= uuid_cvt_buffer) {
			pl_last_error = PL_CONFIG_FILE_OPENING_FAILED;
			goto pl_attach_return;
		}

		//---------------------------------------------------------------------
		// Check if all UUID characters are upper case.  If yes, lowercase them
		// and retry opening.
		//---------------------------------------------------------------------
		for(
			i = 0, upper_char_count = 0, lower_char_count = 0; 
			i < PL_UUID_MAX_CHARS; 
			i++
		) {
			if(isupper(uuid[i]) != 0) {
				upper_char_count++;
			} else {
				if(islower(uuid[i]) != 0) {
					lower_char_count++;
				}
			}
		}
		if(upper_char_count == PL_UUID_MAX_NON_DASH_CHARS) {
			for(i = 0; i < PL_UUID_MAX_CHARS; i++) {
				if(isalpha(uuid[i]) != 0) {
					uuid[i] = tolower(uuid[i]);
				}
			}
		} else {
			if(lower_char_count == PL_UUID_MAX_NON_DASH_CHARS) {
				for(i = 0; i < PL_UUID_MAX_CHARS; i++) {
					if(isalpha(uuid[i]) != 0) {
						uuid[i] = toupper(uuid[i]);
					}
				}
			} else {
				pl_last_error = PL_CONFIG_FILE_OPENING_FAILED;
				goto pl_attach_return;
			}
		}
		pl_config_file = open(
			uuid_cvt_buffer, 
			O_RDONLY
		);
		if(pl_config_file == -1) {
			pl_last_error = PL_CONFIG_FILE_OPENING_FAILED;
			goto pl_attach_return;
		}
	}

	//-------------------------------------------------------------------------
	// First pl_attach call *may* take the pl_table initialization penalty.
	//-------------------------------------------------------------------------
	if(pl_table_initialized == 0) {
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// Allocate dynamically the pl_table -- fixed to default size.
		// This size will de expanded if needed later on and during each future 
		// call to pl_attach/pl_open.
		// Caution: this memory will not be freed! (__PL_DYNAMIC_TABLE_ALLOCA-
		// TION__).  Therefore it should never be defined or you can take 
		// responsibility to free it up (as in the PL Agent).
		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ defined
		// --------------------------------------------
		//
		//                                  |<----- LIMITED BY AVAILABLE MEMORY ---->|
		// +-----------------+------+       +------+------+--        --+------+------+
		// |                 |      |       |      |      |            |      |      |
		// | PL table access | *PL -+-----> | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |      |       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |       |      |      |            |      |      |
		// +-----------------+------+       +------+------+--        --+------+------+
		//---------------------------------------------------------------------
		memory_size = 
			sizeof(PRODUCTIVITY_LINK) * 
			PL_MAX_PRODUCTIVITY_LINKS
		;
		pl_table.pl_array = (PPRODUCTIVITY_LINK)malloc(memory_size);
		if(pl_table.pl_array == NULL) {
			pl_last_error = PL_OUT_OF_MEMORY;
			goto pl_attach_return;
		}
		// nulls in-use flags and the handles
		memset(
			pl_table.pl_array, 
			0, 
			memory_size
		); 
		pl_max_productivity_links = PL_MAX_PRODUCTIVITY_LINKS;
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

		//---------------------------------------------------------------------
		// with __PL_DYNAMIC_TABLE_ALLOCATION__ NOT defined
		// ------------------------------------------------
		//
		//                   |<----- PL_MAX_PRODUCTIVITY_LINKS ------>|
		// +-----------------+------+------+--        --+------+------+
		// |                 |      |      |            |      |      |
		// | PL Table access | PL   | PL   |    ...     | PL   | PL   |
		// | semaphore       |   0  |   1  |            |   N-2|   N-1|
		// |                 |      |      |            |      |      |
		// +-----------------+------+------+--        --+------+------+
		//---------------------------------------------------------------------
		// nulls in-use flags and the handles
		memset(
			&pl_table, 
			0, 
			sizeof(PL_TABLE)
		); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
#ifdef __PL_MACOSX__

		//---------------------------------------------------------------------
		// Create PL Table semaphore.
		// Note:
		//    Semaphore name is required by MacOS X POSIX semaphore 
		//    implementation.
		//    Semaphore name is PL_SEMAPHORE_NAME_MAX_LENGTH characters of a 
		//    guuid.
		//---------------------------------------------------------------------
		uuid_generate(pl_uuid);
		memset(
			pl_uuid_buffer, 
			0, 
			sizeof(pl_uuid_buffer)
		);
		uuid_unparse(
			pl_uuid, 
			pl_uuid_buffer
		);
		pl_uuid_buffer[PL_SEMAPHORE_NAME_MAX_LENGTH] = '\0';
		pl_table.semaphore = sem_open(
			pl_uuid_buffer, 
			O_CREAT | O_EXCL, 
			(mode_t)PL_SEMAPHORE_ACCESS_MODE, 
			1
		);
		if(pl_table.semaphore == (sem_t *)SEM_FAILED) {
			ret = -1;
		}
#else // __PL_MACOSX__		
		ret = sem_init(
			&pl_table.semaphore, 
			0, 
			1
		);
#endif // __PL_MACOSX__		
		if(ret == -1) {
			pl_last_error = PL_SYNCHRONIZATION_FAILED;
			goto pl_attach_return;
		}
		pl_table_initialized = 1;
	}

	//-------------------------------------------------------------------------
	// Read-in the data stored in the productivity link configuration file.
	//-------------------------------------------------------------------------
	bytes_left_in_pl_buffer = sizeof(pl_buffer);
	pl_config_file_bytes_to_read = sizeof(char);
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	p = pl_buffer;
	do {

		//---------------------------------------------------------------------
		// Read one byte of the productivity link configuration file.
		//---------------------------------------------------------------------
		pl_config_file_bytes_read = read(
			pl_config_file, 
			p, 
			pl_config_file_bytes_to_read
		);
		if(pl_config_file_bytes_read != pl_config_file_bytes_to_read) {
			if(
				(pl_config_file_bytes_read == 0) && 
				(errno != -1)
			) { 
					goto pl_attach_eof;
			}
		}

		//---------------------------------------------------------------------
		// Analyze the read byte.
		//---------------------------------------------------------------------
		switch(*p) {

			//-----------------------------------------------------------------
			// LF found.
			//-----------------------------------------------------------------
			case PL_CR:
				*p = '\0';
				break;

			//-----------------------------------------------------------------
			// CR found.
			//-----------------------------------------------------------------
			case PL_LF:
				*p = '\0';
				if(strlen(pl_buffer) == 0) {

					//---------------------------------------------------------
					// Skip empty lines -- in case of *NIX interop.
					//---------------------------------------------------------
					goto pl_attach_blank_line;
				}

				//-------------------------------------------------------------
				// Process this line (was populated in the switch default).
				//-------------------------------------------------------------
				lines++;
				if(pl_counters_count != 0) {

					//---------------------------------------------------------
					// Perform PL_FOLDER substitution if required.  Detection
					// of substitution is performed by searching for the
					// PL_INI_WINDOWS_FOLDER substring.
					// Note:
					//    The table is locked, index points to pl_table entry
					//    to use processing counters.
					// Note:
					//    The line stored in pl_buffer is a counter file at
					//    this stage (since pl_counters_count != 0).
					//---------------------------------------------------------
					pl_folder_substitute = strstr(
						pl_buffer, 
						PL_INI_WINDOWS_FOLDER
					);

					//---------------------------------------------------------
					// A PL_FOLDER substitution is required for this counter.
					//---------------------------------------------------------
					if(pl_folder_substitute != NULL) { 

						//-----------------------------------------------------
						// Is it the first counter to be substituted? 
						//-----------------------------------------------------
						if(pl_folder_substitution == 0) {

							//-------------------------------------------------
							// Collect the local PL folder, do it once now.
							//-------------------------------------------------
							px = strstr(
								pl_config_file_name, 
								PL_INI_CONFIG_FILE_NAME
							) - 2;
							while(*px-- !=
								PL_INI_NIX_PATH_SEPARATOR_CHAR
							) {
								char_count++; 
							};
							px += 2;
							bytes_left_in_pl_local_pl_folder = 
								sizeof(pl_local_pl_folder)
							;
							bytes_count = (size_t)(px - pl_config_file_name);
							if(bytes_count > bytes_left_in_pl_local_pl_folder) {
								pl_last_error = PL_OUT_OF_BUFFER_SPACE;
								goto pl_attach_unlock_table;
							}
							strncpy(
								pl_local_pl_folder, 
								pl_config_file_name, 
								bytes_count
							);
							bytes_left_in_pl_local_pl_folder -= 
								bytes_count
							;
							if(
								bytes_left_in_pl_local_pl_folder <= 
								PL_STRNCPY_MIN_BYTES
							) {
								pl_last_error = PL_OUT_OF_BUFFER_SPACE;
								goto pl_attach_unlock_table;
							}
							pl_folder_substitution = 1;
						}

						//-----------------------------------------------------
						// Perform PL_FOLDER substitution. 
						//-----------------------------------------------------
						bytes_left_in_pl_temp = sizeof(pl_temp);
						memset(
							pl_temp, 
							0, 
							PL_MAX_PATH
						);
						strncpy(
							pl_temp, 
							pl_local_pl_folder, 
							bytes_left_in_pl_temp
						);
						bytes_left_in_pl_temp -= strlen(pl_local_pl_folder);
						if(bytes_left_in_pl_temp <= PL_STRNCPY_MIN_BYTES) {
							pl_last_error = PL_OUT_OF_BUFFER_SPACE;
							goto pl_attach_unlock_table;
						}
						strncat(
							pl_temp, 
							pl_folder_substitute + strlen(PL_INI_NIX_FOLDER) - 1, 
							bytes_left_in_pl_temp
						);
						bytes_left_in_pl_temp -= strlen(pl_folder_substitute);
						if(bytes_left_in_pl_temp <= PL_STRNCPY_MIN_BYTES) {
							pl_last_error = PL_OUT_OF_BUFFER_SPACE;
							goto pl_attach_unlock_table;
						}
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
						bytes_left_in_buffer = sizeof(pl_buffer);
						strncpy(
							pl_buffer, 
							pl_temp, 
							bytes_left_in_buffer
						);
						bytes_left_in_buffer -= strlen(pl_temp);
						if(bytes_left_in_buffer <= PL_STRNCPY_MIN_BYTES) {
							pl_last_error = PL_OUT_OF_BUFFER_SPACE;
							goto pl_attach_unlock_table;
						}
					}

#ifdef __PL_EXTRA_INPUT_CHECKS__

					//---------------------------------------------------------
					// Ckeck the counter file name for validity in pl_buffer.
					// Perform the following checkings:
					//   - <PL_FOLDER> is present at the beginning of the input
					//     string.
					//   - PL_INI_NIX_PATH_SEPARATOR follows <PL_FOLDER> in the
					//     input string.
					//   - <PL_INI_CONFIG_FILE_NAME> at the end of the input 
					//     string.
					//   - NULL follows <PL_INI_CONFIG_FILE_NAME> at the end of
					//     the input string.
					//   - <UUID> has a correct structure:
					//      - <UUID> has only allowed characters.
					//      - <UUID> has 4 dashes and five character blocks.
					//      - <UUID> 1st block has 8 characters.
					//      - <UUID> 2nd block has 4 characters.
					//      - <UUID> 3rd block has 4 characters.
					//      - <UUID> 4st block has 4 characters.
					//      - <UUID> 5th block has 12 characters.
					//   - counter name has only allowed characters.
					//   - application name has only allowed characters.
					//   - application name is the same as the reference.
					//   - UUID is the same as the reference.
					//   - counters found count doesn't exceed the reference.
					//   - counters path is the same as the reference.
					// Note:
					//    <PL_FOLDER>/<application_name>_<UUID>/<PL_INI_CONFIG_
					//    FILE_NAME>
					//---------------------------------------------------------

					//---------------------------------------------------------
					// Check if this counter doesn't exceed the reference count. 
					//---------------------------------------------------------
					if(pl_counters_count < 0) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Check if path is the same as the reference.
					//---------------------------------------------------------
					ret = strncmp(
						pl_buffer,
						reference_path,
						bytes_in_reference_path
					);
					if(ret != 0) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Check <PL_FOLDER>/
					//---------------------------------------------------------
					if(pl_folder_substitution == 0) {

						//-----------------------------------------------------
						// No substitution.
						//-----------------------------------------------------
						//character = PL_INI_NIX_PATH_SEPARATOR_CHAR;
						bytes_left_in_buffer = strlen(pl_buffer);
						pl_buffer_end = &pl_buffer[bytes_left_in_buffer - 1];
						buffer_index = strlen(PL_INI_NIX_FOLDER);
						if(bytes_left_in_buffer < buffer_index) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							strncmp(
								pl_buffer,
								PL_INI_NIX_FOLDER,
								buffer_index
							) != 0
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							pl_buffer[buffer_index] !=
							PL_INI_NIX_PATH_SEPARATOR_CHAR
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
					} else {

						//-----------------------------------------------------
						// Substitution.
						//-----------------------------------------------------
						character = PL_INI_WINDOWS_PATH_SEPARATOR_CHAR;
						bytes_left_in_buffer = strlen(pl_buffer);
						pl_buffer_end = &pl_buffer[bytes_left_in_buffer - 1];
						buffer_index = strlen(PL_INI_NIX_FOLDER);
						if(bytes_left_in_buffer < buffer_index) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							strncmp(
								pl_buffer,
								PL_INI_NIX_FOLDER,
								buffer_index
							) != 0
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
						if(
							pl_buffer[buffer_index] !=
							PL_INI_NIX_PATH_SEPARATOR_CHAR
						) {
							pl_last_error = PL_INVALID_PARAMETERS;
							goto pl_attach_unlock_table;
						}
					}
					application_name = 
						(char *)&pl_buffer[++buffer_index]
					;

					//---------------------------------------------------------
					// Search for counter name (by finding the first 
					// PL_INI_NIX_PATH_SEPARATOR_CHAR from the end of the
					// pl_buffer.  We use the opportunity to check that only
					// allowed characters are used in the counter name.
					//---------------------------------------------------------
					do {
						for(
							m = 0;
							m < PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT;
							m++
						) {
							if(
								(
									*pl_buffer_end ==
									PL_INI_NIX_PATH_SEPARATOR_CHAR
								) ||
								(
									*pl_buffer_end ==
									allowed_characters_in_counter_name[m]
								)
							) {
								goto pl_attach_check_counter_name_character_ok;
							}
						} // for m
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
pl_attach_check_counter_name_character_ok:
						;
					} while(
						(
							pl_buffer <
							pl_buffer_end
						) &&
						(
							*pl_buffer_end-- != 
							PL_INI_NIX_PATH_SEPARATOR_CHAR
						)
					);

					//---------------------------------------------------------
					// Extract the UUID.
					//---------------------------------------------------------
					uuid = 
						pl_buffer_end - 
						PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS +
						1
					;
					if(uuid <= pl_buffer) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}
					if(
						*(uuid - 1) !=
						PL_INI_APPLICATION_NAME_SEPARATOR_CHAR
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Check if application name is the same as the reference.
					//---------------------------------------------------------
					bytes_count = (uuid - application_name) - 1;
					ret = strncmp(
						application_name,
						reference_application_name,
						bytes_count
					);
					if(ret != 0) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Check if UUID is the same as the reference.
					//---------------------------------------------------------
					bytes_count = sizeof(reference_uuid) - 1;
					ret = strncmp(
						uuid,
						reference_uuid,
						bytes_count
					);
					if(ret != 0) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}

					//---------------------------------------------------------
					// Search illegal character in UUID and obvious bad format.
					//---------------------------------------------------------
					dash_count = 0;
					block_byte_count = 0;
					for(
						n = 0; 
						n < PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS; 
						n++
					) {
						if(
							uuid[n] == 
							PL_EXTRA_INPUT_CHECKS_UUID_DASH_CHARACTER
						) {
							dash_count++; 
							switch(dash_count) {

								case 1:

									//-----------------------------------------
									// First UUID block 
									// (nnnnnnnn-0000-0000-0000-000000000000).
									//-----------------------------------------
									if(
										block_byte_count != 
										PL_EXTRA_INPUT_CHECKS_UUID_BLOCK1_SIZE
									) {
										pl_last_error = PL_INVALID_PARAMETERS;
										goto pl_attach_unlock_table;
									}
									block_byte_count = 0;
									goto pl_attach_check_pl_buffer_uuid_next;

								case 2:

									//-----------------------------------------
									// Second UUID block 
									// (00000000-nnnn-0000-0000-000000000000).
									//-----------------------------------------
									if(
										block_byte_count != 
										PL_EXTRA_INPUT_CHECKS_UUID_BLOCK2_SIZE
									) {
										pl_last_error = PL_INVALID_PARAMETERS;
										goto pl_attach_unlock_table;
									}
									block_byte_count = 0;
									goto pl_attach_check_pl_buffer_uuid_next;

								case 3:

									//-----------------------------------------
									// Third UUID block 
									// (00000000-0000-nnnn-0000-000000000000).
									//-----------------------------------------
									if(
										block_byte_count != 
										PL_EXTRA_INPUT_CHECKS_UUID_BLOCK3_SIZE
									) {
										pl_last_error = PL_INVALID_PARAMETERS;
										goto pl_attach_unlock_table;
									}
									block_byte_count = 0;
									goto pl_attach_check_pl_buffer_uuid_next;

								case 4:

									//-----------------------------------------
									// Fourth UUID block 
									// (00000000-0000-0000-nnnn-000000000000).
									//-----------------------------------------
									if(
										block_byte_count != 
										PL_EXTRA_INPUT_CHECKS_UUID_BLOCK4_SIZE
									) {
										pl_last_error = PL_INVALID_PARAMETERS;
										goto pl_attach_unlock_table;
									}
									block_byte_count = 0;
									goto pl_attach_check_pl_buffer_uuid_next;

								default:
									pl_last_error = PL_INVALID_PARAMETERS;
									goto pl_attach_unlock_table;
							} // switch
						}
						for(
							m = 0; 
							m < PL_EXTRA_INPUT_CHECKS_UUID_ALLOWED_CHARACTERS_COUNT; 
							m++
						) {
							if(
								uuid[n] == 
								allowed_characters_in_uuid[m]
							) {
								block_byte_count++;
								goto pl_attach_check_pl_buffer_uuid_next;
							}
						}
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_check_pl_buffer_uuid_error;
pl_attach_check_pl_buffer_uuid_next:
						;
					}

					//---------------------------------------------------------
					// Fifth UUID block (00000000-0000-0000-0000-nnnnnnnnnnnn).
					//---------------------------------------------------------
					if(
						block_byte_count != 
						PL_EXTRA_INPUT_CHECKS_UUID_BLOCK5_SIZE
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
					}
					goto pl_attach_check_pl_buffer_uuid_ok;
pl_attach_check_pl_buffer_uuid_error:
					goto pl_attach_unlock_table;
pl_attach_check_pl_buffer_uuid_ok:
					;

					//---------------------------------------------------------
					// Check that only allowed characters are used in the 
					// application name.
					//---------------------------------------------------------
					uuid--;
					do {
						for(
							m = 0;
							m < PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT;
							m++
						) {
							if(
								*application_name ==
								allowed_characters_in_application_name[m]
							) {
								goto pl_attach_check_application_name_character_ok;
							}
						} // for m
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_unlock_table;
pl_attach_check_application_name_character_ok:
						;
					} while (
						application_name++ <
						uuid
					);

#endif // __PL_EXTRA_INPUT_CHECKS__

					//---------------------------------------------------------
					// Open counter file and create associated semaphore.
					//---------------------------------------------------------
#ifdef __PL_ATTACH_SCRIPT_SUPPORT__
					pl_table.pl_array[index].pl_counter_handles[j] = 
						open(
							pl_buffer, 
							O_RDWR
						);
#else // __PL_ATTACH_SCRIPT_SUPPORT__
					pl_table.pl_array[index].pl_counter_handles[j] = 
						open(
							pl_buffer, 
							O_RDONLY
						);
#endif // __PL_ATTACH_SCRIPT_SUPPORT__
					if(pl_table.pl_array[index].pl_counter_handles[j] == -1) {
						pl_last_error = PL_CONFIG_FILE_OPENING_FAILED;
						goto pl_attach_unlock_table;
					}
#ifdef __PL_MACOSX__

					//---------------------------------------------------------
					// Semaphore name is PL_SEMAPHORE_NAME_MAX_LENGTH 
					// characters of a guuid.
					//---------------------------------------------------------
					uuid_generate(pl_uuid);
					memset(
						pl_uuid_buffer, 
						0, 
						sizeof(pl_uuid_buffer)
					);
					uuid_unparse(pl_uuid, pl_uuid_buffer);
					pl_uuid_buffer[PL_SEMAPHORE_NAME_MAX_LENGTH] = '\0';
					pl_table.pl_array[index].pl_counter_handles_semaphores[j] = 
						sem_open(
							pl_uuid_buffer, 
							O_CREAT | O_EXCL, 
							(mode_t)PL_SEMAPHORE_ACCESS_MODE, 
							1
						);
					if(
						pl_table.pl_array[index].pl_counter_handles_semaphores[j] == 
						(sem_t *)SEM_FAILED
					) {
						ret = -1;
					}
#else // __PL_MACOSX__
					ret = sem_init(
						&pl_table.pl_array[index].pl_counter_handles_semaphores[j], 
						0, 
						1
					);
#endif // __PL_MACOSX__					
					if(ret == -1) {
						pl_last_error = PL_COUNTER_SEMAPHORE_CREATION_FAILED;
						goto pl_attach_unlock_table;
					}
					j++;
					pl_table.pl_array[index].pl_counters_count++;
					pl_counters_count--;
				} // if pl_counters_count != 0

#ifdef __PL_EXTRA_INPUT_CHECKS__

				//-------------------------------------------------------------
				// Storing application name.
				// Note:
				//    No checkings are performed since we do not use this data.
				//    However, we store it so we can compare with each counter
				//    data if it matches the reference data.
				//-------------------------------------------------------------
				if(lines == PL_CONFIGURATION_FILE_APPLICATION_NAME_LINE) {
					bytes_count = strlen(pl_buffer);
					if(bytes_count < PL_MAX_PATH) {
						bytes_left_in_buffer = sizeof(
							reference_application_name
						);
						memset(
							reference_application_name,
							0,
							bytes_left_in_buffer
						);
						strncpy(
							reference_application_name,
							pl_buffer,
							bytes_left_in_buffer
						);
					} else {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
				}

				//-------------------------------------------------------------
				// Storing UUID. 
				// Note:
				//    No checkings are performed since we do not use this data.
				//    However, we store it so we can compare with each counter
				//    data if it matches the reference data.
				//-------------------------------------------------------------
				if(lines == PL_CONFIGURATION_FILE_UUID_STRING_LINE) {
					bytes_count = strlen(pl_buffer);
					if(bytes_count <= PL_UUID_MAX_CHARS) {
						bytes_left_in_buffer = sizeof(reference_uuid);
						memset(
							reference_uuid,
							0,
							bytes_left_in_buffer
						);
						strncpy(
							reference_uuid,
							pl_buffer,
							bytes_left_in_buffer
						);
					} else {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
				}

				//-------------------------------------------------------------
				// Storing location. 
				// Note:
				//    No checkings are performed since we do not use this data.
				//    However, we store it so we can compare with each counter
				//    data if it matches the reference data.
				//-------------------------------------------------------------
				if(lines == PL_CONFIGURATION_FILE_LOCATION_LINE) {
					bytes_count = strlen(pl_buffer);
					if(bytes_count < PL_MAX_PATH) {
						bytes_left_in_buffer = sizeof(reference_path);
						memset(
							reference_path,
							0,
							bytes_left_in_buffer
						);
						strncpy(
							reference_path,
							pl_buffer,
							bytes_left_in_buffer
						);
					} else {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
				}
#endif // __PL_EXTRA_INPUT_CHECKS__

				//-------------------------------------------------------------
				// At this stage, no counter file has been found and we are
				// still expecting the non-counter related files.
				//-------------------------------------------------------------
				if(lines == PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE) {

					//---------------------------------------------------------
					// This line contains the number of counters in the PL.
					// Note:
					//    The table is not locked yet.
					//---------------------------------------------------------
#ifdef __PL_EXTRA_INPUT_CHECKS__
					pl_buffer_length = strlen(pl_buffer);
					if(
						pl_buffer_length > 
						strlen(PL_MAX_UNSIGNED_INTEGER_STRING)
					) {
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
					}
					for(n = 0; n < (int)pl_buffer_length; n++) {
						for(
							m = 0;
							m < PL_EXTRA_INPUT_CHECKS_COUNTERS_COUNT_ALLOWED_CHARACTERS_COUNT;
							m++
						) {
							if(
								pl_buffer[n] ==
								allowed_characters_in_counters_count[m]
							) {
								goto pl_attach_check_counter_count_character_next;
							}
						} // for m
						pl_last_error = PL_INVALID_PARAMETERS;
						goto pl_attach_return;
pl_attach_check_counter_count_character_next:
						;
					} // for n
#endif // __PL_EXTRA_INPUT_CHECKS__

					//---------------------------------------------------------
					// Collect and check the counter count.
					// Note:
					//    The table is not locked yet.
					//---------------------------------------------------------
					pl_counters_count = atoi(pl_buffer);

					//---------------------------------------------------------
					// Lock the pl_table against other threads. blocking wait.
					//---------------------------------------------------------
#ifdef __PL_MACOSX__
					ret = sem_wait(pl_table.semaphore);
#else // __PL_MACOSX__					
					ret = sem_wait(&pl_table.semaphore);
#endif // __PL_MACOSX__					
					if(ret == -1) {
						pl_last_error = PL_SYNCHRONIZATION_FAILED;
						goto pl_attach_return;
					}
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__

					//---------------------------------------------------------
					// Search the first unused entry in the pl_table. index 
					// holds the position.
					//---------------------------------------------------------
					for(index = 0; index < PL_MAX_PRODUCTIVITY_LINKS; index++) {
						if(pl_table.pl_array[index].pl_in_use == 0) {
							goto pl_attach_found;
						}
					}
					// pl_table full
					pl_last_error = PL_DESCRIPTOR_TABLE_FULL;
					goto pl_attach_unlock_table;					
#else // __PL_DYNAMIC_TABLE_ALLOCATION__

					//---------------------------------------------------------
					// Search the first unused entry in the pl_table. index 
					// holds the position.
					//---------------------------------------------------------
					for(index = 0; index < pl_max_productivity_links; index++) {
						if(pl_table.pl_array[index].pl_in_use == 0) {
							goto pl_attach_found;
						}
					}

					//---------------------------------------------------------
					// No room in the table, lets double dynamically the 
					// pl_table size and create the additional counters.
					//---------------------------------------------------------
					pl_old_max_productivity_links = pl_max_productivity_links; 
					pl_max_productivity_links *= 2;
					pl_table.pl_array = 
						(PPRODUCTIVITY_LINK)realloc(
							pl_table.pl_array, 
							sizeof(PRODUCTIVITY_LINK) * pl_max_productivity_links
						);
					if(pl_table.pl_array == NULL) {
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					// clear newly allocated memory
					memset(
						&pl_table.pl_array[index], 
						0, 
						sizeof(PRODUCTIVITY_LINK) * pl_old_max_productivity_links
					); 
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
pl_attach_found:
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

					//---------------------------------------------------------
					// Allocate the found number of counters.
					//---------------------------------------------------------
					memory_size = 
						sizeof(unsigned long long) * 
						pl_counters_count
					;
					pl_table.pl_array[index].pl_write_cache = 
						(unsigned long long *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].pl_write_cache == NULL) {
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					memset(
						pl_table.pl_array[index].pl_write_cache, 
						0, 
						memory_size
					);
#ifdef __PL_TIMESTAMPING__
					memory_size = 
						sizeof(time_t) * 
						pl_counters_count
					;
					pl_table.pl_array[index].open_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].open_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					memset(
						pl_table.pl_array[index].open_time, 
						0, 
						memory_size
					);
					pl_table.pl_array[index].last_attach_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].last_attach_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					memset(
						pl_table.pl_array[index].last_attach_time, 
						0, 
						memory_size
					);
					pl_table.pl_array[index].last_read_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].last_read_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					memset(
						pl_table.pl_array[index].last_read_time, 
						0, 
						memory_size
					);
					pl_table.pl_array[index].last_write_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].last_write_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						free(pl_table.pl_array[index].last_read_time);
						pl_table.pl_array[index].last_read_time = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					memset(
						pl_table.pl_array[index].last_write_time, 
						0, 
						memory_size
					);
					pl_table.pl_array[index].last_close_time = 
						(time_t *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].last_close_time == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						free(pl_table.pl_array[index].last_read_time);
						pl_table.pl_array[index].last_read_time = NULL;
						free(pl_table.pl_array[index].last_write_time);
						pl_table.pl_array[index].last_write_time = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					memset(
						pl_table.pl_array[index].last_close_time, 
						0, 
						memory_size
					);
#endif // __PL_TIMESTAMPING__
					memory_size = 
						sizeof(int) * 
						pl_counters_count
					;
					pl_table.pl_array[index].pl_counter_handles = 
						(int *)malloc(memory_size)
					;
					if(pl_table.pl_array[index].pl_counter_handles == NULL) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						free(pl_table.pl_array[index].last_read_time);
						pl_table.pl_array[index].last_read_time = NULL;
						free(pl_table.pl_array[index].last_write_time);
						pl_table.pl_array[index].last_write_time = NULL;
						free(pl_table.pl_array[index].last_close_time);
						pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_return;
					}
					memset(
						pl_table.pl_array[index].pl_counter_handles, 
						0, 
						memory_size
					);
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
					memory_size = 
						sizeof(sem_t) * 
						pl_counters_count
					;
					pl_table.pl_array[index].pl_counter_handles_semaphores = 
						(sem_t *)malloc(memory_size)
					;
#endif// __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
					memory_size = 
						sizeof(sem_t *) * 
						pl_counters_count
					;
					pl_table.pl_array[index].pl_counter_handles_semaphores = 
						(sem_t **)malloc(memory_size)
					;
#endif// __PL_MACOSX__
					if(
						pl_table.pl_array[index].pl_counter_handles_semaphores == 
						NULL
					) {
						free(pl_table.pl_array[index].pl_write_cache);
						pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
						free(pl_table.pl_array[index].open_time);
						pl_table.pl_array[index].open_time = NULL;
						free(pl_table.pl_array[index].last_attach_time);
						pl_table.pl_array[index].last_attach_time = NULL;
						free(pl_table.pl_array[index].last_read_time);
						pl_table.pl_array[index].last_read_time = NULL;
						free(pl_table.pl_array[index].last_write_time);
						pl_table.pl_array[index].last_write_time = NULL;
						free(pl_table.pl_array[index].last_close_time);
						pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
						free(pl_table.pl_array[index].pl_counter_handles);
						pl_table.pl_array[index].pl_counter_handles = NULL;
						pl_last_error = PL_OUT_OF_MEMORY;
						goto pl_attach_unlock_table;
					}
					memset(
						pl_table.pl_array[index].pl_counter_handles_semaphores,
						0, 
						memory_size
					);
					pl_table.pl_array[index].pl_counters_count = 0;

#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
					pl_table.pl_array[index].pl_in_use = 1;
				}

				//-------------------------------------------------------------
				// Reset pl_buffer for next PL configuration file.
				//-------------------------------------------------------------
				bytes_left_in_pl_buffer = sizeof(pl_buffer);
				memset(
					pl_buffer, 
					0, 
					sizeof(pl_buffer)
				);
				p = pl_buffer;
				break;

#ifdef __PL_MACOSX__

			//-----------------------------------------------------------------
			// PL_SOH found.
			//-----------------------------------------------------------------
			case PL_SOH:
			case PL_EOT:
				break;
#endif // __PL_MACOSX__

			//-----------------------------------------------------------------
			// Not a CR or LF found.
			//-----------------------------------------------------------------
			default:
				p++;
				bytes_left_in_pl_buffer--;
				if(bytes_left_in_pl_buffer <= 0) {
					pl_last_error = PL_OUT_OF_BUFFER_SPACE;
					goto pl_attach_return;
				}
				break;
			}
pl_attach_blank_line:
			;
	} while(pl_config_file_bytes_read == pl_config_file_bytes_to_read);

pl_attach_eof:

#ifdef __PL_EXTRA_INPUT_CHECKS__

	//---------------------------------------------------------
	// Check if the counters count matches the reference count. 
	//---------------------------------------------------------
	if(pl_counters_count != 0) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_attach_unlock_table;
	}
#endif // __PL_EXTRA_INPUT_CHECKS__

	//-------------------------------------------------------------------------
	// Close productivity link configuration file.
	//-------------------------------------------------------------------------
	ret = close(pl_config_file);
	if(ret == -1) {
		pl_last_error = PL_CRITICAL_FAILURE;
		goto pl_attach_unlock_table;
	}
#ifdef __PL_BLOCKING_PL_READ__
	
	//-------------------------------------------------------------------------
	// Setup the file system notification handle for the PL.
	//-------------------------------------------------------------------------
#ifdef __PL_LINUX__
	pl_table.pl_array[index].pl_read_notify_instance = inotify_init();
	if(pl_table.pl_array[index].pl_read_notify_instance == -1) {
		pl_last_error = PL_BLOCKING_PL_READ_INSTANCE_CREATION_FAILED;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Add inotify watch.
	//-------------------------------------------------------------------------
	pl_table.pl_array[index].pl_read_notify_handle = inotify_add_watch(
		pl_table.pl_array[index].pl_read_notify_instance, 
		pl_folder, 
		IN_MODIFY
	);
	if(pl_table.pl_array[index].pl_read_notify_handle == -1) {
		pl_last_error = PL_BLOCKING_PL_READ_HANDLE_CREATION_FAILED;
		goto pl_attach_unlock_table;
	}
#endif // __PL_LINUX__
#ifdef __PL_SOLARIS__
#endif // __PL_SOLARIS__
#ifdef __PL_MACOSX__
//TODO:

	//-------------------------------------------------------------------------
	// Setup FSEvent stream used to track file system notification for the PL.
	//-------------------------------------------------------------------------
	//pl_table.pl_array[index].pl_read_notify_stream = FSEventStreamCreate( 
	//	NULL, 
	//	FSEventStreamCallback callback, //beurk!
	//	NULL, 
	//	CFArrayRef pathsToWatch, 
	//	FSEventStreamEventId sinceWhen, 
	//	CFTimeInterval latency, 
	//	FSEventStreamCreateFlags flags
	//);
	
/*
	//-------------------------------------------------------------------------
	// Setup the kernel queue to be used to track file system notification for
	// the PL.
	//-------------------------------------------------------------------------
	pl_table.pl_array[index].pl_read_notify_kernel_queue = kqueue();
    if(pl_table.pl_array[index].pl_read_notify_kernel_queue == -1) {
		pl_last_error = PL_BLOCKING_PL_READ_INSTANCE_CREATION_FAILED;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Get a file descriptor to the PL folder to be used with the kernel event.
	//-------------------------------------------------------------------------
	pl_table.pl_array[index].pl_read_notify_file_descriptor = 
		open(
			pl_folder, 
			O_RDONLY
		);
	if(pl_table.pl_array[index].pl_read_notify_file_descriptor == -1) {
		pl_last_error = PL_BLOCKING_PL_READ_INSTANCE_CREATION_FAILED;
		goto pl_attach_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Register the kernel event used for notification.
	//-------------------------------------------------------------------------
	EV_SET(
		&pl_table.pl_array[index].pl_read_notify_kernel_event, 
		pl_table.pl_array[index].pl_read_notify_file_descriptor, 
		EVFILT_VNODE, 
		EV_ADD | EV_CLEAR, 
		NOTE_WRITE, 
		0, 
		NULL
	);
	ret = kevent(
		pl_table.pl_array[index].pl_read_notify_kernel_queue, 
		&pl_table.pl_array[index].pl_read_notify_kernel_event, 
		1, 
		NULL, 
		0, 
		NULL
	);
	if(ret == -1) {
		pl_last_error = PL_BLOCKING_PL_READ_HANDLE_CREATION_FAILED;
		goto pl_attach_unlock_table;
	}
	if(!
		(pl_table.pl_array[index].pl_read_notify_kernel_event.filter == EVFILT_VNODE && 
		pl_table.pl_array[index].pl_read_notify_kernel_event.fflags & NOTE_WRITE)
	) {
		pl_last_error = PL_BLOCKING_PL_READ_HANDLE_CREATION_FAILED;
		goto pl_attach_unlock_table;
	}
*/
#endif // __PL_MACOSX__
	pl_table.pl_array[index].pl_attach_flag = 1;
#endif // __PL_BLOCKING_PL_READ__
#endif // __PL_FILESYSTEM_LESS__

pl_attach_unlock_table:

#if defined (__PL_EXTRA_INPUT_CHECKS__) && !defined (__PL_FILESYSTEM_LESS__)
	
	if(pl_last_error == PL_INVALID_PARAMETERS) {

		//---------------------------------------------------------------------
		// Close counter files handles and mutexes.
		//---------------------------------------------------------------------
		for(j = 0; j < pl_table.pl_array[index].pl_counters_count; j++) {
			ret = close(
				pl_table.pl_array[index].pl_counter_handles[j]
			);
			if(ret == -1) {
				pl_last_error = PL_CRITICAL_FAILURE;
				goto pl_attach_unlock_table;
			}
#ifdef __PL_MACOSX__
			ret = sem_close(
				pl_table.pl_array[index].pl_counter_handles_semaphores[j]
			);
#else // __PL_MACOSX__		
			ret = sem_destroy(
				&pl_table.pl_array[index].pl_counter_handles_semaphores[j]
			);
#endif // __PL_MACOSX__		
			if(ret == -1) {
				pl_last_error = PL_CRITICAL_FAILURE;
				goto pl_attach_unlock_table;
			}
		} // for j
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

		//---------------------------------------------------------------------
		// Free counter cache, handle and semaphore memory.
		//---------------------------------------------------------------------
		free(pl_table.pl_array[index].pl_write_cache);
		pl_table.pl_array[index].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].open_time);
		pl_table.pl_array[index].open_time = NULL;
		free(pl_table.pl_array[index].last_attach_time);
		pl_table.pl_array[index].last_attach_time = NULL;
		free(pl_table.pl_array[index].last_read_time);
		pl_table.pl_array[index].last_read_time = NULL;
		free(pl_table.pl_array[index].last_write_time);
		pl_table.pl_array[index].last_write_time = NULL;
		free(pl_table.pl_array[index].last_close_time);
		pl_table.pl_array[index].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
		free(pl_table.pl_array[index].pl_counter_handles);
		pl_table.pl_array[index].pl_counter_handles = NULL;
		free(pl_table.pl_array[index].pl_counter_handles_semaphores);
		pl_table.pl_array[index].pl_counter_handles_semaphores = NULL;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

		//---------------------------------------------------------------------
		// Mark PL slot as unused.
		//---------------------------------------------------------------------
		memset(
			&pl_table.pl_array[index], 
			0, 
			sizeof(PRODUCTIVITY_LINK)
		);
		pl_table.pl_array[index].pl_in_use = 0;
	}

#endif // __PL_EXTRA_INPUT_CHECKS__ && !__PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Unlock the productivity link table (locked against other threads).
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_post(pl_table.semaphore);
#else // __PL_MACOSX__	
	ret = sem_post(&pl_table.semaphore);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}

pl_attach_return:

#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Release java arguments
	//-------------------------------------------------------------------------
	(*interface_pointer)->ReleaseStringUTFChars(
		interface_pointer, 
		java_pl_config_file_name, 
		pl_config_file_name
	);

#endif // __PL_JNI_EXPORTS__

#if defined (__PL_EXTRA_INPUT_CHECKS__) && !defined (__PL_FILESYSTEM_LESS__)
	
	if(pl_last_error == PL_INVALID_PARAMETERS) {

		//-----------------------------------------------------
		// Close productivity link configuration file.
		//-----------------------------------------------------
		ret = close(pl_config_file);
		if(
			(ret == -1) && 
			(errno != EBADF)
		) {
			pl_last_error = PL_CRITICAL_FAILURE;
		} else {
			pl_last_error = PL_INVALID_PARAMETERS;
		}
	}

#endif // __PL_EXTRA_INPUT_CHECKS__ && !__PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Return last error and return status.
	//-------------------------------------------------------------------------
	if(pl_last_error != PL_NO_ERROR) {
		errno = pl_last_error;
		return(PL_INVALID_DESCRIPTOR);
	} else {
		pl_last_error = PL_NO_ERROR;
		errno = pl_last_error;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS || __PL_MACOSX__
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Timestamp all counters of the attached PL.
	// Open timestamp is untouched.
	// Last attach timestamp is set.
	// Last read timestamp is untouched.
	// Last write timestamp is untouched.
	// Last close timestamp is untouched.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[index].pl_counters_count; j++) {
		pl_table.pl_array[index].last_attach_time[j] = time(NULL);
	}
#endif // __PL_TIMESTAMPING__
	return(index);
#endif // __PL_BYPASS__ || __PL_LOGGER_ONLY__
}

/*-----------------------------------------------------------------------------
@@@@@  @              @@@@  @       @@@@   @@@@  @@@@@@
@    @ @             @    @ @      @    @ @    @ @
@    @ @             @      @      @    @ @      @
@@@@@  @             @      @      @    @  @@@@  @@@@@@
@      @             @      @      @    @      @ @
@      @             @    @ @      @    @      @ @
@      @@@@@@         @@@@  @@@@@@  @@@@  @@@@@  @@@@@@
              @@@@@@
Function: pl_close
Purpose : close a productivity link
In      : a valid productivity link descriptor
Out     : none
Return  : status and last error set if error occurs

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/01/2008    Jamel Tayeb             Creation.
06/04/2010    Jamel Tayeb             Added __PL_FILESYSTEM_LESS__ support.
*/
#ifdef __PL_JNI_EXPORTS__
JNIEXPORT jint JNICALL Java_ProductivityLink_pl_1close(
	JNIEnv *interface_pointer, 
	jobject caller_reference, 
	jint java_pld
) {

	int pld = PL_INVALID_DESCRIPTOR; 
#else // __PL_JNI_EXPORTS__
PL_API int pl_close(int pld) {
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// If __PL_BYPASS__ is defined, set system's last error code to 
	// PL_BYPASSED and return.
	//-------------------------------------------------------------------------
#ifdef __PL_BYPASS__
#ifdef __PL_WINDOWS__
	SetLastError(PL_BYPASSED);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	errno = PL_BYPASSED;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	return(PL_FAILURE);
#else // __PL_BYPASS__
	int ret = -1;
	unsigned int j = 0;
#ifdef __PL_FILESYSTEM_LESS__
	int one = 1;
	char pl_input_buffer[PL_MAX_INPUT_BUFFER_SIZE] = { '\0' };
	char pl_output_buffer[PL_MAX_OUTPUT_BUFFER_SIZE] = { '\0' };
	char *message = NULL;
	PL_PROTOCOL_STATUS pret = PL_PROTOCOL_FAILURE;
	PL_PROTOCOL_SIZET message_size = 0;
	int connection_attempt_count = 0;
	SOCKET pl_socket = INVALID_SOCKET;
	#ifdef __PL_WINDOWS__
		ADDRINFO *pa = NULL;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		struct addrinfo *pa = NULL;
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// @    @ @@@@@  @    @ @@@@@   @@@@  @    @  @@@@
	// @    @   @    @@   @ @    @ @    @ @    @ @    @
	// @  @ @   @    @ @  @ @    @ @    @ @  @ @  @@@@
	//  @ @ @   @    @   @@ @    @ @    @  @ @ @      @
	//   @ @  @@@@@  @    @ @@@@@   @@@@    @ @  @@@@@
	//-------------------------------------------------------------------------
	DWORD pl_last_error = PL_NO_ERROR;
	DWORD dw_ret = 0;
	BOOL b_ret = FALSE;
#ifdef __PL_FILESYSTEM_LESS__
	errno_t eno_ret = -1;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;
	DWORD dwret = 0;
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Get the java argument.
	//-------------------------------------------------------------------------
	pld = (unsigned int)java_pld;
#endif // __PL_JNI_EXPORTS__
	if(pl_table_initialized == FALSE) {
		pl_last_error = PL_DESCRIPTOR_TABLE_UNINITIALIZED;
		goto pl_close_return;
	}

	//-------------------------------------------------------------------------
	// Check calling argument.
	//-------------------------------------------------------------------------
	if(
		(pld == PL_INVALID_DESCRIPTOR) ||
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || (pld >= PL_MAX_PRODUCTIVITY_LINKS))
#else // __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || ((unsigned int)pld >= pl_max_productivity_links))
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_close_return;
	}
	if(pl_table.pl_array[pld].pl_in_use == 0) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_close_return;
	}

	//-------------------------------------------------------------------------
	// Lock the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
	dw_ret = WaitForSingleObject(
		pl_table.semaphore, 
		INFINITE
	);
	if(dw_ret != WAIT_OBJECT_0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_close_return;
	}
#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_CLOSE command.
	//-------------------------------------------------------------------------
	// pl_close()
	// +-----------+----------+----------+
	// | OPERATION | UUID     | PLD      |
	// | CODE      |          |          |
	// +-----------+----------+----------+ <- PL_PROTOCOL_PL_CLOSE_INPUT_EOR_INDEX
	// ^           ^ (LSB-MSB)^ (LSB-MSB)          
	// |           |          |
	// |<--- A --->|<--- B -->|<-- C --->
	// |           |          |
	// |           |          +---- PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX
	// |           +--------------- PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX
	// +--------------------------- PL_PROTOCOL_PL_CLOSE_INPUT_OPCODE_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_OPCODE_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_CLOSE_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_CLOSE;
	memcpy(
		&message[PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX],
		&pl_table.pl_array[pld].uuid,
		PL_PROTOCOL_UUID_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX],
		&pl_table.pl_array[pld].remote_pld,
		PL_PROTOCOL_PLD_SIZE
	);
	message[
		PL_PROTOCOL_PL_CLOSE_INPUT_EOR_INDEX
	] = PL_PROTOCOL_EOR;
	bytes_to_send = 
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_UUID_SIZE +
		PL_PROTOCOL_PLD_SIZE +
		PL_PROTOCOL_EOR_SIZE
	;
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_close_try_connect:

	//---------------------------------------------------------------------
	// Attempt to connect to the agent - untill one succeds.
	//---------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[pld].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//-----------------------------------------------------------------
		// Create a socket to communicate with the server.
		//-----------------------------------------------------------------
		pl_socket = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(pl_socket == INVALID_SOCKET) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_close_unlock_table;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_socket,
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_close_unlock_table;
		}

		//---------------------------------------------------------------------
		// Connect to the server.
		//---------------------------------------------------------------------
		ret = connect(
			pl_socket,
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, let's close the
			// socket.
			//-----------------------------------------------------------------
			ret = closesocket(
				pl_socket
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_close_unlock_table;
			}
			continue;
		}
		goto pl_close_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on WSAEADDRINUSE:
	//    If you call pl_write at a too high frequency, you may exhaust the
	//    short lived TCP ports.  The default range of short lived ports is 
	//    from 1025 to 5000. Ways to workaround are to increase the dynamic port 
	//    range (to 65534) by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\MaxUserPort;
	//    or by reducing TIME_WAIT from the default 240s (4 minutes) to 30s
	//    by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\TCPTimedWaitDelay
	//-------------------------------------------------------------------------
	dwret = GetLastError();
	if(dwret == WSAEADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_close_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_close_unlock_table;

pl_close_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_OPEN command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_socket,
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_close_unlock_table;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receive agent's answer.
	//-------------------------------------------------------------------------
	// pl_close() return
	// +----------+
	// | STATUS   |
	// | CODE     |
	// +----------+ <--- PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX
	// ^
	// |
	// |<-- A --->
	// |
	// +--------------------------- PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_input_buffer, 
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_close_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (size_t)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_close_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_close_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close PL socket.
	//-------------------------------------------------------------------------
	ret = closesocket(
		pl_socket
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_close_unlock_table;
	}
	pl_socket = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_close_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_close_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Close PL counters sockets and semaphores.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[pld].pl_counters_count; j++) {
		if(pl_table.pl_array[pld].pl_counter_sockets[j] != INVALID_SOCKET) {
			ret = closesocket(
				pl_table.pl_array[pld].pl_counter_sockets[j]
			);
			if(ret == SOCKET_ERROR) {
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_close_unlock_table;
			}
		}
		b_ret = CloseHandle(
			pl_table.pl_array[pld].pl_counter_handles_semaphores[j]
		);
		if(b_ret == 0) {
			pl_last_error = PL_CRITICAL_FAILURE;
			goto pl_close_unlock_table;
		}
	} // for j
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Free PL counter cache memory and PL time stamp data if any.
	//-------------------------------------------------------------------------
	free(pl_table.pl_array[pld].pl_write_cache);
	pl_table.pl_array[pld].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
	free(pl_table.pl_array[pld].open_time);
	pl_table.pl_array[pld].open_time = NULL;
	free(pl_table.pl_array[pld].last_attach_time);
	pl_table.pl_array[pld].last_attach_time = NULL;
	free(pl_table.pl_array[pld].last_read_time);
	pl_table.pl_array[pld].last_read_time = NULL;
	free(pl_table.pl_array[pld].last_write_time);
	pl_table.pl_array[pld].last_write_time = NULL;
	free(pl_table.pl_array[pld].last_close_time);
	pl_table.pl_array[pld].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
	free(pl_table.pl_array[pld].pl_counter_handles_semaphores);
	pl_table.pl_array[pld].pl_counter_handles_semaphores = NULL;
	free(pl_table.pl_array[pld].pl_counter_sockets);
	pl_table.pl_array[pld].pl_counter_sockets = NULL;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Mark PL slot as unused.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_table.pl_array[pld], 
		sizeof(PRODUCTIVITY_LINK)
	);
	pl_table.pl_array[pld].pl_in_use = FALSE;
#else // __PL_FILESYSTEM_LESS__
#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Close the file system notification handle for the PL.
	//-------------------------------------------------------------------------
	if(pl_table.pl_array[pld].pl_attach_flag == 1) {
		b_ret = FindCloseChangeNotification(
			pl_table.pl_array[pld].pl_read_notify_handle
		);
		if(b_ret == 0) {
			pl_last_error = PL_BLOCKING_PL_READ_HANDLE_DESTRUCTION_FAILED;
			goto pl_close_return;
		}
	}
#endif // __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Close counter files handles and semaphores.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[pld].pl_counters_count; j++) {
		b_ret = CloseHandle(
			pl_table.pl_array[pld].pl_counter_handles[j]
		);
		if(b_ret == 0) {
			pl_last_error = PL_CRITICAL_FAILURE;
			goto pl_close_unlock_table;
		}
		b_ret = CloseHandle(
			pl_table.pl_array[pld].pl_counter_handles_semaphores[j]
		);
		if(b_ret == 0) {
			pl_last_error = PL_CRITICAL_FAILURE;
			goto pl_close_unlock_table;
		}
	} // for j
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Free counter cache, handle and semaphore memory.
	//-------------------------------------------------------------------------
	free(pl_table.pl_array[pld].pl_write_cache);
	pl_table.pl_array[pld].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
	free(pl_table.pl_array[pld].open_time);
	pl_table.pl_array[pld].open_time = NULL;
	free(pl_table.pl_array[pld].last_attach_time);
	pl_table.pl_array[pld].last_attach_time = NULL;
	free(pl_table.pl_array[pld].last_read_time);
	pl_table.pl_array[pld].last_read_time = NULL;
	free(pl_table.pl_array[pld].last_write_time);
	pl_table.pl_array[pld].last_write_time = NULL;
	free(pl_table.pl_array[pld].last_close_time);
	pl_table.pl_array[pld].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
	free(pl_table.pl_array[pld].pl_counter_handles);
	pl_table.pl_array[pld].pl_counter_handles = NULL;
	free(pl_table.pl_array[pld].pl_counter_handles_semaphores);
	pl_table.pl_array[pld].pl_counter_handles_semaphores = NULL;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	
	//-------------------------------------------------------------------------
	// Mark PL slot as unused.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_table.pl_array[pld], 
		sizeof(PRODUCTIVITY_LINK)
	);
	pl_table.pl_array[pld].pl_in_use = FALSE;
#endif // __PL_FILESYSTEM_LESS__
pl_close_unlock_table:

	//-------------------------------------------------------------------------
	// Unlock the productivity link table (locked against other threads).
	//-------------------------------------------------------------------------
	b_ret = ReleaseSemaphore(
		pl_table.semaphore, 
		(LONG)1, 
		NULL
	);
	if(b_ret == 0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}
pl_close_return:

	//-------------------------------------------------------------------------
	// Set last error and return status.
	//-------------------------------------------------------------------------
	if(pl_last_error != PL_NO_ERROR) {
		SetLastError(pl_last_error);
		return(PL_FAILURE);
#ifdef __PL_UNIT_TESTS__
	} else {
		pl_last_error = PL_NO_ERROR;
		SetLastError(pl_last_error);
#endif // __PL_UNIT_TESTS__
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  

	//-------------------------------------------------------------------------
	//   @    @    @ @@@@@  @   @
	// @ @ @  @@   @   @     @ @
	//  @@@   @ @  @   @      @
	// @ @ @  @   @@   @     @ @
	//   @    @    @ @@@@@  @   @
	//-------------------------------------------------------------------------
	int pl_last_error = PL_NO_ERROR;
#ifdef __PL_FILESYSTEM_LESS__
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Get the java arguments.
	//-------------------------------------------------------------------------
	pld = (unsigned int)java_pld;
#endif // __PL_JNI_EXPORTS__
	if(pl_table_initialized == 0) {
		pl_last_error = PL_DESCRIPTOR_TABLE_UNINITIALIZED;
		goto pl_close_return;
	}

	//-------------------------------------------------------------------------
	// Check calling argument.
	//-------------------------------------------------------------------------
	if(
		(pld == PL_INVALID_DESCRIPTOR) ||
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || (pld >= PL_MAX_PRODUCTIVITY_LINKS))
#else // __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || ((unsigned int)pld >= pl_max_productivity_links))
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_close_return;
	}

	//-------------------------------------------------------------------------
	// Lock the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_wait(pl_table.semaphore);
#else // __PL_MACOSX__	
	ret = sem_wait(&pl_table.semaphore);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_close_return;
	}
#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// build the PL_PROTOCOL_OPCODE_CLOSE command.
	//-------------------------------------------------------------------------
	// pl_close()
	// +-----------+----------+----------+
	// | OPERATION | UUID     | PLD      |
	// | CODE      |          |          |
	// +-----------+----------+----------+
	// ^           ^ (LSB-MSB)^ (LSB-MSB)          
	// |           |          |
	// |<--- A --->|<--- B -->|<-- C --->
	// |           |          |
	// |           |          +---- PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX
	// |           +--------------- PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX
	// +--------------------------- PL_PROTOCOL_PL_CLOSE_INPUT_OPCODE_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_OPCODE_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_CLOSE_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_CLOSE;
	memcpy(
		&message[PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX],
		&pl_table.pl_array[pld].uuid,
		PL_PROTOCOL_UUID_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX],
		&pl_table.pl_array[pld].remote_pld,
		PL_PROTOCOL_PLD_SIZE
	);
	message[
		PL_PROTOCOL_PL_CLOSE_INPUT_EOR_INDEX
	] = PL_PROTOCOL_EOR;
	bytes_to_send = 
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_UUID_SIZE +
		PL_PROTOCOL_PLD_SIZE +
		PL_PROTOCOL_EOR_SIZE
	;
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_close_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[pld].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_socket = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(pl_socket == INVALID_SOCKET) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_close_unlock_table;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_socket,
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_close_unlock_table;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_socket,
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = close(
				pl_socket
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_close_unlock_table;
			}
			continue;
		}
		goto pl_close_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on EADDRINUSE:
	//    Address already in use.  This error occurs if an application attempts
	//    to bind to a socket that has already been used for an existing socket,
	//    or a socket that wasn't closed properly, or one that is still in the
	//    process of closing.
	//-------------------------------------------------------------------------
	if(errno == EADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_close_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_close_unlock_table;

pl_close_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_CLOSE command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_socket,
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_close_unlock_table;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's data.
	//-------------------------------------------------------------------------
	// pl_close() return
	// +----------+
	// | STATUS   |
	// | CODE     |
	// +----------+ <--- PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX
	// ^
	// |
	// |<-- A --->
	// |
	// +--------------------------- PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	memset(
		&pl_input_buffer, 
		0,
		PL_MAX_INPUT_BUFFER_SIZE
	);	
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_close_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (size_t)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_close_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_socket,
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_close_unlock_table;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close PL socket.
	//-------------------------------------------------------------------------
	ret = close(
		pl_socket
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_close_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_close_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_close_unlock_table;
	}

	//-------------------------------------------------------------------------
	// Close PL counters socket and semaphores.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[pld].pl_counters_count; j++) {
		if(pl_table.pl_array[pld].pl_counter_sockets[j] != INVALID_SOCKET) {
			ret = close(
				pl_table.pl_array[pld].pl_counter_sockets[j]
			);
			if(ret == SOCKET_ERROR) {
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_close_unlock_table;
			}
		}
#ifdef __PL_MACOSX__
		ret = sem_close(
			pl_table.pl_array[pld].pl_counter_handles_semaphores[j]
		);
#else // __PL_MACOSX__		
		ret = sem_destroy(
			&pl_table.pl_array[pld].pl_counter_handles_semaphores[j]
		);
#endif // __PL_MACOSX__		
		if(ret == -1) {
			pl_last_error = PL_CRITICAL_FAILURE;
			goto pl_close_unlock_table;
		}
	} // for j
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Free PL counter cache memory and time stamp data if any.
	//-------------------------------------------------------------------------
	free(pl_table.pl_array[pld].pl_write_cache);
	pl_table.pl_array[pld].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
	free(pl_table.pl_array[pld].open_time);
	pl_table.pl_array[pld].open_time = NULL;
	free(pl_table.pl_array[pld].last_attach_time);
	pl_table.pl_array[pld].last_attach_time = NULL;
	free(pl_table.pl_array[pld].last_read_time);
	pl_table.pl_array[pld].last_read_time = NULL;
	free(pl_table.pl_array[pld].last_write_time);
	pl_table.pl_array[pld].last_write_time = NULL;
	free(pl_table.pl_array[pld].last_close_time);
	pl_table.pl_array[pld].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
	free(pl_table.pl_array[pld].pl_counter_handles_semaphores);
	pl_table.pl_array[pld].pl_counter_handles_semaphores = NULL;
	free(pl_table.pl_array[pld].pl_counter_sockets);
	pl_table.pl_array[pld].pl_counter_sockets = NULL;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	memset(
		&pl_table.pl_array[pld], 
		0, 
		sizeof(PRODUCTIVITY_LINK)
	);

	//-------------------------------------------------------------------------
	// Mark PL slot as unused.
	//-------------------------------------------------------------------------
	memset(
		&pl_table.pl_array[pld],
		0,
		sizeof(PRODUCTIVITY_LINK)
	);	
	pl_table.pl_array[pld].pl_in_use = 0;
#else // __PL_FILESYSTEM_LESS__
#ifdef __PL_BLOCKING_PL_READ__
	if(pl_table.pl_array[pld].pl_attach_flag == 1) {
#ifdef __PL_LINUX__

		//---------------------------------------------------------------------
		// Delete inotify watch.
		//---------------------------------------------------------------------
		ret = inotify_rm_watch(
			pl_table.pl_array[pld].pl_read_notify_instance, 
			pl_table.pl_array[pld].pl_read_notify_handle
		);
		if(ret == -1) {
			pl_last_error = PL_BLOCKING_PL_READ_HANDLE_DESTRUCTION_FAILED;
			goto pl_close_return;
		}

		//---------------------------------------------------------------------
		// Close the file system notification handle for the PL.
		//---------------------------------------------------------------------
		ret = close(
			pl_table.pl_array[pld].pl_read_notify_instance
		);
		if(ret == -1) {
			pl_last_error = PL_BLOCKING_PL_READ_INSTANCE_DESTRUCTION_FAILED;
			goto pl_close_return;
		}
#endif // __PL_LINUX__
#ifdef __PL_SOLARIS__
#endif // __PL_SOLARIS__
#ifdef __PL_MACOSX__
//TODO:
/*
		//---------------------------------------------------------------------
		// Close the file system notification handle for the PL.
		//---------------------------------------------------------------------
		ret = close(
			pl_table.pl_array[pld].pl_read_notify_kernel_queue
		);
		if(ret == -1) {
			pl_last_error = PL_BLOCKING_PL_READ_INSTANCE_DESTRUCTION_FAILED;
			goto pl_close_return;
		}

		//---------------------------------------------------------------------
		// Close the file descriptor to the PL folder to be used with the 
		// kernel event.
		//---------------------------------------------------------------------
		ret = close(
			pl_table.pl_array[pld].pl_read_notify_file_descriptor
		);
		if(ret == -1) {
			pl_last_error = PL_BLOCKING_PL_READ_INSTANCE_DESTRUCTION_FAILED;
			goto pl_close_return;
		}
*/
#endif // __PL_MACOSX__
	}
#endif // __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Close counter files handles and mutexes.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[pld].pl_counters_count; j++) {
		ret = close(
			pl_table.pl_array[pld].pl_counter_handles[j]
		);
		if(ret == -1) {
			pl_last_error = PL_CRITICAL_FAILURE;
			goto pl_close_unlock_table;
		}
#ifdef __PL_MACOSX__
		ret = sem_close(
			pl_table.pl_array[pld].pl_counter_handles_semaphores[j]
		);
#else // __PL_MACOSX__		
		ret = sem_destroy(
			&pl_table.pl_array[pld].pl_counter_handles_semaphores[j]
		);
#endif // __PL_MACOSX__		
		if(ret == -1) {
			pl_last_error = PL_CRITICAL_FAILURE;
			goto pl_close_unlock_table;
		}
	} // for j
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Free counter cache, handle and semaphore memory.
	//-------------------------------------------------------------------------
	free(pl_table.pl_array[pld].pl_write_cache);
	pl_table.pl_array[pld].pl_write_cache = NULL;
#ifdef __PL_TIMESTAMPING__
	free(pl_table.pl_array[pld].open_time);
	pl_table.pl_array[pld].open_time = NULL;
	free(pl_table.pl_array[pld].last_attach_time);
	pl_table.pl_array[pld].last_attach_time = NULL;
	free(pl_table.pl_array[pld].last_read_time);
	pl_table.pl_array[pld].last_read_time = NULL;
	free(pl_table.pl_array[pld].last_write_time);
	pl_table.pl_array[pld].last_write_time = NULL;
	free(pl_table.pl_array[pld].last_close_time);
	pl_table.pl_array[pld].last_close_time = NULL;
#endif // __PL_TIMESTAMPING__
	free(pl_table.pl_array[pld].pl_counter_handles);
	pl_table.pl_array[pld].pl_counter_handles = NULL;
	free(pl_table.pl_array[pld].pl_counter_handles_semaphores);
	pl_table.pl_array[pld].pl_counter_handles_semaphores = NULL;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Mark PL slot as unused.
	//-------------------------------------------------------------------------
	memset(
		&pl_table.pl_array[pld], 
		0, 
		sizeof(PRODUCTIVITY_LINK)
	);
	pl_table.pl_array[pld].pl_in_use = 0;
#endif // __PL_FILESYSTEM_LESS__
pl_close_unlock_table:

	//-------------------------------------------------------------------------
	// Unlock the productivity link table (locked against other threads).
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_post(pl_table.semaphore);
#else // __PL_MACOSX__	
	ret = sem_post(&pl_table.semaphore);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}
pl_close_return:

	//-------------------------------------------------------------------------
	// Set last error and return status.
	//-------------------------------------------------------------------------
	if(pl_last_error != PL_NO_ERROR) {
		errno = pl_last_error;
		return(PL_FAILURE);
#ifdef __PL_UNIT_TESTS__
	} else {
		pl_last_error = PL_NO_ERROR;
		errno = pl_last_error;
#endif // __PL_UNIT_TESTS__
	}
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Timestamp all counters of the closed PL.
	// Open timestamp is untouched.
	// Last attach timestamp is untouched.
	// Last read timestamp is untouched.
	// Last write timestamp is untouched.
	// Last close timestamp is set.
	//-------------------------------------------------------------------------
	for(j = 0; j < pl_table.pl_array[pld].pl_counters_count; j++) {
		pl_table.pl_array[pld].last_attach_time[j] = time(NULL);
	}
#endif // __PL_TIMESTAMPING__
	return(PL_SUCCESS);
#endif // __PL_BYPASS__
}

/*-----------------------------------------------------------------------------
@@@@@  @             @@@@@  @@@@@@   @@   @@@@@
@    @ @             @    @ @       @  @  @    @
@    @ @             @    @ @      @    @ @    @
@@@@@  @             @@@@@  @@@@@@ @    @ @    @
@      @             @  @   @      @@@@@@ @    @
@      @             @   @  @      @    @ @    @
@      @@@@@@        @    @ @@@@@@ @    @ @@@@@
              @@@@@@
Function: pl_read
Purpose : read a counter's value from a productivity link
In      : a valid productivity link descriptor holding the counter
		: pointer to destination buffer
		: offset to the counter
Out     : status and last error set if error occurs

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/01/2008    Jamel Tayeb             Creation.
06/04/2010    Jamel Tayeb             Added __PL_FILESYSTEM_LESS__ support.
*/
#ifndef __PL_LOGGER_ONLY__
#ifdef __PL_JNI_EXPORTS__
JNIEXPORT jint JNICALL Java_ProductivityLink_pl_1read(
	JNIEnv *interface_pointer, 
	jobject caller_reference, 
	jint java_pld, 
	jobject java_counter_value, 
	jint java_counter
) {

	jfieldID counter_field_id = NULL;
	jclass counter_class = NULL;
	int pld = PL_INVALID_DESCRIPTOR;
	unsigned long long temp_counter = 0;
	unsigned int counter = 0;
	void *p = NULL;
#else // __PL_JNI_EXPORTS__
PL_API int pl_read(int pld, void *p, unsigned int counter) {
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// If __PL_BYPASS__ is defined, set system's last error code to 
	// PL_BYPASSED and return.
	//-------------------------------------------------------------------------
#if defined (__PL_BYPASS__) || (__PL_LOGGER_ONLY__)
	#ifdef __PL_WINDOWS__
		SetLastError(PL_BYPASSED);
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		errno = PL_BYPASSED;
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		return(PL_FAILURE);
#else // __PL_BYPASS__ || __PL_LOGGER_ONLY__
#ifdef __PL_FILESYSTEM_LESS__
	int one = 1;
	char *message = NULL;
	char pl_input_buffer[PL_MAX_INPUT_BUFFER_SIZE] = { '\0' };
	char pl_output_buffer[PL_MAX_OUTPUT_BUFFER_SIZE] = { '\0' };
	PL_PROTOCOL_STATUS pret = PL_PROTOCOL_FAILURE;
	PL_PROTOCOL_SIZET message_size = 0;
	int connection_attempt_count = 0; 
	#ifdef __PL_WINDOWS__
		ADDRINFO *pa = NULL;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		struct addrinfo *pa = NULL;
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#else // __PL_FILESYSTEM_LESS__
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	int lock_attempt_count = 0;
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// @    @ @@@@@  @    @ @@@@@   @@@@  @    @  @@@@
	// @    @   @    @@   @ @    @ @    @ @    @ @    @
	// @  @ @   @    @ @  @ @    @ @    @ @  @ @  @@@@
	//  @ @ @   @    @   @@ @    @ @    @  @ @ @      @
	//   @ @  @@@@@  @    @ @@@@@   @@@@    @ @  @@@@@
	//-------------------------------------------------------------------------
	DWORD pl_last_error = PL_NO_ERROR;
	BOOL b_ret = FALSE;
	DWORD dw_ret = 0;
#ifdef __PL_FILESYSTEM_LESS__
	int ret = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;
	DWORD dwret = 0;
#else // __PL_FILESYSTEM_LESS__
	LARGE_INTEGER offset;
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	OVERLAPPED overlapped; 
	DWORD bytes_transferred = 0;
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
	DWORD pl_counter_file_bytes_to_read = 0;
	DWORD pl_counter_file_bytes_read = 0;
#ifndef __PL_BINARY_COUNTER__
	char pl_buffer[PL_MAX_BUFFER_SIZE];
	char *pl_offending_char = NULL;
#endif // __PL_BINARY_COUNTER__
#ifdef __PL_BLOCKING_PL_READ__
	DWORD dw_status = 0;
#endif // __PL_BLOCKING_PL_READ__
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Caching counter class and field id.
	//-------------------------------------------------------------------------
	if(counter_field_id == NULL) {
		counter_class = (*interface_pointer)->GetObjectClass(
			interface_pointer, 
			java_counter_value
		);
		if(counter_class == NULL) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_read_return;
		}
		counter_field_id = (*interface_pointer)->GetFieldID(
			interface_pointer, 
			counter_class, 
			"value", 
			"J"
		);
		if(counter_field_id == NULL) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_read_return;
		}
	}

	//-------------------------------------------------------------------------
	// Get the java arguments & initializations
	//-------------------------------------------------------------------------
	pld = (unsigned int)java_pld;
	counter = (unsigned int)java_counter;
	p = (void *)&temp_counter;
#endif // __PL_JNI_EXPORTS__
	if(pl_table_initialized == FALSE) {
		pl_last_error = PL_DESCRIPTOR_TABLE_UNINITIALIZED;
		goto pl_read_return;
	}

	//-------------------------------------------------------------------------
	// Check calling arguments.
	//-------------------------------------------------------------------------
	if(
		(pld == PL_INVALID_DESCRIPTOR) ||
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || (pld >= PL_MAX_PRODUCTIVITY_LINKS)) ||
#else // __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || ((unsigned int)pld >= pl_max_productivity_links)) ||
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
		(p == NULL) ||
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		((counter < 0) && (counter >= PL_MAX_COUNTERS_PER_LINK)) ||
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		(counter >= pl_table.pl_array[pld].pl_counters_count)
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_read_return;
	}
#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Lock the counter in the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
	dw_ret = WaitForSingleObject(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter], 
		INFINITE
	);
	if(dw_ret != WAIT_OBJECT_0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_read_return;
	}

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_READ command.
	//-------------------------------------------------------------------------
	// +-----------+---------+---------+-----------+
	// | OPERATION | UUID    | PLD     | OFFSET    |
	// | CODE      |         |         |           |
	// +-----------+---------+---------+-----------+ <- PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX
	// ^           ^         ^         ^
	// |           |         |         |
	// |<--- A --->|<-- B -->|<-- C -->|<--- D --->
	// |           |(LSB-MSB)|(LSB-MSB)|(LSB-MSB)
	// |           |         |         |
	// |           |         |         +------- PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX
	// |           |         +----------------- PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX
	// |           +--------------------------- PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX
	// +--------------------------------------- PL_PROTOCOL_PL_READ_INPUT_OPCODE_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_OPCODE_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//   D = PL_PROTOCOL_COUNTER_OFFSET_SIZE
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_READ_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_READ;
	memcpy(
		&message[PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX],
		&pl_table.pl_array[pld].uuid,
		PL_PROTOCOL_UUID_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX],
		&pl_table.pl_array[pld].remote_pld,
		PL_PROTOCOL_PLD_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX],
		&counter,
		PL_PROTOCOL_COUNTER_OFFSET_SIZE
	);
	message[
		PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX
	] = PL_PROTOCOL_EOR;
	bytes_to_send = (
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_UUID_SIZE +
		PL_PROTOCOL_PLD_SIZE +
		PL_PROTOCOL_COUNTER_OFFSET_SIZE +
		PL_PROTOCOL_EOR_SIZE
	);
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_read_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[pld].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_table.pl_array[pld].pl_counter_sockets[counter] = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(
			pl_table.pl_array[pld].pl_counter_sockets[counter] == 
			INVALID_SOCKET
		) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_read_unlock_counter;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_read_unlock_counter;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = closesocket(
				pl_table.pl_array[pld].pl_counter_sockets[counter]
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_read_unlock_counter;
			}
			continue;
		}
		goto pl_read_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on WSAEADDRINUSE:
	//    If you call pl_write at a too high frequency, you may exhaust the
	//    short lived TCP ports.  The default range of short lived ports is 
	//    from 1025 to 5000. Ways to workaround are to increase the dynamic port 
	//    range (to 65534) by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\MaxUserPort;
	//    or by reducing TIME_WAIT from the default 240s (4 minutes) to 30s
	//    by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\TCPTimedWaitDelay
	//-------------------------------------------------------------------------
	dwret = GetLastError();
	if(dwret == WSAEADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_read_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_read_unlock_counter;

pl_read_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_WRITE command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_read_unlock_counter;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer
	//-------------------------------------------------------------------------
	// pl_read() return
	// +----------+----------+
	// | STATUS   | VALUE    |
	// | CODE     |          |
	// +----------+----------+ <--- PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX
	// ^          ^
	// |          |
	// |<-- A --->|<-- B --->
	// |          |(LSB-MSB)
	// |          |
	// |          +---------------------------- PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX
	// +--------------------------------------- PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//   B = PL_PROTOCOL_ULL_SIZE
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_input_buffer, 
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_read_unlock_counter;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (size_t)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_read_unlock_counter;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_read_unlock_counter;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close PL socket.
	//-------------------------------------------------------------------------
	ret = closesocket(
		pl_table.pl_array[pld].pl_counter_sockets[counter]
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_read_unlock_counter;
	}
	pl_table.pl_array[pld].pl_counter_sockets[counter] = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_read_unlock_counter;
	}	

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_read_unlock_counter;
	}

	//-------------------------------------------------------------------------
	// Extract counter's value.
	//-------------------------------------------------------------------------
	memcpy(
		p,
		(void *)&pl_input_buffer[PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX],
		PL_PROTOCOL_ULL_SIZE
	);
#else // __PL_FILESYSTEM_LESS__
#ifdef __PL_BINARY_COUNTER__
	pl_counter_file_bytes_to_read = (DWORD)sizeof(ULONGLONG);
#else // __PL_BINARY_COUNTER__
	pl_counter_file_bytes_to_read = (DWORD)sizeof(pl_buffer);
#endif // __PL_BINARY_COUNTER__
#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Wait until FILE_NOTIFY_CHANGE_LAST_WRITE is notified.
	// blocking read only makes sense with attached PLs.
	//-------------------------------------------------------------------------
	if(pl_table.pl_array[pld].pl_attach_flag == 1) { 
		b_ret = FindNextChangeNotification(
			pl_table.pl_array[pld].pl_read_notify_handle
		);
		if(b_ret == 0) {
			pl_last_error = PL_BLOCKING_PL_READ_HANDLE_RENEWING_FAILED;
			goto pl_read_return;
		}
		dw_status = WaitForSingleObject(
			pl_table.pl_array[pld].pl_read_notify_handle, 
			INFINITE
		);
		if(dw_status != WAIT_OBJECT_0) {
			pl_last_error = PL_BLOCKING_PL_READ_WAITING_NOTIFICATION_FAILED;
			goto pl_read_return;
		}
	}
#endif // __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Lock the counter in the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
	dw_ret = WaitForSingleObject(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter], 
		INFINITE
	);
	if(dw_ret != WAIT_OBJECT_0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_read_return;
	}

	//-------------------------------------------------------------------------
	// Lock the counter file against other processes.
	//-------------------------------------------------------------------------
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	overlapped.hEvent = 0;
	overlapped.Offset = 0;
	overlapped.OffsetHigh = 0;
pl_read_try_lock:
	b_ret = LockFileEx(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		LOCKFILE_EXCLUSIVE_LOCK, 
		0, 
		pl_counter_file_bytes_to_read, 
		0, 
		&overlapped
	);
	if(b_ret == FALSE) {
		if(lock_attempt_count++ < PL_MAX_COUNTER_FILE_LOCK_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_read_try_lock; 
		} else {
			pl_last_error = PL_COUNTER_FILE_LOCK_FAILED;
			goto pl_read_unlock_counter;
		}
	}
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__
	
	//-------------------------------------------------------------------------
	// In non-blocking mode, if we cannot lock the counter file, then we signal
	// it with PL_COUNTER_FILE_ALREADY_LOCKED last error, setting data to 0 and 
	// returning error status. the caller can ignore it (a loosy logger for 
	// example) and continue processing.
	//-------------------------------------------------------------------------
	b_ret = LockFile(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		0, 
		pl_counter_file_bytes_to_read, 
		0, 
		0
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_FILE_ALREADY_LOCKED;
		*(ULONGLONG *)p = 0;
		goto pl_read_unlock_counter;
	}
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__

	//-------------------------------------------------------------------------
	// Point to the counter file head.
	//-------------------------------------------------------------------------
	offset.QuadPart = 0;
	b_ret = SetFilePointerEx(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		offset, 
		NULL, 
		FILE_BEGIN
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_FILE_RESET_FILE_POINTER_FAILED;
		goto pl_read_unlock_counter_file;
	}

	//-------------------------------------------------------------------------
	// Read the counter data (ascii or binary).
	//-------------------------------------------------------------------------
#ifdef __PL_BINARY_COUNTER__
	b_ret = ReadFile(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		p, 
		pl_counter_file_bytes_to_read, 
		&pl_counter_file_bytes_read, NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_READ_FAILED;
		goto pl_read_unlock_counter_file;
	}
#else // __PL_BINARY_COUNTER__
	ZeroMemory(
		pl_buffer, 
		sizeof(pl_buffer)
	);
	b_ret = ReadFile(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		pl_buffer, 
		pl_counter_file_bytes_to_read, 
		&pl_counter_file_bytes_read, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_READ_FAILED;
		goto pl_read_unlock_counter_file;
	}
	*(ULONGLONG *)p = _strtoui64(
		pl_buffer, 
		&pl_offending_char, 
		PL_COUNTER_BASE
	);
	if(
		(errno == ERANGE) || // In all out-of-range cases, errno is set to ERANGE.
		((pl_offending_char != NULL) && (*pl_offending_char != '\0'))
	) {
		pl_last_error = PL_COUNTER_VALUE_OUT_OF_RANGE;
		goto pl_read_unlock_counter_file;
	}
#endif // __PL_BINARY_COUNTER__
pl_read_unlock_counter_file:

	//-------------------------------------------------------------------------
	// Unlock the counter file locked against other processes.
	//-------------------------------------------------------------------------
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	b_ret = UnlockFileEx(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		0, 
		pl_counter_file_bytes_to_read, 
		0, 
		&overlapped
	);
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__
	b_ret = UnlockFile(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		0, 
		pl_counter_file_bytes_to_read, 
		0, 
		0
	);
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_FILE_UNLOCK_FAILED;
	}
#endif // __PL_FILESYSTEM_LESS__
pl_read_unlock_counter:

	//-------------------------------------------------------------------------
	// Unlock the counter in the pl_table locked against other threads.
	//-------------------------------------------------------------------------
	b_ret = ReleaseSemaphore(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter], 
		(LONG)1, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}
pl_read_return:

	//-------------------------------------------------------------------------
	// Set last error code and return status.
	//-------------------------------------------------------------------------
	if(pl_last_error != PL_NO_ERROR) {
		SetLastError(pl_last_error);
		return(PL_FAILURE);
#ifdef __PL_UNIT_TESTS__
	} else {
		pl_last_error = PL_NO_ERROR;
		SetLastError(pl_last_error);
#endif // __PL_UNIT_TESTS__
	}
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Return counter value.
	//-------------------------------------------------------------------------
	(*interface_pointer)->SetLongField(
		interface_pointer, 
		java_counter_value, 
		counter_field_id, 
		(jlong)temp_counter
	);
#endif // __PL_JNI_EXPORTS__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  

	//-------------------------------------------------------------------------
	//   @    @    @ @@@@@  @   @
	// @ @ @  @@   @   @     @ @
	//  @@@   @ @  @   @      @
	// @ @ @  @   @@   @     @ @
	//   @    @    @ @@@@@  @   @
	//-------------------------------------------------------------------------
	int pl_last_error = PL_NO_ERROR;
	int ret = 0;	
#ifdef __PL_FILESYSTEM_LESS__
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;
#else // __PL_FILESYSTEM_LESS__
	size_t pl_counter_file_bytes_to_read = 0;
	off_t ot_ret = (off_t)0;
	size_t pl_counter_file_bytes_read = 0;
	struct flock pl_lock;
#ifndef __PL_BINARY_COUNTER__
	char pl_buffer[PL_MAX_BUFFER_SIZE];
	char *pl_offending_char = NULL;
#endif // __PL_BINARY_COUNTER__
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Caching counter class and field id.
	//-------------------------------------------------------------------------
	if(counter_field_id == NULL) {
		counter_class = (*interface_pointer)->GetObjectClass(
			interface_pointer, 
			java_counter_value
		);
		if(counter_class == NULL) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_read_return;
		}
		counter_field_id = (*interface_pointer)->GetFieldID(
			interface_pointer, 
			counter_class, 
			"value", 
			"J"
		);
		if(counter_field_id == NULL) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_read_return;
		}
	}

	//-------------------------------------------------------------------------
	// Get the java arguments & initializations.
	//-------------------------------------------------------------------------
	pld = (unsigned int)java_pld;
	counter = (unsigned int)java_counter;
	p = (void *)&temp_counter;
#endif // __PL_JNI_EXPORTS__
	if(pl_table_initialized == 0) {
		pl_last_error = PL_DESCRIPTOR_TABLE_UNINITIALIZED;
		goto pl_read_return;
	}

	//-------------------------------------------------------------------------
	// Check calling arguments.
	//-------------------------------------------------------------------------
	if(
		(pld == PL_INVALID_DESCRIPTOR) ||
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || (pld >= PL_MAX_PRODUCTIVITY_LINKS)) ||
#else // __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || ((unsigned int)pld >= pl_max_productivity_links)) ||
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
		(p == NULL) ||
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		(counter > PL_MAX_COUNTERS_PER_LINK) ||
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		(counter >= pl_table.pl_array[pld].pl_counters_count)
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_read_return;
	}
#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Lock the counter in the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_wait(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#else // __PL_MACOSX__	
	ret = sem_wait(
		&pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_read_return;
	}

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_READ command.
	//-------------------------------------------------------------------------
	// +-----------+---------+---------+-----------+
	// | OPERATION | UUID    | PLD     | OFFSET    |
	// | CODE      |         |         |           |
	// +-----------+---------+---------+-----------+ <- PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX
	// ^           ^         ^         ^
	// |           |         |         |
	// |<--- A --->|<-- B -->|<-- C -->|<--- D --->
	// |           |(LSB-MSB)|(LSB-MSB)|(LSB-MSB)
	// |           |         |         |
	// |           |         |         +------- PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX
	// |           |         +----------------- PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX
	// |           +--------------------------- PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX
	// +--------------------------------------- PL_PROTOCOL_PL_READ_INPUT_OPCODE_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_OPCODE_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//   D = PL_PROTOCOL_COUNTER_OFFSET_SIZE
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_READ_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_READ;
	memcpy(
		&message[PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX],
		&pl_table.pl_array[pld].uuid,
		PL_PROTOCOL_UUID_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX],
		&pl_table.pl_array[pld].remote_pld,
		PL_PROTOCOL_PLD_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX],
		&counter,
		PL_PROTOCOL_COUNTER_OFFSET_SIZE
	);
	message[
		PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX
	] = PL_PROTOCOL_EOR;
	bytes_to_send = (
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_UUID_SIZE +
		PL_PROTOCOL_PLD_SIZE +
		PL_PROTOCOL_COUNTER_OFFSET_SIZE +
		PL_PROTOCOL_EOR_SIZE
	);
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_read_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[pld].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_table.pl_array[pld].pl_counter_sockets[counter] = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(
			pl_table.pl_array[pld].pl_counter_sockets[counter] == 
			INVALID_SOCKET
		) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_read_unlock_counter;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_read_unlock_counter;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = close(
				pl_table.pl_array[pld].pl_counter_sockets[counter]
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_read_unlock_counter;
			}
			continue;
		}
		goto pl_read_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on EADDRINUSE:
	//    Address already in use.  This error occurs if an application attempts
	//    to bind to a socket that has already been used for an existing socket,
	//    or a socket that wasn't closed properly, or one that is still in the
	//    process of closing.
	//-------------------------------------------------------------------------
	if(errno == EADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_read_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_read_unlock_counter;

pl_read_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_WRITE command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_read_unlock_counter;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer
	//-------------------------------------------------------------------------
	// pl_read() return
	// +----------+----------+
	// | STATUS   | VALUE    |
	// | CODE     |          |
	// +----------+----------+ <--- PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX
	// ^          ^
	// |          |
	// |<-- A --->|<-- B --->
	// |          |(LSB-MSB)
	// |          |
	// |          +---------------------------- PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX
	// +--------------------------------------- PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//   B = PL_PROTOCOL_ULL_SIZE
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	memset(
		&pl_input_buffer, 
		0,
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_read_unlock_counter;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (size_t)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_read_unlock_counter;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_read_unlock_counter;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close counter socket.
	//-------------------------------------------------------------------------
	ret = close(
		pl_table.pl_array[pld].pl_counter_sockets[counter]
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_read_unlock_counter;
	}
	pl_table.pl_array[pld].pl_counter_sockets[counter] = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_COUNTER_READ_FAILED;
		goto pl_read_unlock_counter;
	}

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_read_unlock_counter;
	}

	//-------------------------------------------------------------------------
	// Extract counter's value.
	//-------------------------------------------------------------------------
	memcpy(
		p,
		(void *)&pl_input_buffer[PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX],
		PL_PROTOCOL_ULL_SIZE
	);
#else // __PL_FILESYSTEM_LESS__
#ifdef __PL_BINARY_COUNTER__
	pl_counter_file_bytes_to_read = sizeof(unsigned long long);
#else // __PL_BINARY_COUNTER__
	pl_counter_file_bytes_to_read = sizeof(pl_buffer);
#endif // __PL_BINARY_COUNTER__
#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Wait until IN_MODIFY is notified.
	// blocking read only makes sense with attached PLs.
	//-------------------------------------------------------------------------
	if(pl_table.pl_array[pld].pl_attach_flag == 1) {
#ifdef __PL_LINUX__
		ret = read(
			pl_table.pl_array[pld].pl_read_notify_instance, 
			pl_table.pl_array[pld].pl_read_notify_buffer, 
			PL_BLOCKING_PL_READ_NOTIFY_BUFFER_SIZE
		);
		if((ret == -1) && (errno != EINTR)) {
			pl_last_error = PL_BLOCKING_PL_READ_WAITING_NOTIFICATION_FAILED;
			goto pl_read_return;
		}
#endif // __PL_LINUX__
#ifdef __PL_SOLARIS__
#endif // __PL_SOLARIS__
#ifdef __PL_MACOSX__
//TODO:
/*
		ret = kevent(
			pl_table.pl_array[pld].pl_read_notify_kernel_queue, 
			NULL, 
			0, 
			&pl_table.pl_array[pld].pl_read_notify_kernel_event, 
			1, 
			NULL
		);
		if(ret == -1) {
			pl_last_error = PL_BLOCKING_PL_READ_WAITING_NOTIFICATION_FAILED;
			goto pl_read_return;
		}
*/
#endif // __PL_MACOSX__
	}
#endif // __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Lock the counter in the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_wait(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#else // __PL_MACOSX__	
	ret = sem_wait(
		&pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_read_return;
	}

	//-------------------------------------------------------------------------
	// Lock the counter file against other processes.
	//-------------------------------------------------------------------------
	pl_lock.l_type = (short)F_RDLCK;
	pl_lock.l_whence = (short)SEEK_SET;
	pl_lock.l_start = (off_t)0;
	pl_lock.l_len = (off_t)pl_counter_file_bytes_to_read;
	pl_lock.l_pid = getpid();
pl_read_try_lock:
	ret = fcntl(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		F_SETLK, 
		&pl_lock
	);
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	//nop
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__
	//nop
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
	if(ret == -1) {
		if(errno == EAGAIN) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_read_try_lock;
		}
		if(lock_attempt_count++ < PL_MAX_COUNTER_FILE_LOCK_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_read_try_lock;
		} else {
			pl_last_error = PL_COUNTER_FILE_LOCK_FAILED;
			goto pl_read_unlock_counter;
		}
	}

	//-------------------------------------------------------------------------
	// Point to the counter file head.
	//-------------------------------------------------------------------------
	ot_ret = lseek(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		(off_t)0, 
		SEEK_SET
	);
	if(ot_ret == (off_t)-1) {
		pl_last_error = PL_COUNTER_FILE_RESET_FILE_POINTER_FAILED;
		goto pl_read_unlock_counter_file;
	}

	//-------------------------------------------------------------------------
	// Read the counter data (ascii or binary).
	//-------------------------------------------------------------------------
#ifdef __PL_BINARY_COUNTER__
	pl_counter_file_bytes_read = read(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		p, 
		pl_counter_file_bytes_to_read
	);
#else // __PL_BINARY_COUNTER__
	memset(pl_buffer, 0, sizeof(pl_buffer));
	pl_counter_file_bytes_read = read(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		pl_buffer, 
		pl_counter_file_bytes_to_read
	);
#ifdef __PL_SOLARIS__
	errno = 0;
#endif // __PL_SOLOARIS__
	*(unsigned long long *)p = strtoull(
		pl_buffer, 
		&pl_offending_char, 
		PL_COUNTER_BASE
	);
	if(
		(errno == ERANGE) || // In all out-of-range cases, errno is set to ERANGE.
		((pl_offending_char != NULL) && (*pl_offending_char != '\0'))
	) {
		pl_last_error = PL_COUNTER_VALUE_OUT_OF_RANGE;
		goto pl_read_unlock_counter_file;
	}
#endif // __PL_BINARY_COUNTER__
	if(
		(pl_counter_file_bytes_read != pl_counter_file_bytes_to_read) &&
		(errno == -1)
	) {
		pl_last_error = errno = PL_COUNTER_READ_FAILED;
		goto pl_read_unlock_counter_file;
	}
pl_read_unlock_counter_file:

	//-------------------------------------------------------------------------
	// Unlock the counter file locked against other processes.
	//-------------------------------------------------------------------------
	pl_lock.l_type = (short)F_UNLCK;
	ret = fcntl(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		F_SETLK, 
		&pl_lock
	);
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	//nop
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__
	//nop
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
	if(ret == -1) {
		pl_last_error = PL_COUNTER_FILE_UNLOCK_FAILED;
	}
#endif // __PL_FILESYSTEM_LESS__
pl_read_unlock_counter:

	//-------------------------------------------------------------------------
	// Unlock the counter in the pl_table locked against other threads.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_post(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#else // __PL_MACOSX__	
	ret = sem_post(
		&pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}
pl_read_return:

	//-------------------------------------------------------------------------
	// Set last error and return status.
	//-------------------------------------------------------------------------
	if(pl_last_error != PL_NO_ERROR) {
		errno = pl_last_error;
		return(PL_FAILURE);
#ifdef __PL_UNIT_TESTS__
	} else {
		pl_last_error = PL_NO_ERROR;
		errno = pl_last_error;
#endif // __PL_UNIT_TESTS__
	}
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Return counter value.
	//-------------------------------------------------------------------------
	(*interface_pointer)->SetLongField(
		interface_pointer, 
		java_counter_value, 
		counter_field_id, 
		(jlong)temp_counter
	);
#endif // __PL_JNI_EXPORTS__
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Timestamp the read counter of the requested PL.
	// Open timestamp is untouched.
	// Last attach timestamp is untouched.
	// Last read timestamp is set.
	// Last write timestamp is untouched.
	// Last close timestamp is untouched.
	//-------------------------------------------------------------------------
	pl_table.pl_array[pld].last_read_time[counter] = time(NULL);
#endif // __PL_TIMESTAMPING__
	return(PL_SUCCESS);
#endif // __PL_BYPASS__ || __PL_LOGGER_ONLY__
}
#endif // __PL_LOGGER_ONLY__

/*-----------------------------------------------------------------------------
@@@@@  @             @    @ @@@@@  @@@@@   @@@@@ @@@@@@
@    @ @             @    @ @    @   @       @   @
@    @ @             @  @ @ @    @   @       @   @
@@@@@  @             @  @ @ @@@@@    @       @   @@@@@@
@      @             @  @ @ @  @     @       @   @
@      @              @ @ @ @   @    @       @   @
@      @@@@@@          @ @  @    @ @@@@@     @   @@@@@@
              @@@@@@
Function: pl_write
Purpose : write a value into a power link counter file
In      : a valid power link descriptor holding the counter
		: pointer to source buffer
		: offset to the counter
Out     : status and last error set if error occurs

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/01/2008    Jamel Tayeb             Creation.
06/04/2010    Jamel Tayeb             Added __PL_FILESYSTEM_LESS__ support.
*/
#ifdef __PL_JNI_EXPORTS__
JNIEXPORT jint JNICALL Java_ProductivityLink_pl_1write(
	JNIEnv *interface_pointer, 
	jobject caller_reference, 
	jint java_pld, 
	jobject java_counter_value, 
	jint java_counter
) {

	jfieldID counter_field_id = NULL;
	jclass counter_class = NULL;
	int pld = PL_INVALID_DESCRIPTOR;
	unsigned long long temp_counter = 0;
	unsigned int counter = 0;
	void *p = NULL;
#else // __PL_JNI_EXPORTS__
PL_API int pl_write(int pld, const void *p, unsigned int counter) {
#endif // __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// If __PL_BYPASS__ is defined, set system's last error code to 
	// PL_BYPASSED and return.
	//-------------------------------------------------------------------------
#ifdef __PL_BYPASS__
	#ifdef __PL_WINDOWS__
		SetLastError(PL_BYPASSED);
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		errno = PL_BYPASSED;
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		return(PL_FAILURE);
#else // __PL_BYPASS__

#ifdef __PL_FILESYSTEM_LESS__
	int one = 1;
	char *message = NULL;
	char pl_input_buffer[PL_MAX_INPUT_BUFFER_SIZE] = { '\0' };
	char pl_output_buffer[PL_MAX_OUTPUT_BUFFER_SIZE] = { '\0' };
	PL_PROTOCOL_STATUS pret = PL_PROTOCOL_FAILURE;
	PL_PROTOCOL_SIZET message_size = 0;
	int connection_attempt_count = 0; 
	#ifdef __PL_WINDOWS__
		ADDRINFO *pa = NULL;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		struct addrinfo *pa = NULL;
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#else // __PL_FILESYSTEM_LESS__
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	int lock_attempt_count = 0; 
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// @    @ @@@@@  @    @ @@@@@   @@@@  @    @  @@@@
	// @    @   @    @@   @ @    @ @    @ @    @ @    @
	// @  @ @   @    @ @  @ @    @ @    @ @  @ @  @@@@
	//  @ @ @   @    @   @@ @    @ @    @  @ @ @      @
	//   @ @  @@@@@  @    @ @@@@@   @@@@    @ @  @@@@@
	//-------------------------------------------------------------------------
	DWORD dw_ret = 0;
	BOOL b_ret = FALSE;
	DWORD pl_last_error = PL_NO_ERROR;
#ifdef __PL_FILESYSTEM_LESS__
	int ret = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;
	DWORD dwret = 0;
#else // __PL_FILESYSTEM_LESS__	
	errno_t et_ret = 0;
	DWORD pl_counter_file_bytes_to_write = 0;
	DWORD pl_counter_file_bytes_written = 0;
#if defined (__PL_BINARY_COUNTER__) || (!__PL_LOGGER_ONLY__)
	char pl_buffer[PL_MAX_BUFFER_SIZE];
#else // __PL_BINARY_COUNTER__ || !__PL_LOGGER_ONLY__
	char pl_buffer[PL_MAX_BUFFER_SIZE + PL_LOGGER_ONLY_MAX_BUFFER_SIZE];
#endif // __PL_BINARY_COUNTER__ || !__PL_LOGGER_ONLY__
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	OVERLAPPED overlapped;
	DWORD bytes_transferred = 0;
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
#ifndef __PL_LOGGER_ONLY__
	LARGE_INTEGER offset;
#else // __PL_LOGGER_ONLY__
	time_t pl_logger_only_time;
#endif // __PL_LOGGER_ONLY__
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Caching counter class and field id.
	//-------------------------------------------------------------------------
	if(counter_field_id == NULL) {
		counter_class = (*interface_pointer)->GetObjectClass(
			interface_pointer, 
			java_counter_value
		);
		if(counter_class == NULL) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_write_return;
		}
		counter_field_id = (*interface_pointer)->GetFieldID(
			interface_pointer, 
			counter_class, 
			"value", 
			"J"
		);
		if(counter_field_id == NULL) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_write_return;
		}
	}

	//-------------------------------------------------------------------------
	// Get the java arguments & initializations.
	//-------------------------------------------------------------------------
	pld = (unsigned int)java_pld;
	counter = (unsigned int)java_counter;
	temp_counter = (unsigned long long)(*interface_pointer)->GetLongField(
		interface_pointer, 
		java_counter_value, 
		counter_field_id
	);
	p = (void *)&temp_counter;
#endif // __PL_JNI_EXPORTS__
	if(pl_table_initialized == FALSE) {
		pl_last_error = PL_DESCRIPTOR_TABLE_UNINITIALIZED;
		goto pl_write_return;
	}

	//-------------------------------------------------------------------------
	// Check calling arguments.
	//-------------------------------------------------------------------------
	if(
		(pld == PL_INVALID_DESCRIPTOR) ||
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || (pld >= PL_MAX_PRODUCTIVITY_LINKS)) ||
#else // __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || ((unsigned int)pld >= pl_max_productivity_links)) ||
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
		(p == NULL) ||
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		((counter < 0) && (counter >= PL_MAX_COUNTERS_PER_LINK)) ||
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		(counter >= pl_table.pl_array[pld].pl_counters_count)
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_write_return;
	}

#ifndef __PL_ATTACH_SCRIPT_SUPPORT__ // no caching when used with scripting tools

	//-------------------------------------------------------------------------
	// Check counter write cache.
	//-------------------------------------------------------------------------
	if(
		pl_table.pl_array[pld].pl_write_cache[counter] == 
		*((unsigned __int64 *)p)
	) {
		// write cache hit
#ifdef __PL_UNIT_TESTS__
		pl_last_error = PL_COUNTER_WRITE_CACHE_HIT;
		SetLastError(pl_last_error);
#endif // __PL_UNIT_TESTS__
		goto pl_write_return_success;
	} else { // write cache miss
#ifdef __PL_UNIT_TESTS__
		pl_last_error = PL_COUNTER_WRITE_CACHE_MISS;
		SetLastError(pl_last_error);
#endif // __PL_UNIT_TESTS__
		pl_table.pl_array[pld].pl_write_cache[counter] = 
			*((unsigned __int64 *)p)
		;
	}
#endif // __PL_ATTACH_SCRIPT_SUPPORT__

#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Lock the counter in the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
	dw_ret = WaitForSingleObject(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter], 
		INFINITE
	);
	if(dw_ret != WAIT_OBJECT_0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_write_return;
	}

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_WRITE command.
	//-------------------------------------------------------------------------
	// pl_write()
	// +-----------+---------+---------+---------+----------+
	// | OPERATION | UUID    | PLD     | OFFSET  | VALUE    |
	// | CODE      |         |         |         |          |
	// +-----------+---------+---------+---------+----------+ <- PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX
	// ^           ^         ^         ^         ^
	// |           |         |         |         |
	// |<--- A --->|<-- B -->|<-- C -->|<-- D -->|<-- E --->
	// |           |(LSB-MSB)|(LSB-MSB)|(LSB-MSB)|(LSB-MSB)
	// |           |         |         |         |
	// |           |         |         |         +--- PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX
	// |           |         |         +------------- PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX
	// |           |         +----------------------- PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX
	// |           +--------------------------------- PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX
	// +--------------------------------------------- PL_PROTOCOL_PL_WRITE_INPUT_OPCODE_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_OPCODE_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//   D = PL_PROTOCOL_COUNTER_OFFSET_SIZE
	//   E = PL_PROTOCOL_ULL_SIZE
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_WRITE_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_WRITE;
	memcpy(
		&message[PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX],
		&pl_table.pl_array[pld].uuid,
		PL_PROTOCOL_UUID_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX],
		&pl_table.pl_array[pld].remote_pld,
		PL_PROTOCOL_PLD_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX],
		&counter,
		PL_PROTOCOL_COUNTER_OFFSET_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX],
		p,
		PL_PROTOCOL_ULL_SIZE
	);
	message[
		PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX
	] = PL_PROTOCOL_EOR;
	bytes_to_send = (
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_UUID_SIZE +
		PL_PROTOCOL_PLD_SIZE +
		PL_PROTOCOL_COUNTER_OFFSET_SIZE +
		PL_PROTOCOL_ULL_SIZE +
		PL_PROTOCOL_EOR_SIZE
	);
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_write_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[pld].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_table.pl_array[pld].pl_counter_sockets[counter] = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(
			pl_table.pl_array[pld].pl_counter_sockets[counter] == 
			INVALID_SOCKET
		) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_write_unlock_counter;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_write_unlock_counter;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = closesocket(
				pl_table.pl_array[pld].pl_counter_sockets[counter]
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_write_unlock_counter;
			}
			continue;
		}
		goto pl_write_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on WSAEADDRINUSE:
	//    If you call pl_write at a too high frequency, you may exhaust the
	//    short lived TCP ports.  The default range of short lived ports is 
	//    from 1025 to 5000. Ways to workaround are to increase the dynamic port 
	//    range (to 65534) by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\MaxUserPort;
	//    or by reducing TIME_WAIT from the default 240s (4 minutes) to 30s
	//    by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\TCPTimedWaitDelay
	//-------------------------------------------------------------------------
	dwret = GetLastError();
	if(dwret == WSAEADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_write_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_write_unlock_counter;

pl_write_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_WRITE command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_write_unlock_counter;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer
	//-------------------------------------------------------------------------
	// pl_write() return
	// +----------+
	// | STATUS   |
	// | CODE     |
	// +----------+ <--- PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX
	// ^
	// |
	// |<-- A --->
	// |
	// +--------------------------- PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	ZeroMemory(
		&pl_input_buffer, 
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_write_unlock_counter;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (size_t)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_write_unlock_counter;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_write_unlock_counter;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close PL socket.
	//-------------------------------------------------------------------------
	ret = closesocket(
		pl_table.pl_array[pld].pl_counter_sockets[counter]
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_write_unlock_counter;
	}
	pl_table.pl_array[pld].pl_counter_sockets[counter] = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_write_unlock_counter;
	}	

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_write_unlock_counter;
	}
#else // __PL_FILESYSTEM_LESS__
#ifdef __PL_BINARY_COUNTER__
	pl_counter_file_bytes_to_write = (DWORD)sizeof(ULONGLONG);
#else //  __PL_BINARY_COUNTER__

	//-------------------------------------------------------------------------
	// Convert counter data into string.
	//-------------------------------------------------------------------------
	ZeroMemory(
		pl_buffer, 
		sizeof(pl_buffer)
	);
	et_ret = _ui64toa_s(
		*((unsigned __int64 *)p), 
		pl_buffer, 
		PL_MAX_BUFFER_SIZE, 
		PL_COUNTER_BASE
	);
	if(et_ret != 0) {
		if(et_ret == EINVAL) {
			pl_last_error = PL_COUNTER_VALUE_OUT_OF_RANGE;
			goto pl_write_return;
		}
		pl_last_error = PL_COUNTER_TO_STRING_FAILED;
		goto pl_write_return;
	}
	pl_counter_file_bytes_to_write = (DWORD)strlen(pl_buffer);
#ifndef __PL_LOGGER_ONLY__
	pl_buffer[pl_counter_file_bytes_to_write + 1] = PL_EOF;
	pl_counter_file_bytes_to_write += 2;
#else // __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// Add time stamp to log entry (with ascii counters only).
	//-------------------------------------------------------------------------
	pl_buffer[pl_counter_file_bytes_to_write] = PL_LOGGER_ONLY_SEPARATOR;
	pl_counter_file_bytes_to_write += 1;
	time(&pl_logger_only_time);
	ctime_s(
		&pl_buffer[pl_counter_file_bytes_to_write], 
		PL_LOGGER_ONLY_MAX_BUFFER_SIZE, 
		&pl_logger_only_time
	);
	pl_counter_file_bytes_to_write += PL_LOGGER_ONLY_MAX_BUFFER_SIZE - 1;
#endif // __PL_LOGGER_ONLY__
#endif // __PL_BINARY_COUNTER__

	//-------------------------------------------------------------------------
	// Lock the counter in the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
	dw_ret = WaitForSingleObject(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter], 
		INFINITE
	);
	if(dw_ret != WAIT_OBJECT_0) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_write_return;
	}

	//-------------------------------------------------------------------------
	// Lock the counter file against other processes.
	//-------------------------------------------------------------------------
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	overlapped.hEvent = 0;
	overlapped.Offset = 0;
	overlapped.OffsetHigh = 0;
pl_write_try_lock:
	b_ret = LockFileEx(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		LOCKFILE_EXCLUSIVE_LOCK, 
		0, 
		pl_counter_file_bytes_to_write, 
		0, 
		&overlapped
	);
	if(b_ret == FALSE) {
		if(lock_attempt_count++ < PL_MAX_COUNTER_FILE_LOCK_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_write_try_lock; 
		} else {
			pl_last_error = PL_COUNTER_FILE_LOCK_FAILED;
			goto pl_write_unlock_counter;
		}
	}
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__

	//-------------------------------------------------------------------------
	// In non-blocking mode, if we cannot lock the counter file, then we signal
	// it with PL_COUNTER_FILE_ALREADY_LOCKED last error and returning error 
	// status.  The caller can ignore it and continue processing.
	//-------------------------------------------------------------------------
	b_ret = LockFile(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		0, 
		pl_counter_file_bytes_to_write, 
		0, 
		0
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_FILE_ALREADY_LOCKED;
		goto pl_write_unlock_counter;
	}
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
#ifndef __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// Point to the counter file head.
	//-------------------------------------------------------------------------
	offset.QuadPart = 0;
	b_ret = SetFilePointerEx(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		offset, 
		NULL, 
		FILE_BEGIN
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_FILE_RESET_FILE_POINTER_FAILED;
		goto pl_write_unlock_counter_file;
	}
#endif // __PL_LOGGER_ONLY__
	
	//-------------------------------------------------------------------------
	// Write the counter data (ascii or binary).
	//-------------------------------------------------------------------------
#ifdef __PL_BINARY_COUNTER__
	b_ret = WriteFile(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		p, 
		pl_counter_file_bytes_to_write, 
		&pl_counter_file_bytes_written, 
		NULL
	);
#else // __PL_BINARY_COUNTER__
	b_ret = WriteFile(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		pl_buffer, 
		pl_counter_file_bytes_to_write, 
		&pl_counter_file_bytes_written, 
		NULL
	);
#endif // __PL_BINARY_COUNTER__
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_WRITE_FAILED;
		goto pl_write_unlock_counter_file;
	}
pl_write_unlock_counter_file:

	//-------------------------------------------------------------------------
	// Unlock the counter file locked against other processes.
	//-------------------------------------------------------------------------
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	b_ret = UnlockFileEx(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		0, 
		pl_counter_file_bytes_to_write, 
		0, 
		&overlapped
	);
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__
	b_ret = UnlockFile(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		0, 
		pl_counter_file_bytes_to_write, 
		0, 
		0
	);
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
	if(b_ret == FALSE) {
		pl_last_error = PL_COUNTER_FILE_UNLOCK_FAILED;
	}
#endif // __PL_FILESYSTEM_LESS__

pl_write_unlock_counter:

	//-------------------------------------------------------------------------
	// Unlock the counter in the pl_table locked against other threads.
	//-------------------------------------------------------------------------
	b_ret = ReleaseSemaphore(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter], 
		(LONG)1, 
		NULL
	);
	if(b_ret == FALSE) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}

pl_write_return:

	//-------------------------------------------------------------------------
	// Set last error code and return status.
	//-------------------------------------------------------------------------
#ifdef __PL_UNIT_TESTS__
	if(
		(pl_last_error != PL_NO_ERROR) && 
		(pl_last_error != PL_COUNTER_WRITE_CACHE_HIT) &&
		(pl_last_error != PL_COUNTER_WRITE_CACHE_MISS)
	) {
		SetLastError(pl_last_error);
		return(PL_FAILURE);
	} else {
		pl_last_error = pl_last_error;
		SetLastError(pl_last_error);
	}
#else // ! __PL_UNIT_TESTS__
	if(pl_last_error != PL_NO_ERROR) {
		SetLastError(pl_last_error);
		return(PL_FAILURE);
	}
#endif // __PL_UNIT_TESTS__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  

	//-------------------------------------------------------------------------
	//   @    @    @ @@@@@  @   @
	// @ @ @  @@   @   @     @ @
	//  @@@   @ @  @   @      @
	// @ @ @  @   @@   @     @ @
	//   @    @    @ @@@@@  @   @
	//-------------------------------------------------------------------------
	int ret = 0;
	int pl_last_error = PL_NO_ERROR;
#ifdef __PL_FILESYSTEM_LESS__
	int index = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;
#else // __PL_FILESYSTEM_LESS__
	size_t pl_counter_file_bytes_to_write = 0;
	size_t pl_counter_file_bytes_written = 0;
	struct flock pl_lock;
#if defined (__PL_BINARY_COUNTER__) || (! __PL_LOGGER_ONLY__)
	off_t ot_ret = (off_t)0;
	char pl_buffer[PL_MAX_BUFFER_SIZE];
#else // __PL_BINARY_COUNTER__ || ! __PL_LOGGER_ONLY__
	time_t pl_logger_only_time;
	char pl_buffer[PL_MAX_BUFFER_SIZE + PL_LOGGER_ONLY_MAX_BUFFER_SIZE];
#endif // __PL_BINARY_COUNTER__ || ! __PL_LOGGER_ONLY__
#endif // __PL_FILESYSTEM_LESS__
#ifdef __PL_JNI_EXPORTS__

	//-------------------------------------------------------------------------
	// Caching counter class and field id.
	//-------------------------------------------------------------------------
	if(counter_field_id == NULL) {
		counter_class = (*interface_pointer)->GetObjectClass(
			interface_pointer, 
			java_counter_value
		);
		if(counter_class == NULL) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_write_return;
		}
		counter_field_id = (*interface_pointer)->GetFieldID(
			interface_pointer, 
			counter_class, 
			"value", 
			"J"
		);
		if(counter_field_id == NULL) {
			pl_last_error = PL_INVALID_PARAMETERS;
			goto pl_write_return;
		}
	}

	//-------------------------------------------------------------------------
	// Get the java arguments & initializations
	//-------------------------------------------------------------------------
	pld = (unsigned int)java_pld;
	counter = (unsigned int)java_counter;
	temp_counter = (unsigned long long)(*interface_pointer)->GetLongField(
		interface_pointer, 
		java_counter_value, 
		counter_field_id
	);
	p = (void *)&temp_counter;
#endif // __PL_JNI_EXPORTS__
	if(pl_table_initialized == 0) {
		pl_last_error = PL_DESCRIPTOR_TABLE_UNINITIALIZED;
		goto pl_write_return;
	}

	//-------------------------------------------------------------------------
	// Check calling arguments.
	//-------------------------------------------------------------------------
	if(
		(pld == PL_INVALID_DESCRIPTOR) ||
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || (pld >= PL_MAX_PRODUCTIVITY_LINKS)) ||
#else // __PL_DYNAMIC_TABLE_ALLOCATION__
		((pld < 0) || ((unsigned int)pld >= pl_max_productivity_links)) ||
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
		(p == NULL) ||
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		(counter > PL_MAX_COUNTERS_PER_LINK) ||
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		(counter >= pl_table.pl_array[pld].pl_counters_count)
	) {
		pl_last_error = PL_INVALID_PARAMETERS;
		goto pl_write_return;
	}

#ifndef __PL_ATTACH_SCRIPT_SUPPORT__ // no caching when used with scripting tools

	//-------------------------------------------------------------------------
	// Check counter write cache.
	//-------------------------------------------------------------------------
	if(
		pl_table.pl_array[pld].pl_write_cache[counter] == 
		*((unsigned long long *)p)
	) {
		// write cache hit
#ifdef __PL_UNIT_TESTS__
		pl_last_error = PL_COUNTER_WRITE_CACHE_HIT;
		errno = pl_last_error;
#endif // __PL_UNIT_TESTS__
		goto pl_write_return_success;
	} else { // write cache miss
#ifdef __PL_UNIT_TESTS__
		pl_last_error = PL_COUNTER_WRITE_CACHE_MISS;
		errno = pl_last_error;
#endif // __PL_UNIT_TESTS__
		pl_table.pl_array[pld].pl_write_cache[counter] = 
			*((unsigned long long *)p)
		;
	}
#endif // __PL_ATTACH_SCRIPT_SUPPORT__

#ifdef __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Lock the counter in the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_wait(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#else // __PL_MACOSX__	
	ret = sem_wait(
		&pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_write_return;
	}

	//-------------------------------------------------------------------------
	// Build the PL_PROTOCOL_OPCODE_WRITE command.
	//-------------------------------------------------------------------------
	// pl_write()
	// +-----------+---------+---------+---------+----------+
	// | OPERATION | UUID    | PLD     | OFFSET  | VALUE    |
	// | CODE      |         |         |         |          |
	// +-----------+---------+---------+---------+----------+ <- PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX
	// ^           ^         ^         ^         ^
	// |           |         |         |         |
	// |<--- A --->|<-- B -->|<-- C -->|<-- D -->|<-- E --->
	// |           |(LSB-MSB)|(LSB-MSB)|(LSB-MSB)|(LSB-MSB)
	// |           |         |         |         |
	// |           |         |         |         +--- PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX
	// |           |         |         +------------- PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX
	// |           |         +----------------------- PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX
	// |           +--------------------------------- PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX
	// +--------------------------------------------- PL_PROTOCOL_PL_WRITE_INPUT_OPCODE_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_OPCODE_SIZE
	//   B = PL_PROTOCOL_UUID_SIZE
	//   C = PL_PROTOCOL_PLD_SIZE
	//   D = PL_PROTOCOL_COUNTER_OFFSET_SIZE
	//   E = PL_PROTOCOL_ULL_SIZE
	//-------------------------------------------------------------------------
	message = pl_output_buffer;
	memset(
		message,
		0,
		sizeof(pl_output_buffer)
	);
	message[
		PL_PROTOCOL_PL_WRITE_INPUT_OPCODE_INDEX
	] = PL_PROTOCOL_OPCODE_WRITE;
	memcpy(
		&message[PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX],
		&pl_table.pl_array[pld].uuid,
		PL_PROTOCOL_UUID_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX],
		&pl_table.pl_array[pld].remote_pld,
		PL_PROTOCOL_PLD_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX],
		&counter,
		PL_PROTOCOL_COUNTER_OFFSET_SIZE
	);
	memcpy(
		&message[PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX],
		p,
		PL_PROTOCOL_ULL_SIZE
	);
	message[
		PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX
	] = PL_PROTOCOL_EOR;
	bytes_to_send = (
		PL_PROTOCOL_OPCODE_SIZE +
		PL_PROTOCOL_UUID_SIZE +
		PL_PROTOCOL_PLD_SIZE +
		PL_PROTOCOL_COUNTER_OFFSET_SIZE +
		PL_PROTOCOL_ULL_SIZE +
		PL_PROTOCOL_EOR_SIZE
	);
	message_size = (PL_PROTOCOL_SIZET)bytes_to_send;
	memcpy(
		&message[PL_PROTOCOL_BYTES_INDEX],
		&message_size,
		PL_PROTOCOL_SIZET_SIZE
	);
	bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

pl_write_try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)pl_table.pl_array[index].address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		pl_table.pl_array[pld].pl_counter_sockets[counter] = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		if(
			pl_table.pl_array[pld].pl_counter_sockets[counter] == 
			INVALID_SOCKET
		) { 
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_write_unlock_counter;
		}

		//---------------------------------------------------------------------
		// De-activate Nagle algorithm.
		//---------------------------------------------------------------------
		ret = setsockopt(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			IPPROTO_TCP, 
			TCP_NODELAY, 
			(char *)&one, 
			sizeof(one)
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SOCKET_FAILED;
			goto pl_write_unlock_counter;
		}

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = close(
				pl_table.pl_array[pld].pl_counter_sockets[counter]
			);
			if(ret == SOCKET_ERROR) { 
				pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
				goto pl_write_unlock_counter;
			}
			continue;
		}
		goto pl_attach_connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on EADDRINUSE:
	//    Address already in use.  This error occurs if an application attempts
	//    to bind to a socket that has already been used for an existing socket,
	//    or a socket that wasn't closed properly, or one that is still in the
	//    process of closing.
	//-------------------------------------------------------------------------
	if(errno == EADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_write_try_connect;
		}
	}
	pl_last_error = PL_FILESYSTEM_LESS_CONNECTION_FAILED;
	goto pl_write_unlock_counter;

pl_attach_connected:

	//-------------------------------------------------------------------------
	// Sending PL_PROTOCOL_OPCODE_WRITE command to the agent.
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	total_bytes_to_send = bytes_to_send;
	do {
		ret = send(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_output_buffer[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_SEND_FAILED;
			goto pl_write_unlock_counter;
		}
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer
	//-------------------------------------------------------------------------
	// pl_write() return
	// +----------+
	// | STATUS   |
	// | CODE     |
	// +----------+ <--- PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX
	// ^
	// |
	// |<-- A --->
	// |
	// +--------------------------- PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX
	//
	// Note:
	//   A = PL_PROTOCOL_STATUS_SIZE
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	memset(
		&pl_input_buffer, 
		0,
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_write_unlock_counter;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);
	memcpy(
		&message_size,
		&pl_input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (size_t)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_write_unlock_counter;
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			pl_table.pl_array[pld].pl_counter_sockets[counter],
			&pl_input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		if(ret == SOCKET_ERROR) {
			pl_last_error = PL_FILESYSTEM_LESS_RECV_FAILED;
			goto pl_write_unlock_counter;
		}
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close counter socket.
	//-------------------------------------------------------------------------
	ret = close(
		pl_table.pl_array[pld].pl_counter_sockets[counter]
	);
	if(ret == SOCKET_ERROR) { 
		pl_last_error = PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED;
		goto pl_write_unlock_counter;
	}
	pl_table.pl_array[pld].pl_counter_sockets[counter] = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Check for PL_PROTOCOL_EOR.
	//-------------------------------------------------------------------------
	if(
		pl_input_buffer[PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX] != 
		PL_PROTOCOL_EOR
	) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_write_unlock_counter;
	}

	//-------------------------------------------------------------------------
	// Check PL_PROTOCOL_STATUS.
	//-------------------------------------------------------------------------
	memcpy(
		&pret,
		&pl_input_buffer[PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX], 
		PL_PROTOCOL_STATUS_SIZE
	);
	if(pret != PL_PROTOCOL_SUCCESS) {
		pl_last_error = PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE;
		goto pl_write_unlock_counter;
	}
#else // __PL_FILESYSTEM_LESS__
#ifdef __PL_BINARY_COUNTER__
	pl_counter_file_bytes_to_write = sizeof(unsigned long long);
#else //  __PL_BINARY_COUNTER__

	//-------------------------------------------------------------------------
	// Convert counter data into string.
	//-------------------------------------------------------------------------
	memset(
		pl_buffer, 
		0, 
		sizeof(pl_buffer)
	);
	ret = sprintf(
		pl_buffer, 
		"%llu", 
		*((unsigned long long *)p)
	); 	
	if(ret < 0) {
		pl_last_error = PL_COUNTER_TO_STRING_FAILED;
		goto pl_write_return;
	}
	pl_counter_file_bytes_to_write = strlen(pl_buffer);
#ifndef __PL_LOGGER_ONLY__
	pl_buffer[pl_counter_file_bytes_to_write + 1] = PL_EOF;
	pl_counter_file_bytes_to_write += 2;
#else // __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// Add time stamp to log entry (with ascii counters only).
	//-------------------------------------------------------------------------
	pl_buffer[pl_counter_file_bytes_to_write] = PL_LOGGER_ONLY_SEPARATOR;
	pl_counter_file_bytes_to_write += 1;
	time(&pl_logger_only_time);
	ctime_r(
		&pl_logger_only_time, 
		&pl_buffer[pl_counter_file_bytes_to_write]
	);
	pl_counter_file_bytes_to_write += PL_LOGGER_ONLY_MAX_BUFFER_SIZE - 1;
#endif // __PL_LOGGER_ONLY__
#endif // __PL_BINARY_COUNTER__

	//-------------------------------------------------------------------------
	// Lock the counter in the pl_table against other threads. blocking wait.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_wait(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#else // __PL_MACOSX__	
	ret = sem_wait(
		&pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
		goto pl_write_return;
	}

	//-------------------------------------------------------------------------
	// Lock the counter file against other processes.
	//-------------------------------------------------------------------------
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	pl_lock.l_type = (short)F_WRLCK;
	pl_lock.l_whence = (short)SEEK_SET;
	pl_lock.l_start = (off_t)0;
	pl_lock.l_len = (off_t)pl_counter_file_bytes_to_write;
	pl_lock.l_pid = getpid();
pl_write_try_lock:
	ret = fcntl(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		F_SETLK, 
		&pl_lock
	);
	if(ret == -1) {
		if(errno == EAGAIN) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_write_try_lock;
		}
		if(lock_attempt_count++ < PL_MAX_COUNTER_FILE_LOCK_ATTEMPTS) { 
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto pl_write_try_lock;
		} else {
			pl_last_error = PL_COUNTER_FILE_LOCK_FAILED;
			goto pl_write_unlock_counter;
		}
	}
#else // __PL_BLOCKING_COUNTER_FILE_LOCK__
	// nop
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
#ifndef __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// Point to the counter file head.
	//-------------------------------------------------------------------------
	ot_ret = lseek(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		(off_t)0, 
		SEEK_SET
	);
	if(ot_ret == (off_t)-1) {
		pl_last_error = PL_COUNTER_FILE_RESET_FILE_POINTER_FAILED;
		goto pl_write_unlock_counter_file;
	}
#endif // __PL_LOGGER_ONLY__

	//-------------------------------------------------------------------------
	// Write the counter data (ascii or binary).
	//-------------------------------------------------------------------------
#ifdef __PL_BINARY_COUNTER__
	pl_counter_file_bytes_written = write(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		p, 
		pl_counter_file_bytes_to_write
	);
#else // __PL_BINARY_COUNTER__
	pl_counter_file_bytes_written = write(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		pl_buffer, 
		pl_counter_file_bytes_to_write
	);
#endif // __PL_BINARY_COUNTER__
	if(pl_counter_file_bytes_written != pl_counter_file_bytes_to_write) {
		pl_last_error = errno = PL_COUNTER_WRITE_FAILED;
		goto pl_write_unlock_counter_file;
	}
pl_write_unlock_counter_file:

	//-------------------------------------------------------------------------
	// Unlock the counter file locked against other processes.
	//-------------------------------------------------------------------------
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	pl_lock.l_type = (short)F_UNLCK;
	ret = fcntl(
		pl_table.pl_array[pld].pl_counter_handles[counter], 
		F_SETLK, 
		&pl_lock
	);
	//nop
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
	if(ret == -1) {
		pl_last_error = PL_COUNTER_FILE_UNLOCK_FAILED;
	}
#endif // __PL_FILESYSTEM_LESS__
pl_write_unlock_counter:

	//-------------------------------------------------------------------------
	// Unlock the counter in the pl_table locked against other threads.
	//-------------------------------------------------------------------------
#ifdef __PL_MACOSX__
	ret = sem_post(
		pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#else // __PL_MACOSX__	
	ret = sem_post(
		&pl_table.pl_array[pld].pl_counter_handles_semaphores[counter]
	);
#endif // __PL_MACOSX__	
	if(ret == -1) {
		pl_last_error = PL_SYNCHRONIZATION_FAILED;
	}
pl_write_return:

	//-------------------------------------------------------------------------
	// Set last error and return status.
	//-------------------------------------------------------------------------
#ifdef __PL_UNIT_TESTS__
	if(
		(pl_last_error != PL_NO_ERROR) && 
		(pl_last_error != PL_COUNTER_WRITE_CACHE_HIT) &&
		(pl_last_error != PL_COUNTER_WRITE_CACHE_MISS)
	) {
		errno = pl_last_error;
		return(PL_FAILURE);
	} else {
		pl_last_error = pl_last_error;
		errno = pl_last_error;
	}
#else // ! __PL_UNIT_TESTS__
	if(pl_last_error != PL_NO_ERROR) {
		errno = pl_last_error;
		return(PL_FAILURE);
	}
#endif // __PL_UNIT_TESTS__
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifndef __PL_ATTACH_SCRIPT_SUPPORT__
// jump-point on write cahe hit
pl_write_return_success:
#endif // __PL_ATTACH_SCRIPT_SUPPORT__
#ifdef __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Timestamp the written counter of the requested PL.
	// Open timestamp is untouched.
	// Last attach timestamp is untouched.
	// Last read timestamp is untouched.
	// Last write timestamp is set.
	// Last close timestamp is untouched.
	//-------------------------------------------------------------------------
	pl_table.pl_array[pld].last_write_time[counter] = time(NULL);
#endif // __PL_TIMESTAMPING__
	return(PL_SUCCESS);
#endif // __PL_BYPASS__
}
