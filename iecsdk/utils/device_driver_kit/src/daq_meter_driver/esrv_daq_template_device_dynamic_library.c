//-----------------------------------------------------------------------------
// Functions call sequence by the server.
//-----------------------------------------------------------------------------
// 1 - .....ESRV_API int init_device_extra_data(PESRV); // first call
// 2 - .....ESRV_API int parse_device_option_string(PESRV, void *);
// 3 - .....ESRV_API int init_device_extra_data(PESRV); // second call
// 4 - .....ESRV_API int open_device(PESRV, void *);
// 5 - N.......ESRV_API int read_device_all_channels(PESRV, void *);
// N + 1 - .ESRV_API int close_device(PESRV, void *);
// N + 2 - .ESRV_API int delete_device_extra_data(PESRV);
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Headers inclusions.
//-----------------------------------------------------------------------------
#include <string.h>
#include <assert.h>
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// TODO: add here Windows specific header inclusions the device 
	// management may require.
	//-------------------------------------------------------------------------
#endif // __PL_WINDOWS__ 
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  

	#include <stdlib.h>
	//-------------------------------------------------------------------------
	// TODO: add here *NIX specific header inclusions the device 
	// management may require.
	//-------------------------------------------------------------------------
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "pub_esrv.h"
#include "esrv_daq_template_device_dynamic_library.h"

/*-----------------------------------------------------------------------------
Function: init_device_extra_data
Purpose : Initialize the device's data set.  This is done in two passes.
In      : A pointer to an ESRV data structure (as defined in pub_esrv.h).
Out     : Modified ESRV data structure.
Return  : Status code.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int init_device_extra_data(PESRV p) {

	//-------------------------------------------------------------------------
	// The device data structure is allocated in this function and 
	// is static.  The address of this structure is stored into the server's
	// data structure at the end of the first call of this function.
	//-------------------------------------------------------------------------
	static int f_first_init_call = 0;
	static DEVICE_DATA data;
	PDEVICE_DATA py = NULL;

	if(p == NULL) { 
		goto init_device_extra_data_error; 
	}

	if(f_first_init_call == 0) {

		//---------------------------------------------------------------------
		// First call from driver - before device option string parsing.
		//---------------------------------------------------------------------
		memset(
			&data, 
			0, 
			sizeof(DEVICE_DATA)
		);
		py = (void *)&data;

		//---------------------------------------------------------------------
		// Add all initializations the device may require.  Add
		// the additional data into the definition of the DEVICE_DATA
		// structure (defined in template_device_dynamic_library.h file).
		// Use statically allocated data or dynamically allocated data.
		// If the data is dynamically allocated, then it can be done either
		// at first or second call of this function.  If using dynamically 
		// allocated data, it *must* be de-allocated at program end.  There
		// is an opportunity to do so in the delete_template_device_extra_data
		// function which is called at the server's end.
		//---------------------------------------------------------------------
		// TODO: add the first call initialization code
		py->dummy = 0;

		//---------------------------------------------------------------------
		// Set the default channel count (1 based).  If the device
		// has 10 channels, then set this variable to 10.
		// Channels count must be <= DAQ_SERVER_KERNEL_MAX_CHANNELS.
		//---------------------------------------------------------------------
		// TODO: set the default channel count (1 based).
		p->daq_channel_count = 1;

		//---------------------------------------------------------------------
		// Set the f_daq_optimized_data_read flag if the device can 
		// provide all the channel readings in a single call.  If this flag is
		// set, then read_device_all_channels is called at the update frequency
		// (1Hz by default) by the server.  Otherwise, the read_device_channel
		// function will be called for each active channels.
		//---------------------------------------------------------------------
		// TODO: position the f_daq_optimized_data_read flag
		p->f_daq_optimized_data_read = 1;

		//---------------------------------------------------------------------
		// Link of the data structure into the server's data structure
		//---------------------------------------------------------------------
		p->device_data.p_device_data = (void *)&data;

		//---------------------------------------------------------------------
		// A library supported device may use a proprietary interface, or a
		// proprietary driver, or a non-supported protocol to communicate with
		// the server (for example the Yokogawa WT500 uses a dedicated driver,
		// TCP/IP and Vxi11 protocol).  In this case, the device - in the 
		// init_device_extra_data library function - sets the device_interface 
		// to ESRV_DEVICE_INTERFACE_PROPRIETARY, overwriting the default 
		// ESRV_DEVICE_INTERFACE_SERIAL.  It is then the device's 
		// responsibility to manage its interface.  This is done in the 
		// open_device and close_device functions.  Note that the device can
		// still use the interface_options to collect device specific options
		// (and therefore allow for the proprietary interface configuration).
		//---------------------------------------------------------------------
		p->device_interface = ESRV_DEVICE_INTERFACE_PROPRIETARY;

		//---------------------------------------------------------------------
		// Set the first call flag to 1.  This flag is used to distinguish the 
		// first from the second call in this function.
		//---------------------------------------------------------------------
		f_first_init_call = 1;

	} else {

		//---------------------------------------------------------------------
		// Second call from the driver - post device option string parsing.
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		// Add all additional initializations the device may require.  Add
		// the additional data into the definition of the DEVICE_DATA
		// structure (defined in template_device_dynamic_library.h file).
		// Use statically allocated data or dynamically allocated data.
		// If using dynamically allocated data, it *must* be de-allocated at 
		// program end.  There is an opportunity to do so in the 
		// delete_template_device_extra_data function which is called at the 
		// server's end.
		//---------------------------------------------------------------------
		// TODO: add the second call initialization code
		;
	}

	return(ESRV_SUCCESS);
init_device_extra_data_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: delete_device_extra_data
Purpose : Free the device's dynamically allocated data.
In      : Pointer to an ESRV data structure.
Out     : Updated ESRV data structure.
Return  : Status code.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int delete_device_extra_data(PESRV p) {

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//PDEVICE_DATA py = NULL;

	//-------------------------------------------------------------------------

	if(p == NULL) { 
		goto delete_device_extra_data_error; 
	}

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//py = p->device_data.p_device_data;
	//assert(py != NULL);

	//-------------------------------------------------------------------------
	// This function is called at the end of the ESRV server run.  It is the
	// right location to de-allocate any dynamically allocated data used by
	// the device.
	//-------------------------------------------------------------------------
	// TODO: add the de-allocation code here
	;

	return(ESRV_SUCCESS);
delete_device_extra_data_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: open_device.
Purpose : Open the DAQ device.
In      : Pointers to an ESRV and a DEVICE_DATA data structure.
Out     : Modified data structures.
Return  : Status code.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int open_device(PESRV p, void *px) {

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//PDEVICE_DATA py = NULL;

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Note:
	//    px can be NULL if not required by the device.
	//-------------------------------------------------------------------------
	if(p == NULL) { 
		goto open_device_error; 
	}

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//if(px != NULL) {
	//	py = (PDEVICE_DATA)px;
	//}

	//-------------------------------------------------------------------------
	// This function provides the opportunity to open the device.  It is also a
	// good location to perform device initializations.  This function can be a
	// stub function if the device doesn't require any specific configurations
	// to work.
	//-------------------------------------------------------------------------
	// TODO: add the device's open code here
	;

	return(ESRV_SUCCESS);
open_device_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: close_device.
Purpose : Close the DAQ device.
In      : Pointers to an ESRV and a DEVICE_DATA data structure.
Out     : Modified data structures.
Return  : Status code.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int close_device(PESRV p, void *px) {

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//PDEVICE_DATA py = NULL;

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Note:
	//    px can be NULL if not required by the device.
	//-------------------------------------------------------------------------
	if(p == NULL) { 
		goto close_device_error; 
	}

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//if(px != NULL) {
	//	py = (PDEVICE_DATA)px;
	//}

	//-------------------------------------------------------------------------
	// This function provides the opportunity to close the device.  This 
	// function can be a stub function if the device doesn't require any 
	// specific shutdown. 
	//-------------------------------------------------------------------------
	// TODO: add the device's close code here
	;

	return(ESRV_SUCCESS);
close_device_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_all_channels.
Purpose : Read all DAQ channels.
In      : Pointers to an ESRV and a DEVICE_DATA data structure.
Out     : Updated data structures.
Return  : Status code.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_all_channels(PESRV p, void *px) {

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//PDEVICE_DATA py = NULL;

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Note:	
	//    px can be NULL if not required by the device.
	//-------------------------------------------------------------------------
	if(p == NULL) { 
		goto read_device_all_channels_error; 
	}

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//if(px != NULL) {
	//	py = (PDEVICE_DATA)px;
	//}

	//-------------------------------------------------------------------------
	// Note the double indirection of the readings array.
	// This is due to the fact that ESRV compresses the active channels table
	// as it is expected to not use all channels often.  The cost of running
	// through the entire table by the ESRV kernel is too expresive.
	// daq_channel_readings[daq_active_channels[i]]
	//-------------------------------------------------------------------------
	//   for(i = 0; i < p->daq_active_channels_count; i++) {
	//	    p->daq_channel_readings[p->daq_active_channels[i]] = 0.0;
	//   }
	//-------------------------------------------------------------------------
	// TODO: read all DAQ channels and store values in ->daq_channel_readings[].
	// p->daq_channel_status[p->daq_active_channels[i]] = <ESRV_SUCCESS|ESRV_FAILURE>;
	;

	return(ESRV_SUCCESS);
read_device_all_channels_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_channel.
Purpose : Read a given DAQ channel.  Use of this function is not encouraged.
In      : Pointers to an ESRV and a DEVICE_DATA data structure and a channel #
Out     : Updated data structures.
Return  : Status code.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_channel(PESRV p, void *px, int c) {

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//PDEVICE_DATA py = NULL;

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Note:	
	//    px can be NULL if not required by the device.
	//-------------------------------------------------------------------------
	if(p == NULL) { 
		goto read_device_channel_error; 
	}

	if(
		(c < 0) ||
		(c >= p->daq_channel_count)
	) { 
		goto read_device_channel_error; 
	}

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//if(px != NULL) {
	//	py = (PDEVICE_DATA)px;
	//}

	//-------------------------------------------------------------------------
	// Note the double indirection of the readings array.
	// This is due to the fact that ESRV compresses the active channels table
	// as it is expected to not use all channels often and the cost of running
	// through the entire table by the ESRV kernel is too expresive.
	// daq_channel_readings[daq_active_channels[c]]
	//-------------------------------------------------------------------------
	// p->daq_channel_readings[p->daq_active_channels[c]] = 0.0;
	//-------------------------------------------------------------------------
	// TODO: read the required DAQ channels and store values in 
	// p->daq_channel_readings[].
	// p->daq_channel_status[p->daq_active_channels[c]] = <ESRV_SUCCESS|ESRV_FAILURE>;
	;

	return(ESRV_SUCCESS);
read_device_channel_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: parse_device_option_string
Purpose : Parse the device options string and set the devices data structure
          members if required.
In      : Pointers to an ESRV and a DEVICE_DATA data structure.
Out     : Modified data structures.
Return  : Status code.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int parse_device_option_string(PESRV p, void *px) {

	char *ps = NULL;

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//PDEVICE_DATA py = NULL;

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Note:	
	//    px can be NULL if not required by the device.
	//-------------------------------------------------------------------------
	if(p == NULL) { 
		goto parse_device_option_string_error;	
	}

	//-------------------------------------------------------------------------
	// You can use the py pointer to access to your device's data.
	//-------------------------------------------------------------------------
	//if(px != NULL) {
	//	py = (PDEVICE_DATA)px;
	//}

	ps = p->device_option_string;
	assert(ps != NULL);

	//-------------------------------------------------------------------------
	// If the user may need to provide configuration information for the 
	// device, then provide a parsing function of the device option string.
	// This string is pointed by the (ps) pointer.  This function can be a stub 
	// function if the device doesn't offer user accessible options.
	// These options should be defined in the DEVICE_DATA data structure, and 
	// this function should update those options in this function.
	//-------------------------------------------------------------------------
	// TODO: add the device's option string parsing code here
	;

	return(ESRV_SUCCESS);
parse_device_option_string_error:
	return(ESRV_FAILURE);
}
