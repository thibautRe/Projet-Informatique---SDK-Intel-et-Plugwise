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
#ifndef __SENSORS_SAMPLE_CODE__
#define __SENSORS_SAMPLE_CODE__

#ifdef __MTI_SAMPLE_SENSORS_CODE__

//-----------------------------------------------------------------------------
// Headers inclusions
//-----------------------------------------------------------------------------
#define _AFXDLL
#ifndef WINVER
	#define WINVER 0x0501
#endif // WINVER
#ifndef _SECURE_ATL
	#define _SECURE_ATL 1
#endif // _SECURE_ATL
#ifndef VC_EXTRALEAN
	#define VC_EXTRALEAN
#endif // VC_EXTRALEAN
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_ALL_WARNINGS
#include <afxwin.h>
#include <afxext.h>
#ifndef _AFX_NO_OLE_SUPPORT
	#include <afxdtctl.h>
#endif // _AFX_NO_OLE_SUPPORT
#ifndef _AFX_NO_AFXCMN_SUPPORT
	#include <afxcmn.h>
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <sensors.h>
#include <sensorsapi.h>
#include <atlcoll.h>

#include "mti_sample_shared_data.h"

//-----------------------------------------------------------------------------
// classes, structures & enums
//-----------------------------------------------------------------------------
class c_events_sink : public ISensorEvents {

	public:

		//---------------------------------------------------------------------
		// COM ISensorEvents callback inplementation
		//---------------------------------------------------------------------
		STDMETHODIMP QueryInterface(
			REFIID iid, 
			void** ppv
		);
		STDMETHODIMP_(ULONG) AddRef();
		STDMETHODIMP_(ULONG) Release();
		STDMETHODIMP OnEvent(
			ISensor *pSensor,
			REFGUID eventID,
			IPortableDeviceValues *pEventData
		);
		STDMETHODIMP OnLeave(REFSENSOR_ID sensorID);
		STDMETHODIMP OnStateChanged(
			ISensor* pSensor,
			SensorState state
		);
		STDMETHOD(OnDataUpdated)(
			ISensor* ps, 
			ISensorDataReport* pd
		);
		STDMETHOD(get_sensor_data)(
			ISensor *ps, 
			ISensorDataReport *pd
		);

    private:

		//---------------------------------------------------------------------
		// interface use counter
		//---------------------------------------------------------------------
        LONG reference_count;
};

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
extern "C" BOOL connect_to_an_als_sensor(void);
extern "C" BOOL disconnect_from_als_sensor(void);

#endif // __MTI_SAMPLE_SENSORS_CODE__

#endif // __SENSORS_SAMPLE_CODE__
