/*
 * Funciones_RTOS.c
 *
 *  Created on: 12 de oct. de 2016
 *      Author: Ruben
 */
#include "Funciones_RTOS.h"

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Create the mutex(es) */
  /* definition and creation of I2C_2_MUTEX */
  osMutexDef(I2C_2_MUTEX);
  I2C_2_MUTEXHandle = osMutexCreate(osMutex(I2C_2_MUTEX));

  /* definition and creation of UART_MUTEX */
  osMutexDef(UART_MUTEX);
  UART_MUTEXHandle = osMutexCreate(osMutex(UART_MUTEX));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of CONTROL_SMPHR */
  osSemaphoreDef(CONTROL_SMPHR);
  CONTROL_SMPHRHandle = osSemaphoreCreate(osSemaphore(CONTROL_SMPHR), 1);

  /* definition and creation of IMU_SMPHR */
  osSemaphoreDef(IMU_SMPHR);
  IMU_SMPHRHandle = osSemaphoreCreate(osSemaphore(IMU_SMPHR), 1);

  /* definition and creation of COMPASS_SMPHR */
  osSemaphoreDef(COMPASS_SMPHR);
  COMPASS_SMPHRHandle = osSemaphoreCreate(osSemaphore(COMPASS_SMPHR), 1);

  /* definition and creation of ALTURA_SMPHR */
  osSemaphoreDef(ALTURA_SMPHR);
  ALTURA_SMPHRHandle = osSemaphoreCreate(osSemaphore(ALTURA_SMPHR), 1);

  /* definition and creation of COORDINADOR_SMPHR */
  osSemaphoreDef(COORDINADOR_SMPHR);
  COORDINADOR_SMPHRHandle = osSemaphoreCreate(osSemaphore(COORDINADOR_SMPHR), 1);

  /* definition and creation of AHRS_SMPHR */
  osSemaphoreDef(AHRS_SMPHR);
  AHRS_SMPHRHandle = osSemaphoreCreate(osSemaphore(AHRS_SMPHR), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of CONTROL_TIMER */
  osTimerDef(CONTROL_TIMER, CONTROL_TIMER_FCN);
  CONTROL_TIMERHandle = osTimerCreate(osTimer(CONTROL_TIMER), osTimerPeriodic, NULL);

  /* definition and creation of IMU_TIMER */
  osTimerDef(IMU_TIMER, IMU_TIMER_FCN);
  IMU_TIMERHandle = osTimerCreate(osTimer(IMU_TIMER), osTimerPeriodic, NULL);

  /* definition and creation of COORDINADOR_TIMER */
  osTimerDef(COORDINADOR_TIMER, COORDINADOR_TIMER_FCN);
  COORDINADOR_TIMERHandle = osTimerCreate(osTimer(COORDINADOR_TIMER), osTimerPeriodic, NULL);

  /* definition and creation of AHRS_TIMER */
  osTimerDef(AHRS_TIMER, AHRS_TIMER_FCN);
  AHRS_TIMERHandle = osTimerCreate(osTimer(AHRS_TIMER), osTimerPeriodic, NULL);

  /* definition and creation of COMPASS_TIMER */
  osTimerDef(COMPASS_TIMER, COMPASS_TIMER_FCN);
  COMPASS_TIMERHandle = osTimerCreate(osTimer(COMPASS_TIMER), osTimerPeriodic, NULL);

  /* definition and creation of ALTURA_TIMER */
  osTimerDef(ALTURA_TIMER, ALTURA_TIMER_FCN);
  ALTURA_TIMERHandle = osTimerCreate(osTimer(ALTURA_TIMER), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  //osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  //defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of CONTROL_TASK */
  osThreadDef(CONTROL_TASK, CONTROL_TASK_FCN, osPriorityAboveNormal, 0, 128);
  CONTROL_TASKHandle = osThreadCreate(osThread(CONTROL_TASK), NULL);

  /* definition and creation of IMU_TASK */
  osThreadDef(IMU_TASK, IMU_TASK_FCN, osPriorityRealtime, 0, 128);
  IMU_TASKHandle = osThreadCreate(osThread(IMU_TASK), NULL);

  /* definition and creation of AHRS_TASK */
  osThreadDef(AHRS_TASK, AHRS_TASK_FCN, osPriorityHigh, 0, 128);
  AHRS_TASKHandle = osThreadCreate(osThread(AHRS_TASK), NULL);

  /* definition and creation of COORDINADOR_TAS */
  osThreadDef(COORDINADOR_TAS, COORDINADOR_TASK_FCN, osPriorityNormal, 0, 128);
  COORDINADOR_TASHandle = osThreadCreate(osThread(COORDINADOR_TAS), NULL);

  /* definition and creation of COMPASS_TASK */
  osThreadDef(COMPASS_TASK, COMPASS_TASK_FCN, osPriorityIdle, 0, 128);
  COMPASS_TASKHandle = osThreadCreate(osThread(COMPASS_TASK), NULL);

  /* definition and creation of ALTURA_TASK */
  osThreadDef(ALTURA_TASK, ALTURA_TASK_FCN, osPriorityIdle, 0, 128);
  ALTURA_TASKHandle = osThreadCreate(osThread(ALTURA_TASK), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */

//void StartDefaultTask(void const * argument)
//{
//  /* init code for USB_DEVICE */
//  MX_USB_DEVICE_Init();
//
//  /* USER CODE BEGIN StartDefaultTask */
//  /* Infinite loop */
//  for(;;)
//  {
//    osDelay(1);
//  }
//  /* USER CODE END StartDefaultTask */
//}