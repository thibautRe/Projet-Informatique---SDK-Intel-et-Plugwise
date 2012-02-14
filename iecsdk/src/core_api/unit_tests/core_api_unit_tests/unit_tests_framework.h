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
*** or disclosed in any way without Intel's prior express written permission.
***
*** No license under any patent, copyright, trade secret or other intellectual
*** property right is granted to or conferred upon you by disclosure or delivery
*** of the Materials, either expressly, by implication, inducement, estoppel or
*** otherwise. Any license under such intellectual property rights must be 
*** express and approved by Intel in writing.
**/

#ifndef __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS_FRAMEWORK__
#define __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS_FRAMEWORK__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include "productivity_link.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// constants
//-----------------------------------------------------------------------------
#define PL_UNIT_TESTS_PRINT_STRING_HEADER \
"================================================================================================================\n\
[ T#  ] [  STATUS  ] [  ERROR   ] : { FUNCTION, CONDITION (VALUE) --> STATUS (VALUE), ERROR CODE, [EXTRA DATA] }\n\
================================================================================================================"
#define PL_UNIT_TESTS_PRINT_STRING_SEPARATOR \
"----------------------------------------------------------------------------------------------------------------"
#ifdef __PL_WINDOWS__
	#define PL_UNIT_TESTS_PRINT_STRING ": { %s, %s (%s) --> %s (%s), %s, [%I64u] }\n"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#define PL_UNIT_TESTS_PRINT_STRING ": { %s, %s (%s) --> %s (%s), %s, [%llu] }\n"
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#define PL_UNIT_TESTS_APPLICATION_NAME "unit_tests_application"
#define PL_UNIT_TESTS_APPLICATION_NAME1 "unit_tests_application1"

#define PL_UNIT_TESTS_APPLICATION_NAME_1_ILLEGAL_CHAR "unit_tests_application!"
#define PL_UNIT_TESTS_APPLICATION_NAME_LENGTH_GREATER_THAN_PL_MAX_PATH "unit_tests_application_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define PL_CONFIG_FILE_NAME_GREATER_THAN_PL_MAX_PATH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define PL_CONFIG_FILE_NAME_PL_FOLDER_NOT_PRESENT "c:\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\pl_config.ini"
#define PL_CONFIG_FILE_NAME_PL_FOLDER_NAME_INCORRECT "c:\\productivity_pink\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\pl_config.ini"
#define PL_CONFIG_FILE_NAME_NOT_PRESENT "c:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\Test.ini"
#define PL_CONFIG_FILE_NAME_UUID_THREE_DASHES "c:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFFFFFFFFFFFFFF\\pl_config.ini"
#define PL_CONFIG_FILE_NAME_UUID_INVALID_CHARACTER "c:\\productivity_link\\unit_tests_application_(FFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\pl_config.ini"

/*
//-----------------------------------------------------------------------------
// pl_congig.ini file locations.
//-----------------------------------------------------------------------------

      1   5   10   15   20   25   30   35   45   50   55   60   65   70   75   80   85   90   95  100  105 107
    +-+---+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+-+-+
01  | unit_tests_application                                                                                 |
02  | FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF                                                                   |
03  | /opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/                    |
04  | 4                                                                                                      |
05  | /opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_0 |
06  | /opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_1 |
07  | /opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_2 |
08  | /opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_3 |
09  | 2010.12.15(L)                                                                                          |
10  | __PL_EXTRA_INPUT_CHECKS__                                                                              |
11  | __PL_LINUX__                                                                                           |
12  | __PL_GENERATE_INI__                                                                                    |
13  | __PL_GENERATE_INI_VERSION_TAGGING__                                                                    |
14  | __PL_GENERATE_INI_BUILD_TAGGING__                                                                      |
15  | __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__                                                              |
16  | __PL_BLOCKING_COUNTER_FILE_LOCK__                                                                      |
17  | PL created on Mon Nov 29 13:19:51 2010                                                                 |
    +-+---+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+-+-+
01  | unit_tests_application                                                                                 |
02  | FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFFFFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF                               |
03  | C:\productivity_link\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\                      |
04  | 4                                                                                                      |
05  | C:\productivity_link\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\anonymous_counter_0   |
06  | C:\productivity_link\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\anonymous_counter_1   |
07  | C:\productivity_link\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\anonymous_counter_2   |
08  | C:\productivity_link\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\anonymous_counter_3   |
09  | 2010.12.15.(W)                                                                                         |
10  | _UNICODE__PL_EXTRA_INPUT_CHECKS__                                                                      |
11  | UNICODE                                                                                                |
12  | __PL_EXTRA_INPUT_CHECKS__                                                                              |
13  | __PL_WINDOWS__                                                                                         |
14  | __PL_GENERATE_INI__                                                                                    |
15  | __PL_GENERATE_INI_VERSION_TAGGING__                                                                    |
16  | __PL_GENERATE_INI_BUILD_TAGGING__                                                                      |
17  | __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__                                                              |
18  | __PL_BLOCKING_COUNTER_FILE_LOCK__                                                                      |
19  | PL created on Mon Nov 29 13:02:54 2010                                                                 |
    +-+---+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+-+-+
      1   5   10   15   20   25   30   35   45   50   55   60   65   70   75   80   85   90   95  100  105 107

Also defined in productivity_link.h:
------------------------------------
#define PL_CONFIGURATION_FILE_APPLICATION_NAME_LINE 1
#define PL_CONFIGURATION_FILE_UUID_STRING_LINE 2
#define PL_CONFIGURATION_FILE_LOCATION_LINE 3
#define PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE 4
*/
#define PL_UNIT_TESTS_COUNTER_COUNT_LINE PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE
#define PL_UNIT_TESTS_COUNTER_COUNT_COLUMN 1
#define PL_UNIT_TESTS_COUNTER_PL_FOLDER_NAME_LINE (PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE + 1)
#define PL_UNIT_TESTS_COUNTER_PL_FOLDER_NAME_COLUMN 10
#define PL_UNIT_TESTS_COUNTER_NAME_PATH_SEPARATOR_LINE (PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE + 1)
#ifdef __PL_WINDOWS__
	#define PL_UNIT_TESTS_COUNTER_NAME_PATH_SEPARATOR_COLUMN 21
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PL_UNIT_TESTS_COUNTER_NAME_PATH_SEPARATOR_COLUMN 23
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#define PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_LINE (PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE + 1)
#define PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_COLUMN 35
#define PL_UNIT_TESTS_COUNTER_NAME_UUID_LINE (PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE + 1)
#define PL_UNIT_TESTS_COUNTER_NAME_UUID_COLUMN 55

//-----------------------------------------------------------------------------
// test application and counters definitions.
//-----------------------------------------------------------------------------
#define PL_UNIT_TESTS_ANONYMOUS_APPLICATION_NAME PL_ANONYMOUS_APPLICATION_NAME
#ifdef __PL_WINDOWS__
	#define PL_UNIT_TESTS_APPLICATION_TNAME _T("unit_tests_application")
	#define PL_UNIT_TESTS_APPLICATION_COUNTER_TNAMES \
		{ \
			_T("unit_tests_counter_a"), \
			_T("unit_tests_counter_b"), \
			_T("unit_tests_counter_c"), \
			_T("unit_tests_counter_d") \
		}
#endif // __PL_WINDOWS__
#define PL_UNIT_TESTS_COUNTERS_COUNT 4
#define PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES \
	{ \
		"unit_tests_counter_a", \
		"unit_tests_counter_b", \
		"unit_tests_counter_c", \
		"unit_tests_counter_d" \
	}
#define PL_UNIT_TESTS_APPLICATION_ANONYMOUS_COUNTER_NAMES \
	{ \
		"anonymous_counter_1", \
		"anonymous_counter_2", \
		"anonymous_counter_3", \
		"anonymous_counter_4" \
	}
#define PL_UNIT_TESTS_APPLICATION_NULL_COUNTER_NAMES \
	{ \
		NULL, \
		NULL, \
		NULL, \
		NULL \
	}

#define PL_UNIT_TESTS_APPLICATION_ILLEGAL_CHAR_COUNTER_NAMES \
	{ \
		"unit_tests_counter_a!", \
		"unit_tests_counter_b!", \
		"unit_tests_counter_c!", \
		"unit_tests_counter_d!" \
	}
#define PL_UNIT_TESTS_APPLICATION_COUNTER_NAME_LENGTH_GREATER_THAN_PL_MAX_PATH_COUNTER_NAMES \
	{ \
		"unit_tests_counter_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", \
		"unit_tests_counter_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", \
		"unit_tests_counter_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", \
		"unit_tests_counter_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" \
	}

//-----------------------------------------------------------------------------
// test counter values definitions.
//-----------------------------------------------------------------------------
#define PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX 0
#define PL_UNIT_TESTS_COUNTER_TEST_VALUES_MAX_VALUE_INDEX 1
#define PL_UNIT_TESTS_COUNTER_TEST_VALUES_10_VALUE_INDEX 2
#define PL_UNIT_TESTS_COUNTER_TEST_VALUES_100_VALUE_INDEX 3
#define PL_UNIT_TESTS_COUNTER_TEST_VALUES \
	{ \
		0, \
		PL_MAX_COUNTER_VALUE, \
		10, \
		100 \
	}
#define PL_UNIT_TESTS_COUNTER_CACHE_MISS_TEST_VALUES \
	{ \
		0 + 1, \
		PL_MAX_COUNTER_VALUE - 1, \
		10 + 1, \
		100 + 1 \
	}
#define PL_UNIT_TESTS_COUNTER_CORRUPT_TEST_ASCII_VALUES "THIS IS NOT A NUMBER" // same lenght than PL_MAX_COUNTER_VALUE
#define PL_UNIT_TESTS_COUNTER_OVERFLOW_TEST_ASCII_VALUES "18446744073709551616" // PL_MAX_COUNTER_VALUE + 1
#define PL_UNIT_TESTS_COUNTER_COUNT_OFFENDING_CHARACTER 'A'
#define PL_UNIT_TESTS_COUNTER_COUNT_TOO_LONG "42949672951"
#define PL_UNIT_TESTS_COUNTER_PL_FOLDER_NAME_OFFENDING_CHARACTER 'K'
#define PL_UNIT_TESTS_COUNTER_NAME_OFFENDING_PATH_SEPARATOR_OFFENDING_CHARACTER '%'
#define PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_OFFENDING_CHARACTER 'Q'
#define PL_UNIT_TESTS_COUNTER_NAME_UUID_OFFENDING_CHARACTER '&'
#ifdef __PL_WINDOWS__
	#define PL_UNIT_TESTS_NON_EXISTING_PL_CONFIG_NAME "c:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\pl_config.ini"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_MACOSX__) || (__PL_SOLARIS__)
	#define PL_UNIT_TESTS_NON_EXISTING_PL_CONFIG_NAME "/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/pl_config.ini"
#endif // __PL_LINUX__ || __PL_MACOSX__ || __PL_SOLARIS__

//-----------------------------------------------------------------------------
// configuration definitions -- system specific
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// static pl_congig files -- for cross-platform validation.
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#define PL_UNIT_TESTS_CREATE_PL_CONFIG_FILE_REMOTE_FOLDER "mkdir c:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"
	#define PL_CONFIG_FILE_REMOTE "C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\pl_config.ini"
	#define PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_0 "C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\anonymous_counter_0" 
	#define PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_1 "C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\anonymous_counter_1" 
	#define PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_2 "C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\anonymous_counter_2" 
	#define PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_3 "C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\anonymous_counter_3" 
	#define PL_CONFIG_FILE_REMOTE_CONTENT \
"unit_tests_application\n\
FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\n\
/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/\n\
4\n\
/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_0\n\
/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_1\n\
/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_2\n\
/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_3\n\
2010.12.15(L)\n\
__PL_EXTRA_INPUT_CHECKS__\n\
__PL_LINUX__\n\
__PL_GENERATE_INI__\n\
__PL_GENERATE_INI_VERSION_TAGGING__\n\
__PL_GENERATE_INI_BUILD_TAGGING__\n\
__PL_GENERATE_INI_DATE_AND_TIME_TAGGING__\n\
__PL_BLOCKING_COUNTER_FILE_LOCK__\n\
PL created on Mon Nov 29 13:19:51 2010\n\
"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#if defined (__PL_LINUX__) || (__PL_MACOSX__)
		#define PL_UNIT_TESTS_CREATE_PL_CONFIG_FILE_REMOTE_FOLDER "mkdir /opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"
	#endif // __PL_LINUX__ || __PL_MACOSX__
	#if defined (__PL_SOLARIS__)
		#define PL_UNIT_TESTS_CREATE_PL_CONFIG_FILE_REMOTE_FOLDER "mkdir -p /opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"
	#endif // __PL_SOLARIS__
	#define PL_CONFIG_FILE_REMOTE "/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/pl_config.ini"
	#define PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_0 "/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_0" 
	#define PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_1 "/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_1" 
	#define PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_2 "/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_2" 
	#define PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_3 "/opt/productivity_link/unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF/anonymous_counter_3" 
	#define PL_CONFIG_FILE_REMOTE_CONTENT \
"unit_tests_application\n\
FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\n\
C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\\n\
4\n\
C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\anonymous_counter_0\n\
C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\anonymous_counter_1\n\
C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\anonymous_counter_2\n\
C:\\productivity_link\\unit_tests_application_FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\\anonymous_counter_3\n\
2010.12.15.(W)\n\
_UNICODE\n\
UNICODE\n\
__PL_EXTRA_INPUT_CHECKS__\n\
__PL_WINDOWS__\n\
__PL_GENERATE_INI__\n\
__PL_GENERATE_INI_VERSION_TAGGING__\n\
__PL_GENERATE_INI_BUILD_TAGGING__\n\
__PL_GENERATE_INI_DATE_AND_TIME_TAGGING__\n\
__PL_BLOCKING_COUNTER_FILE_LOCK__\n\
PL created on Mon Nov 29 13:02:54 2010\n\
"
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// PL_FOLDER manipulations
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#define PL_UNIT_TESTS_DELETE_PL_FOLDER "rmdir /S /Q c:\\productivity_link\\"
	#define PL_UNIT_TESTS_CREATE_PL_FOLDER "mkdir c:\\productivity_link\\"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_MACOSX__)
	#define PL_UNIT_TESTS_DELETE_PL_FOLDER "rm -rf /opt/productivity_link/"
	#define PL_UNIT_TESTS_CREATE_PL_FOLDER "mkdir /opt/productivity_link/"
#endif // __PL_LINUX__ || __PL_MACOSX__
#if defined (__PL_SOLARIS__)
	#define PL_UNIT_TESTS_DELETE_PL_FOLDER "rm -rf /opt/productivity_link/*"
	#define PL_UNIT_TESTS_CREATE_PL_FOLDER "mkdir -p /opt/productivity_link/"
#endif // __PL_SOLARIS__

//-----------------------------------------------------------------------------
// macros
//-----------------------------------------------------------------------------
#define PLT_PRINT_TEST_NUMBER \
	fprintf(stdout, "[ %03d ] ", test_number++)
#define PLT_PRINT_HEADER \
	fprintf(stdout, "%s\n", PL_UNIT_TESTS_PRINT_STRING_HEADER)
#define PLT_PRINT_SEPARATOR \
	fprintf(stdout, "%s\n", PL_UNIT_TESTS_PRINT_STRING_SEPARATOR)
#define PLT_PRINT_FILLER \
	fprintf(stdout, "        ")

//-----------------------------------------------------------------------------
// functions prototypes
//-----------------------------------------------------------------------------
extern void plt_setup(void);
extern void plt_new_pl_folder(void);
extern void plt_delete_pl_folder(void);
extern void plt_create_pl_folder(void);
extern void plt_teardown(void);
extern void plt_print_test(
	char *, 
	char *, 
	char *, 
	char *, 
	char *, 
	char *, 
	unsigned long long
);
extern void plt_print_pld(PL_STATUS);
extern void plt_print_status(PL_STATUS);
extern void plt_print_error(PL_STATUS);
extern PL_STATUS plt_assert_pld_equal(int, int);
extern PL_STATUS plt_assert_pld_not_equal(int, int);
extern PL_STATUS plt_assert_status_equal(PL_STATUS, PL_STATUS);
extern PL_STATUS plt_assert_error_equal(PL_ERROR, PL_ERROR);
extern PL_STATUS plt_assert_error_equal_tristate(
	PL_ERROR, 
	PL_ERROR, 
	PL_ERROR, 
	PL_ERROR
);
extern PL_ERROR plt_get_last_error(void);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS_FRAMEWORK__
