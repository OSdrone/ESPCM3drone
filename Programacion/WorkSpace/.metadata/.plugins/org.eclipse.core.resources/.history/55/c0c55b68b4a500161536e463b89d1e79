/*
 * IMU.c
 *
 *  Created on: 14 de oct. de 2016
 *      Author: DTUser
 */

#include "IMU_9DOF.h"

static tpCalibracionIMU9DOF CalibracionIMU9DOFInterna;
tpIMU9250 IMU9250;

void LeerCalibracionSensor(tpCalibracionIMU9DOF *CalibracionIMU9DOF){
	memcpy(CalibracionIMU9DOF, &CalibracionIMU9DOFInterna, sizeof(tpCalibracionIMU9DOF));
}
