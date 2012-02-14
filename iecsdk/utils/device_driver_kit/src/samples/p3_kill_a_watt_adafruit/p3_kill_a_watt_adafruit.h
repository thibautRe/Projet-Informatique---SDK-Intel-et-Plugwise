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

#ifndef __INCLUDE_P3_KILL_A_WATT_ADAFRUIT_DEVICE__
#define __INCLUDE_P3_KILL_A_WATT_ADAFRUIT_DEVICE__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include "esrv.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// ESRV_API API definition
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#ifdef _USRDLL
		 // All files compiled for a DLL must be with P3_KILL_A_WATT_ADAFRUIT_DEVICE_EXPORTS symbol defined
		 // this symbol should not be defined on any project that uses this DLL. 
		#ifdef P3_KILL_A_WATT_ADAFRUIT_DEVICE_EXPORTS
			#define ESRV_API __declspec(dllexport) extern
		#else // P3_KILL_A_WATT_ADAFRUIT_DEVICE_EXPORTS
			#define ESRV_API __declspec(dllimport) extern
		#endif // P3_KILL_A_WATT_ADAFRUIT_DEVICE_EXPORTS
	#endif // _USRDLL
#endif // __PL_WINDOWS__

#if (!defined(_USRDLL)) && defined(__cplusplus) 
	#define ESRV_API extern "C"
#endif // (!defined(_USRDLL)) && defined(__cplusplus)
#if (!defined(_USRDLL)) && (!defined(__cplusplus)) 
	#define ESRV_API extern
#endif // (!defined(_USRDLL)) && (!defined(__cplusplus))

//-----------------------------------------------------------------------------
// general definitions
//-----------------------------------------------------------------------------
#ifndef ESRV_DEVICE_INTERFACE_SERIAL
	#define ESRV_DEVICE_INTERFACE_SERIAL 1
#endif // ESRV_DEVICE_INTERFACE_SERIAL
#define P3_KILL_A_WATT_ADAFRUIT_MAX_TOKENS 32
#define P3_KILL_A_WATT_ADAFRUIT_MAX_SUB_TOKENS 64

//-----------------------------------------------------------------------------
// A/D in the XBee is 10 bits, and will return values between 0 and 1023.
//-----------------------------------------------------------------------------
#define P3_KILL_A_WATT_ADAFRUIT_DEFAULT_DC_OFFSET_IN_AMPERES 498
#define P3_KILL_A_WATT_ADAFRUIT_MIN_DC_OFFSET_IN_AMPERES 0.0
#define P3_KILL_A_WATT_ADAFRUIT_MAX_DC_OFFSET_IN_AMPERES 1023.0
#define P3_KILL_A_WATT_ADAFRUIT_SAMPLES_PER_DATA_FRAME_COUNT 18
#define P3_KILL_A_WATT_ADAFRUIT_MIN_KILL_A_WATTS 1
#define P3_KILL_A_WATT_ADAFRUIT_MAX_KILL_A_WATTS 16
#define P3_KILL_A_WATT_ADAFRUIT_VOLTAGE_SENSOR 0 //AD0
#define P3_KILL_A_WATT_ADAFRUIT_CURRENT_SENSOR 4 //AD4

/*
<xbee {
	app_id: 0x83, 
	address_16: 1, 
    rssi: 85, 
    address_broadcast: False, 
    pan_broadcast: False, 
    total_samples: 19, 
    digital: [	[-1, -1, -1, -1, -1, -1, -1, -1, -1],
 				[-1, -1, -1, -1, -1, -1, -1, -1, -1], 
				[-1, -1, -1, -1, -1, -1, -1, -1, -1], 
				[-1, -1, -1, -1, -1, -1, -1, -1, -1], 
				[-1, -1, -1, -1, -1, -1, -1, -1, -1], 
				[-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1],
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1], 
                [-1, -1, -1, -1, -1, -1, -1, -1, -1],
                [-1, -1, -1, -1, -1, -1, -1, -1, -1]], 
	analog: [	[190, -1, -1, -1, 489, -1], 
    			[109, -1, -1, -1, 484, -1], 
                [150, -1, -1, -1, 492, -1], 
                [262, -1, -1, -1, 492, -1], 
                [423, -1, -1, -1, 492, -1], 
                [589, -1, -1, -1, 492, -1], 
                [740, -1, -1, -1, 492, -1], 
                [843, -1, -1, -1, 492, -1], 
                [870, -1, -1, -1, 496, -1], 
                [805, -1, -1, -1, 491, -1], 
                [680, -1, -1, -1, 492, -1], 
                [518, -1, -1, -1, 492, -1], 
                [349, -1, -1, -1, 491, -1], 
                [199, -1, -1, -1, 491, -1], 
                [116, -1, -1, -1, 468, -1], 
                [108, -1, -1, -1, 492, -1], 
                [198, -1, -1, -1, 492, -1], 
                [335, -1, -1, -1, 492, -1], 
                [523, -1, -1, -1, 492, -1]]
}>
*/

#define P3_KILL_A_WATT_ADAFRUIT_MIN_VOLTAGE -170.0 
#define P3_KILL_A_WATT_ADAFRUIT_MAX_VOLTAGE +170.0

//-----------------------------------------------------------------------------
// XBee comms defines
//-----------------------------------------------------------------------------
#define XBEE_DATA_FRAME_START_OFFSET 0
#define XBEE_DATA_FRAME_START_IDENTIFIER 0x7E
#define XBEE_IO16 0x83
#define XBEE_DATA_FRAME_START_IDENTIFIER_SIZE_IN_BYTES 1
#define XBEE_DATA_FRAME_LENGTH_MSB_OFFSET (XBEE_DATA_FRAME_START_OFFSET)
#define XBEE_DATA_FRAME_LENGTH_LSB_OFFSET (XBEE_DATA_FRAME_LENGTH_MSB_OFFSET + 1)
#define XBEE_DATA_FRAME_LENGTH_MSB_SIZE_IN_BYTES 1
#define XBEE_DATA_FRAME_LENGTH_LSB_SIZE_IN_BYTES 1
#define XBEE_DATA_FRAME_DATA_OFFSET (XBEE_DATA_FRAME_LENGTH_LSB_OFFSET + XBEE_DATA_FRAME_LENGTH_LSB_SIZE_IN_BYTES)
#define XBEE_DATA_FRAME_CHECKSUM_SIZE_IN_BYTES 1
#define XBEE_DATA_FRAME_16BIT_ADDRESS_MSB_OFFSET (XBEE_DATA_FRAME_START_OFFSET + 1)
#define XBEE_DATA_FRAME_16BIT_ADDRESS_LSB_OFFSET (XBEE_DATA_FRAME_LENGTH_MSB_OFFSET + 2)
#define XBEE_DATA_FRAME_RSSI_OFFSET 3
#define XBEE_DATA_FRAME_BROADCAST_OFFSET 4
#define XBEE_DATA_FRAME_TOTAL_SAMPLES_OFFSET 5
#define XBEE_DATA_FRAME_CHANNEL_INDICATOR_HIGH_OFFSET 6
#define XBEE_DATA_FRAME_CHANNEL_INDICATOR_LOW_OFFSET 7

//-----------------------------------------------------------------------------
// device option string authorized options.
//-----------------------------------------------------------------------------
#define P3_KILL_A_WATT_ADAFRUIT_CHANNELS "CHANNELS"
#define P3_KILL_A_WATT_ADAFRUIT_DC_OFFSETS "OFFSETS"
#define P3_KILL_A_WATT_ADAFRUIT_AGGREGATE_CHANNELS "AGGREGATE_CHANNELS"

#define P3_KILL_A_WATT_ADAFRUIT_OPTION_MAX_TOKENS 3

#define P3_KILL_A_WATT_ADAFRUIT_OPTIONS \
		P3_KILL_A_WATT_ADAFRUIT_CHANNELS, \
		P3_KILL_A_WATT_ADAFRUIT_DC_OFFSETS, \
		P3_KILL_A_WATT_ADAFRUIT_AGGREGATE_CHANNELS

typedef enum _p3_kill_a_watt_adafruit__option_token_id {

	P3_KILL_A_WATT_ADAFRUIT_CHANNELS_TOKEN_ID = 0,
	P3_KILL_A_WATT_ADAFRUIT_DC_OFFSETS_TOKEN_ID,
	P3_KILL_A_WATT_ADAFRUIT_AGGREGATE_CHANNELS_TOKEN_ID

} P3_KILL_A_WATT_ADAFRUIT_OPTION_TOKEN_ID;

//-----------------------------------------------------------------------------
// device options structure
//-----------------------------------------------------------------------------
typedef struct _p3_kill_a_watt_adafruit_samples_buffer {

	double amperage_reading_buffer[P3_KILL_A_WATT_ADAFRUIT_SAMPLES_PER_DATA_FRAME_COUNT];
	double voltage_reading_buffer[P3_KILL_A_WATT_ADAFRUIT_SAMPLES_PER_DATA_FRAME_COUNT];

} P3_KILL_A_WATT_ADAFRUIT_SAMPLES_BUFFER, *PP3_KILL_A_WATT_ADAFRUIT_SAMPLES_BUFFER;
	
typedef struct _device_data {
	
	//-------------------------------------------------------------------------
	// device options
	//-------------------------------------------------------------------------
	int kill_a_watts_count;
	double *dc_offsets_in_amperes;
	int f_channels_count_provided;
	int f_dc_offsets_provided;
	int f_aggrerate;

	//-------------------------------------------------------------------------
	// data used to track data frames received from kill a watts
	//-------------------------------------------------------------------------
	int *f_kill_a_watts_data_frame_received;

	//-------------------------------------------------------------------------
	// data frame buffers
	//-------------------------------------------------------------------------
	PP3_KILL_A_WATT_ADAFRUIT_SAMPLES_BUFFER data_buffers;

} DEVICE_DATA, *PDEVICE_DATA;

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
ESRV_API int init_device_extra_data(PESRV);
ESRV_API int delete_device_extra_data(PESRV);
ESRV_API int open_device(PESRV, void *);
ESRV_API int close_device(PESRV, void *);
ESRV_API int parse_device_option_string(PESRV, void *);
ESRV_API int read_device_power(PESRV, void *, int);
ESRV_API int read_device_energy(PESRV, void *, int, int);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_P3_KILL_A_WATT_ADAFRUIT_DEVICE__
