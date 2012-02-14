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

#ifdef __PL_DYNAMIC_TABLE_ALLOCATION__
	#ifndef PL_MAX_COUNTERS_PER_LINK
		#define PL_MAX_COUNTERS_PER_LINK 512
	#endif // PL_MAX_COUNTERS_PER_LINK
#endif // __PL_DYNAMIC_TABLE_ALLOCATION__

#ifndef __INCLUDE_PRODUCTIVITY_LINK_HELPER__
#define __INCLUDE_PRODUCTIVITY_LINK_HELPER__

//-----------------------------------------------------------------------------
// version defines
//-----------------------------------------------------------------------------
#define PL_HELPER_VERSION_MAJOR "2009" // year
#define PL_HELPER_VERSION_MINOR "05" // month
#define PL_HELPER_VERSION_REVISION "18" // day

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include "productivity_link.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// configuration - system specific
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
	typedef TCHAR PLH_CHAR, *PPLH_CHAR;
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	typedef char PLH_CHAR, *PPLH_CHAR;
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// Constants definitions.
//-----------------------------------------------------------------------------
#define PLH_MAX_UUIDS 250
#define PLH_DESC_SCRIPT_UUID_STRING_SIZE 36

#ifdef __PL_WINDOWS__
	#define PLH_DIR_SEPARATOR '\\'
	#define PLH_FOLDER_SEARCH _T("C:\\productivity_link\\*")
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
	#define PLH_DIR_SEPARATOR '/'
	#define PLH_FOLDER_SEARCH "/opt/productivity_link/"
#endif// __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

//-----------------------------------------------------------------------------
// constants
//-----------------------------------------------------------------------------
#define MAX_ALLOWED_UUID_CHARACTERS 23
#define ALLOWED_UUID_CHARACTERS	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F', '-'
#define MAX_ALLOWED_NUMBER_CHARACTERS 10
#define ALLOWED_NUMBER_CHARACTERS '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
#define MAX_ALLOWED_NEGATIVE_NUMBER_CHARACTERS 11
#define ALLOWED_NEGATIVE_NUMBER_CHARACTERS '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'
#ifdef __PL_WINDOWS__
	#define MAX_RESERVED_CHARACTERS 10
	#define RESERVED_CHARACTERS '\0', '?', '*', '"', '/', '\\', '<', '>', ':', '|'
#endif // __PL_WINDOWS__
#if defined (__PL_LINUX__) || (__PL_SOLARIS__)
	#define MAX_RESERVED_CHARACTERS 2
	#define RESERVED_CHARACTERS '\0', '\\'
#endif // __PL_LINUX__ || __PL_SOLARIS__
#ifdef __PL_MACOSX__
	#define MAX_RESERVED_CHARACTERS 2
	#define RESERVED_CHARACTERS '\0', ':'
#endif // __PL_MACOSX__

//-----------------------------------------------------------------------------
// structures & types
//-----------------------------------------------------------------------------
typedef struct _plh_config_info {

	PLH_CHAR application_name[PL_MAX_PATH];
	PLH_CHAR uuid[PL_MAX_PATH];
	PLH_CHAR pl_root[PL_MAX_PATH];
	unsigned int max_counters;
	PLH_CHAR full_counter_names[PL_MAX_COUNTERS_PER_LINK][PL_MAX_PATH];
	PLH_CHAR counter_names[PL_MAX_COUNTERS_PER_LINK][PL_MAX_PATH];

} PLH_CONFIG_INFO, *PPLH_CONFIG_INFO;

typedef struct _plh_dynamic_config_info_entry {

	PLH_CHAR full_counter_names[PL_MAX_PATH];
	PLH_CHAR counter_names[PL_MAX_PATH];

} PLH_DYNAMIC_CONFIG_INFO_ENTRY, *PPLH_DYNAMIC_CONFIG_INFO_ENTRY;

typedef struct _plh_dynamic_config_info {

	PLH_CHAR application_name[PL_MAX_PATH];
	PLH_CHAR uuid[PL_MAX_PATH];
	PLH_CHAR pl_root[PL_MAX_PATH];
	unsigned int max_counters;
	PPLH_DYNAMIC_CONFIG_INFO_ENTRY entries;

} PLH_DYNAMIC_CONFIG_INFO, *PPLH_DYNAMIC_CONFIG_INFO;

typedef struct _plh_pl_folder_info {

	unsigned int max_uuids;
	PLH_CHAR full_uuids[PLH_MAX_UUIDS][PL_MAX_PATH];
	PLH_CHAR application_names[PLH_MAX_UUIDS][PL_MAX_PATH];
	PLH_CHAR uuids[PLH_MAX_UUIDS][PL_MAX_PATH];

} PLH_PL_FOLDER_INFO, *PPLH_PL_FOLDER_INFO;

typedef struct _plh_dynamic_pl_folder_info_entry {

	PLH_CHAR full_uuid[PL_MAX_PATH];
	PLH_CHAR application_name[PL_MAX_PATH];
	PLH_CHAR uuid[PL_MAX_PATH];

} PLH_DYNAMIC_PL_FOLDER_INFO_ENTRY, *PPLH_DYNAMIC_PL_FOLDER_INFO_ENTRY;

typedef struct _plh_dynamic_pl_folder_info {

	unsigned int max_uuids;
	PPLH_DYNAMIC_PL_FOLDER_INFO_ENTRY entries;

} PLH_DYNAMIC_PL_FOLDER_INFO, *PPLH_DYNAMIC_PL_FOLDER_INFO;

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
PL_API int plh_get_young_pl_by_application_name(char *, char *);
PL_API void plh_decode_error(PL_ERROR);
PL_API int plh_read_pl_config_ini_file(char *, PPLH_CONFIG_INFO);
PL_API int plh_dynamic_read_pl_config_ini_file(char *, PPLH_DYNAMIC_CONFIG_INFO);
PL_API int plh_read_pl_folder(PPLH_PL_FOLDER_INFO);
PL_API int plh_dynamic_read_pl_folder(PPLH_DYNAMIC_PL_FOLDER_INFO);
PL_API int plh_filter_string(char *);
PL_API int plh_filter_uuid_string(char *);
PL_API int plh_filter_number_string(char *);
PL_API int plh_filter_negative_number_string(char *);
PL_API int plh_upper_string(char *);
PL_API void print_version_info(const char *, const char *, const char *, const char *);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PRODUCTIVITY_LINK_HELPER__
