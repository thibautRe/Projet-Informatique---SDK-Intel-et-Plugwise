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
#include "esrv.h"
#include "interface_control.h"
#include "service.h"
#include "p3_kill_a_watt_adafruit.h"

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
04/07/2010    Jamel Tayeb              Creation.
*/
ESRV_API int init_device_extra_data(PESRV p) {

	//-------------------------------------------------------------------------
	// The device data structure is allocated in this function and 
	// is static.  The address of this structure is linked into the server's
	// data structure at the end of the first call of this function.
	//-------------------------------------------------------------------------
	static DEVICE_DATA data;
	static int f_first_init_call = 0;
	PDEVICE_DATA px = NULL;
	size_t memory_size = 0;

	if(p == NULL) { 
		goto init_device_extra_data_error; 
	}

	if(f_first_init_call == 0) {

		memset(&data, 0, sizeof(DEVICE_DATA));
		px = (void *)&data;
		
		p->device_data.virtual_devices = P3_KILL_A_WATT_ADAFRUIT_MIN_KILL_A_WATTS;
		p->device_interface = ESRV_DEVICE_INTERFACE_SERIAL;
		p->f_optimized_data_read = 1;
		p->f_hw_energy_integration_provided = 0;
		
		p->device_data.p_device_data = (void *)&data;
		f_first_init_call = 1;

	} else {

		//---------------------------------------------------------------------
		// note: dc offset data memory was allocated in the cli perser
		//---------------------------------------------------------------------
		px = p->device_data.p_device_data;
		assert(px != NULL);

		//---------------------------------------------------------------------
		// note: if aggregation is requested, only one - aggregated - virtual
		// device will be exposed to ESRV.
		//---------------------------------------------------------------------
		if((px->f_channels_count_provided == 1) && (px->f_aggrerate == 0)) {
			p->device_data.virtual_devices = px->kill_a_watts_count;
		}

		//---------------------------------------------------------------------
		// allocate memory to store sensors data
		//---------------------------------------------------------------------
		memory_size = sizeof(P3_KILL_A_WATT_ADAFRUIT_SAMPLES_BUFFER) * p->device_data.virtual_devices;
		px->data_buffers = (PP3_KILL_A_WATT_ADAFRUIT_SAMPLES_BUFFER)malloc(memory_size);
		if(px->data_buffers == NULL) { goto init_device_extra_data_error; }
		memset(px->data_buffers, 0, memory_size);

		memory_size = sizeof(int) * p->device_data.virtual_devices;
		px->f_kill_a_watts_data_frame_received = (int *)malloc(memory_size);
		if(px->f_kill_a_watts_data_frame_received == NULL) { goto init_device_extra_data_error; }
		memset(px->f_kill_a_watts_data_frame_received, 0, memory_size);
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
04/07/2010    Jamel Tayeb              Creation.
*/
ESRV_API int delete_device_extra_data(PESRV p) {

	PDEVICE_DATA px = NULL;

	if(p == NULL) { 
		goto delete_device_extra_data_error; 
	}

	px = p->device_data.p_device_data;
	assert(px != NULL);

	//-------------------------------------------------------------------------
	// note: dc offset data memory was allocated in the cli perser
	//-------------------------------------------------------------------------
	if(px->f_dc_offsets_provided == 1) {
		if(px->dc_offsets_in_amperes != NULL) {
			free(px->dc_offsets_in_amperes);
			px->dc_offsets_in_amperes = NULL;
		}
	}

	//-------------------------------------------------------------------------
	// free memory used to store sensors data
	//-------------------------------------------------------------------------
	if(px->data_buffers != NULL) {
		free(px->data_buffers);
		px->data_buffers = NULL;
	}

	if(px->f_kill_a_watts_data_frame_received != NULL) {
		free(px->f_kill_a_watts_data_frame_received);
		px->f_kill_a_watts_data_frame_received = NULL;
	}

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
04/07/2010    Jamel Tayeb              Creation.
*/
ESRV_API int open_device(PESRV p, void *px) {
	return(ESRV_SUCCESS);
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
04/07/2010    Jamel Tayeb              Creation.
*/
ESRV_API int close_device(PESRV p, void *px) {
	return(ESRV_SUCCESS);
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
04/07/2010    Jamel Tayeb              Creation.
*/
ESRV_API int read_device_all_measurements(PESRV p, void *px, int vd) {

	int i = 0;
	int offset = 0;
	int kill_a_watts_received_count = 0;
	unsigned short length = 0;
	unsigned short address = 0;
	unsigned char rssi = 0;
	unsigned char samples_count = 0;
	unsigned char channel_indicator_high = 0;
	unsigned char channel_indicator_low = 0;
	int f_address_broadcast = 0;
	int f_pan_broadcast = 0;
	ESRV_STATUS ret = ESRV_FAILURE;
	PDEVICE_DATA py = NULL;

	//-------------------------------------------------------------------------

	if(p == NULL) { goto read_device_all_measurements_error; }
	py = p->device_data.p_device_data;
	assert(py != NULL);
	if((vd <= 0) || (vd > p->device_data.virtual_devices)) { 
		goto read_device_all_measurements_error; 
	}

	if(py->f_aggrerate == 1) {
		memset(py->f_kill_a_watts_data_frame_received, 0, (sizeof(int) * py->kill_a_watts_count));
	}

read_device_all_measurements_get_next_data_frame:

	//-------------------------------------------------------------------------
	// search for an XBEE_DATA_FRAME_START_IDENTIFIER in the data flow recei-
	// ved via the serial port.
	//-------------------------------------------------------------------------
	do {
		p->interface_data.bytes_to_read = XBEE_DATA_FRAME_START_IDENTIFIER_SIZE_IN_BYTES;
		ret = read_serial(p);
		if(ret != ESRV_SUCCESS) { 
			goto read_device_all_measurements_error; 
		}
	} while(p->interface_data.input_buffer[XBEE_DATA_FRAME_START_OFFSET] != XBEE_DATA_FRAME_START_IDENTIFIER);

	//-------------------------------------------------------------------------
	// read-in lenght MSB and LSB
	//-------------------------------------------------------------------------
	p->interface_data.bytes_to_read = 
		XBEE_DATA_FRAME_LENGTH_MSB_SIZE_IN_BYTES +
		XBEE_DATA_FRAME_LENGTH_LSB_SIZE_IN_BYTES;
	ret = read_serial(p);
	if(ret != ESRV_SUCCESS) { 
		goto read_device_all_measurements_error;
	}

	//-------------------------------------------------------------------------
	// decode data frame length
	//-------------------------------------------------------------------------
	length = 
		(p->interface_data.input_buffer[XBEE_DATA_FRAME_LENGTH_MSB_OFFSET] << 8) + 
		p->interface_data.input_buffer[XBEE_DATA_FRAME_LENGTH_LSB_OFFSET] +
		XBEE_DATA_FRAME_CHECKSUM_SIZE_IN_BYTES
	;

	//-------------------------------------------------------------------------
	// read-in the packed - knowing its length (including checksum)
	//-------------------------------------------------------------------------
	p->interface_data.bytes_to_read = length;
	ret = read_serial(p);
	if(ret != ESRV_SUCCESS) { 
		goto read_device_all_measurements_error; 
	}

	//-------------------------------------------------------------------------
	// check valid data frame type
	//-------------------------------------------------------------------------
	if(p->interface_data.input_buffer[XBEE_DATA_FRAME_START_OFFSET] != (char)XBEE_IO16) {
		goto read_device_all_measurements_get_next_data_frame;
	}

	//-------------------------------------------------------------------------
	// decode 16-bit address
	//-------------------------------------------------------------------------
	address = 
		(p->interface_data.input_buffer[XBEE_DATA_FRAME_16BIT_ADDRESS_MSB_OFFSET] << 8) + 
		p->interface_data.input_buffer[XBEE_DATA_FRAME_16BIT_ADDRESS_LSB_OFFSET]
	;

	//-------------------------------------------------------------------------
	// check if the address of the data frame matches the requested vd
	//-------------------------------------------------------------------------
	if(vd != address) {
		goto read_device_all_measurements_get_next_data_frame;
	}

	//-------------------------------------------------------------------------
	// decode rssi
	//-------------------------------------------------------------------------
	rssi = p->interface_data.input_buffer[XBEE_DATA_FRAME_RSSI_OFFSET];

	//-------------------------------------------------------------------------
	// decode address_broadcast
	//-------------------------------------------------------------------------
	if(((p->interface_data.input_buffer[XBEE_DATA_FRAME_BROADCAST_OFFSET] >> 1) & 0x01) == 1) {
		f_address_broadcast = 1;
	}

	//-------------------------------------------------------------------------
	// decode pan_broadcast
	//-------------------------------------------------------------------------
	if(((p->interface_data.input_buffer[XBEE_DATA_FRAME_BROADCAST_OFFSET] >> 2) & 0x01) == 1) {
		f_pan_broadcast = 1;
	}

	//-------------------------------------------------------------------------
	// decode samples_count
	//-------------------------------------------------------------------------
	samples_count = p->interface_data.input_buffer[XBEE_DATA_FRAME_TOTAL_SAMPLES_OFFSET];

	//-------------------------------------------------------------------------
	// decode channel_indicator high and low
	//-------------------------------------------------------------------------
	channel_indicator_high = p->interface_data.input_buffer[XBEE_DATA_FRAME_CHANNEL_INDICATOR_HIGH_OFFSET];
	channel_indicator_low = p->interface_data.input_buffer[XBEE_DATA_FRAME_CHANNEL_INDICATOR_LOW_OFFSET];

	//-------------------------------------------------------------------------
	// decode and store analog samples
	// note: first analog sample is discarded for quality reason
	//-------------------------------------------------------------------------
	//offset = ((int)samples_count * 2) + 2;
	offset = (int)samples_count * 2;
	for(i = 0; i <= (int)samples_count; i++) {

		//---------------------------------------------------------------------
		// store voltage and current sensors data
		//---------------------------------------------------------------------
		py->data_buffers[vd - 1].voltage_reading_buffer[i] = 
			(p->interface_data.input_buffer[offset + P3_KILL_A_WATT_ADAFRUIT_VOLTAGE_SENSOR + i] << 8) + 
			p->interface_data.input_buffer[offset + P3_KILL_A_WATT_ADAFRUIT_VOLTAGE_SENSOR + i + 1]
		;
		py->data_buffers[vd - 1].amperage_reading_buffer[i] = 
			(p->interface_data.input_buffer[offset + P3_KILL_A_WATT_ADAFRUIT_CURRENT_SENSOR + i] << 8) + 
			p->interface_data.input_buffer[offset + P3_KILL_A_WATT_ADAFRUIT_CURRENT_SENSOR + i + 1]
		;

		//---------------------------------------------------------------------
		// normalize sensor data
		//---------------------------------------------------------------------
		// TODO:

	}

	//-------------------------------------------------------------------------
	// kill-a-watts aggregation logic
	//-------------------------------------------------------------------------
	if(py->f_aggrerate == 1) {
		if(py->f_kill_a_watts_data_frame_received[address] == 0) {
			py->f_kill_a_watts_data_frame_received[address] = 1;
			kill_a_watts_received_count++;
			if(kill_a_watts_received_count == py->kill_a_watts_count) {
				//goto read_device_all_measurements_get_next_data_frame;
			}
		}
	}

	//-------------------------------------------------------------------------
	// average and report readings
	//-------------------------------------------------------------------------
	//	// TODO: add the device's power read code here (in Watts)
	//	p->double_current;
	//	p->double_voltage;
	//	p->double_power = p->double_current * p->double_voltage;

	return(ESRV_SUCCESS);
read_device_all_measurements_error:
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
04/07/2010    Jamel Tayeb              Creation.
*/
ESRV_API int read_device_power(PESRV p, void *px, int vd) {
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_energy.
Purpose : read energy from template device.
In      : pointers to an esrv and a DEVICE_DATA data structure,
          the virtual device's id and the service request
          READ_DEVICE_ENERGY_INIT: requested once, at server start
          READ_DEVICE_ENERGY_START: requested once, at server start right after READ_DEVICE_ENERGY_INIT
          READ_DEVICE_ENERGY_READ: requested at will, possibly indefinitely
          READ_DEVICE_ENERGY_STOP: requested once at server stop
          READ_DEVICE_ENERGY_RESET: requested at will, possibly indefinitely
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
04/07/2010    Jamel Tayeb              Creation.
*/
ESRV_API int read_device_energy(PESRV p, void *px, int vd, int s) {
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
04/07/2010    Jamel Tayeb              Creation.
*/
ESRV_API int parse_device_option_string(PESRV p, void *pd) {

	int i = 0;
	int j = 0;
	int t = 0;
	int f_error = 0;
	double offset = 0.0;
	PDEVICE_DATA py = NULL;
	ESRV_STATUS ret = ESRV_FAILURE;

	//-------------------------------------------------------------------------
	// variables used to tokenize the options string
	//-------------------------------------------------------------------------
	char *px = NULL;
	char *token = NULL;
	char *sub_token = NULL;
	char *buffer = NULL;
	char *sub_token_buffer = NULL;
	size_t length = 0;
	size_t memory_size = 0;
	int argc = 0;
	char *argv[P3_KILL_A_WATT_ADAFRUIT_MAX_TOKENS] = { NULL };
	char token_separators[] = " \t";
	char sub_token_separators[] = " \t=,";

	int sub_tokens_count = 0;
	char *sub_tokens_array[P3_KILL_A_WATT_ADAFRUIT_MAX_SUB_TOKENS] = { NULL };

	//-------------------------------------------------------------------------
	// variable holding authorized device options
	//-------------------------------------------------------------------------
	static char *p3_kill_a_watt_adafruit_option_tokens[P3_KILL_A_WATT_ADAFRUIT_OPTION_MAX_TOKENS] = { 
		P3_KILL_A_WATT_ADAFRUIT_OPTIONS 
	};

	//-------------------------------------------------------------------------

	if(p == NULL) { 
		f_error = 1;
		goto exit; 
	}
	py = p->device_data.p_device_data;
	assert(py != NULL);
	px = p->device_option_string;
	assert(px != NULL);

	//-------------------------------------------------------------------------
	// tokenize options string and build arcg / argv data, start by allocating
	// a buffer to copy the device options string.
	//-------------------------------------------------------------------------
	length = strlen(px);
	if(length == 0) { 
		f_error = 1;
		goto exit; 
	}
	length++;
	memory_size = sizeof(char) * length;
	buffer = (char *)malloc(memory_size);
	if(buffer == NULL) { 
		f_error = 1;
		goto exit; 
	}
	memset(buffer, '\0', memory_size);
	memcpy(buffer, px, length);

	//-------------------------------------------------------------------------
	// tokenize options string in sub-tokens
	//-------------------------------------------------------------------------
	token = strtok(buffer, token_separators);
	while(token != NULL) {

		//---------------------------------------------------------------------
		// allocate buffer to store sub-token
		//---------------------------------------------------------------------
		length = strlen(token);
		if(length == 0) { 
			f_error = 1;
			goto exit; 
		}
		length++;
		memory_size = sizeof(char) * length;
		sub_token_buffer = (char *)malloc(memory_size);
		if(sub_token_buffer == NULL) { 
			f_error = 1;
			goto exit; 
		}
		memset(sub_token_buffer, '\0', memory_size);
		memcpy(sub_token_buffer, token, length);
		sub_tokens_array[sub_tokens_count++] = sub_token_buffer;
		token = strtok(NULL, token_separators);
	}

	//-------------------------------------------------------------------------
	// free memory to store options string copy
	//-------------------------------------------------------------------------
	if(buffer != NULL) {
		free(buffer);
		buffer = NULL;
	}

	for(i = 0; i < sub_tokens_count; i++) {

		//---------------------------------------------------------------------
		// tokenize sub-token
		//---------------------------------------------------------------------
		sub_token = NULL;
		sub_token = strtok(sub_tokens_array[i], sub_token_separators);
		while(sub_token != NULL) {

			//-----------------------------------------------------------------
			// allocate buffer to store final token
			//-----------------------------------------------------------------
			length = strlen(sub_token);
			if(length == 0) { 
				f_error = 1;
				goto exit; 
			}
			length++;
			memory_size = sizeof(char) * length;
			sub_token_buffer = (char *)malloc(memory_size);
			if(sub_token_buffer == NULL) { 
				f_error = 1;
				goto exit; 
			}
			memset(sub_token_buffer, '\0', memory_size);
			memcpy(sub_token_buffer, sub_token, length);
			argv[argc++] = sub_token_buffer;
			sub_token = strtok(NULL, sub_token_separators);
		}

		//---------------------------------------------------------------------
		// free sub-token buffer memory
		//---------------------------------------------------------------------
		free(sub_tokens_array[i]);
		sub_tokens_array[i] = NULL;

	} // for i

	//-------------------------------------------------------------------------
	// parse device options and setup PESRV device data option structure
	//-------------------------------------------------------------------------
	//  [channels=<n>] [offsets=<o1>,...[<on>]] [aggrerate_channels]
	// example: --device_option "channels=3 offsets=500,498,502 aggrerate_channels"
	//-------------------------------------------------------------------------
	for(i = 0; i < argc; i++) { // for each argument
		service_upper_string(argv[i]);
		for(t = 0; t < P3_KILL_A_WATT_ADAFRUIT_OPTION_MAX_TOKENS; t++) { // for each allowed option token
			if(strncmp(argv[i],	p3_kill_a_watt_adafruit_option_tokens[t], strlen(argv[i])) == 0) {
				switch(t) {

					//---------------------------------------------------------
					// process channels <n> option
					//---------------------------------------------------------
					case P3_KILL_A_WATT_ADAFRUIT_CHANNELS_TOKEN_ID:
						if(i + 1 >= argc) { 
							f_error = 1;
							goto exit; 
						} 
						py->kill_a_watts_count = atoi(argv[++i]);
						if(
							(py->kill_a_watts_count < P3_KILL_A_WATT_ADAFRUIT_MIN_KILL_A_WATTS) ||
							(py->kill_a_watts_count > P3_KILL_A_WATT_ADAFRUIT_MAX_KILL_A_WATTS)
						) { 
							f_error = 1;
							goto exit; 
						}
						py->f_channels_count_provided = 1;
						goto next_argument;
						break;

					//---------------------------------------------------------
					// process offset <o1>...[<on>] option
					//---------------------------------------------------------
					case P3_KILL_A_WATT_ADAFRUIT_DC_OFFSETS_TOKEN_ID:
						if(i + py->kill_a_watts_count >= argc) { 
							f_error = 1;
							goto exit; 
						} 
						memory_size = sizeof(double) * py->kill_a_watts_count;
						py->dc_offsets_in_amperes = (double *)malloc(memory_size);
						if(py->dc_offsets_in_amperes == NULL) { 
							f_error = 1;
							goto exit; 
						}
						memset(py->dc_offsets_in_amperes, 0, memory_size);
						for(j = 0; j < py->kill_a_watts_count; j++) {
							offset = atof(argv[++i]);
							if(
								(offset < P3_KILL_A_WATT_ADAFRUIT_MIN_DC_OFFSET_IN_AMPERES) ||
								(offset > P3_KILL_A_WATT_ADAFRUIT_MAX_DC_OFFSET_IN_AMPERES)
							) { 
								f_error = 1;
								goto exit; 
							}
							py->dc_offsets_in_amperes[j] = offset;
						}
						py->f_dc_offsets_provided = 1;
						goto next_argument;
						break;

					//---------------------------------------------------------
					// process aggregate option
					//---------------------------------------------------------
					case P3_KILL_A_WATT_ADAFRUIT_AGGREGATE_CHANNELS_TOKEN_ID:
						py->f_aggrerate = 1;
						goto next_argument;
						break;

					default:
						f_error = 1;
						goto exit;
				} // switch
			} // if token recognized
		} // for each allowed option token (t)
next_argument:
		;
	} // for for each argument (i)

exit:

	//-------------------------------------------------------------------------
	// clean-up and exit
	//-------------------------------------------------------------------------
	for(i = 0; i < sub_tokens_count; i++) {
		if(sub_tokens_array[i] != NULL) {
			free(sub_tokens_array[i]);
			sub_tokens_array[i] = NULL;
		}
	}
	for(i = 0; i < argc; i++) {
		if(argv[i] != NULL) {
			free(argv[i]);
			argv[i] = NULL;
		}
	}
	if(py->dc_offsets_in_amperes != NULL) {
		free(py->dc_offsets_in_amperes);
		py->dc_offsets_in_amperes = NULL;
	}
	if(buffer != NULL) {
		free(buffer);
		buffer = NULL;
	}

	if(f_error == 1) {
		return(ESRV_FAILURE);
	} else {
		return(ESRV_SUCCESS);
	}
}
