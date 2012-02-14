#ifndef __INCLUDE_DAQ_TEMPLATE_DEVICE__
#define __INCLUDE_DAQ_TEMPLATE_DEVICE__

//-----------------------------------------------------------------------------
// Headers inclusions.
//-----------------------------------------------------------------------------
#include "pub_esrv.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// ESRV_API API definition.
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#ifdef _USRDLL
		// All files compiled for a DLL must be with TEMPLATE_DEVICE_EXPORTS 
		// symbol defined.  This symbol should not be defined on any project
		// that uses this DLL. 
		#ifdef TEMPLATE_DEVICE_EXPORTS
			#define ESRV_API __declspec(dllexport) extern
		#else // TEMPLATE_DEVICE_EXPORTS
			#define ESRV_API __declspec(dllimport) extern
		#endif // TEMPLATE_DEVICE_EXPORTS
	#endif // _USRDLL
#endif // __PL_WINDOWS__

#if (!defined(_USRDLL)) && defined(__cplusplus) 
	#define ESRV_API extern "C"
#endif // (!defined(_USRDLL)) && defined(__cplusplus)
#if (!defined(_USRDLL)) && (!defined(__cplusplus)) 
	#define ESRV_API extern
#endif // (!defined(_USRDLL)) && (!defined(__cplusplus))

//-----------------------------------------------------------------------------
// General definitions.
//-----------------------------------------------------------------------------
// TODO: add here your constants' definitions (#define)

//-----------------------------------------------------------------------------
// Messages definitions.
// Note:
//    Most devices are driven using messages.  It is a custom to declare those
//    messages in the header file.  This can simplify the adaptation of an 
//    existing support module for similar devices or devices belonging to the
//    same family.
//-----------------------------------------------------------------------------
// TODO: add here your device's messages' definitions (#define)

//-----------------------------------------------------------------------------
// Device options structure.
//-----------------------------------------------------------------------------
typedef struct _device_data {
	
	//-----------------------------------------------------------------------------
	// Device options.
	// Note:
	//    Declare here all the data - can be data structures - that your device
	//    may require.  This may include data used to store user accessible 
	//    options / configuration data.
	//-----------------------------------------------------------------------------
	// TODO: add here data required by your device.
	int dummy;

} DEVICE_DATA, *PDEVICE_DATA;

//-----------------------------------------------------------------------------
// Functions prototypes.
//-----------------------------------------------------------------------------
ESRV_API int init_device_extra_data(PESRV);
ESRV_API int delete_device_extra_data(PESRV);
ESRV_API int open_device(PESRV, void *);
ESRV_API int close_device(PESRV, void *);
ESRV_API int parse_device_option_string(PESRV, void *);
ESRV_API int read_device_all_channels(PESRV, void *);
ESRV_API int read_device_channel(PESRV, void *, int);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_DAQ_TEMPLATE_DEVICE__
