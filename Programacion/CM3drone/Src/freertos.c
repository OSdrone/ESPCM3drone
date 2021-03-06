/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId CONTROL_TASKHandle;
osThreadId IMU_TASKHandle;
osThreadId AHRS_TASKHandle;
osThreadId COORDINADOR_TASHandle;
osThreadId COMPASS_TASKHandle;
osThreadId ALTURA_TASKHandle;
osTimerId CONTROL_TIMERHandle;
osTimerId IMU_TIMERHandle;
osTimerId COORDINADOR_TIMERHandle;
osTimerId AHRS_TIMERHandle;
osTimerId COMPASS_TIMERHandle;
osTimerId ALTURA_TIMERHandle;
osMutexId I2C_2_MUTEXHandle;
osMutexId UART_MUTEXHandle;
osSemaphoreId CONTROL_SMPHRHandle;
osSemaphoreId IMU_SMPHRHandle;
osSemaphoreId COMPASS_SMPHRHandle;
osSemaphoreId ALTURA_SMPHRHandle;
osSemaphoreId COORDINADOR_SMPHRHandle;
osSemaphoreId AHRS_SMPHRHandle;
osSemaphoreId I2C_2_SMPHRHandle;
osSemaphoreId UART_SMPHRHandle;

QueueHandle_t AcelLecturasCola_Handle;
QueueHandle_t VelLecturasCola_Handle;
QueueHandle_t MagLecturasCola_Handle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
extern void CONTROL_TASK_FCN(void const * argument);
extern void IMU_TASK_FCN(void const * argument);
extern void AHRS_TASK_FCN(void const * argument);
extern void COORDINADOR_TASK_FCN(void const * argument);
extern void COMPASS_TASK_FCN(void const * argument);
extern void ALTURA_TASK_FCN(void const * argument);
extern void CONTROL_TIMER_FCN(void const * argument);
extern void IMU_TIMER_FCN(void const * argument);
extern void COORDINADOR_TIMER_FCN(void const * argument);
extern void AHRS_TIMER_FCN(void const * argument);
extern void COMPASS_TIMER_FCN(void const * argument);
extern void ALTURA_TIMER_FCN(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

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

  /* definition and creation of I2C_2_SMPHR */
  osSemaphoreDef(I2C_2_SMPHR);
  I2C_2_SMPHRHandle = osSemaphoreCreate(osSemaphore(I2C_2_SMPHR), 1);

  /* definition and creation of UART_SMPHR */
  osSemaphoreDef(UART_SMPHR);
  UART_SMPHRHandle = osSemaphoreCreate(osSemaphore(UART_SMPHR), 1);

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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

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
  osThreadDef(COORDINADOR_TASK, COORDINADOR_TASK_FCN, osPriorityNormal, 0, 128);
  COORDINADOR_TASHandle = osThreadCreate(osThread(COORDINADOR_TASK), NULL);

  /* definition and creation of COMPASS_TASK */
  osThreadDef(COMPASS_TASK, COMPASS_TASK_FCN, osPriorityBelowNormal, 0, 128);
  COMPASS_TASKHandle = osThreadCreate(osThread(COMPASS_TASK), NULL);

  /* definition and creation of ALTURA_TASK */
  osThreadDef(ALTURA_TASK, ALTURA_TASK_FCN, osPriorityNormal, 0, 128);
  ALTURA_TASKHandle = osThreadCreate(osThread(ALTURA_TASK), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  AcelLecturasCola_Handle = xQueueCreate(1, 3*sizeof(int16_t));
  VelLecturasCola_Handle = xQueueCreate(1, 3*sizeof(int16_t));
  MagLecturasCola_Handle = xQueueCreate(1, 3*sizeof(int16_t));
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
//  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
