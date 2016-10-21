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

	uint16_t SensibilidadGiroscopo; // bits/ (grados / s)
	float32_t Periodo_Muestreo; //s

	q15_t Kp_Roll_Pitch;
	q15_t Ki_Roll_Pitch;
	q15_t Kp_Yaw;
	q15_t Ki_Yaw;

	q15_t Correccion_Proporcional[3];
	q15_t Correccion_Integral[3];
}tpAHRS_Config;

typedef struct{
	q15_t OrientacionMagnetica;
	q15_t Roll;
	q15_t Pitch;
	q15_t Yaw;

	q15_t DCM_matriz[3][3];
	arm_matrix_instance_q15 DCM;
}tpAHRS_Orientacion;

/*
typedef struct{
	q15_t Vector_Velocidad_Angular[3]; //
	q15_t Vector_Aceleracion_lineal[3];	//  m/s^2
	q15_t Vector_Magnetico[3]; //mT ??
};
*/
typedef struct{
	tpAHRS_Orientacion AHRS_Orientacion;
	tpAHRS_Config AHRS_Config;
}tpAHRS;


void Compensacion_Sensor_magnetico(tpAHRS *AHRS, q15_t VectorMagnetico[3]);
//void Actualizar_Matriz_DCM(tpAHRS *AHRS, q15_t VelocidadAngular[3]);
void Actualizar_Matriz_DCM_V2(tpAHRS *AHRS, q15_t VelocidadAngular[3]);
void Normalizar_DCM(tpAHRS *AHRS);
void Correccion_deriva(tpAHRS *AHRS, q15_t AceleracionLineal[3]);
void Angulos_Euler(tpAHRS *AHRS);

//void Algortimo_DCM(tpAHRS *AHRS);

//void ResetDCM();

#endif //AHRS_H_
