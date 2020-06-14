#ifndef __c5_ekf_cf_h__
#define __c5_ekf_cf_h__

/* Type Definitions */
#ifndef typedef_SFc5_ekf_cfInstanceStruct
#define typedef_SFc5_ekf_cfInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c5_sfEvent;
  boolean_T c5_doneDoubleBufferReInit;
  uint8_T c5_is_active_c5_ekf_cf;
  uint8_T c5_logname[22];
  boolean_T c5_cacheflag;
  uint32_T c5_numRecs;
  FILE* c5_fp;
  boolean_T c5_fp_not_empty;
  boolean_T c5_isflushed;
  boolean_T c5_isflushed_not_empty;
  boolean_T c5_isopen;
  boolean_T c5_isopen_not_empty;
  uint32_T c5_count;
  boolean_T c5_count_not_empty;
  real_T c5_lognumstr;
  boolean_T c5_lognumstr_not_empty;
  uint16_T c5_elem_size;
  boolean_T c5_elem_size_not_empty;
  uint8_T c5_vect_size;
  boolean_T c5_vect_size_not_empty;
  void *c5_fEmlrtCtx;
  boolean_T *c5_en;
  real32_T (*c5_data)[7];
  boolean_T *c5_datalog_flag;
} SFc5_ekf_cfInstanceStruct;

#endif                                 /*typedef_SFc5_ekf_cfInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_ekf_cf_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c5_ekf_cf_get_check_sum(mxArray *plhs[]);
extern void c5_ekf_cf_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
