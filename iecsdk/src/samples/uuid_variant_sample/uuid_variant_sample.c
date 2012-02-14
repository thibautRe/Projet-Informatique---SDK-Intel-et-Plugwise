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

#include <assert.h>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

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

#include "productivity_link.h"
#include "productivity_link_agent.h" // for protocol defines

//-----------------------------------------------------------------------------
// Consts.
//-----------------------------------------------------------------------------
#define COUNTERS_COUNT 5

#define APPLICATION_NAME "admin look-up"
#define COUNTERS_NAME \
	"Hello", \
	"World", \
	NULL, \
	"A", \
	"b" \

enum {
	INDEX_COUNTER_A = 0,
	INDEX_COUNTER_B,
	INDEX_COUNTER_C,
	INDEX_COUNTER_D,
	INDEX_COUNTER_E
};

//-----------------------------------------------------------------------------
// Macros.
//-----------------------------------------------------------------------------
#define CHECK_SUCCESS(v) \
	if((v) != PL_SUCCESS) { \
		printf("Error = %d.\n", GetLastError()); \
		assert(0); \
	}

//-----------------------------------------------------------------------------
// Function prototypes.
//-----------------------------------------------------------------------------
extern PL_STATUS build_pl_config_file_name(
	uuid_t, 
	size_t, 
	char *
);
extern PL_STATUS build_pl_config_file_name_with_string_uuid(
	char *, 
	size_t, 
	char *
);
extern PL_STATUS build_look_up_command(
	uuid_t, 
	size_t, 
	size_t *, 
	unsigned char *
);
extern PL_STATUS send_admin_command_to_agent(
	PL_PROTOCOL_SIZET, 
	unsigned char *,
	char *
);

//-----------------------------------------------------------------------------
// This code demonstrates a way to workaround the platform specific variant
// issue with UUIDs.  For instance, this sample has to run on Windows and the
// agent on a *NIX box.  The sample must be build in file system-less mode.
// The sample perfoms the following steps:
//    1 - open a PL
//    2 - use the retuened UUID to build a PL config file name and try to
//        attach to it.  If there is a UUID variant, then pl_attach will
//        fail with a PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE error.
//    3 - build a look-up UUID command and send it to the agent
//    4 - if a UUID string is returned, then update the PL config file name
//        and call pl_attach again.
// Note:
//    In this sample, the UUID is available as-is in the process.  However,
//    in multi-process configuration, the UUID should be shared with the
//    process attaching to the PL using any suitable IPC.
//-----------------------------------------------------------------------------

int main(void) {

	//-------------------------------------------------------------------------
	// Generic variables.
	//-------------------------------------------------------------------------
	int i = 0;
	DWORD dw_ret = 0;
	PL_STATUS ret = PL_FAILURE;
	PL_ERROR err = PL_INVALID_DESCRIPTOR;
	PL_PROTOCOL_SIZET bytes = 0;
	
	//-------------------------------------------------------------------------
	// PL related variables.
	//-------------------------------------------------------------------------
	uuid_t uuid;
	int pld = PL_INVALID_DESCRIPTOR;
	int attach_pld = PL_INVALID_DESCRIPTOR;
	char *my_application = APPLICATION_NAME;
	const char *my_counters[COUNTERS_COUNT] = { 
		COUNTERS_NAME
	};

	ULONGLONG a = 1;
	ULONGLONG b = 2;
	ULONGLONG c = 3;
	ULONGLONG d = 4;
	ULONGLONG e = 5;

	//-------------------------------------------------------------------------
	// ADMIN command related variables.
	//-------------------------------------------------------------------------
	size_t bytes_in_message = 0;
	unsigned char admin_command_buffer[PL_MAX_PATH] = { '\0' };

	//-------------------------------------------------------------------------
	// PL config related variables.
	//-------------------------------------------------------------------------
	char pl_config_file_name[PL_MAX_PATH] = { '\0' };
	char remote_uuid[PL_UUID_MAX_CHARS + 1] = { '\0' };

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// 1 - open a PL.
	//-------------------------------------------------------------------------
	pld = pl_open(
		my_application, 
		COUNTERS_COUNT, 
		my_counters, 
		&uuid
	);
	printf(
		"PL Descriptor Returned by pl_open = [%d].\n", 
		pld
	);
	assert(pld != PL_INVALID_DESCRIPTOR);

	ret = pl_write(
		pld, 
		&a, 
		INDEX_COUNTER_A
	);
	CHECK_SUCCESS(ret);
	printf(
		"...Wrote [%I64u] Into Counter [%u] of PL [%d].\n",
		a,
		INDEX_COUNTER_A,
		pld
	);
	ret = pl_write(
		pld, 
		&b, 
		INDEX_COUNTER_B
	);
	CHECK_SUCCESS(ret);
	printf(
		"...Wrote [%I64u] Into Counter [%u] of PL [%d].\n",
		b,
		INDEX_COUNTER_B,
		pld
	);
	ret = pl_write(
		pld, 
		&c, 
		INDEX_COUNTER_C
	);
	CHECK_SUCCESS(ret);
	printf(
		"...Wrote [%I64u] Into Counter [%u] of PL [%d].\n",
		c,
		INDEX_COUNTER_C,
		pld
	);
	ret = pl_write(
		pld, 
		&d, 
		INDEX_COUNTER_D
	);
	CHECK_SUCCESS(ret);
	printf(
		"...Wrote [%I64u] Into Counter [%u] of PL [%d].\n",
		d,
		INDEX_COUNTER_D,
		pld
	);
	ret = pl_write(
		pld, 
		&e, 
		INDEX_COUNTER_E
	);
	CHECK_SUCCESS(ret);
	printf(
		"...Wrote [%I64u] Into Counter [%u] of PL [%d].\n",
		e,
		INDEX_COUNTER_E,
		pld
	);

	//-------------------------------------------------------------------------
	// 2 - build PL config file name and try to attach.
	//-------------------------------------------------------------------------
	ret = build_pl_config_file_name(
		uuid,
		sizeof(pl_config_file_name),
		pl_config_file_name
	);
	attach_pld = pl_attach(pl_config_file_name);
	printf(
		"PL Descriptor Returned by pl_attach to [%s] = [%d].\n",
		pl_config_file_name,
		attach_pld
	);
	if(attach_pld == PL_INVALID_DESCRIPTOR) {
		dw_ret = GetLastError();
		if(dw_ret == PL_FILESYSTEM_LESS_REMOTE_CRITICAL_FAILURE) {

			//-----------------------------------------------------------------
			// 3 - build ADMIN look-up command.
			//-----------------------------------------------------------------
			printf(
				"Attach to [%s] Has Failed Possibly Because of a platform UUID variant.\n",
				pl_config_file_name,
				pld
			);
			ret = build_look_up_command(
				uuid,
				sizeof(admin_command_buffer),
				&bytes_in_message,
				admin_command_buffer
			);
			printf(
				"Querying the Agent With [%s] to Retrieve the Remote UUID string for PL [%d].\n",
				admin_command_buffer,
				pld
			);
			CHECK_SUCCESS(ret);

			//-----------------------------------------------------------------
			// Send the command to the agent.
			//-----------------------------------------------------------------
			printf("Sending the Query to the Agent.\n");
			bytes = (PL_PROTOCOL_SIZET)bytes_in_message;
			ret = send_admin_command_to_agent(
				bytes,
				admin_command_buffer,
				&remote_uuid[0]
			);
			if(ret == PL_SUCCESS) {

				//-------------------------------------------------------------
				// 4 - update the PL config file name and try to attach again.
				//-------------------------------------------------------------
				ret = build_pl_config_file_name_with_string_uuid(
					remote_uuid,
					sizeof(pl_config_file_name),
					pl_config_file_name
				);
				CHECK_SUCCESS(ret);
				printf(
					"The Agent Sent Back the Remote UUID string for PL [%d].\n",
					pld
				);
				attach_pld = pl_attach(pl_config_file_name);
				if(attach_pld == PL_INVALID_DESCRIPTOR) {
					assert(0);
				}
				printf(
					"Attach to [%s] Has Succeeded, and PL Descriptor Returned by pl_open = [%d].\n",
					pl_config_file_name,
					attach_pld
				);
			} else {
				assert(0);
			}
		} else {
			CHECK_SUCCESS(PL_FAILURE);
		}
	}

	if(attach_pld != PL_INVALID_DESCRIPTOR) {

		//---------------------------------------------------------------------
		// The UUID platform variant issue is solved, let's read.
		//---------------------------------------------------------------------
		ret = pl_read(
			attach_pld, 
			&a, 
			INDEX_COUNTER_A
		);
		CHECK_SUCCESS(ret);
		printf(
			"...Read [%I64u] From Counter [%u] of PL [%d].\n",
			a,
			INDEX_COUNTER_A,
			attach_pld
		);
		ret = pl_read(
			attach_pld, 
			&b, 
			INDEX_COUNTER_B
		);
		CHECK_SUCCESS(ret);
		printf(
			"...Read [%I64u] From Counter [%u] of PL [%d].\n",
			b,
			INDEX_COUNTER_B,
			attach_pld
		);
		ret = pl_read(
			attach_pld, 
			&c, 
			INDEX_COUNTER_C
		);
		CHECK_SUCCESS(ret);
		printf(
			"...Read [%I64u] From Counter [%u] of PL [%d].\n",
			c,
			INDEX_COUNTER_C,
			attach_pld
		);
		ret = pl_read(
			attach_pld, 
			&d, 
			INDEX_COUNTER_D
		);
		CHECK_SUCCESS(ret);
		printf(
			"...Read [%I64u] From Counter [%u] of PL [%d].\n",
			d,
			INDEX_COUNTER_D,
			attach_pld
		);
		ret = pl_read(
			attach_pld, 
			&e, 
			INDEX_COUNTER_E
		);
		CHECK_SUCCESS(ret);
		printf(
			"...Read [%I64u] From Counter [%u] of PL [%d].\n",
			e,
			INDEX_COUNTER_E,
			attach_pld
		);
	}

	//-------------------------------------------------------------------------
	// Clean-up.
	//-------------------------------------------------------------------------
	ret = pl_close(pld);
	CHECK_SUCCESS(ret);
	if(attach_pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(attach_pld);
		CHECK_SUCCESS(ret);
	}
	printf("Done.\n");
	return(0);
}

//-----------------------------------------------------------------------------
// build_pl_config_file_name.
//-----------------------------------------------------------------------------
PL_STATUS build_pl_config_file_name(
	uuid_t uuid, 
	size_t buffer_size, 
	char *buffer
) {

	size_t st_ret = 0;
	TCHAR *puuid = NULL;
	RPC_STATUS rpc_ret = 0;	
	char uuid_buffer[PL_UUID_MAX_CHARS + 1] = { '\0' };

	assert(buffer != NULL);
	assert(buffer_size != 0);

	//-------------------------------------------------------------------------
	// Clear buffer.
	//-------------------------------------------------------------------------
	memset(
		buffer,
		0,
		buffer_size
	);
	
	//-------------------------------------------------------------------------
	// Unparse UUID
	//-------------------------------------------------------------------------
	UuidToString(
		&uuid, 
		&puuid
	);
	assert(puuid != NULL);
	wcstombs_s(
		&st_ret, 
		uuid_buffer, 
		sizeof(uuid_buffer), 
		puuid, 
		_TRUNCATE
	);

	//-------------------------------------------------------------------------
	// Build PL config file name.
	// Note:
	//    the pl_agent sample does PL_FOLDER translation, so no need to care
	//    if PL_FOLDER on the pl_agent host system is different. 
	//-------------------------------------------------------------------------
	sprintf(
		buffer,
		"%s\\%s_%s\\%s",
		PL_FOLDER_STRING,
		APPLICATION_NAME,
		uuid_buffer,
		PL_CONFIG_FILE_NAME_STRING
	);

	//-------------------------------------------------------------------------
	// Clean-up.
	//-------------------------------------------------------------------------
	rpc_ret = RpcStringFree(&puuid);
	assert(rpc_ret == RPC_S_OK);

	return(PL_SUCCESS);
}

//-----------------------------------------------------------------------------
// build_pl_config_file_name_with_string_uuid.
//-----------------------------------------------------------------------------
extern PL_STATUS build_pl_config_file_name_with_string_uuid(
	char *puuid, 
	size_t buffer_size, 
	char *buffer
) {

	assert(puuid != NULL);
	assert(buffer != NULL);
	assert(buffer_size != 0);

	//-------------------------------------------------------------------------
	// Clear buffer.
	//-------------------------------------------------------------------------
	memset(
		buffer,
		0,
		buffer_size
	);
	
	//-------------------------------------------------------------------------
	// Build PL config file name.
	// Note:
	//    the pl_agent sample does PL_FOLDER translation, so no need to care
	//    if PL_FOLDER on the pl_agent host system is different. 
	//-------------------------------------------------------------------------
	sprintf(
		buffer,
		"%s\\%s_%s\\%s",
		PL_FOLDER_STRING,
		APPLICATION_NAME,
		puuid,
		PL_CONFIG_FILE_NAME_STRING
	);

	return(PL_SUCCESS);
}

//-----------------------------------------------------------------------------
// build_look_up_command.
//-----------------------------------------------------------------------------
PL_STATUS build_look_up_command(
	uuid_t uuid, 
	size_t buffer_size,
	size_t *bytes,
	unsigned char *buffer
) {
	
	int index = 0;
		
	assert(bytes != NULL);
	assert(buffer != NULL);
	assert(buffer_size != 0);

	//-------------------------------------------------------------------------
	// Clear buffer.
	//-------------------------------------------------------------------------
	memset(
		buffer,
		0,
		buffer_size
	);

	//-------------------------------------------------------------------------
	// build command.
	//-------------------------------------------------------------------------
	index = sprintf(
		buffer,
		"%s%s",
		PL_ADMIN_PROTOCOL_COMMAND_LOOK_UP_UUID_STRING,
		PL_ADMIN_PROTOCOL_COMMAND_ITEM_DELIMITER
	);
	*bytes = (size_t)index;
	memcpy(
		&buffer[index],
		&uuid,
		PL_PROTOCOL_UUID_SIZE
	);
	*bytes += PL_PROTOCOL_UUID_SIZE;

	return(PL_SUCCESS);
}

//-----------------------------------------------------------------------------
// send_admin_command_to_agent.
//-----------------------------------------------------------------------------
PL_STATUS send_admin_command_to_agent(
	PL_PROTOCOL_SIZET bytes_in_buffer, 
	unsigned char *buffer,
	char *puuid
) {

	//-------------------------------------------------------------------------
	// Generic variables.
	//-------------------------------------------------------------------------
	int ret = -1;
	char *pc = NULL;
	errno_t eno_ret = -1;
	size_t length = 0;
	DWORD dwret = 0;

	//-------------------------------------------------------------------------
	// Message related variables.
	//-------------------------------------------------------------------------
	char input_buffer[PL_MAX_INPUT_BUFFER_SIZE] = { '\0' };
	char *output_message = NULL;
	PL_PROTOCOL_SIZET total_bytes_to_send = 0;
	PL_AGENT_IPC_BUFFER message = {{ '\0' }};
	PL_PROTOCOL_SIZET message_size = 0;

	//-------------------------------------------------------------------------
	// Environment variable related variables.
	//-------------------------------------------------------------------------
	size_t bytes_left_in_buffer = 0;
	char *env_port = NULL;
	char *env_address = NULL;

	//-------------------------------------------------------------------------
	// IPC related variables.
	//-------------------------------------------------------------------------
	WSADATA windows_socket_data;
	int connection_attempt_count = 0;
	char address[PL_MAX_NODE_NAME_SIZE];
	char port[PL_MAX_PORT_NAME_SIZE];
	ADDRINFO address_info_hint;
	ADDRINFO *address_info;
	ADDRINFO *pa = NULL;
	SOCKET _socket = INVALID_SOCKET;
	size_t bytes_sent = 0;
	size_t bytes_to_send = 0;
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;
	size_t total_bytes_to_read = 0;

	//-------------------------------------------------------------------------

	assert(buffer != NULL);
	assert(bytes_in_buffer != 0);
	assert(puuid != NULL);

	//-------------------------------------------------------------------------
	// Encapsulate message in a PL_PROTOCOL message.
	//-------------------------------------------------------------------------
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
	//-------------------------------------------------------------------------
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
	//-------------------------------------------------------------------------
	total_bytes_to_send = 0;
	output_message = message.data;
	memset(
		output_message,
		0,
		sizeof(message.data)
	);
	memcpy(
		&output_message[
			PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_INDEX
		],
		&bytes_in_buffer,
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_send += PL_PROTOCOL_SIZET_SIZE;
	memcpy(
		&output_message[
			PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_INDEX +
			PL_PROTOCOL_SIZET_SIZE
		],
		buffer,
		bytes_in_buffer
	);
	total_bytes_to_send += bytes_in_buffer;
	output_message[
		PL_ADMIN_PROTOCOL_INPUT_COMMAND_STRING_INDEX +
		PL_PROTOCOL_SIZET_SIZE +
		bytes_in_buffer
	] = PL_PROTOCOL_EOR;
	total_bytes_to_send += PL_PROTOCOL_EOR_SIZE;
	memcpy(
		&output_message[
			PL_PROTOCOL_BYTES_INDEX
		],
		&total_bytes_to_send,
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_send += PL_PROTOCOL_SIZET_SIZE;

	//-------------------------------------------------------------------------
	// Send the message.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Initialize Winsoks to communicate with the agent.
	//-------------------------------------------------------------------------
	ret = WSAStartup(
		MAKEWORD(2, 2), 
		&windows_socket_data
	);
	assert(ret == 0);

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_ADDRESS environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	eno_ret = _dupenv_s(
		&env_address,
		&length,
		PL_DEFAULT_PL_AGENT_ADDRESS_ENVAR_NAME
	);
	if(
		(eno_ret != 0) ||
		(length == 0)
	) {
		strncpy_s(
			address,
			sizeof(address),
			PL_DEFAULT_PL_AGENT_ADDRESS,
			_TRUNCATE
		);
	} else {
		strncpy_s(
			address,
			sizeof(address),
			env_address,
			_TRUNCATE
		);
		free(env_address);
		env_address = NULL;
	}

	//-------------------------------------------------------------------------
	// Get the PL_AGENT_ADMIN_PORT environment variable to overwrite defaults.
	//-------------------------------------------------------------------------
	eno_ret = _dupenv_s(
		&env_port,
		&length,
		PL_DEFAULT_ADMIN_PORT_ENVAR_NAME
	);
	if(
		(eno_ret != 0) ||
		(length == 0)
	) {
		strncpy_s(
			port,
			sizeof(port),
			PL_DEFAULT_PL_AGENT_ADMIN_PORT,
			_TRUNCATE
		);
	} else {
		strncpy_s(
			port,
			sizeof(port),
			env_port,
			_TRUNCATE
		);
		free(env_port);
		env_port = NULL;
	}

	//-------------------------------------------------------------------------
	// Initialize address data.
	//-------------------------------------------------------------------------
	memset(
		&address_info_hint, 
		0,
		sizeof(address_info_hint)
	);
	address_info_hint.ai_family = 
		PL_ADDRESS_INFO_HINT_AI_FAMILY
	;
	address_info_hint.ai_socktype = 
		PL_ADDRESS_INFO_HINT_AI_SOCKTYPE
	;
	address_info_hint.ai_protocol = 
		PL_ADDRESS_INFO_HINT_AI_PROTOCOL
	;
	address_info_hint.ai_flags = 
		PL_ADDRESS_INFO_HINT_AI_FLAGS
	;

	//-------------------------------------------------------------------------
	// Resolve agent address and port.
	//-------------------------------------------------------------------------
	ret = getaddrinfo(
		address,
		port, 
		&address_info_hint, 
		&address_info
	);
	assert(ret == 0);

try_connect:

	//-------------------------------------------------------------------------
	// Attempt to connect to the agent - untill one address succeds.
	//-------------------------------------------------------------------------
	for(
		pa = (struct addrinfo *)address_info;
		pa != NULL; 
		pa = pa->ai_next
	) {

		//---------------------------------------------------------------------
		// Create a socket to communicate with the agent.
		//---------------------------------------------------------------------
		_socket = socket(
				pa->ai_family, 
				pa->ai_socktype, 
				pa->ai_protocol
		);
		assert(_socket != INVALID_SOCKET);

		//---------------------------------------------------------------------
		// Connect to the agent.
		//---------------------------------------------------------------------
		ret = connect(
			_socket,
			pa->ai_addr, 
			(int)pa->ai_addrlen
		);
		if(ret == SOCKET_ERROR) {

			//-----------------------------------------------------------------
			// Failed to connect to the agent on this address, close the socket.
			//-----------------------------------------------------------------
			ret = closesocket(
				_socket
			);
			assert(ret != SOCKET_ERROR);
			continue;
		}
		goto connected;
	}

	//-------------------------------------------------------------------------
	// No connection attempt succeded, signal error.
	// Note on WSAEADDRINUSE:
	//    If you call pl_write at a too high frequency, you may exhaust the
	//    short lived TCP ports.  The default range of short lived ports is 
	//    from 1025 to 5000. Ways to workaround are to increase the dynamic port 
	//    range (to 65534) by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\MaxUserPort;
	//    or by reducing TIME_WAIT from the default 240s (4 minutes) to 30s
	//    by updating the following registry key:
	//    HKLM\System\CurrentControlSet\Services\Tcpip\Parameters\TCPTimedWaitDelay
	//-------------------------------------------------------------------------
	dwret = GetLastError();
	if(dwret == WSAEADDRINUSE) {
		if(connection_attempt_count++ < PL_MAX_CONNECTION_ATTEMPTS) {
#ifndef __PL_NO_SSE_PAUSE_SUPPORT__
			_mm_pause();
#endif // __PL_NO_SSE_PAUSE_SUPPORT__
			goto try_connect;
		}
	}
	assert(0);

connected:

	//-------------------------------------------------------------------------
	// Send!
	//-------------------------------------------------------------------------
	bytes_sent = 0;
	bytes_to_send = total_bytes_to_send;
	do {
		ret = send(
			_socket,
			&output_message[bytes_sent], 
			(int)bytes_to_send, 
			0
		);
		assert(ret != SOCKET_ERROR);
		bytes_sent += ret;
		bytes_to_send = total_bytes_to_send - bytes_sent;
	} while(bytes_to_send > 0);

	//-------------------------------------------------------------------------
	// Receiving agent's answer.
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Read the message size in bytes.
	//-------------------------------------------------------------------------
	memset(
		&input_buffer,
		0,
		PL_MAX_INPUT_BUFFER_SIZE
	);
	bytes_read = 0;
	total_bytes_to_read = PL_PROTOCOL_SIZET_SIZE;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			_socket,
			&input_buffer[bytes_read], 
			(int)bytes_to_read, 
			0
		);
		assert(ret != SOCKET_ERROR);
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	memcpy(
		&message_size,
		&input_buffer[PL_PROTOCOL_BYTES_INDEX],
		PL_PROTOCOL_SIZET_SIZE
	);
	total_bytes_to_read = (PL_PROTOCOL_SIZET)message_size;
	if(
		(total_bytes_to_read <= 0) ||
		(total_bytes_to_read > PL_PROTOCOL_MESSAGE_MAX_SIZE)
	) {
		assert(0);
	}

	//-------------------------------------------------------------------------
	// Read the message data.
	//-------------------------------------------------------------------------
	bytes_read = 0;
	bytes_to_read = total_bytes_to_read;
	do {
		ret = recv(
			_socket,
			&input_buffer[bytes_read + PL_PROTOCOL_BYTES_OFFSET_INDEX], 
			(int)bytes_to_read, 
			0
		);
		assert(ret != SOCKET_ERROR);
		bytes_read += ret;
		bytes_to_read = total_bytes_to_read - bytes_read;
	} while(bytes_to_read > 0);

	//-------------------------------------------------------------------------
	// Close socket.
	//-------------------------------------------------------------------------
	ret = closesocket(
		_socket
	);
	assert(ret != SOCKET_ERROR);
	_socket = INVALID_SOCKET;

	//-------------------------------------------------------------------------
	// Extract agent's answer.
	//-------------------------------------------------------------------------
	// Receiving agent's answer.
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
	//-------------------------------------------------------------------------
	pc = strstr(
		&input_buffer[PL_ADMIN_PROTOCOL_OUTPUT_COMMAND_STRING_OFFSET],
		PL_ADMIN_PROTOCOL_COMMAND_LOOK_UP_UUID_FAILURE
	);
	if(pc != NULL) {
		goto send_admin_command_to_agent_error;
	}
	pc =  strstr(
		&input_buffer[PL_ADMIN_PROTOCOL_OUTPUT_COMMAND_STRING_OFFSET],
		PL_ADMIN_PROTOCOL_COMMAND_ITEM_DELIMITER
	);
	if(pc == NULL) {
		goto send_admin_command_to_agent_error;
	}
	memset(
		puuid,
		0,
		PL_UUID_MAX_CHARS + 1
	);
	memcpy(
		puuid,
		++pc,
		PL_UUID_MAX_CHARS
	 );

	return(PL_SUCCESS);
send_admin_command_to_agent_error:
	return(PL_FAILURE);
}
