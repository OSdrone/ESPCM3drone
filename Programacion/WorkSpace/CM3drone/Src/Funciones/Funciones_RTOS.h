/**
  ******************************************************************************
  * File Name          : Funciones_RTOS.c
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
#include "arm_math.h"
#include "task.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "tim.h"

/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
//osThreadId defaultTaskHandle;
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

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
//void StartDefaultTask(void const * argument);
extern void CONTROL_TASK_FCN(void const * argument);
extern void CONTROL_TIMER_FCN(void const * argument);
extern void IMU_TASK_FCN(void const * argument);
extern void AHRS_TASK_FCN(void const * argument);
extern void COORDINADOR_TASK_FCN(void const * argument);
extern void COMPASS_TASK_FCN(void const * argument);
extern void ALTURA_TASK_FCN(void const * argument);
extern void IMU_TIMER_FCN(void const * argument);
extern void COORDINADOR_TIMER_FCN(void const * argument);
extern void AHRS_TIMER_FCN(void const * argument);
extern void COMPASS_TIMER_FCN(void const * argument);
extern void ALTURA_TIMER_FCN(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

