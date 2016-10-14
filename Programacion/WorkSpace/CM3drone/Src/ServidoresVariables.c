/*
 * ServidoresVariables.c
 *
 *  Created on: 12 de oct. de 2016
 *      Author: Ruben
 */

#include "ServidoresVariables.h"

/*  MUTEX  */
osMutexId MutexVariablesEstado;
osMutexId MutexAHRS;

/*  VARIABLES ALMACENADAS  */
static q15_t VariablesEstadoAlmacenadas[NUM_VAR_ESTADO];
static tpAHRS AHRSAlmacenado;

void IniciarServidoresVariables(){
	MutexVariablesEstado = xSemaphoreCreateMutex();
	MutexAHRS = xSemaphoreCreateMutex();
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


void LeerVariableAHRS(tpAHRS* AHRS){
	xSemaphoreTake(MutexAHRS, portMAX_DELAY);
	memcpy(AHRS, &AHRSAlmacenado, sizeof(AHRSAlmacenado));
	xSemaphoreGive(MutexAHRS);
}

void EscribirVariableAHRS(tpAHRS* AHRS){
	xSemaphoreTake(MutexAHRS, portMAX_DELAY);
	memcpy(&AHRSAlmacenado, AHRS, sizeof(AHRSAlmacenado));
	xSemaphoreGive(MutexAHRS);
}

void LeerRollPitchYaw(q15_t Roll, q15_t Pitch, q15_t Yaw){
	xSemaphoreTake(MutexAHRS, portMAX_DELAY);
	Roll = AHRSAlmacenado.Roll;
	Pitch = AHRSAlmacenado.Pitch;
	Yaw = AHRSAlmacenado.Yaw;
	xSemaphoreGive(MutexAHRS);
}
