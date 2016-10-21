#include "Funciones_RTOS.h"

void IMU_TASK_FCN(void const * argument){


	osSemaphoreId SEMPH_RecepcionDatos;

	SEMPH_RecepcionDatos = xSemaphoreCreateBinary();

	//TODO Configurar DMA
	while(1){
		xSemaphoreTake(IMU_SMPHRHandle, portMAX_DELAY);


		xSemaphoreTake(I2C_2_MUTEXHandle, portMAX_DELAY);
		//TODO Lanzar DMA

		xSemaphoreTake(SEMPH_RecepcionDatos, portMAX_DELAY);
	}
}

void IMU_TIMER_FCN(void const * argument){
	xSemaphoreGive(IMU_SMPHRHandle);
}
