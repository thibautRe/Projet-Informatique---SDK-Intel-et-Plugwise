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
#ifdef __PL_WINDOWS__
	#include <tchar.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#include <string.h>
	#include <errno.h>
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"
#include "unit_tests.h"
#include "unit_tests_tools.h"
#include "unit_tests_framework.h"

/*
@@@@@  @              @@@@  @@@@@  @@@@@@ @    @
@    @ @             @    @ @    @ @      @@   @
@    @ @             @    @ @    @ @      @ @  @
@@@@@  @             @    @ @@@@@  @@@@@@ @ @  @
@      @             @    @ @      @      @  @ @
@      @             @    @ @      @      @   @@
@      @@@@@@         @@@@  @      @@@@@@ @    @
              @@@@@@
*/
/*---------------------------------------------------------------------------
Function: plt_pl_open_pl_counters_name_NULL_failure_PL_INVALID_PARAMETERS
Purpose : check pl_open failure (with NULL pl_counters_name)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_pl_counters_name_NULL_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	PL_ERROR err = PL_NO_ERROR;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		NULL, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_counters_name", 
		"NULL", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_puuid_NULL_failure_PL_INVALID_PARAMETERS
Purpose : check pl_open failure (with NULL puuid)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_puuid_NULL_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	PL_ERROR err = PL_NO_ERROR;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		NULL
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_open", 
		"puuid", 
		"NULL", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_pl_counters_count_LOWER_THAN_0_failure_PL_INVALID_...
          PARAMETERS
Purpose : check pl_open failure (with lower than 0 pl_counters_count)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_pl_counters_count_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	uuid_t uuid;
	PL_ERROR err = PL_NO_ERROR;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		-1, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_counters_count", 
		"LOWER_THAN_0", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_OUT_OF_MEMORY
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_counters_count", 
		"LOWER_THAN_0", 
		"FAILURE", 
		"PL_OUT_OF_MEMORY", 
		"NEG VALUE-> TOO HIGH VALUE FOR MALLOC", 
		0
	);
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_pl_counters_count_HIGHER_THAN_PL_MAX_COUNTERS_PER_...
          LINK_failure_PL_INVALID_PARAMETERS
Purpose : check pl_open failure (with higher than x pl_counters_count)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_pl_counters_count_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	const char *counters[PL_MAX_COUNTERS_PER_LINK + 1] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	uuid_t uuid;
	PL_ERROR err = PL_NO_ERROR;
#ifdef __PL_DYNAMIC_COUNTERS_ALLOCATION__
	PL_STATUS ret = PL_FAILURE;
#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_MAX_COUNTERS_PER_LINK + 1, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
#ifndef __PL_DYNAMIC_COUNTERS_ALLOCATION__
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_counters_count", 
		"HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
#else // __PL_DYNAMIC_COUNTERS_ALLOCATION__
	plt_print_pld(
		plt_assert_pld_not_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_counters_count", 
		"HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR -- DYNAMIC", 
		0
	);

	//-----------------------------------------------------------------------
	// close PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}

#endif // __PL_DYNAMIC_COUNTERS_ALLOCATION__
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_pl_counters_count_EQUAL_TO_PL_MAX_COUNTERS_PER_LINK...
          _success_PL_SUCCESS
Purpose : check pl_open failure (with pl_counters_count EQUAL_TO_PL_MAX_...
          COUNTERS_PER_LINK)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_pl_counters_count_EQUAL_TO_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	const char *counters[PL_MAX_COUNTERS_PER_LINK + 1] = { NULL };
	uuid_t uuid;
	PL_ERROR err = PL_NO_ERROR;
	PL_STATUS ret = PL_FAILURE;
	int i = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// request anonymous counters -- do not affect test vs. named counters
	//-----------------------------------------------------------------------
	for(i = 0; i < PL_MAX_COUNTERS_PER_LINK; i++) {
		counters[i] = NULL;
	}

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_MAX_COUNTERS_PER_LINK, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_pld_not_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_open",
		"pl_counters_count", 
		"EQUAL_TO_PL_MAX_COUNTERS_PER_LINK", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);

	//-----------------------------------------------------------------------
	// close PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK...
          _success_PL_SUCCESS
Purpose : check pl_open success (with pl)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(void) {
	
	PL_STATUS ret = PL_FAILURE;
	int pld = PL_INVALID_DESCRIPTOR;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	uuid_t uuid;
	PL_ERROR err = PL_NO_ERROR;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_pld_not_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_counters_count", 
		"BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_MAX_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_...
          LINK_success_PL_SUCCESS
Purpose : check pl_open success (with pl BETWEEN_0_AND_PL_MAX_COUNTERS_PER...
          _LINK)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_MAX_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_success_PL_SUCCESS(void) {
	
	PL_STATUS ret = PL_FAILURE;
	int plds[PL_MAX_PRODUCTIVITY_LINKS];
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	uuid_t uuid;
	PL_ERROR err = PL_NO_ERROR;
	int i = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open PL_MAX_PRODUCTIVITY_LINKS PLs
	//-----------------------------------------------------------------------
	for(i = 0; i < PL_MAX_PRODUCTIVITY_LINKS; i++) {

		//-----------------------------------------------------------------------
		// *** test ***
		//-----------------------------------------------------------------------
		plds[i] = PL_INVALID_DESCRIPTOR;
		plds[i] = pl_open(
			PL_UNIT_TESTS_APPLICATION_NAME, 
			PL_UNIT_TESTS_COUNTERS_COUNT, 
			counters, 
			&uuid
		);
		err = plt_get_last_error();

		//-----------------------------------------------------------------------
		// display test result
		//-----------------------------------------------------------------------
		if(i != 0) { 
			PLT_PRINT_FILLER; 
		}
		plt_print_pld(
			plt_assert_pld_not_equal(
				plds[i], 
				PL_INVALID_DESCRIPTOR
			)
		);
		plt_print_error(
			plt_assert_error_equal(
				err, 
				PL_NO_ERROR
			)
		);
		plt_print_test(
			"pl_open", 
			"pld", 
			"PL_MAX_PRODUCTIVITY_LINKS", 
			"SUCCESS", 
			"PL_SUCCESS", 
			"PL_NO_ERROR", 
			i
		);
	} // for i

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	for(i = 0; i < PL_MAX_PRODUCTIVITY_LINKS; i++) {
		if(plds[i] != PL_INVALID_DESCRIPTOR) {
			ret = pl_close(plds[i]);
			assert(ret == PL_SUCCESS);
		}
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_MAX_PLUS_1_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTE...
          RS_PER_LINK_success_PL_SUCCESS
Purpose : check pl_open failure (with pl BETWEEN_0_AND_PL_MAX_COUNTERS_PE...
          R_LINK)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_MAX_PLUS_1_pld_in_range_BETWEEN_0_AND_PL_MAX_COUNTERS_PER_LINK_failure_PL_DESCRIPTOR_TABLE_FULL(void) {
	
	int i = 0;
	PL_STATUS ret = PL_FAILURE;
	PL_ERROR err = PL_NO_ERROR;
	int plds[PL_MAX_PRODUCTIVITY_LINKS + 1] = { PL_INVALID_DESCRIPTOR };
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open PL_MAX_PRODUCTIVITY_LINKS PLs
	//-----------------------------------------------------------------------
	for(i = 0; i < PL_MAX_PRODUCTIVITY_LINKS; i++) {
		plds[i] = PL_INVALID_DESCRIPTOR;
		plds[i] = pl_open(
			PL_UNIT_TESTS_APPLICATION_NAME, 
			PL_UNIT_TESTS_COUNTERS_COUNT, 
			counters, 
			&uuid
		);
		assert(plds[i] != PL_INVALID_DESCRIPTOR);
	}

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	plds[i] =  PL_INVALID_DESCRIPTOR;
	plds[i] = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
	plt_print_pld(
		plt_assert_pld_not_equal(
			plds[i], 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_open", 
		"pld", 
		"PL_MAX_PRODUCTIVITY_LINKS + 1", 
		"SUCCESS", 
		"PL_NO_ERROR -- DYNAMIC", 
		"PL_NO_ERROR", 
		i
	);
#else // __PL_DYNAMIC_TABLE_ALLOCATION__
	plt_print_pld(
		plt_assert_pld_equal(
			plds[i], 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_DESCRIPTOR_TABLE_FULL
		)
	);
	plt_print_test(
		"pl_open", 
		"pld", 
		"PL_MAX_PRODUCTIVITY_LINKS + 1", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_DESCRIPTOR_TABLE_FULL", 
		i
	);
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
	for(i = 0; i <= PL_MAX_PRODUCTIVITY_LINKS; i++) {
#else // __PL_DYNAMIC_TABLE_ALLOCATION__ 
	for(i = 0; i < PL_MAX_PRODUCTIVITY_LINKS; i++) {
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
		if(plds[i] != PL_INVALID_DESCRIPTOR) {
			ret = pl_close(plds[i]);
			assert(ret == PL_SUCCESS);
		}
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_application_name_NULL_success_PL_SUCCESS
Purpose : check application name is NULL
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_application_name_NULL_success_PL_SUCCESS(void) {
	
	PL_STATUS ret = PL_FAILURE;
	PL_ERROR err = PL_NO_ERROR;
	int pld = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char buffer[PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		NULL, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// check counter names
	//-----------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE
	);
	plt_tools_get_pl_application_name(buffer);
#ifdef __PL_UNDEF_T__
	#undef _T
	#define _T(x) (x)
#endif // __PL_UNDEF_T__
	if(
		strncmp(
			buffer, 
			PL_UNIT_TESTS_ANONYMOUS_APPLICATION_NAME, 
			strlen(PL_UNIT_TESTS_ANONYMOUS_APPLICATION_NAME)
		) != 0
	) {
		ret = PL_FAILURE;
	}
#ifdef __PL_UNDEF_T__
	#undef _T
	#define _T(x) __T(x)
#endif // __PL_UNDEF_T__

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_open", 
		"application name", 
		"PRE_DEFINED_ANONYMOUS_APPLICATION_NAME", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_pl_application_name_illegal_char_failure_PL_INVALID_...
          PARAMETERS
Purpose : check pl_open failure (with pl_application_name with illegal char...
          acter)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari            Creation.
*/
void plt_pl_open_pl_application_name_illegal_char_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_NULL_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME_1_ILLEGAL_CHAR, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_application_name", 
		"illegal char", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_pl_counter_name_illegal_char_failure_PL_INVALID_PAR...
          AMETERS
Purpose : check pl_open failure (with pl_counter_name with illegal character)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_open_pl_counter_name_illegal_char_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_ILLEGAL_CHAR_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME_1_ILLEGAL_CHAR, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_counter_name", 
		"illegal char", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_pl_application_name_length_greater_than_PL_MAX_PATH...
          _failure_PL_INVALID_PARAMETERS
Purpose : check pl_open failure (with pl_application_name length greater...
          than PL_MAX_PATH)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_open_pl_application_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME_LENGTH_GREATER_THAN_PL_MAX_PATH, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_application_name", 
		"greater than PL_MAX_PATH", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_pl_counter_name_length_greater_than_PL_MAX_PATH_fail..
          ure_PL_INVALID_PARAMETERS
Purpose : check pl_open failure (with pl_counter_name length greater than...
          PL_MAX_PATH)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_open_pl_counter_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAME_LENGTH_GREATER_THAN_PL_MAX_PATH_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_open", 
		"pl_counter_name", 
		"greater than PL_MAX_PATH", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_application_name_NOT_NULL_success_PL_SUCCESS
Purpose : check application name (with pre-defined one in unit_tests_frame...
          work.h)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_application_name_NOT_NULL_success_PL_SUCCESS(void) {
	
	PL_STATUS ret = PL_FAILURE;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	int pld = PL_INVALID_DESCRIPTOR;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_NULL_COUNTER_NAMES
	;
	char buffer[PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// check counter names
	//-----------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE
	);
	plt_tools_get_pl_application_name(buffer);
	if(
		strncmp(
			buffer, 
			PL_UNIT_TESTS_APPLICATION_NAME, 
			strlen(PL_UNIT_TESTS_APPLICATION_NAME)
		) != 0
	) {
		ret = PL_FAILURE;
	}

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_open", 
		"application name", 
		"PRE_DEFINED_APPLICATION_NAME", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_counter_names_NULL_success_PL_SUCCESS
Purpose : check all counters name are NULL
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_counter_names_NULL_success_PL_SUCCESS(void) {
	
	int i = 0;
	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_FAILURE;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	char *reference_counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_ANONYMOUS_COUNTER_NAMES
	;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_NULL_COUNTER_NAMES
	;
	char buffer[PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// check counter names
	//-----------------------------------------------------------------------
	for(i = 0, ret = PL_SUCCESS; i < PL_UNIT_TESTS_COUNTERS_COUNT; i++) {
		memset(
			buffer, 
			0, 
			PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE
		);
		plt_tools_get_pl_counter_name(
			i, 
			buffer
		);
		if(
			strncmp(
				buffer, 
				reference_counters[i], 
				strlen(reference_counters[i])
			) != 0
		) {
			ret = PL_FAILURE;
		}
	}

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_open", 
		"counter(s) names", 
		"PRE_DEFINED_ANONYMOUS_NAMES", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_open_counter_names_NOT_NULL_success_PL_SUCCESS
Purpose : check all counters name (with pre-defined ones in unit_tests_fr...
          amework.h)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_open_counter_names_NOT_NULL_success_PL_SUCCESS(void) {
	
	int i = 0;
	PL_STATUS ret = PL_FAILURE;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	int pld = PL_INVALID_DESCRIPTOR;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char buffer[PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// check counter names
	//-----------------------------------------------------------------------
	for(i = 0, ret = PL_SUCCESS; i < PL_UNIT_TESTS_COUNTERS_COUNT; i++) {
		memset(
			buffer, 
			0, 
			PLT_TOOLS_COUNTER_NAME_BUFFER_SIZE
		);
		plt_tools_get_pl_counter_name(
			i, 
			buffer
		);
		if(
			strncmp(
				buffer, 
				counters[i], 
				strlen(counters[i])
			) != 0
		) {
			ret = PL_FAILURE;
		}
	}

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_open", 
		"counter(s) names", 
		"PRE_DEFINED_NAMES", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

//---------------------------------------------------------------------------

/*
@@@@@  @              @@@@  @       @@@@   @@@@  @@@@@@
@    @ @             @    @ @      @    @ @    @ @
@    @ @             @      @      @    @ @      @
@@@@@  @             @      @      @    @  @@@@  @@@@@@
@      @             @      @      @    @      @ @
@      @             @    @ @      @    @      @ @
@      @@@@@@         @@@@  @@@@@@  @@@@  @@@@@  @@@@@@
              @@@@@@
*/
/*---------------------------------------------------------------------------
Function: plt_pl_close_pl_table_not_initialized_failure_PL_DESCRIPTOR_TAB...
          LE_UNINITIALIZED
Purpose : check pl_close failure (with PL_DESCRIPTOR_TABLE_UNINITIALIZED)...
          when pl table
          is not initialized
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_pl_close_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
#ifdef __PL_WINDOWS__
	BOOL old_pl_table_initialized = FALSE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int old_pl_table_initialized = 0;
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-----------------------------------------------------------------------
	// save pl table itialized state
	//-----------------------------------------------------------------------
	old_pl_table_initialized = plt_tools_get_pl_table_state();

	//-----------------------------------------------------------------------
	// set pl table as uninitialized
	//-----------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	plt_tools_set_pl_table_state(FALSE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	plt_tools_set_pl_table_state(0);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		
	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_close(pld);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_DESCRIPTOR_TABLE_UNINITIALIZED
		)
	);
	plt_print_test(
		"pl_close", 
		"pl_table_initialized", 
		"FALSE", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_DESCRIPTOR_TABLE_UNINITIALIZED", 
		0
	);

	//-----------------------------------------------------------------------
	// restore pl table itialized state
	//-----------------------------------------------------------------------
	plt_tools_set_pl_table_state(old_pl_table_initialized);
}

/*---------------------------------------------------------------------------
Function: plt_pl_close_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAM...
          ETERS
Purpose : check pl_close failure (with PL_INVALID_PARAMETERS) when pld is
          equal to PL_INVALID_DESCRIPTOR
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_pl_close_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(void) {
	
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters,
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_close(pld);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_close", 
		"pld", 
		"PL_INVALID_DESCRIPTOR", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pldx != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pldx);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_close_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVAL...
          ID_PARAMETERS
Purpose : check pl_close failure (with < 0 pld)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_pl_close_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = -1;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_close(pld);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_close", 
		"pld", 
		"LOWER_THAN_0_PLD", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pldx != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pldx);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_close_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_...
          LINKS_PLD_failure_PL_INVALID_PARAMETERS
Purpose : check pl_close failure (with >= PL_MAX_PRODUCTIVITY_LINKS pld)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_pl_close_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(void) {

	int pldx = PL_INVALID_DESCRIPTOR;
#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
	int pld = 2 * PL_MAX_PRODUCTIVITY_LINKS; // table expanded in unit test 12
#else // // __PL_DYNAMIC_TABLE_ALLOCATION__
	int pld = PL_MAX_PRODUCTIVITY_LINKS;
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_close(pld);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_close", 
		"pld", 
		"HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pldx != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pldx);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_close_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LIN...
          KS_PLD_success_PL_SUCCESS
Purpose : check pl_close success (with in-range pld)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/01/2009    Jamel Tayeb             Creation.
*/
void plt_pl_close_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_PLD_success_PL_SUCCESS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_close(pld);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_close", 
		"pld", 
		"BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_PLD", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);
}

//---------------------------------------------------------------------------

/*
@@@@@  @               @@    @@@@@  @@@@@   @@    @@@@  @    @
@    @ @              @  @     @      @    @  @  @    @ @    @
@    @ @             @    @    @      @   @    @ @      @    @
@@@@@  @             @    @    @      @   @    @ @      @@@@@@
@      @             @@@@@@    @      @   @@@@@@ @      @    @
@      @             @    @    @      @   @    @ @    @ @    @
@      @@@@@@        @    @    @      @   @    @  @@@@  @    @
              @@@@@@
*/
/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_NULL_failure_PL_INVALID_PARAMETERS
Purpose : check pl_attach fails (with NULL pl_config.ini)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_NULL_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(NULL);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_pld_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pld", 
		"NULL", 
		"FAILURE", 
		"PL_INVALID_DESCRIPTOR", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_DOESNT_EXIST_failure_PL_CONFIG_FILE_OPE...
          NING_FAILED
Purpose : ckeck pl_attach fails (with non existing pl_config.ini)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_DOESNT_EXIST_failure_PL_CONFIG_FILE_OPENING_FAILED(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(PL_UNIT_TESTS_NON_EXISTING_PL_CONFIG_NAME);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_pld_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_CONFIG_FILE_OPENING_FAILED
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config", 
		"DOESN'T EXIST", 
		"FAILURE", 
		"PL_INVALID_DESCRIPTOR", 
		"PL_CONFIG_FILE_OPENING_FAILED", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_EXIST_success_PL_SUCCESS
Purpose : check pl_attach success (with valid pl_config.ini)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_EXIST_success_PL_SUCCESS(void) {
	
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_pld_not_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config", 
		"DOES EXIST", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
	if(pldx != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pldx);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_file_name_length_greater_than_PL_MAX_PA...
          TH_failure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config file name length greater..
          than PL_MAX_PATH)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_attach_pl_config_file_name_length_greater_than_PL_MAX_PATH_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	
	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(
		PL_CONFIG_FILE_NAME_GREATER_THAN_PL_MAX_PATH
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file_name_length", 
		"greater_than_PL_MAX_PATH", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_file_name_pl_folder_not_present_failure...
          _PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config file name where PL_FOLDER..
          is not present)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_attach_pl_config_file_name_pl_folder_not_present_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	
	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(
		PL_CONFIG_FILE_NAME_PL_FOLDER_NOT_PRESENT
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file_name", 
		"pl_folder_not_present", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_file_name_pl_folder_name_incorrect_fa...
          ilure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config file name with incorre...
          ct PL_FOLDER name)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_attach_pl_config_file_name_pl_folder_name_incorrect_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	
	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(
		PL_CONFIG_FILE_NAME_PL_FOLDER_NAME_INCORRECT
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file_name", 
		"pl_folder_name_incorrect", 
		"FAILURE", 
		"PL_FAILURE",
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_file_name_not_present_failure_PL_INVAL...
          ID_PARAMETERS
Purpose : check pl_attach failure (with pl_config file name not present)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_attach_pl_config_file_name_not_present_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	
	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(
		PL_CONFIG_FILE_NAME_NOT_PRESENT
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file_name", 
		"not present", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_file_name_UUID_three_dashes_failure_PL_...
          INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config file name with UUID con...
          taining three dashes)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_attach_pl_config_file_name_UUID_three_dashes_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	
	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(
		PL_CONFIG_FILE_NAME_UUID_THREE_DASHES
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file_name", 
		"UUID with three dashes", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_file_name_UUID_invalid_character_failu...
          re_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config file name with UUID conta...
          ining illegal character)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/01/2010    Sree Syamalakumari             Creation.
*/
void plt_pl_attach_pl_config_file_name_UUID_invalid_character_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	
	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(
		PL_CONFIG_FILE_NAME_UUID_INVALID_CHARACTER
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file_name", 
		"UUID with illegal character", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_count_not_allowed_characters_...
          failure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters cou...
          nt containg not allowed characters)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_count_not_allowed_characters_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);
 
	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte(
		pl_config,
		PL_UNIT_TESTS_COUNTER_COUNT_LINE,
		PL_UNIT_TESTS_COUNTER_COUNT_COLUMN,
		PL_UNIT_TESTS_COUNTER_COUNT_OFFENDING_CHARACTER
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters count with illegal character", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS",
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_count_length_greater_than_PL_...
          MAX_UNSIGNED_INTEGER_STRING_failure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters cou...
          nt length is greater than PL_MAX_UNSIGNED_INTEGER_STRING)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_count_length_greater_than_PL_MAX_UNSIGNED_INTEGER_STRING_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);

	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte_string(
		pl_config,
		PL_UNIT_TESTS_COUNTER_COUNT_LINE,
		PL_UNIT_TESTS_COUNTER_COUNT_COLUMN,
		(unsigned char *)PL_UNIT_TESTS_COUNTER_COUNT_TOO_LONG,
		strlen(PL_UNIT_TESTS_COUNTER_COUNT_TOO_LONG)
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters count greater than PL_MAX_UNSIGNED_INTEGER_STRING", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-------------------------------------------------------------------------
	// close the PLs
	//-------------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*-----------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_name_PL_folder_incorrect_fail...
          ure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters name 
          contains incorrect PL folder)
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_name_PL_folder_incorrect_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);
 
	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte(
		pl_config,
		PL_UNIT_TESTS_COUNTER_PL_FOLDER_NAME_LINE,
		PL_UNIT_TESTS_COUNTER_PL_FOLDER_NAME_COLUMN,
		PL_UNIT_TESTS_COUNTER_PL_FOLDER_NAME_OFFENDING_CHARACTER
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters name with incorrect PL folder", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_name_path_separator_incorrect_f...
          ailure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters name 
          contains incorrect path separator)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_name_path_separator_incorrect_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);
 
	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte(
		pl_config,
		PL_UNIT_TESTS_COUNTER_NAME_PATH_SEPARATOR_LINE,
		PL_UNIT_TESTS_COUNTER_NAME_PATH_SEPARATOR_COLUMN,
		PL_UNIT_TESTS_COUNTER_NAME_OFFENDING_PATH_SEPARATOR_OFFENDING_CHARACTER
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters name with incorrect path separator", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_name_application_name_incorre...
          ct_failure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters name
          contains incorrect application name)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_name_application_name_incorrect_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);
 
	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte(
		pl_config,
		PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_LINE,
		PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_COLUMN,
		PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_OFFENDING_CHARACTER
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters name with incorrect application name", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_name_application_name_invalid_c...
          haracters_failure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters name 
          contains application name with invalid characters)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_name_application_name_invalid_characters_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);
 
	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte(
		pl_config,
		PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_LINE,
		PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_COLUMN,
		PL_UNIT_TESTS_COUNTER_NAME_APPLICATION_NAME_OFFENDING_CHARACTER
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters name with application name invalid characters", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_name_UUID_incorrect_failure_PL_...
          INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters name 
          contains incorrect UUID)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_name_UUID_incorrect_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);
 
	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte(
		pl_config,
		PL_UNIT_TESTS_COUNTER_NAME_UUID_LINE,
		PL_UNIT_TESTS_COUNTER_NAME_UUID_COLUMN,
		PL_UNIT_TESTS_COUNTER_NAME_UUID_OFFENDING_CHARACTER
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters name with incorrect UUID", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS",
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_name_UUID_invalid_format_fail...
          ure_PL_INVALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters name 
          contains invalid UUID format)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_name_UUID_invalid_format_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);
 
	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte(
		pl_config,
		PL_UNIT_TESTS_COUNTER_NAME_UUID_LINE,
		PL_UNIT_TESTS_COUNTER_NAME_UUID_COLUMN,
		PL_UNIT_TESTS_COUNTER_NAME_UUID_OFFENDING_CHARACTER
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters name with invalid UUID format", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_file_from_linux_success_PL_SUCCESS
Purpose : check pl_attach success (with pl_config.ini created on a 
          remote system requiering PL_FOLDER substitution)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
11/29/2010   Jamel Tayeb              Creation.
*/
void plt_pl_attach_pl_config_file_from_remote_success_PL_SUCCESS(void) {

	int ret = -1;
	int pld = PL_INVALID_DESCRIPTOR;
	PL_ERROR err = PL_NO_ERROR;
	FILE* pl_config_file = NULL;
	size_t bytes_to_write = 0;
	size_t bytes_written = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// save remote PL_CONGIG ini file and create counter files
	//-----------------------------------------------------------------------
	ret = system(PL_UNIT_TESTS_CREATE_PL_CONFIG_FILE_REMOTE_FOLDER);
	assert(ret != -1);
	pl_config_file = fopen(
		PL_CONFIG_FILE_REMOTE, 
		"w"
	);
	assert(pl_config_file != NULL);
	bytes_to_write = strlen(PL_CONFIG_FILE_REMOTE_CONTENT);
	bytes_written = fwrite(
		PL_CONFIG_FILE_REMOTE_CONTENT, 
		sizeof(char), 
		bytes_to_write, 
		pl_config_file
	);
	assert(bytes_written == bytes_to_write);
	ret = fclose(pl_config_file);
	assert(ret == 0);
	pl_config_file = fopen(
		PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_0, 
		"w"
	);
	assert(pl_config_file != NULL);
	ret = fclose(pl_config_file);
	assert(ret == 0);
	pl_config_file = fopen(
		PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_1, 
		"w"
	);
	assert(pl_config_file != NULL);
	ret = fclose(pl_config_file);
	assert(ret == 0);
	pl_config_file = fopen(
		PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_2, 
		"w"
	);
	assert(pl_config_file != NULL);
	ret = fclose(pl_config_file);
	assert(ret == 0);
	pl_config_file = fopen(
		PL_CONFIG_FILE_REMOTE_COUNTER_FILE_NAME_3, 
		"w"
	);
	assert(pl_config_file != NULL);
	ret = fclose(pl_config_file);
	assert(ret == 0);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(PL_CONFIG_FILE_REMOTE);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(plt_assert_pld_not_equal(pld, PL_INVALID_DESCRIPTOR));
	plt_print_error(plt_assert_error_equal(err, PL_NO_ERROR));
#ifdef __PL_WINDOWS__
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"from *NIX", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"from Windows", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		0
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_attach_pl_config_counters_count_incorrect_failure_PL_INV...
          ALID_PARAMETERS
Purpose : check pl_attach failure (with pl_config.ini where counters count
          is incorrect)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/04/2009    Jamel Tayeb             Creation.
*/
void plt_pl_attach_pl_config_counters_count_incorrect_failure_PL_INVALID_PARAMETERS(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	int pldx = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	char pl_config[PL_MAX_PATH] = { '\0' };

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pldx = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pldx != PL_INVALID_DESCRIPTOR);
	ret = pl_close(pldx);
	assert(ret == PL_SUCCESS);
 
	//-----------------------------------------------------------------------
	// get pl_config.ini for the PL
	//-----------------------------------------------------------------------
	memset(
		pl_config, 
		0, 
		sizeof(pl_config)
	);
	plt_tools_get_pl_config_full_file_name(pl_config);

	//-----------------------------------------------------------------------
	// change the characters in counter count
	//-----------------------------------------------------------------------
	ptl_replace_byte_in_file_with_byte(
		pl_config,
		PL_UNIT_TESTS_COUNTER_COUNT_LINE,
		PL_UNIT_TESTS_COUNTER_COUNT_COLUMN,
		(unsigned char)(PL_UNIT_TESTS_COUNTERS_COUNT + 1)
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	pld = pl_attach(pl_config);
	err = plt_get_last_error();
	
	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_pld(
		plt_assert_status_equal(
			pld, 
			PL_INVALID_DESCRIPTOR
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_attach", 
		"pl_config_file", 
		"counters count incorrect", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PLs
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

//---------------------------------------------------------------------------

/*
@@@@@  @             @@@@@  @@@@@@   @@   @@@@@
@    @ @             @    @ @       @  @  @    @
@    @ @             @    @ @      @    @ @    @
@@@@@  @             @@@@@  @@@@@@ @    @ @    @
@      @             @  @   @      @@@@@@ @    @
@      @             @   @  @      @    @ @    @
@      @@@@@@        @    @ @@@@@@ @    @ @@@@@
              @@@@@@
*/
/*---------------------------------------------------------------------------
Function: plt_pl_read_pl_table_not_initialized_failure_PL_DESCRIPTOR_TAB...
          LE_UNINITIALIZED
Purpose : check pl_read failure (with pl table not initialized)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	unsigned long long v = 0;
#ifdef __PL_WINDOWS__
	BOOL old_pl_table_initialized = FALSE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int old_pl_table_initialized = 0;
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-----------------------------------------------------------------------
	// save pl table itialized state
	//-----------------------------------------------------------------------
	old_pl_table_initialized = plt_tools_get_pl_table_state();

	//-----------------------------------------------------------------------
	// set pl table as uninitialized
	//-----------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	plt_tools_set_pl_table_state(FALSE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	plt_tools_set_pl_table_state(0);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		
	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_DESCRIPTOR_TABLE_UNINITIALIZED
		)
	);
	plt_print_test(
		"pl_read", 
		"pl_table_initialized", 
		"FALSE", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_DESCRIPTOR_TABLE_UNINITIALIZED", 
		0
	);

	//-----------------------------------------------------------------------
	// restore pl table itialized state
	//-----------------------------------------------------------------------
	plt_tools_set_pl_table_state(old_pl_table_initialized);
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS
Purpose : check pl_read failure (with pld is PL_INVALID_DESCRIPTOR)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_read", 
		"pld", 
		"PL_INVALID_DESCRIPTOR", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVAL...
          ID_PARAMETERS
Purpose : check pl_read failure (with pld lower than 0) 
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(void) {

	int pld = -1;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_read", 
		"pld", 
		"LOWER_THAN_0", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LIN...
          KS_PLD_failure_PL_INVALID_PARAMETERS
Purpose : check pl_read failure (with pld higher than PL_MAX_PRODUCTIVITY_L...
          INKS)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_MAX_PRODUCTIVITY_LINKS + 1;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_read", 
		"pld", 
		"HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_p_NULL_failure_PL_INVALID_PARAMETERS
Purpose : check pl_read failure (with p NULL)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_p_NULL_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		NULL, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_read", 
		"p", 
		"NULL", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_counter_out_of_range_LOWER_THAN_0_failure_PL_INVALI...
          D_PARAMETERS
Purpose : check pl_read failure (with counter index LOWER_THAN_0)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_counter_out_of_range_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		-1
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_read", 
		"counter", 
		"LOWER_THAN_0", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_counter_out_of_range_HIGHER_THAN_PL_MAX_COUNTERS_PE...
          R_LINK_failure_PL_INVALID_PARAMETERS
Purpose : check pl_read failure (with counter index HIGHER_THAN_PL_MAX_COUN...
          TERS_PER_LINK)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_counter_out_of_range_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		PL_MAX_COUNTERS_PER_LINK + 1
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_read", 
		"counter", 
		"HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_counter_out_of_range_HIGHER_THAN_ACTUAL_COUNTERS...
          _IN_PL_failure_PL_INVALID_PARAMETERS
Purpose : check pl_read failure (with counter index HIGHER_THAN_ACTUAL_CO...
          UNTERS_IN_PL)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_counter_out_of_range_HIGHER_THAN_ACTUAL_COUNTERS_IN_PL_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned int count = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// get actual counters count for the PL
	//-----------------------------------------------------------------------
	count = plt_tools_get_pl_counter_counts();
	assert(count > 0);
	assert(count <= PL_MAX_COUNTERS_PER_LINK);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		count + 1
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_read", 
		"counter", 
		"HIGHER_THAN_ACTUAL_COUNTERS_IN_PL", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_...
          LINKS_success_PL_SUCCESS
Purpose : check pl_read success (with pld BETWEEN_0_AND_PL_MAX_PROD...
          UCTIVITY_LINKS)
          NOTE: does PL_UNIT_TESTS_COUNTERS_COUNT tests with PL_UNIT_TES...
		  TS_COUNTERS_COUNT representative values 
		  (defined in unit_tests_framework.h)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(void) {

	int i = 0;
	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned long long ref_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	for(i = 0; i < PL_UNIT_TESTS_COUNTERS_COUNT; i++) {

		//-----------------------------------------------------------------------
		// write values into PL
		//-----------------------------------------------------------------------
		plt_tools_set_pl_counter_value(i);

		//-----------------------------------------------------------------------
		// *** test ***
		//-----------------------------------------------------------------------
		ret = pl_read(
			pld, 
			&v, 
			i
		);
		assert(v == ref_values[i]);
		err = plt_get_last_error();

		//-----------------------------------------------------------------------
		// display test result
		//-----------------------------------------------------------------------
		if(i != 0) { 
			PLT_PRINT_FILLER; 
		}
		plt_print_status(
			plt_assert_status_equal(
				ret, 
				PL_SUCCESS
			)
		);
		plt_print_error(
			plt_assert_error_equal(
				err, 
				PL_NO_ERROR
			)
		);
		plt_print_test(
			"pl_read", 
			"pld", 
			"BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS", 
			"SUCCESS", 
			"PL_SUCCESS", 
			"PL_NO_ERROR", 
			ref_values[i]
		);
	}

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_p_VALID_ADDRESS_AND_MAX_COUNTER_VALUE_success_PL_...
          SUCCESS
Purpose : check pl_read success (with value = PL_MAX_COUNTER_VALUE)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_p_VALID_ADDRESS_AND_MAX_COUNTER_VALUE_success_PL_SUCCESS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned long long ref_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// write values into PL
	//-----------------------------------------------------------------------
	plt_tools_set_pl_counter_value(
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MAX_VALUE_INDEX
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MAX_VALUE_INDEX
	);
	assert(v == ref_values[PL_UNIT_TESTS_COUNTER_TEST_VALUES_MAX_VALUE_INDEX]);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_read", 
		"*p", 
		"PL_MAX_COUNTER_VALUE", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		ref_values[PL_UNIT_TESTS_COUNTER_TEST_VALUES_MAX_VALUE_INDEX]
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_success_PL...
          _SUCCESS
Purpose : check pl_read success (with value = 0)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/05/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_success_PL_SUCCESS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned long long ref_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// write values into PL
	//-----------------------------------------------------------------------
	plt_tools_set_pl_counter_value(
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX
	);
	assert(v == ref_values[PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX]);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_NO_ERROR
		)
	);
	plt_print_test(
		"pl_read",
		"*p", 
		"0 (a.k.a. PL_MIN_COUNTER_VALUE", 
		"SUCCESS",
		"PL_SUCCESS",
		"PL_NO_ERROR", 
		ref_values[PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX]
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_CORRUPT_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VA...
          LUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE
Purpose : check pl_read failure (with corrupt data)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_CORRUPT_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// write values into PL
	//-----------------------------------------------------------------------
	plt_tools_set_pl_corrupt_counter_file_value(0);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_COUNTER_VALUE_OUT_OF_RANGE
		)
	);
	plt_print_test(
		"pl_read", 
		"counter data", 
		"CORRUPT DATA", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_COUNTER_VALUE_OUT_OF_RANGE", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_read_OVERFLOW_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VAL...
          UE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE
Purpose : check pl_read failure (with overflow data)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_read_OVERFLOW_DATA_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_failure_PL_COUNTER_VALUE_OUT_OF_RANGE(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// write values into PL
	//-----------------------------------------------------------------------
	plt_tools_set_pl_overflow_counter_value(0);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_read(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_COUNTER_VALUE_OUT_OF_RANGE
		)
	);
	plt_print_test(
		"pl_read",
		"counter data", 
		"OVERFLOW DATA", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_COUNTER_VALUE_OUT_OF_RANGE", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

//---------------------------------------------------------------------------

/*
@@@@@  @             @    @ @@@@@  @@@@@   @@@@@ @@@@@@
@    @ @             @    @ @    @   @       @   @
@    @ @             @  @ @ @    @   @       @   @
@@@@@  @             @  @ @ @@@@@    @       @   @@@@@@
@      @             @  @ @ @  @     @       @   @
@      @              @ @ @ @   @    @       @   @
@      @@@@@@          @ @  @    @ @@@@@     @   @@@@@@
              @@@@@@
*/
/*---------------------------------------------------------------------------
Function: plt_pl_write_pl_table_not_initialized_failure_PL_DESCRIPTO...
          R_TABLE_UNINITIALIZED
Purpose : check pl_write failure (with pl table not initialized)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_pl_table_not_initialized_failure_PL_DESCRIPTOR_TABLE_UNINITIALIZED(void) {
	
	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	unsigned long long v = 0;
#ifdef __PL_WINDOWS__
	BOOL old_pl_table_initialized = FALSE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int old_pl_table_initialized = 0;
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-----------------------------------------------------------------------
	// save pl table itialized state
	//-----------------------------------------------------------------------
	old_pl_table_initialized = plt_tools_get_pl_table_state();

	//-----------------------------------------------------------------------
	// set pl table as uninitialized
	//-----------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	plt_tools_set_pl_table_state(FALSE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	plt_tools_set_pl_table_state(0);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		
	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_DESCRIPTOR_TABLE_UNINITIALIZED
		)
	);
	plt_print_test(
		"pl_write", 
		"pl_table_initialized", 
		"FALSE", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_DESCRIPTOR_TABLE_UNINITIALIZED", 
		0
	);

	//-----------------------------------------------------------------------
	// restore pl table itialized state
	//-----------------------------------------------------------------------
	plt_tools_set_pl_table_state(old_pl_table_initialized);
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PAR...
          AMETERS
Purpose : check pl_write failure (with pld is PL_INVALID_DESCRIPTOR)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_pld_PL_INVALID_DESCRIPTOR_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_write",
		"pld", 
		"PL_INVALID_DESCRIPTOR", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INV...
          ALID_PARAMETERS
Purpose : check pl_write failure (with pld lower than 0)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_pld_out_of_range_LOWER_THAN_0_PLD_failure_PL_INVALID_PARAMETERS(void) {

	int pld = -1;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_write", 
		"pld", 
		"LOWER_THAN_0", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY...
          _LINKS_PLD_failure_PL_INVALID_PARAMETERS
Purpose : check pl_write failure (with pld higher than PL_MAX_PRODUCTIV...
          ITY_LINKS)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_pld_out_of_range_HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS_PLD_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_MAX_PRODUCTIVITY_LINKS + 1;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		&v, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_write", 
		"pld", 
		"HIGHER_THAN_PL_MAX_PRODUCTIVITY_LINKS", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_p_NULL_failure_PL_INVALID_PARAMETERS
Purpose : check pl_write failure (with p NULL)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_p_NULL_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		NULL, 
		0
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_write", 
		"p", 
		"NULL", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_counter_out_of_range_LOWER_THAN_0_failure_PL_INV...
          ALID_PARAMETERS
Purpose : check pl_write failure (with counter index LOWER_THAN_0)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_counter_out_of_range_LOWER_THAN_0_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		&v, 
		-1
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_write", 
		"counter", 
		"LOWER_THAN_0", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS",
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_counter_out_of_range_HIGHER_THAN_PL_MAX_COUNTERS_...
          PER_LINK_failure_PL_INVALID_PARAMETERS
Purpose : check pl_write failure (with counter index HIGHER_THAN_PL_MAX_C...
          OUNTERS_PER_LINK)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_counter_out_of_range_HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		&v, 
		PL_MAX_COUNTERS_PER_LINK + 1
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_write", 
		"counter", 
		"HIGHER_THAN_PL_MAX_COUNTERS_PER_LINK", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_counter_out_of_range_HIGHER_THAN_ACTUAL_COUNTER...
          S_IN_PL_failure_PL_INVALID_PARAMETERS
Purpose : check pl_write failure (with counter index HIGHER_THAN_ACTUAL_C...
          OUNTERS_IN_PL)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_counter_out_of_range_HIGHER_THAN_ACTUAL_COUNTERS_IN_PL_failure_PL_INVALID_PARAMETERS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned int count = 0;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// get actual counters count for the PL
	//-----------------------------------------------------------------------
	count = plt_tools_get_pl_counter_counts();
	assert(count > 0);
	assert(count <= PL_MAX_COUNTERS_PER_LINK);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		&v, 
		count + 1
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_FAILURE
		)
	);
	plt_print_error(
		plt_assert_error_equal(
			err, 
			PL_INVALID_PARAMETERS
		)
	);
	plt_print_test(
		"pl_write", 
		"counter", 
		"HIGHER_THAN_ACTUAL_COUNTERS_IN_PL", 
		"FAILURE", 
		"PL_FAILURE", 
		"PL_INVALID_PARAMETERS", 
		0
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_...
          LINKS_success_PL_SUCCESS
Purpose : check pl_read success (with pld BETWEEN_0_AND_PL_MAX_PRODUCTIV...
          ITY_LINKS)
          NOTE: does PL_UNIT_TESTS_COUNTERS_COUNT tests with PL_UNIT_T...
		  ESTS_COUNTERS_COUNT representative values 
		  (defined in unit_tests_framework.h)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(void) {

	int i = 0;
	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned long long rv = 0;
	unsigned long long ref_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	for(i = 0; i < PL_UNIT_TESTS_COUNTERS_COUNT; i++) {

		//-----------------------------------------------------------------------
		// set for cache miss
		//-----------------------------------------------------------------------
		plt_tools_set_pl_counter_write_cache_miss(i);
		v = ref_values[i];

		//-----------------------------------------------------------------------
		// *** test ***
		//-----------------------------------------------------------------------
		ret = pl_write(
			pld, 
			&v, 
			i
		);
		err = plt_get_last_error();

		//-----------------------------------------------------------------------
		// check write
		//-----------------------------------------------------------------------
		rv = plt_tools_get_pl_counter_value(i);
		assert(rv == v);

		//-----------------------------------------------------------------------
		// display test result
		//-----------------------------------------------------------------------
		if(i != 0) { 
			PLT_PRINT_FILLER; 
		}
		plt_print_status(
			plt_assert_status_equal(
				ret, 
				PL_SUCCESS
			)
		);
		plt_print_error(
			plt_assert_error_equal_tristate(
				err, 
				PL_NO_ERROR, 
				PL_COUNTER_WRITE_CACHE_HIT, 
				PL_COUNTER_WRITE_CACHE_MISS
			)
		);
		plt_print_test(
			"pl_write", 
			"pld", 
			"BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS", 
			"SUCCESS", 
			"PL_SUCCESS", 
			"PL_NO_ERROR", 
			ref_values[i]
		);
	}

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_p_VALID_ADDRESS_AND_MAX_COUNTER_VALUE_success_...
          PL_SUCCESS
Purpose : check pl_write success (with value = PL_MAX_COUNTER_VALUE)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_p_VALID_ADDRESS_AND_MAX_COUNTER_VALUE_success_PL_SUCCESS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned long long rv = 1;
	unsigned long long ref_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld, 
		&v, 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MAX_VALUE_INDEX
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// check write
	//-----------------------------------------------------------------------
	rv = plt_tools_get_pl_counter_value(
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MAX_VALUE_INDEX
	);
	assert(rv == v);

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal_tristate(
			err, 
			PL_NO_ERROR, 
			PL_COUNTER_WRITE_CACHE_HIT, 
			PL_COUNTER_WRITE_CACHE_MISS
		)
	);
	plt_print_test(
		"pl_write", 
		"*p", 
		"PL_MAX_COUNTER_VALUE", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		ref_values[PL_UNIT_TESTS_COUNTER_TEST_VALUES_MAX_VALUE_INDEX]
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_success_P...
          L_SUCCESS
Purpose : check pl_write success (with value = 0)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_p_VALID_ADDRESS_AND_MIN_COUNTER_VALUE_success_PL_SUCCESS(void) {

	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned long long rv = 1;
	unsigned long long ref_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-----------------------------------------------------------------------
	// write values into PL
	//-----------------------------------------------------------------------
	plt_tools_set_pl_counter_value(
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX
	);

	//-----------------------------------------------------------------------
	// *** test ***
	//-----------------------------------------------------------------------
	ret = pl_write(
		pld,
		&v, 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX
	);
	err = plt_get_last_error();

	//-----------------------------------------------------------------------
	// check write
	//-----------------------------------------------------------------------
	rv = plt_tools_get_pl_counter_value(
		PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX
	);
	assert(rv == v);

	//-----------------------------------------------------------------------
	// display test result
	//-----------------------------------------------------------------------
	plt_print_status(
		plt_assert_status_equal(
			ret, 
			PL_SUCCESS
		)
	);
	plt_print_error(
		plt_assert_error_equal_tristate(
			err, 
			PL_NO_ERROR, 
			PL_COUNTER_WRITE_CACHE_HIT, 
			PL_COUNTER_WRITE_CACHE_MISS
		)
	);
	plt_print_test(
		"pl_write", 
		"*p", 
		"0 (a.k.a. PL_MIN_COUNTER_VALUE", 
		"SUCCESS", 
		"PL_SUCCESS", 
		"PL_NO_ERROR", 
		ref_values[PL_UNIT_TESTS_COUNTER_TEST_VALUES_MIN_VALUE_INDEX]
	);

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_CACHED_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIV...
          ITY_LINKS_success_PL_SUCCESS
Purpose : check pl_write success (with error code = PL_COUNTER_WRITE_CA...
          CHE_HIT)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_CACHED_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(void) {

	int i = 0;
	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned long long ref_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	for(i = 0; i < PL_UNIT_TESTS_COUNTERS_COUNT; i++) {

		//-----------------------------------------------------------------------
		// set for cache hit
		//-----------------------------------------------------------------------
		plt_tools_set_pl_counter_write_cache_hit(i);
		v = ref_values[i];

		//-----------------------------------------------------------------------
		// *** test ***
		//-----------------------------------------------------------------------
		ret = pl_write(
			pld, 
			&v, 
			i
		);
		err = plt_get_last_error();

		//-----------------------------------------------------------------------
		// no read check as write is canceled by cache hit
		//-----------------------------------------------------------------------

		//-----------------------------------------------------------------------
		// display test result
		//-----------------------------------------------------------------------
		if(i != 0) { 
			PLT_PRINT_FILLER; 
		}
		plt_print_status(
			plt_assert_status_equal(
				ret, 
				PL_SUCCESS
			)
		);
		plt_print_error(
			plt_assert_error_equal(
				err, 
				PL_COUNTER_WRITE_CACHE_HIT
			)
		);
		plt_print_test(
			"pl_write", 
			"counter",
			"CACHED-CACHE HIT", 
			"SUCCESS", 
			"PL_SUCCESS", 
			"PL_COUNTER_WRITE_CACHE_HIT", 
			ref_values[i]
		);
	}

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
Function: plt_pl_write_CACHED_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUC...
          TIVITY_LINKS_success_PL_SUCCESS
Purpose : check pl_write success (with error code = PL_COUNTER_WRITE_CA...
          CHE_MISS)
In      : none
Out     : none
Return  : none

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
05/06/2009    Jamel Tayeb             Creation.
*/
void plt_pl_write_NON_CACHED_pld_in_range_BETWEEN_0_AND_PL_MAX_PRODUCTIVITY_LINKS_success_PL_SUCCESS(void) {

	int i = 0;
	int pld = PL_INVALID_DESCRIPTOR;
	PL_STATUS ret = PL_SUCCESS;
	PL_ERROR err = PL_NO_ERROR;
	uuid_t uuid;
	const char *counters[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_APPLICATION_COUNTER_NAMES
	;
	unsigned long long v = 0;
	unsigned long long ref_values[PL_UNIT_TESTS_COUNTERS_COUNT] = 
		PL_UNIT_TESTS_COUNTER_TEST_VALUES
	;

	//-----------------------------------------------------------------------
	// delete PL_FOLDER and re-create it
	//-----------------------------------------------------------------------
	plt_new_pl_folder();

	//-----------------------------------------------------------------------
	// open a PL
	//-----------------------------------------------------------------------
	pld = pl_open(
		PL_UNIT_TESTS_APPLICATION_NAME, 
		PL_UNIT_TESTS_COUNTERS_COUNT, 
		counters, 
		&uuid
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	for(i = 0; i < PL_UNIT_TESTS_COUNTERS_COUNT; i++) {

		//-----------------------------------------------------------------------
		// set for cache miss
		//-----------------------------------------------------------------------
		plt_tools_set_pl_counter_write_cache_miss(i);
		v = ref_values[i];

		//-----------------------------------------------------------------------
		// *** test ***
		//-----------------------------------------------------------------------
		ret = pl_write(
			pld, 
			&v, 
			i
		);
		err = plt_get_last_error();

		//-----------------------------------------------------------------------
		// no read check as write is canceled by cache hit
		//-----------------------------------------------------------------------

		//-----------------------------------------------------------------------
		// display test result
		//-----------------------------------------------------------------------
		if(i != 0) {
			PLT_PRINT_FILLER; 
		}
		plt_print_status(
			plt_assert_status_equal(
				ret, 
				PL_SUCCESS
			)
		);
		plt_print_error(
			plt_assert_error_equal(
				err, 
				PL_COUNTER_WRITE_CACHE_MISS
			)
		);
		plt_print_test(
			"pl_write", 
			"counter", 
			"NON CACHED-CACHE MISS", 
			"SUCCESS", 
			"PL_SUCCESS", 
			"PL_COUNTER_WRITE_CACHE_MISS", 
			ref_values[i]
		);
	}

	//-----------------------------------------------------------------------
	// close the PL
	//-----------------------------------------------------------------------
	if(pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(pld);
		assert(ret == PL_SUCCESS);
	}
}
