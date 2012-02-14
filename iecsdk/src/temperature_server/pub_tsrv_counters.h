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

#ifndef __INCLUDE_TSRV_COUNTERS__
#define __INCLUDE_TSRV_COUNTERS__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#include <windows.h>
#endif // __PL_WINDOWS_
#include "tsrv.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// general definitions.
//-----------------------------------------------------------------------------
#ifndef TSRV_BASE_COUNTERS_COUNT
	#define TSRV_BASE_COUNTERS_COUNT 20
#endif // TSRV_BASE_COUNTERS_COUNT
#ifndef TSRV_APPLICATION_NAME
	#define ESRV_APPLICATION_NAME "tsrv"
#endif // TSRV_APPLICATION_NAME

//-----------------------------------------------------------------------------
// counters definitions.
//-----------------------------------------------------------------------------
typedef enum _tsrv_running_status {
	
	TSRV_STATUS_NOT_RUNNING = 0,
	TSRV_STATUS_RUNNING

} TSRV_RUNNING_STATUS, *PTSRV_RUNNING_STATUS;

//-----------------------------------------------------------------------------
// counters definitions.
//-----------------------------------------------------------------------------
typedef enum _tsrv_counters_base_indexes {

	TSRV_COUNTER_TEMPERATURE_KELVIN_INDEX = 0,
	TSRV_COUNTER_TEMPERATURE_KELVIN_DECIMALS_INDEX,
	TSRV_COUNTER_MAX_TEMPERATURE_KELVIN_INDEX,
	TSRV_COUNTER_MAX_TEMPERATURE_KELVIN_DECIMALS_INDEX,
	TSRV_COUNTER_MIN_TEMPERATURE_KELVIN_INDEX,
	TSRV_COUNTER_MIN_TEMPERATURE_KELVIN_DECIMALS_INDEX,
	TSRV_COUNTER_TEMPERATURE_KELVIN_SECONDS_INDEX,
	TSRV_COUNTER_TEMPERATURE_KELVIN_SECONDS_DECIMALS_INDEX,
	TSRV_COUNTER_RELATIVE_HUMIDITY_PERCENTAGE_INDEX,
	TSRV_COUNTER_RELATIVE_HUMIDITY_PERCENTAGE_DECIMALS_INDEX,
	TSRV_COUNTER_MAX_RELATIVE_HUMIDITY_PERCENTAGE_INDEX,
	TSRV_COUNTER_MAX_RELATIVE_HUMIDITY_PERCENTAGE_DECIMALS_INDEX,
	TSRV_COUNTER_MIN_RELATIVE_HUMIDITY_PERCENTAGE_INDEX,
	TSRV_COUNTER_MIN_RELATIVE_HUMIDITY_PERCENTAGE_DECIMALS_INDEX,
	TSRV_COUNTER_RELATIVE_HUMIDITY_PERCENTAGE_SECONDS_INDEX,
	TSRV_COUNTER_RELATIVE_HUMIDITY_PERCENTAGE_SECONDS_DECIMALS_INDEX,
	TSRV_COUNTER_UPDATE_FREQUENCY_SECOND_INDEX,

	//-------------------------------------------------------------------------
	// tsrv specific counters
	//-------------------------------------------------------------------------
	TSRV_COUNTER_CHANNELS_INDEX,
	TSRV_COUNTER_STATUS_INDEX,
	TSRV_COUNTER_VERSION_INDEX

} TSRV_COUNTERS_BASE_INDEXES;

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_TSRV_COUNTERS__
