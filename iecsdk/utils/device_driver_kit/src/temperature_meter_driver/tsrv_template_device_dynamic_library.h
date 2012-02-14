#ifndef __INCLUDE_TEMPLATE_DEVICE__
#define __INCLUDE_TEMPLATE_DEVICE__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include "pub_tsrv.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// TSRV_API API drinition
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#ifdef _USRDLL
		// All files compiled for a DLL must be with TEMPLATE_DEVICE_EXPORTS 
		// symbol defined. This symbol should not be defined on any project 
		// that uses this DLL. 
		#ifdef TEMPLATE_DEVICE_EXPORTS
			#define TSRV_API __declspec(dllexport) extern
		#else // TEMPLATE_DEVICE_EXPORTS
			#define TSRV_API __declspec(dllimport) extern
		#endif // TEMPLATE_DEVICE_EXPORTS
	#endif // _USRDLL
#endif // __PL_WINDOWS__

#if (!defined(_USRDLL)) && defined(__cplusplus) 
	#define TSRV_API extern "C"
#endif // (!defined(_USRDLL)) && defined(__cplusplus)
#if (!defined(_USRDLL)) && (!defined(__cplusplus)) 
	#define TSRV_API extern
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
TSRV_API int init_device_extra_data(PTSRV);
TSRV_API int delete_device_extra_data(PTSRV);
TSRV_API int open_device(PTSRV, void *);
TSRV_API int close_device(PTSRV, void *);
TSRV_API int parse_device_option_string(PTSRV, void *);
TSRV_API int read_device_power(PTSRV, void *, int);
TSRV_API int read_device_energy(PTSRV, void *, int);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_TEMPLATE_DEVICE__
