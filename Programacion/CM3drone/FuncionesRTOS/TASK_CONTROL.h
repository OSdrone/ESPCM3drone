/*
 * TASK_CONTROL.h
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#ifndef FUNCIONESRTOS_TASK_CONTROL_H_
#define FUNCIONESRTOS_TASK_CONTROL_H_

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "arm_math.h"
//#include "OSmath.h"
#include "ServidoresVariables.h"
#include "tim.h"

extern osSemaphoreId CONTROL_SMPHRHandle;
//extern TIM_HandleTypeDef htim3;
//extern TIM_HandleTypeDef htim4;

//#define TIM_CHANNEL_1                      ((uint32_t)0x0000)
//#define TIM_CHANNEL_2                      ((uint32_t)0x0004)
//#define TIM_CHANNEL_3                      ((uint32_t)0x0008)
//#define TIM_CHANNEL_4                      ((uint32_t)0x000C)
//#define TIM_CHANNEL_ALL                    ((uint32_t)0x0018)

void CONTROL_TASK_FCN(void const * argument);
void CONTROL_TIMER_FCN(void const * argument);
#endif /* FUNCIONESRTOS_TASK_CONTROL_H_ */
