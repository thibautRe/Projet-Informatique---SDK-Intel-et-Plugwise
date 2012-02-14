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

#ifndef __INCLUDE_PRODUCTIVITY_LINK_AGENT__
#define __INCLUDE_PRODUCTIVITY_LINK_AGENT__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include "productivity_link.h"

#ifndef __PL_FILESYSTEM_LESS__
	
	#ifdef __PL_WINDOWS__

	 	//---------------------------------------------------------------------
		// Note: 
		//    To solve the winsock2.h / winsock.h / windows.h header problem, 
		//    we define at project-level the _WINSOCKAPI_ symbol.  This is 
		//    preventing windows.h to include windows.h and therefore come up 
		//    with the re-defintion compiler error messages.
		//    This also generates symbol re-definition warning on _WINSOCKAPI_.
		//    To silent it, we use the push, pop and disable warning pragma. 
		//---------------------------------------------------------------------
		#pragma warning(push)
		#pragma warning(disable:4005)
		#include <winsock2.h>
		#include <ws2tcpip.h>
		#include <windows.h>
		#pragma warning(pop) 
		#pragma comment(lib, "WS2_32.lib")

	#endif // __PL_WINDOWS__
	
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  

		#include <stdio.h>
		#include <sys/types.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <sys/socket.h>
		#include <netdb.h>
	
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#endif // __PL_FILESYSTEM_LESS__

//-----------------------------------------------------------------------------
// Version defines
//-----------------------------------------------------------------------------
#define PL_AGENT_NAME "pl_agent"
#define PL_AGENT_VERSION_MAJOR "2010" // year
#define PL_AGENT_VERSION_MINOR "06" // month
#define PL_AGENT_VERSION_REVISION "08" // day

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define SERVICES_PL_AGENT_DEBUG_MESSAGE_TIME_STAMP_BUFFER_SIZE 26
#define SERVICES_PL_AGENT_DEBUG_MESSAGE_TIME_STAMP_BEGIN "["
#define SERVICES_PL_AGENT_DEBUG_MESSAGE_TIME_STAMP_END "]: "
#ifdef __PL_SOLARIS__
	#define TIME_STAMP_BUFFER_SIZE 26
#endif // __PL_SOLARIS__

//-----------------------------------------------------------------------------
// IPC defines
// Note: 
//    The Dynamic and/or Private Ports are those from 49152 through 65535
//-----------------------------------------------------------------------------
#define PL_AGENT_IPC_DATA_SIZE PL_PROTOCOL_MESSAGE_MAX_SIZE
#define PL_AGENT_DYNAMIC_PRIVATE_PORT_BEGIN 49152
#define PL_AGENT_DYNAMIC_PRIVATE_PORT_END 65535

//-----------------------------------------------------------------------------
// Note: 
//    Under Windows, a thread can wait simultaneously only up to 
//    MAXIMUM_WAIT_OBJECTS handles with WaitForMultipleObjects.
//-----------------------------------------------------------------------------
#define PL_AGENT_DYNAMIC_PRIVATE_PORT_BEGIN 49152
#define PL_AGENT_DYNAMIC_PRIVATE_PORT_END 65535
#define PL_AGENT_MIN_THREADS_IN_POOL 1
#define PL_AGENT_MAX_THREADS_IN_POOL 64
#define PL_AGENT_DEFAULT_THREADS_IN_POOL 16

#ifdef __PL_MACOSX__
	#define SEMAPHORE_NAME_MAX_SIZE 13
	#define PL_AGENT_SEMAPHORE_ACCESS_MODE 0x01ff // octal 0777
	#define MAIN_THREAD_DONE_SEMAPHORE_NAME "MD"
	#define ADMIN_PORT_LISTENER_THREAD_DONE_SEMAPHORE_NAME "AD"
	#define PL_PORT_LISTENER_THREAD_DONE_SEMAPHORE_NAME "PL"
	#define POOL_THREAD_DO_SEMAPHORE_BASE_NAME "PDO"
	#define POOL_THREAD_DONE_SEMAPHORE_BASE_NAME "PO"
	#ifdef _DEBUG
		#define CS_SEMAPHORE_NAME "CS"
	#endif // _DEBUG
#endif // __PL_MACOSX__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define SOCKET int
	#define ADDRINFO struct sockaddr_in
	#define INVALID_SOCKET (-1)
	#define SOCKET_ERROR (-1)
	#define SD_BOTH 2
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#define PL_AGENT_IPC_SOCKET_DEFAULT_NODE_MAME "127.0.0.1"
#define PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FAMILY AF_INET;
#define PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_SOCKTYPE SOCK_STREAM;
#define PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_PROTOCOL IPPROTO_TCP;
#define PL_AGENT_IPC_SOCKET_DEFAULT_ADDRESS_INFO_HINT_AI_FLAGS AI_PASSIVE;
#define PL_AGENT_IPC_SOCKET_MAX_NODE_NAME_SIZE 20
#define PL_AGENT_IPC_SOCKET_MAX_PORT_NAME_SIZE 10

#ifdef __PL_WINDOWS__
	#define PL_AGENT_PL_EXPORT_POOL_THREAD_SEARCH_GRACE_TIME 1000
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PL_AGENT_PL_EXPORT_POOL_THREAD_SEARCH_GRACE_TIME 1
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// Cli options.
//-----------------------------------------------------------------------------
#define PL_AGENT_CLI_MAX_TOKENS 6
#define PL_AGENT_CLI_HELP "--HELP"
#define PL_AGENT_VERSION "--VERSION"
#define PL_AGENT_ADMIN_PORT "--ADMIN_PORT"
#define PL_AGENT_PL_PORT "--PL_PORT"
#define PL_AGENT_THREADS_IN_POOL "--THREADS_IN_POOL"
#define PL_AGENT_ENCRYPT "--ENCRYPT"

typedef enum _pl_mount_cli_token_id {

	PL_AGENT_CLI_HELP_TOKEN_ID = 0,
	PL_AGENT_VERSION_TOKEN_ID,
	PL_AGENT_ADMIN_PORT_TOKEN_ID, 
	PL_AGENT_PL_PORT_TOKEN_ID,
	PL_AGENT_THREADS_IN_POOL_TOKEN_ID,
	PL_AGENT_ENCRYPT_TOKEN_ID

} PL_AGENT_CLI_TOKEN_ID;

//-----------------------------------------------------------------------------
// Response to invalid syntax and startup banner.
//-----------------------------------------------------------------------------
#define PL_AGENT_HELP_PL_AGENT_DEBUG_MESSAGE_LINES_COUNT 23
#define PL_AGENT_HELP_PL_AGENT_DEBUG_MESSAGE_LINES \
	"\n", \
	"Start PL agent for instrumented applications compiled in __PL_FILESYSTEM_LESS__ mode.\n", \
	"\n", \
	"Usage:  pl_agent [--admin_port <port>] [--pl_port <port>]\n", \
	"                 [--threads_in_pool <n>] [--encrypt]\n", \
	"Or      pl_agent [--version]\n", \
	"Or      pl_agent [--help]\n", \
	"\n", \
	"   --admin_port specifies a TCP/IP port number to use for administrative tasks.\n", \
	"      By default, port 49252 is used.\n", \
	"   --pl_port specifies a TCP/IP port number to use by pl functions.\n", \
	"      By default, port 49253 is used.\n", \
	"   --threads_in_pool specifies the number of threads created to process PL calls.\n", \
	"      By default, 16 threads are created. (with 1 <= n <= 64)\n", \
	"   --encrypt uses encripted communications via the admin port.\n", \
	"   Notes:\n", \
	"      Only dynamic and/or private ports are accepted (49152 through 65535).\n", \
	"      Use netstat command to display current TCP/IP network connections.\n", \
	"   --version prints version information.\n", \
	"   --help prints this help message.\n", \
	"\n", \
	"To interrupt the agent, type <CTRL>+<C>.", \
	"\n"

//-----------------------------------------------------------------------------
// Messages.
//-----------------------------------------------------------------------------
#define PL_AGENT_INTERRUPT_INSTRUCTIONS_PL_AGENT_DEBUG_MESSAGE_STRING "To interrupt the agent, type <CTRL>+<C>.\n"
#define PL_AGENT_INTERRUPT_RECEIVED_PL_AGENT_DEBUG_MESSAGE_STRING "Received agent interrupt request from user [<CTRL>+<C>].\n"
#define PL_AGENT_INTERRUPT_GENERATED_PL_AGENT_DEBUG_MESSAGE_STRING "The agent tries to interrupt itself.\n"

#define PL_MOUNT_ALL_MOUNT_THREADS_DISCONNECTED_PL_AGENT_DEBUG_MESSAGE_STRING "All mount thread(s) were disconnected by their respective pl_export instance(s).\n"
#define PL_MOUNT_RECEIVED_DISCONNECT_PL_AGENT_DEBUG_MESSAGE_STRING "Received disconnect request.\n"
#define PL_MOUNT_INTERRUPT_RECEIVED_PL_AGENT_DEBUG_MESSAGE_STRING "Detected interrupt request.\n"
#define PL_MOUNT_INTERRUPT_INSTRUCTIONS_PL_AGENT_DEBUG_MESSAGE_STRING "To interrupt the mount operation, type <CTRL>+<C>.\n"
#define PL_MOUNT_ENDED_WITH_ERRORS_PL_AGENT_DEBUG_MESSAGE_STRING "Mount operation has ended with error(s).\n"
#define PL_MOUNT_ENDED_SUCCESSFULLY_PL_AGENT_DEBUG_MESSAGE_STRING "Mount operation has successfully ended.\n"

//-----------------------------------------------------------------------------
// Error messages.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// No erro error.
//-----------------------------------------------------------------------------
#define PL_AGENT_NO_ERROR_STRING "No error has been detected.  Please ignore this message."

//-----------------------------------------------------------------------------
// System errors.
//-----------------------------------------------------------------------------
#define PL_AGENT_UNABLE_TO_STOP_AGENT_STRING "A critical error has been detected while trying to stop the agent.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_CREATE_UUID_STRING "A critical error has been detected during a UUID generation.  The program will be terminated."
#define PL_AGENT_INVALID_USER_INPUT_STRING "An inconsistent user input has beed found.  Please use --help for syntax details."
#define PL_AGENT_INVALID_MESSAGE_DATA_STRING "An inconsistent message has beed received."
#define PL_AGENT_UNABLE_TO_ACTIVATE_MEMORY_LEAK_DETECTION_STRING "A critical error has beed detected during memory leak detection setup.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_INSTALL_SIGNAL_HANDLER_STRING "A critical error has beed detected during the signal handler routine setup.  The program will be terminated."
#define PL_AGENT_OUT_OF_MEMORY_STRING "A low memory condition has been detected.  Please try to close unecessary running applications to free memory.  The program will be terminated."
#define PL_AGENT_OUT_OF_BUFFER_SPACE_STRING "An internal buffer has no room to store more data into it.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT_STRING "A critical error has been detected during synchronization.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_CREATE_THREAD_STRING "A critical error has been detected during thread creation.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_SYNCHRONIZE_STRING "A critical error has been detected during thread synchronization.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT_STRING "A critical error has been detected during synchronization object release.  The program will be terminated."

//-------------------------------------------------------------------------
// IPC errors.
//-------------------------------------------------------------------------
#define PL_AGENT_UNABLE_TO_INITIALIZE_SOCKET_STRING "A critical error has beed detected during the operating system's socket sub-system initialization.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_TEARDOWN_SOCKET_STRING "A critical error has beed detected while de-initializing the operating system's socket sub-system.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_GET_HOST_STRUCTURE_FROM_HOSTNAME_STRING "A critical error has been detected while trying to find the host's name.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_CONVERT_ADDRESS_STRING_INTO_STRUCTURE_STRING "A critical error has been detected while converting the host’s address into a format usable by the program.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_GET_ADDRESS_INFO_STRING "A critical error has been detected while trying to obtain the host’s address.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_CREATE_SOCKET_STRING "A critical error has been detected while creating a socket.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_CLOSE_SOCKET_STRING "A critical error has been detected while closing a socket.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_CONNECT_TO_SOCKET_STRING "A critical error has been detected while connecting to a socket.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_SEND_VIA_SOCKET_STRING "A critical error has been detected while sending data via a socket.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_SHUTDOWN_SOCKET_STRING "A critical error has been detected while shutting-down a socket.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_SET_SOCKET_OPTIONS_STRING "A critical error has been detected while setting a socket’s options.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_LISTEN_SOCKET_STRING "A critical error has been detected while listening to a socket.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_ACCEPT_SOCKET_STRING "A critical error has been detected while accepting connections from a socket.  The program will be terminated."
#define PL_AGENT_UNABLE_TO_RECEIVE_FROM_SOCKET_STRING "A critical error has been detected while receiving from a socket.  The program will be terminated."

//-----------------------------------------------------------------------------
// PL protocol errors.
//-----------------------------------------------------------------------------
#define PL_AGENT_PROTOCOL_ERROR_STRING "An error has been detected in a client’s message structure according to the protocol.  The program will try to recover, but may behave inconsistently."
#define PL_AGENT_PROTOCOL_UNKNOWN_OP_CODE_STRING "An error has been detected in a client’s request according to the protocol.  The program will try to recover, but may behave inconsistently."

//-----------------------------------------------------------------------------
// PL API errors.
//-----------------------------------------------------------------------------
#define PL_AGENT_UNABLE_TO_PL_OPEN_STRING "An error has been detected opening a PL.  The program will try to recover, but may behave inconsistently."
#define PL_AGENT_UNABLE_TO_PL_ATTACH_STRING "An error has been detected attaching to a PL.  The program will try to recover, but may behave inconsistently."
#define PL_AGENT_UNABLE_TO_PL_CLOSE_STRING "An error has been detected closing a PL.  The program will try to recover, but may behave inconsistently."
#define PL_AGENT_UNABLE_TO_PL_READ_STRING "An error has been detected reading from a PL.  The program will try to recover, but may behave inconsistently."
#define PL_AGENT_UNABLE_TO_PL_WRITE_STRING "An error has been detected writing into a PL.  The program will try to recover, but may behave inconsistently."

#ifdef _DEBUG

//-----------------------------------------------------------------------------
// Debug messages.
//-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Primary thread debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_STARTED_STRING "pl_agent has started.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_PARSING_CLI_STRING "Parsing user input.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_INIT_SOCKET_STRING "Initializing Windows socket system.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_ALLOCATE_THREAD_POOL_DATA_STRING "Allocating thread pool data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_CREATING_SYNCH_OBJECTS_STRING "Creating synchronization objects.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_CREATEING_THREAD_POOL_STRING "Creating thread pool.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_CREATING_ADMIN_THREAD_STRING "Creating admin port listener thread.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_CREATING_PL_PORT_THREAD_STRING "Creating pl port listener thread.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_MAIN_THREAD_DONE_STRING "Signaling main thread done.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_WAITING_ALL_THREADS_STRING "Waiting for all threads to end.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_DESTROYING_SYNCH_OBJECTS_STRING "Destroying synchronization objects.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_DESTROYING_THREAD_POOL_DATA_STRING "De-allocating thread pool data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_DEINIT_SOCKET_STRING "De-initializing Windows socket system.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_ENDED_STRING "pl_agent has ended.\n"

	//-------------------------------------------------------------------------
	// Primary thread's signal handler debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SIGNALING_POOL_THREAD_N_STRING "Signal handler is signaling pool thread [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SIGNALING_ADMIN_THREAD_STRING "Signal handler is signaling the ADMIN port listener thread.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SETUP_ADMIN_PORT_IPC_STRING "...Signal handler is setting-up IPC (ADMIN port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SETUP_ADMIN_SOCKET_DATA_STRING "...Signal handler is setting-up socket IPC data (ADMIN port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_RESOLVING_ADMIN_ADDRESS_PORT_STRING "...Signal handler is resolving IPC address & port (ADMIN port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_CONNCECTING_TO_ADMIN_PORT_STRING "...Signal handler is attempting to connect to ADMIN listener thread (ADMIN port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SENDING_EMPTY_ADMIN_MESSAGE_STRING "...Signal handler is sending empty-message to ADMIN port listener thread (ADMIN port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_DISCONNECTING_FROM_ADMIN_PORT_STRING "...Signal handler is disconnecting from ADMIN port listener thread (ADMIN port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_TEARDOWN_ADMIN_IPC_STRING "...Signal handler is tearing-down ADMIN IPC.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SIGNALING_PL_PORT_THREAD_STRING "Signal handler is signaling the PL port listener thread.\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SETUP_PL_PORT_IPC_STRING "...Signal handler is setting-up IPC (PL port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SETUP_PL_SOCKET_DATA_STRING "...Signal handler is setting-up socket IPC data (PL port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_RESOLVING_PL_PORT_ADDRESS_PORT_STRING "...Signal handler is resolving IPC address & port (PL port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_CONNCECTING_TO_PL_PORT_STRING "...Signal handler is attempting to connect to PL listener thread (PL port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_SENDING_EMPTY_PL_MESSAGE_STRING "...Signal handler is sending empty-message to PL port listener thread (PL port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_DISCONNECTING_FROM_PL_PORT_STRING "...Signal handler is disconnecting from PL port listener thread (PL port).\n"
	#define PL_AGENT_DEBUG_MESSAGE_AGENT_TEARDOWN_PL_IPC_STRING "...Signal handler is tearing-down PL IPC.\n"

	//-------------------------------------------------------------------------
	// Admin port listener thread's debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_STARTED_STRING "Admin port listener thread has started.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_WAITING_MAIN_THREAD_DONE_STRING "Admin port listener thread is waiting for main thread to be done.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_RECEIVED_MAIN_THREAD_DONE_SIGNAL_STRING "Admin port listener thread has received the main thread done signal.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SETTING_UP_IPC_STRING "Admin port listener thread is setting-up IPC.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_INITIALIZING_IPC_STRING "...Admin port listener thread is initializing IPC data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SETTING_UP_SOCKET_DATA_STRING "...Admin port listener thread is setting-up socket IPC data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_RESOLVING_ADDRESS_PORT_STRING "...Admin port listener thread is resolving IPC address & port.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_CREATING_BINDING_SOCKET_STRING "...Admin port listener thread is attempting to create & bind IPC socket.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_LISTENING_SOCKET_STRING "...Admin port listener thread is listening on IPC bound socket.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_ACCEPTING_CONNECTION_STRING "...Admin port listener thread is accepting connections.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_INTERRUPTED_BY_USER_STRING "Admin port listener thread was interrupted by user request.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_RECEIVING_DATA_STRING "...Admin port listener thread is receiving data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_RECEIVED_DATA_STRING "...Admin port listener thread received data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SENDING_DATA_STRING "...Admin port listener thread sending.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_CLOSING_IPC_STRING "...Admin port listener thread is closing IPC.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_TEARINGDOWN_IPC_STRING "Admin port listener thread is tearing-down IPC.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_ENDED_STRING "Admin port listener thread has ended.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_DECYPHERING_DATA_STRING "...Admin port listener thread is decyphering received data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_CYPHERING_DATA_STRING "...Admin port listener thread is cyphering data to be sent.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SERVING_LOOK_UP_UUID_COMMAND "...Admin port listener thread is serving a LOOK-UP UUID command.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_LOCKING_PL_TABLE "...Admin port listener thread is locking the PL table.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_UNLOCKING_PL_TABLE "...Admin port listener thread is unlocking the PL table.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_SEARCHING_UUID "......Admin port listener thread is searching the requested UUID...\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_FOUND_UUID "......Admin port listener thread has found the requested UUID.\n"
	#define PL_AGENT_DEBUG_MESSAGE_ADMIN_THREAD_NOT_FOUND_UUID "......Admin port listener thread didn't find the requested UUID.\n"

	#define PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_L1_STRING "......[%s]: Bytes in full message: [%d]d - [%x]h.\n"
	#define PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_L2_STRING "......[%s]: Bytes in message (skipping size header): [%d]d - [%x]h.\n"
	#define PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_LFULL_STRING "......[%s]: "
	#define PL_AGENT_DEBUG_MESSAGE_HEX_DUMP_LPARTIAL_STRING "......[%s]: xx xx xx xx "

	//-------------------------------------------------------------------------
	// PL port listener thread's debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_STARTED_STRING "Pl port listener thread has started.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_WAITING_MAIN_THREAD_DONE_STRING "Pl port listener thread is waiting for main thread to be done.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_RECEIVED_MAIN_THREAD_DONE_SIGNAL_STRING "Pl port listener thread has received the main thread done signal.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_SETTING_UP_IPC_STRING "Pl port listener thread is setting-up IPC.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_INITIALIZING_IPC_STRING "...Pl port listener thread is initializing IPC data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_SETTING_UP_SOCKET_DATA_STRING "...Pl port listener thread is setting-up socket IPC data.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_RESOLVING_ADDRESS_PORT_STRING "...Pl port listener thread is resolving IPC address & port.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_CREATING_BINDING_SOCKET_STRING "...Pl port listener thread is attempting to create & bind IPC socket.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_LISTENING_SOCKET_STRING "...Pl port listener thread is listening on IPC bound socket.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_ACCEPTING_CONNECTION_STRING "...Pl port listener thread is accepting connections.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_INTERRUPTED_BY_USER_STRING "Pl port listener thread was interrupted by user request.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_RECEIVING_REQUEST_STRING "...Pl port listener thread has received a request.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_SEARCHING_IDLE_POOL_THREAD_STRING "...Pl port listener thread is searching a thread in the pool to serve the request.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_FOUND_IDLE_POOL_THREAD_STRING "...Pl port listener thread has triggered pool thread [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_NO_IDLE_POOL_THREAD_FOUND_STRING "...Pl port listener thread has not found an idle thread in the pool.  It is waitong for [%d] before checking again.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_TRY_LOCK_POOL_THREAD_STRING "......Pl port listener thread is trying to lock pool thread [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_LOCK_SUCCEDED_POOL_THREAD_STRING "......Pl port listener thread has successfully locked pool thread [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_UNLOCK_SUCCEDED_POOL_THREAD_STRING "......Pl port listener thread has successfully unlocked pool thread [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_POOL_THREAD_BUSY_STRING "......Pl port listener thread detected that pool thread [%d] is still buzy.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_LOCK_FAILED_POOL_THREAD_STRING "......Pl port listener thread has failed to lock pool thread [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_TEARINGDOWN_IPC_STRING "Pl port listener thread is tearing-down IPC.\n"
	#define PL_AGENT_DEBUG_MESSAGE_PL_THREAD_ENDED_STRING "Pl port listener thread has ended.\n"

	#define PL_AGENT_DEBUG_MESSAGE_DUMP_L1_STRING "......Pool thread [%d]: Bytes in full message: [%d]d - [%x]h.\n"
	#define PL_AGENT_DEBUG_MESSAGE_DUMP_L2_STRING "......Pool thread [%d]: Bytes in message (skipping size header): [%d]d - [%x]h.\n"
	#define PL_AGENT_DEBUG_MESSAGE_DUMP_LFULL_STRING "......Pool thread [%d]: "
	#define PL_AGENT_DEBUG_MESSAGE_DUMP_LPARTIAL_STRING "......Pool thread [%d]: xx xx xx xx "

	//-------------------------------------------------------------------------
	// Pool threads' debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_STARTED_STRING "Pool thread [%d] has started.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_WAITING_MAIN_THREAD_DONE_STRING "Pool thread [%d] is waiting for main thread to be done.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_RECEIVED_MAIN_THREAD_DONE_SIGNAL_STRING "Pool thread [%d] has received the main thread done signal.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_WAITING_PL_API_CALL_STRING "Pool thread [%d] is waiting for a PL API call to serve.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_INTERRUPTED_BY_USER_STRING "Pool thread [%d] was interrupted by user request.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_SERVING_PL_API_CALL_STRING "Pool thread [%d] is serving a PL API call.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_RECEIVED_DATA_STRING "...Pool thread [%d] has received...\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_SENDING_DATA_STRING "...Pool thread [%d] is sending...\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_CLOSING_IPC_STRING "...Pool thread [%d] is closing IPC.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_ENDED_STRING "Pool thread [%d] has ended.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_UNLOCKING_STRING "...Pool thread [%d] has unlocked itself.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_LOCKING_API_CALL_COUNTER_STRING "...Pool thread [%d] has locked the global API call counter.\n"
	#define PL_AGENT_DEBUG_MESSAGE_POOL_THREAD_UNLOCKING_API_CALL_COUNTER_STRING "...Pool thread [%d] has unlocked the global API call counter.\n"

	//-------------------------------------------------------------------------
	// pl_open decode debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_OP_CODE_STRING "......Pool thread [%d]: Op code = [PL_PROTOCOL_OPCODE_OPEN].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_COUNTERS_COUNT_STRING "......Pool thread [%d]: Counters count = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_APPLICATION_NAME_LENGTH_STRING "......Pool thread [%d]: Application name length = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_APPLICATION_NAME_STRING "......Pool thread [%d]: Application name = [%s].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_COUNTER_NAME_LENGHT_STRING "......Pool thread [%d]: Counter [%d] length = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_COUNTER_NAME_STRING "......Pool thread [%d]: Counter [%d] name = [%s].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_OPEN_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// pl_close decode debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_OP_CODE_STRING "......Pool thread [%d]: Op code = [PL_PROTOCOL_OPCODE_CLOSE].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_UUID_STRING "......Pool thread [%d]: uuid = [%s].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_PLD_STRING "......Pool thread [%d]: pld = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_CLOSE_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// pl_attach decode debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_OP_CODE_STRING "......Pool thread [%d]: Op code = [PL_PROTOCOL_OPCODE_ATTACH].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_CONFIG_FILE_NAME_LENGHT_STRING "......Pool thread [%d]: PL configuration file name length = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_CONFIG_FILE_NAME_STRING "......Pool thread [%d]: PL configuration file name = [%s].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_ATTACH_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// pl_read decode debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_OP_CODE_STRING "......Pool thread [%d]: Op code = [PL_PROTOCOL_OPCODE_READ].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_UUID_STRING "......Pool thread [%d]: uuid = [%s].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_PLD_STRING "......Pool thread [%d]: pld = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_COUNTER_OFFSET_STRING "......Pool thread [%d]: counter offset = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_READ_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// pl_write decode debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_OP_CODE_STRING "......Pool thread [%d]: Op code = [PL_PROTOCOL_OPCODE_WRITE].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_UUID_STRING "......Pool thread [%d]: uuid = [%s].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_PLD_STRING "......Pool thread [%d]: pld = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_COUNTER_OFFSET_STRING "......Pool thread [%d]: counter offset = [%d].\n"
	#ifdef __PL_WINDOWS__
		#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_COUNTER_VALUE_STRING "......Pool thread [%d]: counter value = [%I64u].\n"
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || defined (__PL_SOLARIS__) || (__PL_MACOSX__)	
		#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_COUNTER_VALUE_STRING "......Pool thread [%d]: counter value = [%llu].\n"
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_PL_WRITE_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// Default decode debug protocol error message.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ERROR_OP_CODE_STRING "......Pool thread [%d]: Op code = [UNKNOWN OP_CODE].\n"

	//-------------------------------------------------------------------------
	// All API call decode answer debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_ALL_STATUS_FAILURE_STRING "......Pool thread [%d]: Status = [PL_PROTOCOL_FAILURE].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_ALL_STATUS_SUCCESS_STRING "......Pool thread [%d]: Status = [PL_PROTOCOL_SUCCESS].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_ALL_STATUS_UNKNOWN_STRING "......Pool thread [%d]: Status = [UNKNOWN].\n"

	//-------------------------------------------------------------------------
	// pl_open decode answer debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_OP_CODE_STRING "......Pool thread [%d]: Answer to op code = [PL_PROTOCOL_OPCODE_OPEN].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_UUID_STRING "......Pool thread [%d]: uuid = [%s].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_PLD_STRING "......Pool thread [%d]: pld = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_OPEN_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// pl_close decode answer debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_CLOSE_OP_CODE_STRING "......Pool thread [%d]: Answer to op code = [PL_PROTOCOL_OPCODE_CLOSE].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_CLOSE_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// pl_attach decode answer debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_OP_CODE_STRING "......Pool thread [%d]: Answer to op code = [PL_PROTOCOL_OPCODE_ATTACH].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_UUID_STRING "......Pool thread [%d]: uuid = [%s].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_PLD_STRING "......Pool thread [%d]: pld = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_COUNTERS_COUNT_STRING "......Pool thread [%d]: counters count = [%d].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_ATTACH_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// pl_read decode answer debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_OP_CODE_STRING "......Pool thread [%d]: Answer to op code = [PL_PROTOCOL_OPCODE_READ].\n"
	#ifdef __PL_WINDOWS__
		#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_VALUE_STRING "......Pool thread [%d]: Value = [%I64u].\n"
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_VALUE_STRING "......Pool thread [%d]: Value = [%llu].\n"
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_READ_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// pl_write decode answer debug messages.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_WRITE_OP_CODE_STRING "......Pool thread [%d]: Answer to op code = [PL_PROTOCOL_OPCODE_WRITE].\n"
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_PL_WRITE_LAST_BYTE_STRING "......Pool thread [%d]: Last byte = [%d] - [%s].\n"

	//-------------------------------------------------------------------------
	// Default decode debug protocol answer error message.
	//-------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_DECODE_ANSWER_ERROR_OP_CODE_STRING "......Pool thread [%d]: Answer to op code = [UNKNOWN OP_CODE].\n"

	//-----------------------------------------------------------------------------
	// Stats messages.
	//-----------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_STATS_API_USAGE_COUNT "API Use Stats:\n"
	#ifdef __PL_WINDOWS__
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_OPEN_COUNT "...pl_open:   [%I64u] Call(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_CLOSE_COUNT "...pl_close:  [%I64u] Call(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_ATTACH_COUNT "...pl_attach: [%I64u] Call(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_READ_COUNT "...pl_read:   [%I64u] Call(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_WRITE_COUNT "...pl_write:  [%I64u] Call(s)\n"
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_OPEN_COUNT "...pl_open:   [%llu] Call(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_CLOSE_COUNT "...pl_close:  [%llu] Call(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_ATTACH_COUNT "...pl_attach: [%llu] Call(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_READ_COUNT "...pl_read:   [%llu] Call(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_WRITE_COUNT "...pl_write:  [%llu] Call(s)\n"
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-----------------------------------------------------------------------------
	// Error messages.
	//-----------------------------------------------------------------------------
	#define PL_AGENT_DEBUG_MESSAGE_STATS_API_ERROR_COUNT "API Errors Stats:\n"
	#ifdef __PL_WINDOWS__
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_OPEN_ERROR_COUNT "...pl_open:   [%I64u] Error(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_CLOSE_ERROR_COUNT "...pl_close:  [%I64u] Error(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_ATTACH_ERROR_COUNT "...pl_attach: [%I64u] Error(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_READ_ERROR_COUNT "...pl_read:   [%I64u] Error(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_WRITE_ERROR_COUNT "...pl_write:  [%I64u] Error(s)\n"
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_OPEN_ERROR_COUNT "...pl_open:   [%llu] Error(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_CLOSE_ERROR_COUNT "...pl_close:  [%llu] Error(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_ATTACH_ERROR_COUNT "...pl_attach: [%llu] Error(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_READ_ERROR_COUNT "...pl_read:   [%llu] Error(s)\n"
		#define PL_AGENT_DEBUG_MESSAGE_STATS_API_PL_WRITE_ERROR_COUNT "...pl_write:  [%llu] Error(s)\n"
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#endif // _DEBUG

#ifdef __PL_WINDOWS__
	#define PL_AGENT_MESSAGE_STATS_TOTAL_ERROR_COUNT "Total error(s) count: [%I64u]\n"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PL_AGENT_MESSAGE_STATS_TOTAL_ERROR_COUNT "Total error(s) count: [%llu]\n"
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// Admin protocol example
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// @    @  @@@@  @@@@@  @    @  @@@@         @@@@@  @             @@@@@  @@@@@   @@@@   @@@@@  @@@@   @@@@   @@@@  @
// @    @ @        @    @ @  @ @             @    @ @             @    @ @    @ @    @    @   @    @ @      @    @ @
// @    @  @@@@    @    @ @  @ @             @@@@@  @             @@@@@  @@@@@  @    @    @   @    @ @      @    @ @
// @    @      @   @    @   @@ @    @        @      @             @      @   @  @    @    @   @    @ @    @ @    @ @
//  @@@@  @@@@@  @@@@@  @    @  @@@@         @      @@@@@@        @      @    @  @@@@     @    @@@@   @@@@   @@@@  @@@@@@
//
// Note:
//    All generic defines are defined in productivity_link.h
// Note:
//    All sizes in byte.
//    All data transmitted as binary.
//    All data in little-endian.
//
//-----------------------------------------------------------------------------
// <string> encoding
// +-----------+---------+---------+---            ---+-----------+-----------+
// | BYTES (N) | BYTE 0  | BYTE 1  |        ...       | BYTE N-2  | BYTE N-1  | 
// +-----------+---------+---------+---            ---+-----------+-----------+
// |<--- A --->|<-- B -->|<-- B -->|                  |<--- B --->|<--- B --->
// | (LSB-MSB) |         |         |                  |           |
//
// Note:
//    A = PL_PROTOCOL_SIZET_SIZE
//    B = PL_PROTOCOL_CHAR_SIZE
//
//-----------------------------------------------------------------------------
// All messages are built as:
// +-----------+---------+-------+
// | BYTES (N) | MESSAGE |  EOR  | (PL_PROTOCOL_EOR)
// +-----------+---------+-------+
// |<--- A --->|<-- X -->|<- B ->
// | (LSB-MSB) | 
//
// Note:
//    A = PL_PROTOCOL_SIZET_SIZE
//    B : PL_PROTOCOL_EOR_SIZE
// Note:
//    BYTES is the number of bytes, including PL_PROTOCOL_EOR of a message.
// Note:
//    BYTES is the number of bytes, including PL_PROTOCOL_EOR of a message.
//-----------------------------------------------------------------------------
#define PL_ADMIN_PROTOCOL_COMMAND_ITEM_DELIMITER ":"

//-----------------------------------------------------------------------------
// Look-up UUID command.
// +-------------------------------------------------------------+
// | <string>                                                    |
// | COMMAND                                                     |
// +-------------------------------------------------------------+
// ^
// |
// |<---------------------- A ---------------------------------->
// |
// +--------------- PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_INDEX
//
// Note:
//    A = variable
//
// Look-up UUID command return
// +-------------------------------------------------------------+
// | <string>                                                    |
// | ANSWER: a UUID or "UUID NOT FOUND"                          |
// +-------------------------------------------------------------+
// ^
// |
// |<---------------------- A ---------------------------------->
// |
// +--------------- PL_ADMIN_PROTOCOL_OUTPUT_COMMAND_STRING_INDEX
//
// Note:
//    A = variable
//-----------------------------------------------------------------------------
#define PL_ADMIN_PROTOCOL_COMMAND_LOOK_UP_UUID_STRING "LOOK-UP UUID"
#define PL_ADMIN_PROTOCOL_COMMAND_LOOK_UP_UUID_FAILURE "UUID NOT FOUND"
#define PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_INDEX \
	PL_PROTOCOL_INPUT_OP_CODE_INDEX
#define PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_OFFSET \
	PL_PROTOCOL_SIZET_SIZE + \
	PL_PROTOCOL_SIZET_SIZE

#define PL_ADMIN_PROTOCOL_OUTPUT_COMMAND_STRING_INDEX \
	PL_PROTOCOL_OUTPUT_STATUS_INDEX
#define PL_ADMIN_PROTOCOL_OUTPUT_COMMAND_STRING_OFFSET \
	PL_PROTOCOL_SIZET_SIZE

//-----------------------------------------------------------------------------
// structures & enums
//-----------------------------------------------------------------------------
typedef struct _pl_agent_ipc_buffer {

	char data[PL_AGENT_IPC_DATA_SIZE];

} PL_AGENT_IPC_BUFFER, *PPL_AGENT_IPC_BUFFER;

typedef struct _pl_agent_ipc_data {

	//-------------------------------------------------------------------------
	// SOCKET data
	//-------------------------------------------------------------------------
	char node_name[PL_AGENT_IPC_SOCKET_MAX_NODE_NAME_SIZE];
	SOCKET socket;
	int socket_family;
	int socket_type;
	int protocol;
	struct sockaddr socket_address;

#ifdef __PL_WINDOWS__
	ADDRINFO *address_info;
	ADDRINFO address_info_hint;
	char port[PL_AGENT_IPC_SOCKET_MAX_PORT_NAME_SIZE];
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	struct addrinfo *address_info;
	struct addrinfo address_info_hint;
	int port;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

} PL_AGENT_IPC_DATA, *PPL_AGENT_IPC_DATA;

typedef struct _pl_agent_pool_threads_data {

	//-------------------------------------------------------------------------
	// Pool thread data access synchronization data.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	HANDLE semaphore;
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

#ifndef __PL_MACOSX__
	sem_t semaphore;
#else // __PL_MACOSX__
	sem_t *semaphore;
	char semaphore_name[SEMAPHORE_NAME_MAX_SIZE + 1];
#endif // __PL_MACOSX__

#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Pool thread data - state & IPC data.
	//-------------------------------------------------------------------------
	int f_busy;
	SOCKET new_socket;

} PL_AGENT_POOL_THREADS_DATA, *PPL_AGENT_POOL_THREADS_DATA;

typedef struct _pl_agent_data {

#ifdef _DEBUG

	//-------------------------------------------------------------------------
	// Data used to collect API call stats. 
	//-------------------------------------------------------------------------
	unsigned long long pl_open_count;
	unsigned long long pl_close_count;
	unsigned long long pl_attach_count;
	unsigned long long pl_read_count;
	unsigned long long pl_write_count;

	//-------------------------------------------------------------------------
	// Data used to collect error stats. 
	//-------------------------------------------------------------------------
	unsigned long long pl_open_errors_count;
	unsigned long long pl_close_errors_count;
	unsigned long long pl_attach_errors_count;
	unsigned long long pl_read_errors_count;
	unsigned long long pl_write_errors_count;

	//-------------------------------------------------------------------------
	// API call stats synchronisation object. 
	//-------------------------------------------------------------------------
	#ifdef __PL_WINDOWS__
		CRITICAL_SECTION cs;
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		#ifndef __PL_MACOSX__
			sem_t cs;
		#else // __PL_MACOSX__
			sem_t *cs;
			char cs_name[
				SEMAPHORE_NAME_MAX_SIZE + 1
			];
		#endif // __PL_MACOSX__
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#endif // _DEBUG

	//-------------------------------------------------------------------------
	// Data used to get IP @. 
	//-------------------------------------------------------------------------
	char *ip_address;

	//-------------------------------------------------------------------------
	// ADMIN & PL port listener threads IPC data.
	//-------------------------------------------------------------------------
	PL_AGENT_IPC_DATA admin_port_listener_thread_ipc_data;
	PL_AGENT_IPC_DATA pl_port_listener_thread_ipc_data;

	//-------------------------------------------------------------------------
	// CLI related data.
	//-------------------------------------------------------------------------
	int f_admin_port;
	char *admin_port_string;
	unsigned int admin_port_value;
	int f_pl_port;
	char *pl_port_string;
	unsigned int pl_port_value;
	int f_threads_in_pool;
	int threads_in_pool_value;
	int f_encrypt;

	//-------------------------------------------------------------------------
	// Data used to detect help / version request
	//-------------------------------------------------------------------------
	int f_version_requested;
	int f_help_requested;

	//-------------------------------------------------------------------------
	// Pool thread data sets.
	//-------------------------------------------------------------------------
	PL_AGENT_POOL_THREADS_DATA *pool_threads_data;

	//-------------------------------------------------------------------------
	// Threads related data (pool threads and ADMIN port listener thread)
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// Main thread
	//-------------------------------------------------------------------------
	HANDLE *h_main_thread_done;

	//-------------------------------------------------------------------------
	// ADMIN port listener thread
	//-------------------------------------------------------------------------
	HANDLE h_admin_port_listener_thread;
	DWORD admin_port_listener_thread_ids;
	HANDLE h_admin_port_listener_thread_done;

	//-------------------------------------------------------------------------
	// PL port listener thread
	//-------------------------------------------------------------------------
	HANDLE h_pl_port_listener_thread;
	DWORD pl_port_listener_thread_ids;
	HANDLE h_pl_port_listener_thread_done;

	//-------------------------------------------------------------------------
	// Pool threads
	//-------------------------------------------------------------------------
	HANDLE *h_pool_threads;
	HANDLE *h_pool_threads_do;
	HANDLE *h_pool_threads_done;
	DWORD *pool_threads_ids;

#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

	#ifndef __PL_MACOSX__

		//---------------------------------------------------------------------
		// Main thread
		//---------------------------------------------------------------------
		sem_t h_main_thread_done;

		//---------------------------------------------------------------------
		// ADMIN port listener thread
		//---------------------------------------------------------------------
		sem_t h_admin_port_listener_thread_done;

		//---------------------------------------------------------------------
		// PL port listener thread
		//---------------------------------------------------------------------
		sem_t h_pl_port_listener_thread_done;

		//---------------------------------------------------------------------
		// Pool threads
		//---------------------------------------------------------------------
		sem_t *h_pool_threads_do;
		sem_t *h_pool_threads_done;

	#else // __PL_MACOSX__

		//---------------------------------------------------------------------
		// Main thread
		// Note:
		//    MacOS X doesn't have unnamed semaphores
		//---------------------------------------------------------------------
		sem_t *h_main_thread_done;
		char main_thread_done_sem_name[
			SEMAPHORE_NAME_MAX_SIZE + 1
		];

		//---------------------------------------------------------------------
		// ADMIN port listener thread
		//---------------------------------------------------------------------
		sem_t *h_admin_port_listener_thread_done;
		char admin_port_listener_thread_done_sem_name[
			SEMAPHORE_NAME_MAX_SIZE + 1
		];

		//---------------------------------------------------------------------
		// PL port listener thread
		//---------------------------------------------------------------------
		sem_t *h_pl_port_listener_thread_done;
		char pl_port_listener_thread_done_sem_name[
			SEMAPHORE_NAME_MAX_SIZE + 1
		];

		//---------------------------------------------------------------------
		// Pool threads
		//---------------------------------------------------------------------
		sem_t **h_pool_threads_do;
		char **pool_threads_do_sem_names;
		sem_t **h_pool_threads_done;
		char **pool_threads_done_sem_names;

	#endif // __PL_MACOSX__

	//-------------------------------------------------------------------------
	// ADMIN port listener thread
	//-------------------------------------------------------------------------
	pthread_t h_admin_port_listener_thread;

	//-------------------------------------------------------------------------
	// PL port listener thread
	//-------------------------------------------------------------------------
	pthread_t h_pl_port_listener_thread;

	//-------------------------------------------------------------------------
	// Pool threads
	//-------------------------------------------------------------------------
	pthread_t *h_pool_threads;

#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Data used to manage errors.
	//-------------------------------------------------------------------------
	unsigned long long errors_count;

} PL_AGENT_DATA, *PPL_AGENT_DATA;

typedef enum _pl_agent_error_code {

	//-------------------------------------------------------------------------
	// No erro error.
	//-------------------------------------------------------------------------
	PL_AGENT_NO_ERROR = 0,

	//-------------------------------------------------------------------------
	// System errors.
	//-------------------------------------------------------------------------
	PL_AGENT_UNABLE_TO_STOP_AGENT,
	PL_AGENT_UNABLE_TO_CREATE_UUID,
	PL_AGENT_INVALID_USER_INPUT,
	PL_AGENT_INVALID_MESSAGE_DATA,
	PL_AGENT_UNABLE_TO_ACTIVATE_MEMORY_LEAK_DETECTION,
	PL_AGENT_UNABLE_TO_INSTALL_SIGNAL_HANDLER,
	PL_AGENT_OUT_OF_MEMORY,
	PL_AGENT_OUT_OF_BUFFER_SPACE,
	PL_AGENT_UNABLE_TO_CREATE_SYNCHRONIZATION_OBJECT,
	PL_AGENT_UNABLE_TO_CREATE_THREAD,
	PL_AGENT_UNABLE_TO_SYNCHRONIZE,
	PL_AGENT_UNABLE_TO_DESTROY_SYNCHRONIZATION_OBJECT,

	//-------------------------------------------------------------------------
	// IPC errors.
	//-------------------------------------------------------------------------
	PL_AGENT_UNABLE_TO_INITIALIZE_SOCKET,
	PL_AGENT_UNABLE_TO_TEARDOWN_SOCKET,
	PL_AGENT_UNABLE_TO_GET_HOST_STRUCTURE_FROM_HOSTNAME,
	PL_AGENT_UNABLE_TO_CONVERT_ADDRESS_STRING_INTO_STRUCTURE,
	PL_AGENT_UNABLE_TO_GET_ADDRESS_INFO,
	PL_AGENT_UNABLE_TO_CREATE_SOCKET,
	PL_AGENT_UNABLE_TO_CLOSE_SOCKET,
	PL_AGENT_UNABLE_TO_CONNECT_TO_SOCKET,
	PL_AGENT_UNABLE_TO_SEND_VIA_SOCKET,
	PL_AGENT_UNABLE_TO_SHUTDOWN_SOCKET,
	PL_AGENT_UNABLE_TO_SET_SOCKET_OPTIONS,
	PL_AGENT_UNABLE_TO_LISTEN_SOCKET,
	PL_AGENT_UNABLE_TO_ACCEPT_SOCKET,
	PL_AGENT_UNABLE_TO_RECEIVE_FROM_SOCKET,

	//-------------------------------------------------------------------------
	// PL protocol errors.
	//-------------------------------------------------------------------------
	PL_AGENT_PROTOCOL_ERROR,
	PL_AGENT_PROTOCOL_UNKNOWN_OP_CODE,

	//-------------------------------------------------------------------------
	// PL API errors.
	//-------------------------------------------------------------------------
	PL_AGENT_UNABLE_TO_PL_OPEN,
	PL_AGENT_UNABLE_TO_PL_ATTACH,
	PL_AGENT_UNABLE_TO_PL_CLOSE,
	PL_AGENT_UNABLE_TO_PL_READ,
	PL_AGENT_UNABLE_TO_PL_WRITE

} PL_AGENT_ERROR_CODE, *PPL_AGENT_ERROR_CODE;

typedef enum _admin_command_code {

	PL_ADMIN_COMMAND_LOOK_UP_UUID = 0,

} ADMIN_COMMAND_CODE, *PADMIN_COMMAND_CODE;

typedef struct _pl_agent_command {

	int command_code;
	char binary_uuid_argument[PL_UUID_SIZE];

} PL_AGENT_COMMAND, *PPL_AGENT_COMMAND;

//-----------------------------------------------------------------------------
// macros
// Note:
//    PL_AGENT_DEBUG_MESSAGE... macros requires a char tmp_buffer[PL_MAX_PATH] 
//    variable to exist.
//-----------------------------------------------------------------------------
#define CHECK_SOCKET(s, j) \
	do { \
		if( \
			(s).socket == \
			INVALID_SOCKET \
		) { \
			goto j; \
		} \
	} while(0)

#ifndef S_ISDIR
	#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif // S_ISDIR

#ifdef _DEBUG

	#define PL_AGENT_DEBUG_MESSAGE_WITH_ULL(s, u) \
		do { \
			memset( \
				tmp_buffer, \
				0, \
				sizeof(tmp_buffer) \
			); \
			sprintf( \
				tmp_buffer, \
				(s), \
				(u) \
			); \
			pl_agent_message( \
				tmp_buffer, \
				NULL \
			); \
		} while(0)

	#define PL_AGENT_DEBUG_MESSAGE(s) \
		do { \
			memset( \
				tmp_buffer, \
				0, \
				sizeof(tmp_buffer) \
			); \
			sprintf( \
				tmp_buffer, \
				"%s", \
				(s) \
			); \
			pl_agent_message( \
				tmp_buffer, \
				NULL \
			); \
		} while(0)

	#define PL_AGENT_DEBUG_MESSAGE_WITH_STRING(s1, s2) \
		do { \
			memset( \
				tmp_buffer, \
				0, \
				sizeof(tmp_buffer) \
			); \
			sprintf( \
				tmp_buffer, \
				(s1), \
				(s2) \
			); \
			pl_agent_message( \
				tmp_buffer, \
				NULL \
			); \
		} while(0)

	#define PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(s, v) \
		do { \
			memset( \
				tmp_buffer, \
				0, \
				sizeof(tmp_buffer) \
			); \
			sprintf( \
				tmp_buffer, \
				(s), \
				(v) \
			); \
			pl_agent_message( \
				tmp_buffer, \
				NULL \
			); \
		} while(0)

	#define PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE_AND_STRING(s1, v, s2) \
		do { \
			memset( \
				tmp_buffer, \
				0, \
				sizeof(tmp_buffer) \
			); \
			sprintf( \
				tmp_buffer, \
				(s1), \
				(v), \
				(s2) \
			); \
			pl_agent_message( \
				tmp_buffer, \
				NULL \
			); \
		} while(0)

	#define PL_AGENT_ERROR(e) \
		do { \
			memset( \
				tmp_buffer, \
				0, \
				sizeof(tmp_buffer) \
			); \
			sprintf( \
				tmp_buffer, \
				"ERROR [%d]d - [%x]h : at line [%d] in file [%s].\n", \
				errno, \
				errno, \
				__LINE__, \
				__FILE__ \
			); \
			pl_agent_message( \
				tmp_buffer, \
				NULL \
			); \
		} while(0)

	//-------------------------------------------------------------------------
	// Note:
	//    PL_AGENT_INCREMENT_API_USE_COUNT and PL_AGENT_INCREMENT_ERROR_COUNT
	//    macros requires a PPL_AGENT_DATA p. PL_AGENT_INCREMENT_API_USE_COUNT
	//    and PL_AGENT_INCREMENT_ERROR_COUNT macros on non-Windows OS also
	//    requires int ret variable in the scope.
	//-------------------------------------------------------------------------
	#ifdef __PL_WINDOWS__

		#define PL_AGENT_INCREMENT_API_USE_COUNT(c) \
			do { \
				EnterCriticalSection(&p->cs); \
				(c)++; \
				LeaveCriticalSection(&p->cs); \
			} while(0)

		#define PL_AGENT_INCREMENT_ERROR_COUNT(c) \
			do { \
				EnterCriticalSection(&p->cs); \
				(c)++; \
				LeaveCriticalSection(&p->cs); \
			} while(0)

	#endif // __PL_WINDOWS__

	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

		#ifndef __PL_MACOSX__

			#define PL_AGENT_INCREMENT_API_USE_COUNT(c) \
				do { \
					ret = sem_wait( \
						&p->cs \
					); \
					if(ret != 0) { \
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); \
					} \
					(c++); \
					ret = sem_post( \
						&p->cs \
					); \
					if(ret != 0) { \
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); \
					} \
				} while(0)

			#define PL_AGENT_INCREMENT_ERROR_COUNT(c) \
				do { \
					ret = sem_wait( \
						&p->cs \
					); \
					if(ret != 0) { \
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); \
					} \
					(c++); \
					ret = sem_post( \
						&p->cs \
					); \
					if(ret != 0) { \
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); \
					} \
				} while(0)

		#else // __PL_MACOSX__
		
			#define PL_AGENT_INCREMENT_API_USE_COUNT(c) \
				do { \
					ret = sem_wait( \
						p->cs \
					); \
					if(ret != 0) { \
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); \
					} \
					(c++); \
					ret = sem_post( \
						p->cs \
					); \
					if(ret != 0) { \
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); \
					} \
				} while(0)

			#define PL_AGENT_INCREMENT_ERROR_COUNT(c) \
				do { \
					ret = sem_wait( \
						p->cs \
					); \
					if(ret != 0) { \
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); \
					} \
					(c++); \
					ret = sem_post( \
						p->cs \
					); \
					if(ret != 0) { \
						PL_AGENT_ERROR(PL_AGENT_UNABLE_TO_SYNCHRONIZE); \
					} \
				} while(0)
		
		#endif // __PL_MACOSX__
	
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

#else // _DEBUG

	#define PL_AGENT_DEBUG_MESSAGE(s) \
		;

	#define PL_AGENT_DEBUG_MESSAGE_WITH_STRING(s1, s2) \
		;

	#define PL_AGENT_DEBUG_MESSAGE_WITH_INTEGER_VALUE(s, v) \
		;

	#define PL_AGENT_INCREMENT_API_USE_COUNT(c) \
		;

	#define PL_AGENT_INCREMENT_ERROR_COUNT(c) \
		;

	#define PL_AGENT_ERROR(e) \
		do { \
			pl_agent_error( \
				(e), \
				NULL, \
				0 \
			); \
		} while(0)

#endif // _DEBUG

#define PL_AGENT_MESSAGE_WITH_ULL(s, u) \
	do { \
		memset( \
			tmp_buffer, \
			0, \
			sizeof(tmp_buffer) \
		); \
		sprintf( \
			tmp_buffer, \
			(s), \
			(u) \
		); \
		pl_agent_message( \
			tmp_buffer, \
			NULL \
		); \
	} while(0)

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
extern PL_STATUS pl_agent_cli_parser(PPL_AGENT_DATA, int, char *[]);
extern void pl_agent_error(PL_AGENT_ERROR_CODE, char *, int);
extern size_t pl_agent_message(char *, char *);
extern PL_STATUS switch_socket_to_non_blocking_mode(SOCKET);
extern PL_STATUS switch_socket_to_blocking_mode(SOCKET);
extern PL_STATUS service_time_stamp(char *);
extern PL_STATUS stop_agent(PPL_AGENT_DATA);
extern PL_STATUS decode_admin_command(PPL_AGENT_COMMAND, size_t, char *);

#ifdef _DEBUG
	extern void pl_agent_hex_dump_string(char *, size_t, char *);
	extern void pl_agent_hex_dump_message(char *, size_t, char *);
	extern void pl_agent_decode_message(int, size_t, char *);
	extern void pl_agent_decode_response(int, PL_PROTOCOL_OPCODE, size_t, char *);
#endif // _DEBUG

#ifdef __PL_WINDOWS__
	extern BOOL signal_handler(DWORD);
	LPTHREAD_START_ROUTINE admin_port_listener_thread(void *);
	LPTHREAD_START_ROUTINE pl_port_listener_thread(void *);
	LPTHREAD_START_ROUTINE pool_thread(void *);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	extern void signal_handler();
	void *admin_port_listener_thread(void *);
	void *pl_port_listener_thread(void *);
	void *pool_thread(void *);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PRODUCTIVITY_LINK_AGENT__
