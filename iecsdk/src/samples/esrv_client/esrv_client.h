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

#ifndef __INCLUDE_ESRV_CLIENT__
#define __INCLUDE_ESRV_CLIENT__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
//#include "esrv.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// general definitions
//-----------------------------------------------------------------------------
#define SAMPLE_INTERVAL 1
#ifdef CUMULATIVE_EE 
	#define COUNTERS_COUNT 7
#else // CUMULATIVE_EE
	#define COUNTERS_COUNT 11
#endif // CUMULATIVE_EE
#define EE_ENERGY_CONSUMED_DECIMALS 2
#define EE_JOULES_PER_WORK_UNIT_DECIMALS 4
#define EE_WORK_UNIT_PER_JOULE_DECIMALS 4
#ifdef CUMULATIVE_EE
#else // CUMULATIVE_EE
	#define EE_WATTS_PER_WORK_UNIT_DECIMALS 4
	#define EE_WORK_UNIT_PER_WATT_DECIMALS 4
#endif // CUMULATIVE_EE

#define EE_APPLICATION_NAME "My EE Application"

#ifdef CUMULATIVE_EE
	#define EE_COUNTERS_NAMES \
		"Work Units Done - cumulative", \
		"Energy Consumed (cumulative in Joules)", \
		"Energy Consumed (cumulative in Joules).decimals", \
		"Joule(s) per Work Unit - average", \
		"Joule(s) per Work Unit - average.decimals", \
		"Work Unit(s) per Joule - average", \
		"Work Unit(s) per Joule - average.decimals"
#else // CUMULATIVE_EE 
	#define EE_COUNTERS_NAMES \
		"Work Units Done", \
		"Energy Consumed (in Joules)", \
		"Energy Consumed (in Joules).decimals", \
		"Joule(s) per Work Unit", \
		"Joule(s) per Work Unit.decimals", \
		"Work Unit(s) per Joule", \
		"Work Unit(s) per Joule.decimals", \
		"Watt(s) per Work Unit", \
		"Watt(s) per Work Unit.decimals", \
		"Work Unit(s) per Watt", \
		"Work Unit(s) per Watt.decimals"
#endif // CUMULATIVE_EE 

//-----------------------------------------------------------------------------
// enums and structures definition
//-----------------------------------------------------------------------------
enum {

	WORK_UNITS_DONE_INDEX = 0,

	ENERGY_CONSUMED_INDEX,
	ENERGY_CONSUMED_DECIMALS_INDEX,

	JOULES_PER_WORK_UNIT_INDEX,
	JOULES_PER_WORK_UNIT_DECIMALS_INDEX,
	WORK_UNIT_PER_JOULE_INDEX,
	WORK_UNIT_PER_JOULE_DECIMALS_INDEX,

#ifdef CUMULATIVE_EE
#else // CUMULATIVE_EE
	WATTS_PER_WORK_UNIT_INDEX,
	WATTS_PER_WORK_UNIT_DECIMALS_INDEX,
	WORK_UNIT_PER_WATT_INDEX,
	WORK_UNIT_PER_WATT_DECIMALS_INDEX
#endif // CUMULATIVE_EE

};

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
extern int main(int argc, char *argv[]);
extern int ee_monitor(int argc, char *argv[]);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_ESRV_CLIENT__
