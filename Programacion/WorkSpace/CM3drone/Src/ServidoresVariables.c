/*
 * ServidoresVariables.c
 *
 *  Created on: 12 de oct. de 2016
 *      Author: Ruben
 */

#include "ServidoresVariables.h"

/*  MUTEX  */
osMutexId MutexVariablesEstado;

/*  VARIABLES ALMACENADAS  */
static q15_t VariablesEstadoAlmacenadas[NUM_VAR_ESTADO];

void IniciarServidoresVariables(){
	MutexVariablesEstado = xSemaphoreCreateMutex();
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