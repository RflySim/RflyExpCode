/*
 * File: ekf_cf_types.h
 *
 * Code generated for Simulink model 'ekf_cf'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Fri Jun 12 00:35:33 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ekf_cf_types_h_
#define RTW_HEADER_ekf_cf_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_RGBLED_MODE_ENUM_
#define DEFINED_TYPEDEF_FOR_RGBLED_MODE_ENUM_

typedef enum {
  SL_MODE_OFF = 0,                     /* Default value */
  SL_MODE_ON,
  SL_MODE_DISABLED,
  SL_MODE_BLINK_SLOW,
  SL_MODE_BLINK_NORMAL,
  SL_MODE_BLINK_FAST,
  SL_MODE_BREATHE
} RGBLED_MODE_ENUM;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RGBLED_COLOR_ENUM_
#define DEFINED_TYPEDEF_FOR_RGBLED_COLOR_ENUM_

typedef enum {
  SL_COLOR_OFF = 0,                    /* Default value */
  SL_COLOR_RED,
  SL_COLOR_GREEN,
  SL_COLOR_BLUE,
  SL_COLOR_YELLOW,
  SL_COLOR_PURPLE,
  SL_COLOR_AMBER,
  SL_COLOR_CYAN,
  SL_COLOR_WHITE
} RGBLED_COLOR_ENUM;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_ekf_cf_T RT_MODEL_ekf_cf_T;

#endif                                 /* RTW_HEADER_ekf_cf_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
