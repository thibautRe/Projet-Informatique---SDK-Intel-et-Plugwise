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

#ifndef __INCLUDE_TSRV__
#define __INCLUDE_TSRV__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#include <windows.h>
#endif // __PL_WINDOWS_
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#include <stddef.h>
	#include <pthread.h>
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#ifndef TSRV_MAX_VIRTUAL_DEVICES
	#define TSRV_MAX_VIRTUAL_DEVICES 1
#endif // TSRV_MAX_VIRTUAL_DEVICES
#ifndef TSRV_DEVICE_INTERFACE_PROPRIETARY
	#define TSRV_DEVICE_INTERFACE_PROPRIETARY 4
#endif // TSRV_DEVICE_INTERFACE_PROPRIETARY

//-----------------------------------------------------------------------------
// structures & types
//-----------------------------------------------------------------------------
typedef enum _tsrv_status {

	TSRV_SUCCESS,
	TSRV_FAILURE

} TSRV_STATUS, *PTSRV_STATUS;

//-----------------------------------------------------------------------------
// data options structure
//-----------------------------------------------------------------------------
typedef struct _device {

	//-----------------------------------------------------------------------------
	// generic device data
	//-----------------------------------------------------------------------------
	int virtual_devices;

	//-----------------------------------------------------------------------------
	// serial device data
	//-----------------------------------------------------------------------------
	char *eor;
	size_t leor;
	int f_extraction_required;
	char token_separator;

	//-----------------------------------------------------------------------------
	// device specific data pointer
	//-----------------------------------------------------------------------------
	void *p_device_data;

} DEVICE, *PDEVICE;

//-----------------------------------------------------------------------------
// temperature server structure
//-----------------------------------------------------------------------------
typedef struct _tsrv {

	//-----------------------------------------------------------------------------
	// public temperature and humidity data.
	//-----------------------------------------------------------------------------
	double double_temperature; // in Kelvin
	double double_humidity; // in %

	//-----------------------------------------------------------------------------
	// device related public data.
	//-----------------------------------------------------------------------------
	int device_interface;
	DEVICE device_data;
	char *device_option_string;

} TSRV, *PTSRV;

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_TSRV__
