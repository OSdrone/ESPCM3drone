/*
 * TASK_IMU.c
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#include "TASK_IMU.h"

static q15_t CoeficientesFiltroVelocidad[5*NUM_ETAPAS_FILTRO_VEL_ANG] =  COEF_FILTRO_VEL_VALUES;
static q15_t EstadoFiltroVelocidad [4*NUM_ETAPAS_FILTRO_VEL_ANG][3];
static arm_biquad_casd_df1_inst_q15 FiltroVelocidad[3] = {
		{NUM_ETAPAS_FILTRO_VEL_ANG, &EstadoFiltroVelocidad[0][0], CoeficientesFiltroVelocidad, SHIFT_FILTRO_VELOCIDAD},
		{NUM_ETAPAS_FILTRO_VEL_ANG, &EstadoFiltroVelocidad[0][1], CoeficientesFiltroVelocidad, SHIFT_FILTRO_VELOCIDAD},
		{NUM_ETAPAS_FILTRO_VEL_ANG, &EstadoFiltroVelocidad[0][2], CoeficientesFiltroVelocidad, SHIFT_FILTRO_VELOCIDAD}
};

static q15_t CoeficientesFiltroAceleracion[5*NUM_ETAPAS_FILTRO_ACEL_ANG] =  COEF_FILTRO_ACEL_VALUES;
static q15_t EstadoFiltroVelocidadAceleracion [4*NUM_ETAPAS_FILTRO_ACEL_ANG][3];
static arm_biquad_casd_df1_inst_q15 FiltroAceleracion[3] = {
		{NUM_ETAPAS_FILTRO_VEL_ANG, &EstadoFiltroVelocidadAceleracion[0][0], CoeficientesFiltroAceleracion, SHIFT_FILTRO_ACEL},
		{NUM_ETAPAS_FILTRO_VEL_ANG, &EstadoFiltroVelocidadAceleracion[0][1], CoeficientesFiltroAceleracion, SHIFT_FILTRO_ACEL},
		{NUM_ETAPAS_FILTRO_VEL_ANG, &EstadoFiltroVelocidadAceleracion[0][2], CoeficientesFiltroAceleracion, SHIFT_FILTRO_ACEL}
};

void IMU_TASK_FCN(void const * argument){
	tpLecturasIMU LecturasIMU;
	const uint8_t BufferSalida[] = {IMU_MPU6050_ACCEL_XOUT_H};
	uint8_t DatosLeidos[14];

	while(1){
		xSemaphoreTake(IMU_SMPHRHandle, portMAX_DELAY);
		HAL_I2C_Master_Transmit(&hi2c2, IMU9250.Direccion_IMU, (uint8_t*)BufferSalida, 1, 100);
		HAL_I2C_Master_Receive_DMA_MUTEX(&hi2c2, IMU9250.Direccion_IMU, DatosLeidos, 14);

		//Ordenar datos si se precisa
		LecturasIMU.x_acel = ((uint16_t)DatosLeidos[0])<<8 | DatosLeidos[1];
		LecturasIMU.y_acel = ((uint16_t)DatosLeidos[2])<<8 | DatosLeidos[3];
		LecturasIMU.z_acel = ((uint16_t)DatosLeidos[4])<<8 | DatosLeidos[5];

		LecturasIMU.temp = ((uint16_t)DatosLeidos[6])<<8 | DatosLeidos[7];

		LecturasIMU.x_vel = (int16_t)(((uint16_t)DatosLeidos[8])<<8 | DatosLeidos[9]);
		LecturasIMU.x_vel -= CalibracionIMU9DOF.Media_Vel_x;
		LecturasIMU.y_vel = ((uint16_t)DatosLeidos[10])<<8 | DatosLeidos[11];
		LecturasIMU.y_vel -= CalibracionIMU9DOF.Media_Vel_y;
		LecturasIMU.z_vel = ((uint16_t)DatosLeidos[12])<<8 | DatosLeidos[13];
		LecturasIMU.z_vel -= CalibracionIMU9DOF.Media_Vel_z;

		arm_biquad_cascade_df1_q15(&FiltroAceleracion[0], &LecturasIMU.x_acel, &LecturasIMU.x_acel, 1);
		arm_biquad_cascade_df1_q15(&FiltroAceleracion[1], &LecturasIMU.y_acel, &LecturasIMU.y_acel, 1);
		arm_biquad_cascade_df1_q15(&FiltroAceleracion[2], &LecturasIMU.z_acel, &LecturasIMU.z_acel, 1);

		arm_biquad_cascade_df1_q15(&FiltroVelocidad[0], &LecturasIMU.x_vel, &LecturasIMU.x_vel, 1);
		arm_biquad_cascade_df1_q15(&FiltroVelocidad[1], &LecturasIMU.y_vel, &LecturasIMU.y_vel, 1);
		arm_biquad_cascade_df1_q15(&FiltroVelocidad[2], &LecturasIMU.z_vel, &LecturasIMU.z_vel, 1);

		EscribirLecturasIMU(&LecturasIMU);
	}
}

void IMU_TIMER_FCN(void const * argument){
	xSemaphoreGive(IMU_SMPHRHandle);
}
