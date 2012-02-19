#ifndef __INCLUDE_PUB_ESRV__
#define __INCLUDE_PUB_ESRV__

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
#ifndef ESRV_MAX_VIRTUAL_DEVICES
	#define ESRV_MAX_VIRTUAL_DEVICES 10
#endif // ESRV_MAX_VIRTUAL_DEVICES
#ifndef DAQ_SERVER_KERNEL_MAX_CHANNELS
	#define DAQ_SERVER_KERNEL_MAX_CHANNELS 128
#endif // DAQ_SERVER_KERNEL_MAX_CHANNELS
#ifndef DAQ_EVAL_ENGINE_STACK_TYPE
	#define DAQ_EVAL_ENGINE_STACK_TYPE long double
#endif // DAQ_EVAL_ENGINE_STACK_TYPE

//-----------------------------------------------------------------------------
// structures & types
//-----------------------------------------------------------------------------
typedef enum _pub_esrv_read_device_energy_services {

	READ_DEVICE_ENERGY_INIT = 0,
	READ_DEVICE_ENERGY_READ,
	READ_DEVICE_ENERGY_START,
	READ_DEVICE_ENERGY_STOP,
	READ_DEVICE_ENERGY_RESET

} PUB_ESRV_READ_DEVICE_ENERGY_SERVICES, *PPUB_ESRV_READ_DEVICE_ENERGY_SERVICES;

typedef enum _esrv_interface_id {

	ESRV_DEVICE_INTERFACE_PROPRIETARY = 0,
	ESRV_DEVICE_INTERFACE_SERIAL,
	ESRV_DEVICE_INTERFACE_ETHERNET

} ESRV_INTERFACE_ID;

typedef enum _esrv_status {

	ESRV_SUCCESS,
	ESRV_FAILURE

} ESRV_STATUS, *PESRV_STATUS;

//-----------------------------------------------------------------------------
// data options structure
//-----------------------------------------------------------------------------
typedef struct _device {

	//-------------------------------------------------------------------------
	// generic device data
	//-------------------------------------------------------------------------
	int virtual_devices;

	//-------------------------------------------------------------------------
	// serial device data
	//-------------------------------------------------------------------------
	char *eor;
	size_t leor;
	int f_extraction_required;
	char token_separator;
	char power_token_position;

	//-------------------------------------------------------------------------
	// device specific data pointer
	//-------------------------------------------------------------------------
	void *p_device_data;

} DEVICE, *PDEVICE;

/**
* \struct _esrv
* \brief Structure du serveur d'énergie
*
*/
typedef struct _esrv {

	//------------------------------------------------------------------------
	// public energy data.
	//-------------------------------------------------------------------------
	int f_hw_energy_integration_provided;
	double double_power; // in Watts
	long double double_energy; // in Joules

	//-------------------------------------------------------------------------
	// public optional data.
	//-------------------------------------------------------------------------
	double double_current; /**< en Ampère */
	double double_voltage; // in Volts
	double double_power_factor; // has no unit
	double double_voltage_frequency; // in Hz
	double double_current_frequency; // in Hz

	//-------------------------------------------------------------------------
	// public function pointers data.
	//-------------------------------------------------------------------------
	int (*p_open_interface)(struct _esrv *);
	int (*p_close_interface)(struct _esrv *);
	int (*p_read_interface)(struct _esrv *);
	int (*p_write_interface)(struct _esrv *);

	//-------------------------------------------------------------------------
	// device related public data.
	//-------------------------------------------------------------------------
	ESRV_INTERFACE_ID device_interface;
	DEVICE device_data;
	char *device_option_string;

	//-------------------------------------------------------------------------
	// public DAQ channel data.
	//-------------------------------------------------------------------------
	int f_daq_optimized_data_read;
	int daq_channel_count;
	int daq_active_channels_count;
	int daq_active_channels[DAQ_SERVER_KERNEL_MAX_CHANNELS];
	int daq_channel_status[DAQ_SERVER_KERNEL_MAX_CHANNELS]; // ESRV_STATUS
	DAQ_EVAL_ENGINE_STACK_TYPE daq_channel_readings[DAQ_SERVER_KERNEL_MAX_CHANNELS];

} ESRV, *PESRV;

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PUB_ESRV__
