/*
 * FuncionIMU.c
 *
 *  Created on: 14 de oct. de 2016
 *      Author: DTUser
 */

#include "Funciones_RTOS.h"
#include "../ServidoresVariables.h"
#include "../Dispositivos/IMU.h"

void IMU_TASK_FCN(void const * argument) {
	tpI
	while (1) {
		xSemaphoreTask(IMU_SMPHRHandle, portMAX_DELAY);

	}

}

void IMU_TIMER_FCN(void const * argument) {
	xSemaphoreGive(IMU_SMPHRHandle);
}

