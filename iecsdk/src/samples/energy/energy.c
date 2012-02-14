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
	#include <io.h> 
	#include <windows.h>
	#include <tchar.h>
	#include <direct.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include <signal.h> // compile with -std=gnu99 not with -std=c99 
	#include <string.h> // for memset
	#include <unistd.h> // for sleep
	#include <uuid/uuid.h>
	#include <sys/types.h>
	#include <dirent.h>
	#include <ctype.h>
	#include <math.h> // for pow
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"
#include "productivity_link_helper.h"
#include "pub_esrv_counters.h"
#include "energy.h"

//-----------------------------------------------------------------------------
// Global so the signal handler can access it.
//-----------------------------------------------------------------------------
ENERGY_DATA energy_data;

//-----------------------------------------------------------------------------
// program entry point.
//-----------------------------------------------------------------------------
int main(int argc, char *argv[], char *envp[]) {

	//-------------------------------------------------------------------------
	// Generic variables.
	//-------------------------------------------------------------------------
	int ret = -1;
	PENERGY_DATA p = NULL;
	PL_STATUS plret = PL_FAILURE; 
	unsigned long long value = 0;
	char buffer[ENERGY_INPUT_LINE_MAX_SIZE] = { '\0' };
#ifdef __PL_WINDOWS__
	BOOL bret = FALSE;
#endif // __PL_WINDOWS__

	//-------------------------------------------------------------------------
	// ESRV instance handling variables.
	//-------------------------------------------------------------------------
	char esrv_config_file_name_buffer[PL_MAX_PATH] = { '\0' };
	int f_esrv_guid = 0;
	int f_esrv_pid = 0;
	char *env = NULL;

	//-------------------------------------------------------------------------
	// Variables used to build ESRV start command -- if we have to.
	//-------------------------------------------------------------------------
	char esrv_command_buffer[PL_MAX_PATH] = { '\0' };

	//-------------------------------------------------------------------------
	// Variables used to remove ESRV PL after use -- if we started it.
	//-------------------------------------------------------------------------
	char esrv_pl_path_name[PL_MAX_PATH] = { '\0' };
#ifdef __PL_WINDOWS__
	char current_path_name[PL_MAX_PATH] = { '\0' };
	char esrv_pl_config_file_name[PL_MAX_PATH] = { '\0' };
	struct _finddata_t find_files;
	intptr_t file = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	DIR *directory = NULL;
	struct dirent *file = NULL;
	char file_name[PL_MAX_PATH] = { '\0' };
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Variables used to read ESRV's sartup output -- used to get the GUID
	//-------------------------------------------------------------------------
	char *pc = NULL;
	char *token = NULL;
	int input_line_count = 0;
	char esrv_guid[ENERGY_GUID_LENGHT_IN_CHARACTERS + 1] = { '\0' };
#ifdef __PL_WINDOWS__
	DWORD esrv_pid = 0;
	HANDLE esrv_handle = NULL;
	DWORD bytes_read = 0;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	pid_t esrv_pid = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// Signal handler variables.
	//-------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	struct sigaction sa;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//--------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// Retrive the energy structure address.
	//-------------------------------------------------------------------------
	p = &energy_data;
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// Initialize the energy data structure.
	//-------------------------------------------------------------------------
	memset(p, 0, sizeof(ENERGY_DATA));
	p->argc = argc;
	p->argv = argv;
	p->channel = ENERGY_DEFAULT_CHANNEL;
	p->esrv_pld = PL_INVALID_DESCRIPTOR;
	p->esrv_status = ESRV_STATUS_NOT_RUNNING;

	//-------------------------------------------------------------------------
	// Parse user input.
	//-------------------------------------------------------------------------
	plret = parser(&energy_data);
	if(plret != PL_SUCCESS) {
		_ERROR("Unable to make sense of user input.");
	} else {
		if((p->f_help == 1) || (p->f_version == 1)) {
			goto done;
		}
	}

	//-------------------------------------------------------------------------
	// Check for inconsistent user input.
	//-------------------------------------------------------------------------
	if(
		(
			(p->f_guid == 1) && 
			(p->f_guid_shell_variable)
		)
	) {
		_ERROR(
			"Incompatible ESRV instance designation.  Please use --guid or --guid_shell_variable option."
		);
	}
	if(p->f_command == 0) {
		_ERROR(
			"You need to specify a command.  Use energy --help for details."
		);
	}

	//-------------------------------------------------------------------------
	// Select the ESRV instance to use.
	// Note:
	//    If no ESRV id is provided, then an instance is started and ended
	//    by the program.
	// Note:
	//    If GUID is provided, build the pl_config.ini full path name for the
	//    attach.
	// Note:
	//    If CONFIG is provided, then do nothing, we are ready to attach.
	//-------------------------------------------------------------------------
	memset(
		esrv_config_file_name_buffer, 
		0, 
		sizeof(esrv_config_file_name_buffer)
	);
	if(p->f_guid == 1) {
		memcpy(
			esrv_config_file_name_buffer, 
			ENERGY_ESRV_PL_CONFIG_FILE_ROOT, 
			strlen(ENERGY_ESRV_PL_CONFIG_FILE_ROOT)
		);
		strncat(
			esrv_config_file_name_buffer, 
			ESRV_APPLICATION_NAME, 
			strlen(ESRV_APPLICATION_NAME)
		);
		strncat(
			esrv_config_file_name_buffer, 
			ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE, 
			strlen(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE)
		);
		strncat(
			esrv_config_file_name_buffer, 
			p->esrv_guid, 
			strlen(p->esrv_guid)
		);
		strncat(
			esrv_config_file_name_buffer, 
			ENERGY_ESRV_PL_CONFIG_FILE_NAME, 
			strlen(ENERGY_ESRV_PL_CONFIG_FILE_NAME)
		);
		goto attach_to_esrv;
	}
	if(p->f_guid_shell_variable == 1) {
		memcpy(
			esrv_config_file_name_buffer, 
			ENERGY_ESRV_PL_CONFIG_FILE_ROOT, 
			strlen(ENERGY_ESRV_PL_CONFIG_FILE_ROOT)
		);
		strncat(
			esrv_config_file_name_buffer, 
			ESRV_APPLICATION_NAME, 
			strlen(ESRV_APPLICATION_NAME)
		);
		strncat(
			esrv_config_file_name_buffer, 
			ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE, 
			strlen(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE)
		);
		strncat(
			esrv_config_file_name_buffer, 
			p->esrv_guid_shell_variable_value, 
			strlen(p->esrv_guid_shell_variable_value)
		);
		strncat(
			esrv_config_file_name_buffer, 
			ENERGY_ESRV_PL_CONFIG_FILE_NAME, 
			strlen(ENERGY_ESRV_PL_CONFIG_FILE_NAME)
		);
		goto attach_to_esrv;
	}

	//-------------------------------------------------------------------------
	// Because it is easier to type energy -- command than energy --guid xxx --
	// command, we check for the existence of a ENERGY_ESRV_DEFAULT_GUID_SHELL_-
	// -VARIABLE shell variable.  If it exist and has a valid GUID, then it is 
	// used.  If no such variable exist, then energy continues by starting its
	// own instance of ESRV.
	//-------------------------------------------------------------------------
	env = getenv(ENERGY_ESRV_DEFAULT_GUID_SHELL_VARIABLE); 
	if(env != NULL) {
		ret = plh_filter_uuid_string(env);
		if(ret != PL_FAILURE) {
			memcpy(
				esrv_config_file_name_buffer, 
				ENERGY_ESRV_PL_CONFIG_FILE_ROOT, 
				strlen(ENERGY_ESRV_PL_CONFIG_FILE_ROOT)
			);
			strncat(
				esrv_config_file_name_buffer, 
				ESRV_APPLICATION_NAME, 
				strlen(ESRV_APPLICATION_NAME)
			);
			strncat(
				esrv_config_file_name_buffer, 
				ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE, 
				strlen(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE)
			);
			strncat(
				esrv_config_file_name_buffer, 
				env, 
				strlen(env)
			);
			strncat(
				esrv_config_file_name_buffer, 
				ENERGY_ESRV_PL_CONFIG_FILE_NAME, 
				strlen(ENERGY_ESRV_PL_CONFIG_FILE_NAME)
			);
			goto attach_to_esrv;
		}
	}

	//-------------------------------------------------------------------------
	// Build ESRV binary name and command line
	// Note:
	//   cli_buffer holds the ESRV binary name and the command line options.
	//   if the command and the arguments are provided separately to
	//   CreateProcess then the argv count is erroneous in the started 
	//   process and ESRV fails the cli parsing.
	//-------------------------------------------------------------------------
	memset(
		esrv_command_buffer, 
		0, 
		sizeof(esrv_command_buffer)
	);
	strncpy(
		esrv_command_buffer, 
		ENERGY_ESRV_BINARY_NAME, 
		strlen(ENERGY_ESRV_BINARY_NAME)
	);
	if(p->f_esrv_options == 1) {
		strncat(
			esrv_command_buffer, 
			p->esrv_options, 
			strlen(p->esrv_options)
		);
	} else {
		strncat(
			esrv_command_buffer, 
			ENERGY_ESRV_DEFAULT_OPTIONS, 
			strlen(ENERGY_ESRV_DEFAULT_OPTIONS)
		);
	}
	strncat(
		esrv_command_buffer, 
		ENERGY_ESRV_SHELL_OPTION, 
		strlen(ENERGY_ESRV_SHELL_OPTION)
	);

	//-------------------------------------------------------------------------
	// Start an ESRV instance in a child process.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	p->fp_esrv = _popen(
		esrv_command_buffer, 
		"rt"
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	p->fp_esrv = popen(
		esrv_command_buffer, 
		"r"
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	if(p->fp_esrv == NULL) {
		_ERROR("Unable to start ESRV.");
	}

	//-------------------------------------------------------------------------
	// Retrieve the ESRV's instance PID and GUID.
	//-------------------------------------------------------------------------
	do {
		pc = fgets(
			buffer, 
			sizeof(buffer), 
			p->fp_esrv
		);
		if(pc != NULL) {
			switch(++input_line_count) {

				case ENERGY_ESRV_GUID_LINE:

					//---------------------------------------------------------
					// extract ESRV's GUID and save it
					//---------------------------------------------------------
					token = strtok(
						buffer, 
						ENERGY_ESRV_GUID_TOKEN_SEPARATORS
					);
					while(token != NULL) {
						if(strncmp(
							token, 
							ENERGY_ESRV_PRE_GUID_TOKEN, 
							strlen(ENERGY_ESRV_PRE_GUID_TOKEN)
						) == 0) { 
							token = strtok(
								NULL, 
								ENERGY_ESRV_GUID_TOKEN_TERMINATOR
							);
							memset(
								esrv_guid, 
								0, 
								sizeof(esrv_guid)
							);
							strncpy(
								esrv_guid, 
								token, 
								strlen(token)
							);
							f_esrv_guid = 1;
							break;
						}
						token = strtok(
							NULL, 
							ENERGY_ESRV_GUID_TOKEN_SEPARATORS
						);
					}
					break;

				case ENERGY_ESRV_PID_LINE:

					//---------------------------------------------------------
					// extract ESRV's PID and save it.
					//---------------------------------------------------------
					token = strtok(
						buffer, 
						ENERGY_ESRV_PID_TOKEN_SEPARATORS
					);
					while(token != NULL) {
						if(strncmp(
							token, 
							ENERGY_ESRV_PRE_PID_TOKEN, 
							strlen(ENERGY_ESRV_PRE_PID_TOKEN)
						) == 0) { 
							token = strtok(
								NULL, 
								ENERGY_ESRV_PID_TOKEN_TERMINATOR
							);
#ifdef __PL_WINDOWS__
							esrv_pid = (DWORD)atoi(token);
#endif // __Pl_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
							esrv_pid = (pid_t)atoi(token);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
							assert(esrv_pid != 0);
							f_esrv_pid = 1;
							goto pid_found;
						}
						token = strtok(
							NULL, 
							ENERGY_ESRV_GUID_TOKEN_SEPARATORS
						);
					}
					break;

				default:
					break;
			}
		} else {

			//-----------------------------------------------------------------
			// Likely the ESRV launch has failed, let's signal this error.
			//-----------------------------------------------------------------
			_ERROR("ESRV likely failed to start.");
		}
	} while(pc != NULL);

	//-------------------------------------------------------------------------
	// Likely the ESRV launch has failed, let's signal this error.
	//-------------------------------------------------------------------------
	_ERROR("ESRV likely failed to start.");

pid_found:

	//-------------------------------------------------------------------------
	// Check and build the pl_config.ini file to attach to.
	//-------------------------------------------------------------------------
	assert((f_esrv_guid == 1) && (f_esrv_pid == 1));
	memset(
		esrv_config_file_name_buffer, 
		0, 
		sizeof(esrv_config_file_name_buffer)
	);
	memcpy(
		esrv_config_file_name_buffer, 
		ENERGY_ESRV_PL_CONFIG_FILE_ROOT, 
		strlen(ENERGY_ESRV_PL_CONFIG_FILE_ROOT)
	);
	strncat(
		esrv_config_file_name_buffer, 
		ESRV_APPLICATION_NAME, 
		strlen(ESRV_APPLICATION_NAME)
	);
	strncat(
		esrv_config_file_name_buffer, 
		ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE, 
		strlen(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE)
	);
	strncat(
		esrv_config_file_name_buffer, 
		esrv_guid, 
		strlen(esrv_guid)
	);
	memset(
		esrv_pl_path_name, 
		0, 
		sizeof(esrv_pl_path_name)
	);
	strncpy(
		esrv_pl_path_name, 
		esrv_config_file_name_buffer, 
		strlen(esrv_config_file_name_buffer)
	);
	strncat(
		esrv_config_file_name_buffer, 
		ENERGY_ESRV_PL_CONFIG_FILE_NAME, 
		strlen(ENERGY_ESRV_PL_CONFIG_FILE_NAME)
	);

attach_to_esrv:

	//-------------------------------------------------------------------------
	// Attach to the identified instance of ESRV and read settings.
	//-------------------------------------------------------------------------
	p->esrv_pld = pl_attach(esrv_config_file_name_buffer);
	if(p->esrv_pld == PL_INVALID_DESCRIPTOR) {
		_ERROR("Unable to attach to the specified ESRV instance.");
	}

	//-------------------------------------------------------------------------
	// read-in esrv's configuration:
	//  - ESRV Status (running or not)
	//  - ESRV Channel count
	//  - ESRV Version (not used)
	//  - ESRV energy in joule counter's precision
	// Note:
	//    since each channel holds esrv's configuration counters, we read the 
	//    first channel to read the channel count.  ESRV has always at least
	//    one channel, so the read is safe
	// Note:
	//    Channel count is zero count, therefore the --.
	//-------------------------------------------------------------------------
	plret = pl_read(
		p->esrv_pld, 
		&p->channels, 
		ESRV_COUNTER_CHANNELS_INDEX
	);
	if(plret != PL_SUCCESS) {
		_ERROR("Unable to read the ESRV channels count counter.");
	}
	if(p->channel > p->channels) {
		WARNING(
			"The requested channel does not exist in the specified ESRV instance.  Will use default channel (1)."
		);
		p->channel = 1; 
	}
	p->channel--;

	//-------------------------------------------------------------------------
	// Now that the channels count is known, we can read the requested ESRV channel
	//-------------------------------------------------------------------------
	plret = pl_read(
		p->esrv_pld, 
		&p->status, 
		(p->channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_STATUS_INDEX
	);
	if(plret != PL_SUCCESS) {
		_ERROR("Unable to read the ESRV status counter.");
	}
	if(p->status != ESRV_STATUS_RUNNING) {
		_ERROR("The specified ESRV instance doesn't seem to be alive.");
	}
	plret = pl_read(
		p->esrv_pld, 
		&p->version, 
		(p->channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_VERSION_INDEX
	); 
	if(plret != PL_SUCCESS) {
		_ERROR("Unable to read the ESRV version counter.");
	}
	plret = pl_read(
		p->esrv_pld, 
		&value, 
		(p->channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_ENERGY_JOULES_DECIMALS_INDEX
	); 
	if(plret != PL_SUCCESS) {
		_ERROR(
			"Unable to read the ESRV energy in Joule(s) counter's .decimal suffix counter."
		);
	}
	p->energy_data_multiplier = pow(
		10.0, 
		(double)value
	);

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
		_ERROR("Unable to install the signal handler."); 
	}

	//-------------------------------------------------------------------------
	// Read start energy.
	//-------------------------------------------------------------------------
	plret = pl_read(
		p->esrv_pld, 
		&p->start_energy_data, 
		(p->channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_ENERGY_JOULES_INDEX
	);
	if(plret != PL_SUCCESS) {
		_ERROR("Unable to read start energy value.");
	}

	//-------------------------------------------------------------------------
	// Run command.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	p->fp = _popen(
		p->command, 
		"rt"
	);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	p->fp = popen(
		p->command, 
		"r"
	);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	if(p->fp == NULL) {
		_ERROR("Unable to execute command.");
	}

	//-------------------------------------------------------------------------
	// Echo command output to stdout.
	// Note:
	//    With some verbose commands, the extra processing on the output may
	//    consume extra energy (buffer[strlen(buffer) - 1] = '\0';).  Remove
	//    this cosmetic processing if this becomes an issue.
	//-------------------------------------------------------------------------
	while(p->f_interrupted == 0) {
		pc = fgets(
			buffer, 
			sizeof(buffer), 
			p->fp
		);
		if(pc != NULL) {
			buffer[strlen(buffer) - 1] = '\0';
			puts(buffer);
		} else {
			break;
		}
	}

	//-------------------------------------------------------------------------
	// Read end energy and close ESRV PL.
	//-------------------------------------------------------------------------
	plret = pl_read(
		p->esrv_pld, 
		&p->end_energy_data, 
		(p->channel * ESRV_BASE_COUNTERS_COUNT) + ESRV_COUNTER_ENERGY_JOULES_INDEX
	);
	if(plret != PL_SUCCESS) {
		_ERROR("Unable to read end energy value.");
	}
	plret = pl_close(p->esrv_pld);
	if(plret != PL_SUCCESS) {
		_ERROR("Unable to close ESRV instance's PL.");
	}

	//-------------------------------------------------------------------------
	// End command.
	//-------------------------------------------------------------------------
	if(p->f_interrupted == 0) {
		if(feof(p->fp)) {
#ifdef __PL_WINDOWS__
			_pclose(p->fp);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
			pclose(p->fp);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		} else {
			_ERROR("Unable to completely read command's output.");
		}
	}

	//-------------------------------------------------------------------------
	// Compute energy consumed.
	//-------------------------------------------------------------------------
	p->consumed_energy_in_joules = (double)(
			p->end_energy_data - 
			p->start_energy_data
		) / 
		p->energy_data_multiplier
	;
	p->consumed_energy_in_kwhs = 
		p->consumed_energy_in_joules / 
		ONE_KWH_IN_JOULES
	;

	//-------------------------------------------------------------------------
	// Report consumed energy.
	//-------------------------------------------------------------------------
	fprintf(
		stdout, 
		"\nEnergy: [%g] Joule(s) - [%g] kWh(s).\n", 
		p->consumed_energy_in_joules, 
		p->consumed_energy_in_kwhs
	);

	//-------------------------------------------------------------------------
	// close the ESRV instance's process and remove its PL
	//-------------------------------------------------------------------------
	if(
		(f_esrv_guid == 1) && 
		(f_esrv_pid == 1)
	) {
#ifdef __PL_WINDOWS__
		esrv_handle = OpenProcess(
			PROCESS_TERMINATE, 
			FALSE, 
			esrv_pid
		);
		assert(esrv_handle != NULL);
		bret = TerminateProcess(
			esrv_handle, 
			0
		);
		assert(bret != FALSE);

		//---------------------------------------------------------------------
		// reset last ESRV instance's flags and ids 
		//---------------------------------------------------------------------
		esrv_handle = NULL;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		ret = kill(
			esrv_pid, 
			SIGTERM
		); 
		assert(ret != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
		f_esrv_guid = 0;
		f_esrv_pid = 0;
		esrv_pid = 0;

		//---------------------------------------------------------------------
		// close last ESRV instance's output stream
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		_pclose(p->fp_esrv);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		pclose(p->fp_esrv);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Delete ESRV instance's PL.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		pc = _getcwd(
			current_path_name, 
			sizeof(current_path_name)
		); 
		assert(pc != NULL);		
		ret = _chdir(esrv_pl_path_name); 
		assert(ret != -1);
		file = _findfirst(
			"*", 
			&find_files
		);
		do {
			if(
				(
					strcmp(
						find_files.name, 
						"."
					) != 0
				) && 
				(
					strcmp(
						find_files.name, 
						".."
					) != 0
				)
			) {
				ret = -1;
				do { 
					ret = remove(find_files.name); 
				} while(ret == -1);
			}
		} while(
			_findnext(
				file, 
				&find_files
			) == 0);
		ret = _findclose(file); 
		assert(ret != -1);
		ret = _chdir(current_path_name); 
		assert(ret != -1);
		ret = -1;
		do { 
			ret = _rmdir(esrv_pl_path_name); 
		} while(ret == -1);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
		directory = opendir(esrv_pl_path_name);
		assert(directory != NULL);
		file = readdir(directory);
		while(file != NULL) {
			if(
				(
					strcmp(
						file->d_name, 
						"."
					) != 0
				) && 
				(
					strcmp(
						file->d_name, 
						".."
					) != 0
				)
			) {
				memset(
					file_name, 
					0, 
					sizeof(file_name)
				);
				strncat(
					file_name, 
					esrv_pl_path_name, 
					strlen(esrv_pl_path_name)
				);
				strncat(
					file_name, 
					"/", 
					strlen("/")
				);
				strncat(
					file_name, 
					file->d_name, 
					strlen(file->d_name)
				);
				ret = -1;
				do { 
					ret = unlink(file_name); 
				} while(ret != -1);
			}
			file = readdir(directory);
		}
		closedir(directory);
		ret = -1;
		do { 
			ret = rmdir(esrv_pl_path_name); 
		} while(ret != -1);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
	}
done:
	return(PL_SUCCESS);
error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: parser
Purpose : parse user input to set energy data structure
In      : pointer to energy data structure
Out     : updated energy data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
01/28/2010    Jamel Tayeb             Creation.
*/
int parser(PENERGY_DATA p) {

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
	PL_STATUS ret = PL_FAILURE;

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
			if(strncmp(buffer, options[j], strlen(options[j])) == 0) {
				switch(j) {

					//---------------------------------------------------------
					// [-H] option.
					//---------------------------------------------------------
					case H_ID:
					case HELP_ID:
						fprintf(
							stdout, 
							HELP_STRING, 
							ENERGY_APPLICATION_NAME, 
							ENERGY_APPLICATION_NAME, 
							ENERGY_APPLICATION_NAME,
							ENERGY_ESRV_DEFAULT_GUID_SHELL_VARIABLE,
							ENERGY_APPLICATION_NAME, 
							ENERGY_APPLICATION_NAME, 
							ENERGY_APPLICATION_NAME
						);
						p->f_help = 1;
						goto parser_done;
						break;

					//---------------------------------------------------------
					// [-V] option.
					//---------------------------------------------------------
					case V_ID:
					case VERSION_ID:
						p->f_version = 1;
						fprintf(
							stdout, 
							"%s: version %s.%s.%s\n", 
							ENERGY_APPLICATION_NAME, 
							ENERGY_VERSION_MAJOR, 
							ENERGY_VERSION_MINOR, 
							ENERGY_VERSION_REVISION
						);
						fprintf(
							stdout, 
							"Using PL helper version %s.%s.%s\n", 
							PL_HELPER_VERSION_MAJOR, 
							PL_HELPER_VERSION_MINOR, 
							PL_HELPER_VERSION_REVISION
						);
						fprintf(
							stdout, 
							"Using PL version %s.%s.%s(%s)", 
							PL_VERSION_MAJOR, 
							PL_VERSION_MINOR, 
							PL_VERSION_REVISION, 
							PL_VERSION_OS
						);
						fprintf(stdout, "\n");
						goto parser_done;
						break;

					//---------------------------------------------------------
					// [-G <string>] option.
					//---------------------------------------------------------
					case G_ID:
					case GUID_ID:
						if(i + 1 >= p->argc) {
							ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						p->f_guid = 1;
						i++;
						p->esrv_guid = p->argv[i];
						ret = plh_filter_uuid_string(p->esrv_guid);
						if(ret == PL_FAILURE) {
							memset(buffer, 0, sizeof(buffer));
							sprintf(
								buffer, 
								"Guid [%s] does not seem to be a valig guid.", 
								p->esrv_guid
							);
							_ERROR(buffer);
						}
						goto parser_skip;
						break;

					//---------------------------------------------------------
					// [-X <string>] option.
					//---------------------------------------------------------
					case X_ID:
					case GUID_SHELL_VARIABLE_ID:
						if(i + 1 >= p->argc) {
							ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						p->f_guid_shell_variable = 1;
						i++;
						p->esrv_guid_shell_variable = p->argv[i];
						p->esrv_guid_shell_variable_value = getenv(p->esrv_guid_shell_variable); 
						if(p->esrv_guid_shell_variable_value == NULL) {
							memset(buffer, 0, sizeof(buffer));
							sprintf(
								buffer, 
								"Environment variable [%s] does not exist.", 
								p->esrv_guid_shell_variable
							);
							_ERROR(buffer);
						} else {
							ret = plh_filter_uuid_string(p->esrv_guid_shell_variable_value);
							if(ret == PL_FAILURE) {
								memset(buffer, 0, sizeof(buffer));
								sprintf(
									buffer, 
									"Environment variable [%s] value [%s] does not seem to be a valig guid.", 
									p->esrv_guid_shell_variable,
									p->esrv_guid_shell_variable_value
								);
								_ERROR(buffer);
							}
						}
						goto parser_skip;
						break;

					//---------------------------------------------------------
					// [-N <integer>] option.
					//---------------------------------------------------------
					case N_ID:
					case CHANNEL_ID:
						if(i + 1 >= p->argc) {
							ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						i++;
						p->channel = (unsigned int)atoi(p->argv[i]);
						if(value == 0) {
							value = ENERGY_DEFAULT_CHANNEL;
						}
						p->f_channel = 1;
						goto parser_skip;
						break;

					//---------------------------------------------------------
					// [-E <string>] option.
					//---------------------------------------------------------
					case E_ID:
					case ESRV_OPTIONS_ID:
						if(i + 1 >= p->argc) {
							ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						p->f_esrv_options = 1;
						i++;
						p->esrv_options = p->argv[i];
						goto parser_skip;
						break;

					//---------------------------------------------------------
					// -- separator id.
					//---------------------------------------------------------
					case SEPARATOR_ID:
						if(i + 1 >= p->argc) {
							ERROR_INDEX(
								"Missing argument after token [%s] in position [%d].", 
								p->argv[i], 
								i + 1
							);
						}
						i++;
						memset(p->command, 0, sizeof(p->command));
						strncpy(p->command, p->argv[i], strlen(p->argv[i]));
						while(++i < p->argc) {
							strncat(p->command, " ", strlen(" "));
							strncat(p->command, p->argv[i], strlen(p->argv[i]));
						}
						p->f_command = 1;
						goto parser_done;
						break;

					//---------------------------------------------------------
					// Unknown option.
					//---------------------------------------------------------
					default:
						ERROR_INDEX(
							"Unable to make sense of token [%s] in position [%d].", 
							buffer, 
							j
						);
				}
			}
		} // for j
		_ERROR("Unable to make sense of options.  Use --help option for help.");
		goto error;
parser_skip:
		;
	} // for i
parser_done:

	//-------------------------------------------------------------------------
	// Return status.
	//-------------------------------------------------------------------------
	return(PL_SUCCESS);
error:
	return(PL_FAILURE);
}

/*-----------------------------------------------------------------------------
Function: signal_handler
Purpose : analyzer interrupt signal handler
In      : signal
Out     : interrupt flag in energy data structure
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

	switch(c) {

		//---------------------------------------------------------------------
		// Interrupt program.
		//---------------------------------------------------------------------
#ifdef __PL_WINDOWS__
		case CTRL_C_EVENT: 
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		case SIGINT:
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

		//---------------------------------------------------------------------
		// Read end energy, compute consumed energy and report result.
		//---------------------------------------------------------------------
		energy_data.f_interrupted = 1;

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
