/*
 * File: ert_main.c
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

#include <stdio.h>
#include <stdlib.h>
#include "ekf_cf.h"
#include "ekf_cf_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "rt_nonfinite.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"
#include "debug.h"
#include "time.h"
#include "math.h"
#include "poll.h"
#include "px4_posix.h"
#include "px4_tasks.h"
#include "unistd.h"
#include "uORB/uORB.h"
#include "uORB/topics/sensor_combined.h"
#include "uORB/topics/vehicle_attitude.h"
#include "uORB/topics/optical_flow.h"
#include "px4_config.h"
#include "px4_tasks.h"
#include "px4_posix.h"
#include "string.h"
#include "drivers/drv_led.h"
#include "drivers/drv_pwm_output.h"
#include "drivers/drv_rc_input.h"
#include "drivers/drv_hrt.h"
#include "arch/board/board.h"
#include "sys/mount.h"
#include "sys/ioctl.h"
#include "sys/stat.h"
#include "systemlib/perf_counter.h"
#include "systemlib/systemlib.h"
#include "systemlib/err.h"
#include "systemlib/param/param.h"
#include "nuttxinitialize.h"
#define UNUSED(x)                      x = x

/* Function prototype declaration*/
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T runModel = true;
sem_t stopSem;
sem_t baserateTaskSem;
extern sem_t PX4_Simulink_Task_Sem;
extern struct hrt_call BaseRate_HRT;
extern void (*MW_model_init)(void);
extern void (*MW_model_term)(void);
void PX4_Simulink_Task_Callback(void *arg);
extern void PX4_Simulink_Task_Callback_Test(void *arg);
sem_t subrateTaskSem[1];
int taskId[1];
pthread_t schedulerThread;
pthread_t baseRateThread;
unsigned long threadJoinStatus[8];
int terminatingmodel = 0;
pthread_t subRateThread[1];
int subratePriority[1];
void *subrateTask(void *arg)
{
  int tid = *((int *) arg);
  int subRateId;
  subRateId = tid + 1;
  while (runModel) {
    sem_wait(&subrateTaskSem[tid]);
    if (terminatingmodel)
      break;

#ifdef MW_RTOS_DEBUG

    printf(" -subrate task %d semaphore received\n", subRateId);

#endif

    ekf_cf_step(subRateId);

    /* Get model outputs here */
  }

  pthread_exit((void *)0);
  return NULL;
}

void *baseRateTask(void *arg)          //multi-rate multi-tasking
{
  runModel = (rtmGetErrorStatus(ekf_cf_M) == (NULL));
  while (runModel) {
    sem_wait(&baserateTaskSem);

#ifdef MW_RTOS_DEBUG

    printf("*base rate task semaphore received\n");
    fflush(stdout);

#endif

    if (rtmStepTask(ekf_cf_M, 1)
        ) {
      sem_post(&subrateTaskSem[0]);
    }

    ekf_cf_step(0);

    /* Get model outputs here */
    runModel = (rtmGetErrorStatus(ekf_cf_M) == (NULL));
  }

  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(ekf_cf_M, "stopping the model");
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;
  printf("**terminating the model**\n");
  fflush(stdout);

  {
    int i;

    /* Signal all periodic tasks to complete */
    for (i=0; i<1; i++) {
      CHECK_STATUS(sem_post(&subrateTaskSem[i]), 0, "sem_post");
      CHECK_STATUS(sem_destroy(&subrateTaskSem[i]), 0, "sem_destroy");
    }

    /* Wait for all periodic tasks to complete */
    for (i=0; i<1; i++) {
      CHECK_STATUS(pthread_join(subRateThread[i],(void *)&threadJoinStatus), 0,
                   "pthread_join");
    }

    runModel = 0;
  }

  sem_post(&stopSem);
  return NULL;
}

int px4_simulink_app_main(int argc, char *argv[]) //PX4 Simulink App
{
  subratePriority[0] = 249;
  rtmSetErrorStatus(ekf_cf_M, 0);
  int PX4_Simulink_Task_PID = 0;
  if (argc < 1)
    px4_app_usage("missing command");
  if (!strcmp(argv[1], "start")) {
    if (g_baseRateLife == false) {
      /* Start the Simulink Tasks here */
      printf("**starting the model**\n");
      fflush(stdout);

      /* Initialize function pointers */
      MW_model_init = &ekf_cf_initialize;
      MW_model_term = &ekf_cf_terminate;

      /* Reset semaphore */
      g_baseRateLife = true;
      sem_init(&PX4_Simulink_Task_Sem,0,0);

      /* Create task */
      PX4_Simulink_Task_PID = task_create("PX4_Simulink_Task", 100, 2048, (void *)
        PX4_Simulink_Task_Callback, (void *) &PX4_Simulink_Task_PID);
    } else {
      PX4_INFO("\t**model is already running**\n");
      fflush(stdout);
    }

    exit(0);
  }

  if (!strcmp(argv[1], "stop")) {
    if (g_baseRateLife == true) {
      rtmSetErrorStatus(ekf_cf_M, "Module finished");
      g_baseRateLife = false;
      sem_post(&baserateTaskSem);

      /* wait until the tasks completely finish */
      PX4_INFO("exiting model... waiting on stopSem...");

      /* Wait for stop semaphore */
      sem_wait(&stopSem);
      sem_post(&PX4_Simulink_Task_Sem);
    } else {
      PX4_INFO("\t**model is not running**\n");
      fflush(stdout);
    }

    exit(0);
  }

  if (!strcmp(argv[1], "status")) {
    if (g_baseRateLife) {
      PX4_INFO("\trunning\n");
    } else {
      PX4_INFO("\tnot started\n");
    }

    exit(0);
  }

  px4_app_usage("unrecognized command");
  return 1;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
