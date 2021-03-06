/*
 * TASK_AHRS.c
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */
#include "TASK_AHRS.h"

	static tpAHRS AHRS;
	static uint16_t SensibilidadGiroscopo;

void AHRS_TASK_FCN(void const * argument) {

	q31_t OrientacionMagnetica = 0;
	q16_4_t VelocidadAngular[3];
	tpLecturas9DOFIMU Lecturas9DOFIMU;

	SensibilidadGiroscopo = Sensibilidad_Giroscopo();
	while(1){
		xSemaphoreTake(AHRS_SMPHRHandle, portMAX_DELAY);

		LeerLecturasIMU9DOF(&Lecturas9DOFIMU);

		OrientacionMagnetica = Compensacion_Sensor_magnetico(AHRS.OrientacionAHRS.Roll,
				AHRS.OrientacionAHRS.Pitch, &Lecturas9DOFIMU.LecturasBrujula.x_mag);

		//Conversion a �/s
		VelocidadAngular[0] = (q16_4_t)(((int32_t)Lecturas9DOFIMU.LecturasIMU.x_vel/SensibilidadGiroscopo)>>12);
		VelocidadAngular[1] = (q16_4_t)(((int32_t)Lecturas9DOFIMU.LecturasIMU.y_vel/SensibilidadGiroscopo)>>12);
		VelocidadAngular[2] = (q16_4_t)(((int32_t)Lecturas9DOFIMU.LecturasIMU.z_vel/SensibilidadGiroscopo)>>12);

		Actualizar_Matriz_DCM_V2(&AHRS, VelocidadAngular);
		Normalizar_DCM(&AHRS);
		Correccion_deriva(&AHRS, (q15_t*)&Lecturas9DOFIMU.LecturasIMU.x_acel, OrientacionMagnetica);
		Angulos_Euler(&AHRS);

		EscribirVariableAHRS_Orientacion_q15(&AHRS.OrientacionAHRS);
		EscribirOrientacionMagnetica(OrientacionMagnetica);
	}
}

void AHRS_TIMER_FCN(void const * argument) {
	xSemaphoreGive(AHRS_SMPHRHandle);
}

void ResetAHRS(){
	AHRS.OrientacionAHRS.Pitch = 0;
	AHRS.OrientacionAHRS.Roll = 0;
	AHRS.OrientacionAHRS.Yaw = 0;

	arm_fill_q15(0, (q15_t*)AHRS.OrientacionAHRS.DCM_matriz, 9);
	AHRS.OrientacionAHRS.DCM_matriz[0][0] = 32767;
	AHRS.OrientacionAHRS.DCM_matriz[1][1] = 32767;
	AHRS.OrientacionAHRS.DCM_matriz[2][2] = 32767;
}
void setAHRS(tpAHRS *AHRSset){
	memcpy(&AHRS, AHRSset, sizeof(tpAHRS));
}
