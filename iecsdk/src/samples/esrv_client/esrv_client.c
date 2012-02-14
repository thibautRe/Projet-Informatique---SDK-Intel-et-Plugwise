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

#include <assert.h>
#include <stdio.h>
#include <math.h> // for pow
#ifdef __PL_WINDOWS__
	#include <windows.h>
	#include <tchar.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include <string.h> // for memset
	#include <unistd.h> // for sleep
	#include <uuid/uuid.h>
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"
#include "productivity_link_helper.h"
#include "pub_esrv_counters.h"
#include "esrv_client.h"

//-----------------------------------------------------------------------------
// program entry point.
// Note:
//   can be viewed with pl_gui_monitor using --process --gdiplus --format 
//   --transparency 15 --geometry "gauges=3x2" --top --title "ESRV Client Sample"  
//   use --geometry "gauges=3x2" if cumulative reporting is selected
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	return(ee_monitor(argc, argv));
}

//-----------------------------------------------------------------------------
// program entry point.
// Note:
//   this sample takes a single integer argument indicating a channel to use
//   if the ESRV used has more than one channel.  If no argument is provided,
//   then the first channel will be used.  If the ESRV doesn't have enough
//   channels, then the first channel will be used.
//-----------------------------------------------------------------------------
int ee_monitor(int argc, char *argv[]) {

	//--------------------------------------------------------------------------
	// data to manage the PLs
	//--------------------------------------------------------------------------
	uuid_t uuid;
	char application_name[] = EE_APPLICATION_NAME;
	const char *counters_names[COUNTERS_COUNT] = { EE_COUNTERS_NAMES };
	char esrv_pl_config_file [PL_MAX_PATH] = { '\0' };
	int ret = PL_FAILURE;
	int pl_esrv = PL_INVALID_DESCRIPTOR;
	int pld = PL_INVALID_DESCRIPTOR;

	//--------------------------------------------------------------------------
	// data to manage the attached ESRV
	//--------------------------------------------------------------------------
	int channel = -1;
	unsigned long long channels = 0;
	unsigned long long status = 0;
	unsigned long long version = 0;

	//--------------------------------------------------------------------------
	// data to manage EE
	//--------------------------------------------------------------------------
	// temp varibles
	unsigned long long value = 0;
	// work unit variables.  Note: in this sample, work units are integer
	unsigned long long work_units = 0;
	unsigned long long work_units_done = 0;
	unsigned long long reference_work_units = 0;
	// energy variables
	double double_energy_in_joules = 0.0;
	double double_consumed_energy_in_joules = 0;
	double double_reference_energy_in_joules = 0;
	double double_energy_in_joules_scaling = 0.0;
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
	double double_power = 0.0;
	double double_power_scaling = 0.0;
#endif // CUMULATIVE_EE 
	// energy EE variables
	double double_joules_per_work_unit = 0.0;
	double double_work_unit_per_joule = 0.0;
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
	// power EE variables
	double double_watts_per_work_unit = 0.0;
	double double_work_unit_per_watt = 0.0;
#endif // CUMULATIVE_EE

	//--------------------------------------------------------------------------
	// data to manage EE precision
	//--------------------------------------------------------------------------
	double double_energy_consumed_scaling = 0.0;
	double double_joules_per_work_unit_scaling = 0.0;
	double double_work_unit_per_joule_scaling = 0.0;
#ifdef CUMULATIVE_EE
#else // CUMULATIVE_EE
	double double_watts_per_work_unit_scaling = 0.0;
	double double_work_unit_per_watt_scaling = 0.0;
#endif // CUMULATIVE_EE

	//--------------------------------------------------------------------------
	// data to manage display
	//--------------------------------------------------------------------------
	unsigned long long samples_collected = 0;
	int chars_displayed = 0;
	int i = 0;

#ifdef __PL_WINDOWS__
	TCHAR *pu = NULL;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	char uuid_buffer[PL_MAX_PATH];
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//--------------------------------------------------------------------------
	// collect channel argument if any
	//--------------------------------------------------------------------------
	if(argc == 2) { channel = atoi(argv[1]); }
	if(channel <= 0) { channel = 1; }

	//--------------------------------------------------------------------------
	// compute EE precision data
	//--------------------------------------------------------------------------
	double_energy_consumed_scaling = pow(10.0, EE_ENERGY_CONSUMED_DECIMALS);
	double_joules_per_work_unit_scaling = pow(10.0, EE_JOULES_PER_WORK_UNIT_DECIMALS);
	double_work_unit_per_joule_scaling = pow(10.0, EE_WORK_UNIT_PER_JOULE_DECIMALS);
#ifdef CUMULATIVE_EE
#else // CUMULATIVE_EE
	double_watts_per_work_unit_scaling = pow(10.0, EE_WATTS_PER_WORK_UNIT_DECIMALS);
	double_work_unit_per_watt_scaling = pow(10.0, EE_WORK_UNIT_PER_WATT_DECIMALS);
#endif // CUMULATIVE_EE

	//--------------------------------------------------------------------------
	// attach to the latest ESRV instance (open ESRV's PL)
	// Note:
	//   programmer can choose a user input instead of an automatic attach
	//--------------------------------------------------------------------------
	memset(esrv_pl_config_file, 0, sizeof(esrv_pl_config_file));
	ret = plh_get_young_pl_by_application_name(ESRV_APPLICATION_NAME, &esrv_pl_config_file[0]); 
	if(ret == PL_FAILURE) {
		fprintf(stderr, "No ESRV To Attach To.\n");
		goto main_error;
	}
	pl_esrv = pl_attach(esrv_pl_config_file); assert(pl_esrv != PL_INVALID_DESCRIPTOR);

	//--------------------------------------------------------------------------
	// read-in esrv's configuration:
	//  - ESRV Status (running or not)
	//  - ESRV Channel count
	//  - ESRV Version (not used)
	//  - ESRV energy in joule counter's precision
	//  - ESRV power counter's precision (if CUMULATIVE_EE is not defined)
	// Note:
	//    since each channel holds esrv's configuration counters, we read the 
	//    first channel to read the channel count.  ESRV has always at least
	//    one channel, so the read is safe
	//--------------------------------------------------------------------------
	ret = pl_read(pl_esrv, &channels, ESRV_COUNTER_CHANNELS_INDEX); assert(ret != PL_FAILURE);
	if(channel > channels) { channel = 1; }
	channel--; // zero based channel count
	// now that the cannel count is known, we can read the requested ESRV channel
	ret = pl_read(pl_esrv, &status, (channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_STATUS_INDEX); assert(ret != PL_FAILURE);
	assert(status == ESRV_STATUS_RUNNING);
	ret = pl_read(pl_esrv, &version, (channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_VERSION_INDEX); assert(ret != PL_FAILURE);
	ret = pl_read(pl_esrv, &value, (channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_ENERGY_JOULES_DECIMALS_INDEX); assert(ret != PL_FAILURE);
	double_energy_in_joules_scaling = pow(10.0, (double)value);
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
	ret = pl_read(pl_esrv, &value, (channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_POWER_DECIMALS_INDEX); assert(ret != PL_FAILURE);
	double_power_scaling = pow(10.0, (double)value);
#endif // CUMULATIVE_EE 

	//--------------------------------------------------------------------------
	// open (our) application’s PL and print-out summary info to stdout
	//--------------------------------------------------------------------------
	pld = pl_open(application_name, COUNTERS_COUNT, counters_names, &uuid); assert(pld != PL_INVALID_DESCRIPTOR);
	fprintf(stdout, "Application Name: [%s]\n", EE_APPLICATION_NAME);
	fprintf(stdout, "ESRV Name:        [%s]\n", esrv_pl_config_file);
#ifdef __PL_WINDOWS__
	UuidToString(&uuid, (RPC_WSTR *)&pu);
	_ftprintf(stdout, _T("Using Guid:       [%s]\n"), pu);
	RpcStringFree(&pu);
#endif // __PL_WINDOWS__
#ifdef CUMULATIVE_EE 
	fprintf(stdout, "Cumulative EE:    [Yes]\n");
#else // CUMULATIVE_EE 
	fprintf(stdout, "Cumulative EE:    [No]\n");
#endif // CUMULATIVE_EE 
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	memset(uuid_buffer, 0, PL_MAX_PATH);
	uuid_unparse(uuid, uuid_buffer);
	fprintf(stdout, "Using Guid:       [%s]\n", uuid_buffer);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//--------------------------------------------------------------------------
	// write-out static counters
	// Note:
	//   by static we mean that the value of the counter - precision - will
	//   not change over time.  this is true in this sample, but may not be
	//   true for all applications.  for example, the pl_csv_logger sample
	//   doesn't assume that any counter in a PL is static and therefore
	//   reads-in suffix counters at each sample.
	//--------------------------------------------------------------------------
	value = EE_ENERGY_CONSUMED_DECIMALS; ret = pl_write(pld, &value, EE_ENERGY_CONSUMED_DECIMALS); assert(ret != PL_FAILURE);
	value = EE_JOULES_PER_WORK_UNIT_DECIMALS; ret = pl_write(pld, &value, JOULES_PER_WORK_UNIT_DECIMALS_INDEX); assert(ret != PL_FAILURE);
	value = EE_WORK_UNIT_PER_JOULE_DECIMALS; ret = pl_write(pld, &value, WORK_UNIT_PER_JOULE_DECIMALS_INDEX); assert(ret != PL_FAILURE);
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
	value = EE_WATTS_PER_WORK_UNIT_DECIMALS; ret = pl_write(pld, &value, WATTS_PER_WORK_UNIT_DECIMALS_INDEX); assert(ret != PL_FAILURE);
	value = EE_WORK_UNIT_PER_WATT_DECIMALS; ret = pl_write(pld, &value, WORK_UNIT_PER_WATT_DECIMALS_INDEX); assert(ret != PL_FAILURE);
#endif // CUMULATIVE_EE 

	//--------------------------------------------------------------------------
	// read the reference energy
	// Note:
	//   in this sample we do not assume that we expose the consumer energy
	//   with the same precision as ESRV provides it to us.  therefore we 
	//   compute the real reference energy value
	//--------------------------------------------------------------------------
	ret = pl_read(pl_esrv, &value, (channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_ENERGY_JOULES_INDEX); assert(ret != PL_FAILURE);
	double_reference_energy_in_joules = (double)value / double_energy_in_joules_scaling; 

	//--------------------------------------------------------------------------
	// in this sample we loop while the attached ESRV is running
	//--------------------------------------------------------------------------
	while(status == ESRV_STATUS_RUNNING) {

		//-----------------------------------------------------------------------
		// read the instantaneous energy and power
		// Note:
		//   in this sample we do not assume that we expose the consumer energy
		//   with the same precision as ESRV provides it to us.  therefore we 
		//   compute the real energy value
		//-----------------------------------------------------------------------
		ret = pl_read(pl_esrv, &value, (channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_ENERGY_JOULES_INDEX); assert(ret != PL_FAILURE);
		double_energy_in_joules = (double)value / double_energy_in_joules_scaling;
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
		ret = pl_read(pl_esrv, &value, (channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_POWER_INDEX); assert(ret != PL_FAILURE);
		double_power = (double)value / double_power_scaling;
#endif // CUMULATIVE_EE 

		//-----------------------------------------------------------------------
		// colect the work units done (assumed monotonously increasing)
		//-----------------------------------------------------------------------
		// TODO: implement your own work unit collection code here
		work_units = work_units + 1000;

		//-----------------------------------------------------------------------
		// compute energy consumed and work units done
		//-----------------------------------------------------------------------
		double_consumed_energy_in_joules = double_energy_in_joules - double_reference_energy_in_joules;
		work_units_done = work_units - reference_work_units;

		//-----------------------------------------------------------------------
		// write-out work units done and energy consumed
		// Note:
		//   in this sample we do not assume that we expose the consumer energy
		//   with the same precision as ESRV provides it to us.  a lower precision
		//   may make sense this is why we re-scale the energy consumed value.
		//   if the same precision is required, then the double re-scaling can be
		//   ommited.
		//-----------------------------------------------------------------------
		value = (unsigned long long)(double_consumed_energy_in_joules * double_energy_consumed_scaling);
		ret = pl_write(pld, &value, ENERGY_CONSUMED_INDEX); assert(ret != PL_FAILURE);
		ret = pl_write(pld, &work_units_done, WORK_UNITS_DONE_INDEX); assert(ret != PL_FAILURE);

		//-----------------------------------------------------------------------
		// compute and write-out joules / watts per work unit EE counters
		//-----------------------------------------------------------------------
		if(work_units_done != 0) {

			double_joules_per_work_unit = double_consumed_energy_in_joules / (double)work_units_done;
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
			double_watts_per_work_unit = double_power / (double)work_units_done;
#endif // CUMULATIVE_EE 
		} else {
			double_joules_per_work_unit = 0.0;
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
			double_watts_per_work_unit = 0.0;
#endif // CUMULATIVE_EE 
		}
		value = (unsigned long long)(double_joules_per_work_unit * double_joules_per_work_unit_scaling);
		ret = pl_write(pld, &value, JOULES_PER_WORK_UNIT_INDEX); assert(ret != PL_FAILURE);
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
		value = (unsigned long long)(double_watts_per_work_unit * double_watts_per_work_unit_scaling);
		ret = pl_write(pld, &value, WATTS_PER_WORK_UNIT_INDEX); assert(ret != PL_FAILURE);
#endif // CUMULATIVE_EE 

		//-----------------------------------------------------------------------
		// compute and write-out work unit per joule / watt EE counters
		//-----------------------------------------------------------------------
		if(double_consumed_energy_in_joules != 0) {

			double_work_unit_per_joule = (double)work_units_done / double_consumed_energy_in_joules;
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
			double_work_unit_per_watt = (double)work_units_done / double_power;
#endif // CUMULATIVE_EE 
		} else {
			double_work_unit_per_joule = 0.0;
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
			double_work_unit_per_watt = 0.0;
#endif // CUMULATIVE_EE 
		}
		value = (unsigned long long)(double_work_unit_per_joule * double_work_unit_per_joule_scaling);
		ret = pl_write(pld, &value, WORK_UNIT_PER_JOULE_INDEX); assert(ret != PL_FAILURE);
#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 
		value = (unsigned long long)(double_work_unit_per_watt * double_work_unit_per_watt_scaling);
		ret = pl_write(pld, &value, WORK_UNIT_PER_WATT_INDEX); assert(ret != PL_FAILURE);
#endif // CUMULATIVE_EE 

#ifdef CUMULATIVE_EE 
#else // CUMULATIVE_EE 

		//-----------------------------------------------------------------------
		// save reference work units done and energy for next sample
		//-----------------------------------------------------------------------
		reference_work_units = work_units;
		double_reference_energy_in_joules = double_energy_in_joules;

#endif // CUMULATIVE_EE 

		//-----------------------------------------------------------------------------
		// pause
		//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		Sleep(SAMPLE_INTERVAL * 1000);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
		sleep(SAMPLE_INTERVAL);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//-----------------------------------------------------------------------------
		// print to stdout the sample count
		//-----------------------------------------------------------------------------
		samples_collected++;
#ifdef __PL_WINDOWS__
		chars_displayed = fprintf(stdout, "Samples:          [%I64u]", samples_collected);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
		chars_displayed = fprintf(stdout, "Samples:          [%llu]", samples_collected);
		fflush(stdout);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		for(i = 0; i < chars_displayed; i++) { fprintf(stdout, "\b"); }

		//-----------------------------------------------------------------------
		// check ESRV status
		//-----------------------------------------------------------------------
		ret = pl_read(pl_esrv, &status, (channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_STATUS_INDEX); assert(ret != PL_FAILURE);

	} // while

	return(0);
main_error:
	return(1);
}
