/*
 * TASK_COMPASS.c
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#include "TASK_COMPASS.h"


void COMPASS_TASK_FCN(void const * argument){
	tpLecturasBrujula LecturasBrujula;
	const uint8_t BufferSalida[] = {IMU_MPU9250_MAG_HXL};
	uint8_t DatosLeidos[6];

//	int16_t LecturaOrientada_matriz[3];
	arm_matrix_instance_q15 LecturaOrientada = {3, 1, &LecturasBrujula.x_mag};
	int16_t Lectura_matriz[3];
	arm_matrix_instance_q15 Lectura = {3, 1, Lectura_matriz};

	while(1){
		xSemaphoreTake(COMPASS_SMPHRHandle, portMAX_DELAY);

		MandarDatosI2C(&hi2c2, IMU9250.Direccion_MAG , (uint8_t*)BufferSalida, DatosLeidos, 1, 6);
		//Ordenar datos si se precisa
		Lectura_matriz[0] = (int16_t)((uint16_t)DatosLeidos[0])<<8 | DatosLeidos[1];
		Lectura_matriz[1] = (int16_t)((uint16_t)DatosLeidos[2])<<8 | DatosLeidos[3];
		Lectura_matriz[2] = (int16_t)((uint16_t)DatosLeidos[4])<<8 | DatosLeidos[5];

		//Cola para otras tareas
		xQueueOverwrite(MagLecturasCola_Handle, Lectura_matriz);

		//Alinear
		arm_mat_mult_q15(&CalibracionIMU9DOF.Correccion_Alineamiento_IMU,
				&Lectura, &LecturaOrientada, NULL);

		//TODO Filtrar

		EscribirLecturasBrujulas(&LecturasBrujula);
	}
}

void COMPASS_TIMER_FCN(void const * argument){
	xSemaphoreGive(COMPASS_SMPHRHandle);
}
