/*
 * ServidoresVariables.c
 *
 *  Created on: 12 de oct. de 2016
 *      Author: Ruben
 */

#include "ServidoresVariables.h"

/*  MUTEX  */
static osMutexId MutexLecturas9DOFIMU;
static osMutexId MutexVariablesEstado;
static osMutexId MutexAHRS_Orientacion_q15;

/*  VARIABLES ALMACENADAS  */

static tpLecturas9DOFIMU Lecturas9DOFIMUAlmacenadas;
static q15_t VariablesEstadoAlmacenadas[NUM_VAR_ESTADO];
static tpAHRS_Orientacion AHRS_Orientacion_q15Almacenado;

void IniciarServidoresVariables(){
	MutexVariablesEstado = xSemaphoreCreateMutex();
	MutexAHRS_Orientacion_q15 = xSemaphoreCreateMutex();
	MutexLecturas9DOFIMU = xSemaphoreCreateMutex();
}

void LeerVariablesEstado_Q16(q15_t VariablesEstado[NUM_VAR_ESTADO]){

	xSemaphoreTake(MutexVariablesEstado, portMAX_DELAY);
	memcpy(VariablesEstado, VariablesEstadoAlmacenadas, sizeof(VariablesEstadoAlmacenadas));
	xSemaphoreGive(MutexVariablesEstado);

}

void EscribirVariablesEstado_Q16(q15_t VariablesEstado[NUM_VAR_ESTADO]){

	xSemaphoreTake(MutexVariablesEstado, portMAX_DELAY);
	memcpy(VariablesEstadoAlmacenadas, VariablesEstado, sizeof(VariablesEstadoAlmacenadas));
	xSemaphoreGive(MutexVariablesEstado);
}

void LeerLecturasIMU9DOF(tpLecturas9DOFIMU* Lecturas9DOFIMU){

	xSemaphoreTake(MutexLecturas9DOFIMU, portMAX_DELAY);
	memcpy(Lecturas9DOFIMU, &Lecturas9DOFIMUAlmacenadas, sizeof(Lecturas9DOFIMUAlmacenadas));
	xSemaphoreGive(MutexLecturas9DOFIMU);
}

void EscribirLecturasIMU(tpLecturasIMU* LecturasIMU){

	xSemaphoreTake(MutexLecturas9DOFIMU, portMAX_DELAY);
	memcpy(&Lecturas9DOFIMUAlmacenadas.LecturasIMU, LecturasIMU, sizeof(tpLecturasIMU));
	xSemaphoreGive(MutexLecturas9DOFIMU);
}

void EscribirLecturasBrujulas(tpLecturasBrujula* LecturasBrujula){

	xSemaphoreTake(MutexLecturas9DOFIMU, portMAX_DELAY);
	memcpy(&Lecturas9DOFIMUAlmacenadas.LecturasBrujula, LecturasBrujula, sizeof(tpLecturasBrujula));
	xSemaphoreGive(MutexLecturas9DOFIMU);
}


void LeerVariableAHRS_Orientacion_q15(tpAHRS_Orientacion* AHRS_Orientacion_q15){
	xSemaphoreTake(MutexAHRS_Orientacion_q15, portMAX_DELAY);
	memcpy(AHRS_Orientacion_q15, &AHRS_Orientacion_q15Almacenado, sizeof(AHRS_Orientacion_q15Almacenado));
	xSemaphoreGive(MutexAHRS_Orientacion_q15);
}

void EscribirVariableAHRS_Orientacion_q15(tpAHRS_Orientacion* AHRS_Orientacion_q15){
	xSemaphoreTake(MutexAHRS_Orientacion_q15, portMAX_DELAY);
	memcpy(&AHRS_Orientacion_q15Almacenado, AHRS_Orientacion_q15, sizeof(AHRS_Orientacion_q15Almacenado));
	xSemaphoreGive(MutexAHRS_Orientacion_q15);
}

void LeerRollPitchYaw(q15_t Roll, q15_t Pitch, q15_t Yaw){
	xSemaphoreTake(MutexAHRS_Orientacion_q15, portMAX_DELAY);
	Roll = AHRS_Orientacion_q15Almacenado.Roll;
	Pitch = AHRS_Orientacion_q15Almacenado.Pitch;
	Yaw = AHRS_Orientacion_q15Almacenado.Yaw;
	xSemaphoreGive(MutexAHRS_Orientacion_q15);
}
