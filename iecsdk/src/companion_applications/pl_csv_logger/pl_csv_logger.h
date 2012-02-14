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

#ifndef __INCLUDE_PL_CSV_LOGGER__
#define __INCLUDE_PL_CSV_LOGGER__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	#include <windows.h>
	#include <tchar.h>
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_MACOSX__)
	extern char *ctime_r(const time_t *timep, char *buf);
#endif // __PL_LINUX__ || __PL_MACOSX__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define ALLOWED_TIME_MARGIN_IN_MS 10 // 10ms out of 1s is 1% error
#define PL_CSV_CONFIG_MIN_PL_INIS 0
#define PL_CSV_CONFIG_MAX_PL_INIS 0
#define PL_CSV_LOGGER_MAX_PLS 1024
#define PL_CSV_LOGGER_LOG_ENTRY_SIZE 9192
#define PL_CSV_LOGGER_SAMPLE_HEADER "\"Sample #\"\n"
#define PL_CSV_LOGGER_SAMPLE_FAIL "FAIL"
#define PL_CSV_LOGGER_LOG_FILE_ACCESS_MODE "w+"
#define PL_CSV_LOGGER_TIME_STAMP_OFFSET 24
#define PL_CSV_LOGGER_TIME_STAMP_END_OFFSET 26
#define PL_CSV_LOGGER_CVT_BUFFER_SIZE PL_MAX_BUFFER_SIZE
#define PL_CSV_LOGGER_TIME_BUFFER_SIZE 27
#define PL_CSV_LOGGER_COUNTER_DECIMALS_SUFFIX ".decimals"
#define PL_CSV_LOGGER_COUNTER_OFFSET_SUFFIX ".offset"
#define PL_CSV_LOGGER_COUNTER_SCALAR_SUFFIX ".scalar"
#define PL_CSV_LOGGER_COUNTER_SCALAR_DECIMALS_SUFFIX ".scalar.decimals"
#define PL_CSV_LOGGER_COUNTER_SIGN_SUFFIX ".sign"
#define PL_CSV_LOGGER_COUNTER_OFFSET_DECIMALS_SUFFIX ".offset.decimals"
#define PL_CSV_LOGGER_COUNTER_OFFSET_SIGN_SUFFIX ".offset.sign"
#define PL_CSV_LOGGER_DEFAULT_PAUSE 1 // 1 second
#define PL_CSV_LOGGER_PL_FOLDER "productivity_link"
#define PL_CSV_LOGGER_PL_CONFIG_FILE_NAME "pl_config.ini"
#define PL_CSV_LOGGER_QUOTES "\""
#ifdef __PL_WINDOWS__
	#define PL_CSV_LOGGER_FP_FORMAT "%+.*f"
	#define PL_CSV_LOGGER_LOG_SEPARATOR ", "
	#define PL_CSV_LOGGER_TIME_STAMP_HEADER "\"Time Stamp\"" ## PL_CSV_LOGGER_LOG_SEPARATOR
	#define PL_CSV_LOGGER_PROCESSING_DATA_MARKER "*" ## PL_CSV_LOGGER_LOG_SEPARATOR
	#define PL_CSV_LOGGER_BUFFER_SIZE PL_MAX_PATH
	#define PL_CSV_LOGGER_FORMAT "%I64u"
	#define PL_CSV_LOGGER_SAMPLE_FORMAT "%I64u\n"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#define PL_CSV_LOGGER_FP_FORMAT "%+.*Lf"
	#define PL_CSV_LOGGER_LOG_SEPARATOR ", "
	#define PL_CSV_LOGGER_TIME_STAMP_HEADER "\"Time Stamp\", "
	#define PL_CSV_LOGGER_PROCESSING_DATA_MARKER "*, "
	#define PL_CSV_LOGGER_FORMAT "%llu"
	#define PL_CSV_LOGGER_SAMPLE_FORMAT "%llu\n"
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// version defines
//-----------------------------------------------------------------------------
#define PL_CSV_LOGGER_NAME "pl_csv_logger"
#define PL_CSV_LOGGER_VERSION_MAJOR "2009" // year
#define PL_CSV_LOGGER_VERSION_MINOR "06" // month
#define PL_CSV_LOGGER_VERSION_REVISION "03" // day

//-----------------------------------------------------------------------------
// structures and enums
//-----------------------------------------------------------------------------
typedef struct _pl_csv_logger_counter_data {

	int processed;
	char name[PL_MAX_PATH];
	unsigned int i_decimals;
	unsigned int i_offset;
	unsigned int i_offset_decimals;
	unsigned int i_offset_sign;
	unsigned int i_scalar;
	unsigned int i_scalar_decimals;
	unsigned int i_sign;

} PL_CSV_LOGGER_COUNTER_DATA, *PPL_CSV_LOGGER_COUNTER_DATA;

typedef enum _pl_csv_processing_codes {

	PROCESSING_DATA = -1,
	NO_PROCESSING = 0,
	DECIMALS_PROCESSING = 2,
	OFFSET_PROCESSING = 4,
	OFFSET_DECIMALS_PROCESSING = 8,
	SCALAR_PROCESSING = 16,
	SIGN_PROCESSING = 32,
	OFFSET_SIGN_PROCESSING = 64,
	SCALAR_DECIMALS_PROCESSING = 128

} PL_CSV_PROCESSING_CODES;

//-----------------------------------------------------------------------------
// cli options
//-----------------------------------------------------------------------------
#define PL_CSV_LOGGER_CLI_MAX_TOKENS 5

#define PL_CSV_LOGGER_PROCESS "--PROCESS"
#define PL_CSV_LOGGER_TIME "--T"
#define PL_CSV_LOGGER_OUTPUT "--OUTPUT"
#define PL_CSV_LOGGER_CLI_HELP "--HELP"
#define PL_CSV_LOGGER_VERSION "--VERSION"

typedef enum _pl_csv_logger_cli_token_id {
	PL_CSV_LOGGER_PROCESS_TOKEN_ID = 0,
	PL_CSV_LOGGER_TIME_TOKEN_ID,
	PL_CSV_LOGGER_OUTPUT_TOKEN_ID,
	PL_CSV_LOGGER_CLI_HELP_TOKEN_ID,
	PL_CSV_LOGGER_VERSION_TOKEN_ID
} PL_CSV_LOGGER_CLI_TOKEN_ID;

//-----------------------------------------------------------------------------
// Response to invalid syntax and startup banner
//-----------------------------------------------------------------------------
#define PL_CSV_LOGGER_HELP_MESSAGE_LINES_COUNT 20
#define PL_CSV_LOGGER_HELP_MESSAGE_LINES \
	"\n", \
	"Start PL CSV logger and output data in comma-separated variable format that can\n", \
	"be loaded into spreadsheets or other analysis tools.\n", \
	"\n", \
	"Usage:  pl_csv_logger [[PL_ini] ... ] [--t <n>] [--output <filename>] [--process]\n", \
	"Or      pl_csv_logger [--version]\n", \
	"Or      pl_csv_logger [--help]\n", \
	"\n", \
	"   [PL_ini] is one or more fully qualified path(s) to PL configuration file(s).\n", \
	"   --t with [n] sets the pause time between each log entry creation.\n", \
	"      n is expressed in seconds.  n is equal to 1 by default.\n", \
	"   --output with [filename] writes output to the named file rather than stdout.\n", \
	"   --process forces additional analysis on counter values with prescribed suffixes.\n", \
	"      Use pl_csv_logger --process --help for more information on the suffixes.\n", \
	"   --version prints version information.\n", \
	"   --help prints this help message.\n", \
	"\n", \
	"The logger application continues to append data to the file once per second (or\n", \
	"whatever time interval is selected with the --t option).\n", \
	"\n"

#define PL_CSV_LOGGER_SUFFIXES_HELP_MESSAGE_LINES_COUNT 119
#define PL_CSV_LOGGER_SUFFIXES_HELP_MESSAGE_LINES \
	"\n", \
	"Additional help information on the counter suffixes supported by the CSV logger.\n", \
	"\n", \
	"   The following suffixes are recognized by csv logger when the --process\n", \
	"   parameter is supplied:\n", \
	"\n", \
	"      .decimals (defaults to 0 if suffix counter doesn't exist)\n", \
	"      .scalar (defaults to 1 if suffix counter doesn't exist)\n", \
	"      .scalar.decimals (defaults to 0 if suffix counter doesn’t exist)\n", \
	"      .sign (defaults to 0 if suffix counter doesn't exist)\n", \
	"      .offset (defaults to 0 if suffix counter doesn't exist)\n", \
	"      .offset.decimals (defaults to 0 if suffix counter doesn't exist)\n", \
	"      .offset.sign (defaults to 0 if suffix counter doesn't exist)\n", \
	"\n", \
	"   The following formula is used to compute a \"total\" counters' real values:\n", \
	"\n", \
	"      real_total = total\n", \
	"                 / (10 ^ total.decimals)\n", \
	"                 * total.scalar\n", \
	"                 / (10 ^ total.scalar.decimals)\n", \
	"                 * (total.sign ? -1 : 1)\n", \
	"                 + total.offset\n", \
	"                 / (10 ^ total.offset.decimals)\n", \
	"                 * (total.offset.sign ? -1 : 1)\n", \
	"      ;\n", \
	"\n", \
	"Sign Suffix\n", \
	"-----------\n", \
	"      For maximum portability across different architectures,\n", \
	"   the Intel EC SDK always uses positive values for its counters,\n", \
	"   but negative values can easily be represented with PL counters\n", \
	"   and interpreted by other applications if the following\n", \
	"   convention is adhered to:\n", \
	"      1.  Add a supplemental counter with a \".sign\" suffix\n", \
	"      2.  Write the static sign to the supplemental counter\n", \
	"          using the following convention: \n", \
	"              1 means a negative number.\n", \
	"              0 means a positive number (or zero).\n", \
	"   If the sign suffix is omitted, the number is assumed to be\n", \
	"   positive.\n", \
	"\n", \
	"Decimals Suffix\n", \
	"---------------\n", \
	"      The Intel EC SDK always uses unsigned long long values for its counters,\n", \
	"   but floating point values with a fixed number of decimal places can\n", \
	"   easily be represented with PL counters and interpreted by other\n", \
	"   applications if the following convention is adhered to:\n", \
	"      1.  Add a supplemental counter with a \".decimals\" suffix\n", \
	"      2.  Write the static number of decimal places to the supplemental\n", \
	"          counter\n", \
	"      3.  Adjust counters by 10 ^ n before writing to PL\n", \
	"\n", \
	"   For example, the ESRV utility makes use of this with its\n", \
	"   \"Energy (kWh)\" counter.  To represent the value to two decimal\n", \
	"   places, the actual number of kiloWatt-hours is multiplied by 100 and\n", \
	"   stored as an unsigned long long.  In addition, at program startup,\n", \
	"   ESRV writes a value of 2 to the \"Energy (kWh).decimals\" counter to\n", \
	"   indicate that \"Energy (kWh)\" should be interpreted as having two\n", \
	"   decimal places.\n", \
	"\n", \
	"   All applications writing counters representing fixed decimal numbers\n", \
	"   should use the .decimals suffix on a supplemental static counter as\n", \
	"   appropriate.  The number of decimal places should not be changed\n", \
	"   after it is written.\n", \
	"\n", \
	"Offset Suffix\n", \
	"-------------\n", \
	"      In some cases, the native source of a counter may represent a\n", \
	"   differential value from some fixed offset value.  Rather than\n", \
	"   constantly adding the differential value to the offset value each\n", \
	"   time the counter is written out, an application developer could\n", \
	"   elect to define a static offset counter and let any consumers of the\n", \
	"   PL data add in the offset where needed.  To do this, the following\n", \
	"   convention has been established:\n", \
	"      1.  Add a supplemental counter with a \".offset\" suffix\n", \
	"      2.  Write the static value of the offset to the supplemental\n", \
	"          counter\n", \
	"   For example, if an application is counting the number of visitors\n", \
	"   over 5000 to a theme park, a \"Visitor Total\" value of 800 might\n", \
	"   represent a total attendance of 5800 visitors.  By adding a\n", \
	"   \"Visitor Total.offset\" counter and writing a value of 5000 to that\n", \
	"   offset counter, the application developer can indicate what number\n", \
	"   to add to the counter value to get the real value.\n", \
	"      The Offset suffix may have additional suffixes.  Currently, the\n", \
	"   .sign and .decimal suffixes are supported by this logger.\n", \
	"\n", \
	"Scalar Suffix\n", \
	"-------------\n", \
	"      In most cases, the decimals suffix provides sufficient ability\n", \
	"   to scale the way numbers are reported out.  However, there are some\n", \
	"   cases where the counter values written through PL need some sort of\n", \
	"   scaling factor applied to them.  In such cases, the following\n", \
	"   convention should be used:\n", \
	"      1.  Add a supplemental counter with a \".scalar\" suffix\n", \
	"      2.  Write the static value of the scaling factor to the\n", \
	"          supplemental counter\n", \
	"   For example, software for an egg producer could report how many\n", \
	"   dozens of eggs were produced with an \"Egg Dozens\" counter.\n", \
	"   That same value could be written to an \"Eggs\" counter, provided\n", \
	"   that \"Eggs.scalar\" had been set up with a value of twelve.\n", \
	"   When units are measured by the thousands or millions, using a\n", \
	"   scalar factor of 1000 or 1,000,000 as appropriate will represent\n", \
	"   the proper scale of the units.\n", \
	"\n", \
	"   The scalar suffix also supports the .decimals suffix (i.e.,\n", \
	"   .scalar.decimals) to allow scalar values to represent values\n", \
	"   Other than integers.\n", \
	"\n", \
	"\n", \
	"NOTE\n", \
	"    The static counters can be used in a compound manner.\n", \
	"    For example, consider the following:\n", \
	"       MyTotal counter has a value of 5\n", \
	"       MyTotal.decimals has a value of 1\n", \
	"       MyTotal.scalar has a value of 72\n", \
	"\n", \
	"   In this example, the actual value is 36:\n", \
	"       5 / (10 ^ 1) * 72 = 36\n", \
	"\n"

#define PL_CSV_LOGGER_STARTUP_MESSAGE_LINES_COUNT 9
#define PL_CSV_LOGGER_STARTUP_MESSAGE_LINES \
	"\n", \
	"  @@@@   @@@@  @    @        @       @@@@   @@@@   @@@@  @@@@@@ @@@@@\n", \
	" @    @ @    @ @    @        @      @    @ @    @ @    @ @      @    @\n", \
	" @      @      @    @        @      @    @ @      @      @      @    @\n", \
	" @       @@@@  @    @        @      @    @ @      @      @@@@@@ @@@@@\n", \
	" @           @  @   @        @      @    @ @  @@@ @  @@@ @      @  @\n", \
	" @    @      @   @ @         @      @    @ @    @ @    @ @      @   @\n", \
	"  @@@@  @@@@@     @          @@@@@@  @@@@   @@@@   @@@@  @@@@@@ @    @\n", \
	"\n"

//-----------------------------------------------------------------------------
// error messages
//-----------------------------------------------------------------------------
#define PL_CSV_LOGGER_ERROR_SUSPICIOUS_PL_INI "Suspicious PL ini file - check PL ini file or use esrv --help for help."
#define PL_CSV_LOGGER_ERROR_INVALID_PARAMETERS "Invalid parameters - use --help for help."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_SET_SIGNAL_HANDLER "Unable to setup signal handler."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_READ_PL_INI_DATA "Unable to Read PL configuration data."
#define PL_CSV_LOGGER_ERROR_MALLOC_FAIL "Not enough memory - you may try to close other applications."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_CREATE_LOG_FILE "Unable to create the log file."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_CLOSE_LOG_FILE "Unable to close the log file."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_WRITE_LOG_FILE_HEADER "Unable to write the log file header."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_WRITE_LOG_ENTRY "Unable to write log entry."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_ATTACH_TO_PL "Unable to attach to PL."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_CLOSE_PL "Unable to close PL."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_READ_PL "Unable to read PL."
#define PL_CSV_LOGGER_ERROR_UNABLE_TO_READ_SYSTEM_TIME "Unable to read system time."

//-----------------------------------------------------------------------------
// macros
// Note:
//    this macros expects the following variables to exist in the scope:
//       char *log_header;
//       char *tmp_log_header;
//       size_t log_header_size;
//       size_t length;
//       size_t memory_size;
//-----------------------------------------------------------------------------
#define PL_CSV_LOGGER_LOG_HEADER_APPEND(s) \
	assert((s) != NULL); \
	length = strlen((s)) + 1; \
	new_memory_size = memory_size + (sizeof(char) * length); \
	tmp_log_header = (char *)realloc( \
		log_header, \
		new_memory_size \
	); \
	if(tmp_log_header == NULL) { \
		pl_csv_logger_error( \
			PL_CSV_LOGGER_ERROR_MALLOC_FAIL \
		); \
	} \
	log_header = tmp_log_header; \
	tmp_log_header = NULL; \
	memset( \
		log_header + memory_size, \
		0, \
		length \
	); \
	memory_size = new_memory_size; \
	strncat( \
		log_header, \
		(s), \
		length \
	);

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
extern void pl_csv_logger_debug(char *);
extern int pl_csv_logger_cli_parser(int, char *[]);
extern void pl_csv_logger_info(char *, char *);
extern void pl_csv_logger_info_int(char *, int);
extern void pl_csv_logger_error(char *);
#ifdef __PL_WINDOWS__
	extern BOOL signal_handler(DWORD);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	extern void signal_handler();
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PL_CSV_LOGGER__
