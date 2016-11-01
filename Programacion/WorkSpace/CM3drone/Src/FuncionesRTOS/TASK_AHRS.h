/*
 * TASK_AHRS.h
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "../AHRS.h"

#ifndef FUNCIONESRTOS_TASK_AHRS_H_
#define FUNCIONESRTOS_TASK_AHRS_H_

extern osSemaphoreId AHRS_SMPHRHandle;

void AHRS_TASK_FCN(void const * argument);
void AHRS_TIMER_FCN(void const * argument);

void ResetAHRS();
void setAHRS(tpAHRS *AHRS);

#endif /* FUNCIONESRTOS_TASK_AHRS_H_ */