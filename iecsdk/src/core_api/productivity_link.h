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

#ifndef __INCLUDE_PRODUCTIVITY_LINK__
#define __INCLUDE_PRODUCTIVITY_LINK__

/*
+-------------------------------------------+---------------------------------+
| Symbol                                    | Role                            |
+-------------------------------------------+---------------------------------+
| _DEBUG                                    | Generic build configuration     |
| _RELEASE                                  |                                 |
| _CONSOLE                                  |                                 |
| _UNICODE                                  |                                 |
| UNICODE                                   |                                 |
| _ATL_STATIC_REGISTRY                      |                                 |
| __PL_LITTLE_ENDIAN__                      |                                 |
| __PL_DYNAMIC_COUNTERS_ALLOCATION__        |                                 |
| __PL_BLOCKING_PL_READ__                   |                                 |
| __PL_FILESYSTEM_LESS__                    |                                 |
| __PL_IN_MEMORY__                          |                                 |
| __PL_AGENT__                              |                                 |
| __PL_EXTRA_INPUT_CHECKS__                 |                                 |
+-------------------------------------------+---------------------------------+
| __PL_WINDOWS__                            | OS build configuration          |
| __PL_LINUX__ (use for MeeGo too)          |                                 |
| __PL_SOLARIS__                            |                                 |
| __PL_MACOSX__                             |                                 |
| __PL_IOS__                                |                                 |
+-------------------------------------------+---------------------------------+
| _WINDLL                                   | Dynamic library build           |
| _USRDLL                                   | configuration                   |
| __PL_WINDOWS_DLL_EXPORTS__                |                                 |
| __PL_LINUX_SO_EXPORTS__                   |                                 |
| __PL_SOLARIS_SO_EXPORTS__                 |                                 |
| __PL_MACOSX_SO_EXPORTS__                  |                                 |
| __PL_IOS_SO_EXPORTS__                     |                                 |
| __PL_JNI_EXPORTS__                        |                                 |
+-------------------------------------------+---------------------------------+
| __PL_BYPASS__                             | PL functional build             |
| __PL_GENERATE_INI__                       | configuration                   |
| __PL_GENERATE_INI_VERSION_TAGGING__       |                                 |
| __PL_GENERATE_INI_BUILD_TAGGING__         |                                 |
| __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__ |                                 |
| __PL_BLOCKING_COUNTER_FILE_LOCK__         |                                 |
| __PL_ATTACH_SCRIPT_SUPPORT__              |                                 |
| __PL_UNDEF_T__                            |                                 |
| __PL_TIMESTAMPING__                       |                                 |
+-------------------------------------------+---------------------------------+
| __PL_CONSTANT_UUID__                      | PL configuration reporting (use |
| __PL_BINARY_COUNTER__                     | of forbidden mode in customer   |
| __PL_DYNAMIC_TABLE_ALLOCATION__           | available software is not       |
| __PL_AGENT__                              | allowed) - except __PL_AGENT__  |
| __PL_UNIT_TESTS__                         |                                 |
| __PL_LOGGER_ONLY__                        |                                 |
+-------------------------------------------+---------------------------------+
| __PL_NO_SSE_PAUSE_SUPPORT__               | Architecture specific build     |
|                                           | configuration                   |
+-------------------------------------------+---------------------------------+
*/

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#ifdef __PL_FILESYSTEM_LESS__

	 	//---------------------------------------------------------------------
		// Note: 
		//    To solve the winsock2.h / winsock.h / windows.h header problem, 
		//    we define at project-level the _WINSOCKAPI_ symbol.  This is 
		//    preventing windows.h to include windows.h and therefore come up 
		//    with the re-defintion compiler error messages.
		//    This also generates symbol re-definition warning on _WINSOCKAPI_.
		//    To silent it, we use the push, pop and disable warning pragma. 
		//---------------------------------------------------------------------
		#pragma warning(push)
		#pragma warning(disable:4005)
			#include <winsock2.h>
			#include <ws2tcpip.h>
			#include <windows.h>
		#pragma warning(pop) 
		#pragma comment(lib, "WS2_32.lib")
	#endif // __PL_FILESYSTEM_LESS__
	#include <Rpc.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include <stdio.h>
	#include <stdlib.h>
	#include <semaphore.h>
	#include <uuid/uuid.h>
	#ifdef __PL_LOGGER_ONLY__
		extern char *ctime_r(const time_t *, char *);
	#endif // __PL_LOGGER_ONLY__
	#ifdef __PL_BLOCKING_PL_READ__
		#ifdef __PL_LINUX__
			#include <sys/inotify.h>
		#endif // __PL_LINUX__
		#ifdef __PL_MACOSX__
			#include <CoreServices/CoreServices.h>
			#include <FSEvents.h>
//			#include <sys/event.h>
		#endif // __PL_MACOSX__
		#ifdef __PL_SOLARIS__
//			#include <aio.h>
			#include <port.h>
		#endif // __PL_SOLARIS__
	#endif // __PL_BLOCKING_PL_READ__
	#ifdef __PL_FILESYSTEM_LESS__
		#include <stdio.h>
		#include <sys/types.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <sys/socket.h>
		#include <netdb.h>
	#endif // __PL_FILESYSTEM_LESS__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#if defined (__PL_TIMESTAMPING__) || (__PL_GENERATE_INI_DATE_AND_TIME_TAGGING__)
	#include <time.h>
#endif // __PL_TIMESTAMPING__ || __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
#ifdef __PL_JNI_EXPORTS__
	#include <jni.h>
#endif // __PL_JNI_EXPORTS__

//-----------------------------------------------------------------------------
// Version defines.
//-----------------------------------------------------------------------------
#define PL_VERSION_MAJOR "2010" // year
#define PL_VERSION_MINOR "12" // month
#define PL_VERSION_REVISION "15" // day
#ifdef __PL_WINDOWS__
	#define PL_VERSION_OS "W"
#endif // __PL_WINDOWS__
#ifdef __PL_LINUX__
	#define PL_VERSION_OS "L"
#endif // __PL_LINUX__
#ifdef __PL_SOLARIS__
	#define PL_VERSION_OS "S"
#endif // __PL_SOLARIS__
#ifdef __PL_MACOSX__
	#ifdef __PL_IOS__
		#define PL_VERSION_OS "I"
	#else // __PL_IOS__
		#define PL_VERSION_OS "M"
	#endif // __PL_IOS__
#endif // __PL_MACOSX__
#ifdef __PL_GENERATE_INI_VERSION_TAGGING__
	#define PL_VERSION_TAG_SEPARATOR "."
	#define PL_VERSION_TAG_OPEN "("
	#define PL_VERSION_TAG_CLOSE ")"
	#ifdef __PL_WINDOWS__
		#define PL_VERSION_TAG PL_VERSION_MAJOR \
			## "." ## \
			PL_VERSION_MINOR ## "." ## \
			PL_VERSION_REVISION ## "." ## "(" ## \
			PL_VERSION_OS ## ")"
	#endif // __PL_WINDOWS__
#endif // __PL_GENERATE_INI_VERSION_TAGGING__
#ifdef __PL_GENERATE_INI_BUILD_TAGGING__

	//-------------------------------------------------------------------------
	// Tagging strings and indexes.
	//-------------------------------------------------------------------------
	#define PL_BUILD_TAGS \
		"_DEBUG", \
		"_RELEASE", \
		"_CONSOLE", \
		"_UNICODE", \
		"UNICODE", \
		"_ATL_STATIC_REGISTRY", \
		"__PL_LITTLE_ENDIAN__", \
		"__PL_DYNAMIC_TABLE_ALLOCATION__ (*FORBIDDEN* in customer available software)", \
		"__PL_DYNAMIC_TABLE_ALLOCATION__ (__PL_AGENT__)", \
		"__PL_DYNAMIC_COUNTERS_ALLOCATION__", \
		"__PL_WINDOWS__", \
		"__PL_LINUX__", \
		"__PL_SOLARIS__", \
		"__PL_MACOSX__", \
		"__PL_IOS__", \
		"_WINDLL", \
		"_USRDLL", \
		"__PL_WINDOWS_DLL_EXPORTS__", \
		"__PL_LINUX_SO_EXPORTS__", \
		"__PL_SOLARIS_SO_EXPORTS__", \
		"__PL_MACOSX_SO_EXPORTS__", \
		"__PL_JNI_EXPORTS__", \
		"__PL_BYPASS__", \
		"__PL_GENERATE_INI__", \
		"__PL_GENERATE_INI_VERSION_TAGGING__", \
		"__PL_GENERATE_INI_BUILD_TAGGING__", \
		"__PL_BLOCKING_COUNTER_FILE_LOCK__", \
		"__PL_BINARY_COUNTER__ (*FORBIDDEN* in customer available software)", \
		"__PL_ATTACH_SCRIPT_SUPPORT__", \
		"__PL_UNDEF_T__", \
		"__PL_TIMESTAMPING__", \
		"__PL_UNIT_TESTS__ (*FORBIDDEN* in customer available software)", \
		"__PL_LOGGER_ONLY__ (*FORBIDDEN* in customer available software)", \
		"__PL_BLOCKING_PL_READ__", \
		"__PL_CONSTANT_UUID__ (*FORBIDDEN* in customer available software)", \
		"__PL_GENERATE_INI_DATE_AND_TIME_TAGGING__", \
		"__PL_NO_SSE_PAUSE_SUPPORT__", \
		"__PL_AGENT__", \
		"__PL_FILESYSTEM_LESS__", \
		"__PL_EXTRA_INPUT_CHECKS__"

	typedef enum _PL_BUILD_TAG_INDEXES {

		DEBUG_INDEX = 0, 
		RELEASE_INDEX, 
		CONSOLE_INDEX, 
		_UNICODE_INDEX, 
		UNICODE_INDEX, 
		ATL_STATIC_REGISTRY_INDEX, 
		PL_LITTLE_ENDIAN_INDEX, 
		PL_DYNAMIC_TABLE_ALLOCATION_INDEX,
		PL_DYNAMIC_TABLE_ALLOCATION_PL_AGENT_INDEX,
		PL_DYNAMIC_COUNTERS_ALLOCATION_INDEX, 
		PL_WINDOWS_INDEX, 
		PL_LINUX_INDEX, 
		PL_SOLARIS_INDEX, 
		PL_MACOSX_INDEX,
		PL_IOS_INDEX,
		WINDLL_INDEX, 
		USRDLL_INDEX,
		PL_WINDOWS_DLL_EXPORTS_INDEX, 
		PL_LINUX_SO_EXPORTS_INDEX, 
		PL_SOLARIS_SO_EXPORTS_INDEX, 
		PL_MACOSX_SO_EXPORTS_INDEX, 
		PL_JNI_EXPORTS_INDEX,
		PL_BYPASS_INDEX, 
		PL_GENERATE_INI_INDEX, 
		PL_GENERATE_INI_VERSION_TAGGING_INDEX, 
		PL_GENERATE_INI_BUILD_TAGGING_INDEX, 
		PL_BLOCKING_COUNTER_FILE_LOCK_INDEX,
		PL_BINARY_COUNTER_INDEX, 
		PL_ATTACH_SCRIPT_SUPPORT_INDEX, 
		PL_UNDEF_T_INDEX, 
		PL_TIMESTAMPING_INDEX, 
		PL_UNIT_TESTS_INDEX, 
		PL_LOGGER_ONLY_INDEX, 
		PL_BLOCKING_PL_READ_INDEX,
		PL_CONSTANT_UUID_INDEX, 
		PL_GENERATE_INI_DATE_AND_TIME_TAGGING_INDEX, 
		PL_NO_SSE_PAUSE_SUPPORT_INDEX,
		PL_AGENT_INDEX,
		PL_FILESYSTEM_LESS_INDEX,
		PL_EXTRA_INPUT_CHECKS_INDEX
	
	} PL_BUILD_TAG_INDEXES;

#endif // __PL_GENERATE_INI_BUILD_TAGGING__

//-----------------------------------------------------------------------------
// PL_API definition.
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#ifdef _USRDLL

		//---------------------------------------------------------------------
		// All files compiled for a DLL must be with __PL_WINDOWS_DLL_EXPORTS__
		// symbol defined.  This symbol should not be defined on any project 
		// that uses this DLL. 
		//---------------------------------------------------------------------
		#ifdef __PL_WINDOWS_DLL_EXPORTS__
			#define PL_API __declspec(dllexport) extern
		#else // __PL_WINDOWS_DLL_EXPORTS__
			#define PL_API __declspec(dllimport) extern
		#endif // __PL_WINDOWS_DLL_EXPORTS__
	#endif // _USRDLL
#endif // __PL_WINDOWS__

#if (!defined(_USRDLL)) && defined(__cplusplus) 
	#define PL_API extern "C"
#endif // (!defined(_USRDLL)) && defined(__cplusplus)
#if (!defined(_USRDLL)) && (!defined(__cplusplus)) 
	#define PL_API extern
#endif // (!defined(_USRDLL)) && (!defined(__cplusplus))

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Constants.
//-----------------------------------------------------------------------------
//0 to 18,446,744,073,709,551,615
#define PL_MAX_COUNTER_VALUE 18446744073709551615ULL
#define PL_MIN_COUNTER_VALUE 0ULL
#define PL_MAX_UNSIGNED_INTEGER_STRING "4294967295"
#define PL_UUID_SIZE sizeof(uuid_t)
#define PL_UUID_MAX_CHARS 36
#define PL_UUID_MAX_NON_DASH_CHARS 32
#ifndef PL_MAX_PATH
	#define PL_MAX_PATH 255
#endif // PL_MAX_PATH

//-----------------------------------------------------------------------------
// Configuration - generic.
//-----------------------------------------------------------------------------
#define PL_MAX_PRODUCTIVITY_LINKS 10
#ifndef __PL_DYNAMIC_COUNTER_ALLOCATION__
	#define PL_MAX_COUNTERS_PER_LINK 512
#endif // __PL_DYNAMIC_COUNTER_ALLOCATION__
#define PL_MAX_BUFFER_SIZE 22
#define PL_COUNTER_NAME_BASE 10
#define PL_COUNTER_BASE 10
#define PL_CR 0x0d
#define PL_LF 0x0a
#define PL_NULL 0x00
#define PL_SOH 0x01
#define PL_EOT 0x04
#define PL_CONFIGURATION_FILE_APPLICATION_NAME_LINE 1
#define PL_CONFIGURATION_FILE_UUID_STRING_LINE 2
#define PL_CONFIGURATION_FILE_LOCATION_LINE 3
#define PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE 4
#ifdef __PL_LOGGER_ONLY__
	#define PL_LOGGER_ONLY_MAX_BUFFER_SIZE 26
	#define PL_LOGGER_ONLY_SEPARATOR ','
#endif // __PL_LOGGER_ONLY__
#ifdef __PL_BLOCKING_COUNTER_FILE_LOCK__
	#define PL_MAX_COUNTER_FILE_LOCK_ATTEMPTS 1024
#endif // __PL_BLOCKING_COUNTER_FILE_LOCK__
#if defined (__PL_FILESYSTEM_LESS__) || defined (__PL_AGENT__)
	#define PL_MAX_CONNECTION_ATTEMPTS 1024
#endif // __PL_FILESYSTEM_LESS__ || __PL_AGENT__
#ifdef __PL_CONSTANT_UUID__
	#define PL_CONSTANT_UUID_STRING "00000000-0000-0000-0000-000000000000"
	#define PL_CONSTANT_UUID_STRING_MAX_CHARS PL_UUID_MAX_CHARS
#endif // __PL_CONSTANT_UUID__
#ifdef __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	#define PL_DATE_AND_TIME_INI_TAGGING_STRING "PL created on "
#endif // __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
#ifdef __PL_EXTRA_INPUT_CHECKS__
	
	#define PL_EXTRA_INPUT_CHECKS_APPLICATION_NAME_ALLOWED_CHARACTERS_COUNT 70
	#define PL_EXTRA_INPUT_CHECKS_APPLICATION_NAME_ALLOWED_CHARACTERS \
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', \
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', \
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', \
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', \
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', \
		'_', '-', '(', ')', '.', ' ', '[', ']'

	#define PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS_COUNT 70
	#define PL_EXTRA_INPUT_CHECKS_COUNTER_NAME_ALLOWED_CHARACTERS \
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', \
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', \
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', \
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', \
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', \
		'_', '-', '(', ')', '.', ' ', '[', ']'

	#define PL_EXTRA_INPUT_CHECKS_UUID_LENGHT_IN_CHARACTERS PL_UUID_MAX_CHARS
	#define PL_EXTRA_INPUT_CHECKS_UUID_DASH_CHARACTER '-'
	#define PL_EXTRA_INPUT_CHECKS_UUID_ALLOWED_CHARACTERS_COUNT 23
	#define PL_EXTRA_INPUT_CHECKS_UUID_ALLOWED_CHARACTERS \
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', \
		'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F', \
		PL_EXTRA_INPUT_CHECKS_UUID_DASH_CHARACTER
	#define PL_EXTRA_INPUT_CHECKS_UUID_BLOCK1_SIZE 8
	#define PL_EXTRA_INPUT_CHECKS_UUID_BLOCK2_SIZE 4
	#define PL_EXTRA_INPUT_CHECKS_UUID_BLOCK3_SIZE 4
	#define PL_EXTRA_INPUT_CHECKS_UUID_BLOCK4_SIZE 4
	#define PL_EXTRA_INPUT_CHECKS_UUID_BLOCK5_SIZE 12

	#define PL_EXTRA_INPUT_CHECKS_COUNTERS_COUNT_ALLOWED_CHARACTERS_COUNT 10
	#define PL_EXTRA_INPUT_CHECKS_COUNTERS_COUNT_ALLOWED_CHARACTERS \
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'

	#ifdef __PL_FILESYSTEM_LESS__
	
		typedef enum _pl_extra_input_checks_ip_v4_address_classes {
			PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_A = 0,
			PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_B,
			PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_C,
			PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_D,
			PL_EXTRA_INPUT_CHECKS_IP_V4_CLASS_E
		} 
			PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_CLASSES, 
			*PPL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_CLASSES
		;
		#define PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_BUFFER_SIZE 4
		#define PL_EXTRA_INPUT_CHECKS_IP_V4_BUFFER_LAST_BYTE \
			(PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_BUFFER_SIZE - 1)
		#define PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DIGITS_IN_ADDRESS_VALUE 3
		#define PL_EXTRA_INPUT_CHECKS_IP_V4_MAX_DOT_CHARACTERS_IN_ADDRESS 3
		#define PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_DOT_CHARACTER '.'
		#define PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS_COUNT 11
		#define PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_ALLOWED_CHARACTERS \
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', \
			PL_EXTRA_INPUT_CHECKS_IP_V4_ADDRESS_DOT_CHARACTER

		//---------------------------------------------------------------------
		// Class A: 000.000.000.000 to 127.255.255.255
		// Class B: 128.000.000.000 to 191.255.255.255
		// Class C: 192.000.000.000 to 223.255.255.255
		// Class D: 224.000.000.000 to 239.255.255.255
		// Class E: 240.000.000.000 to 255.255.255.255
		//---------------------------------------------------------------------
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE1_MAX_VALUE 127
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE2_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE3_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_A_VALUE4_MAX_VALUE 255

		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MIN_VALUE 128
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE1_MAX_VALUE 191
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE2_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE3_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_B_VALUE4_MAX_VALUE 255

		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MIN_VALUE 192
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE1_MAX_VALUE 223
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE2_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE3_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_C_VALUE4_MAX_VALUE 255

		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MIN_VALUE 224
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE1_MAX_VALUE 239
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE2_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE3_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_D_VALUE4_MAX_VALUE 255

		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MIN_VALUE 240
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE1_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE2_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE3_MAX_VALUE 255
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MIN_VALUE 0
		#define PL_EXTRA_INPUT_CHECKS_IPV4_ADDRESS_CLASS_E_VALUE4_MAX_VALUE 255

		#define PL_EXTRA_INPUT_CHECKS_PORT_MAX_BUFFER_SIZE 6
		#define PL_EXTRA_INPUT_CHECKS_PORT_BUFFER_LAST_BYTE \
			(PL_EXTRA_INPUT_CHECKS_PORT_MAX_BUFFER_SIZE - 1)
		#define PL_EXTRA_INPUT_CHECKS_PORT_MAX_DIGITS_IN_PORT_VALUE 5
		#define PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS_COUNT 10
		#define PL_EXTRA_INPUT_CHECKS_PORT_ALLOWED_CHARACTERS \
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
		#define PL_EXTRA_INPUT_CHECKS_PORT_MIN_PORT_VALUE 1
		#define PL_EXTRA_INPUT_CHECKS_PORT_MAX_PORT_VALUE 65535

	#endif // __PL_FILESYSTEM_LESS__
#endif // __PL_EXTRA_INPUT_CHECKS__

//-----------------------------------------------------------------------------
// Configuration - system specific.
//-----------------------------------------------------------------------------
#define PL_STRNCPY_MIN_BYTES 0
#define PL_STRNCAT_MIN_BYTES 1
#ifdef __PL_WINDOWS__
	#define PL_FOLDER_STRING "C:\\productivity_link"
	#define PL_CONFIG_FILE_NAME_STRING "pl_config.ini"
	#define PL_PATH_SEPARATOR_STRING "\\"
	#define PL_PATH_SEPARATOR_CHAR '\\'
	#define PL_APPLICATION_NAME_SEPARATOR_STRING "_"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PL_FOLDER_STRING "/opt/productivity_link"
	#define PL_CONFIG_FILE_NAME_STRING "pl_config.ini"
	#define PL_PATH_SEPARATOR_STRING "/"
	#define PL_PATH_SEPARATOR_CHAR '/'
	#define PL_APPLICATION_NAME_SEPARATOR_STRING "_"
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef __PL_WINDOWS__
	#define PL_END_OF_LINE { PL_CR, PL_LF, PL_NULL }
	#define PL_EOF 0x1a
	#define PL_FOLDER _T("C:\\productivity_link")
	#define PL_ANONYMOUS_APPLICATION_NAME _T("anonymous_application")
	#define PL_INI_ANONYMOUS_APPLICATION_NAME "anonymous_application"
	#define PL_APPLICATION_NAME_SEPARATOR _T("_")
	#define PL_GENERIC_COUNTER_NAME _T("anonymous_counter_")
	#define PL_INI_GENERIC_COUNTER_NAME "anonymous_counter_"
	#ifdef __PL_GENERATE_INI__
		#define PL_CONFIG_FILE_NAME _T("pl_config.ini")
		#define PL_PATH_SEPARATOR _T("\\")
	#endif // __PL_GENERATE_INI__
	#ifdef __PL_BLOCKING_PL_READ__
		#define PL_CONFIG_FILE_NAME_LENGHT 13
	#endif // __PL_BLOCKING_PL_READ__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#ifndef __PL_MACOSX__
		#define PL_END_OF_LINE { PL_LF, PL_CR, PL_NULL }
	#endif // __PL_MACOSX__
	#define PL_EOF '\0'
	#define PL_GENERIC_COUNTER_NAME "anonymous_counter_"
	#define PL_FOLDER "/opt/productivity_link"
	#define PL_ANONYMOUS_APPLICATION_NAME "anonymous_application"
	#define PL_APPLICATION_NAME_SEPARATOR "_"
	#define PL_FOLDER_ACCESS_MODE 0x1ff
	#define PL_COUNTER_FILES_ACCESS_MODE 0x1ff
	#define PL_CONFIG_FILE_ACCESS_MODE 0x1ff
	#ifdef __PL_GENERATE_INI__
		#define PL_CONFIG_FILE_NAME "pl_config.ini"
		#define PL_PATH_SEPARATOR "/"
	#endif // __PL_GENERATE_INI__
	#ifdef __PL_BLOCKING_PL_READ__
		#ifdef __PL_LINUX__
			#define PL_BLOCKING_PL_READ_NOTIFY_EVENT_SIZE \
				(sizeof(struct inotify_event))
			#define PL_BLOCKING_PL_READ_MAX_NOTIFY_EVENTS (1024)
			#define PL_BLOCKING_PL_READ_NOTIFY_BUFFER_SIZE \
			( \
				PL_BLOCKING_PL_READ_MAX_NOTIFY_EVENTS * \
				PL_BLOCKING_PL_READ_NOTIFY_EVENT_SIZE \
			)
		#endif // __PL_LINUX__
		#define PL_CONFIG_FILE_NAME_LENGHT 13
	#endif // __PL_BLOCKING_PL_READ__
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef __PL_MACOSX__
	#define PL_END_OF_LINE { PL_CR, PL_LF, PL_NULL }
	#define PL_SEMAPHORE_ACCESS_MODE 0x01ff // octal 0777
	#define PL_SEMAPHORE_NAME_MAX_LENGTH 13
#endif// __PL_MACOSX__
#ifdef __PL_GENERATE_INI__
	#define PL_INI_APPLICATION_NAME_SEPARATOR "_"
	#define PL_INI_APPLICATION_NAME_SEPARATOR_CHAR '_'
	#define PL_INI_CONFIG_FILE_NAME "pl_config.ini"
	#define PL_INI_WINDOWS_FOLDER "C:\\productivity_link"
	#define PL_INI_WINDOWS_LC_FOLDER "c:\\productivity_link"
	#define PL_INI_NIX_FOLDER "/opt/productivity_link"
	#define PL_INI_WINDOWS_PATH_SEPARATOR "\\"
	#define PL_INI_WINDOWS_PATH_SEPARATOR_CHAR '\\'
	#define PL_INI_NIX_PATH_SEPARATOR "/"
	#define PL_INI_NIX_PATH_SEPARATOR_CHAR '/'
	#ifdef __PL_EXTRA_INPUT_CHECKS__
		#define PL_INI_WINDOWS_PL_FOLDER_ROOT_CHAR 'c'
		#define PL_INI_WINDOWS_PL_FOLDER_ROOT_UPPER_CHAR 'C'
		#define PL_INI_WINDOWS_ROOTLESS_FOLDER ":\\productivity_link"
	#endif // __PL_EXTRA_INPUT_CHECKS__
#endif // __PL_GENERATE_INI__

//-----------------------------------------------------------------------------
// Structures and types.
//-----------------------------------------------------------------------------
typedef enum _PL_STATUS {

	PL_SUCCESS,
	PL_FAILURE

} PL_STATUS, *PPL_STATUS;

typedef enum _PL_FAILURE {

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
	PL_INVALID_DESCRIPTOR = 0x10000000,
	PL_BYPASSED,
	PL_INVALID_PARAMETERS,
	PL_SYNCHRONIZATION_FAILED,
	PL_MISSING_DIRECTORY,
	PL_NOT_A_DIRECTORY,
	PL_DIRECTORY_CREATION_FAILED,
	PL_DIRECTORY_ALREADY_EXISTS,
	PL_PATH_NOT_FOUND,
	PL_DESCRIPTOR_TABLE_FULL,
	PL_DESCRIPTOR_TABLE_UNINITIALIZED,
	PL_NON_GLOBAL_UUID_DESCRIPTOR,
	PL_NON_GLOBAL_UUID_DESCRIPTOR_NO_ADDRESS,
	PL_GLOBAL_UUID_DESCRIPTOR_CREATION_FAILED,
	PL_GLOBAL_UUID_DESCRIPTOR_TO_STRING_FAILED,
	PL_CRITICAL_FAILURE,
	PL_CONFIG_FILE_GENERATION_FAILED,
	PL_CONFIG_FILE_OPENING_FAILED,
	PL_COUNTER_CREATION_FAILED,
	PL_COUNTER_SEMAPHORE_CREATION_FAILED,
	PL_COUNTER_ATTACH_FAILED,
	PL_COUNTER_TO_STRING_FAILED,
	PL_COUNTER_WRITE_FAILED,
	PL_COUNTER_FILE_RESET_FILE_POINTER_FAILED,
	PL_COUNTER_READ_FAILED,
	PL_COUNTER_FILE_LOCK_FAILED,
	PL_COUNTER_FILE_ALREADY_LOCKED,
	PL_COUNTER_FILE_UNLOCK_FAILED,
	PL_COUNTER_VALUE_OUT_OF_RANGE,
	PL_OUT_OF_MEMORY,
	PL_OUT_OF_BUFFER_SPACE,

	PL_BLOCKING_PL_READ_INSTANCE_CREATION_FAILED,
	PL_BLOCKING_PL_READ_INSTANCE_DESTRUCTION_FAILED,
	PL_BLOCKING_PL_READ_HANDLE_CREATION_FAILED,
	PL_BLOCKING_PL_READ_HANDLE_DESTRUCTION_FAILED,
	PL_BLOCKING_PL_READ_HANDLE_RENEWING_FAILED,
	PL_BLOCKING_PL_READ_WAITING_NOTIFICATION_FAILED,
	
	PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE,
	PL_FILESYSTEM_LESS_INITIALIZATION_FAILED,
	PL_FILESYSTEM_LESS_NETWORK_ADDRESS_RESOLUTION_FAILED,
	PL_FILESYSTEM_LESS_SOCKET_FAILED,
	PL_FILESYSTEM_LESS_CLOSE_SOCKET_FAILED,
	PL_FILESYSTEM_LESS_CONNECTION_FAILED,
	PL_FILESYSTEM_LESS_SEND_FAILED,
	PL_FILESYSTEM_LESS_RECV_FAILED,

	PL_FILESYSTEM_LESS_INVALID_IPV4_ADDRESS,
	PL_FILESYSTEM_LESS_INVALID_PORT,
	
	PL_COUNTER_WRITE_CACHE_HIT,
	PL_COUNTER_WRITE_CACHE_MISS,
	
	PL_NO_ERROR
	
} PL_ERROR, *PPL_ERROR;

#if defined (__PL_FILESYSTEM_LESS__) || defined (__PL_AGENT__)

//-----------------------------------------------------------------------------
//
// @@@@@  @             @@@@@  @@@@@   @@@@   @@@@@  @@@@   @@@@   @@@@  @
// @    @ @             @    @ @    @ @    @    @   @    @ @      @    @ @
// @@@@@  @             @@@@@  @@@@@  @    @    @   @    @ @      @    @ @
// @      @             @      @   @  @    @    @   @    @ @    @ @    @ @
// @      @@@@@@        @      @    @  @@@@     @    @@@@   @@@@   @@@@  @@@@@@
//
// Note:
//    PL protocol definitions are protected by __PL_FILESYSTEM_LESS__ and
//    __PL_AGENT__ #ifdef/#endif.
// Note:
//    All sizes in byte.
//    All data transmitted as binary.
//    All data in little-endian.
//
//-----------------------------------------------------------------------------
// <string> encoding
// +-----------+---------+---------+---            ---+-----------+-----------+
// | BYTES (N) | BYTE 0  | BYTE 1  |        ...       | BYTE N-2  | BYTE N-1  | 
// +-----------+---------+---------+---            ---+-----------+-----------+
// |<--- A --->|<-- B -->|<-- B -->|                  |<--- B --->|<--- B --->
// | (LSB-MSB) |         |         |                  |           |
//
// Note:
//    A = PL_PROTOCOL_SIZET_SIZE
//    B = PL_PROTOCOL_CHAR_SIZE
//
//-----------------------------------------------------------------------------
// All messages are built as:
// +-----------+---------+-------+
// | BYTES (N) | MESSAGE |  EOR  | (PL_PROTOCOL_EOR)
// +-----------+---------+-------+
// |<--- A --->|<-- X -->|<- B ->
// | (LSB-MSB) | 
//
// Note:
//    A = PL_PROTOCOL_SIZET_SIZE
//    B : PL_PROTOCOL_EOR_SIZE
// Note:
//    BYTES is the number of bytes, including PL_PROTOCOL_EOR of a message.
// Note:
//    BYTES is the number of bytes, including PL_PROTOCOL_EOR of a message.
//-----------------------------------------------------------------------------
#define PL_PROTOCOL_CHAR char
#define PL_PROTOCOL_PCHAR char *
#define PL_PROTOCOL_PPCHAR char **
#define PL_PROTOCOL_UUIDT uuid_t
#define PL_PROTOCOL_SIZET unsigned int
#define PL_PROTOCOL_INT int
#define PL_PROTOCOL_UINT unsigned int
#define PL_PROTOCOL_ULL unsigned long long
#define PL_PROTOCOL_EOR_SIZE sizeof(PL_PROTOCOL_CHAR)
#define PL_PROTOCOL_OPCODE_SIZE sizeof(PL_PROTOCOL_CHAR)
#define PL_PROTOCOL_STATUS_SIZE sizeof(PL_PROTOCOL_STATUS)
#define PL_PROTOCOL_UUID_SIZE sizeof(PL_PROTOCOL_UUIDT)
#define PL_PROTOCOL_INT_SIZE sizeof(PL_PROTOCOL_INT)
#define PL_PROTOCOL_UINT_SIZE sizeof(PL_PROTOCOL_UINT)
#define PL_PROTOCOL_ULL_SIZE sizeof(PL_PROTOCOL_ULL)
#define PL_PROTOCOL_SIZET_SIZE sizeof(PL_PROTOCOL_UINT)
#define PL_PROTOCOL_CHAR_SIZE sizeof(PL_PROTOCOL_CHAR)
#define PL_PROTOCOL_PCHAR_SIZE sizeof(PL_PROTOCOL_PCHAR)
#define PL_PROTOCOL_PPCHAR_SIZE sizeof(PL_PROTOCOL_PPCHAR)

#define PL_PROTOCOL_COUNTERS_COUNT_SIZE \
	PL_PROTOCOL_UINT_SIZE
#define PL_PROTOCOL_COUNTER_OFFSET_SIZE \
	PL_PROTOCOL_UINT_SIZE
#define PL_PROTOCOL_PLD_SIZE \
	PL_PROTOCOL_INT_SIZE

#define PL_PROTOCOL_BYTES_INDEX 0
#define PL_PROTOCOL_BYTES_OFFSET_INDEX \
	PL_PROTOCOL_SIZET_SIZE
#define PL_PROTOCOL_INPUT_OP_CODE_INDEX \
	PL_PROTOCOL_BYTES_INDEX + \
	PL_PROTOCOL_SIZET_SIZE
#define PL_PROTOCOL_OUTPUT_STATUS_INDEX \
	PL_PROTOCOL_BYTES_INDEX + \
	PL_PROTOCOL_SIZET_SIZE

#define PL_DEFAULT_PL_AGENT_ADDRESS "127.0.0.1"
#define PL_DEFAULT_PL_AGENT_ADDRESS_ENVAR_NAME "PL_AGENT_ADDRESS"
#define PL_DEFAULT_PL_PORT_ENVAR_NAME "PL_AGENT_PL_PORT"
#define PL_DEFAULT_ADMIN_PORT_ENVAR_NAME "PL_AGENT_ADMIN_PORT"
#ifdef __PL_WINDOWS__
	#define PL_DEFAULT_PL_AGENT_PL_PORT "49253"
	#define PL_DEFAULT_PL_AGENT_ADMIN_PORT "49252"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PL_DEFAULT_PL_AGENT_PL_PORT_STRING "49253"
	#define PL_DEFAULT_PL_AGENT_PL_PORT 49253
	#define PL_DEFAULT_PL_AGENT_ADMIN_PORT_STRING "49252"
	#define PL_DEFAULT_PL_AGENT_ADMIN_PORT 49252
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-------------------------------------------------------------------------
// Note:
//    With UINT_MAX	(maximum value for an unsigned int) equal to:
//       +4,294,967,295 -> PL_PROTOCOL_MESSAGE_MAX_SIZE ~1TB
//       +65,535 -> PL_PROTOCOL_MESSAGE_MAX_SIZE ~16MB
//       We use +255 -> ~65KB
//-------------------------------------------------------------------------
#define PL_UINT_MAX 255
#define PL_PROTOCOL_EOR PL_CR
#define PL_PROTOCOL_MAX_LENGTH_STRING_SIZE \
	( \
		PL_PROTOCOL_SIZET_SIZE + \
		( \
			PL_MAX_PATH * \
			PL_PROTOCOL_CHAR_SIZE \
		) \
	)
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__
	#define PL_PROTOCOL_MESSAGE_MAX_SIZE \
		( \
			PL_PROTOCOL_SIZET_SIZE + \
			PL_PROTOCOL_OPCODE_SIZE + \
			PL_PROTOCOL_COUNTERS_COUNT_SIZE + \
			PL_PROTOCOL_MAX_LENGTH_STRING_SIZE + \
			( \
				PL_PROTOCOL_MAX_LENGTH_STRING_SIZE * \
				PL_UINT_MAX \
			) + \
			PL_PROTOCOL_EOR_SIZE \
		)
#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	#define PL_PROTOCOL_MESSAGE_MAX_SIZE \
		PL_PROTOCOL_SIZET_SIZE + \
		PL_PROTOCOL_OPCODE_SIZE + \
		PL_PROTOCOL_COUNTERS_COUNT_SIZE + \
		PL_PROTOCOL_MAX_LENGTH_STRING_SIZE + \
		( \
			PL_PROTOCOL_MAX_LENGTH_STRING_SIZE * \
			PL_MAX_COUNTERS_PER_LINK \
		) + \
		PL_PROTOCOL_EOR_SIZE
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

#define PL_ONE_BYTE 1
#define PL_MAX_NODE_NAME_SIZE 20
#define PL_MAX_PORT_NAME_SIZE 10
#define PL_MAX_OUTPUT_BUFFER_SIZE 4096
#define PL_MAX_INPUT_BUFFER_SIZE 4096
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define SOCKET int
	#define ADDRINFO struct sockaddr_in
	#define INVALID_SOCKET (-1)
	#define SOCKET_ERROR (-1)
	#define SD_BOTH 2
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#define PL_ADDRESS_INFO_HINT_AI_FAMILY AF_INET;
#define PL_ADDRESS_INFO_HINT_AI_SOCKTYPE SOCK_STREAM;
#define PL_ADDRESS_INFO_HINT_AI_PROTOCOL IPPROTO_TCP;
#define PL_ADDRESS_INFO_HINT_AI_FLAGS AI_PASSIVE;

//-----------------------------------------------------------------------------
// pl_open()
// +-----------+-----------+-----------+------------+--     --+---------------+
// | OPERATION | COUNTERS  |  <string> | <string>   |         | <string>      |
// | CODE      | COUNT     | APP NAME  | COUNTER 0  |   ...   | COUNTER (N-1) |
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
//
// pl_open() return
// +----------+-----------+-----------+-------------+
// | STATUS   | UUID      | PLD       | <string>    |
// | CODE     |           |           | REMOTE UUID |
// +----------+-----------+-----------+-------------+ <-- PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX
// ^          ^ (LSB-MSB) ^ (LSB-MSB) ^
// |          |           |           |
// |<-- A --->|<--- B --->|<--- C --->|<---- D ---->
// |          |           |           |
// |          |           |           +--- PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_STRING_INDEX
// |          |           +--------------- PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX
// |          +--------------------------- PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX
// +-------------------------------------- PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX
//
// Note:
//   A = PL_PROTOCOL_STATUS_SIZE
//   B = PL_PROTOCOL_UUID_SIZE
//   C = PL_PROTOCOL_PLD_SIZE
//   D = variable
//-----------------------------------------------------------------------------
#define PL_PROTOCOL_PL_OPEN_INPUT_OPCODE_INDEX \
	PL_PROTOCOL_INPUT_OP_CODE_INDEX
#define PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX \
	(PL_PROTOCOL_PL_OPEN_INPUT_OPCODE_INDEX + PL_PROTOCOL_OPCODE_SIZE)
#define PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX \
	(PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX + PL_PROTOCOL_COUNTERS_COUNT_SIZE)

#define PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX \
	PL_PROTOCOL_OUTPUT_STATUS_INDEX
#define PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX \
	(PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX + PL_PROTOCOL_STATUS_SIZE)
#define PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX \
	(PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX + PL_PROTOCOL_UUID_SIZE)
#define PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX \
	(PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX + PL_PROTOCOL_PLD_SIZE)


//-----------------------------------------------------------------------------
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
//
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
//-----------------------------------------------------------------------------
#define PL_PROTOCOL_PL_ATTACH_INPUT_OPCODE_INDEX \
	PL_PROTOCOL_INPUT_OP_CODE_INDEX
#define PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX \
	(PL_PROTOCOL_PL_ATTACH_INPUT_OPCODE_INDEX + PL_PROTOCOL_OPCODE_SIZE)

#define PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX \
	PL_PROTOCOL_OUTPUT_STATUS_INDEX
#define PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX \
	(PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX + PL_PROTOCOL_STATUS_SIZE)
#define PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX \
	(PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX + PL_PROTOCOL_UUID_SIZE)
#define PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX \
	(PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX + PL_PROTOCOL_PLD_SIZE)
#define PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX \
	(PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX + PL_PROTOCOL_COUNTERS_COUNT_SIZE)

//-----------------------------------------------------------------------------
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
//
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
//-----------------------------------------------------------------------------
#define PL_PROTOCOL_PL_CLOSE_INPUT_OPCODE_INDEX \
	PL_PROTOCOL_INPUT_OP_CODE_INDEX
#define PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX \
	(PL_PROTOCOL_PL_CLOSE_INPUT_OPCODE_INDEX + PL_PROTOCOL_OPCODE_SIZE)
#define PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX \
	(PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX + PL_PROTOCOL_UUID_SIZE)
#define PL_PROTOCOL_PL_CLOSE_INPUT_EOR_INDEX \
	(PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX + PL_PROTOCOL_PLD_SIZE)
#define PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX \
	PL_PROTOCOL_OUTPUT_STATUS_INDEX
#define PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX \
	(PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX + PL_PROTOCOL_STATUS_SIZE)

//-----------------------------------------------------------------------------
// pl_read()
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
//
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
//-----------------------------------------------------------------------------
#define PL_PROTOCOL_PL_READ_INPUT_OPCODE_INDEX \
	PL_PROTOCOL_INPUT_OP_CODE_INDEX
#define PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX \
	(PL_PROTOCOL_PL_READ_INPUT_OPCODE_INDEX + PL_PROTOCOL_OPCODE_SIZE)
#define PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX \
	(PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX + PL_PROTOCOL_UUID_SIZE)
#define PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX \
	(PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX + PL_PROTOCOL_PLD_SIZE)
#define PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX \
	(PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX + PL_PROTOCOL_COUNTER_OFFSET_SIZE)

#define PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX \
	PL_PROTOCOL_OUTPUT_STATUS_INDEX
#define PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX \
	(PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX + PL_PROTOCOL_STATUS_SIZE)
#define PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX \
	(PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX + PL_PROTOCOL_ULL_SIZE)

//-----------------------------------------------------------------------------
// pl_write()
// +-----------+---------+---------+---------+----------+
// | OPERATION | UUID    | PLD     | OFFSET  | VALUE    |
// | CODE      |         |         |         |          |
// +-----------+---------+---------+---------+----------+ <- PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX
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
//
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
//-----------------------------------------------------------------------------
#define PL_PROTOCOL_PL_WRITE_INPUT_OPCODE_INDEX \
	PL_PROTOCOL_INPUT_OP_CODE_INDEX
#define PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX \
	(PL_PROTOCOL_PL_WRITE_INPUT_OPCODE_INDEX + PL_PROTOCOL_OPCODE_SIZE)
#define PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX \
	(PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX + PL_PROTOCOL_UUID_SIZE)
#define PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX \
	(PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX + PL_PROTOCOL_PLD_SIZE)
#define PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX \
	(PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX + PL_PROTOCOL_COUNTER_OFFSET_SIZE)
#define PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX \
	(PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX + PL_PROTOCOL_ULL_SIZE)

#define PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX \
	PL_PROTOCOL_OUTPUT_STATUS_INDEX
#define PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX \
	(PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX + PL_PROTOCOL_STATUS_SIZE)

typedef enum _PL_PROTOCOL_STATUS {

	PL_PROTOCOL_FAILURE = PL_FAILURE,
	PL_PROTOCOL_SUCCESS = PL_SUCCESS

} PL_PROTOCOL_STATUS, *PPL_PROTOCOL_STATUS;

typedef enum _PL_PROTOCOL_OPCODE {

	PL_PROTOCOL_OPCODE_OPEN = 1,
	PL_PROTOCOL_OPCODE_ATTACH,
	PL_PROTOCOL_OPCODE_CLOSE,
	PL_PROTOCOL_OPCODE_READ,
	PL_PROTOCOL_OPCODE_WRITE

} PL_PROTOCOL_OPCODE, *PPL_PROTOCOL_OPCODE;

#endif // __PL_FILESYSTEM_LESS__ || __PL_AGENT__

//-----------------------------------------------------------------------------
//
// @@@@@  @          @@@@@   @@   @@@@@  @      @@@@@@
// @    @ @            @   @    @ @    @ @      @
// @@@@@  @            @   @@@@@@ @@@@@  @      @@@@@@
// @      @            @   @    @ @    @ @      @
// @      @@@@@@       @   @    @ @@@@@  @@@@@@ @@@@@@
//
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
//
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
//
//-----------------------------------------------------------------------------
//
//   @@          @@@@@  @
// @    @        @    @ @
// @@@@@@        @@@@@  @
// @    @        @      @
// @    @        @      @@@@@@
//
// __PL_DYNAMIC_COUNTERS_ALLOCATION__      __PL_DYNAMIC_COUNTERS_ALLOCATION__ 
//          NOT defined                               defined
//
// +-----------------------------+            +-----------------------------+   
// | Counters count (M)          |            | Counters count (M)          | 
// +-----------------------------+            +-----------------------------+
// | Blocking pl_read data       |            | Blocking pl_read data       |
// | (if __PL_BLOCKING_PL_READ__ |            | (if __PL_BLOCKING_PL_READ__ |
// |  defined)                   |            |  defined)                   |
// +-----------------------------+            +-----------------------------+
// | Socket data                 |            | Socket data                 |
// | (if __PL_FILESYSTEM_LESS__  |            | (if __PL_FILESYSTEM_LESS__  |
// |  defined)                   |            |  defined)                   |
// +-----------------------------+            +-----------------------------+
// | Counter timestamp data      |            | Counter timestamp data      |
// | (if __PL_TIMESTAMPING__ defi|            | (if __PL_TIMESTAMPING__ defi|
// |  defined)                   |            |  defined)                   |
// +-----------------------------+ ---        +-----------------------------+ ---
// | Counter                     |  ^         | * Counter                   |  ^
// |         0                   |  |         |         |                   |  |
// +-----------------------------+            +---------|-------------------+
// |                             |  X                   |                      Y
// | Counter                     |                      |     
// |         1                   |  |                   |                      |
// +-----------------------------+  |                   v                      |
//                                  |         +-----------------------------+  |
//                    ...           |         |                             |  |
//                                  |         | Counter                     |  |
// +-----------------------------+  |         |         0                   |  |
// |                             |  |         +-----------------------------+  |
// | Counter                     |  |         |                             |  |
// |         M-2                 |  |         | Counter                     |  |
// +-----------------------------+  |         |         1                   |  |
// |                             |  |         +-----------------------------+  |
// | Counter                     |  |                                          |
// |         M-1                 |  v                      ...                 |
// +-----------------------------+ ---                                         |
//                                            +-----------------------------+  |
// X: PL_MAX_COUNTERS_PER_LINK                |                             |  |
// Y: LIMITED BY AVAILABLE MEMORY             | Counter                     |  |
//                                            |         M-2                 |  |
//                                            +-----------------------------+  |
//                                            | Counter                     |  |
//                                            |         M-1                 |  v
//                                            +-----------------------------+ ---
// Note:
//    A counter is represented in memory by a handle (implementation dependent)
//    and a samaphore to protect access to the handle.  No counter value is
//    duplicated from application space - besides in the write cache if 
//    available.
//-----------------------------------------------------------------------------

/*
@@@@@  @
@    @ @
@    @ @
@@@@@  @
@      @
@      @
@      @@@@@@
*/
//-----------------------------------------------------------------------------
// Productivity link definition.
//-----------------------------------------------------------------------------
typedef struct _productivity_link {

	unsigned int pl_counters_count;
	#ifdef __PL_WINDOWS__
		BOOL pl_in_use;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		int pl_in_use;
	#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__	
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-------------------------------------------------------------------------
	// Counter write cache.
	//-------------------------------------------------------------------------
	unsigned long long pl_write_cache[PL_MAX_COUNTERS_PER_LINK];
#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	unsigned long long *pl_write_cache;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

#ifdef __PL_BLOCKING_PL_READ__

	//-------------------------------------------------------------------------
	// Data used for local blocking pl_read mode.
	//-------------------------------------------------------------------------
	int pl_attach_flag;
	#ifdef __PL_WINDOWS__
		HANDLE pl_read_notify_handle;
	#endif // __PL_WINDOWS__
	#ifdef __PL_LINUX__
		int pl_read_notify_instance;		
		int pl_read_notify_handle;
		char pl_read_notify_buffer[PL_BLOCKING_PL_READ_NOTIFY_BUFFER_SIZE];
		int pl_read_notify_events;
	#endif // __PL_LINUX__
	#ifdef __PL_SOLARIS__
		int pl_read_notify_port; // not sure it is implemented already ()
	#endif // __PL_SOLARIS__
	#ifdef __PL_MACOSX__
		FSEventStreamRef pl_read_notify_stream;
		//int pl_read_notify_file_descriptor;
		//int pl_read_notify_kernel_queue;
		//struct kevent pl_read_notify_kernel_event;
	#endif // __PL_MACOSX__
#endif // __PL_BLOCKING_PL_READ__

#ifdef __PL_TIMESTAMPING__ 

	//-------------------------------------------------------------------------
	// Data used to maintain counter timestamps.
	// Note:
	//    All in seconds elapsed since midnight, January 1, 1970.
	//-------------------------------------------------------------------------
	#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		time_t open_time[PL_MAX_COUNTERS_PER_LINK];
		time_t last_attach_time[PL_MAX_COUNTERS_PER_LINK];
		time_t last_read_time[PL_MAX_COUNTERS_PER_LINK];
		time_t last_write_time[PL_MAX_COUNTERS_PER_LINK];
		time_t last_close_time[PL_MAX_COUNTERS_PER_LINK];
	#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		time_t *open_time;
		time_t *last_attach_time;
		time_t *last_read_time;
		time_t *last_write_time;
		time_t *last_close_time;
	#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
#endif // __PL_TIMESTAMPING__

	//-------------------------------------------------------------------------
	// Filesystem-less operations data.
	//-------------------------------------------------------------------------
	uuid_t uuid;
	int remote_pld;
#ifdef __PL_FILESYSTEM_LESS__
	char pl_address[PL_MAX_NODE_NAME_SIZE];
	char pl_port[PL_MAX_PORT_NAME_SIZE];
	#ifdef __PL_WINDOWS__
		ADDRINFO *address_info;
		ADDRINFO address_info_hint;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		struct addrinfo *address_info;
		struct addrinfo address_info_hint;
	#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__	
	#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		SOCKET pl_counter_sockets[PL_MAX_COUNTERS_PER_LINK];
	#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		SOCKET *pl_counter_sockets;
	#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
#endif // __PL_FILESYSTEM_LESS__

	//-------------------------------------------------------------------------
	// Counters data.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		HANDLE pl_counter_handles_semaphores[PL_MAX_COUNTERS_PER_LINK];
	#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		HANDLE *pl_counter_handles_semaphores;
	#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	#ifndef __PL_FILESYSTEM_LESS__
		#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
			HANDLE pl_counter_handles[PL_MAX_COUNTERS_PER_LINK];
		#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
			HANDLE *pl_counter_handles;
		#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	#endif // __PL_FILESYSTEM_LESS__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#ifndef __PL_FILESYSTEM_LESS__
		#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
			int pl_counter_handles[PL_MAX_COUNTERS_PER_LINK];
		#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
			int *pl_counter_handles;
		#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	#endif // __PL_FILESYSTEM_LESS__
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
	#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		sem_t pl_counter_handles_semaphores[PL_MAX_COUNTERS_PER_LINK];
	#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		sem_t *pl_counter_handles_semaphores;
	#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
#endif// __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
	#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
		sem_t *pl_counter_handles_semaphores[PL_MAX_COUNTERS_PER_LINK];
	#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
		sem_t **pl_counter_handles_semaphores;
	#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
#endif// __PL_MACOSX__

} PRODUCTIVITY_LINK, *PPRODUCTIVITY_LINK;

/*
@@@@@  @              @@@@@   @@   @@@@@  @      @@@@@@
@    @ @                @    @  @  @    @ @      @
@    @ @                @   @    @ @    @ @      @
@@@@@  @                @   @    @ @@@@@  @      @@@@@@
@      @                @   @@@@@@ @    @ @      @
@      @                @   @    @ @    @ @      @
@      @@@@@@           @   @    @ @@@@@  @@@@@@ @@@@@@
*/
//-----------------------------------------------------------------------------
// Productivity links table.
//-----------------------------------------------------------------------------
typedef struct _pl_table {

	//-------------------------------------------------------------------------
	// semaphore handle for thread safety
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		HANDLE semaphore;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)  
		sem_t semaphore;
#endif// __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
		sem_t *semaphore;
#endif// __PL_MACOSX__

	//-------------------------------------------------------------------------
	// productivity links table
	//-------------------------------------------------------------------------
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
		PRODUCTIVITY_LINK pl_array[PL_MAX_PRODUCTIVITY_LINKS];
#else // __PL_DYNAMIC_TABLE_ALLOCATION__
		PPRODUCTIVITY_LINK pl_array;
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__

} PL_TABLE, *PPL_TABLE;

//-----------------------------------------------------------------------------
// macros
//-----------------------------------------------------------------------------
#if defined (__PL_TIMESTAMPING__) && (__PL_UNIT_TESTS__)
	#define PL_EXTERN_TABLE_DEF extern \
		PPL_TABLE ppl_table
	#define PL_GET_COUNTER_OPEN_TIMESTAMP(p, i) \
		ppl_table->pl_array[(p)].open_time[(i)]
	#define PL_GET_COUNTER_LAST_ATTACH_TIMESTAMP(p, i) \
		ppl_table->pl_array[(p)].last_attach_time[(i)]
	#define PL_GET_COUNTER_LAST_READ_TIMESTAMP(p, i) \
		ppl_table->pl_array[(p)].last_read_time[(i)]
	#define PL_GET_COUNTER_LAST_WRITE_TIMESTAMP(p, i) \
		ppl_table->pl_array[(p)].last_write_time[(i)]
	#define PL_GET_COUNTER_LAST_CLOSE_TIMESTAMP(p, i) \
		ppl_table->pl_array[(p)].last_close_time[(i)]
#endif // __PL_TIMESTAMPING__ && __PL_UNIT_TESTS__

//-----------------------------------------------------------------------------
// globals extern definitions.
//-----------------------------------------------------------------------------
#ifndef __PL_BYPASS__
	extern PL_TABLE pl_table;
	#ifdef __PL_UNIT_TESTS__
		extern PPL_TABLE ppl_table;
	#endif // __PL_UNIT_TESTS__
	#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
		extern unsigned int pl_max_productivity_links;
	#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
#endif // __PL_BYPASS__

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
#ifdef __PL_JNI_EXPORTS__
	#include "ProductivityLink.h"
#else // __PL_JNI_EXPORTS__
	PL_API int pl_open(char *, unsigned int, const char *[], uuid_t *);
	PL_API int pl_attach(const char *);
#ifndef __PL_LOGGER_ONLY__
	PL_API int pl_read(int, void *, unsigned int);
#endif // __PL_LOGGER_ONLY__
	PL_API int pl_close(int);
	PL_API int pl_write(int, const void *, unsigned int);
#endif // __PL_JNI_EXPORTS__

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PRODUCTIVITY_LINK__
