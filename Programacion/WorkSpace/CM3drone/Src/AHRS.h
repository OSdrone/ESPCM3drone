/*
 * AHRS.h
 *
 *  Created on: 13 de oct. de 2016
 *      Author: DTUser
 */

#ifndef AHRS_H_
#define AHRS_H_

#include "arm_math.h"

typedef struct { //tpAHRS
	q15_t DCM_matriz[3][3];
	arm_matrix_instance_q15 DCM;

	float32_t Periodo_Muestreo; //s

	q15_t Vector_Velocidad_Angular[3]; //
	uint16_t SensibilidadGiroscopo; // bits/ (grados / s)
	q15_t Vector_Aceleracion_lineal[3];	//  m/s^2
	q15_t Vector_Magnetico[3]; //mT ??

	q15_t Roll;
	q15_t Pitch;
	q15_t Yaw;

	//Almacecenado de -180 a 180

	q15_t Kp_Roll_Pitch;
	q15_t Ki_Roll_Pitch;
	q15_t Kp_Yaw;
	q15_t Ki_Yaw;

	float32_t Orientacion_Z;
	q15_t Correccion_Proporcional[3];
	q15_t Correccion_Integral[3];

}tpAHRS;

void Compensacion_Sensor_magnetico(tpAHRS *AHRS);
void Actualizar_Matriz_DCM(tpAHRS *AHRS);
void Actualizar_Matriz_DCM_V2(tpAHRS *AHRS);
void Normalizar_DCM(tpAHRS *AHRS);
void Correccion_deriva(tpAHRS *AHRS);
void Angulos_Euler(tpAHRS *AHRS);

void Algortimo_DCM(tpAHRS *AHRS);

void ResetDCM();

#endif //AHRS_H_
