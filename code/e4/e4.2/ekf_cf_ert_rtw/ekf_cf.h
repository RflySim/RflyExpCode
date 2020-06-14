/*
 * File: ekf_cf.h
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

#ifndef RTW_HEADER_ekf_cf_h_
#define RTW_HEADER_ekf_cf_h_
#include <stddef.h>
#include <math.h>
#include <string.h>
#ifndef ekf_cf_COMMON_INCLUDES_
# define ekf_cf_COMMON_INCLUDES_
#include <stdio.h>
#include <time.h>
#include <uORB/topics/vehicle_attitude.h>
#include <poll.h>
#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>
#include <unistd.h>
#include <string.h>
#include <px4_defines.h>
#include <uORB/uORB.h>
#include <drivers/drv_hrt.h>
#include <drivers/drv_led.h>
#include <drivers/drv_board_led.h>
#include <uORB/topics/led_control.h>
#include <drivers/drv_rc_input.h>
#include <uORB/topics/sensor_combined.h>
#include "rtwtypes.h"
#endif                                 /* ekf_cf_COMMON_INCLUDES_ */

#include "ekf_cf_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

typedef struct pollfd pollfd_t;
typedef struct led_control_s led_control_s_t;

/* Block signals (auto storage) */
typedef struct {
  real32_T PHI[36];
  real32_T GAMMA[36];
  real32_T PHI_m[36];
  real32_T b_a[36];
  real32_T GAMMA_c[36];
  real32_T PHI_k[36];
  real32_T GAMMA_cx[36];
  real32_T H_k[18];
  real32_T K_k[18];
  real32_T y[18];
  char_T c[56];
  real_T x_apriori[6];
  real32_T bCn[9];
  real32_T x_aposteriori_k_x[9];
  int8_T b_I[36];
  real32_T fv0[9];
  real_T sensor_combined_o7;           /* '<S7>/sensor_combined' */
  real_T sensor_combined_o8;           /* '<S7>/sensor_combined' */
  real_T sensor_combined_o9;           /* '<S7>/sensor_combined' */
  real_T sensor_combined_o10;          /* '<S7>/sensor_combined' */
  real32_T vehicle_attitude[4];        /* '<S8>/vehicle_attitude' */
  real32_T sensor_combined_o1;         /* '<S7>/sensor_combined' */
  real32_T sensor_combined_o2;         /* '<S7>/sensor_combined' */
  real32_T sensor_combined_o3;         /* '<S7>/sensor_combined' */
  real32_T sensor_combined_o4;         /* '<S7>/sensor_combined' */
  real32_T sensor_combined_o5;         /* '<S7>/sensor_combined' */
  real32_T sensor_combined_o6;         /* '<S7>/sensor_combined' */
  RGBLED_COLOR_ENUM Switch1;           /* '<Root>/Switch1' */
  uint16_T input_rc;                   /* '<Root>/input_rc' */
} B_ekf_cf_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  led_control_s_t RGB_LED1_sl_led_control_s;/* '<Root>/RGB_LED1' */
  pollfd_t vehicle_attitude_vehicle_attitu;/* '<S8>/vehicle_attitude' */
  pollfd_t input_rc_input_rc_fd;       /* '<Root>/input_rc' */
  pollfd_t sensor_combined_sensor_fd;  /* '<S7>/sensor_combined' */
  real_T lognumstr;                    /* '<S11>/MATLAB Function1' */
  real_T count;                        /* '<S5>/MATLAB Function' */
  real32_T Delay2_DSTATE;              /* '<S3>/Delay2' */
  real32_T Delay_DSTATE[6];            /* '<S6>/Delay' */
  real32_T Delay1_DSTATE[36];          /* '<S6>/Delay1' */
  real32_T Delay_DSTATE_m;             /* '<S4>/Delay' */
  real32_T Delay1_DSTATE_l;            /* '<S4>/Delay1' */
  orb_advert_t RGB_LED1_orb_advert_t;  /* '<Root>/RGB_LED1' */
  uint32_T count_g;                    /* '<S11>/MATLAB Function1' */
  uint16_T elem_size;                  /* '<S11>/MATLAB Function1' */
  uint8_T vect_size;                   /* '<S11>/MATLAB Function1' */
  boolean_T isflushed;                 /* '<S11>/MATLAB Function1' */
  boolean_T isopen;                    /* '<S11>/MATLAB Function1' */
  FILE* fp;                            /* '<S11>/MATLAB Function1' */
} DW_ekf_cf_T;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: logname
   * Referenced by: '<S11>/MATLAB Function1'
   */
  uint8_T MATLABFunction1_logname[22];
} ConstP_ekf_cf_T;

/* Real-time Model Data Structure */
struct tag_RTM_ekf_cf_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals (auto storage) */
extern B_ekf_cf_T ekf_cf_B;

/* Block states (auto storage) */
extern DW_ekf_cf_T ekf_cf_DW;

/* Constant parameters (auto storage) */
extern const ConstP_ekf_cf_T ekf_cf_ConstP;

/* External function called from main */
extern void ekf_cf_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void ekf_cf_SetEventsForThisBaseStep(boolean_T *eventFlags);
extern void ekf_cf_initialize(void);
extern void ekf_cf_step(int_T tid);
extern void ekf_cf_terminate(void);

/* Real-time Model object */
extern RT_MODEL_ekf_cf_T *const ekf_cf_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S11>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S11>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion5' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ekf_cf'
 * '<S1>'   : 'ekf_cf/MATLAB Function1'
 * '<S2>'   : 'ekf_cf/MATLAB Function2'
 * '<S3>'   : 'ekf_cf/Subsystem'
 * '<S4>'   : 'ekf_cf/cf'
 * '<S5>'   : 'ekf_cf/datalog'
 * '<S6>'   : 'ekf_cf/ekf'
 * '<S7>'   : 'ekf_cf/sensor_combined'
 * '<S8>'   : 'ekf_cf/vehicle_attitude'
 * '<S9>'   : 'ekf_cf/cf/MATLAB Function1'
 * '<S10>'  : 'ekf_cf/datalog/MATLAB Function'
 * '<S11>'  : 'ekf_cf/datalog/logger'
 * '<S12>'  : 'ekf_cf/datalog/logger/MATLAB Function1'
 * '<S13>'  : 'ekf_cf/ekf/MATLAB Function'
 * '<S14>'  : 'ekf_cf/vehicle_attitude/px4_est_en'
 * '<S15>'  : 'ekf_cf/vehicle_attitude/quat2eul'
 */
#endif                                 /* RTW_HEADER_ekf_cf_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
