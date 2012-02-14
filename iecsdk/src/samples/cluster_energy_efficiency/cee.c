/**
*** INTEL CONFIDENTIAL
*** 
*** Copyright (October 2010) (October 2010) Intel Corporation All Rights Reserved. 
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
// Build symbols.
//-----------------------------------------------------------------------------
//   __PL_WINDOWS__, __PL_LINUX__, __PL_SOLARIS__ or __PL_MACOSX__
//   __PL_GENERATE_INI__
//   __PL_BLOCKING_COUNTER_FILE_LOCK__
//   __PL_GENERATE_INI_VERSION_TAGGING__
//   __PL_GENERATE_INI_BUILD_TAGGING__
//   __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
//   __PL_DYNAMIC_COUNTERS_ALLOCATION__
//   __PL_DYNAMIC_TABLE_ALLOCATION__
//
//   __CEE_ESRV_ON_EACH_NODE__
//   __CEE_ESRV_ON_AGGREGATION_NODE__
//   __CEE_LOAD_BALANCING__
//   __CEE_LIVE_MONITORING__
//   __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__
//
//   _CRT_SECURE_NO_WARNINGS if __PL_WINDOWS__ is defined
//   _CRT_SECURE_NO_DEPRECATE if __PL_WINDOWS__ is defined
//

//-----------------------------------------------------------------------------
// Headers inclusions.
//-----------------------------------------------------------------------------
#ifdef _DEBUG
	#ifdef __PL_WINDOWS__
		#define _CRTDBG_MAP_ALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif // __PL_WINDOWS__
#endif // _DEBUG
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h> // for pow
#ifdef __PL_WINDOWS__
	#include <tchar.h>
	#pragma comment (lib, "Winmm")
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include <errno.h>
	#include <signal.h> // compile with -std=gnu99 not with -std=c99 
	#include <string.h>
	#include <unistd.h>
	#include <uuid/uuid.h>
	#include <semaphore.h>
	#include <sched.h>
	#include <sys/time.h>
	#include <pthread.h>
	#include <ctype.h> // for toupper
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"
#include "productivity_link_helper.h"
#include "pub_esrv_counters.h"
#include "cee.h"

//-----------------------------------------------------------------------------
// Global so the signal handler can access it.
//-----------------------------------------------------------------------------
CONTROL_DATA control_data;

/*-----------------------------------------------------------------------------
Function: main
Purpose : entry point
In      : none
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int main(int argc, char **argv) {

	//-------------------------------------------------------------------------
	// Error indicator flag for clean exit processing.
	//-------------------------------------------------------------------------
	int f_error = 0;

	//-------------------------------------------------------------------------
	// General purpose variables.
	//-------------------------------------------------------------------------
	PCONTROL_DATA p = NULL;
	size_t size = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	char pl_config_file[PL_MAX_PATH] = { '\0' };
	char buffer[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
	DWORD dwret = 0;
	size_t st_ret = 0;
	char convert_buffer[PL_MAX_PATH] = { '\0' };
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// Variables used to read PLs.
	//-------------------------------------------------------------------------
	// Generic
	//-------------------------------------------------------------------------
	PL_STATUS ret = PL_FAILURE;
	PLH_DYNAMIC_PL_FOLDER_INFO pc;
	unsigned long long value = 0;

	//-------------------------------------------------------------------------
	// PL indexes in PL forlder variables.
	// Note:
	//    Allocation of index tables is defered past PL_FOLDER snapshot.
	//-------------------------------------------------------------------------
	unsigned int *work_pl_indexes = NULL;
#ifdef __CEE_ESRV_ON_EACH_NODE__
	unsigned int *esrv_pl_indexes = NULL;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	unsigned int esrv_pl_indexe = 0;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__

	//-------------------------------------------------------------------------
	// Signal handler variables.
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	struct sigaction sa;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Sampling count and statistics variables.
	//-------------------------------------------------------------------------
	int chars_displayed = 0;

#ifdef __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Load balancing variables.
	//-------------------------------------------------------------------------
	int work_index = 0;
	int esrv_index = 0;
#endif // __CEE_LOAD_BALANCING__

#ifdef __CEE_LIVE_MONITORING__

	//-------------------------------------------------------------------------
	// PL live monitoring variables.
	//-------------------------------------------------------------------------
	static const char *cee_counters[CEE_COUNTERS_STRINGS_COUNT] = { 
		CEE_COUNTERS_STRINGS 
	};
#endif // __CEE_LIVE_MONITORING__

	//-------------------------------------------------------------------------
	// Thread priority variables (system).
	//-------------------------------------------------------------------------
#ifndef __CEE_LOAD_BALANCING__
	#ifdef __PL_WINDOWS__
		HANDLE h_thread = NULL;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		pthread_t h_thread;
		struct sched_param sched_param;
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Timer & timing variables (system).
	//-------------------------------------------------------------------------
	double maximum_allowed_measurement_time_in_ms = 
		DEFAULT_SAMPLING_INTERVAL_IN_SECONDS * 1000
	;
	double allowed_time_margin_in_ms = DEFAULT_ALLOWED_TIME_MARGIN_IN_MS;
	double time_to_sleep_in_ms = 0.0;
	double total_duration_in_ms = 0.0;
	double measurement_time_in_ms = 0.0;
#ifdef __PL_WINDOWS__
	MMRESULT mmret = 0;
	LARGE_INTEGER frequency;
	LARGE_INTEGER start_time;
	LARGE_INTEGER end_time;
	#ifdef __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__
		UINT resolution = 0;
	#endif // __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	struct timespec time_spec;
	struct timeval start_time;
	struct timeval end_time;
	int time_to_sleep_in_s = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Variables used to manage not-enough-work for load-balancing threads.
	//-------------------------------------------------------------------------
	int f_not_enough_work = 0;
	int zero_work_load_balancing_threads_count = 0;
#endif // __CEE_LOAD_BALANCING__

	/*-----------------------------------------------------------------------*/

#if defined (_DEBUG) && (__PL_WINDOWS__)

	//-------------------------------------------------------------------------
	// Setup debug output.
	//-------------------------------------------------------------------------
	dwret = _CrtSetDbgFlag(
		_CRTDBG_ALLOC_MEM_DF | 
		_CRTDBG_LEAK_CHECK_DF 
		/*| _CRTDBG_CHECK_CRT_DF*/
	);
	assert(dwret != -1);

	//-----------------------------------------------------------------------------
	// redirect dump to stdout
	//-----------------------------------------------------------------------------
	_CrtSetReportMode(
		_CRT_WARN, 
		_CRTDBG_MODE_FILE
	);
	_CrtSetReportFile(
		_CRT_WARN, 
		_CRTDBG_FILE_STDOUT
	);
	_CrtSetReportMode(
		_CRT_ERROR, 
		_CRTDBG_MODE_FILE
	);
	_CrtSetReportFile(
		_CRT_ERROR, 
		_CRTDBG_FILE_STDOUT
	);
	_CrtSetReportMode(
		_CRT_ASSERT, 
		_CRTDBG_MODE_FILE
	);
	_CrtSetReportFile(
		_CRT_ASSERT, 
		_CRTDBG_FILE_STDOUT
	);
#endif // _DEBUG && __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// Retrive the control structure address.
	//-------------------------------------------------------------------------
	p = &control_data;
	assert(p != NULL);

	memset(
		p, 
		0, 
		sizeof(control_data)
	);
	memset(
		&pc, 
		0, 
		sizeof(pc)
	);

	//-------------------------------------------------------------------------
	// Initialize the control data structure.
	//-------------------------------------------------------------------------
	p->command = EXIT;
	p->sampling_interval = DEFAULT_SAMPLING_INTERVAL_IN_SECONDS;
	p->work_index = DEFAULT_WORK_INDEX;
#ifdef __PL_WINDOWS__
	_tcsncpy(
		p->application_name, 
		DEFAULT_APPLICATION_NAME, 
		_tcslen(DEFAULT_APPLICATION_NAME)
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	strncpy(
		p->application_name, 
		DEFAULT_APPLICATION_NAME, 
		strlen(DEFAULT_APPLICATION_NAME)
	);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	p->f_help = 0;
	p->argc = argc;
	p->argv = argv;
#ifdef __CEE_ESRV_ON_EACH_NODE__
	p->f_esrv_on_each_node = 1;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	p->f_esrv_on_aggregation_node = 1;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#ifdef __CEE_LOAD_BALANCING__
	p->f_load_balancing = 0;
#endif // __CEE_LOAD_BALANCING__
	p->work_pls_count = 0;
	p->work_plds = NULL;
	p->work_data = NULL;
	p->start_work_data = NULL;
	p->dead_esrv_pls_count = 0;
#ifdef __CEE_ESRV_ON_EACH_NODE__
	p->esrv_pls_count = 0;
	p->esrv_plds = NULL;
	p->start_energy_data = NULL;
	p->energy_data = NULL;
	p->energy_data_multipliers = NULL;
	p->esrv_status = NULL;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	p->esrv_pls_count = 0;
	p->esrv_pld = 0;
	p->start_energy_data = 0;
	p->energy_data = 0;
	p->energy_data_multipliers = 0.0;
	p->esrv_status = ESRV_STATUS_NOT_RUNNING;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
	p->samples_collected = 0;
	p->samples = NO_SAMPLING_LIMIT;
	p->accumulated_enery_in_joules = 0.0;
	p->accumulated_enery_in_kwh = 0.0;
	p->average_work_unit_per_node = 0.0;
	p->average_energy_in_joule_per_node = 0.0;
	p->average_energy_in_kwh_per_node = 0.0;
	p->average_energy_in_joule_per_work_unit = 0.0;
	p->average_energy_in_kwh_per_work_unit = 0.0;
	p->average_work_unit_per_energy_in_joule = 0.0;
	p->average_work_unit_per_energy_in_kwh = 0.0;
	p->average_energy_in_joule_per_work_unit_per_node = 0.0;
	p->average_energy_in_kwh_per_work_unit_per_node = 0.0;
	p->average_work_unit_per_energy_in_joule_per_node = 0.0;
	p->average_work_unit_per_energy_in_kwh_per_node = 0.0;
	p->accumulated_work_data = 0;
	p->accumulated_work_all_nodes = 0;
	p->accumulated_start_work_all_nodes = 0;
#ifdef __CEE_ESRV_ON_EACH_NODE__
	p->accumulated_energy_in_joule_all_nodes = 0.0;
	p->accumulated_start_energy_in_joule_all_nodes = 0.0;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_LIVE_MONITORING__
	p->cee_pld = PL_INVALID_DESCRIPTOR;
	p->accumulated_energy_joules_multiplier = pow(
		10, 
		DEFAULT_ACCUMULATED_ENERGY_JOULES_DECIMALS
	);
	p->accumulated_energy_kwhs_multiplier = pow(
		10, 
		DEFAULT_ACCUMULATED_ENERGY_KWHS_DECIMALS
	);
	p->average_energy_per_work_unit_wu_joule_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE_DECIMALS
	);
	p->average_energy_per_work_unit_wu_kwh_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH_DECIMALS
	);
	p->average_work_unit_per_energy_joule_wu_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU_DECIMALS
	);
	p->average_work_unit_per_energy_kwh_wu_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU_DECIMALS
	);
	p->average_work_unit_per_node_wu_node_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_WORK_UNIT_PER_NODE_WU_NODE_DECIMALS
	);
	p->average_energy_per_node_joule_node_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_ENERGY_PER_NODE_JOULE_NODE_DECIMALS
	);
	p->average_energy_per_node_kwh_node_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_ENERGY_PER_NODE_KWH_NODE_DECIMALS
	);
	p->average_energy_per_work_unit_per_node_wu_joule_node_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE_DECIMALS
	);
	p->average_energy_per_work_unit_per_node_wu_kwh_node_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE_DECIMALS
	);
	p->average_work_unit_per_energy_per_node_joule_wu_node_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE_DECIMALS
	);
	p->average_work_unit_per_energy_per_node_kwh_wu_node_multiplier = pow(
		10, 
		DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU_NODE_DECIMALS
	);
#endif // __CEE_LIVE_MONITORING__
#ifdef __CEE_LOAD_BALANCING__
	p->threads_count = DEFAULT_LOAD_BALANCING_THREADS_COUNT;
	p->per_thread_work_plds_count = NULL;
	p->per_thread_work_plds = NULL;
#ifdef __CEE_ESRV_ON_EACH_NODE__
	p->per_thread_esrv_plds_count = NULL;
	p->per_thread_esrv_plds = NULL;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __PL_WINDOWS__
	p->h_sample = NULL;
	p->h_sample_done = NULL;
	p->h_load_balancing_threads = NULL;
	p->load_balancing_threads_ids = NULL;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	p->h_sample = NULL;  
	p->h_sample_done = NULL;  
#else // __PL_MACOSX__
	// MacOS X doesn't have unnamed semaphores
	p->h_sample = NULL;  
	p->h_sample_done = NULL;  
	p->sample_sem_names = NULL;
	p->sample_done_sem_names = NULL;
#endif // __PL_MACOSX__
	p->h_load_balancing_threads = NULL;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // __CEE_LOAD_BALANCING__
	p->boost_priority = DEFAULT_THREADS_BOOST_PRIORITY;
	p->f_output_file = 0;
	p->output_file = stdout;
	p->output_file_name = NULL;

	//-------------------------------------------------------------------------
	// Display startup banner and version information.
	//-------------------------------------------------------------------------
	ret = display_startup_message(p);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// Parse user input.
	//-------------------------------------------------------------------------
	ret = parser(&control_data);
	if(ret != PL_SUCCESS) {
		f_error = 1;
		goto main_stop;
	} else {
		if(p->f_help == 1) {
			goto main_done;
		}
	}

	//-------------------------------------------------------------------------
	// Check for incoherent user input.
	//-------------------------------------------------------------------------
#if defined (__CEE_ESRV_ON_EACH_NODE__) && (__CEE_ESRV_ON_AGGREGATION_NODE__)
	if(
		(p->f_esrv_on_each_node == 1) && 
		(p->f_esrv_on_aggregation_node == 1)
	) {
		_ERROR("Icompatible ESRV options specified [on each node and on aggregation nobe].");
	}
#endif // __CEE_ESRV_ON_EACH_NODE__ && __CEE_ESRV_ON_AGGREGATION_NODE__

#ifdef __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Allocate memory to store work plds and plds count to be used by each 
	// thread.
	// Note:
	//    Since at this time we do not know yet how many work PL descriptors
	//    each load-balancing threads will have to process, the PL descriptor
	//    arrays will be allocated later-on.
	//-------------------------------------------------------------------------
	size = sizeof(unsigned int) * p->threads_count;
	p->per_thread_work_plds_count = (unsigned int *)malloc(size);
	if(p->per_thread_work_plds_count == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing threads' work PL descriptors counts.");	
	}
	memset(
		p->per_thread_work_plds_count, 
		0, 
		size
	);
	size = sizeof(int *) * p->threads_count;
	p->per_thread_work_plds = (int **)malloc(size);
	if(p->per_thread_work_plds == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing threads' work PL descriptors.");	
	}
	memset(
		p->per_thread_work_plds, 
		0, 
		size
	);
#ifdef __CEE_ESRV_ON_EACH_NODE__

	//-------------------------------------------------------------------------
	// Allocate memory to store energy plds and plds count to be used by each
	// thread.
	// Note:
	//    We assume that since __CEE_ESRV_ON_EACH_NODE__ is defined, that we 
	//    will have as many ESRV instances than application instances running
	//    on the cluster.
	//-------------------------------------------------------------------------
	p->per_thread_esrv_plds_count = (unsigned int *)malloc(size);
	if(p->per_thread_esrv_plds_count == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing threads' energy PL descriptors counts.");	
	}
	memset(
		p->per_thread_esrv_plds_count, 
		0, 
		size
	);
	size = sizeof(int *) * p->threads_count;
	p->per_thread_esrv_plds = (int **)malloc(size);
	if(p->per_thread_esrv_plds == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing threads' energy PL descriptors.");	
	}
	memset(p->per_thread_esrv_plds, 0, size);
#endif // __CEE_ESRV_ON_EACH_NODE__

	//-------------------------------------------------------------------------
	// Allocate memory to store load-balancing threads management data.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	size = sizeof(HANDLE) * p->threads_count;
	p->h_sample = (HANDLE *)malloc(size);
	if(p->h_sample == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->h_sample, 
		0, 
		size
	);

	size = sizeof(HANDLE) * p->threads_count;
	p->h_sample_done = (HANDLE *)malloc(size);
	if(p->h_sample_done == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s)");	
	}
	memset(
		p->h_sample_done, 
		0, 
		size
	);

	size = sizeof(HANDLE) * p->threads_count;
	p->h_load_balancing_threads = (HANDLE *)malloc(size);
	if(p->h_load_balancing_threads == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->h_load_balancing_threads, 
		0, 
		size
	);

	size = sizeof(DWORD) * p->threads_count;
	p->load_balancing_threads_ids = (DWORD *)malloc(size);
	if(p->load_balancing_threads_ids == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->load_balancing_threads_ids, 
		0, 
		size
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	size = sizeof(sem_t) * p->threads_count;
	p->h_sample = (sem_t *)malloc(size);
	if(p->h_sample == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->h_sample, 
		0, 
		size
	);

	size = sizeof(sem_t) * p->threads_count;
	p->h_sample_done = (sem_t *)malloc(size);
	if(p->h_sample_done == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->h_sample_done, 
		0, 
		size
	);
#else // __PL_MACOSX__
	// MacOS X doesn't have unnamed semaphores
	size = sizeof(sem_t *) * p->threads_count;
	p->h_sample = (sem_t **)malloc(size);
	if(p->h_sample == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->h_sample, 
		0, 
		size
	);

	size = sizeof(sem_t *) * p->threads_count;
	p->h_sample_done = (sem_t **)malloc(size);
	if(p->h_sample_done == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->h_sample_done, 
		0, 
		size
	);

	size = sizeof(char *) * p->threads_count;
	p->sample_sem_names = (char **)malloc(size);
	if(p->sample_sem_names == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->sample_sem_names, 
		0, 
		size
	);

	size = sizeof(char *) * p->threads_count;
	p->sample_done_sem_names = (char **)malloc(size);
	if(p->sample_done_sem_names == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->sample_done_sem_names, 
		0, 
		size
	);
#endif // __PL_MACOSX__
	size = sizeof(pthread_t) * p->threads_count;
	p->h_load_balancing_threads = (pthread_t *)malloc(size);
	if(p->h_load_balancing_threads == NULL) {
		_ERROR("Unable to allocate memory to store load-balancing thread synchronization object(s).");	
	}
	memset(
		p->h_load_balancing_threads, 
		0, 
		size
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Install signal handler.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	bret = SetConsoleCtrlHandler(
		(PHANDLER_ROUTINE)signal_handler, 
		TRUE
	);
	if(bret == 0) { 
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags = 0;
	ret = sigaction(
		SIGINT, 
		&sa, 
		NULL
	);
	if(ret == -1) { 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		f_error = 1;
		goto main_stop; 
	}

	//-------------------------------------------------------------------------
	// Setup precision timer.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
#ifdef __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__

	//-------------------------------------------------------------------------
	// Set highest possible timer resolution.
	//-------------------------------------------------------------------------
	resolution = 1; // in ms
	do {
		mmret = timeBeginPeriod(resolution++);
	} while(mmret != TIMERR_NOERROR);
#endif // __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__

	//-------------------------------------------------------------------------
	// Setup (hp) timer.
	//-------------------------------------------------------------------------
	bret = QueryPerformanceFrequency(&frequency);
	if(
		(bret == FALSE) || 
		(frequency.QuadPart == 0)
	) {
		_ERROR("Unable to setup high-precision timer.");
	}
#endif // __IEC_WINDOWS__
	maximum_allowed_measurement_time_in_ms = p->sampling_interval * 1000.0;

#ifdef __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Nothing to do, since each load-balancing thread will boost their own
	// priority.
	//-------------------------------------------------------------------------
#else // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Boost main thread's (which is the data collector thread) priority.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	h_thread = GetCurrentThread();
	bret = SetThreadPriority(
		h_thread, 
		p->boost_priority
	);
	if(bret == FALSE) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	threads_tid = pthread_self();
	sched_param.sched_priority = p->boost_priority;
	ret = pthread_setschedparam(
		threads_tid, 
		SCHED_RR, 
		&threads_sched_param
	);
	if(ret == -1) { 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		_ERROR("Unable to boost main thread's priority.");
	}
#endif // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Read PL folder content.
	//-------------------------------------------------------------------------
	ret = plh_dynamic_read_pl_folder(&pc);
	if(ret != PL_SUCCESS) {
		_ERROR("Unable to read PL folder.  Is the Intel(r) Energy Checker SDK installed?");
	}

	//-------------------------------------------------------------------------
	// Check for empty PL folder.
	//-------------------------------------------------------------------------
	if(pc.max_uuids == 0) {
		_ERROR("No PLs found in the PL folder.  Is there a netwroked file system setup for the cluster?  Are the workloads and/or ESRV(s) started?");
	}

	//-------------------------------------------------------------------------
	// Allocate memory to store PL indexes.
	//-------------------------------------------------------------------------
	work_pl_indexes = (unsigned int *)malloc(sizeof(unsigned int) * pc.max_uuids);
	if(work_pl_indexes == NULL) {
		_ERROR("Not enough memory to store work PL index table.");
	}
	memset(
		work_pl_indexes, 
		0, 
		sizeof(unsigned int) * pc.max_uuids
	);
#ifdef __CEE_ESRV_ON_EACH_NODE__
	esrv_pl_indexes = (unsigned int *)malloc(sizeof(unsigned int) * pc.max_uuids);
	if(esrv_pl_indexes == NULL) {
		_ERROR("Not enough memory to store esrv PL index table.");
	}
	memset(
		esrv_pl_indexes, 
		0, 
		sizeof(unsigned int) * pc.max_uuids
	);
#endif // __CEE_ESRV_ON_EACH_NODE__

	//-------------------------------------------------------------------------
	// Count work and ESRV PLs in the local PL folder.
	//-------------------------------------------------------------------------
	for(i = 0; i < pc.max_uuids; i++) {

		//---------------------------------------------------------------------
		// Work.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		if(
			_tcsncmp(
				pc.entries[i].application_name, 
				p->application_name, 
				sizeof(p->application_name)
			) == 0
		) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		if(
			strncmp(
				pc.entries[i].application_name, 
				p->application_name, 
				sizeof(p->application_name)
			) == 0
		) {
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			work_pl_indexes[p->work_pls_count] = i;
			p->work_pls_count++;
		}

		//---------------------------------------------------------------------
		// Energy.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		if(
			_tcsncmp(
				pc.entries[i].application_name, 
				ESRV_NAME, 
				sizeof(ESRV_NAME)
			) == 0
		) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		if(
			strncmp(
				pc.entries[i].application_name, 
				ESRV_NAME, 
				sizeof(ESRV_NAME)
			) == 0
		) {
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __CEE_ESRV_ON_EACH_NODE__
			esrv_pl_indexes[p->esrv_pls_count] = i;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
			esrv_pl_indexe = i;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
			p->esrv_pls_count++;
		}
	}

	//-------------------------------------------------------------------------
	// Check for missing application or ESRV PL in the PL folder.
	// Note
	//    While application PLs are searched, ESRV PL or PLs are searched too.
	//    The ESRV PL(s) count is checked against 1 or the number of application
	//    PL(s) found if __CEE_ESRV_ON_EACH_NODE__ is defined.
	// Note:
	//    The ESRV PL(s) count checking is deffered since we need to open each
	//    of them to check if they are live or dead.  The chech is found later
	//    on, after each ESRV PL is oppeneb (note that the status of each ESRV
	//    PL is stored). 
	//-------------------------------------------------------------------------
	if(p->work_pls_count == 0) {
		_ERROR("Not a single application PL was found in the PL folder.  Are the workloads started?");
	}
	if(p->esrv_pls_count == 0) {
		_ERROR("No ESRV PL(s) found in the PL folder.  Is(are) the ESRV(s) started?");
	}
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	if(p->esrv_pls_count != 1) {
		WARNING("Found more than one ESRV PL.  Remove unneeded ESRV PLs to silent this warning.  This will likely lead to problems later-on.");
	}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__

	//-------------------------------------------------------------------------
	// Allocate memory to store work and energy PL descriptors.
	//-------------------------------------------------------------------------
	size = sizeof(int) * p->work_pls_count;
	p->work_plds = (int *)malloc(size);
	if(p->work_plds == NULL) { 
		_ERROR("Unable to allocate memory to store application PL descriptors.");
	}
	memset(
		p->work_plds, 
		0, 
		size
	);
	for(i = 0; i < p->work_pls_count; i++) { 
		p->work_plds[i] = PL_INVALID_DESCRIPTOR; 
	}
#ifdef __CEE_ESRV_ON_EACH_NODE__
	size = sizeof(int) * p->esrv_pls_count;
	p->esrv_plds = (int *)malloc(size);
	if(p->esrv_plds == NULL) { 
		_ERROR("Unable to allocate memory to store ESRV PL descriptors.");
	}
	memset(
		p->esrv_plds, 
		0, 
		size
	);
	for(i = 0; i < p->esrv_pls_count; i++) { 
		p->esrv_plds[i] = PL_INVALID_DESCRIPTOR; 
	}
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	p->esrv_pld = PL_INVALID_DESCRIPTOR;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__

	//-------------------------------------------------------------------------
	// Allocate memory to store work and energy data.
	// Note:
	//    If __CEE_ESRV_ON_EACH_NODE__ is defined, then there should be at least 
	//    as many ESRV PLs as work PLs.
	//-------------------------------------------------------------------------
	size = sizeof(unsigned long long) * p->work_pls_count;
	p->work_data = (unsigned long long *)malloc(size);
	if(p->work_data == NULL) { 
		_ERROR("Unable to allocate memory to store application data.");
	}
	memset(
		p->work_data, 
		0, 
		size
	);
	size = sizeof(unsigned long long) * p->work_pls_count;
	p->start_work_data = (unsigned long long *)malloc(size);
	if(p->start_work_data == NULL) { 
		_ERROR("Unable to allocate memory to store application data.");
	}
	memset(
		p->start_work_data, 
		0, 
		size
	);

#ifdef __CEE_ESRV_ON_EACH_NODE__
	size = sizeof(unsigned long long) * p->esrv_pls_count;
	p->energy_data = (unsigned long long *)malloc(size);
	if(p->energy_data == NULL) { 
		_ERROR("Unable to allocate memory to store energy data.");
	}
	memset(
		p->energy_data, 
		0, 
		size
	);

	p->start_energy_data = (unsigned long long *)malloc(size);
	if(p->start_energy_data == NULL) { 
		_ERROR("Unable to allocate memory to store energy data.");
	}
	memset(
		p->start_energy_data, 
		0, 
		size
	);

	size = sizeof(double) * p->esrv_pls_count;
	p->energy_data_multipliers = (double *)malloc(size);
	if(p->energy_data_multipliers == NULL) { 
		_ERROR("Unable to allocate memory to store energy decimals data.");
	}
	memset(
		p->energy_data_multipliers, 
		0, 
		size
	);

	size = sizeof(unsigned long long) * p->esrv_pls_count;
	p->esrv_status = (unsigned long long *)malloc(size);
	if(p->esrv_status == NULL) { 
		_ERROR("Unable to allocate memory to store ESRV status data.");
	}
	for(i = 0; i < p->esrv_pls_count; i++) {
		p->esrv_status[i] = ESRV_STATUS_NOT_RUNNING;
	}
#endif // __CEE_ESRV_ON_EACH_NODE__

#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	p->energy_data = 0;
	p->start_energy_data = 0;
	p->energy_data_multipliers = 0.0;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__

	//-------------------------------------------------------------------------
	// Open work and energy PLs and set energy decimals value.
	//-------------------------------------------------------------------------
	// Work.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->work_pls_count; i++) {
		memset(
			pl_config_file, 
			0, 
			sizeof(pl_config_file)
		);
		strncpy(
			pl_config_file, 
			PLS_FOLDER, 
			strlen(PLS_FOLDER)
		);
		strncat(
			pl_config_file, 
			PLS_FOLDER_PATH_SEPARATOR, 
			strlen(PLS_FOLDER_PATH_SEPARATOR)
		);
#ifdef __PL_WINDOWS__
		memset(
			convert_buffer, 
			0, 
			sizeof(convert_buffer)
		);
		wcstombs_s(
			&st_ret, 
			convert_buffer, 
			sizeof(convert_buffer), 
			pc.entries[work_pl_indexes[i]].full_uuid, 
			_TRUNCATE
		);
		strncat(
			pl_config_file, 
			convert_buffer, 
			strlen(convert_buffer)
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		strncat(
			pl_config_file, 
			pc.entries[work_pl_indexes[i]].full_uuid, 
			strlen(pc.entries[work_pl_indexes[i]].full_uuid)
		);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		strncat(
			pl_config_file, 
			PLS_FOLDER_PATH_SEPARATOR, 
			strlen(PLS_FOLDER_PATH_SEPARATOR)
		);
		strncat(
			pl_config_file, 
			PL_INI_CONFIG_FILE_NAME, 
			strlen(PL_INI_CONFIG_FILE_NAME)
		);
		p->work_plds[i] = pl_attach(pl_config_file);
		if(p->work_plds[i] == PL_INVALID_DESCRIPTOR) {
			ERROR_INDEX("Unable to open application PL [%d].", i);
		}
	}

	//-------------------------------------------------------------------------
	// Energy.
	// Note:
	//    We do not assume that each ESRV instance uses the same .decimals 
	//    suffix counter value.
	//-------------------------------------------------------------------------
#ifdef __CEE_ESRV_ON_EACH_NODE__
	for(i = 0; i < p->esrv_pls_count; i++) {

		//---------------------------------------------------------------------
		// Open each ESRV PL.
		//---------------------------------------------------------------------
		memset(
			pl_config_file, 
			0, 
			sizeof(pl_config_file)
		);
		strncpy(
			pl_config_file, 
			PLS_FOLDER, 
			strlen(PLS_FOLDER)
		);
		strncat(
			pl_config_file, 
			PLS_FOLDER_PATH_SEPARATOR, 
			strlen(PLS_FOLDER_PATH_SEPARATOR)
		);
#ifdef __PL_WINDOWS__
		memset(
			convert_buffer, 
			0, 
			sizeof(convert_buffer)
		);
		wcstombs_s(
			&st_ret, 
			convert_buffer, 
			sizeof(convert_buffer), 
			pc.entries[esrv_pl_indexes[i]].full_uuid, 
			_TRUNCATE
		);
		strncat(
			pl_config_file, 
			convert_buffer, 
			strlen(convert_buffer)
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		strncat(
			pl_config_file, 
			pc.entries[esrv_pl_indexes[i]].full_uuid, 
			strlen(pc.entries[esrv_pl_indexes[i]].full_uuid)
		);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		strncat(
			pl_config_file, 
			PLS_FOLDER_PATH_SEPARATOR, 
			strlen(PLS_FOLDER_PATH_SEPARATOR)
		);
		strncat(
			pl_config_file, 
			PL_INI_CONFIG_FILE_NAME, 
			strlen(PL_INI_CONFIG_FILE_NAME)
		);
		p->esrv_plds[i] = pl_attach(pl_config_file);
		if(p->esrv_plds[i] == PL_INVALID_DESCRIPTOR) {
			ERROR_INDEX("Unable to open ESRV PL [%d].", i);
		}

		//---------------------------------------------------------------------
		// Check if this ESRV PL is live or dead.
		// Note:
		//    Only [Channel 1] of each ESRV PL is taken in account.
		// Note:
		//    We store the status for each ESRV PL found
		//---------------------------------------------------------------------
		ret = pl_read(
			p->esrv_plds[i], 
			&p->esrv_status[i], 
			ESRV_COUNTER_STATUS_INDEX
		);
		if(ret != PL_SUCCESS) {
			ERROR_INDEX(
				"Unable to read ESRV [%d] instance's ESRV_COUNTER_STATUS_INDEX counter.", 
				i
			);
		}
		if(p->esrv_status[i] != ESRV_STATUS_RUNNING) {
			WARNING_INDEX(
				"ESRV [%d] instance's ESRV_COUNTER_STATUS_INDEX counter is not equal to 1 (Dead ESRV).", 
				i
			);
			p->dead_esrv_pls_count++;
		}

		//---------------------------------------------------------------------
		// Read each energy .decimals counter and compute energy multiplier.
		// Note:
		//    Since ESRV doesn't change the energy measurement precision, we
		//    read the energy .decimals counter only once and compute the
		//    corresponding multiplier.
		//---------------------------------------------------------------------
		ret = pl_read(
			p->esrv_plds[i], 
			&value, 
			ESRV_COUNTER_ENERGY_JOULES_DECIMALS_INDEX
		);
		if(ret != PL_SUCCESS) {
			ERROR_INDEX(
				"Unable to read ESRV [%d] instance's ESRV_COUNTER_ENERGY_JOULES_DECIMALS counter.", 
				i
			);
		}
		p->energy_data_multipliers[i] = pow(
			10, 
			(double)value
		);
	} // for i

	//-------------------------------------------------------------------------
	// Check if there is at least one live ESRV PL.
	//-------------------------------------------------------------------------		
	if(p->dead_esrv_pls_count >= p->esrv_pls_count) {
		_ERROR("None of the ESRV PL(s) found are live.  Check the status of the ESRV instance(s) running on the cluster.");
	}
#endif // __CEE_ESRV_ON_EACH_NODE__

#ifdef __CEE_ESRV_ON_EACH_NODE__

	//-------------------------------------------------------------------------
	// Check for missmatch between application and live ESRV PLs count.
	//-------------------------------------------------------------------------
	if(p->work_pls_count != p->esrv_pls_count) {
		_ERROR("The number of application and ESRV PL(s) are different when they are supposed to be identical.  Are you running more than one instance of the application per node?  Are you running more ESRV instances than applications?");
	}
#endif // __CEE_ESRV_ON_EACH_NODE__

#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__

	//-------------------------------------------------------------------------
	// Open the ESRV PL.
	//-------------------------------------------------------------------------
	memset(
		pl_config_file, 
		0, 
		sizeof(pl_config_file)
	);
	strncpy(
		pl_config_file, 
		PLS_FOLDER, 
		strlen(PLS_FOLDER)
	);
	strncat(
		pl_config_file, 
		PLS_FOLDER_PATH_SEPARATOR, 
		strlen(PLS_FOLDER_PATH_SEPARATOR)
	);
#ifdef __PL_WINDOWS__
	memset(
		convert_buffer, 
		0, 
		sizeof(convert_buffer)
	);
	wcstombs_s(
		&st_ret, 
		convert_buffer, 
		sizeof(convert_buffer), 
		pc.entries[esrv_pl_indexe].full_uuid,
		_TRUNCATE
	);
	strncat(
		pl_config_file, 
		convert_buffer, 
		strlen(convert_buffer)
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	strncat(
		pl_config_file, 
		pc.entries[esrv_pl_indexe].full_uuid, 
		strlen(pc.entries[esrv_pl_indexe].full_uuid)
	);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	strncat(
		pl_config_file, 
		PLS_FOLDER_PATH_SEPARATOR, 
		strlen(PLS_FOLDER_PATH_SEPARATOR)
	);
	strncat(
		pl_config_file, 
		PL_INI_CONFIG_FILE_NAME, 
		strlen(PL_INI_CONFIG_FILE_NAME)
	);
	p->esrv_pld = pl_attach(pl_config_file);
	if(p->esrv_pld == PL_INVALID_DESCRIPTOR) {
		_ERROR("Unable To Open The ESRV PL.");
	}

	//---------------------------------------------------------------------
	// Check if the ESRV PL is live or dead.
	// Note:
	//    Only [Channel 1] of each ESRV PL is taken in account.
	//---------------------------------------------------------------------
	ret = pl_read(
		p->esrv_pld, 
		&p->esrv_status, 
		ESRV_COUNTER_STATUS_INDEX
	);
	if(ret != PL_SUCCESS) {
		_ERROR("Unable to read the ESRV instance's status counter (ESRV_COUNTER_STATUS_INDEX).");
	}
	if(p->esrv_status != ESRV_STATUS_RUNNING) {
		p->dead_esrv_pls_count++;
		_ERROR("The ESRV instance's status is dead (ESRV_COUNTER_STATUS_INDEX != 1).");
	}

	//-------------------------------------------------------------------------
	// Read the energy .decimals counter and compute energy multiplier.
	// Note:
	//    Since ESRV doesn't change the energy measurement precision, we
	//    read the energy .decimals counter only once and compute the
	//    corresponding multiplier.
	//-------------------------------------------------------------------------
	ret = pl_read(
		p->esrv_pld, 
		&value, 
		ESRV_COUNTER_ENERGY_JOULES_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		_ERROR("Unable to read the ESRV instance's energy in joule .decimal suffix counter (ESRV_COUNTER_ENERGY_JOULES_DECIMALS_INDEX).");
	}
	p->energy_data_multipliers = pow(
		10, 
		(double)value
	);
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__

#ifdef __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Setup load balancing control data, start by sharing the application
	// - and ESRV if applicable - PLs between load-balancing threads.
	// Note:
	//    All decisions are taken based on the application PLs count.
	// Note:
	//    If not enough work is available, then threads will still be 
	//    created.  However, if any load-balancing thread ends-up with zero 
	//    work (or energy is __CEE_ESRV_ON_EACH_NODE__ is defined at build 
	//    time) data source, then they will gracefully end.  The total count
	//    of load-balancing threads will be decreased accordingly to not 
	//    pollute the stats.
	//-------------------------------------------------------------------------
	// Check if there is enough work to start load-balancing.
	//-------------------------------------------------------------------------
	if(p->work_pls_count < LOAD_BALANCING_PLS_COUNT_THRESHOLD) {
		f_not_enough_work = 1;
		WARNING("Not enough PLs found to use load-balancing.  Load balancing will not be effective during this session.");
	}

	//-------------------------------------------------------------------------
	// Distribute application and ESRV PLs - if applicable - to each 
	// load-balancing threads (simple round-robin).
	// Note:
	//    We cannot assume that each load-balancing thread will have the same
	//    number of PLs to process.
	// Note:
	//    For each load-balancing thread, the number of work PLs is equal to
	//    the number of esrv PL (if __CEE_ESRV_ON_EACH_NODE__ defined).
	//-------------------------------------------------------------------------
	for(i = 0, j = 0; j < p->work_pls_count; j++) {
		p->per_thread_work_plds_count[i] += 1;
#ifdef __CEE_ESRV_ON_EACH_NODE__
		p->per_thread_esrv_plds_count[i] += 1;
#endif // __CEE_ESRV_ON_EACH_NODE__
		i = i + 1;
		if(i == p->threads_count) { 
			i = 0; 
		}
	}

	//-------------------------------------------------------------------------
	// Check if any load-balancing thread has some work.  Indeed, it is pos-
	// -sible to have one or more load-balancing threads having zero PL as-
	// -signed.  This will happen only if the work PLs count < MIN_LOAD_BALANC-
	// -ING_THREADS_COUNT.
	//-------------------------------------------------------------------------
	if(f_not_enough_work == 1) {
		for(i = 0, j = 0; j < p->work_pls_count; j++) {
			if(p->per_thread_work_plds_count[i] == 0) {
				zero_work_load_balancing_threads_count++;
			}
			if(zero_work_load_balancing_threads_count != 0) {
				p->work_pls_count -= zero_work_load_balancing_threads_count;
			}
		}
	}

	//-------------------------------------------------------------------------
	// Check load-balancing threads' load.
	//-------------------------------------------------------------------------
	for(i = 1; i < p->threads_count; i++) {
		if(p->per_thread_work_plds_count[i] < LOAD_BALANCING_MIN_PLS_COUNT) {
			WARNING_INDEX("Too few PLs for thread [%d].", i);
		}
		if(p->per_thread_work_plds_count[i] > LOAD_BALANCING_MAX_PLS_COUNT) { 
			WARNING_INDEX("Too many PLs for thread [%d], please increase the thread count (--load_balancing option).", i);
		}
	}

	//-------------------------------------------------------------------------
	// Now that load-balancing threads' PL count is known, we allocate memory
	// to store the actual PL descriptors (work and energy - if applicable).
	// Note:
	//    for each load-balancing thread, the number of work PLs is equal to
	//    the number of esrv PL (if __CEE_ESRV_ON_EACH_NODE__ defined).  This 
	//    means that there is only one instance of the application running on
	//    each node.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->threads_count; i++) {
		size = sizeof(int) * p->per_thread_work_plds_count[i];
		p->per_thread_work_plds[i] = (int *)malloc(size);
		if(p->per_thread_work_plds[i] == NULL) {
			ERROR_INDEX(
				"Unable to allocate memory to store load-balancing thread [%d]'s work PL descriptors.", 
				i
			);
		}
		memset(
			p->per_thread_work_plds[i], 
			0, 
			size
		);
#ifdef __CEE_ESRV_ON_EACH_NODE__
		p->per_thread_esrv_plds[i] = (int *)malloc(size);
		if(p->per_thread_esrv_plds[i] == NULL) {
			ERROR_INDEX(
				"Unable to allocate memory to store load-balancing thread [%d]'s energy PL descriptors.", 
				i
			);
		}
		memset(
			p->per_thread_esrv_plds[i], 
			0, 
			size
		);
#endif // __CEE_ESRV_ON_EACH_NODE__
	}

	//-------------------------------------------------------------------------
	// Store the actual PL descriptors in the newly allocated memory.
	// Note:
	//    for each load-balancing thread, the number of work PLs is equal to
	//    the number of esrv PL (if __CEE_ESRV_ON_EACH_NODE__ defined).  This 
	//    means that there is only one instance of the application running on
	//    each node.
	//-------------------------------------------------------------------------
	work_index = 0;
	esrv_index = 0;
	for(i = 0; i < p->threads_count; i++) {
		for(j = 0; j < p->per_thread_work_plds_count[i]; j++) {
			p->per_thread_work_plds[i][j] = p->work_plds[work_index++];
		}
#ifdef __CEE_ESRV_ON_EACH_NODE__
		for(j = 0; j < p->per_thread_esrv_plds_count[i]; j++) {
			p->per_thread_esrv_plds[i][j] = p->esrv_plds[esrv_index++];
		}
#endif // __CEE_ESRV_ON_EACH_NODE__
	}

	//-------------------------------------------------------------------------
	// Create load-balancing threads' synchronization objects (system).
	//-------------------------------------------------------------------------
	for(i = 0; i < p->threads_count; i++) {
#ifdef __PL_WINDOWS__
		p->h_sample[i] = CreateEvent(
			NULL, 
			FALSE, 
			FALSE, 
			NULL
		); // autoreset and non signaled
		if(p->h_sample[i] == NULL) {
			ERROR_INDEX(
				"Unable to create load-balancing thread [%d]'s synchronization objects.", 
				i
			);
		}
		p->h_sample_done[i] = CreateEvent(
			NULL, 
			FALSE, 
			FALSE, 
			NULL
		); // autoreset and non signaled
		if(p->h_sample_done[i] == NULL) {
			ERROR_INDEX(
				"Unable to create load-balancing thread [%d]'s synchronization objects.", 
				i
			);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		ret = sem_init(&p->h_sample[i], 0, 0);
		if(ret == -1) {
			ERROR_INDEX(
				"Unable to create load-balancing thread [%d]'s synchronization objects.", 
				i
			);
		}
		ret = sem_init(&p->h_sample_done[i], 0, 0);
		if(ret == -1) {
			ERROR_INDEX(
				"Unable to create load-balancing thread [%d]'s synchronization objects.", 
				i
			);
		}
#else // __PL_MACOSX__
		memset(
			p->sample_sem_names[i], 
			0, 
			sizeof(p->sample_sem_names[i])
		);
		sprintf(
			p->sample_sem_names[i], 
			"%s%d", 
			SAMPLE_SEMAPHORE_BASE_NAME, 
			i
		); 
		p->h_sample[i] = sem_open(
			p->sample_sem_names[i], 
			O_CREAT
		);
		if(p->h_sample[i] == SEM_FAILED) {
			ERROR_INDEX(
				"Unable to create load-balancing thread [%d]'s synchronization objects.", 
				i
			);
		}
		memset(
			p->sample_done_sem_names[i], 
			0, 
			sizeof(p->sample_done_sem_names[i])
		);
		sprintf(
			p->sample_done_sem_names[i], 
			"%s%d", 
			SAMPLE_DONE_SEMAPHORE_BASE_NAME, 
			i
		);
		p->h_sample_done[i] = sem_open(
			p->sample_done_sem_names[i], 
			O_CREAT
		);
		if(p->h_sample_done[i] == SEM_FAILED) {
			ERROR_INDEX(
				"Unable to create load-balancing thread [%d]'s synchronization objects.", 
				i
			);
		}
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	} // for i

	//-------------------------------------------------------------------------
	// Set command to COLLECT_START_DATA, so start work and energy data
	// - if applicable - data will be collected right at load-balancing 
	// threads' startup.
	//-------------------------------------------------------------------------
	p->command = COLLECT_START_DATA;

	//-------------------------------------------------------------------------
	// Create and start load-balancing threads.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->threads_count; i++) {
#ifdef __PL_WINDOWS__
		p->h_load_balancing_threads[i] = CreateThread(
			NULL, 
			0, 
			(LPTHREAD_START_ROUTINE)load_balancing_thread, 
			(LPVOID)p, 
			0, 
			&p->load_balancing_threads_ids[i]
		);
		if(p->h_load_balancing_threads[i] == NULL) {
			ERROR_INDEX(
				"Unable to create load-balancing thread [%d].", 
				i
			);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = pthread_create(
			&p->h_load_balancing_threads[i], 
			NULL, 
			load_balancing_thread, 
			(void *)p
		);
		if(ret != 0) {
			ERROR_INDEX(
				"Unable to create load-balancing thread [%d].", 
				i
			);
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	} // for i
#endif // __CEE_LOAD_BALANCING__

	//-----------------------------------------------------------------------------
	// display startup message and several settings info.
	//-----------------------------------------------------------------------------
	ret = display_configuration_message(p);
	assert(ret == PL_SUCCESS);

#ifdef __CEE_LIVE_MONITORING__

	//-------------------------------------------------------------------------
	// Open cee's PL.
	//-------------------------------------------------------------------------
	p->cee_pld = pl_open(
		CEE_APPLICATION_NAME, 
		CEE_COUNTERS_STRINGS_COUNT, 
		cee_counters, 
		&p->uuid
	);
	if(p->cee_pld == PL_INVALID_DESCRIPTOR) {
		_ERROR("Unable to open CEE's PL.");
	}

	//-------------------------------------------------------------------------
	// Write static counters.
	//-------------------------------------------------------------------------
	ret = write_static_counters(p);
	if(ret != PL_SUCCESS) {
		_ERROR("Unable to write CEE's static counters.");
	}
#endif // __CEE_LIVE_MONITORING__

	/*-----------------------------------------------------------------------*/

#ifdef __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Note:
	//    Nothing to be done here, since the start work and energy - if 
	//    applicable - data are collected by the load-balancing threads
	//    on first activation.
	//-------------------------------------------------------------------------
#else // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Capture work data.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->esrv_pls_count; i++) {
		ret = pl_read(
			p->work_plds[i], 
			&p->start_work_data[i], 
			p->work_index
		);
		if(ret != PL_SUCCESS) {
			WARNING_INDEX(
				"Unable to read application PL [%d] work counter.", 
				i
			);
		}
	} // for i

	//-------------------------------------------------------------------------
	// Capture start energy data.
	//-------------------------------------------------------------------------
#ifdef __CEE_ESRV_ON_EACH_NODE__
	for(i = 0; i < p->esrv_pls_count; i++) {
		ret = pl_read(
			p->esrv_plds[i], 
			&p->esrv_status[i], 
			ESRV_COUNTER_STATUS_INDEX
		);
		if(ret != PL_SUCCESS) {
			ERROR_INDEX(
				"Unable to read ESRV's instance [%d] status counter (ESRV_COUNTER_STATUS_INDEX).", 
				i
			);
		}
		if(p->esrv_status[i] == ESRV_STATUS_RUNNING) { 
			ret = pl_read(
				p->esrv_plds[i], 
				&p->start_energy_data[i], 
				ESRV_COUNTER_ENERGY_JOULES_INDEX
			);
			if(ret != PL_SUCCESS) {
				WARNING_INDEX(
					"Unable to read ESRV PL [%d] energy counter.", 
					i
				);
			}
		} else {
			ERROR_INDEX(
				"ESRV instance [%d] doesn't seem to be alive anymore.", 
				i
			);
		}
	} // for i
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	ret = pl_read(
		p->esrv_pld, 
		&p->esrv_status, 
		ESRV_COUNTER_STATUS_INDEX
	);
	if(ret != PL_SUCCESS) {
		_ERROR("Unable to read the ESRV instance's status counter (ESRV_COUNTER_STATUS_INDEX).");
	}
	if(p->esrv_status == ESRV_STATUS_RUNNING) { 
		ret = pl_read(
			p->esrv_pld, 
			&p->start_energy_data, 
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		if(ret != PL_SUCCESS) {
			WARNING("Unable to read the ESRV PL energy counter.");
		}
	} else {
		_ERROR("The ESRV on the aggregation node doesn't seem to be alive anymore.");
	}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#endif // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Set command to COLLECT_DATA.
	//-------------------------------------------------------------------------
	p->command = COLLECT_DATA;

	//-------------------------------------------------------------------------
	// Collect work and energy data until end is requested or requested sample
	// count is reached.
	//-------------------------------------------------------------------------
	do {

		//---------------------------------------------------------------------
		// Collection data for sampling time check.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = QueryPerformanceCounter(&start_time);
		if(bret == FALSE) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = gettimeofday(&start_time, NULL);
		if(ret != 0) {
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			_ERROR("Unable to measure sampling start time.");
		}

#ifdef __CEE_LOAD_BALANCING__

		//---------------------------------------------------------------------
		// Begin load-balancing threads' data collection.
		// Note:
		//    When load balancing is activated, the load balancing threads 
		//    collects work and enegy data.  The energy data is collected 
		//    by the load balancing threads only if __CEE_ESRV_ON_EACH_NODE__
		//    is defined.
		//---------------------------------------------------------------------
		ret = signal_load_balancing_threads_to_sample(p);
		if(ret != PL_SUCCESS) {
			_ERROR("Unable to initiate load-balancing threads' sammpling.");
		}

		//---------------------------------------------------------------------
		// Wait load balancing threads' data collection end.
		//---------------------------------------------------------------------
		ret = wait_for_load_balancing_threads_end_of_sample(p);
		if(ret != PL_SUCCESS) {
			_ERROR("Unable to detect load-balancing threads' end of sampling.");
		}
#else // __CEE_LOAD_BALANCING__

		//---------------------------------------------------------------------
		// Read work counters.
		//---------------------------------------------------------------------
		for(i = 0; i < p->work_pls_count; i++) {
			ret = pl_read(
				p->work_plds[i], 
				&p->work_data[i], 
				p->work_index
			);
			if(ret != PL_SUCCESS) {
				WARNING_INDEX(
					"Unable to read application PL [%d] work counter." , 
					i
				);
			}
		}

		//---------------------------------------------------------------------
		// Read the energy counters.
		//---------------------------------------------------------------------
#ifdef __CEE_ESRV_ON_EACH_NODE__
		for(i = 0; i < p->esrv_pls_count; i++) {
			ret = pl_read(
				p->esrv_plds[i], 
				&p->esrv_status[i], 
				ESRV_COUNTER_STATUS_INDEX
			);
			if(ret != PL_SUCCESS) {
				ERROR_INDEX(
					"Unable to read ESRV's instance [%d] status counter (ESRV_COUNTER_STATUS_INDEX).", 
					i
				);
			}
			if(p->esrv_status[i] == ESRV_STATUS_RUNNING) { 
				ret = pl_read(
					p->esrv_plds[i], 
					&p->energy_data[i], 
					ESRV_COUNTER_ENERGY_JOULES_INDEX
				);
				if(ret != PL_SUCCESS) {
					WARNING_INDEX(
						"Unable to read ESRV PL [%d] energy counter.", 
						i
					);
				}
			} else {
				ERROR_INDEX(
					"ESRV instance [%d] doesn't seem to be alive anymore.", 
					i
				);
			}
		}
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
		ret = pl_read(
			p->esrv_pld, 
			&p->esrv_status, 
			ESRV_COUNTER_STATUS_INDEX
		);
		if(ret != PL_SUCCESS) {
			_ERROR("Unable to read the ESRV instance's status counter (ESRV_COUNTER_STATUS_INDEX).");
		}
		if(p->esrv_status == ESRV_STATUS_RUNNING) { 
			ret = pl_read(
				p->esrv_pld, 
				&p->energy_data, 
				ESRV_COUNTER_ENERGY_JOULES_INDEX
			);
			if(ret != PL_SUCCESS) {
				WARNING("Unable to read the ESRV PL energy counter.");
			}
		} else {
			_ERROR("The ESRV on the aggregation node doesn't seem to be alive anymore.");
		}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#endif // __CEE_LOAD_BALANCING__

#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__

		//---------------------------------------------------------------------
		// Read the energy counter.
		//---------------------------------------------------------------------
		ret = pl_read(
			p->esrv_pld, 
			&p->esrv_status, 
			ESRV_COUNTER_STATUS_INDEX
		);
		if(ret != PL_SUCCESS) {
			_ERROR("Unable to read the ESRV instance's status counter (ESRV_COUNTER_STATUS_INDEX).");
		}
		if(p->esrv_status == ESRV_STATUS_RUNNING) { 
			ret = pl_read(
				p->esrv_pld, 
				&p->energy_data, 
				ESRV_COUNTER_ENERGY_JOULES_INDEX
			);
			if(ret != PL_SUCCESS) {
				WARNING("Unable to read the ESRV PL energy counter.");
			}
		} else {
			_ERROR("The ESRV on the aggregation node doesn't seem to be alive anymore.");
		}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__

#ifdef __CEE_LIVE_MONITORING__

		//-------------------------------------------------------------------------
		// Conpute statistical data and update cee's PL.
		//-------------------------------------------------------------------------
		ret = compute_statistics(p);
		if(ret != PL_SUCCESS) {
			WARNING("Unable to compute statistical data.");
		}

		//-------------------------------------------------------------------------
		// Write counters' values into cee's PL.
		//-------------------------------------------------------------------------
		ret = write_counters(p);
		if(ret != PL_SUCCESS) {
			_ERROR("Unable to write CEE's counters.");
		}
#endif // __CEE_LIVE_MONITORING__

		//---------------------------------------------------------------------
		// Display sampling data.
		//---------------------------------------------------------------------
		p->samples_collected += 1;
#ifdef __PL_WINDOWS__
		chars_displayed = fprintf(stdout, "Samples:                                                         [%I64u]", p->samples_collected);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
		chars_displayed = fprintf(stdout, "Samples:                                                         [%llu]", p->samples_collected);
		fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		for(i = 0; i < (unsigned int)chars_displayed; i++) { 
			fprintf(stdout, "\b"); 
		}

		//---------------------------------------------------------------------
		// Compute time to sleep based on actual data collection
		// & computation time.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = QueryPerformanceCounter(&end_time);
		if(bret == FALSE) {
			_ERROR("Unable to measure sampling end time.");
		}
		measurement_time_in_ms = (double)(
			(end_time.QuadPart - start_time.QuadPart) * 
			(double)1000.0/(double)frequency.QuadPart)
		;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
		ret = gettimeofday(
			&end_time, 
			NULL
		); 
		if(ret != 0) {
			_ERROR("Unable to measure sampling end time.");
		}
		measurement_time_in_ms = (double)( 
			((end_time.tv_sec - start_time.tv_sec) * (double)1000.0) + // 1 second = 1000 milliseconds
			((end_time.tv_usec - start_time.tv_usec) / (double)1000.0) // 1 microsecond = 0.001 milliseconds or 1 millisecond = 1000 microseconds
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		time_to_sleep_in_ms = 
			maximum_allowed_measurement_time_in_ms - 
			measurement_time_in_ms
		;

		//---------------------------------------------------------------------
		// check for slow measurement.
		//---------------------------------------------------------------------
		if(time_to_sleep_in_ms < 0.0) {
			WARNING("Too Slow To Collect Data.");
			time_to_sleep_in_ms = 0.0;
		}

		//---------------------------------------------------------------------
		// Pause sampling for the sampling interval less the collection time.
		// Note:
		//    This is where the timer precision comes in play since even if the
		//    time to sleep calculation is accurate to the ms, the OS can very
		//    well not satisfy our request.  We try to mitigate with priority,
		//    but still, we are not in real-time domain...
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		Sleep((DWORD)time_to_sleep_in_ms);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		time_to_sleep_in_s = (int)(time_to_sleep_in_ms / (double)1000.0);
		time_spec.tv_sec = time_to_sleep_in_s;
		time_spec.tv_nsec = (long int)(
			(time_to_sleep_in_ms - (time_to_sleep_in_s * 
			(double)1000.0)) * (double)1000000.0  // 1 millisecond = 1 000 000 nanoseconds
		);
		nanosleep(&time_spec, NULL);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Measure sampling effective duration.
		// Note:
		//    This is done after the sleep, so we can at least detect the 
		//    error introduced by the OS.  We cannot do much about it, but
		//    we can signal it (better knowing).
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = QueryPerformanceCounter(&end_time);
		if(bret == FALSE) {
			_ERROR("Unable to measure effective sampling end time.");
		}
		total_duration_in_ms = (double)(
			(end_time.QuadPart - start_time.QuadPart) * 
			(double)1000.0/(double)frequency.QuadPart
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = gettimeofday(
			&end_time, 
			NULL
		);
		if(ret != 0) {
			_ERROR("Unable to measure effective sampling end time.");
		}
		total_duration_in_ms = (double)( 
			((end_time.tv_sec - start_time.tv_sec) * (double)1000.0) + // 1 second = 1000 milliseconds
			((end_time.tv_usec - start_time.tv_usec) / (double)1000.0) // 1 microsecond = 0.001 milliseconds or 1 millisecond = 1000 microseconds
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Check if effective sampling time is in the allowed time margin.
		//---------------------------------------------------------------------
		if(total_duration_in_ms > maximum_allowed_measurement_time_in_ms + allowed_time_margin_in_ms) {
#ifdef __PL_WINDOWS__
			SAMPLING_TIME_WARNING(
				"Sample [%I64u] took [%+8.2f] ms instead of <= [%+8.2f] ms (M: [%+8.2f] ms + S: [%+8.2f] ms).",
				p->samples_collected,
				total_duration_in_ms,
				maximum_allowed_measurement_time_in_ms + allowed_time_margin_in_ms,
				measurement_time_in_ms,
				time_to_sleep_in_ms
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			SAMPLING_TIME_WARNING(
				"Sample [%llu] took [%+8.2f] ms instead of <= [%+8.2f] ms (M: [%+8.2f] ms + S: [%+8.2f] ms).",
				p->samples_collected,
				total_duration_in_ms,
				maximum_allowed_measurement_time_in_ms + allowed_time_margin_in_ms,
				measurement_time_in_ms,
				time_to_sleep_in_ms
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		}

		//---------------------------------------------------------------------
		// Check exit condition.
		// Note:
		//    If the user has requested a limited number of samples, then we
		//    collect a last time the work and energy counters to provide an
		//    accurate set of results.
		//---------------------------------------------------------------------
		if(p->samples != NO_SAMPLING_LIMIT) {
			if(p->samples == (int)p->samples_collected) {

#ifdef __CEE_LOAD_BALANCING__

				//---------------------------------------------------------------------
				// Begin load-balancing threads' data collection.
				//---------------------------------------------------------------------
				ret = signal_load_balancing_threads_to_sample(p);
				if(ret != PL_SUCCESS) {
					_ERROR("Unable to initiate load-balancing threads' sammpling.");
				}

				//---------------------------------------------------------------------
				// Wait - for the last time - load balancing threads' data collection end.
				//---------------------------------------------------------------------
				ret = wait_for_load_balancing_threads_end_of_sample(p);
				if(ret != PL_SUCCESS) {
					_ERROR("Unable to detect load-balancing threads' end of sampling.");
				}
#else // __CEE_LOAD_BALANCING__

				//---------------------------------------------------------------------
				// Read work counters.
				//---------------------------------------------------------------------
				for(i = 0; i < p->work_pls_count; i++) {
					ret = pl_read(
						p->work_plds[i], 
						&p->work_data[i], 
						p->work_index
					);
					if(ret != PL_SUCCESS) {
						WARNING_INDEX(
							"Unable to read application PL [%d] work counter.", 
							i
						);
					}
				}

				//---------------------------------------------------------------------
				// Read the energy counters.
				//---------------------------------------------------------------------
#ifdef __CEE_ESRV_ON_EACH_NODE__
				for(i = 0; i < p->esrv_pls_count; i++) {
					ret = pl_read(
						p->esrv_plds[i], 
						&p->esrv_status[i], 
						ESRV_COUNTER_STATUS_INDEX
					);
					if(ret != PL_SUCCESS) {
						_ERROR("Unable to read the ESRV instance's status counter (ESRV_COUNTER_STATUS_INDEX).");
					}
					if(p->esrv_status[i] == ESRV_STATUS_RUNNING) {
						ret = pl_read(
							p->esrv_plds[i], 
							&p->energy_data[i], 
							ESRV_COUNTER_ENERGY_JOULES_INDEX
						);
						if(ret != PL_SUCCESS) {
							WARNING_INDEX("Unable to read ESRV PL [%d] energy counter." , i);
						}
					} else {
						_ERROR("The ESRV on the aggregation node doesn't seem to be alive anymore.");
					}
				} // for i
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
				ret = pl_read(
					p->esrv_pld, 
					&p->esrv_status, 
					ESRV_COUNTER_STATUS_INDEX
				);
				if(ret != PL_SUCCESS) {
					_ERROR("Unable to read the ESRV instance's status counter (ESRV_COUNTER_STATUS_INDEX).");
				}
				if(p->esrv_status == ESRV_STATUS_RUNNING) {
					ret = pl_read(
						p->esrv_pld, 
						&p->energy_data, 
						ESRV_COUNTER_ENERGY_JOULES_INDEX
					);
					if(ret != PL_SUCCESS) {
						WARNING("Unable to read the ESRV PL energy counter.");
					}
				} else {
					WARNING("The ESRV on the aggregation node doesn't seem to be alive anymore.");
				}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#endif // __CEE_LOAD_BALANCING__

				//-----------------------------------------------------------------
				// Set exit condition.
				//-----------------------------------------------------------------
				control_data.command = EXIT;

#ifdef __CEE_LOAD_BALANCING__

				//---------------------------------------------------------------------
				// Begin - for the last time - load-balancing threads' data collection.
				// Note:
				//    We do not wait load balancing threads' data collection end since
				//    the end command is set and each load-balancing thread will
				//    exit gracrfully and terminate.
				//---------------------------------------------------------------------
				ret = signal_load_balancing_threads_to_sample(p);
				if(ret != PL_SUCCESS) {
					_ERROR("Unable to initiate load-balancing threads' sammpling.");
				}
#endif // __CEE_LOAD_BALANCING__
			}
		}

	} while(p->command == COLLECT_DATA);

	/*-----------------------------------------------------------------------*/

	//-------------------------------------------------------------------------
	// Compute sampling statistics.
	// Note:
	//    If __CEE_LIVE_MONITORING__ is defined, then this is the last time the
	//    statistical data is computed.  If __CEE_LIVE_MONITORING__ is not defined,
	//    then it is the first and last time the statistical data is computed.
	// Note:
	//    Never fails, reports possible issues during computation.
	//-------------------------------------------------------------------------
	ret = compute_statistics(p);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// Report sampling results.
	// Note:
	//    Never fails.
	//-------------------------------------------------------------------------
	ret = display_statistics(p);
	assert(ret == PL_SUCCESS);
	if(p->f_output_file == 1) {

		//---------------------------------------------------------------------
		// Remind that result is stored in the output file.
		//---------------------------------------------------------------------
		fprintf(stdout, "-------------------------------------------------------------------------------\n");
		fprintf(stdout, " *** Sampling Report is in file: [%s] ***\n", p->output_file_name);
		fprintf(stdout, "-------------------------------------------------------------------------------\n");

		//---------------------------------------------------------------------
		// Close the output file.
		//---------------------------------------------------------------------
		ret = fclose(p->output_file);
		if(ret != 0) {
			_ERROR("Unable to close the output file.");
		}
		p->output_file = NULL;
		p->output_file_name = NULL;
		p->f_output_file = 0;
	}

#ifdef __CEE_LIVE_MONITORING__

	//-----------------------------------------------------------------
	// Write  - for the last time - counters' values into cee's PL.
	//-----------------------------------------------------------------
	ret = write_counters(p);
	if(ret != PL_SUCCESS) {
		_ERROR("Unable to write CEE's counters.");
	}
#endif // __CEE_LIVE_MONITORING__

main_stop:

	//-------------------------------------------------------------------------
	// Close PL descriptors.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->work_pls_count; i++) {
		if(p->work_plds[i] != PL_INVALID_DESCRIPTOR) {
			ret = pl_close(p->work_plds[i]);
			if(ret != PL_SUCCESS) {
				ERROR_INDEX("Unable to close work PL [%d] descriptor.", i);
			}
			p->work_plds[i] = PL_INVALID_DESCRIPTOR;
		}
	}
#ifdef __CEE_ESRV_ON_EACH_NODE__
	if(p->esrv_plds != NULL) {
		for(i = 0; i < p->esrv_pls_count; i++) {
			if(p->esrv_plds[i] != PL_INVALID_DESCRIPTOR) {
				ret = pl_close(p->esrv_plds[i]);
				if(ret != PL_SUCCESS) {
					ERROR_INDEX("Unable to close ESRV PL [%d] descriptor.", i);
				}
				p->esrv_plds[i] = PL_INVALID_DESCRIPTOR;
			}
		}
	}
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	if(p->esrv_pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(p->esrv_pld);
		if(ret != PL_SUCCESS) {
			_ERROR("Unable To Close The ESRV PL Descriptor.");
		}
		p->esrv_pld = PL_INVALID_DESCRIPTOR;
	}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__

	//-------------------------------------------------------------------------
	// De-allocate memory used to store Pl indexes.
	//-------------------------------------------------------------------------
	if(work_pl_indexes != NULL) {
		free(work_pl_indexes);
		work_pl_indexes = NULL;
	}
#ifdef __CEE_ESRV_ON_EACH_NODE__
	if(esrv_pl_indexes != NULL) {
		free(esrv_pl_indexes);
		esrv_pl_indexes = NULL;
	}
#endif // __CEE_ESRV_ON_EACH_NODE__

	//-------------------------------------------------------------------------
	// De-allocate memory used to store applicaton PL descriptors and data.
	//-------------------------------------------------------------------------
	if(p->work_plds != NULL) {
		free(p->work_plds);
		p->work_plds = NULL;
	}
	if(p->work_data != NULL) {
		free(p->work_data);
		p->work_data = NULL;
	}
	if(p->start_work_data != NULL) {
		free(p->start_work_data);
		p->start_work_data = NULL;
	}
#ifdef __CEE_ESRV_ON_EACH_NODE__

	//-------------------------------------------------------------------------
	// De-allocate memory used to store ESRV PL descriptors and data - if
	// applicable.
	//-------------------------------------------------------------------------
	if(p->esrv_plds != NULL) {
		free(p->esrv_plds);
		p->esrv_plds = NULL;
	}
	if(p->energy_data != NULL) {
		free(p->energy_data);
		p->energy_data = NULL;
	}
	if(p->start_energy_data != NULL) {
		free(p->start_energy_data);
		p->start_energy_data = NULL;
	}
	if(p->energy_data_multipliers != NULL) {
		free(p->energy_data_multipliers);
		p->energy_data_multipliers = NULL;
	}
	if(p->esrv_status != NULL) {
		free(p->esrv_status);
		p->esrv_status = NULL;
	}

#ifdef __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// De-allocate memory used to store load-balancing threads' energy PL data
	// - if applicable - and their count.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->threads_count; i++) {
		if(p->per_thread_esrv_plds[i] != NULL) {
			free(p->per_thread_esrv_plds[i]);
			p->per_thread_esrv_plds[i] = NULL;
		}
	}
	free(p->per_thread_esrv_plds);
	p->per_thread_esrv_plds = NULL;

	if(p->per_thread_esrv_plds_count != NULL) {
		free(p->per_thread_esrv_plds_count);
		p->per_thread_esrv_plds_count = NULL;
	}
#endif // __CEE_LOAD_BALANCING__
#endif // __CEE_ESRV_ON_EACH_NODE__

#ifdef __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// De-allocate memory used to store load-balancing threads' work PL data
	// - if applicable - and their count.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->threads_count; i++) {
		if(p->per_thread_work_plds[i] != NULL) {
			free(p->per_thread_work_plds[i]);
			p->per_thread_work_plds[i] = NULL;
		}
	}
	free(p->per_thread_work_plds);
	p->per_thread_work_plds = NULL;

	if(p->per_thread_work_plds_count != NULL) {
		free(p->per_thread_work_plds_count);
		p->per_thread_work_plds_count = NULL;
	}

	//-------------------------------------------------------------------------
	// Destroy load-balancing threads' synchronization objects and de-allocate
	// associated memory.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	for(i = 0; i < p->threads_count; i++) {
		if(p->h_sample[i] != NULL) {
			bret = CloseHandle(p->h_sample[i]);
			if(bret == FALSE) {
				ERROR_INDEX(
					"Unable to de-allocate memory used to store load-balancing thread synchronization object [%d].", 
					i
				);
			}
		}
	}
	free(p->h_sample);
	p->h_sample = NULL;

	for(i = 0; i < p->threads_count; i++) {
		if(p->h_sample_done[i] != NULL) {
			bret = CloseHandle(p->h_sample_done[i]);
			if(bret == FALSE) {
				ERROR_INDEX(
					"Unable to de-allocate memory used to store load-balancing thread synchronization object [%d].", 
					i
				);
			}
		}
	}
	free(p->h_sample_done);
	p->h_sample_done = NULL;

	for(i = 0; i < p->threads_count; i++) {
		if(p->h_load_balancing_threads[i] != NULL) {
			bret = CloseHandle(p->h_load_balancing_threads[i]);
			if(bret == FALSE) {
				ERROR_INDEX(
					"Unable to de-allocate memory used to store load-balancing thread synchronization object [%d].", 
					i
				);
			}
		}
	}
	free(p->h_load_balancing_threads);
	p->h_load_balancing_threads = NULL;
	
	if(p->load_balancing_threads_ids != NULL) {
		free(p->load_balancing_threads_ids);
		p->load_balancing_threads_ids = NULL;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

	//-------------------------------------------------------------------------
	// Destroy load-balancing threads' synchronization objects and de-allocate
	// associated memory.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->threads_count; i++) {
#ifndef __PL_MACOSX__
retry_sample:
		ret = sem_destroy(&p->h_sample[i]);
		if(ret == -1) {
			if(errno == EBUSY) { 
				sched_yield(); 
				goto retry_sample;
			} else {
				ERROR_INDEX(
					"Unable to de-allocate memory used to store load-balancing thread synchronization object [%d].", 
					i
				);
			}
		}
#else // __PL_MACOSX__
		ret = sem_unlink(p->sample_sem_names[i]);
		if(ret == -1) {
			ERROR_INDEX(
				"Unable to de-allocate memory used to store load-balancing thread synchronization object [%d].", 
				i
			);
		}
#endif // __PL_MACOSX__
	} // for i
	free(p->h_sample);
	p->h_sample = NULL;

	for(i = 0; i < p->threads_count; i++) {
#ifndef __PL_MACOSX__
retry_sample_done:
		ret = sem_destroy(&p->h_sample_done[i]);
		if(ret == -1) {
			if(errno == EBUSY) { 
				sched_yield(); 
				goto retry_sample_done;
			} else {
				ERROR_INDEX(
					"Unable to de-allocate memory used to store load-balancing thread synchronization object [%d].", 
					i
				);
			}
		}
#else // __PL_MACOSX__
		ret = sem_unlink(p->sample_done_sem_names[i]);
		if(ret == -1) {
			ERROR_INDEX(
				"Unable to de-allocate memory used to store load-balancing thread synchronization object [%d].", 
				i
			);
		}
#endif // __PL_MACOSX__
	} // for i

	free(p->h_sample_done);
	p->h_sample_done = NULL;

	free(p->h_load_balancing_threads);
	p->h_load_balancing_threads = NULL;

#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // __CEE_LOAD_BALANCING__

main_done:

#ifdef __CEE_LIVE_MONITORING__

	//-------------------------------------------------------------------------
	// Close cee's PL.
	//-------------------------------------------------------------------------
	if(p->cee_pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(p->cee_pld);
		if(ret != PL_SUCCESS) {
			_ERROR("Unable to close CEE's PL.");
		}
	}
#endif // __CEE_LIVE_MONITORING__

#ifdef __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// Restore timer resolution.
	//-------------------------------------------------------------------------
	mmret = timeEndPeriod(--resolution);
	if(mmret != TIMERR_NOERROR) {
		_ERROR("Unable to restore thread's initial resolution.");
	}
#endif // __IEC_WINDOWS__
#endif // __IEC_TRADE_POWER_DRAW_FOR_PRECISION__

	//-------------------------------------------------------------------------
	// Free memory allocated for us by plh_dynamic_read_pl_folder.
	//-------------------------------------------------------------------------
	if(pc.entries != NULL) {
		free(pc.entries);
		pc.entries = NULL;
	}

	//-------------------------------------------------------------------------
	// End program.
	//-------------------------------------------------------------------------
	if(f_error == 0) {
		return(PL_SUCCESS);
	} else {
		return(PL_FAILURE);
	}
}

#ifdef __CEE_LOAD_BALANCING__
/*-----------------------------------------------------------------------------
Function: load_balancing_thread
Purpose : load-balancing thread's code
In      : pointer to control structure
Out     : updated work and energy data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
LPTHREAD_START_ROUTINE load_balancing_thread(void *px) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
void *load_balancing_thread(void *px) {
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// General purpose variables.
	//-------------------------------------------------------------------------
	PL_STATUS plret = PL_FAILURE;
	unsigned int i = 0;
	char buffer[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int ret = -1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Load-balancing thread rank, etc. variables.
	//-------------------------------------------------------------------------
	unsigned int rank = 0;
	unsigned int offset = 0;
	unsigned int local_work_pls_count = 0;
#ifdef __CEE_ESRV_ON_EACH_NODE__
	unsigned int local_esrv_pls_count = 0;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __PL_WINDOWS__
	DWORD tid = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	pthread_t tid;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Load-balancing thread's control data pointer (sole thread's argument).
	//-------------------------------------------------------------------------
	PCONTROL_DATA p = NULL;

	//-------------------------------------------------------------------------
	// Thread priority variable (system).
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	struct sched_param threads_sched_param;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	/*-----------------------------------------------------------------------*/

	assert(px != NULL);
	p = (PCONTROL_DATA)px;
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Get this load-balancing thread's rank.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	tid = GetCurrentThreadId();
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	tid = pthread_self();
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	for(i = 0; i < p->threads_count; i++) {
#ifdef __PL_WINDOWS__
		if(tid == p->load_balancing_threads_ids[i]) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		if(tid == p->h_load_balancing_threads[i]) {
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			rank = i;
			goto load_balancing_thread_id_found; 
		}
	}
	LOAD_BALANCING_THREAD_ERROR("Unable to retrive this load-balancing thread's rank.");
	goto load_balancing_thread_end;

load_balancing_thread_id_found:

	//-------------------------------------------------------------------------
	// Boost this thread's priority.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	bret = SetThreadPriority(
		p->h_load_balancing_threads[rank], 
		p->boost_priority
	);
	if(bret == FALSE) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	threads_sched_param.sched_priority = p->boost_priority;
	ret = pthread_setschedparam(
		p->h_load_balancing_threads[rank], 
		SCHED_RR, 
		&threads_sched_param
	);
	if(ret == -1) { 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		LOAD_BALANCING_THREAD_ERROR_INDEX(
			"Unable to boost main thread's priority [%d].", 
			rank
		);
	}

	//-------------------------------------------------------------------------
	// Get this thread's work and ESRV - if applicable - PLs count.
	//-------------------------------------------------------------------------
	local_work_pls_count = p->per_thread_work_plds_count[rank];
	assert(local_work_pls_count > 0);
#ifdef __CEE_ESRV_ON_EACH_NODE__
	local_esrv_pls_count = p->per_thread_esrv_plds_count[rank];
	assert(local_esrv_pls_count > 0);
#endif // __CEE_ESRV_ON_EACH_NODE__

	//-------------------------------------------------------------------------
	// Compute this thread's data storage offset.
	// Note:
	//    Since the work and ESRV PLs count are equal by definition, only one
	//    data offset is computed and used for storing both data - and if
	//    applicable for the energy data.
	//-------------------------------------------------------------------------
	offset = 0;
	for(i = 0; i < rank; i++) {
		offset += p->per_thread_work_plds_count[i];
	}

	//-------------------------------------------------------------------------
	// Collect work and energy - if applicable - start data.
	// Note:
	//    The main thread sets the command to COLLECT_START_DATA right before
	//    load-balancing threads' creation.  Therefore, the command sequence
	//    expected is always: COLLECT_START_DATA, x * COLLECT_DATA and EXIT.
	//-------------------------------------------------------------------------
	if(p->command == COLLECT_START_DATA) {

		//---------------------------------------------------------------------
		// Read work and energy counters - if applicable - as start data.
		//---------------------------------------------------------------------
		for(i = 0; i < local_work_pls_count; i++) {
			plret = pl_read(
				p->per_thread_work_plds[rank][i], 
				&p->start_work_data[offset + i], 
				p->work_index
			);
			if(plret != PL_SUCCESS) {
				WARNING_INDEX(
					"Unable to read application PL [%d] work counter.", 
					i
				);
			}
#ifdef __CEE_ESRV_ON_EACH_NODE__
			plret = pl_read(
				p->per_thread_esrv_plds[rank][i], 
				&p->esrv_status[offset + i], 
				ESRV_COUNTER_STATUS_INDEX
			);
			if(plret != PL_SUCCESS) {
				LOAD_BALANCING_THREAD_ERROR_INDEX(
					"Unable to read ESRV's instance [%d] status counter (ESRV_COUNTER_STATUS_INDEX).", 
					i
				);
			}
			if(p->esrv_status[offset + i] == ESRV_STATUS_RUNNING) {
				plret = pl_read(
					p->per_thread_esrv_plds[rank][i], 
					&p->start_energy_data[offset + i], 
					ESRV_COUNTER_ENERGY_JOULES_INDEX
				);
				if(plret != PL_SUCCESS) {
					WARNING_INDEX(
						"Unable to read ESRV [%d]'s energy counter.", 
						i
					);
				}
			} else {
				LOAD_BALANCING_THREAD_ERROR_INDEX(
					"ESRV instance [%d] doesn't seem to be alive anymore.", 
					i
				);
			}
#endif // __CEE_ESRV_ON_EACH_NODE__
		}
	}

	//-------------------------------------------------------------------------
	// Main loop. each "itteration" is triggered by ecc's main thread.
	//-------------------------------------------------------------------------
	do {

		//---------------------------------------------------------------------
		// Wait signal from ecc's main thread to start a sampling cycle.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		WaitForSingleObject(
			p->h_sample[rank], 
			INFINITE
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		ret = sem_wait(&p->h_sample[rank]);
#else // __PL_MACOSX__
		ret = sem_wait(p->h_sample[rank]);
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Since the end of sampling can be set during the signal wait, we 
		// check the end condition right after the sample signal was set by
		// ecc's main thread.
		//---------------------------------------------------------------------
		if(p->command != COLLECT_DATA) {
			goto load_balancing_thread_end; 
		}

		//---------------------------------------------------------------------
		// Read work and energy counters - if applicable.
		//---------------------------------------------------------------------
		for(i = 0; i < local_work_pls_count; i++) {
			plret = pl_read(
				p->per_thread_work_plds[rank][i], 
				&p->work_data[offset + i], 
				p->work_index
			);
			if(plret != PL_SUCCESS) {
				WARNING_INDEX(
					"Unable to read application PL [%d] work counter.", 
					i
				);
			}
#ifdef __CEE_ESRV_ON_EACH_NODE__
			plret = pl_read(
				p->per_thread_esrv_plds[rank][i], 
				&p->esrv_status[offset + i], 
				ESRV_COUNTER_STATUS_INDEX
			);
			if(plret != PL_SUCCESS) {
				LOAD_BALANCING_THREAD_ERROR_INDEX(
					"Unable to read ESRV's instance [%d] status counter (ESRV_COUNTER_STATUS_INDEX).", 
					i
				);
			}
			if(p->esrv_status[offset + i] == ESRV_STATUS_RUNNING) {
				plret = pl_read(
					p->per_thread_esrv_plds[rank][i], 
					&p->energy_data[offset + i], 
					ESRV_COUNTER_ENERGY_JOULES_INDEX
				);
				if(plret != PL_SUCCESS) {
					WARNING_INDEX(
						"Unable to read ESRV [%d]'s energy counter.", 
						i
					);
				}
			} else {
				LOAD_BALANCING_THREAD_ERROR_INDEX(
					"ESRV instance [%d] doesn't seem to be alive anymore.", 
					i
				);
			}
#endif // __CEE_ESRV_ON_EACH_NODE__
		}

		//---------------------------------------------------------------------
		// Signal load-balancing thread has finished the sampling cycle.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		bret = SetEvent(p->h_sample_done[rank]);
		if(bret == FALSE) {
			LOAD_BALANCING_THREAD_ERROR_INDEX(
				"Unable to signal load-balancing thread [%d]'s completion.", 
				rank
			);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		ret = sem_post(&p->h_sample_done[rank]);
#else // __PL_MACOSX__
		ret = sem_post(p->h_sample_done[rank]);
#endif // __PL_MACOSX__
		if(ret == -1) {
			LOAD_BALANCING_THREAD_ERROR_INDEX(
				"Unable to signal load-balancing thread [%d]'s completion.", 
				rank
			);
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	} while(p->command == COLLECT_DATA);

load_balancing_thread_end:

	//-------------------------------------------------------------------------
	// Signal load-balancing thread's end.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	return((PTHREAD_START_ROUTINE)PL_SUCCESS);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	return(PL_SUCCESS);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

load_balancing_thread_error:

	//-------------------------------------------------------------------------
	// This really should not happen...
	// Note:
	//    This is a bit of a repetition, but it is also a very bad place to be. 
	//-------------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
	sprintf(
		buffer, 
		"Unexpected load-balancing thread [%d]'s end of run.", 
		rank
	);
	fprintf(
		stderr, 
		"Error: %s [%d]\n", 
		buffer, 
		__LINE__
	);
#ifdef __PL_WINDOWS__
	return((PTHREAD_START_ROUTINE)PL_SUCCESS);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	return(PL_SUCCESS);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}
#endif // __CEE_LOAD_BALANCING__

/*-----------------------------------------------------------------------------
Function: compute_statistics
Purpose : compute statistical data
In      : pointer to control data structure
Out     : updated statistic data in the control data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int compute_statistics(PCONTROL_DATA p) {
	
	unsigned int i = 0;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Compute sampling statistics -- start by all nodes data.
	//-------------------------------------------------------------------------
	// Work.
	//-------------------------------------------------------------------------
	p->accumulated_start_work_all_nodes = 0;
	for(i = 0; i < p->work_pls_count; i++) {
		p->accumulated_start_work_all_nodes += p->start_work_data[i];
	}
	p->accumulated_work_all_nodes = 0;
	for(i = 0; i < p->work_pls_count; i++) {
		p->accumulated_work_all_nodes += p->work_data[i];
	}
	p->accumulated_work_data = 
		p->accumulated_work_all_nodes - 
		p->accumulated_start_work_all_nodes
	;

	//-------------------------------------------------------------------------
	// Energy.
	//-------------------------------------------------------------------------
#ifdef __CEE_ESRV_ON_EACH_NODE__
	p->accumulated_start_energy_in_joule_all_nodes = 0.0;
	for(i = 0; i < p->esrv_pls_count; i++) {
		p->accumulated_start_energy_in_joule_all_nodes += 
			p->start_energy_data[i] / 
			p->energy_data_multipliers[i]
		;
	}
	p->accumulated_energy_in_joule_all_nodes = 0.0;
	for(i = 0; i < p->esrv_pls_count; i++) {
		p->accumulated_energy_in_joule_all_nodes += 
			p->energy_data[i] / 
			p->energy_data_multipliers[i]
		;
	}
	p->accumulated_enery_in_joules = 
		p->accumulated_energy_in_joule_all_nodes - 
		p->accumulated_start_energy_in_joule_all_nodes
	;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	p->accumulated_enery_in_joules = 
		(double)(
			p->energy_data - 
			p->start_energy_data
		) / 
		p->energy_data_multipliers
	;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
	p->accumulated_enery_in_kwh = 
		p->accumulated_enery_in_joules / 
		JOULES_IN_A_KWH
	;

	if(p->accumulated_work_data != 0) {
		p->average_energy_in_joule_per_work_unit = 
			p->accumulated_enery_in_joules / 
			(double)p->accumulated_work_data
		;
	} else {
		p->average_energy_in_joule_per_work_unit = 0.0;
		WARNING("Unable to compute the average energy in joule per work unit because the accumulated work is equal to zero.");
	}
	if(p->accumulated_work_data != 0) {
		p->average_energy_in_kwh_per_work_unit = 
			p->accumulated_enery_in_kwh / 
			(double)p->accumulated_work_data
		;
	} else {
		p->average_energy_in_kwh_per_work_unit = 0.0;
		WARNING("Unable to compute the average energy in kwh per work unit because the accumulated work is equal to zero.");
	}
	if(p->accumulated_enery_in_joules != 0.0) {
		p->average_work_unit_per_energy_in_joule = 
			(double)p->accumulated_work_data / 
			p->accumulated_enery_in_joules
		;
	} else {
		p->average_work_unit_per_energy_in_joule = 0.0;
		WARNING("Unable to compute the average work unit per energy in joule because the accumulated enery in joules is equal to zero.");
	}
	if(p->accumulated_enery_in_kwh != 0.0) {
		p->average_work_unit_per_energy_in_kwh = 
			(double)p->accumulated_work_data / 
			p->accumulated_enery_in_kwh
		;
	} else {
		p->average_work_unit_per_energy_in_kwh = 0.0;
		WARNING("Unable to compute the average work unit per energy in kwh because the accumulated enery in kwh is equal to zero.");
	}

	//-------------------------------------------------------------------------
	// Continue with per node.
	//-------------------------------------------------------------------------
	if(p->work_pls_count != 0) {
		p->average_work_unit_per_node = 
			(double)p->accumulated_work_data / 
			(double)p->work_pls_count
		;
	} else {
		p->average_work_unit_per_node = 0.0;
		WARNING("Unable to compute the average work unit per node because it seems that no node has contributed to the work done.");
	}
	if(p->work_pls_count != 0) {
		p->average_energy_in_joule_per_node = 
			p->accumulated_enery_in_joules / 
			(double)p->work_pls_count
		;
	} else {
		p->average_energy_in_joule_per_node = 0.0;
		WARNING("Unable to compute the average energy in joule per node because it seems that no node has contributed to the work done.");
	}
	if(p->work_pls_count != 0) {
		p->average_energy_in_kwh_per_node = 
			p->accumulated_enery_in_kwh / 
			(double)p->work_pls_count
		;
	} else {
		p->average_energy_in_kwh_per_node = 0.0;
		WARNING("Unable to compute the average energy in kwh per node because it seems that no node has contributed to the work done.");
	}
	if(p->work_pls_count != 0) {
		p->average_energy_in_joule_per_work_unit_per_node = 
			p->average_energy_in_joule_per_work_unit / 
			(double)p->work_pls_count
		;
	} else {
		p->average_energy_in_joule_per_work_unit_per_node = 0.0;
		WARNING("Unable to compute the average energy in joule per work unit per node because it seems that no node has contributed to the work done.");
	}
	if(p->work_pls_count != 0) {
		p->average_energy_in_kwh_per_work_unit_per_node = 
			p->average_energy_in_kwh_per_work_unit / 
			(double)p->work_pls_count
		;
	} else {
		p->average_energy_in_kwh_per_work_unit_per_node = 0.0;
		WARNING("Unable to compute the average energy in kwh per work unit per node because it seems that no node has contributed to the work done.");
	}
	if(p->work_pls_count != 0) {
		p->average_work_unit_per_energy_in_joule_per_node = 
			p->average_work_unit_per_energy_in_joule / 
			(double)p->work_pls_count
		;
	} else {
		p->average_work_unit_per_energy_in_joule_per_node = 0.0;
		WARNING("Unable to compute the average work unit per energy in joule per node because it seems that no node has contributed to the work done.");
	}
	if(p->work_pls_count != 0) {
		p->average_work_unit_per_energy_in_kwh_per_node = 
			p->average_work_unit_per_energy_in_kwh / 
			(double)p->work_pls_count
		;
	} else {
		p->average_work_unit_per_energy_in_kwh_per_node = 0.0;
		WARNING("Unable to compute the average work unit per energy in kwh per node because the it seems that no node has contributed to the work done.");
	}
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: display_statistics
Purpose : display statisctical data to stdout
In      : pointer to control data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int display_statistics(PCONTROL_DATA p) {
	
	assert(p != NULL);

	fprintf(p->output_file, "-------------------------------------------------------------------------------\n");
	fprintf(p->output_file, "                            *** Sampling Report ***\n");
	fprintf(p->output_file, "--- ALL NODES -----------------------------------------------------------------\n");
	fprintf(p->output_file, "Node(s) aggregated:                                              [%d]\n", p->work_pls_count);
	fprintf(p->output_file, "Sampling interval (seconds):                                     [%d]\n", p->sampling_interval);
#ifdef __PL_WINDOWS__
	fprintf(p->output_file, "Sample(s) collected:                                             [%I64u]\n", p->samples_collected);
	fprintf(p->output_file, "Accumulated work unit(s):                                        [%I64u]\n", p->accumulated_work_data);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	fprintf(p->output_file, "Sample(s) collected:                                             [%llu]\n", p->samples_collected);
	fprintf(p->output_file, "Accumulated work unit(s):                                        [%llu]\n", p->accumulated_work_data);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	fprintf(p->output_file, "Accumulated energy (Joule(s)):                                   [%g]\n", p->accumulated_enery_in_joules);
	fprintf(p->output_file, "Accumulated energy (kWh(s)):                                     [%g]\n", p->accumulated_enery_in_kwh);
	fprintf(p->output_file, "--- AVERAGE ALL NODES ---------------------------------------------------------\n");
	fprintf(p->output_file, "Average energy per work unit (Joule/wu):                         [%g]\n", p->average_energy_in_joule_per_work_unit);
	fprintf(p->output_file, "Average energy per work unit (kWh/wu):                           [%g]\n", p->average_energy_in_kwh_per_work_unit);
	fprintf(p->output_file, "Average work unit per energy (wu/Joule):                         [%g]\n", p->average_work_unit_per_energy_in_joule);
	fprintf(p->output_file, "Average work unit per energy (wu/kWh):                           [%g]\n", p->average_work_unit_per_energy_in_kwh);
	fprintf(p->output_file, "--- AVERAGE PER NODE ----------------------------------------------------------\n");
	fprintf(p->output_file, "Average work unit per node (wu/node):                            [%g]\n", p->average_work_unit_per_node);
	fprintf(p->output_file, "Average energy per node (Joule/node):                            [%g]\n", p->average_energy_in_joule_per_node);
	fprintf(p->output_file, "Average energy per node (kWh/node):                              [%g]\n", p->average_energy_in_kwh_per_node);
	fprintf(p->output_file, "Average energy per work unit per node (Joule/wu/node):           [%g]\n", p->average_energy_in_joule_per_work_unit_per_node);
	fprintf(p->output_file, "Average energy per work unit per node (kWh/wu/node):             [%g]\n", p->average_energy_in_kwh_per_work_unit_per_node);
	fprintf(p->output_file, "Average work unit per energy per node (wu/Joule/node):           [%g]\n", p->average_work_unit_per_energy_in_joule_per_node);
	fprintf(p->output_file, "Average work unit per energy per node (wu/kWh/node):             [%g]\n", p->average_work_unit_per_energy_in_kwh_per_node);
	fprintf(p->output_file, "-------------------------------------------------------------------------------\n");
	fprintf(p->output_file, "                            *** End of Report ***\n");
	fprintf(p->output_file, "-------------------------------------------------------------------------------\n");
	fprintf(p->output_file, "\n");

	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: parser
Purpose : parse user input to set control data
In      : none
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int parser(PCONTROL_DATA p) {

	//-------------------------------------------------------------------------
	// Parsing variables.
	//-------------------------------------------------------------------------
	int i = 0;
	int j = 0;
	int value = 0;
	char buffer[PL_MAX_PATH] = { '\0' };
	char *options[OPTION_STRINGS_COUNT] = { OPTION_STRINGS };
#ifdef __PL_WINDOWS__
	size_t st_ret = 0;
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// String to upper case variables.
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	size_t k = 0;
	size_t l = 0;
	char *pc = NULL;
	char c = '\0';
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(p != NULL);

	for(i = 1; i < p->argc; i++) {
		memset(buffer, 0, sizeof(buffer));
		strncpy(buffer, p->argv[i], sizeof(buffer));
#ifdef __PL_WINDOWS__
		_strupr(buffer);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		pc = buffer;
		l = strlen(buffer);
		for(k = 0; k < l; k++) {
			c = *pc;
			*pc++ = (char)toupper(c);
		}
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		for(j = 0; j < OPTION_STRINGS_COUNT; j++) {
			if(
				strncmp(
					buffer, 
					options[j], 
					strlen(options[j])
				) == 0
			) {
				switch(j) {

					//---------------------------------------------------------
					// [-H] option.
					//---------------------------------------------------------
					case H_ID:
					case HELP_ID:
#ifdef __CEE_LOAD_BALANCING__
						fprintf(
							stdout, 
							HELP_STRING, 
							p->argv[0],
							DEFAULT_LOAD_BALANCING_THREADS_COUNT,
							MIN_LOAD_BALANCING_THREADS_COUNT,
							MAX_LOAD_BALANCING_THREADS_COUNT,
							LOAD_BALANCING_PLS_COUNT_THRESHOLD
						);
#else // __CEE_LOAD_BALANCING__
						fprintf(
							stdout, 
							HELP_STRING, 
							p->argv[0]
						);
#endif // __CEE_LOAD_BALANCING__
						p->f_help = 1;
						goto parser_done;
						break;

					//---------------------------------------------------------
					// [-I <integer>] option.
					//---------------------------------------------------------
					case I_ID:
					case INTERVAL_ID:
						if(i + 1 >= p->argc) {
							PARSER_ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						value = atoi(p->argv[++i]);
						if(value < 1) {
							PARSER_ERROR_INDEX(
								"Bad argument value [%s] in position [%d].", 
								p->argv[i], 
								j
							);
						} else {
							p->sampling_interval = value;
						}
						goto parser_skip;
						break;

					//---------------------------------------------------------
					// [-S <integer>] option.
					//---------------------------------------------------------
					case S_ID:
					case SAMPLES_ID:
						if(i + 1 >= p->argc) {
							PARSER_ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						value = atoi(p->argv[++i]);
						if(value < 1) {
							PARSER_ERROR_INDEX(
								"Bad argument value [%s] in position [%d].", 
								p->argv[i], 
								j
							);
						} else {
							p->samples = value;
						}
						goto parser_skip;
						break;

					//---------------------------------------------------------
					// [-W <integer>] option.
					//---------------------------------------------------------
					case W_ID:
					case WORK_ID:
						if(i + 1 >= p->argc) {
							PARSER_ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						value = atoi(p->argv[++i]);
						if(value < 0) {
							PARSER_ERROR_INDEX(
								"Bad argument value [%s] in position [%d].", 
								p->argv[i], 
								j
							);
						} else {
							p->work_index = (unsigned int)value;
						}
						goto parser_skip;
						break;

					//---------------------------------------------------------
					// [-A <string>] option.
					//---------------------------------------------------------
					case A_ID:
					case APPLICATION_ID:
						if(i + 1 >= p->argc) {
							PARSER_ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						i++;
						memset(
							p->application_name, 
							0, 
							sizeof(p->application_name)
						);
#ifdef __PL_WINDOWS__
						mbstowcs_s(
							&st_ret, 
							p->application_name, 
							strlen(p->argv[i]) + 1, 
							p->argv[i], 
							_TRUNCATE
						);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
						strncpy(
							p->application_name, 
							p->argv[i], 
							strlen(p->argv[i])
						);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
						goto parser_skip;
						break;

#ifdef __CEE_ESRV_ON_EACH_NODE__
					//---------------------------------------------------------
					// [-E] option.
					//---------------------------------------------------------
					case E_ID:
					case ESRV_ON_NODES_ID:
						p->f_esrv_on_each_node = 1;
						goto parser_skip;
						break;
#endif // __CEE_ESRV_ON_EACH_NODE__

#ifdef __CEE_LOAD_BALANCING__

					//---------------------------------------------------------
					// [-L [integer]] option.
					//---------------------------------------------------------
					case L_ID:
					case LOAD_BALANCING_ID:
						if(i + 1 < p->argc) {
							value = atoi(p->argv[++i]);
							if(
								(value < MIN_LOAD_BALANCING_THREADS_COUNT) || 
								(MAX_LOAD_BALANCING_THREADS_COUNT < value)
							) {
								PARSER_ERROR_INDEX(
									"Bad argument value [%s] in position [%d].", 
									p->argv[i], 
									j
								);
							} else {
								p->threads_count = value;
							}						
						}
						p->f_load_balancing = 1;
						goto parser_skip;
						break;
#endif // __CEE_LOAD_BALANCING__

					//---------------------------------------------------------
					// [-O <string>] option.
					//---------------------------------------------------------
					case O_ID:
					case OUTPUT_ID:
						if(i + 1 >= p->argc) {
							PARSER_ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						i++;
						p->output_file = fopen(p->argv[i], "w");
						if(p->output_file == NULL) {
							WARNING("Unable to create the output file, will use stdout instead.");
							p->f_output_file = 0;
							p->output_file_name = NULL;
							p->output_file = stdout;
						} else {
							p->f_output_file = 1;
							p->output_file_name = p->argv[i];
						}
						goto parser_skip;
						break;

					//---------------------------------------------------------
					// Unknown option.
					//---------------------------------------------------------
					default:
						PARSER_ERROR_INDEX(
							"Unable to make sense of token [%s] in position [%d].", 
							buffer, 
							j
						);
				}
			}
		} // for j
		PARSER_ERROR("Unable to make sense of options.  Use --help option for help.");
		goto parser_error;
parser_skip:
		;
	} // for i
parser_done:

	//-------------------------------------------------------------------------
	// Return status.
	//-------------------------------------------------------------------------
	return(PL_SUCCESS);
parser_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: signal_handler
Purpose : analyzer interrupt signal handler
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
BOOL signal_handler(DWORD c) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
void signal_handler(int c) { 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifndef __CEE_LOAD_BALANCING__
	unsigned int i = 0;
	char buffer[PL_MAX_PATH] = { '\0' };
#endif // __CEE_LOAD_BALANCING__
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
	PL_STATUS ret = PL_FAILURE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	int ret = -1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	switch(c) {

		//---------------------------------------------------------------------
		// Interrupt program.
		// Note:
		//    To offer accurate data, we perform a last data collection since
		//    the sampling interval may be long and if the user interrupts the
		//    program sometime in the middle, then valuable data could be 
		//    ignored.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		case CTRL_C_EVENT: 
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		case SIGINT:
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef __CEE_LOAD_BALANCING__

			//-----------------------------------------------------------------
			// Begin load-balancing threads' data collection.
			//-----------------------------------------------------------------
			ret = signal_load_balancing_threads_to_sample(&control_data);
			if(ret != PL_SUCCESS) {
				SIGNAL_HANDLER_ERROR("Unable to initiate load-balancing threads' sammpling.");
			}

			//-----------------------------------------------------------------
			// Wait - for the last time - for load balancing threads' data 
			// collection end.
			//-----------------------------------------------------------------
			ret = wait_for_load_balancing_threads_end_of_sample(&control_data);
			if(ret != PL_SUCCESS) {
				SIGNAL_HANDLER_ERROR("Unable to detect load-balancing threads' end of sampling.");
			}
#else // __CEE_LOAD_BALANCING__

			//-----------------------------------------------------------------
			// Read work counters.
			//-----------------------------------------------------------------
			for(i = 0; i < control_data.work_pls_count; i++) {
				ret = pl_read(
					control_data.work_plds[i], 
					&control_data.work_data[i], 
					control_data.work_index
				);
				if(ret != PL_SUCCESS) {
					WARNING_INDEX(
						"Unable to read application PL [%d] work counter." , 
						i
					);
				}
			}

			//-----------------------------------------------------------------
			// Read the energy counters.
			//-----------------------------------------------------------------
#ifdef __CEE_ESRV_ON_EACH_NODE__
			for(i = 0; i < control_data.esrv_pls_count; i++) {
				ret = pl_read(
					control_data.esrv_plds[i], 
					&control_data.esrv_status[i], 
					ESRV_COUNTER_STATUS_INDEX
				);
				if(ret != PL_SUCCESS) {
					SIGNAL_HANDLER_ERROR_INDEX(
						"Unable to read the ESRV instance's status counter (ESRV_COUNTER_STATUS_INDEX).", 
						i
					);
				}
				if(control_data.esrv_status[i] == ESRV_STATUS_RUNNING) { 
					ret = pl_read(
						control_data.esrv_plds[i], 
						&control_data.energy_data[i], 
						ESRV_COUNTER_ENERGY_JOULES_INDEX
					);
					if(ret != PL_SUCCESS) {
						WARNING_INDEX(
							"Unable to read ESRV PL [%d] energy counter." , 
							i
						);
					}
				} else {
					SIGNAL_HANDLER_ERROR_INDEX(
						"The ESRV on the aggregation node doesn't seem to be alive anymore.", 
						i
					);
				}
			}
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
			ret = pl_read(
				control_data.esrv_pld, 
				&control_data.esrv_status, 
				ESRV_COUNTER_STATUS_INDEX
			);
			if(ret != PL_SUCCESS) {
				SIGNAL_HANDLER_ERROR_INDEX(
					"Unable to read the ESRV instance's status counter (ESRV_COUNTER_STATUS_INDEX).", 
					i
				);
			}
			if(control_data.esrv_status == ESRV_STATUS_RUNNING) { 
				ret = pl_read(
					control_data.esrv_pld, 
					&control_data.energy_data, 
					ESRV_COUNTER_ENERGY_JOULES_INDEX
				);
				if(ret != PL_SUCCESS) {
					WARNING("Unable to read the ESRV PL energy counter.");
				}
			} else {
				SIGNAL_HANDLER_ERROR_INDEX(
					"The ESRV on the aggregation node doesn't seem to be alive anymore.", 
					i
				);
			}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#endif // __CEE_LOAD_BALANCING__

			//-----------------------------------------------------------------
			// Set exit condition.
			//-----------------------------------------------------------------
			control_data.command = EXIT;
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
			fprintf(control_data.output_file, "\n");
			fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef __CEE_LOAD_BALANCING__

				//-------------------------------------------------------------
				// Begin - for the last time - load-balancing threads' data 
			    // collection.
				// Note:
				//    We do not wait load balancing threads' data collection 
				//    end since the end command is set and each load-balancing
				//    thread will exit gracefully and terminate.
				//-------------------------------------------------------------
				ret = signal_load_balancing_threads_to_sample(&control_data);
				if(ret != PL_SUCCESS) {
					SIGNAL_HANDLER_ERROR("Unable to initiate load-balancing threads' sammpling.");
				}
#endif // __CEE_LOAD_BALANCING__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
			break;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS__
			return(TRUE);

		default: 
			return(FALSE); 
#endif // __PL_WINDOWS__

	} 
}

#ifdef __CEE_LIVE_MONITORING__
/*-----------------------------------------------------------------------------
Function: write_static_counters
Purpose : write static cee counters
In      : pointer to control data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int write_static_counters(PCONTROL_DATA p) {

	PL_STATUS ret = PL_FAILURE;
	unsigned long long value = 0;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Write static counters.
	//-------------------------------------------------------------------------
	value = (unsigned long long)p->work_pls_count;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		NODES_AGGREGATED_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [NODES_AGGREGATED].");
	}
	value = (unsigned long long)p->sampling_interval;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		SAMPLING_INTERVAL_SECONDS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [SAMPLING_INTERVAL_SECONDS].");
	}
	value = DEFAULT_ACCUMULATED_ENERGY_JOULES_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		ACCUMULATED_ENERGY_JOULES_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [ACCUMULATED_ENERGY_JOULES_DECIMALS].");
	}
	value = DEFAULT_ACCUMULATED_ENERGY_KWHS_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		ACCUMULATED_ENERGY_KWHS_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [ACCUMULATED_ENERGY_KWHS_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_WORK_UNIT_PER_NODE_WU_NODE_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_NODE_WU_NODE_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_WORK_UNIT_PER_NODE_WU_NODE_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_ENERGY_PER_NODE_JOULE_NODE_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_NODE_JOULE_NODE_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_ENERGY_PER_NODE_JOULE_NODE_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_ENERGY_PER_NODE_KWH_NODE_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_NODE_KWH_NODE_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_ENERGY_PER_NODE_KWH_NODE_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE_DECIMALS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE_DECIMALS].");
	}
	value = DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU_NODE_DECIMALS;
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU_NODE_DECIMALS
	);
	if(ret != PL_SUCCESS) {
		WRITE_STATIC_COUNTERS_ERROR("Unable write static counter [AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU_NODE].");
	}

	return(PL_SUCCESS);
write_static_counters_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: write_counters
Purpose : write cee counters
In      : pointer to control data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int write_counters(PCONTROL_DATA p) {

	PL_STATUS ret = PL_FAILURE;
	unsigned long long value = 0;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Write counters' values into cee's PL.
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->cee_pld,
		&p->samples_collected, 
		SAMPLES_COLLECTED_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [SAMPLES_COLLECTED].");
	}
	ret = pl_write(
		p->cee_pld, 
		&p->accumulated_work_data, 
		ACCUMULATED_WORK_UNITS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [ACCUMULATED_WORK_UNITS].");
	}
	value = (unsigned long long)(p->accumulated_enery_in_joules * p->accumulated_energy_joules_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		ACCUMULATED_ENERGY_JOULES_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [ACCUMULATED_ENERGY_JOULES].");
	}
	value = (unsigned long long)(p->accumulated_enery_in_kwh * p->accumulated_energy_kwhs_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		ACCUMULATED_ENERGY_KWHS_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [ACCUMULATED_ENERGY_KWHS].");
	}

	//-------------------------------------------------------------------------
	// Averages all nodes.
	//-------------------------------------------------------------------------
	value = (unsigned long long)(p->average_energy_in_joule_per_work_unit * p->average_energy_per_work_unit_wu_joule_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE].");
	}
	value = (unsigned long long)(p->average_energy_in_kwh_per_work_unit * p->average_energy_per_work_unit_wu_kwh_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH].");
	}
	value = (unsigned long long)(p->average_work_unit_per_energy_in_joule * p->average_work_unit_per_energy_joule_wu_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU].");
	}
	value = (unsigned long long)(p->average_work_unit_per_energy_in_kwh * p->average_work_unit_per_energy_kwh_wu_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU].");
	}

	//-------------------------------------------------------------------------
	// Averages per nodes.
	//-------------------------------------------------------------------------
	value = (unsigned long long)(p->average_work_unit_per_node * p->average_work_unit_per_node_wu_node_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_NODE_WU_NODE_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_WORK_UNIT_PER_NODE_WU_NODE].");
	}
	value = (unsigned long long)(p->average_energy_in_joule_per_node * p->average_energy_per_node_joule_node_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_NODE_JOULE_NODE_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_ENERGY_PER_NODE_JOULE_NODE].");
	}
	value = (unsigned long long)(p->average_energy_in_kwh_per_node * p->average_energy_per_node_kwh_node_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_NODE_KWH_NODE_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_ENERGY_PER_NODE_KWH_NODE].");
	}

	value = (unsigned long long)(p->average_energy_in_joule_per_work_unit_per_node * p->average_energy_per_work_unit_per_node_wu_joule_node_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE].");
	}
	value = (unsigned long long)(p->average_energy_in_kwh_per_work_unit_per_node * p->average_energy_per_work_unit_per_node_wu_kwh_node_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE].");
	}
	value = (unsigned long long)(p->average_work_unit_per_energy_in_joule_per_node * p->average_work_unit_per_energy_per_node_joule_wu_node_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE_INDEX
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE].");
	}
	value = (unsigned long long)(p->average_work_unit_per_energy_in_kwh_per_node * p->average_work_unit_per_energy_per_node_kwh_wu_node_multiplier);
	ret = pl_write(
		p->cee_pld, 
		&value, 
		AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU_NODE
	);
	if(ret != PL_SUCCESS) {
		WRITE_COUNTERS_ERROR("Unable write counter [AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU].");
	}

	return(PL_SUCCESS);
write_counters_error:
	return(PL_FAILURE);
}
#endif // __CEE_LIVE_MONITORING__

#ifdef __CEE_LOAD_BALANCING__
/*-----------------------------------------------------------------------------
Function: signal_load_balancing_threads_to_sample
Purpose : signal sampling time to load-balancing threads
In      : pointer to control data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int signal_load_balancing_threads_to_sample(PCONTROL_DATA p) {

	unsigned int i = 0;
	char buffer[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int ret = -1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(p != NULL);

	//---------------------------------------------------------------------
	// Begin load-balancing threads' data collection.
	// Note:
	//    When load balancing is activated, the load balancing threads 
	//    collects work and enegy data.  The energy data is collected 
	//    by the load balancing threads only if __CEE_ESRV_ON_EACH_NODE__
	//    is defined.
	//---------------------------------------------------------------------
	for(i = 0; i < p->threads_count; i++) {
#ifdef __PL_WINDOWS__
		bret = SetEvent(p->h_sample[i]);
		if(bret == FALSE) {
			SIGNAL_LOAD_BALANCING_THREAD_ERROR_INDEX(
				"Unable to signal load-balancing thread [%d].", 
				i
			);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		ret = sem_post(&p->h_sample[i]);
#else // __PL_MACOSX__
		ret = sem_post(p->h_sample[i]);
#endif // __PL_MACOSX__
		if(ret == -1) {
			SIGNAL_LOAD_BALANCING_THREAD_ERROR_INDEX(
				"Unable to signal load-balancing thread [%d].", 
				i
			);
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	} // for i

	return(PL_SUCCESS);
signal_load_balancing_threads_to_sample_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: wait_for_load_balancing_threads_end_of_sample
Purpose : wait until all load-balancing threads finished a sampling
In      : pointer to control data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int wait_for_load_balancing_threads_end_of_sample(PCONTROL_DATA p) {

	unsigned int i = 0;
	char buffer[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
	DWORD dwret = -1;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int ret = -1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(p != NULL);

	//---------------------------------------------------------------------
	// Wait load balancing threads' data collection end.
	//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	dwret = WaitForMultipleObjects(
		p->threads_count, 
		p->h_sample_done, 
		TRUE, 
		INFINITE
	);
	if(dwret == WAIT_FAILED) {
		WAIT_LOAD_BALANCING_THREAD_ERROR("Unable to wait for load-balancing thread's sampling cycle to end.");
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	for(i = 0; i < p->threads_count; i++) {
#ifndef __PL_MACOSX__
		ret = sem_wait(&p->h_sample_done[i]);
#else // __PL_MACOSX__
		ret = sem_wait(p->h_sample_done[i]);
#endif // __PL_MACOSX__
		if(ret == -1) {
			WAIT_LOAD_BALANCING_THREAD_ERROR_INDEX(
				"Unable to wait for load-balancing thread [%d]'s sampling cycle to end.", 
				i
			);
		}
	} // for i
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	return(PL_SUCCESS);
wait_for_load_balancing_threads_end_of_sample_error:
	return(PL_FAILURE);
}
#endif // __CEE_LOAD_BALANCING__

/*-----------------------------------------------------------------------------
Function: display_startup_message
Purpose : print startup message to stdout
In      : pointer to control data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int display_startup_message(PCONTROL_DATA p) {

	int i = 0;
	static char *banner[BANNER_LINES_COUNT] = { BANNER_LINES };
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Display startup banner.
	//-------------------------------------------------------------------------
	fprintf(p->output_file, "\n");
	fprintf(p->output_file, "-------------------------------------------------------------------------------\n");
	for(i = 0; i < BANNER_LINES_COUNT; i++) {
		fprintf(stdout, "%s", banner[i]);
	}
	fprintf(stdout, "-------------------------------------------------------------------------------\n");
	fprintf(stdout, "%s: version %s.%s.%s\n", CEE_APPLICATION_NAME, CEE_VERSION_MAJOR, CEE_VERSION_MINOR, CEE_VERSION_REVISION);
	fprintf(stdout, "Using PL helper version %s.%s.%s\n", PL_HELPER_VERSION_MAJOR, PL_HELPER_VERSION_MINOR, PL_HELPER_VERSION_REVISION);
	fprintf(stdout, "Using PL version %s.%s.%s(%s)", PL_VERSION_MAJOR, PL_VERSION_MINOR, PL_VERSION_REVISION, PL_VERSION_OS);
	fprintf(stdout, "\n");
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: display_configuration_message
Purpose : print configuration data to stdout
In      : pointer to control data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int display_configuration_message(PCONTROL_DATA p) {

	assert(p != NULL);

	//-----------------------------------------------------------------------------
	// Report directions on how to stop sampling.
	//-----------------------------------------------------------------------------
	fprintf(stdout, "-------------------------------------------------------------------------------\n");
	fprintf(stdout, "Sampling cluster energy efficiency data.\n");
	fprintf(stdout, "Type <CTRL>+<C> to stop sampling and print statistics.\n");
	fprintf(stdout, "-------------------------------------------------------------------------------\n");

	//-----------------------------------------------------------------------------
	// Report build flags.
	//-----------------------------------------------------------------------------


	fprintf(stdout, "Binary built with the following symbol(s) defined:\n");
#ifdef __PL_WINDOWS__
	fprintf(stdout, "   __PL_WINDOWS__.\n");
#endif // __PL_WINDOWS__
#ifdef __PL_LINUX__
	fprintf(stdout, "   __PL_LINUX__.\n");
#endif // __PL_LINUX__
#ifdef __PL_SOLARIS__
	fprintf(stdout, "   __PL_SOLARIS__.\n");
#endif // __PL_SOLARIS__
#ifdef __PL_MACOSX__
	fprintf(stdout, "   __PL_MACOSX__.\n");
#endif // __PL_MACOSX__
#ifdef __CEE_ESRV_ON_EACH_NODE__
	fprintf(stdout, "   __CEE_ESRV_ON_EACH_NODE__.\n");
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	fprintf(stdout, "   __CEE_ESRV_ON_AGGREGATION_NODE__.\n");
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#ifdef __CEE_LOAD_BALANCING__
	fprintf(stdout, "   __CEE_LOAD_BALANCING__.\n");
#endif // __CEE_LOAD_BALANCING__
#ifdef __CEE_LIVE_MONITORING__
	fprintf(stdout, "   __CEE_LIVE_MONITORING__.\n");
#endif // __CEE_LIVE_MONITORING__
#ifdef __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__
	fprintf(stdout, "   __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__.\n");
#endif // __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__
	fprintf(stdout, "-------------------------------------------------------------------------------\n");

	//-------------------------------------------------------------------------
	// Report some stats.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	_ftprintf(p->output_file, _T("Application:                                                     [%s]\n"), p->application_name);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	fprintf(stdout, "Application:                                                     [%s]\n", p->application_name);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	fprintf(stdout, "Node(s):                                                         [%d]\n", p->work_pls_count);
	fprintf(stdout, "ESRV(s):                                                         [%d]\n", p->esrv_pls_count);
#ifdef __CEE_LOAD_BALANCING__
	fprintf(stdout, "Thread(s):                                                       [%d]\n", p->threads_count);
#endif // __CEE_LOAD_BALANCING__
	fprintf(stdout, "-------------------------------------------------------------------------------\n");
#ifdef __CEE_ESRV_ON_EACH_NODE__
	if(p->f_esrv_on_each_node == 1) {
		fprintf(stdout, "One ESRV per node:                                               [Yes]\n");
	} else {
		fprintf(stdout, "One ESRV per node:                                               [No]\n");
	}
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	if(p->f_esrv_on_aggregation_node == 1) {
		fprintf(stdout, "ESRV on aggregation node only:                                   [Yes]\n");
	} else {
		fprintf(stdout, "ESRV on aggregation node only:                                   [No]\n");
	}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#ifdef __CEE_LOAD_BALANCING__
	if(p->f_load_balancing == 1) {
		fprintf(stdout, "Load-balancing requested:                                        [Yes]\n");
	} else {
		fprintf(stdout, "Load-balancing requested:                                        [No]\n");
	}
#endif // __CEE_LOAD_BALANCING__
	fprintf(stdout, "-------------------------------------------------------------------------------\n");

	//-------------------------------------------------------------------------
	// Report same data in output file if requested.
	//-------------------------------------------------------------------------
	if(p->f_output_file == 1) {
		fprintf(p->output_file, "Binary build with the following symbol(s) defined:\n");
#ifdef __PL_WINDOWS__
		fprintf(p->output_file, "   __PL_WINDOWS__.\n");
#endif // __PL_WINDOWS__
#ifdef __PL_LINUX__
		fprintf(p->output_file, "   __PL_LINUX__.\n");
#endif // __PL_LINUX__
#ifdef __PL_SOLARIS__
		fprintf(p->output_file, "   __PL_SOLARIS__.\n");
#endif // __PL_SOLARIS__
#ifdef __PL_MACOSX__
		fprintf(p->output_file, "   __PL_MACOSX__.\n");
#endif // __PL_MACOSX__
#ifdef __CEE_ESRV_ON_EACH_NODE__
		fprintf(p->output_file, "   __CEE_ESRV_ON_EACH_NODE__.\n");
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
		fprintf(p->output_file, "   __CEE_ESRV_ON_AGGREGATION_NODE__.\n");
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#ifdef __CEE_LOAD_BALANCING__
		fprintf(p->output_file, "   __CEE_LOAD_BALANCING__.\n");
#endif // __CEE_LOAD_BALANCING__
#ifdef __CEE_LIVE_MONITORING__
		fprintf(p->output_file, "   __CEE_LIVE_MONITORING__.\n");
#endif // __CEE_LIVE_MONITORING__
#ifdef __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__
		fprintf(p->output_file, "   __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__.\n");
#endif // __CEE_FAVOR_TIMER_PRECISION_OVER_POWER_DRAW__
		fprintf(p->output_file, "-------------------------------------------------------------------------------\n");

		//-------------------------------------------------------------------------
		// Report some stats.
		//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		_ftprintf(p->output_file, _T("Application:                                                     [%s]\n"), p->application_name);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		fprintf(p->output_file, "Application:                                                     [%s]\n", p->application_name);
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		fprintf(p->output_file, "Node(s):                                                         [%d]\n", p->work_pls_count);
		fprintf(p->output_file, "ESRV(s):                                                         [%d]\n", p->esrv_pls_count);
#ifdef __CEE_LOAD_BALANCING__
		fprintf(p->output_file, "Thread(s):                                                       [%d]\n", p->threads_count);
#endif // __CEE_LOAD_BALANCING__
		fprintf(p->output_file, "-------------------------------------------------------------------------------\n");
#ifdef __CEE_ESRV_ON_EACH_NODE__
		if(p->f_esrv_on_each_node == 1) {
			fprintf(p->output_file, "One ESRV per node:                                               [Yes]\n");
		} else {
			fprintf(p->output_file, "One ESRV per node:                                               [No]\n");
		}
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
		if(p->f_esrv_on_aggregation_node == 1) {
			fprintf(p->output_file, "ESRV on aggregation node only:                                   [Yes]\n");
		} else {
			fprintf(p->output_file, "ESRV on aggregation node only:                                   [No]\n");
		}
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#ifdef __CEE_LOAD_BALANCING__
		if(p->f_load_balancing == 1) {
			fprintf(p->output_file, "Load-balancing requested:                                        [Yes]\n");
		} else {
			fprintf(p->output_file, "Load-balancing requested:                                        [No]\n");
		}
#endif // __CEE_LOAD_BALANCING__
		fprintf(p->output_file, "-------------------------------------------------------------------------------\n");
	}

	return(PL_SUCCESS);
}
