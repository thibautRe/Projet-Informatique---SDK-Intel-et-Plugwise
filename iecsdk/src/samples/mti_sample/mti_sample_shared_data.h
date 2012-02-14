/**
*** INTEL CONFIDENTIAL
*** 
*** Copyright (August 2010) (August 2010) Intel Corporation All Rights Reserved. 
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
#ifndef __MTI_SAMPLE_SHARE__
#define __MTI_SAMPLE_SHARE__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// headers inclusion
//-----------------------------------------------------------------------------
#include <math.h> // for log10

//-----------------------------------------------------------------------------
// defines
// Note:
//    we do not use WM_USER (0x0400) since it would require the inclusion of
//    windows.h, which would conflict in the sensor support code - using ATL.
//-----------------------------------------------------------------------------
#define MTI_SAMPLE_SENSOR_UPDATE (0x0400 + 1)
#define MIN_LUX_VALUE 1.0
#define MAX_LUX_VALUE 100000.0
#define DEFAULT_LUX_VALUE 400.0
#define NORMALIZE_LUX(l) \
	log10((l))/5.0

//-----------------------------------------------------------------------------
// structures & enums
//-----------------------------------------------------------------------------
typedef struct _mti_sample_shared_data {

	//-------------------------------------------------------------------------
	// data used to notify main window that a sensor value was updated
	//-------------------------------------------------------------------------
	HWND hwnd;

	//-------------------------------------------------------------------------
	// data used to notify sensor prsent or not
	// Note:
	//     This flag is essentialy used on the sensor management side.  
	//     On the application side, the lux value [0.0 - 1.0] is always used,
	//     not the flag.  When the sensor is not available, then the lux value
	//     is set to 0.5 (DEFAULT_LUX_VALUE).
	//-------------------------------------------------------------------------
	BOOL f_sensor;

	//-------------------------------------------------------------------------
	// data used to store raw sensor data
	//-------------------------------------------------------------------------
	double lux;
	double light_coefficient;

} MTI_SAMPLE_SHARED_DATA, *PMTI_SAMPLE_SHARED_DATA;

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __MTI_SAMPLE_SHARE__
