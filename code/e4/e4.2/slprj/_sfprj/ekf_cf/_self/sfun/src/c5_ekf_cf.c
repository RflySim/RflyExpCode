/* Include files */

#include "ekf_cf_sfun.h"
#include "c5_ekf_cf.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ekf_cf_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c5_debug_family_names[23] = { "elsize", "eltype",
  "elem_type", "mlStrVer", "tm", "tmptr", "recSize", "addr", "idx", "nargin",
  "nargout", "en", "data", "datalog_flag", "logname", "cacheflag", "numRecs",
  "isflushed", "isopen", "count", "lognumstr", "elem_size", "vect_size" };

static const char * c5_b_debug_family_names[4] = { "dtype", "elem_size",
  "nargin", "nargout" };

static const char_T c5_cv0[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o',
  'l', 'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
  '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

/* Function Declarations */
static void initialize_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void initialize_params_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void enable_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void disable_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_ekf_cf(SFc5_ekf_cfInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c5_ekf_cf(SFc5_ekf_cfInstanceStruct
  *chartInstance);
static void set_sim_state_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_st);
static void finalize_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void sf_gateway_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void mdl_start_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void c5_chartstep_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void initSimStructsc5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static uint8_T c5_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_vect_size, const char_T *c5_identifier, boolean_T
  *c5_svPtr);
static uint8_T c5_b_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint16_T c5_c_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_elem_size, const char_T *c5_identifier, boolean_T
  *c5_svPtr);
static uint16_T c5_d_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_e_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_lognumstr, const char_T *c5_identifier, boolean_T
  *c5_svPtr);
static real_T c5_f_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint32_T c5_g_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_count, const char_T *c5_identifier, boolean_T *c5_svPtr);
static uint32_T c5_h_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static boolean_T c5_i_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_isopen, const char_T *c5_identifier, boolean_T *c5_svPtr);
static boolean_T c5_j_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr);
static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint32_T c5_k_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static boolean_T c5_l_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_m_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, uint8_T c5_y[22]);
static void c5_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_i_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_j_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_n_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_k_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint8_T c5_o_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_idx, const char_T *c5_identifier);
static uint8_T c5_p_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_l_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint16_T c5_q_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_m_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_r_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, char_T c5_y[8]);
static void c5_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_check_forloop_overflow_error(SFc5_ekf_cfInstanceStruct
  *chartInstance, boolean_T c5_overflow);
static void c5_b_check_forloop_overflow_error(SFc5_ekf_cfInstanceStruct
  *chartInstance, boolean_T c5_overflow);
static const mxArray *c5_n_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_s_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static int8_T c5__s8_u8_(SFc5_ekf_cfInstanceStruct *chartInstance, uint8_T c5_b,
  uint32_T c5_ssid_src_loc, int32_T c5_offset_src_loc, int32_T c5_length_src_loc);
static void init_dsm_address_info(SFc5_ekf_cfInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc5_ekf_cfInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc5_ekf_cf(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_fp_not_empty = false;
  chartInstance->c5_isflushed_not_empty = false;
  chartInstance->c5_isopen_not_empty = false;
  chartInstance->c5_count_not_empty = false;
  chartInstance->c5_lognumstr_not_empty = false;
  chartInstance->c5_elem_size_not_empty = false;
  chartInstance->c5_vect_size_not_empty = false;
  chartInstance->c5_is_active_c5_ekf_cf = 0U;
}

static void initialize_params_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  real_T c5_dv0[22];
  int32_T c5_i0;
  real_T c5_d0;
  real_T c5_d1;
  sf_mex_import_named("logname", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      c5_dv0, 0, 0, 0U, 1, 0U, 2, 1, 22);
  for (c5_i0 = 0; c5_i0 < 22; c5_i0++) {
    chartInstance->c5_logname[c5_i0] = (uint8_T)c5_dv0[c5_i0];
  }

  sf_mex_import_named("cacheflag", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c5_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c5_cacheflag = (c5_d0 != 0.0);
  sf_mex_import_named("numRecs", sf_mex_get_sfun_param(chartInstance->S, 2, 0),
                      &c5_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c5_numRecs = (uint32_T)c5_d1;
}

static void enable_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_ekf_cf(SFc5_ekf_cfInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c5_ekf_cf(SFc5_ekf_cfInstanceStruct
  *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  uint32_T c5_hoistedGlobal;
  const mxArray *c5_b_y = NULL;
  uint16_T c5_b_hoistedGlobal;
  const mxArray *c5_c_y = NULL;
  boolean_T c5_c_hoistedGlobal;
  const mxArray *c5_d_y = NULL;
  boolean_T c5_d_hoistedGlobal;
  const mxArray *c5_e_y = NULL;
  real_T c5_e_hoistedGlobal;
  const mxArray *c5_f_y = NULL;
  uint8_T c5_f_hoistedGlobal;
  const mxArray *c5_g_y = NULL;
  uint8_T c5_g_hoistedGlobal;
  const mxArray *c5_h_y = NULL;
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(7, 1), false);
  c5_hoistedGlobal = chartInstance->c5_count;
  c5_b_y = NULL;
  if (!chartInstance->c5_count_not_empty) {
    sf_mex_assign(&c5_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_hoistedGlobal, 7, 0U, 0U, 0U,
      0), false);
  }

  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = chartInstance->c5_elem_size;
  c5_c_y = NULL;
  if (!chartInstance->c5_elem_size_not_empty) {
    sf_mex_assign(&c5_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_hoistedGlobal, 5, 0U, 0U, 0U,
      0), false);
  }

  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_c_hoistedGlobal = chartInstance->c5_isflushed;
  c5_d_y = NULL;
  if (!chartInstance->c5_isopen_not_empty) {
    sf_mex_assign(&c5_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_hoistedGlobal, 11, 0U, 0U,
      0U, 0), false);
  }

  sf_mex_setcell(c5_y, 2, c5_d_y);
  c5_d_hoistedGlobal = chartInstance->c5_isopen;
  c5_e_y = NULL;
  if (!chartInstance->c5_isopen_not_empty) {
    sf_mex_assign(&c5_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_d_hoistedGlobal, 11, 0U, 0U,
      0U, 0), false);
  }

  sf_mex_setcell(c5_y, 3, c5_e_y);
  c5_e_hoistedGlobal = chartInstance->c5_lognumstr;
  c5_f_y = NULL;
  if (!chartInstance->c5_lognumstr_not_empty) {
    sf_mex_assign(&c5_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_e_hoistedGlobal, 0, 0U, 0U, 0U,
      0), false);
  }

  sf_mex_setcell(c5_y, 4, c5_f_y);
  c5_f_hoistedGlobal = chartInstance->c5_vect_size;
  c5_g_y = NULL;
  if (!chartInstance->c5_vect_size_not_empty) {
    sf_mex_assign(&c5_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_f_hoistedGlobal, 3, 0U, 0U, 0U,
      0), false);
  }

  sf_mex_setcell(c5_y, 5, c5_g_y);
  c5_g_hoistedGlobal = chartInstance->c5_is_active_c5_ekf_cf;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_g_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c5_y, 6, c5_h_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_st)
{
  const mxArray *c5_u;
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  chartInstance->c5_count = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 0)), "count", &chartInstance->c5_count_not_empty);
  chartInstance->c5_elem_size = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 1)), "elem_size",
    &chartInstance->c5_elem_size_not_empty);
  chartInstance->c5_isflushed = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 2)), "isflushed",
    &chartInstance->c5_isflushed_not_empty);
  chartInstance->c5_isopen = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 3)), "isopen", &chartInstance->c5_isopen_not_empty);
  chartInstance->c5_lognumstr = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 4)), "lognumstr",
    &chartInstance->c5_lognumstr_not_empty);
  chartInstance->c5_vect_size = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 5)), "vect_size",
    &chartInstance->c5_vect_size_not_empty);
  chartInstance->c5_is_active_c5_ekf_cf = c5_o_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 6)), "is_active_c5_ekf_cf");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_ekf_cf(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  int32_T c5_i1;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c5_datalog_flag, 2U);
  for (c5_i1 = 0; c5_i1 < 7; c5_i1++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c5_data)[c5_i1], 1U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c5_en, 0U);
  chartInstance->c5_sfEvent = CALL_EVENT;
  c5_chartstep_c5_ekf_cf(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ekf_cfMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void c5_chartstep_c5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  boolean_T c5_b_en;
  int32_T c5_i2;
  boolean_T c5_b_datalog_flag;
  real32_T c5_b_data[7];
  int32_T c5_i3;
  boolean_T c5_b_cacheflag;
  uint8_T c5_b_logname[22];
  uint32_T c5_b_numRecs;
  uint32_T c5_debug_family_var_map[23];
  uint16_T c5_elsize;
  uint8_T c5_eltype;
  uint8_T c5_elem_type;
  char_T c5_mlStrVer[8];
  uint32_T c5_tm;
  uint32_T c5_tmptr;
  uint16_T c5_recSize;
  uint32_T c5_addr;
  uint32_T c5_idx;
  uint8_T c5_b_idx;
  real_T c5_nargin = 6.0;
  real_T c5_nargout = 0.0;
  uint32_T c5_b_debug_family_var_map[4];
  uint8_T c5_dtype;
  int32_T c5_i4;
  uint16_T c5_b_elem_size;
  uint64_T c5_u0;
  real_T c5_c_elem_size;
  real_T c5_b_dtype;
  char_T c5_cv1[28];
  static char_T c5_cv2[28] = { 'C', 'L', 'O', 'S', 'I', 'N', 'G', ' ', 'f', 'i',
    'l', 'e', '.', ' ', 'c', 'o', 'u', 'n', 't', ' ', '=', ' ', '%', 'd', ' ',
    '%', 'c', '\x00' };

  real_T c5_b_nargin = 1.0;
  uint32_T c5_q0;
  real_T c5_b_nargout = 2.0;
  uint32_T c5_b_q0;
  uint32_T c5_qY;
  uint32_T c5_b_qY;
  uint32_T c5_c_q0;
  uint32_T c5_c_qY;
  uint64_T c5_u1;
  uint8_T c5_b_vect_size;
  boolean_T c5_overflow;
  uint32_T c5_b;
  uint64_T c5_u2;
  boolean_T c5_b_overflow;
  uint32_T c5_b_b;
  uint8_T c5_c_idx;
  boolean_T c5_c_overflow;
  uint32_T c5_d_idx;
  uint32_T c5_d_q0;
  uint32_T c5_e_idx;
  uint32_T c5_d_qY;
  uint32_T c5_e_q0;
  uint32_T c5_e_qY;
  int32_T c5_i5;
  real_T c5_hoistedGlobal;
  uint8_T c5_x[22];
  boolean_T c5_b0;
  const mxArray *c5_y = NULL;
  static char_T c5_cv3[44] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'O', 'u', 't', 'O', 'f', 'T', 'a', 'r', 'g', 'e', 't',
    'R', 'a', 'n', 'g', 'e', 'T', 'r', 'u', 'n', 'c', 'a', 't', 'e', 'd', 'F',
    'l', 'o', 'a', 't' };

  int32_T c5_i6;
  real_T c5_u;
  const mxArray *c5_b_y = NULL;
  int32_T c5_i7;
  char_T c5_cv4[56];
  static char_T c5_cv5[56] = { 'O', 'P', 'E', 'N', 'I', 'N', 'G', ' ', 'f', 'i',
    'l', 'e', ' ', '%', 's', ' ', 'v', 'e', 'c', 't', '_', 's', 'i', 'z', 'e',
    ' ', '%', 'd', ' ', 'e', 'l', 'e', 'm', '_', 's', 'i', 'z', 'e', ' ', '%',
    'd', ' ', 'n', 'u', 'm', 'R', 'e', 'c', 's', ' ', '%', 'd', ' ', '%', 'c',
    '\x00' };

  real_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  char_T c5_b_x[29];
  real_T c5_c_u;
  real_T c5_d2;
  real_T c5_d3;
  int32_T c5_i8;
  static char_T c5_cv6[4] = { '.', 'b', 'i', 'n' };

  int32_T c5_i9;
  real_T c5_b_hoistedGlobal;
  boolean_T c5_b1;
  const mxArray *c5_d_y = NULL;
  static char_T c5_cv7[44] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'O', 'u', 't', 'O', 'f', 'T', 'a', 'r', 'g', 'e', 't',
    'R', 'a', 'n', 'g', 'e', 'T', 'r', 'u', 'n', 'c', 'a', 't', 'e', 'd', 'F',
    'l', 'o', 'a', 't' };

  int32_T c5_i10;
  real_T c5_d_u;
  const mxArray *c5_e_y = NULL;
  char_T c5_c_x[29];
  real_T c5_e_u;
  real_T c5_f_u;
  const mxArray *c5_f_y = NULL;
  real_T c5_d4;
  real_T c5_d5;
  int32_T c5_i11;
  int32_T c5_i12;
  char_T c5_cv8[3];
  static char_T c5_cv9[3] = { 'w', 'b', '\x00' };

  int32_T c5_i13;
  static char_T c5_cv10[8] = { 'M', 'W', 'L', 'O', 'G', 'V', '0', '1' };

  uint32_T c5_u3;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  c5_b_en = *chartInstance->c5_en;
  for (c5_i2 = 0; c5_i2 < 7; c5_i2++) {
    c5_b_data[c5_i2] = (*chartInstance->c5_data)[c5_i2];
  }

  c5_b_datalog_flag = *chartInstance->c5_datalog_flag;
  for (c5_i3 = 0; c5_i3 < 22; c5_i3++) {
    c5_b_logname[c5_i3] = chartInstance->c5_logname[c5_i3];
  }

  c5_b_cacheflag = chartInstance->c5_cacheflag;
  c5_b_numRecs = chartInstance->c5_numRecs;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 23U, 24U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_elsize, 0U, c5_l_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_eltype, 1U, c5_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_elem_type, 2U, c5_k_sf_marshallOut,
    c5_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_mlStrVer, 3U, c5_m_sf_marshallOut,
    c5_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_tm, 4U, c5_f_sf_marshallOut,
    c5_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_tmptr, 5U, c5_f_sf_marshallOut,
    c5_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_recSize, 6U, c5_l_sf_marshallOut,
    c5_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_addr, 7U, c5_f_sf_marshallOut,
    c5_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_idx, MAX_uint32_T,
    c5_f_sf_marshallOut, c5_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_idx, MAX_uint32_T,
    c5_k_sf_marshallOut, c5_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 9U, c5_j_sf_marshallOut,
    c5_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 10U, c5_j_sf_marshallOut,
    c5_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_en, 11U, c5_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_b_data, 12U, c5_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_datalog_flag, 13U, c5_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_b_logname, 14U, c5_h_sf_marshallOut,
    c5_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_cacheflag, 15U, c5_g_sf_marshallOut,
    c5_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_numRecs, 16U, c5_f_sf_marshallOut,
    c5_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_isflushed, 17U,
    c5_e_sf_marshallOut, c5_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_isopen, 18U,
    c5_e_sf_marshallOut, c5_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_count, 19U,
    c5_d_sf_marshallOut, c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_lognumstr, 20U,
    c5_c_sf_marshallOut, c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_elem_size, 21U,
    c5_b_sf_marshallOut, c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_vect_size, 22U,
    c5_sf_marshallOut, c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 15);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 16);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 17);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 19);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c5_count_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 20);
    chartInstance->c5_count = 0U;
    chartInstance->c5_count_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 21);
    chartInstance->c5_lognumstr = 65.0;
    chartInstance->c5_lognumstr_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 22);
    chartInstance->c5_isopen = false;
    chartInstance->c5_isopen_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 23);
    chartInstance->c5_fp = NULL;
    chartInstance->c5_fp_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 24);
    chartInstance->c5_isflushed = false;
    chartInstance->c5_isflushed_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 25);
    chartInstance->c5_elem_size = 1U;
    chartInstance->c5_elem_size_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 26);
    chartInstance->c5_vect_size = 7U;
    chartInstance->c5_vect_size_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 27);
    CV_EML_IF(0, 1, 1, c5_b_cacheflag);
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 32);
  if (CV_EML_IF(0, 1, 2, c5_b_en)) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 33);
    if (CV_EML_IF(0, 1, 3, !chartInstance->c5_isopen)) {
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 34);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 6U, c5_b_debug_family_names,
        c5_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_dtype, MAX_uint32_T,
        c5_k_sf_marshallOut, c5_j_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_elem_size, MAX_uint32_T,
        c5_l_sf_marshallOut, c5_k_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML(&c5_c_elem_size, MAX_uint32_T,
        c5_j_sf_marshallOut);
      _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_dtype, MAX_uint32_T, c5_j_sf_marshallOut);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargin, 2U, c5_j_sf_marshallOut,
        c5_i_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargout, 3U,
        c5_j_sf_marshallOut, c5_i_sf_marshallIn);
      CV_EML_FCN(0, 1);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 110);
      CV_EML_SWITCH(0, 1, 0, 2);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 115);
      c5_c_elem_size = 4.0;
      _SFD_SYMBOL_SWITCH(1U, 2U);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 116);
      c5_b_dtype = 2.0;
      _SFD_SYMBOL_SWITCH(0U, 3U);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 143U);
      CV_EML_COND(0, 1, 1, true);
      CV_EML_MCDC(0, 1, 1, false);
      CV_EML_IF(0, 1, 11, false);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 147U);
      c5_b_elem_size = 4U;
      _SFD_SYMBOL_SWITCH(1U, 1U);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 148U);
      c5_dtype = 2U;
      _SFD_SYMBOL_SWITCH(0U, 0U);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -148);
      _SFD_SYMBOL_SCOPE_POP();
      c5_elsize = 4U;
      c5_eltype = 2U;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 35);
      chartInstance->c5_elem_size = 4U;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 36);
      c5_elem_type = 2U;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 37);
      chartInstance->c5_vect_size = 7U;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 38);
      for (c5_i5 = 0; c5_i5 < 22; c5_i5++) {
        c5_x[c5_i5] = c5_b_logname[c5_i5];
      }

      c5_hoistedGlobal = chartInstance->c5_lognumstr;
      if ((0.0 <= c5_hoistedGlobal) && (c5_hoistedGlobal <= 255.0)) {
        c5_b0 = true;
      } else {
        c5_b0 = false;
      }

      if (c5_b0) {
      } else {
        c5_y = NULL;
        sf_mex_assign(&c5_y, sf_mex_create("y", c5_cv3, 10, 0U, 1U, 0U, 2, 1, 44),
                      false);
        c5_u = 0.0;
        c5_b_y = NULL;
        sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0),
                      false);
        c5_b_u = 255.0;
        c5_c_y = NULL;
        sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 0, 0U, 0U, 0U, 0),
                      false);
        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                          sf_mex_call_debug(sfGlobalDebugInstanceStruct,
          "message", 1U, 3U, 14, c5_y, 14, c5_b_y, 14, c5_c_y));
      }

      for (c5_i6 = 0; c5_i6 < 56; c5_i6++) {
        c5_cv4[c5_i6] = c5_cv5[c5_i6];
      }

      for (c5_i7 = 0; c5_i7 < 22; c5_i7++) {
        c5_b_x[c5_i7] = (char_T)c5__s8_u8_(chartInstance, c5_x[c5_i7], 1U, 1518U,
          7U);
      }

      c5_b_x[22] = '_';
      c5_c_u = c5_hoistedGlobal;
      if (c5_c_u < 0.0) {
        c5_d2 = muDoubleScalarCeil(c5_c_u);
      } else {
        c5_d2 = muDoubleScalarFloor(c5_c_u);
      }

      if (muDoubleScalarIsNaN(c5_d2) || muDoubleScalarIsInf(c5_d2)) {
        c5_d3 = 0.0;
      } else {
        c5_d3 = muDoubleScalarRem(c5_d2, 256.0);
      }

      if (c5_d3 < 0.0) {
        c5_b_x[23] = (char_T)(int8_T)-(int8_T)(uint8_T)-c5_d3;
      } else {
        c5_b_x[23] = (char_T)(int8_T)(uint8_T)c5_d3;
      }

      for (c5_i8 = 0; c5_i8 < 4; c5_i8++) {
        c5_b_x[c5_i8 + 24] = c5_cv6[c5_i8];
      }

      c5_b_x[28] = '\x00';
      printf(c5_cv4, c5_b_x, (uint32_T)chartInstance->c5_vect_size, (uint32_T)
             chartInstance->c5_elem_size, c5_b_numRecs, 10U);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 40);
      for (c5_i9 = 0; c5_i9 < 22; c5_i9++) {
        c5_x[c5_i9] = c5_b_logname[c5_i9];
      }

      c5_b_hoistedGlobal = chartInstance->c5_lognumstr;
      if ((0.0 <= c5_b_hoistedGlobal) && (c5_b_hoistedGlobal <= 255.0)) {
        c5_b1 = true;
      } else {
        c5_b1 = false;
      }

      if (c5_b1) {
      } else {
        c5_d_y = NULL;
        sf_mex_assign(&c5_d_y, sf_mex_create("y", c5_cv7, 10, 0U, 1U, 0U, 2, 1,
          44), false);
        c5_d_u = 0.0;
        c5_e_y = NULL;
        sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_d_u, 0, 0U, 0U, 0U, 0),
                      false);
        c5_e_u = 255.0;
        c5_f_y = NULL;
        sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_e_u, 0, 0U, 0U, 0U, 0),
                      false);
        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                          sf_mex_call_debug(sfGlobalDebugInstanceStruct,
          "message", 1U, 3U, 14, c5_d_y, 14, c5_e_y, 14, c5_f_y));
      }

      for (c5_i10 = 0; c5_i10 < 22; c5_i10++) {
        c5_c_x[c5_i10] = (char_T)c5__s8_u8_(chartInstance, c5_x[c5_i10], 1U,
          1673U, 7U);
      }

      c5_c_x[22] = '_';
      c5_f_u = c5_b_hoistedGlobal;
      if (c5_f_u < 0.0) {
        c5_d4 = muDoubleScalarCeil(c5_f_u);
      } else {
        c5_d4 = muDoubleScalarFloor(c5_f_u);
      }

      if (muDoubleScalarIsNaN(c5_d4) || muDoubleScalarIsInf(c5_d4)) {
        c5_d5 = 0.0;
      } else {
        c5_d5 = muDoubleScalarRem(c5_d4, 256.0);
      }

      if (c5_d5 < 0.0) {
        c5_c_x[23] = (char_T)(int8_T)-(int8_T)(uint8_T)-c5_d5;
      } else {
        c5_c_x[23] = (char_T)(int8_T)(uint8_T)c5_d5;
      }

      for (c5_i11 = 0; c5_i11 < 4; c5_i11++) {
        c5_c_x[c5_i11 + 24] = c5_cv6[c5_i11];
      }

      c5_c_x[28] = '\x00';
      for (c5_i12 = 0; c5_i12 < 3; c5_i12++) {
        c5_cv8[c5_i12] = c5_cv9[c5_i12];
      }

      chartInstance->c5_fp = fopen(c5_c_x, c5_cv8);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 41);
      chartInstance->c5_lognumstr++;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 42);
      chartInstance->c5_isflushed = false;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 43);
      chartInstance->c5_count = 0U;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 44);
      chartInstance->c5_isopen = true;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 47);
      for (c5_i13 = 0; c5_i13 < 8; c5_i13++) {
        c5_mlStrVer[c5_i13] = c5_cv10[c5_i13];
      }

      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 48);
      fwrite(c5_mlStrVer, 1U, 8.0, chartInstance->c5_fp);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 50);
      c5_tm = 0U;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 51);
      c5_tmptr = 0U;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 52);
      c5_tm = time(&c5_tmptr);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 53);
      fwrite(&c5_tm, 4U, 1U, chartInstance->c5_fp);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 55);
      fwrite(&chartInstance->c5_vect_size, 1U, 1U, chartInstance->c5_fp);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 57);
      fwrite(&c5_elem_type, 1U, 1U, chartInstance->c5_fp);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 59);
      c5_u3 = (uint32_T)chartInstance->c5_elem_size * (uint32_T)
        chartInstance->c5_vect_size;
      if (CV_SATURATION_EVAL(4, 0, 0, 0, c5_u3 > 65535U)) {
        c5_u3 = 65535U;
        _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 2611U, 29U);
      }

      c5_recSize = (uint16_T)c5_u3;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 60);
      fwrite(&c5_recSize, 2U, 1U, chartInstance->c5_fp);
    }

    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 63);
    if (CV_EML_IF(0, 1, 4, c5_b_cacheflag)) {
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 64);
      c5_u0 = (uint64_T)chartInstance->c5_count * (uint64_T)
        chartInstance->c5_vect_size;
      if (CV_SATURATION_EVAL(4, 0, 2, 0, c5_u0 > 4294967295ULL)) {
        c5_u0 = 4294967295ULL;
        _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 2830U, 23U);
      }

      c5_q0 = (uint32_T)c5_u0;
      c5_qY = c5_q0 + 1U;
      if (CV_SATURATION_EVAL(4, 0, 1, 0, c5_qY < c5_q0)) {
        c5_qY = MAX_uint32_T;
        _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 2829U, 27U);
      }

      c5_addr = c5_qY;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 65);
      c5_b_vect_size = chartInstance->c5_vect_size;
      c5_overflow = ((!(1 > c5_b_vect_size)) && (c5_b_vect_size > 254));
      if (c5_overflow) {
        c5_check_forloop_overflow_error(chartInstance, true);
      }

      c5_b_idx = 1U;
      _SFD_SYMBOL_SWITCH(8U, 9U);
      c5_c_idx = 1U;
      while (c5_c_idx <= c5_b_vect_size) {
        c5_b_idx = c5_c_idx;
        _SFD_SYMBOL_SWITCH(8U, 9U);
        CV_EML_FOR(0, 1, 0, 1);
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 67);
        c5_e_q0 = c5_addr;
        c5_e_qY = c5_e_q0 + 1U;
        if (CV_SATURATION_EVAL(4, 0, 3, 0, c5_e_qY < c5_e_q0)) {
          c5_e_qY = MAX_uint32_T;
          _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 2962U, 8U);
        }

        c5_addr = c5_e_qY;
        c5_c_idx = (uint8_T)((uint32_T)c5_c_idx + 1U);
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 0, 0);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 69);
      c5_d_q0 = chartInstance->c5_count;
      c5_d_qY = c5_d_q0 + 1U;
      if (CV_SATURATION_EVAL(4, 0, 4, 0, c5_d_qY < c5_d_q0)) {
        c5_d_qY = MAX_uint32_T;
        _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 3008U, 17U);
      }

      chartInstance->c5_count = c5_d_qY;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 71);
      if (CV_EML_IF(0, 1, 5, c5_b_datalog_flag)) {
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 72);
        fwrite(c5_b_data, chartInstance->c5_elem_size,
               chartInstance->c5_vect_size, chartInstance->c5_fp);
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 73);
        c5_b_q0 = chartInstance->c5_count;
        c5_b_qY = c5_b_q0 + 1U;
        if (CV_SATURATION_EVAL(4, 0, 5, 0, c5_b_qY < c5_b_q0)) {
          c5_b_qY = MAX_uint32_T;
          _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 3176U, 17U);
        }

        chartInstance->c5_count = c5_b_qY;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 78);
    if (CV_EML_IF(0, 1, 6, CV_RELATIONAL_EVAL(4U, 0U, 3, (real_T)
          chartInstance->c5_count, (real_T)c5_b_numRecs, 0, 5U,
          chartInstance->c5_count >= c5_b_numRecs))) {
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 79);
      if (CV_EML_IF(0, 1, 7, c5_b_cacheflag)) {
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 80);
        c5_u1 = (uint64_T)chartInstance->c5_count * (uint64_T)
          chartInstance->c5_vect_size;
        if (CV_SATURATION_EVAL(4, 0, 6, 0, c5_u1 > 4294967295ULL)) {
          c5_u1 = 4294967295ULL;
          _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 3350U, 23U);
        }

        c5_b = (uint32_T)c5_u1;
        c5_b_overflow = ((!(1U > c5_b)) && (c5_b > 4294967294U));
        if (c5_b_overflow) {
          c5_b_check_forloop_overflow_error(chartInstance, true);
        }

        c5_idx = 1U;
        _SFD_SYMBOL_SWITCH(8U, 8U);
        c5_d_idx = 1U;
        while (c5_d_idx <= c5_b) {
          c5_idx = c5_d_idx;
          _SFD_SYMBOL_SWITCH(8U, 8U);
          CV_EML_FOR(0, 1, 1, 1);
          c5_d_idx++;
          _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
        }

        CV_EML_FOR(0, 1, 1, 0);
      }

      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 84);
      fflush(chartInstance->c5_fp);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 85);
      chartInstance->c5_isflushed = false;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 86);
      chartInstance->c5_count = 0U;
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 89);
    if (CV_EML_IF(0, 1, 8, chartInstance->c5_isopen)) {
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 90);
      if (CV_EML_IF(0, 1, 9, CV_EML_MCDC(0, 1, 0, !CV_EML_COND(0, 1, 0,
             chartInstance->c5_isflushed)))) {
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 91);
        for (c5_i4 = 0; c5_i4 < 28; c5_i4++) {
          c5_cv1[c5_i4] = c5_cv2[c5_i4];
        }

        printf(c5_cv1, chartInstance->c5_count, 10U);
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 92);
        if (CV_EML_IF(0, 1, 10, c5_b_cacheflag)) {
          _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 93);
          c5_c_q0 = chartInstance->c5_count;
          c5_c_qY = c5_c_q0 + 1U;
          if (CV_SATURATION_EVAL(4, 0, 7, 0, c5_c_qY < c5_c_q0)) {
            c5_c_qY = MAX_uint32_T;
            _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 3847U, 17U);
          }

          chartInstance->c5_count = c5_c_qY;
          _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 94);
          c5_u2 = (uint64_T)chartInstance->c5_count * (uint64_T)
            chartInstance->c5_vect_size;
          if (CV_SATURATION_EVAL(4, 0, 8, 0, c5_u2 > 4294967295ULL)) {
            c5_u2 = 4294967295ULL;
            _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 1U, 3898U, 23U);
          }

          c5_b_b = (uint32_T)c5_u2;
          c5_c_overflow = ((!(1U > c5_b_b)) && (c5_b_b > 4294967294U));
          if (c5_c_overflow) {
            c5_b_check_forloop_overflow_error(chartInstance, true);
          }

          c5_idx = 1U;
          _SFD_SYMBOL_SWITCH(8U, 8U);
          c5_e_idx = 1U;
          while (c5_e_idx <= c5_b_b) {
            c5_idx = c5_e_idx;
            _SFD_SYMBOL_SWITCH(8U, 8U);
            CV_EML_FOR(0, 1, 2, 1);
            c5_e_idx++;
            _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
          }

          CV_EML_FOR(0, 1, 2, 0);
        }

        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 98);
        fflush(chartInstance->c5_fp);
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 99);
        chartInstance->c5_isflushed = true;
      }

      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 101);
      fclose(chartInstance->c5_fp);
    }

    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 103);
    chartInstance->c5_isopen = false;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 104);
    chartInstance->c5_count = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -104);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
}

static void initSimStructsc5_ekf_cf(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)(c5_machineNumber);
  (void)(c5_chartNumber);
  (void)(c5_instanceNumber);
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint8_T *)c5_inData;
  c5_y = NULL;
  if (!chartInstance->c5_vect_size_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint8_T c5_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_vect_size, const char_T *c5_identifier, boolean_T
  *c5_svPtr)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_vect_size),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_vect_size);
  return c5_y;
}

static uint8_T c5_b_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr)
{
  uint8_T c5_y;
  uint8_T c5_u4;
  (void)chartInstance;
  if (mxIsEmpty(c5_u)) {
    *c5_svPtr = false;
  } else {
    *c5_svPtr = true;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u4, 1, 3, 0U, 0, 0U, 0);
    c5_y = c5_u4;
  }

  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_vect_size;
  boolean_T *c5_svPtr;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_vect_size = sf_mex_dup(c5_mxArrayInData);
  c5_svPtr = &chartInstance->c5_vect_size_not_empty;
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_vect_size),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_vect_size);
  *(uint8_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint16_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint16_T *)c5_inData;
  c5_y = NULL;
  if (!chartInstance->c5_elem_size_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 5, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint16_T c5_c_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_elem_size, const char_T *c5_identifier, boolean_T
  *c5_svPtr)
{
  uint16_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_elem_size),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_elem_size);
  return c5_y;
}

static uint16_T c5_d_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr)
{
  uint16_T c5_y;
  uint16_T c5_u5;
  (void)chartInstance;
  if (mxIsEmpty(c5_u)) {
    *c5_svPtr = false;
  } else {
    *c5_svPtr = true;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u5, 1, 5, 0U, 0, 0U, 0);
    c5_y = c5_u5;
  }

  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_elem_size;
  boolean_T *c5_svPtr;
  emlrtMsgIdentifier c5_thisId;
  uint16_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_elem_size = sf_mex_dup(c5_mxArrayInData);
  c5_svPtr = &chartInstance->c5_elem_size_not_empty;
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_elem_size),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_elem_size);
  *(uint16_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  if (!chartInstance->c5_lognumstr_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_e_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_lognumstr, const char_T *c5_identifier, boolean_T
  *c5_svPtr)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_lognumstr),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_lognumstr);
  return c5_y;
}

static real_T c5_f_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr)
{
  real_T c5_y;
  real_T c5_d6;
  (void)chartInstance;
  if (mxIsEmpty(c5_u)) {
    *c5_svPtr = false;
  } else {
    *c5_svPtr = true;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d6, 1, 0, 0U, 0, 0U, 0);
    c5_y = c5_d6;
  }

  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_lognumstr;
  boolean_T *c5_svPtr;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_lognumstr = sf_mex_dup(c5_mxArrayInData);
  c5_svPtr = &chartInstance->c5_lognumstr_not_empty;
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_lognumstr),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_lognumstr);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint32_T *)c5_inData;
  c5_y = NULL;
  if (!chartInstance->c5_count_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 7, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint32_T c5_g_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_count, const char_T *c5_identifier, boolean_T *c5_svPtr)
{
  uint32_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_count), &c5_thisId,
    c5_svPtr);
  sf_mex_destroy(&c5_b_count);
  return c5_y;
}

static uint32_T c5_h_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr)
{
  uint32_T c5_y;
  uint32_T c5_u6;
  (void)chartInstance;
  if (mxIsEmpty(c5_u)) {
    *c5_svPtr = false;
  } else {
    *c5_svPtr = true;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u6, 1, 7, 0U, 0, 0U, 0);
    c5_y = c5_u6;
  }

  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_count;
  boolean_T *c5_svPtr;
  emlrtMsgIdentifier c5_thisId;
  uint32_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_count = sf_mex_dup(c5_mxArrayInData);
  c5_svPtr = &chartInstance->c5_count_not_empty;
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_count), &c5_thisId,
    c5_svPtr);
  sf_mex_destroy(&c5_b_count);
  *(uint32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  boolean_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(boolean_T *)c5_inData;
  c5_y = NULL;
  if (!chartInstance->c5_isopen_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 11, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static boolean_T c5_i_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_b_isopen, const char_T *c5_identifier, boolean_T *c5_svPtr)
{
  boolean_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_isopen),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_isopen);
  return c5_y;
}

static boolean_T c5_j_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T
  *c5_svPtr)
{
  boolean_T c5_y;
  boolean_T c5_b2;
  (void)chartInstance;
  if (mxIsEmpty(c5_u)) {
    *c5_svPtr = false;
  } else {
    *c5_svPtr = true;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_b2, 1, 11, 0U, 0, 0U, 0);
    c5_y = c5_b2;
  }

  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_isopen;
  boolean_T *c5_svPtr;
  emlrtMsgIdentifier c5_thisId;
  boolean_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_isopen = sf_mex_dup(c5_mxArrayInData);
  c5_svPtr = &chartInstance->c5_isopen_not_empty;
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_isopen),
    &c5_thisId, c5_svPtr);
  sf_mex_destroy(&c5_b_isopen);
  *(boolean_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 7, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint32_T c5_k_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint32_T c5_y;
  uint32_T c5_u7;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u7, 1, 7, 0U, 0, 0U, 0);
  c5_y = c5_u7;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_numRecs;
  emlrtMsgIdentifier c5_thisId;
  uint32_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_numRecs = sf_mex_dup(c5_mxArrayInData);
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_numRecs),
    &c5_thisId);
  sf_mex_destroy(&c5_b_numRecs);
  *(uint32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  boolean_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(boolean_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static boolean_T c5_l_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  boolean_T c5_y;
  boolean_T c5_b3;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_b3, 1, 11, 0U, 0, 0U, 0);
  c5_y = c5_b3;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_cacheflag;
  emlrtMsgIdentifier c5_thisId;
  boolean_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_cacheflag = sf_mex_dup(c5_mxArrayInData);
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_cacheflag),
    &c5_thisId);
  sf_mex_destroy(&c5_b_cacheflag);
  *(boolean_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i14;
  const mxArray *c5_y = NULL;
  uint8_T c5_u[22];
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  for (c5_i14 = 0; c5_i14 < 22; c5_i14++) {
    c5_u[c5_i14] = (*(uint8_T (*)[22])c5_inData)[c5_i14];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 3, 0U, 1U, 0U, 2, 1, 22), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_m_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, uint8_T c5_y[22])
{
  uint8_T c5_uv0[22];
  int32_T c5_i15;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_uv0, 1, 3, 0U, 1, 0U, 2, 1, 22);
  for (c5_i15 = 0; c5_i15 < 22; c5_i15++) {
    c5_y[c5_i15] = c5_uv0[c5_i15];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_logname;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y[22];
  int32_T c5_i16;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_logname = sf_mex_dup(c5_mxArrayInData);
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_logname), &c5_thisId,
                        c5_y);
  sf_mex_destroy(&c5_b_logname);
  for (c5_i16 = 0; c5_i16 < 22; c5_i16++) {
    (*(uint8_T (*)[22])c5_outData)[c5_i16] = c5_y[c5_i16];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_i_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i17;
  const mxArray *c5_y = NULL;
  real32_T c5_u[7];
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  for (c5_i17 = 0; c5_i17 < 7; c5_i17++) {
    c5_u[c5_i17] = (*(real32_T (*)[7])c5_inData)[c5_i17];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 1, 0U, 1U, 0U, 1, 7), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_j_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_n_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d7;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d7, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d7;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nargout;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_nargout = sf_mex_dup(c5_mxArrayInData);
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_k_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint8_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint8_T c5_o_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_idx, const char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = (const char *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_idx), &c5_thisId);
  sf_mex_destroy(&c5_idx);
  return c5_y;
}

static uint8_T c5_p_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u8;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u8, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u8;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_idx;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_idx = sf_mex_dup(c5_mxArrayInData);
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_idx), &c5_thisId);
  sf_mex_destroy(&c5_idx);
  *(uint8_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_l_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint16_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint16_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint16_T c5_q_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint16_T c5_y;
  uint16_T c5_u9;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u9, 1, 5, 0U, 0, 0U, 0);
  c5_y = c5_u9;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_recSize;
  emlrtMsgIdentifier c5_thisId;
  uint16_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_recSize = sf_mex_dup(c5_mxArrayInData);
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_recSize), &c5_thisId);
  sf_mex_destroy(&c5_recSize);
  *(uint16_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_m_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i18;
  const mxArray *c5_y = NULL;
  char_T c5_u[8];
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  for (c5_i18 = 0; c5_i18 < 8; c5_i18++) {
    c5_u[c5_i18] = (*(char_T (*)[8])c5_inData)[c5_i18];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 10, 0U, 1U, 0U, 2, 1, 8), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_r_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, char_T c5_y[8])
{
  char_T c5_cv11[8];
  int32_T c5_i19;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_cv11, 1, 10, 0U, 1, 0U, 2, 1,
                8);
  for (c5_i19 = 0; c5_i19 < 8; c5_i19++) {
    c5_y[c5_i19] = c5_cv11[c5_i19];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_mlStrVer;
  emlrtMsgIdentifier c5_thisId;
  char_T c5_y[8];
  int32_T c5_i20;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mlStrVer = sf_mex_dup(c5_mxArrayInData);
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_mlStrVer), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_mlStrVer);
  for (c5_i20 = 0; c5_i20 < 8; c5_i20++) {
    (*(char_T (*)[8])c5_outData)[c5_i20] = c5_y[c5_i20];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_ekf_cf_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c5_nameCaptureInfo;
}

static void c5_check_forloop_overflow_error(SFc5_ekf_cfInstanceStruct
  *chartInstance, boolean_T c5_overflow)
{
  const mxArray *c5_y = NULL;
  const mxArray *c5_b_y = NULL;
  static char_T c5_cv12[5] = { 'u', 'i', 'n', 't', '8' };

  (void)chartInstance;
  if (!c5_overflow) {
  } else {
    c5_y = NULL;
    sf_mex_assign(&c5_y, sf_mex_create("y", c5_cv0, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    c5_b_y = NULL;
    sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_cv12, 10, 0U, 1U, 0U, 2, 1, 5),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c5_y, 14, c5_b_y));
  }
}

static void c5_b_check_forloop_overflow_error(SFc5_ekf_cfInstanceStruct
  *chartInstance, boolean_T c5_overflow)
{
  const mxArray *c5_y = NULL;
  const mxArray *c5_b_y = NULL;
  static char_T c5_cv13[6] = { 'u', 'i', 'n', 't', '3', '2' };

  (void)chartInstance;
  if (!c5_overflow) {
  } else {
    c5_y = NULL;
    sf_mex_assign(&c5_y, sf_mex_create("y", c5_cv0, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    c5_b_y = NULL;
    sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_cv13, 10, 0U, 1U, 0U, 2, 1, 6),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c5_y, 14, c5_b_y));
  }
}

static const mxArray *c5_n_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_s_emlrt_marshallIn(SFc5_ekf_cfInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i21;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i21, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i21;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_thisId.fIdentifier = (const char *)c5_varName;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static int8_T c5__s8_u8_(SFc5_ekf_cfInstanceStruct *chartInstance, uint8_T c5_b,
  uint32_T c5_ssid_src_loc, int32_T c5_offset_src_loc, int32_T c5_length_src_loc)
{
  int8_T c5_a;
  (void)chartInstance;
  c5_a = (int8_T)c5_b;
  if (c5_a < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c5_ssid_src_loc, c5_offset_src_loc,
      c5_length_src_loc);
  }

  return c5_a;
}

static void init_dsm_address_info(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc5_ekf_cfInstanceStruct *chartInstance)
{
  chartInstance->c5_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c5_en = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c5_data = (real32_T (*)[7])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_datalog_flag = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c5_ekf_cf_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2001409370U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4171959036U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2179840403U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(939105276U);
}

mxArray* sf_c5_ekf_cf_get_post_codegen_info(void);
mxArray *sf_c5_ekf_cf_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("lgZ2kdxTP1qrIqLBNMYMP");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(22);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(7));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c5_ekf_cf_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_ekf_cf_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_ekf_cf_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("printf");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c5_ekf_cf_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c5_ekf_cf_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c5_ekf_cf(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[4],M[0],T\"count\",S'l','i','p'{{M1x2[641 646],M[0],}}},{M[4],M[0],T\"elem_size\",S'l','i','p'{{M1x2[657 666],M[0],}}},{M[4],M[0],T\"isflushed\",S'l','i','p'{{M1x2[624 633],M[0],}}},{M[4],M[0],T\"isopen\",S'l','i','p'{{M1x2[634 640],M[0],}}},{M[4],M[0],T\"lognumstr\",S'l','i','p'{{M1x2[647 656],M[0],}}},{M[4],M[0],T\"vect_size\",S'l','i','p'{{M1x2[667 676],M[0],}}},{M[8],M[0],T\"is_active_c5_ekf_cf\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_ekf_cf_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_ekf_cfInstanceStruct *chartInstance = (SFc5_ekf_cfInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ekf_cfMachineNumber_,
           5,
           1,
           1,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_ekf_cfMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ekf_cfMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ekf_cfMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"en");
          _SFD_SET_DATA_PROPS(1,1,1,0,"data");
          _SFD_SET_DATA_PROPS(2,1,1,0,"datalog_flag");
          _SFD_SET_DATA_PROPS(3,10,0,0,"cacheflag");
          _SFD_SET_DATA_PROPS(4,10,0,0,"logname");
          _SFD_SET_DATA_PROPS(5,10,0,0,"numRecs");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,2,0,12,0,9,1,3,0,2,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",520,-1,4275);
        _SFD_CV_INIT_EML_FCN(0,1,"get_elem_size",4319,-1,5326);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,2611,-1,2640);
        _SFD_CV_INIT_EML_SATURATION(0,1,1,2829,-1,2856);
        _SFD_CV_INIT_EML_SATURATION(0,1,2,2830,-1,2853);
        _SFD_CV_INIT_EML_SATURATION(0,1,3,2962,-1,2970);
        _SFD_CV_INIT_EML_SATURATION(0,1,4,3008,-1,3025);
        _SFD_CV_INIT_EML_SATURATION(0,1,5,3176,-1,3193);
        _SFD_CV_INIT_EML_SATURATION(0,1,6,3350,-1,3373);
        _SFD_CV_INIT_EML_SATURATION(0,1,7,3847,-1,3864);
        _SFD_CV_INIT_EML_SATURATION(0,1,8,3898,-1,3921);
        _SFD_CV_INIT_EML_IF(0,1,0,751,768,-1,1139);
        _SFD_CV_INIT_EML_IF(0,1,1,1007,1027,-1,1131);
        _SFD_CV_INIT_EML_IF(0,1,2,1145,1152,3626,4271);
        _SFD_CV_INIT_EML_IF(0,1,3,1161,1179,-1,2735);
        _SFD_CV_INIT_EML_IF(0,1,4,2789,2809,3035,3222);
        _SFD_CV_INIT_EML_IF(0,1,5,3052,3068,-1,3210);
        _SFD_CV_INIT_EML_IF(0,1,6,3277,3296,-1,3621);
        _SFD_CV_INIT_EML_IF(0,1,7,3309,3321,-1,3508);
        _SFD_CV_INIT_EML_IF(0,1,8,3639,3656,-1,4212);
        _SFD_CV_INIT_EML_IF(0,1,9,3669,3682,-1,4161);
        _SFD_CV_INIT_EML_IF(0,1,10,3806,3818,-1,4068);
        _SFD_CV_INIT_EML_IF(0,1,11,5199,5215,-1,5256);
        _SFD_CV_INIT_EML_FOR(0,1,0,2870,2892,2987);
        _SFD_CV_INIT_EML_FOR(0,1,1,3338,3374,3492);
        _SFD_CV_INIT_EML_FOR(0,1,2,3886,3922,4048);

        {
          static int caseStart[] = { -1, 4401, 4473, 4545, 4616, 4688, 4759,
            4831, 4901, 4972, 5045 };

          static int caseExprEnd[] = { 8, 4414, 4486, 4557, 4629, 4700, 4772,
            4842, 4913, 4986, 5063 };

          _SFD_CV_INIT_EML_SWITCH(0,1,0,4373,4392,5194,11,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int condStart[] = { 3673 };

          static int condEnd[] = { 3682 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,3672,3682,1,0,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 5203 };

          static int condEnd[] = { 5215 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,5202,5215,1,1,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,3280,3296,0,5);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_g_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 7U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_SINGLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_g_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_g_sf_marshallOut,(MexInFcnForType)c5_g_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 22U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_h_sf_marshallOut,(MexInFcnForType)
            c5_h_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_f_sf_marshallOut,(MexInFcnForType)c5_f_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ekf_cfMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_ekf_cfInstanceStruct *chartInstance = (SFc5_ekf_cfInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c5_en);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c5_data);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c5_datalog_flag);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)&chartInstance->c5_logname);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)&chartInstance->c5_cacheflag);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)&chartInstance->c5_numRecs);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s7SKa2rny5EBQwKfzSpgtkD";
}

static void sf_opaque_initialize_c5_ekf_cf(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_ekf_cfInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c5_ekf_cf((SFc5_ekf_cfInstanceStruct*) chartInstanceVar);
  initialize_c5_ekf_cf((SFc5_ekf_cfInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_ekf_cf(void *chartInstanceVar)
{
  enable_c5_ekf_cf((SFc5_ekf_cfInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_ekf_cf(void *chartInstanceVar)
{
  disable_c5_ekf_cf((SFc5_ekf_cfInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_ekf_cf(void *chartInstanceVar)
{
  sf_gateway_c5_ekf_cf((SFc5_ekf_cfInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c5_ekf_cf(SimStruct* S)
{
  return get_sim_state_c5_ekf_cf((SFc5_ekf_cfInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c5_ekf_cf(SimStruct* S, const mxArray *st)
{
  set_sim_state_c5_ekf_cf((SFc5_ekf_cfInstanceStruct*)sf_get_chart_instance_ptr
    (S), st);
}

static void sf_opaque_terminate_c5_ekf_cf(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_ekf_cfInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ekf_cf_optimization_info();
    }

    finalize_c5_ekf_cf((SFc5_ekf_cfInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_ekf_cf((SFc5_ekf_cfInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_ekf_cf(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_ekf_cf((SFc5_ekf_cfInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c5_ekf_cf(SimStruct *S)
{
  /* Actual parameters from chart:
     cacheflag logname numRecs
   */
  const char_T *rtParamNames[] = { "cacheflag", "logname", "numRecs" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for cacheflag*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_BOOLEAN);

  /* registration for logname*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT8);

  /* registration for numRecs*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT32);

  /* Set overwritable ports for inplace optimization */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ekf_cf_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 5);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=0; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(657607842U));
  ssSetChecksum1(S,(1413853724U));
  ssSetChecksum2(S,(452415909U));
  ssSetChecksum3(S,(2112308973U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetSimStateCompliance(S, DISALLOW_SIM_STATE);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_ekf_cf(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_ekf_cf(SimStruct *S)
{
  SFc5_ekf_cfInstanceStruct *chartInstance;
  chartInstance = (SFc5_ekf_cfInstanceStruct *)utMalloc(sizeof
    (SFc5_ekf_cfInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc5_ekf_cfInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  if (ssGetSampleTime(S, 0) == CONTINUOUS_SAMPLE_TIME && ssGetOffsetTime(S, 0) ==
      0 && ssGetNumContStates(ssGetRootSS(S)) > 0) {
    sf_error_out_about_continuous_sample_time_with_persistent_vars(S);
  }

  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_ekf_cf;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_ekf_cf;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_ekf_cf;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_ekf_cf;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_ekf_cf;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_ekf_cf;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_ekf_cf;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_ekf_cf;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_ekf_cf;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_ekf_cf;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_ekf_cf;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c5_ekf_cf(chartInstance);
}

void c5_ekf_cf_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_ekf_cf(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_ekf_cf(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_ekf_cf(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_ekf_cf_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
