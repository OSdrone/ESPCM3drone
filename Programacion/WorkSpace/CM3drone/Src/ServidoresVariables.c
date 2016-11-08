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
static osMutexId MutexOrientacionMagnetica;
static osMutexId MutexReferencia;

/*  VARIABLES ALMACENADAS  */

static tpLecturas9DOFIMU Lecturas9DOFIMUAlmacenadas;
static q15_t VariablesEstadoAlmacenadas[NUM_VAR_ESTADO];
static tpOrientacionAHRS OrientacionAHRS_q15Almacenado;
static q31_t OrientacionMagneticaAlmacenada = 0;
static q15_t ReferenciaAlmacenada[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void IniciarServidoresVariables(){
	MutexVariablesEstado = xSemaphoreCreateMutex();
	MutexAHRS_Orientacion_q15 = xSemaphoreCreateMutex();
	MutexLecturas9DOFIMU = xSemaphoreCreateMutex();
	MutexOrientacionMagnetica = xSemaphoreCreateMutex();
	MutexReferencia = xSemaphoreCreateMutex();
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

void EscribirLecturasIMU(tpLecturasIMU *LecturasIMU){

	xSemaphoreTake(MutexLecturas9DOFIMU, portMAX_DELAY);
	memcpy(&Lecturas9DOFIMUAlmacenadas.LecturasIMU, LecturasIMU, sizeof(tpLecturasIMU));
	xSemaphoreGive(MutexLecturas9DOFIMU);
}

void EscribirLecturasBrujulas(tpLecturasBrujula* LecturasBrujula){

	xSemaphoreTake(MutexLecturas9DOFIMU, portMAX_DELAY);
	memcpy(&Lecturas9DOFIMUAlmacenadas.LecturasBrujula, LecturasBrujula, sizeof(tpLecturasBrujula));
	xSemaphoreGive(MutexLecturas9DOFIMU);
}


void LeerVariableAHRS_Orientacion_q15(tpOrientacionAHRS* OrientacionAHRS_q15){
	xSemaphoreTake(MutexAHRS_Orientacion_q15, portMAX_DELAY);
	memcpy(OrientacionAHRS_q15, &OrientacionAHRS_q15Almacenado, sizeof(OrientacionAHRS_q15Almacenado));
	xSemaphoreGive(MutexAHRS_Orientacion_q15);
}

void EscribirVariableAHRS_Orientacion_q15(tpOrientacionAHRS* OrientacionAHRS_q15){
	xSemaphoreTake(MutexAHRS_Orientacion_q15, portMAX_DELAY);
	memcpy(&OrientacionAHRS_q15Almacenado, OrientacionAHRS_q15, sizeof(OrientacionAHRS_q15Almacenado));
	xSemaphoreGive(MutexAHRS_Orientacion_q15);
}

void LeerRollPitchYaw(q15_t Roll, q15_t Pitch, q15_t Yaw){
	xSemaphoreTake(MutexAHRS_Orientacion_q15, portMAX_DELAY);
	Roll = OrientacionAHRS_q15Almacenado.Roll;
	Pitch = OrientacionAHRS_q15Almacenado.Pitch;
	Yaw = OrientacionAHRS_q15Almacenado.Yaw;
	xSemaphoreGive(MutexAHRS_Orientacion_q15);
}

void LeerOrientacionMagnetica(q31_t OrientacionMagnetica){
	xSemaphoreTake(MutexOrientacionMagnetica, portMAX_DELAY);
	OrientacionMagnetica = OrientacionMagneticaAlmacenada;
	xSemaphoreGive(MutexOrientacionMagnetica);
}

void EscribirOrientacionMagnetica(q31_t OrientacionMagnetica){
	xSemaphoreTake(MutexOrientacionMagnetica, portMAX_DELAY);
	OrientacionMagneticaAlmacenada = OrientacionMagnetica;
	xSemaphoreGive(MutexOrientacionMagnetica);
}

void LeerReferencia(q15_t* Referencia, uint8_t numero){
	xSemaphoreTake(MutexReferencia, portMAX_DELAY);
	memcpy(Referencia, ReferenciaAlmacenada, 2*numero);
	xSemaphoreGive(MutexReferencia);
}

void EscribirReferencia(q15_t* Referencia, uint8_t numero){
	xSemaphoreTake(MutexReferencia, portMAX_DELAY);
	memcpy(ReferenciaAlmacenada, Referencia, 2*numero);
	xSemaphoreGive(MutexReferencia);
}
