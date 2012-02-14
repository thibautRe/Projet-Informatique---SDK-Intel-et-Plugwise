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

#ifndef __INCLUDE_CEE__
#define __INCLUDE_CEE__

//-----------------------------------------------------------------------------
// Headers inclusions.
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#include <tchar.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include <errno.h>
	#include <string.h>
	#include <unistd.h>
	#include <uuid/uuid.h>
	#include <semaphore.h>
	#include <sched.h>
	#include <sys/time.h>
	#include <pthread.h>
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// version defines
//-----------------------------------------------------------------------------
#define CEE_APPLICATION_NAME "Cluster Energy Efficiency"
#define CEE_VERSION_MAJOR "2010" // year
#define CEE_VERSION_MINOR "01" // month
#define CEE_VERSION_REVISION "30" // day

//-----------------------------------------------------------------------------
// Constants.
//-----------------------------------------------------------------------------
#define DEFAULT_ALLOWED_TIME_MARGIN_IN_MS 10 // 10ms out of 1s is 1% error
#ifdef __PL_WINDOWS__
	#define DEFAULT_THREADS_BOOST_PRIORITY THREAD_PRIORITY_TIME_CRITICAL
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define DEFAULT_THREADS_BOOST_PRIORITY 1
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#define NO_SAMPLING_LIMIT -1
#define JOULES_IN_A_KWH 3600000.0
#define DEFAULT_SAMPLING_INTERVAL_IN_SECONDS 1
#define DEFAULT_WORK_INDEX 0
#ifdef __PL_WINDOWS__
	#define PLS_FOLDER PL_INI_WINDOWS_FOLDER
	#define PLS_FOLDER_PATH_SEPARATOR PL_INI_WINDOWS_PATH_SEPARATOR
	#define ESRV_NAME _T("esrv")
	#define DEFAULT_APPLICATION_NAME PL_ANONYMOUS_APPLICATION_NAME
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PLS_FOLDER PL_INI_NIX_FOLDER
	#define PLS_FOLDER_PATH_SEPARATOR PL_INI_NIX_PATH_SEPARATOR
	#define ESRV_NAME "esrv"
	#define DEFAULT_APPLICATION_NAME PL_ANONYMOUS_APPLICATION_NAME
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __CEE_LOAD_BALANCING__
	#if defined (_DEBUG) || (__PLDEBUG__)
		#define DEFAULT_LOAD_BALANCING_THREADS_COUNT 2
		#define MIN_LOAD_BALANCING_THREADS_COUNT 2
		#define MAX_LOAD_BALANCING_THREADS_COUNT 128
		#define LOAD_BALANCING_PLS_COUNT_THRESHOLD 1
		#define LOAD_BALANCING_MIN_PLS_COUNT 1
		#define LOAD_BALANCING_MAX_PLS_COUNT 128
	#else // _DEBUG || __PLDEBUG__
		#define DEFAULT_LOAD_BALANCING_THREADS_COUNT 16
		#define MIN_LOAD_BALANCING_THREADS_COUNT 2
		#define MAX_LOAD_BALANCING_THREADS_COUNT 128
		#define LOAD_BALANCING_PLS_COUNT_THRESHOLD 32
		#define LOAD_BALANCING_MIN_PLS_COUNT \
			(LOAD_BALANCING_PLS_COUNT_THRESHOLD / \
			DEFAULT_LOAD_BALANCING_THREADS_COUNT)
		#define LOAD_BALANCING_MAX_PLS_COUNT 256
	#endif // _DEBUG || __PLDEBUG__
	#ifdef __PL_MACOSX__
		#define SAMPLE_SEMAPHORE_BASE_NAME "SMPL"
		#define SAMPLE_DONE_SEMAPHORE_BASE_NAME "SMPLE"
	#endif // __PL_MACOSX__
	#define HELP_STRING \
"\n \
%s start a cluster energy efficiency sampling.\n\n \
[--pause <integer>]:\n \
   Set the sampling interval in second(s). 1 by default.\n \
[--work_counter_index <integer>]:\n \
   Set the work counter index. 0 by default.\n \
[--application_name <string>]:\n \
	Set the application's name to <string>.\n \
	It is set to \"anonymous_application\" by default.\n \
[--esrv_on_each_node]:\n \
   Specify that ESRV runs on each node.\n \
   By default it is assumed to run on the aggregation node.\n \
[--load_balancing [integer]]:\n \
   Activate the load balancer.\n \
   Optional [integer] sets the thread count. %d by default,\n \
   %d at minimum and %d at maximum.\n \
[--samples <integer>]:\n \
   End analysis after <integer> samples were collected.\n \
   Sampling ends by default when interrupted by user (<CTRL>+<C>).\n \
[--help]:\n \
   Print this help message.\n\n \
This utility assumes the following:\n \
  - Each cluster node runs the same application.\n \
  - Each application PL is aggregated in one node.\n \
  - Application accumulates work and exposes it in\n \
    a single counter without suffix.\n \
  - This utility is run on the aggregated node.\n \
  - ESRV can either run on each node or on the aggregation node.\n\n \
  - Only channel 1 of ESRV is taken in account.\n\n \
Notes:\n \
  - Load balancing is activated only if there are more than %d nodes.\n \
  - If application name has spaces, use double-quotes (\") around it.\n \
  - Several behaviors are set at compilation by:\n \
      __CEE_ESRV_ON_EACH_NODE__\n \
      __CEE_ESRV_ON_AGGREGATION_NODE__\n \
      __CEE_LOAD_BALANCING__\n \
      __CEE_LIVE_MONITORING__\n \
\n"
#else // __CEE_LOAD_BALANCING__
	#define HELP_STRING \
"\n \
%s start a cluster energy efficiency sampling.\n\n \
[--pause <integer>]:\n \
   Set the sampling interval in second(s). 1 by default.\n \
[--work_counter_index <integer>]:\n \
   Set the work counter index. 0 by default.\n \
[--application_name <string>]:\n \
	Set the application's name to <string>.\n \
	It is set to \"anonymous_application\" by default.\n \
[--esrv_on_each_node]:\n \
   Specify that ESRV runs on each node.\n \
   By default it is assumed to run on the aggregation node.\n \
[--samples <integer>]:\n \
   End analszis after <integer> samples were collected.\n \
   Sampling ends by default when interrupted by user (<CTRL>+<C>).\n \
[--help]:\n \
   Print this help message.\n\n \
This utility assumes the following:\n \
  - Each cluster node runs the same application.\n \
  - Each application PL is aggregated in one node.\n \
  - Application accumulates work and exposes it in\n \
    a single counter without suffix.\n \
  - This utility is run on the aggregated node.\n \
  - ESRV can either run on each node or on the aggregation node.\n\n \
  - Only channel 1 of ESRV is taken in account.\n\n \
Notes:\n \
  - If application name has spaces, use double-quotes (\") around it.\n \
  - Several behaviors are set at compilation by:\n \
      __CEE_ESRV_ON_EACH_NODE__\n \
      __CEE_ESRV_ON_AGGREGATION_NODE__\n \
      __CEE_LIVE_MONITORING__\n \
\n"
#endif // __CEE_LOAD_BALANCING__

#define BANNER_LINES_COUNT 7
#define BANNER_LINES \
	" @@@@  @@@@@@ @@@@@@\n", \
	"@    @ @      @\n", \
	"@      @      @\n", \
	"@      @@@@@@ @@@@@@\n", \
	"@      @      @\n", \
	"@    @ @      @\n", \
	" @@@@  @@@@@@ @@@@@@\n"

#define OPTION_STRINGS_COUNT 16
#define OPTION_STRINGS \
	"-H", \
	"-P", \
	"-W", \
	"-A", \
	"-E", \
	"-L", \
	"-S", \
	"-O", \
	"--HELP", \
	"--PAUSE", \
	"--WORK_COUNTER_INDEX", \
	"--APPLICATION_NAME", \
	"--ESRV_ON_EACH_NODE", \
	"--LOAD_BALANCING", \
	"--SAMPLES", \
	"--OUTPUT" \

#ifdef __CEE_LIVE_MONITORING__

	#define DEFAULT_HIGH_PRECISION 6
	#define DEFAULT_PRECISION 4
	#define DEFAULT_LOW_PRECISION 2 

	#define DEFAULT_ACCUMULATED_ENERGY_JOULES_DECIMALS DEFAULT_LOW_PRECISION
	#define DEFAULT_ACCUMULATED_ENERGY_KWHS_DECIMALS DEFAULT_PRECISION
	#define DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE_DECIMALS DEFAULT_PRECISION
	#define DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH_DECIMALS DEFAULT_HIGH_PRECISION
	#define DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU_DECIMALS DEFAULT_PRECISION
	#define DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU_DECIMALS DEFAULT_PRECISION
	#define DEFAULT_AVERAGE_WORK_UNIT_PER_NODE_WU_NODE_DECIMALS DEFAULT_LOW_PRECISION
	#define DEFAULT_AVERAGE_ENERGY_PER_NODE_JOULE_NODE_DECIMALS DEFAULT_LOW_PRECISION
	#define DEFAULT_AVERAGE_ENERGY_PER_NODE_KWH_NODE_DECIMALS DEFAULT_PRECISION
	#define DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE_DECIMALS DEFAULT_PRECISION
	#define DEFAULT_AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE_DECIMALS DEFAULT_HIGH_PRECISION
	#define DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE_DECIMALS DEFAULT_PRECISION
	#define DEFAULT_AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU_NODE_DECIMALS DEFAULT_PRECISION

	#define CEE_COUNTERS_STRINGS_COUNT 30
	#define CEE_COUNTERS_STRINGS \
		"Node(s) aggregated", \
		"Sampling interval (seconds)", \
		"Sample(s) collected", \
		"Accumulated work unit(s)", \
		"Accumulated energy (Joule)", \
		"Accumulated energy (Joule).decimals", \
		"Accumulated energy (kWh)", \
		"Accumulated energy (kWh).decimals", \
		"Average energy per work unit (Joule per wu)", \
		"Average energy per work unit (Joule per wu).decimals", \
		"Average energy per work unit (kWh per wu)", \
		"Average energy per work unit (kWh per wu).decimals", \
		"Average work unit(s) per energy (wu per Joule)", \
		"Average work unit(s) per energy (wu per Joule).decimals", \
		"Average work unit(s) per energy (kWh per wu)", \
		"Average work unit(s) per energy (kWh per wu).decimals", \
		"Average work unit(s) per node (wu per node)", \
		"Average work unit(s) per node (wu per node).decimals", \
		"Average energy per node (Joule per node)", \
		"Average energy per node (Joule per node).decimals", \
		"Average energy per node (kWh per node)", \
		"Average energy per node (kWh per node).decimals", \
		"Average energy per work unit per node (Joule per wu per node)", \
		"Average energy per work unit per node (Joule per wu per node).decimals", \
		"Average energy per work unit per node (kWh per wu per node)", \
		"Average energy per work unit per node (kWh per wu per node).decimals", \
		"Average work unit(s) per energy per node (wu per Joule per node)", \
		"Average work unit(s) per energy per node (wu per Joule per node).decimals", \
		"Average work unit(s) per energy per node (wu per kWh per node)", \
		"Average work unit(s) per energy per node (wu per kWh per node).decimals"
#endif // __CEE_LIVE_MONITORING__

//-----------------------------------------------------------------------------
// Enums and constants.
//-----------------------------------------------------------------------------
typedef enum _option_ids {

	H_ID = 0,
	I_ID,
	W_ID,
	A_ID,
	E_ID,
	L_ID,
	S_ID,
	O_ID,

	HELP_ID,
	INTERVAL_ID,
	WORK_ID,
	APPLICATION_ID,
	ESRV_ON_NODES_ID,
	LOAD_BALANCING_ID,
	SAMPLES_ID,
	OUTPUT_ID

} OPTION_IDS, *POPTION_IDS;
	
typedef enum _command {

	COLLECT_START_DATA = 0,
	COLLECT_DATA,
	EXIT

} COMMAND, *PCOMMAND;

#ifdef __CEE_LIVE_MONITORING__

	typedef enum _cee_counters_indexes {

		NODES_AGGREGATED_INDEX = 0,
		SAMPLING_INTERVAL_SECONDS_INDEX,
		SAMPLES_COLLECTED_INDEX,
		ACCUMULATED_WORK_UNITS_INDEX,
		ACCUMULATED_ENERGY_JOULES_INDEX,
		ACCUMULATED_ENERGY_JOULES_DECIMALS_INDEX,
		ACCUMULATED_ENERGY_KWHS_INDEX,
		ACCUMULATED_ENERGY_KWHS_DECIMALS_INDEX,
		AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE_INDEX,
		AVERAGE_ENERGY_PER_WORK_UNIT_WU_JOULE_DECIMALS_INDEX,
		AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH_INDEX,
		AVERAGE_ENERGY_PER_WORK_UNIT_WU_KWH_DECIMALS_INDEX,
		AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU_INDEX,
		AVERAGE_WORK_UNIT_PER_ENERGY_JOULE_WU_DECIMALS_INDEX,
		AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU_INDEX,
		AVERAGE_WORK_UNIT_PER_ENERGY_KWH_WU_DECIMALS_INDEX,
		AVERAGE_WORK_UNIT_PER_NODE_WU_NODE_INDEX,
		AVERAGE_WORK_UNIT_PER_NODE_WU_NODE_DECIMALS_INDEX,
		AVERAGE_ENERGY_PER_NODE_JOULE_NODE_INDEX,
		AVERAGE_ENERGY_PER_NODE_JOULE_NODE_DECIMALS_INDEX,
		AVERAGE_ENERGY_PER_NODE_KWH_NODE_INDEX,
		AVERAGE_ENERGY_PER_NODE_KWH_NODE_DECIMALS_INDEX,
		AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE_INDEX,
		AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_JOULE_NODE_DECIMALS_INDEX,
		AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE_INDEX,
		AVERAGE_ENERGY_PER_WORK_UNIT_PER_NODE_WU_KWH_NODE_DECIMALS_INDEX,
		AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE_INDEX,
		AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_JOULE_WU_NODE_DECIMALS_INDEX,
		AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU_NODE,
		AVERAGE_WORK_UNIT_PER_ENERGY_PER_NODE_KWH_WU_NODE_DECIMALS

	} CEE_COUNTERS_INDEXES, *PCEE_COUNTERS_INDEXES;
#endif // __CEE_LIVE_MONITORING__

typedef struct _control_data {

	//-------------------------------------------------------------------------
	// Sampling control flag -- sampling ends when set to EXIT.
	//-------------------------------------------------------------------------
	COMMAND command;

	//-------------------------------------------------------------------------
	// Sampling interval & count.
	//-------------------------------------------------------------------------
	int sampling_interval;
	int samples;

	//-------------------------------------------------------------------------
	// Application name and work index.
	//-------------------------------------------------------------------------
	unsigned int work_index;
#ifdef __PL_WINDOWS__
	TCHAR application_name[PL_MAX_PATH];
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	char application_name[PL_MAX_PATH];
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Parser data.
	//-------------------------------------------------------------------------
	int f_help;
	int argc;
	char **argv;

	//-------------------------------------------------------------------------
	// Functional data.
	//-------------------------------------------------------------------------
#ifdef __CEE_ESRV_ON_EACH_NODE__
	int f_esrv_on_each_node;
#endif // __CEE_ESRV_ON_EACH_NODE__
#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	int f_esrv_on_aggregation_node;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__
#ifdef __CEE_LOAD_BALANCING__
	int f_load_balancing;
#endif // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Work sampling data.
	//-------------------------------------------------------------------------
	unsigned int work_pls_count;
	int *work_plds;
	unsigned long long *work_data;
	unsigned long long *start_work_data;
#ifdef __CEE_LOAD_BALANCING__
	unsigned int *per_thread_work_plds_count;
	int **per_thread_work_plds;
#endif // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Energy sampling data.
	//-------------------------------------------------------------------------
	unsigned int dead_esrv_pls_count;

#ifdef __CEE_ESRV_ON_EACH_NODE__
	unsigned int esrv_pls_count;
	int *esrv_plds;
	unsigned long long *energy_data;
	unsigned long long *start_energy_data;
	double *energy_data_multipliers;
	unsigned long long *esrv_status;
	unsigned int *per_thread_esrv_plds_count;
	int **per_thread_esrv_plds;
#endif // __CEE_ESRV_ON_EACH_NODE__

#ifdef __CEE_ESRV_ON_AGGREGATION_NODE__
	unsigned int esrv_pls_count;
	int esrv_pld;
	unsigned long long start_energy_data;
	unsigned long long energy_data;
	double energy_data_multipliers;
	unsigned long long esrv_status;
#endif // __CEE_ESRV_ON_AGGREGATION_NODE__

	//-------------------------------------------------------------------------
	// Sampling count and statistics variables.
	//-------------------------------------------------------------------------
	unsigned long long samples_collected;
	double accumulated_enery_in_joules;
	double accumulated_enery_in_kwh;
	double average_work_unit_per_node;
	double average_energy_in_joule_per_node;
	double average_energy_in_kwh_per_node;
	double average_energy_in_joule_per_work_unit;
	double average_energy_in_kwh_per_work_unit;
	double average_work_unit_per_energy_in_joule;
	double average_work_unit_per_energy_in_kwh;
	double average_energy_in_joule_per_work_unit_per_node;
	double average_energy_in_kwh_per_work_unit_per_node;
	double average_work_unit_per_energy_in_joule_per_node;
	double average_work_unit_per_energy_in_kwh_per_node;
	unsigned long long accumulated_work_data;
	unsigned long long accumulated_work_all_nodes;
	unsigned long long accumulated_start_work_all_nodes;
#ifdef __CEE_ESRV_ON_EACH_NODE__
	double accumulated_energy_in_joule_all_nodes;
	double accumulated_start_energy_in_joule_all_nodes;
#endif // __CEE_ESRV_ON_EACH_NODE__
	double accumulated_energy_joules_multiplier;
	double accumulated_energy_kwhs_multiplier;
	double average_energy_per_work_unit_wu_joule_multiplier;
	double average_energy_per_work_unit_wu_kwh_multiplier;
	double average_work_unit_per_energy_joule_wu_multiplier;
	double average_work_unit_per_energy_kwh_wu_multiplier;
	double average_work_unit_per_node_wu_node_multiplier;
	double average_energy_per_node_joule_node_multiplier;
	double average_energy_per_node_kwh_node_multiplier;
	double average_energy_per_work_unit_per_node_wu_joule_node_multiplier;
	double average_energy_per_work_unit_per_node_wu_kwh_node_multiplier;
	double average_work_unit_per_energy_per_node_joule_wu_node_multiplier;
	double average_work_unit_per_energy_per_node_kwh_wu_node_multiplier;

#ifdef __CEE_LIVE_MONITORING__

	//-------------------------------------------------------------------------
	// cee's PL data.
	//-------------------------------------------------------------------------
	int cee_pld;
	uuid_t uuid;
#endif // __CEE_LIVE_MONITORING__

	//-------------------------------------------------------------------------
	// Load balancing data (system). 
	//-------------------------------------------------------------------------
#ifdef __CEE_LOAD_BALANCING__
	unsigned int threads_count;
#ifdef __PL_WINDOWS__
	HANDLE *h_sample;
	HANDLE *h_sample_done;
	HANDLE *h_load_balancing_threads;
	DWORD *load_balancing_threads_ids;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	sem_t *h_sample;  
	sem_t *h_sample_done;  
#else // __PL_MACOSX__
	// MacOS X doesn't have unnamed semaphores
	sem_t **h_sample;  
	sem_t **h_sample_done;  
	char **sample_sem_names;
	char **sample_done_sem_names;
#endif // __PL_MACOSX__
	pthread_t *h_load_balancing_threads;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // __CEE_LOAD_BALANCING__

	//-------------------------------------------------------------------------
	// Priority data (system).
	//-------------------------------------------------------------------------
	int boost_priority; 

	//-------------------------------------------------------------------------
	// Output data.
	//-------------------------------------------------------------------------
	int f_output_file;
	char *output_file_name;
	FILE *output_file;

} CONTROL_DATA, *PCONTROL_DATA;

//-----------------------------------------------------------------------------
// Macros.
// Note:
//    The INDEX version of the error macro is using a format string as first
//    argument and an integer index to specify the index for the error.
// Note:
//    To avoid under Windows* the redefinition of the ERROR macro, we prefix
//    it with an underscode character (_).
//-----------------------------------------------------------------------------
#define _ERROR(s) \
	fprintf(stderr, "Error: %s [%d]\n", s, __LINE__); \
	f_error = 1; \
	goto main_stop;

#define SIGNAL_HANDLER_ERROR(s) \
	fprintf(stderr, "Error: %s [%d]\n", s, __LINE__); \

#define SIGNAL_HANDLER_ERROR_INDEX(s, i) \
	sprintf(buffer, s, (i)); \
	fprintf(stderr, "Error: %s [%d]\n", s, __LINE__); \

#define ERROR_INDEX(s, i) \
	memset(buffer, 0, sizeof(buffer)); \
	sprintf(buffer, s, (i)); \
	f_error = 1; \
	fprintf(stderr, "Error: %s [%d]\n", buffer, __LINE__); \
	goto main_stop;

#define PARSER_ERROR(s) \
	fprintf(stderr, "Error: %s [%d]\n", s, __LINE__); \
	goto parser_error;

#define PARSER_ERROR_INDEX(s, t, i) \
	memset(buffer, 0, sizeof(buffer)); \
	sprintf(buffer, s, (t), (i)); \
	fprintf(stderr, "Error: %s [%d]\n", buffer, __LINE__); \
	goto parser_error;

#define WARNING(s) \
	fprintf(stderr, "Warning: %s [%d]\n", s, __LINE__);

#define WARNING_INDEX(s, i) \
	memset(buffer, 0, sizeof(buffer)); \
	sprintf(buffer, s, (i)); \
	fprintf(stderr, "Warning: %s [%d]\n", buffer, __LINE__);

#define SAMPLING_TIME_WARNING(s, x, t, l, a, p) \
	memset(buffer, 0, sizeof(buffer)); \
	sprintf(buffer, s, (x), (t), (l), (a), (p)); \
	fprintf(stderr, "Warning: %s [%d]\n", buffer, __LINE__);

#ifdef __CEE_LIVE_MONITORING__
	#define WRITE_STATIC_COUNTERS_ERROR(s) \
		fprintf(stderr, "Error: %s [%d]\n", s, __LINE__); \
		goto write_static_counters_error;
	#define WRITE_COUNTERS_ERROR(s) \
		fprintf(stderr, "Error: %s [%d]\n", s, __LINE__); \
		goto write_counters_error;
#endif // #ifdef __CEE_LIVE_MONITORING__

#ifdef __CEE_LOAD_BALANCING__
	#define LOAD_BALANCING_THREAD_ERROR(s) \
		fprintf(stderr, "Error: %s [%d]\n", s, __LINE__); \
		goto load_balancing_thread_error;

	#define LOAD_BALANCING_THREAD_ERROR_INDEX(s, i) \
		memset(buffer, 0, sizeof(buffer)); \
		sprintf(buffer, s, (i)); \
		fprintf(stderr, "Error: %s [%d]\n", buffer, __LINE__); \
		goto load_balancing_thread_error;

	#define SIGNAL_LOAD_BALANCING_THREAD_ERROR_INDEX(s, i) \
		memset(buffer, 0, sizeof(buffer)); \
		sprintf(buffer, s, (i)); \
		fprintf(stderr, "Error: %s [%d]\n", buffer, __LINE__); \
		goto signal_load_balancing_threads_to_sample_error;

	#define WAIT_LOAD_BALANCING_THREAD_ERROR(s) \
		fprintf(stderr, "Error: %s [%d]\n", buffer, __LINE__); \
		goto wait_for_load_balancing_threads_end_of_sample_error;

	#define WAIT_LOAD_BALANCING_THREAD_ERROR_INDEX(s, i) \
		memset(buffer, 0, sizeof(buffer)); \
		sprintf(buffer, s, (i)); \
		fprintf(stderr, "Error: %s [%d]\n", buffer, __LINE__); \
		goto wait_for_load_balancing_threads_end_of_sample_error;
#endif // __CEE_LOAD_BALANCING__

//-----------------------------------------------------------------------------
// Functions prototype.
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	extern BOOL signal_handler(DWORD);
	#ifdef __CEE_LOAD_BALANCING__
		extern LPTHREAD_START_ROUTINE load_balancing_thread(void *);
	#endif // __CEE_LOAD_BALANCING__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	extern void signal_handler(int); 
	#ifdef __CEE_LOAD_BALANCING__
		extern void *load_balancing_thread(void *);
	#endif // __CEE_LOAD_BALANCING__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __CEE_LOAD_BALANCING__
	extern int signal_load_balancing_threads_to_sample(PCONTROL_DATA);
	extern int wait_for_load_balancing_threads_end_of_sample(PCONTROL_DATA);
#endif // __CEE_LOAD_BALANCING__
#ifdef __CEE_LIVE_MONITORING__
	extern int write_static_counters(PCONTROL_DATA);
	extern int write_counters(PCONTROL_DATA);
#endif // __CEE_LIVE_MONITORING__
extern int compute_statistics(PCONTROL_DATA);
extern int display_statistics(PCONTROL_DATA);
extern int parser(PCONTROL_DATA);
extern int display_startup_message(PCONTROL_DATA);
extern int display_configuration_message(PCONTROL_DATA);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_CEE__
