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
#ifndef __MTI_SAMPLE_CODE__
#define __MTI_SAMPLE_CODE__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Build notes
//-----------------------------------------------------------------------------
// following symbols alters compilation and execution paths:
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
// headers include
//-----------------------------------------------------------------------------
#include <windows.h>

//-----------------------------------------------------------------------------
// generic definitions
//-----------------------------------------------------------------------------
#define MTI_SAMPLE_APPLICATION_NAME "mti-sample"
#define MTI_SAMPLE_WINDOW_TITLE "Sample Application demonstrating MTI/STI"

//-----------------------------------------------------------------------------
// STI definitions
//-----------------------------------------------------------------------------
#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__
	// none
#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

//-----------------------------------------------------------------------------
// MTI definitions
//-----------------------------------------------------------------------------
#ifdef __MTI_SAMPLE_MTI_CODE__
	#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__
		#define MOUSEEVENTF_FROMTOUCH 0xFF515700 
	#else // __MTI_SAMPLE_MTI_TOUCH_CODE__
		#define MTI_SAMPLE_DEFAULT_GESTURES_COUNT 1
		#define MTI_SAMPLE_DEFAULT_GESTURES { 0, GC_ALLGESTURES, 0 }
	#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__
#endif // __MTI_SAMPLE_MTI_CODE__

//-----------------------------------------------------------------------------
// PL instrumntation definitions -- for performance and energy-efficiency
//-----------------------------------------------------------------------------
#ifdef __MTI_SAMPLE_INSTRUMENTED__

	#define ENERGY_DEFAULT_CHANNEL 1
	#define METRICS_THREAD_TIMER 1
	#define METRICS_THREAD_UPDATE_INTERVAL_IN_MS 1000
	#define MTI_SAMPLE_MS_IN_ONE_S 1000

	#ifdef __MTI_SAMPLE_GUI_MONITOR__
		#define MTI_SAMPLE_REMOVE_PL_MESSAGE_STRING \
			_T("Do you want to remove the PL?")
	#else // __MTI_SAMPLE_GUI_MONITOR__
		#define MTI_SAMPLE_REMOVE_PL_MESSAGE_STRING \
			_T("Do you want to remove the PL?\nIf the PL is monitored, then if cannot be removed.")
	#endif // __MTI_SAMPLE_GUI_MONITOR__
	#define MTI_SAMPLE_REMOVE_PL_CAPTION_STRING \
		_T("Remove PL")

	#undef MTI_SAMPLE_APPLICATION_NAME
	#define MTI_SAMPLE_APPLICATION_NAME "energy_aware_mti-sample"
	
	#define MTI_SAMPLE_COUNTERS_COUNT 42
	#define MTI_SAMPLE_COUNTERS_NAMES \
		"Bezier curves", \
		"Bezier curve redraws", \
		"Translations", \
		"Scalings", \
		"Rotations", \
		\
		"Sum of Joules consumed for Bezier curves", \
		"Sum of Joules consumed for translations", \
		"Sum of Joules consumed for scalings", \
		"Sum of Joules consumed for rotations", \
		"Sum of Joules consumed for Bezier curves.decimals", \
		"Sum of Joules consumed for translations.decimals", \
		"Sum of Joules consumed for scalings.decimals", \
		"Sum of Joules consumed for rotations.decimals", \
		\
		"ms elapsed drawing Bezier curves", \
		"ms elapsed performing translations", \
		"ms elapsed performing scalings", \
		"ms elapsed performing rotations", \
		\
		"Average Bezier curves per joule", \
		"Average translations per joule", \
		"Average scalings per joule", \
		"Average rotations per joule", \
		"Average Bezier curves per joule.decimals", \
		"Average translations per joule.decimals", \
		"Average scalings per joule.decimals", \
		"Average rotations per joule.decimals", \
		\
		"Average Joules per Bezier curve", \
		"Average Joules per translation", \
		"Average Joules per scaling", \
		"Average Joules per rotation", \
		"Average Joules per Bezier curve.decimals", \
		"Average Joules per translation.decimals", \
		"Average Joules per scaling.decimals", \
		"Average Joules per rotation.decimals", \
		\
		"Average ms per Bezier curve", \
		"Average ms per translation", \
		"Average ms per scale", \
		"Average ms per rotation", \
		"Average ms per Bezier curve.decimals", \
		"Average ms per translation.decimals", \
		"Average ms per scale.decimals", \
		"Average ms per rotation.decimals", \
		\
		"Status [1 means running]"

enum {

	BEZIER_CURVES_INDEX = 0,
	BEZIER_CURVES_DRAWN_INDEX,
	TRANSLATIONS_PERFORMED_INDEX,
	SCALINGS_PERFORMED_INDEX,
	ROTATIONS_PERFORMED_INDEX,

	ENERGY_CONSUMED_WHILE_DRAWING_BEZIER_CURVES_INDEX,
	ENERGY_CONSUMED_WHILE_PERFORMING_TRANSLATIONS_INDEX,
	ENERGY_CONSUMED_WHILE_PERFORMING_SCALEINGS_INDEX,
	ENERGY_CONSUMED_WHILE_PERFORMING_ROTATIONS_INDEX,
	ENERGY_CONSUMED_WHILE_DRAWING_BEZIER_CURVES_DECIMALS_INDEX,
	ENERGY_CONSUMED_WHILE_PERFORMING_TRANSLATIONS_DECIMALS_INDEX,
	ENERGY_CONSUMED_WHILE_PERFORMING_SCALEINGS_DECIMALS_INDEX,
	ENERGY_CONSUMED_WHILE_PERFORMING_ROTATIONS_DECIMALS_INDEX,

	TICKS_ELAPSED_WHILE_DRAWING_BEZIER_CURVES_INDEX,
	TICKS_ELAPSED_WHILE_PERFORMING_TRANSLATIONS_INDEX,
	TICKS_ELAPSED_WHILE_PERFORMING_SCALEINGS_INDEX,
	TICKS_ELAPSED_WHILE_PERFORMING_ROTATIONS_INDEX,

	BEZIER_CURVES_DRAWN_PER_JOULE_CONSUMMED_INDEX,
	TRANSLATIONS_PERFORMED_PER_JOULE_INDEX,
	SCALINGS_PERFORMED_PER_JOULE_INDEX,
	ROTATIONS_PERFORMED_PER_JOULE_INDEX,
	BEZIER_CURVES_DRAWN_PER_JOULE_CONSUMMED_DECIMALS_INDEX,
	TRANSLATIONS_PERFORMED_PER_JOULE_DECIMALS_INDEX,
	SCALINGS_PERFORMED_PER_JOULE_DECIMALS_INDEX,
	ROTATIONS_PERFORMED_PER_JOULE_DECIMALS_INDEX,

	JOULES_CONUMED_PER_BEZIER_CURVE_INDEX,
	JOULES_CONUMED_PER_TRANSLATION_INDEX,
	JOULES_CONUMED_PER_SCALE_INDEX,
	JOULES_CONUMED_PER_ROTATION_INDEX,
	JOULES_CONUMED_PER_BEZIER_CURVE_DECIMALS_INDEX,
	JOULES_CONUMED_PER_TRANSLATION_DECIMALS_INDEX,
	JOULES_CONUMED_PER_SCALE_DECIMALS_INDEX,
	JOULES_CONUMED_PER_ROTATION_DECIMALS_INDEX,

	TICKS_ELAPSED_PER_BEZIER_CURVE_INDEX,
	TICKS_ELAPSED_PER_TRANSLATION_INDEX,
	TICKS_ELAPSED_PER_SCALE_INDEX,
	TICKS_ELAPSED_PER_ROTATION_INDEX,
	TICKS_ELAPSED_PER_BEZIER_CURVE_DECIMALS_INDEX,
	TICKS_ELAPSED_PER_TRANSLATION_DECIMALS_INDEX,
	TICKS_ELAPSED_PER_SCALE_DECIMALS_INDEX,
	TICKS_ELAPSED_PER_ROTATION_DECIMALS_INDEX,

	STATUS_INDEX
};

#endif // __MTI_SAMPLE_INSTRUMENTED__

#if defined (__MTI_SAMPLE_FILE_LOG__) || defined (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

	#define MTI_SAMPLE_TIME_BUFFER_SIZE 27
	#define MTI_SAMPLE_TIME_STAMP_OFFSET 24
	#define MTI_SAMPLE_TIME_STAMP_END_OFFSET 26
	#define MTI_SAMPLE_LOG_FILE_NAME "mti_sample_log.csv" 
	#define MTI_SAMPLE_LOG_FILE_ACCESS "w+"
	#ifdef __MTI_SAMPLE_POWER_AWARE__
		#define MTI_SAMPLE_LOG_FILE_RESUME_ACCESS "a"
	#endif // __MTI_SAMPLE_POWER_AWARE__
	#define MTI_SAMPLE_LOG_FILE_SEPARATOR ", "
	#define MTI_SAMPLE_LOG_FILE_NEW_LINE "\n"

#endif // (__MTI_SAMPLE_FILE_LOG__) || (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

#ifdef __MTI_SAMPLE_POWER_AWARE__
	#define MTI_SAMPLE_POWER_SAVE_ESRV_STARTED "1"
	#define MTI_SAMPLE_POWER_SAVE_ESRV_NOT_STARTED "0"
	#define MTI_SAMPLE_POWER_SAVE_FILE_NAME "mti_sample_suspend.txt" 
	#define MTI_SAMPLE_POWER_SAVE_SUSPEND_FILE_ACCESS "w+"
	#define MTI_SAMPLE_POWER_SAVE_RESUME_FILE_ACCESS "r+"
#endif // __MTI_SAMPLE_POWER_AWARE__

#ifdef __MTI_SAMPLE_FILE_LOG__

	#define MTI_SAMPLE_LOG_FILE_HEADER \
"Time stamp, \
Bézier curves, \
Bézier curve redraws, \
Translations, \
Scalings, \
Rotations, \
\
Sum of Joules consumed for Bézier curves, \
Sum of Joules consumed for translations, \
Sum of Joules consumed for scalings, \
Sum of Joules consumed for rotations, \
\
ms elapsed drawing Bézier curves, \
ms elapsed performing translations, \
ms elapsed performing scalings, \
ms elapsed performing rotations, \
\
Average Bézier curves per joule, \
Average translations per joule, \
Average scalings per joule, \
Average rotations per joule, \
\
Average Joules per Bézier curve, \
Average Joules per translation, \
Average Joules per scaling, \
Average Joules per rotation, \
\
Average ms per Bézier curve, \
Average ms per translation, \
Average ms per scale, \
Average ms per rotation\n"

#endif // __MTI_SAMPLE_FILE_LOG__

#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

	#define MTI_SAMPLE_LOG_FILE_TRANSLATE_STRING "Translation"
	#define MTI_SAMPLE_LOG_FILE_SCALE_STRING "Scaling"
	#define MTI_SAMPLE_LOG_FILE_ROTATE_STRING "Rotation"
	#define MTI_SAMPLE_LOG_FILE_HEADER \
"Time stamp, \
Gesture, \
Gesture type, \
Gesture duration in ms, \
Gesture energy in Joules\n"

#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

//-----------------------------------------------------------------------------
// message definitions
//-----------------------------------------------------------------------------
#define MTI_SAMPLE_NOT_IN_WINDOWS_MESSAGE_STRING "Program requires Windows NT!"
#define MTI_SAMPLE_HELP_MESSAGE_STRING _T(\
"Draw a Bézier curve and move around the control points to study the effect \
on the B-Spline.  Use left click to place control points on the screen. \
A particular control point is an anchor point.  Anchor points are the \
beginning and the ending points of the Bézier curve.  Control points define \
the tangents to the Bézier curve at the anchor points.  Changing the \
position of the control points changes the shape of the Bézier curve. \
Control points are positioned in sequence.  The first left click places the \
first anchor point.  The second left click places the first control point. \
The segment joining the first anchor point to the first control point is the \
first control bar.  The third left click places the second anchor point. \
The fourth left click places the second control point.  The segment joining \
the second anchor point to the second control point is the second control bar. \
At any time, you can use a right click and a mouse drag to re-position any of \
the control points.  The shape of the Bézier curve will be updated accordingly. \
Subsequent left clicks will erase the Bézier curve and you can proceed to the \
next one.  At any time, pressing the space bar will reset the drawing. \
Press F1 to display this help message and ESC to return to the drawing.")

//-----------------------------------------------------------------------------
// geometric definitions
//-----------------------------------------------------------------------------
#define MTI_SAMPLE_MAX_POINTS 4
#define MTI_SAMPLE_DEFAULT_STEPS 100.0

#define MTI_SAMPLE_FIRST_ANCHOR_PRESENT 1
#define MTI_SAMPLE_SECOND_ANCHOR_PRESENT 3
#define MTI_SAMPLE_FIRST_CONTROL_PRESENT 2
#define MTI_SAMPLE_SECOND_CONTROL_PRESENT 4
#define MTI_SAMPLE_FIRST_CONTROL_BAR_PRESENT 2
#define MTI_SAMPLE_SECOND_CONTROL_BAR_PRESENT 4
#define MTI_SAMPLE_BEZIER_CURVE_PRESENT 4

#define MTI_SAMPLE_FIRST_ANCHOR_POINT_INDEX 0
#define MTI_SAMPLE_SECOND_ANCHOR_POINT_INDEX 2
#define MTI_SAMPLE_FIRST_CONTROL_POINT_INDEX 1
#define MTI_SAMPLE_SECOND_CONSTROL_POINT_INDEX 3

#if defined(__MTI_SAMPLE_MTI_CODE__) || !defined(__MTI_SAMPLE_STI_TOUCH_CODE__)
	
	#define MTI_SAMPLE_RADIAN_TO_DEGREE 57.2957795

#endif // __MTI_SAMPLE_MTI_CODE__ || !__MTI_SAMPLE_STI_TOUCH_CODE__

#if defined(__MTI_SAMPLE_MTI_CODE__) || defined(__MTI_SAMPLE_STI_TOUCH_CODE__)

	#define MTI_SAMPLE_PROXIMITY 48

#else // __MTI_SAMPLE_MTI_CODE__ || __MTI_SAMPLE_STI_TOUCH_CODE__

	#define MTI_SAMPLE_PROXIMITY 6

#endif // __MTI_SAMPLE_MTI_CODE__ || __MTI_SAMPLE_STI_TOUCH_CODE__

#define MTI_SAMPLE_ROTATIONS_ACCELERATOR 2.0

//-----------------------------------------------------------------------------
// graphic definitions
//-----------------------------------------------------------------------------
#define MTI_SAMPLE_WINDOW_WIDTH 320
#define MTI_SAMPLE_WINDOW_HEIGHT 480

#ifdef __MTI_SAMPLE_SENSORS_CODE__

	#define MTI_SAMPLE_ADAPT_TO_LIGHT(v) \
		((v) + ((int)(shared_data.light_coefficient * (double)(v))))

	#ifdef __MTI_SAMPLE_LINEAR_COLOR_SCALE__
		#define MTI_SAMPLE_LIGHT_COLOR_COEFFICIENT \
			(1.0 - shared_data.light_coefficient)
	#else // __MTI_SAMPLE_LINEAR_COLOR_SCALE__
		#define MTI_SAMPLE_LIGHT_COLOR_COEFFICIENT \
			(log10(MAX_LUX_VALUE - shared_data.lux))
	#endif // __MTI_SAMPLE_LINEAR_COLOR_SCALE__

	#define MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(r, g, b) \
		RGB( \
			(int)(MTI_SAMPLE_LIGHT_COLOR_COEFFICIENT * ((double)(r))), \
			(int)(MTI_SAMPLE_LIGHT_COLOR_COEFFICIENT * ((double)(g))), \
			(int)(MTI_SAMPLE_LIGHT_COLOR_COEFFICIENT * ((double)(b))) \
		)

	#define MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE MTI_SAMPLE_ADAPT_TO_LIGHT(8)
	#define MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS MTI_SAMPLE_ADAPT_TO_LIGHT(8)
	#define MTI_SAMPLE_DEFAULT_WIDTH MTI_SAMPLE_ADAPT_TO_LIGHT(2)
	#define MTI_SAMPLE_BEZIER_CURVE_WIDTH MTI_SAMPLE_ADAPT_TO_LIGHT(4)
	#define MTI_SAMPLE_CONTROL_BAR_WIDTH MTI_SAMPLE_ADAPT_TO_LIGHT(4)
	#define MTI_SAMPLE_DEFAULT_LINE_STYLE PS_SOLID

	#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

		#define MTI_SAMPLE_BBOX_CENTER_POINT_HALF_RADIUS MTI_SAMPLE_ADAPT_TO_LIGHT(8)

	#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

		#define MTI_SAMPLE_FEEDBACK_WIDTH MTI_SAMPLE_ADAPT_TO_LIGHT(2)
		#define MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE MTI_SAMPLE_ADAPT_TO_LIGHT(4)
		#define MTI_SAMPLE_FEEDBACK_LINE_STYLE PS_DASH

	#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	#define MTI_SAMPLE_ANCHOR_POINT_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(127, 127, 0) 
	#define MTI_SAMPLE_ANCHOR_POINT_OUTLINE_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 0, 0) 
	#define MTI_SAMPLE_CONTROL_POINT_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(255, 0, 0) 
	#define MTI_SAMPLE_CONTROL_POINT_OUTLINE_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 0, 0) 
	#define MTI_SAMPLE_CONTROL_BAR_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 0, 255) 


	#define MTI_SAMPLE_BEZIER_CURVE_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 0, 0)
	#define MTI_SAMPLE_HELP_BACKGROUND_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(127, 127, 127)

	#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

		#define MTI_SAMPLE_BBOX_CENTER_POINT_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 255, 0) 
		#define MTI_SAMPLE_BBOX_CENTER_POINT_OUTLINE_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 0, 0) 

	#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__
		
		#define MTI_SAMPLE_FEEDBACK_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 160, 235) 
		#define MTI_SAMPLE_FEEDBACK_OUTLINE_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 180, 255) 
		#define MTI_SAMPLE_FEEDBACK_TRANSLATE_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 235, 160) 
		#define MTI_SAMPLE_FEEDBACK_TRANSLATE_OUTLINE_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(0, 255, 180) 
		#define MTI_SAMPLE_FEEDBACK_SWEEP_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(200, 200, 200) 
		#define MTI_SAMPLE_FEEDBACK_SWEEP_OUTLINE_COLOR MTI_SAMPLE_ADAPT_RGB_TO_LIGHT(180, 180, 180) 

		#if defined(__MTI_SAMPLE_MTI_CODE__) || !defined(__MTI_SAMPLE_STI_TOUCH_CODE__)
			
			#define MTI_SAMPLE_FEEDBACK_ROTATION_RADIUS 200
		
		#endif // __MTI_SAMPLE_MTI_CODE__ || !__MTI_SAMPLE_STI_TOUCH_CODE__

	#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

#else // __MTI_SAMPLE_SENSORS_CODE__

	#define MTI_SAMPLE_ANCHOR_POINT_HALF_SIZE 8
	#define MTI_SAMPLE_CONTROL_POINT_HALF_RADIUS 8
	#define MTI_SAMPLE_DEFAULT_WIDTH 2
	#define MTI_SAMPLE_BEZIER_CURVE_WIDTH 4
	#define MTI_SAMPLE_CONTROL_BAR_WIDTH 4
	#define MTI_SAMPLE_DEFAULT_LINE_STYLE PS_SOLID

	#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

		#define MTI_SAMPLE_BBOX_CENTER_POINT_HALF_RADIUS 8

	#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

		#define MTI_SAMPLE_FEEDBACK_WIDTH 2
		#define MTI_SAMPLE_FEEDBACK_POINT_HALF_SIZE 4
		#define MTI_SAMPLE_FEEDBACK_LINE_STYLE PS_DASH

	#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	#define MTI_SAMPLE_ANCHOR_POINT_COLOR RGB(127, 127, 0) 
	#define MTI_SAMPLE_ANCHOR_POINT_OUTLINE_COLOR RGB(0, 0, 0) 
	#define MTI_SAMPLE_CONTROL_POINT_COLOR RGB(255, 0, 0) 
	#define MTI_SAMPLE_CONTROL_POINT_OUTLINE_COLOR RGB(0, 0, 0) 
	#define MTI_SAMPLE_CONTROL_BAR_COLOR RGB(0, 0, 255) 
	#define MTI_SAMPLE_BEZIER_CURVE_COLOR RGB(0, 0, 0)
	#define MTI_SAMPLE_HELP_BACKGROUND_COLOR RGB(127, 127, 127)

	#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

		#define MTI_SAMPLE_BBOX_CENTER_POINT_COLOR RGB(0, 255, 0) 
		#define MTI_SAMPLE_BBOX_CENTER_POINT_OUTLINE_COLOR RGB(0, 0, 0) 

	#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__
		
		#define MTI_SAMPLE_FEEDBACK_COLOR RGB(0, 160, 235) 
		#define MTI_SAMPLE_FEEDBACK_OUTLINE_COLOR RGB(0, 180, 255) 
		#define MTI_SAMPLE_FEEDBACK_TRANSLATE_COLOR RGB(0, 235, 160) 
		#define MTI_SAMPLE_FEEDBACK_TRANSLATE_OUTLINE_COLOR RGB(0, 255, 180) 
		#define MTI_SAMPLE_FEEDBACK_SWEEP_COLOR RGB(200, 200, 200) 
		#define MTI_SAMPLE_FEEDBACK_SWEEP_OUTLINE_COLOR RGB(180, 180, 180) 

		#if defined(__MTI_SAMPLE_MTI_CODE__) || !defined(__MTI_SAMPLE_STI_TOUCH_CODE__)
			
			#define MTI_SAMPLE_FEEDBACK_ROTATION_RADIUS 200
		
		#endif // __MTI_SAMPLE_MTI_CODE__ || !__MTI_SAMPLE_STI_TOUCH_CODE__

	#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

#endif // __MTI_SAMPLE_SENSORS_CODE__

//-----------------------------------------------------------------------------
// interface definitions
//-----------------------------------------------------------------------------
#define MTI_SAMPLE_RESET_KEY VK_SPACE
#define MTI_SAMPLE_HELP_KEY VK_F1
#define MTI_SAMPLE_EXIT_HELP_KEY VK_ESCAPE
#define MTI_SAMPLE_LONG_PAUSE_IN_S 2

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

	#define MTI_SAMPLE_SHIFT_KEY VK_SHIFT
	#define MTI_SAMPLE_CONTROL_KEY VK_CONTROL

#endif // #ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

#ifdef __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

	#define MTI_SAMPLE_MTI_TOUCH_CODE_MAX_TOUCH_CONTACTS_SEQUENCES 20
	#define MTI_SAMPLE_MTI_TOUCH_CODE_TOUCH_CONTACTS_SEQUENCES_SENTINEL_ID -1

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#endif // __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	//-------------------------------------------------------------------------
	// energy efficiency definitions
	//-------------------------------------------------------------------------
	#define MTI_SAMPLE_DEFAULT_BEZIERS_JOULES_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_TRANSLATIONS_JOULES_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_SCALES_JOULES_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_ROTATIONS_JOULES_DECIMALS 2

	#define MTI_SAMPLE_DEFAULT_BEZIERS_PER_JOULE_DECIMALS 4
	#define MTI_SAMPLE_DEFAULT_TRANSLATIONS_PER_JOULE_DECIMALS 4
	#define MTI_SAMPLE_DEFAULT_SCALES_PER_JOULE_DECIMALS 4
	#define MTI_SAMPLE_DEFAULT_ROTATIONS_PER_JOULE_DECIMALS 4

	#define MTI_SAMPLE_DEFAULT_JOULES_PER_BEZIER_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_JOULES_PER_TRANSLATION_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_JOULES_PER_SCALE_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_JOULES_PER_ROTATION_DECIMALS 2

	#define MTI_SAMPLE_DEFAULT_TICKS_PER_BEZIER_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_TICKS_PER_TRANSLATION_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_TICKS_PER_SCALE_DECIMALS 2
	#define MTI_SAMPLE_DEFAULT_TICKS_PER_ROTATION_DECIMALS 2

	//-------------------------------------------------------------------------
	// ESRV pid and uuid retrieval
	//-------------------------------------------------------------------------
	#define ENERGY_INPUT_LINE_MAX_SIZE 4096
	#define ENERGY_ESRV_GUID_LINE 9
	#define ENERGY_ESRV_PID_LINE 10
	#define GUID_LENGHT_IN_CHARACTERS 36
	#define ENERGY_ESRV_PRE_GUID_TOKEN "Using Guid:     "
	#define ENERGY_ESRV_GUID_TOKEN_SEPARATORS "\n["
	#define ENERGY_ESRV_GUID_TOKEN_TERMINATOR "]"
	#define ENERGY_ESRV_PRE_PID_TOKEN "PID:            "
	#define ENERGY_ESRV_PID_TOKEN_SEPARATORS "\n["
	#define ENERGY_ESRV_PID_TOKEN_TERMINATOR "]"

	//-------------------------------------------------------------------------
	// ESRV shell variables
	//-------------------------------------------------------------------------
	#define ENERGY_ESRV_DEFAULT_GUID_SHELL_VARIABLE "ESRV_GUID"

	//-------------------------------------------------------------------------
	// generic PL instance handling
	//-------------------------------------------------------------------------
	#define PL_CONFIG_FILE_NAME_CHAR "\\pl_config.ini"
	#define PL_CONFIG_FILE_ROOT "C:\\productivity_link\\"

	//-------------------------------------------------------------------------
	// ESRV instance handling
	//-------------------------------------------------------------------------
	#define ENERGY_ESRV_PL_CONFIG_FILE_UNDERSCORE "_"
	#define ENERGY_ESRV_PL_CONFIG_FILE_APPLICATION_NAME "esrv_"
	#define ENERGY_ESRV_BINARY_NAME "esrv --start "
	#define ENERGY_ESRV_SHELL_OPTION " --shell"

	#if defined (_DEBUG) || (__PL_DEBUG__)
	
		#define ENERGY_ESRV_DEFAULT_OPTIONS \
			"--library esrv_simulated_device.dll"
	
	#else // _DEBUG || __PL_DEBUG__
	
		#define ENERGY_ESRV_DEFAULT_OPTIONS \
			"--device y210 --device_options \"items=all\""
	
	#endif // _DEBUG || __PL_DEBUG__

	#ifdef __MTI_SAMPLE_GUI_MONITOR__

		//-------------------------------------------------------------------------
		// pl_gui_monitor instance handling
		//-------------------------------------------------------------------------
		#define GUI_MONITOR_BINARY_NAME "pl_gui_monitor "
		#define GUI_MONITOR_DEFAULT_OPTIONS \
			"--gdiplus --process --format --transparency 30 --top --trend --time_in_ms --t 1000 --geometry \"gauges=3x2 position=middlexright\" "		
	
	#endif // __MTI_SAMPLE_GUI_MONITOR__

#endif // __MTI_SAMPLE_INSTRUMENTED__

//-----------------------------------------------------------------------------
// structures & enums
//-----------------------------------------------------------------------------
enum {
	SUCCESS = TRUE,
	FAILURE = FALSE
};

//-----------------------------------------------------------------------------
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
// 
//-----------------------------------------------------------------------------
typedef enum {

	QUADRANT_UNDEFINED = 0,
	QUADRANT1 = 1,
	QUADRANT2,
	QUADRANT3,
	QUADRANT4,

} MTI_SAMPLE_QUADRANT, *PMTI_SAMPLE_QUADRANT;

typedef enum {

	IDENTITY = 0,
	TRANSLATE = 1,
	SCALE = 2,
	ROTATE = 4

} MTI_SAMPLE_TRANSFORMATION, *PMTI_SAMPLE_TRANSFORMATION;

#ifdef __MTI_SAMPLE_INSTRUMENTED__
	enum {
		RUNNING = TRUE,
		NOT_RUNNING = FALSE
	};
#endif  //__MTI_SAMPLE_INSTRUMENTED__

typedef struct _mti_sample_interface_data {

	HWND hwnd;
	RECT rect;
	LONG xpos;
	LONG ypos;
	LONG ref_xpos;
	LONG ref_ypos;
	RECT ref_bbox;
	POINT ref_bbox_center;
	POINT ref_points[MTI_SAMPLE_MAX_POINTS];
	LONG key;
	unsigned int selected_point_index;
	BOOL f_point_selected;
	BOOL f_bbox_selected;
	BOOL f_in_help;
	BOOL f_shift;
	BOOL f_control;
	MTI_SAMPLE_TRANSFORMATION transformation;

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

	UINT touch_inputs_count;
	PTOUCHINPUT touch_inputs;

#endif // __MTI_SAMPLE_STI_TOUCH_CODE__

#ifdef __MTI_SAMPLE_MTI_CODE__

	#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__

		UINT touch_inputs_count;
		PTOUCHINPUT touch_inputs;
		int touch_contacts_sequence_ids_count;
		int touch_contacts_sequence_ids[MTI_SAMPLE_MTI_TOUCH_CODE_MAX_TOUCH_CONTACTS_SEQUENCES];

	#else // __MTI_SAMPLE_MTI_TOUCH_CODE__

		GESTUREINFO gesture_info;
		POINT center;
		double scale_coefficient;
		double rotation_angle;
	
	#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#endif // __MTI_SAMPLE_MTI_CODE__

} MTI_SAMPLE_INTERFACE_DATA, *PMTI_SAMPLE_INTERFACE_DATA;

typedef struct _mti_sample_geometry_data {

	RECT bbox;
	POINT bbox_center;
	unsigned int points_count;
	POINT points[MTI_SAMPLE_MAX_POINTS];
	double steps;
	
} MTI_SAMPLE_GEOMETRY_DATA, *PMTI_SAMPLE_GEOMETRY_DATA;

typedef struct _mti_sample_graphic_data {

	HDC hdc;
	HDC in_memory_hdc;
	PAINTSTRUCT ps;

	HBITMAP in_memory_bitmap;
	HBITMAP old_bitmap;

	HBRUSH anchor_point_brush;
	HBRUSH control_point_brush;

#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	HBRUSH bbox_center_point_brush;

#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	HBRUSH feedback_brush;
	HBRUSH feedback_translate_brush;
	HBRUSH feedback_sweep_brush;

#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	HPEN anchor_point_pen;
	HPEN control_point_pen;
	HPEN control_bar_pen;
	HPEN bezier_curve_pen;

#ifdef __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

	HPEN bbox_center_point_pen;

#endif // __MTI_SAMPLE_DRAW_BOUNDING_BOX_CENTER__

#ifdef __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

	HPEN feedback_pen;
	HPEN feedback_translate_pen;
	HPEN feedback_sweep_pen;

#endif // __MTI_SAMPLE_DRAW_TRANSFORMATIONS_FEEDBACKS__

} MTI_SAMPLE_GRAPHIC_DATA, *PMTI_SAMPLE_GRAPHIC_DATA;

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	typedef struct _energy_data {

		//---------------------------------------------------------------------
		// Data to manage ESRV instance.
		//---------------------------------------------------------------------
		BOOL f_started_esrv;
		DWORD esrv_pid;
		FILE *fp_esrv;
		BOOL f_esrv_guid;
		BOOL f_esrv_pid;
		char esrv_pl_path_name[MAX_PATH];

		//---------------------------------------------------------------------
		// Data to manage the attached ESRV.
		//---------------------------------------------------------------------
		unsigned int channel;
		unsigned long long update_interval_in_ms;
		unsigned long long channels;
		unsigned long long status;
		unsigned long long version;

		//---------------------------------------------------------------------
		// Energy sampling data.
		//---------------------------------------------------------------------
		int esrv_pld;
		double energy_data_multiplier;
		double power_data_multiplier;
		unsigned long long esrv_status;

	} ENERGY_DATA, *PENERGY_DATA;

	typedef struct _mti_sample_instrumentation_data {

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__
		
		//---------------------------------------------------------------------
		// timer data
		//---------------------------------------------------------------------
		HWND hwnd;
		HRESULT timer;

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

#ifdef __MTI_SAMPLE_POWER_AWARE__

		//---------------------------------------------------------------------
		// suspend-resume data
		//---------------------------------------------------------------------
		FILE *save_file;
		char uuid_string[GUID_LENGHT_IN_CHARACTERS];
#endif // __MTI_SAMPLE_POWER_AWARE__

		//---------------------------------------------------------------------
		// PL counter data
		//---------------------------------------------------------------------
		int pld;
		uuid_t uuid;

		unsigned long long beziers;
		unsigned long long beziers_drawn;
		unsigned long long translations;
		unsigned long long scales;
		unsigned long long rotations;

		unsigned long long beziers_joules;
		unsigned long long translations_joules;
		unsigned long long scales_joules;
		unsigned long long rotations_joules;
		unsigned long long beziers_joules_decimals;
		unsigned long long translations_joules_decimals;
		unsigned long long scales_joules_decimals;
		unsigned long long rotations_joules_decimals;

		unsigned long long beziers_ticks;
		unsigned long long translations_ticks;
		unsigned long long scales_ticks;
		unsigned long long rotations_ticks;

		unsigned long long beziers_per_joule;
		unsigned long long translations_per_joule;
		unsigned long long scales_per_joule;
		unsigned long long rotations_per_joule;
		unsigned long long beziers_per_joule_decimals;
		unsigned long long translations_per_joule_decimals;
		unsigned long long scales_per_joule_decimals;
		unsigned long long rotations_per_joule_decimals;

		unsigned long long joules_per_bezier;
		unsigned long long joules_per_translation;
		unsigned long long joules_per_scale;
		unsigned long long joules_per_rotation;
		unsigned long long joules_per_bezier_decimals;
		unsigned long long joules_per_translation_decimals;
		unsigned long long joules_per_scale_decimals;
		unsigned long long joules_per_rotation_decimals;

		unsigned long long ticks_per_bezier;
		unsigned long long ticks_per_translation;
		unsigned long long ticks_per_scale;
		unsigned long long ticks_per_rotation;
		unsigned long long ticks_per_bezier_decimals;
		unsigned long long ticks_per_translation_decimals;
		unsigned long long ticks_per_scale_decimals;
		unsigned long long ticks_per_rotation_decimals;

		unsigned long long status;

		//---------------------------------------------------------------------
		// ESRV management data
		//---------------------------------------------------------------------
		ENERGY_DATA energy_data;

		//---------------------------------------------------------------------
		// start & stop energy data
		//---------------------------------------------------------------------
		unsigned long long beziers_joules_start;
		unsigned long long beziers_joules_stop;
		unsigned long long translations_joules_start;
		unsigned long long translations_joules_stop;
		unsigned long long scales_joules_start;
		unsigned long long scales_joules_stop;
		unsigned long long rotations_joules_start;
		unsigned long long rotations_joules_stop;

		//---------------------------------------------------------------------
		// start & stop ticks data
		//---------------------------------------------------------------------
		unsigned long long beziers_ticks_start;
		unsigned long long beziers_ticks_stop;
		unsigned long long translations_ticks_start;
		unsigned long long translations_ticks_stop;
		unsigned long long scales_ticks_start;
		unsigned long long scales_ticks_stop;
		unsigned long long rotations_ticks_start;
		unsigned long long rotations_ticks_stop;

		//---------------------------------------------------------------------
		// metrics thread data
		//---------------------------------------------------------------------
		BOOL f_running;
		DWORD metrics_thread_id;
		HANDLE metrics_thread_handle;
		HANDLE metrics_thread_can_start_event;
		HANDLE metrics_thread_stoped_event;

#ifdef __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

		HANDLE metrics_thread_update_event;

#endif // __MTI_SAMPLE_NON_AUTONOMOUS_METRICS_THREAD__

#ifdef __MTI_SAMPLE_GUI_MONITOR__

		//---------------------------------------------------------------------
		// Data to manage pl_gui_instance.
		//---------------------------------------------------------------------
		PROCESS_INFORMATION pi;

#endif // __MTI_SAMPLE_GUI_MONITOR__

	} MTI_SAMPLE_INSTRUMENTATION_DATA, 
	  *PMTI_SAMPLE_INSTRUMENTATION_DATA
	;

#endif // __MTI_SAMPLE_INSTRUMENTED__

typedef struct _mti_sample_data {

	MTI_SAMPLE_INTERFACE_DATA interface_data;
	MTI_SAMPLE_GEOMETRY_DATA geometry_data;
	MTI_SAMPLE_GRAPHIC_DATA graphic_data;

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	MTI_SAMPLE_INSTRUMENTATION_DATA instrumentation_data;

#endif // __MTI_SAMPLE_INSTRUMENTED__

#ifdef __MTI_SAMPLE_SENSORS_CODE__
	
	MTI_SAMPLE_GRAPHIC_DATA sensors_data;

#endif // __MTI_SAMPLE_SENSORS_CODE__

#if defined (__MTI_SAMPLE_FILE_LOG__) || defined (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

	FILE *log_file;

#endif // (__MTI_SAMPLE_FILE_LOG__) || (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

} MTI_SAMPLE_DATA, *PMTI_SAMPLE_DATA;

//-----------------------------------------------------------------------------
// macros definitions
// Note: 
//    Bn macros are respectively first, second, third and fourth Bernstein 
//    derivations to compute teh quadratic B-Spline.
// Note:
//    Proudly not using the draw Bézier APIs, it would be SO easy :)
//-----------------------------------------------------------------------------
#define B1(t) ((t) * (t) * (t))
#define B2(t) (3 * (t) * (t) * (1 - (t)))
#define B3(t) (3 * (t) * (1 - (t)) * (1 - (t)))
#define B4(t) ((1 - (t)) * (1 - (t)) * (1 - (t)))

#if defined(__MTI_SAMPLE_MTI_CODE__) && !defined(__MTI_SAMPLE_MTI_TOUCH_CODE__)

	#ifndef LODWORD
	
		#define LODWORD(u) \
			((DWORD) ((DWORDLONG)(u)))

	#endif // LODWORD

#endif // (__MTI_SAMPLE_MTI_CODE) && !(__MTI_SAMPLE_MTI_TOUCH_CODE__)

#if defined (__MTI_SAMPLE_FILE_LOG__) || defined (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

	//-------------------------------------------------------------------------
	// this macro expects the following variables defined in its scope
	//    char log_buffer[] = MTI_SAMPLE_LOG_FILE_HEADER;
	//    char cvt_buffer[MTI_SAMPLE_TIME_BUFFER_SIZE] = { '\0' };
	//-------------------------------------------------------------------------
	#define LOG_ULL(v) \
		sprintf( \
			cvt_buffer, \
			"%I64u", \
			(v) \
		); \
		strncat( \
			log_buffer, \
			cvt_buffer, \
			strlen(cvt_buffer) \
		); \
		strncat( \
			log_buffer, \
			MTI_SAMPLE_LOG_FILE_SEPARATOR, \
			strlen(MTI_SAMPLE_LOG_FILE_SEPARATOR) \
		);

	#define LOG_DOUBLE(v) \
		sprintf( \
			cvt_buffer, \
			"%g", \
			(v) \
		); \
		strncat( \
			log_buffer, \
			cvt_buffer, \
			strlen(cvt_buffer) \
		); \
		strncat( \
			log_buffer, \
			MTI_SAMPLE_LOG_FILE_SEPARATOR, \
			strlen(MTI_SAMPLE_LOG_FILE_SEPARATOR) \
		);

	#ifdef __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

		#define LOG_STRING(s) \
			sprintf( \
				cvt_buffer, \
				"%s", \
				(s) \
			); \
			strncat( \
				log_buffer, \
				cvt_buffer, \
				strlen(cvt_buffer) \
			); \
			strncat( \
				log_buffer, \
				MTI_SAMPLE_LOG_FILE_SEPARATOR, \
				strlen(MTI_SAMPLE_LOG_FILE_SEPARATOR) \
			);

	#endif // __MTI_SAMPLE_PER_GESTURE_FILE_LOG__

#endif // (__MTI_SAMPLE_FILE_LOG__) || (__MTI_SAMPLE_PER_GESTURE_FILE_LOG__)

//-----------------------------------------------------------------------------
// functions prototype
//-----------------------------------------------------------------------------
extern BOOL process_mouse_left_button_down(PMTI_SAMPLE_DATA);
extern BOOL process_mouse_right_button_down(PMTI_SAMPLE_DATA);
extern BOOL process_mouse_right_button_up(PMTI_SAMPLE_DATA);
extern BOOL process_mouse_move(PMTI_SAMPLE_DATA);
extern BOOL process_destroy(PMTI_SAMPLE_DATA);
extern BOOL process_paint(PMTI_SAMPLE_DATA);
extern BOOL process_key_pressed(PMTI_SAMPLE_DATA);

#ifdef __MTI_SAMPLE_STI_TOUCH_CODE__

	extern BOOL process_key_depressed(PMTI_SAMPLE_DATA);

#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#ifdef __MTI_SAMPLE_MTI_CODE__

	extern BOOL process_zoom(PMTI_SAMPLE_DATA);
	extern BOOL process_pan(PMTI_SAMPLE_DATA);
	extern BOOL process_rotate(PMTI_SAMPLE_DATA);
	extern BOOL process_2fingers_tap(PMTI_SAMPLE_DATA);
	extern BOOL process_roll_over(PMTI_SAMPLE_DATA);

#endif // __MTI_SAMPLE_MTI_CODE__

extern BOOL initialize_geometry_data(PMTI_SAMPLE_GEOMETRY_DATA);
extern BOOL initialize_graphic_data(PMTI_SAMPLE_GRAPHIC_DATA);
extern BOOL destroy_graphic_data(PMTI_SAMPLE_GRAPHIC_DATA);
extern BOOL initialize_interface_data(PMTI_SAMPLE_INTERFACE_DATA, HWND);

#ifdef __MTI_SAMPLE_SENSORS_CODE__

	extern BOOL re_initialize_graphic_data(PMTI_SAMPLE_GRAPHIC_DATA);

#endif // __MTI_SAMPLE_SENSORS_CODE__

#ifdef __MTI_SAMPLE_MTI_CODE__

	#ifdef __MTI_SAMPLE_MTI_TOUCH_CODE__
		extern BOOL clear_touch_contact_ids(PMTI_SAMPLE_INTERFACE_DATA);
		extern int store_touch_contact_id(PMTI_SAMPLE_INTERFACE_DATA, DWORD);
	
	#endif // __MTI_SAMPLE_MTI_TOUCH_CODE__

#endif // __MTI_SAMPLE_MTI_CODE__

#ifdef __MTI_SAMPLE_INSTRUMENTED__

	extern BOOL initialize_instrumentation_data(PMTI_SAMPLE_INSTRUMENTATION_DATA);
	extern BOOL destroy_instrumentation_data(PMTI_SAMPLE_INSTRUMENTATION_DATA);
	extern BOOL update_all_counters(PMTI_SAMPLE_INSTRUMENTATION_DATA);
	extern BOOL update_all_non_suffix_counters(PMTI_SAMPLE_INSTRUMENTATION_DATA);
	extern BOOL get_esrv_pld(PMTI_SAMPLE_INSTRUMENTATION_DATA); 
	extern BOOL remove_esrv(PMTI_SAMPLE_INSTRUMENTATION_DATA);
	extern BOOL remove_pl(PMTI_SAMPLE_INSTRUMENTATION_DATA);
	extern BOOL start_timer(PMTI_SAMPLE_DATA);
	extern BOOL stop_timer(PMTI_SAMPLE_DATA);
	extern BOOL start_metrics_thread(PMTI_SAMPLE_DATA);
	extern BOOL stop_metrics_thread(PMTI_SAMPLE_DATA);
	extern BOOL update_bezier_instrumentation_data(PMTI_SAMPLE_DATA);
	extern BOOL update_transformations_instrumentation_data(PMTI_SAMPLE_DATA);
	extern LPTHREAD_START_ROUTINE metrics_thread_function(PMTI_SAMPLE_DATA);

	#ifdef __MTI_SAMPLE_GUI_MONITOR__

		extern BOOL start_pl_gui_monitor(PMTI_SAMPLE_DATA);
		extern BOOL stop_pl_gui_monitor(PMTI_SAMPLE_DATA);

	#endif // __MTI_SAMPLE_GUI_MONITOR__

#endif // __MTI_SAMPLE_INSTRUMENTED__

#ifdef __MTI_SAMPLE_POWER_AWARE__

	extern BOOL power_suspend(PMTI_SAMPLE_DATA);
	extern BOOL power_resume(PMTI_SAMPLE_DATA);

#endif // #ifdef __MTI_SAMPLE_POWER_AWARE__

extern BOOL draw_anchor_points(PMTI_SAMPLE_DATA);
extern BOOL draw_control_points(PMTI_SAMPLE_DATA);
extern BOOL draw_control_bars(PMTI_SAMPLE_DATA);
extern BOOL draw_bezier_curve(PMTI_SAMPLE_DATA);
extern BOOL draw_background(PMTI_SAMPLE_DATA);
extern BOOL draw_help_message(PMTI_SAMPLE_DATA);

extern MTI_SAMPLE_QUADRANT find_quadrant(PPOINT, PPOINT); 

extern LRESULT CALLBACK window_class_procedure(HWND, UINT, WPARAM, LPARAM); 
extern int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int);

#ifdef __MTI_SAMPLE_SENSORS_CODE__

	extern BOOL connect_to_an_als_sensor(void);
	extern BOOL disconnect_from_als_sensor(void);

#endif // __MTI_SAMPLE_SENSORS_CODE__

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __MTI_SAMPLE_CODE__
