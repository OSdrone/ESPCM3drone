/*
 * TASK_IMU.h
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#ifndef FUNCIONESRTOS_TASK_IMU_H_
#define FUNCIONESRTOS_TASK_IMU_H_

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "Dispositivos/IMU_9DOF.h"
#include "i2c.h"

extern osSemaphoreId IMU_SMPHRHandle;

void IMU_TASK_FCN(void const * argument);
void IMU_TIMER_FCN(void const * argument);

#endif /* FUNCIONESRTOS_TASK_IMU_H_ */
