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
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace ProductivityLinkDemo {

    class Program {

        //-----------------------------------------------------------------------------
        // the entry point
        //-----------------------------------------------------------------------------
        [STAThread]
        static void Main(string[] args) {

		    int pld;
		    string application_name = "my_C#_application";
		    string [] counter_names = {
			    "The Amazing A Counter",
			    "The not so bad B Counter",
			    "Counter C",
			    "Counter D"
		    };
		    Guid uuid = Guid.NewGuid();
		    ulong val1 = 987654321;
		    ulong val2 = 123456789;

		    //-----------------------------------------------------------------------------
		    // create and open a PL
		    //-----------------------------------------------------------------------------
            pld = ProductivityLink.pl_open(application_name, counter_names.Length, counter_names, ref uuid);

		    //-----------------------------------------------------------------------------
		    // write few counters
		    //-----------------------------------------------------------------------------
            ProductivityLink.pl_write(pld, ref val1, 0);
            ProductivityLink.pl_write(pld, ref val2, 1);

		    //-----------------------------------------------------------------------------
		    // close the PL
		    //-----------------------------------------------------------------------------
            ProductivityLink.pl_close(pld);
        }
    }

    public class ProductivityLink {

        //-----------------------------------------------------------------------------
        // functions InteropServices interfaces
        //-----------------------------------------------------------------------------
        [DllImport("productivity_link.dll", CharSet = CharSet.Ansi, EntryPoint = "pl_open", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pl_open(string pl_application_name, int pl_counters_count, string[] pl_counters_names, ref Guid puuid);
        [DllImport("productivity_link.dll", CharSet = CharSet.Ansi, EntryPoint = "pl_attach", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pl_attach(string pl_config_file_name);
        [DllImport("productivity_link.dll", EntryPoint = "pl_close", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pl_close(int pld);
        [DllImport("productivity_link.dll", EntryPoint = "pl_read", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pl_read(int pld, ref ulong counter, int counter_index);
        [DllImport("productivity_link.dll", EntryPoint = "pl_write", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pl_write(int pld, ref ulong counter, int counter_index);
    }
}
