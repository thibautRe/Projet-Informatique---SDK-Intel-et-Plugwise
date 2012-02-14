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
*** or disclosed in any way without Intel's prior express written permission.
***
*** No license under any patent, copyright, trade secret or other intellectual
*** property right is granted to or conferred upon you by disclosure or delivery
*** of the Materials, either expressly, by implication, inducement, estoppel or
*** otherwise. Any license under such intellectual property rights must be 
*** express and approved by Intel in writing.
**/

import java.util.UUID;

public class ProductivityLinkDemo
{
	public static void main(String[] args) {

		int pld;
		String application_name = "my_java_application";
		String counter_names[] = {
			"The Amazing A Counter",
			"The not so bad B Counter",
			"Counter C",
			"Counter D"
		};
		UUID uuid = new UUID(0, 0);
		Long val1 = new Long(987654321);
		Long val2 = new Long(123456789);

		//-----------------------------------------------------------------------------
		// create and open a PL
		//-----------------------------------------------------------------------------
		ProductivityLink jpl = new ProductivityLink();
		pld = jpl.pl_open(application_name, counter_names.length, counter_names, uuid);

		//-----------------------------------------------------------------------------
		// write few counters
		//-----------------------------------------------------------------------------
		jpl.pl_write(pld, val1, 0);
		jpl.pl_write(pld, val2, 1);

		//-----------------------------------------------------------------------------
		// close the PL
		//-----------------------------------------------------------------------------
		jpl.pl_close(pld);
	}
}
