/*
 * TASK_COMPASS.h
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#ifndef FUNCIONESRTOS_TASK_COMPASS_H_
#define FUNCIONESRTOS_TASK_COMPASS_H_

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "IMU_9DOF.h"
#include "i2c.h"
#include "Constantes.h"
#include "ServidoresVariables.h"

extern osSemaphoreId COMPASS_SMPHRHandle;

extern tpIMU9250 IMU9250;
extern tpCalibracionIMU9DOF CalibracionIMU9DOF;

extern QueueHandle_t MagLecturasCola_Handle;;

void COMPASS_TASK_FCN(void const * argument);
void COMPASS_TIMER_FCN(void const * argument);

#endif /* FUNCIONESRTOS_TASK_COMPASS_H_ */
