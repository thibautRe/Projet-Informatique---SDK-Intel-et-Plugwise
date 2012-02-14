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
// Notes: 
//    deactivate all compiler optimizations
//    run on a single CPU configuration
//    if run on a laptop, deactivate all voltage and frequency positionning 
//       features before running the test.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <assert.h>
#ifdef __PL_WINDOWS__
	#include <windows.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
	#include <string.h>
	#include <unistd.h>
	#include <errno.h>
	#include <uuid/uuid.h>
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"

//-----------------------------------------------------------------------------
// constants
//-----------------------------------------------------------------------------
#define MAX_ITERATIONS 10
#define MAX_OPERATIONS 100000

//-----------------------------------------------------------------------------
// macros
//-----------------------------------------------------------------------------
#if !defined (__PL_IA64__) && !defined (_WIN64)
	#ifdef __PL_WINDOWS__
		#define start_timer()\
				_asm RDTSC\
				_asm mov DWORD PTR start_counter, eax\
				_asm mov DWORD PTR start_counter + 4, edx
		#define stop_timer()\
				_asm RDTSC\
				_asm mov DWORD PTR stop_counter, eax\
				_asm mov DWORD PTR stop_counter + 4, edx
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
		#define start_timer() __asm__ __volatile__ ("rdtsc" : "=A" (start_counter))
		#define stop_timer() __asm__ __volatile__ ("rdtsc" : "=A" (stop_counter))
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#else // !__PL_IA64__ && !_WIN64
	#ifdef __PL_IA64__
		#ifdef __PL_IA64_USE_INTRINSIC__
			extern __int64 ItaniumTimer(void);
			#define start_timer() start_counter = ItaniumTimer()
			#define stop_timer() stop_counter = ItaniumTimer()
		#else // __PL_IA64_USE_INTRINSIC__
			#include <ia64regs.h>
			#include <ia64intrin.h>
			#define start_timer() start_counter = __getReg(_IA64_REG_AR_ITC)
			#define stop_timer() stop_counter = __getReg(_IA64_REG_AR_ITC)
		#endif // __PL_IA64_USE_INTRINSIC__
	#endif // __PL_IA64__
#endif // !__PL_IA64__ && !_WIN64
#ifdef __PL_WINDOWS__
	#define print_timer() fprintf(stdout, " (%12I64d Cycles)", stop_counter - start_counter)
	#define print_average_timer() fprintf(stdout, "Average Elapsed CPU Cycles: %12I64d\n", average_counter)
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
	#define print_timer() fprintf(stdout, " (%12llu Cycles)", stop_counter - start_counter)
	#define print_average_timer() fprintf(stdout, "Average Elapsed CPU Cycles: %12llu\n", average_counter)
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#define init_average() average_counter = 0
#define sum_average() average_counter += stop_counter - start_counter
#define compute_average(x) average_counter /= (x)

/*---------------------------------------------------------------------------
Function: main
Purpose : benchmark entry point
In      : none
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
04/16/2009    Jamel Tayeb             Creation.
*/
int main(void) {

	//----------------------------------------------------------------------
	// timing data
	//----------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	__int64 start_counter = 0;
	__int64 stop_counter = 0;
	__int64 average_counter = 0;
	__int64 base_average_cycles = 0;
	__int64 pl_write_average_cycles = 0;
	__int64 pl_read_average_cycles = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	unsigned long long start_counter = 0;
	unsigned long long stop_counter = 0;
	unsigned long long average_counter = 0;
	unsigned long long base_average_cycles = 0;
	unsigned long long pl_write_average_cycles = 0;
	unsigned long long pl_read_average_cycles = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//----------------------------------------------------------------------
	// Test PL data 
	//----------------------------------------------------------------------
	PL_STATUS ret = PL_FAILURE;
	int pld = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	char application_name[] = "benchmark";
	const char *counter_names[] = { "test_counter" };
	unsigned int counter_count = 1;
	unsigned long long i = 0;
	unsigned long long x = 0;
	int j = 0;

	//-----------------------------------------------------------------------
	// open test PL
	//-----------------------------------------------------------------------
	fprintf(stdout, "\n");
	fprintf(stdout, "************************************************************\n");
	fprintf(stdout, "* This micro-benchmark uses RDTSC / _IA64_REG_AR_ITC to    *\n");
	fprintf(stdout, "* evaluate the processor cycles required to carry-out the  *\n");
	fprintf(stdout, "* pl_write() and pl_read() Productivity Link API calls     *\n");
#ifdef __PL_WINDOWS__               
	fprintf(stdout, "* (%12I64u write and read operations are performed    *\n", (unsigned long long)(MAX_ITERATIONS * MAX_OPERATIONS));
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	fprintf(stdout, "* (%12llu write and read operations are performed    *\n", (unsigned long long)(MAX_ITERATIONS * MAX_OPERATIONS));
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	fprintf(stdout, "* in sequence).                                            *\n");
	fprintf(stdout, "*                                                          *\n");
	fprintf(stdout, "* This method is imperfect as it will catch cycles         *\n");
	fprintf(stdout, "* consumed by interrupt routines.  Therefore, consider     *\n");
	fprintf(stdout, "* numbers as indications, not exact values.                *\n");
	fprintf(stdout, "* When running the benchmark, stop all other applications. *\n");
	fprintf(stdout, "*                                                          *\n");
	fprintf(stdout, "* When compiling the benchmark, deactivate all compiler    *\n");
	fprintf(stdout, "* optimizations.  Run in single processor configuration.   *\n");
	fprintf(stdout, "* Deactivate all frequency and voltage adjustment          *\n");
	fprintf(stdout, "* features before running this micro-benchmark.            *\n");
	fprintf(stdout, "************************************************************\n");
	fprintf(stdout, "\n");

	fprintf(stdout, "Opening Test PL:\n");
	pld = pl_open(application_name, counter_count, counter_names, &uuid);
	assert(pld != PL_INVALID_DESCRIPTOR);

	//-- test zone ----------------------------------------------------------

	/*
	@@@@@    @@    @@@@  @@@@@@         @@@@@ @@@@@@  @@@@   @@@@@
	@    @  @  @  @    @ @                @   @      @    @    @
	@    @ @    @ @      @                @   @      @         @
	@@@@@  @    @  @@@@  @@@@@@           @   @@@@@@  @@@@     @
	@    @ @@@@@@      @ @                @   @           @    @
	@    @ @    @      @ @                @   @           @    @
	@@@@@  @    @ @@@@@  @@@@@@           @   @@@@@@ @@@@@     @	
	*/
	//-----------------------------------------------------------------------
	// reference loop
	//-----------------------------------------------------------------------
	init_average();
	fprintf(stdout, "Measuring Base Data       : ");
	for(j = 0; j < MAX_ITERATIONS; j++) {
		fprintf(stdout, "*");
		start_timer();
		for(i = 0; i < MAX_OPERATIONS; i++) {
			;
		}
		stop_timer();
		x = i; // consume i in case optimization is activated
		sum_average();
	}
	print_timer();
	fprintf(stdout, "\n");
	compute_average(MAX_ITERATIONS * MAX_OPERATIONS);
	base_average_cycles = average_counter;

	/*
	@    @ @@@@@  @@@@@   @@@@@ @@@@@@         @@@@@ @@@@@@  @@@@   @@@@@
	@    @ @    @   @       @   @                @   @      @    @    @
	@  @ @ @    @   @       @   @                @   @      @         @
	@  @ @ @@@@@    @       @   @@@@@@           @   @@@@@@  @@@@     @
	@  @ @ @  @     @       @   @                @   @           @    @
	 @ @ @ @   @    @       @   @                @   @           @    @
	  @ @  @    @ @@@@@     @   @@@@@@           @   @@@@@@ @@@@@     @	
	*/
	//----------------------------------------------------------------------
	// write loop
	//----------------------------------------------------------------------
	init_average();
	fprintf(stdout, "Measuring pl_write() Data : ");
	for(j = 0; j < MAX_ITERATIONS; j++) {
		fprintf(stdout, "*");
		start_timer();
		for(i = 0; i < MAX_OPERATIONS; i++) {
			pl_write(pld, &i, 0);
		}
		stop_timer();
		sum_average();
	}
	print_timer();
	fprintf(stdout, "\n");
	compute_average(MAX_ITERATIONS * MAX_OPERATIONS);
	pl_write_average_cycles = average_counter;

	/*
	@@@@@  @@@@@@   @@   @@@@@          @@@@@ @@@@@@  @@@@   @@@@@
	@    @ @       @  @  @    @           @   @      @    @    @
	@    @ @      @    @ @    @           @   @      @         @
	@@@@@  @@@@@@ @    @ @    @           @   @@@@@@  @@@@     @
	@  @   @      @@@@@@ @    @           @   @           @    @
	@   @  @      @    @ @    @           @   @           @    @
	@    @ @@@@@@ @    @ @@@@@            @   @@@@@@ @@@@@     @	
	*/
	//----------------------------------------------------------------------
	// read loop
	//----------------------------------------------------------------------
	init_average();
	fprintf(stdout, "Measuring pl_read() Data  : ");
	for(j = 0; j < MAX_ITERATIONS; j++) {
		fprintf(stdout, "*");
		start_timer();
		for(i = 0; i < MAX_OPERATIONS; i++) {
			pl_read(pld, &x, 0);
		}
		stop_timer();
		sum_average();
	}
	print_timer();
	fprintf(stdout, "\n");
	compute_average(MAX_ITERATIONS * MAX_OPERATIONS);
	pl_read_average_cycles = average_counter;

	//-- end test zone -----------------------------------------------------

	//----------------------------------------------------------------------
	// close test PL
	//----------------------------------------------------------------------
	fprintf(stdout, "Closing Test PL.\n");
	ret = pl_close(pld);
	assert(ret == PL_SUCCESS);

	//----------------------------------------------------------------------
	// report test results
	//----------------------------------------------------------------------
	fprintf(stdout, "\n");
	fprintf(stdout, "Test Report:\n");
	fprintf(stdout, "=============\n");
	fprintf(stdout, "\n");
#ifdef __PL_WINDOWS__
	fprintf(stdout, "Average CPU cycles per pl_write() call :       %12I64u.\n", pl_write_average_cycles);
	fprintf(stdout, "Average CPU cycles per pl_read() call  :       %12I64u.\n", pl_read_average_cycles);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	fprintf(stdout, "Average CPU cycles per pl_write() call :       %12llu.\n", pl_write_average_cycles);
	fprintf(stdout, "Average CPU cycles per pl_read() call  :       %12llu.\n", pl_read_average_cycles);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	fprintf(stdout, "\n");
	fprintf(stdout, "Notes:\n");
	fprintf(stdout, "======\n");
	fprintf(stdout, " *  A 2.0 GHz processor with two cores processes ~4 billion\n");
	fprintf(stdout, "instructions per second (~2 billion per core).   Allocation\n");
	fprintf(stdout, "of system CPU cycles under the following conditions:\n");
#ifdef __PL_WINDOWS__
	fprintf(stdout, "1000 pl_write() calls per second:                   ~%1.3f%%\n", (double)pl_write_average_cycles / 40000.0);
	fprintf(stdout, "1000 pl_read() calls per second:                    ~%1.3f%%\n", (double)pl_read_average_cycles / 40000.0);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	fprintf(stdout, "1000 pl_write() calls per second:                   ~%1.3f%%\n", (double)pl_write_average_cycles / 40000.0);
	fprintf(stdout, "1000 pl_read() calls per second:                    ~%1.3f%%\n", (double)pl_read_average_cycles / 40000.0);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__	fprintf(stdout, "\n");
	fprintf(stdout, "\n");
	fprintf(stdout, " *  1.0 GHz cycle = 1.0 nanosecond = 1.0 x 10-9 second.\n");
	fprintf(stdout, "                10 nanoseconds   =   1.0 x 10-5 millisecond.\n");
	fprintf(stdout, "               100 nanoseconds   =       0.0001 millisecond.\n");
	fprintf(stdout, "             1,000 nanoseconds   =        0.001 millisecond.\n");
	fprintf(stdout, "            10,000 nanoseconds   =         0.01 millisecond.\n");
	fprintf(stdout, "          100,000 nanoseconds    =          0.1 millisecond.\n");
	fprintf(stdout, "        1,000,000 nanoseconds    =            1 millisecond.\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "************************************************************\n");
	fprintf(stdout, "*               End of micro-benchmark                     *\n");
	fprintf(stdout, "************************************************************\n");
	fprintf(stdout, "\n");

	return(PL_SUCCESS);
}
