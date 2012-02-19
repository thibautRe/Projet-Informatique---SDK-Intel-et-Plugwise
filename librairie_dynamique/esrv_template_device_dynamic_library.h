#ifndef __INCLUDE_TEMPLATE_DEVICE__
#define __INCLUDE_TEMPLATE_DEVICE__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include "pub_esrv.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// ESRV_API API drinition
//-----------------------------------------------------------------------------
// Suppression du code Windows
#if (!defined(_USRDLL)) && defined(__cplusplus) 
	#define ESRV_API extern "C"
#endif // (!defined(_USRDLL)) && defined(__cplusplus)
#if (!defined(_USRDLL)) && (!defined(__cplusplus)) 
	#define ESRV_API extern
#endif // (!defined(_USRDLL)) && (!defined(__cplusplus))

//-----------------------------------------------------------------------------
// general definitions
//-----------------------------------------------------------------------------
// TODO: add here your constants' definitions (#define)

//-----------------------------------------------------------------------------
// messages definitions
//-----------------------------------------------------------------------------
// TODO: add here your device's messages' definitions (#define)

//-----------------------------------------------------------------------------
// device options structure
//-----------------------------------------------------------------------------
typedef struct _device_data {
	
	//-----------------------------------------------------------------------------
	// device options
	//-----------------------------------------------------------------------------
	// TODO: add here data required by your device.
	int dummy;

} DEVICE_DATA, *PDEVICE_DATA;

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
ESRV_API int init_device_extra_data(PESRV);
ESRV_API int delete_device_extra_data(PESRV);
ESRV_API int open_device(PESRV, void *);
ESRV_API int close_device(PESRV, void *);
ESRV_API int parse_device_option_string(PESRV, void *);
ESRV_API int read_device_all_measurements(PESRV, void *, int);
ESRV_API int read_device_power(PESRV, void *, int);
ESRV_API int read_device_energy(PESRV, void *, int, int);
// Optional functions' prototypes
ESRV_API int read_device_current(PESRV, void *, int);
ESRV_API int read_device_voltage(PESRV, void *, int);
ESRV_API int read_device_power_factor(PESRV, void *, int);
ESRV_API int read_device_voltage_frequency(PESRV, void *, int);
ESRV_API int read_device_current_frequency(PESRV, void *, int);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_TEMPLATE_DEVICE__
