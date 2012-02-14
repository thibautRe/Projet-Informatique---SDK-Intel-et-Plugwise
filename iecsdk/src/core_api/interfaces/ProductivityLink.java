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
*** or disclosed in any way without Intels prior express written permission.
***
*** No license under any patent, copyright, trade secret or other intellectual
*** property right is granted to or conferred upon you by disclosure or delivery
*** of the Materials, either expressly, by implication, inducement, estoppel or
*** otherwise. Any license under such intellectual property rights must be 
*** express and approved by Intel in writing.
**/

//-----------------------------------------------------------------------------
// Productivity Link JNI interface class
//-----------------------------------------------------------------------------
import java.util.UUID;

public class ProductivityLink {
	
	//-----------------------------------------------------------------------------
	// functions jni interfaces
	//-----------------------------------------------------------------------------
	public native int pl_open(String pl_application_name, int pl_counters_count, String pl_counters_names[], UUID puuid);
	public native int pl_attach(String pl_config_file_name);
	public native int pl_close(int pld);
	public native int pl_write(int pld, Long counter, int counter_index);
	public native int pl_read(int pld, Long counter, int counter_index);

	//-----------------------------------------------------------------------------
	// enums
	//-----------------------------------------------------------------------------
	public enum _pl_status {
		PL_SUCCESS,
		PL_FAILURE;
	}

	public enum _pl_failure {
		PL_INVALID_DESCRIPTOR (0x10000000),
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
		PL_OUT_OF_MEMORY,
		PL_BLOCKING_PL_READ_INSTANCE_CREATION_FAILED,
		PL_BLOCKING_PL_READ_INSTANCE_DESTRUCTION_FAILED,
		PL_BLOCKING_PL_READ_HANDLE_CREATION_FAILED,
		PL_BLOCKING_PL_READ_HANDLE_DESTRUCTION_FAILED,
		PL_BLOCKING_PL_READ_HANDLE_RENEWING_FAILED,
		PL_BLOCKING_PL_READ_WAITING_NOTIFICATION_FAILED,
		PL_COUNTER_WRITE_CACHE_HIT,
		PL_COUNTER_WRITE_CACHE_MISS,
		PL_NO_ERROR;
		
		private int failure_code = 0;
		
		private _pl_failure(int code) {
			this.failure_code = code;
		}
		
		private _pl_failure() {
			this.failure_code = 0;
		}		
	}

	//-----------------------------------------------------------------------------
	// constants definitions
	//-----------------------------------------------------------------------------
	public static class _pl_constants
	{
		static final int PL_MAX_PRODUCTIVITY_LINKS = 10;
		static final int PL_MAX_COUNTERS_PER_LINK = 250;
		static final int PL_CONFIGURATION_FILE_APPLICATION_NAME_LINE = 1;
		static final int PL_CONFIGURATION_FILE_UUID_STRING_LINE = 2;
		static final int PL_CONFIGURATION_FILE_LOCATION_LINE = 3;
		static final int PL_CONFIGURATION_FILE_COUNTERS_NUMBER_LINE = 4;
	}

	static {
		System.loadLibrary("productivity_link_jni");
	}
}
