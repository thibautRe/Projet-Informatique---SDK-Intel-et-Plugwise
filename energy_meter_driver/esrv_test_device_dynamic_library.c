//-----------------------------------------------------------------------------
// function call sequence by the server
//-----------------------------------------------------------------------------
// 1 - .....ESRV_API int init_device_extra_data(PESRV); // first call
// 2 - .....ESRV_API int parse_device_option_string(PESRV, void *);
// 3 - .....ESRV_API int init_device_extra_data(PESRV); // second call
// 4 - .....ESRV_API int open_device(PESRV, void *);
// 5 - N.......ESRV_API int read_device_power(PESRV, void *, int);
//      .......ESRV_API int read_device_energy(PESRV, void *, int); if available
// N + 1 - .ESRV_API int close_device(PESRV, void *);
// N + 2 - .ESRV_API int delete_device_extra_data(PESRV);
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include <stdio.h>
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
#include "pub_esrv.h"
#include "esrv_test_device_dynamic_library.h"

/*-----------------------------------------------------------------------------
Function: init_device_extra_data
Purpose : initialize the device's extra data set
In      : pointer to an esrv data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int init_device_extra_data(PESRV p) {
	  printf("coucou0 - initialize\n");

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
	  printf("coucou1 - First call initialize\n");
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
		// integrates 3 independent power readers sharing the same interface 
		// (source), then set this variable (virtual_devices) to 3.
		// Later on, the server will use this information to query each virtual
		// device independently, by providing the virtual device's id (0 based)
		// in the call to the read_device_power function.
		//---------------------------------------------------------------------
		// TODO: set the default virtual device count (1 based).
		p->device_data.virtual_devices = 1;

		//---------------------------------------------------------------------
		// Set the f_hw_energy_integration_provided flag if the device can 
		// provide  hardware power integration.  If this flag is set, then 
		// read_device_energy is called at the update frequency (1Hz by default)
		// by the server.  As for the read_device_power function, the virtual
		// device's id is provided during the read_device_energy function.
		//---------------------------------------------------------------------
		// TODO: position the f_hw_energy_integration_provided flag
		p->f_hw_energy_integration_provided = 0;

		//---------------------------------------------------------------------
		// Link of the data structure into the server's data structure
		//---------------------------------------------------------------------
		p->device_data.p_device_data = (void *)&data;

		//---------------------------------------------------------------------
		// a library supported device may use a proprietary interface to 
		// communicate with the server (for example the Yokogawa WT500 uses a 
		// modified TCP/IP interface).  In this case, the device - in the 
		// init_device_extra_data library function - sets the device_interface 
		// to ESRV_DEVICE_INTERFACE_PROPRIETARY, overwriting the default 
		// ESRV_DEVICE_INTERFACE_SERIAL. It is then the device's responsibility
		// to manage its interface.  This is done in the open_device and 
		// close_device functions.  Note that the device can still use the 
		// interface_options to collect device specific options (and therefore
		// allow for the proprietary interface configuration).
		//---------------------------------------------------------------------
		p->device_interface = ESRV_DEVICE_INTERFACE_PROPRIETARY;

		//---------------------------------------------------------------------
		// Set the first call flag to 1.  This flag is used to distinguish 
		// the first from the second call in this function.
		//---------------------------------------------------------------------
		f_first_init_call = 1;

	} else {
	  printf("coucou2 - Second call initialize\n");

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

	return(ESRV_SUCCESS);
init_device_extra_data_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: delete_device_extra_data
Purpose : free the device's dynamically allocated data
In      : pointer to an esrv data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int delete_device_extra_data(PESRV p) {

	printf("coucou3 - delete extra data\n");
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

	return(ESRV_SUCCESS);
delete_device_extra_data_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: open_device.
Purpose : open the template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int open_device(PESRV p, void *px) {

	printf("coucou4 - open device\n");
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

	return(ESRV_SUCCESS);
open_device_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: close_device.
Purpose : close the template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int close_device(PESRV p, void *px) {

	printf("coucou5 - close device\n");
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

	return(ESRV_SUCCESS);
close_device_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_all_measurements.
Purpose : read all measurements from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
          and the virtual device's id
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_all_measurements(PESRV p, void *px, int vd) {

	printf("Coucou6 - read device all \n");
	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_power_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) { 
		goto read_device_power_error; 
	}

	//-------------------------------------------------------------------------
	// Collect all measurements read by the device here and return it in (see 
	// code below). The (vd) integer is the id of the virtual device queried by
	// the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.
	//-------------------------------------------------------------------------
	p->double_power = 0.0;
	p->double_current = 0.0;
	p->double_voltage = 0.0;
	p->double_power_factor = 0.0;
	p->double_voltage_frequency = 0.0;
	p->double_current_frequency = 0.0;
	
	return(ESRV_SUCCESS);
read_device_power_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_power.
Purpose : read power from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
          and the virtual device's id
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_power(PESRV p, void *px, int vd) {

	printf("Coucou7 - read device power\n");
	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_power_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) { 
		goto read_device_power_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the power read by the device here and return it in 
	// (p->double_power). The (vd) integer is the id of the virtual device 
	// queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The power must be provided in Watts.
	//-------------------------------------------------------------------------
	// TODO: add the device's power read code here (in Watts)
	;
	
	return(ESRV_SUCCESS);
read_device_power_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_energy.
Purpose : read energy from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure,
          the virtual device's id and the service request
          READ_DEVICE_ENERGY_INIT: requested once, at server start
          READ_DEVICE_ENERGY_START: requested once, at server start right after
		  READ_DEVICE_ENERGY_INIT
          READ_DEVICE_ENERGY_READ: requested at will, possibly indefinitely
          READ_DEVICE_ENERGY_STOP: requested once at server stop
          READ_DEVICE_ENERGY_RESET: requested at will, possibly indefinitely
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_energy(PESRV p, void *px, int vd, int s) {

	printf("Coucou8 - read device energy\n");
	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_energy_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the energy integrated by the device here and return it in 
	// (p->double_energy)
	// The (vd) integer is the id of the virtual device queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The power must be provided in Joules.
	//-------------------------------------------------------------------------
	switch(s) { 
	
		case READ_DEVICE_ENERGY_INIT:
			// TODO: process service request
			break;

		case READ_DEVICE_ENERGY_START:
			// TODO: process service request
			break;

		case READ_DEVICE_ENERGY_RESET:
			// TODO: process service request
			break;

		case READ_DEVICE_ENERGY_STOP:
			// TODO: process service request
			break;

		case READ_DEVICE_ENERGY_READ:
			//-----------------------------------------------------------------
			// you must return power (in watts) and integrated energy (in 
			// joules)
			// NOTE: handle integrated energy overflow gracefully!  The server
			// is supposed to run for months, years, etc.
			//-----------------------------------------------------------------
			// TODO: process service request
			p->double_power = 0.0;
			p->double_energy = 0.0;
			break;

		default: // unknown service
			assert(0); // should never happen
			goto read_device_energy_error;
	}

	return(ESRV_SUCCESS);
read_device_energy_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: parse_device_option_string
Purpose : parse the device option string and set the esrv structure
In      : pointers to an esrv and a DEVICE_DATA data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int parse_device_option_string(PESRV p, void *pd) {

	char *ps = NULL;

	printf("Coucou9 - parse device machin\n");
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

	return(ESRV_SUCCESS);
parse_device_option_string_error:
	return(ESRV_FAILURE);
}

/*
 @@@@  @@@@@   @@@@@ @@@@@   @@@@  @    @   @@   @             @@@@@@ @    @ @    @  @@@@   @@@@@ @@@@@   @@@@  @    @  @@@@
@    @ @    @    @     @    @    @ @@   @  @  @  @             @      @    @ @@   @ @    @    @     @    @    @ @@   @ @    @
@    @ @    @    @     @    @    @ @ @  @ @    @ @             @      @    @ @ @  @ @         @     @    @    @ @ @  @ @
@    @ @@@@@     @     @    @    @ @ @  @ @    @ @             @@@@@  @    @ @ @  @ @         @     @    @    @ @ @  @  @@@@
@    @ @         @     @    @    @ @  @ @ @@@@@@ @             @      @    @ @  @ @ @         @     @    @    @ @  @ @      @
@    @ @         @     @    @    @ @   @@ @    @ @             @      @    @ @   @@ @    @    @     @    @    @ @   @@      @
 @@@@  @         @   @@@@@   @@@@  @    @ @    @ @@@@@@        @       @@@@  @    @  @@@@     @   @@@@@   @@@@  @    @ @@@@@
*/

/*-----------------------------------------------------------------------------
Function: current.
Purpose : read current from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
          and the virtual device's id
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_current(PESRV p, void *px, int vd) {

	printf("CoucouA\n");
	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_current_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) { 
		goto read_device_current_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the current read by the device here and return it in 
	// (p->double_current)
	// The (vd) integer is the id of the virtual device queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The current must be provided in Amps.
	//-------------------------------------------------------------------------
	// TODO: add the device's current read code here (in Amps)
	p->double_current = 0.0;
	
	return(ESRV_SUCCESS);
read_device_current_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: voltage.
Purpose : read voltage from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
          and the virtual device's id
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_voltage(PESRV p, void *px, int vd) {

	printf("CoucouB\n");
	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_voltage_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) { 
		goto read_device_voltage_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the voltage read by the device here and return it in 
	// (p->double_voltage)
	// The (vd) integer is the id of the virtual device queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The voltage must be provided in Volts.
	//-------------------------------------------------------------------------
	// TODO: add the device's voltage read code here (in Volts)
	p->double_voltage = 0.0;
	
	return(ESRV_SUCCESS);
read_device_voltage_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: power_factor.
Purpose : read power_factor from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
          and the virtual device's id
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_power_factor(PESRV p, void *px, int vd) {

	printf("CoucouC\n");
	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_power_factor_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) { 
		goto read_device_power_factor_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the power_factor read by the device here and return it in 
	// (p->double_power_factor)
	// The (vd) integer is the id of the virtual device queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The power_factor has no unit.
	//-------------------------------------------------------------------------
	// TODO: add the device's power_factor read code here
	p->double_power_factor = 0.0;
	
	return(ESRV_SUCCESS);
read_device_power_factor_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: voltage_frequency.
Purpose : read voltage_frequency from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
          and the virtual device's id
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_voltage_frequency(PESRV p, void *px, int vd) {

	printf("CoucouD\n");
	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_voltage_frequency_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) { 
		goto read_device_voltage_frequency_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the voltage_frequency read by the device here and return it in 
	// (p->double_voltage_frequency)
	// The (vd) integer is the id of the virtual device queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The voltage_frequency must be provided in Hz.
	//-------------------------------------------------------------------------
	// TODO: add the device's voltage_frequency read code here (in Hz)
	p->double_voltage_frequency = 0.0;
	
	return(ESRV_SUCCESS);
read_device_voltage_frequency_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: current_frequency.
Purpose : read current_frequency from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure
          and the virtual device's id
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
00/00/0000    Your Name               Creation.
*/
ESRV_API int read_device_current_frequency(PESRV p, void *px, int vd) {

	printf("CoucouE\n");
	// px can be NULL if not required by device
	if(!p) { 
		goto read_device_current_frequency_error; 
	}

	//-------------------------------------------------------------------------
	// validity check on virtual device count.
	// Note: virtual device id is 1 based (0 has a special meaning)
	//-------------------------------------------------------------------------
	if(
		(vd <= 0) || 
		(vd > p->device_data.virtual_devices)
	) { 
		goto read_device_current_frequency_error; 
	}

	//-------------------------------------------------------------------------
	// Collect the current_frequency read by the device here and return it in 
	// (p->double_current_frequency)
	// The (vd) integer is the id of the virtual device queried by the server.
	// (vd) can be any integer between 0 and the maximum virtual device number
	// provided in the init_device_extra_data function.  By default,
	// the max vd is equal to 0.  The current_frequency must be provided in Hz.
	//-------------------------------------------------------------------------
	// TODO: add the device's current_frequency read code here (in Hz)
	p->double_current_frequency = 0.0;
	
	return(ESRV_SUCCESS);
read_device_current_frequency_error:
	return(ESRV_FAILURE);
}
