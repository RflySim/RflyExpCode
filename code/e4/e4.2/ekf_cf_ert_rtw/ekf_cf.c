/*
 * File: ekf_cf.c
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

#include "ekf_cf.h"
#include "ekf_cf_private.h"

/* Block signals (auto storage) */
B_ekf_cf_T ekf_cf_B;

/* Block states (auto storage) */
DW_ekf_cf_T ekf_cf_DW;

/* Real-time model */
RT_MODEL_ekf_cf_T ekf_cf_M_;
RT_MODEL_ekf_cf_T *const ekf_cf_M = &ekf_cf_M_;

/* Forward declaration for local functions */
static real32_T ekf_cf_norm(const real32_T x[3]);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void ekf_cf_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(ekf_cf_M, 1));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (ekf_cf_M->Timing.TaskCounters.TID[1])++;
  if ((ekf_cf_M->Timing.TaskCounters.TID[1]) > 3) {/* Sample time: [0.004s, 0.0s] */
    ekf_cf_M->Timing.TaskCounters.TID[1] = 0;
  }
}

real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    if (u0 > 0.0F) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0F) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = (real32_T)atan2((real32_T)u0_0, (real32_T)u1_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = (real32_T)atan2(u0, u1);
  }

  return y;
}

/* Function for MATLAB Function: '<S6>/MATLAB Function' */
static real32_T ekf_cf_norm(const real32_T x[3])
{
  real32_T y;
  real32_T scale;
  real32_T absxk;
  real32_T t;
  scale = 1.29246971E-26F;
  absxk = (real32_T)fabs(x[0]);
  if (absxk > 1.29246971E-26F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.29246971E-26F;
    y = t * t;
  }

  absxk = (real32_T)fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = (real32_T)fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * (real32_T)sqrt(y);
}

/* Model step function for TID0 */
void ekf_cf_step0(void)                /* Sample time: [0.001s, 0.0s] */
{
  {                                    /* Sample time: [0.001s, 0.0s] */
    rate_monotonic_scheduler();
  }
}

/* Model step function for TID1 */
void ekf_cf_step1(void)                /* Sample time: [0.004s, 0.0s] */
{
  real32_T theta;
  int8_T I[9];
  int32_T r1;
  int32_T r2;
  int32_T r3;
  real32_T maxval;
  real32_T a21;
  int32_T rtemp;
  static const int8_T b[18] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0 };

  static const int8_T c[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T b_a[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real32_T theta_am;
  uint8_T elem_type;
  static const char_T mlStrVer[8] = { 'M', 'W', 'L', 'O', 'G', 'V', '0', '1' };

  uint32_T tm;
  uint32_T tmptr;
  uint16_T recSize;
  static const char_T b_0[28] = { 'C', 'L', 'O', 'S', 'I', 'N', 'G', ' ', 'f',
    'i', 'l', 'e', '.', ' ', 'c', 'o', 'u', 'n', 't', ' ', '=', ' ', '%', 'd',
    ' ', '%', 'c', '\x00' };

  static const char_T c_0[56] = { 'O', 'P', 'E', 'N', 'I', 'N', 'G', ' ', 'f',
    'i', 'l', 'e', ' ', '%', 's', ' ', 'v', 'e', 'c', 't', '_', 's', 'i', 'z',
    'e', ' ', '%', 'd', ' ', 'e', 'l', 'e', 'm', '_', 's', 'i', 'z', 'e', ' ',
    '%', 'd', ' ', 'n', 'u', 'm', 'R', 'e', 'c', 's', ' ', '%', 'd', ' ', '%',
    'c', '\x00' };

  boolean_T rtb_en;
  real32_T rtb_Saturation;
  boolean_T rtb_px4_att_est_ok;
  real32_T rtb_TmpSignalConversionAtSFunct[6];
  real32_T rtb_TmpSignalConversionAtSFun_o[7];
  real32_T rtb_phi;
  char_T b_1[28];
  char_T d[3];
  char_T tmp[29];
  real32_T rtb_TmpSignalConversionAtSFun_1[3];
  real32_T a_m_idx_0;
  real32_T a_m_idx_2;
  real32_T a_m_idx_1;
  real_T rtb_px4_att_est_ok_tmp;
  int32_T PHI_tmp;
  int32_T GAMMA_tmp;
  int32_T K_k_tmp;
  real32_T maxval_tmp;
  real32_T maxval_tmp_0;

  /* S-Function (sfun_px4_vehicle_attitude): '<S8>/vehicle_attitude'
   *
   * Block description for '<S8>/vehicle_attitude':
   *  This block gives access to the running service that calculates the vehicle＊s attitude.  A uORB topic (vehicle_attitude (attitude measurements)) publisher MUST be running in order for this block to provide valid signal values.  The available ones as of v1.3 are:
   *  attitude_estimator_ekf 每 EKF-Extended Kalman Filter for attitude estimation
   *  attitude_estimator_so3 每 SO(3)-attitude estimation by using accelerometer, gyroscopes and magnetometer
   *  One of these MUST be running on the px4fmu in order for this block to return valid values.  Refer to the sample model: px4demo_attitude_control.slx. Attitude in NED (North-East-Down) body frame in SI units.
   *  Signal definitions:
   *  Roll 每 single value, Roll angle (rad, Tait-Bryan, NED)
   *  Pitch 每 single value, Pitch angle (rad, Tait-Bryan, NED)
   *  Yaw 每 single value, Yaw angle (rad, Tait-Bryan, NED)
   *  Quaternion (NED) 每 single(4) values (optional based on the uORB publisher)
   *
   */
  {
    bool updated;
    orb_check(ekf_cf_DW.vehicle_attitude_vehicle_attitu.fd, &updated);
    if (updated) {
      struct vehicle_attitude_s raw;
      orb_copy(ORB_ID(vehicle_attitude),
               ekf_cf_DW.vehicle_attitude_vehicle_attitu.fd, &raw);

      /* read out the Quaternion values */
      ekf_cf_B.vehicle_attitude[0] = raw.q[0];
      ekf_cf_B.vehicle_attitude[1] = raw.q[1];
      ekf_cf_B.vehicle_attitude[2] = raw.q[2];
      ekf_cf_B.vehicle_attitude[3] = raw.q[3];
    }
  }

  /* MATLAB Function: '<S8>/quat2eul' */
  theta = (real32_T)asin(-((ekf_cf_B.vehicle_attitude[1] *
    ekf_cf_B.vehicle_attitude[3] - ekf_cf_B.vehicle_attitude[0] *
    ekf_cf_B.vehicle_attitude[2]) * 2.0F));
  if ((real32_T)fabs(theta - 1.57079637F) < 0.001) {
    rtb_phi = 0.0F;
  } else if ((real32_T)fabs(theta + 1.57079637F) < 0.001) {
    rtb_phi = 0.0F;
  } else {
    rtb_phi = rt_atan2f_snf((ekf_cf_B.vehicle_attitude[0] *
      ekf_cf_B.vehicle_attitude[1] + ekf_cf_B.vehicle_attitude[2] *
      ekf_cf_B.vehicle_attitude[3]) * 2.0F, ((ekf_cf_B.vehicle_attitude[0] *
      ekf_cf_B.vehicle_attitude[0] - ekf_cf_B.vehicle_attitude[1] *
      ekf_cf_B.vehicle_attitude[1]) - ekf_cf_B.vehicle_attitude[2] *
      ekf_cf_B.vehicle_attitude[2]) + ekf_cf_B.vehicle_attitude[3] *
      ekf_cf_B.vehicle_attitude[3]);
  }

  /* MATLAB Function: '<S8>/px4_est_en' incorporates:
   *  MATLAB Function: '<S8>/quat2eul'
   */
  rtb_px4_att_est_ok_tmp = (real32_T)fabs(rtb_phi);
  rtb_px4_att_est_ok = (((rtb_px4_att_est_ok_tmp < 1.0E-6) && (!((real32_T)fabs
    (theta) < 1.0E-6))) || (!(rtb_px4_att_est_ok_tmp < 1.0E-6)));

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant8'
   */
  if (rtb_px4_att_est_ok) {
    ekf_cf_B.Switch1 = SL_COLOR_GREEN;
  } else {
    ekf_cf_B.Switch1 = SL_COLOR_RED;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* S-Function (sfun_px4_rgbled): '<Root>/RGB_LED1' incorporates:
   *  Constant: '<Root>/Constant4'
   *
   * Block description for '<Root>/RGB_LED1':
   *  This block gives the user control over various lighting modes of the RGB LED available on the PX4 hardware.
   *  This block accepts 2 inputs: Mode and Color.  These are enumeration data types.  You can find out what values are valid in the MATLAB command window by typing:
   *  Enumeration members for class 'RGBLED_COLOR_ENUM':
   *      SL_COLOR_OFF
   *      SL_COLOR_RED
   *      SL_COLOR_GREEN
   *      SL_COLOR_BLUE
   *      SL_COLOR_YELLOW
   *      SL_COLOR_PURPLE
   *      SL_COLOR_AMBER
   *      SL_COLOR_CYAN
   *      SL_COLOR_WHITE
   *  Enumeration members for class 'RGBLED_MODE_ENUM':
   *      SL_MODE_OFF
   *      SL_MODE_ON
   *      SL_MODE_DISABLED
   *      SL_MODE_BLINK_SLOW
   *      SL_MODE_BLINK_NORMAL
   *      SL_MODE_BLINK_FAST
   *      SL_MODE_BREATHE
   *  Look at the sample Simulink model: px4demo_rgbled.slx for an example of how to use this block.
   */
  ekf_cf_DW.RGB_LED1_sl_led_control_s.mode = SL_MODE_BLINK_NORMAL;
  ekf_cf_DW.RGB_LED1_sl_led_control_s.color = ekf_cf_B.Switch1;
  ekf_cf_DW.RGB_LED1_sl_led_control_s.num_blinks = 0;
  ekf_cf_DW.RGB_LED1_sl_led_control_s.priority = 0;
  ekf_cf_DW.RGB_LED1_sl_led_control_s.timestamp = hrt_absolute_time();
  orb_publish(ORB_ID(led_control), ekf_cf_DW.RGB_LED1_orb_advert_t ,
              &ekf_cf_DW.RGB_LED1_sl_led_control_s);

  /* S-Function (sfun_px4_input_rc): '<Root>/input_rc'
   *
   * Block description for '<Root>/input_rc':
   *  RC Input Block
   *
   *  This block provides user input control to the model.
   *  It uses the input_rc uORB topic.
   *
   *  The user has the ability to choose which channels are available as outputs from this block and also some optional outputs. These include
   *  Channels 1 through 18
   *  double data type indicating the PWM value from the controller
   *  measured pulse widths for each of the supported channels
   *  Channel Count
   *  uint32 data type of the number of channels which are detector by the PX4
   *  RC Failsafe
   *  boolean data types indicating that the RC Tx is sending the FailSafe signal (if equipped and properly setup)
   *  explicit failsafe flag: true on TX failure or TX out of range , false otherwise.
   *  Only the true state is reliable, as there are some (PPM) receivers on the market going into failsafe without telling us explicitly.
   *  RC Input Source
   *  Enumeration data type indicating which source the RC input is from.
   *  Valid values are found in the ENUM file: RC_INPUT_SOURCE_ENUM.m
   *            Enumeration members for class 'RC_INPUT_SOURCE_ENUM':
   *            RCINPUT_SOURCE_UNKNOWN         (0)
   *            RCINPUT_SOURCE_PX4FMU_PPM      (1)
   *            RCINPUT_SOURCE_PX4IO_PPM       (2)
   *            RCINPUT_SOURCE_PX4IO_SPEKTRUM  (3)
   *            RCINPUT_SOURCE_PX4IO_SBUS      (4)
   *            RCINPUT_SOURCE_PX4IO_ST24      (5)
   *            RCINPUT_SOURCE_MAVLINK         (6)
   *            RCINPUT_SOURCE_QURT            (7)
   *            RCINPUT_SOURCE_PX4FMU_SPEKTRUM (8)
   *            RCINPUT_SOURCE_PX4FMU_SBUS     (9)
   *            RCINPUT_SOURCE_PX4FMU_ST24     (10)
   *            RCINPUT_SOURCE_PX4FMU_SUMD     (11)
   *            RCINPUT_SOURCE_PX4FMU_DSM      (12)
   *            RCINPUT_SOURCE_PX4IO_SUMD      (13)
   *
   *  RSSI - Receive signal strength index
   *  receive signal strength indicator (RSSI): < 0: Undefined, 0: no signal, 255: full reception
   *  RC Lost Connection
   *  boolean data type indicating RC receiver connection status
   *  True, if no frame has arrived in the expected time, false otherwise.
   *  True usally means that the receiver has been disconnected, but can also indicate a radio link loss on "stupid" systems.
   *  Will remain false, if a RX with failsafe option continues to transmit frames after a link loss.
   *
   *  Sample Model: px4demo_input_rc.slx
   */
  {
    bool updated;
    orb_check(ekf_cf_DW.input_rc_input_rc_fd.fd, &updated);
    if (updated) {
      struct rc_input_values pwm_inputs;

      /* copy input_rc raw data into local buffer (uint16)*/
      orb_copy(ORB_ID(input_rc), ekf_cf_DW.input_rc_input_rc_fd.fd, &pwm_inputs);
      ekf_cf_B.input_rc = pwm_inputs.values[4];
    }
  }

  /* MATLAB Function: '<S5>/MATLAB Function' */
  if (rtb_px4_att_est_ok) {
    ekf_cf_DW.count++;
  }

  if (ekf_cf_DW.count > 60000.0) {
    rtb_en = false;
    ekf_cf_DW.count = 0.0;
  } else {
    rtb_en = true;
  }

  /* End of MATLAB Function: '<S5>/MATLAB Function' */

  /* S-Function (sfun_px4_sensor_combined): '<S7>/sensor_combined'
   *
   * Block description for '<S7>/sensor_combined':
   *  Sensor Combined Block
   *
   *  This block enables access to the various sensors available on the px4fmu-v2 hardware.
   *  The user can use these signals in the Simulink control model.
   *  The sample time needs to be provided in the mask dialog.
   *  Optional output ports can also be selected.
   *  Refer to the sample model: px4demo_attitude_control.slx
   *
   *  Signal definitions:
   *  Magnetometer (x,y,z) - single values 每 Magnetic field in NED body frame, in Gauss
   *  Accelerometer (x,y,z) - single values 每 Acceleration in NED body frame, in m/s^2
   *  Gyroscope (p,q,r) - single values 每 Angular velocity in radians per second
   *  Barometer (Altitude) - single value 每 Barometric pressure, already temperature compensated (millibars)
   *  RunTime (timestamp) - double value 每 Timestamp in microseconds since boot, from gyro
   *
   *  The sensor_combined block needs to have the px4io service running on the PX4 hardware in order to get valid signal values.

   */
  {
    bool updated;
    orb_check(ekf_cf_DW.sensor_combined_sensor_fd.fd, &updated);
    if (updated) {
      /* obtained data sensor combined */
      struct sensor_combined_s raw;

      /* copy sensors raw data into local buffer */
      orb_copy(ORB_ID(sensor_combined), ekf_cf_DW.sensor_combined_sensor_fd.fd,
               &raw);

      /* read out the accelerometer X,Y,Z */
      ekf_cf_B.sensor_combined_o1 = (float)raw.accelerometer_m_s2[0];
      ekf_cf_B.sensor_combined_o2 = (float)raw.accelerometer_m_s2[1];
      ekf_cf_B.sensor_combined_o3 = (float)raw.accelerometer_m_s2[2];

      /* read out the gyro X,Y,Z */
      ekf_cf_B.sensor_combined_o4 = (float)raw.gyro_rad[0];
      ekf_cf_B.sensor_combined_o5 = (float)raw.gyro_rad[1];
      ekf_cf_B.sensor_combined_o6 = (float)raw.gyro_rad[2];

      /* read out the timestamp */
      ekf_cf_B.sensor_combined_o7 = (double)raw.magnetometer_timestamp_relative;
      ekf_cf_B.sensor_combined_o8 = (double)raw.accelerometer_timestamp_relative;
      ekf_cf_B.sensor_combined_o9 = (double)raw.baro_timestamp_relative;
      ekf_cf_B.sensor_combined_o10 = (double)raw.timestamp;
    }
  }

  /* Gain: '<S3>/Gain1' incorporates:
   *  DataTypeConversion: '<S7>/Data Type Conversion6'
   *  Delay: '<S3>/Delay2'
   *  Sum: '<S3>/Add'
   */
  rtb_Saturation = ((real32_T)ekf_cf_B.sensor_combined_o10 -
                    ekf_cf_DW.Delay2_DSTATE) * 1.0E-6F;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_Saturation > 0.1F) {
    rtb_Saturation = 0.1F;
  } else {
    if (rtb_Saturation < 0.001F) {
      rtb_Saturation = 0.001F;
    }
  }

  /* End of Saturate: '<S3>/Saturation' */

  /* SignalConversion: '<S13>/TmpSignal ConversionAt SFunction Inport2' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function'
   */
  rtb_TmpSignalConversionAtSFunct[0] = ekf_cf_B.sensor_combined_o4;
  rtb_TmpSignalConversionAtSFunct[1] = ekf_cf_B.sensor_combined_o5;
  rtb_TmpSignalConversionAtSFunct[2] = ekf_cf_B.sensor_combined_o6;
  rtb_TmpSignalConversionAtSFunct[3] = ekf_cf_B.sensor_combined_o1;
  rtb_TmpSignalConversionAtSFunct[4] = ekf_cf_B.sensor_combined_o2;
  rtb_TmpSignalConversionAtSFunct[5] = ekf_cf_B.sensor_combined_o3;

  /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
   *  Constant: '<S6>/v'
   *  Delay: '<S6>/Delay'
   *  Delay: '<S6>/Delay1'
   *  SignalConversion: '<S13>/TmpSignal ConversionAt SFunction Inport2'
   */
  for (r1 = 0; r1 < 9; r1++) {
    I[r1] = 0;
  }

  I[0] = 1;
  I[4] = 1;
  I[8] = 1;
  ekf_cf_B.fv0[0] = 0.0F * rtb_Saturation;
  maxval = ekf_cf_B.sensor_combined_o6 - ekf_cf_DW.Delay_DSTATE[2];
  ekf_cf_B.fv0[3] = -maxval * rtb_Saturation;
  a21 = ekf_cf_B.sensor_combined_o5 - ekf_cf_DW.Delay_DSTATE[1];
  ekf_cf_B.fv0[6] = a21 * rtb_Saturation;
  ekf_cf_B.fv0[1] = maxval * rtb_Saturation;
  ekf_cf_B.fv0[4] = 0.0F * rtb_Saturation;
  maxval = ekf_cf_B.sensor_combined_o4 - ekf_cf_DW.Delay_DSTATE[0];
  ekf_cf_B.fv0[7] = -maxval * rtb_Saturation;
  ekf_cf_B.fv0[2] = -a21 * rtb_Saturation;
  ekf_cf_B.fv0[5] = maxval * rtb_Saturation;
  ekf_cf_B.fv0[8] = 0.0F * rtb_Saturation;
  for (r1 = 0; r1 < 3; r1++) {
    ekf_cf_B.bCn[3 * r1] = (real32_T)I[3 * r1] - ekf_cf_B.fv0[3 * r1];
    r2 = 3 * r1 + 1;
    ekf_cf_B.bCn[1 + 3 * r1] = (real32_T)I[r2] - ekf_cf_B.fv0[r2];
    r2 = 3 * r1 + 2;
    ekf_cf_B.bCn[2 + 3 * r1] = (real32_T)I[r2] - ekf_cf_B.fv0[r2];
  }

  for (r1 = 0; r1 < 6; r1++) {
    ekf_cf_B.x_apriori[r1] = 0.0;
  }

  for (r1 = 0; r1 < 3; r1++) {
    ekf_cf_B.x_apriori[r1] = ekf_cf_DW.Delay_DSTATE[r1];
    ekf_cf_B.x_apriori[3 + r1] = (ekf_cf_B.bCn[r1 + 3] * ekf_cf_DW.Delay_DSTATE
      [4] + ekf_cf_B.bCn[r1] * ekf_cf_DW.Delay_DSTATE[3]) + ekf_cf_B.bCn[r1 + 6]
      * ekf_cf_DW.Delay_DSTATE[5];
  }

  ekf_cf_B.x_aposteriori_k_x[0] = 0.0F;
  ekf_cf_B.x_aposteriori_k_x[3] = -ekf_cf_DW.Delay_DSTATE[5];
  ekf_cf_B.x_aposteriori_k_x[6] = ekf_cf_DW.Delay_DSTATE[4];
  ekf_cf_B.x_aposteriori_k_x[1] = ekf_cf_DW.Delay_DSTATE[5];
  ekf_cf_B.x_aposteriori_k_x[4] = 0.0F;
  ekf_cf_B.x_aposteriori_k_x[7] = -ekf_cf_DW.Delay_DSTATE[3];
  ekf_cf_B.x_aposteriori_k_x[2] = -ekf_cf_DW.Delay_DSTATE[4];
  ekf_cf_B.x_aposteriori_k_x[5] = ekf_cf_DW.Delay_DSTATE[3];
  ekf_cf_B.x_aposteriori_k_x[8] = 0.0F;
  for (r1 = 0; r1 < 6; r1++) {
    ekf_cf_B.PHI[6 * r1] = b[3 * r1];
    ekf_cf_B.PHI[1 + 6 * r1] = b[3 * r1 + 1];
    ekf_cf_B.PHI[2 + 6 * r1] = b[3 * r1 + 2];
  }

  for (r1 = 0; r1 < 3; r1++) {
    rtemp = 3 + 6 * r1;
    maxval = -ekf_cf_B.x_aposteriori_k_x[3 * r1] * rtb_Saturation;
    ekf_cf_B.PHI[rtemp] = maxval;
    r2 = 6 * (r1 + 3);
    r3 = 3 + r2;
    ekf_cf_B.PHI[r3] = ekf_cf_B.bCn[3 * r1];
    ekf_cf_B.GAMMA[6 * r1] = (real32_T)c[3 * r1] * rtb_Saturation;
    ekf_cf_B.GAMMA[r2] = 0.0F;
    ekf_cf_B.GAMMA[rtemp] = 0.0F;
    ekf_cf_B.GAMMA[r3] = maxval;
    rtemp = 3 * r1 + 1;
    r3 = 4 + 6 * r1;
    maxval = -ekf_cf_B.x_aposteriori_k_x[rtemp] * rtb_Saturation;
    ekf_cf_B.PHI[r3] = maxval;
    PHI_tmp = 4 + r2;
    ekf_cf_B.PHI[PHI_tmp] = ekf_cf_B.bCn[rtemp];
    ekf_cf_B.GAMMA[1 + 6 * r1] = (real32_T)c[rtemp] * rtb_Saturation;
    ekf_cf_B.GAMMA[1 + r2] = 0.0F;
    ekf_cf_B.GAMMA[r3] = 0.0F;
    ekf_cf_B.GAMMA[PHI_tmp] = maxval;
    rtemp = 3 * r1 + 2;
    r3 = 5 + 6 * r1;
    maxval = -ekf_cf_B.x_aposteriori_k_x[rtemp] * rtb_Saturation;
    ekf_cf_B.PHI[r3] = maxval;
    PHI_tmp = 5 + r2;
    ekf_cf_B.PHI[PHI_tmp] = ekf_cf_B.bCn[rtemp];
    ekf_cf_B.GAMMA[2 + 6 * r1] = (real32_T)c[rtemp] * rtb_Saturation;
    ekf_cf_B.GAMMA[2 + r2] = 0.0F;
    ekf_cf_B.GAMMA[r3] = 0.0F;
    ekf_cf_B.GAMMA[PHI_tmp] = maxval;
  }

  for (r1 = 0; r1 < 6; r1++) {
    for (r2 = 0; r2 < 6; r2++) {
      rtemp = r2 + 6 * r1;
      ekf_cf_B.PHI_m[rtemp] = 0.0F;
      for (r3 = 0; r3 < 6; r3++) {
        ekf_cf_B.PHI_m[rtemp] = ekf_cf_B.PHI[6 * r3 + r2] *
          ekf_cf_DW.Delay1_DSTATE[6 * r1 + r3] + ekf_cf_B.PHI_m[6 * r1 + r2];
      }
    }
  }

  for (r1 = 0; r1 < 3; r1++) {
    ekf_cf_B.b_a[6 * r1] = (real32_T)((real_T)b_a[3 * r1] * 0.08);
    r2 = 6 * (r1 + 3);
    ekf_cf_B.b_a[r2] = 0.0F;
    ekf_cf_B.b_a[3 + 6 * r1] = 0.0F;
    ekf_cf_B.b_a[3 + r2] = (real32_T)((real_T)b_a[3 * r1] * 0.01);
    ekf_cf_B.b_a[1 + 6 * r1] = (real32_T)((real_T)b_a[3 * r1 + 1] * 0.08);
    ekf_cf_B.b_a[1 + r2] = 0.0F;
    ekf_cf_B.b_a[4 + 6 * r1] = 0.0F;
    ekf_cf_B.b_a[4 + r2] = (real32_T)((real_T)b_a[3 * r1 + 1] * 0.01);
    ekf_cf_B.b_a[2 + 6 * r1] = (real32_T)((real_T)b_a[3 * r1 + 2] * 0.08);
    ekf_cf_B.b_a[2 + r2] = 0.0F;
    ekf_cf_B.b_a[5 + 6 * r1] = 0.0F;
    ekf_cf_B.b_a[5 + r2] = (real32_T)((real_T)b_a[3 * r1 + 2] * 0.01);
  }

  for (r1 = 0; r1 < 6; r1++) {
    for (r2 = 0; r2 < 6; r2++) {
      rtemp = r1 + 6 * r2;
      ekf_cf_B.GAMMA_c[rtemp] = 0.0F;
      ekf_cf_B.PHI_k[rtemp] = 0.0F;
      for (r3 = 0; r3 < 6; r3++) {
        PHI_tmp = 6 * r3 + r1;
        GAMMA_tmp = 6 * r2 + r1;
        ekf_cf_B.GAMMA_c[rtemp] = ekf_cf_B.GAMMA[PHI_tmp] * ekf_cf_B.b_a[6 * r2
          + r3] + ekf_cf_B.GAMMA_c[GAMMA_tmp];
        ekf_cf_B.PHI_k[rtemp] = ekf_cf_B.PHI_m[PHI_tmp] * ekf_cf_B.PHI[6 * r3 +
          r2] + ekf_cf_B.PHI_k[GAMMA_tmp];
      }
    }

    for (r2 = 0; r2 < 6; r2++) {
      rtemp = r1 + 6 * r2;
      ekf_cf_B.GAMMA_cx[rtemp] = 0.0F;
      for (r3 = 0; r3 < 6; r3++) {
        ekf_cf_B.GAMMA_cx[rtemp] = ekf_cf_B.GAMMA_c[6 * r3 + r1] *
          ekf_cf_B.GAMMA[6 * r3 + r2] + ekf_cf_B.GAMMA_cx[6 * r2 + r1];
      }
    }
  }

  for (r1 = 0; r1 < 6; r1++) {
    for (r2 = 0; r2 < 6; r2++) {
      r3 = 6 * r1 + r2;
      ekf_cf_B.PHI[r2 + 6 * r1] = ekf_cf_B.PHI_k[r3] + ekf_cf_B.GAMMA_cx[r3];
    }
  }

  maxval = -ekf_cf_norm(&rtb_TmpSignalConversionAtSFunct[3]);
  for (r1 = 0; r1 < 9; r1++) {
    ekf_cf_B.H_k[r1] = 0.0F;
    ekf_cf_B.H_k[r1 + 9] = maxval * (real32_T)c[r1];
  }

  for (r1 = 0; r1 < 6; r1++) {
    for (r2 = 0; r2 < 3; r2++) {
      rtemp = r1 + 6 * r2;
      ekf_cf_B.y[rtemp] = 0.0F;
      for (r3 = 0; r3 < 6; r3++) {
        ekf_cf_B.y[rtemp] = ekf_cf_B.PHI[6 * r3 + r1] * ekf_cf_B.H_k[3 * r3 + r2]
          + ekf_cf_B.y[6 * r2 + r1];
      }
    }
  }

  for (r1 = 0; r1 < 3; r1++) {
    for (r2 = 0; r2 < 6; r2++) {
      rtemp = r1 + 3 * r2;
      ekf_cf_B.K_k[rtemp] = 0.0F;
      for (r3 = 0; r3 < 6; r3++) {
        ekf_cf_B.K_k[rtemp] = ekf_cf_B.H_k[3 * r3 + r1] * ekf_cf_B.PHI[6 * r2 +
          r3] + ekf_cf_B.K_k[3 * r2 + r1];
      }
    }

    for (r2 = 0; r2 < 3; r2++) {
      maxval = 0.0F;
      for (r3 = 0; r3 < 6; r3++) {
        maxval += ekf_cf_B.K_k[3 * r3 + r1] * ekf_cf_B.H_k[3 * r3 + r2];
      }

      ekf_cf_B.bCn[r1 + 3 * r2] = (real32_T)b_a[3 * r2 + r1] * 50.0F + maxval;
    }
  }

  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = (real32_T)fabs(ekf_cf_B.bCn[0]);
  a21 = (real32_T)fabs(ekf_cf_B.bCn[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if ((real32_T)fabs(ekf_cf_B.bCn[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  ekf_cf_B.bCn[r2] /= ekf_cf_B.bCn[r1];
  ekf_cf_B.bCn[r3] /= ekf_cf_B.bCn[r1];
  ekf_cf_B.bCn[3 + r2] -= ekf_cf_B.bCn[3 + r1] * ekf_cf_B.bCn[r2];
  ekf_cf_B.bCn[3 + r3] -= ekf_cf_B.bCn[3 + r1] * ekf_cf_B.bCn[r3];
  ekf_cf_B.bCn[6 + r2] -= ekf_cf_B.bCn[6 + r1] * ekf_cf_B.bCn[r2];
  ekf_cf_B.bCn[6 + r3] -= ekf_cf_B.bCn[6 + r1] * ekf_cf_B.bCn[r3];
  if ((real32_T)fabs(ekf_cf_B.bCn[3 + r3]) > (real32_T)fabs(ekf_cf_B.bCn[3 + r2]))
  {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  ekf_cf_B.bCn[3 + r3] /= ekf_cf_B.bCn[3 + r2];
  ekf_cf_B.bCn[6 + r3] -= ekf_cf_B.bCn[3 + r3] * ekf_cf_B.bCn[6 + r2];
  for (rtemp = 0; rtemp < 6; rtemp++) {
    PHI_tmp = rtemp + 6 * r1;
    ekf_cf_B.K_k[PHI_tmp] = ekf_cf_B.y[rtemp] / ekf_cf_B.bCn[r1];
    GAMMA_tmp = rtemp + 6 * r2;
    ekf_cf_B.K_k[GAMMA_tmp] = ekf_cf_B.y[6 + rtemp] - ekf_cf_B.K_k[6 * r1 +
      rtemp] * ekf_cf_B.bCn[3 + r1];
    K_k_tmp = rtemp + 6 * r3;
    ekf_cf_B.K_k[K_k_tmp] = ekf_cf_B.y[12 + rtemp] - ekf_cf_B.K_k[6 * r1 + rtemp]
      * ekf_cf_B.bCn[6 + r1];
    ekf_cf_B.K_k[GAMMA_tmp] = ekf_cf_B.K_k[6 * r2 + rtemp] / ekf_cf_B.bCn[3 + r2];
    ekf_cf_B.K_k[K_k_tmp] = ekf_cf_B.K_k[6 * r3 + rtemp] - ekf_cf_B.K_k[6 * r2 +
      rtemp] * ekf_cf_B.bCn[6 + r2];
    ekf_cf_B.K_k[K_k_tmp] = ekf_cf_B.K_k[6 * r3 + rtemp] / ekf_cf_B.bCn[6 + r3];
    ekf_cf_B.K_k[GAMMA_tmp] = ekf_cf_B.K_k[6 * r2 + rtemp] - ekf_cf_B.K_k[6 * r3
      + rtemp] * ekf_cf_B.bCn[3 + r3];
    ekf_cf_B.K_k[PHI_tmp] = ekf_cf_B.K_k[6 * r1 + rtemp] - ekf_cf_B.K_k[6 * r3 +
      rtemp] * ekf_cf_B.bCn[r3];
    ekf_cf_B.K_k[PHI_tmp] = ekf_cf_B.K_k[6 * r1 + rtemp] - ekf_cf_B.K_k[6 * r2 +
      rtemp] * ekf_cf_B.bCn[r2];
  }

  for (r1 = 0; r1 < 3; r1++) {
    maxval = 0.0F;
    for (r2 = 0; r2 < 6; r2++) {
      maxval += ekf_cf_B.H_k[3 * r2 + r1] * (real32_T)ekf_cf_B.x_apriori[r2];
    }

    rtb_TmpSignalConversionAtSFun_1[r1] = rtb_TmpSignalConversionAtSFunct[3 + r1]
      - maxval;
  }

  for (r1 = 0; r1 < 6; r1++) {
    rtb_TmpSignalConversionAtSFunct[r1] = ((ekf_cf_B.K_k[r1 + 6] *
      rtb_TmpSignalConversionAtSFun_1[1] + ekf_cf_B.K_k[r1] *
      rtb_TmpSignalConversionAtSFun_1[0]) + ekf_cf_B.K_k[r1 + 12] *
      rtb_TmpSignalConversionAtSFun_1[2]) + (real32_T)ekf_cf_B.x_apriori[r1];
  }

  for (r1 = 0; r1 < 36; r1++) {
    ekf_cf_B.b_I[r1] = 0;
  }

  for (r1 = 0; r1 < 6; r1++) {
    ekf_cf_B.b_I[r1 + 6 * r1] = 1;
  }

  maxval = ekf_cf_norm(&rtb_TmpSignalConversionAtSFunct[3]);
  a_m_idx_0 = rtb_TmpSignalConversionAtSFunct[3] / maxval;
  a_m_idx_1 = rtb_TmpSignalConversionAtSFunct[4] / maxval;
  a_m_idx_2 = rtb_TmpSignalConversionAtSFunct[5] / maxval;

  /* MATLAB Function: '<S4>/MATLAB Function1' incorporates:
   *  Constant: '<S4>/tao'
   *  Delay: '<S4>/Delay'
   *  Delay: '<S4>/Delay1'
   *  SignalConversion: '<S9>/TmpSignal ConversionAt SFunction Inport2'
   */
  a21 = (real32_T)sqrt((ekf_cf_B.sensor_combined_o1 *
                        ekf_cf_B.sensor_combined_o1 +
                        ekf_cf_B.sensor_combined_o2 *
                        ekf_cf_B.sensor_combined_o2) +
                       ekf_cf_B.sensor_combined_o3 * ekf_cf_B.sensor_combined_o3);
  theta_am = (real32_T)asin(ekf_cf_B.sensor_combined_o1 / a21);
  maxval_tmp = 0.1F / (0.1F + rtb_Saturation);
  maxval_tmp_0 = rtb_Saturation / (0.1F + rtb_Saturation);
  maxval = maxval_tmp * (ekf_cf_B.sensor_combined_o5 * rtb_Saturation +
    ekf_cf_DW.Delay1_DSTATE_l) + maxval_tmp_0 * theta_am;
  rtb_Saturation = maxval_tmp * (ekf_cf_B.sensor_combined_o4 * rtb_Saturation +
    ekf_cf_DW.Delay_DSTATE_m) + maxval_tmp_0 * -(real32_T)asin
    (ekf_cf_B.sensor_combined_o2 / (a21 * (real32_T)cos(theta_am)));

  /* SignalConversion: '<S12>/TmpSignal ConversionAt SFunction Inport2' incorporates:
   *  DataTypeConversion: '<S7>/Data Type Conversion6'
   *  MATLAB Function: '<S11>/MATLAB Function1'
   *  MATLAB Function: '<S6>/MATLAB Function'
   *  MATLAB Function: '<S8>/quat2eul'
   */
  rtb_TmpSignalConversionAtSFun_o[0] = rt_atan2f_snf(a_m_idx_1, a_m_idx_2);
  rtb_TmpSignalConversionAtSFun_o[1] = -(real32_T)asin(a_m_idx_0);
  rtb_TmpSignalConversionAtSFun_o[2] = rtb_Saturation;
  rtb_TmpSignalConversionAtSFun_o[3] = maxval;
  rtb_TmpSignalConversionAtSFun_o[4] = rtb_phi;
  rtb_TmpSignalConversionAtSFun_o[5] = theta;
  rtb_TmpSignalConversionAtSFun_o[6] = (real32_T)ekf_cf_B.sensor_combined_o10;

  /* MATLAB Function: '<S11>/MATLAB Function1' incorporates:
   *  Logic: '<S5>/Logical Operator'
   *  Switch: '<S5>/ '
   */
  if ((ekf_cf_B.input_rc > 1600) && rtb_en) {
    if (!ekf_cf_DW.isopen) {
      ekf_cf_DW.elem_size = 4U;
      elem_type = 2U;
      ekf_cf_DW.vect_size = 7U;
      for (r1 = 0; r1 < 56; r1++) {
        ekf_cf_B.c[r1] = c_0[r1];
      }

      for (r1 = 0; r1 < 22; r1++) {
        tmp[r1] = (int8_T)ekf_cf_ConstP.MATLABFunction1_logname[r1];
      }

      tmp[22] = '_';
      if (ekf_cf_DW.lognumstr < 0.0) {
        rtb_px4_att_est_ok_tmp = ceil(ekf_cf_DW.lognumstr);
      } else {
        rtb_px4_att_est_ok_tmp = floor(ekf_cf_DW.lognumstr);
      }

      if (rtIsNaN(rtb_px4_att_est_ok_tmp) || rtIsInf(rtb_px4_att_est_ok_tmp)) {
        rtb_px4_att_est_ok_tmp = 0.0;
      } else {
        rtb_px4_att_est_ok_tmp = fmod(rtb_px4_att_est_ok_tmp, 256.0);
      }

      tmp[23] = (int8_T)(rtb_px4_att_est_ok_tmp < 0.0 ? (int32_T)(int8_T)
                         -(int8_T)(uint8_T)-rtb_px4_att_est_ok_tmp : (int32_T)
                         (int8_T)(uint8_T)rtb_px4_att_est_ok_tmp);
      tmp[24] = '.';
      tmp[25] = 'b';
      tmp[26] = 'i';
      tmp[27] = 'n';
      tmp[28] = '\x00';
      printf(ekf_cf_B.c, tmp, (uint32_T)ekf_cf_DW.vect_size, (uint32_T)
             ekf_cf_DW.elem_size, 60000U, 10U);
      for (r1 = 0; r1 < 22; r1++) {
        tmp[r1] = (int8_T)ekf_cf_ConstP.MATLABFunction1_logname[r1];
      }

      tmp[22] = '_';
      if (ekf_cf_DW.lognumstr < 0.0) {
        rtb_px4_att_est_ok_tmp = ceil(ekf_cf_DW.lognumstr);
      } else {
        rtb_px4_att_est_ok_tmp = floor(ekf_cf_DW.lognumstr);
      }

      if (rtIsNaN(rtb_px4_att_est_ok_tmp) || rtIsInf(rtb_px4_att_est_ok_tmp)) {
        rtb_px4_att_est_ok_tmp = 0.0;
      } else {
        rtb_px4_att_est_ok_tmp = fmod(rtb_px4_att_est_ok_tmp, 256.0);
      }

      tmp[23] = (int8_T)(rtb_px4_att_est_ok_tmp < 0.0 ? (int32_T)(int8_T)
                         -(int8_T)(uint8_T)-rtb_px4_att_est_ok_tmp : (int32_T)
                         (int8_T)(uint8_T)rtb_px4_att_est_ok_tmp);
      tmp[24] = '.';
      tmp[25] = 'b';
      tmp[26] = 'i';
      tmp[27] = 'n';
      tmp[28] = '\x00';
      d[0] = 'w';
      d[1] = 'b';
      d[2] = '\x00';
      ekf_cf_DW.fp = fopen(tmp, d);
      ekf_cf_DW.lognumstr++;
      ekf_cf_DW.isflushed = false;
      ekf_cf_DW.count_g = 0U;
      ekf_cf_DW.isopen = true;
      fwrite(mlStrVer, 1U, 8.0, ekf_cf_DW.fp);
      tm = time(&tmptr);
      fwrite(&tm, 4U, 1U, ekf_cf_DW.fp);
      fwrite(&ekf_cf_DW.vect_size, 1U, 1U, ekf_cf_DW.fp);
      fwrite(&elem_type, 1U, 1U, ekf_cf_DW.fp);
      tmptr = (uint32_T)ekf_cf_DW.elem_size * ekf_cf_DW.vect_size;
      if (tmptr > 65535U) {
        tmptr = 65535U;
      }

      recSize = (uint16_T)tmptr;
      fwrite(&recSize, 2U, 1U, ekf_cf_DW.fp);
    }

    if (rtb_px4_att_est_ok) {
      fwrite(rtb_TmpSignalConversionAtSFun_o, ekf_cf_DW.elem_size,
             ekf_cf_DW.vect_size, ekf_cf_DW.fp);
      tmptr = ekf_cf_DW.count_g + /*MW:OvSatOk*/ 1U;
      if (tmptr < ekf_cf_DW.count_g) {
        tmptr = MAX_uint32_T;
      }

      ekf_cf_DW.count_g = tmptr;
    }

    if (ekf_cf_DW.count_g >= 60000U) {
      fflush(ekf_cf_DW.fp);
      ekf_cf_DW.isflushed = false;
      ekf_cf_DW.count_g = 0U;
    }
  } else {
    if (ekf_cf_DW.isopen) {
      if (!ekf_cf_DW.isflushed) {
        for (r1 = 0; r1 < 28; r1++) {
          b_1[r1] = b_0[r1];
        }

        printf(b_1, ekf_cf_DW.count_g, 10U);
        fflush(ekf_cf_DW.fp);
        ekf_cf_DW.isflushed = true;
      }

      fclose(ekf_cf_DW.fp);
    }

    ekf_cf_DW.isopen = false;
    ekf_cf_DW.count_g = 0U;
  }

  /* Update for Delay: '<S3>/Delay2' incorporates:
   *  DataTypeConversion: '<S7>/Data Type Conversion6'
   */
  ekf_cf_DW.Delay2_DSTATE = (real32_T)ekf_cf_B.sensor_combined_o10;
  for (r3 = 0; r3 < 6; r3++) {
    /* Update for Delay: '<S6>/Delay' */
    ekf_cf_DW.Delay_DSTATE[r3] = rtb_TmpSignalConversionAtSFunct[r3];

    /* MATLAB Function: '<S6>/MATLAB Function' */
    for (r1 = 0; r1 < 6; r1++) {
      ekf_cf_B.PHI_k[r3 + 6 * r1] = (real32_T)ekf_cf_B.b_I[6 * r1 + r3] -
        ((ekf_cf_B.H_k[3 * r1 + 1] * ekf_cf_B.K_k[r3 + 6] + ekf_cf_B.H_k[3 * r1]
          * ekf_cf_B.K_k[r3]) + ekf_cf_B.H_k[3 * r1 + 2] * ekf_cf_B.K_k[r3 + 12]);
    }

    /* Update for Delay: '<S6>/Delay1' incorporates:
     *  MATLAB Function: '<S6>/MATLAB Function'
     */
    for (r1 = 0; r1 < 6; r1++) {
      /* MATLAB Function: '<S6>/MATLAB Function' */
      rtemp = r3 + 6 * r1;
      ekf_cf_DW.Delay1_DSTATE[rtemp] = 0.0F;
      for (r2 = 0; r2 < 6; r2++) {
        ekf_cf_DW.Delay1_DSTATE[rtemp] = ekf_cf_B.PHI_k[6 * r2 + r3] *
          ekf_cf_B.PHI[6 * r1 + r2] + ekf_cf_DW.Delay1_DSTATE[6 * r1 + r3];
      }
    }

    /* End of Update for Delay: '<S6>/Delay1' */
  }

  /* Update for Delay: '<S4>/Delay' */
  ekf_cf_DW.Delay_DSTATE_m = rtb_Saturation;

  /* Update for Delay: '<S4>/Delay1' */
  ekf_cf_DW.Delay1_DSTATE_l = maxval;
}

/* Model step wrapper function for compatibility with a static main program */
void ekf_cf_step(int_T tid)
{
  switch (tid) {
   case 0 :
    ekf_cf_step0();
    break;

   case 1 :
    ekf_cf_step1();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void ekf_cf_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ekf_cf_M, 0,
                sizeof(RT_MODEL_ekf_cf_T));

  /* block I/O */
  (void) memset(((void *) &ekf_cf_B), 0,
                sizeof(B_ekf_cf_T));

  {
    ekf_cf_B.Switch1 = SL_COLOR_OFF;
  }

  /* states (dwork) */
  (void) memset((void *)&ekf_cf_DW, 0,
                sizeof(DW_ekf_cf_T));

  /* Start for S-Function (sfun_px4_vehicle_attitude): '<S8>/vehicle_attitude'
   *
   * Block description for '<S8>/vehicle_attitude':
   *  This block gives access to the running service that calculates the vehicle＊s attitude.  A uORB topic (vehicle_attitude (attitude measurements)) publisher MUST be running in order for this block to provide valid signal values.  The available ones as of v1.3 are:
   *  attitude_estimator_ekf 每 EKF-Extended Kalman Filter for attitude estimation
   *  attitude_estimator_so3 每 SO(3)-attitude estimation by using accelerometer, gyroscopes and magnetometer
   *  One of these MUST be running on the px4fmu in order for this block to return valid values.  Refer to the sample model: px4demo_attitude_control.slx. Attitude in NED (North-East-Down) body frame in SI units.
   *  Signal definitions:
   *  Roll 每 single value, Roll angle (rad, Tait-Bryan, NED)
   *  Pitch 每 single value, Pitch angle (rad, Tait-Bryan, NED)
   *  Yaw 每 single value, Yaw angle (rad, Tait-Bryan, NED)
   *  Quaternion (NED) 每 single(4) values (optional based on the uORB publisher)
   *
   */
  {
    /* S-Function Block: <S8>/vehicle_attitude */
    /* subscribe to PWM RC input topic */
    int fd = orb_subscribe(ORB_ID(vehicle_attitude));
    ekf_cf_DW.vehicle_attitude_vehicle_attitu.fd = fd;
    ekf_cf_DW.vehicle_attitude_vehicle_attitu.events = POLLIN;
    orb_set_interval(fd, 1);
    PX4_INFO("* Subscribed to vehicle_attitude topic (fd = %d)*\n", fd);
  }

  /* Start for S-Function (sfun_px4_rgbled): '<Root>/RGB_LED1' incorporates:
   *  Constant: '<Root>/Constant4'
   *
   * Block description for '<Root>/RGB_LED1':
   *  This block gives the user control over various lighting modes of the RGB LED available on the PX4 hardware.
   *  This block accepts 2 inputs: Mode and Color.  These are enumeration data types.  You can find out what values are valid in the MATLAB command window by typing:
   *  Enumeration members for class 'RGBLED_COLOR_ENUM':
   *      SL_COLOR_OFF
   *      SL_COLOR_RED
   *      SL_COLOR_GREEN
   *      SL_COLOR_BLUE
   *      SL_COLOR_YELLOW
   *      SL_COLOR_PURPLE
   *      SL_COLOR_AMBER
   *      SL_COLOR_CYAN
   *      SL_COLOR_WHITE
   *  Enumeration members for class 'RGBLED_MODE_ENUM':
   *      SL_MODE_OFF
   *      SL_MODE_ON
   *      SL_MODE_DISABLED
   *      SL_MODE_BLINK_SLOW
   *      SL_MODE_BLINK_NORMAL
   *      SL_MODE_BLINK_FAST
   *      SL_MODE_BREATHE
   *  Look at the sample Simulink model: px4demo_rgbled.slx for an example of how to use this block.
   */
  {
    // enable RGBLED, set intitial mode and color
    // more devices will be 1, 2, etc
    ekf_cf_DW.RGB_LED1_sl_led_control_s.led_mask = 0xff;
    ekf_cf_DW.RGB_LED1_sl_led_control_s.mode = MODE_OFF;
    ekf_cf_DW.RGB_LED1_sl_led_control_s.priority = 0;
    ekf_cf_DW.RGB_LED1_sl_led_control_s.timestamp = hrt_absolute_time();
    ekf_cf_DW.RGB_LED1_orb_advert_t = orb_advertise_queue(ORB_ID(led_control),
      &ekf_cf_DW.RGB_LED1_sl_led_control_s, LED_UORB_QUEUE_LENGTH);
  }

  /* Start for S-Function (sfun_px4_input_rc): '<Root>/input_rc'
   *
   * Block description for '<Root>/input_rc':
   *  RC Input Block
   *
   *  This block provides user input control to the model.
   *  It uses the input_rc uORB topic.
   *
   *  The user has the ability to choose which channels are available as outputs from this block and also some optional outputs. These include
   *  Channels 1 through 18
   *  double data type indicating the PWM value from the controller
   *  measured pulse widths for each of the supported channels
   *  Channel Count
   *  uint32 data type of the number of channels which are detector by the PX4
   *  RC Failsafe
   *  boolean data types indicating that the RC Tx is sending the FailSafe signal (if equipped and properly setup)
   *  explicit failsafe flag: true on TX failure or TX out of range , false otherwise.
   *  Only the true state is reliable, as there are some (PPM) receivers on the market going into failsafe without telling us explicitly.
   *  RC Input Source
   *  Enumeration data type indicating which source the RC input is from.
   *  Valid values are found in the ENUM file: RC_INPUT_SOURCE_ENUM.m
   *            Enumeration members for class 'RC_INPUT_SOURCE_ENUM':
   *            RCINPUT_SOURCE_UNKNOWN         (0)
   *            RCINPUT_SOURCE_PX4FMU_PPM      (1)
   *            RCINPUT_SOURCE_PX4IO_PPM       (2)
   *            RCINPUT_SOURCE_PX4IO_SPEKTRUM  (3)
   *            RCINPUT_SOURCE_PX4IO_SBUS      (4)
   *            RCINPUT_SOURCE_PX4IO_ST24      (5)
   *            RCINPUT_SOURCE_MAVLINK         (6)
   *            RCINPUT_SOURCE_QURT            (7)
   *            RCINPUT_SOURCE_PX4FMU_SPEKTRUM (8)
   *            RCINPUT_SOURCE_PX4FMU_SBUS     (9)
   *            RCINPUT_SOURCE_PX4FMU_ST24     (10)
   *            RCINPUT_SOURCE_PX4FMU_SUMD     (11)
   *            RCINPUT_SOURCE_PX4FMU_DSM      (12)
   *            RCINPUT_SOURCE_PX4IO_SUMD      (13)
   *
   *  RSSI - Receive signal strength index
   *  receive signal strength indicator (RSSI): < 0: Undefined, 0: no signal, 255: full reception
   *  RC Lost Connection
   *  boolean data type indicating RC receiver connection status
   *  True, if no frame has arrived in the expected time, false otherwise.
   *  True usally means that the receiver has been disconnected, but can also indicate a radio link loss on "stupid" systems.
   *  Will remain false, if a RX with failsafe option continues to transmit frames after a link loss.
   *
   *  Sample Model: px4demo_input_rc.slx
   */
  {
    /* S-Function Block: <Root>/input_rc */
    /* subscribe to PWM RC input topic */
    int fd = orb_subscribe(ORB_ID(input_rc));
    ekf_cf_DW.input_rc_input_rc_fd.fd = fd;
    ekf_cf_DW.input_rc_input_rc_fd.events = POLLIN;
    orb_set_interval(fd, 1);
    PX4_INFO("* Subscribed to input_rc topic (fd = %d)*\n", fd);
  }

  /* Start for S-Function (sfun_px4_sensor_combined): '<S7>/sensor_combined'
   *
   * Block description for '<S7>/sensor_combined':
   *  Sensor Combined Block
   *
   *  This block enables access to the various sensors available on the px4fmu-v2 hardware.
   *  The user can use these signals in the Simulink control model.
   *  The sample time needs to be provided in the mask dialog.
   *  Optional output ports can also be selected.
   *  Refer to the sample model: px4demo_attitude_control.slx
   *
   *  Signal definitions:
   *  Magnetometer (x,y,z) - single values 每 Magnetic field in NED body frame, in Gauss
   *  Accelerometer (x,y,z) - single values 每 Acceleration in NED body frame, in m/s^2
   *  Gyroscope (p,q,r) - single values 每 Angular velocity in radians per second
   *  Barometer (Altitude) - single value 每 Barometric pressure, already temperature compensated (millibars)
   *  RunTime (timestamp) - double value 每 Timestamp in microseconds since boot, from gyro
   *
   *  The sensor_combined block needs to have the px4io service running on the PX4 hardware in order to get valid signal values.

   */
  {
    /* S-Function Block: <S7>/sensor_combined */
    /* subscribe to sensor_combined topic */
    int fd = orb_subscribe(ORB_ID(sensor_combined));
    ekf_cf_DW.sensor_combined_sensor_fd.fd = fd;
    ekf_cf_DW.sensor_combined_sensor_fd.events = POLLIN;
    orb_set_interval(fd, 1);
    PX4_INFO("* Subscribed to sensor_combined topic (fd = %d)*\n", fd);
  }

  /* SystemInitialize for MATLAB Function: '<S5>/MATLAB Function' */
  ekf_cf_DW.count = 0.0;

  /* SystemInitialize for MATLAB Function: '<S11>/MATLAB Function1' */
  ekf_cf_DW.count_g = 0U;
  ekf_cf_DW.lognumstr = 65.0;
  ekf_cf_DW.isopen = false;
  ekf_cf_DW.fp = NULL;
  ekf_cf_DW.isflushed = false;
  ekf_cf_DW.elem_size = 1U;
  ekf_cf_DW.vect_size = 7U;
}

/* Model terminate function */
void ekf_cf_terminate(void)
{
  /* Terminate for S-Function (sfun_px4_vehicle_attitude): '<S8>/vehicle_attitude'
   *
   * Block description for '<S8>/vehicle_attitude':
   *  This block gives access to the running service that calculates the vehicle＊s attitude.  A uORB topic (vehicle_attitude (attitude measurements)) publisher MUST be running in order for this block to provide valid signal values.  The available ones as of v1.3 are:
   *  attitude_estimator_ekf 每 EKF-Extended Kalman Filter for attitude estimation
   *  attitude_estimator_so3 每 SO(3)-attitude estimation by using accelerometer, gyroscopes and magnetometer
   *  One of these MUST be running on the px4fmu in order for this block to return valid values.  Refer to the sample model: px4demo_attitude_control.slx. Attitude in NED (North-East-Down) body frame in SI units.
   *  Signal definitions:
   *  Roll 每 single value, Roll angle (rad, Tait-Bryan, NED)
   *  Pitch 每 single value, Pitch angle (rad, Tait-Bryan, NED)
   *  Yaw 每 single value, Yaw angle (rad, Tait-Bryan, NED)
   *  Quaternion (NED) 每 single(4) values (optional based on the uORB publisher)
   *
   */

  /* Close uORB service used in the S-Function Block: <S8>/vehicle_attitude */
  close(ekf_cf_DW.vehicle_attitude_vehicle_attitu.fd);

  /* Terminate for S-Function (sfun_px4_rgbled): '<Root>/RGB_LED1' incorporates:
   *  Constant: '<Root>/Constant4'
   *
   * Block description for '<Root>/RGB_LED1':
   *  This block gives the user control over various lighting modes of the RGB LED available on the PX4 hardware.
   *  This block accepts 2 inputs: Mode and Color.  These are enumeration data types.  You can find out what values are valid in the MATLAB command window by typing:
   *  Enumeration members for class 'RGBLED_COLOR_ENUM':
   *      SL_COLOR_OFF
   *      SL_COLOR_RED
   *      SL_COLOR_GREEN
   *      SL_COLOR_BLUE
   *      SL_COLOR_YELLOW
   *      SL_COLOR_PURPLE
   *      SL_COLOR_AMBER
   *      SL_COLOR_CYAN
   *      SL_COLOR_WHITE
   *  Enumeration members for class 'RGBLED_MODE_ENUM':
   *      SL_MODE_OFF
   *      SL_MODE_ON
   *      SL_MODE_DISABLED
   *      SL_MODE_BLINK_SLOW
   *      SL_MODE_BLINK_NORMAL
   *      SL_MODE_BLINK_FAST
   *      SL_MODE_BREATHE
   *  Look at the sample Simulink model: px4demo_rgbled.slx for an example of how to use this block.
   */

  /* Turn off LED */
  ekf_cf_DW.RGB_LED1_sl_led_control_s.led_mask = 0xff;
  ekf_cf_DW.RGB_LED1_sl_led_control_s.mode = MODE_OFF;
  ekf_cf_DW.RGB_LED1_sl_led_control_s.priority = 0;
  ekf_cf_DW.RGB_LED1_sl_led_control_s.timestamp = hrt_absolute_time();
  ekf_cf_DW.RGB_LED1_orb_advert_t = orb_advertise_queue(ORB_ID(led_control),
    &ekf_cf_DW.RGB_LED1_sl_led_control_s, LED_UORB_QUEUE_LENGTH);

  /* Close uORB service used in the S-Function Block: <Root>/RGB_LED1 */
  orb_unadvertise(ekf_cf_DW.RGB_LED1_orb_advert_t);

  /* Terminate for S-Function (sfun_px4_input_rc): '<Root>/input_rc'
   *
   * Block description for '<Root>/input_rc':
   *  RC Input Block
   *
   *  This block provides user input control to the model.
   *  It uses the input_rc uORB topic.
   *
   *  The user has the ability to choose which channels are available as outputs from this block and also some optional outputs. These include
   *  Channels 1 through 18
   *  double data type indicating the PWM value from the controller
   *  measured pulse widths for each of the supported channels
   *  Channel Count
   *  uint32 data type of the number of channels which are detector by the PX4
   *  RC Failsafe
   *  boolean data types indicating that the RC Tx is sending the FailSafe signal (if equipped and properly setup)
   *  explicit failsafe flag: true on TX failure or TX out of range , false otherwise.
   *  Only the true state is reliable, as there are some (PPM) receivers on the market going into failsafe without telling us explicitly.
   *  RC Input Source
   *  Enumeration data type indicating which source the RC input is from.
   *  Valid values are found in the ENUM file: RC_INPUT_SOURCE_ENUM.m
   *            Enumeration members for class 'RC_INPUT_SOURCE_ENUM':
   *            RCINPUT_SOURCE_UNKNOWN         (0)
   *            RCINPUT_SOURCE_PX4FMU_PPM      (1)
   *            RCINPUT_SOURCE_PX4IO_PPM       (2)
   *            RCINPUT_SOURCE_PX4IO_SPEKTRUM  (3)
   *            RCINPUT_SOURCE_PX4IO_SBUS      (4)
   *            RCINPUT_SOURCE_PX4IO_ST24      (5)
   *            RCINPUT_SOURCE_MAVLINK         (6)
   *            RCINPUT_SOURCE_QURT            (7)
   *            RCINPUT_SOURCE_PX4FMU_SPEKTRUM (8)
   *            RCINPUT_SOURCE_PX4FMU_SBUS     (9)
   *            RCINPUT_SOURCE_PX4FMU_ST24     (10)
   *            RCINPUT_SOURCE_PX4FMU_SUMD     (11)
   *            RCINPUT_SOURCE_PX4FMU_DSM      (12)
   *            RCINPUT_SOURCE_PX4IO_SUMD      (13)
   *
   *  RSSI - Receive signal strength index
   *  receive signal strength indicator (RSSI): < 0: Undefined, 0: no signal, 255: full reception
   *  RC Lost Connection
   *  boolean data type indicating RC receiver connection status
   *  True, if no frame has arrived in the expected time, false otherwise.
   *  True usally means that the receiver has been disconnected, but can also indicate a radio link loss on "stupid" systems.
   *  Will remain false, if a RX with failsafe option continues to transmit frames after a link loss.
   *
   *  Sample Model: px4demo_input_rc.slx
   */

  /* Close uORB service used in the S-Function Block: <Root>/input_rc */
  close(ekf_cf_DW.input_rc_input_rc_fd.fd);

  /* Terminate for S-Function (sfun_px4_sensor_combined): '<S7>/sensor_combined'
   *
   * Block description for '<S7>/sensor_combined':
   *  Sensor Combined Block
   *
   *  This block enables access to the various sensors available on the px4fmu-v2 hardware.
   *  The user can use these signals in the Simulink control model.
   *  The sample time needs to be provided in the mask dialog.
   *  Optional output ports can also be selected.
   *  Refer to the sample model: px4demo_attitude_control.slx
   *
   *  Signal definitions:
   *  Magnetometer (x,y,z) - single values 每 Magnetic field in NED body frame, in Gauss
   *  Accelerometer (x,y,z) - single values 每 Acceleration in NED body frame, in m/s^2
   *  Gyroscope (p,q,r) - single values 每 Angular velocity in radians per second
   *  Barometer (Altitude) - single value 每 Barometric pressure, already temperature compensated (millibars)
   *  RunTime (timestamp) - double value 每 Timestamp in microseconds since boot, from gyro
   *
   *  The sensor_combined block needs to have the px4io service running on the PX4 hardware in order to get valid signal values.

   */

  /* Close uORB service used in the S-Function Block: <S7>/sensor_combined */
  close(ekf_cf_DW.sensor_combined_sensor_fd.fd);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
