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

#ifndef __INCLUDE_ENERGY__
#define __INCLUDE_ENERGY__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
//#include "esrv.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// version defines
//-----------------------------------------------------------------------------
#define ENERGY_APPLICATION_NAME "energy"
#define ENERGY_VERSION_MAJOR "2010" // year
#define ENERGY_VERSION_MINOR "04" // month
#define ENERGY_VERSION_REVISION "01" // day

//-----------------------------------------------------------------------------
// ESRV pid and uuid retrieval
//-----------------------------------------------------------------------------
#define ENERGY_INPUT_LINE_MAX_SIZE 4096
#define ENERGY_ESRV_GUID_LINE 9
#define ENERGY_ESRV_PID_LINE 10
#define ENERGY_GUID_LENGHT_IN_CHARACTERS 36
#define ENERGY_ESRV_PRE_GUID_TOKEN "Using Guid:     "
#define ENERGY_ESRV_GUID_TOKEN_SEPARATORS "\n["
#define ENERGY_ESRV_GUID_TOKEN_TERMINATOR "]"
#define ENERGY_ESRV_PRE_PID_TOKEN "PID:            "
#define ENERGY_ESRV_PID_TOKEN_SEPARATORS "\n["
#define ENERGY_ESRV_PID_TOKEN_TERMINATOR "]"

//-----------------------------------------------------------------------------
// ESRV shell variables
//-----------------------------------------------------------------------------
#define ENERGY_ESRV_DEFAULT_GUID_SHELL_VARIABLE "ESRV_GUID"

//-----------------------------------------------------------------------------
// ESRV instance handling
//-----------------------------------------------------------------------------
#define ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE "_"
#ifdef __PL_WINDOWS__
	#define ENERGY_ESRV_PL_CONFIG_FILE_NAME "\\pl_config.ini"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#define ENERGY_ESRV_PL_CONFIG_FILE_NAME "/pl_config.ini"
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#define ENERGY_ESRV_PL_CONFIG_FILE_APPLICATION_NAME "esrv_"
#define ENERGY_ESRV_BINARY_NAME "esrv --start "
#define ENERGY_ESRV_SHELL_OPTION " --shell"
#ifdef __PL_WINDOWS__
	#define ENERGY_ESRV_PL_CONFIG_FILE_ROOT "C:\\productivity_link\\"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#define ENERGY_ESRV_PL_CONFIG_FILE_ROOT "/opt/productivity_link/"
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#if defined (_DEBUG) || (__PL_DEBUG__)
	#ifdef __PL_WINDOWS__
		#define ENERGY_ESRV_DEFAULT_OPTIONS "--library esrv_simulated_device.dll"
	#endif // __PL_WINDOWS__
	#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
		#define ENERGY_ESRV_DEFAULT_OPTIONS "--library esrv_simulated_device.so"
	#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#else // _DEBUG || __PL_DEBUG__
	#define ENERGY_ESRV_DEFAULT_OPTIONS "--device y210 --device_options \"items=all\""
#endif // _DEBUG || __PL_DEBUG__

//-----------------------------------------------------------------------------
// general definitions
//-----------------------------------------------------------------------------
#define ONE_KWH_IN_JOULES 3600000
#define ENERGY_DEFAULT_CHANNEL 1
#define OPTION_STRINGS_COUNT 13
#define OPTION_STRINGS \
	"-X", \
	"-G", \
	"-N", \
	"-E", \
	"-V", \
	"-H", \
	"--GUID_SHELL_VARIABLE", \
	"--GUID", \
	"--CHANNEL", \
	"--ESRV_OPTIONS", \
	"--VERSION", \
	"--HELP", \
	"--"
//-----------------------------------------------------------------------------
#define HELP_STRING \
"\n \
%s give the energy usage for a simple command.\n\n \
Use: %s [options] -- command [arguments...]\n\n \
[--guid <string>]:\n \
   Read energy data from esrv instance identified by the <string> guid.\n \
[--guid_shell_variable <string>]:\n \
   Read energy data from esrv instance identified by the guid stored in\n \
   <string> shell variable.\n \
[--channel <integer>]:\n \
   Use esrv channel <integer>.  By default, channel 1 is used.\n \
[--esrv_options <string>]:\n \
   Start an esrv instance with <string> options to read energy data from.\n \
   By default, the options used are: --device y210 and esrv default settings.\n \
   Use esrv --help for details on esrv defaults.\n \
[--version]:\n \
   Print version info and exit successfully.\n \
[--help]:\n \
   Print this help message and exit successfully.\n \
\n \
Notes:\n \
   -  Energy is given in Joule and kWh -- 1 kWh equals 3,600,000 Joules.\n \
   -  If neither --guid nor --guid_shell_variable options are used, then %s\n \
   starts an instance of esrv.  This instance is terminated and its PL is\n \
   suppressed at\n \
   the end of the command execution.  Starting an esrv instance may add some\n \
   execution time at startup.\n \
   However, if a shell variable named %s and has a well-fomed guid, then it\n \
   will be used as the default esrv identifier.\n \
   -  Esrv and support library -- if applicable -- must be in the search path\n \
   or in the execution folder.  This also includes the library path under\n \
   non-Windows* OSes.\n \
   -  User can interrupt the measurement by typing <CTRL>+<C>.  The command\n \
   will be ended when the next output will be printed.\n \
   -  Options --guid, --guid_shell_variable and --config are mutually\n \
   exclusive.\n \
\n \
   * Third-party trademarks are the property of their respective owners.\n \
\n \
Examples:\n \
   %s -- dir c:\\ /s\n \
   %s --guid 4d3e6616-d71c-4b12-8e2a-bee7e3cde0e2 -- dir c:\\ /s\n \
   %s --guid_shell_variable ESRV_GUID -- dir c:\\ /s\n \
\n"

//-----------------------------------------------------------------------------
// enums and structures definition
//-----------------------------------------------------------------------------
typedef enum _option_ids {

	X_ID = 0,
	G_ID,
	N_ID,
	E_ID,
	V_ID,
	H_ID,

	GUID_SHELL_VARIABLE_ID,
	GUID_ID,
	CHANNEL_ID,
	ESRV_OPTIONS_ID,
	VERSION_ID,
	HELP_ID,
	SEPARATOR_ID

} OPTION_IDS, *POPTION_IDS;

typedef struct _energy_data {

	//-------------------------------------------------------------------------
	// Parser data.
	//-------------------------------------------------------------------------
	int argc;
	char **argv;

	int f_interrupted;
	int f_guid;
	int f_guid_shell_variable;
	int f_channel;
	int f_esrv_options;
	int f_version;
	int f_help;
	int f_command;

	//--------------------------------------------------------------------------
	// Data to manage ESRV instance.
	//--------------------------------------------------------------------------
	FILE *fp_esrv;

	//--------------------------------------------------------------------------
	// Data to manage ESRV PL.
	//--------------------------------------------------------------------------
	char *esrv_guid;
	char *esrv_guid_shell_variable;
	char *esrv_guid_shell_variable_value;
	char *esrv_options;

	//--------------------------------------------------------------------------
	// Data to manage the attached ESRV.
	//--------------------------------------------------------------------------
	unsigned int channel;
	unsigned long long channels;
	unsigned long long status;
	unsigned long long version;

	//-------------------------------------------------------------------------
	// Energy sampling data.
	//-------------------------------------------------------------------------
	int esrv_pld;
	unsigned long long start_energy_data;
	unsigned long long end_energy_data;
	double consumed_energy_in_joules;
	double consumed_energy_in_kwhs;
	double energy_data_multiplier;
	unsigned long long esrv_status;

	//-------------------------------------------------------------------------
	// Data to manage command.
	//-------------------------------------------------------------------------
	char command[PL_MAX_PATH];
	FILE *fp;

} ENERGY_DATA, *PENERGY_DATA;

//-----------------------------------------------------------------------------
// macros
//-----------------------------------------------------------------------------
#define _ERROR(s) \
	fprintf(stderr, "Error: %s [%d]\n", s, __LINE__); \
	goto error;

#define ERROR_INDEX(s, t, i) \
	memset(buffer, 0, sizeof(buffer)); \
	sprintf(buffer, s, (t), (i)); \
	fprintf(stderr, "Error: %s [%d]\n", buffer, __LINE__); \
	goto error;

#define WARNING(s) \
	fprintf(stdout, "Warning: %s [%d]\n", s, __LINE__);

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
extern int main(int argc, char *argv[], char *envp[]);
extern int parser(PENERGY_DATA);
#ifdef __PL_WINDOWS__
BOOL signal_handler(DWORD);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
void signal_handler(int);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_ENERGY__
