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
// Headers inclusions.
//-----------------------------------------------------------------------------
#ifdef _DEBUG
	#ifdef __PL_WINDOWS__
		#define _CRTDBG_MAP_ALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif // __PL_WINDOWS__
#else // _DEBUG
	#include <stdlib.h>
#endif // _DEBUG

#include <assert.h>

#ifdef __PL_WINDOWS__
	#include <windows.h>
	#ifdef _DEBUG
		#include <tchar.h>
	#endif // _DEBUG
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

	//-------------------------------------------------------------------------
	// Notes:
	//    Under Linux, compile with _BSD_SOURCE
	//    Under Solaris 10, link with -lnsl, -lsocket
	//-------------------------------------------------------------------------
	#include <string.h>
	#include <signal.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <pthread.h>
	#include <errno.h>
	#include <netdb.h>
	#include <stdio.h>
	#include <sys/ioctl.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#include "productivity_link.h"
#include "productivity_link_helper.h"
#include "productivity_link_agent.h"

//-----------------------------------------------------------------------------
// Global(s).
//-----------------------------------------------------------------------------
int f_running = 1;
PL_AGENT_DATA agent_data;

/*-----------------------------------------------------------------------------
Function: main
Purpose : agent entry code
In      : none
Out     : None
Return  : status.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
06/07/2010    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
PL_STATUS main(int argc, char *argv[]) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
int main(int argc, char *argv[]) {
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Generic variables
	//-------------------------------------------------------------------------
	int i = 0;
	int f_error = 0;
	size_t memory_size = 0;
	PL_STATUS ret = PL_FAILURE;
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
	DWORD dwret = 0;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	struct sigaction sa;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Pointer to agent data structure.
	//-------------------------------------------------------------------------
	PPL_AGENT_DATA p = NULL;

	//-------------------------------------------------------------------------
	// Data used to display messages.
	//-------------------------------------------------------------------------
	char tmp_buffer[PL_MAX_PATH] = { '\0' };

	//-------------------------------------------------------------------------
	// Data used to manage IPC.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	WSADATA windows_socket_data;
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// Data used to retrive local IP @.
	//-------------------------------------------------------------------------
	char host_name[PL_MAX_PATH] = { '\0' };

#ifdef __PL_WINDOWS__
	PHOSTENT host_info;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	struct hostent *host_info;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Setup memory allocation errors detection (Windows and debug only).
	//-------------------------------------------------------------------------
#ifdef _DEBUG
#ifdef __PL_WINDOWS__

	DWORD dw_ret = -1;

	//-------------------------------------------------------------------------

	#pragma	message ("NOTE: Building a Debug version with memory leak detection.")

	//-------------------------------------------------------------------------
	// Dump memory leak info on any exit.
	//-------------------------------------------------------------------------
	dw_ret = _CrtSetDbgFlag(
		_CRTDBG_ALLOC_MEM_DF | 
		_CRTDBG_LEAK_CHECK_DF
	);
	if(dw_ret == -1) {
		f_error = 1;
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_ACTIVATE_MEMORY_LEAK_DETECTION);
		goto main_clean_up;
	}

	//-------------------------------------------------------------------------
	// Redirect dump to stdout.
	//-------------------------------------------------------------------------
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

#endif // __PL_WINDOWS__
#endif // _DEBUG

	//-------------------------------------------------------------------------
	// Retrive the pointer to agent data structure.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_STARTED_STRING
	);
	p = &agent_data;
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Clear agent data structure.
	//-------------------------------------------------------------------------
	memset(
		p, 
		0, 
		sizeof(agent_data)
	);
	p->threads_in_pool_value = PL_AGENT_DEFAULT_THREADS_IN_POOL;

	//-------------------------------------------------------------------------
	// Parse CLI input.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_PARSING_CLI_STRING
	);
	ret = pl_agent_cli_parser(
		p, 
		argc, 
		argv
	);
	if(ret == PL_SUCCESS) {

		//---------------------------------------------------------------------
		// Check for no_error error condition return from the parser.  If such
		// case is detected, then free memory allocated to store IP addresses
		// and exit successfully - with no special echo.
		//---------------------------------------------------------------------
		if(
			(p->f_help_requested == 1) || 
			(p->f_version_requested == 1)
		) {
			goto main_return;
		}

		//---------------------------------------------------------------------
		// Echo version info to stdout.
		//---------------------------------------------------------------------
		memset(
			tmp_buffer, 
			0, 
			sizeof(tmp_buffer)
		);
		sprintf(
			tmp_buffer, 
			"%s version [%s.%s.%s].\n",
			PL_AGENT_NAME, 
			PL_AGENT_VERSION_MAJOR, 
			PL_AGENT_VERSION_MINOR, 
			PL_AGENT_VERSION_REVISION
		);
		pl_agent_message(
			tmp_buffer, 
			NULL
		);
		memset(
			tmp_buffer, 
			0, 
			sizeof(tmp_buffer)
		);
		sprintf(
			tmp_buffer, 
			"Using PL helper version [%s.%s.%s].\n",
			PL_HELPER_VERSION_MAJOR, 
			PL_HELPER_VERSION_MINOR, 
			PL_HELPER_VERSION_REVISION
		);
		pl_agent_message(
			tmp_buffer, 
			NULL
		);
		memset(
			tmp_buffer, 
			0, 
			sizeof(tmp_buffer)
		);
		sprintf(
			tmp_buffer, 
			"Using PL version [%s.%s.%s(%s)].\n",
			PL_VERSION_MAJOR, 
			PL_VERSION_MINOR, 
			PL_VERSION_REVISION, 
			PL_VERSION_OS
		);
		pl_agent_message(
			tmp_buffer, 
			NULL
		);

#ifdef __PL_WINDOWS__

		//---------------------------------------------------------------------
		// Initialize winsoks.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_INIT_SOCKET_STRING
		);
		ret = WSAStartup(
			MAKEWORD(
				2, 
				2
			),
			&windows_socket_data
		);
		if(ret != 0) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_INITIALIZE_SOCKET);
		}
#endif // __PL_WINDOWS__

		//---------------------------------------------------------------------
		// Get the local IP @.
		//---------------------------------------------------------------------
		memset(
			host_name, 
			0, 
			sizeof(host_name)
		);
		ret = gethostname(
			host_name, 
			sizeof(host_name)
		);
		if(
			(ret != 0) ||
			(strlen(host_name) == 0)
		) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_GET_HOST_STRUCTURE_FROM_HOSTNAME);
			goto main_return;
		}
#ifdef __PL_WINDOWS__
		host_info = gethostbyname(host_name);
		if(host_info == NULL) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_GET_HOST_STRUCTURE_FROM_HOSTNAME);
		}
		p->ip_address = inet_ntoa(*(struct in_addr *)*host_info->h_addr_list);
		if(p->ip_address == NULL) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CONVERT_ADDRESS_STRING_INTO_STRUCTURE);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		host_info = gethostbyname(host_name);
		if(host_info == NULL) { 

			//-----------------------------------------------------------------
			// don't give up completely yet, let's try localhost.
			//-----------------------------------------------------------------
			sprintf(
				host_name,
				"%s",
				PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME
			);
			host_info = gethostbyname(host_name);
			if(host_info == NULL) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_GET_HOST_STRUCTURE_FROM_HOSTNAME);
				goto main_return;
			}
		}
		p->ip_address = inet_ntoa(*(struct in_addr *)*host_info->h_addr_list);
		if(p->ip_address == NULL) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CONVERT_ADDRESS_STRING_INTO_STRUCTURE);
			goto main_return;
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Echo local IP@ and ports info to stdout.
		//---------------------------------------------------------------------
		memset(
			tmp_buffer, 
			0, 
			sizeof(tmp_buffer)
		);
		sprintf(
			tmp_buffer, 
			"Agent is running on [%s].\n",
			p->ip_address
		);
		pl_agent_message(
			tmp_buffer, 
			NULL
		);
		memset(
			tmp_buffer, 
			0, 
			sizeof(tmp_buffer)
		);
		sprintf(
			tmp_buffer, 
#ifdef __PL_WINDOWS__
			"ADMIN port is [%s] and PL port is [%s].\n",
			(
				p->f_admin_port == 1 ? 
				p->admin_port_string : 
				PL_DEFAULT_PL_AGENT_ADMIN_PORT
			),
			(
				p->f_pl_port == 1 ? 
				p->pl_port_string : 
				PL_DEFAULT_PL_AGENT_PL_PORT
			)
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			"ADMIN port is [%d] and PL port is [%d].\n",
			(
				p->f_admin_port == 1 ? 
				p->admin_port_value : 
				PL_DEFAULT_PL_AGENT_ADMIN_PORT
			),
			(
				p->f_pl_port == 1 ? 
				p->pl_port_value : 
				PL_DEFAULT_PL_AGENT_PL_PORT
			)
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		); // end of sprintf call
		pl_agent_message(
			tmp_buffer, 
			NULL
		);

		//---------------------------------------------------------------------
		// Allocate pool thread data.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_ALLOCATE_THREAD_POOL_DATA_STRING
		);
		memory_size = 
			sizeof(PL_AGENT_POOL_THREADS_DATA) * 
			p->threads_in_pool_value
		;
		p->pool_threads_data = 
			(PL_AGENT_POOL_THREADS_DATA *)malloc(memory_size)
		;
		if(p->pool_threads_data == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->pool_threads_data, 
			0, 
			memory_size
		);
#ifdef __PL_WINDOWS__
		memory_size = sizeof(HANDLE) * p->threads_in_pool_value;
		p->h_pool_threads = (HANDLE *)malloc(memory_size);
		if(p->h_pool_threads == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->h_pool_threads, 
			0, 
			memory_size
		);

		p->h_pool_threads_do = (HANDLE *)malloc(memory_size);
		if(p->h_pool_threads_do == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->h_pool_threads_do, 
			0, 
			memory_size
		);

		p->h_pool_threads_done = (HANDLE *)malloc(memory_size);
		if(p->h_pool_threads_done == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->h_pool_threads_done, 
			0, 
			memory_size
		);

		memory_size = sizeof(DWORD) * p->threads_in_pool_value;
		p->pool_threads_ids = (DWORD *)malloc(memory_size);
		if(p->pool_threads_ids == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->pool_threads_ids, 
			0, 
			memory_size
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		memory_size = sizeof(pthread_t) * p->threads_in_pool_value;
		p->h_pool_threads = (pthread_t *)malloc(memory_size);
		if(p->h_pool_threads == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->h_pool_threads, 
			0, 
			memory_size
		);
#ifndef __PL_MACOSX__
		memory_size = sizeof(sem_t) * p->threads_in_pool_value;
		p->h_pool_threads_do = (sem_t *)malloc(memory_size);
		if(p->h_pool_threads_do == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->h_pool_threads_do, 
			0, 
			memory_size
		);
		p->h_pool_threads_done = (sem_t *)malloc(memory_size);
		if(p->h_pool_threads_done == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->h_pool_threads_done, 
			0, 
			memory_size
		);
#else // __PL_MACOSX__
		memory_size = sizeof(char *) * p->threads_in_pool_value;
		p->pool_threads_do_sem_names = (char **)malloc(memory_size);
		if(p->pool_threads_do_sem_names == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->pool_threads_do_sem_names, 
			0, 
			memory_size
		);
		p->pool_threads_done_sem_names = (char **)malloc(memory_size);
		if(p->pool_threads_done_sem_names == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->pool_threads_done_sem_names, 
			0, 
			memory_size
		);
		memory_size = sizeof(char) * (SEMAPHORE_NAME_MAX_SIZE + 1);
		for(i = 0; i < p->threads_in_pool_value; i++) {
			p->pool_threads_do_sem_names[i] = (char *)malloc(memory_size);
			if(p->pool_threads_do_sem_names[i] == NULL) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
			}
			memset(
				p->pool_threads_do_sem_names[i], 
				0, 
				memory_size
			);
			p->pool_threads_done_sem_names[i] = (char *)malloc(memory_size);
			if(p->pool_threads_done_sem_names[i] == NULL) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
			}
			memset(
				p->pool_threads_done_sem_names[i], 
				0, 
				memory_size
			);
		}

		memory_size = sizeof(sem_t *) * p->threads_in_pool_value;
		p->h_pool_threads_do = (sem_t **)malloc(memory_size);
		if(p->h_pool_threads_do == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->h_pool_threads_do, 
			0, 
			memory_size
		);
		p->h_pool_threads_done = (sem_t **)malloc(memory_size);
		if(p->h_pool_threads_done == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
		}
		memset(
			p->h_pool_threads_done, 
			0, 
			memory_size
		);
		memory_size = sizeof(sem_t *);
		for(i = 0; i < p->threads_in_pool_value; i++) {
			p->h_pool_threads_do[i] = (sem_t *)malloc(memory_size);
			if(p->h_pool_threads_do[i] == NULL) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
			}
			memset(
				p->h_pool_threads_do[i], 
				0, 
				memory_size
			);
			p->h_pool_threads_done[i] = (sem_t *)malloc(memory_size);
			if(p->h_pool_threads_done[i] == NULL) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
			}
			memset(
				p->h_pool_threads_done[i], 
				0, 
				memory_size
			);
		}
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Create synchornization objects.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_CREATING_SYNCH_OBJECTS_STRING
		);
#ifdef __PL_WINDOWS__
		p->h_main_thread_done = CreateEvent(
			NULL, 
			TRUE, 
			FALSE, 
			NULL
		); // manual-reset and non signaled

		p->h_admin_port_listener_thread_done = CreateEvent(
			NULL, 
			FALSE, 
			FALSE, 
			NULL
		); // auto-reset and non signaled

		if(p->h_admin_port_listener_thread_done == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}
		p->h_pl_port_listener_thread_done = CreateEvent(
			NULL, 
			FALSE, 
			FALSE, 
			NULL
		); // auto-reset and non signaled
		if(p->h_pl_port_listener_thread_done == NULL) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}
		for(i = 0; i < p->threads_in_pool_value; i++) {
			p->h_pool_threads_do[i] = CreateEvent(
				NULL, 
				FALSE, 
				FALSE, 
				NULL
			); // auto-reset and non signaled
			if(p->h_pool_threads_do[i] == NULL) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
			}
			p->h_pool_threads_done[i] = CreateEvent(
				NULL, 
				FALSE, 
				FALSE, 
				NULL
			); // auto-reset and non signaled
			if(p->h_pool_threads_done[i] == NULL) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
			}
			p->pool_threads_data[i].semaphore = CreateSemaphore(
				NULL, 
				(LONG)1, 
				(LONG)1, 
				NULL
			);
			if(p->pool_threads_data[i].semaphore == NULL) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
			}
		} // for i
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		ret = sem_init(
			&p->h_main_thread_done, 
			0, 
			0
		);
		if(ret == -1) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}
		ret = sem_init(
			&p->h_admin_port_listener_thread_done, 
			0, 
			0
		);
		if(ret == -1) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}
		ret = sem_init(
			&p->h_pl_port_listener_thread_done, 
			0, 
			0
		);
		if(ret == -1) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}
		for(i = 0; i < p->threads_in_pool_value; i++) {
			ret = sem_init(
				&p->h_pool_threads_do[i],
				0, 
				0
			);
			if(ret == -1) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
			}
			ret = sem_init(
				&p->h_pool_threads_done[i],
				0, 
				0
			);
			if(ret == -1) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
			}
			ret = sem_init(
				&p->pool_threads_data[i].semaphore, 
				0, 
				1
			);
			if(ret == -1) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
			}
		} // for i
#else // __PL_MACOSX__
		memset(
			p->main_thread_done_sem_name, 
			0, 
			sizeof(p->main_thread_done_sem_name)
		);
		sprintf(
			p->main_thread_done_sem_name, 
			"%s", 
			MAIN_THREAD_DONE_SEMAPHORE_NAME
		);
		p->h_main_thread_done = sem_open(
			p->main_thread_done_sem_name, 
			O_CREAT, 
			(mode_t)PL_AGENT_SEMAPHORE_ACCESS_MODE, 
			0
		);
		if(p->h_main_thread_done == SEM_FAILED) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}

		memset(
			p->admin_port_listener_thread_done_sem_name, 
			0, 
			sizeof(p->admin_port_listener_thread_done_sem_name)
		);
		sprintf(
			p->admin_port_listener_thread_done_sem_name, 
			"%s", 
			ADMIN_PORT_LISTENER_THREAD_DONE_SEMAPHORE_NAME
		);
		p->h_admin_port_listener_thread_done = sem_open(
			p->admin_port_listener_thread_done_sem_name, 
			O_CREAT, 
			(mode_t)PL_AGENT_SEMAPHORE_ACCESS_MODE, 
			0
		);
		if(p->h_admin_port_listener_thread_done == SEM_FAILED) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}

		memset(
			p->pl_port_listener_thread_done_sem_name, 
			0, 
			sizeof(p->pl_port_listener_thread_done_sem_name)
		);
		sprintf(
			p->pl_port_listener_thread_done_sem_name, 
			"%s", 
			PL_PORT_LISTENER_THREAD_DONE_SEMAPHORE_NAME
		);
		p->h_pl_port_listener_thread_done = sem_open(
			p->pl_port_listener_thread_done_sem_name, 
			O_CREAT, 
			(mode_t)PL_AGENT_SEMAPHORE_ACCESS_MODE, 
			0
		);
		if(p->h_pl_port_listener_thread_done == SEM_FAILED) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}

		for(i = 0; i < p->threads_in_pool_value; i++) {
			memset(
				p->pool_threads_do_sem_names[i], 
				0, 
				sizeof(char) * (SEMAPHORE_NAME_MAX_SIZE + 1)
			);
			sprintf(
				p->pool_threads_do_sem_names[i], 
				"%s%d", 
				POOL_THREAD_DO_SEMAPHORE_BASE_NAME,
				i
			);
			p->h_pool_threads_do[i] = sem_open(
				p->pool_threads_do_sem_names[i], 
				O_CREAT, 
				(mode_t)PL_AGENT_SEMAPHORE_ACCESS_MODE, 
				0
			);
			if(p->h_pool_threads_do[i] == SEM_FAILED) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
			}

			memset(
				p->pool_threads_done_sem_names[i], 
				0, 
				sizeof(char) * (SEMAPHORE_NAME_MAX_SIZE + 1)
			);
			sprintf(
				p->pool_threads_done_sem_names[i], 
				"%s%d", 
				POOL_THREAD_DONE_SEMAPHORE_BASE_NAME,
				i
			);
			p->h_pool_threads_done[i] = sem_open(
				p->pool_threads_done_sem_names[i], 
				O_CREAT, 
				(mode_t)PL_AGENT_SEMAPHORE_ACCESS_MODE, 
				0
			);
			if(p->h_pool_threads_done[i] == SEM_FAILED) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
			}
		} // for i
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Create pool threads.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_CREATEING_THREAD_POOL_STRING
		);
		for(i = 0; i < p->threads_in_pool_value; i++) {
#ifdef __PL_WINDOWS__
			p->h_pool_threads[i] = CreateThread(
				NULL, 
				0, 
				(LPTHREAD_START_ROUTINE)pool_thread, 
				(LPVOID)p, 
				0,
				&p->pool_threads_ids[i]
			);
			if(p->h_pool_threads[i] == NULL) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_THREAD);
			}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			ret = pthread_create(
				&p->h_pool_threads[i], 
				NULL, 
				pool_thread, 
				(void *)p
			);
			if(ret != 0) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_THREAD);
			}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		} // for i

		//---------------------------------------------------------------------
		// Echo to stdout the pool thread size.
		//---------------------------------------------------------------------
		memset(
			tmp_buffer, 
			0, 
			sizeof(tmp_buffer)
		);
		sprintf(
			tmp_buffer, 
			"Agent has [%d] thread(s) in the pool.\n",
			p->threads_in_pool_value
		);
		pl_agent_message(
			tmp_buffer, 
			NULL
		);

		//---------------------------------------------------------------------
		// Create admin port listener thread.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_CREATING_ADMIN_THREAD_STRING
		);
#ifdef __PL_WINDOWS__
		p->h_admin_port_listener_thread = CreateThread(
			NULL, 
			0, 
			(LPTHREAD_START_ROUTINE)admin_port_listener_thread, 
			(LPVOID)p, 
			0,
			&p->admin_port_listener_thread_ids
		);
		if(p->h_pool_threads[i] == NULL) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_THREAD);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = pthread_create(
			&p->h_admin_port_listener_thread, 
			NULL, 
			admin_port_listener_thread, 
			(void *)p
		);
		if(ret != 0) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_THREAD);
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Create pl port listener thread.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_CREATING_PL_PORT_THREAD_STRING
		);
#ifdef __PL_WINDOWS__
		p->h_pl_port_listener_thread = CreateThread(
			NULL, 
			0, 
			(LPTHREAD_START_ROUTINE)pl_port_listener_thread, 
			(LPVOID)p, 
			0,
			&p->pl_port_listener_thread_ids
		);
		if(p->h_pool_threads[i] == NULL) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_THREAD);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = pthread_create(
			&p->h_pl_port_listener_thread, 
			NULL, 
			pl_port_listener_thread, 
			(void *)p
		);
		if(ret != 0) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_THREAD);
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Echo to stdout the interrupt message.
		//---------------------------------------------------------------------
		pl_agent_message(
			PL_AGENT_INTERRUPT_INSTRUCTIONS_PL_AGENT_DEBUG_MESSAGE_STRING, 
			NULL
		);

		//---------------------------------------------------------------------
		// Signal that main thread is done.
		// Note:
		//    Passed this point, all threads - including pool threads -- will
		//    start working.  This means that any data & initialization
		//    required by these threads MUST be allocated and properly 
		//    initialized before.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_MAIN_THREAD_DONE_STRING
		);
#ifdef __PL_WINDOWS__
		bret = SetEvent(
			p->h_main_thread_done
		);
		if(bret == FALSE) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		for(i = 0; i < (p->threads_in_pool_value + 2); i++) {
#ifndef __PL_MACOSX__
			ret = sem_post(
				&p->h_main_thread_done
			);
#else // __PL_MACOSX__
			ret = sem_post(
				p->h_main_thread_done
			);
#endif // __PL_MACOSX__
			if(ret != 0) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
			}
		} // for i
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Install the signal handler routine.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	bret = SetConsoleCtrlHandler(
		(PHANDLER_ROUTINE)signal_handler, 
		TRUE
	);
	if(bret == FALSE) { 
		f_error = 1; 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_INSTALL_SIGNAL_HANDLER);
		goto main_clean_up;
	}
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
		f_error = 1;
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_INSTALL_SIGNAL_HANDLER);
		goto main_clean_up; 
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef _DEBUG

		//---------------------------------------------------------------------
		// Setup API Stat counters
		//---------------------------------------------------------------------
		p->pl_open_count = 0;
		p->pl_close_count = 0;
		p->pl_attach_count = 0;
		p->pl_read_count = 0;
		p->pl_write_count = 0;

		//---------------------------------------------------------------------
		// Setup API errors Stat counters
		//---------------------------------------------------------------------
		p->pl_open_errors_count = 0;
		p->pl_close_errors_count = 0;
		p->pl_attach_errors_count = 0;
		p->pl_read_errors_count = 0;
		p->pl_write_errors_count = 0;

		//---------------------------------------------------------------------
		// Setup synchronisation object
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		InitializeCriticalSection(&p->cs);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		ret = sem_init(
			&p->cs, 
			0, 
			1
		);
		if(ret == -1) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}
#else // __PL_MACOSX__
		memset(
			p->cs_name, 
			0, 
			sizeof(p->cs_name)
		);
		sprintf(
			p->cs_name, 
			"%s", 
			CS_SEMAPHORE_NAME
		);
		p->cs = sem_open(
			p->cs_name, 
			O_CREAT,
			(mode_t)PL_SEMAPHORE_ACCESS_MODE,
			1
		);
		if(p->cs == SEM_FAILED) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT);
		}
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // _DEBUG

		//---------------------------------------------------------------------
		// Wait for all threads completion.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_WAITING_ALL_THREADS_STRING
		);
#ifdef __PL_WINDOWS__
		dwret = WaitForMultipleObjects(
			p->threads_in_pool_value,
			p->h_pool_threads_done, 
			TRUE,
			INFINITE
		);
		if(dwret != WAIT_OBJECT_0) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
		}
		dwret = WaitForSingleObject(
			p->h_admin_port_listener_thread_done,
			INFINITE
		);
		if(dwret != WAIT_OBJECT_0) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
		}
		dwret = WaitForSingleObject(
			p->h_pl_port_listener_thread_done,
			INFINITE
		);
		if(dwret != WAIT_OBJECT_0) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		for(i = 0; i < p->threads_in_pool_value; i++) {
pl_agent_main_wait_pool:
#ifndef __PL_MACOSX__
			ret = sem_wait(&p->h_pool_threads_done[i]);
#else // __PL_MACOSX__
			ret = sem_wait(p->h_pool_threads_done[i]);
#endif // __PL_MACOSX__
			if(ret == -1) {
				if(errno == EINTR) {
					goto pl_agent_main_wait_pool;
				}
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
			}
		}
pl_agent_main_wait_admin_listener:
#ifndef __PL_MACOSX__
		ret = sem_wait(&p->h_admin_port_listener_thread_done);
#else // __PL_MACOSX__
		ret = sem_wait(p->h_admin_port_listener_thread_done);
#endif // __PL_MACOSX__
		if(ret == -1) {
			if(errno == EINTR) {
				goto pl_agent_main_wait_admin_listener;
			}
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
		}
pl_agent_main_wait_pl_listener:
#ifndef __PL_MACOSX__
		ret = sem_wait(&p->h_pl_port_listener_thread_done);
#else // __PL_MACOSX__
		ret = sem_wait(p->h_pl_port_listener_thread_done);
#endif // __PL_MACOSX__
		if(ret == -1) {
			if(errno == EINTR) {
				goto pl_agent_main_wait_pl_listener;
			}
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	}

#ifdef _DEBUG

	//-------------------------------------------------------------------------
	// Display API usage stats
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(PL_AGENT_DEBUG_MESSAGE_STATS_API_USAGE_COUNT);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_OPEN_COUNT, 
		p->pl_open_count
	);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_CLOSE_COUNT, 
		p->pl_close_count
	);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_ATTACH_COUNT, 
		p->pl_attach_count
	);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_READ_COUNT, 
		p->pl_read_count
	);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_WRITE_COUNT, 
		p->pl_write_count
	);

	//-------------------------------------------------------------------------
	// Display API error stats
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(PL_AGENT_DEBUG_MESSAGE_STATS_API_ERROR_COUNT);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_OPEN_ERROR_COUNT, 
		p->pl_open_errors_count
	);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_CLOSE_ERROR_COUNT, 
		p->pl_close_errors_count
	);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_ATTACH_ERROR_COUNT, 
		p->pl_attach_errors_count
	);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_READ_ERROR_COUNT, 
		p->pl_read_errors_count
	);
	PL_AGENT_DEBUG_MESSAGE_WITH_ULL(
		PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_WRITE_ERROR_COUNT, 
		p->pl_write_errors_count
	);

	//-------------------------------------------------------------------------
	// Destroy stat/error synchronisation object
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	DeleteCriticalSection(&p->cs);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	ret = sem_destroy(
		&p->cs
	);
	if(ret == -1) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
	}
#else // __PL_MACOSX__
	ret = sem_unlink(
		p->cs_name
	);
	if(ret == -1) { 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
	}
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#endif // _DEBUG

	//-------------------------------------------------------------------------
	// Display total errors count.
	//-------------------------------------------------------------------------
	PL_AGENT_MESSAGE_WITH_ULL(
		PL_AGENT_MESSAGE_STATS_TOTAL_ERROR_COUNT, 
		p->errors_count
	);

main_clean_up:

	//-------------------------------------------------------------------------
	// Destroy synchronization objects.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_DESTROYING_SYNCH_OBJECTS_STRING
	);
#ifdef __PL_WINDOWS__
	if(p->h_main_thread_done != NULL) {
		bret = CloseHandle(p->h_main_thread_done);
		if(bret == FALSE) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
		}
		p->h_main_thread_done = NULL;
	}
	if(p->h_admin_port_listener_thread_done != NULL) {
		bret = CloseHandle(p->h_admin_port_listener_thread_done);
		if(bret == FALSE) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
		}
		p->h_admin_port_listener_thread_done = NULL;
	}
	if(p->h_pl_port_listener_thread_done != NULL) {
		bret = CloseHandle(p->h_pl_port_listener_thread_done);
		if(bret == FALSE) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
		}
		p->h_pl_port_listener_thread_done = NULL;
	}
	for(i = 0; i < p->threads_in_pool_value; i++) {
		if(p->h_pool_threads_do[i] != NULL) {
			bret = CloseHandle(p->h_pool_threads_do[i]);
			if(bret == FALSE) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
			}
			p->h_pool_threads_do[i] = NULL;
		}
		if(p->h_pool_threads_done[i] != NULL) {
			bret = CloseHandle(p->h_pool_threads_done[i]);
			if(bret == FALSE) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
			}
			p->h_pool_threads_done[i] = NULL;
		}
		if(p->pool_threads_data[i].semaphore != NULL) {
			bret = CloseHandle(
				p->pool_threads_data[i].semaphore
			);
			if(bret == FALSE) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
			}
			p->pool_threads_data[i].semaphore = NULL;
		}
	} // for i
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	ret = sem_destroy(
		&p->h_main_thread_done
	);
	if(ret == -1) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
	}
	ret = sem_destroy(
		&p->h_admin_port_listener_thread_done
	);
	if(ret == -1) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
	}
	ret = sem_destroy(
		&p->h_pl_port_listener_thread_done
	);
	if(ret == -1) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
	}
	for(i = 0; i < p->threads_in_pool_value; i++) {
		ret = sem_destroy(
			&p->h_pool_threads_do[i]
		);
		if(ret == -1) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
		}
		ret = sem_destroy(
			&p->h_pool_threads_done[i]
		);
		if(ret == -1) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
		}

		ret = sem_destroy(
			&p->pool_threads_data[i].semaphore
		);
		if(ret == -1) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
		}
	} // for i
#else // __PL_MACOSX__
	ret = sem_unlink(
		p->main_thread_done_sem_name
	);
	if(ret == -1) { 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
	}
	ret = sem_unlink(
		p->admin_port_listener_thread_done_sem_name
	);
	if(ret == -1) { 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
	}
	ret = sem_unlink(
		p->pl_port_listener_thread_done_sem_name
	);
	if(ret == -1) { 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
	}
	for(i = 0; i < p->threads_in_pool_value; i++) {
		ret = sem_unlink(
			p->pool_threads_do_sem_names[i]
		);
		if(ret == -1) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
		}
		ret = sem_unlink(
			p->pool_threads_done_sem_names[i]
		);
		if(ret == -1) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT);
		}
	} // for i
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// De-allocate pool thread data.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_DESTROYING_THREAD_POOL_DATA_STRING
	);
	memory_size = sizeof(PL_AGENT_POOL_THREADS_DATA) * p->threads_in_pool_value;
	if(p->pool_threads_data != NULL) {
		memset(
			p->pool_threads_data, 
			0, 
			memory_size
		);
		free(p->pool_threads_data);
		p->pool_threads_data = NULL;
	}

#ifdef __PL_WINDOWS__
	memory_size = sizeof(HANDLE) * p->threads_in_pool_value;
	if(p->h_pool_threads != NULL) {
		memset(
			p->h_pool_threads, 
			0, 
			memory_size
		);
		free(p->h_pool_threads);
		p->h_pool_threads = NULL;
	}

	if(p->h_pool_threads_do != NULL) {
		memset(
			p->h_pool_threads_do, 
			0, 
			memory_size
		);
		free(p->h_pool_threads_do);
		p->h_pool_threads_do = NULL;
	}

	if(p->h_pool_threads_done != NULL) {
		memset(
			p->h_pool_threads_done, 
			0, 
			memory_size
		);
		free(p->h_pool_threads_done);
		p->h_pool_threads_done = NULL;
	}

	if(p->pool_threads_ids != NULL) {
		memset(
			p->pool_threads_ids, 
			0, 
			sizeof(DWORD) * p->threads_in_pool_value
		);
		free(p->pool_threads_ids);
		p->pool_threads_ids = NULL;
	}
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	if(p->h_pool_threads != NULL) {
		memset(
			p->h_pool_threads, 
			0, 
			sizeof(pthread_t) * p->threads_in_pool_value
		);
		free(p->h_pool_threads);
		p->h_pool_threads = NULL;
	}
#ifndef __PL_MACOSX__
	if(p->h_pool_threads_done != NULL) {
		memset(
			p->h_pool_threads_done, 
			0, 
			sizeof(sem_t) * p->threads_in_pool_value
		);
		free(p->h_pool_threads_done);
		p->h_pool_threads_done = NULL;
	}
#else // __PL_MACOSX__
	if(p->h_pool_threads_done != NULL) {
		memset(
			p->h_pool_threads_done, 
			0, 
			sizeof(sem_t *) * p->threads_in_pool_value
		);
		free(p->h_pool_threads_done);
		p->h_pool_threads_done = NULL;
	}
	if(p->pool_threads_done_sem_names != NULL) {
		for(i = 0; i < p->threads_in_pool_value; i++) {
			if(p->pool_threads_done_sem_names[i] != NULL) {
				memset(
					&p->pool_threads_done_sem_names[i], 
					0, 
					sizeof(char) * (SEMAPHORE_NAME_MAX_SIZE + 1)
				);
				free(p->pool_threads_done_sem_names[i]);
				p->pool_threads_done_sem_names[i] = NULL;
			}
		}
		free(p->pool_threads_done_sem_names);
		p->pool_threads_done_sem_names = NULL;
	}
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// de-initialize winsok.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_DEINIT_SOCKET_STRING
	);
	ret = WSACleanup();
	if(ret != 0) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_TEARDOWN_SOCKET);
	}
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// Close PLs that might still be opened (due to dead clients).
	//-------------------------------------------------------------------------
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
	for(i = 0; i < PL_MAX_PRODUCTIVITY_LINKS; i++) {
		if(pl_table.pl_array[i].pl_in_use != 0) {
			ret = pl_close(i);
			if(ret != PL_SUCCESS) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_PL_CLOSE);
			}
		}
	}
#else // !__PL_DYNAMIC_TABLE_ALLOCATION__
	if(pl_table.pl_array != NULL) {
		for(i = 0; i < (int)pl_max_productivity_links; i++) {
			if(
				(&pl_table.pl_array[i] != NULL) &&
				(pl_table.pl_array[i].pl_in_use != 0)
			) {
				ret = pl_close(i);
				if(ret != PL_SUCCESS) {
					// Critial error - error routine will try to stop the agent.
					PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_PL_CLOSE);
				}
			}
		}
	}
#endif // !__PL_DYNAMIC_TABLE_ALLOCATION__

#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__

	//-------------------------------------------------------------------------
	// de-allocate PL_TABLE.
	//-------------------------------------------------------------------------
	free(pl_table.pl_array);
	pl_table.pl_array = NULL;
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__

main_return:
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_ENDED_STRING
	);
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: pl_agent_cli_parser
Purpose : parse the cli
In      : main's arguments
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
03/22/2010    Jamel Tayeb             Creation.
*/
PL_STATUS pl_agent_cli_parser(PPL_AGENT_DATA px, int argc, char *argv[]) {

	//-------------------------------------------------------------------------
	// Generic variables
	//-------------------------------------------------------------------------
	int i = 0;
	int t = 0;
	size_t s_length = 0;
	size_t t_length = 0;
	char s[PL_MAX_PATH] = { '\0' };

	//-------------------------------------------------------------------------
	// Options variables
	//-------------------------------------------------------------------------
	char *help[PL_AGENT_HELP_PL_AGENT_DEBUG_MESSAGE_LINES_COUNT] = { 
		PL_AGENT_HELP_PL_AGENT_DEBUG_MESSAGE_LINES 
	};
	char *cli_tokens[PL_AGENT_CLI_MAX_TOKENS] = { 
		PL_AGENT_CLI_HELP, 
		PL_AGENT_VERSION, 
		PL_AGENT_ADMIN_PORT,
		PL_AGENT_PL_PORT,
		PL_AGENT_THREADS_IN_POOL,
		PL_AGENT_ENCRYPT
	};

	//-------------------------------------------------------------------------
	// Agent data pointer
	//-------------------------------------------------------------------------
	PPL_AGENT_DATA p = NULL;

	assert(px != NULL);
	p = (PPL_AGENT_DATA)px;

	//-------------------------------------------------------------------------
	// parse cli and setup PESRV structure.
	//-------------------------------------------------------------------------
	for(i = 1; i < argc; i++) { // for each argument on the cli
		memset(
			s, 
			0, 
			sizeof(s)
		);
		s_length = strlen(argv[i]);
		strncpy(
			s, 
			argv[i], 
			s_length
		);
		plh_upper_string(s);
		// for each possible cli token
		for(t = 0; t < PL_AGENT_CLI_MAX_TOKENS; t++) { 
			t_length = strlen(cli_tokens[t]);
			if(
				(s_length == t_length) &&
				(strncmp(
					s, 
					cli_tokens[t], 
					t_length
				) == 0)
			) {
				switch(t) {

					case PL_AGENT_ENCRYPT_TOKEN_ID:

						//-----------------------------------------------------
						// process --encrypt option
						//-----------------------------------------------------
						p->f_encrypt = 1;
						goto pl_agent_cli_parser_exit;
						break;

					case PL_AGENT_VERSION_TOKEN_ID:

						//-----------------------------------------------------
						// process --version option
						//-----------------------------------------------------
						print_version_info(
							PL_AGENT_NAME, 
							PL_AGENT_VERSION_MAJOR, 
							PL_AGENT_VERSION_MINOR, 
							PL_AGENT_VERSION_REVISION
						);
						p->f_version_requested = 1;
						goto pl_agent_cli_parser_exit;
						break;

					case PL_AGENT_CLI_HELP_TOKEN_ID:

						//-----------------------------------------------------
						// process --help option and exit
						//-----------------------------------------------------
						for(
							i = 0; 
							i < PL_AGENT_HELP_PL_AGENT_DEBUG_MESSAGE_LINES_COUNT; 
							i++
						) {
							fprintf(stdout, "%s", help[i]);
						}
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
						fprintf(stdout, "\n");
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

						p->f_help_requested = 1;
						goto pl_agent_cli_parser_exit;
						break;

					case PL_AGENT_ADMIN_PORT_TOKEN_ID:

						//-----------------------------------------------------
						// process --admin_port option.
						//-----------------------------------------------------
						if(argc >= i + 1) { // Is there another token?
							i++;
							p->admin_port_string = argv[i];
							p->admin_port_value = atoi(argv[i]);
							if(
								(
									p->admin_port_value < 
									PL_AGENT_DYNAMIC_PRIVATE_PORT_BEGIN
								) ||
								(
									p->admin_port_value > 
									PL_AGENT_DYNAMIC_PRIVATE_PORT_END
								)
							) {
								goto pl_agent_cli_parser_error;
							}
							p->f_admin_port = 1;
							goto pl_agent_cli_parser_skip;
						} else {
							goto pl_agent_cli_parser_error;
						}
						break;

					case PL_AGENT_PL_PORT_TOKEN_ID:

						//-----------------------------------------------------
						// process --pl_port option.
						//-----------------------------------------------------
						if(argc >= i + 1) { // Is there another token?
							i++;
							p->pl_port_string = argv[i];
							p->pl_port_value = atoi(argv[i]);
							if(
								(
									p->pl_port_value < 
									PL_AGENT_DYNAMIC_PRIVATE_PORT_BEGIN
								) ||
								(
									p->pl_port_value > 
									PL_AGENT_DYNAMIC_PRIVATE_PORT_END
								)
							) {
								goto pl_agent_cli_parser_error;
							}
							p->f_pl_port = 1;
							goto pl_agent_cli_parser_skip;
						} else {
							goto pl_agent_cli_parser_error;
						}
						break;


					case PL_AGENT_THREADS_IN_POOL_TOKEN_ID:

						//-----------------------------------------------------
						// process --threads_in_pool option.
						//-----------------------------------------------------
						if(argc >= i + 1) { // Is there another token?
							i++;
							p->threads_in_pool_value = atoi(argv[i]);
							if(
								(
									p->threads_in_pool_value < 
									PL_AGENT_MIN_THREADS_IN_POOL
								) ||
								(
									p->threads_in_pool_value > 
									PL_AGENT_MAX_THREADS_IN_POOL
								)
							) {
								p->threads_in_pool_value = 
									PL_AGENT_DEFAULT_THREADS_IN_POOL
								;
							}
							p->f_threads_in_pool = 1;
							goto pl_agent_cli_parser_skip;
						} else {
							goto pl_agent_cli_parser_error;
						}
						break;

					default:
						break;
				}
			}
		} // for t

pl_agent_cli_parser_skip:
		;
	} // for i

pl_agent_cli_parser_exit:

	return(PL_SUCCESS);
pl_agent_cli_parser_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: pl_agent_error
Purpose : print error message and exit with error code
In      : error code, pointer to a string and an integer
          the string pointer and integer are automatically appended to the 
		  function call using __FILE__ and __LINE__ compiler defined macros.
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
03/22/2010    Jamel Tayeb             Creation.
*/
void pl_agent_error(PL_AGENT_ERROR_CODE e, char *f, int l) {

	char *p = NULL;
	int f_continue = 0;
	char time_stamp_buffer[PL_MAX_PATH] = { '\0' };
	char error_message_buffer[PL_MAX_PATH] = { '\0' };
	char line_buffer[PL_MAX_PATH * 2] = { '\0' };
	PL_STATUS ret = PL_FAILURE;

#if defined (_DEBUG) || (__PL_DEBUG__)
	char tmp_buffer[PL_MAX_PATH] = { '\0' };
	assert(f != NULL);
#endif // _DEBUG || __PL_DEBUG__

	switch(e) {

		//---------------------------------------------------------------------
		// No erro error.
		//---------------------------------------------------------------------
		case PL_AGENT_NO_ERROR:
			p = PL_AGENT_NO_ERROR_STRING;
			f_continue = 1;
			break;

		//---------------------------------------------------------------------
		// System errors.
		//---------------------------------------------------------------------
		case PL_AGENT_UNABLE_TO_STOP_AGENT:
			p = PL_AGENT_UNABLE_TO_STOP_AGENT_STRING;
			break;
		case PL_AGENT_UNABLE_TO_CREATE_UUID:
			p = PL_AGENT_UNABLE_TO_CREATE_UUID_STRING;
			break;
		case PL_AGENT_INVALID_USER_INPUT:
			p = PL_AGENT_INVALID_USER_INPUT_STRING;
			break;
		case PL_AGENT_INVALID_MESSAGE_DATA:
			p = PL_AGENT_INVALID_MESSAGE_DATA_STRING;
			break;
		case PL_AGENT_UNABLE_TO_ACTIVATE_MEMORY_LEAK_DETECTION:
			p = PL_AGENT_UNABLE_TO_ACTIVATE_MEMORY_LEAK_DETECTION_STRING;
			break;
		case PL_AGENT_UNABLE_TO_INSTALL_SIGNAL_HANDLER:
			p = PL_AGENT_UNABLE_TO_INSTALL_SIGNAL_HANDLER_STRING;
			break;
		case PL_AGENT_OUT_OF_MEMORY:
			p = PL_AGENT_OUT_OF_MEMORY_STRING;
			break;
		case PL_AGENT_OUT_OF_BUFFER_SPACE:
			p = PL_AGENT_OUT_OF_MEMORY_STRING;
			break;
		case PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT:
			p = PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT_STRING;
			break;
		case PL_AGENT_UNABLE_TO_CREATE_THREAD:
			p = PL_AGENT_UNABLE_TO_CREATE_THREAD_STRING;
			break;
		case PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT:
			p = PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT_STRING;
			break;

		//---------------------------------------------------------------------
		// IPC errors.
		//---------------------------------------------------------------------
		case PL_AGENT_UNABLE_TO_INITIALIZE_SOCKET:
			p = PL_AGENT_UNABLE_TO_INITIALIZE_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_TEARDOWN_SOCKET:
			p = PL_AGENT_UNABLE_TO_TEARDOWN_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_GET_HOST_STRUCTURE_FROM_HOSTNAME:

			//-----------------------------------------------------------------
			// Note: This error may occure at starup only, so we continue 
			// even if it critical, so we can end clean.
			//-----------------------------------------------------------------
			p = PL_AGENT_UNABLE_TO_GET_HOST_STRUCTURE_FROM_HOSTNAME_STRING;
			f_continue = 1;
			break;
		case PL_AGENT_UNABLE_TO_CONVERT_ADDRESS_STRING_INTO_STRUCTURE:

			//-----------------------------------------------------------------
			// Note: This error may occure at starup only, so we continue 
			// even if it critical, so we can end clean.
			//-----------------------------------------------------------------
			p = PL_AGENT_UNABLE_TO_CONVERT_ADDRESS_STRING_INTO_STRUCTURE_STRING;
			f_continue = 1;
			break;
		case PL_AGENT_UNABLE_TO_GET_ADDRESS_INFO:
			p = PL_AGENT_UNABLE_TO_GET_ADDRESS_INFO_STRING;
			break;
		case PL_AGENT_UNABLE_TO_CREATE_SOCKET:
			p = PL_AGENT_UNABLE_TO_CREATE_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_CLOSE_SOCKET:
			p = PL_AGENT_UNABLE_TO_CLOSE_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_CONNECT_TO_SOCKET:
			p = PL_AGENT_UNABLE_TO_CONNECT_TO_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_SEND_VIA_SOCKET:
			p = PL_AGENT_UNABLE_TO_SEND_VIA_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_SHUTDOWN_SOCKET:
			p = PL_AGENT_UNABLE_TO_SHUTDOWN_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_SET_SOCKET_OPTIONS:
			p = PL_AGENT_UNABLE_TO_SET_SOCKET_OPTIONS_STRING;
			break;
		case PL_AGENT_UNABLE_TO_LISTEN_SOCKET:
			p = PL_AGENT_UNABLE_TO_LISTEN_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_ACCEPT_SOCKET:
			p = PL_AGENT_UNABLE_TO_ACCEPT_SOCKET_STRING;
			break;
		case PL_AGENT_UNABLE_TO_RECEIVE_FROM_SOCKET:
			p = PL_AGENT_UNABLE_TO_RECEIVE_FROM_SOCKET_STRING;
			break;

		//---------------------------------------------------------------------
		// PL protocol errors.
		//---------------------------------------------------------------------
		case PL_AGENT_PROTOCOL_ERROR:
			p = PL_AGENT_PROTOCOL_ERROR_STRING;
			f_continue = 1;
			break;
		case PL_AGENT_PROTOCOL_UNKNOWN_OP_CODE:
			p = PL_AGENT_PROTOCOL_UNKNOWN_OP_CODE_STRING;
			f_continue = 1;
			break;

		//---------------------------------------------------------------------
		// PL API errors.
		//---------------------------------------------------------------------
		case PL_AGENT_UNABLE_TO_PL_OPEN:
			p = PL_AGENT_UNABLE_TO_PL_OPEN_STRING;
			f_continue = 1;
			break;
		case PL_AGENT_UNABLE_TO_PL_ATTACH:
			p = PL_AGENT_UNABLE_TO_PL_ATTACH_STRING;
			f_continue = 1;
			break;
		case PL_AGENT_UNABLE_TO_PL_CLOSE:
			p = PL_AGENT_UNABLE_TO_PL_CLOSE_STRING;
			f_continue = 1;
			break;
		case PL_AGENT_UNABLE_TO_PL_READ:
			p = PL_AGENT_UNABLE_TO_PL_READ_STRING;
			f_continue = 1;
			break;
		case PL_AGENT_UNABLE_TO_PL_WRITE:
			p = PL_AGENT_UNABLE_TO_PL_WRITE_STRING;
			f_continue = 1;
			break;

		default:
			assert(0); // Should never happen, trap it!
			break;

	} // switch

	agent_data.errors_count++;

	//-------------------------------------------------------------------------
	// Time-stamp and print the error message.
	//-------------------------------------------------------------------------
	memset(
		time_stamp_buffer, 
		0, 
		sizeof(time_stamp_buffer)
	);
	service_time_stamp(time_stamp_buffer);
	memset(
		line_buffer, 
		0, 
		sizeof(line_buffer)
	);
	strncpy(
		line_buffer, 
		time_stamp_buffer, 
		strlen(time_stamp_buffer)
	);
	memset(
		error_message_buffer, 
		0, 
		sizeof(error_message_buffer)
	);

#if defined (_DEBUG) || (__PL_DEBUG__)
	sprintf(
		error_message_buffer, 
		"ERROR: %d - %s [%s]:[%d]", 
		e, 
		p, 
		f, 
		l
	);
#else // _DEBUG || __PL_DEBUG__
	sprintf(
		error_message_buffer, 
		"ERROR: %s", 
		p
	);
#endif // _DEBUG || __PL_DEBUG__

	strncat(
		line_buffer, 
		error_message_buffer, 
		strlen(error_message_buffer)
	);

	//-------------------------------------------------------------------------
	// Display error message.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__	
	fprintf(
		stderr, 
		"%s\n", 
		line_buffer
	);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	fprintf(
		stderr, 
		"%s\n", 
		line_buffer
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	fflush(stderr);

	//-------------------------------------------------------------------------
	// End program if critial error.
	//-------------------------------------------------------------------------
	if(f_continue == 0) {

		//---------------------------------------------------------------------
		// Interrupt agent and echo.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_INTERRUPT_GENERATED_PL_AGENT_DEBUG_MESSAGE_STRING
		);
		f_running = 0;
		ret = stop_agent(&agent_data);
		if(ret != PL_SUCCESS) {
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_STOP_AGENT);
			assert(0);
		}
	}
}

/*-----------------------------------------------------------------------------
Function: pl_agent_message
Purpose : time stamp and print a message
In      : pointer to message string
Out     : none
Return  : number of characters printed.

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
03/22/2010    Jamel Tayeb             Creation.
*/
size_t pl_agent_message(char *m, char *s) {

	char time_stamp_buffer[PL_MAX_PATH] = { '\0' };
	char message_buffer[PL_PROTOCOL_MESSAGE_MAX_SIZE] = { '\0' };
	char line_buffer[PL_PROTOCOL_MESSAGE_MAX_SIZE] = { '\0' };
	int characters_printed = 0;

	assert(m != NULL);

	memset(
		time_stamp_buffer, 
		0, 
		sizeof(time_stamp_buffer)
	);
	service_time_stamp(time_stamp_buffer);
	memset(
		line_buffer, 
		0, 
		sizeof(line_buffer)
	);
	strncpy(
		line_buffer, 
		time_stamp_buffer, 
		strlen(time_stamp_buffer)
	);
	memset(
		message_buffer, 
		0, 
		sizeof(message_buffer)
	);
	if(s != NULL) {
		sprintf(
			message_buffer, 
			m, 
			s
		);
	} else {
		sprintf(
			message_buffer, 
			"%s", 
			m
		);
	}
	strncat(
		line_buffer, 
		message_buffer, 
		strlen(message_buffer)
	);
	characters_printed = fprintf(
		stdout, 
		"%s", 
		line_buffer
	);
	fflush(stdout);
	return(characters_printed);
}

/*---------------------------------------------------------------------------
Function: service_time_stamp
Purpose : add a time stamp into received buffer. 
In      : pointer to a large-enough buffer (SERVICES_PL_AGENT_DEBUG_MESSAG...
          ...E_TIME_STAMP_BUFFER_SIZE).
Out     : none
Return  : status

History
----------------------------------------------------------------------------
Date        : Author                  Modification
----------------------------------------------------------------------------
08/10/2009    Jamel Tayeb             Creation.
*/
PL_STATUS service_time_stamp(char *buffer) {

	char time_buffer[
		SERVICES_PL_AGENT_DEBUG_MESSAGE_TIME_STAMP_BUFFER_SIZE
	] = { '\0' };
	time_t log_time;
	size_t length = 0;
	
	assert(time_buffer != NULL);

	//-----------------------------------------------------------------------
	// collect time information and convert it into text
	//-----------------------------------------------------------------------
	memset(
		time_buffer, 
		0, 
		sizeof(time_buffer)
	);

#ifdef __PL_WINDOWS__
	time(&log_time);
	ctime_s(
		time_buffer, 
		sizeof(time_buffer), 
		&log_time
	);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	time(&log_time);
#ifdef __PL_SOLARIS__
	ctime_r(
		&log_time, 
		time_buffer, 
		TIME_STAMP_BUFFER_SIZE
	);
#else // __PL_SOLARIS__
	ctime_r(
		&log_time, 
		time_buffer
	);
#endif // __PL_SOLARIS__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-----------------------------------------------------------------------
	// errase newline added by libc in time buffer
	//-----------------------------------------------------------------------
	length = strlen(time_buffer) - 1;
	time_buffer[length] = '\0';

	//-----------------------------------------------------------------------
	// build the log buffer
	//-----------------------------------------------------------------------
	memset(
		buffer, 
		0, 
		sizeof(buffer)
	);
	strncpy(
		buffer, 
		SERVICES_PL_AGENT_DEBUG_MESSAGE_TIME_STAMP_BEGIN, 
		strlen(SERVICES_PL_AGENT_DEBUG_MESSAGE_TIME_STAMP_BEGIN)
	);
	strncat(
		buffer, 
		time_buffer, 
		strlen(time_buffer)
	);
	strncat(
		buffer, 
		SERVICES_PL_AGENT_DEBUG_MESSAGE_TIME_STAMP_END, 
		strlen(SERVICES_PL_AGENT_DEBUG_MESSAGE_TIME_STAMP_END)
	);
	
	return(PL_SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: signal_handler
Purpose : replicator interrupt signal handler
In      : none
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
03/22/2010    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
BOOL signal_handler(DWORD c) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
void signal_handler(int c) { 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	PL_STATUS ret = PL_FAILURE;
	static int f_interrupted = 0;

#if defined (_DEBUG) || (__PL_DEBUG__)
	char tmp_buffer[PL_MAX_PATH] = { '\0' };
#endif // _DEBUG || __PL_DEBUG__

	switch(c) { 

#ifdef __PL_WINDOWS__
		case CTRL_C_EVENT:
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		case SIGINT:
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			//-----------------------------------------------------------------
			// Interrupt agent and echo.
			//-----------------------------------------------------------------
			f_running = 0;
			if(f_interrupted == 0) {
				PL_AGENT_DEBUG_MESSAGE(
					PL_AGENT_INTERRUPT_RECEIVED_PL_AGENT_DEBUG_MESSAGE_STRING
				);
				f_interrupted = 1;
				ret = stop_agent(&agent_data);
				if(ret != PL_SUCCESS) {
					PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_STOP_AGENT);
					assert(0);
				}
			}
#ifdef __PL_WINDOWS__
			return(TRUE);

		default: 
			return(FALSE);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			break;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	} 
}

/*-----------------------------------------------------------------------------
Function: stop_agent
Purpose : stop the agent by unlocking all waiting threads.
In      : pointer to agent data
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
03/22/2010    Jamel Tayeb             Creation.
*/
extern PL_STATUS stop_agent(PPL_AGENT_DATA p) {

	//-------------------------------------------------------------------------
	// Generic data.
	//-------------------------------------------------------------------------
	int i = 0;
	PL_STATUS ret = PL_FAILURE;

#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// Data used to manage IPC.
	//-------------------------------------------------------------------------
	PL_AGENT_IPC_DATA ipc_data;

#ifdef __PL_WINDOWS__
	ADDRINFO *pa = NULL;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	char port[PL_AGENT_IPC_SOCKET_MAX_PORT_NAME_SIZE] = { '\0' };
	struct addrinfo *pa = NULL;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef _DEBUG

	//-------------------------------------------------------------------------
	// Data used to display messages.
	//-------------------------------------------------------------------------
	char tmp_buffer[PL_MAX_PATH] = { '\0' };
#endif // _DEBUG

	//-------------------------------------------------------------------------

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Interrupt agent and echo.
	//-------------------------------------------------------------------------
	f_running = 0;

	//-------------------------------------------------------------------------
	// Signal pool threads to unlock them.
	//-------------------------------------------------------------------------
	for(i = 0; i < p->threads_in_pool_value; i++) {
		PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
			PL_AGENT_DEBUG_MESSAGE_AGENT_SIGNALING_POOL_THREAD_N_STRING, 
			i
		);
#ifdef __PL_WINDOWS__
		if(p->h_pool_threads_do[i] != NULL) {
			bret = SetEvent(
				p->h_pool_threads_do[i]
			);
			if(bret == FALSE) {
				goto stop_agent_error;
			}
		}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		ret = sem_post(
			&p->h_pool_threads_do[i]
		);
#else // __PL_MACOSX__
		ret = sem_post(
			p->h_pool_threads_do[i]
		);
#endif // __PL_MACOSX__
		if(ret != 0) {
			goto stop_agent_error;
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	} // for i

	//-------------------------------------------------------------------------
	// Signal ADMIN port listener thread to unlock it.
	// Note:
	//    Signaling these threads cannot be done using a signal since 
	//    they are blocked on a blocking socket read.  This must be 
	//    done via an IPC write.
	// Note:
	//    We send an "empty" message since we just want to unlock the
	//    ADMIN port listening threads - which will exit gracefuly 
	//    since the agent flag was cleared.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_SIGNALING_ADMIN_THREAD_STRING
	);

	//-------------------------------------------------------------------------
	// clear and initialize the address info hint structure and sockets
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_SETUP_ADMIN_PORT_IPC_STRING
	);
	memset(
		&ipc_data,
		0,
		sizeof(ipc_data)
	);
	ipc_data.socket = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Setup socket data, start with address...
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_SETUP_ADMIN_SOCKET_DATA_STRING
	);
	if(p->ip_address != NULL) {
		strncpy(
			ipc_data.node_name,
			p->ip_address, 
			strlen(p->ip_address)
		);
	} else {
		strncpy(
			ipc_data.node_name,
			PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME, 
			strlen(PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME)
		);
	}

	//-------------------------------------------------------------------------
	// ...continue with port number
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	memset(
		ipc_data.port, 
		0, 
		sizeof(ipc_data.port)
	);
	if(
		(p->f_admin_port == 1) && 
		(p->admin_port_string != NULL)
	) {
		strncpy(
			ipc_data.port, 
			p->admin_port_string, 
			strlen(p->admin_port_string)
		);
	} else {
		strncpy(
			ipc_data.port, 
			PL_DEFAULT_PL_AGENT_ADMIN_PORT, 
			strlen(PL_DEFAULT_PL_AGENT_ADMIN_PORT)
		);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	if(p->f_admin_port == 1) {
		ipc_data.port = p->admin_port_value;
	} else {
		ipc_data.port = PL_DEFAULT_PL_AGENT_ADMIN_PORT;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// set the address info hint structure
	//-------------------------------------------------------------------------
	ipc_data.address_info_hint.ai_family = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FAMILY
	;
	ipc_data.address_info_hint.ai_socktype = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	ipc_data.address_info_hint.ai_protocol = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	ipc_data.address_info_hint.ai_flags = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve address and port.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_RESOLVING_ADMIN_ADDRESS_PORT_STRING
	);
#ifdef __PL_WINDOWS__
	ret = getaddrinfo(
		ipc_data.node_name, 
		ipc_data.port, 
		&ipc_data.address_info_hint, 
		&ipc_data.address_info
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	sprintf(
		port, 
		"%d", 
		ipc_data.port
	);
	ret = getaddrinfo(
		ipc_data.node_name, 
		port, 
		(const struct addrinfo *)&ipc_data.address_info_hint, 
		(struct addrinfo **)&ipc_data.address_info
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	if(ret != 0) {
		goto stop_agent_error;
	}

	//-------------------------------------------------------------------------
	// Attempt to connect to the server address - untill one succeds.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_CONNCECTING_TO_ADMIN_PORT_STRING
	);
	for(
		pa = (struct addrinfo *)ipc_data.address_info; 
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the server
		//---------------------------------------------------------------------
		ipc_data.socket = socket(
			pa->ai_family, 
			pa->ai_socktype, 
			pa->ai_protocol
		);
		if(ipc_data.socket == INVALID_SOCKET) { 
			goto stop_agent_error;
		}

		//---------------------------------------------------------------------
		// Connect to the ADMIN listener thrad.
		//---------------------------------------------------------------------
		ret = connect(
			ipc_data.socket, 
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) { 
			
			//-----------------------------------------------------------------
			// Failed to connect to the ADMIN listener thread on 
			// this address, let's close the socket.
			//-----------------------------------------------------------------
#ifdef __PL_WINDOWS__
			ret = closesocket(
				ipc_data.socket
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			ret = close(
				ipc_data.socket
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			if(ret == SOCKET_ERROR) { 
				goto stop_agent_error;
			}
			
			//-----------------------------------------------------------------
			// Mark the socket as invalid before trying a new address.
			//-----------------------------------------------------------------
			ipc_data.socket = INVALID_SOCKET;
			continue;
		}
		goto signal_handler_connected_to_admin;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	//-------------------------------------------------------------------------
	goto stop_agent_error;

signal_handler_connected_to_admin:

	//-------------------------------------------------------------------------
	// Note:
	//    No need to send any data to the ADMIN port listener thread.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Disconnect from ADMIN listener thread.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_DISCONNECTING_FROM_ADMIN_PORT_STRING
	);
	ret = shutdown(
		ipc_data.socket, 
		SD_BOTH
	);
#ifdef __PL_WINDOWS__
	if(ret == SOCKET_ERROR) { 
		goto stop_agent_error;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	if(ret == SOCKET_ERROR) {
#ifdef __PL_MACOSX__

		//---------------------------------------------------------------------
		// Note: 
		//    Under MacOS X, it is not possible to shutdown a socket
		//    when it was closed by the server (errno = ENOTCONN (57)).
		//---------------------------------------------------------------------
		if(errno != ENOTCONN) { 
			goto stop_agent_error;
		}
#else // __PL_MACOSX__
		goto stop_agent_error;
#endif // __PL_MACOSX__
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Tear-down IPC
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_TEARDOWN_ADMIN_IPC_STRING
	);
	if(ipc_data.socket != INVALID_SOCKET) {

		//---------------------------------------------------------------------
		// Close socket
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		ret = closesocket(
			ipc_data.socket
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = close(
			ipc_data.socket
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		if(ret == SOCKET_ERROR) {
			goto stop_agent_error;
		}
		ipc_data.socket = INVALID_SOCKET;

		//---------------------------------------------------------------------
		// Free socket ressources
		//---------------------------------------------------------------------
		if(ipc_data.address_info != NULL) {
#ifdef __PL_WINDOWS__
			freeaddrinfo(
				ipc_data.address_info
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			freeaddrinfo(
				(struct addrinfo *)
					ipc_data.address_info
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		}
	}

	//-------------------------------------------------------------------------
	// Signal PL port listener thread to unlock it.
	// Note:
	//    Signaling these threads cannot be done using a signal since they are 
	//    blocked on a blocking socket read. This must be done via an IPC write.
	// Note:
	//    We send an "empty" message since we just want to unlock the PL 
	//    port listening threads - which will exit gracefuly since the agent 
	//    flag was cleared.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_SIGNALING_PL_PORT_THREAD_STRING
	);

	//-------------------------------------------------------------------------
	// clear and initialize the address info hint structure and sockets
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_SETUP_PL_PORT_IPC_STRING
	);
	memset(
		&ipc_data,
		0,
		sizeof(ipc_data)
	);
	ipc_data.socket = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Setup socket data, start with address...
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_SETUP_PL_SOCKET_DATA_STRING
	);
	if(p->ip_address != NULL) {
		strncpy(
			ipc_data.node_name,
			p->ip_address, 
			strlen(p->ip_address)
		);
	} else {
		strncpy(
			ipc_data.node_name,
			PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME, 
			strlen(PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME)
		);
	}

	//-------------------------------------------------------------------------
	// ...continue with port number
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	memset(
		ipc_data.port, 
		0, 
		sizeof(ipc_data.port)
	);
	if(
		(p->f_pl_port == 1) && 
		(p->pl_port_string != NULL)
	) {
		strncpy(
			ipc_data.port, 
			p->pl_port_string, 
			strlen(p->pl_port_string)
		);
	} else {
		strncpy(
			ipc_data.port, 
			PL_DEFAULT_PL_AGENT_PL_PORT, 
			strlen(PL_DEFAULT_PL_AGENT_PL_PORT)
		);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	if(p->f_pl_port == 1) {
		ipc_data.port = p->pl_port_value;
	} else {
		ipc_data.port = PL_DEFAULT_PL_AGENT_PL_PORT;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// set the address info hint structure
	//-------------------------------------------------------------------------
	ipc_data.address_info_hint.ai_family = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FAMILY
	;
	ipc_data.address_info_hint.ai_socktype = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	ipc_data.address_info_hint.ai_protocol = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	ipc_data.address_info_hint.ai_flags = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve address and port.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_RESOLVING_PL_PORT_ADDRESS_PORT_STRING
	);
#ifdef __PL_WINDOWS__
	ret = getaddrinfo(
		ipc_data.node_name, 
		ipc_data.port, 
		&ipc_data.address_info_hint, 
		&ipc_data.address_info
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	sprintf(
		port, 
		"%d", 
		ipc_data.port
	);
	ret = getaddrinfo(
		ipc_data.node_name, 
		port, 
		(const struct addrinfo *)&ipc_data.address_info_hint, 
		(struct addrinfo **)&ipc_data.address_info
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	if(ret != 0) {
		goto stop_agent_error;
	}

	//-------------------------------------------------------------------------
	// Attempt to connect to the server address - untill one succeds.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_CONNCECTING_TO_PL_PORT_STRING
	);
	for(
		pa = (struct addrinfo *)ipc_data.address_info; 
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the server
		//---------------------------------------------------------------------
		ipc_data.socket = socket(
			pa->ai_family, 
			pa->ai_socktype, 
			pa->ai_protocol
		);
		if(ipc_data.socket == INVALID_SOCKET) { 
			goto stop_agent_error;
		}

		//---------------------------------------------------------------------
		// Connect to the PL listener thrad.
		//---------------------------------------------------------------------
		ret = connect(
			ipc_data.socket, 
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) { 
			
			//-----------------------------------------------------------------
			// Failed to connect to the PL listener thread on this address, 
			// let's close the socket.
			//-----------------------------------------------------------------
#ifdef __PL_WINDOWS__
			ret = closesocket(
				ipc_data.socket
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			ret = close(
				ipc_data.socket
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			if(ret == SOCKET_ERROR) { 
				goto stop_agent_error;
			}
			
			//-----------------------------------------------------------------
			// Mark the socket as invalid before trying a new address.
			//-----------------------------------------------------------------
			ipc_data.socket = INVALID_SOCKET;
			continue;
		}
		goto signal_handler_connected_to_pl;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	//-------------------------------------------------------------------------
	goto stop_agent_error;

signal_handler_connected_to_pl:

	//-------------------------------------------------------------------------
	// Note:
	//    No need to send any data to the PL port listener thread.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Disconnect from PL listener thread.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_DISCONNECTING_FROM_PL_PORT_STRING
	);
	ret = shutdown(
		ipc_data.socket, 
		SD_BOTH
	);
#ifdef __PL_WINDOWS__
	if(ret == SOCKET_ERROR) { 
		goto stop_agent_error;
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	if(ret == SOCKET_ERROR) {
#ifdef __PL_MACOSX__

		//---------------------------------------------------------------------
		// Note: 
		//    Under MacOS X, it is not possible to shutdown a socket when it 
		//    was closed by the server (errno = ENOTCONN (57)).
		//---------------------------------------------------------------------
		if(errno != ENOTCONN) { 
			goto stop_agent_error;
		}
#else // __PL_MACOSX__
		goto stop_agent_error;
#endif // __PL_MACOSX__
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Tear-down IPC.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_AGENT_TEARDOWN_PL_IPC_STRING
	);
	if(ipc_data.socket != INVALID_SOCKET) {

		//---------------------------------------------------------------------
		// Close socket.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		ret = closesocket(
			ipc_data.socket
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = close(
			ipc_data.socket
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		if(ret == SOCKET_ERROR) {
			goto stop_agent_error;
		}
		ipc_data.socket = INVALID_SOCKET;

		//---------------------------------------------------------------------
		// Free socket ressources.
		//---------------------------------------------------------------------
		if(ipc_data.address_info != NULL) {
#ifdef __PL_WINDOWS__
			freeaddrinfo(
				ipc_data.address_info
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			freeaddrinfo(
				(struct addrinfo *)
					ipc_data.address_info
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		}
	}

	//-------------------------------------------------------------------------
	// return status
	//-------------------------------------------------------------------------
	return(PL_SUCCESS);
stop_agent_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: admin_port_listener_thread
Purpose : ADMIN port listener thread code.
In      : pointer to pl_agent_data structure
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
06/30/2010    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
LPTHREAD_START_ROUTINE admin_port_listener_thread(void *px) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
void *admin_port_listener_thread(void *px) {
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Generic data.
	//-------------------------------------------------------------------------
	PL_STATUS ret = PL_FAILURE;
	PPL_AGENT_DATA p = NULL;
#ifdef __PL_WINDOWS__
	DWORD dwret = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int iret = -1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Data used to manage IPC.
	//-------------------------------------------------------------------------
	PL_AGENT_IPC_BUFFER input_ipc_buffer = { {'\0'} };
	PL_AGENT_IPC_BUFFER output_ipc_buffer = { {'\0'} };
	PL_PROTOCOL_SIZET message_size = 0;
	int one = 1;
	SOCKET new_socket = INVALID_SOCKET;

#ifdef __PL_WINDOWS__
	ADDRINFO *pa = NULL;
	TCHAR buffer[PL_MAX_PATH] = { '\0' };
	TCHAR temp[PL_MAX_PATH] = { '\0' };
	int bytes_received = 0;
	int bytes_to_receive = 0;
	int total_bytes_to_receive = 0;
	int bytes_sent = 0;
	int bytes_to_send = 0;
	int total_bytes_to_send = 0;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	char port[PL_AGENT_IPC_SOCKET_MAX_PORT_NAME_SIZE] = { '\0' };
	struct addrinfo *pa = NULL;
	size_t bytes_received = 0;
	size_t bytes_to_receive = 0;
	size_t total_bytes_to_receive = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Data used to manage commands.
	//-------------------------------------------------------------------------
	PL_AGENT_COMMAND command;
	ADMIN_COMMAND_CODE command_code = 0;
	int f_found = 0;
	unsigned int index = 0;
	char *input_message = NULL;
	char *output_message = NULL;
	char uuid_buffer[PL_UUID_MAX_CHARS + 1] = { '\0' };
#ifdef __PL_WINDOWS__
	DWORD dw_ret = 0;
	BOOL b_ret = FALSE;
	RPC_STATUS rpc_ret = 0;	
	TCHAR *puuid = NULL;
	size_t st_ret = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef _DEBUG

	//-------------------------------------------------------------------------
	// Data used to display messages.
	//-------------------------------------------------------------------------
	char tmp_buffer[PL_MAX_PATH] = { '\0' };
#endif // _DEBUG

	//-------------------------------------------------------------------------

	p = (PPL_AGENT_DATA)px;
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Wait for main thread done.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_STARTED_STRING
	);
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_WAITING_MAIN_THREAD_DONE_STRING
	);
#ifdef __PL_WINDOWS__
	dwret = WaitForSingleObject(
		p->h_main_thread_done,
		INFINITE
	);
	if(dwret != WAIT_OBJECT_0) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	iret = sem_wait(
		&p->h_main_thread_done
	);
#else // __PL_MACOSX__
	iret = sem_wait(
		p->h_main_thread_done
	);
#endif // __PL_MACOSX__
	if(iret != 0) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_RECEIVED_MAIN_THREAD_DONE_SIGNAL_STRING
	);

	//-------------------------------------------------------------------------
	// Setup IPC for ADMIN port.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SETTING_UP_IPC_STRING
	);
	memset(
		&p->admin_port_listener_thread_ipc_data, 
		0, 
		sizeof(p->admin_port_listener_thread_ipc_data)
	);

	//-------------------------------------------------------------------------
	// Clear and initialize the address info hint structure and socket
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_INITIALIZING_IPC_STRING
	);
	p->admin_port_listener_thread_ipc_data.socket = INVALID_SOCKET;
	memset(
		&p->admin_port_listener_thread_ipc_data.address_info_hint, 
		0, 
		sizeof(p->admin_port_listener_thread_ipc_data.address_info_hint)
	);

	//-------------------------------------------------------------------------
	// Setup socket data, start with address...
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SETTING_UP_SOCKET_DATA_STRING
	);
	memset(
		p->admin_port_listener_thread_ipc_data.node_name, 
		0, 
		sizeof(p->admin_port_listener_thread_ipc_data.node_name)
	);
	if(p->ip_address != NULL) {
		strncpy(
			p->admin_port_listener_thread_ipc_data.node_name, 
			p->ip_address, 
			strlen(p->ip_address)
		);
	} else {
		strncpy(
			p->admin_port_listener_thread_ipc_data.node_name, 
			PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME, 
			strlen(PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME)
		);
	}

	//-------------------------------------------------------------------------
	// ...continue with port number
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	memset(
		p->admin_port_listener_thread_ipc_data.port, 
		0, 
		sizeof(p->admin_port_listener_thread_ipc_data.port)
	);
	if(
		(p->f_admin_port == 1) && 
		(p->admin_port_string != NULL)
	) {
		strncpy(
			p->admin_port_listener_thread_ipc_data.port, 
			p->admin_port_string, 
			strlen(p->admin_port_string)
		);
	} else {
		strncpy(
			p->admin_port_listener_thread_ipc_data.port, 
			PL_DEFAULT_PL_AGENT_ADMIN_PORT, 
			strlen(PL_DEFAULT_PL_AGENT_ADMIN_PORT)
		);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	if(
		(p->f_admin_port == 1) && 
		(p->admin_port_string != NULL)
	) {
		p->admin_port_listener_thread_ipc_data.port = 
			p->admin_port_value;
	} else {
		p->admin_port_listener_thread_ipc_data.port = 
			PL_DEFAULT_PL_AGENT_ADMIN_PORT;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Set the address info hint structure
	//-------------------------------------------------------------------------
	p->admin_port_listener_thread_ipc_data.address_info_hint.ai_family = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FAMILY
	;
	p->admin_port_listener_thread_ipc_data.address_info_hint.ai_socktype = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	p->admin_port_listener_thread_ipc_data.address_info_hint.ai_protocol = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	p->admin_port_listener_thread_ipc_data.address_info_hint.ai_flags = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve address and port
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_RESOLVING_ADDRESS_PORT_STRING
	);
#ifdef __PL_WINDOWS__
	ret = getaddrinfo(
		NULL, 
		p->admin_port_listener_thread_ipc_data.port, 
		&p->admin_port_listener_thread_ipc_data.address_info_hint, 
		&p->admin_port_listener_thread_ipc_data.address_info
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	sprintf(
		port, 
		"%d", 
		p->admin_port_listener_thread_ipc_data.port
	);
	ret = getaddrinfo(
		NULL, 
		port, 
		(const struct addrinfo *)
			&p->admin_port_listener_thread_ipc_data.address_info_hint, 
		(struct addrinfo **)
			&p->admin_port_listener_thread_ipc_data.address_info
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	if(ret != 0) { 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_GET_ADDRESS_INFO);
	}

	//-------------------------------------------------------------------------
	// Attempt to create the socket and bind - untill one succeds
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_CREATING_BINDING_SOCKET_STRING
	);
	for(
		pa = (struct addrinfo *)
			p->admin_port_listener_thread_ipc_data.address_info; 
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the client
		//---------------------------------------------------------------------
		p->admin_port_listener_thread_ipc_data.socket = socket(
			pa->ai_family, 
			pa->ai_socktype, 
			pa->ai_protocol
		);
		if(p->admin_port_listener_thread_ipc_data.socket == INVALID_SOCKET) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SOCKET); 
		}

		//---------------------------------------------------------------------
		// Configure socket
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		ret = setsockopt(
			p->admin_port_listener_thread_ipc_data.socket, 
			SOL_SOCKET, 
			SO_EXCLUSIVEADDRUSE, 
			(char *)&one, 
			sizeof(one)
		);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

		//-------------------------------------------------------------
		// Note: 
		//   SO_EXCLUSIVEADDRUSE is not implemented on *NIX, 
		//    use it as it bocomes available for security reasons.
		//-------------------------------------------------------------
		ret = setsockopt(
			p->admin_port_listener_thread_ipc_data.socket, 
			SOL_SOCKET, 
			SO_REUSEADDR, 
			(char *)&one, 
			sizeof(one)
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		if(ret == SOCKET_ERROR) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SET_SOCKET_OPTIONS);
		}

		//-------------------------------------------------------------
		// Bind
		//-------------------------------------------------------------
#ifdef __PL_WINDOWS__
		ret = bind(
			p->admin_port_listener_thread_ipc_data.socket, 
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = bind(
			p->admin_port_listener_thread_ipc_data.socket, 
			pa->ai_addr, 
			pa->ai_addrlen
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		if(ret == SOCKET_ERROR) {
			
			//-----------------------------------------------------------------
			// Failed to bind to this address, let's close the socket
			//-----------------------------------------------------------------
#ifdef __PL_WINDOWS__
			ret = closesocket(
				p->admin_port_listener_thread_ipc_data.socket
			);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			ret = close(
				p->admin_port_listener_thread_ipc_data.socket
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			if(ret == SOCKET_ERROR) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CLOSE_SOCKET); 
			}
			
			//-----------------------------------------------------------------
			// Mark the socket as invalid before trying a new address
			//-----------------------------------------------------------------
			p->admin_port_listener_thread_ipc_data.socket = INVALID_SOCKET;
			continue;
		}
		goto admin_port_listener_ipc_setup_socket_bound;
	} // for pa

	//-------------------------------------------------------------------------
	// No bind attempt succeded, signal error.
	//-------------------------------------------------------------------------
	// Critial error - error routine will try to stop the agent.
	PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CONNECT_TO_SOCKET);

admin_port_listener_ipc_setup_socket_bound:

	//-------------------------------------------------------------------------
	// Listen
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_LISTENING_SOCKET_STRING
	);
	ret = listen(
		p->admin_port_listener_thread_ipc_data.socket, 
		SOMAXCONN
	);
	if(ret == SOCKET_ERROR) { 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_LISTEN_SOCKET); 
	}

	//-------------------------------------------------------------------------
	// Main loop.
	//-------------------------------------------------------------------------
	while(f_running == 1) {

		//---------------------------------------------------------------------
		// Connect to the ADMIN port and wait (blocking) for an admin request.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_ACCEPTING_CONNECTION_STRING
		);
		new_socket = accept(
			p->admin_port_listener_thread_ipc_data.socket, 
			NULL, 
			NULL
		);
		if(new_socket == INVALID_SOCKET) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_ACCEPT_SOCKET); 
		}

		//---------------------------------------------------------------------
		// Since this thread can be activated via a user interrupt request
		// we check the f_running flag to find out the signal condition.
		//---------------------------------------------------------------------
		if(f_running == 0) {
			PL_AGENT_DEBUG_MESSAGE(
				PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_INTERRUPTED_BY_USER_STRING
			);
			goto admin_port_listener_thread_end; 
		}

		//---------------------------------------------------------------------
		// Read the message size in bytes.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_RECEIVING_DATA_STRING
		);
		memset(
			&input_ipc_buffer.data,
			0,
			sizeof(input_ipc_buffer.data)
		);
		bytes_received = 0;
		bytes_to_receive = PL_PROTOCOL_SIZET_SIZE;
		total_bytes_to_receive = bytes_to_receive;
		do {
			ret = recv(
				new_socket,
				&input_ipc_buffer.data[bytes_received],
				(int)bytes_to_receive,
				0
			);
			if(ret == SOCKET_ERROR) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_RECEIVE_FROM_SOCKET);
			}
#ifdef __PL_WINDOWS__
			bytes_received += ret;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			bytes_received += (size_t)ret;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__			
			bytes_to_receive = total_bytes_to_receive - bytes_received;
		} while(
			(
				bytes_received <=
				PL_AGENT_IPC_DATA_SIZE
			) &&
			(
				bytes_to_receive > 
				0
			)
		);
		memcpy(
			&message_size,
			&input_ipc_buffer.data[PL_PROTOCOL_BYTES_INDEX],
			PL_PROTOCOL_SIZET_SIZE
		);
		total_bytes_to_receive = message_size;
		if(
			(total_bytes_to_receive <= 0) ||
			(total_bytes_to_receive) > PL_AGENT_IPC_DATA_SIZE
		) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_INVALID_MESSAGE_DATA);
		}

		//---------------------------------------------------------------------
		// Read the message data.
		//---------------------------------------------------------------------
		bytes_received = 0;
		bytes_to_receive = total_bytes_to_receive;
		do {
			ret = recv(
				new_socket,
				&input_ipc_buffer.data[
					bytes_received + 
					PL_PROTOCOL_BYTES_OFFSET_INDEX
				], 
				total_bytes_to_receive, 
				0
			);
			if(ret == SOCKET_ERROR) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_PROTOCOL_ERROR);
			}
#ifdef __PL_WINDOWS__
			bytes_received += ret;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			bytes_received += (size_t)ret;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			bytes_to_receive = total_bytes_to_receive - bytes_received;
		} while(
			(
				bytes_received <=
				PL_AGENT_IPC_DATA_SIZE
			) &&
			(
				bytes_to_receive > 
				0
			)
		);
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_RECEIVED_DATA_STRING
		);

#ifdef _DEBUG

		//---------------------------------------------------------------------
		// Hex dumps received message for debug purposes.
		//---------------------------------------------------------------------
		pl_agent_hex_dump_message(
			"ADMIN",
			bytes_received,
			input_ipc_buffer.data
		);
#endif // _DEBUG

		//---------------------------------------------------------------------
		// Decrypt data.
		//---------------------------------------------------------------------
		if(p->f_encrypt == 1) {
			PL_AGENT_DEBUG_MESSAGE(
				PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_DECYPHERING_DATA_STRING
			);
			// TODO: add de-cypher code.
		}

		//---------------------------------------------------------------------
		// Process admin request -- start by decoding the command.
		//---------------------------------------------------------------------
		input_message = input_ipc_buffer.data;
		output_message = output_ipc_buffer.data;
		memset(
			output_message,
			0,
			PL_AGENT_IPC_DATA_SIZE
		);
		ret = decode_admin_command(
			&command,
			bytes_received,
			input_message
		);
		if(ret != PL_SUCCESS) {
			; // ERROR
		}

		/*
		 @@@@  @    @ @@@@@   @@@@@  @@@@  @    @         @@@@   @@@@  @    @ @    @   @@   @    @ @@@@@
		@    @ @    @   @       @   @    @ @    @        @    @ @    @ @@  @@ @@  @@  @  @  @@   @ @    @
		@      @  @ @   @       @   @      @    @        @      @    @ @ @@ @ @ @@ @ @    @ @ @  @ @    @
		 @@@@  @  @ @   @       @   @      @@@@@@        @      @    @ @    @ @    @ @    @ @ @  @ @    @
			 @ @  @ @   @       @   @      @    @        @      @    @ @    @ @    @ @@@@@@ @  @ @ @    @
			 @  @ @ @   @       @   @    @ @    @        @    @ @    @ @    @ @    @ @    @ @   @@ @    @
		@@@@@    @ @  @@@@@     @    @@@@  @    @         @@@@   @@@@  @    @ @    @ @    @ @    @ @@@@@
		*/
		command_code = command.command_code;
		switch(command_code) {

			/*
			@       @@@@   @@@@  @   @         @    @ @@@@@         @    @ @    @ @@@@@  @@@@@
			@      @    @ @    @ @  @          @    @ @    @        @    @ @    @   @    @    @
			@      @    @ @    @ @ @           @    @ @    @        @    @ @    @   @    @    @
			@      @    @ @    @ @@     @@@@@@ @    @ @@@@@         @    @ @    @   @    @    @
			@      @    @ @    @ @ @           @    @ @             @    @ @    @   @    @    @
			@      @    @ @    @ @  @          @    @ @             @    @ @    @   @    @    @
			@@@@@@  @@@@   @@@@  @   @          @@@@  @              @@@@   @@@@  @@@@@  @@@@@
			*/
			case PL_ADMIN_COMMAND_LOOK_UP_UUID:

				PL_AGENT_DEBUG_MESSAGE(
					PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SERVING_LOOK_UP_UUID_COMMAND
				);

				//-------------------------------------------------------------
				// Lock the pl_table against other threads. blocking wait.
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE(
					PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_LOCKING_PL_TABLE
				);
#ifdef __PL_WINDOWS__
				dw_ret = WaitForSingleObject(
					pl_table.semaphore, 
					INFINITE
				);
				if(dw_ret != WAIT_OBJECT_0) {
					// Critial error - error routine will try to stop
					PL_AGENT_ERROR(
						PL_AGENT_UNABLE_TO_SYNCHRONIZE
					);
				}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifdef __PL_MACOSX__
				ret = sem_wait(pl_table.semaphore);
#else // __PL_MACOSX__
				ret = sem_wait(&pl_table.semaphore);
#endif // __PL_MACOSX__	
				if(ret == -1) {
					// Critial error - error routine will try to stop
					PL_AGENT_ERROR(
						PL_AGENT_UNABLE_TO_SYNCHRONIZE
					);
				}
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

				//-------------------------------------------------------------
				// Search the UUID in the the pl_table.
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE(
					PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SEARCHING_UUID
				);
#ifdef _DEBUG
	pl_agent_hex_dump_string(
		"UUID TO LOOK-UP",
		PL_UUID_SIZE,
		command.binary_uuid_argument
	);
#endif // _DEBUG

				f_found = 0;
				for(
					index = 0;
#ifndef __PL_DYNAMIC_TABLE_ALLOCATION__
					index < PL_MAX_PRODUCTIVITY_LINKS; 
#else // !__PL_DYNAMIC_TABLE_ALLOCATION__
					index < pl_max_productivity_links; 
#endif // !__PL_DYNAMIC_TABLE_ALLOCATION__
					index++
				) {
					if(pl_table.pl_array[index].pl_in_use != 0) {

#ifdef _DEBUG
					pl_agent_hex_dump_string(
						"UUID COMPARED",
						PL_UUID_SIZE,
						(char *)&pl_table.pl_array[index].uuid
					);
#endif // _DEBUG
						if(
							memcmp(
								(void *)&command.binary_uuid_argument,
								(void *)&pl_table.pl_array[index].uuid,
								PL_UUID_SIZE
							) == 0
						) {
							PL_AGENT_DEBUG_MESSAGE(
								PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_FOUND_UUID
							);
							f_found = 1;
							goto admin_thread_uuid_found;
						}
					}
				}
				PL_AGENT_DEBUG_MESSAGE(
					PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_NOT_FOUND_UUID
				);

admin_thread_uuid_found:

				//-------------------------------------------------------------
				// Unlock the productivity link table (locked against other 
				// threads).
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE(
					PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_UNLOCKING_PL_TABLE
				);
#ifdef __PL_WINDOWS__
				b_ret = ReleaseSemaphore(
					pl_table.semaphore, 
					(LONG)1, 
					NULL
				);
				if(b_ret == FALSE) {
					// Critial error - error routine will try to stop the agent.
					PL_AGENT_ERROR(
						PL_AGENT_UNABLE_TO_SYNCHRONIZE
					);
				}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
#ifdef __PL_MACOSX__
				ret = sem_post(pl_table.semaphore);
#else // __PL_MACOSX__	
				ret = sem_post(&pl_table.semaphore);
#endif // __PL_MACOSX__	
				if(ret == -1) {
					// Critial error - error routine will try to stop the agent.
					PL_AGENT_ERROR(
						PL_AGENT_UNABLE_TO_SYNCHRONIZE
					);
				}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

				//-------------------------------------------------------------
				// Build answer to the client.
				//-------------------------------------------------------------
				memset(
					uuid_buffer, 
					0, 
					sizeof(uuid_buffer)
				);
				if(f_found == 1) {
#ifdef __PL_WINDOWS__
					rpc_ret = UuidToString(
						&pl_table.pl_array[index].uuid, 
						(RPC_WSTR *)&puuid
					);
					if(puuid == NULL) {
						//pl_last_error = PL_CRITICAL_FAILURE;
					}
					wcstombs_s(
						&st_ret, 
						uuid_buffer, 
						sizeof(uuid_buffer), 
						puuid, 
						_TRUNCATE
					);
					rpc_ret = RpcStringFree(&puuid);
					if(rpc_ret != RPC_S_OK) {
						//pl_last_error = PL_CRITICAL_FAILURE;
					}
					puuid = NULL;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
					uuid_unparse(
						pl_table.pl_array[index].uuid, 
						uuid_buffer
					);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
				} else {
					sprintf(
						uuid_buffer,
						"%s",
						PL_ADMIN_PROTOCOL_COMMAND_LOOK_UP_UUID_FAILURE
					);
				}

				//-------------------------------------------------------------
				// Build answer message.
				//-------------------------------------------------------------
				total_bytes_to_send = sprintf(
					&output_message[
						PL_ADMIN_PROTOCOL_OUTPUT_COMMAND_STRING_INDEX
					],
					"%s%s%s%c",
					PL_ADMIN_PROTOCOL_COMMAND_LOOK_UP_UUID_STRING,
					PL_ADMIN_PROTOCOL_COMMAND_ITEM_DELIMITER,
					uuid_buffer,
					PL_PROTOCOL_EOR
				);
				message_size = (PL_PROTOCOL_SIZET)total_bytes_to_send;
				memcpy(
					&output_message[PL_PROTOCOL_BYTES_INDEX],
					&message_size,
					PL_PROTOCOL_SIZET_SIZE
				);
				total_bytes_to_send += PL_PROTOCOL_SIZET_SIZE;
				break;

			/*
			@    @ @    @ @   @  @    @  @@@@  @    @ @    @         @@@@   @@@@  @@@@@  @@@@@@
			@    @ @@   @ @  @   @@   @ @    @ @    @ @@   @        @    @ @    @ @    @ @
			@    @ @ @  @ @ @    @ @  @ @    @ @  @ @ @ @  @        @      @    @ @    @ @
			@    @ @ @  @ @@     @ @  @ @    @ @  @ @ @ @  @        @      @    @ @    @ @@@@@@
			@    @ @  @ @ @ @    @  @ @ @    @ @  @ @ @  @ @        @      @    @ @    @ @
			@    @ @   @@ @  @   @   @@ @    @  @ @ @ @   @@        @    @ @    @ @    @ @
			 @@@@  @    @ @   @  @    @  @@@@    @ @  @    @         @@@@   @@@@  @@@@@  @@@@@@
			*/
			default:

				// Non critial error. Not accounted in stats.
				PL_AGENT_ERROR(PL_AGENT_PROTOCOL_UNKNOWN_OP_CODE); 
				goto admin_port_listener_thread_skip_message;
				;
		} // switch command code

		//---------------------------------------------------------------------
		// Encrypt data.
		//---------------------------------------------------------------------
		if(p->f_encrypt == 1) {
			PL_AGENT_DEBUG_MESSAGE(
				PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_CYPHERING_DATA_STRING
			);
			// TODO: add cypher code.
		}

#ifdef _DEBUG

		//---------------------------------------------------------------------
		// Hex dumps to be sent for debug purposes.
		//---------------------------------------------------------------------
		pl_agent_hex_dump_message(
			"ADMIN",
			total_bytes_to_send - PL_PROTOCOL_SIZET_SIZE,
			output_ipc_buffer.data
		);
#endif // _DEBUG

		//---------------------------------------------------------------------
		// Send answer to client.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SENDING_DATA_STRING
		);

#ifdef _DEBUG
		// TODO: add answer dump for debug.
#endif // _DEBUG

		bytes_sent = 0;
		bytes_to_send = total_bytes_to_send;
		do {
			ret = send(
				new_socket, 
				&output_ipc_buffer.data[bytes_sent], 
				bytes_to_send, 
				0
			);
			if(ret == SOCKET_ERROR) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SEND_VIA_SOCKET); 
			}

#ifdef __PL_WINDOWS__
			bytes_sent += ret;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			bytes_sent += (size_t)ret;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			bytes_to_send = total_bytes_to_send - bytes_sent;
		} while(bytes_to_send > 0);

admin_port_listener_thread_skip_message:

		//---------------------------------------------------------------------
		// Close socket.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_CLOSING_IPC_STRING
		);
		ret = shutdown(
			new_socket, 
			SD_BOTH
		);
		if(ret == SOCKET_ERROR) {
#ifdef __PL_MACOSX__
			if(errno != ENOTCONN) { 
#endif // __PL_MACOSX__
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SHUTDOWN_SOCKET); 
#ifdef __PL_MACOSX__
			}
#endif // __PL_MACOSX__
		}
#ifdef __PL_WINDOWS__
		ret = closesocket(
			new_socket
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = close(
			new_socket
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		if(ret == SOCKET_ERROR) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CLOSE_SOCKET); 
		}
	} // while f_running == 1

admin_port_listener_thread_end:

	//-------------------------------------------------------------------------
	// Tear-down IPC
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_TEARINGDOWN_IPC_STRING
	);
	if(p->admin_port_listener_thread_ipc_data.socket != INVALID_SOCKET) {

		//---------------------------------------------------------------------
		// Close socket
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		ret = closesocket(
			p->admin_port_listener_thread_ipc_data.socket
		);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = close(
			p->admin_port_listener_thread_ipc_data.socket
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		if(ret == SOCKET_ERROR) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CLOSE_SOCKET); 
		}
		p->admin_port_listener_thread_ipc_data.socket = INVALID_SOCKET;

		//---------------------------------------------------------------------
		// Free socket ressources
		//---------------------------------------------------------------------
		if(p->admin_port_listener_thread_ipc_data.address_info != NULL) {
#ifdef __PL_WINDOWS__
			freeaddrinfo(
				p->admin_port_listener_thread_ipc_data.address_info
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			freeaddrinfo(
				(struct addrinfo *)
					p->admin_port_listener_thread_ipc_data.address_info
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		}
	}

	//-------------------------------------------------------------------------
	// Signal ADMIN port listener thread end to primary thread (waiting on us).
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_ENDED_STRING
	);
#ifdef __PL_WINDOWS__
	SetEvent(p->h_admin_port_listener_thread_done);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	sem_post(&p->h_admin_port_listener_thread_done);
#else // __PL_MACOSX__
	sem_post(p->h_admin_port_listener_thread_done);
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Return.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	return((PTHREAD_START_ROUTINE)PL_SUCCESS);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	return(PL_SUCCESS);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
Function: decode_admin_command
Purpose : Decode an admin command and populate a command structure.
In      : pointer to command structure, a command string and length of it
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
06/30/2010    Jamel Tayeb             Creation.
*/
PL_STATUS decode_admin_command(PPL_AGENT_COMMAND p, size_t l, char *s) {

	char *pc = NULL;

	assert(p != NULL);
	assert(s != NULL);
	assert(l != 0);

	//-------------------------------------------------------------------------
	// Note:
	//    in this sample code - associated with the demo code -, only the 
	//    UUID look-up ADMIN command is implemented, thus the simplistic 
	//    decode routine.  TODO: adapt the ADMIN protocol and related
	//    functions & files to suit your needs.
	//-------------------------------------------------------------------------
	pc = strstr(
		&s[PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_OFFSET],
		PL_ADMIN_PROTOCOL_COMMAND_LOOK_UP_UUID_STRING
	);
	if(pc == NULL) {
		goto decode_admin_command_error;
	}
	p->command_code = PL_ADMIN_COMMAND_LOOK_UP_UUID;
	pc = strstr(
		&s[PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_OFFSET],
		PL_ADMIN_PROTOCOL_COMMAND_LOOK_UP_UUID_FAILURE
	);
	if(pc != NULL) {
		goto decode_admin_command_error;
	}
	pc = strstr(
		&s[PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_OFFSET],
		PL_ADMIN_PROTOCOL_COMMAND_ITEM_DELIMITER
	);
	if(pc == NULL) {
		goto decode_admin_command_error;
	}
	memcpy(
		&p->binary_uuid_argument,
		++pc,
		PL_UUID_SIZE
	);

	return(PL_SUCCESS);
decode_admin_command_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: pl_port_listener_thread
Purpose : PL port listener thread code.
In      : pointer to pl_agent_data structure
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
06/30/2010    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
LPTHREAD_START_ROUTINE pl_port_listener_thread(void * px) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
void *pl_port_listener_thread(void *px) {
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Generic data
	//-------------------------------------------------------------------------
	PL_STATUS ret = PL_FAILURE;
	PPL_AGENT_DATA p = NULL;

#ifdef __PL_WINDOWS__
	DWORD dwret = 0;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int iret = -1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Data used to manage IPC.
	//-------------------------------------------------------------------------
	int one = 1;
	SOCKET new_socket = INVALID_SOCKET;

#ifdef __PL_WINDOWS__
	ADDRINFO *pa = NULL;
	TCHAR buffer[PL_MAX_PATH] = { '\0' };
	TCHAR temp[PL_MAX_PATH] = { '\0' };
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	char port[PL_AGENT_IPC_SOCKET_MAX_PORT_NAME_SIZE] = { '\0' };
	struct addrinfo *pa = NULL;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Data used to manage thread pool.
	//-------------------------------------------------------------------------
	int i = 0;
	int f_non_buzy_pool_thread_found = 0;

#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
#endif // __PL_WINDOWS__

#ifdef _DEBUG

	//-------------------------------------------------------------------------
	// Data used to display messages.
	//-------------------------------------------------------------------------
	char tmp_buffer[PL_MAX_PATH] = { '\0' };
#endif // _DEBUG

	//-------------------------------------------------------------------------

	p = (PPL_AGENT_DATA)px;
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Wait for main thread done.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_STARTED_STRING
	);
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_WAITING_MAIN_THREAD_DONE_STRING
	);
#ifdef __PL_WINDOWS__
	dwret = WaitForSingleObject(
		p->h_main_thread_done,
		INFINITE
	);
	if(dwret != WAIT_OBJECT_0) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	iret = sem_wait(
		&p->h_main_thread_done
	);
#else // __PL_MACOSX__
	iret = sem_wait(
		p->h_main_thread_done
	);
#endif // __PL_MACOSX__
	if(iret != 0) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_RECEIVED_MAIN_THREAD_DONE_SIGNAL_STRING
	);

	//-------------------------------------------------------------------------
	// Setup IPC for PL port.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_SETTING_UP_IPC_STRING
	);
	memset(
		&p->pl_port_listener_thread_ipc_data, 
		0, 
		sizeof(p->pl_port_listener_thread_ipc_data)
	);

	//-------------------------------------------------------------------------
	// Clear and initialize the address info hint structure and socket
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_INITIALIZING_IPC_STRING
	);
	p->pl_port_listener_thread_ipc_data.socket = INVALID_SOCKET;
	memset(
		&p->pl_port_listener_thread_ipc_data.address_info_hint,
		0, 
		sizeof(p->pl_port_listener_thread_ipc_data.address_info_hint)
	);

	//-------------------------------------------------------------------------
	// Setup socket data, start with address...
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_SETTING_UP_SOCKET_DATA_STRING
	);
	memset(
		p->pl_port_listener_thread_ipc_data.node_name, 
		0, 
		sizeof(p->pl_port_listener_thread_ipc_data.node_name)
	);
	if(p->ip_address != NULL) {
		strncpy(
			p->pl_port_listener_thread_ipc_data.node_name, 
			p->ip_address, 
			strlen(p->ip_address)
		);
	} else {
		strncpy(
			p->pl_port_listener_thread_ipc_data.node_name, 
			PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME, 
			strlen(PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME)
		);
	}

	//-------------------------------------------------------------------------
	// ...continue with port number
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	memset(
		p->pl_port_listener_thread_ipc_data.port, 
		0, 
		sizeof(p->pl_port_listener_thread_ipc_data.port)
	);
	if(
		(p->f_pl_port == 1) && 
		(p->pl_port_string != NULL)
	) {
		strncpy(
			p->pl_port_listener_thread_ipc_data.port, 
			p->pl_port_string, 
			strlen(p->pl_port_string)
		);
	} else {
		strncpy(
			p->pl_port_listener_thread_ipc_data.port, 
			PL_DEFAULT_PL_AGENT_PL_PORT, 
			strlen(PL_DEFAULT_PL_AGENT_PL_PORT)
		);
	}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	if(
		(p->f_pl_port == 1) && 
		(p->pl_port_string != NULL)
	) {
		p->pl_port_listener_thread_ipc_data.port = 
			p->pl_port_value;
	} else {
		p->pl_port_listener_thread_ipc_data.port = 
			PL_DEFAULT_PL_AGENT_PL_PORT;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Set the address info hint structure
	//-------------------------------------------------------------------------
	p->pl_port_listener_thread_ipc_data.address_info_hint.ai_family = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FAMILY
	;
	p->pl_port_listener_thread_ipc_data.address_info_hint.ai_socktype = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	p->pl_port_listener_thread_ipc_data.address_info_hint.ai_protocol = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	p->pl_port_listener_thread_ipc_data.address_info_hint.ai_flags = 
		PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve address and port
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_RESOLVING_ADDRESS_PORT_STRING
	);

#ifdef __PL_WINDOWS__
	ret = getaddrinfo(
		NULL, 
		p->pl_port_listener_thread_ipc_data.port, 
		&p->pl_port_listener_thread_ipc_data.address_info_hint, 
		&p->pl_port_listener_thread_ipc_data.address_info
	);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	sprintf(
		port, 
		"%d", 
		p->pl_port_listener_thread_ipc_data.port
	);
	ret = getaddrinfo(
		NULL, 
		port, 
		(const struct addrinfo *)
			&p->pl_port_listener_thread_ipc_data.address_info_hint, 
		(struct addrinfo **)
			&p->pl_port_listener_thread_ipc_data.address_info
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	if(ret != 0) { 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_GET_ADDRESS_INFO);
	}

	//-------------------------------------------------------------------------
	// Attempt to create the socket and bind - untill one succeds
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_CREATING_BINDING_SOCKET_STRING
	);
	for(
		pa = (struct addrinfo *)
			p->pl_port_listener_thread_ipc_data.address_info; 
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the client
		//---------------------------------------------------------------------
		p->pl_port_listener_thread_ipc_data.socket = socket(
			pa->ai_family, 
			pa->ai_socktype, 
			pa->ai_protocol
		);
		if(p->pl_port_listener_thread_ipc_data.socket == INVALID_SOCKET) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_SOCKET); 
		}

		//---------------------------------------------------------------------
		// Configure socket.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		ret = setsockopt(
			p->pl_port_listener_thread_ipc_data.socket, 
			SOL_SOCKET, 
			SO_EXCLUSIVEADDRUSE, 
			(char *)&one, 
			sizeof(one)
		);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

		//-------------------------------------------------------------
		// Note: 
		//   SO_EXCLUSIVEADDRUSE is not implemented on *NIX, 
		//    use it as it becomes available for security reasons.
		//-------------------------------------------------------------
		ret = setsockopt(
			p->pl_port_listener_thread_ipc_data.socket,
			SOL_SOCKET, 
			SO_REUSEADDR, 
			(char *)&one, 
			sizeof(one)
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		if(ret == SOCKET_ERROR) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SET_SOCKET_OPTIONS);
		}

		//-------------------------------------------------------------
		// Bind.
		//-------------------------------------------------------------
#ifdef __PL_WINDOWS__
		ret = bind(
			p->pl_port_listener_thread_ipc_data.socket, 
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = bind(
			p->pl_port_listener_thread_ipc_data.socket, 
			pa->ai_addr, 
			pa->ai_addrlen
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		if(ret == SOCKET_ERROR) {
			
			//-----------------------------------------------------------------
			// Failed to bind to this address, let's close the socket.
			//-----------------------------------------------------------------
#ifdef __PL_WINDOWS__
			ret = closesocket(
				p->pl_port_listener_thread_ipc_data.socket
			);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			ret = close(
				p->pl_port_listener_thread_ipc_data.socket
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			if(ret == SOCKET_ERROR) { 
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CLOSE_SOCKET); 
			}
			
			//-----------------------------------------------------------------
			// Mark the socket as invalid before trying a new address.
			//-----------------------------------------------------------------
			p->pl_port_listener_thread_ipc_data.socket = INVALID_SOCKET;
			continue;
		}
		goto pl_port_listener_ipc_setup_socket_bound;
	} // for pa

	//-------------------------------------------------------------------------
	// No bind attempt succeded, signal error.
	//-------------------------------------------------------------------------
	// Critial error - error routine will try to stop the agent.
	PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CONNECT_TO_SOCKET);

pl_port_listener_ipc_setup_socket_bound:

	//-------------------------------------------------------------------------
	// Listen.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_LISTENING_SOCKET_STRING
	);
	ret = listen(
		p->pl_port_listener_thread_ipc_data.socket, 
		SOMAXCONN
	);
	if(ret == SOCKET_ERROR) { 
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_LISTEN_SOCKET); 
	}

	//-------------------------------------------------------------------------
	// Main loop.
	//-------------------------------------------------------------------------
	while(f_running == 1) {

		//---------------------------------------------------------------------
		// Connect to the PL port and wait (blocking) for a pl API request.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_PL_THREAD_ACCEPTING_CONNECTION_STRING
		);
		new_socket = accept(
			p->pl_port_listener_thread_ipc_data.socket, 
			NULL, 
			NULL
		);
		if(new_socket == INVALID_SOCKET) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_ACCEPT_SOCKET); 
		}

		//---------------------------------------------------------------------
		// Since this thread can be activated via a user interrupt request
		// we check the f_running flag to find out the signal condition.
		//---------------------------------------------------------------------
		if(f_running == 0) {
			PL_AGENT_DEBUG_MESSAGE(
				PL_AGENT_DEBUG_MESSAGE_PL_THREAD_INTERRUPTED_BY_USER_STRING
			);
			goto pl_port_listener_thread_end; 
		}

		//---------------------------------------------------------------------
		// Find a free thread in the pool.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_PL_THREAD_RECEIVING_REQUEST_STRING
		);
		PL_AGENT_DEBUG_MESSAGE(
			PL_AGENT_DEBUG_MESSAGE_PL_THREAD_SEARCHING_IDLE_POOL_THREAD_STRING
		);

pl_port_listener_thread_search_non_busy_thread:

		f_non_buzy_pool_thread_found = 0;
		for(i = 0; i < p->threads_in_pool_value; i++) {

			/*
			@       @@@@   @@@@  @   @
			@      @    @ @    @ @  @
			@      @    @ @      @ @
			@      @    @ @      @@
			@      @    @ @      @ @
			@      @    @ @    @ @  @
			@@@@@@  @@@@   @@@@  @   @
			*/
			//-----------------------------------------------------------------
			// Try to lock the ith pool thread's data (non blocking).
			//-----------------------------------------------------------------
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_PL_THREAD_TRY_LOCK_POOL_THREAD_STRING,
				i
			);
#ifdef __PL_WINDOWS__
			dwret = WaitForSingleObject(
				p->pool_threads_data[i].semaphore, 
				0L
			);
			if(dwret != WAIT_OBJECT_0) {
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_PL_THREAD_LOCK_FAILED_POOL_THREAD_STRING,
					i
				);
				goto pl_port_listener_thread_try_lock_thread_next;
			}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
			ret = sem_trywait(
				&p->pool_threads_data[i].semaphore
			);
#else // __PL_MACOSX__
			ret = sem_trywait(
				p->pool_threads_data[i].semaphore
			);
#endif // __PL_MACOSX__
			if(
				(ret == -1) && 
				(errno == EAGAIN)
			) {
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_PL_THREAD_LOCK_FAILED_POOL_THREAD_STRING,
					i
				);
				goto pl_port_listener_thread_try_lock_thread_next;
			}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			//-----------------------------------------------------------------
			// Lock was successfull, set-up the ith pool thread's data 
			// appropriately to serve the request received on the PL 
			// port (CONNECT, DISCONNECT, etc.).
			// Note:
			//    The thread's data will be unlocked by the pool thread.
			//-----------------------------------------------------------------
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_PL_THREAD_LOCK_SUCCEDED_POOL_THREAD_STRING,
				i
			);
			
			//-----------------------------------------------------------------
			// Check status as reported by pool thread.
			//-----------------------------------------------------------------
			if(p->pool_threads_data[i].f_busy == 1) {
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_PL_THREAD_POOL_THREAD_BUSY_STRING,
					i
				);

				//-------------------------------------------------------------
				// Unlock the thread's semaphore
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_PL_THREAD_UNLOCK_SUCCEDED_POOL_THREAD_STRING, 
					i
				);
#ifdef __PL_WINDOWS__
				ReleaseSemaphore(
					p->pool_threads_data[i].semaphore, 
					(LONG)1, 
					NULL
				);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
				sem_post(&p->pool_threads_data[i].semaphore);
#else // __PL_MACOSX__
				sem_post(p->pool_threads_data[i].semaphore);
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

				//-------------------------------------------------------------
				// Continue searching...
				//-------------------------------------------------------------
				goto pl_port_listener_thread_try_lock_thread_next;

			} else {

				//-------------------------------------------------------------
				// Mark the thread as busy...
				//-------------------------------------------------------------
				p->pool_threads_data[i].f_busy = 1;
			}

			//-------------------------------------------------------------
			// Set the ith pool thread's data so it can process the API 
			// call.  Here, it solely consist in passing the socket.
			//-------------------------------------------------------------
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_PL_THREAD_FOUND_IDLE_POOL_THREAD_STRING,
				i
			);
			p->pool_threads_data[i].new_socket = new_socket;

			//-------------------------------------------------------------
			// Fire the ith thread!
			//-------------------------------------------------------------
#ifdef __PL_WINDOWS__
			bret = SetEvent(
				p->h_pool_threads_do[i]
			);
			if(bret == FALSE) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
			}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
			ret = sem_post(
				&p->h_pool_threads_do[i]
			);
#else // __PL_MACOSX__
			ret = sem_post(
				p->h_pool_threads_do[i]
			);
#endif // __PL_MACOSX__
			if(ret != 0) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
			}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			goto pl_port_listener_thread_end_thread_search;

pl_port_listener_thread_try_lock_thread_next:
			;
		} // for i

		//---------------------------------------------------------------------
		// Check if a non-busy thread was found.  If not, wait for a defined
		// period of time and retry.
		//---------------------------------------------------------------------
		if(f_non_buzy_pool_thread_found == 0) {
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_PL_THREAD_NO_IDLE_POOL_THREAD_FOUND_STRING,
				PL_AGENT_PL_EXPORT_POOL_THREAD_SEARCH_GRACE_TIME
			);
#ifdef __PL_WINDOWS__
			Sleep(
				PL_AGENT_PL_EXPORT_POOL_THREAD_SEARCH_GRACE_TIME
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			sleep(
				PL_AGENT_PL_EXPORT_POOL_THREAD_SEARCH_GRACE_TIME
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			//-----------------------------------------------------------------
			// Check for stop condition after the grace time wait.
			//-----------------------------------------------------------------
			if(f_running == 0) { 
				goto pl_port_listener_thread_end; 
			}
			goto pl_port_listener_thread_search_non_busy_thread;
		} else {
			f_non_buzy_pool_thread_found = 0;
		}
pl_port_listener_thread_end_thread_search:
		;
	} // while running

pl_port_listener_thread_end:

	//-------------------------------------------------------------------------
	// Tear-down IPC.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_TEARINGDOWN_IPC_STRING
	);
	if(p->pl_port_listener_thread_ipc_data.socket != INVALID_SOCKET) {

		//---------------------------------------------------------------------
		// Close socket.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		ret = closesocket(
			p->pl_port_listener_thread_ipc_data.socket
		);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = close(
			p->pl_port_listener_thread_ipc_data.socket
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		if(ret == SOCKET_ERROR) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CLOSE_SOCKET); 
		}
		p->pl_port_listener_thread_ipc_data.socket = INVALID_SOCKET;

		//---------------------------------------------------------------------
		// Free socket ressources.
		//---------------------------------------------------------------------
		if(p->pl_port_listener_thread_ipc_data.address_info != NULL) {
#ifdef __PL_WINDOWS__
			freeaddrinfo(
				p->pl_port_listener_thread_ipc_data.address_info
			);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			freeaddrinfo(
				(struct addrinfo *)
					p->pl_port_listener_thread_ipc_data.address_info
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		}
	}

	//-------------------------------------------------------------------------
	// Signal PL port listener thread end to primary thread (waiting on us).
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE(
		PL_AGENT_DEBUG_MESSAGE_PL_THREAD_ENDED_STRING
	);
#ifdef __PL_WINDOWS__
	SetEvent(p->h_pl_port_listener_thread_done);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	sem_post(&p->h_pl_port_listener_thread_done);
#else // __PL_MACOSX__
	sem_post(p->h_pl_port_listener_thread_done);
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Return.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	return((PTHREAD_START_ROUTINE)PL_SUCCESS);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	return(PL_SUCCESS);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
Function: pool_thread
Purpose : pool thread code (responsible to process any PL core API calls
          passed by the PL port listener thread.
In      : pointer to pl_agent_data structure
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
06/30/2010    Jamel Tayeb             Creation.
*/
#ifdef __PL_WINDOWS__
LPTHREAD_START_ROUTINE pool_thread(void *px) {
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
void *pool_thread(void *px) {
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Generic data.
	//-------------------------------------------------------------------------
	int i = 0;
	int rank = 0;
	int f_non_critical_error = 0;
	PL_STATUS ret = PL_FAILURE;
	PPL_AGENT_DATA p = NULL;
	PPL_AGENT_POOL_THREADS_DATA pd = NULL;

#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
	DWORD tid = 0;
	DWORD dwret = 0;
	RPC_STATUS rpc_ret = 0;	
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int iret = -1;
	pthread_t tid;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Data used to manage PL_FOLDER transposition.
	//-------------------------------------------------------------------------
	size_t buffer_index = 0;
	size_t bytes_in_buffer = 0;
	size_t start_byte_index = 0;
	size_t end_byte_index = 0;

	//-------------------------------------------------------------------------
	// Data used to manage IPC.
	//-------------------------------------------------------------------------
	PL_AGENT_IPC_BUFFER input_ipc_buffer = { {'\0'} };
	PL_AGENT_IPC_BUFFER output_ipc_buffer = { {'\0'} };

#ifdef __PL_WINDOWS__
	int bytes_received = 0;
	int bytes_to_receive = 0;
	int total_bytes_to_receive = 0;
	int bytes_sent = 0;
	int bytes_to_send = 0;
	int total_bytes_to_send = 0;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	size_t bytes_received = 0;
	size_t bytes_to_receive = 0;
	size_t total_bytes_to_receive = 0;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t total_bytes_to_send = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#ifdef _DEBUG

	//-------------------------------------------------------------------------
	// Data used to display degug messages.
	//-------------------------------------------------------------------------
	char tmp_buffer[PL_MAX_PATH] = { '\0' };
#endif // _DEBUG

	//-------------------------------------------------------------------------
	// Data used to implement PL protocol.
	//-------------------------------------------------------------------------
	PL_PROTOCOL_OPCODE opcode = 0;
	char *input_message = NULL;
	char *output_message = NULL;
	uuid_t uuid;

#ifdef __PL_DUMMY_AGENT__
	unsigned long long value = 0;
#endif // __PL_DUMMY_AGENT__

	//-------------------------------------------------------------------------
	// Data used to decode messages.
	//-------------------------------------------------------------------------
	char *pp = NULL;
	unsigned int pl_counters_count = 0;
	size_t length = 0;
	size_t memory_size = 0;
	PL_PROTOCOL_SIZET message_size = 0;
	PL_PROTOCOL_PPCHAR pl_counters_names = NULL;
	PL_PROTOCOL_PCHAR p_string = NULL;
	PL_PROTOCOL_CHAR pl_application_name[PL_MAX_PATH] = { '\0' };
	PL_PROTOCOL_CHAR pl_config_file_name[PL_MAX_PATH] = { '\0' };
	PL_PROTOCOL_CHAR transposed_pl_config_file_name[PL_MAX_PATH] = { '\0' };

#ifndef __PL_DUMMY_AGENT__
	size_t counter_index = 0;
#ifndef __PL_IN_MEMORY__

	//-------------------------------------------------------------------------
	// Data used to call PL APIs.
	//-------------------------------------------------------------------------
	int pl_pld = PL_INVALID_DESCRIPTOR;
	unsigned long long counter_value = 0;
	unsigned int counter_offset = 0;
	uuid_t pl_uuid;
#endif // __PL_IN_MEMORY__
#endif //__PL_DUMMY_AGENT__

	//-------------------------------------------------------------------------

	p = (PPL_AGENT_DATA)px;
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Retrive this thread's rank.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	tid = GetCurrentThreadId();
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	tid = pthread_self();
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	for(i = 0; i < p->threads_in_pool_value; i++) {

#ifdef __PL_WINDOWS__
		if(tid == p->pool_threads_ids[i]) {
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		if(tid == p->h_pool_threads[i]) {
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

			rank = i;
			goto pool_thread_id_found;
		}
	}
	goto pool_thread_end;

pool_thread_id_found:

	//-------------------------------------------------------------------------
	// Retrieve this threads data structure pointer.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
		PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_STARTED_STRING, 
		rank
	);
	pd = &p->pool_threads_data[rank];
	assert(pd != NULL);

	//-------------------------------------------------------------------------
	// Wait for main thread done.
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
		PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_WAITING_MAIN_THREAD_DONE_STRING, 
		rank
	);
#ifdef __PL_WINDOWS__
	dwret = WaitForSingleObject(
		p->h_main_thread_done,
		INFINITE
	);
	if(dwret != WAIT_OBJECT_0) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
	}
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	iret = sem_wait(
		&p->h_main_thread_done
	);
#else // __PL_MACOSX__
	iret = sem_wait(
		p->h_main_thread_done
	);
#endif // __PL_MACOSX__
	if(iret != 0) {
		// Critial error - error routine will try to stop the agent.
		PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
		PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_RECEIVED_MAIN_THREAD_DONE_SIGNAL_STRING, 
		rank
	);

	/*
	@    @   @@   @@@@@  @    @        @       @@@@   @@@@  @@@@@
	@@  @@  @  @    @    @@   @        @      @    @ @    @ @    @
	@ @@ @ @    @   @    @ @  @        @      @    @ @    @ @    @
	@    @ @    @   @    @ @  @        @      @    @ @    @ @@@@@
	@    @ @@@@@@   @    @  @ @        @      @    @ @    @ @
	@    @ @    @   @    @   @@        @      @    @ @    @ @
	@    @ @    @ @@@@@  @    @        @@@@@@  @@@@   @@@@  @
	*/
	//-------------------------------------------------------------------------
	// Main loop.
	//-------------------------------------------------------------------------
	while(f_running == 1) {

		//---------------------------------------------------------------------
		// Wait a request to serve a PL API call from PL port listener thread.
		// Note:
		//    The primary thread is also signaling us when the user has 
		//    interrupted the agent (from the signal handler).
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
			PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_WAITING_PL_API_CALL_STRING, 
			rank
		);

		//---------------------------------------------------------------------
		// Update this pool thread's busy state.
		//---------------------------------------------------------------------
		p->pool_threads_data[rank].f_busy = 0;

#ifdef __PL_WINDOWS__
		dwret = WaitForSingleObject(
			p->h_pool_threads_do[rank], 
			INFINITE
		);
		if(dwret != WAIT_OBJECT_0) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
		}
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		ret = sem_wait(
			&p->h_pool_threads_do[rank]
		);
#else // __PL_MACOSX__
		ret = sem_wait(
			p->h_pool_threads_do[rank]
		);
#endif // __PL_MACOSX__
		if(ret != 0) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE);
		}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		
		//---------------------------------------------------------------------
		// Since this thread can be activated via a signal comming from the 
		// PL port listener thread or the signal handler of the main thread,
		// we check the f_running flag to find out the signal condition.
		// Note:
		//    On interrupt, thread's data is not unlocked.
		//---------------------------------------------------------------------
		if(f_running == 0) {
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_INTERRUPTED_BY_USER_STRING, 
				rank
			);
			goto pool_thread_end;
		}

		//---------------------------------------------------------------------
		// Reset non critical error.
		//---------------------------------------------------------------------
		f_non_critical_error = 0;

		//---------------------------------------------------------------------
		// Let's serve the API call!
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
			PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_SERVING_PL_API_CALL_STRING, 
			rank
		);

		//-------------------------------------------------------------------------
		// Read the message size in bytes.
		//-------------------------------------------------------------------------
		memset(
			&input_ipc_buffer.data,
			0,
			sizeof(input_ipc_buffer.data)
		);
		bytes_received = 0;
		bytes_to_receive = PL_PROTOCOL_SIZET_SIZE;
		total_bytes_to_receive = bytes_to_receive;
		do {
			ret = recv(
				pd->new_socket,
				&input_ipc_buffer.data[bytes_received],
				(int)bytes_to_receive,
				0
			);
			if(ret == SOCKET_ERROR) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_RECEIVE_FROM_SOCKET);
			}
#ifdef __PL_WINDOWS__
			bytes_received += ret;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			bytes_received += (size_t)ret;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__			
			bytes_to_receive = total_bytes_to_receive - bytes_received;
		} while(
			(
				bytes_received <=
				PL_AGENT_IPC_DATA_SIZE
			) &&
			(
				bytes_to_receive > 
				0
			)
		);
		memcpy(
			&message_size,
			&input_ipc_buffer.data[PL_PROTOCOL_BYTES_INDEX],
			PL_PROTOCOL_SIZET_SIZE
		);
		total_bytes_to_receive = message_size;
		if(
			(total_bytes_to_receive <= 0) ||
			(total_bytes_to_receive) > PL_AGENT_IPC_DATA_SIZE
		) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_INVALID_MESSAGE_DATA);
		}

		//---------------------------------------------------------------------
		// Read the message data.
		//---------------------------------------------------------------------
		bytes_received = 0;
		bytes_to_receive = total_bytes_to_receive;
		do {
			ret = recv(
				pd->new_socket,
				&input_ipc_buffer.data[
					bytes_received + 
					PL_PROTOCOL_BYTES_OFFSET_INDEX
				], 
				total_bytes_to_receive, 
				0
			);
			if(ret == SOCKET_ERROR) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_PROTOCOL_ERROR);
			}
#ifdef __PL_WINDOWS__
			bytes_received += ret;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			bytes_received += (size_t)ret;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			bytes_to_receive = total_bytes_to_receive - bytes_received;
		} while(
			(
				bytes_received <=
				PL_AGENT_IPC_DATA_SIZE
			) &&
			(
				bytes_to_receive > 
				0
			)
		);
		PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
			PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_RECEIVED_DATA_STRING,
			rank
		);

#ifdef _DEBUG

		//---------------------------------------------------------------------
		// Decode received message for debug purposes.
		//---------------------------------------------------------------------
		pl_agent_decode_message(
			rank,
			bytes_received,
			input_ipc_buffer.data
		);
#endif // _DEBUG

		//---------------------------------------------------------------------
		// Process pl API request -- start by decoding the op_code.
		//---------------------------------------------------------------------
		input_message = input_ipc_buffer.data;
		output_message = output_ipc_buffer.data;
		memset(
			output_message,
			0,
			PL_AGENT_IPC_DATA_SIZE
		);

		/*
		 @@@@  @    @ @@@@@   @@@@@  @@@@  @    @         @@@@  @@@@@   @@@@   @@@@  @@@@@  @@@@@@
		@    @ @    @   @       @   @    @ @    @        @    @ @    @ @    @ @    @ @    @ @
		@      @  @ @   @       @   @      @    @        @    @ @    @ @      @    @ @    @ @
		 @@@@  @  @ @   @       @   @      @@@@@@        @    @ @@@@@  @      @    @ @    @ @@@@@@
			 @ @  @ @   @       @   @      @    @        @    @ @      @      @    @ @    @ @
			 @  @ @ @   @       @   @    @ @    @        @    @ @      @    @ @    @ @    @ @
		@@@@@    @ @  @@@@@     @    @@@@  @    @         @@@@  @       @@@@   @@@@  @@@@@  @@@@@@
		*/
		opcode = (PL_PROTOCOL_OPCODE)input_message[PL_PROTOCOL_INPUT_OP_CODE_INDEX];
		switch(opcode) {

			/*
			@@@@@  @              @@@@  @@@@@  @@@@@@ @    @
			@    @ @             @    @ @    @ @      @@   @
			@    @ @             @    @ @    @ @      @ @  @
			@@@@@  @             @    @ @@@@@  @@@@@@ @ @  @
			@      @             @    @ @      @      @  @ @
			@      @             @    @ @      @      @   @@
			@      @@@@@@         @@@@  @      @@@@@@ @    @
						  @@@@@@
			*/
			case PL_PROTOCOL_OPCODE_OPEN:

				//-------------------------------------------------------------
				// Update API utilization stats data
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_LOCKING_API_CALL_COUNTER_STRING,
					rank
				);
				PL_AGENT_INCREMENT_API_USE_COUNT(p->pl_open_count);
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_UNLOCKING_API_CALL_COUNTER_STRING,
					rank
				);

				//-------------------------------------------------------------
				// Process pl_open API call.
				//-------------------------------------------------------------
				// pl_open()
				// +-----------+-----------+-----------+------------+--     --+---------------+
				// | OPERATION | COUNTERS  |  <string> | <string>   |         | <string>      |
				// | CODE      | COUNT (N) | APP NAME  | COUNTER 0  |   ...   | COUNTER (N-1) |
				// |           |           |           | NAME       |         | NAME          |
				// +---------- +-----------+-----------+------------+--     --+---------------+
				// ^           ^ (LSB-MSB) ^           
				// |           |           |           
				// |<--- A --->|<--- B --->|<--- C ---> <--------------- D ------------------>
				// |           |           |
				// |           |           |
				// |           |           +--- PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX
				// |           +--------------- PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX
				// +--------------------------- PL_PROTOCOL_PL_OPEN_INPUT_OPCODE_INDEX 
				//
				// Note:
				//    A = PL_PROTOCOL_OPCODE_SIZE
				//    B = PL_PROTOCOL_COUNTERS_COUNT_SIZE
				//    C = variable
				//    D = variable
				//-------------------------------------------------------------
#ifndef __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// decode PL_PROTOCOL_OPCODE_OPEN message.
				//-------------------------------------------------------------
				memcpy(
					&pl_counters_count,
					&input_message[
						PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX
					],
					PL_PROTOCOL_UINT_SIZE
				);
				memcpy(
					&message_size,
					&input_message[
						PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX
					],
					PL_PROTOCOL_SIZET_SIZE
				);
				length = (size_t)message_size;
				memcpy(
					pl_application_name,
					&input_message[			
						PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX + 
						PL_PROTOCOL_SIZET_SIZE
					],
					length
				);
				memory_size = 
					pl_counters_count * 
					PL_PROTOCOL_PPCHAR_SIZE
				;
				pl_counters_names = (PL_PROTOCOL_PPCHAR)malloc(memory_size);
				if(pl_counters_names == NULL) {
					// Critial error - error routine will try to stop the agent.
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_open_errors_count);
					PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
				}
				memset(
					pl_counters_names,
					0,
					memory_size
				);

				p_string = (PL_PROTOCOL_PCHAR)&input_message[
					PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX +
					PL_PROTOCOL_SIZET_SIZE +
					length
				];
				for(
					counter_index = 0; 
					counter_index < pl_counters_count; 
					counter_index++
				) {
					memcpy(
						&message_size,
						p_string,
						PL_PROTOCOL_SIZET_SIZE
					);
					length = (size_t)message_size;
					memory_size = (length + 1) * PL_PROTOCOL_CHAR_SIZE;
					pl_counters_names[counter_index] = 
						(PL_PROTOCOL_PCHAR)malloc(memory_size);
					if(pl_counters_names[counter_index] == NULL) {
						// Critial error - error routine will try to stop the agent.
						PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_open_errors_count);
						PL_AGENT_ERROR(PL_AGENT_OUT_OF_MEMORY);
					}
					memset(
						pl_counters_names[counter_index],
						0,
						memory_size
					);
					p_string += PL_PROTOCOL_SIZET_SIZE;
					memcpy(
						pl_counters_names[counter_index],
						p_string,
						length
					);
					p_string += length;
				} // for counter_index
				if(*p_string != PL_PROTOCOL_EOR) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_open_errors_count);
					PL_AGENT_ERROR(PL_AGENT_PROTOCOL_ERROR);
				}
#ifdef __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// TODO: use in-memory data
				//-------------------------------------------------------------
				// TODO:
#else // __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// call pl_open().
				//-------------------------------------------------------------
				pl_pld = pl_open(
					pl_application_name,
					pl_counters_count,
					(const char **)pl_counters_names,
					&pl_uuid
				);

				//-------------------------------------------------------------
				// Catch the error locally.
				//-------------------------------------------------------------
				if(pl_pld == PL_INVALID_DESCRIPTOR) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_open_errors_count);
					PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_PL_OPEN);
				}

				//-------------------------------------------------------------
				// Store UUID for further references.
				//-------------------------------------------------------------
				if(f_non_critical_error == 0) {
					memcpy(
						&pl_table.pl_array[pl_pld].uuid,
						&pl_uuid,
						PL_UUID_SIZE
					);
				}

				//-------------------------------------------------------------
				// Build the answer.
				//-------------------------------------------------------------
				// pl_open() return
				// +----------+-----------+----------+
				// | STATUS   | UUID      | PLD      |
				// | CODE     |           |          |
				// +----------+-----------+----------+ <-- PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX
				// ^          ^ (LSB-MSB) ^ (LSB-MSB)
				// |          |           |
				// |<-- A --->|<--- B --->|<-- C --->
				// |          |           |
				// |          |           +---- PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX
				// |          +---------------- PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX
				// +--------------------------- PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//   B = PL_PROTOCOL_UUID_SIZE
				//   C = PL_PROTOCOL_PLD_SIZE
				//-------------------------------------------------------------
				output_message[
					PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX
				] = PL_PROTOCOL_SUCCESS;
				memcpy(
					&output_message[PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX],
					&pl_uuid,
					PL_PROTOCOL_UUID_SIZE
				 );
				memcpy(
					&output_message[PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX],
					&pl_pld,
					PL_PROTOCOL_PLD_SIZE
				);
				output_message[
					PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX
				] = PL_PROTOCOL_EOR;
#endif // __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// free memory used to store counters names.
				//-------------------------------------------------------------
				if(pl_counters_names != NULL) {
					for(
						counter_index = 0; 
						counter_index < pl_counters_count; 
						counter_index++
					) {
						if(pl_counters_names[counter_index] != NULL) {
							memset(
								pl_counters_names[counter_index],
								0,
								strlen(pl_counters_names[counter_index])
							);
							free(pl_counters_names[counter_index]);
							pl_counters_names[counter_index] = NULL;
						}
					} // for counter_index
					memset(
						pl_counters_names,
						0,
						pl_counters_count * PL_PROTOCOL_PPCHAR_SIZE
					);
					free(pl_counters_names);
					pl_counters_names = NULL;
				}
#else // __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// Build a successful, well formed - but dummy - answer.
				//-------------------------------------------------------------
				// pl_open() return
				// +----------+-----------+----------+
				// | STATUS   | UUID      | PLD      |
				// | CODE     |           |          |
				// +----------+-----------+----------+ <-- PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX
				// ^          ^ (LSB-MSB) ^ (LSB-MSB)
				// |          |           |
				// |<-- A --->|<--- B --->|<-- C --->
				// |          |           |
				// |          |           +---- PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX
				// |          +---------------- PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX
				// +--------------------------- PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//   B = PL_PROTOCOL_UUID_SIZE
				//   C = PL_PROTOCOL_PLD_SIZE
				//-------------------------------------------------------------
				output_message[PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX] = 
					PL_PROTOCOL_SUCCESS;
				memcpy(
					&output_message[PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX],
					&uuid,
					PL_PROTOCOL_UUID_SIZE
				 );
				memcpy(
					&output_message[PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX],
					&pld,
					PL_PROTOCOL_PLD_SIZE
				);
				output_message[PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX] = 
					PL_PROTOCOL_EOR;
#endif // __PL_DUMMY_AGENT__
				total_bytes_to_send = 
					PL_PROTOCOL_STATUS_SIZE +
					PL_PROTOCOL_UUID_SIZE +
					PL_PROTOCOL_PLD_SIZE +
					PL_PROTOCOL_EOR_SIZE
				;
				message_size = (PL_PROTOCOL_SIZET)total_bytes_to_send;
				memcpy(
					&output_message[PL_PROTOCOL_BYTES_INDEX],
					&message_size,
					PL_PROTOCOL_SIZET_SIZE
				);
				total_bytes_to_send += PL_PROTOCOL_SIZET_SIZE;
				break;

			/*
			@@@@@  @               @@    @@@@@  @@@@@   @@    @@@@  @    @
			@    @ @              @  @     @      @    @  @  @    @ @    @
			@    @ @             @    @    @      @   @    @ @      @    @
			@@@@@  @             @    @    @      @   @    @ @      @@@@@@
			@      @             @@@@@@    @      @   @@@@@@ @      @    @
			@      @             @    @    @      @   @    @ @    @ @    @
			@      @@@@@@        @    @    @      @   @    @  @@@@  @    @
						  @@@@@@
			*/
			case PL_PROTOCOL_OPCODE_ATTACH:

				//-------------------------------------------------------------
				// Update API utilization stats data
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_LOCKING_API_CALL_COUNTER_STRING,
					rank
				);
				PL_AGENT_INCREMENT_API_USE_COUNT(p->pl_attach_count);
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_UNLOCKING_API_CALL_COUNTER_STRING,
					rank
				);

				//-------------------------------------------------------------
				// Process pl_attach API call.
				//-------------------------------------------------------------
				// pl_attach()
				// +-----------+-------------------------------------------------------------+
				// | OPERATION | <string>                                                    |
				// | CODE      | PL CONFIG INI                                               |
				// |           | ABSOLUTE PATH                                               |
				// +---------- +-------------------------------------------------------------+
				// ^           ^
				// |           |
				// |<--- A --->|<---------------------- B ---------------------------------->
				// |           |
				// |           +--------------- PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX
				// +--------------------------- PL_PROTOCOL_PL_ATTACH_INPUT_OPCODE_INDEX
				//
				// Note:
				//    A = PL_PROTOCOL_OPCODE_SIZE
				//    B = variable
				//-------------------------------------------------------------
#ifndef __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// decode PL_PROTOCOL_OPCODE_ATTACH message.
				//-------------------------------------------------------------
				memcpy(
					&message_size,
					&input_message[
						PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX
					],
					PL_PROTOCOL_SIZET_SIZE
				);
				length = (size_t)message_size;
				memory_size = length * PL_PROTOCOL_CHAR_SIZE;
				memset(
					pl_config_file_name,
					0,
					sizeof(pl_config_file_name)
				);
				memcpy(
					pl_config_file_name,
					&input_message[
						PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX +
						PL_PROTOCOL_SIZET_SIZE
					],
					memory_size
				);
				if(input_message[
						PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX +
						PL_PROTOCOL_SIZET_SIZE +
						memory_size
					] != PL_PROTOCOL_EOR
				) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_attach_errors_count);
					PL_AGENT_ERROR(PL_AGENT_PROTOCOL_ERROR);
				}
#ifdef __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// TODO: use in-memory data
				//-------------------------------------------------------------
				// TODO:
#else // __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// perform PL_FOLDER translation.
				//-------------------------------------------------------------
#ifdef __PL_WINDOWS__
				pp = strstr(
					pl_config_file_name,
					PL_INI_NIX_FOLDER
				);
				if(pp != NULL) {
					memset(
						transposed_pl_config_file_name,
						0,
						sizeof(transposed_pl_config_file_name)
					);
					bytes_in_buffer = sizeof(transposed_pl_config_file_name);
					memset(
						transposed_pl_config_file_name,
						0,
						bytes_in_buffer
					);
					memcpy(
						transposed_pl_config_file_name,
						PL_INI_WINDOWS_FOLDER,
						bytes_in_buffer
					);
					bytes_in_buffer -= strlen(PL_INI_WINDOWS_FOLDER);
					if(bytes_in_buffer <= 0) {
						// Critial error - error routine will try to stop the agent.
						PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_attach_errors_count);
						PL_AGENT_ERROR(PL_AGENT_OUT_OF_BUFFER_SPACE);
					}
					strncat(
						transposed_pl_config_file_name,
						pp + strlen(PL_INI_NIX_FOLDER),
						bytes_in_buffer
					);
					start_byte_index = strlen(PL_INI_WINDOWS_FOLDER);
					end_byte_index = strlen(pl_config_file_name);
					for(
						buffer_index = start_byte_index; 
						buffer_index < end_byte_index; 
						buffer_index++
					) {
						if(
							transposed_pl_config_file_name[buffer_index] == 
							PL_INI_NIX_PATH_SEPARATOR_CHAR 
						) {
							transposed_pl_config_file_name[buffer_index] = 
								PL_INI_WINDOWS_PATH_SEPARATOR_CHAR
							;
						}
					}
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
				pp = strstr(
					pl_config_file_name,
					PL_INI_WINDOWS_LC_FOLDER
				);
				if(pp == NULL) {
					pp = strstr(
						pl_config_file_name,
						PL_INI_WINDOWS_FOLDER
					);
				}
				if(pp != NULL) {
					bytes_in_buffer = sizeof(transposed_pl_config_file_name);
					memset(
						transposed_pl_config_file_name,
						0,
						bytes_in_buffer
					);
					memcpy(
						transposed_pl_config_file_name,
						PL_INI_NIX_FOLDER,
						bytes_in_buffer
					);
					bytes_in_buffer -= strlen(PL_INI_NIX_FOLDER);
					if(bytes_in_buffer <= 0) {
						// Critial error - error routine will try to stop the agent.
						PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_attach_errors_count);
						PL_AGENT_ERROR(PL_AGENT_OUT_OF_BUFFER_SPACE);
					}
					strncat(
						transposed_pl_config_file_name,
						pp + strlen(PL_INI_WINDOWS_FOLDER),
						bytes_in_buffer
					);
					start_byte_index = strlen(PL_INI_NIX_FOLDER);
					end_byte_index = strlen(pl_config_file_name);
					for(
						buffer_index = start_byte_index; 
						buffer_index < end_byte_index; 
						buffer_index++
					) {
						if(
							transposed_pl_config_file_name[buffer_index] == 
							PL_INI_WINDOWS_PATH_SEPARATOR_CHAR
						) {
							transposed_pl_config_file_name[buffer_index] = 
								PL_INI_NIX_PATH_SEPARATOR_CHAR
							;
						}
					}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
				}

				//-------------------------------------------------------------
				// call pl_attach().
				//-------------------------------------------------------------
				if(pp != NULL) {
					pl_pld = pl_attach(
						transposed_pl_config_file_name
					);
				} else {
					pl_pld = pl_attach(
						pl_config_file_name
					);
				}

				//-------------------------------------------------------------
				// Catch the error locally.
				//-------------------------------------------------------------
				if(pl_pld == PL_INVALID_DESCRIPTOR) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_attach_errors_count);
					PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_PL_ATTACH);
				}

				//-------------------------------------------------------------
				// create uuid.
				//-------------------------------------------------------------
				if(f_non_critical_error == 0) {
#ifdef __PL_WINDOWS__
#ifndef __PL_CONSTANT_UUID__
					rpc_ret = UuidCreate(&pl_uuid);
					if(rpc_ret != RPC_S_OK) {
						// Critial error - error routine will try to stop the
						// agent.
						PL_AGENT_INCREMENT_ERROR_COUNT(
							p->pl_attach_errors_count
						);
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CREATE_UUID);
					}
#else // __PL_CONSTANT_UUID__
					ZeroMemory(
						pl_uuid, 
						sizeof(uuid_t)
					); 
#endif // __PL_CONSTANT_UUID__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
#ifndef __PL_CONSTANT_UUID__
					uuid_generate(pl_uuid);
#else // !__PL_CONSTANT_UUID__
					memset(
						&pl_uuid,
						0,
						sizeof(uuid_t)
					);
#endif // !__PL_CONSTANT_UUID__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
				}

				//-------------------------------------------------------------
				// Build the answer.
				//-------------------------------------------------------------
				// pl_attach() return
				// +----------+-----------+-----------+----------+
				// | STATUS   | UUID      | PLD       | COUNTERS |
				// | CODE     |           |           | COUNT    |
				// +----------+-----------+-----------+----------+ <-- PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX
				// ^          ^ (LSB-MSB) ^ (LSB-MSB) ^ (LSB-MSB)         
				// |          |           |           |
				// |<-- A --->|<--- B --->|<--- C --->|<-- D --->
				// |          |           |           +--- PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX
				// |          |           +--------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX
				// |          +--------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX
				// +-------------------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//   B = PL_PROTOCOL_UUID_SIZE
				//   C = PL_PROTOCOL_PLD_SIZE
				//   D = PL_PROTOCOL_COUNTERS_COUNT_SIZE
				//-------------------------------------------------------------
				if(f_non_critical_error == 0) {
					output_message[
						PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX
					] = PL_PROTOCOL_SUCCESS;
				} else {
					output_message[
						PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX
					] = PL_PROTOCOL_FAILURE;
				}
				memcpy(
					&output_message[PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX],
					&pl_uuid,
					PL_PROTOCOL_UUID_SIZE
				 );
				memcpy(
					&output_message[PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX],
					&pl_pld,
					PL_PROTOCOL_PLD_SIZE
				);
				if(f_non_critical_error == 0) {
					memcpy(
						&output_message[PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX],
						&pl_table.pl_array[pl_pld].pl_counters_count,
						PL_PROTOCOL_COUNTERS_COUNT_SIZE
					);
				}
				output_message[
					PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX
				] = PL_PROTOCOL_EOR;
#endif // __PL_IN_MEMORY__
#else // __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// Build a successful, well formed - but dummy - answer.
				//-------------------------------------------------------------
				// pl_attach() return
				// +----------+-----------+-----------+----------+
				// | STATUS   | UUID      | PLD       | COUNTERS |
				// | CODE     |           |           | COUNT    |
				// +----------+-----------+-----------+----------+ <-- PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX
				// ^          ^ (LSB-MSB) ^ (LSB-MSB) ^ (LSB-MSB)         
				// |          |           |           |
				// |<-- A --->|<--- B --->|<--- C --->|<-- D --->
				// |          |           |           +--- PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX
				// |          |           +--------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX
				// |          +--------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX
				// +-------------------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//   B = PL_PROTOCOL_UUID_SIZE
				//   C = PL_PROTOCOL_PLD_SIZE
				//   D = PL_PROTOCOL_COUNTERS_COUNT_SIZE				
				//-------------------------------------------------------------
				output_message[PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX] = 
					PL_PROTOCOL_SUCCESS;
				memcpy(
					&output_message[PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX],
					&uuid,
					PL_PROTOCOL_UUID_SIZE
				 );
				memcpy(
					&output_message[PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX],
					&pld,
					PL_PROTOCOL_PLD_SIZE
				);
				memcpy(
					&output_message[PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX],
					&counters_count,
					PL_PROTOCOL_COUNTERS_COUNT_SIZE
				);
				output_message[PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX] = 
					PL_PROTOCOL_EOR;
#endif // __PL_DUMMY_AGENT__
				total_bytes_to_send = 
					PL_PROTOCOL_STATUS_SIZE +
					PL_PROTOCOL_UUID_SIZE +
					PL_PROTOCOL_PLD_SIZE +
					PL_PROTOCOL_COUNTERS_COUNT_SIZE +
					PL_PROTOCOL_EOR_SIZE
				;
				message_size = (PL_PROTOCOL_SIZET)total_bytes_to_send;
				memcpy(
					&output_message[PL_PROTOCOL_BYTES_INDEX],
					&message_size,
					PL_PROTOCOL_SIZET_SIZE
				);
				total_bytes_to_send += PL_PROTOCOL_SIZET_SIZE;
				break;

			/*
			@@@@@  @              @@@@  @       @@@@   @@@@  @@@@@@
			@    @ @             @    @ @      @    @ @    @ @
			@    @ @             @      @      @    @ @      @
			@@@@@  @             @      @      @    @  @@@@  @@@@@@
			@      @             @      @      @    @      @ @
			@      @             @    @ @      @    @      @ @
			@      @@@@@@         @@@@  @@@@@@  @@@@  @@@@@  @@@@@@
						  @@@@@@
			*/
			case PL_PROTOCOL_OPCODE_CLOSE:

				//-------------------------------------------------------------
				// Update API utilization stats data
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_LOCKING_API_CALL_COUNTER_STRING,
					rank
				);
				PL_AGENT_INCREMENT_API_USE_COUNT(p->pl_close_count);
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_UNLOCKING_API_CALL_COUNTER_STRING,
					rank
				);

				//-------------------------------------------------------------
				// Process pl_close API call.
				//-------------------------------------------------------------
				// pl_close()
				// +-----------+----------+----------+
				// | OPERATION | UUID     | PLD      |
				// | CODE      |          |          |
				// +-----------+----------+----------+
				// ^           ^ (LSB-MSB)^ (LSB-MSB)          
				// |           |          |
				// |<--- A --->|<--- B -->|<-- C --->
				// |           |          |
				// |           |          +---- PL_PROTOCOL_PL_CLOSE_OUTPUT_PLD_INDEX
				// |           +--------------- PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX
				// +--------------------------- PL_PROTOCOL_PL_CLOSE_INPUT_OPCODE_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_OPCODE_SIZE
				//   B = PL_PROTOCOL_UUID_SIZE
				//   C = PL_PROTOCOL_PLD_SIZE
				//-------------------------------------------------------------
#ifndef __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// decode PL_PROTOCOL_OPCODE_CLOSE message.
				//-------------------------------------------------------------
				memcpy(
					&uuid,
					&input_message[PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX],
					PL_PROTOCOL_UUID_SIZE
				);
				memcpy(
					&pl_pld,
					&input_message[PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX],
					PL_PROTOCOL_PLD_SIZE
				);
				if(
					input_message[PL_PROTOCOL_PL_CLOSE_INPUT_EOR_INDEX] != 
					PL_PROTOCOL_EOR
				) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_close_errors_count);
					PL_AGENT_ERROR(PL_AGENT_PROTOCOL_ERROR);
				}
#ifdef __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// TODO: use in-memory data
				//-------------------------------------------------------------
				// TODO:
#else // __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// call pl_close()
				//-------------------------------------------------------------
				ret = pl_close(
					pl_pld
				);

				//-------------------------------------------------------------
				// Catch the error locally.
				//-------------------------------------------------------------
				if(ret != PL_SUCCESS) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_close_errors_count);
					PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_PL_CLOSE);
				}

				//-------------------------------------------------------------
				// Build the answer.
				//-------------------------------------------------------------
				// pl_close() return
				// +----------+
				// | STATUS   |
				// | CODE     |
				// +----------+ <--- PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX
				// ^
				// |
				// |<-- A --->
				// |
				// +--------------------------- PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//-------------------------------------------------------------
				if(ret == PL_SUCCESS) {
					output_message[PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX] = 
						PL_PROTOCOL_SUCCESS;
				} else {
					output_message[PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX] = 
						PL_PROTOCOL_FAILURE;
				}
				output_message[PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX] = 
					PL_PROTOCOL_EOR;
#endif // __PL_IN_MEMORY__
#else // __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// Build a successful, well formed - but dummy - answer.
				//-------------------------------------------------------------
				// pl_close() return
				// +----------+
				// | STATUS   |
				// | CODE     |
				// +----------+ <--- PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX
				// ^
				// |
				// |<-- A --->
				// |
				// +--------------------------- PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//-------------------------------------------------------------
				output_message[PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX] = 
					PL_PROTOCOL_SUCCESS;
				output_message[PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX] = 
					PL_PROTOCOL_EOR;
#endif // __PL_DUMMY_AGENT__
				total_bytes_to_send = 
					PL_PROTOCOL_STATUS_SIZE +
					PL_PROTOCOL_EOR_SIZE
				;
				message_size = (PL_PROTOCOL_SIZET)total_bytes_to_send;
				memcpy(
					&output_message[PL_PROTOCOL_BYTES_INDEX],
					&message_size,
					PL_PROTOCOL_SIZET_SIZE
				);
				total_bytes_to_send += PL_PROTOCOL_SIZET_SIZE;
				break;

			/*
			@@@@@  @             @@@@@  @@@@@@   @@   @@@@@
			@    @ @             @    @ @       @  @  @    @
			@    @ @             @    @ @      @    @ @    @
			@@@@@  @             @@@@@  @@@@@@ @    @ @    @
			@      @             @  @   @      @@@@@@ @    @
			@      @             @   @  @      @    @ @    @
			@      @@@@@@        @    @ @@@@@@ @    @ @@@@@
						  @@@@@@
			*/
			case PL_PROTOCOL_OPCODE_READ:

				//-------------------------------------------------------------
				// Update API utilization stats data
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_LOCKING_API_CALL_COUNTER_STRING,
					rank
				);
				PL_AGENT_INCREMENT_API_USE_COUNT(p->pl_read_count);
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_UNLOCKING_API_CALL_COUNTER_STRING,
					rank
				);

				//-------------------------------------------------------------
				// Process pl_read API call.
				//-------------------------------------------------------------
				// pl_read()
				// +-----------+---------+---------+-----------+
				// | OPERATION | UUID    | PLD     | OFFSET    |
				// | CODE      |         |         |           |
				// +-----------+---------+---------+-----------+ <- PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX
				// ^           ^         ^         ^
				// |           |         |         |
				// |<--- A --->|<-- B -->|<-- C -->|<--- D --->
				// |           |(LSB-MSB)|(LSB-MSB)|(LSB-MSB)
				// |           |         |         |
				// |           |         |         +------- PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX
				// |           |         +----------------- PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX
				// |           +--------------------------- PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX
				// +--------------------------------------- PL_PROTOCOL_PL_READ_INPUT_OPCODE_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_OPCODE_SIZE
				//   B = PL_PROTOCOL_UUID_SIZE
				//   C = PL_PROTOCOL_PLD_SIZE
				//   D = PL_PROTOCOL_COUNTER_OFFSET_SIZE
				//-------------------------------------------------------------
#ifndef __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// decode PL_PROTOCOL_OPCODE_READ message.
				//-------------------------------------------------------------
				memcpy(
					&uuid,
					&input_message[PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX],
					PL_PROTOCOL_UUID_SIZE
				);
				memcpy(
					&pl_pld,
					&input_message[PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX],
					PL_PROTOCOL_PLD_SIZE
				);
				memcpy(
					&counter_offset,
					&input_message[PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX],
					PL_PROTOCOL_COUNTER_OFFSET_SIZE
				);
				if(
					input_message[PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX] != 
					PL_PROTOCOL_EOR
				) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_read_errors_count);
					PL_AGENT_ERROR(PL_AGENT_PROTOCOL_ERROR);
				}
#ifdef __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// TODO: use in-memory data
				//-------------------------------------------------------------
				// TODO:
#else // __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// call pl_read()
				//-------------------------------------------------------------
				ret = pl_read(
					pl_pld,
					(void *)&counter_value,
					counter_offset
				);

				//-------------------------------------------------------------
				// Catch the error locally.
				//-------------------------------------------------------------
				if(ret != PL_SUCCESS) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_read_errors_count);
					PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_PL_READ);
				}

				//-------------------------------------------------------------
				// Build the answer.
				//-------------------------------------------------------------
				// pl_read() return
				// +----------+----------+
				// | STATUS   | VALUE    |
				// | CODE     |          |
				// +----------+----------+ <--- PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX
				// ^          ^
				// |          |
				// |<-- A --->|<-- B --->
				// |          |(LSB-MSB)
				// |          |
				// |          +---------------------------- PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX
				// +--------------------------------------- PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//   B = PL_PROTOCOL_ULL_SIZE
				//-------------------------------------------------------------
				if(ret == PL_SUCCESS) {
					output_message[PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX] = 
						PL_PROTOCOL_SUCCESS;
					memcpy(
						&output_message[PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX],
						&counter_value,
						PL_PROTOCOL_ULL_SIZE
					);
				} else {
					output_message[PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX] = 
						PL_PROTOCOL_FAILURE;
				}
				output_message[PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX] = 
					PL_PROTOCOL_EOR;
#endif // __PL_IN_MEMORY__
#else // __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// Build a successful, well formed - but dummy - answer.
				//-------------------------------------------------------------
				// pl_read() return
				// +----------+----------+
				// | STATUS   | VALUE    |
				// | CODE     |          |
				// +----------+----------+ <--- PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX
				// ^          ^
				// |          |
				// |<-- A --->|<-- B --->
				// |          |(LSB-MSB)
				// |          |
				// |          +---------------------------- PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX
				// +--------------------------------------- PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//   B = PL_PROTOCOL_ULL_SIZE
				//-------------------------------------------------------------
				output_message[PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX] = 
					PL_PROTOCOL_SUCCESS;
				output_message[PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX] = 
					PL_PROTOCOL_EOR;
#endif // __PL_DUMMY_AGENT__
				total_bytes_to_send = 
					PL_PROTOCOL_STATUS_SIZE +
					PL_PROTOCOL_ULL_SIZE +
					PL_PROTOCOL_EOR_SIZE
				;
				message_size = (PL_PROTOCOL_SIZET)total_bytes_to_send;
				memcpy(
					&output_message[PL_PROTOCOL_BYTES_INDEX],
					&message_size,
					PL_PROTOCOL_SIZET_SIZE
				);
				total_bytes_to_send += PL_PROTOCOL_SIZET_SIZE;
				break;

			/*
			@@@@@  @             @    @ @@@@@  @@@@@   @@@@@ @@@@@@
			@    @ @             @    @ @    @   @       @   @
			@    @ @             @  @ @ @    @   @       @   @
			@@@@@  @             @  @ @ @@@@@    @       @   @@@@@@
			@      @             @  @ @ @  @     @       @   @
			@      @              @ @ @ @   @    @       @   @
			@      @@@@@@          @ @  @    @ @@@@@     @   @@@@@@
						  @@@@@@
			*/
			case PL_PROTOCOL_OPCODE_WRITE:

				//-------------------------------------------------------------
				// Update API utilization stats data
				//-------------------------------------------------------------
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_LOCKING_API_CALL_COUNTER_STRING,
					rank
				);
				PL_AGENT_INCREMENT_API_USE_COUNT(p->pl_write_count);
				PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
					PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_UNLOCKING_API_CALL_COUNTER_STRING,
					rank
				);

				//-------------------------------------------------------------
				// Process pl_write API call.
				//-------------------------------------------------------------
				// pl_write()
				// +-----------+---------+---------+---------+----------+
				// | OPERATION | UUID    | PLD     | OFFSET  | VALUE    |
				// | CODE      |         |         |         |          |
				// +-----------+---------+---------+---------+----------+ <- PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX
				// ^           ^         ^         ^         ^
				// |           |         |         |         |
				// |<--- A --->|<-- B -->|<-- C -->|<-- D -->|<-- E --->
				// |           |(LSB-MSB)|(LSB-MSB)|(LSB-MSB)|(LSB-MSB)
				// |           |         |         |         |
				// |           |         |         |         +--- PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX
				// |           |         |         +------------- PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX
				// |           |         +----------------------- PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX
				// |           +--------------------------------- PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX
				// +--------------------------------------------- PL_PROTOCOL_PL_WRITE_INPUT_OPCODE_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_OPCODE_SIZE
				//   B = PL_PROTOCOL_UUID_SIZE
				//   C = PL_PROTOCOL_PLD_SIZE
				//   D = PL_PROTOCOL_COUNTER_OFFSET_SIZE
				//   E = PL_PROTOCOL_ULL_SIZE
				//-------------------------------------------------------------
#ifndef __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// decode PL_PROTOCOL_OPCODE_WRITE message.
				//-------------------------------------------------------------
				memcpy(
					&uuid,
					&input_message[PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX],
					PL_PROTOCOL_UUID_SIZE
				);
				memcpy(
					&pl_pld,
					&input_message[PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX],
					PL_PROTOCOL_PLD_SIZE
				);
				memcpy(
					&counter_offset,
					&input_message[PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX],
					PL_PROTOCOL_COUNTER_OFFSET_SIZE
				);
				memcpy(
					&counter_value,
					&input_message[PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX],
					PL_PROTOCOL_ULL_SIZE
				);
				if(
					input_message[PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX] != 
					PL_PROTOCOL_EOR
				) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_write_errors_count);
					PL_AGENT_ERROR(PL_AGENT_PROTOCOL_ERROR);
				}
#ifdef __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// TODO: use in-memory data
				//-------------------------------------------------------------
				// TODO:
#else // __PL_IN_MEMORY__

				//-------------------------------------------------------------
				// call pl_write()
				//-------------------------------------------------------------
				ret = pl_write(
					pl_pld,
					(void *)&counter_value,
					counter_offset
				);

				//-------------------------------------------------------------
				// Catch the error locally.
				//-------------------------------------------------------------
				if(ret != PL_SUCCESS) {
					// Non critial error.
					f_non_critical_error = 1;
					PL_AGENT_INCREMENT_ERROR_COUNT(p->pl_write_errors_count);
					PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_PL_WRITE);
				}

				//-------------------------------------------------------------
				// Build the answer.
				//-------------------------------------------------------------
				// pl_write() return
				// +----------+
				// | STATUS   |
				// | CODE     |
				// +----------+ <--- PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX
				// ^
				// |
				// |<-- A --->
				// |
				// +--------------------------- PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//-------------------------------------------------------------
				if(ret == PL_SUCCESS) {
					output_message[PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX] = 
						PL_PROTOCOL_SUCCESS;
				} else {
					output_message[PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX] = 
						PL_PROTOCOL_FAILURE;
				}
				output_message[PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX] = 
					PL_PROTOCOL_EOR;
#endif // __PL_IN_MEMORY__
#else // __PL_DUMMY_AGENT__

				//-------------------------------------------------------------
				// Build a successful, well formed - but dummy - answer.
				//-------------------------------------------------------------
				// pl_write() return
				// +----------+
				// | STATUS   |
				// | CODE     |
				// +----------+ <--- PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX
				// ^
				// |
				// |<-- A --->
				// |
				// +--------------------------- PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX
				//
				// Note:
				//   A = PL_PROTOCOL_STATUS_SIZE
				//-------------------------------------------------------------
				output_message[PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX] = 
					PL_PROTOCOL_SUCCESS;
				output_message[PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX] = 
					PL_PROTOCOL_EOR;
#endif // __PL_DUMMY_AGENT__
				total_bytes_to_send = 
					PL_PROTOCOL_STATUS_SIZE +
					PL_PROTOCOL_EOR_SIZE
				;
				message_size = (PL_PROTOCOL_SIZET)total_bytes_to_send;
				memcpy(
					&output_message[PL_PROTOCOL_BYTES_INDEX],
					&message_size,
					PL_PROTOCOL_SIZET_SIZE
				);
				total_bytes_to_send += PL_PROTOCOL_SIZET_SIZE;
				break;

			/*
			@    @ @    @ @   @  @    @  @@@@  @    @ @    @         @@@@  @@@@@   @@@@   @@@@  @@@@@  @@@@@@
			@    @ @@   @ @  @   @@   @ @    @ @    @ @@   @        @    @ @    @ @    @ @    @ @    @ @
			@    @ @ @  @ @ @    @ @  @ @    @ @  @ @ @ @  @        @    @ @    @ @      @    @ @    @ @
			@    @ @ @  @ @@     @ @  @ @    @ @  @ @ @ @  @        @    @ @@@@@  @      @    @ @    @ @@@@@@
			@    @ @  @ @ @ @    @  @ @ @    @ @  @ @ @  @ @        @    @ @      @      @    @ @    @ @
			@    @ @   @@ @  @   @   @@ @    @  @ @ @ @   @@        @    @ @      @    @ @    @ @    @ @
			 @@@@  @    @ @   @  @    @  @@@@    @ @  @    @         @@@@  @       @@@@   @@@@  @@@@@  @@@@@@
			*/
			default:

				// Non critial error. Not accounted in stats.
				f_non_critical_error = 1;
				PL_AGENT_ERROR(PL_AGENT_PROTOCOL_UNKNOWN_OP_CODE); 
				goto pool_thread_skip_message;
				;
		} // switch op_code

		//---------------------------------------------------------------------
		// Send answer to client.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
			PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_SENDING_DATA_STRING,
			rank
		);

#ifdef _DEBUG
		pl_agent_decode_response(
			rank,
			input_message[PL_PROTOCOL_INPUT_OP_CODE_INDEX], 
			total_bytes_to_send,
			output_ipc_buffer.data
		);
#endif // _DEBUG

		bytes_sent = 0;
		bytes_to_send = total_bytes_to_send;
		do {
			ret = send(
				pd->new_socket, 
				&output_ipc_buffer.data[bytes_sent], 
				bytes_to_send, 
				0
			);
			if(ret == SOCKET_ERROR) {
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SEND_VIA_SOCKET); 
			}

#ifdef __PL_WINDOWS__
			bytes_sent += ret;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			bytes_sent += (size_t)ret;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			bytes_to_send = total_bytes_to_send - bytes_sent;
		} while(bytes_to_send > 0);

		//---------------------------------------------------------------------
		// Close socket.
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
			PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_CLOSING_IPC_STRING,
			rank
		);
		ret = shutdown(
			pd->new_socket, 
			SD_BOTH
		);
		if(ret == SOCKET_ERROR) {
#ifdef __PL_MACOSX__
			if(errno != ENOTCONN) { 
#endif // __PL_MACOSX__
				// Critial error - error routine will try to stop the agent.
				PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SHUTDOWN_SOCKET); 
#ifdef __PL_MACOSX__
			}
#endif // __PL_MACOSX__
		}

#ifdef __PL_WINDOWS__
		ret = closesocket(
			pd->new_socket
		);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = close(
			pd->new_socket
		);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		if(ret == SOCKET_ERROR) { 
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_CLOSE_SOCKET); 
		}
		pd->new_socket = INVALID_SOCKET;

pool_thread_skip_message:
		;

		/*
		@    @ @    @ @       @@@@   @@@@  @   @
		@    @ @@   @ @      @    @ @    @ @  @
		@    @ @ @  @ @      @    @ @      @ @
		@    @ @ @  @ @      @    @ @      @@
		@    @ @  @ @ @      @    @ @      @ @
		@    @ @   @@ @      @    @ @    @ @  @
		 @@@@  @    @ @@@@@@  @@@@   @@@@  @   @
		*/
		//---------------------------------------------------------------------
		// Unlock the thread's semaphore
		//---------------------------------------------------------------------
		PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
			PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_UNLOCKING_STRING, 
			rank
		);
#ifdef __PL_WINDOWS__
		bret = ReleaseSemaphore(
			p->pool_threads_data[rank].semaphore, 
			(LONG)1, 
			NULL
		);
		if(bret == FALSE) {
			// Critial error - error routine will try to stop the agent.
			PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); 
		}
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
		sem_post(&p->pool_threads_data[rank].semaphore);
#else // __PL_MACOSX__
		sem_post(p->pool_threads_data[rank].semaphore);
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	} // while f_running == 1

	/*
	@@@@@@ @    @ @@@@@         @    @   @@   @@@@@  @    @        @       @@@@   @@@@  @@@@@
	@      @@   @ @    @        @@  @@  @  @    @    @@   @        @      @    @ @    @ @    @
	@      @ @  @ @    @        @ @@ @ @    @   @    @ @  @        @      @    @ @    @ @    @
	@@@@@@ @ @  @ @    @        @    @ @    @   @    @ @  @        @      @    @ @    @ @@@@@
	@      @  @ @ @    @        @    @ @@@@@@   @    @  @ @        @      @    @ @    @ @
	@      @   @@ @    @        @    @ @    @   @    @   @@        @      @    @ @    @ @
	@@@@@@ @    @ @@@@@         @    @ @    @ @@@@@  @    @        @@@@@@  @@@@   @@@@  @
	*/

pool_thread_end:

	//-------------------------------------------------------------------------
	// Signal pool thread end to primary thread (waiting on us)
	//-------------------------------------------------------------------------
	PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
		PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_ENDED_STRING, 
		rank
	);
#ifdef __PL_WINDOWS__
	SetEvent(p->h_pool_threads_done[rank]);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
#ifndef __PL_MACOSX__
	sem_post(&p->h_pool_threads_done[rank]);
#else // __PL_MACOSX__
	sem_post(p->h_pool_threads_done[rank]);
#endif // __PL_MACOSX__
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Return
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	return((PTHREAD_START_ROUTINE)PL_SUCCESS);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
	return(PL_SUCCESS);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
}

/*-----------------------------------------------------------------------------
Function: switch_socket_to_blocking_mode.
Purpose : switch a give socket into blocking mode
In      : a socket.
Out     : none.
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
10/15/2010    Jamel Tayeb             Creation.
*/
PL_STATUS switch_socket_to_blocking_mode(SOCKET s) {

	int ret = -1;

#ifdef __PL_WINDOWS__

	ULONG mode = 0; // 0, non-blocking mode is enabled.

	assert(s != INVALID_SOCKET);

	ret = ioctlsocket(
		s, 
		FIONBIO, 
		&mode
	);
	if(ret != 0) {
		goto switch_socket_to_blocking_mode_error;
	}

#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

	int actual_flags = -1;

	assert(s != INVALID_SOCKET);

	actual_flags = fcntl(
		s,
		F_GETFL,
		0
	);
	if(actual_flags == -1) {
		goto switch_socket_to_blocking_mode_error;
	}
	ret = fcntl(
		s, 
		F_SETFL, 
		actual_flags | ~O_NONBLOCK
	);
	if(ret == -1) {
		goto switch_socket_to_blocking_mode_error;
	}
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	return(PL_SUCCESS);
switch_socket_to_blocking_mode_error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: switch_socket_to_non_blocking_mode.
Purpose : switch a give socket into non-blocking mode
In      : a socket.
Out     : none.
Return  : status code

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
10/15/2010    Jamel Tayeb             Creation.
*/
PL_STATUS switch_socket_to_non_blocking_mode(SOCKET s) {

	int ret = -1;

#ifdef __PL_WINDOWS__

	ULONG mode = 1; // != 0, non-blocking mode is enabled.

	assert(s != INVALID_SOCKET);

	ret = ioctlsocket(
		s, 
		FIONBIO, 
		&mode
	);
	if(ret != 0) {
		goto switch_socket_to_non_blocking_mode_error;
	}

#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

	int actual_flags = -1;

	assert(s != INVALID_SOCKET);

	actual_flags = fcntl(
		s,
		F_GETFL,
		0
	);
	if(actual_flags == -1) {
		goto switch_socket_to_non_blocking_mode_error;
	}
	ret = fcntl(
		s, 
		F_SETFL, 
		actual_flags | O_NONBLOCK
	);
	if(ret == -1) {
		goto switch_socket_to_non_blocking_mode_error;
	}

#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	return(PL_SUCCESS);
switch_socket_to_non_blocking_mode_error:
	return(PL_FAILURE);
}

#ifdef _DEBUG
/*-----------------------------------------------------------------------------
Function: pl_agent_hex_dump_string
Purpose : decode a message
In      : a string, length of the message in byte(s) and pointer to char buffer
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
07/10/2010    Jamel Tayeb             Creation.
*/
void pl_agent_hex_dump_string(char *o, size_t s, char *p) {

	//-------------------------------------------------------------------------
	// Generic data.
	//-------------------------------------------------------------------------
	char *p_string = NULL;
	unsigned int i = 0;
	unsigned int d = 0;
	char tmp_buffer[PL_PROTOCOL_MESSAGE_MAX_SIZE] = { '\0' };
	char buffer[PL_PROTOCOL_MESSAGE_MAX_SIZE] = { '\0' };

	//-------------------------------------------------------------------------

	assert(o != NULL);
	assert(p != NULL);
	assert(s > 0);

	//-------------------------------------------------------------------------
	// Message HEX dump.
	//-------------------------------------------------------------------------
	memset(
		buffer,
		0,
		sizeof(buffer)
	);
	p_string = buffer;
	d = sprintf(
		buffer,
		PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_LFULL_STRING,
		o
	);
	p_string += d;
	for(i = 0; i < s; i++) {
		sprintf(
			p_string,
			"%02X ", 
			(unsigned char)p[i]
		);
		p_string += strlen("XXX");
	}
	sprintf(
		p_string,
		"\n"
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);
}

/*-----------------------------------------------------------------------------
Function: pl_agent_hex_dump_message
Purpose : decode a message
In      : a string, length of the message in byte(s) and pointer to char buffer
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
07/10/2010    Jamel Tayeb             Creation.
*/
void pl_agent_hex_dump_message(char *o, size_t s, char *p) {

	//-------------------------------------------------------------------------
	// Generic data.
	//-------------------------------------------------------------------------
	char *p_string = NULL;
	unsigned int i = 0;
	unsigned int d = 0;
	char tmp_buffer[PL_PROTOCOL_MESSAGE_MAX_SIZE] = { '\0' };
	char buffer[PL_PROTOCOL_MESSAGE_MAX_SIZE] = { '\0' };

	//-------------------------------------------------------------------------

	assert(o != NULL);
	assert(p != NULL);
	assert(s > 0);

	//-------------------------------------------------------------------------
	// Message HEX dump.
	//-------------------------------------------------------------------------
	s += PL_PROTOCOL_SIZET_SIZE;
	sprintf(
		buffer, 
		PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_L1_STRING,
		o,
		(int)s, 
		(int)s
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);
	sprintf(
		buffer, 
		PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_L2_STRING,
		o,
		(int)(s - PL_PROTOCOL_SIZET_SIZE), 
		(int)(s - PL_PROTOCOL_SIZET_SIZE)
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);
	
	memset(
		buffer,
		0,
		sizeof(buffer)
	);
	p_string = buffer;
	d = sprintf(
		buffer,
		PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_LFULL_STRING,
		o
	);
	p_string += d;
	for(i = 0; i < s; i++) {
		sprintf(
			p_string,
			"%02X ", 
			(unsigned char)p[i]
		);
		p_string += strlen("XXX");
	}
	sprintf(
		p_string,
		"\n"
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);

	memset(
		buffer,
		0,
		sizeof(buffer)
	);
	p_string = buffer;
	d = sprintf(
		buffer,
		PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_LPARTIAL_STRING,
		o
	);
	p_string += d;
	for(i = PL_PROTOCOL_SIZET_SIZE; i < s; i++) {
		sprintf(
			p_string,
			"%02X ", 
			(unsigned char)p[i]
		);
		p_string += strlen("XXX");
	}
	sprintf(
		p_string,
		"\n"
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);
}

/*-----------------------------------------------------------------------------
Function: pl_agent_decode_message
Purpose : decode a message
In      : thread rank, length of the message in byte(s) and pointer to char buffer
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
07/10/2010    Jamel Tayeb             Creation.
*/
void pl_agent_decode_message(int r, size_t s, char *p) {

	//-------------------------------------------------------------------------
	// Generic data.
	//-------------------------------------------------------------------------
	char *p_string = NULL;
	size_t length = 0;
	unsigned int i = 0;

#ifdef __PL_WINDOWS__
	size_t st_ret = 0;
	char *pu = NULL;
	char cvt_buffer[PL_MAX_PATH] = { '\0' };
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
	char uuid_buffer[PL_MAX_PATH] = { '\0' };
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// PL data.
	//-------------------------------------------------------------------------
	unsigned int pl_counters_count = 0;
	char pl_config_file_name[PL_MAX_PATH] = { '\0' };
	char pl_application_name[PL_MAX_PATH] = { '\0' };
	char pl_counter_name[PL_MAX_PATH] = { '\0' };
	char tmp_buffer[PL_PROTOCOL_MESSAGE_MAX_SIZE] = { '\0' };
	char buffer[PL_PROTOCOL_MESSAGE_MAX_SIZE] = { '\0' };
	uuid_t uuid;
	int pld = PL_INVALID_DESCRIPTOR;
	unsigned long long counter_value = 0;
	unsigned int counter_offset = 0;

	//-------------------------------------------------------------------------

	assert(p != NULL);
	assert(s > 0);

	//-------------------------------------------------------------------------
	// Message HEX dump.
	//-------------------------------------------------------------------------
	s += PL_PROTOCOL_SIZET_SIZE;
	sprintf(
		buffer, 
		PL_AGENT_DEBUG_MESSAGE_DUMP_L1_STRING,
		r,
		(int)s, 
		(int)s
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);
	sprintf(
		buffer, 
		PL_AGENT_DEBUG_MESSAGE_DUMP_L2_STRING,
		r,
		(int)(s - PL_PROTOCOL_SIZET_SIZE), 
		(int)(s - PL_PROTOCOL_SIZET_SIZE)
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);
	memset(
		buffer,
		0,
		sizeof(buffer)
	);
	p_string = buffer;
	sprintf(
		buffer,
		PL_AGENT_DEBUG_MESSAGE_DUMP_LFULL_STRING,
		r
	);
	p_string += strlen(PL_AGENT_DEBUG_MESSAGE_DUMP_LFULL_STRING) - 1;
	for(i = 0; i < s; i++) {
		sprintf(
			p_string,
			"%02X ", 
			(unsigned char)p[i]
		);
		p_string += strlen("XXX");
	}
	sprintf(
		p_string,
		"\n"
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);

	memset(
		buffer,
		0,
		sizeof(buffer)
	);
	p_string = buffer;
	sprintf(
		buffer,
		PL_AGENT_DEBUG_MESSAGE_DUMP_LPARTIAL_STRING,
		r
	);
	p_string += strlen(PL_AGENT_DEBUG_MESSAGE_DUMP_LPARTIAL_STRING) - 1;
	for(i = PL_PROTOCOL_SIZET_SIZE; i < s; i++) {
		sprintf(
			p_string,
			"%02X ", 
			(unsigned char)p[i]
		);
		p_string += strlen("XXX");
	}
	sprintf(
		p_string,
		"\n"
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);

	//-------------------------------------------------------------------------
	// Decode Message.
	//-------------------------------------------------------------------------
	switch(p[PL_PROTOCOL_INPUT_OP_CODE_INDEX]) {

		/*
		@@@@@  @              @@@@  @@@@@  @@@@@@ @    @
		@    @ @             @    @ @    @ @      @@   @
		@    @ @             @    @ @    @ @      @ @  @
		@@@@@  @             @    @ @@@@@  @@@@@@ @ @  @
		@      @             @    @ @      @      @  @ @
		@      @             @    @ @      @      @   @@
		@      @@@@@@         @@@@  @      @@@@@@ @    @
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_OPEN:

			//-----------------------------------------------------------------
			// pl_open()
			// +-----------+-----------+-----------+------------+--     --+---------------+
			// | OPERATION | COUNTERS  |  <string> | <string>   |         | <string>      |
			// | CODE      | COUNT (N) | APP NAME  | COUNTER 0  |   ...   | COUNTER (N-1) |
			// |           |           |           | NAME       |         | NAME          |
			// +---------- +-----------+-----------+------------+--     --+---------------+
			// ^           ^ (LSB-MSB) ^           
			// |           |           |           
			// |<--- A --->|<--- B --->|<--- C ---> <--------------- D ------------------>
			// |           |           |
			// |           |           |
			// |           |           +--- PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX
			// |           +--------------- PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX
			// +--------------------------- PL_PROTOCOL_PL_OPEN_INPUT_OPCODE_INDEX 
			//
			// Note:
			//    A = PL_PROTOCOL_OPCODE_SIZE
			//    B = PL_PROTOCOL_COUNTERS_COUNT_SIZE
			//    C = variable
			//    D = variable
			//-----------------------------------------------------------------
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_OP_CODE_STRING,
				r
			);
			memcpy(
				&pl_counters_count,
				&p[PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX],
				PL_PROTOCOL_UINT_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_COUNTERS_COUNT_STRING,
				r,
				pl_counters_count
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memcpy(
				&length,
				&p[PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX],
				PL_PROTOCOL_SIZET_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_APPLICATION_NAME_LENGTH_STRING,
				r,
				(int)length
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memset(
				buffer,
				0,
				sizeof(pl_application_name)
			);
			memcpy(
				pl_application_name,
				&p[			
					PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX + 
					PL_PROTOCOL_SIZET_SIZE
				],
				length
			);
			memcpy(
				&length,
				&p[PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX],
				PL_PROTOCOL_SIZET_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_APPLICATION_NAME_STRING,
				r,
				pl_application_name
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			p_string = &p[
				PL_PROTOCOL_PL_OPEN_INPUT_APPLICATION_NAME_STRING_INDEX + 
				PL_PROTOCOL_SIZET_SIZE +
				length
			];
			for(i = 0; i < pl_counters_count; i++) {
				memcpy(
					&length,
					p_string,
					PL_PROTOCOL_SIZET_SIZE
				);
				memset(
					buffer,
					0,
					sizeof(buffer)
				);
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_COUNTER_NAME_LENGHT_STRING,
					r,
					i,
					(int)length
				);
				PL_AGENT_DEBUG_MESSAGE(buffer);
				p_string += PL_PROTOCOL_SIZET_SIZE;
				memset(
					pl_counter_name,
					0,
					sizeof(pl_counter_name)
				);
				memcpy(
					pl_counter_name,
					p_string,
					length
				);
				memset(
					buffer,
					0,
					sizeof(buffer)
				);
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_COUNTER_NAME_STRING,
					r,
					i,
					pl_counter_name
				);
				PL_AGENT_DEBUG_MESSAGE(buffer);
				p_string += length;
			} // for i
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			if(*p_string != PL_PROTOCOL_EOR) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_LAST_BYTE_STRING,
					r,
					*p_string,
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_LAST_BYTE_STRING,
					r,
					*p_string,
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		/*
		@@@@@  @               @@    @@@@@  @@@@@   @@    @@@@  @    @
		@    @ @              @  @     @      @    @  @  @    @ @    @
		@    @ @             @    @    @      @   @    @ @      @    @
		@@@@@  @             @    @    @      @   @    @ @      @@@@@@
		@      @             @@@@@@    @      @   @@@@@@ @      @    @
		@      @             @    @    @      @   @    @ @    @ @    @
		@      @@@@@@        @    @    @      @   @    @  @@@@  @    @
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_ATTACH:

			//-----------------------------------------------------------------------------
			// pl_attach()
			// +-----------+-------------------------------------------------------------+
			// | OPERATION | <string>                                                    |
			// | CODE      | PL CONFIG INI                                               |
			// |           | ABSOLUTE PATH                                               |
			// +---------- +-------------------------------------------------------------+
			// ^           ^
			// |           |
			// |<--- A --->|<---------------------- B ---------------------------------->
			// |           |
			// |           +--------------- PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX
			// +--------------------------- PL_PROTOCOL_PL_ATTACH_INPUT_OPCODE_INDEX
			//
			// Note:
			//    A = PL_PROTOCOL_OPCODE_SIZE
			//    B = variable
			//-----------------------------------------------------------------------------
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_OP_CODE_STRING,
				r
			);
			memcpy(
				&length,
				&p[PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX],
				PL_PROTOCOL_SIZET_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_CONFIG_FILE_NAME_LENGHT_STRING,
				r,
				(int)length
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memset(
				pl_config_file_name,
				0,
				sizeof(pl_config_file_name)
			);
			memcpy(
				pl_config_file_name,
				&p[			
					PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX + 
					PL_PROTOCOL_SIZET_SIZE
				],
				length
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_CONFIG_FILE_NAME_STRING,
				r,
				pl_config_file_name
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			p_string = &p[
				PL_PROTOCOL_PL_ATTACH_INPUT_PL_CONFIG_STRING_INDEX + 
				PL_PROTOCOL_SIZET_SIZE +
				length
			];
			if(*p_string != PL_PROTOCOL_EOR) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_LAST_BYTE_STRING,
					r,
					*p_string,
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_LAST_BYTE_STRING,
					r,
					*p_string,
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		/*
		@@@@@  @              @@@@  @       @@@@   @@@@  @@@@@@
		@    @ @             @    @ @      @    @ @    @ @
		@    @ @             @      @      @    @ @      @
		@@@@@  @             @      @      @    @  @@@@  @@@@@@
		@      @             @      @      @    @      @ @
		@      @             @    @ @      @    @      @ @
		@      @@@@@@         @@@@  @@@@@@  @@@@  @@@@@  @@@@@@
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_CLOSE:

			//-----------------------------------------------------------------
			// pl_close()
			// +-----------+----------+----------+
			// | OPERATION | UUID     | PLD      |
			// | CODE      |          |          |
			// +-----------+----------+----------+
			// ^           ^ (LSB-MSB)^ (LSB-MSB)          
			// |           |          |
			// |<--- A --->|<--- B -->|<-- C --->
			// |           |          |
			// |           |          +---- PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX
			// |           +--------------- PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX
			// +--------------------------- PL_PROTOCOL_PL_CLOSE_INPUT_OPCODE_INDEX
			////
			// Note:
			//   A = PL_PROTOCOL_OPCODE_SIZE
			//   B = PL_PROTOCOL_UUID_SIZE
			//   C = PL_PROTOCOL_PLD_SIZE
			//-----------------------------------------------------------------
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_OP_CODE_STRING,
				r
			);
			memcpy(
				&pl_counters_count,
				&p[PL_PROTOCOL_PL_OPEN_INPUT_COUNTERS_COUNT_INDEX],
				PL_PROTOCOL_UINT_SIZE
			);
			memcpy(
				&uuid,
				&p[PL_PROTOCOL_PL_CLOSE_INPUT_UUID_INDEX],
				PL_PROTOCOL_UUID_SIZE
			);
#ifdef __PL_WINDOWS__
			UuidToString(
				&uuid, 
				(RPC_WSTR *)&pu
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
			memset(
				uuid_buffer, 
				0, 
				sizeof(uuid_buffer)
			);
			uuid_unparse(
				uuid, 
				uuid_buffer
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS__
			wcstombs_s(
				&st_ret, 
				cvt_buffer, 
				sizeof(cvt_buffer), 
				(TCHAR *)pu, 
				_TRUNCATE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_UUID_STRING,
				r,
				cvt_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);			
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_UUID_STRING,
				r,
				uuid_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS
			RpcStringFree(&pu);
#endif // __PL_WINDOWS__
			memcpy(
				&pld,
				&p[PL_PROTOCOL_PL_CLOSE_INPUT_PLD_INDEX],
				PL_PROTOCOL_PLD_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_PLD_STRING,
				r,
				pld
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			if(
				p[PL_PROTOCOL_PL_CLOSE_INPUT_EOR_INDEX] != 
				PL_PROTOCOL_EOR
			) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_CLOSE_INPUT_EOR_INDEX],
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_CLOSE_INPUT_EOR_INDEX],
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		/*
		@@@@@  @             @@@@@  @@@@@@   @@   @@@@@
		@    @ @             @    @ @       @  @  @    @
		@    @ @             @    @ @      @    @ @    @
		@@@@@  @             @@@@@  @@@@@@ @    @ @    @
		@      @             @  @   @      @@@@@@ @    @
		@      @             @   @  @      @    @ @    @
		@      @@@@@@        @    @ @@@@@@ @    @ @@@@@
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_READ:

			//-----------------------------------------------------------------
			// pl_read()
			// +-----------+---------+---------+-----------+
			// | OPERATION | UUID    | PLD     | OFFSET    |
			// | CODE      |         |         |           |
			// +-----------+---------+---------+-----------+
			// ^           ^         ^         ^
			// |           |         |         |
			// |<--- A --->|<-- B -->|<-- C -->|<--- D --->
			// |           |(LSB-MSB)|(LSB-MSB)|(LSB-MSB)
			// |           |         |         |
			// |           |         |         +------- PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX
			// |           |         +----------------- PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX
			// |           +--------------------------- PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX
			// +--------------------------------------- PL_PROTOCOL_PL_READ_INPUT_OPCODE_INDEX
			//
			// Note:
			//   A = PL_PROTOCOL_OPCODE_SIZE
			//   B = PL_PROTOCOL_UUID_SIZE
			//   C = PL_PROTOCOL_PLD_SIZE
			//   D = PL_PROTOCOL_COUNTER_OFFSET_SIZE
			//-----------------------------------------------------------------
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_OP_CODE_STRING,
				r
			);
			memcpy(
				&uuid,
				&p[PL_PROTOCOL_PL_READ_INPUT_UUID_INDEX],
				PL_PROTOCOL_UUID_SIZE
			);
#ifdef __PL_WINDOWS__
			UuidToString(
				&uuid, 
				(RPC_WSTR *)&pu
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
			memset(
				uuid_buffer, 
				0, 
				sizeof(uuid_buffer)
			);
			uuid_unparse(
				uuid, 
				uuid_buffer
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
#ifdef __PL_WINDOWS__
			wcstombs_s(
				&st_ret, 
				cvt_buffer, 
				sizeof(cvt_buffer), 
				(TCHAR *)pu, 
				_TRUNCATE
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_UUID_STRING,
				r,
				cvt_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);			
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_UUID_STRING,
				r,
				uuid_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS
			RpcStringFree(&pu);
#endif // __PL_WINDOWS__
			memcpy(
				&pld,
				&p[PL_PROTOCOL_PL_READ_INPUT_PLD_INDEX],
				PL_PROTOCOL_PLD_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_PLD_STRING,
				r,
				pld
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memcpy(
				&counter_offset,
				&p[PL_PROTOCOL_PL_READ_INPUT_OFFSET_INDEX],
				PL_PROTOCOL_COUNTER_OFFSET_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_COUNTER_OFFSET_STRING,
				r,
				counter_offset
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			if(
				p[PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX] != 
				PL_PROTOCOL_EOR
			) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX],
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_READ_INPUT_EOR_INDEX],
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		/*
		@@@@@  @             @    @ @@@@@  @@@@@   @@@@@ @@@@@@
		@    @ @             @    @ @    @   @       @   @
		@    @ @             @  @ @ @    @   @       @   @
		@@@@@  @             @  @ @ @@@@@    @       @   @@@@@@
		@      @             @  @ @ @  @     @       @   @
		@      @              @ @ @ @   @    @       @   @
		@      @@@@@@          @ @  @    @ @@@@@     @   @@@@@@
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_WRITE:

			//-----------------------------------------------------------------
			// pl_write()
			// +-----------+---------+---------+---------+----------+
			// | OPERATION | UUID    | PLD     | OFFSET  | VALUE    |
			// | CODE      |         |         |         |          |
			// +-----------+---------+---------+---------+----------+
			// ^           ^         ^         ^         ^
			// |           |         |         |         |
			// |<--- A --->|<-- B -->|<-- C -->|<-- D -->|<-- E --->
			// |           |(LSB-MSB)|(LSB-MSB)|(LSB-MSB)|(LSB-MSB)
			// |           |         |         |         |
			// |           |         |         |         +--- PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX
			// |           |         |         +------------- PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX
			// |           |         +----------------------- PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX
			// |           +--------------------------------- PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX
			// +--------------------------------------------- PL_PROTOCOL_PL_WRITE_INPUT_OPCODE_INDEX
			//
			// Note:
			//   A = PL_PROTOCOL_OPCODE_SIZE
			//   B = PL_PROTOCOL_UUID_SIZE
			//   C = PL_PROTOCOL_PLD_SIZE
			//   D = PL_PROTOCOL_COUNTER_OFFSET_SIZE
			//   E = PL_PROTOCOL_ULL_SIZE
			//-----------------------------------------------------------------
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_OP_CODE_STRING,
				r
			);
			memcpy(
				&uuid,
				&p[PL_PROTOCOL_PL_WRITE_INPUT_UUID_INDEX],
				PL_PROTOCOL_UUID_SIZE
			);
#ifdef __PL_WINDOWS__
			UuidToString(
				&uuid, 
				(RPC_WSTR *)&pu
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
			memset(
				uuid_buffer, 
				0, 
				sizeof(uuid_buffer)
			);
			uuid_unparse(
				uuid, 
				uuid_buffer
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
#ifdef __PL_WINDOWS__
			wcstombs_s(
				&st_ret, 
				cvt_buffer, 
				sizeof(cvt_buffer), 
				(TCHAR *)pu, 
				_TRUNCATE
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_UUID_STRING,
				r,
				cvt_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);			
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_UUID_STRING,
				r,
				uuid_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS
			RpcStringFree(&pu);
#endif // __PL_WINDOWS__
			memcpy(
				&pld,
				&p[PL_PROTOCOL_PL_WRITE_INPUT_PLD_INDEX],
				PL_PROTOCOL_PLD_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_PLD_STRING,
				r,
				pld
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memcpy(
				&counter_offset,
				&p[PL_PROTOCOL_PL_WRITE_INPUT_OFFSET_INDEX],
				PL_PROTOCOL_COUNTER_OFFSET_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_COUNTER_OFFSET_STRING,
				r,
				counter_offset
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memcpy(
				&counter_value,
				&p[PL_PROTOCOL_PL_WRITE_INPUT_VALUE_INDEX],
				PL_PROTOCOL_ULL_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
#ifdef __PL_WINDOWS__
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_COUNTER_VALUE_STRING,
				r,
				counter_value
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_COUNTER_VALUE_STRING,
				r,
				counter_value
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			PL_AGENT_DEBUG_MESSAGE(buffer);
			if(
				p[PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX] != 
				PL_PROTOCOL_EOR
			) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX],
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_WRITE_INPUT_EOR_INDEX],
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		default:
			PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(
				PL_AGENT_DEBUG_MESSAGE_DECODE_ERROR_OP_CODE_STRING,
				r
			);
			return;
	}
}

/*-----------------------------------------------------------------------------
Function: pl_agent_decode_response
Purpose : decode a message
In      : thread rank, opcode, message size and pointer to char buffer
Out     : none
Return  : none

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
07/10/2010    Jamel Tayeb             Creation.
*/
void pl_agent_decode_response(int r, PL_PROTOCOL_OPCODE o, size_t s, char *p) {
	
	unsigned int i = 0;
	uuid_t uuid;
	int pld = PL_INVALID_DESCRIPTOR;
	char tmp_buffer[PL_MAX_PATH] = { '\0' };
	char buffer[PL_MAX_PATH] = { '\0' };
	char *p_string = NULL;
	unsigned long long value = 0;
	unsigned int uvalue = 0;
#ifdef __PL_WINDOWS__
	size_t st_ret = 0;
	char *pu = NULL;
	char cvt_buffer[PL_MAX_PATH] = { '\0' };
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
	char uuid_buffer[PL_MAX_PATH] = { '\0' };
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Answer HEX dump.
	//-------------------------------------------------------------------------
	sprintf(
		buffer, 
		PL_AGENT_DEBUG_MESSAGE_DUMP_L1_STRING,
		r,
		(int)s, 
		(int)s
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);
	sprintf(
		buffer, 
		PL_AGENT_DEBUG_MESSAGE_DUMP_L2_STRING,
		r,
		(int)(s - PL_PROTOCOL_SIZET_SIZE), 
		(int)(s - PL_PROTOCOL_SIZET_SIZE)
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);
	memset(
		buffer,
		0,
		sizeof(buffer)
	);
	p_string = buffer;
	sprintf(
		buffer,
		PL_AGENT_DEBUG_MESSAGE_DUMP_LFULL_STRING,
		r
	);
	p_string += strlen(PL_AGENT_DEBUG_MESSAGE_DUMP_LFULL_STRING) - 1;
	for(i = 0; i < s; i++) {
		sprintf(
			p_string,
			"%02X ", 
			(unsigned char)p[i]
		);
		p_string += strlen("XXX");
	}
	sprintf(
		p_string,
		"\n"
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);

	memset(
		buffer,
		0,
		sizeof(buffer)
	);
	p_string = buffer;
	sprintf(
		buffer,
		PL_AGENT_DEBUG_MESSAGE_DUMP_LPARTIAL_STRING,
		r
	);
	p_string += strlen(PL_AGENT_DEBUG_MESSAGE_DUMP_LPARTIAL_STRING) - 1;
	for(i = PL_PROTOCOL_SIZET_SIZE; i < s; i++) {
		sprintf(
			p_string,
			"%02X ", 
			(unsigned char)p[i]
		);
		p_string += strlen("XXX");
	}
	sprintf(
		p_string,
		"\n"
	);
	PL_AGENT_DEBUG_MESSAGE(buffer);

	//-------------------------------------------------------------------------
	// Display the status code (common to all API calls).
	//-------------------------------------------------------------------------
	switch(p[PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX]) {

		case PL_PROTOCOL_FAILURE:
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_ALL_STATUS_FAILURE_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		case PL_PROTOCOL_SUCCESS:
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_ALL_STATUS_SUCCESS_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		default:
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_ALL_STATUS_UNKNOWN_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			return;
	}

	//-------------------------------------------------------------------------
	// Process each API call.
	//-------------------------------------------------------------------------
	switch(o) {

		/*
		@@@@@  @              @@@@  @@@@@  @@@@@@ @    @
		@    @ @             @    @ @    @ @      @@   @
		@    @ @             @    @ @    @ @      @ @  @
		@@@@@  @             @    @ @@@@@  @@@@@@ @ @  @
		@      @             @    @ @      @      @  @ @
		@      @             @    @ @      @      @   @@
		@      @@@@@@         @@@@  @      @@@@@@ @    @
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_OPEN:

			//-----------------------------------------------------------------
			// pl_open() return
			// +----------+-----------+----------+
			// | STATUS   | UUID      | PLD      |
			// | CODE     |           |          |
			// +----------+-----------+----------+ <-- PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX
			// ^          ^ (LSB-MSB) ^ (LSB-MSB)
			// |          |           |
			// |<-- A --->|<--- B --->|<-- C --->
			// |          |           |
			// |          |           +---- PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX
			// |          +---------------- PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX
			// +--------------------------- PL_PROTOCOL_PL_OPEN_OUTPUT_STATUS_INDEX
			//
			// Note:
			//   A = PL_PROTOCOL_STATUS_SIZE
			//   B = PL_PROTOCOL_UUID_SIZE
			//   C = PL_PROTOCOL_PLD_SIZE
			//-----------------------------------------------------------------
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_OP_CODE_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memcpy(
				&uuid,
				&p[PL_PROTOCOL_PL_OPEN_OUTPUT_UUID_INDEX],
				PL_PROTOCOL_UUID_SIZE
			 );
#ifdef __PL_WINDOWS__
			UuidToString(
				&uuid, 
				(RPC_WSTR *)&pu
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
			memset(
				uuid_buffer, 
				0, 
				sizeof(uuid_buffer)
			);
			uuid_unparse(
				uuid, 
				uuid_buffer
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS__
			wcstombs_s(
				&st_ret, 
				cvt_buffer, 
				sizeof(cvt_buffer), 
				(TCHAR *)pu, 
				_TRUNCATE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_UUID_STRING,
				r,
				cvt_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);			
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_UUID_STRING,
				r,
				uuid_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);						
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS
			RpcStringFree(&pu);
#endif // __PL_WINDOWS__
			memcpy(
				&pld,
				&p[PL_PROTOCOL_PL_OPEN_OUTPUT_PLD_INDEX],
				PL_PROTOCOL_PLD_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_PLD_STRING,
				r,
				pld
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			if(p[PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX] != PL_PROTOCOL_EOR) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX],
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_OPEN_OUTPUT_EOR_INDEX],
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		/*
		@@@@@  @               @@    @@@@@  @@@@@   @@    @@@@  @    @
		@    @ @              @  @     @      @    @  @  @    @ @    @
		@    @ @             @    @    @      @   @    @ @      @    @
		@@@@@  @             @    @    @      @   @    @ @      @@@@@@
		@      @             @@@@@@    @      @   @@@@@@ @      @    @
		@      @             @    @    @      @   @    @ @    @ @    @
		@      @@@@@@        @    @    @      @   @    @  @@@@  @    @
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_ATTACH:

			//-----------------------------------------------------------------
			// pl_attach() return
			// +----------+-----------+-----------+----------+
			// | STATUS   | UUID      | PLD       | COUNTERS |
			// | CODE     |           |           | COUNT    |
			// +----------+-----------+-----------+----------+ <-- PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX
			// ^          ^ (LSB-MSB) ^ (LSB-MSB) ^ (LSB-MSB)         
			// |          |           |           |
			// |<-- A --->|<--- B --->|<--- C --->|<-- D --->
			// |          |           |           +--- PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX
			// |          |           +--------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX
			// |          +--------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX
			// +-------------------------------------- PL_PROTOCOL_PL_ATTACH_OUTPUT_STATUS_INDEX
			//
			// Note:
			//   A = PL_PROTOCOL_STATUS_SIZE
			//   B = PL_PROTOCOL_UUID_SIZE
			//   C = PL_PROTOCOL_PLD_SIZE
			//   D = PL_PROTOCOL_COUNTERS_COUNT_SIZE
			//-----------------------------------------------------------------
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_OP_CODE_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memcpy(
				&uuid,
				&p[PL_PROTOCOL_PL_ATTACH_OUTPUT_UUID_INDEX],
				PL_PROTOCOL_UUID_SIZE
			 );
#ifdef __PL_WINDOWS__
			UuidToString(
				&uuid, 
				(RPC_WSTR *)&pu
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__) 
			memset(
				uuid_buffer, 
				0, 
				sizeof(uuid_buffer)
			);
			uuid_unparse(
				uuid, 
				uuid_buffer
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS__
			wcstombs_s(
				&st_ret, 
				cvt_buffer, 
				sizeof(cvt_buffer), 
				(TCHAR *)pu, 
				_TRUNCATE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_UUID_STRING,
				r,
				cvt_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);			
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__) 
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_UUID_STRING,
				r,
				uuid_buffer
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);						
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#ifdef __PL_WINDOWS
			RpcStringFree(&pu);
#endif // __PL_WINDOWS__
			memcpy(
				&pld,
				&p[PL_PROTOCOL_PL_ATTACH_OUTPUT_PLD_INDEX],
				PL_PROTOCOL_PLD_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_PLD_STRING,
				r,
				pld
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memcpy(
				&uvalue,
				&p[PL_PROTOCOL_PL_ATTACH_OUTPUT_COUNTERS_COUNT_INDEX],
				PL_PROTOCOL_COUNTERS_COUNT_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_COUNTERS_COUNT_STRING,
				r,
				uvalue
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			if(p[PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX] != PL_PROTOCOL_EOR) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX],
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_ATTACH_OUTPUT_EOR_INDEX],
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		/*
		@@@@@  @              @@@@  @       @@@@   @@@@  @@@@@@
		@    @ @             @    @ @      @    @ @    @ @
		@    @ @             @      @      @    @ @      @
		@@@@@  @             @      @      @    @  @@@@  @@@@@@
		@      @             @      @      @    @      @ @
		@      @             @    @ @      @    @      @ @
		@      @@@@@@         @@@@  @@@@@@  @@@@  @@@@@  @@@@@@
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_CLOSE:

			//-----------------------------------------------------------------
			// pl_close() return
			// +----------+
			// | STATUS   |
			// | CODE     |
			// +----------+ <--- PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX
			// ^
			// |
			// |<-- A --->
			// |
			// +--------------------------- PL_PROTOCOL_PL_CLOSE_OUTPUT_STATUS_INDEX
			//
			// Note:
			//   A = PL_PROTOCOL_STATUS_SIZE
			//-----------------------------------------------------------------
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_CLOSE_OP_CODE_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			if(p[PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX] != PL_PROTOCOL_EOR) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_CLOSE_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX],
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_CLOSE_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_CLOSE_OUTPUT_EOR_INDEX],
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		/*
		@@@@@  @             @@@@@  @@@@@@   @@   @@@@@
		@    @ @             @    @ @       @  @  @    @
		@    @ @             @    @ @      @    @ @    @
		@@@@@  @             @@@@@  @@@@@@ @    @ @    @
		@      @             @  @   @      @@@@@@ @    @
		@      @             @   @  @      @    @ @    @
		@      @@@@@@        @    @ @@@@@@ @    @ @@@@@
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_READ:

			//-----------------------------------------------------------------
			// pl_read() return
			// +----------+----------+
			// | STATUS   | VALUE    |
			// | CODE     |          |
			// +----------+----------+ <--- PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX
			// ^          ^
			// |          |
			// |<-- A --->|<-- B --->
			// |          |(LSB-MSB)
			// |          |
			// |          +---------------------------- PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX
			// +--------------------------------------- PL_PROTOCOL_PL_READ_OUTPUT_STATUS_INDEX
			//
			// Note:
			//   A = PL_PROTOCOL_STATUS_SIZE
			//   B = PL_PROTOCOL_ULL_SIZE
			//-----------------------------------------------------------------
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_OP_CODE_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			memcpy(
				&value,
				&p[PL_PROTOCOL_PL_READ_OUTPUT_VALUE_INDEX],
				PL_PROTOCOL_ULL_SIZE
			);
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
#ifdef __PL_WINDOWS__
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_VALUE_STRING,
				r,
				value
			);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_VALUE_STRING,
				r,
				value
			);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
			PL_AGENT_DEBUG_MESSAGE(buffer);
			if(p[PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX] != PL_PROTOCOL_EOR) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX],
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_READ_OUTPUT_EOR_INDEX],
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		/*
		@@@@@  @             @    @ @@@@@  @@@@@   @@@@@ @@@@@@
		@    @ @             @    @ @    @   @       @   @
		@    @ @             @  @ @ @    @   @       @   @
		@@@@@  @             @  @ @ @@@@@    @       @   @@@@@@
		@      @             @  @ @ @  @     @       @   @
		@      @              @ @ @ @   @    @       @   @
		@      @@@@@@          @ @  @    @ @@@@@     @   @@@@@@
					  @@@@@@
		*/
		case PL_PROTOCOL_OPCODE_WRITE:

			//-----------------------------------------------------------------
			// pl_write() return
			// +----------+
			// | STATUS   |
			// | CODE     |
			// +----------+ <--- PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX
			// ^
			// |
			// |<-- A --->
			// |
			// +--------------------------- PL_PROTOCOL_PL_WRITE_OUTPUT_STATUS_INDEX
			//
			// Note:
			//   A = PL_PROTOCOL_STATUS_SIZE
			//-----------------------------------------------------------------
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_WRITE_OP_CODE_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			if(p[PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX] != PL_PROTOCOL_EOR) {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_WRITE_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX],
					"ERROR, not PL_PROTOCOL_EOR"
				);
			} else {
				sprintf(
					buffer,
					PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_WRITE_LAST_BYTE_STRING,
					r,
					p[PL_PROTOCOL_PL_WRITE_OUTPUT_EOR_INDEX],
					"PL_PROTOCOL_EOR"
				);
			}
			PL_AGENT_DEBUG_MESSAGE(buffer);
			break;

		default:
			memset(
				buffer,
				0,
				sizeof(buffer)
			);
			sprintf(
				buffer,
				PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_ERROR_OP_CODE_STRING,
				r
			);
			PL_AGENT_DEBUG_MESSAGE(buffer);
			return;
	}
}
#endif // _DEBUG
