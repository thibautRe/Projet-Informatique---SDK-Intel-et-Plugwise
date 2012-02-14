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

#ifndef __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS__
#define __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// pl_open unit tests
	//-------------------------------------------------------------------------
	// PL_FAILURE
	extern void plt_pl_open_pl_counters_name_NULL_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_open_puuid_NULL_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_open_pl_counters_count_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_open_pl_counters_count_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_open_pl_counters_count_EQUAL_TO_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(void);
	extern void plt_pl_open_MAX_PLUS_1_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_failure_PL_DESCRIPTOR_TABLE_FULL(void);
	// PL_SUCCESS
	extern void plt_pl_open_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(void);
	extern void plt_pl_open_MAX_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(void);
	extern void plt_pl_open_application_name_NULL_success_PL_SUCCESS(void);
	extern void plt_pl_open_application_name_NOT_NULL_success_PL_SUCCESS(void);
	extern void plt_pl_open_counter_names_NULL_success_PL_SUCCESS(void);
	extern void plt_pl_open_counter_names_NOT_NULL_success_PL_SUCCESS(void);
	extern void plt_pl_open_MAX_PLUS_1_counters_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_failure_PL_DESCRIPTOR_TABLE_FULL(void);

	//-------------------------------------------------------------------------
	// pl_open unit tests __PL_EXTRA_INPUT_TESTS__
	//-------------------------------------------------------------------------
	extern void plt_pl_open_pl_application_name_illegal_char_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_open_pl_counter_name_illegal_char_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_open_pl_application_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_open_pl_counter_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_open_pl_filesystem_less_IPV4_ADDRESS_DIGIT_ZERO_failure_PL_FILESYSTEM_LESS_INVALID_IPV4_ADDRESS(void);

	//-------------------------------------------------------------------------
	// pl_close unit tests
	//-------------------------------------------------------------------------
	// PL_FAILURE
	extern void plt_pl_close_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(void);
	extern void plt_pl_close_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_close_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_close_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(void);
	// PL_SUCCESS
	extern void plt_pl_close_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_PLD_success_PL_SUCCESS(void);

	//-------------------------------------------------------------------------
	// pl_attach unit tests
	//-------------------------------------------------------------------------
	// PL_FAILURE
	extern void plt_pl_attach_pl_config_NULL_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_DOESNT_EXIST_failure_PL_CONFIG_FILE_OPENING_FAILED(void);
	// PL_SUCCESS
	extern void plt_pl_attach_pl_config_EXIST_success_PL_SUCCESS(void);

	//-------------------------------------------------------------------------
	// pl_attach unit tests __PL_EXTRA_INPUT_TESTS__
	//-------------------------------------------------------------------------
	extern void plt_pl_attach_pl_config_file_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_file_name_pl_folder_not_present_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_file_name_pl_folder_name_incorrect_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_file_name_not_present_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_file_name_UUID_three_dashes_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_file_name_UUID_invalid_character_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_counters_count_not_allowed_characters_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_counters_count_length_greater_than_PL_MAX_UNSIGNED_INTEGER_STRING_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_counters_name_PL_folder_incorrect_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_counters_name_path_separator_incorrect_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_counters_name_application_name_incorrect_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_counters_name_application_name_invalid_characters_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_counters_name_UUID_incorrect_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_counters_name_UUID_invalid_format_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_attach_pl_config_file_from_remote_success_PL_SUCCESS(void);
	extern void plt_pl_attach_pl_config_counters_count_incorrect_failure_PL_INVALID_PARAMETERS(void);

	//-------------------------------------------------------------------------
	// pl_read unit tests
	//-------------------------------------------------------------------------
	// PL_FAILURE
	extern void plt_pl_read_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(void);
	extern void plt_pl_read_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_read_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_read_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_read_p_NULL_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_read_counter_out_of_range_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_read_counter_out_of_range_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_read_counter_out_of_range_HIGHER_THAN_ACTUAL_COUNTERS_IN_PL_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_read_CORRUPT_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE(void);
	extern void plt_pl_read_OVERFLOW_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE(void);
	// PL_SUCCESS
	extern void plt_pl_read_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(void);
	extern void plt_pl_read_p_VALID_ADDRESS_AND_MAX_COUNTER_VALUE_success_PL_SUCCESS(void);
	extern void plt_pl_read_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_success_PL_SUCCESS(void);

	//-------------------------------------------------------------------------
	// pl_write unit tests
	//-------------------------------------------------------------------------
	// PL_FAILURE
	extern void plt_pl_write_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(void);
	extern void plt_pl_write_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_write_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_write_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_write_p_NULL_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_write_counter_out_of_range_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_write_counter_out_of_range_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_write_counter_out_of_range_HIGHER_THAN_ACTUAL_COUNTERS_IN_PL_failure_PL_INVALID_PARAMETERS(void);
	extern void plt_pl_write_CORRUPT_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE(void);
	extern void plt_pl_write_OVERFLOW_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE(void);
	// PL_SUCCESS
	extern void plt_pl_write_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(void);
	extern void plt_pl_write_p_VALID_ADDRESS_AND_MAX_COUNTER_VALUE_success_PL_SUCCESS(void);
	extern void plt_pl_write_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_success_PL_SUCCESS(void);
	extern void plt_pl_write_CACHED_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(void);
	extern void plt_pl_write_NON_CACHED_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(void);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS__
