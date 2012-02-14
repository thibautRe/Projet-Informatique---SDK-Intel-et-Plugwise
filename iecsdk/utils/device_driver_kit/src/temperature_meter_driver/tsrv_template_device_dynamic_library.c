//-----------------------------------------------------------------------------
// function call sequence by the server
//-----------------------------------------------------------------------------
// 1 - .....TSRV_API int init_device_extra_data(PTSRV); // first call
// 2 - .....TSRV_API int parse_device_option_string(PTSRV, void *);
// 3 - .....TSRV_API int init_device_extra_data(PTSRV); // second call
// 4 - .....TSRV_API int open_device(PTSRV, void *);
// 5 - N.......TSRV_API int read_device_temperature(PTSRV, void *, int);
//      .......TSRV_API int read_device_humidity(PTSRV, void *, int);
// N + 1 - .TSRV_API int close_device(PTSRV, void *);
// N + 2 - .TSRV_API int delete_device_extra_data(PTSRV);
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include <string.h>
#include <assert.h>
#ifdef __PL_WINDOWS__
	// TODO: add here Windows specific header inclusions 
	// the device management may require.
#endif // __PL_WINDOWS__ 
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#include <stdlib.h>
	// TODO: add here *NIX specific header inclusions 
	// the device management may require.
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "pub_tsrv.h"
#include "tsrv_template_device_dynamic_library.h"

/*-----------------------------------------------------------------------------
Function: init_device_extra_data
Purpose : initialize the device's extra data set
In      : pointer to an tsrv data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
TSRV_API int init_device_extra_data(PTSRV p) {

	//-------------------------------------------------------------------------
	// The device data structure is allocated in this function and 
	// is static.  The address of this structure is linked into the server's
	// data structure at the end of the first call of this function.
	//-------------------------------------------------------------------------
	static DEVICE_DATA data;
	static int f_first_init_call = 0;
	PDEVICE_DATA px = NULL;

	if(!p) { 
		goto init_device_extra_data_error; 
	}

	if(f_first_init_call == 0) {

		//---------------------------------------------------------------------
		// first call from driver - before device option string parsing
		//---------------------------------------------------------------------
		memset(
			&data, 
			0, 
			sizeof(DEVICE_DATA)
		);
		px = (void *)&data;

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
		px->dummy = 0;

		//---------------------------------------------------------------------
		// Set the default virtual device count (1 based).  If the device
		// integrates 3 independent temperature readers sharing the same 
		// interface (source), then set this variable (virtual_devices) to 3.
		// Later on, the server will use this information to query each virtual
		// device independently, by providing the virtual device's id (0 based)
		// in the call to the read_device_temperature and read_device_humidity
		// functions.
		//---------------------------------------------------------------------
		// TODO: set the default virtual device count (1 based).
		p->device_data.virtual_devices = 1;

		//---------------------------------------------------------------------
		// Link of the data structure into the server's data structure
		//---------------------------------------------------------------------
		p->device_data.p_device_data = (void *)&data;

		//---------------------------------------------------------------------
		// a library supported device may use a proprietary interface to 
		// communicate with the server.  In this case, the device - in the 
		// init_device_extra_data library function - sets the device_interface
		// to TSRV_DEVICE_INTERFACE_PROPRIETARY, overwriting the default 
		// TSRV_DEVICE_INTERFACE_SERIAL.
		// it is then the device's responsibility to manage its interface.  
		// This is done in the open_device and close_device functions.  
		// Note that the device can still use the interface_options to collect 
		// device specific options (and therefore allow for the proprietary 
		// interface configuration).
		//---------------------------------------------------------------------
		p->device_interface = TSRV_DEVICE_INTERFACE_PROPRIETARY;

		//---------------------------------------------------------------------
		// Set the first call flag to 1.  This flag is used to distinguish the 
		// first from the second call in this function.
		//---------------------------------------------------------------------
		f_first_init_call = 1;

	} else {

		//---------------------------------------------------------------------
		// Second call from the driver - post device option string parsing
		//---------------------------------------------------------------------
		
		//---------------------------------------------------------------------
		// Add all additional initializations the device may require.  Add
		// the additional data into the definition of the DEVICE_DATA
		// structure (defined in template_device_dynamic_library.h file).
		// Use statically allocated data or dynamically allocated data.
		// If using dynamically allocated data, it *must* be de-allocated at 
		// program end.
		// There is an opportunity to do so in the 
		// delete_template_device_extra_data function which is called at the
		// server's end.
		//---------------------------------------------------------------------
		// TODO: add the second call initialization code
		;

	}

	return(TSRV_SUCCESS);
init_device_extra_data_error:
	return(TSRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: delete_device_extra_data
Purpose : free the device's dynamically allocated data
In      : pointer to a tsrv data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
TSRV_API int delete_device_extra_data(PTSRV p) {

	if(!p) { 
		goto delete_device_extra_data_error; 
	}

	//-------------------------------------------------------------------------
	// This function is called at the end of the server's run.  It is the
	// right location to de-allocate any dynamically allocated data used by
	// the device.
	//-------------------------------------------------------------------------
	// TODO: add the de-allocation code here
	;

	return(TSRV_SUCCESS);
delete_device_extra_data_error:
	return(TSRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: open_device.
Purpose : open the template device.
In      : pointers to a tsrv and a DEVICE_DATA data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
TSRV_API int open_device(PTSRV p, void *px) {

	// px can be NULL if not required by device
	if(!p) { 
		goto open_device_error; 
	}

	//-------------------------------------------------------------------------
	// This function provides the opportunity to open the device.  It is also a
	// good location to perform device initializations.  This function can be a
	// stub function if the device doesn't require any specific configurations 
	// to work.
	//-------------------------------------------------------------------------
	// TODO: add the device's open code here
	;

	return(TSRV_SUCCESS);
open_device_error:
	return(TSRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: close_device.
Purpose : close the template device.
In      : pointers to a tsrv and a DEVICE_DATA data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
TSRV_API int close_device(PTSRV p, void *px) {

	// px can be NULL if not required by device
	if(!p) { 
		goto close_device_error; 
	}

	//-------------------------------------------------------------------------
	// This function provides the opportunity to close the device.  This 
	// function can be a stub function if the device doesn't require any 
	// specific shutdown. 
	//-------------------------------------------------------------------------
	// TODO: add the device's close code here
	;

	return(TSRV_SUCCESS);
close_device_error:
	return(TSRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_temperature.
Purpose : read temperature from template device.
In      : pointers to a tsrv and a DEVICE_DATA data structure
          and the virtual device's id
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
TSRV_API int read_device_temperature(PTSRV p, void *px, int vd) {

	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_temperature_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) {
		goto read_device_temperature_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the temperature read by the device here and return it in 
	// (p->double_temperature)
	// The (vd) integer is the id of the virtual device queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The temperature must be provided in Kelvin.
	//-------------------------------------------------------------------------
	// TODO: add the device's temperature read code here (in Kelvin)
	// p->double_temperature = ...;
	;
	
	return(TSRV_SUCCESS);
read_device_temperature_error:
	return(TSRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_humidity.
Purpose : read energy from template device.
In      : pointers to a tsrv and a DEVICE_DATA data structure.
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
TSRV_API int read_device_humidity(PTSRV p, void *px, int vd) {

	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_humidity_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) {
		goto read_device_humidity_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the humidity read by the device here and return it in 
	// (p->double_humidity)
	// The (vd) integer is the id of the virtual device queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The humidity must be provided in %.
	//-------------------------------------------------------------------------
	// TODO: add the device's humidity read code here (in %)
	// p->double_humidity = ...;
	;

	return(TSRV_SUCCESS);
read_device_humidity_error:
	return(TSRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: parse_device_option_string
Purpose : parse the device option string and set the tsrv structure
In      : pointers to a tsrv and a DEVICE_DATA data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
TSRV_API int parse_device_option_string(PTSRV p, void *pd) {

	char *ps = NULL;

	// pd can be NULL if not required by device
	if(!p) { 
		goto parse_device_option_string_error;	
	}

	ps = p->device_option_string;
	assert(ps);

	//-------------------------------------------------------------------------
	// If the user may need to provide configuration information for the device
	// then provide a parsing function of the device option string.
	// This string is pointed by the (ps) pointer.  This function can be a stub 
	// function if the device doesn't offer user accessible options.
	// These options should be defined in the DEVICE_DATA data structure, and 
	// this function should update those options in this function.
	//-------------------------------------------------------------------------
	// TODO: add the device's option string parsing code here
	;

	return(TSRV_SUCCESS);
parse_device_option_string_error:
	return(TSRV_FAILURE);
}
