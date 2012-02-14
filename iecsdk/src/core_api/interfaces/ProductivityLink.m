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

//-----------------------------------------------------------------------------
// headers inclusion
//-----------------------------------------------------------------------------
#include "productivity_link.h"
#import <Foundation/NSObject.h>
#import "ProductivityLink.h"

//-----------------------------------------------------------------------------
// ProductivityLink implementation
//-----------------------------------------------------------------------------
@implementation ProductivityLink

-(int) PlOpen: 
	(char *) application_name andcounters_count: 
	(unsigned int) counters_count andcounters_names: 
	(const char *[]) counters_names andpuuid: 
	(uuid_t *)puuid 
{
	return(
		pl_open(
			application_name, 
			counters_count, 
			counters_names, 
			puuid
		)
	);
}

-(int) PlAttach: 
	(char *) pl_config 
{
	return(
		pl_attach(
			pl_config
		)
	);
}

-(int) PlWrite: 
	(int) pld andpvalue: 
	(void *)pvalue andoffset: 
	(unsigned int)offset 
{
	return(
		pl_write(
			pld, 
			pvalue, 
			offset
		)
	);
}

-(int) PlRead: 
	(int) pld andpvalue: 
	(void *)pvalue andoffset: 
	(unsigned int)offset 
{
	return(
		pl_read(
			pld, 
			pvalue, 
			offset
		)
	);
}

-(int) PlClose: 
	(int) pld 
{
	return(
		pl_close(
			pld
		)
	);
}
@end
