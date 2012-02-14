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

#include "productivity_link.h"

int main(void) {

	PL_STATUS ret = PL_FAILURE;
	int pld = PL_INVALID_DESCRIPTOR;
	char application_name[] = "dummy_main";
	const char *counters_name[] = { "A" };
	unsigned long long value = 0;
	unsigned int counters_count = 1;
	uuid_t uuid;

	pld = pl_open(
		application_name,
		counters_count,
		counters_name,
		&uuid
	);
	if(pld != PL_INVALID_DESCRIPTOR) {
		value = 1000;
		ret = pl_write(
			pld,
			&value,
			0
		);
		if(ret == PL_SUCCESS) {
			ret = pl_close(pld);
		}
	}
	return(ret);
}
