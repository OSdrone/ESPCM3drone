/*
 * ServidoresVariables.h
 *
 *  Created on: 12 de oct. de 2016
 *      Author: Ruben
 */

#ifndef SERVIDORESVARIABLES_H_
#define SERVIDORESVARIABLES_H_

#include "arm_math.h"
#include "cmsis_os.h"
#include "Constantes.h"
#include "AHRS.h"
#include "IMU_9DOF.h"

void IniciarServidoresVariables();

void LeerVariablesEstado_Q16(q15_t VariablesEstado[NUM_VAR_ESTADO]);
void EscribirVariablesEstado_Q16(q15_t VariablesEstado[NUM_VAR_ESTADO]);

void LeerLecturasIMU9DOF(tpLecturas9DOFIMU *Lecturas9DOFIMU);
void EscribirLecturasIMU(tpLecturasIMU *LecturasIMU);
void EscribirLecturasBrujulas(tpLecturasBrujula *LecturasBrujula);

void LeerVariableAHRS_Orientacion_q15(tpOrientacionAHRS* OrientacionAHRS);
void EscribirVariableAHRS_Orientacion_q15(tpOrientacionAHRS* OrientacionAHRS);
void LeerRollPitchYaw(q15_t Roll, q15_t Pitch, q15_t Yaw);

void LeerOrientacionMagnetica(q31_t* OrientacionMagnetica);
void EscribirOrientacionMagnetica(q31_t OrientacionMagnetica);

void LeerReferencia(q15_t* Referencia, uint8_t numero);
void EscribirReferencia(q15_t* Referencia, uint8_t numero);

#endif /* SERVIDORESVARIABLES_H_ */
