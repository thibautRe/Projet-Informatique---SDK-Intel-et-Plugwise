#/**
#*** INTEL CONFIDENTIAL
#*** 
#*** Copyright (October 2008) (October 2008) Intel Corporation All Rights Reserved. 
#*** The source code contained or described herein and all documents related to the
#*** source code ("Material") are owned by Intel Corporation or its suppliers or 
#*** licensors. Title to the Material remains with Intel Corporation or its 
#*** suppliers and licensors. The Material contains trade secrets and proprietary 
#*** and confidential information of Intel or its suppliers and licensors. 
#*** The Material is protected by worldwide copyright and trade secret laws 
#*** and treaty provisions. No part of the Material may be used, copied, 
#*** reproduced, modified, published, uploaded, posted, transmitted, distributed,
#*** or disclosed in any way without Intel's prior express written permission.
#***
#*** No license under any patent, copyright, trade secret or other intellectual
#*** property right is granted to or conferred upon you by disclosure or delivery
#*** of the Materials, either expressly, by implication, inducement, estoppel or
#*** otherwise. Any license under such intellectual property rights must be 
#*** express and approved by Intel in writing.
#**/

# @      @@@@@  @    @ @    @ @   @
# @        @    @@   @ @    @  @ @
# @        @    @ @  @ @    @   @
# @        @    @ @  @ @    @   @
# @        @    @  @ @ @    @   @
# @        @    @   @@ @    @  @ @
# @@@@@@ @@@@@  @    @  @@@@  @   @

#-----------------------------------------------------------------------------
# IEC SDK directory structure and useful defines.
#-----------------------------------------------------------------------------
IECSDK_ROOT=/orssg-data/Development/iecsdk
IECSDK_SRC_ROOT=$(IECSDK_ROOT)/src
IECSDK_DEP_UTILS=$(IECSDK_ROOT)/utils

IECSDK_IECDDK=$(IECSDK_DEP_UTILS)/device_driver_kit
IECSDK_CORE_API=$(IECSDK_SRC_ROOT)/core_api
IECSDK_IECDDK_SRV=$(IECSDK_IECDDK)/src
IECSDK_IECDDK_SAMPLES=$(IECSDK_IECDDK_SRV)/samples

IECSDK_IECDDK_EMETER_SRC=$(IECSDK_IECDDK)/src/energy_meter_driver
IECSDK_IECDDK_TMETER_SRC=$(IECSDK_IECDDK)/src/temperature_meter_driver
IECSDK_IECDDK_DAQ_SRC=$(IECSDK_IECDDK)/src/daq_meter_driver
IECSDK_IECDDK_EMETER_INCLUDE=$(IECSDK_SRC_ROOT)/energy_server
IECSDK_IECDDK_TMETER_INCLUDE=$(IECSDK_SRC_ROOT)/temperature_server
IECSDK_IECDDK_DAQ_INCLUDE=$(IECSDK_SRC_ROOT)/daq_meter_server
IECSDK_IECDDK_ESRV_CPU_INDEXED_SIMULATED_DEVICE_SRC=$(IECSDK_IECDDK_SAMPLES)/esrv_cpu_indexed_simulated_device
IECSDK_IECDDK_ESRV_CPU_INDEXED_SIMULATED_DEVICE_INCLUDE=$(IECSDK_IECDDK_SAMPLES)/esrv_cpu_indexed_simulated_device

#-----------------------------------------------------------------------------
# IEC SDK configuration.
#-----------------------------------------------------------------------------
#IECSDK_VERSION=debug
IECSDK_VERSION=release
IECSDK_ADDRESSING=32
#IECSDK_ADDRESSING=64

#-----------------------------------------------------------------------------
# IEC SDK tools.
#-----------------------------------------------------------------------------
IECSDK_CLEAR=/usr/bin/clear
IECSDK_CC=/usr/bin/gcc
IECSDK_NM=/usr/bin/nm
IECSDK_LN=/bin/ln
IECSDK_LL=/bin/ls -al
IECSDK_RM_F=/bin/rm -f
IECSDK_MAKE=/usr/bin/make
IECSDK_ECHO=/bin/echo
IECSDK_GREP=/bin/grep

#-----------------------------------------------------------------------------
# IEC SDK build configuration.
#-----------------------------------------------------------------------------
IECSDK_SO_MAJOR_VERSION=1
IECSDK_SO_MINOR_VERSION=0
ifeq ($(IECSDK_ADDRESSING), 32)
	IECSDK_COMPILER_ADDRESSING=-m32
	ifeq ($(IECSDK_VERSION), debug)
		IECSDK_COMPILER_DEBUG_INFO=-g -D_DEBUG -D__PL_DEBUG__
		IECSDK_COMPILER_OPTIMIZATION=-O0 -msse
	else
		IECSDK_COMPILER_DEBUG_INFO=
		IECSDK_COMPILER_OPTIMIZATION=-O2 -msse
	endif
else
	IECSDK_COMPILER_ADDRESSING=-m64
	ifeq ($(IECSDK_VERSION), debug)
		IECSDK_COMPILER_DEBUG_INFO=-g -D_DEBUG -D__PL_DEBUG__
		IECSDK_COMPILER_OPTIMIZATION=-O0 -msse
	else
		IECSDK_COMPILER_DEBUG_INFO=
		IECSDK_COMPILER_OPTIMIZATION=-O2 -msse
	endif
endif

#-----------------------------------------------------------------------------
# API build configuration.
#-----------------------------------------------------------------------------
IECSDK_API_CONFIG=\
	-D__PL_LINUX__ \
	-D__PL_GENERATE_INI__ \
	-D__PL_GENERATE_INI_VERSION_TAGGING__ \
	-D__PL_GENERATE_INI_BUILD_TAGGING__ \
	-D__PL_GENERATE_INI_DATE_AND_TIME_TAGGING__ \
	-D__PL_BLOCKING_COUNTER_FILE_LOCK__ \
	-D__PL_EXTRA_INPUT_CHECKS__

IECSDK_CFLAGS=\
	$(IECSDK_API_CONFIG) \
	$(IECSDK_COMPILER_ADDRESSING) \
	$(IECSDK_COMPILER_DEBUG_INFO) \
	$(IECSDK_COMPILER_OPTIMIZATION) \
	-Wall \
	-fPIC \
	-std=gnu99 \
	-D_SVID_SOURCE \
	-D_REENTRANT \
	-D_LIBC_REENTRANT \
	-pthread

IECSDK_LDFLAGS=\
	-lpthread \
	-luuid \
	-ldl

#-----------------------------------------------------------------------------
# IECSDK targets.
#-----------------------------------------------------------------------------
IECSDK_TARGET_ALL=all
ENERGY_METER_DRIVER=energy_meter_driver
TEMPERATURE_METER_DRIVER=temperature_meter_driver
DAQ_DRIVER=daq_driver
SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE=esrv_cpu_indexed_simulated_device
IECSDK_CLEAN=clean
IECSDK_HELP=help

#-----------------------------------------------------------------------------
# Display available targets.
#-----------------------------------------------------------------------------
$(IECSDK_HELP):
	@$(IECSDK_CLEAR)
	@$(IECSDK_ECHO) ""
	@$(IECSDK_ECHO) "Makefile Targets:"
	@$(IECSDK_ECHO) "-----------------"
	@$(IECSDK_ECHO) ""
	@$(IECSDK_ECHO) "all:.................................Build All Targets."
	@$(IECSDK_ECHO) "energy_meter_driver:.................Build The Template Energy Meter Device Support Shared Object for ESRV."
	@$(IECSDK_ECHO) "temperature_meter_driver:............Build The Template Temperature Meter Device Support Shared Object for TSRV."
	@$(IECSDK_ECHO) "daq_driver:..........................Build The DAQ Device Support Shared Object for ESRV."
	@$(IECSDK_ECHO) "esrv_cpu_indexed_simulated_device:...Build The Sample CPU Indexed ESRV Simulated Device."
	@$(IECSDK_ECHO) ""
	@$(IECSDK_ECHO) "clean:...............................Delete All Build Files."
	@$(IECSDK_ECHO) "help:................................Print This Help Message."
	@$(IECSDK_ECHO) ""
	@$(IECSDK_ECHO) "Notes:"
	@$(IECSDK_ECHO) "------"
	@$(IECSDK_ECHO) "   Use The IECSDK_VERSION Symbol To Build Debug (debug) Or Release (release) Binaries."
	@$(IECSDK_ECHO) "   Use The IECSDK_ADDRESSING Symbol To Build 32bit (32) Or 64bit (64) Binaries."
	@$(IECSDK_ECHO) "   By Default, IECSDK_VERSION=debug and IECSDK_ADDRESSING=32 Are Used."
	@$(IECSDK_ECHO) ""

#-----------------------------------------------------------------------------
# Clean all targets.
#-----------------------------------------------------------------------------
$(IECSDK_CLEAN):
	@$(IECSDK_CLEAR)
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	@$(IECSDK_ECHO) "# Clean all targets."
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	@$(IECSDK_RM_F) $(ENERGY_METER_DRIVER).so
	@$(IECSDK_RM_F) $(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION)
	@$(IECSDK_RM_F) $(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION)
	@$(IECSDK_RM_F) $(TEMPERATURE_METER_DRIVER).so
	@$(IECSDK_RM_F) $(TEMPERATURE_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION)
	@$(IECSDK_RM_F) $(TEMPERATURE_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION)
	@$(IECSDK_RM_F) $(DAQ_DRIVER).so
	@$(IECSDK_RM_F) $(DAQ_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION)
	@$(IECSDK_RM_F) $(DAQ_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION)
	@$(IECSDK_RM_F) $(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so
	@$(IECSDK_RM_F) $(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so.$(IECSDK_SO_MAJOR_VERSION)
	@$(IECSDK_RM_F) $(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION)

#------------------------- build rules ---------------------------------------

#-----------------------------------------------------------------------------
# Build all targets.
#-----------------------------------------------------------------------------
$(IECSDK_TARGET_ALL):
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	@$(IECSDK_ECHO) "# Build all targets."
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	$(IECSDK_MAKE) $(ENERGY_METER_DRIVER)
	$(IECSDK_MAKE) $(TEMPERATURE_METER_DRIVER)
	$(IECSDK_MAKE) $(DAQ_DRIVER)
	$(IECSDK_MAKE) $(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE)
	$(IECSDK_LL)

#-----------------------------------------------------------------------------
# Build The Template Energy Meter Device Support Shared Object for ESRV.
#-----------------------------------------------------------------------------
$(ENERGY_METER_DRIVER):
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	@$(IECSDK_ECHO) "# Build The Template Energy Meter Device Support Shared Object for ESRV."
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	$(IECSDK_CC) \
		$(IECSDK_CFLAGS) \
		-I$(IECSDK_IECDDK_EMETER_SRC) \
		-I$(IECSDK_IECDDK_EMETER_INCLUDE) \
		-c $(IECSDK_IECDDK_EMETER_SRC)/esrv_template_device_dynamic_library.c
	$(IECSDK_CC) \
		$(IECSDK_CFLAGS) \
		-shared \
		-Wl,-soname,$(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		-o $(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		./esrv_template_device_dynamic_library.o
	$(IECSDK_LN) \
		-sf $(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		$(ENERGY_METER_DRIVER).so
	$(IECSDK_LN) \
		-sf $(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		$(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION)
	$(IECSDK_RM_F) \
		./esrv_template_device_dynamic_library.o
	$(IECSDK_NM) \
		$(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) | $(IECSDK_GREP) _device

#-----------------------------------------------------------------------------
# Build The Template Temperature Meter Device Support Shared Object for TSRV.
#-----------------------------------------------------------------------------
$(TEMPERATURE_METER_DRIVER):
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	@$(IECSDK_ECHO) "# Build The Template Temperature Meter Device Support Shared Object for TSRV."
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	$(IECSDK_CC) \
		$(IECSDK_CFLAGS) \
		-I$(IECSDK_IECDDK_TMETER_SRC) \
		-I$(IECSDK_IECDDK_TMETER_INCLUDE) \
		-c $(IECSDK_IECDDK_TMETER_SRC)/tsrv_template_device_dynamic_library.c
	$(IECSDK_CC) \
		$(IECSDK_CFLAGS) \
		-shared \
		-Wl,-soname,$(ENERGY_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		-o $(TEMPERATURE_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		./tsrv_template_device_dynamic_library.o
	$(IECSDK_LN) \
		-sf $(TEMPERATURE_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		$(TEMPERATURE_METER_DRIVER).so
	$(IECSDK_LN) \
		-sf $(TEMPERATURE_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		$(TEMPERATURE_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION)
	$(IECSDK_RM_F) \
		./tsrv_template_device_dynamic_library.o
	$(IECSDK_NM) \
		$(TEMPERATURE_METER_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) | $(IECSDK_GREP) _device

#-----------------------------------------------------------------------------
# Build The DAQ Device Support Shared Object for ESRV.
#-----------------------------------------------------------------------------
$(DAQ_DRIVER):
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	@$(IECSDK_ECHO) "# Build The DAQ Device Support Shared Object for ESRV."
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	$(IECSDK_CC) \
		$(IECSDK_CFLAGS) \
		-I$(IECSDK_IECDDK_DAQ_SRC) \
		-I$(IECSDK_IECDDK_EMETER_INCLUDE) \
		-c $(IECSDK_IECDDK_DAQ_SRC)/esrv_daq_template_device_dynamic_library.c
	$(IECSDK_CC) \
		$(IECSDK_CFLAGS) \
		-shared \
		-Wl,-soname,$(DAQ_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		-o $(DAQ_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		./esrv_daq_template_device_dynamic_library.o
	$(IECSDK_LN) \
		-sf $(DAQ_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		$(DAQ_DRIVER).so
	$(IECSDK_LN) \
		-sf $(DAQ_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		$(DAQ_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION)
	$(IECSDK_RM_F) \
		./esrv_daq_template_device_dynamic_library.o
	$(IECSDK_NM) \
		$(DAQ_DRIVER).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) | $(IECSDK_GREP) _device

#-----------------------------------------------------------------------------
# Build The Sample CPU Indexed ESRV Simulated Device.
#-----------------------------------------------------------------------------
$(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE):
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	@$(IECSDK_ECHO) "# Build The Sample CPU Indexed ESRV Simulated Device."
	@$(IECSDK_ECHO) "#-----------------------------------------------------------------------------"
	$(IECSDK_CC) \
		$(IECSDK_CFLAGS) \
		-I$(IECSDK_IECDDK_EMETER_SRC) \
		-I$(IECSDK_IECDDK_EMETER_INCLUDE) \
		-I$(IECSDK_IECDDK_ESRV_CPU_INDEXED_SIMULATED_DEVICE_INCLUDE) \
		-c $(IECSDK_IECDDK_ESRV_CPU_INDEXED_SIMULATED_DEVICE_SRC)/esrv_cpu_indexed_simulated_device.c
	$(IECSDK_CC) \
		$(IECSDK_CFLAGS) \
		-shared \
		-Wl,-soname,$(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		-o $(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		./esrv_cpu_indexed_simulated_device.o
	$(IECSDK_LN) \
		-sf \
		$(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		$(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so
	$(IECSDK_LN) \
		-sf $(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) \
		$(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so.$(IECSDK_SO_MAJOR_VERSION)
	$(IECSDK_RM_F) ./esrv_cpu_indexed_simulated_device.o
	$(IECSDK_NM) $(SAMPLE_CPU_INDEXED_ESRV_SIMULATED_DEVICE).so.$(IECSDK_SO_MAJOR_VERSION).$(IECSDK_SO_MINOR_VERSION) | $(IECSDK_GREP) _device
