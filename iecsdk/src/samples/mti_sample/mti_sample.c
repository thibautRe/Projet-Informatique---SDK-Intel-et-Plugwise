/**
*** INTEL CONFIDENTIAL
*** 
*** Copyright (August 2010) (August 2010) Intel Corporation All Rights Reserved. 
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

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Note on asserts:
//    This is a sample code and not a production code. Therefore, no error
//    processing is performed in addition of the use of assertions.  However,
//    all function call returns are tested and asserted for success.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Build notes
//-----------------------------------------------------------------------------
// following symbols alters compilation and execution paths
// __MTI_SAMPLE_FILE_LOG__:
//    define this symbol to enable file logging
// __MTI_SAMPLE_PER_GESTURE_FILE_LOG__:
//    define this symbol to enable file logging for each gesture.  This symbol
//    is exclusive with __MTI_SAMPLE_FILE_LOG__.
// __MTI_SAMPLE_NO_DISPLAY__:
//    define this symbol to disable application display
// __MTI_SAMPLE_DRAW_BOUNDING_BOX__:
//    define this symbol to display the Bézier curve's bounding box
// __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__:
//    define this symbol to display the Bézier curve's bounding box center
// __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__:
//    define this symbol to display visual guids when applying a 
//    transformation to the Bézier curve.
// __MTI_SAMPLE_INSTRUMENTED__:
//    define this symbol to activate instrumentation done using the
//    Intel(r) Energy Checker SDK.  If instrumentation is activated, also 
//    define the following symbols:
//       __PL_WINDOWS__
//       __PL_GENERATE_INI__
//       __PL_GENERATE_INI_VERSION_TAGGING__
//       __PL_GENERATE_INI_BUILD_TAGGING__
//       __PL_GENERATE_INI_DATE_AND_TIME_TAGGING__
//       __PL_BLOCKING_COUNTER_FILE_LOCK__
//       __PL_EXTRA_INPUT_CHECKS__
//   Please read to the Intel(r) Energy Checker SDK documentation for details.
// __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__:
//    define this symbol to control the metrics thread updates from a timer.
//    this will always give priority to the workload vs. instrumentation.  If
//    not defined, the metrics thread will automatically update the counters
// __MTI_SAMPLE_STI_TOUCH_CODE__:
//    define this symbol to activate the STI support code using touch messages.
// __MTI_SAMPLE_MTI_CODE__:
//    define this symbol to activate the MTI support code.
// __MTI_SAMPLE_MTI_TOUCH_CODE__:
//    define this symbol to activate touch messages.  Touch and gesture messages
//    are mutually exclusive.  By default, gesture messages are expected.
// __MTI_SAMPLE_GUI_MONITOR__:
//    define this symbol to have the sample start and stop a pl_gui_monitor
//    instance.
// __MTI_SAMPLE_POWER_AWARE__:
//    define this symbol to answer to system power suspend and resume messages.
// __MTI_SAMPLE_SENSORS_CODE__:
//    define this symbol to activate sensor code.
// __MTI_SAMPLE_LINEAR_COLOR_SCALE__:
//    define this symbol to select linear color scaling based on ALS sensor
//    readings.  By default a logarithmic scale is used.
//
// Note:
//    define _CRT_SECURE_NO_DEPRECATE to remove deprecation warnings.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// detect forbidden symbol configurations
//-----------------------------------------------------------------------------
#if defined(__MTI_SAMPLE_FILE_LOG__) && defined(__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)
	#error("NOTE: Building using __MTI_SAMPLE_FILE_LOG__ and __MTI_SAMPLE_PER_GESTURE_FILE_LOG__.")
#endif

#if defined(__MTI_SAMPLE_NO_DISPLAY__) && (defined(__MTI_SAMPLE_DRAW_BOUNDING_BOX__) || defined(__MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__) || defined(__MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__))
	#error("NOTE: Building using __MTI_SAMPLE_NO_DISPLAY__ and a drawing symbol defined.")
#endif

#if (defined(__MTI_SAMPLE_FILE_LOG__) || defined(__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)) && !defined(__MTI_SAMPLE_INSTRUMENTED__)
	#error("NOTE: Building using __MTI_SAMPLE_FILE_LOG__ or __MTI_SAMPLE_PER_GESTURE_FILE_LOG__ without __MTI_SAMPLE_INSTRUMENTED__.")
#endif

#if defined(__MTI_SAMPLE_STI_TOUCH_CODE__) && defined (__MTI_SAMPLE_MTI_CODE__)
	#error("NOTE: Building using __MTI_SAMPLE_STI_TOUCH_CODE__ and __MTI_SAMPLE_MTI_CODE__.")
#endif

//-----------------------------------------------------------------------------
// sample build configuration report
//-----------------------------------------------------------------------------
#ifdef _MSC_VER

	#pragma	message ("//-----------------------------------------------------------------------------")
	#pragma	message ("// MTI Sample Build configuration report.")
	#pragma	message ("//-----------------------------------------------------------------------------")

	//-------------------------------------------------------------------------
	// Generic build configuration reporting.
	//-------------------------------------------------------------------------
	#ifdef __MTI_SAMPLE_FILE_LOG__
			#pragma	message("NOTE: Building using __MTI_SAMPLE_FILE_LOG__.")
	#endif // __MTI_SAMPLE_FILE_LOG__

	#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_PER_GESTURE_FILE_LOG__.")
	#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__
	
	#ifdef __MTI_SAMPLE_NO_DISPLAY__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_NO_DISPLAY__.")
	#endif // __MTI_SAMPLE_NO_DISPLAY__
	
	#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_DRAW_BOUNDING_BOX__.")
	#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX__
	
	#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__.")
	#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__
	
	#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__.")
	#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__
	
	#ifdef __MTI_SAMPLE_INSTRUMENTED__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_INSTRUMENTED__.")
	#endif // __MTI_SAMPLE_INSTRUMENTED__
	
	#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__.")
	#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__
	
	#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_STI_TOUCH_CODE__.")
	#endif // __MTI_SAMPLE_STI_TOUCH_CODE__
	
	#ifdef __MTI_SAMPLE_MTI_CODE__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_MTI_CODE__.")
		#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__
			#pragma	message("NOTE: Building using __MTI_SAMPLE_MTI_TOUCH_CODE__.")
		#else // __MTI_SAMPLE_MTI_TOUCH_CODE__
			#pragma	message("NOTE: Building not using __MTI_SAMPLE_MTI_TOUCH_CODE__, gestures will be used.")
		#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__
	#endif // __MTI_SAMPLE_MTI_CODE__
	
	#ifdef __MTI_SAMPLE_GUI_MONITOR__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_GUI_MONITOR__.")
	#endif // __MTI_SAMPLE_GUI_MONITOR__
	
	#ifdef __MTI_SAMPLE_POWER_AWARE__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_POWER_AWARE__.")
	#endif // __MTI_SAMPLE_POWER_AWARE__

	#ifdef __MTI_SAMPLE_SENSORS_CODE__
		#pragma	message("NOTE: Building using __MTI_SAMPLE_SENSORS_CODE__.")
	#endif // __MTI_SAMPLE_SENSORS_CODE__


#endif // _MSC_VER

//-----------------------------------------------------------------------------
// headers include
//-----------------------------------------------------------------------------
#ifdef _DEBUG

	#include <crtdbg.h>
	#include <errno.h>

#endif // _DEBUG

#include <assert.h>
#include <tchar.h>
#include <math.h> // for sqrt
#include "mti_sample.h"

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	#include <io.h>
	#include <stdio.h>
	#include <direct.h> // for _getcwd 
	#include "productivity_link.h"
	#include "pub_esrv_counters.h"

#endif // __MTI_SAMPLE_INSTRUMENTED__

#ifdef __MTI_SAMPLE_SENSORS_CODE__

	#include "mti_sample_shared_data.h"

#endif // __MTI_SAMPLE_SENSORS_CODE__

#pragma comment (lib, "Rpcrt4") // for RPCFree

//-----------------------------------------------------------------------------
// Global shared variable
//-----------------------------------------------------------------------------
#ifdef __MTI_SAMPLE_SENSORS_CODE__
	MTI_SAMPLE_SHARED_DATA shared_data;
#endif // __MTI_SAMPLE_SENSORS_CODE__

#ifdef __MTI_SAMPLE_SENSORS_CODE__


/*-----------------------------------------------------------------------------
Function: re_initialize_graphic_data
Purpose : re create and initialize drawing data
In      : pointer to MTI graphic data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
10/11/2010    Jamel Tayeb             Creation.
*/
BOOL re_initialize_graphic_data(PMTI_SAMPLE_GRAPHIC_DATA p) {

	BOOL bret = FALSE;

	assert(p != NULL);

	bret = destroy_graphic_data(p);
	assert(bret == TRUE);
	bret = initialize_graphic_data(p);
	assert(bret == TRUE);

	return(TRUE);
}

#endif // __MTI_SAMPLE_SENSORS_CODE__

/*-----------------------------------------------------------------------------
Function: initialize_graphic_data
Purpose : create and initialize drawing data
In      : pointer to MTI graphic data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
*/
BOOL initialize_graphic_data(PMTI_SAMPLE_GRAPHIC_DATA p) {

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// clear graphic data structure	
	//-------------------------------------------------------------------------
	memset(
		p,
		0,
		sizeof(MTI_SAMPLE_GRAPHIC_DATA)
	);

	//-------------------------------------------------------------------------
	// create pen used to draw the Bézier curve
	//-------------------------------------------------------------------------
	p->bezier_curve_pen = CreatePen(
		MTI_SAMPLE_DEFAULT_LINE_STYLE,
		MTI_SAMPLE_BEZIER_CURVE_WIDTH,
		MTI_SAMPLE_BEZIER_CURVE_COLOR
	);
	assert(p->bezier_curve_pen != NULL);
	
	//-------------------------------------------------------------------------
	// create pen used to draw the control bars
	//-------------------------------------------------------------------------
	p->control_bar_pen = CreatePen(
		MTI_SAMPLE_DEFAULT_LINE_STYLE,
		MTI_SAMPLE_CONTROL_BAR_WIDTH,
		MTI_SAMPLE_CONTROL_BAR_COLOR
	);
	assert(p->control_bar_pen != NULL);
	
	//-------------------------------------------------------------------------
	// create brush & pen used to draw the control points
	//-------------------------------------------------------------------------
	p->control_point_brush = CreateSolidBrush(
		MTI_SAMPLE_CONTROL_POINT_COLOR
	);
	assert(p->control_point_brush != NULL);
	
	p->control_point_pen = CreatePen(
		MTI_SAMPLE_DEFAULT_LINE_STYLE,
		MTI_SAMPLE_DEFAULT_WIDTH,
		MTI_SAMPLE_CONTROL_POINT_OUTLINE_COLOR
	);
	assert(p->control_point_pen != NULL);
	
	//-------------------------------------------------------------------------
	// create brush & pen used to draw the anchor points
	//-------------------------------------------------------------------------
	p->anchor_point_brush = CreateSolidBrush(
		MTI_SAMPLE_ANCHOR_POINT_COLOR
	);
	assert(p->anchor_point_brush != NULL);
	
	p->anchor_point_pen = CreatePen(
		MTI_SAMPLE_DEFAULT_LINE_STYLE,
		MTI_SAMPLE_DEFAULT_WIDTH,
		MTI_SAMPLE_ANCHOR_POINT_OUTLINE_COLOR
	);
	assert(p->anchor_point_pen != NULL);

#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	//-------------------------------------------------------------------------
	// create brush & pen used to draw the bounding box center
	// Note:
	//   if displayed, the bounding box is drawn using a stock object.
	//-------------------------------------------------------------------------
	p->bbox_center_point_brush = CreateSolidBrush(
		MTI_SAMPLE_BBOX_CENTER_POINT_COLOR
	);
	assert(p->bbox_center_point_brush != NULL);
	
	p->bbox_center_point_pen = CreatePen(
	  MTI_SAMPLE_DEFAULT_LINE_STYLE,
	  MTI_SAMPLE_DEFAULT_WIDTH,
	  MTI_SAMPLE_BBOX_CENTER_POINT_OUTLINE_COLOR
	);
	assert(p->bbox_center_point_pen != NULL);

#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	//-------------------------------------------------------------------------
	// create brush & pen used to draw the transformations visual feedbacks
	//-------------------------------------------------------------------------
	p->feedback_brush = CreateSolidBrush(
		MTI_SAMPLE_FEEDBACK_COLOR
	);
	assert(p->feedback_brush != NULL);
	p->feedback_pen = CreatePen(
	  MTI_SAMPLE_FEEDBACK_LINE_STYLE,
	  MTI_SAMPLE_FEEDBACK_WIDTH,
	  MTI_SAMPLE_FEEDBACK_OUTLINE_COLOR
	);
	assert(p->feedback_pen != NULL);

	p->feedback_sweep_brush = CreateSolidBrush(
		MTI_SAMPLE_FEEDBACK_SWEEP_COLOR
	);
	assert(p->feedback_sweep_brush != NULL);
	p->feedback_sweep_pen = CreatePen(
	  MTI_SAMPLE_FEEDBACK_LINE_STYLE,
	  MTI_SAMPLE_FEEDBACK_WIDTH,
	  MTI_SAMPLE_FEEDBACK_SWEEP_OUTLINE_COLOR
	);
	assert(p->feedback_sweep_pen != NULL);

	p->feedback_translate_brush = CreateSolidBrush(
		MTI_SAMPLE_FEEDBACK_TRANSLATE_COLOR
	);
	assert(p->feedback_translate_brush != NULL);
	p->feedback_translate_pen = CreatePen(
	  MTI_SAMPLE_FEEDBACK_LINE_STYLE,
	  MTI_SAMPLE_FEEDBACK_WIDTH,
	  MTI_SAMPLE_FEEDBACK_TRANSLATE_OUTLINE_COLOR
	);
	assert(p->feedback_translate_pen != NULL);

#endif __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: initialize_interface_data
Purpose : initialize interface data
In      : pointer to MTI graphic data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
*/
extern BOOL initialize_interface_data(PMTI_SAMPLE_INTERFACE_DATA p, HWND hwnd) {

	BOOL bret = FALSE;

	assert(p != NULL);
	assert(hwnd != NULL);

	//-------------------------------------------------------------------------
	// clear interface data structure
	//-------------------------------------------------------------------------
	memset(
		p,
		0,
		sizeof(MTI_SAMPLE_INTERFACE_DATA)
	);

	//-------------------------------------------------------------------------
	// set non-zero default values
	//-------------------------------------------------------------------------
	p->hwnd = hwnd;

#if defined(__MTI_SAMPLE_NO_DISPLAY__) || defined(__MTI_SAMPLE_STI_TOUCH_CODE__) || defined(__MTI_SAMPLE_MTI_TOUCH_CODE__) || defined(__MTI_SAMPLE_MTI_CODE__) 

	//-------------------------------------------------------------------------
	// all these symbols requires a start in no-help mode
	//-------------------------------------------------------------------------
	p->f_in_help = FALSE;

#endif // __MTI_SAMPLE_MTI_CODE__ || __MTI_SAMPLE_STI_TOUCH_CODE__ || __MTI_SAMPLE_MTI_TOUCH_CODE__ || __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

	//-------------------------------------------------------------------------
	// set touch contact id tracking data
	//-------------------------------------------------------------------------
	bret = clear_touch_contact_ids(p);
	assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#endif // __MTI_SAMPLE_MTI_CODE__

	return(SUCCESS);
}

#ifdef __MTI_SAMPLE_INSTRUMENTED__

/*-----------------------------------------------------------------------------
Function: initialize_instrumentation_data
Purpose : initialize instrumentation data and open PL
In      : pointer to MTI instrumentation data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL initialize_instrumentation_data(PMTI_SAMPLE_INSTRUMENTATION_DATA p) {

	BOOL bret = FAILURE;
	static char application_name[] = MTI_SAMPLE_APPLICATION_NAME;
	const static char *counters_names[MTI_SAMPLE_COUNTERS_COUNT] = {
		MTI_SAMPLE_COUNTERS_NAMES
	};

#ifdef __MTI_SAMPLE_POWER_AWARE__

	size_t stret = 0;
	char *puuid = NULL;
	RPC_STATUS rret = RPC_S_OUT_OF_MEMORY;

#endif // __MTI_SAMPLE_POWER_AWARE__

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// clear instrumentation data structure
	//-------------------------------------------------------------------------
	memset(
		p,
		0,
		sizeof(MTI_SAMPLE_INSTRUMENTATION_DATA)
	);

	//-------------------------------------------------------------------------
	// attach to - or start - an ESRV PL
	//-------------------------------------------------------------------------
	bret = get_esrv_pld(p);
	assert(bret == SUCCESS);

	//-------------------------------------------------------------------------
	// set non-zero structure members
	//-------------------------------------------------------------------------
	p->status = RUNNING;
	p->pld = PL_INVALID_DESCRIPTOR;

	p->beziers_joules_decimals = 
		MTI_SAMPLE_DEFAULT_BEZIERS_JOULES_DECIMALS;
	p->translations_joules_decimals = 
		MTI_SAMPLE_DEFAULT_TRANSLATIONS_JOULES_DECIMALS;
	p->scales_joules_decimals = 
		MTI_SAMPLE_DEFAULT_SCALES_JOULES_DECIMALS;
	p->rotations_joules_decimals = 
		MTI_SAMPLE_DEFAULT_ROTATIONS_JOULES_DECIMALS;

	p->beziers_per_joule_decimals = 
		MTI_SAMPLE_DEFAULT_BEZIERS_PER_JOULE_DECIMALS;
	p->translations_per_joule_decimals = 
		MTI_SAMPLE_DEFAULT_TRANSLATIONS_PER_JOULE_DECIMALS;
	p->scales_per_joule_decimals = 
		MTI_SAMPLE_DEFAULT_SCALES_PER_JOULE_DECIMALS;
	p->rotations_per_joule_decimals = 
		MTI_SAMPLE_DEFAULT_ROTATIONS_PER_JOULE_DECIMALS;

	p->joules_per_bezier_decimals = 
		MTI_SAMPLE_DEFAULT_JOULES_PER_BEZIER_DECIMALS;
	p->joules_per_translation_decimals = 
		MTI_SAMPLE_DEFAULT_JOULES_PER_TRANSLATION_DECIMALS;
	p->joules_per_scale_decimals = 
		MTI_SAMPLE_DEFAULT_JOULES_PER_SCALE_DECIMALS;
	p->joules_per_rotation_decimals = 
		MTI_SAMPLE_DEFAULT_JOULES_PER_ROTATION_DECIMALS;

	p->ticks_per_bezier_decimals = 
		MTI_SAMPLE_DEFAULT_TICKS_PER_BEZIER_DECIMALS;
	p->ticks_per_translation_decimals = 
		MTI_SAMPLE_DEFAULT_TICKS_PER_TRANSLATION_DECIMALS;
	p->ticks_per_scale_decimals = 
		MTI_SAMPLE_DEFAULT_TICKS_PER_SCALE_DECIMALS;
	p->ticks_per_rotation_decimals = 
		MTI_SAMPLE_DEFAULT_TICKS_PER_ROTATION_DECIMALS;

	//-------------------------------------------------------------------------
	// open PL
	//-------------------------------------------------------------------------
	p->pld = pl_open(
		application_name,
		MTI_SAMPLE_COUNTERS_COUNT,
		counters_names,
		&p->uuid
	);
	assert(p->pld != PL_INVALID_DESCRIPTOR);

#ifdef __MTI_SAMPLE_POWER_AWARE__

	//-------------------------------------------------------------------------
	// unparse uuid
	//-------------------------------------------------------------------------
	rret = UuidToString(
		&p->uuid, 
		(RPC_WSTR *)&puuid
	);
	assert(rret == RPC_S_OK);
	wcstombs_s(
		&stret, 
		p->uuid_string, 
		sizeof(p->uuid_string), 
		(TCHAR *)puuid, 
		_TRUNCATE
	);
	rret = RpcStringFree((RPC_WSTR *)&puuid);
	assert(rret == RPC_S_OK);
	puuid = NULL;

#endif // __MTI_SAMPLE_POWER_AWARE__

	//-------------------------------------------------------------------------
	// initial update counters (including suffixes) and status counter
	//-------------------------------------------------------------------------
	bret = update_all_counters(p);
	assert(bret != FAILURE);

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: destroy_instrumentation_data
Purpose : close PL
In      : pointer to MTI instrumentation data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL destroy_instrumentation_data(PMTI_SAMPLE_INSTRUMENTATION_DATA p) {

	BOOL bret = FAILURE;
	PL_STATUS ret = PL_FAILURE;

	assert(p != NULL);
	assert(p->pld != PL_INVALID_DESCRIPTOR);

	//-------------------------------------------------------------------------
	// close PL
	//-------------------------------------------------------------------------
	ret = pl_close(p->pld);
	assert(ret == PL_SUCCESS);
	p->pld = PL_INVALID_DESCRIPTOR;

	//-------------------------------------------------------------------------
	// close - or kill and remove PL - of attached ESRV
	//-------------------------------------------------------------------------
	bret = remove_esrv(p);
	assert(bret == SUCCESS);

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: update_all_counters
Purpose : update all counters, including suffixes and status
In      : pointer to MTI instrumentation data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL update_all_counters(PMTI_SAMPLE_INSTRUMENTATION_DATA p) {

	BOOL bret = FAILURE;
	PL_STATUS ret = PL_FAILURE;

	assert(p != NULL);
	assert(p->pld != PL_INVALID_DESCRIPTOR);

	//-------------------------------------------------------------------------
	// update all counters and status counter.
	//-------------------------------------------------------------------------
	bret = update_all_non_suffix_counters(p);
	assert(bret != FAILURE);

	//-------------------------------------------------------------------------
	// update all suffix counters.
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	// update energy suffix counters
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->beziers_joules_decimals,
		ENERGY_CONSUMED_WHILE_DRAWING_BEZIER_CURVES_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->translations_joules_decimals,
		ENERGY_CONSUMED_WHILE_PERFORMING_TRANSLATIONS_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->scales_joules_decimals,
		ENERGY_CONSUMED_WHILE_PERFORMING_SCALEINGS_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->rotations_joules_decimals,
		ENERGY_CONSUMED_WHILE_PERFORMING_ROTATIONS_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// update energy-efficiency suffix counters
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->beziers_per_joule_decimals,
		BEZIER_CURVES_DRAWN_PER_JOULE_CONSUMMED_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->translations_per_joule_decimals,
		TRANSLATIONS_PERFORMED_PER_JOULE_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->scales_per_joule_decimals,
		SCALINGS_PERFORMED_PER_JOULE_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->rotations_per_joule_decimals,
		ROTATIONS_PERFORMED_PER_JOULE_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->joules_per_bezier_decimals,
		JOULES_CONUMED_PER_BEZIER_CURVE_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->joules_per_translation_decimals,
		JOULES_CONUMED_PER_TRANSLATION_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->joules_per_scale_decimals,
		JOULES_CONUMED_PER_SCALE_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->joules_per_rotation_decimals,
		JOULES_CONUMED_PER_ROTATION_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// update performance suffix counters
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->ticks_per_bezier_decimals,
		TICKS_ELAPSED_PER_BEZIER_CURVE_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->ticks_per_translation_decimals,
		TICKS_ELAPSED_PER_TRANSLATION_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->ticks_per_scale_decimals,
		TICKS_ELAPSED_PER_SCALE_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->ticks_per_rotation_decimals,
		TICKS_ELAPSED_PER_ROTATION_DECIMALS_INDEX
	);
	assert(ret == PL_SUCCESS);

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: update_all_non_suffix_counters
Purpose : update all counters (and status), excluding suffixes
In      : pointer to MTI instrumentation data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL update_all_non_suffix_counters(PMTI_SAMPLE_INSTRUMENTATION_DATA p) {

	PL_STATUS ret = PL_FAILURE;

	assert(p != NULL);
	assert(p->pld != PL_INVALID_DESCRIPTOR);

	//-------------------------------------------------------------------------
	// update counters (excluding suffixes) and status counter.
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	// update work counters
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->beziers,
		BEZIER_CURVES_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->beziers_drawn,
		BEZIER_CURVES_DRAWN_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->translations,
		TRANSLATIONS_PERFORMED_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->scales,
		SCALINGS_PERFORMED_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->rotations,
		ROTATIONS_PERFORMED_INDEX
	);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// update energy counters
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->beziers_joules,
		ENERGY_CONSUMED_WHILE_DRAWING_BEZIER_CURVES_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->translations_joules,
		ENERGY_CONSUMED_WHILE_PERFORMING_TRANSLATIONS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->scales_joules,
		ENERGY_CONSUMED_WHILE_PERFORMING_SCALEINGS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->rotations_joules,
		ENERGY_CONSUMED_WHILE_PERFORMING_ROTATIONS_INDEX
	);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// update timing counters
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->beziers_ticks,
		TICKS_ELAPSED_WHILE_DRAWING_BEZIER_CURVES_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->translations_ticks,
		TICKS_ELAPSED_WHILE_PERFORMING_TRANSLATIONS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->scales_ticks,
		TICKS_ELAPSED_WHILE_PERFORMING_SCALEINGS_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->rotations_ticks,
		TICKS_ELAPSED_WHILE_PERFORMING_ROTATIONS_INDEX
	);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// update energy-efficiency counters
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->beziers_per_joule,
		BEZIER_CURVES_DRAWN_PER_JOULE_CONSUMMED_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->translations_per_joule,
		TRANSLATIONS_PERFORMED_PER_JOULE_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->scales_per_joule,
		SCALINGS_PERFORMED_PER_JOULE_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->rotations_per_joule,
		ROTATIONS_PERFORMED_PER_JOULE_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->joules_per_bezier,
		JOULES_CONUMED_PER_BEZIER_CURVE_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->joules_per_translation,
		JOULES_CONUMED_PER_TRANSLATION_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->joules_per_scale,
		JOULES_CONUMED_PER_SCALE_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->joules_per_rotation,
		JOULES_CONUMED_PER_ROTATION_INDEX
	);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// update performance counters
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->ticks_per_bezier,
		TICKS_ELAPSED_PER_BEZIER_CURVE_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->ticks_per_translation,
		TICKS_ELAPSED_PER_TRANSLATION_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->ticks_per_scale,
		TICKS_ELAPSED_PER_SCALE_INDEX
	);
	assert(ret == PL_SUCCESS);

	ret = pl_write(
		p->pld,
		&p->ticks_per_rotation,
		TICKS_ELAPSED_PER_ROTATION_INDEX
	);
	assert(ret == PL_SUCCESS);

	//-------------------------------------------------------------------------
	// update status counter
	//-------------------------------------------------------------------------
	ret = pl_write(
		p->pld,
		&p->status,
		STATUS_INDEX
	);
	assert(ret == PL_SUCCESS);

	return(SUCCESS);
}

#endif // __MTI_SAMPLE_INSTRUMENTED__

/*-----------------------------------------------------------------------------
Function: destroy_graphic_data
Purpose : destroy graphic data
In      : pointer to MTI sample data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
*/
BOOL destroy_graphic_data(PMTI_SAMPLE_GRAPHIC_DATA p) {

	BOOL bret = FALSE;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// destroy pen used to draw the Bézier curve
	//-------------------------------------------------------------------------
	if(p->bezier_curve_pen != NULL) {
		bret = DeleteObject(p->bezier_curve_pen);
		assert(bret == TRUE);
		p->bezier_curve_pen = NULL;
	}

	//-------------------------------------------------------------------------
	// destroy pen used to draw the control bars
	//-------------------------------------------------------------------------
	if(p->control_bar_pen != NULL) {
		bret = DeleteObject(p->control_bar_pen);
		assert(bret == TRUE);
		p->control_bar_pen = NULL;
	}

	//-------------------------------------------------------------------------
	// destroy brush and pen used to draw the control points
	//-------------------------------------------------------------------------
	if(p->control_point_brush != NULL) {
		bret = DeleteObject(p->control_point_brush);
		assert(bret == TRUE);
		p->control_point_brush = NULL;
	}

	if(p->control_point_pen != NULL) {
		bret = DeleteObject(p->control_point_pen);
		assert(bret == TRUE);
		p->control_point_pen = NULL;
	}

	//-------------------------------------------------------------------------
	// destroy brush and pen used to draw the anchor points
	//-------------------------------------------------------------------------
	if(p->anchor_point_brush != NULL) {
		bret = DeleteObject(p->anchor_point_brush);
		assert(bret == TRUE);
		p->anchor_point_brush = NULL;
	}

	if(p->anchor_point_pen != NULL) {
		bret = DeleteObject(p->anchor_point_pen);
		assert(bret == TRUE);
		p->anchor_point_pen = NULL;
	}

#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	//-------------------------------------------------------------------------
	// destroy brush and pen used to draw the bounding box center
	//-------------------------------------------------------------------------
	if(p->bbox_center_point_brush != NULL) {
		bret = DeleteObject(p->bbox_center_point_brush);
		assert(bret == TRUE);
		p->bbox_center_point_brush = NULL;
	}

	if(p->bbox_center_point_pen != NULL) {
		bret = DeleteObject(p->bbox_center_point_pen);
		assert(bret == TRUE);
		p->bbox_center_point_pen = NULL;
	}

#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	//-------------------------------------------------------------------------
	// destroy brush and pen used to draw transformations visual feedbacks
	//-------------------------------------------------------------------------
	if(p->feedback_brush != NULL) {
		bret = DeleteObject(p->feedback_brush);
		assert(bret == TRUE);
		p->feedback_brush = NULL;
	}
	if(p->feedback_pen != NULL) {
		bret = DeleteObject(p->feedback_pen);
		assert(bret == TRUE);
		p->feedback_pen = NULL;
	}

	if(p->feedback_sweep_brush != NULL) {
		bret = DeleteObject(p->feedback_sweep_brush);
		assert(bret == TRUE);
		p->feedback_sweep_brush = NULL;
	}
	if(p->feedback_sweep_pen != NULL) {
		bret = DeleteObject(p->feedback_sweep_pen);
		assert(bret == TRUE);
		p->feedback_sweep_pen = NULL;
	}

	if(p->feedback_translate_brush != NULL) {
		bret = DeleteObject(p->feedback_translate_brush);
		assert(bret == TRUE);
		p->feedback_translate_brush = NULL;
	}
	if(p->feedback_translate_pen != NULL) {
		bret = DeleteObject(p->feedback_translate_pen);
		assert(bret == TRUE);
		p->feedback_translate_pen = NULL;
	}

#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: process_paint
Purpose : process WM_PAINT windows messages
In      : pointer to MTI sample data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
*/
BOOL process_paint(PMTI_SAMPLE_DATA p) {

	BOOL bret = FAILURE;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// errase background
	//-------------------------------------------------------------------------
	bret = draw_background(p);
	assert(bret == SUCCESS);

	if(p->interface_data.f_in_help == TRUE) {

		//---------------------------------------------------------------------
		// display help message
		//---------------------------------------------------------------------
		bret = draw_help_message(p);
		assert(bret == SUCCESS);
		goto process_paint_done;
	}

	if(p->geometry_data.points_count != 0) {

		//---------------------------------------------------------------------
		// draw the Bezier curve
		//---------------------------------------------------------------------
		bret = draw_bezier_curve(p);
		assert(bret == SUCCESS);

		//---------------------------------------------------------------------
		// draw the control bars
		//---------------------------------------------------------------------
		bret = draw_control_bars(p);
		assert(bret == SUCCESS);

		//---------------------------------------------------------------------
		// draw the anchor points
		//---------------------------------------------------------------------
		bret = draw_anchor_points(p);
		assert(bret == SUCCESS);

		//---------------------------------------------------------------------
		// draw the control points
		//---------------------------------------------------------------------
		bret = draw_control_points(p);
		assert(bret == SUCCESS);
	}

process_paint_done:

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: draw_background
Purpose : draw the background
In      : pointer to MTI sample data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
09/09/2010    Jamel Tayeb             Added support for MTI (gesture).
*/
extern BOOL draw_background(PMTI_SAMPLE_DATA p) {

	int ret = 0;
	BOOL bret = FAILURE;

#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__
	RECT rect = { 0, 0, 0, 0 };

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

#else //  __MTI_SAMPLE_MTI_TOUCH_CODE__

	double start_angle = 0.0;

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#endif // __MTI_SAMPLE_MTI_CODE__

#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

#if defined __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__ || __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	HGDIOBJ old_brush = NULL;
	HGDIOBJ old_pen = NULL;

#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__ || __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// errase background
	//-------------------------------------------------------------------------
	bret = GetClientRect(
		p->interface_data.hwnd, 
		&p->interface_data.rect
	);
	assert(bret = TRUE);
	ret = FillRect(
		p->graphic_data.in_memory_hdc,
		&p->interface_data.rect,
		(HBRUSH)GetStockObject(WHITE_BRUSH)
	);
	assert(bret != 0);

#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX__

	//-------------------------------------------------------------------------
	// draw bounding box
	//-------------------------------------------------------------------------
	if(p->geometry_data.points_count > 1) {
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&p->geometry_data.bbox,
			(HBRUSH)GetStockObject(LTGRAY_BRUSH)
		);
		assert(bret != 0);
	}

#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX__

#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	if(
		(p->interface_data.f_point_selected == TRUE) &&
		(p->interface_data.f_bbox_selected == FALSE)
	) {

		//---------------------------------------------------------------------
		// draw control point repositioning visual feedback
		//---------------------------------------------------------------------
		old_brush = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_translate_brush
		); 
		assert(old_brush != NULL);
		old_pen = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_translate_pen
		);			
		assert(old_pen != NULL);
		bret = MoveToEx(
			p->graphic_data.in_memory_hdc,
			p->interface_data.ref_points[
				p->interface_data.selected_point_index
			].x,			
			p->interface_data.ref_points[
				p->interface_data.selected_point_index
			].y,			
			NULL
		);
		assert(bret != FALSE);
		bret = LineTo(
			p->graphic_data.in_memory_hdc,
			p->interface_data.xpos,
			p->interface_data.ypos
		);
		assert(bret != FALSE);
		rect.left = 
			p->interface_data.ref_points[
				p->interface_data.selected_point_index
			].x - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.ref_points[
				p->interface_data.selected_point_index
			].y - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.ref_points[
				p->interface_data.selected_point_index
			].x + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.ref_points[
				p->interface_data.selected_point_index
			].y + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_translate_brush
		);
		assert(bret != 0);
		rect.left = 
			p->interface_data.xpos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.ypos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.xpos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.ypos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_translate_brush
		);
		assert(bret != 0);
		p->graphic_data.feedback_translate_brush = (HBRUSH)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_brush
		);
		assert(p->graphic_data.feedback_translate_brush != NULL);
		p->graphic_data.feedback_translate_pen = (HPEN)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_pen
		);
		assert(p->graphic_data.feedback_translate_pen != NULL);
	}

	if(
		(p->interface_data.transformation & ROTATE) &&
		(p->interface_data.f_bbox_selected == TRUE)
	) {

		/*
		@@@@@   @@@@   @@@@@   @@    @@@@@ @@@@@@           @
		@    @ @    @    @    @  @     @   @               @@
		@    @ @    @    @   @    @    @   @              @ @
		@@@@@  @    @    @   @    @    @   @@@@@@           @
		@  @   @    @    @   @@@@@@    @   @                @
		@   @  @    @    @   @    @    @   @                @
		@    @  @@@@     @   @    @    @   @@@@@@         @@@@@
		*/
		//---------------------------------------------------------------------
		// draw rotation transformation visual feedback, start with sweep angle
		//---------------------------------------------------------------------
		old_brush = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_sweep_brush
		); 
		assert(old_brush != NULL);
		old_pen = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_sweep_pen
		);			
		assert(old_pen != NULL);

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

		// TODO:

#else // __MTI_SAMPLE_MTI_TOUCH_CODE__

		start_angle = atan2(
			(double)p->interface_data.center.x, 
			(double)p->interface_data.center.y
		);
		bret = MoveToEx(
			p->graphic_data.in_memory_hdc,
			p->interface_data.center.x,
			p->interface_data.center.y,
			NULL
		);
		assert(bret != FALSE);
		bret = AngleArc(
			p->graphic_data.in_memory_hdc,
			p->interface_data.center.x,
			p->interface_data.center.y,
			MTI_SAMPLE_FEEDBACK_ROTATION_RADIUS,
			(float)(start_angle * MTI_SAMPLE_RADIAN_TO_DEGREE),
			(float)(
				p->interface_data.rotation_angle * MTI_SAMPLE_RADIAN_TO_DEGREE
			)
		);
		assert(bret != FALSE);
		bret = LineTo(
			p->graphic_data.in_memory_hdc,
			p->interface_data.center.x,
			p->interface_data.center.y
		);
		assert(bret != FALSE);

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#else // __MTI_SAMPLE_MTI_CODE__

		bret = Pie(
			p->graphic_data.in_memory_hdc,
			p->geometry_data.bbox.left,
			p->geometry_data.bbox.top,
			p->geometry_data.bbox.right,
			p->geometry_data.bbox.bottom,
			p->interface_data.ref_xpos,
			p->interface_data.ref_ypos,
			p->interface_data.xpos,
			p->interface_data.ypos
		);
		assert(bret != FALSE);

#endif // __MTI_SAMPLE_MTI_CODE__

		p->graphic_data.feedback_sweep_brush = (HBRUSH)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_brush
		);
		assert(p->graphic_data.feedback_sweep_brush != NULL);
		p->graphic_data.feedback_sweep_pen = (HPEN)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_pen
		);
		assert(p->graphic_data.feedback_sweep_pen != NULL);
	}

#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	//-------------------------------------------------------------------------
	// draw bounding box center
	//-------------------------------------------------------------------------
	if(p->geometry_data.points_count > 1) {
		old_brush = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.bbox_center_point_brush
		); 
		assert(old_brush != NULL);
		old_pen = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.bbox_center_point_pen
		);			
		assert(old_pen != NULL);
		ret = Ellipse(
			p->graphic_data.in_memory_hdc,
			p->geometry_data.bbox_center.x - 
			MTI_SAMPLE_BBOX_CENTER_POINT_HALF_RADIUS,
			p->geometry_data.bbox_center.y - 
			MTI_SAMPLE_BBOX_CENTER_POINT_HALF_RADIUS,
			p->geometry_data.bbox_center.x + 
			MTI_SAMPLE_BBOX_CENTER_POINT_HALF_RADIUS,
			p->geometry_data.bbox_center.y + 
			MTI_SAMPLE_BBOX_CENTER_POINT_HALF_RADIUS
		);
		assert(bret != 0);
		p->graphic_data.bbox_center_point_brush = (HBRUSH)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_brush
		);
		assert(p->graphic_data.bbox_center_point_brush != NULL);
		p->graphic_data.bbox_center_point_pen = (HPEN)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_pen
		);
		assert(p->graphic_data.bbox_center_point_pen != NULL);
	}

#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	/*
	@@@@@   @@@@   @@@@@   @@    @@@@@ @@@@@@          @@
	@    @ @    @    @    @  @     @   @              @  @
	@    @ @    @    @   @    @    @   @                 @
	@@@@@  @    @    @   @    @    @   @@@@@@           @
	@  @   @    @    @   @@@@@@    @   @               @
	@   @  @    @    @   @    @    @   @              @
	@    @  @@@@     @   @    @    @   @@@@@@         @@@@
	*/
	if(
		(p->interface_data.transformation & ROTATE) &&
		(p->interface_data.f_bbox_selected == TRUE)
	) {

		//---------------------------------------------------------------------
		// initiate the draw of rotation transformation visual feedback
		//---------------------------------------------------------------------
		old_brush = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_brush
		); 
		assert(old_brush != NULL);
		old_pen = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_pen
		);			
		assert(old_pen != NULL);

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

		// TODO:

#else // __MTI_SAMPLE_MTI_TOUCH_CODE__

		//---------------------------------------------------------------------
		// draw rotation center -- which is the center of the two fingers
		//---------------------------------------------------------------------
		rect.left = 
			p->interface_data.center.x - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.center.y - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.center.x + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.center.y + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_brush
		);
		assert(bret != 0);

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#else // __MTI_SAMPLE_MTI_CODE__

		//---------------------------------------------------------------------
		// draw first vector
		//---------------------------------------------------------------------
		bret = MoveToEx(
			p->graphic_data.in_memory_hdc,
			p->geometry_data.bbox_center.x,
			p->geometry_data.bbox_center.y,
			NULL
		);
		assert(bret != FALSE);
		bret = LineTo(
			p->graphic_data.in_memory_hdc,
			p->interface_data.ref_xpos,
			p->interface_data.ref_ypos
		);
		assert(bret != FALSE);

		//---------------------------------------------------------------------
		// draw second vector
		//---------------------------------------------------------------------
		bret = MoveToEx(
			p->graphic_data.in_memory_hdc,
			p->geometry_data.bbox_center.x,
			p->geometry_data.bbox_center.y,
			NULL
		);
		assert(bret != FALSE);
		bret = LineTo(
			p->graphic_data.in_memory_hdc,
			p->interface_data.xpos,
			p->interface_data.ypos
		);
		assert(bret != FALSE);

		//---------------------------------------------------------------------
		// draw rotation center -- which is the bounding box center
		//---------------------------------------------------------------------
		rect.left = 
			p->geometry_data.bbox_center.x - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->geometry_data.bbox_center.y - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->geometry_data.bbox_center.x + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->geometry_data.bbox_center.y + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_brush
		);
		assert(bret != 0);

		//---------------------------------------------------------------------
		// draw vectors edges
		//---------------------------------------------------------------------
		rect.left = 
			p->interface_data.ref_xpos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.ref_ypos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.ref_xpos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.ref_ypos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_brush
		);
		assert(bret != 0);
		rect.left = 
			p->interface_data.xpos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.ypos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.xpos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.ypos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_brush
		);
		assert(bret != 0);

#endif // __MTI_SAMPLE_MTI_CODE__

		//---------------------------------------------------------------------
		// finalyze draw of rotation transformation visual feedback
		//---------------------------------------------------------------------
		p->graphic_data.feedback_brush = (HBRUSH)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_brush
		);
		assert(p->graphic_data.feedback_brush != NULL);
		p->graphic_data.feedback_pen = (HPEN)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_pen
		);
		assert(p->graphic_data.feedback_pen != NULL);
	}

	/*
	 @@@@   @@@@    @@   @      @@@@@@
	@    @ @    @  @  @  @      @
	@      @      @    @ @      @
	 @@@@  @      @    @ @      @@@@@@
	     @ @      @@@@@@ @      @
	     @ @    @ @    @ @      @
	@@@@@   @@@@  @    @ @@@@@@ @@@@@@
	*/
	if(
		(p->interface_data.transformation & SCALE) &&
		(p->interface_data.f_bbox_selected == TRUE)
	) {

		//---------------------------------------------------------------------
		// draw scale transformation visual feedback
		// Note:
		//    when MTI is used, the visual feedback is limited to the center
		//    point between the two fingers
		//---------------------------------------------------------------------
		//---------------------------------------------------------------------
		// initiate the draw of scale transformation visual feedback
		//---------------------------------------------------------------------
		old_brush = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_brush
		); 
		assert(old_brush != NULL);
		old_pen = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_pen
		);			
		assert(old_pen != NULL);

#ifdef __MTI_SAMPLE_MTI_CODE__
		
#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

		// TODO:

#else // __MTI_SAMPLE_MTI_TOUCH_CODE__

		rect.left = 
			p->interface_data.center.x - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.center.y - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.center.x + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.center.y + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_brush
		);
		assert(bret != 0);

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#else // __MTI_SAMPLE_MTI_CODE__

		bret = LineTo(
			p->graphic_data.in_memory_hdc,
			p->interface_data.xpos,
			p->interface_data.ypos
		);
		assert(bret != FALSE);
		rect.left = 
			p->interface_data.ref_xpos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.ref_ypos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.ref_xpos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.ref_ypos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_brush
		);
		assert(bret != 0);
		rect.left = 
			p->interface_data.xpos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.ypos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.xpos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.ypos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_brush
		);
		assert(bret != 0);

#endif // __MTI_SAMPLE_MTI_CODE__ 

		//---------------------------------------------------------------------
		// finalyze draw of scale transformation visual feedback
		//---------------------------------------------------------------------
		p->graphic_data.feedback_brush = (HBRUSH)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_brush
		);
		assert(p->graphic_data.feedback_brush != NULL);
		p->graphic_data.feedback_pen = (HPEN)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_pen
		);
		assert(p->graphic_data.feedback_pen != NULL);
	}

	/*
	 @@@@@ @@@@@    @@   @    @  @@@@  @        @@    @@@@@ @@@@@@
	   @   @    @  @  @  @@   @ @    @ @       @  @     @   @
	   @   @    @ @    @ @ @  @ @      @      @    @    @   @
	   @   @@@@@  @    @ @ @  @  @@@@  @      @    @    @   @@@@@@
	   @   @  @   @@@@@@ @  @ @      @ @      @@@@@@    @   @
	   @   @   @  @    @ @   @@      @ @      @    @    @   @
	   @   @    @ @    @ @    @ @@@@@  @@@@@@ @    @    @   @@@@@@
	*/
	if(
		(p->interface_data.transformation & TRANSLATE) &&
		(p->interface_data.f_bbox_selected == TRUE)
	) {

		//---------------------------------------------------------------------
		// draw translation transformation visual feedback
		//---------------------------------------------------------------------
		old_brush = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_translate_brush
		); 
		assert(old_brush != NULL);
		old_pen = SelectObject(
			p->graphic_data.in_memory_hdc,
			p->graphic_data.feedback_translate_pen
		);			
		assert(old_pen != NULL);
		bret = MoveToEx(
			p->graphic_data.in_memory_hdc,
			p->interface_data.ref_xpos,
			p->interface_data.ref_ypos,
			NULL
		);
		assert(bret != FALSE);
		bret = LineTo(
			p->graphic_data.in_memory_hdc,
			p->interface_data.xpos,
			p->interface_data.ypos
		);
		assert(bret != FALSE);
		rect.left = 
			p->interface_data.ref_xpos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.ref_ypos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.ref_xpos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.ref_ypos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_translate_brush
		);
		assert(bret != 0);
		rect.left = 
			p->interface_data.xpos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.top = 
			p->interface_data.ypos - 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.right = 
			p->interface_data.xpos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		rect.bottom = 
			p->interface_data.ypos + 
			MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE
		;
		ret = FillRect(
			p->graphic_data.in_memory_hdc,
			&rect,
			p->graphic_data.feedback_translate_brush
		);
		assert(bret != 0);
		p->graphic_data.feedback_translate_brush = (HBRUSH)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_brush
		);
		assert(p->graphic_data.feedback_translate_brush != NULL);
		p->graphic_data.feedback_translate_pen = (HPEN)SelectObject(
			p->graphic_data.in_memory_hdc,
			old_pen
		);
		assert(p->graphic_data.feedback_translate_pen != NULL);
	}

#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: draw_anchor_points
Purpose : draw the anchor points
In      : pointer to MTI sample data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
BOOL draw_anchor_points(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;
	HGDIOBJ old_brush = NULL;
	HGDIOBJ old_pen = NULL;
	RECT rect = { 0, 0, 0, 0 };

	assert(p != NULL);

	if(p->geometry_data.points_count != 0) {

		//---------------------------------------------------------------------
		// draw the first anchor point - if any
		//---------------------------------------------------------------------
		if(p->geometry_data.points_count >= MTI_SAMPLE_FIRST_ANCHOR_PRESENT) {
			old_brush = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.anchor_point_brush
			); 
			assert(old_brush != NULL);
			old_pen = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.anchor_point_pen
			);			
			assert(old_pen != NULL);
			rect.bottom = 
				p->geometry_data.points[MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX].y + 
				MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE
			;
			rect.left =
				p->geometry_data.points[MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX].x - 
				MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE
			;
			rect.right =
				p->geometry_data.points[MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX].x + 
				MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE
			;
			rect.top =
				p->geometry_data.points[MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX].y - 
				MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE
			;
			bret = Rectangle(
				p->graphic_data.in_memory_hdc,
				rect.left,
				rect.top,
				rect.right,
				rect.bottom
			);
			assert(bret == TRUE);
			p->graphic_data.anchor_point_brush = (HBRUSH)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_brush
			);
			assert(p->graphic_data.anchor_point_brush != NULL);
			p->graphic_data.anchor_point_pen = (HPEN)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_pen
			);
			assert(p->graphic_data.anchor_point_pen != NULL);
		}

		//---------------------------------------------------------------------
		// draw the second anchor point - if any
		//---------------------------------------------------------------------
		if(p->geometry_data.points_count >= MTI_SAMPLE_SECOND_ANCHOR_PRESENT) {
			old_brush = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.anchor_point_brush
			); 
			assert(old_brush != NULL);
			old_pen = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.anchor_point_pen
			);			
			assert(old_pen != NULL);
			rect.bottom = 
				p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].y + 
				MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE
			;
			rect.left =
				p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].x - 
				MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE
			;
			rect.right =
				p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].x + 
				MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE
			;
			rect.top =
				p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].y - 
				MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE
			;
			bret = Rectangle(
				p->graphic_data.in_memory_hdc,
				rect.left,
				rect.top,
				rect.right,
				rect.bottom
			);
			assert(bret == TRUE);
			p->graphic_data.anchor_point_brush = (HBRUSH)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_brush
			);
			assert(p->graphic_data.anchor_point_brush != NULL);
			p->graphic_data.anchor_point_pen =  (HPEN)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_pen
			);
			assert(p->graphic_data.anchor_point_pen != NULL);
		}
	}

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: draw_control_points
Purpose : draw the control points
In      : pointer to MTI sample data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
BOOL draw_control_points(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;
	HGDIOBJ old_brush = NULL;
	HGDIOBJ old_pen = NULL;

	assert(p != NULL);

	if(p->geometry_data.points_count != 0) {

		//---------------------------------------------------------------------
		// draw the first control point - if any
		//---------------------------------------------------------------------
		if(p->geometry_data.points_count >= MTI_SAMPLE_FIRST_CONTROL_PRESENT) {
			old_brush = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.control_point_brush
			); 
			assert(old_brush != NULL);
			old_pen = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.control_point_pen
			);			
			assert(old_pen != NULL);
			bret = Ellipse(
				p->graphic_data.in_memory_hdc,
				p->geometry_data.points[MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX].x - 
					MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS,
				p->geometry_data.points[MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX].y - 
					MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS,
				p->geometry_data.points[MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX].x + 
					MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS,
				p->geometry_data.points[MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX].y + 
					MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS
			);
			assert(bret != FALSE);
			p->graphic_data.control_point_brush = (HBRUSH)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_brush
			);
			assert(p->graphic_data.control_point_brush != NULL);
			p->graphic_data.control_point_pen = (HPEN)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_pen
			);
			assert(p->graphic_data.control_point_pen != NULL);
		}

		//---------------------------------------------------------------------
		// draw the second control point - if any
		//---------------------------------------------------------------------
		if(p->geometry_data.points_count >= MTI_SAMPLE_SECOND_CONTROL_PRESENT) {
			old_brush = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.control_point_brush
			); 
			assert(old_brush != NULL);
			old_pen = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.control_point_pen
			);			
			assert(old_pen != NULL);
			bret = Ellipse(
				p->graphic_data.in_memory_hdc,
				p->geometry_data.points[MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX].x - 
					MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS,
				p->geometry_data.points[MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX].y - 
					MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS,
				p->geometry_data.points[MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX].x + 
					MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS,
				p->geometry_data.points[MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX].y + 
					MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS
			);
			assert(bret != FALSE);
			p->graphic_data.control_point_brush = (HBRUSH)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_brush
			);
			assert(p->graphic_data.control_point_brush != NULL);
			p->graphic_data.control_point_pen = (HPEN)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_pen
			);
			assert(p->graphic_data.control_point_pen != NULL);
		}
	}

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: draw_control_bars
Purpose : draw the control bars
In      : pointer to MTI sample data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
BOOL draw_control_bars(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;
	POINT point = { 0, 0 };
	HGDIOBJ old_pen = NULL;

	assert(p != NULL);

	if(p->geometry_data.points_count != 0) {

		//---------------------------------------------------------------------
		// draw the first control bar - if any
		//---------------------------------------------------------------------
		if(
			p->geometry_data.points_count >= 
			MTI_SAMPLE_FIRST_CONTROL_BAR_PRESENT
		) {
			old_pen = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.control_bar_pen
			);			
			assert(old_pen != NULL);
			bret = MoveToEx(
				p->graphic_data.in_memory_hdc,
				p->geometry_data.points[MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX].x,
				p->geometry_data.points[MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX].y,
				&point
			);
			assert(bret != FALSE);
			bret = LineTo(
				p->graphic_data.in_memory_hdc,
				p->geometry_data.points[MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX].x,
				p->geometry_data.points[MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX].y
			);
			assert(bret != FALSE);
			p->graphic_data.control_bar_pen = (HPEN)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_pen
			);
			assert(p->graphic_data.control_point_pen != NULL);
		}

		//---------------------------------------------------------------------
		// draw the second control bar - if any
		//---------------------------------------------------------------------
		if(
			p->geometry_data.points_count >= 
			MTI_SAMPLE_SECOND_CONTROL_BAR_PRESENT
		) {
			old_pen = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.control_bar_pen
			);			
			assert(old_pen != NULL);
			bret = MoveToEx(
				p->graphic_data.in_memory_hdc,
				p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].x,
				p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].y,
				&point
			);
			assert(bret != FALSE);
			bret = LineTo(
				p->graphic_data.in_memory_hdc,
				p->geometry_data.points[MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX].x,
				p->geometry_data.points[MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX].y
			);
			assert(bret != FALSE);
			p->graphic_data.control_bar_pen = (HPEN)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_pen
			);
			assert(p->graphic_data.control_point_pen != NULL);
		}
	}

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: draw_bezier_curve
Purpose : draw the Bézier curve
In      : pointer to MTI sample data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
BOOL draw_bezier_curve(PMTI_SAMPLE_DATA p) {

	LONG x = 0;
	LONG y = 0;
	LONG lastx = 0;
	LONG lasty = 0;
	POINT point = { 0, 0 };
	double i = 0.0;
	double d = 0.0;
	BOOL bret = FALSE;
	HGDIOBJ old_pen = NULL;

	assert(p != NULL);

	if(p->geometry_data.points_count != 0) {

		//---------------------------------------------------------------------
		// draw the Bézier curve - if any
		//---------------------------------------------------------------------
		if(p->geometry_data.points_count == MTI_SAMPLE_BEZIER_CURVE_PRESENT) {
			old_pen = SelectObject(
				p->graphic_data.in_memory_hdc,
				p->graphic_data.bezier_curve_pen
			);			
			assert(old_pen != NULL);

			//-----------------------------------------------------------------
			// draw the Bézier manually
			//-----------------------------------------------------------------
			d = 1.0 / p->geometry_data.steps;
			lastx = 
				p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].x;
			lasty = 
				p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].y;
			do {
				x = (LONG) (
					p->geometry_data.points[MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX].x * B1(i) +
					p->geometry_data.points[MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX].x * B2(i) +
					p->geometry_data.points[MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX].x * B3(i) +
					p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].x * B4(i)
				);
				y = (LONG)( 
					p->geometry_data.points[MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX].y * B1(i) +
					p->geometry_data.points[MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX].y * B2(i) +
					p->geometry_data.points[MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX].y * B3(i) +
					p->geometry_data.points[MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX].y * B4(i)
				);
				bret = MoveToEx(
					p->graphic_data.in_memory_hdc,
					lastx,
					lasty,
					&point
				);
				assert(bret != FALSE);
				bret = LineTo(
					p->graphic_data.in_memory_hdc,
					x,
					y
				);
				lastx = x;
				lasty = y;
				i += d;
			} while(i < 1.0);
			p->graphic_data.bezier_curve_pen = (HPEN)SelectObject(
				p->graphic_data.in_memory_hdc,
				old_pen
			);
			assert(p->graphic_data.bezier_curve_pen != NULL);
		}
	}

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// update instrumentation data
	//-------------------------------------------------------------------------
	if(p->geometry_data.points_count == MTI_SAMPLE_BEZIER_CURVE_PRESENT) {
		p->instrumentation_data.beziers_drawn++;
	}

#endif // __MTI_SAMPLE_INSTRUMENTED__

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: draw_help_message
Purpose : draw the help message
In      : pointer to MTI sample data structure
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
*/
BOOL draw_help_message(PMTI_SAMPLE_DATA p) {

	int ret = 0;
	RECT rect = { 0, 0, 0, 0 };
	COLORREF crefret = CLR_INVALID;
	BOOL bret = FALSE;
	TCHAR text[] = MTI_SAMPLE_HELP_MESSAGE_STRING;

	assert(p != NULL);

	bret = GetClientRect(
		p->interface_data.hwnd, 
		&rect
	);
	assert(bret = TRUE);
	ret = FillRect(
		p->graphic_data.in_memory_hdc,
		&rect,
		(HBRUSH)GetStockObject(GRAY_BRUSH)
	);
	assert(bret != 0);
	crefret = SetBkColor(
		p->graphic_data.in_memory_hdc,
		MTI_SAMPLE_HELP_BACKGROUND_COLOR
	);
	assert(crefret != CLR_INVALID);
	ret = DrawText(
		p->graphic_data.in_memory_hdc, 
		text, 
		ARRAYSIZE(text) - 1,
		&rect, 
		DT_TOP | DT_LEFT | DT_WORDBREAK | DT_END_ELLIPSIS
	);
	assert(bret != 0);

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: process_mouse_left_button_down
Purpose : process WM_LBUTTONDOWN windows messages
In      : pointer to MTI sample data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/16/2010    Jamel Tayeb             Added support for Intel(r) ECSDK.
*/
BOOL process_mouse_left_button_down(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// store mouse position in next point to store
	//-------------------------------------------------------------------------
	p->geometry_data.points[p->geometry_data.points_count].x = 
		p->interface_data.xpos;
	p->geometry_data.points[p->geometry_data.points_count].y = 
		p->interface_data.ypos;

	//-------------------------------------------------------------------------
	// increment points count
	//-------------------------------------------------------------------------
	p->geometry_data.points_count++;

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// update instrumentation data
	//-------------------------------------------------------------------------
	bret = update_bezier_instrumentation_data(p);
	assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_INSTRUMENTED__

	if(p->geometry_data.points_count > MTI_SAMPLE_MAX_POINTS) {

		//---------------------------------------------------------------------
		// the Bézier was completed, start a new one
		//---------------------------------------------------------------------
		bret = initialize_geometry_data(&p->geometry_data);
		assert(bret == SUCCESS);
	}

	//-------------------------------------------------------------------------
	// update bounding box
	//-------------------------------------------------------------------------
	if(p->geometry_data.points_count <= 1) {

		//---------------------------------------------------------------------
		// first point is the bounding box
		//---------------------------------------------------------------------
		p->geometry_data.bbox.left = p->interface_data.xpos;
		p->geometry_data.bbox.right = p->interface_data.xpos;
		p->geometry_data.bbox.top = p->interface_data.ypos;
		p->geometry_data.bbox.bottom = p->interface_data.ypos;

	} else {

		//---------------------------------------------------------------------
		// expand bounding box with next points
		//---------------------------------------------------------------------
		if(p->interface_data.xpos < p->geometry_data.bbox.left) {
			p->geometry_data.bbox.left = p->interface_data.xpos;
		}
		if(p->interface_data.xpos > p->geometry_data.bbox.right) {
			p->geometry_data.bbox.right = p->interface_data.xpos;
		}
		if(p->interface_data.ypos < p->geometry_data.bbox.top) {
			p->geometry_data.bbox.top = p->interface_data.ypos;
		}
		if(p->interface_data.ypos > p->geometry_data.bbox.bottom) {
			p->geometry_data.bbox.bottom = p->interface_data.ypos;
		}

		//---------------------------------------------------------------------
		// update bounding box center
		//---------------------------------------------------------------------
		p->geometry_data.bbox_center.x =
			p->geometry_data.bbox.left +
			(
				p->geometry_data.bbox.right -
				p->geometry_data.bbox.left
			) /
			2
		;
		p->geometry_data.bbox_center.y =
			p->geometry_data.bbox.top +
			(
				p->geometry_data.bbox.bottom -
				p->geometry_data.bbox.top
			) /
			2
		;
	}

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: process_mouse_right_button_down
Purpose : process WM_RBUTTONDOWN windows messages
In      : pointer to MTI sample data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
08/16/2010    Jamel Tayeb             Added support for Intel(r) ECSDK.
*/
BOOL process_mouse_right_button_down(PMTI_SAMPLE_DATA p) {

	unsigned int i = 0;

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	PL_STATUS ret = PL_FAILURE;

#endif // __MTI_SAMPLE_INSTRUMENTED__

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// search the selected point
	//-------------------------------------------------------------------------
	for(i = 0 ; i < p->geometry_data.points_count; i++) {
		if(
			(
				p->geometry_data.points[i].x < 
				(p->interface_data.xpos + MTI_SAMPLE_PROXIMITY)
			) &&
			(
				p->geometry_data.points[i].y < 
				(p->interface_data.ypos + MTI_SAMPLE_PROXIMITY)
			) &&
			(
				p->geometry_data.points[i].x > 
				(p->interface_data.xpos - MTI_SAMPLE_PROXIMITY)
			) &&
			(
				p->geometry_data.points[i].y > 
				(p->interface_data.ypos - MTI_SAMPLE_PROXIMITY)
			)
		) {

			p->interface_data.selected_point_index = i;
			p->interface_data.f_point_selected = TRUE;
			p->interface_data.transformation = IDENTITY;

#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

			//-----------------------------------------------------------------
			// remember the points reference coordinate for visual feedback
			//-----------------------------------------------------------------
			p->interface_data.ref_points[i].x = p->geometry_data.points[i].x;
			p->interface_data.ref_points[i].y = p->geometry_data.points[i].y;

#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

			goto process_mouse_right_button_down_done;
		}
	} // for

	//-------------------------------------------------------------------------
	// no point selected
	//-------------------------------------------------------------------------
	p->interface_data.selected_point_index = 0;
	p->interface_data.f_point_selected = FALSE;

	//-------------------------------------------------------------------------
	// in the bounding box?
	//-------------------------------------------------------------------------
	if(
		(p->interface_data.xpos < p->geometry_data.bbox.right) &&
		(p->interface_data.ypos < p->geometry_data.bbox.bottom) &&
		(p->interface_data.xpos > p->geometry_data.bbox.left) &&
		(p->interface_data.ypos > p->geometry_data.bbox.top)
	) {

		//---------------------------------------------------------------------
		// remember it and save reference data for visual feedback
		//---------------------------------------------------------------------
		p->interface_data.f_bbox_selected = TRUE;
		p->interface_data.ref_xpos = p->interface_data.xpos;
		p->interface_data.ref_ypos = p->interface_data.ypos;
		for(i = 0 ; i < p->geometry_data.points_count; i++) {
			p->interface_data.ref_points[i].x = p->geometry_data.points[i].x;
			p->interface_data.ref_points[i].y = p->geometry_data.points[i].y;
		}
		p->interface_data.ref_bbox.bottom = p->geometry_data.bbox.bottom;
		p->interface_data.ref_bbox.top = p->geometry_data.bbox.top;
		p->interface_data.ref_bbox.left = p->geometry_data.bbox.left;
		p->interface_data.ref_bbox.right = p->geometry_data.bbox.right;
		p->interface_data.ref_bbox_center.x = p->geometry_data.bbox_center.x;
		p->interface_data.ref_bbox_center.y = p->geometry_data.bbox_center.y;

	} else {
		p->interface_data.f_bbox_selected = FALSE;
	}

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// update instrumentation data
	//-------------------------------------------------------------------------
	if(p->interface_data.transformation & TRANSLATE) {

		//---------------------------------------------------------------------
		// update translation energy data
		//---------------------------------------------------------------------
		ret = pl_read(
			p->instrumentation_data.energy_data.esrv_pld,
			&p->instrumentation_data.translations_joules_start,
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		assert(ret == PL_SUCCESS);

		//---------------------------------------------------------------------
		// update translation timing data
		//---------------------------------------------------------------------
		p->instrumentation_data.translations_ticks_start = 
			(unsigned long long)GetTickCount()
		;
	}

	if(p->interface_data.transformation & SCALE) {

		//---------------------------------------------------------------------
		// update scale energy data
		//---------------------------------------------------------------------
		ret = pl_read(
			p->instrumentation_data.energy_data.esrv_pld,
			&p->instrumentation_data.scales_joules_start,
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		assert(ret == PL_SUCCESS);

		//---------------------------------------------------------------------
		// update scale timing data
		//---------------------------------------------------------------------
		p->instrumentation_data.scales_ticks_start = 
			(unsigned long long)GetTickCount()
		;
	}

	if(p->interface_data.transformation & ROTATE) {

		//---------------------------------------------------------------------
		// update rotation energy data
		//---------------------------------------------------------------------
		ret = pl_read(
			p->instrumentation_data.energy_data.esrv_pld,
			&p->instrumentation_data.rotations_joules_start,
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		assert(ret == PL_SUCCESS);

		//---------------------------------------------------------------------
		// update rotation timing data
		//---------------------------------------------------------------------
		p->instrumentation_data.rotations_ticks_start = 
			(unsigned long long)GetTickCount()
		;
	}

#endif // __MTI_SAMPLE_INSTRUMENTED__

process_mouse_right_button_down_done:

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: process_mouse_right_button_up
Purpose : process WM_RBUTTONUP windows messages
In      : pointer to MTI sample data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
08/16/2010    Jamel Tayeb             Added support for Intel(r) ECSDK.
*/
BOOL process_mouse_right_button_up(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;

	assert(p != NULL);

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// update instrumentation data
	//-------------------------------------------------------------------------
	bret = update_transformations_instrumentation_data(p);
	assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// reset interface data
	//-------------------------------------------------------------------------
	p->interface_data.selected_point_index = 0;
	p->interface_data.f_point_selected = FALSE;
	p->interface_data.f_bbox_selected = FALSE;
	p->interface_data.f_shift = FALSE;
	p->interface_data.f_control = FALSE;
	p->interface_data.transformation = IDENTITY;

	//-------------------------------------------------------------------------
	// force display redraw
	//-------------------------------------------------------------------------
	bret = InvalidateRect(
		p->interface_data.hwnd, 
		NULL, 
		TRUE
	);
	assert(bret == TRUE);

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: process_key_pressed
Purpose : process WM_KEYDOWN windows messages
          if space key is pressed, all the geometry data is cleared
In      : pointer to MTI sample data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
09/03/2010    Jamel Tayeb             Added STI support.
*/
BOOL process_key_pressed(PMTI_SAMPLE_DATA p) {

	BOOL bret = FAILURE;
	static BOOL f_mouse_visible = FALSE;

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	PL_STATUS ret = PL_FAILURE;

#endif // __MTI_SAMPLE_INSTRUMENTED__

	assert(p != NULL);

	switch(p->interface_data.key) {

		//---------------------------------------------------------------------
		// pressing the reset key, restarts the control points input sequence 
		//---------------------------------------------------------------------
		case MTI_SAMPLE_RESET_KEY:
			bret = initialize_geometry_data(&p->geometry_data);
			assert(bret == SUCCESS);

#ifdef __MTI_SAMPLE_INSTRUMENTED__

			//-----------------------------------------------------------------
			// update instrumentation data
			//-----------------------------------------------------------------
			bret = update_bezier_instrumentation_data(p);
			assert(bret == SUCCESS);
			bret = update_transformations_instrumentation_data(p);
			assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_INSTRUMENTED__

		break;

		//---------------------------------------------------------------------
		// pressing the help key displays a help message
		//---------------------------------------------------------------------
 		case MTI_SAMPLE_HELP_KEY:
			if(p->interface_data.f_in_help == FALSE) {
				p->interface_data.f_in_help = TRUE;
			}
			break;

		//---------------------------------------------------------------------
		// pressing the help escape key exits from displaying the help message
		//---------------------------------------------------------------------
		case MTI_SAMPLE_EXIT_HELP_KEY:
			if(p->interface_data.f_in_help == TRUE) {
				p->interface_data.f_in_help = FALSE;
			}
			break;
	 
#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

		//---------------------------------------------------------------------
		// pressing the SHIFT key
		//---------------------------------------------------------------------
 		case MTI_SAMPLE_SHIFT_KEY:
			p->interface_data.f_shift = TRUE;
			p->interface_data.transformation |= SCALE;
			break;

		//---------------------------------------------------------------------
		// pressing the CONTROL key
		//---------------------------------------------------------------------
 		case MTI_SAMPLE_CONTROL_KEY:
			p->interface_data.f_control = TRUE;
			p->interface_data.transformation |= ROTATE;
			break;

#endif // __MTI_SAMPLE_STI_TOUCH_CODE__
	
		default:
			if(f_mouse_visible == TRUE) {
				ShowCursor(FALSE);
				f_mouse_visible = FALSE;
			} else {
				ShowCursor(TRUE);
				f_mouse_visible = TRUE;
			}
	} // switch

	return(SUCCESS);
}

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__
/*-----------------------------------------------------------------------------
Function: process_key_depressed
Purpose : process WM_KEYUP windows messages
          if space key is pressed, all the geometry data is cleared
In      : pointer to MTI sample data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
09/03/2010    Jamel Tayeb             Creation.
*/
BOOL process_key_depressed(PMTI_SAMPLE_DATA p) {

	assert(p != NULL);

	switch(p->interface_data.key) {

		//---------------------------------------------------------------------
		// depressing the SHIFT key
		//---------------------------------------------------------------------
 		case MTI_SAMPLE_SHIFT_KEY:
			p->interface_data.f_shift = FALSE;
			p->interface_data.transformation = IDENTITY;
			break;

		//---------------------------------------------------------------------
		// depressing the CONTROL key
		//---------------------------------------------------------------------
 		case MTI_SAMPLE_CONTROL_KEY:
			p->interface_data.f_control = FALSE;
			p->interface_data.transformation = IDENTITY;
			break;
	
	} // switch

	return(SUCCESS);
}
#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

/*-----------------------------------------------------------------------------
Function: process_mouse_move
Purpose : process WM_MOUSEMOVE windows messages
In      : pointer to MTI sample data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
09/09/2010    Jamel Tayeb             Added support for MTI (gesture).
*/
BOOL process_mouse_move(PMTI_SAMPLE_DATA p) {
	
	LONG x = 0;
	LONG y = 0;
	LONG dx = 0;
	LONG dy = 0;
	double sx = 1.0;
	double sy = 1.0;
	double a = 0.0;
	double a1 = 0.0;
	double a2 = 0.0;
	double sa = 0.0;
	double ca = 0.0;
	unsigned int i = 0;
	POINT point = { 0, 0 };
	MTI_SAMPLE_QUADRANT qref = QUADRANT_UNDEFINED;
	MTI_SAMPLE_QUADRANT qpos = QUADRANT_UNDEFINED;

	assert(p != NULL);

	if(p->interface_data.f_point_selected == TRUE) {
		assert(
			p->interface_data.selected_point_index < 
			p->geometry_data.points_count
		);

		/*
		@    @ @@@@@  @@@@@    @@    @@@@@ @@@@@@
		@    @ @    @ @    @  @  @     @   @
		@    @ @    @ @    @ @    @    @   @
		@    @ @@@@@  @    @ @    @    @   @@@@@@
		@    @ @      @    @ @@@@@@    @   @
		@    @ @      @    @ @    @    @   @
		 @@@@  @      @@@@@  @    @    @   @@@@@@
		*/
		//---------------------------------------------------------------------
		// update selected point's coordinates
		//---------------------------------------------------------------------
		p->geometry_data.points[p->interface_data.selected_point_index].x = 
			p->interface_data.xpos;
		p->geometry_data.points[p->interface_data.selected_point_index].y = 
			p->interface_data.ypos;
		i = 0;
		goto process_mouse_move_done;
	}

	if(p->interface_data.f_bbox_selected == TRUE) {

		/*
		 @@@@   @@@@    @@   @      @@@@@@
		@    @ @    @  @  @  @      @
		@      @      @    @ @      @
		 @@@@  @      @    @ @      @@@@@@
		     @ @      @@@@@@ @      @
		     @ @    @ @    @ @      @
		@@@@@   @@@@  @    @ @@@@@@ @@@@@@
		*/
		if(p->interface_data.transformation & SCALE) {

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

			// TODO:

#else // __MTI_SAMPLE_MTI_TOUCH_CODE__
	
			//-----------------------------------------------------------------
			// use the scale coefficient provided by the gesture
			//-----------------------------------------------------------------
			sx = p->interface_data.scale_coefficient;
			sy = p->interface_data.scale_coefficient;

			//-----------------------------------------------------------------
			// scale control points
			//-----------------------------------------------------------------
			for(i = 0; i < p->geometry_data.points_count; i++) {
				x = 
					p->geometry_data.points[i].x - 
					p->interface_data.center.x
				;
				y = 
					p->geometry_data.points[i].y - 
					p->interface_data.center.y
				;
				p->geometry_data.points[i].x = (LONG)(
					(double)x * sx
				) + p->interface_data.center.x;
				p->geometry_data.points[i].y = (LONG)(
					(double)y * sy
				) + p->interface_data.center.y;
			} // for

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#else // __MTI_SAMPLE_MTI_CODE__

			//-----------------------------------------------------------------
			// compute scale coefficients
			//-----------------------------------------------------------------
			point.x = p->interface_data.ref_xpos;
			point.y = p->interface_data.ref_ypos;
			qref = find_quadrant(
				&p->interface_data.ref_bbox_center, 
				&point
			);
			point.x = p->interface_data.xpos;
			point.y = p->interface_data.ypos;
			qpos = find_quadrant(
				&p->interface_data.ref_bbox_center, 
				&point
			);
			assert(qref != QUADRANT_UNDEFINED);
			if((qref == QUADRANT1) && (qpos == QUADRANT1)) {
				if(p->interface_data.xpos != 0) {
					sx =
						(double)p->interface_data.ref_xpos / 
						(double)p->interface_data.xpos
					;
				} else {
					sx = 1.0;
				}
				if(p->interface_data.ypos != 0) {
					sy =
						(double)p->interface_data.ref_ypos /
						(double)p->interface_data.ypos
					;
				} else {
					sy = 1.0;
				}
			}
			if((qref == QUADRANT2) && (qpos == QUADRANT2)) {
				if(p->interface_data.ref_xpos != 0) {
					sx =
						(double)p->interface_data.xpos /
						(double)p->interface_data.ref_xpos 
					;
				} else {
					sx = 1.0;
				}
				if(p->interface_data.ypos != 0) {
					sy =
						(double)p->interface_data.ref_ypos /
						(double)p->interface_data.ypos
					;
				} else {
					sy = 1.0;
				}
			}
			if((qref == QUADRANT3) && (qpos == QUADRANT3)) {
				if(p->interface_data.ref_xpos != 0) {
					sx =
						(double)p->interface_data.xpos /
						(double)p->interface_data.ref_xpos 
					;
				} else {
					sx = 1.0;
				}
				if(p->interface_data.ref_ypos != 0) {
					sy =
						(double)p->interface_data.ypos /
						(double)p->interface_data.ref_ypos
					;
				} else {
					sy = 1.0;
				}
			}
			if((qref == QUADRANT4) && (qpos == QUADRANT4)) {
				if(p->interface_data.xpos != 0) {
					sx =
						(double)p->interface_data.ref_xpos /
						(double)p->interface_data.xpos
					;
				} else {
					sx = 1.0;
				}
				if(p->interface_data.ref_ypos != 0) {
					sy =
						(double)p->interface_data.ypos /
						(double)p->interface_data.ref_ypos
					;
				} else {
					sy = 1.0;
				}
			}
			if(
				(qref == QUADRANT_UNDEFINED) || 
				(qpos == QUADRANT_UNDEFINED)
			) {
				goto process_mouse_move_done;
			}

			//-----------------------------------------------------------------
			// scale control points
			//-----------------------------------------------------------------
			for(i = 0; i < p->geometry_data.points_count; i++) {
				x = 
					p->interface_data.ref_points[i].x - 
					p->geometry_data.bbox_center.x
				;
				y = 
					p->interface_data.ref_points[i].y - 
					p->geometry_data.bbox_center.y
				;
				p->geometry_data.points[i].x = (LONG)(
					(double)x * sx
				) + p->geometry_data.bbox_center.x;
				p->geometry_data.points[i].y = (LONG)(
					(double)y * sy
				) + p->geometry_data.bbox_center.y;
			} // for

#endif // __MTI_SAMPLE_MTI_CODE__

			i = 0;
			goto process_mouse_move_done;
		}

		/*
		@@@@@   @@@@   @@@@@   @@    @@@@@ @@@@@@
		@    @ @    @    @    @  @     @   @
		@    @ @    @    @   @    @    @   @
		@@@@@  @    @    @   @    @    @   @@@@@@
		@  @   @    @    @   @@@@@@    @   @
		@   @  @    @    @   @    @    @   @
		@    @  @@@@     @   @    @    @   @@@@@@
		*/
		if(p->interface_data.transformation & ROTATE) {

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

			// TODO:

#else // __MTI_SAMPLE_MTI_TOUCH_CODE__
	
			//-----------------------------------------------------------------
			// use the rotation angle provided by the gesture
			// Note:
			//    note the sign change to the angle so the rotation accurately
			//    represents the gesture.
			//-----------------------------------------------------------------
			a = -p->interface_data.rotation_angle; // negative sign!
			a *= MTI_SAMPLE_ROTATIONS_ACCELERATOR;
			sa = sin(a);
			ca = cos(a);

			//-----------------------------------------------------------------
			// scale control points
			//-----------------------------------------------------------------
			for(i = 0; i < p->geometry_data.points_count; i++) {
				x = 
					p->interface_data.ref_points[i].x - 
					p->interface_data.center.x
				;
				y = 
					p->interface_data.ref_points[i].y - 
					p->interface_data.center.y
				;
				p->geometry_data.points[i].x = (LONG)(
					(double)x * ca -
					(double)y * sa
				) + p->interface_data.center.x;
				p->geometry_data.points[i].y = (LONG)(
					(double)y * ca +
					(double)x * sa
				) + p->interface_data.center.y;
			} // for

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#else // __MTI_SAMPLE_MTI_CODE__

			//-----------------------------------------------------------------
			// compute rotation angle
			//-----------------------------------------------------------------
			point.x = p->interface_data.ref_xpos;
			point.y = p->interface_data.ref_ypos;
			qref = find_quadrant(
				&p->interface_data.ref_bbox_center, 
				&point
			);
			assert(qref != QUADRANT_UNDEFINED);
			point.x = p->interface_data.xpos;
			point.y = p->interface_data.ypos;
			qpos = find_quadrant(
				&p->interface_data.ref_bbox_center, 
				&point
			);
			assert(qref != QUADRANT_UNDEFINED);
			a1 = atan2(
				(double)p->interface_data.ref_xpos, 
				(double)p->interface_data.ref_ypos
			);
			a2 = atan2(
				(double)p->interface_data.xpos, 
				(double)p->interface_data.ypos
			);
			if(qref == qpos) {
				if(qref != QUADRANT1) {
					a =  a1 - a2;
				} else {
					a = -(a1 - a2);
				}
			} else {
				if(
					(qref == QUADRANT1) &&
					(qpos == QUADRANT2)
				) {
					a = a2 - a1;
				}
				if(
					(qref == QUADRANT2) &&
					(qpos == QUADRANT3)
				) {
					;
				}
				if(
					(qref == QUADRANT3) &&
					(qpos == QUADRANT4)
				) {
					;
				}
				if(
					(qref == QUADRANT4) &&
					(qpos == QUADRANT1)
				) {
					;
				}
			}
			a *= MTI_SAMPLE_ROTATIONS_ACCELERATOR;
			sa = sin(a);
			ca = cos(a);

			//-----------------------------------------------------------------
			// rotate control points
			//-----------------------------------------------------------------
			for(i = 0; i < p->geometry_data.points_count; i++) {
				x = 
					p->interface_data.ref_points[i].x - 
					p->geometry_data.bbox_center.x
				;
				y = 
					p->interface_data.ref_points[i].y - 
					p->geometry_data.bbox_center.y
				;
				p->geometry_data.points[i].x = (LONG)(
					(double)x * ca -
					(double)y * sa
				) + p->geometry_data.bbox_center.x;
				p->geometry_data.points[i].y = (LONG)(
					(double)y * ca +
					(double)x * sa
				) + p->geometry_data.bbox_center.y;
			} // for

#endif // __MTI_SAMPLE_MTI_CODE__
			
			i = 0;
			goto process_mouse_move_done;
		} // for

		/*
		 @@@@@ @@@@@    @@   @    @  @@@@  @        @@    @@@@@ @@@@@@
		   @   @    @  @  @  @@   @ @    @ @       @  @     @   @
		   @   @    @ @    @ @ @  @ @      @      @    @    @   @
		   @   @@@@@  @    @ @ @  @  @@@@  @      @    @    @   @@@@@@
		   @   @  @   @@@@@@ @  @ @      @ @      @@@@@@    @   @
		   @   @   @  @    @ @   @@      @ @      @    @    @   @
		   @   @    @ @    @ @    @ @@@@@  @@@@@@ @    @    @   @@@@@@
		*/
		//---------------------------------------------------------------------
		// compute translation
		// Note:
		//    STI keyboard use do not use TRANSLATE transformation (it is 
		//    implicit) so it is never set - therefore the removal of the 
		//    assert.
		//---------------------------------------------------------------------
#ifndef __MTI_SAMPLE_STI_TOUCH_CODE__
		
		assert(p->interface_data.transformation & TRANSLATE);

#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

		dx = p->interface_data.ref_xpos - p->interface_data.xpos;
		dy = p->interface_data.ref_ypos - p->interface_data.ypos;

		//---------------------------------------------------------------------
		// translate control points
		//---------------------------------------------------------------------
		for(i = 0; i < p->geometry_data.points_count; i++) {
			p->geometry_data.points[i].x = 
				p->interface_data.ref_points[i].x - dx;
			p->geometry_data.points[i].y = 
				p->interface_data.ref_points[i].y - dy;
		} // for
	}

process_mouse_move_done:

	//-------------------------------------------------------------------------
	// update bounding box
	//-------------------------------------------------------------------------
	i = 0;
	p->geometry_data.bbox.left = p->geometry_data.points[i].x;
	p->geometry_data.bbox.right = p->geometry_data.points[i].x;
	p->geometry_data.bbox.top = p->geometry_data.points[i].y;
	p->geometry_data.bbox.bottom = p->geometry_data.points[i].y;
	do {
		if(
			p->geometry_data.points[i].x < 
			p->geometry_data.bbox.left
		) {
			p->geometry_data.bbox.left = 
				p->geometry_data.points[i].x
			;
		}
		if(
			p->geometry_data.points[i].x > 
			p->geometry_data.bbox.right
		) {
			p->geometry_data.bbox.right = 
				p->geometry_data.points[i].x
			;
		}
		if(
			p->geometry_data.points[i].y < 
			p->geometry_data.bbox.top
		) {
			p->geometry_data.bbox.top = 
				p->geometry_data.points[i].y
			;
		}
		if(
			p->geometry_data.points[i].y > 
			p->geometry_data.bbox.bottom
		) {
			p->geometry_data.bbox.bottom = 
				p->geometry_data.points[i].y
			;
		}
	} while(++i < p->geometry_data.points_count);

	//-------------------------------------------------------------------------
	// update bounding box center
	//-------------------------------------------------------------------------
	p->geometry_data.bbox_center.x =
		p->geometry_data.bbox.left +
		(
			p->geometry_data.bbox.right -
			p->geometry_data.bbox.left
		) /
		2
	;
	p->geometry_data.bbox_center.y =
		p->geometry_data.bbox.top +
		(
			p->geometry_data.bbox.bottom -
			p->geometry_data.bbox.top
		) /
		2
	;

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: process_destroy
Purpose : process WM_CLOSE windows messages
In      : pointer to MTI sample data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/16/2010    Jamel Tayeb             Added instrumentation.
*/
BOOL process_destroy(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;
	DWORD dwret = 0;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// release graphic ressources
	//-------------------------------------------------------------------------
	bret = destroy_graphic_data(&p->graphic_data);
	assert(bret == SUCCESS);

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// prepare for ending
	//-------------------------------------------------------------------------
	p->instrumentation_data.status = NOT_RUNNING;

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	//-------------------------------------------------------------------------
	// fire the metrics thread
	//-------------------------------------------------------------------------
	if(
		p->instrumentation_data.metrics_thread_update_event !=
		NULL
	) {
		bret = SetEvent(
			p->instrumentation_data.metrics_thread_update_event
		);
		assert(bret != FALSE);
	}

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	//-------------------------------------------------------------------------
	// update counters (excluding suffixes).  This allows us to keep latest 
	// counter data as accurate as possible.
	//-------------------------------------------------------------------------
	bret = update_all_non_suffix_counters(&p->instrumentation_data);
	assert(bret == SUCCESS);

#ifdef __MTI_SAMPLE_GUI_MONITOR__

	//-----------------------------------------------------------------
	// stop a pl_gui_monitor instance
	//-----------------------------------------------------------------
	bret = stop_pl_gui_monitor(p);
	assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_GUI_MONITOR__

	//-------------------------------------------------------------------------
	// wait until the metrics thread has ended
	//-------------------------------------------------------------------------
	if(
		p->instrumentation_data.metrics_thread_stoped_event	!=
		NULL
	) {
		dwret = WaitForSingleObject(
			p->instrumentation_data.metrics_thread_stoped_event,
			INFINITE
		);
		assert(dwret == WAIT_OBJECT_0);
	}

	//-------------------------------------------------------------------------
	// destroy instrumentation data
	//-------------------------------------------------------------------------
	bret = destroy_instrumentation_data(&p->instrumentation_data);
	assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_INSTRUMENTED__

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: initialize_geometry_data
Purpose : initialize geometry dataset
In      : pointer to MTI_SAMPLE_GEOMETRY_DATA data structure
Out     : modified data structure
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
BOOL initialize_geometry_data(PMTI_SAMPLE_GEOMETRY_DATA p) {

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// clear geometry data
	//-------------------------------------------------------------------------
	memset(
		p,
		0,
		sizeof(MTI_SAMPLE_GEOMETRY_DATA)
	);

	//-------------------------------------------------------------------------
	// set non-zero data 
	//-------------------------------------------------------------------------
	p->steps = MTI_SAMPLE_DEFAULT_STEPS;

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: find_quadrant
Purpose : find, based on the reference point, in wich quadrant the given point
          is
In      : pointer to the reference point and point of interest
Out     : none
Return  : quadrant

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/15/2010    Jamel Tayeb             Creation.
*/
MTI_SAMPLE_QUADRANT find_quadrant(PPOINT pref, PPOINT pp) {

	MTI_SAMPLE_QUADRANT q = QUADRANT_UNDEFINED;

	assert(pref != NULL);
	assert(pp != NULL);

	//-------------------------------------------------------------------------
	// (0,0)
	//  +-------------+-------------+
	//  |             |             |
	//  | QUADRANT 1  | QUADRANT 2  |
	//  |             |             | 
	//  +-------------+-------------+ 
	//  |             |             |
	//  | QUADRANT 4  | QUADRANT 3  |
	//  |             |             | 
	//  +-------------+-------------+ 
	//-------------------------------------------------------------------------
	if(
		(pp->x < pref->x) &&
		(pp->y < pref->y)
	) {
		q = QUADRANT1;
		goto find_quadrant_done;
	}
	if(
		(pp->x > pref->x) &&
		(pp->y < pref->y)
	) {
		q = QUADRANT2;
		goto find_quadrant_done;
	}
	if(
		(pp->x > pref->x) &&
		(pp->y > pref->y)
	) {
		q = QUADRANT3;
		goto find_quadrant_done;
	}
	if(
		(pp->x < pref->x) &&
		(pp->y > pref->y)
	) {
		q = QUADRANT4;
	}

find_quadrant_done:
	return(q);
}

/*-----------------------------------------------------------------------------
Function: window_class_procedure
Purpose : messages loop function
In      : usual Windows stuff
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
08/15/2010    Jamel Tayeb             Added support for simulated MTIs.
08/16/2010    Jamel Tayeb             Added support for Intel(r) ECSDK.
08/21/2010    Jamel Tayeb             Added MTI support.
08/22/2010    Jamel Tayeb             Added file logging support.
09/02/2010    Jamel Tayeb             Added power awarness.
09/03/2010    Jamel Tayeb             Added explicit STI touch support.
10/11/2010    Jamel Tayeb             Added sensor support (ALS example).
*/
LRESULT CALLBACK window_class_procedure(
	HWND hwnd, 
	UINT message,
	WPARAM wparam,
	LPARAM lparam
) {

	//-------------------------------------------------------------------------
	// generic variables
	//-------------------------------------------------------------------------
	int ret = 0;
	BOOL bret = FALSE;
	BOOL f_handled = FALSE;
	LRESULT return_value = FALSE;
	static MTI_SAMPLE_DATA data;

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef _DEBUG
	
		TCHAR buffer[MAX_PATH] = { '\0' };
		TCHAR buffer2[MAX_PATH] = { '\0' };
		
#endif // _DEBUG

#endif // __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

	//-------------------------------------------------------------------------
	// variables used to handle touch inputs
	//-------------------------------------------------------------------------
	UINT i = 0;
	size_t memory_size = 0;
	PTOUCHINPUT touch_input = NULL;

#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

	//-------------------------------------------------------------------------
	// variables used to handle touch inputs
	//-------------------------------------------------------------------------
	UINT i = 0;
	size_t memory_size = 0;
	PTOUCHINPUT touch_input = NULL;

#else // __MTI_SAMPLE_MTI_TOUCH_CODE__

	//-------------------------------------------------------------------------
	// variables used to handle gesture inputs
	//-------------------------------------------------------------------------
	UINT gestures_count = MTI_SAMPLE_DEFAULT_GESTURES_COUNT;
	GESTURECONFIG gesture_config[] = MTI_SAMPLE_DEFAULT_GESTURES;

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#endif // __MTI_SAMPLE_MTI_CODE__

	switch(message) {

		/*
		@@@@@  @@@@@@  @@@@  @@@@@  @    @
		@    @ @      @    @   @    @@   @
		@    @ @      @        @    @ @  @
		@@@@@  @@@@@@ @        @    @ @  @
		@    @ @      @  @@@   @    @  @ @
		@    @ @      @    @   @    @   @@
		@@@@@  @@@@@@  @@@@  @@@@@  @    @
		*/
		//---------------------------------------------------------------------
		// WM user send from WinMain
		//---------------------------------------------------------------------
		case WM_USER:

#if defined (__MTI_SAMPLE_FILE_LOG__) || defined (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

			//-----------------------------------------------------------------
			// open log file
			//-----------------------------------------------------------------
			data.log_file = fopen(
				MTI_SAMPLE_LOG_FILE_NAME, 
				MTI_SAMPLE_LOG_FILE_ACCESS
			);
			assert(data.log_file != NULL);

#endif // (__MTI_SAMPLE_FILE_LOG__) || (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

			//-----------------------------------------------------------------
			// initialize once the all data structures used by the application
			//-----------------------------------------------------------------
			bret = initialize_geometry_data(&data.geometry_data);
			assert(bret == SUCCESS);
			bret = initialize_graphic_data(&data.graphic_data);
			assert(bret == SUCCESS);
			bret = initialize_interface_data(
				&data.interface_data, 
				hwnd
			);
			assert(bret == SUCCESS);

#ifdef __MTI_SAMPLE_INSTRUMENTED__

			//-----------------------------------------------------------------
			// initialize instrumentation data
			//-----------------------------------------------------------------
			bret = initialize_instrumentation_data(
				&data.instrumentation_data
			);
			assert(bret == SUCCESS);
			bret = start_metrics_thread(&data);
			assert(bret == SUCCESS);

#ifdef __MTI_SAMPLE_GUI_MONITOR__

			//-----------------------------------------------------------------
			// start a pl_gui_monitor instance
			//-----------------------------------------------------------------
			bret = start_pl_gui_monitor(&data);
			assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_GUI_MONITOR__

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

			//-----------------------------------------------------------------
			// setup metrics thread's activation timer
			//-----------------------------------------------------------------
			data.instrumentation_data.hwnd = hwnd;
			bret = start_timer(&data);
			assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

#endif // __MTI_SAMPLE_INSTRUMENTED__

#if defined(__MTI_SAMPLE_NO_DISPLAY__) || defined(__MTI_SAMPLE_STI_TOUCH_CODE__) || defined(__MTI_SAMPLE_MTI_TOUCH_CODE__) || defined(__MTI_SAMPLE_MTI_CODE__) 

			//----------------------------------------------------------------
			// all these symbols requires us to hide the mouse pointer
			//----------------------------------------------------------------	
			ShowCursor(FALSE);

#endif // __MTI_SAMPLE_MTI_CODE__ || __MTI_SAMPLE_STI_TOUCH_CODE__ || __MTI_SAMPLE_MTI_TOUCH_CODE__ || __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_SENSORS_CODE__

			//-----------------------------------------------------------------
			// setup data for sensor update notification(s)
			//-----------------------------------------------------------------
			memset(
				&shared_data,
				0,
				sizeof(MTI_SAMPLE_SHARED_DATA)
			);
			shared_data.hwnd = hwnd;

			//-----------------------------------------------------------------
			// attach to an ALS sensor
			// Note:
			//    we do not test the BOOL return value of the 
			//    connect_to_an_als_sensor function since if no ALS sensor is 
			//    available, we decided to go with an average lux value of 
			//    0.5 (DEFAULT_LUX_VALUE).
			// Note:
			//    the sensor's current reading is collectd on successfull
			//    attachement, this is why we need to re-initialize the
			//    graphic objects so we can use the right parameters
			//    as soon as we start.
			//-----------------------------------------------------------------
			connect_to_an_als_sensor();
			shared_data.light_coefficient = NORMALIZE_LUX(shared_data.lux);
			bret = re_initialize_graphic_data(&data.graphic_data);
			assert(bret == TRUE);

#endif // __MTI_SAMPLE_SENSORS_CODE__

			f_handled = TRUE;
			break;

#ifdef __MTI_SAMPLE_INSTRUMENTED__

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

		//---------------------------------------------------------------------
		// metrics thread's timer tick
		// Note:
		//    we are not checking the timer id since only one timer is used
		//---------------------------------------------------------------------
		case WM_TIMER:
			bret = SetEvent(
				data.instrumentation_data.metrics_thread_update_event
			);
			assert(bret != FALSE);
			f_handled = TRUE;
			break;

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

#endif // __MTI_SAMPLE_INSTRUMENTED__

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

		/*
		 @@@@   @@@@@ @@@@@
		@    @    @     @
		@         @     @
		 @@@@     @     @
		     @    @     @
		     @    @     @
		@@@@@     @   @@@@@
		*/
		//---------------------------------------------------------------------
		// STI touch message
		//---------------------------------------------------------------------
		case WM_TOUCH:

			//-----------------------------------------------------------------
			// allocate memory to store touch inputs
			//-----------------------------------------------------------------
			data.interface_data.touch_inputs_count = LOWORD(wparam);
			memory_size = 
				sizeof(TOUCHINPUT) * 
				data.interface_data.touch_inputs_count
			;
			data.interface_data.touch_inputs = (PTOUCHINPUT)malloc(memory_size);
			assert(data.interface_data.touch_inputs != NULL);

			//-----------------------------------------------------------------
			// get touch inputs
			//-----------------------------------------------------------------
			bret = GetTouchInputInfo(
				(HTOUCHINPUT)lparam,
				data.interface_data.touch_inputs_count,
				data.interface_data.touch_inputs,
				sizeof(TOUCHINPUT)
			);
			assert(bret != FALSE);

			//-----------------------------------------------------------------
			// process touch inputs
			//-----------------------------------------------------------------
			for(i = 0; i < data.interface_data.touch_inputs_count; i++) {

				//-------------------------------------------------------------
				// process each touch input in sequence
				//-------------------------------------------------------------
				touch_input = &data.interface_data.touch_inputs[i];
				if(touch_input->dwFlags & TOUCHEVENTF_DOWN) {

					//---------------------------------------------------------
					// touch event is used as a left and right mouse button 
					// down messages replacement.  the logic used is the fol-
					// lowing: if any object is selected, then it is a right 
					// button, otherwise, it is a left button.
					// Note:
					//    we still check that we are not in help mode
					// Note:
					//    the x, y position of a touch is given in hundredths 
					//    of physical pixels.
					//---------------------------------------------------------
					if(data.interface_data.f_in_help == FALSE) {

						//-----------------------------------------------------
						// retrive x & y of the touch input 
						//-----------------------------------------------------
						data.interface_data.xpos = touch_input->x / 100;
						data.interface_data.ypos = touch_input->y / 100;

						//-----------------------------------------------------
						// process the touch as a right mouse button down to
						// detect if an existing - displayed or not - object
						// was selected by the touch input
						//-----------------------------------------------------
						bret = process_mouse_right_button_down(&data);
						assert(bret == SUCCESS);

						//-----------------------------------------------------
						// check if an object was selected
						//-----------------------------------------------------
						if(
							(data.interface_data.f_point_selected == TRUE) ||	
							(data.interface_data.f_bbox_selected == TRUE)
						) {

							//-------------------------------------------------
							// at this stage, we know that it is a translation
							//-------------------------------------------------
							data.interface_data.transformation = TRANSLATE;

						} else {

							//-------------------------------------------------
							// process the touch as a left mouse button down
							//-------------------------------------------------
							bret = process_mouse_left_button_down(&data);
							assert(bret == SUCCESS);
							bret = InvalidateRect(
								hwnd, 
								NULL,
								TRUE
							);
							assert(bret == TRUE);
							bret = PostMessage(
								hwnd, 
								WM_PAINT, 
								0,
								0
							);
							assert(bret == TRUE);
						}
					}
				}

				if(touch_input->dwFlags & TOUCHEVENTF_MOVE) {

					//---------------------------------------------------------
					// touch event is used as a mouse move event 
					// Note:
					//    we still check that we are not in help mode
					// Note:
					//    the x, y position of a touch is given in hundredths 
					//    of physical pixels.
					//---------------------------------------------------------
					if(data.interface_data.f_in_help == FALSE) {

						//-----------------------------------------------------
						// retrive x & y of the touch input 
						//-----------------------------------------------------
						data.interface_data.xpos = touch_input->x / 100;
						data.interface_data.ypos = touch_input->y / 100;

						//-----------------------------------------------------
						// process the touch as a right mouse button down
						//-----------------------------------------------------
						bret = process_mouse_move(&data);
						assert(bret == SUCCESS);
						bret = InvalidateRect(
							hwnd, 
							NULL,
							TRUE
						);
						assert(bret == TRUE);
						PostMessage(
							hwnd,
							WM_PAINT,
							0,
							0
						);
						assert(bret == TRUE);
					}
				}

				if(touch_input->dwFlags & TOUCHEVENTF_UP) {

					//---------------------------------------------------------
					// touch event is used as a mouse right button up event 
					// Note:
					//    we still check that we are not in help mode
					// Note:
					//    the x, y position of a touch is given in hundredths 
					//    of physical pixels.
					//---------------------------------------------------------
					if(data.interface_data.f_in_help == FALSE) {

						//-----------------------------------------------------
						// retrive x & y of the touch input 
						//-----------------------------------------------------
						data.interface_data.xpos = touch_input->x / 100;
						data.interface_data.ypos = touch_input->y / 100;

						//-----------------------------------------------------
						// process the touch as a right mouse button down
						//-----------------------------------------------------
						bret = process_mouse_right_button_up(&data);
						assert(bret == SUCCESS);
					}
				}
			} // for i
			
			//-----------------------------------------------------------------
			// close the input handler
			//-----------------------------------------------------------------
			bret = CloseTouchInputHandle((HTOUCHINPUT)lparam);

			//-----------------------------------------------------------------
			// free memory used to store touch inputs
			//-----------------------------------------------------------------
			free(data.interface_data.touch_inputs);
			data.interface_data.touch_inputs = NULL;
			data.interface_data.touch_inputs_count = 0;
			assert(bret != FALSE);
			f_handled = TRUE;
			break;

#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

		/*
		@    @  @@@@@ @@@@@          @@@@@  @@@@  @    @  @@@@  @    @
		@@  @@    @     @              @   @    @ @    @ @    @ @    @
		@ @@ @    @     @              @   @    @ @    @ @      @    @
		@    @    @     @              @   @    @ @    @ @      @@@@@@
		@    @    @     @              @   @    @ @    @ @      @    @
		@    @    @     @              @   @    @ @    @ @    @ @    @
		@    @    @   @@@@@            @    @@@@   @@@@   @@@@  @    @
		*/
		//---------------------------------------------------------------------
		// MTI touch message
		//---------------------------------------------------------------------
		case WM_TOUCH:

			//-----------------------------------------------------------------
			// allocate memory to store touch inputs
			//-----------------------------------------------------------------
			data.interface_data.touch_inputs_count = LOWORD(wparam);
			memory_size = 
				sizeof(TOUCHINPUT) * 
				data.interface_data.touch_inputs_count
			;
			data.interface_data.touch_inputs = (PTOUCHINPUT)malloc(memory_size);
			assert(data.interface_data.touch_inputs != NULL);

			//-----------------------------------------------------------------
			// get touch inputs
			//-----------------------------------------------------------------
			bret = GetTouchInputInfo(
				(HTOUCHINPUT)lparam,
				data.interface_data.touch_inputs_count,
				data.interface_data.touch_inputs,
				sizeof(TOUCHINPUT)
			);
			assert(bret != FALSE);

			//-----------------------------------------------------------------
			// process touch inputs
			//-----------------------------------------------------------------
			for(i = 0; i < data.interface_data.touch_inputs_count; i++) {

				//-------------------------------------------------------------
				// process each touch input in sequence
				//-------------------------------------------------------------
				touch_input = &data.interface_data.touch_inputs[i];

				//-------------------------------------------------------------
				// add id to id store
				//-------------------------------------------------------------
				// TODO:
				if(touch_input->dwFlags & TOUCHEVENTF_DOWN) {

					//---------------------------------------------------------
					// touch event is used as a left and right mouse button 
					// down messages replacement.  the logic used is the fol-
					// lowing: if any object is selected, then it is a right 
					// button, otherwise, it is a left button.
					// Note:
					//    we still check that we are not in help mode
					// Note:
					//    the x, y position of a touch is given in hundredths 
					//    of physical pixels.
					//---------------------------------------------------------
					if(data.interface_data.f_in_help == FALSE) {

						//-----------------------------------------------------
						// retrive x & y of the touch input 
						//-----------------------------------------------------
						data.interface_data.xpos = touch_input->x / 100;
						data.interface_data.ypos = touch_input->y / 100;

						//-----------------------------------------------------
						// process the touch as a right mouse button down to
						// detect if an existing - displayed or not - object
						// was selected by the touch input
						//-----------------------------------------------------
						bret = process_mouse_right_button_down(&data);
						assert(bret == SUCCESS);

						//-----------------------------------------------------
						// check if an object was selected
						//-----------------------------------------------------
						if(
							(data.interface_data.f_point_selected == TRUE) ||	
							(data.interface_data.f_bbox_selected == TRUE)
						) {

							//-------------------------------------------------
							// at this stage, we know that it is a translation
							//-------------------------------------------------
							data.interface_data.transformation = TRANSLATE;

						} else {

							//-------------------------------------------------
							// process the touch as a left mouse button down
							//-------------------------------------------------
							bret = process_mouse_left_button_down(&data);
							assert(bret == SUCCESS);
							bret = InvalidateRect(
								hwnd, 
								NULL,
								TRUE
							);
							assert(bret == TRUE);
							bret = PostMessage(
								hwnd, 
								WM_PAINT, 
								0,
								0
							);
							assert(bret == TRUE);
						}
					}
				}

				if(touch_input->dwFlags & TOUCHEVENTF_MOVE) {

					//---------------------------------------------------------
					// touch event is used as a mouse move event 
					// Note:
					//    we still check that we are not in help mode
					// Note:
					//    the x, y position of a touch is given in hundredths 
					//    of physical pixels.
					//---------------------------------------------------------
					if(data.interface_data.f_in_help == FALSE) {

						//-----------------------------------------------------
						// retrive x & y of the touch input 
						//-----------------------------------------------------
						data.interface_data.xpos = touch_input->x / 100;
						data.interface_data.ypos = touch_input->y / 100;

						//-----------------------------------------------------
						// process the touch as a right mouse button down
						//-----------------------------------------------------
						bret = process_mouse_move(&data);
						assert(bret == SUCCESS);
						bret = InvalidateRect(
							hwnd, 
							NULL,
							TRUE
						);
						assert(bret == TRUE);
						PostMessage(
							hwnd,
							WM_PAINT,
							0,
							0
						);
						assert(bret == TRUE);
					}
				}

				if(touch_input->dwFlags & TOUCHEVENTF_UP) {

					//---------------------------------------------------------
					// touch event is used as a mouse right button up event 
					// Note:
					//    we still check that we are not in help mode
					// Note:
					//    the x, y position of a touch is given in hundredths 
					//    of physical pixels.
					//---------------------------------------------------------
					if(data.interface_data.f_in_help == FALSE) {

						//-----------------------------------------------------
						// retrive x & y of the touch input 
						//-----------------------------------------------------
						data.interface_data.xpos = touch_input->x / 100;
						data.interface_data.ypos = touch_input->y / 100;

						//-----------------------------------------------------
						// process the touch as a right mouse button down
						//-----------------------------------------------------
						bret = process_mouse_right_button_up(&data);
						assert(bret == SUCCESS);

						//-----------------------------------------------------
						// reset touch trace ids data
						//-----------------------------------------------------
						bret = clear_touch_contact_ids(&data.interface_data);
						assert(bret == SUCCESS);
					}
				}
			} // for i
			
			//-----------------------------------------------------------------
			// close the input handler
			//-----------------------------------------------------------------
			bret = CloseTouchInputHandle((HTOUCHINPUT)lparam);

			//-----------------------------------------------------------------
			// free memory used to store touch inputs
			//-----------------------------------------------------------------
			free(data.interface_data.touch_inputs);
			data.interface_data.touch_inputs = NULL;
			data.interface_data.touch_inputs_count = 0;
			assert(bret != FALSE);
			f_handled = TRUE;
			break;

#else // __MTI_SAMPLE_MTI_TOUCH_CODE__

		/*
		@    @  @@@@@ @@@@@          @@@@  @@@@@@  @@@@   @@@@@ @    @ @@@@@  @@@@@@
		@@  @@    @     @           @    @ @      @    @    @   @    @ @    @ @
		@ @@ @    @     @           @      @      @         @   @    @ @    @ @
		@    @    @     @           @      @@@@@@  @@@@     @   @    @ @@@@@  @@@@@@
		@    @    @     @           @  @@@ @           @    @   @    @ @  @   @
		@    @    @     @           @    @ @           @    @   @    @ @   @  @
		@    @    @   @@@@@          @@@@  @@@@@@ @@@@@     @    @@@@  @    @ @@@@@@
		*/
		//---------------------------------------------------------------------
		// MTI gesture messages
		//---------------------------------------------------------------------
		case WM_GESTURENOTIFY:

			//-----------------------------------------------------------------
			// register gestures to receive
			// Note:
			//    processing the WM_GESTURENOTIFY message this way allows us 
			//    - if needed later on - to dynamically change the list of
			//    the gesture we want to receive.  If dynamicity is not
			//    required, the call to SetGestureConfig can be done during
			//    the application's initialization (though you will still 
			//    need a hwnd to do so).
			// Note:
			//    cbSize is the size of a single GESTURECONFIG and not the 
			//    size of the GESTURECONFIG array as the documentation may
			//    let suppose
			//-----------------------------------------------------------------
			bret = SetGestureConfig(
				hwnd,
				0,
				gestures_count,
				gesture_config,
				sizeof(GESTURECONFIG)
			);
			assert(bret != FALSE);
			f_handled = TRUE;
			break;

		//---------------------------------------------------------------------
		// MTI gesture messages
		//---------------------------------------------------------------------
		case WM_GESTURE:

			//-----------------------------------------------------------------
			// get gesture info
			//-----------------------------------------------------------------
			memset(
				&data.interface_data.gesture_info, 
				0,
				sizeof(GESTUREINFO)
			);
			data.interface_data.gesture_info.cbSize = sizeof(GESTUREINFO);
			bret = GetGestureInfo(
				(HGESTUREINFO)lparam, 
				&data.interface_data.gesture_info
			);
			assert(bret != FALSE);

			//-----------------------------------------------------------------
			// decode gesture info
			//-----------------------------------------------------------------
			switch(data.interface_data.gesture_info.dwID) {

				//-------------------------------------------------------------
				// zoom
				//-------------------------------------------------------------
				case GID_ZOOM:
					bret = process_zoom(&data);
					assert(bret == SUCCESS);
					f_handled = TRUE;
					break;

				//-------------------------------------------------------------
				// pan
				//-------------------------------------------------------------
				case GID_PAN:
					bret = process_pan(&data);
					assert(bret == SUCCESS);
					f_handled = TRUE;
					break;

				//-------------------------------------------------------------
				// rotate
				//-------------------------------------------------------------
				case GID_ROTATE:
					bret = process_rotate(&data);
					assert(bret == SUCCESS);
					f_handled = TRUE;
					break;

				//-------------------------------------------------------------
				// two finger tap
				//-------------------------------------------------------------
				case GID_TWOFINGERTAP:
					bret = process_2fingers_tap(&data);
					assert(bret == SUCCESS);
					f_handled = TRUE;
					break;

				//-------------------------------------------------------------
				// roll over
				//-------------------------------------------------------------
				case GID_PRESSANDTAP:
					bret = process_roll_over(&data);
					assert(bret == SUCCESS);
					f_handled = TRUE;
					break;

				//-------------------------------------------------------------
				// not recognized gesture
				//-------------------------------------------------------------
				default:
					f_handled = FALSE;
					break;
			} // switch MTI messages

			if(f_handled == TRUE) {

				//-------------------------------------------------------------
				// since we handled the message, we close the gesture info
				// handler to avoid memory leaks.  Non handled messages will
				// be processed by the default window message handler and the
				// gesture info handler will be passed to it (and closed by it)
				//-------------------------------------------------------------
				bret = CloseGestureInfoHandle((HGESTUREINFO)lparam);
				assert(bret != FALSE);

			}
			break;

		//---------------------------------------------------------------------
		// left mouse click (button depressed)
		// Note:
		//    we still process the mouse messages since non-gestures are 
		//    translated by the OS into legacy mouse messages.  However, we
		//    process only the WM_LBUTTONDOWN button - and no other messages -
		//    to be able to drop-down control points.  All other mouse inter-
		//    actions are replaced by use of gestures.
		//---------------------------------------------------------------------
		case WM_LBUTTONDOWN:
			if(data.interface_data.f_in_help == FALSE) {
				data.interface_data.xpos = LOWORD(lparam);
				data.interface_data.ypos = HIWORD(lparam);
				bret = process_mouse_left_button_down(&data);
				assert(bret == SUCCESS);
				bret = InvalidateRect(
					hwnd, 
					NULL,
					TRUE
				);
				assert(bret == TRUE);
				bret = PostMessage(
					hwnd, 
					WM_PAINT, 
					0,
					0
				);
				assert(bret == TRUE);
			}
			f_handled = TRUE;
			break;

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#else // __MTI_SAMPLE_MTI_CODE__

		/*
		@    @  @@@@  @    @  @@@@  @@@@@@
		@@  @@ @    @ @    @ @    @ @
		@ @@ @ @    @ @    @ @      @
		@    @ @    @ @    @  @@@@  @@@@@@
		@    @ @    @ @    @      @ @
		@    @ @    @ @    @      @ @
		@    @  @@@@   @@@@  @@@@@  @@@@@@
		*/
#ifndef __MTI_SAMPLE_STI_TOUCH_CODE__

		//---------------------------------------------------------------------
		// left mouse click (button depressed)
		//---------------------------------------------------------------------
		case WM_LBUTTONDOWN:
			if(data.interface_data.f_in_help == FALSE) {
				data.interface_data.xpos = LOWORD(lparam);
				data.interface_data.ypos = HIWORD(lparam);
				bret = process_mouse_left_button_down(&data);
				assert(bret == SUCCESS);
				bret = InvalidateRect(
					hwnd, 
					NULL,
					TRUE
				);
				assert(bret == TRUE);
				bret = PostMessage(
					hwnd, 
					WM_PAINT, 
					0,
					0
				);
				assert(bret == TRUE);
			}
			f_handled = TRUE;
			break;

		//---------------------------------------------------------------------
		// right mouse click (button depressed)
		//---------------------------------------------------------------------
		case WM_RBUTTONDOWN:
			if(data.interface_data.f_in_help == FALSE) {
				data.interface_data.xpos = LOWORD(lparam);
				data.interface_data.ypos = HIWORD(lparam);
				if(wparam & MK_SHIFT) {
					data.interface_data.f_shift = TRUE;
				}
				if(wparam & MK_CONTROL) {
					data.interface_data.f_control = TRUE;
				}
				if(wparam & MK_SHIFT) {
					data.interface_data.f_shift = TRUE;
					data.interface_data.transformation |= SCALE;
				}
				if(wparam & MK_CONTROL) {
					data.interface_data.f_control = TRUE;
					data.interface_data.transformation |= ROTATE;
				}
				if(
					!(wparam & MK_SHIFT) &&
					!(wparam & MK_CONTROL)
				) {
					data.interface_data.transformation |= TRANSLATE;
				}
				bret = process_mouse_right_button_down(&data);
				assert(bret == SUCCESS);
			}
			f_handled = TRUE;
			break;

		//---------------------------------------------------------------------
		// right mouse click (button released)
		//---------------------------------------------------------------------
		case WM_RBUTTONUP:
			if(data.interface_data.f_in_help == FALSE) {
				bret = process_mouse_right_button_up(&data);
				assert(bret == SUCCESS);
			}
			f_handled = TRUE;
			break;

		//---------------------------------------------------------------------
		// mouse position changed
		//---------------------------------------------------------------------
		case WM_MOUSEMOVE:
			if(
				(
					(data.interface_data.f_point_selected == TRUE) ||
					(data.interface_data.f_bbox_selected == TRUE)
				) &&
				(data.interface_data.f_in_help == FALSE)
			) {
				data.interface_data.xpos = LOWORD(lparam);
				data.interface_data.ypos = HIWORD(lparam);
				bret = process_mouse_move(&data);
				assert(bret == SUCCESS);
				bret = InvalidateRect(
					hwnd, 
					NULL,
					TRUE
				);
				assert(bret == TRUE);
				PostMessage(
					hwnd,
					WM_PAINT,
					0,
					0
				);
				assert(bret == TRUE);
			}
			f_handled = TRUE;
			break;

#endif // !__MTI_SAMPLE_STI_TOUCH_CODE__

#endif // __MTI_SAMPLE_MTI_CODE__

		/*
		@   @  @@@@@@  @  @  @@@@@   @@@@    @@   @@@@@  @@@@@
		@  @   @       @  @  @    @ @    @  @  @  @    @ @    @
		@ @    @       @  @  @    @ @    @ @    @ @    @ @    @
		@@     @@@@@@   @    @@@@@  @    @ @    @ @@@@@  @    @
		@ @    @        @    @    @ @    @ @@@@@@ @  @   @    @
		@  @   @        @    @    @ @    @ @    @ @   @  @    @
		@   @  @@@@@@   @    @@@@@   @@@@  @    @ @    @ @@@@@
		*/
		//---------------------------------------------------------------------
		// a key was pressed
		//---------------------------------------------------------------------
		case WM_KEYDOWN:
			data.interface_data.key = (LONG)wparam;
			bret = process_key_pressed(&data);
			assert(bret == SUCCESS);
			bret = InvalidateRect(
				hwnd, 
				NULL,
				TRUE
			);
			assert(bret == TRUE);
			bret = PostMessage(
				hwnd, 
				WM_PAINT, 
				0,
				0
			);
			assert(bret == TRUE);
			f_handled = TRUE;
			break;

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

		//---------------------------------------------------------------------
		// a key was depressed
		//---------------------------------------------------------------------
		case WM_KEYUP:
			data.interface_data.key = wparam;
			bret = process_key_depressed(&data);
			assert(bret == SUCCESS);
			bret = InvalidateRect(
				hwnd, 
				NULL,
				TRUE
			);
			assert(bret == TRUE);
			bret = PostMessage(
				hwnd, 
				WM_PAINT, 
				0,
				0
			);
			assert(bret == TRUE);
			f_handled = TRUE;
			break;

#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

#ifdef __MTI_SAMPLE_SENSORS_CODE__

		/*
		 @@@@  @@@@@@  @@@@  @    @  @@@@  @@@@@   @@@@ 
		@    @ @      @    @ @@   @ @    @ @    @ @    @
		@      @      @      @ @  @ @    @ @    @ @     
		 @@@@  @@@@@@  @@@@  @ @  @ @    @ @@@@@   @@@@ 
		     @ @           @ @  @ @ @    @ @  @	     @
		     @ @           @ @   @@ @    @ @   @       @
		@@@@@  @@@@@@ @@@@@  @    @  @@@@  @    @ @@@@@ 
		*/
		//---------------------------------------------------------------------
		// process sensors value update
		//---------------------------------------------------------------------
		//---------------------------------------------------------------------
		// Note:
		//    In this sample, we do implement only the ISensorEvents interface.
		//    This is the reason why if a sensor is installed once the program
		//    has started it is not taken in account.  Do do so, the 
		//    ISensorManagerEvents intrface must be implemented, added to the
		//    sensors manager (OnSensorEnter).
		// Note:
		//    The Windows sensor interface is accessible thru COM interfaces.
		//    In this sample (mainly written in C/Win32), sensor management
		//    code is implemented in sensors-sample.cpp and sensors-sample.hpp
		//    files.  In addition, shared data between C and C++ code is 
		//    defined in mti_sample-share.h file.  This is required since the
		//    use of ATL forbids the inclusion of windows.h.
		//---------------------------------------------------------------------
		case MTI_SAMPLE_SENSOR_UPDATE:

			//-----------------------------------------------------------------
			// update the light coefficient baded on ALS lux reading 
			//-----------------------------------------------------------------
			if(shared_data.f_sensor == FALSE) {
				shared_data.lux = DEFAULT_LUX_VALUE;
			}
			shared_data.light_coefficient = NORMALIZE_LUX(shared_data.lux);
			
			//-----------------------------------------------------------------
			// since several GUI data are created and initialized during 
			// startup, we need to destroy them and re-created them based on 
			// the new sesnor values.
			//-----------------------------------------------------------------
			bret = re_initialize_graphic_data(&data.graphic_data);
			assert(bret == TRUE);

			//-----------------------------------------------------------------
			// force display update 
			//-----------------------------------------------------------------
			bret = InvalidateRect(
				hwnd, 
				NULL,
				TRUE
			);
			assert(bret == TRUE);
			bret = PostMessage(
				hwnd, 
				WM_PAINT, 
				0,
				0
			);
			assert(bret == TRUE);
			f_handled = TRUE;
			break;

#endif // __MTI_SAMPLE_SENSORS_CODE__

		/*
		@@@@@    @@   @@@@@  @    @  @@@@@
		@    @  @  @    @    @@   @    @
		@    @ @    @   @    @ @  @    @
		@@@@@  @    @   @    @ @  @    @
		@      @@@@@@   @    @  @ @    @
		@      @    @   @    @   @@    @
		@      @    @ @@@@@  @    @    @
		*/
		//---------------------------------------------------------------------
		// redraw the window
		//---------------------------------------------------------------------
		case WM_PAINT:

#ifndef __MTI_SAMPLE_NO_DISPLAY__

			bret = GetClientRect(
				hwnd, 
				&data.interface_data.rect
			); 
			assert(bret != FALSE);
			data.graphic_data.hdc = BeginPaint(
				hwnd, 
				&data.graphic_data.ps
			);
			assert(data.graphic_data.hdc != NULL);
			data.graphic_data.in_memory_hdc = CreateCompatibleDC(
				data.graphic_data.hdc
			);
			assert(data.graphic_data.in_memory_hdc != NULL);
			data.graphic_data.in_memory_bitmap = CreateCompatibleBitmap(
				data.graphic_data.hdc, 
				data.interface_data.rect.right, 
				data.interface_data.rect.bottom
			); 
			assert(data.graphic_data.in_memory_bitmap != NULL);
			data.graphic_data.old_bitmap = (HBITMAP)SelectObject(
				data.graphic_data.in_memory_hdc, 
				data.graphic_data.in_memory_bitmap
			);
			assert(data.graphic_data.old_bitmap != NULL);
			bret = process_paint(&data);
			assert(bret == SUCCESS);
			BitBlt(
				data.graphic_data.hdc, 
				0, 
				0, 
				data.interface_data.rect.right, 
				data.interface_data.rect.bottom, 
				data.graphic_data.in_memory_hdc, 
				0, 
				0, 
				SRCCOPY
			);
			data.graphic_data.in_memory_bitmap = (HBITMAP)SelectObject(
				data.graphic_data.in_memory_hdc, 
				data.graphic_data.old_bitmap
			); 
			assert(data.graphic_data.in_memory_bitmap != NULL);
			bret = DeleteObject(data.graphic_data.in_memory_bitmap);
			assert(bret != FALSE);
			bret = DeleteDC(data.graphic_data.in_memory_hdc);
			assert(bret != FALSE);
			ret = ReleaseDC(
				hwnd, 
				data.graphic_data.hdc
			); 
			assert(ret != 0);
			bret = EndPaint(
				hwnd, 
				&data.graphic_data.ps
			);
			assert(bret != FALSE);

#endif // __MTI_SAMPLE_NO_DISPLAY__

			f_handled = TRUE;
			break; 

		//-----------------------------------------------------------------
		// intercept background clear
		//-----------------------------------------------------------------
		case WM_ERASEBKGND:
			bret = PostMessage(
				hwnd, 
				WM_PAINT, 
				0,
				0
			);
			assert(bret == TRUE);
			f_handled = TRUE;
			break;


#ifdef __MTI_SAMPLE_POWER_AWARE__

		/*
		@@@@@   @@@@  @    @ @@@@@@ @@@@@
		@    @ @    @ @    @ @      @    @
		@    @ @    @ @  @ @ @      @    @
		@@@@@  @    @ @  @ @ @@@@@@ @@@@@
		@      @    @ @  @ @ @      @  @
		@      @    @  @ @ @ @      @   @
		@       @@@@    @ @  @@@@@@ @    @
		*/
		//---------------------------------------------------------------------
		// power status messages
		//---------------------------------------------------------------------
		case WM_POWERBROADCAST:
			switch(wparam) {

				//-------------------------------------------------------------
				// power will be lost, let's prepare for it
				//-------------------------------------------------------------
				case PBT_APMSUSPEND:
				case PBT_APMBATTERYLOW:
				case PBT_APMQUERYSUSPEND:
					bret = power_suspend(&data);
					assert(bret == SUCCESS);
					f_handled = TRUE;
					return_value = TRUE;
					break;

				//-------------------------------------------------------------
				// power is back, let's resume from previous power loss
				//-------------------------------------------------------------
				case PBT_APMRESUMEAUTOMATIC:
				case PBT_APMRESUMESUSPEND:
				case PBT_APMRESUMECRITICAL:
				case PBT_APMQUERYSUSPENDFAILED:
					bret = power_resume(&data);
					assert(bret == SUCCESS);
					f_handled = TRUE;
					return_value = TRUE;
					break;

				case PBT_POWERSETTINGCHANGE:
				case PBT_APMOEMEVENT:
				case PBT_APMPOWERSTATUSCHANGE:
					break;
				default: 
					assert(0);
			}
			break;

#endif // __MTI_SAMPLE_POWER_AWARE__

		/*
		@@@@@@ @    @ @@@@@
		@      @@   @ @    @
		@      @ @  @ @    @
		@@@@@@ @ @  @ @    @
		@      @  @ @ @    @
		@      @   @@ @    @
		@@@@@@ @    @ @@@@@
		*/
		//---------------------------------------------------------------------
		// close window - house keeping
		//---------------------------------------------------------------------
		case WM_CLOSE:

#ifdef __MTI_SAMPLE_INSTRUMENTED__

		//---------------------------------------------------------------------
		// signal metrics thread to end
		//---------------------------------------------------------------------
		data.instrumentation_data.f_running = FALSE;

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

			bret = stop_timer(&data);
			assert(bret == SUCCESS);
			bret = stop_metrics_thread(&data);
			assert(bret == SUCCESS);
			
#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

#endif // __MTI_SAMPLE_INSTRUMENTED__

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

			//-----------------------------------------------------------------
			// unregister window so no touch messages will be received
			//-----------------------------------------------------------------
			bret = UnregisterTouchWindow(hwnd);
			assert(bret != FALSE);

#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

			//-----------------------------------------------------------------
			// unregister window so no touch messages will be received
			//-----------------------------------------------------------------
			bret = UnregisterTouchWindow(hwnd);
			assert(bret != FALSE);

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#endif // __MTI_SAMPLE_MTI_CODE__

#if defined(__MTI_SAMPLE_NO_DISPLAY__) || defined(__MTI_SAMPLE_STI_TOUCH_CODE__) || defined(__MTI_SAMPLE_MTI_TOUCH_CODE__) || defined(__MTI_SAMPLE_MTI_CODE__) 

			//-----------------------------------------------------------------
			// all these symbols required us to hide the mouse pointer, let's 
			// show it again
			//-----------------------------------------------------------------
			ShowCursor(TRUE);

#endif // __MTI_SAMPLE_MTI_CODE__ || __MTI_SAMPLE_STI_TOUCH_CODE__ || __MTI_SAMPLE_MTI_TOUCH_CODE__ || __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_SENSORS_CODE__

			//-----------------------------------------------------------------
			// detach from ALS sensor
			//-----------------------------------------------------------------
			bret = disconnect_from_als_sensor();
			assert(bret == TRUE);

#endif // __MTI_SAMPLE_SENSORS_CODE__

			bret = process_destroy(&data);
			assert(bret == SUCCESS);
			bret = DestroyWindow(hwnd);
			assert(bret == SUCCESS);
			f_handled = TRUE;
			break;

		//---------------------------------------------------------------------
		// quit
		//---------------------------------------------------------------------
		case WM_DESTROY:

#ifdef __MTI_SAMPLE_INSTRUMENTED__

			//-----------------------------------------------------------------
			// ask if PL should be removed or not from PL_FOLDER
			//-----------------------------------------------------------------
			ret = MessageBox(
				hwnd,
				MTI_SAMPLE_REMOVE_PL_MESSAGE_STRING,
				MTI_SAMPLE_REMOVE_PL_CAPTION_STRING,
				MB_ICONQUESTION | MB_YESNO
			);
			if(ret == IDYES) {

				//-------------------------------------------------------------
				// remove PL from PL_FOLDER
				//-------------------------------------------------------------
				bret = remove_pl(&data.instrumentation_data);
				assert(bret == SUCCESS);
			}

#endif // __MTI_SAMPLE_INSTRUMENTED__

#if defined (__MTI_SAMPLE_FILE_LOG__) || defined (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

			//-----------------------------------------------------------------
			// close log file
			//-----------------------------------------------------------------
			if(data.log_file != NULL) {
				ret = fclose(data.log_file);
				assert(ret == 0);
				data.log_file = NULL;
			}

#endif // (__MTI_SAMPLE_FILE_LOG__) || (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

			PostQuitMessage(0);
			f_handled = TRUE;
			break;

	} // switch message

	/*
	@@@@@  @@@@@@ @@@@@@   @@   @    @ @       @@@@@
	@    @ @      @       @  @  @    @ @         @
	@    @ @      @      @    @ @    @ @         @
	@    @ @@@@@@ @@@@@  @    @ @    @ @         @
	@    @ @      @      @@@@@@ @    @ @         @
	@    @ @      @      @    @ @    @ @         @
	@@@@@  @@@@@@ @      @    @  @@@@  @@@@@@    @
	*/
	if(f_handled == FALSE) {

		//---------------------------------------------------------------------
		// pass un-processed messages to Window's defautl message handler
		//---------------------------------------------------------------------
		return(
			DefWindowProc(
				hwnd, 
				message, 
				wparam,  
				lparam
			)
		);
	} else {
		return(return_value);
	}
}

/*-----------------------------------------------------------------------------
Function: WinMain
Purpose : windows program entry point
In      : usual Windows stuff
Out     : none
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/11/2010    Jamel Tayeb             Creation.
*/
int WINAPI WinMain(
	HINSTANCE instance, 
	HINSTANCE prev_instance, 
	PSTR szCmdLine, 
	int iCmdShow
) {

	MSG msg;
	int ret = -1;
	BOOL bret = FALSE;
	WNDCLASS window_class;
	HWND hwindow_class = NULL;
	static TCHAR application_name[] = TEXT(MTI_SAMPLE_APPLICATION_NAME);

	//---------- no declarations after this line --------------------------

#ifdef _DEBUG

	_HFILE hfret = _CRTDBG_HFILE_ERROR;
	DWORD dwret = 0;

#pragma	message ("NOTE: Building with memory leak detection.")

	//---------------------------------------------------------------------
	// dump memory leak info on any exit
	//---------------------------------------------------------------------
	dwret = _CrtSetDbgFlag(
		_CRTDBG_ALLOC_MEM_DF | 
		_CRTDBG_LEAK_CHECK_DF
	);
	assert(dwret != -1);

	//---------------------------------------------------------------------
	// redirect dump to stdout
	//---------------------------------------------------------------------
	ret = _CrtSetReportMode(
		_CRT_WARN, 
		_CRTDBG_MODE_FILE
	);
	assert(ret != -1);
	hfret = _CrtSetReportFile(
		_CRT_WARN, 
		_CRTDBG_FILE_STDOUT
	);
	assert(hfret != _CRTDBG_HFILE_ERROR);
	ret = _CrtSetReportMode(
		_CRT_ERROR, 
		_CRTDBG_MODE_FILE
	);
	assert(ret != -1);
	hfret = _CrtSetReportFile(
		_CRT_ERROR, 
		_CRTDBG_FILE_STDOUT
	);
	assert(hfret != _CRTDBG_HFILE_ERROR);
	ret = _CrtSetReportMode(
		_CRT_ASSERT, 
		_CRTDBG_MODE_FILE
	);
	assert(ret != -1);
	hfret = _CrtSetReportFile(
		_CRT_ASSERT, 
		_CRTDBG_FILE_STDOUT
	);
	assert(hfret != _CRTDBG_HFILE_ERROR);

#endif // _DEBUG

#if defined(__MTI_SAMPLE_MTI_CODE__) || defined(__MTI_SAMPLE_STI_TOUCH_CODE__)

	//---------------------------------------------------------------------
	// check for touch features
	//---------------------------------------------------------------------
	ret = GetSystemMetrics(SM_DIGITIZER);
	assert((ret & (NID_READY + NID_MULTI_INPUT)) != 0);
	ret = GetSystemMetrics(SM_MAXIMUMTOUCHES);
	assert(ret > 0);

#endif // __MTI_SAMPLE_MTI_CODE__ || __MTI_SAMPLE_STI_TOUCH_CODE__

	//---------------------------------------------------------------------
	// setup window class attributes
	//---------------------------------------------------------------------
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = window_class_procedure;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = instance;
	window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	window_class.lpszMenuName = NULL;
	window_class.lpszClassName = application_name;

	//---------------------------------------------------------------------
	// register window class attributes
	//---------------------------------------------------------------------
	if(!RegisterClass(&window_class)) {
		MessageBox(
			NULL, 
			TEXT(MTI_SAMPLE_NOT_IN_WINDOWS_MESSAGE_STRING), 
			application_name, 
			MB_ICONERROR
		);
		return(0);
	}

	//---------------------------------------------------------------------
	// create window
	//---------------------------------------------------------------------
	hwindow_class = CreateWindow(
		application_name, 
		TEXT(MTI_SAMPLE_WINDOW_TITLE),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		MTI_SAMPLE_WINDOW_WIDTH, 
		MTI_SAMPLE_WINDOW_HEIGHT,
		NULL, 
		NULL, 
		instance, 
		NULL
	);
	assert(hwindow_class != NULL);

	//---------------------------------------------------------------------
	// send WM_USER to initialize data
	//---------------------------------------------------------------------
	SendMessage(
		hwindow_class, 
		WM_USER, 
		0, 
		0
	);

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

	//-------------------------------------------------------------------------
	// register to STI touch sub-system
	// Note:
	//    TWF_WANTPALM is specified for speed, not because we are 
	//    interested in palm input at this stage
	//-------------------------------------------------------------------------
	bret = RegisterTouchWindow(
		hwindow_class,
		TWF_WANTPALM
	);
	assert(bret == TRUE);

#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

#if defined(__MTI_SAMPLE_MTI_CODE__) && defined(__MTI_SAMPLE_MTI_TOUCH_CODE__)

	//-------------------------------------------------------------------------
	// register to MTI sub-system so our window will receive touch and gesture
	// messages
	// Note:
	//    TWF_WANTPALM is specified for speed, not because we are 
	//    interested in palm input at this stage
	//-------------------------------------------------------------------------
	bret = RegisterTouchWindow(
		hwindow_class,
		TWF_WANTPALM
	);
	assert(bret == TRUE);

#endif // (__MTI_SAMPLE_MTI_CODE__) && (__MTI_SAMPLE_MTI_TOUCH_CODE__)

	//-------------------------------------------------------------------------
	// display window
	//-------------------------------------------------------------------------
#if defined(__MTI_SAMPLE_NO_DISPLAY__) || defined(__MTI_SAMPLE_STI_TOUCH_CODE__) || defined(__MTI_SAMPLE_MTI_TOUCH_CODE__) || defined(__MTI_SAMPLE_MTI_CODE__) 

	//-------------------------------------------------------------------------
	// all these symbols requires a start in no-help mode and full-screen
	//-------------------------------------------------------------------------	
	iCmdShow |= SW_MAXIMIZE;

#endif // __MTI_SAMPLE_MTI_CODE__ || __MTI_SAMPLE_STI_TOUCH_CODE__ || __MTI_SAMPLE_MTI_TOUCH_CODE__ || __MTI_SAMPLE_MTI_CODE__

	bret = ShowWindow(
		hwindow_class, 
		iCmdShow
	);
	assert(bret == FALSE);
	bret = UpdateWindow(hwindow_class);
	assert(bret != FALSE);

	//-------------------------------------------------------------------------
	// message loop
	//-------------------------------------------------------------------------
	while(GetMessage(
		&msg, 
		NULL, 
		0, 
		0) > 0
	) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

#ifdef __MTI_SAMPLE_INSTRUMENTED__

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

/*-----------------------------------------------------------------------------
Function: start_timer
Purpose : start the metrics thread's timer
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL start_timer(PMTI_SAMPLE_DATA p) {

	assert(p != NULL);

	p->instrumentation_data.timer = (HRESULT)SetTimer(
		p->instrumentation_data.hwnd, 
		METRICS_THREAD_TIMER, 
		METRICS_THREAD_UPDATE_INTERVAL_IN_MS, 
		NULL
	);
	assert(p->instrumentation_data.timer != 0);

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: stop_timer
Purpose : stop the metrics thread's timer
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL stop_timer(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE; 

	assert(p != NULL);

	bret = KillTimer(
		p->instrumentation_data.hwnd, 
		METRICS_THREAD_TIMER
	); 
	assert(bret != FALSE);

	return(SUCCESS);
}
#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

/*-----------------------------------------------------------------------------
Function: start_metrics_thread
Purpose : start the metrics thread
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL start_metrics_thread(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// create synchronization objects
	// Note:
	//    all events are manual reset except the update event
	//-------------------------------------------------------------------------
	p->instrumentation_data.metrics_thread_can_start_event = CreateEvent(
		NULL, 
		TRUE, 
		FALSE, 
		NULL
	);
	assert(p->instrumentation_data.metrics_thread_can_start_event != NULL);
	p->instrumentation_data.metrics_thread_stoped_event = CreateEvent(
		NULL, 
		TRUE, 
		FALSE, 
		NULL
	);
	assert(p->instrumentation_data.metrics_thread_stoped_event != NULL);

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	p->instrumentation_data.metrics_thread_update_event = CreateEvent(
		NULL, 
		FALSE, 
		FALSE, 
		NULL
	);
	assert(p->instrumentation_data.metrics_thread_update_event != NULL);

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	//-------------------------------------------------------------------------
	// start the metrics thread
	//-------------------------------------------------------------------------
	p->instrumentation_data.f_running = TRUE;
	p->instrumentation_data.metrics_thread_handle = CreateThread(
		NULL, 
		0, 
		(LPTHREAD_START_ROUTINE)metrics_thread_function, 
		p, 
		0, 
		&p->instrumentation_data.metrics_thread_id
	);
	assert(p->instrumentation_data.metrics_thread_handle != NULL);

	//-------------------------------------------------------------------------
	// check that all data is available and unlock metrics thread
	//-------------------------------------------------------------------------
	// TODO: checks
	bret = SetEvent(
		p->instrumentation_data.metrics_thread_can_start_event
	);
	assert(bret != FALSE);

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: stop_metrics_thread
Purpose : stop the metrics thread
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL stop_metrics_thread(PMTI_SAMPLE_DATA p) {
	
	BOOL bret = FALSE;
	DWORD dwret = WAIT_FAILED;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// fire update thread and wait its end
	//-------------------------------------------------------------------------
	p->instrumentation_data.f_running = FALSE;

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	bret = SetEvent(
		p->instrumentation_data.metrics_thread_update_event
	);
	assert(bret != FALSE);
	dwret = WaitForSingleObject(
		p->instrumentation_data.metrics_thread_stoped_event,
		INFINITE
	);
	assert(dwret == WAIT_OBJECT_0);

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	//-------------------------------------------------------------------------
	// destroy synchronization objects
	//-------------------------------------------------------------------------
	if(p->instrumentation_data.metrics_thread_can_start_event != NULL) {
		bret = CloseHandle(
			p->instrumentation_data.metrics_thread_can_start_event
		);
		assert(bret != FALSE);
		p->instrumentation_data.metrics_thread_can_start_event = NULL;
	}
	if(p->instrumentation_data.metrics_thread_stoped_event != NULL) {
		bret = CloseHandle(
			p->instrumentation_data.metrics_thread_stoped_event
		);
		assert(bret != FALSE);
		p->instrumentation_data.metrics_thread_stoped_event = NULL;
	}
#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	if(p->instrumentation_data.metrics_thread_update_event != NULL) {
		bret = CloseHandle(
			p->instrumentation_data.metrics_thread_update_event
		);
		assert(bret != FALSE);
		p->instrumentation_data.metrics_thread_update_event = NULL;
	}

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: metrics_thread_function
Purpose : metrics thread implementation function
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
08/22/2010    Jamel Tayeb             Added file logging support.
*/
LPTHREAD_START_ROUTINE metrics_thread_function(PMTI_SAMPLE_DATA px) {
	
	BOOL bret = FALSE;
	DWORD dwret = WAIT_FAILED;
	double value = 0.0;

#ifdef __MTI_SAMPLE_FILE_LOG__

	//-------------------------------------------------------------------------
	// variables used to manage file logging
	//-------------------------------------------------------------------------
	int ret = 0;
	errno_t eret = 0;
	time_t log_time;
	char log_buffer[] = MTI_SAMPLE_LOG_FILE_HEADER;
	char cvt_buffer[MTI_SAMPLE_TIME_BUFFER_SIZE] = { '\0' };
	char time_buffer[MTI_SAMPLE_TIME_BUFFER_SIZE] = { '\0' };

#endif // __MTI_SAMPLE_FILE_LOG__

	//-------------------------------------------------------------------------
	// multiplier data
	//-------------------------------------------------------------------------
	double beziers_per_joule_multiplier = 0.0;
	double translations_per_joule_multiplier = 0.0;
	double scales_per_joule_multiplier = 0.0;
	double rotations_per_joule_multiplier = 0.0;
	double joules_per_bezier_multiplier = 0.0;
	double joules_per_translation_multiplier = 0.0;
	double joules_per_scale_multiplier = 0.0;
	double joules_per_rotation_multiplier = 0.0;

	double ticks_per_bezier_multiplier = 0.0;
	double ticks_per_translation_multiplier = 0.0;
	double ticks_per_scale_multiplier = 0.0;
	double ticks_per_rotation_multiplier = 0.0;

	PMTI_SAMPLE_INSTRUMENTATION_DATA p = NULL;

	assert(px != NULL);
	p = &px->instrumentation_data;
	assert(p != NULL);

	//-------------------------------------------------------------------------
	// wait for start signal 
	//-------------------------------------------------------------------------
	dwret = WaitForSingleObject(
		p->metrics_thread_can_start_event,
		INFINITE
	);
	assert(dwret == WAIT_OBJECT_0);

	//-------------------------------------------------------------------------
	// compute energy-efficiency multipliers
	//-------------------------------------------------------------------------
	beziers_per_joule_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_BEZIERS_PER_JOULE_DECIMALS
	);
	translations_per_joule_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_TRANSLATIONS_PER_JOULE_DECIMALS
	);
	scales_per_joule_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_SCALES_PER_JOULE_DECIMALS
	);
	rotations_per_joule_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_ROTATIONS_PER_JOULE_DECIMALS
	);
	joules_per_bezier_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_JOULES_PER_BEZIER_DECIMALS
	);
	joules_per_translation_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_JOULES_PER_TRANSLATION_DECIMALS
	);
	joules_per_scale_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_JOULES_PER_SCALE_DECIMALS
	);
	joules_per_rotation_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_JOULES_PER_ROTATION_DECIMALS
	);

	//-------------------------------------------------------------------------
	// compute performance multipliers
	//-------------------------------------------------------------------------
	ticks_per_bezier_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_TICKS_PER_BEZIER_DECIMALS
	);
	ticks_per_translation_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_TICKS_PER_TRANSLATION_DECIMALS
	);
	ticks_per_scale_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_TICKS_PER_SCALE_DECIMALS
	);
	ticks_per_rotation_multiplier = pow(
		10.0, 
		(double)MTI_SAMPLE_DEFAULT_TICKS_PER_ROTATION_DECIMALS
	);

#ifdef __MTI_SAMPLE_FILE_LOG__

	//-------------------------------------------------------------------------
	// write log file header
	//-------------------------------------------------------------------------
	ret = (int)fwrite(
		log_buffer, 
		strlen(log_buffer), 
		sizeof(char), 
		px->log_file
	);
	assert(ret != 0);

#endif // __MTI_SAMPLE_FILE_LOG__

	//-------------------------------------------------------------------------
	// main metrics thread loop
	//-------------------------------------------------------------------------
	while(p->f_running == TRUE) {

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

		//---------------------------------------------------------------------
		// wait for update signal from message loop's timer 
		//---------------------------------------------------------------------
		dwret = WaitForSingleObject(
			p->metrics_thread_update_event,
			INFINITE
		);
		assert(dwret == WAIT_OBJECT_0);

#else // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

		//---------------------------------------------------------------------
		// sleep for pause time
		// Note:
		//    if the sampling time goes over one second, it is recommended to
		//    replace the Sleep by a timed wait for an event.  This event could
		//    then be signaled by the message loop if the user ends the 
		//    application.  This will avoid the application to hang until the
		//    sleep timeout happens.
		//---------------------------------------------------------------------
		Sleep(
			METRICS_THREAD_UPDATE_INTERVAL_IN_MS
		);

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

		//---------------------------------------------------------------------
		// check if end was requested by the user
		//---------------------------------------------------------------------
		if(p->f_running == FALSE) {
			goto metrics_thread_done;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add time stamp to log buffer
		//---------------------------------------------------------------------
		memset(
			log_buffer, 
			0,
			sizeof(log_buffer)
		);
		time(&log_time);
		eret = ctime_s(
			time_buffer, 
			sizeof(time_buffer), 
			&log_time
		);
		assert(eret == 0);
		strncpy(
			&time_buffer[MTI_SAMPLE_TIME_STAMP_OFFSET], 
			MTI_SAMPLE_LOG_FILE_SEPARATOR, 
			strlen(MTI_SAMPLE_LOG_FILE_SEPARATOR)
		);
		time_buffer[MTI_SAMPLE_TIME_STAMP_END_OFFSET] = '\0';
		strncat(
			log_buffer, 
			time_buffer, 
			sizeof(time_buffer)
		);

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		//    Bézier curves
		//    Bézier curve redraws
		//    Translations
		//    Scalings
		//    Rotations
		//---------------------------------------------------------------------
		LOG_ULL(p->beziers);
		LOG_ULL(p->beziers_drawn);
		LOG_ULL(p->translations);
		LOG_ULL(p->scales);
		LOG_ULL(p->rotations);

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		//    Sum of Joules consumed for Bézier curves
		//    Sum of Joules consumed for translations
		//    Sum of Joules consumed for scalings
		//    Sum of Joules consumed for rotations
		//---------------------------------------------------------------------
		value = 
			(double)p->beziers_joules / 
			p->energy_data.energy_data_multiplier
		;
		LOG_DOUBLE(value);
		value = 
			(double)p->translations_joules / 
			p->energy_data.energy_data_multiplier
		;
		LOG_DOUBLE(value);
		value = 
			(double)p->scales_joules / 
			p->energy_data.energy_data_multiplier
		;
		LOG_DOUBLE(value);
		value = 
			(double)p->rotations_joules / 
			p->energy_data.energy_data_multiplier
		;
		LOG_DOUBLE(value);

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		//    ms elapsed drawing Bézier curves
		//    ms elapsed performing translations
		//    ms elapsed performing scalings
		//    ms elapsed performing rotations
		//---------------------------------------------------------------------
		LOG_ULL(p->beziers_ticks);
		LOG_ULL(p->translations_ticks);
		LOG_ULL(p->scales_ticks);
		LOG_ULL(p->rotations_ticks);

#endif // __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// compute energy-efficiency metrics (work units per joule)
		//---------------------------------------------------------------------
		if(p->beziers_joules != 0) {
			value = 
				(double)p->beziers /
				(double)p->beziers_joules *
				p->energy_data.energy_data_multiplier
			;
			p->beziers_per_joule = (unsigned long long)(
				value * 
				beziers_per_joule_multiplier
			);
		} else {
			value = 0.0;
		}
#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->translations_joules != 0) {
			value = 
				(double)p->translations /
				(double)p->translations_joules *
				p->energy_data.energy_data_multiplier 
			;
			p->translations_per_joule = (unsigned long long)(
				value *
				translations_per_joule_multiplier
			);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->scales_joules != 0) {
			value =
				(double)p->scales /
				(double)p->scales_joules *
				p->energy_data.energy_data_multiplier 
			;
			p->scales_per_joule = (unsigned long long)(
				value *
				scales_per_joule_multiplier
			);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->rotations_joules != 0) {
			value =
				(double)p->rotations /
				(double)p->rotations_joules *
				p->energy_data.energy_data_multiplier 
			;
			p->rotations_per_joule = (unsigned long long)(
				value *
				rotations_per_joule_multiplier 
			);
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value);

#endif // __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// compute energy-efficiency metrics (joules per work unit)
		//---------------------------------------------------------------------
		if(p->beziers != 0) {
			value =
				(double)p->beziers_joules /
				(double)p->beziers
			;
			p->joules_per_bezier = (unsigned long long)(value);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value / p->energy_data.energy_data_multiplier);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->translations != 0) {
			value =
				(double)p->translations_joules /
				(double)p->translations
			;
			p->joules_per_translation = (unsigned long long)(value);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value / p->energy_data.energy_data_multiplier);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->scales != 0) {
			value = 
				(double)p->scales_joules /
				(double)p->scales
			;
			p->joules_per_scale = (unsigned long long)(value);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(p->joules_per_scale / p->energy_data.energy_data_multiplier);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->rotations != 0) {
			value =
				(double)p->rotations_joules /
				(double)p->rotations
			;
			p->joules_per_rotation = (unsigned long long)(value);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value / p->energy_data.energy_data_multiplier);

#endif // __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// compute performance metrics
		//---------------------------------------------------------------------
		if(p->beziers != 0) {
			value =
				(double)p->beziers_ticks /
				(double)p->beziers
			;
			p->ticks_per_bezier = (unsigned long long)(
				value *	ticks_per_bezier_multiplier
			);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->translations != 0) {
			value = 
				(double)p->translations_ticks /
				(double)p->translations
			;
			p->ticks_per_translation = (unsigned long long)(
				value * ticks_per_translation_multiplier
			);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->scales != 0) {
			value =
				(double)p->scales_ticks /
				(double)p->scales
			;
			p->ticks_per_scale = (unsigned long long)(value * ticks_per_scale_multiplier);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value);

#endif // __MTI_SAMPLE_FILE_LOG__

		if(p->rotations != 0) {
			value =
				(double)p->rotations_ticks /
				(double)p->rotations
			;
			p->ticks_per_rotation = (unsigned long long)(
				value * ticks_per_rotation_multiplier
			);
		} else {
			value = 0.0;
		}

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// add data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(value);

#endif // __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// update non-suffix counters
		//---------------------------------------------------------------------
		bret = update_all_non_suffix_counters(p);
		assert(bret == SUCCESS);

#ifdef __MTI_SAMPLE_FILE_LOG__

		//---------------------------------------------------------------------
		// write log line to log file
		//---------------------------------------------------------------------
		strncat( \
			log_buffer, \
			MTI_SAMPLE_LOG_FILE_NEW_LINE, \
			strlen(MTI_SAMPLE_LOG_FILE_NEW_LINE) \
		);
		ret = (int)fwrite(
			log_buffer, 
			strlen(log_buffer), 
			sizeof(char), 
			px->log_file
		);
		assert(ret != 0);

#endif // #ifdef __MTI_SAMPLE_FILE_LOG__

	} // while f_running

metrics_thread_done:

	//-------------------------------------------------------------------------
	// signal thread end
	//-------------------------------------------------------------------------
	bret = SetEvent(
		p->metrics_thread_stoped_event
	);
	assert(bret != FALSE);

	return((LPTHREAD_START_ROUTINE)0);
}

/*-----------------------------------------------------------------------------
Function: get_esrv_pld
Purpose : return a valid ESRV PL descriptor (starts one if there is no shell
          variable (ESRV_GUID) defined.
In      : pointer to MTI instrumentation data
Out     : updated MTI instrumentation data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL get_esrv_pld(PMTI_SAMPLE_INSTRUMENTATION_DATA p) {
	
	//-------------------------------------------------------------------------
	// Generic variables.
	//-------------------------------------------------------------------------
	PL_STATUS plret = PL_FAILURE; 
	unsigned long long value = 0;
	char buffer[MAX_PATH] = { '\0' };

	//-------------------------------------------------------------------------
	// ESRV instance handling variables.
	//-------------------------------------------------------------------------
	char esrv_config_file_name_buffer[MAX_PATH] = { '\0' };
	char *env = NULL;

	//-------------------------------------------------------------------------
	// Variables used to build ESRV start command -- if we have to.
	//-------------------------------------------------------------------------
	char esrv_command_buffer[MAX_PATH] = { '\0' };

	//-------------------------------------------------------------------------
	// Variables used to read ESRV's startup output -- used to get the GUID
	//-------------------------------------------------------------------------
	char *pc = NULL;
	char *token = NULL;
	int input_line_count = 0;
	char esrv_guid[GUID_LENGHT_IN_CHARACTERS + 1] = { '\0' };

	//-------------------------------------------------------------------------
	// Initialize the energy data structure.
	//-------------------------------------------------------------------------
	memset(
		&p->energy_data, 
		0, 
		sizeof(ENERGY_DATA)
	);
	p->energy_data.channel = ENERGY_DEFAULT_CHANNEL;
	p->energy_data.esrv_pld = PL_INVALID_DESCRIPTOR;
	p->energy_data.esrv_status = ESRV_STATUS_NOT_RUNNING;

	//-------------------------------------------------------------------------
	// search for an ESRV shell variable.
	//-------------------------------------------------------------------------
	env = getenv(ENERGY_ESRV_DEFAULT_GUID_SHELL_VARIABLE); 
	if(env != NULL) {
		memcpy(
			esrv_config_file_name_buffer, 
			PL_CONFIG_FILE_ROOT, 
			strlen(PL_CONFIG_FILE_ROOT)
		);
		strncat(
			esrv_config_file_name_buffer, 
			ESRV_APPLICATION_NAME, 
			strlen(ESRV_APPLICATION_NAME)
		);
		strncat(
			esrv_config_file_name_buffer, 
			ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE, 
			strlen(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE)
		);
		strncat(
			esrv_config_file_name_buffer, 
			env, 
			strlen(env)
		);
		strncat(
			esrv_config_file_name_buffer, 
			PL_CONFIG_FILE_NAME_CHAR, 
			strlen(PL_CONFIG_FILE_NAME_CHAR)
		);
		goto attach_to_esrv;
	}

	//-------------------------------------------------------------------------
	// Build ESRV binary name and command line
	// Note:
	//   cli_buffer holds the ESRV binary name and the command line options.
	//   if the command and the arguments are provided separately to
	//   CreateProcess then the argv count is erroneous in the started 
	//   process and ESRV fails the cli parsing.
	//-------------------------------------------------------------------------
	memset(
		esrv_command_buffer, 
		0, 
		sizeof(esrv_command_buffer)
	);
	strncpy(
		esrv_command_buffer, 
		ENERGY_ESRV_BINARY_NAME, 
		strlen(ENERGY_ESRV_BINARY_NAME)
	);
	strncat(
		esrv_command_buffer, 
		ENERGY_ESRV_DEFAULT_OPTIONS, 
		strlen(ENERGY_ESRV_DEFAULT_OPTIONS)
	);
	strncat(
		esrv_command_buffer, 
		ENERGY_ESRV_SHELL_OPTION, 
		strlen(ENERGY_ESRV_SHELL_OPTION)
	);

	//-------------------------------------------------------------------------
	// Start an ESRV instance in a child process.
	//-------------------------------------------------------------------------
	p->energy_data.fp_esrv = _popen(
		esrv_command_buffer, 
		"rt"
	);
	assert(p->energy_data.fp_esrv != NULL);

	//-------------------------------------------------------------------------
	// Retrieve the ESRV's instance PID and GUID.
	//-------------------------------------------------------------------------
	do {
		pc = fgets(
			buffer, 
			sizeof(buffer), 
			p->energy_data.fp_esrv
		);
		if(pc != NULL) {
			switch(++input_line_count) {

				case ENERGY_ESRV_GUID_LINE:

					//---------------------------------------------------------
					// extract ESRV's GUID and save it
					//---------------------------------------------------------
					token = strtok(
						buffer, 
						ENERGY_ESRV_GUID_TOKEN_SEPARATORS
					);
					while(token != NULL) {
						if(strncmp(
							token, 
							ENERGY_ESRV_PRE_GUID_TOKEN, 
							strlen(ENERGY_ESRV_PRE_GUID_TOKEN)
						) == 0) { 
							token = strtok(
								NULL, 
								ENERGY_ESRV_GUID_TOKEN_TERMINATOR
							);
							memset(
								esrv_guid, 
								0, 
								sizeof(esrv_guid)
							);
							strncpy(
								esrv_guid, 
								token, 
								strlen(token)
							);
							p->energy_data.f_esrv_guid = TRUE;
							break;
						}
						token = strtok(
							NULL, 
							ENERGY_ESRV_GUID_TOKEN_SEPARATORS
						);
					}
					break;

				case ENERGY_ESRV_PID_LINE:

					//---------------------------------------------------------
					// extract ESRV's PID and save it.
					//---------------------------------------------------------
					token = strtok(
						buffer, 
						ENERGY_ESRV_PID_TOKEN_SEPARATORS
					);
					while(token != NULL) {
						if(strncmp(
							token, 
							ENERGY_ESRV_PRE_PID_TOKEN, 
							strlen(ENERGY_ESRV_PRE_PID_TOKEN)
						) == 0) { 
							token = strtok(
								NULL, 
								ENERGY_ESRV_PID_TOKEN_TERMINATOR
							);
							p->energy_data.esrv_pid = (DWORD)atoi(token);
							assert(p->energy_data.esrv_pid != 0);
							p->energy_data.f_esrv_pid = TRUE;
							goto pid_found;
						}
						token = strtok(
							NULL, 
							ENERGY_ESRV_GUID_TOKEN_SEPARATORS
						);
					}
					break;

				default:
					break;
			}
		} else {

			//-----------------------------------------------------------------
			// Likely the ESRV launch has failed, let's signal this error.
			//-----------------------------------------------------------------
			assert(0);
		}
	} while(pc != NULL);

	//-------------------------------------------------------------------------
	// Likely the ESRV launch has failed, let's signal this error.
	//-------------------------------------------------------------------------
	assert(0);

pid_found:

	//-------------------------------------------------------------------------
	// Check and build the pl_config.ini file to attach to.
	//-------------------------------------------------------------------------
	assert(
		(p->energy_data.f_esrv_guid == TRUE) && 
		(p->energy_data.f_esrv_pid == TRUE)
	);
	memset(
		esrv_config_file_name_buffer, 
		0, 
		sizeof(esrv_config_file_name_buffer)
	);
	memcpy(
		esrv_config_file_name_buffer, 
		PL_CONFIG_FILE_ROOT, 
		strlen(PL_CONFIG_FILE_ROOT)
	);
	strncat(
		esrv_config_file_name_buffer, 
		ESRV_APPLICATION_NAME, 
		strlen(ESRV_APPLICATION_NAME)
	);
	strncat(
		esrv_config_file_name_buffer, 
		ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE, 
		strlen(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE)
	);
	strncat(
		esrv_config_file_name_buffer, 
		esrv_guid, 
		strlen(esrv_guid)
	);
	memset(
		p->energy_data.esrv_pl_path_name, 
		0, 
		sizeof(p->energy_data.esrv_pl_path_name)
	);
	strncpy(
		p->energy_data.esrv_pl_path_name,
		esrv_config_file_name_buffer, 
		strlen(esrv_config_file_name_buffer)
	);
	strncat(
		esrv_config_file_name_buffer, 
		PL_CONFIG_FILE_NAME_CHAR, 
		strlen(PL_CONFIG_FILE_NAME_CHAR)
	);

	//-------------------------------------------------------------------------
	// remember that we have started ESRV
	//-------------------------------------------------------------------------
	p->energy_data.f_started_esrv = TRUE;

attach_to_esrv:

	//-------------------------------------------------------------------------
	// Attach to the identified instance of ESRV and read settings.
	//-------------------------------------------------------------------------
	p->energy_data.esrv_pld = pl_attach(
		esrv_config_file_name_buffer
	);
	assert(p->energy_data.esrv_pld != PL_INVALID_DESCRIPTOR);

	//-------------------------------------------------------------------------
	// read-in esrv's configuration:
	//  - ESRV Status (running or not)
	//  - ESRV Channel count
	//  - ESRV Version (not used)
	//  - ESRV energy in joule counter's precision
	// Note:
	//    since each channel holds esrv's configuration counters, we read the 
	//    first channel to read the channel count.  ESRV has always at least
	//    one channel, so the read is safe
	// Note:
	//    Channel count is zero count, therefore the --.
	//-------------------------------------------------------------------------
	plret = pl_read(
		p->energy_data.esrv_pld, 
		&p->energy_data.channels, 
		ESRV_COUNTER_CHANNELS_INDEX
	);
	assert(plret == PL_SUCCESS);
	assert(p->energy_data.channels >= 1);
	p->energy_data.channel = 1; 
	p->energy_data.channel--;

	//-------------------------------------------------------------------------
	// Now that the channels count is known, we can read the requested ESRV channel
	//-------------------------------------------------------------------------
	plret = pl_read(
		p->energy_data.esrv_pld, 
		&p->status, 
		(
			p->energy_data.channel * 
			ESRV_BASE_COUNTERS_COUNT
		) + 
		ESRV_COUNTER_STATUS_INDEX
	);
	assert(plret == PL_SUCCESS);
	if(p->energy_data.status != ESRV_STATUS_RUNNING) {
		// TODO:
		//_ERROR("The specified ESRV instance doesn't seem to be alive.");
	}
	plret = pl_read(
		p->energy_data.esrv_pld, 
		&p->energy_data.version, 
		(
			p->energy_data.channel * 
			ESRV_BASE_COUNTERS_COUNT
		) + 
		ESRV_COUNTER_VERSION_INDEX
	); 
	assert(plret == PL_SUCCESS);
	plret = pl_read(
		p->energy_data.esrv_pld, 
		&value, 
		(
			p->energy_data.channel * 
			ESRV_BASE_COUNTERS_COUNT
		) + 
		ESRV_COUNTER_ENERGY_JOULES_DECIMALS_INDEX
	); 
	assert(plret == PL_SUCCESS);
	p->energy_data.energy_data_multiplier = pow(
		10.0, 
		(double)value
	);
	plret = pl_read(
		p->energy_data.esrv_pld, 
		&value, 
		(
			p->energy_data.channel * 
			ESRV_BASE_COUNTERS_COUNT
		) + 
		ESRV_COUNTER_UPDATE_FREQUENCY_INDEX
	); 
	assert(plret == PL_SUCCESS);
	p->energy_data.update_interval_in_ms = 
		value *
		MTI_SAMPLE_MS_IN_ONE_S
	;

	plret = pl_read(
		p->energy_data.esrv_pld, 
		&value, 
		(
			p->energy_data.channel * 
			ESRV_BASE_COUNTERS_COUNT
		) + 
		ESRV_COUNTER_MAX_POWER_DECIMALS_INDEX
	); 
	assert(plret == PL_SUCCESS);
	p->energy_data.power_data_multiplier = pow(
		10.0, 
		(double)value
	);

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: remove_esrv
Purpose : kills ESRV if started earlier (remove PL) and close ESRV PL.
In      : pointer to MTI instrumentation data
Out     : updated MTI instrumentation data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL remove_esrv(PMTI_SAMPLE_INSTRUMENTATION_DATA p) {

	int ret = -1;
	BOOL bret = FALSE;

	//-------------------------------------------------------------------------
	// Variables used to remove ESRV PL after use -- if we started it.
	//-------------------------------------------------------------------------
	char current_path_name[MAX_PATH] = { '\0' };
	struct _finddata_t find_files;
	intptr_t file = 0;

	//-------------------------------------------------------------------------
	// Variables used to stop the ESRV process
	//-------------------------------------------------------------------------
	char *pc = NULL;
	DWORD esrv_pid = 0;
	HANDLE esrv_handle = NULL;

	assert(p != NULL);
	assert(p->energy_data.esrv_pld != PL_INVALID_DESCRIPTOR); 

	//-------------------------------------------------------------------------
	// close the ESRV PL descriptor
	//-------------------------------------------------------------------------
	if(p->energy_data.esrv_pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(
			p->energy_data.esrv_pld
		);
		assert(ret == PL_SUCCESS);
	}

	//-------------------------------------------------------------------------
	// close the ESRV instance's process and remove its PL
	//-------------------------------------------------------------------------
	if(
		(p->energy_data.f_esrv_guid == TRUE) && 
		(p->energy_data.f_esrv_pid == TRUE)
	) {
		esrv_handle = OpenProcess(
			PROCESS_TERMINATE, 
			FALSE, 
			p->energy_data.esrv_pid
		);
		assert(esrv_handle != NULL);
		bret = TerminateProcess(
			esrv_handle, 
			0
		);
		assert(bret != FALSE);

		//---------------------------------------------------------------------
		// close last ESRV instance's output stream
		//---------------------------------------------------------------------
		ret = _pclose(p->energy_data.fp_esrv);
		assert(ret != -1);

		//---------------------------------------------------------------------
		// Delete ESRV instance's PL.
		//---------------------------------------------------------------------
		pc = _getcwd(
			current_path_name, 
			(int)sizeof(current_path_name)
		); 
		assert(pc != NULL);		
		ret = _chdir(p->energy_data.esrv_pl_path_name); 
		assert(ret != -1);
		file = _findfirst("*", &find_files);
		do {
			if(
				(strcmp(find_files.name, ".") != 0) && 
				(strcmp(find_files.name, "..") != 0)
			) {
				ret = -1;
				do { 
					ret = remove(find_files.name); 
				} while(ret == -1);
			}
		} while(_findnext(file, &find_files) == 0);
		ret = _findclose(file); 
		assert(ret != -1);
		ret = _chdir(current_path_name); 
		assert(ret != -1);
		ret = -1;
		do { 
			ret = _rmdir(p->energy_data.esrv_pl_path_name); 
		} while(ret == -1);
	}

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: remove_esrv
Purpose : remove sampl's PL
In      : pointer to MTI instrumentation data
Out     : updated MTI instrumentation data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL remove_pl(PMTI_SAMPLE_INSTRUMENTATION_DATA p) {

	char *pc = NULL;
	int ret = -1;
	BOOL bret = FALSE;
	char *puuid = NULL;
	char pl_path_name_buffer[MAX_PATH] = { '\0' };
	RPC_STATUS rret = RPC_S_OUT_OF_MEMORY;
	size_t stret = 0;
	char buffer[GUID_LENGHT_IN_CHARACTERS + 1] = { '\0' };

	//-------------------------------------------------------------------------
	// variables used to remove PL
	//-------------------------------------------------------------------------
	char current_path_name[MAX_PATH] = { '\0' };
	struct _finddata_t find_files;
	intptr_t file = 0;

	assert(p != NULL);
	assert(p->energy_data.esrv_pld != PL_INVALID_DESCRIPTOR); 

	//-------------------------------------------------------------------------
	// close the PL
	//-------------------------------------------------------------------------
	if(p->pld != PL_INVALID_DESCRIPTOR) {
		ret = pl_close(
			p->pld
		);
		assert(ret == PL_SUCCESS);
	}

	//-------------------------------------------------------------------------
	// build PL foldername
	//-------------------------------------------------------------------------
	memset(
		pl_path_name_buffer, 
		0, 
		sizeof(pl_path_name_buffer)
	);
	memcpy(
		pl_path_name_buffer, 
		PL_CONFIG_FILE_ROOT, 
		strlen(PL_CONFIG_FILE_ROOT)
	);
	strncat(
		pl_path_name_buffer, 
		MTI_SAMPLE_APPLICATION_NAME, 
		strlen(MTI_SAMPLE_APPLICATION_NAME)
	);
	strncat(
		pl_path_name_buffer, 
		ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE, 
		strlen(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE)
	);
	rret = UuidToString(
		&p->uuid, 
		(RPC_WSTR *)&puuid
	);
	assert(rret == RPC_S_OK);
	wcstombs_s(
		&stret, 
		buffer, 
		sizeof(buffer), 
		(TCHAR *)puuid, 
		_TRUNCATE
	);
	strncat(
		pl_path_name_buffer, 
		buffer, 
		strlen(buffer)
	);

	//-------------------------------------------------------------------------
	// delete instance's PL
	//-------------------------------------------------------------------------
	pc = _getcwd(
		current_path_name, 
		(int)sizeof(current_path_name)
	); 
	assert(pc != NULL);		
	ret = _chdir(pl_path_name_buffer); 
	assert(ret != -1);
	file = _findfirst("*", &find_files);
	do {
		if(
			(strcmp(find_files.name, ".") != 0) && 
			(strcmp(find_files.name, "..") != 0)
		) {
			ret = -1;
			do { 
				ret = remove(find_files.name); 
			} while(ret == -1);
		}
	} while(_findnext(file, &find_files) == 0);
	ret = _findclose(file); 
	assert(ret != -1);
	ret = _chdir(current_path_name); 
	assert(ret != -1);
	ret = -1;
	do { 
		ret = _rmdir(pl_path_name_buffer); 
	} while(ret == -1);

	rret = RpcStringFree((RPC_WSTR *)&puuid);
	assert(rret == RPC_S_OK);
	puuid = NULL;
	
	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: update_bezier_instrumentation_data
Purpose : update instrumentation data
In      : pointer to MTI data
Out     : updated MTI instrumentation data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
*/
BOOL update_bezier_instrumentation_data(PMTI_SAMPLE_DATA p) {

	unsigned long long power = 0;
	unsigned long long ms = 0;
	unsigned long long remainder_ms = 0;
	PL_STATUS ret = PL_FAILURE;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// update instrumentation data
	//-------------------------------------------------------------------------

	if(p->geometry_data.points_count == MTI_SAMPLE_BEZIER_CURVE_PRESENT) {

		//---------------------------------------------------------------------
		// update work data
		//---------------------------------------------------------------------
		p->instrumentation_data.beziers++;

		//---------------------------------------------------------------------
		// update timing data
		//---------------------------------------------------------------------
		p->instrumentation_data.beziers_ticks_stop = 
			(unsigned long long)GetTickCount()
		;
		ms =
			p->instrumentation_data.beziers_ticks_stop -
			p->instrumentation_data.beziers_ticks_start
		;
		p->instrumentation_data.beziers_ticks += ms;

		//---------------------------------------------------------------------
		// update energy data
		//---------------------------------------------------------------------
		ret = pl_read(
			p->instrumentation_data.energy_data.esrv_pld,
			&p->instrumentation_data.beziers_joules_stop,
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		assert(ret == PL_SUCCESS);
		if(
			p->instrumentation_data.beziers_joules_start <
			p->instrumentation_data.beziers_joules_stop
		) {
			p->instrumentation_data.beziers_joules += 
				p->instrumentation_data.beziers_joules_stop -
				p->instrumentation_data.beziers_joules_start
			;
			remainder_ms = 
				ms % 
				p->instrumentation_data.energy_data.update_interval_in_ms
			;
			if(remainder_ms != 0) {
				ret = pl_read(
					p->instrumentation_data.energy_data.esrv_pld,
					&power,
					ESRV_COUNTER_MAX_POWER_INDEX
				);
				assert(ret == PL_SUCCESS);
				p->instrumentation_data.beziers_joules += 
					(unsigned long long) (
						(double)power *
						(double)ms /
						(double)MTI_SAMPLE_MS_IN_ONE_S /
						p->instrumentation_data.energy_data.power_data_multiplier *
						p->instrumentation_data.energy_data.energy_data_multiplier
					)			
				;
			}
		} else {
			ret = pl_read(
				p->instrumentation_data.energy_data.esrv_pld,
				&power,
				ESRV_COUNTER_MAX_POWER_INDEX
			);
			assert(ret == PL_SUCCESS);
			p->instrumentation_data.beziers_joules += 
				(unsigned long long) (
					(double)power *
					(double)ms /
					(double)MTI_SAMPLE_MS_IN_ONE_S /
					p->instrumentation_data.energy_data.power_data_multiplier *
					p->instrumentation_data.energy_data.energy_data_multiplier
				)
			;
		}
		p->instrumentation_data.beziers_ticks_start = 0;
		p->instrumentation_data.beziers_ticks_stop = 0;
		p->instrumentation_data.beziers_joules_start = 0;
		p->instrumentation_data.beziers_joules_stop = 0;
	}

	if(p->geometry_data.points_count == MTI_SAMPLE_FIRST_ANCHOR_PRESENT) {

		//---------------------------------------------------------------------
		// update energy data
		//---------------------------------------------------------------------
		ret = pl_read(
			p->instrumentation_data.energy_data.esrv_pld,
			&p->instrumentation_data.beziers_joules_start,
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		assert(ret == PL_SUCCESS);

		//---------------------------------------------------------------------
		// update timing data
		//---------------------------------------------------------------------
		p->instrumentation_data.beziers_ticks_start = 
			(unsigned long long)GetTickCount()
		;
	}

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: update_transformations_instrumentation_data
Purpose : update instrumentation data
In      : pointer to MTI data
Out     : updated MTI instrumentation data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/16/2010    Jamel Tayeb             Creation.
08/22/2010    Jamel Tayeb             Added support for per gesture file logging.
*/
BOOL update_transformations_instrumentation_data(PMTI_SAMPLE_DATA p) {
	
	unsigned long long j = 0;
	unsigned long long power = 0;
	unsigned long long ms = 0;
	unsigned long long remainder_ms = 0;
	PL_STATUS ret = PL_FAILURE;

#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

	//-------------------------------------------------------------------------
	// variables used to manage file logging
	//-------------------------------------------------------------------------
	size_t stret = 0;
	errno_t eret = 0;
	time_t log_time;
	static BOOL f_header_done = FALSE;
	static unsigned long long gesture_serial_number = 1;
	char log_buffer[] = MTI_SAMPLE_LOG_FILE_HEADER;
	char cvt_buffer[MTI_SAMPLE_TIME_BUFFER_SIZE] = { '\0' };
	char time_buffer[MTI_SAMPLE_TIME_BUFFER_SIZE] = { '\0' };

#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

	assert(p != NULL);

#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

	if(f_header_done == FALSE) {

		//-------------------------------------------------------------------------
		// write log file header
		//-------------------------------------------------------------------------
		stret = fwrite(
			log_buffer, 
			strlen(log_buffer), 
			sizeof(char), 
			p->log_file
		);
		assert(stret != 0);
		f_header_done = TRUE;

	}
	
	if(
		(p->interface_data.transformation & TRANSLATE) ||
		(p->interface_data.transformation & SCALE) ||		
		(p->interface_data.transformation & ROTATE)		
	) {

		//---------------------------------------------------------------------
		// add time stamp to log buffer
		//---------------------------------------------------------------------
		memset(
			log_buffer, 
			0,
			sizeof(log_buffer)
		);
		time(&log_time);
		eret = ctime_s(
			time_buffer, 
			sizeof(time_buffer), 
			&log_time
		);
		assert(eret == 0);
		strncpy(
			&time_buffer[MTI_SAMPLE_TIME_STAMP_OFFSET], 
			MTI_SAMPLE_LOG_FILE_SEPARATOR, 
			strlen(MTI_SAMPLE_LOG_FILE_SEPARATOR)
		);
		time_buffer[MTI_SAMPLE_TIME_STAMP_END_OFFSET] = '\0';
		strncat(
			log_buffer, 
			time_buffer, 
			sizeof(time_buffer)
		);

		//---------------------------------------------------------------------
		// add gesture serial number
		//---------------------------------------------------------------------
		LOG_ULL(gesture_serial_number);
		gesture_serial_number++;

		//---------------------------------------------------------------------
		// add gesture type
		//---------------------------------------------------------------------
		if(p->interface_data.transformation & TRANSLATE) {
			LOG_STRING(MTI_SAMPLE_LOG_FILE_TRANSLATE_STRING);
		}
		if(p->interface_data.transformation & SCALE) {
			LOG_STRING(MTI_SAMPLE_LOG_FILE_SCALE_STRING);
		}
		if(p->interface_data.transformation & ROTATE) {
			LOG_STRING(MTI_SAMPLE_LOG_FILE_ROTATE_STRING);
		}
	}

#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

	//-------------------------------------------------------------------------
	// update instrumentation data
	//-------------------------------------------------------------------------
	if(p->interface_data.transformation & TRANSLATE) {

		//---------------------------------------------------------------------
		// update translation work data
		//---------------------------------------------------------------------
		p->instrumentation_data.translations++;

		//---------------------------------------------------------------------
		// update translation timing data
		//---------------------------------------------------------------------
		p->instrumentation_data.translations_ticks_stop = 
			(unsigned long long)GetTickCount()
		;
		ms =
			p->instrumentation_data.translations_ticks_stop -
			p->instrumentation_data.translations_ticks_start
		;
		p->instrumentation_data.translations_ticks += ms;

		//---------------------------------------------------------------------
		// update translation energy data
		//---------------------------------------------------------------------
		ret = pl_read(
			p->instrumentation_data.energy_data.esrv_pld,
			&p->instrumentation_data.translations_joules_stop,
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		assert(ret == PL_SUCCESS);
		if(
			p->instrumentation_data.translations_joules_start <
			p->instrumentation_data.translations_joules_stop
		) {
			j =
				p->instrumentation_data.translations_joules_stop -
				p->instrumentation_data.translations_joules_start
			;
			p->instrumentation_data.translations_joules += j; 
			remainder_ms = 
				ms % 
				p->instrumentation_data.energy_data.update_interval_in_ms
			;
			if(remainder_ms != 0) {
				ret = pl_read(
					p->instrumentation_data.energy_data.esrv_pld,
					&power,
					ESRV_COUNTER_MAX_POWER_INDEX
				);
				assert(ret == PL_SUCCESS);
				j +=
					(unsigned long long) (
						(double)power *
						(double)ms /
						(double)MTI_SAMPLE_MS_IN_ONE_S /
						p->instrumentation_data.energy_data.power_data_multiplier *
						p->instrumentation_data.energy_data.energy_data_multiplier
					)
				;
				p->instrumentation_data.translations_joules += j; 
			}
		} else {
			ret = pl_read(
				p->instrumentation_data.energy_data.esrv_pld,
				&power,
				ESRV_COUNTER_MAX_POWER_INDEX
			);
			assert(ret == PL_SUCCESS);
			j =
				(unsigned long long) (
					(double)power *
					(double)ms /
					(double)MTI_SAMPLE_MS_IN_ONE_S /
					p->instrumentation_data.energy_data.power_data_multiplier *
					p->instrumentation_data.energy_data.energy_data_multiplier
				)
			;
			p->instrumentation_data.translations_joules += j;
		}

#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

		//---------------------------------------------------------------------
		// add time data to log buffer
		//---------------------------------------------------------------------
		LOG_ULL(ms);

		//---------------------------------------------------------------------
		// add energy data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(
			(double)j / 
			p->instrumentation_data.energy_data.energy_data_multiplier
		);

#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

		p->instrumentation_data.translations_ticks_start = 0;
		p->instrumentation_data.translations_ticks_stop = 0;		
		p->instrumentation_data.translations_joules_stop = 0;
		p->instrumentation_data.translations_joules_start = 0;
	}

	if(p->interface_data.transformation & SCALE) {

		//---------------------------------------------------------------------
		// update scale work data
		//---------------------------------------------------------------------
		p->instrumentation_data.scales++;

		//---------------------------------------------------------------------
		// update scale timing data
		//---------------------------------------------------------------------
		p->instrumentation_data.scales_ticks_stop = 
			(unsigned long long)GetTickCount()
		;
		ms = 
			p->instrumentation_data.scales_ticks_stop -
			p->instrumentation_data.scales_ticks_start
		;
		p->instrumentation_data.scales_ticks += ms;

		//---------------------------------------------------------------------
		// update scale energy data
		//---------------------------------------------------------------------
		ret = pl_read(
			p->instrumentation_data.energy_data.esrv_pld,
			&p->instrumentation_data.scales_joules_stop,
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		if(
			p->instrumentation_data.scales_joules_start <
			p->instrumentation_data.scales_joules_stop
		) {
			j =
				p->instrumentation_data.scales_joules_stop -
				p->instrumentation_data.scales_joules_start
			;
			p->instrumentation_data.scales_joules += j;
			remainder_ms = 
				ms % 
				p->instrumentation_data.energy_data.update_interval_in_ms
			;
			if(remainder_ms != 0) {
				ret = pl_read(
					p->instrumentation_data.energy_data.esrv_pld,
					&power,
					ESRV_COUNTER_MAX_POWER_INDEX
				);
				assert(ret == PL_SUCCESS);
				j =
					(unsigned long long) (
						(double)power *
						(double)ms /
						(double)MTI_SAMPLE_MS_IN_ONE_S /
						p->instrumentation_data.energy_data.power_data_multiplier *
						p->instrumentation_data.energy_data.energy_data_multiplier
					)
				;
				p->instrumentation_data.scales_joules += j;
			}
		} else {
			ret = pl_read(
				p->instrumentation_data.energy_data.esrv_pld,
				&power,
				ESRV_COUNTER_MAX_POWER_INDEX
			);
			assert(ret == PL_SUCCESS);
			j =
				(unsigned long long) (
					(double)power *
					(double)ms /
					(double)MTI_SAMPLE_MS_IN_ONE_S /
					p->instrumentation_data.energy_data.power_data_multiplier *
					p->instrumentation_data.energy_data.energy_data_multiplier
				)
			;
			p->instrumentation_data.scales_joules += j;
		}

#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

		//---------------------------------------------------------------------
		// add time data to log buffer
		//---------------------------------------------------------------------
		LOG_ULL(ms);

		//---------------------------------------------------------------------
		// add energy data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(
			(double)j / 
			p->instrumentation_data.energy_data.energy_data_multiplier
		);

#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

		p->instrumentation_data.scales_ticks_start = 0;
		p->instrumentation_data.scales_ticks_stop = 0;
		p->instrumentation_data.scales_joules_stop = 0;
		p->instrumentation_data.scales_joules_start = 0;
	}

	if(p->interface_data.transformation & ROTATE) {

		//---------------------------------------------------------------------
		// update rotation work data
		//---------------------------------------------------------------------
		p->instrumentation_data.rotations++;

		//---------------------------------------------------------------------
		// update rotation timing data
		//---------------------------------------------------------------------
		p->instrumentation_data.rotations_ticks_stop = 
			(unsigned long long)GetTickCount()
		;
		ms =
			p->instrumentation_data.rotations_ticks_stop -
			p->instrumentation_data.rotations_ticks_start
		;
		p->instrumentation_data.rotations_ticks += ms;

		//---------------------------------------------------------------------
		// update rotation energy data
		//---------------------------------------------------------------------
		ret = pl_read(
			p->instrumentation_data.energy_data.esrv_pld,
			&p->instrumentation_data.rotations_joules_stop,
			ESRV_COUNTER_ENERGY_JOULES_INDEX
		);
		assert(ret == PL_SUCCESS);
		if(
			p->instrumentation_data.rotations_joules_start <
			p->instrumentation_data.rotations_joules_stop
		) {
			j =
				p->instrumentation_data.rotations_joules_stop -
				p->instrumentation_data.rotations_joules_start
			;
			p->instrumentation_data.rotations_joules += j;
			remainder_ms = 
				ms % 
				p->instrumentation_data.energy_data.update_interval_in_ms
			;
			if(remainder_ms != 0) {
				ret = pl_read(
					p->instrumentation_data.energy_data.esrv_pld,
					&power,
					ESRV_COUNTER_MAX_POWER_INDEX
				);
				assert(ret == PL_SUCCESS);
				j =
					(unsigned long long) (
						(double)power *
						(double)ms /
						(double)MTI_SAMPLE_MS_IN_ONE_S /
						p->instrumentation_data.energy_data.power_data_multiplier *
						p->instrumentation_data.energy_data.energy_data_multiplier
					)
				;
				p->instrumentation_data.rotations_joules += j;
			}
		} else {
			ret = pl_read(
				p->instrumentation_data.energy_data.esrv_pld,
				&power,
				ESRV_COUNTER_MAX_POWER_INDEX
			);
			assert(ret == PL_SUCCESS);
			j =
				(unsigned long long) (
					(double)power *
					(double)ms /
					(double)MTI_SAMPLE_MS_IN_ONE_S /
					p->instrumentation_data.energy_data.power_data_multiplier *
					p->instrumentation_data.energy_data.energy_data_multiplier
				)
			;
			p->instrumentation_data.rotations_joules += j;
		}

#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

		//---------------------------------------------------------------------
		// add time data to log buffer
		//---------------------------------------------------------------------
		LOG_ULL(ms);

		//---------------------------------------------------------------------
		// add energy data to log buffer
		//---------------------------------------------------------------------
		LOG_DOUBLE(
			(double)j / 
			p->instrumentation_data.energy_data.energy_data_multiplier
		);

#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

		p->instrumentation_data.rotations_ticks_start = 0;
		p->instrumentation_data.rotations_ticks_stop = 0;
		p->instrumentation_data.rotations_joules_stop = 0;
		p->instrumentation_data.rotations_joules_start = 0;
	}

#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

		//---------------------------------------------------------------------
		// write log line to log file
		//---------------------------------------------------------------------
		strncat( \
			log_buffer, \
			MTI_SAMPLE_LOG_FILE_NEW_LINE, \
			strlen(MTI_SAMPLE_LOG_FILE_NEW_LINE) \
		);
		stret = fwrite(
			log_buffer, 
			strlen(log_buffer), 
			sizeof(char), 
			p->log_file
		);
		assert(stret != 0);

#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

	return(SUCCESS);
}

#ifdef __MTI_SAMPLE_GUI_MONITOR__

/*-----------------------------------------------------------------------------
Function: start_pl_gui_monitor
Purpose : start pl_gui_monitor instance
In      : pointer to MTI data
Out     : updated MTI instrumentation data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/22/2010    Jamel Tayeb             Creation.
*/
BOOL start_pl_gui_monitor(PMTI_SAMPLE_DATA p) {

	size_t stret = 0;
	char *puuid = NULL;
	char char_buffer[GUID_LENGHT_IN_CHARACTERS + 1] = { '\0' };
	TCHAR pl_path_name_buffer[MAX_PATH] = { '\0' };
	TCHAR pl_gui_monitor_command_buffer[MAX_PATH] = { '\0' };
	TCHAR buffer[GUID_LENGHT_IN_CHARACTERS + 1] = { '\0' };
	RPC_STATUS rret = RPC_S_OUT_OF_MEMORY;
    STARTUPINFO si;
	BOOL bret = FALSE;

	assert(p != NULL);

	//---------------------------------------------------------------------
	// build PL foldername
	//---------------------------------------------------------------------
	memset(
		pl_path_name_buffer, 
		0, 
		sizeof(pl_path_name_buffer)
	);
	memcpy(
		pl_path_name_buffer, 
		_T(PL_CONFIG_FILE_ROOT), 
		_tcslen(_T(PL_CONFIG_FILE_ROOT)) * sizeof(TCHAR)
	);
	_tcsncat(
		pl_path_name_buffer, 
		_T(MTI_SAMPLE_APPLICATION_NAME), 
		_tcslen(_T(MTI_SAMPLE_APPLICATION_NAME))
	);
	_tcsncat(
		pl_path_name_buffer, 
		_T(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE), 
		_tcslen(_T(ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE))
	);
	rret = UuidToString(
		&p->instrumentation_data.uuid, 
		(RPC_WSTR *)&puuid
	);
	assert(rret == RPC_S_OK);
	wcstombs_s(
		&stret, 
		char_buffer, 
		sizeof(char_buffer), 
		(TCHAR *)puuid, 
		_TRUNCATE
	);
	stret = mbstowcs(
		buffer, 
		char_buffer, 
		strlen(char_buffer)
	);
	_tcsncat(
		pl_path_name_buffer, 
		buffer, 
		_tcslen(buffer)
	);
	_tcsncat(
		pl_path_name_buffer, 
		_T(PL_CONFIG_FILE_NAME_CHAR), 
		_tcslen(_T(PL_CONFIG_FILE_NAME_CHAR))
	);

	//-------------------------------------------------------------------------
	// build the start command.
	//-------------------------------------------------------------------------
	_stprintf_s(
		pl_gui_monitor_command_buffer,
		sizeof(pl_gui_monitor_command_buffer) / sizeof(TCHAR),
		_T("%s%s%s"),
		_T(GUI_MONITOR_BINARY_NAME),
		_T(GUI_MONITOR_DEFAULT_OPTIONS),
		pl_path_name_buffer
	);

	//-------------------------------------------------------------------------
	// start a pl_gui_monitor instance in a child process.
	//-------------------------------------------------------------------------
	memset(
		&si,
		0,
		sizeof(si)
	);
    si.cb = sizeof(si);
	si.dwFlags =  STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWMINIMIZED;
    memset(
		&p->instrumentation_data.pi, 
		0,
		sizeof(p->instrumentation_data.pi)
	);
	bret = CreateProcess(
		NULL,
		pl_gui_monitor_command_buffer,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&p->instrumentation_data.pi
	);
	assert(bret != FALSE);

	//-------------------------------------------------------------------------
	// house keeping
	//-------------------------------------------------------------------------
	rret = RpcStringFree((RPC_WSTR *)&puuid);
	assert(rret == RPC_S_OK);
	puuid = NULL;

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: stop_pl_gui_monitor
Purpose : strop pl_gui_monitor instance
In      : pointer to MTI data
Out     : updated MTI instrumentation data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/22/2010    Jamel Tayeb             Creation.
*/
BOOL stop_pl_gui_monitor(PMTI_SAMPLE_DATA p) {

	HANDLE pl_gui_monitor_handle = NULL;
	BOOL bret = FALSE;

	assert(p != NULL);

	pl_gui_monitor_handle = OpenProcess(
		PROCESS_TERMINATE, 
		FALSE, 
		p->instrumentation_data.pi.dwProcessId
	);
	assert(pl_gui_monitor_handle != NULL);

	bret = TerminateProcess(
		pl_gui_monitor_handle, 
		0
	);
	assert(bret != FALSE);

	return(SUCCESS);
}

#endif // __MTI_SAMPLE_GUI_MONITOR__

#endif // __MTI_SAMPLE_INSTRUMENTED__

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

/*-----------------------------------------------------------------------------
Function: clear_touch_contact_ids
Purpose : clear the id store.
In      : pointer to MTI interface data
Out     : updated MTI interface data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
09/01/2010    Jamel Tayeb             Creation.
*/
BOOL clear_touch_contact_ids(PMTI_SAMPLE_INTERFACE_DATA p) {

	int i = 0;

	assert(p != NULL);

	p->touch_contacts_sequence_ids_count = 0;
	for(
		i = 0; 
		i < MTI_SAMPLE_MTI_TOUCH_CODE_MAX_TOUCH_CONTACTS_SEQUENCES; 
		i++
		) {
		p->touch_contacts_sequence_ids[i] = 
			MTI_SAMPLE_MTI_TOUCH_CODE_TOUCH_CONTACTS_SEQUENCES_SENTINEL_ID
		;
	} // for i

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: store_touch_contact_id
Purpose : add a touch contact id to the id store - add only new ids.
In      : pointer to MTI interface data
Out     : updated MTI interface data
Return  : ids count

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
09/01/2010    Jamel Tayeb             Creation.
*/
int store_touch_contact_id(PMTI_SAMPLE_INTERFACE_DATA p, DWORD d) {

	int i = 0;

#ifdef _DEBUG

	int j = 0;
	TCHAR buffer[MAX_PATH] = { 0 };
	TCHAR buffer2[MAX_PATH] = { 0 };

#endif // _DEBUG

	assert(p != NULL);
	assert(
		p->touch_contacts_sequence_ids_count + 1 <
		MTI_SAMPLE_MTI_TOUCH_CODE_MAX_TOUCH_CONTACTS_SEQUENCES
	);

	//-------------------------------------------------------------------------
	// search the id
	//-------------------------------------------------------------------------
	for(
		i = 0; 
		i < p->touch_contacts_sequence_ids_count; 
		i++
	) {
		if(p->touch_contacts_sequence_ids[i] == d) {
			goto store_touch_contact_id_found;
		}
	}

	//-------------------------------------------------------------------------
	// add the id
	//-------------------------------------------------------------------------
	assert(i >= 0);
	assert(i < MTI_SAMPLE_MTI_TOUCH_CODE_MAX_TOUCH_CONTACTS_SEQUENCES);
	assert(
		p->touch_contacts_sequence_ids[i] == 
		MTI_SAMPLE_MTI_TOUCH_CODE_TOUCH_CONTACTS_SEQUENCES_SENTINEL_ID
	);
	p->touch_contacts_sequence_ids[i] = d;
	p->touch_contacts_sequence_ids_count++;

#ifdef _DEBUG

	if(p->touch_contacts_sequence_ids_count > 1) {
		wsprintf(
			buffer,
			_T("Touche ids = %d - ids are: "),
			p->touch_contacts_sequence_ids_count
		);
		for(j = 0; j < p->touch_contacts_sequence_ids_count; j++) {
			wsprintf(
				buffer2,
				_T("%d "),
				p->touch_contacts_sequence_ids[j]
			);
			_tcsncat(
				buffer,
				buffer2,
				_tcsnlen(buffer, sizeof(buffer))
			);
		}
		MessageBox(
			NULL,
			buffer,
			_T("GLOBAL Touch Info"),
			MB_OK
		);
	}

#endif // _DEBUG

store_touch_contact_id_found:

	//-------------------------------------------------------------------------
	// return the ids count 
	//-------------------------------------------------------------------------
	return(p->touch_contacts_sequence_ids_count);
}

#else // __MTI_SAMPLE_MTI_TOUCH_CODE__

/*-----------------------------------------------------------------------------
Function: process_zoom
Purpose : process the zoom gesture
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/23/2010    Jamel Tayeb             Creation.
*/
BOOL process_zoom(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;
	DWORD distance = 0;
	static DWORD initial_distance = 0;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// do nothing if help is displayed
	//-------------------------------------------------------------------------
	if(p->interface_data.f_in_help == TRUE) {
		goto process_zoom_done;
	}

	//-------------------------------------------------------------------------
	// Note:
	//    the zoom gesture messages provides the following information:
	//    - the first message doesn't zoom (during the gesture begin [GF_BEGIN])
	//    - the zoom center point (during all other messages)
	//    - the distance between the two fingers' positions (in ullArguments
	//    that you can extract using the LODWORD macro)
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// get gesture related position
	//-------------------------------------------------------------------------
	p->interface_data.xpos = p->interface_data.gesture_info.ptsLocation.x;
	p->interface_data.ypos = p->interface_data.gesture_info.ptsLocation.y;

	//-------------------------------------------------------------------------
	// use the dwFlags to determine where we are in the gesture
	// Note:
	//    we do not process intertia (GF_INERTIA) since it doesn't make sense
	//    to our sample code.
	//-------------------------------------------------------------------------
	if(p->interface_data.gesture_info.dwFlags & GF_BEGIN) {

		//---------------------------------------------------------------------
		// perform a right mouse button down operation - this detects if an
		// existing control point was selected by the user (and sets all the 
		// data for energy and performance measurements - if applicable).
		//---------------------------------------------------------------------
		bret = process_mouse_right_button_down(p);
		assert(bret == SUCCESS);

		//---------------------------------------------------------------------
		// store the initial distance between the two fingers
		//---------------------------------------------------------------------
		initial_distance = LODWORD(
			p->interface_data.gesture_info.ullArguments
		);

	} else {

		if(p->interface_data.gesture_info.dwFlags & GF_END) {

			//-----------------------------------------------------------------
			// perform a right mouse button up operation - this sets all the 
			// data for energy and performance measurements - if applicable.
			// it also resets all transformation information.
			//-----------------------------------------------------------------
			bret = process_mouse_right_button_up(p);
			assert(bret == SUCCESS);

			//-----------------------------------------------------------------
			// house keeping
			//-----------------------------------------------------------------
			initial_distance = 0;
			p->interface_data.scale_coefficient = 0.0;
			p->interface_data.center.x = 0;
			p->interface_data.center.y = 0;

		} else {

			//-----------------------------------------------------------------
			// get the new distance between the two fingers
			//-----------------------------------------------------------------
			distance = LODWORD(
				p->interface_data.gesture_info.ullArguments
			);

			//-----------------------------------------------------------------
			// compute the zoom scale coefficient
			// Note:
			//    if needed, the zoom center could be computed as:
			//      center.x = (
			//         first_zoom_point.x + 
			//         second_zoom_point.x
			//      ) / 2;
			//      center.y = (
			//         first_zoom_point.y + 
			//         second_zoom_point.y
			//      ) / 2;
			//-----------------------------------------------------------------
			p->interface_data.scale_coefficient = (
				(double)distance /
				(double)initial_distance
			);

			//---------------------------------------------------------------------
			// store the zoom center point -- needed for transformation visual 
			// feedback
			//---------------------------------------------------------------------
			p->interface_data.center.x = p->interface_data.xpos;
			p->interface_data.center.y = p->interface_data.ypos;

			//-----------------------------------------------------------------
			// set transformation
			//-----------------------------------------------------------------
			p->interface_data.transformation = (MTI_SAMPLE_TRANSFORMATION)(
				(int)p->interface_data.transformation |
				SCALE
			);

			//-----------------------------------------------------------------
			// perform a mouse move operation - this performs the zoom gesture
			//-----------------------------------------------------------------
			bret = process_mouse_move(p);
			assert(bret == SUCCESS);

			//-----------------------------------------------------------------
			// make the current distance the initial distance
			//-----------------------------------------------------------------
			initial_distance = distance;

			//-----------------------------------------------------------------
			// ask for redraw
			//-----------------------------------------------------------------
			bret = InvalidateRect(
				p->interface_data.hwnd,
				NULL,
				TRUE
			);
			assert(bret == TRUE);
			PostMessage(
				p->interface_data.hwnd,
				WM_PAINT,
				0,
				0
			);
			assert(bret == TRUE);
		}
	}

process_zoom_done:

	return(SUCCESS);

}

/*-----------------------------------------------------------------------------
Function: process_pan
Purpose : process the pan gesture
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/23/2010    Jamel Tayeb             Creation.
*/
BOOL process_pan(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// do nothing if help is displayed
	//-------------------------------------------------------------------------
	if(p->interface_data.f_in_help == TRUE) {
		goto process_pan_done;
	}

	//-------------------------------------------------------------------------
	// set transformation
	//-------------------------------------------------------------------------
	p->interface_data.transformation = (MTI_SAMPLE_TRANSFORMATION)(
		(int)p->interface_data.transformation |
		TRANSLATE
	);

	//-------------------------------------------------------------------------
	// get gesture related position
	//-------------------------------------------------------------------------
	p->interface_data.xpos = p->interface_data.gesture_info.ptsLocation.x;
	p->interface_data.ypos = p->interface_data.gesture_info.ptsLocation.y;

	//-------------------------------------------------------------------------
	// use the dwFlags to determine where we are in the gesture
	// Note:
	//    we do not process intertia (GF_INERTIA) since it doesn't make sense
	//    to our sample code.
	//-------------------------------------------------------------------------
	if(p->interface_data.gesture_info.dwFlags & GF_BEGIN) {

		//---------------------------------------------------------------------
		// perform a right mouse button down operation - this detects if an
		// existing control point was selected by the user (and sets all the 
		// data for energy and performance measurements - if applicable).
		//---------------------------------------------------------------------
		bret = process_mouse_right_button_down(p);
		assert(bret == SUCCESS);

	} else {

		if(p->interface_data.gesture_info.dwFlags & GF_END) {

			//-----------------------------------------------------------------
			// perform a right mouse button up operation - this sets all the 
			// data for energy and performance measurements - if applicable.
			// it also resets all transformation information.
			//-----------------------------------------------------------------
			bret = process_mouse_right_button_up(p);
			assert(bret == SUCCESS);

		} else {

			//-----------------------------------------------------------------
			// perform a mouse move operation - this performs the pan gesture
			//-----------------------------------------------------------------
			if(
				(p->interface_data.f_point_selected == TRUE) ||
				(p->interface_data.f_bbox_selected == TRUE)
			) {
				bret = process_mouse_move(p);
				assert(bret == SUCCESS);
			}
		}
	}

	//-------------------------------------------------------------------------
	// ask for redraw
	//-------------------------------------------------------------------------
	bret = InvalidateRect(
		p->interface_data.hwnd,
		NULL,
		TRUE
	);
	assert(bret == TRUE);
	PostMessage(
		p->interface_data.hwnd,
		WM_PAINT,
		0,
		0
	);
	assert(bret == TRUE);

process_pan_done:

		return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: process_rotate
Purpose : process the rotate gesture
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/23/2010    Jamel Tayeb             Creation.
*/
BOOL process_rotate(PMTI_SAMPLE_DATA p) {

	BOOL bret = FALSE;
	DWORD angle = 0;

	assert(p != NULL);

	//-------------------------------------------------------------------------
	// do nothing if help is displayed
	//-------------------------------------------------------------------------
	if(p->interface_data.f_in_help == TRUE) {
		goto process_rotate_done;
	}

	//-------------------------------------------------------------------------
	// Note:
	//    the rotate gesture messages provides the following information:
	//    - the first message doesn't rotate (during the gesture begin
	//    [GF_BEGIN])
	//    - the rotation center point (during all other messages)
	//    - the cumulative rotation angle relative to first position (in 
	//    ullArguments that you can extract using the LODWORD macro)
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// get gesture related position
	//-------------------------------------------------------------------------
	p->interface_data.xpos = p->interface_data.gesture_info.ptsLocation.x;
	p->interface_data.ypos = p->interface_data.gesture_info.ptsLocation.y;

	//-------------------------------------------------------------------------
	// use the dwFlags to determine where we are in the gesture
	// Note:
	//    we do not process intertia (GF_INERTIA) since it doesn't make sense
	//    to our sample code.
	//-------------------------------------------------------------------------
	if(p->interface_data.gesture_info.dwFlags & GF_BEGIN) {

		//---------------------------------------------------------------------
		// perform a right mouse button down operation - this detects if an
		// existing control point was selected by the user (and sets all the 
		// data for energy and performance measurements - if applicable).
		//---------------------------------------------------------------------
		bret = process_mouse_right_button_down(p);
		assert(bret == SUCCESS);

	} else {

		if(p->interface_data.gesture_info.dwFlags & GF_END) {

			//-----------------------------------------------------------------
			// perform a right mouse button up operation - this sets all the 
			// data for energy and performance measurements - if applicable.
			// it also resets all transformation information.
			//-----------------------------------------------------------------
			bret = process_mouse_right_button_up(p);
			assert(bret == SUCCESS);

			//-----------------------------------------------------------------
			// house keeping
			//-----------------------------------------------------------------
			p->interface_data.rotation_angle = 0.0;
			p->interface_data.center.x = 0;
			p->interface_data.center.y = 0;

		} else {

			//-----------------------------------------------------------------
			// get the angle
			//-----------------------------------------------------------------
			angle = LODWORD(
				p->interface_data.gesture_info.ullArguments
			);

			//-----------------------------------------------------------------
			// get the rotation angle
			//-----------------------------------------------------------------
			p->interface_data.rotation_angle = 
				GID_ROTATE_ANGLE_FROM_ARGUMENT(angle)
			;

			//-----------------------------------------------------------------
			// store the rotation center point -- needed for transformation 
			// visual feedback
			//-----------------------------------------------------------------
			p->interface_data.center.x = p->interface_data.xpos;
			p->interface_data.center.y = p->interface_data.ypos;

			//-----------------------------------------------------------------
			// set transformation
			//-----------------------------------------------------------------
			p->interface_data.transformation = (MTI_SAMPLE_TRANSFORMATION)(
				(int)p->interface_data.transformation |
				ROTATE
			);

			//-----------------------------------------------------------------
			// perform a mouse move operation - this performs the zoom gesture
			//-----------------------------------------------------------------
			bret = process_mouse_move(p);
			assert(bret == SUCCESS);

			//-----------------------------------------------------------------
			// ask for redraw
			//-----------------------------------------------------------------
			bret = InvalidateRect(
				p->interface_data.hwnd,
				NULL,
				TRUE
			);
			assert(bret == TRUE);
			PostMessage(
				p->interface_data.hwnd,
				WM_PAINT,
				0,
				0
			);
			assert(bret == TRUE);
		}
	}

process_rotate_done:

	return(SUCCESS);

}

/*-----------------------------------------------------------------------------
Function: process_2fingers_tap
Purpose : process the two fingers tap gesture
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/23/2010    Jamel Tayeb             Creation.
*/
BOOL process_2fingers_tap(PMTI_SAMPLE_DATA p) {
	assert(p != NULL);
	//MessageBox(NULL, _T("this is two fingers tap."), _T("2 Fingers tap"), MB_OK);
	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: process_roll_over
Purpose : process the roll over gesture
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
08/23/2010    Jamel Tayeb             Creation.
*/
BOOL process_roll_over(PMTI_SAMPLE_DATA p) {
	assert(p != NULL);
	//MessageBox(NULL, _T("this is a roll over."), _T("Roll over"), MB_OK);
	return(SUCCESS);
}

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__
#endif // __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_POWER_AWARE__
/*-----------------------------------------------------------------------------
Function: power_suspend
Purpose : suspend activity -- power will be lost soon
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
09/02/2010    Jamel Tayeb             Creation.
*/
BOOL power_suspend(PMTI_SAMPLE_DATA p) {

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	int ret = -1;
	BOOL bret = FALSE;

#endif // __MTI_SAMPLE_INSTRUMENTED__

	assert(p != NULL);

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// stop on-going measurements (stop metrics thread)
	//-------------------------------------------------------------------------
	p->instrumentation_data.f_running = FALSE;	
	bret = stop_metrics_thread(p);
	assert(bret == SUCCESS);

	//-------------------------------------------------------------------------
	// clear data
	//-------------------------------------------------------------------------
	bret = initialize_geometry_data(&p->geometry_data);
	assert(bret == SUCCESS);

	//-------------------------------------------------------------------------
	// update instrumentation data
	//-------------------------------------------------------------------------
	bret = update_bezier_instrumentation_data(p);
	assert(bret == SUCCESS);
	bret = update_transformations_instrumentation_data(p);
	assert(bret == SUCCESS);

#ifndef __MTI_SAMPLE_NO_DISPLAY__

	//-------------------------------------------------------------------------
	// refresh screen
	//-------------------------------------------------------------------------
	bret = PostMessage(
		p->instrumentation_data.hwnd, 
		WM_PAINT, 
		0,
		0
	);
	assert(bret == TRUE);

#endif // __MTI_SAMPLE_NO_DISPLAY__

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	//-------------------------------------------------------------------------
	// stop timer
	//-------------------------------------------------------------------------
	bret = stop_timer(p);
	assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

#ifdef __MTI_SAMPLE_FILE_LOG__ // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

	//-------------------------------------------------------------------------
	// close the log file
	//-------------------------------------------------------------------------
	assert(p->log_file != NULL);
	ret = fclose(p->log_file);
	assert(ret == 0);
	p->log_file = NULL;

#endif // __MTI_SAMPLE_FILE_LOG__

#ifdef __MTI_SAMPLE_GUI_MONITOR__

	//-------------------------------------------------------------------------
	// stop pl_gui_monitor_instance
	//-------------------------------------------------------------------------
	bret = stop_pl_gui_monitor(p);
	assert(bret == SUCCESS);

	//-------------------------------------------------------------------------
	// stop ESRV instance
	//-------------------------------------------------------------------------
	if(p->instrumentation_data.energy_data.f_started_esrv == TRUE) {
		bret = remove_esrv(&p->instrumentation_data);
		assert(bret == SUCCESS);
	}

#endif // __MTI_SAMPLE_GUI_MONITOR__

	//-------------------------------------------------------------------------
	// save key data for resume
	// Note:
	//     save the folowing data in the suspend file:
	//     - ESRV GUID
	//     - our GUID
	//     - if ESRV has to be re-started on resume (TRUE or FALSE)
	//-------------------------------------------------------------------------
	p->instrumentation_data.save_file = fopen(
		MTI_SAMPLE_POWER_SAVE_FILE_NAME,
		MTI_SAMPLE_POWER_SAVE_SUSPEND_FILE_ACCESS
	);
	assert(p->instrumentation_data.save_file != NULL);
	ret = fprintf(
		p->instrumentation_data.save_file,
		"%s\n",
		p->instrumentation_data.energy_data.esrv_pl_path_name
	);
	assert(ret > 0);
	ret = fprintf(
		p->instrumentation_data.save_file,
		"%s\n",
		p->instrumentation_data.uuid_string
	);
	assert(ret > 0);
	if(p->instrumentation_data.energy_data.f_started_esrv == TRUE) {
		ret = fprintf(
			p->instrumentation_data.save_file,
			"%s",
			MTI_SAMPLE_POWER_SAVE_ESRV_STARTED
		);
		assert(ret > 0);
	} else {
		ret = fprintf(
			p->instrumentation_data.save_file,
			"%s\n",
			MTI_SAMPLE_POWER_SAVE_ESRV_NOT_STARTED
		);
		assert(ret > 0);
	}
	ret = fclose(p->instrumentation_data.save_file);
	assert(ret == 0);

#endif // __MTI_SAMPLE_INSTRUMENTED__

	return(SUCCESS);
}

/*-----------------------------------------------------------------------------
Function: power_resume
Purpose : resume from power loss
In      : pointer to MTI data
Out     : updated MTI data
Return  : status

History
-------------------------------------------------------------------------------
Date        : Author                  Modification
-------------------------------------------------------------------------------
09/02/2010    Jamel Tayeb             Creation.
*/
BOOL power_resume(PMTI_SAMPLE_DATA p) {

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	int ret = -1;
	BOOL bret = FALSE;
	char buffer[MAX_PATH] = { '\0' };

#endif // __MTI_SAMPLE_INSTRUMENTED__

	assert(p != NULL);

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// load saved data during suspend
	// Note:
	//     load the folowing data in the suspend file:
	//     - ESRV GUID
	//     - our GUID
	//-------------------------------------------------------------------------
	p->instrumentation_data.save_file = fopen(
		MTI_SAMPLE_POWER_SAVE_FILE_NAME,
		MTI_SAMPLE_POWER_SAVE_RESUME_FILE_ACCESS
	);
	assert(p->instrumentation_data.save_file != NULL);
	ret = fscanf(
		p->instrumentation_data.save_file,
		"%[^\n]\n",
		p->instrumentation_data.energy_data.esrv_pl_path_name
	);
	assert(ret > 0);
	ret = fscanf(
		p->instrumentation_data.save_file,
		"%[^\n]\n",
		p->instrumentation_data.uuid_string
	);
	assert(ret > 0);
	ret = fscanf(
		p->instrumentation_data.save_file,
		"%[^\n]\n",
		buffer
	);
	assert(ret > 0);
	ret = fclose(p->instrumentation_data.save_file);
	assert(ret == 0);

	//-------------------------------------------------------------------------
	// delete the file
	//-------------------------------------------------------------------------
	ret = _unlink(MTI_SAMPLE_POWER_SAVE_FILE_NAME);
	assert(ret == 0);

#ifdef __MTI_SAMPLE_FILE_LOG__

	//-------------------------------------------------------------------------
	// re-open the log file
	//-------------------------------------------------------------------------
	p->log_file = fopen(
		MTI_SAMPLE_LOG_FILE_NAME,
		MTI_SAMPLE_LOG_FILE_RESUME_ACCESS
	);
	assert(p->log_file != NULL);

#endif // __MTI_SAMPLE_FILE_LOG__

#ifdef __MTI_SAMPLE_GUI_MONITOR__

	//-------------------------------------------------------------------------
	// re-start a pl_gui_monitor_instance
	//-------------------------------------------------------------------------
	bret = start_pl_gui_monitor(p);
	assert(bret == SUCCESS);
	if(strncmp(
			buffer,
			MTI_SAMPLE_POWER_SAVE_ESRV_STARTED,
			strlen(MTI_SAMPLE_POWER_SAVE_ESRV_STARTED)
		) == 0
	) {
		p->instrumentation_data.energy_data.f_started_esrv = TRUE;
	}

#endif // __MTI_SAMPLE_GUI_MONITOR__

	if(p->instrumentation_data.energy_data.f_started_esrv == TRUE) {

		//---------------------------------------------------------------------
		// re-start an ESRV  instance
		//---------------------------------------------------------------------
		bret = get_esrv_pld(&p->instrumentation_data);
		assert(bret == SUCCESS);

	} else {

		//---------------------------------------------------------------------
		// attach to the previously attached ESRV -- this assumes that who
		// ever started ESRV did restart it.
		//---------------------------------------------------------------------
		strncat(
			p->instrumentation_data.energy_data.esrv_pl_path_name,
			PL_CONFIG_FILE_NAME_CHAR,
			strlen(PL_CONFIG_FILE_NAME_CHAR)
		);
		p->instrumentation_data.energy_data.esrv_pld = pl_attach(
			p->instrumentation_data.energy_data.esrv_pl_path_name
		);
		assert(
			p->instrumentation_data.energy_data.esrv_pld != 
			PL_INVALID_DESCRIPTOR
		);
	}

	//-------------------------------------------------------------------------
	// re-start the metrics thread
	//-------------------------------------------------------------------------
	bret = start_metrics_thread(p);
	assert(bret == SUCCESS);

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

	//-------------------------------------------------------------------------
	// start timer
	//-------------------------------------------------------------------------
	bret = start_timer(p);
	assert(bret == SUCCESS);

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__


#endif // __MTI_SAMPLE_INSTRUMENTED__

	return(SUCCESS);
}
#endif // __MTI_SAMPLE_POWER_AWARE__

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus
