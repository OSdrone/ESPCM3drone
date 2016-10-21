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

	static tpAHRS AHRS;
	static tpLecturas9DOFIMU Lecturas9DOFIMU;

	static q15_t VelocidadAngular[3];
	//TODO Configurar AHRS

	while (1) {
		xSemaphoreTake(AHRS_SMPHRHandle, portMAX_DELAY);

		LeerLecturasIMU9DOF(&Lecturas9DOFIMU);
		LeerVariableAHRS_Orientacion_q15(&AHRS.AHRS_Orientacion);

		//Pasamos a velocidad
		VelocidadAngular[0] = (Lecturas9DOFIMU.LecturasIMU.x_vel<<15)/AHRS.AHRS_Config.SensibilidadGiroscopo; //TODO Reviasr unidades
		VelocidadAngular[1] = (Lecturas9DOFIMU.LecturasIMU.y_vel<<15)/AHRS.AHRS_Config.SensibilidadGiroscopo; //TODO Reviasr unidades
		VelocidadAngular[2] = (Lecturas9DOFIMU.LecturasIMU.z_vel<<15)/AHRS.AHRS_Config.SensibilidadGiroscopo; //TODO Reviasr unidades

		//Ejecutamos Algoritmo
		Compensacion_Sensor_magnetico(&AHRS, (q15_t*)&Lecturas9DOFIMU.LecturasBrujula);
		Actualizar_Matriz_DCM_V2(&AHRS, VelocidadAngular);
		Normalizar_DCM(&AHRS);
		Correccion_deriva(&AHRS, (q15_t*)&Lecturas9DOFIMU.LecturasIMU.x_acel);
		Angulos_Euler(&AHRS);

		//Almacenamos resultados
		EscribirVariableAHRS_Orientacion_q15(&AHRS.AHRS_Orientacion);
	}
}

void AHRS_TIMER_FCN(void const * argument) {
	xSemaphoreGive(AHRS_SMPHRHandle);
}
