/*
 * IMU.c
 *
 *  Created on: 14 de oct. de 2016
 *      Author: DTUser
 */

#include "IMU_9DOF.h"

static tpCalibracionIMU9DOF CalibracionIMU9DOF;
tpIMU9250 IMU9250;

tpCalibracionIMU9DOF LeerCalibracionSensor(){
	return CalibracionIMU9DOF;
}

int16_t LeerOffsetGyro_X(){
	return CalibracionIMU9DOF.Des_est_Vel_x;
}

int16_t LeerOffsetGyro_Y(){
	return CalibracionIMU9DOF.Des_est_Vel_y;
}

int16_t LeerOffsetGyro_Z(){
	return CalibracionIMU9DOF.Des_est_Vel_z;
}

//int16_t LeerSensibilidadGiroscopo(){
//	return IMU9250.Sensibilidad_Giroscopo;
//}
