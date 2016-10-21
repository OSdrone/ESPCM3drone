/*
 * FuncionAHRS.c
 *
 *  Created on: 13 de oct. de 2016
 *      Author: DTUser
 */

#include "Funciones_RTOS.h"
#include "../AHRS.h"
#include "../ServidoresVariables.h"

void AHRS_TASK_FCN(void const * argument) {

	while (1) {
		xSemaphoreTask(AHRS_SMPHRHandle, portMAX_DELAY);
	}
}

void AHRS_TIMER_FCN(void const * argument) {
	xSemaphoreGive(AHRS_SMPHRHandle);
}
