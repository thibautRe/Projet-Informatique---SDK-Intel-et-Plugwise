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

#ifndef __INCLUDE_ESRV_CPU_INDEXED_SIMULATED_DEVICE__
#define __INCLUDE_ESRV_CPU_INDEXED_SIMULATED_DEVICE__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#include <tchar.h>
	#include <pdh.h>
#endif // __PL_WINDOWS__ 
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include <stdlib.h>
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "pub_esrv.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Power draw definitions.
//-----------------------------------------------------------------------------
#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_DEFAULT_FIXED_POWER_DRAW 60.0
#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_DEFAULT_VARIABLE_POWER_DRAW 40.0
#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_DEFAULT_CPU_POWER_PERCENTAGE 25.0

//-----------------------------------------------------------------------------
// Device option strings definitions.
//-----------------------------------------------------------------------------
#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_OPTIONS_MAX_TOKENS 3
#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_FIXED_POWER "FIXED_POWER"
#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_VARIABLE_POWER "VARIABLE_POWER"
#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_CPU_POWER_PERCENTATGE "CPU_POWER_PERCENTAGE"

typedef enum _Watts_Up_Pro_option_token_id {

	ESRV_CPU_INDEXED_SIMULATED_DEVICE_FIXED_POWER_TOKEN_ID = 0,
	ESRV_CPU_INDEXED_SIMULATED_DEVICE_VARIABLE_POWER_TOKEN_ID,
	ESRV_CPU_INDEXED_SIMULATED_DEVICE_CPU_POWER_PERCENTATGE_TOKEN_ID
	
} WATTS_UP_PRO_OPTION_TOKEN_ID;

#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_OPTIONS_MAX_ARGUMENTS ESRV_CPU_INDEXED_SIMULATED_DEVICE_OPTIONS_MAX_TOKENS * 2
#define ESRV_CPU_INDEXED_SIMULATED_DEVICE_OPTIONS_MAX_SUB_TOKENS 20

//-----------------------------------------------------------------------------
// CPU load definitions.
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#define CPU_COUNTER _T("\\Processor(_Total)\\% Processor Time")
#endif // __PL_WINDOWS__
#ifdef __PL_LINUX__
	#define DATA_SOURCE_CPU "/proc/stat"
	#define CPU_TO_MONITOR "cpu"
	#define COUNTERS_COUNT_CPU_USAGE 2
	#define BUFFER_SIZE 4096
#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)
#endif // __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// DLL definitions.
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#ifdef _USRDLL
		 // All files compiled for a DLL must be with ESRV_CPU_INDEXED_SIMULATED_DEVICE_EXPORTS symbol defined
		 // this symbol should not be defined on any project that uses this DLL. 
		#ifdef ESRV_CPU_INDEXED_SIMULATED_DEVICE_EXPORTS
			#define ESRV_API __declspec(dllexport) extern
		#else // ESRV_CPU_INDEXED_SIMULATED_DEVICE_EXPORTS
			#define ESRV_API __declspec(dllimport) extern
		#endif // ESRV_CPU_INDEXED_SIMULATED_DEVICE_EXPORTS
	#endif // _USRDLL
#endif // __PL_WINDOWS__

#if (!defined(_USRDLL)) && defined(__cplusplus) 
	#define ESRV_API extern "C"
#endif // (!defined(_USRDLL)) && defined(__cplusplus)
#if (!defined(_USRDLL)) && (!defined(__cplusplus)) 
	#define ESRV_API extern
#endif // (!defined(_USRDLL)) && (!defined(__cplusplus))

//-----------------------------------------------------------------------------
// Device options structure.
//-----------------------------------------------------------------------------
typedef struct _device_data {

	//-------------------------------------------------------------------------
	// Simulation data.
	//-------------------------------------------------------------------------
	int f_fixed_power_draw;
	int f_variable_power_draw;
	int f_cpu_power_percentage;
	double fixed_power_draw;
	double variable_power_draw;
	double cpu_power_percentage;

	//-------------------------------------------------------------------------
	// Device data.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	HQUERY hquery;
	HCOUNTER handle;
	PDH_FMT_COUNTERVALUE counter_value;
	TCHAR cpu_counter[MAX_PATH];
#endif // __PL_WINDOWS__ 
#ifdef __PL_LINUX__
	int file;
#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int dummy;
#endif // __PL_SOLARIS__ || __PL_MACOSX__

} DEVICE_DATA, *PDEVICE_DATA;

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
ESRV_API int init_device_extra_data(PESRV);
ESRV_API int delete_device_extra_data(PESRV);
ESRV_API int open_device(PESRV, void *);
ESRV_API int close_device(PESRV, void *);
ESRV_API int parse_device_option_string(PESRV, void *);
ESRV_API int read_device_power(PESRV, void *, int);
ESRV_API int read_device_energy(PESRV, void *, int, int);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_ESRV_CPU_INDEXED_SIMULATED_DEVICE__
