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

#ifndef __INCLUDE_PL2GANGLIA__
#define __INCLUDE_PL2GANGLIA__

//-----------------------------------------------------------------------------
// Headers inclusions.
//-----------------------------------------------------------------------------
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#include "ganglia.h"
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#include "productivity_link.h"

//-----------------------------------------------------------------------------
// Dersion defines.
//-----------------------------------------------------------------------------
#define PL2GANGLIA_VERSION_MAJOR "2010" // year
#define PL2GANGLIA_VERSION_MINOR "04" // month
#define PL2GANGLIA_VERSION_REVISION "30" // day
#define PL2GANGLIA_NAME "pl2ganglia"
#define PL2GANGLIA_PL_FOLDER "productivity_link"
#define PL2GANGLIA_PL_CONFIG_FILE_NAME "pl_config.ini"
#define PL2GANGLIA_DECORATED_COUNTER_NAME_SEPARATOR "_"

#define PL2GANGLIA_COUNTER_DECIMALS_SUFFIX ".decimals"
#define PL2GANGLIA_COUNTER_OFFSET_SUFFIX ".offset"
#define PL2GANGLIA_COUNTER_SCALAR_SUFFIX ".scalar"
#define PL2GANGLIA_COUNTER_SCALAR_DECIMALS_SUFFIX ".scalar.decimals"
#define PL2GANGLIA_COUNTER_SIGN_SUFFIX ".sign"
#define PL2GANGLIA_COUNTER_OFFSET_DECIMALS_SUFFIX ".offset.decimals"
#define PL2GANGLIA_COUNTER_OFFSET_SIGN_SUFFIX ".offset.sign"

#define PL2GANGLIA_BUILD_PL_CONFIG_FILE_UNDERSCORE "_"
#ifdef __PL_WINDOWS__
	#define PL2GANGLIA_BUILD_PL_CONFIG_FILE_ROOT "C:\\productivity_link\\"
	#define PL2GANGLIA_BUILD_PL_CONFIG_FILE_NAME "\\pl_config.ini"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#define PL2GANGLIA_BUILD_PL_CONFIG_FILE_ROOT "/opt/productivity_link/"
	#define PL2GANGLIA_BUILD_PL_CONFIG_FILE_NAME "/pl_config.ini"
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// Filtering related definitions.
// Note:
//    The forbidden characters and their substitution characters must be
//    provided in the same number and same order.  The last two characters are
//    examples only, since they are also forbidden in PL counter names.
// Note:
//    The counters name filtering also clips the lenght of the counter name
//    to PL2GANFLIA_COUNTER_MAX_LENGTH. The last charcater is set to NULL.
//-----------------------------------------------------------------------------
#define PL2GANFLIA_COUNTER_MAX_LENGTH PL_MAX_PATH
#define PL2GANFLIA_COUNTER_FOBIDDEN_CHARS_COUNT 5
#define PL2GANFLIA_COUNTER_FOBIDDEN_CHARS \
	' ', \
	'[', \
	']', \
	'(', \
	')'

#define PL2GANFLIA_COUNTER_ALLOWED_CHARS \
	'_', \
	'_', \
	'_', \
	'_', \
	'_'

//-----------------------------------------------------------------------------
// Timing defines.
//-----------------------------------------------------------------------------
#define P2GANGLIA_MIN_PAUSE_INTERVAL_IN_S 1
#define P2GANGLIA_MAX_PAUSE_INTERVAL_IN_S 3600
#define PL2GANGLIA_DEFAULT_UPDATE_INTERVAL_IN_MS 60000 // 1 minute
#define PL2GANGLIA_ALLOWED_TIME_MARGIN_IN_MS 10 // 1% of 1s interval
#ifdef __PL_WINDOWS__
	#define PL2GANGLIA_BOOST_PRIORITY THREAD_PRIORITY_TIME_CRITICAL
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PL2GANGLIA_BOOST_PRIORITY 1
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#define P2GANGLIA_TIME_STAMP_BUFFER_SIZE 26
#define P2GANGLIA_TIME_STAMP_BEGIN "["
#define P2GANGLIA_TIME_STAMP_END "]-"

//-----------------------------------------------------------------------------
// Ganglia defines.
// * Third-party trademarks are the property of their respective owners.
//-----------------------------------------------------------------------------
#define PL2GANGLIA_GANGLIA_VERSION "3.1.7"
#ifdef __PL_WINDOWS__
	#define PL2GANGLIA_ULL_GANGLIA_COMMAND_STRING \
		"gmetric -n \"%s\" -v %I64u -t ull"
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PL2GANGLIA_ULL_GANGLIA_COMMAND_STRING \
		"gmetric -n \"%s\" -v %llu -t ull"
	#define PL2GANGLIA_ULL_FORMAT_STRING "%llu"
	#define PL2GANGLIA_UINT_FORMAT_STRING "%du"
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
#define PL2GANGLIA_DOUBLE_GANGLIA_COMMAND_STRING \
	"gmetric -n \"%s\" -v %.16Lg -t double"
#define PL2GANGLIA_UINT_GANGLIA_COMMAND_STRING \
	"gmetric -n \"%s\" -v %d -t uint32"
#define PL2GANGLIA_DOUBLE_FORMAT_STRING "%.16Lg"
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	#define PL2GANGLIA_DEFAULT_GMOND_CONFIG_FILE "/etc/ganglia/gmond.conf"
	#define PL2GANGLIA_ULL_TYPE_STRING "ull"
	#define PL2GANGLIA_DOUBLE_TYPE_STRING "double"
	#define PL2GANGLIA_UINT_TYPE_STRING "uint32"
	#define PL2GANGLIA_UNIT_STRING "No Unit"
	#define PL2GANGLIA_SLOPE_BOTH_INT GANGLIA_SLOPE_BOTH
	#define PL2GANGLIA_DMAX_INT 0
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// Sentinel values defines
//-----------------------------------------------------------------------------
#define PL2GANGLIA_UINT_OVERFLOW_VALUE (0xffffffff)
#define PL2GANGLIA_DOUBLE_OVERFLOW_VALUE (1.7976931348623158e+308)

//-----------------------------------------------------------------------------
// Messages defines.
//-----------------------------------------------------------------------------
#define PL2GANGLIA_HELP_MESSAGE_LINES_COUNT 72
#define PL2GANGLIA_HELP_MESSAGE_LINES \
	"\n", \
	"Start pl2ganglia and send PL counter data to local gmond instance.\n", \
	"\n", \
	"Usage:  pl2ganglia --application <name> --guid <GUID> ...\n", \
	"        [--pause <n>] [--process] [--decorate] ...\n", \
	"        [--filter] [--force_use_gmetric] [--force_to_double] ...\n", \
	"        [--list_counters | --counters <string>] ...\n", \
	"        [--gmond_config <gmond.conf>]\n", \
	"Or      pl2ganglia [--version]\n", \
	"Or      pl2ganglia [--help]\n", \
	"\n", \
	"Note: ellipsis (...) marks a line continuation.\n", \
	"\n", \
	"   pl2ganglia converts the counters of a given PL into Ganglia*\n", \
	"metrics.  These metrics are sent to gmond at a regular time interval\n", \
	"until it is interrupted by the user.\n", \
	"   The metric name is the name of the PL counter.  If name decoration\n", \
	"is requested (--decorate), then the PL application's GUID is appended\n", \
	"to the metric name separated by an underscore (_) character.\n", \
	"\n", \
	"   --application with <name> sets the name of the application which\n", \
	"     generates(ed) the PL to convert.\n", \
	"   --guid with <GUID> sets the GUID to specify the application's\n", \
	"     PL instance.\n", \
	"     Note:\n", \
	"       For details on PL, GUID, instances, counters, etc., read\n", \
	"       the Intel(r) Energy Checker SDK User Guide.\n", \
	"   --pause with <n> sets the pause time between each metric update.\n", \
	"     n is expressed in seconds.  n is equal to 60 by default (1 minute).\n", \
	"   --process forces additional analysis on counter values with prescribed\n", \
	"     suffixes.  Use pl2ganglia --process --help for more information on\n", \
	"     the suffixes.\n", \
	"   --decorate appends the PL GUID to each counter name for the Ganglia\n", \
	"     metric names.\n", \
	"   --filter performs the following actions on the Ganglia metric names:\n", \
	"     1 Clips the name to PL2GANGLIA_COUNTER_MAX_LENGTH characters.\n", \
	"     2 Replace space ( ) character with underscode (_) character.\n", \
	"   --force_use_gmetric forces the use of gmetric to send metric update.\n", \
	"     to gmond.  By default, pl2ganglia communicates directly with gmond.\n", \
	"     Note that on Windows*, this option is enforced and the gmetric\n", \
	"     command is displayed for informational purpose only.\n", \
	"   --force_to_double forces native, non-processes PL counters into.\n", \
	"     double metric.  This option allows pl2ganglia to work with versions\n", \
	"     of Ganglia not supporting ull data types.  Caution, data will be\n", \
	"     converted into double and will be lost when a PL counter's value \n", \
	"     becomes too big to be represented by a double on your system.\n", \
	"   --list_counters lists the specified PL's counters after applying\n", \
	"     counter processing if requested (--process).  Each counter is\n", \
	"     numbered from one.  Use this information with --counter option.\n", \
	"   --counters with <string> selects which counters in the PL will be\n", \
	"     converted.  By default all counters in the PL are converted.\n", \
	"     The counter string represents counter numbers and/or counter ranges\n", \
	"     separated by space(s).  A counter range is specified by the first and\n", \
	"     the last (inclusive) counter numbers separated by a dash (-) character.\n", \
	"     For example \"1 2 5-10\".  Use the --list_counters to identify the\n", \
	"     counter numbers to use.\n", \
	"   --gmond_config with <gmond.conf> sets the configuration file name to\n", \
	"     use.  By default it is set to /etc/ganglia/gmond.conf.\n", \
	"   --version prints version information.\n", \
	"   --help prints this help message.\n", \
	"\n", \
	"Example:\n", \
	"   ./pl2ganglia --application test --guid 8c04f223-425b-42e8-9605-83d...\n", \
	"   05e15d4f9 --boost --decorate --filter --gmond_conf...\n", \
	"   /usr/etc/gmond.conf --process\n", \
	"\n", \
	"pl2ganglia continues to send data once per minute to gmond (or\n", \
	"whatever time interval is selected with the --pause option) until it.\n", \
	"is interrupted by the user (<CTRL>+<C>).\n", \
	"\n", \
	"* Third-party trademarks are the property of their respective owners.\n", \
	"\n"

#define PL2GANGLIA_SUFFIXES_HELP_MESSAGE_LINES_COUNT 119
#define PL2GANGLIA_SUFFIXES_HELP_MESSAGE_LINES \
	"\n", \
	"Additional help information on the counter suffixes supported by pl2gnaglia.\n", \
	"\n", \
	"   The following suffixes are recognized by pl2gnaglia when the --process\n", \
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

#define PL2GANGLIA_STARTUP_MESSAGE_LINES_COUNT 10
#define PL2GANGLIA_STARTUP_MESSAGE_LINES \
	"\n", \
	"----------------------------------------------------------------------\n", \
	" @@@@@  @        @@    @@@@    @@   @    @  @@@@  @      @@@@@    @@\n", \
	" @    @ @       @  @  @    @  @  @  @@   @ @    @ @        @     @  @\n", \
	" @    @ @          @  @      @    @ @ @  @ @      @        @    @    @\n", \
	" @@@@@  @         @   @      @    @ @ @  @ @      @        @    @    @\n", \
	" @      @        @    @  @@@ @@@@@@ @  @ @ @  @@@ @        @    @@@@@@\n", \
	" @      @       @     @    @ @    @ @   @@ @    @ @        @    @    @\n", \
	" @      @@@@@@  @@@@   @@@@  @    @ @    @  @@@@  @@@@@@ @@@@@  @    @\n", \
	"----------------------------------------------------------------------"
#define PL2GANGLIA_DASHES \
	"----------------------------------------------------------------------"

//-----------------------------------------------------------------------------
// Constants definitions and enums.
//-----------------------------------------------------------------------------
#define PL2GANGLIA_COUNTER_RANGE_SEPARATOR "-"

#define PL2GANGLIA_MAX_TOKENS 14

#define PL2GANGLIA_PRIORITY_BOOST "--BOOST"
#define PL2GANGLIA_PROCESS "--PROCESS"
#define PL2GANGLIA_DECORATE "--DECORATE"
#define PL2GANGLIA_FILTER "--FILTER"
#define PL2GANGLIA_FORCE_TO_DOUBLE "--FORCE_TO_DOUBLE"
#define PL2GANGLIA_FORCE_USE_GMETRIC "--FORCE_USE_GMETRIC"
#define PL2GANGLIA_VERSION "--VERSION"
#define PL2GANGLIA_PAUSE "--PAUSE"
#define PL2GANGLIA_HELP "--HELP"
#define PL2GANGLIA_GMOND_CONFIG_FILE_NAME "--GMOND_CONFIG"
#define PL2GANGLIA_APPLICATION "--APPLICATION"
#define PL2GANGLIA_GUID "--GUID"
#define PL2GANGLIA_LIST_COUNTERS "--LIST_COUNTERS"
#define PL2GANGLIA_COUNTERS "--COUNTERS"

#define PL2GANGLIA_TOKENS \
	PL2GANGLIA_PRIORITY_BOOST, \
	PL2GANGLIA_PROCESS, \
	PL2GANGLIA_DECORATE, \
	PL2GANGLIA_FILTER, \
	PL2GANGLIA_FORCE_TO_DOUBLE, \
	PL2GANGLIA_FORCE_USE_GMETRIC, \
	PL2GANGLIA_VERSION, \
	PL2GANGLIA_PAUSE, \
	PL2GANGLIA_HELP, \
	PL2GANGLIA_GMOND_CONFIG_FILE_NAME, \
	PL2GANGLIA_APPLICATION, \
	PL2GANGLIA_GUID, \
	PL2GANGLIA_LIST_COUNTERS, \
	PL2GANGLIA_COUNTERS

typedef enum _pl2ganglia_token_ids {

	PL2GANGLIA_PRIORITY_BOOST_TOKEN_ID = 0,
	PL2GANGLIA_PROCESS_TOKEN_ID,
	PL2GANGLIA_DECORATE_TOKEN_ID,
	PL2GANGLIA_FILTER_TOKEN_ID,
	PL2GANGLIA_FORCE_TO_DOUBLE_TOKEN_ID,
	PL2GANGLIA_FORCE_USE_GMETRIC_TOKEN_ID,
	PL2GANGLIA_VERSION_TOKEN_ID,
	PL2GANGLIA_PAUSE_TOKEN_ID,
	PL2GANGLIA_HELP_TOKEN_ID,
	PL2GANGLIA_GMOND_CONFIG_FILE_NAME_TOKEN_ID,
	PL2GANGLIA_APPLICATION_TOKEN_ID,
	PL2GANGLIA_GUID_TOKEN_ID,
	PL2GANGLIA_LIST_COUNTERS_TOKEN_ID,
	PL2GANGLIA_COUNTERS_TOKEN_ID
	
} PL2GANGLIA_TOKEN_IDS, *PPL2GANGLIA_TOKEN_IDS;

//-----------------------------------------------------------------------------
// Error codes.
//-----------------------------------------------------------------------------
typedef enum _pl2ganglia_error {

	//-------------------------------------------------------------------------
	// Generic error codes.
	//-------------------------------------------------------------------------
	PL2GANGLIA_NO_ERROR = 0,
	PL2GANGLIA_OUT_OF_MEMORY,
	PL2GANGLIA_INVALID_PARAMETERS,
	PL2GANGLIA_CONFLICTING_OPTIONS,
	PL2GANGLIA_UNABLE_TO_SET_MEMORY_DEBUG,
	PL2GANGLIA_UNABLE_TO_INSTALL_EVENT_HANDLER,
	PL2GANGLIA_UNABLE_TO_REMOVE_EVENT_HANDLER,
	PL2GANGLIA_UNABLE_TO_SIGNAL_INTERRUPT,
	PL2GANGLIA_MISSING_PAUSE_TIME,
	PL2GANGLIA_INVALID_PAUSE_TIME,
	PL2GANGLIA_UNABLE_TO_SETUP_HP_TIMER,
	PL2GANGLIA_UNABLE_TO_MEASURE_TIME,
	PL2GANGLIA_UNABLE_TO_SLEEP,
	PL2GANGLIA_UNABLE_TO_BOOST_PRIORITY,
	PL2GANGLIA_SUSPICIOUS_PL_INI,
	PL2GANGLIA_TOO_MANY_PL_INI,
	PL2GANGLIA_MISSING_COUNTERS,

	//-------------------------------------------------------------------------
	// PL error codes.
	//-------------------------------------------------------------------------
	PL2GANGLIA_TOO_MANY_PL_PARAMETERS,
	PL2GANGLIA_MISSING_PL_PARAMETERS,
	PL2GANGLIA_MISSING_APPLICATION_NAME,
	PL2GANGLIA_MISSING_GUID,
	PL2GANGLIA_SUSPICIOUS_GUID,
	PL2GANGLIA_MISSING_PL_CONFIG_FILE_NAME,
	PL2GANGLIA_UNABLE_TO_GET_PL_DATA,
	PL2GANGLIA_UNABLE_TO_OPEN_PL,
	PL2GANGLIA_UNABLE_TO_ATTACH_TO_PL,
	PL2GANGLIA_UNABLE_TO_CLOSE_PL,
	PL2GANGLIA_UNABLE_TO_READ_PL,

	//-------------------------------------------------------------------------
	// Ganglia error codes.
	//-------------------------------------------------------------------------
	PL2GANGLIA_MISSING_GMOND_CONFIGURATION_FILE_NAME,
	PL2GANGLIA_UNABLE_TO_CREATE_GANGLIA_POOL,
	PL2GANGLIA_UNABLE_TO_CONFIGURE_GMOND,
	PL2GANGLIA_UNABLE_TO_CREATE_UDP_CHANNELS,
	PL2GANGLIA_UNABLE_TO_CREATE_UPDATE_MESSAGE,
	PL2GANGLIA_INVALID_METRIC_PARAMETERS,
	PL2GANGLIA_INVALID_METRIC_CHARACTER,
	PL2GANGLIA_INVALID_METRIC_TYPE,
	PL2GANGLIA_INVALID_METRIC_VALUE,
	PL2GANGLIA_UNABLE_TO_COMMUNICATE_WITH_GMOND,
	PL2GANGLIA_UNABLE_TO_RUN_GMETRIC,
	PL2GANGLIA_UNABLE_TO_SEND_METRIC_UPDATE_MESSAGE
	
} PL2GANGLIA_ERROR, *PPL2GANGLIA_ERROR;

//-----------------------------------------------------------------------------
// Counter processing codes.
//-----------------------------------------------------------------------------
typedef enum _pl2ganglia_processing_codes {

	PROCESSING_DATA = -1,
	NO_PROCESSING = 0,
	DECIMALS_PROCESSING = 2,
	OFFSET_PROCESSING = 4,
	OFFSET_DECIMALS_PROCESSING = 8,
	SCALAR_PROCESSING = 16,
	SIGN_PROCESSING = 32,
	OFFSET_SIGN_PROCESSING = 64,
	SCALAR_DECIMALS_PROCESSING = 128

} PL2GANGLIA_PROCESSING_CODES;

typedef enum _pl2ganglia_counter_type_codes {

	PL2GANGLIA_STRING = -1,
	PL2GANGLIA_INT8 = 0,
	PL2GANGLIA_UINT8,
	PL2GANGLIA_INT16,
	PL2GANGLIA_UINT16,
	PL2GANGLIA_INT32,
	PL2GANGLIA_UINT32,
	PL2GANGLIA_FLOAT,
	PL2GANGLIA_DOUBLE,
	PL2GANGLIA_ULL

} PL2GANGLIA_COUNTER_TYPE_CODES;

//-----------------------------------------------------------------------------
// Structures.
//-----------------------------------------------------------------------------
typedef struct _pl2ganglia_counter_data {

	int f_selected;
	PL2GANGLIA_PROCESSING_CODES processed;
	unsigned long long ull_value;
	unsigned int ui_value;
	long double double_value;
	char name[PL_MAX_PATH];
	char decorated_name[PL_MAX_PATH];
	unsigned int i_decimals;
	unsigned int i_offset;
	unsigned int i_offset_decimals;
	unsigned int i_offset_sign;
	unsigned int i_scalar;
	unsigned int i_scalar_decimals;
	unsigned int i_sign;

} PL2GANGLIA_COUNTER_DATA, *PPL2GANGLIA_COUNTER_DATA;

#ifdef __PL_MACOSX__
	#define PL2GANGLIA_SEMAPHORE_NAME_MAX_SIZE 12
	#define PL2GANGLIA_SEMAPHORE_NAME "SSSTOT"
#endif // __PL_MACOSX__

typedef struct _pl2ganglia_data {

	//-------------------------------------------------------------------------
	// User options.
	//-------------------------------------------------------------------------
	int pause_time;
	int pause_time_in_s;
	int f_process;
	int f_decorate;
	int f_filter;
	int f_force_to_double;
	int f_force_use_gmetric;
	int f_version;
	int f_help;
	int f_boost;
	int f_gmond_coniguration_file_name;
	char gmond_configuration_file_name[PL_MAX_PATH];
	int f_config;
	char *config;
	int f_application_name;
	char *application_name;
	int f_guid;
	char *guid;
	int f_list_counters;
	int f_counters;
	char *counters;

	//-------------------------------------------------------------------------
	// Converter data.
	//-------------------------------------------------------------------------
	int f_convert;
	int *counters_map;
	unsigned int processed_counters_count;
	unsigned int requested_counters_count;
	PL2GANGLIA_ERROR last_error;

	//-------------------------------------------------------------------------
	// Timing & synchronization data.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	HANDLE sleep_event;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	int f_sleep_event_created;
	pthread_cond_t sleep_condition_variable;
	pthread_mutex_t sleep_mutex;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	//-------------------------------------------------------------------------
	// PL data.
	//-------------------------------------------------------------------------
	int pld;
	PLH_DYNAMIC_CONFIG_INFO pl_data;
	PL2GANGLIA_COUNTER_DATA *pl_counters_data;

	//-------------------------------------------------------------------------
	// Ganglia* data.
	// * Third-party trademarks are the property of their respective owners.
	//-------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	Ganglia_pool global_context;
	Ganglia_metric gmetric;
	Ganglia_gmond_config gmond_config;
	Ganglia_udp_send_channels send_channels;
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

} PL2GANGLIA_DATA, *PPL2GANGLIA_DATA;

//-----------------------------------------------------------------------------
// Functions prototype
//-----------------------------------------------------------------------------
extern PL_STATUS pl2ganglia_send_metric_update(PPL2GANGLIA_DATA, unsigned int, PL2GANGLIA_COUNTER_TYPE_CODES);
extern PL_STATUS pl2ganglia_parse_cli(PPL2GANGLIA_DATA, int, char **);
extern PL_STATUS pl2ganglia_parse_counter_list(PPL2GANGLIA_DATA, char *);
extern PL_STATUS pl2ganglia_clean_up(PPL2GANGLIA_DATA);
#ifdef __PL_WINDOWS__
	extern BOOL signal_handler(DWORD);
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	extern void signal_handler(int);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__
extern void pl2ganglia_decode_error(PL2GANGLIA_ERROR);
extern void pl2ganglia_time_stamp(char *, size_t);
extern void pl2ganglia_display(char *);
extern void pl2ganglia_diagnostic(char *);
extern void pl2ganglia_error(char *);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PL2GANGLIA__
