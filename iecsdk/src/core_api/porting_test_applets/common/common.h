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

#ifndef __INCLUDE_PRODUCTIVITY_LINK_DEMOS__
#define __INCLUDE_PRODUCTIVITY_LINK_DEMOS__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Counters - producer
//-----------------------------------------------------------------------------
#define APPLICATION_NAME_STRING "producer"
#define MAX_COUNTERS 5
#define COUNTER_STRINGS	{ \
	"performance", \
	NULL, \
	"work_units", \
	NULL, \
	NULL \
}

enum { 
	PERFORMANCE = 0,	
	UNNAMED_1, 
	WORK_UNITS, 
	UNNAMED_2, 
	UNNAMED_3 
};

//-----------------------------------------------------------------------------
// Log - logger
//-----------------------------------------------------------------------------
#define MAX_BUFFER_SIZE 1024
#define LOG_FILE_NAME "logger.csv"

//-----------------------------------------------------------------------------
// Behavior - all
//-----------------------------------------------------------------------------
#define SAMPLES 10
//#define ITERATIONS 100000
#define ITERATIONS 10000
//#define ITERATIONS 1000
//#define ITERATIONS 100
//#define ITERATIONS 10

//-----------------------------------------------------------------------------
// Sampling intervale - all
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#define PAUSE 1000
	//#define PAUSE 0
#endif // __PL__WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	#define PAUSE 1
	//#define PAUSE 0
#endif // __PL__LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PRODUCTIVITY_LINK_DEMOS__
