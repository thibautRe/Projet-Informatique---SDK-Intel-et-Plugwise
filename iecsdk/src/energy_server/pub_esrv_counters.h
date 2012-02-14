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

#ifndef __INCLUDE_PUB_ESRV_COUNTERS__
#define __INCLUDE_PUB_ESRV_COUNTERS__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// general definitions.
//-----------------------------------------------------------------------------
#ifndef ESRV_BASE_COUNTERS_COUNT
	#define ESRV_BASE_COUNTERS_COUNT 63
#endif // ESRV_BASE_COUNTERS_COUNT
#ifndef ESRV_APPLICATION_NAME
	#define ESRV_APPLICATION_NAME "esrv"
#endif // ESRV_APPLICATION_NAME

//-----------------------------------------------------------------------------
// counters definitions.
//-----------------------------------------------------------------------------
typedef enum _esrv_running_status {
	
	ESRV_STATUS_NOT_RUNNING = 0,
	ESRV_STATUS_RUNNING

} ESRV_RUNNING_STATUS, *PESRV_RUNNING_STATUS;

typedef enum _esrv_counters_base_indexes {

	//-------------------------------------------------------------------------
	// mandatory counters
	//-------------------------------------------------------------------------
	ESRV_COUNTER_ENERGY_JOULES_INDEX = 0,
	ESRV_COUNTER_ENERGY_JOULES_DECIMALS_INDEX,
	ESRV_COUNTER_ENERGY_KWH_INDEX,
	ESRV_COUNTER_ENERGY_KWH_DECIMALS_INDEX,
	ESRV_COUNTER_ENERGY_OVERFLOWS_INDEX,
	ESRV_COUNTER_UPDATE_FREQUENCY_INDEX,
	ESRV_COUNTER_POWER_INDEX,
	ESRV_COUNTER_POWER_DECIMALS_INDEX,
	ESRV_COUNTER_MAX_POWER_INDEX,
	ESRV_COUNTER_MAX_POWER_DECIMALS_INDEX,
	ESRV_COUNTER_MIN_POWER_INDEX,
	ESRV_COUNTER_MIN_POWER_DECIMALS_INDEX,

	//-------------------------------------------------------------------------
	// optional counters
	// Note: counters below are optional and may not be updated or set by
	// the device driver.  It is recommended that un-implemented counters
	// are set to zero.
	//-------------------------------------------------------------------------
	ESRV_COUNTER_CURRENT_INDEX,
	ESRV_COUNTER_CURRENT_SIGN_INDEX,
	ESRV_COUNTER_CURRENT_DECIMALS_INDEX,
	ESRV_COUNTER_MAX_CURRENT_INDEX,
	ESRV_COUNTER_MAX_CURRENT_SIGN_INDEX,
	ESRV_COUNTER_MAX_CURRENT_DECIMALS_INDEX,
	ESRV_COUNTER_MIN_CURRENT_INDEX,
	ESRV_COUNTER_MIN_CURRENT_SIGN_INDEX,
	ESRV_COUNTER_MIN_CURRENT_DECIMALS_INDEX,
	ESRV_COUNTER_CURRENT_SECONDS_INDEX,
	ESRV_COUNTER_CURRENT_SECONDS_SIGN_INDEX,
	ESRV_COUNTER_CURRENT_SECONDS_DECIMALS_INDEX,
	ESRV_COUNTER_VOLTAGE_INDEX,
	ESRV_COUNTER_VOLTAGE_SIGN_INDEX,
	ESRV_COUNTER_VOLTAGE_DECIMALS_INDEX,
	ESRV_COUNTER_MAX_VOLTAGE_INDEX,
	ESRV_COUNTER_MAX_VOLTAGE_SIGN_INDEX,
	ESRV_COUNTER_MAX_VOLTAGE_DECIMALS_INDEX,
	ESRV_COUNTER_MIN_VOLTAGE_INDEX,
	ESRV_COUNTER_MIN_VOLTAGE_SIGN_INDEX,
	ESRV_COUNTER_MIN_VOLTAGE_DECIMALS_INDEX,
	ESRV_COUNTER_VOLTAGE_SECONDS_INDEX,
	ESRV_COUNTER_VOLTAGE_SECONDS_SIGN_INDEX,
	ESRV_COUNTER_VOLTAGE_SECONDS_DECIMALS_INDEX,
	ESRV_COUNTER_POWER_FACTOR_INDEX,
	ESRV_COUNTER_POWER_FACTOR_DECIMALS_INDEX,
	ESRV_COUNTER_MAX_POWER_FACTOR_INDEX,
	ESRV_COUNTER_MAX_POWER_FACTOR_DECIMALS_INDEX,
	ESRV_COUNTER_MIN_POWER_FACTOR_INDEX,
	ESRV_COUNTER_MIN_POWER_FACTOR_DECIMALS_INDEX,
	ESRV_COUNTER_POWER_FACTOR_SECONDS_INDEX,
	ESRV_COUNTER_POWER_FACTOR_SECONDS_DECIMALS_INDEX,
	ESRV_COUNTER_CURRENT_FREQUENCY_INDEX,
	ESRV_COUNTER_CURRENT_FREQUENCY_DECIMALS_INDEX,
	ESRV_COUNTER_MAX_CURRENT_FREQUENCY_INDEX,
	ESRV_COUNTER_MAX_CURRENT_FREQUENCY_DECIMALS_INDEX,
	ESRV_COUNTER_MIN_CURRENT_FREQUENCY_INDEX,
	ESRV_COUNTER_MIN_CURRENT_FREQUENCY_DECIMALS_INDEX,
	ESRV_COUNTER_CURRENT_FREQUENCY_SECONDS_INDEX,
	ESRV_COUNTER_CURRENT_FREQUENCY_SECONDS_DECIMALS_INDEX,
	ESRV_COUNTER_VOLTAGE_FREQUENCY_INDEX,
	ESRV_COUNTER_VOLTAGE_FREQUENCY_DECIMALS_INDEX,
	ESRV_COUNTER_MAX_VOLTAGE_FREQUENCY_INDEX,
	ESRV_COUNTER_MAX_VOLTAGE_FREQUENCY_DECIMALS_INDEX,
	ESRV_COUNTER_MIN_VOLTAGE_FREQUENCY_INDEX,
	ESRV_COUNTER_MIN_VOLTAGE_FREQUENCY_DECIMALS_INDEX,
	ESRV_COUNTER_VOLTAGE_FREQUENCY_SECONDS_INDEX,
	ESRV_COUNTER_VOLTAGE_FREQUENCY_SECONDS_DECIMALS_INDEX,

	//-------------------------------------------------------------------------
	// esrv specific counters
	//-------------------------------------------------------------------------
	ESRV_COUNTER_CHANNELS_INDEX,
	ESRV_COUNTER_STATUS_INDEX,
	ESRV_COUNTER_VERSION_INDEX

} ESRV_COUNTERS_BASE_INDEXES;

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PUB_ESRV_COUNTERS__
