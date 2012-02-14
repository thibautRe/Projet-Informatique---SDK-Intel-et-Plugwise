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

using System;
using System.Runtime.InteropServices;

public class ProductivityLink {

    //-----------------------------------------------------------------------------
    // functions InteropServices interfaces
    //-----------------------------------------------------------------------------
    [DllImport("productivity_link.dll", CharSet = CharSet.Ansi, EntryPoint = "pl_open", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
    public static extern int pl_open(string pl_application_name, int pl_counters_count, string[] pl_counters_names, ref Guid puuid);
    [DllImport("productivity_link.dll", CharSet = CharSet.Ansi, EntryPoint = "pl_attach", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
    public static extern int pl_attach(string pl_config_file_name);
    [DllImport("productivity_link.dll", CharSet = CharSet.Ansi, EntryPoint = "pl_close", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
    public static extern int pl_close(int pld);
    [DllImport("productivity_link.dll", CharSet = CharSet.Ansi, EntryPoint = "pl_read", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
    public static extern int pl_read(int pld, ref ulong counter, int counter_index);
    [DllImport("productivity_link.dll", CharSet = CharSet.Ansi, EntryPoint = "pl_write", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
    public static extern int pl_write(int pld, ref ulong counter, int counter_index);

    //-----------------------------------------------------------------------------
    // enums
    //-----------------------------------------------------------------------------
    public enum _pl_status {
	    PL_SUCCESS,
	    PL_FAILURE
    }

    public enum _pl_failure {
	    PL_INVALID_DESCRIPTOR = 0x10000000,
	    PL_BYPASSED,
	    PL_INVALID_PARAMETERS,
	    PL_SYNCHRONIZATION_FAILED,
	    PL_MISSING_DIRECTORY,
	    PL_NOT_A_DIRECTORY,
	    PL_DIRECTORY_CREATION_FAILED,
	    PL_DIRECTORY_ALREADY_EXISTS,
	    PL_PATH_NOT_FOUND,
	    PL_DESCRIPTOR_TABLE_FULL,
	    PL_DESCRIPTOR_TABLE_UNINITIALIZED,
	    PL_NON_GLOBAL_UUID_DESCRIPTOR,
	    PL_NON_GLOBAL_UUID_DESCRIPTOR_NO_ADDRESS,
	    PL_GLOBAL_UUID_DESCRIPTOR_CREATION_FAILED,
	    PL_GLOBAL_UUID_DESCRIPTOR_TO_STRING_FAILED,
	    PL_CRITICAL_FAILURE,
	    PL_CONFIG_FILE_GENERATION_FAILED,
	    PL_CONFIG_FILE_OPENING_FAILED,
	    PL_COUNTER_CREATION_FAILED,
	    PL_COUNTER_SEMAPHORE_CREATION_FAILED,
	    PL_COUNTER_ATTACH_FAILED,
	    PL_COUNTER_TO_STRING_FAILED,
	    PL_COUNTER_WRITE_FAILED,
	    PL_COUNTER_FILE_RESET_FILE_POINTER_FAILED,
	    PL_COUNTER_READ_FAILED,
	    PL_COUNTER_FILE_LOCK_FAILED,
	    PL_COUNTER_FILE_ALREADY_LOCKED,
	    PL_COUNTER_FILE_UNLOCK_FAILED,
	    PL_COUNTER_VALUE_OUT_OF_RANGE,
	    PL_NO_ERROR
    }

    //-----------------------------------------------------------------------------
    // constants definitions
    // In C# the #define preprocessor directive cannot be used to define constants
    // in the way that is typically used in C and C++. 
    //-----------------------------------------------------------------------------
    public static class _pl_constants {
        public const int PL_MAX_PRODUCTIVITY_LINKS = 10;
        public const int PL_MAX_COUNTERS_PER_LINK = 250;
        public const int PL_CONFIGURATION_FILE_APPLICATION_NAME_LINE = 1;
        public const int PL_CONFIGURATION_FILE_UUID_STRING_LINE = 2;
        public const int PL_CONFIGURATION_FILE_LOCATION_LINE = 3;
        public const int PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE = 4;   
    }
}