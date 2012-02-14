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

#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// Note: build with
	//	_USRDLL
	//	__PL_WINDOWS__
	//	__PL_GENERATE_INI__
	//	__PL_GENERATE_INI_VERSION_TAGGING__
	//	__PL_GENERATE_INI_BUILD_TAGGING__
	//	__PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
	//	__PL_BLOCKING_COUNTER_FILE_LOCK__
	//	ESRV_CPU_INDEXED_SIMULATED_DEVICE_EXPORTS
	//	_CRT_SECURE_NO_DEPRECATE
	//-------------------------------------------------------------------------
#endif // __PL_WINDOWS__ 
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include <string.h>
#include <assert.h>
#ifdef _DEBUG
	#include <stdio.h>
#endif // _DEBUG
#ifdef __PL_WINDOWS__
	#include <pdh.h>
	#pragma comment(lib, "pdh.lib")
	#pragma comment(lib, "Rpcrt4.lib")
#endif // __PL_WINDOWS__ 
#ifdef __PL_LINUX__
	#include <ctype.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#include <stdlib.h>
	// TODO: add here *NIX specific header inclusions 
	// the device management may require.
#endif // __PL_SOLARIS__ || __PL_MACOSX__
#include "pub_esrv.h"
#include "esrv_cpu_indexed_simulated_device.h"

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
02/17/2010    Jamel Tayeb             Creation.
*/
ESRV_API int init_device_extra_data(PESRV p) {

	static DEVICE_DATA data;
	static int f_first_init_call = 0;
	PDEVICE_DATA px = NULL;

	if(p == NULL) { 
		goto init_device_extra_data_error; 
	}
	if(f_first_init_call == 0) {
		memset(&data, 0, sizeof(DEVICE_DATA));
		px = (void *)&data;
#ifdef __PL_WINDOWS__
		_tcsncpy(px->cpu_counter, CPU_COUNTER, _tcslen(CPU_COUNTER));
#endif // __PL_WINDOWS__ 
#ifdef __PL_LINUX__
		px->file = -1;
#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)  
		px->dummy = 0;
#endif // __PL_SOLARIS__ || __PL_MACOSX__
		p->device_data.virtual_devices = 1;
		p->f_hw_energy_integration_provided = 0;
		p->device_interface = ESRV_DEVICE_INTERFACE_PROPRIETARY;
		p->device_data.p_device_data = (void *)&data;

		data.f_fixed_power_draw = 0;
		data.f_variable_power_draw = 0;
		data.f_cpu_power_percentage = 0;
		data.fixed_power_draw = 
			ESRV_CPU_INDEXED_SIMULATED_DEVICE_DEFAULT_FIXED_POWER_DRAW;
		data.variable_power_draw = 
			ESRV_CPU_INDEXED_SIMULATED_DEVICE_DEFAULT_VARIABLE_POWER_DRAW;
		data.cpu_power_percentage =
			ESRV_CPU_INDEXED_SIMULATED_DEVICE_DEFAULT_CPU_POWER_PERCENTAGE;		

		f_first_init_call = 1;
	} else {
		;
	}
	return(ESRV_SUCCESS);
init_device_extra_data_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: delete_device_extra_data
Purpose : none
In      : pointer to an esrv data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
02/17/2010    Jamel Tayeb             Creation.
*/
ESRV_API int delete_device_extra_data(PESRV p) {
	return(ESRV_SUCCESS);
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
02/17/2010    Jamel Tayeb             Creation.
*/
ESRV_API int open_device(PESRV p, void *px) {

#ifdef __PL_WINDOWS__
	PDH_STATUS status = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)
#endif // __PL_SOLARIS__ || __PL_MACOSX__
	PDEVICE_DATA pd = NULL;

	if(p == NULL) { 
		goto open_device_error; 
	}
	pd = (PDEVICE_DATA)px;
	if(pd == NULL) { 
		goto open_device_error; 
	}

#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// open query
	//-------------------------------------------------------------------------
	status = PdhOpenQuery(
		NULL, 
		0, 
		&pd->hquery
	);
	if(status != ERROR_SUCCESS) { 
		goto open_device_error; 
	}

	//-------------------------------------------------------------------------
	// add cpu counter to the query
	//-------------------------------------------------------------------------
	status = PdhAddCounter(
		pd->hquery, 
		pd->cpu_counter, 
		0, 
		&pd->handle
	);
	if(status != ERROR_SUCCESS) { 
		goto open_device_error; 
	}
#endif // __PL_WINDOWS__ 
#ifdef __PL_LINUX__

	//-------------------------------------------------------------------------
	// open cpu info /proc file
	//-------------------------------------------------------------------------
	pd->file = open(
		DATA_SOURCE_CPU, 
		O_RDONLY
	);
	if(pd->file == -1) {
		goto open_device_error; 
	}
#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)
#endif // __PL_SOLARIS__ || __PL_MACOSX__

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
02/17/2010    Jamel Tayeb             Creation.
*/
ESRV_API int close_device(PESRV p, void *px) {

#ifdef __PL_WINDOWS__
	PDH_STATUS status = 0;
#endif // __PL_WINDOWS__
#ifdef __PL_LINUX__
	int status = -1;
#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)
#endif // __PL_SOLARIS__ || __PL_MACOSX__
	PDEVICE_DATA pd = NULL;

	if(p == NULL) { 
		goto close_device_error; 
	}
	pd = (PDEVICE_DATA)px;
	if(pd == NULL) { 
		goto close_device_error; 
	}

#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// close query
	//-------------------------------------------------------------------------
	if(pd->hquery != NULL) {
		status = PdhCloseQuery(
			pd->hquery
		);
		if(status != ERROR_SUCCESS) { 
			goto close_device_error; 
		}
		pd->handle = NULL;
		pd->hquery = NULL;
	}
#endif // __PL_WINDOWS__ 
#ifdef __PL_LINUX__

	//-------------------------------------------------------------------------
	// close cpu info /proc file
	//-------------------------------------------------------------------------
	if(pd->file != -1) {
		status = close(
			pd->file
		);
		if(status == -1) {
			goto close_device_error; 
		}
		pd->file = -1;
	}
#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)
#endif // __PL_SOLARIS__ || __PL_MACOSX__

	return(ESRV_SUCCESS);
close_device_error:
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
02/17/2010    Jamel Tayeb             Creation.
*/
ESRV_API int read_device_power(PESRV p, void *px, int vd) {

#ifdef __PL_WINDOWS__
	PDH_STATUS status = 0;
#endif // __PL_WINDOWS__ 
#ifdef __PL_LINUX__
	off_t oret = 0;
	ssize_t sret = 0;
	char separators_cpu[] = " \t\n";
	char buffer[BUFFER_SIZE] = { '\0' };
	char *token = NULL;
	static unsigned long long user_last = 0;
	static unsigned long long nice_last = 0;
	static unsigned long long system_last = 0;
	static unsigned long long idle_last = 0;
	static unsigned long long io_wait_last = 0;
	static unsigned long long soft_irq_last = 0;
	static unsigned long long hard_irq_last = 0;
	static unsigned long long steal_last = 0;
	static unsigned long long user = 0;
	static unsigned long long nice = 0;
	static unsigned long long system = 0;
	static unsigned long long idle = 0;
	static unsigned long long io_wait = 0;
	static unsigned long long soft_irq = 0;
	static unsigned long long hard_irq = 0;
	static unsigned long long steal = 0;
	long double usage_percentage = 0.0;
	long double usage_time = 0.0;
	long double total_time = 0.0;
#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)
#endif // __PL_SOLARIS__ || __PL_MACOSX__
	PDEVICE_DATA pd = NULL;
	double cpu_load = 0.0;
	static int f = 0;
	static double cpu_part_of_variable_power_draw = 0.0;

	if(p == NULL) { 
		goto read_device_power_error; 
	}
	pd = (PDEVICE_DATA)px;
	if(pd == NULL) { 
		goto read_device_power_error; 
	}
	if(
		(vd <= 0) ||
		(vd > p->device_data.virtual_devices)
	) { 
		goto read_device_power_error; 
	}

	if(f == 0) {
		cpu_part_of_variable_power_draw =
			pd->variable_power_draw *
			(
				pd->cpu_power_percentage /
				100.0
			)
		;
		f = 1;
	}

#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// read CPU utilization from the query
	//-------------------------------------------------------------------------
	status = PdhCollectQueryData(
		pd->hquery
	);
	if(status != ERROR_SUCCESS) { 
		goto read_device_power_error; 
	}

	//-------------------------------------------------------------------------
	// interprete data
	//-------------------------------------------------------------------------
	status = PdhGetFormattedCounterValue(
		pd->handle, 
		PDH_FMT_DOUBLE, 
		NULL, 
		&pd->counter_value
	);
	if(status != ERROR_SUCCESS) { 
		goto read_device_power_error; 
	}

	//-------------------------------------------------------------------------
	// set cpu load
	//-------------------------------------------------------------------------
	cpu_load = pd->counter_value.doubleValue;

#endif // __PL_WINDOWS__ 
#ifdef __PL_LINUX__

	//-------------------------------------------------------------------------
	// read CPU utilization data from /proc file
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0,  
		BUFFER_SIZE
	);
	sret = read(
		pd->file, 
		buffer, 
		BUFFER_SIZE
	);
	assert(sret != -1);
	token = strtok(buffer, separators_cpu);
	while(token != NULL) {
		if(strcmp(token, CPU_TO_MONITOR) == 0) {
			// jiffies in user mode
			token = strtok(NULL, separators_cpu);
			if(token != NULL) {				
				user_last = user;
				user = (unsigned long long)atoi(token);
			}
			// jiffies in low priority user mode - nice
			token = strtok(NULL, separators_cpu);
			if(token != NULL) {				
				nice_last = nice;
				nice = (unsigned long long)atoi(token);
			}
			// jiffies in system mode mode
			token = strtok(NULL, separators_cpu);
			if(token != NULL) {				
				system_last = system;
				system = (unsigned long long)atoi(token);;
			}
			// jiffies in idle task mode
			token = strtok(NULL, separators_cpu);
			if(token != NULL) {				
				idle_last = idle;
				idle = (unsigned long long)atoi(token);
			}
			// jiffies in IO wait
			token = strtok(NULL, separators_cpu);
			if(token != NULL) {				
				io_wait_last = io_wait;
				io_wait = (unsigned long long)atoi(token);
			}
			// jiffies in IRQ - hardirq
			token = strtok(NULL, separators_cpu);
			if(token != NULL) {				
				hard_irq_last = hard_irq;
				hard_irq = (unsigned long long)atoi(token);
			}
			// jiffies in IRQ - softirq
			token = strtok(NULL, separators_cpu);
			if(token != NULL) {				
				soft_irq_last = soft_irq;
				soft_irq = (unsigned long long)atoi(token);
			}
			// jiffies in steal
			token = strtok(NULL, separators_cpu);
			if(token != NULL) {				
				steal_last = steal;
				steal = (unsigned long long)atoi(token);
			}
			oret = lseek(
				pd->file,
				0,
				0
			);
			assert(oret != -1);
			goto read_device_power_found;
		}
		token = strtok(
			NULL, 
			separators_cpu
		);
	}
read_device_power_found:

	//-------------------------------------------------------------------
	// compute cpu utilization %
	//-------------------------------------------------------------------
	usage_time = (long double)(
		(user - user_last) + 
		(nice - nice_last) + 
		(system - system_last) + 
		(soft_irq - soft_irq_last) +
		(hard_irq - hard_irq_last) +
		(steal - steal_last)
	);
	total_time = (long double)(
		usage_time + 
		(idle - idle_last) +
		(io_wait - io_wait_last)
	);
	usage_percentage = 
		(long double)(
			100.0 * 
			usage_time / 
			total_time
		);

	//-------------------------------------------------------------------------
	// set cpu load
	//-------------------------------------------------------------------------
	cpu_load = usage_percentage;

#endif // __PL_LINUX__
#if defined (__PL_SOLARIS__) || (__PL_MACOSX__)
	p->double_power = 150.0 + (rand() % 10);
#endif // __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// compute power estimation
	//-------------------------------------------------------------------------
	p->double_power =
		pd->fixed_power_draw +
		(
			cpu_part_of_variable_power_draw *
			cpu_load /
			100.0
		)
	;

#ifdef _DEBUG
	//printf(
	//	"load = %g, Power = %g\n", 
	//	cpu_load, 
	//	p->double_power
	//);
#endif // _DEBUG

	return(ESRV_SUCCESS);
read_device_power_error:
	return(ESRV_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: read_device_energy.
Purpose : none
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
02/17/2010    Jamel Tayeb             Creation.
*/
ESRV_API int read_device_energy(PESRV p, void *px, int vd, int s) {
	return(ESRV_SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: parse_device_option_string
Purpose : none
In      : pointers to an esrv and a DEVICE_DATA data structure
Out     : none
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
02/17/2010    Jamel Tayeb             Creation.
*/
ESRV_API int parse_device_option_string(PESRV p, void *pd) {

	int i = 0;
	int t = 0;
	int f_error = 0;
	PDEVICE_DATA py = NULL;
	size_t s_length = 0;
	size_t t_length = 0;

    //-------------------------------------------------------------------------
	// variables used to upper tokens
	//-------------------------------------------------------------------------
	size_t k = 0;
	char *pc = NULL;
	char c = '\0';

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
	char *argv[ESRV_CPU_INDEXED_SIMULATED_DEVICE_OPTIONS_MAX_ARGUMENTS] = { NULL };
	char token_separators[] = " \t";
	char sub_token_separators[] = " \t=,";

	int sub_tokens_count = 0;
	char *sub_tokens_array[ESRV_CPU_INDEXED_SIMULATED_DEVICE_OPTIONS_MAX_SUB_TOKENS] = { NULL };

	//-------------------------------------------------------------------------
	// variable holding authorized device options
	//-------------------------------------------------------------------------
	static char *esrv_cpu_indexed_simulated_device_option_tokens[ESRV_CPU_INDEXED_SIMULATED_DEVICE_OPTIONS_MAX_TOKENS] = { 
		ESRV_CPU_INDEXED_SIMULATED_DEVICE_FIXED_POWER,
		ESRV_CPU_INDEXED_SIMULATED_DEVICE_VARIABLE_POWER,
		ESRV_CPU_INDEXED_SIMULATED_DEVICE_CPU_POWER_PERCENTATGE
	};
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
	// parse device options and setup device data option structure
	//-------------------------------------------------------------------------
	// example: --device_option "hardware_energy_integral"
	//
	for(i = 0; i < argc; i++) { // for each argument
		s_length = strlen(argv[i]);
		pc = argv[i];
		for(k = 0; k < s_length; k++) {
			c = *pc;
			*pc++ = (char)toupper(c);
		}
		for(t = 0; t < ESRV_CPU_INDEXED_SIMULATED_DEVICE_OPTIONS_MAX_TOKENS; t++) { // for each allowed option token
			t_length = strlen(esrv_cpu_indexed_simulated_device_option_tokens[t]);
			if(
				(s_length == t_length) &&
				(
					strncmp(argv[i],
					esrv_cpu_indexed_simulated_device_option_tokens[t], 
					s_length
				)
			) == 0) {

				switch(t) {

					//---------------------------------------------------------
					// process --fixed_power=<n> option
					//---------------------------------------------------------
					case ESRV_CPU_INDEXED_SIMULATED_DEVICE_FIXED_POWER_TOKEN_ID:
						if(i + 1 >= argc) { 
							f_error = 1;
							goto exit; 
						} 
						py->fixed_power_draw = atof(argv[++i]);
						if(
							py->fixed_power_draw < 0
						) { 
							f_error = 1;
							goto exit; 
						}
						py->f_fixed_power_draw = 1;
						goto next_argument;
						break;

					//---------------------------------------------------------
					// process --variable_power=<n> option
					//---------------------------------------------------------
					case ESRV_CPU_INDEXED_SIMULATED_DEVICE_VARIABLE_POWER_TOKEN_ID:
						if(i + 1 >= argc) { 
							f_error = 1;
							goto exit; 
						} 
						py->variable_power_draw = atof(argv[++i]);
						if(
							py->variable_power_draw < 0
						) { 
							f_error = 1;
							goto exit; 
						}
						py->f_variable_power_draw = 1;
						goto next_argument;
						break;

					//---------------------------------------------------------
					// process --cpu_power_percentatge=<n> option
					//---------------------------------------------------------
					case ESRV_CPU_INDEXED_SIMULATED_DEVICE_CPU_POWER_PERCENTATGE_TOKEN_ID:
						if(i + 1 >= argc) { 
							f_error = 1;
							goto exit; 
						} 
						py->cpu_power_percentage = atof(argv[++i]);
						if(
							py->cpu_power_percentage < 0
						) { 
							f_error = 1;
							goto exit; 
						}
						py->f_cpu_power_percentage = 1;
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
