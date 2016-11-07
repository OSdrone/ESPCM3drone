/*
 * TASK_IMU.c
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#include "TASK_IMU.h"


void IMU_TASK_FCN(void const * argument){
	uint8_t DatosLeidos[14];

	while(1){
		xSemaphoreTake(IMU_SMPHRHandle, portMAX_DELAY);
		HAL_I2C_Master_Receive_DMA_MUTEX(&hi2c2, IMU9250.Direccion_IMU, DatosLeidos, 14);
	}
}

void IMU_TIMER_FCN(void const * argument){
	xSemaphoreGive(IMU_SMPHRHandle);
}
