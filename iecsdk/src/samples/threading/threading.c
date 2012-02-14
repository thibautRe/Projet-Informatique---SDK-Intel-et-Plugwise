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
#include <windows.h>
#include <rpc.h>
#include "productivity_link.h"

//-----------------------------------------------------------------------------
// use the defines below to compile specific threading demo code.
//-----------------------------------------------------------------------------
//#define DEMO1
//#define DEMO2
#define DEMO3

#pragma	message ("//-----------------------------------------------------------------------------")
#pragma	message ("// PL SDK Threading Sample.")
#pragma	message ("//-----------------------------------------------------------------------------")
#ifdef DEMO1
#pragma	message ("// DEMO1: Each worker thread owns a PL and exposes a counter.")
#endif // DEMO1
#ifdef DEMO2
#pragma	message ("// DEMO2: The primary thread owns the PL and Each worker thread exposes a counter.")
#endif // DEMO2
#ifdef DEMO3
#pragma	message ("// DEMO3: A collector thread (created by the primary thread) owns the PL")
#pragma	message ("//        and exposes the worker threads' counters.  Each worker thread ")
#pragma	message ("//        simply updates the counter values.  This is the recommanded mode,")
#pragma	message ("//        it is the less intrusive for existing codes.")
#pragma	message ("//-----------------------------------------------------------------------------")
#endif // DEMO3

//-----------------------------------------------------------------------------
// configuration defines (thread count, etc.)
//-----------------------------------------------------------------------------
#define MAX_THREADS 10
#define WORKER_THREAD_UPDATE_INTERVAL 1000
#define COLLECTOR_THREAD_UPDATE_INTERVAL 500
#define COUNTERS_BASE_NAME "counter_"
#define WORKER_THREAD_BASE_NAME "worker_thread_"
#define MAX_ITERATIONS 1000
#define MAX_COUNTER_NAME_SIZE 16
#define BUFFER_SIZE 26
#ifdef DEMO1
	#define MAX_COUNTERS 1
#endif // DEMO1
#ifdef DEMO2
	#define MAX_COUNTERS MAX_THREADS
#endif // DEMO2
#ifdef DEMO3
	#define MAX_COUNTERS MAX_THREADS
#endif // DEMO3

//-----------------------------------------------------------------------------
// thread management.
//-----------------------------------------------------------------------------
HANDLE worker_threads_handles[MAX_THREADS];
HANDLE worker_threads_events[MAX_THREADS];
DWORD worker_threads_ids[MAX_THREADS];
unsigned int worker_threads_ranks[MAX_THREADS]; 
#ifdef DEMO3
	HANDLE collector_thread_handle = NULL;
	HANDLE collector_thread_event = NULL;
	int collector_thread_id = 0;
	int job_done = 0;
#endif // DEMO3

//-----------------------------------------------------------------------------
// to simplify the demo code, these variables are made global.
//-----------------------------------------------------------------------------
#ifdef DEMO3
	unsigned long long counters_values[MAX_THREADS];
#endif // DEMO3
#ifdef DEMO2
	int pld = PL_INVALID_DESCRIPTOR;
#endif // DEMO2

/*---------------------------------------------------------------------------
@    @  @@@@  @@@@@  @   @  @@@@@@ @@@@@
@    @ @    @ @    @ @  @   @      @    @
@  @ @ @    @ @    @ @ @    @      @    @
@  @ @ @    @ @@@@@  @@     @@@@@@ @@@@@
@  @ @ @    @ @  @   @ @    @      @  @
 @ @ @ @    @ @   @  @  @   @      @   @
  @ @   @@@@  @    @ @   @  @@@@@@ @    @

Function: worker_thread_function.
Purpose : demo worker thread code.
In      : pointer to an integer = to the thread rank.
Out     : none.
Return  : none.

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
02/02/2009    Jamel Tayeb             Creation.
*/
void worker_thread_function(void *p) {
	int *px = NULL;
	int i = 0;
	int thread_rank = 0;
#ifdef DEMO1
	int pld = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	char application_name[BUFFER_SIZE] = WORKER_THREAD_BASE_NAME;
	char buffer[BUFFER_SIZE];
	char *counters[MAX_COUNTERS] = { "counter_0" };
	unsigned int counter_index = 0;
#endif // DEMO1
#ifdef DEMO3
	PL_STATUS ret = PL_SUCCESS;
#else // DEMO3
	PL_STATUS ret = PL_FAILURE;
	unsigned long long counter_value = 0;
#endif // DEMO3
	//-----------------------------------------------------------------------------
	// retrieve thread's rank.
	//-----------------------------------------------------------------------------
	assert(p != NULL);
	px = p;
	thread_rank = *px;
	printf("Worker Thread %d Is Running.\n", thread_rank);
#ifdef DEMO1
	ZeroMemory(buffer, sizeof(buffer));
	_itoa(thread_rank, buffer, 10);
	strncat(application_name, buffer, BUFFER_SIZE);
	//-----------------------------------------------------------------------------
	// open the PL.
	//-----------------------------------------------------------------------------
	pld = pl_open(application_name, MAX_COUNTERS, counters, &uuid);
	assert(pld != PL_INVALID_DESCRIPTOR);
#endif // DEMO1
#ifdef DEMO3
	for(i = 0, counters_values[thread_rank] = thread_rank * 1000; i < MAX_ITERATIONS; i++, counters_values[thread_rank]++) {
#else // MODE3
	for(i = 0, counter_value = thread_rank * 1000; i < MAX_ITERATIONS; i++, counter_value++) {
#endif // MODE3
#ifdef DEMO1
		//-----------------------------------------------------------------------------
		// write counter into the PL.
		//-----------------------------------------------------------------------------
		ret = pl_write(pld, &counter_value, counter_index);
#endif // DEMO1
#ifdef DEMO2
		//-----------------------------------------------------------------------------
		// write worker threads assigned counter into the PL.
		//-----------------------------------------------------------------------------
		ret = pl_write(pld, &counter_value, thread_rank);
#endif // DEMO2
		assert(ret == PL_SUCCESS);
		Sleep(WORKER_THREAD_UPDATE_INTERVAL);
	}
#ifdef DEMO1
	//-----------------------------------------------------------------------------
	// close the PL.
	//-----------------------------------------------------------------------------
	ret = pl_close(pld);
	assert(ret == PL_SUCCESS);
#endif // DEMO1
	//-----------------------------------------------------------------------------
	// signal work completion.
	//-----------------------------------------------------------------------------
	SetEvent(worker_threads_events[thread_rank]);
}

#ifdef DEMO3
/*---------------------------------------------------------------------------
 @@@@   @@@@  @      @      @@@@@@  @@@@   @@@@@  @@@@  @@@@@
@    @ @    @ @      @      @      @    @    @   @    @ @    @
@      @    @ @      @      @      @         @   @    @ @    @
@      @    @ @      @      @@@@@@ @         @   @    @ @@@@@
@      @    @ @      @      @      @         @   @    @ @  @
@    @ @    @ @      @      @      @    @    @   @    @ @   @
 @@@@   @@@@  @@@@@@ @@@@@@ @@@@@@  @@@@     @    @@@@  @    @

Function: collector_thread_function.
Purpose : demo counter collector thread code.
In      : none.
Out     : none.
Return  : none.

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
02/02/2009    Jamel Tayeb             Creation.
*/
void collector_thread_function(void *p) {
	int i = 0;
	PL_STATUS ret = PL_FAILURE;
	int pld = PL_INVALID_DESCRIPTOR;
	uuid_t uuid;
	char application_name[BUFFER_SIZE] = "collector_thread";
	char buffer[BUFFER_SIZE];
	char *counters_names[MAX_COUNTERS];
	printf("Collector Thread Is Running.\n");
	//-----------------------------------------------------------------------------
	// build counters' names
	//-----------------------------------------------------------------------------
	for(i = 0; i < MAX_COUNTERS; i++) {
		counters_names[i] = (char *)malloc(sizeof(char) * MAX_COUNTER_NAME_SIZE);
		assert(counters_names[i] != NULL);
		ZeroMemory(counters_names[i], MAX_COUNTER_NAME_SIZE);
		strncpy(counters_names[i], COUNTERS_BASE_NAME, MAX_COUNTER_NAME_SIZE);
		ZeroMemory(buffer, sizeof(buffer));
		_itoa(i, buffer, 10);
		strncat(counters_names[i], buffer, BUFFER_SIZE);
	}
	//-----------------------------------------------------------------------------
	// open the PL.
	//-----------------------------------------------------------------------------
	pld = pl_open(application_name, MAX_COUNTERS, counters_names, &uuid);
	assert(pld != PL_INVALID_DESCRIPTOR);
	while(job_done != 1) {
		//-----------------------------------------------------------------------------
		// write all MAX_THREADS worker threads' assigned counter into the PL.
		//-----------------------------------------------------------------------------
		for(i = 0; i < MAX_COUNTERS; i++) {
			ret = pl_write(pld, &counters_values[i], i);
			assert(ret == PL_SUCCESS);
		}
		Sleep(COLLECTOR_THREAD_UPDATE_INTERVAL);
	}
	//-----------------------------------------------------------------------------
	// close the PL.
	//-----------------------------------------------------------------------------
	ret = pl_close(pld);
	assert(ret == PL_SUCCESS);
	//-----------------------------------------------------------------------------
	// free memory allocated to store counters' names
	// Note: this could be done right after the successfull open of the PL
	//-----------------------------------------------------------------------------
	for(i = 0; i < MAX_COUNTERS; i++) {	free(counters_names[i]); }
	//-----------------------------------------------------------------------------
	// signal work completion.
	//-----------------------------------------------------------------------------
	SetEvent(collector_thread_event);
}
#endif // DEMO3

/*---------------------------------------------------------------------------
@    @   @@   @@@@@  @    @
@@  @@  @  @    @    @@   @
@ @@ @ @    @   @    @ @  @
@    @ @    @   @    @ @  @
@    @ @@@@@@   @    @  @ @
@    @ @    @   @    @   @@
@    @ @    @ @@@@@  @    @
Function: main.
Purpose : demo entry code.
In      : none.
Out     : none.
Return  : none.

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
02/02/2009    Jamel Tayeb             Creation.
*/
int main(void) {
	int i = 0;
#ifdef DEMO2
	uuid_t uuid;
	PL_STATUS ret = PL_FAILURE;
	char application_name[BUFFER_SIZE] = "primary_thread";
	char buffer[BUFFER_SIZE];
	char *counters_names[MAX_COUNTERS];
	//-----------------------------------------------------------------------------
	// build counters' names
	//-----------------------------------------------------------------------------
	for(i = 0; i < MAX_COUNTERS; i++) {
		counters_names[i] = (char *)malloc(sizeof(char) * MAX_COUNTER_NAME_SIZE);
		assert(counters_names[i] != NULL);
		ZeroMemory(counters_names[i], MAX_COUNTER_NAME_SIZE);
		strncpy(counters_names[i], COUNTERS_BASE_NAME, MAX_COUNTER_NAME_SIZE);
		ZeroMemory(buffer, sizeof(buffer));
		_itoa(i, buffer, 10);
		strncat(counters_names[i], buffer, BUFFER_SIZE);
	}
#endif // DEMO2
	printf("Primary Thread Is Running.\n");
	ZeroMemory(worker_threads_handles, sizeof(worker_threads_handles));
	ZeroMemory(worker_threads_events, sizeof(worker_threads_events));
	ZeroMemory(worker_threads_ids, sizeof(worker_threads_ids));
	ZeroMemory(worker_threads_ranks, sizeof(worker_threads_ranks));
#ifdef DEMO3
	ZeroMemory(counters_values, sizeof(counters_values));
#endif // DEMO3
#ifdef DEMO2
	//-----------------------------------------------------------------------------
	// open the PL.
	//-----------------------------------------------------------------------------
	pld = pl_open(application_name, MAX_COUNTERS, counters_names, &uuid);
	assert(pld != PL_INVALID_DESCRIPTOR);
#endif // DEMO2
	//-----------------------------------------------------------------------------
	// start MAX_THREADS worker threads.
	//-----------------------------------------------------------------------------
	for(i = 0; i < MAX_THREADS; i++) {
		worker_threads_ranks[i] = i;
		worker_threads_events[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		assert(worker_threads_events[i] != NULL);
		worker_threads_handles[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker_thread_function, &worker_threads_ranks[i], 0, &worker_threads_ids[i]);
		assert(worker_threads_handles[i] != NULL);
	}
#ifdef DEMO3
	//-----------------------------------------------------------------------------
	// start the counter collector thread.
	//-----------------------------------------------------------------------------
	collector_thread_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	assert(collector_thread_event != NULL);
	collector_thread_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)collector_thread_function, NULL, 0, &collector_thread_id);
	assert(collector_thread_handle != NULL);
#endif // DEMO3
	//-----------------------------------------------------------------------------
	// wait until all the MAX_THREADS worker threads finished to work.
	//-----------------------------------------------------------------------------
	WaitForMultipleObjects(MAX_THREADS, worker_threads_events, TRUE, INFINITE);
	printf("All Worker Threads Finished Running.\n");
#ifdef DEMO3
	//-----------------------------------------------------------------------------
	// signal the counter collector thread that all the MAX_THREADS worker threads
	// finished to work, then wait for the end of the run of the counter collector.
	//-----------------------------------------------------------------------------
	job_done = 1;
	WaitForSingleObject(collector_thread_event, INFINITE);
	printf("Collector Thread Finished Running.\n");
#endif // DEMO3
#ifdef DEMO2
	//-----------------------------------------------------------------------------
	// close the PL.
	//-----------------------------------------------------------------------------
	ret = pl_close(pld);
	assert(ret == PL_SUCCESS);
	//-----------------------------------------------------------------------------
	// free memory allocated to store counters' names
	//-----------------------------------------------------------------------------
	for(i = 0; i < MAX_COUNTERS; i++) {	free(counters_names[i]); }
#endif // DEMO2
	printf("Primary Thread Finished Running.\n");
	return(PL_SUCCESS);
}
