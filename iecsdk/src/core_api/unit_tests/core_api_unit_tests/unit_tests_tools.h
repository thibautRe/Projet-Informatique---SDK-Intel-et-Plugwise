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

#ifndef __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS_TOOLS__
#define __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS_TOOLS__

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
// constants
//-----------------------------------------------------------------------------
#define PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE PL_MAX_PATH

//-----------------------------------------------------------------------------
// configuration - system specific
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	extern void plt_tools_set_pl_table_state(BOOL);
	extern BOOL plt_tools_get_pl_table_state(void);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	extern void plt_tools_set_pl_table_state(int);
	extern int plt_tools_get_pl_table_state(void);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
extern void plt_tools_get_pl_counter_name(unsigned int, char *);
extern void plt_tools_get_pl_application_name(char *);
extern void plt_tools_get_pl_config_full_file_name(char *);
extern unsigned int plt_tools_get_pl_counter_counts(void);
extern unsigned long long plt_tools_get_pl_counter_value(unsigned int);
extern void plt_tools_set_pl_counter_value(unsigned int);
extern void plt_tools_set_pl_corrupt_counter_file_value(unsigned int);
extern void plt_tools_set_pl_corrupt_counter_value(unsigned long long *);
extern void plt_tools_set_pl_overflow_counter_value(unsigned int);
extern void plt_tools_set_pl_counter_write_cache_hit(unsigned int);
extern void plt_tools_set_pl_counter_write_cache_miss(unsigned int);
extern void ptl_replace_byte_in_file_with_byte(
	char *, 
	size_t, 
	size_t, 
	unsigned char
);
extern void ptl_replace_byte_in_file_with_byte_string(
	char *, 
	size_t, 
	size_t, 
	unsigned char*, 
	size_t
);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PRODUCTIVITY_LINK_UNIT_TESTS_TOOLS__
