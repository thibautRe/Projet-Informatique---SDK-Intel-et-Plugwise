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
// build with
//-----------------------------------------------------------------------------
//	__PL_WINDOWS__
//  __PL_GENERATE_INI__
//  __PL_GENERATE_INI_VERSION_TAGGING__
//  __PL_GENERATE_INI_BUILD_TAGGING__
//  __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
//  __PL_BLOCKING_COUNTER_FILE_LOCK__
//  __PL_UNIT_TESTS__
//  __PL_UNDEF_T__
//  __PL_EXTRA_INPUT_CHECKS__
//  _CRT_SECURE_NO_DEPRECATE

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include <assert.h>
#include <stdio.h>
#include "productivity_link.h"
#include "unit_tests_framework.h"
#include "unit_tests.h"
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	#include <errno.h>
	#ifdef __PL_MACOSX__
		#include <stdlib.h>
	#endif // __PL_MACOSX__
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

/*---------------------------------------------------------------------------
Function: main
Purpose : entry point
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
int main(void) {

	int test_number = 1;

	//----------------------------------------------------------------------
	// setup unit tests framework 
	//----------------------------------------------------------------------
	plt_setup();

	//----------------------------------------------------------------------
	// display unit tests header line
	//----------------------------------------------------------------------
	PLT_PRINT_HEADER;

	//----------------------------------------------------------------------
	// test pl_open()
	//----------------------------------------------------------------------
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pl_counters_name_NULL_failure_PL_INVALID_PARAMETERS(); // 001
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_puuid_NULL_failure_PL_INVALID_PARAMETERS(); // 002
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pl_counters_count_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(); // 003
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pl_counters_count_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(); // 004
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pl_counters_count_EQUAL_TO_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(); // 005
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(); // 006
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_application_name_NOT_NULL_success_PL_SUCCESS(); // 007
	PLT_PRINT_TEST_NUMBER;
	plt_pl_open_application_name_NULL_success_PL_SUCCESS(); // 008
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_counter_names_NOT_NULL_success_PL_SUCCESS(); // 009
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_counter_names_NULL_success_PL_SUCCESS(); // 010
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_MAX_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(); // 011
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_MAX_PLUS_1_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_failure_PL_DESCRIPTOR_TABLE_FULL(); // 012

	//----------------------------------------------------------------------
	// test pl_open() __PL_EXTRA_INPUT_TESTS__
	//----------------------------------------------------------------------
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pl_application_name_illegal_char_failure_PL_INVALID_PARAMETERS(); // 013
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pl_counter_name_illegal_char_failure_PL_INVALID_PARAMETERS(); // 014
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pl_application_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(); // 015
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_open_pl_counter_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(); // 016	

	//----------------------------------------------------------------------
	// display test separator
	//----------------------------------------------------------------------
	PLT_PRINT_SEPARATOR;

	//----------------------------------------------------------------------
	// test pl_close()
	//----------------------------------------------------------------------
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_close_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(); // 017
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_close_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(); // 018
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_close_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(); // 019
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_close_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(); // 020
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_close_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_PLD_success_PL_SUCCESS(); // 021

	//----------------------------------------------------------------------
	// display test separator
	//----------------------------------------------------------------------
	PLT_PRINT_SEPARATOR;

	//----------------------------------------------------------------------
	// test pl_attach()
	//----------------------------------------------------------------------
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_NULL_failure_PL_INVALID_PARAMETERS(); // 022
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_DOESNT_EXIST_failure_PL_CONFIG_FILE_OPENING_FAILED(); // 023
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_EXIST_success_PL_SUCCESS(); // 024

	//----------------------------------------------------------------------
	// test pl_attach() __PL_EXTRA_INPUT_TESTS__
	//----------------------------------------------------------------------
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_file_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(); // 025
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_file_name_pl_folder_not_present_failure_PL_INVALID_PARAMETERS(); // 026
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_file_name_pl_folder_name_incorrect_failure_PL_INVALID_PARAMETERS(); // 027
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_file_name_not_present_failure_PL_INVALID_PARAMETERS(); // 028
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_file_name_UUID_three_dashes_failure_PL_INVALID_PARAMETERS(); // 029
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_file_name_UUID_invalid_character_failure_PL_INVALID_PARAMETERS(); // 030
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_count_not_allowed_characters_failure_PL_INVALID_PARAMETERS(); // 031
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_count_length_greater_than_PL_MAX_UNSIGNED_INTEGER_STRING_failure_PL_INVALID_PARAMETERS(); // 032
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_name_PL_folder_incorrect_failure_PL_INVALID_PARAMETERS(); // 033
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_name_path_separator_incorrect_failure_PL_INVALID_PARAMETERS(); // 034
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_name_application_name_incorrect_failure_PL_INVALID_PARAMETERS(); // 035
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_name_application_name_invalid_characters_failure_PL_INVALID_PARAMETERS(); // 036
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_name_UUID_incorrect_failure_PL_INVALID_PARAMETERS();  // 037
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_name_UUID_invalid_format_failure_PL_INVALID_PARAMETERS(); // 038
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_counters_count_incorrect_failure_PL_INVALID_PARAMETERS(); // 039
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_attach_pl_config_file_from_remote_success_PL_SUCCESS(); // 040

	//----------------------------------------------------------------------
	// display test separator
	//----------------------------------------------------------------------
	PLT_PRINT_SEPARATOR;

	//----------------------------------------------------------------------
	// test pl_read()
	//----------------------------------------------------------------------
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(); // 041
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(); // 042
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(); // 043
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(); // 044
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_p_NULL_failure_PL_INVALID_PARAMETERS(); // 045
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_counter_out_of_range_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(); // 046
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_counter_out_of_range_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(); // 047
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_counter_out_of_range_HIGHER_THAN_ACTUAL_COUNTERS_IN_PL_failure_PL_INVALID_PARAMETERS(); // 048
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(); // 049
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_p_VALID_ADDRESS_AND_MAX_COUNTER_VALUE_success_PL_SUCCESS(); // 050
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_success_PL_SUCCESS(); // 051
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_CORRUPT_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE(); // 052
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_read_OVERFLOW_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE(); // 053

	//----------------------------------------------------------------------
	// display test separator
	//----------------------------------------------------------------------
	PLT_PRINT_SEPARATOR;

	//----------------------------------------------------------------------
	// test pl_write()
	//----------------------------------------------------------------------
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(); // 054
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(); // 055
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(); // 056
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(); // 057
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_p_NULL_failure_PL_INVALID_PARAMETERS(); // 058
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_counter_out_of_range_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(); // 059
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_counter_out_of_range_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(); // 060
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_counter_out_of_range_HIGHER_THAN_ACTUAL_COUNTERS_IN_PL_failure_PL_INVALID_PARAMETERS(); // 061
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(); // 062
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_p_VALID_ADDRESS_AND_MAX_COUNTER_VALUE_success_PL_SUCCESS(); // 063
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_success_PL_SUCCESS(); // 064
	PLT_PRINT_TEST_NUMBER; 
	plt_pl_write_CACHED_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(); // 065
	PLT_PRINT_TEST_NUMBER;
	plt_pl_write_NON_CACHED_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(); // 066

	//----------------------------------------------------------------------
	// teardown unit tests framework 
	//----------------------------------------------------------------------
	PLT_PRINT_SEPARATOR;
	plt_teardown();

	return(PL_SUCCESS);
}

/*---------------------------------------------------------------------------
Function: pl_test_setup
Purpose : set up a clean PL configuration
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_setup(void) {
	plt_new_pl_folder();
}

/*---------------------------------------------------------------------------
Function: plt_new_pl_folder
Purpose : delete PL_FORLDER and re-create it
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
extern void plt_new_pl_folder(void) {
	plt_delete_pl_folder();
	plt_create_pl_folder();
}

/*---------------------------------------------------------------------------
Function: plt_delete_pl_folder
Purpose : delete PL_FORLDER
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_delete_pl_folder(void) {
	int ret = -1;
	ret = system(PL_UNIT_TESTS_DELETE_PL_FOLDER);
	assert(ret != -1);
}

/*---------------------------------------------------------------------------
Function: plt_create_pl_folder
Purpose : create PL_FORLDER
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_create_pl_folder(void) {
	int ret = -1;
	ret = system(PL_UNIT_TESTS_CREATE_PL_FOLDER);
	assert(ret != -1);
}

/*---------------------------------------------------------------------------
Function: plt_teardown
Purpose : tear down test setup
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_teardown(void) {
	plt_new_pl_folder();
}

/*---------------------------------------------------------------------------
Function: plt_print_test
Purpose : print to stdout a string describing the test
In      : pointer to a test description string
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_print_test(
	char *function, 
	char *condition, 
	char *condition_value, 
	char *status, 
	char *status_value, 
	char *error, 
	unsigned long long extra_data
) {
	
	assert(function != 0);
	assert(condition != 0);
	assert(condition_value != 0);
	assert(status != 0);
	assert(status_value != 0);
	assert(error != 0);

	fprintf(
		stdout, 
		PL_UNIT_TESTS_PRINT_STRING, 
		function, 
		condition, 
		condition_value, 
		status, 
		status_value, 
		error, 
		extra_data
	);
}

/*---------------------------------------------------------------------------
Function: plt_print_status
Purpose : print to stdout a PASS / FAIL message
In      : PL_STATUS
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_print_status(PL_STATUS x) {
	if(x == PL_SUCCESS) { 
		fprintf(
			stdout, 
			"[   PASS   ] "
		); 
	} else { 
		fprintf(
			stdout, 
			"[ --FAIL-- ] "
		);
	}
}

/*---------------------------------------------------------------------------
Function: plt_print_pld
Purpose : print to stdout a PASS / FAIL message
In      : PL_STATUS
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_print_pld(PL_STATUS x) {
	if(x == PL_SUCCESS) { 
		fprintf(
			stdout, 
			"[   PASS   ] "
		); 
	} else { 
		fprintf(
			stdout, 
			"[ --FAIL-- ] "
		); 
	}
}

/*---------------------------------------------------------------------------
Function: plt_print_error
Purpose : print to stdout a PASS / FAIL message
In      : PL_STATUS
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_print_error(PL_STATUS x) {
	if(x == PL_SUCCESS) { 
		fprintf(
			stdout, 
			"[   PASS   ] "
		); 
	} else { 
		fprintf(
			stdout, 
			"[ --FAIL-- ] "
		); 
	}
}

/*---------------------------------------------------------------------------
Function: plt_assert_equal
Purpose : assert equality of two PL_STATUS arguments
In      : two PL_STATUS to compare
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
PL_STATUS plt_assert_status_equal(PL_STATUS x, PL_STATUS y) {
	if(x == y) return (PL_SUCCESS);
	return(PL_FAILURE);
}

/*---------------------------------------------------------------------------
Function: plt_assert_pld_equal
Purpose : assert equality of two integer arguments (pld)
In      : two PL_STATUS to compare
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
PL_STATUS plt_assert_pld_equal(int x, int y) {
	if(x == y) return (PL_SUCCESS);
	return(PL_FAILURE);
}

/*---------------------------------------------------------------------------
Function: plt_assert_pld_not_equal
Purpose : assert non equality of two integer arguments (pld)
In      : two PL_STATUS to compare
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
PL_STATUS plt_assert_pld_not_equal(int x, int y) {
	if(x != y) return (PL_SUCCESS);
	return(PL_FAILURE);
}

/*---------------------------------------------------------------------------
Function: plt_assert_error_equal
Purpose : assert equality of two PL_ERROR arguments
In      : two PL_STATUS to compare
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
PL_STATUS plt_assert_error_equal(PL_ERROR x, PL_ERROR y) {
	if(x == y) return (PL_SUCCESS);
	return(PL_FAILURE);
}

/*---------------------------------------------------------------------------
Function: plt_assert_error_equal_tristate
Purpose : assert equality of error code with three possible values
In      : two PL_STATUS to compare
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
PL_STATUS plt_assert_error_equal_tristate(PL_ERROR a, PL_ERROR x, PL_ERROR y, PL_ERROR z) {
	if((a == x) || (a == y) || (a == z)) return (PL_SUCCESS);
	return(PL_FAILURE);
}

/*---------------------------------------------------------------------------
Function: plt_get_last_error
Purpose : returns last error
In      : none
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
PL_ERROR plt_get_last_error(void) {
#ifdef __PL_WINDOWS__
	return((PL_ERROR)GetLastError());
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	return(errno);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}
