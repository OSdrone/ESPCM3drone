/*
 * AHRS.h

 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#include "arm_math.h"
#include "OSmath.h"

#ifndef AHRS_H_
#define AHRS_H_

typedef struct{
	q16_t TiempoMuestreo;

	q15_t Kp_Roll_Pitch;
	q15_t Ki_Roll_Pitch;
	q15_t Kp_Yaw;
	q15_t Ki_Yaw;

	q11_4_t Correccion_Proporcional[3];
	q11_4_t Correccion_Integral[3];
}tpConfiguracionAHRS;

typedef struct{
	q15_t Roll;
	q15_t Pitch;
	q15_t Yaw;

	q15_t DCM_matriz[3][3];
	arm_matrix_instance_q15 DCM;
}tpOrientacionAHRS;

typedef struct{
	tpConfiguracionAHRS ConfiguracionAHRS;
	tpOrientacionAHRS OrientacionAHRS;
}tpAHRS;

q15_t Compensacion_Sensor_magnetico(q15_t Roll, q15_t Pitch, int16_t VectorMagnetico[3]);
void Actualizar_Matriz_DCM_V2(tpAHRS *AHRS, q11_4_t VelocidadAngular[3]);
void Normalizar_DCM(tpAHRS *AHRS);
void Correccion_deriva(tpAHRS *AHRS, int16_t AceleracionLineal[3]);
void Angulos_Euler(tpAHRS *AHRS);

#endif /* AHRS_H_ */