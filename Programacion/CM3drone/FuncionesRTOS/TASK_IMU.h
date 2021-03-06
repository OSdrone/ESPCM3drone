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
#include "IMU_9DOF.h"
#include "i2c.h"
#include "Constantes.h"
#include "ServidoresVariables.h"
#include "arm_math.h"

extern osSemaphoreId IMU_SMPHRHandle;

extern tpIMU9250 IMU9250;
extern tpCalibracionIMU9DOF CalibracionIMU9DOF;

extern QueueHandle_t AcelLecturasCola_Handle;
extern QueueHandle_t VelLecturasCola_Handle;

void IMU_TASK_FCN(void const * argument);
void IMU_TIMER_FCN(void const * argument);

#endif /* FUNCIONESRTOS_TASK_IMU_H_ */
