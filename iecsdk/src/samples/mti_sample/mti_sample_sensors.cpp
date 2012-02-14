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

#ifdef __MTI_SAMPLE_SENSORS_CODE__
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Note on asserts:
//    This is a sample code and not a production code. Therefore, no error
//    processing is performed in addition of the use of assertions.  However,
//    all function call returns are tested and asserted for success.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Note:
//    In this sample, we do implement only the ISensorEvents interface.  This
//    is the reason why if a sensor is installed once the program has started
//    it is not taken in account.  Do do so, the ISensorManagerEvents intrface
//    must be implemented, added to the sensors manager (OnSensorEnter).
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Build notes
//-----------------------------------------------------------------------------
// following symbols alters compilation and execution paths
// __MTI_SAMPLE_SENSORS_CODE__:
//    define this symbol to activate sensor code.
//-----------------------------------------------------------------------------

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

#include <assert.h>
#include "mti_sample_sensors.hpp"
#include "mti_sample_shared_data.h"

#pragma comment (lib, "sensorsapi")

//-----------------------------------------------------------------------------
// Global sensor variable and extern definition for shared data
//-----------------------------------------------------------------------------
extern "C" {
	extern MTI_SAMPLE_SHARED_DATA shared_data;
}
c_events_sink *events = NULL;

/*-----------------------------------------------------------------------------
Function: connect_to_an_als_sensor
Purpose : connects to an ambiant light sensor (attached to the PC, first one)
          if no sensor is found, signal it to the user and use default lux value.
In      : none
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
extern "C" BOOL connect_to_an_als_sensor(void) {

	ULONG i = 0;
	HRESULT hret = S_FALSE;
	BOOL f_sensor_found = FALSE;
	ULONG sensors_count = 0;
	PROPVARIANT sensor_property;
	CComPtr<ISensor> sensor = NULL;
	CComPtr<ISensorManager> sensor_manager = NULL;
	CComPtr<ISensorCollection> sensor_collection = NULL;
	CComPtr<ISensorDataReport> data_report = NULL;

	//-------------------------------------------------------------------------
	// initialize COM
	//-------------------------------------------------------------------------
	hret = CoInitializeEx(
		NULL, 
		COINIT_APARTMENTTHREADED
	);
	if(FAILED(hret)) {
		goto connect_to_an_als_sample_exit;
	}

	//-------------------------------------------------------------------------
	// instanciate events sink object
	//-------------------------------------------------------------------------
	events = new c_events_sink;
	assert(events != NULL);

	//-------------------------------------------------------------------------
	// create a sensor manager
	//-------------------------------------------------------------------------
	hret = sensor_manager.CoCreateInstance(CLSID_SensorManager);
	if(FAILED(hret)) {
		goto connect_to_an_als_sample_exit;
	}

	//-------------------------------------------------------------------------
	// get information on all ALS sensors present in the system
	//-------------------------------------------------------------------------
	hret = sensor_manager->GetSensorsByType(
		SENSOR_TYPE_AMBIENT_LIGHT,
		&sensor_collection
	);
	if(FAILED(hret)) {
		goto connect_to_an_als_sample_exit;
	}

	//-------------------------------------------------------------------------
	// request permission to access sensor
	//-------------------------------------------------------------------------
	hret = sensor_manager->RequestPermissions(
		0,
		sensor_collection,
		TRUE	
	);
	if(FAILED(hret)) {
		goto connect_to_an_als_sample_exit;
	}

	//-------------------------------------------------------------------------
	// get number of sensors in the collection
	//-------------------------------------------------------------------------
	hret = sensor_collection->GetCount(&sensors_count);
	if(FAILED(hret)) {
		goto connect_to_an_als_sample_exit;
	}
	assert(sensors_count >= 1);

	for(i = 0; i < sensors_count; i++) {

		//---------------------------------------------------------------------
		// get the ith ALS sensor in the collection
		//---------------------------------------------------------------------
		hret = sensor_collection->GetAt(
			i,
			&sensor
		);
		if(FAILED(hret)) {
			goto connect_to_an_als_sample_exit;
		}

		//---------------------------------------------------------------------
		// get the ith ALS sensor's location property
		//---------------------------------------------------------------------
		PropVariantInit(&sensor_property);
		hret = sensor->GetProperty(
			SENSOR_PROPERTY_CONNECTION_TYPE,
			&sensor_property
		);
		if(FAILED(hret)) {
			goto connect_to_an_als_sample_exit;
		}

		//---------------------------------------------------------------------
		// if this sensor is integrated, then we use it
		//---------------------------------------------------------------------
		if(sensor_property.uiVal == SENSOR_CONNECTION_TYPE_PC_INTEGRATED) {

			//-----------------------------------------------------------------
			// setup the event sink for the sensor
			//-----------------------------------------------------------------
			hret = sensor->SetEventSink(events);
			if(FAILED(hret)) {
				goto connect_to_an_als_sample_exit;
			}
			f_sensor_found = TRUE;
			break;
		}
		PropVariantClear(&sensor_property);
	} // for i

connect_to_an_als_sample_exit:

	if(f_sensor_found != TRUE) {

		//---------------------------------------------------------------------
		// signal no ALS sensor available and set average condition
		//---------------------------------------------------------------------
		ShowCursor(TRUE);
		MessageBox(
			shared_data.hwnd,
			L"No ALS sensor has been detected on your system.\nWill assume average anbiant light conditions.",
			L"ALS Sensor",
			MB_OK
		);
		ShowCursor(FALSE);
		shared_data.lux = DEFAULT_LUX_VALUE;
		shared_data.light_coefficient = NORMALIZE_LUX(shared_data.lux);
		shared_data.f_sensor = FALSE;
		return(FALSE);
	
	} else {

		//---------------------------------------------------------------------
		// try reading the actual sensor's reading
		//---------------------------------------------------------------------
        hret = sensor->GetData(&data_report);
		if(FAILED(hret)) {
			shared_data.lux = DEFAULT_LUX_VALUE;
		} else {
			hret = events->get_sensor_data(
				sensor, 
				data_report
			);
			if(shared_data.lux == 0.0) {
				shared_data.lux = MIN_LUX_VALUE;
			}
        }
		shared_data.light_coefficient = NORMALIZE_LUX(shared_data.lux);
		return(TRUE);
	}
}

/*-----------------------------------------------------------------------------
Function: disconnect_from_als_sensor
Purpose : disconnects from the connected ambiant light sensor
In      : none
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
extern "C" BOOL disconnect_from_als_sensor(void) {
	return(TRUE);
}

/*-----------------------------------------------------------------------------
Function: _events_sink::OnDataUpdated
Purpose : ALS update handler
In      : pointer to sensor and sensor data report interfaces
Out     : none
Return  : handle

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
HRESULT c_events_sink::OnDataUpdated(
	ISensor* ps, 
	ISensorDataReport* pd
) {

	BOOL bret = FALSE;
	HRESULT hret = S_FALSE;
	PROPVARIANT sensor_reading;

	assert(ps != NULL);
	assert(pd != NULL);

	//-------------------------------------------------------------------------
	// retrieve the updated sensor value
	//-------------------------------------------------------------------------
	hret = events->get_sensor_data(
		ps,
		pd
	);
	if(FAILED(hret)) {
		assert(0);
	}

	//-------------------------------------------------------------------------
	// if sensor reading is null, set lux value to the minimin not null value,
	// this will avoid division and Lon10 by/of 0 later in the code.
	//-------------------------------------------------------------------------
	if(shared_data.lux == 0.0) {
		shared_data.lux = MIN_LUX_VALUE;
	}
	PropVariantClear(&sensor_reading);

	//-------------------------------------------------------------------------
	// signal change so the application's UI/behavior can be updated
	//-------------------------------------------------------------------------
	bret = PostMessage(
		shared_data.hwnd,
		MTI_SAMPLE_SENSOR_UPDATE,
		0,
		0
	);
	assert(bret == TRUE);
	shared_data.f_sensor = TRUE;
	return(S_OK);
}

/*-----------------------------------------------------------------------------
Function: _events_sink::QueryInterface
Purpose : ALS sensor interface is queried, return a pointer to the requested
          interface. Reinterprete IUnknown to the right interface. Add a 
		  reference if successful.
In      : interface id and void pointer (IUnknown)
Out     : none
Return  : handle

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
HRESULT c_events_sink::QueryInterface(
	REFIID iid, 
	void** ppv
) {
	if(ppv == NULL) {
		return E_POINTER;
	}
	if(iid == __uuidof(IUnknown)) {
		*ppv = static_cast<IUnknown*>(this);
	} else {
		if(iid == __uuidof(ISensorEvents)) {
			*ppv = static_cast<ISensorEvents*>(this);
		} else {
			*ppv = NULL;
			return E_NOINTERFACE;
		}
	}
	AddRef();
	return(S_OK);
}

/*-----------------------------------------------------------------------------
Function: _events_sink::AddRef
Purpose : ALS sensor is referenced (add a reference to the object interface)
In      : none
Out     : none
Return  : handle

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
STDMETHODIMP_(ULONG) c_events_sink::AddRef() {
	reference_count++;
	shared_data.f_sensor = TRUE;
	return(reference_count); 
}

/*-----------------------------------------------------------------------------
Function: _events_sink::Release
Purpose : ALS sensor is released (remove a reference to the object interface)
In      : none
Out     : none
Return  : handle

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
STDMETHODIMP_(ULONG) c_events_sink::Release() {

	reference_count--;
	if(reference_count == 0) {
		delete(this);
		return(0);
	}
	shared_data.f_sensor = FALSE;
	return(reference_count);
}

/*-----------------------------------------------------------------------------
Function: _events_sink::OnEvent
Purpose : ALS sensor event received (not update related).
In      : pointer to sensor, event value and pointer to data
Out     : none
Return  : handle

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
HRESULT c_events_sink::OnEvent(
	ISensor *ps,
	REFGUID e,
	IPortableDeviceValues *pd
) {
	assert(ps != NULL);
	assert(pd != NULL);
	return(E_NOTIMPL);
}

/*-----------------------------------------------------------------------------
Function: _events_sink::OnLeave
Purpose : ALS sensor not available anymore
In      : sensor id
Out     : none
Return  : handle

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
HRESULT c_events_sink::OnLeave(REFSENSOR_ID id) {
	shared_data.f_sensor = FALSE;
	return(S_OK);
}

/*-----------------------------------------------------------------------------
Function: _events_sink::OnStateChanged
Purpose : ALS sensor state has changed.  Called for example 
          when sensor permission changed or the sensor is disabled, etc.
          If sensor is not SENSOR_STATE_READY then its a value update, we will
		  catch it in the updade methode.
In      : pointer to sensor and sensor data sensor state
Out     : none
Return  : handle

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
HRESULT c_events_sink::OnStateChanged(
	ISensor* ps,
	SensorState s
) {
	assert(ps != NULL);

	HRESULT hret = S_FALSE;
	SENSOR_ID id = GUID_NULL;

	hret = ps->GetID(&id);
	if(SUCCEEDED(hret)) {
		if(s == SENSOR_STATE_READY) {
			shared_data.f_sensor = TRUE;
		} else {
			shared_data.f_sensor = FALSE;
		}
	}
	return(S_OK);
}

/*-----------------------------------------------------------------------------
Function: _events_sink::get_sensor_data
Purpose : get the ALS sensor reading 
In      : pointer to sensor and sensor data sensor state
Out     : none
Return  : handle

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
HRESULT c_events_sink::get_sensor_data(
	ISensor *ps, 
	ISensorDataReport *pd
) {

    HRESULT hret = S_FALSE;
	SENSOR_ID id = GUID_NULL;
	PROPVARIANT sensor_property;

	assert(ps != NULL);
	assert(pd != NULL);

	hret = ps->GetID(&id);
	if(SUCCEEDED(hret)) {
		PropVariantInit(&sensor_property);
		hret = pd->GetSensorValue(
			SENSOR_DATA_TYPE_LIGHT_LEVEL_LUX, 
			&sensor_property
		);
		if(SUCCEEDED(hret)) {
			shared_data.lux = sensor_property.fltVal;
		}
		PropVariantClear(&sensor_property);
	}
    return(hret);
}


/*--------------------------------------------------------------------------*/
#endif // __MTI_SAMPLE_SENSORS_CODE__
