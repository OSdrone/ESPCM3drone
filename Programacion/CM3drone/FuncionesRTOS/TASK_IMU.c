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

	int16_t LecturaOrientada_matriz[3];
	arm_matrix_instance_q15 LecturaOrientada = {3, 1, LecturaOrientada_matriz};
	int16_t Lectura_matriz[3];
	arm_matrix_instance_q15 Lectura = {3, 1, Lectura_matriz};

	while(1){
		xSemaphoreTake(IMU_SMPHRHandle, portMAX_DELAY);

		MandarDatosI2C(&hi2c2, IMU9250.Direccion_IMU , (uint8_t*)BufferSalida, DatosLeidos, 1, 14);

		//..ACELERACION..//
		//Ordenar datos si se precisa
		Lectura_matriz[0] = (int16_t)((uint16_t)DatosLeidos[0])<<8 | DatosLeidos[1];
		Lectura_matriz[1] = (int16_t)((uint16_t)DatosLeidos[2])<<8 | DatosLeidos[3];
		Lectura_matriz[2] = (int16_t)((uint16_t)DatosLeidos[4])<<8 | DatosLeidos[5];

		//Cola para otras tareas
		xQueueOverwrite(AcelLecturasCola_Handle, Lectura_matriz);

		//Alinear
		arm_mat_mult_q15(&CalibracionIMU9DOF.Correccion_Alineamiento_IMU,
				&Lectura, &LecturaOrientada, NULL);
		//Filtrar
		arm_biquad_cascade_df1_q15(&FiltroAceleracion[0], &LecturaOrientada_matriz[0], &LecturasIMU.x_acel, 1);
		arm_biquad_cascade_df1_q15(&FiltroAceleracion[1], &LecturaOrientada_matriz[1], &LecturasIMU.y_acel, 1);
		arm_biquad_cascade_df1_q15(&FiltroAceleracion[2], &LecturaOrientada_matriz[2], &LecturasIMU.z_acel, 1);

		//..VELOCIDAD..//
		//Ordenar datos si se precisa
		Lectura_matriz[0] = (int16_t)(((uint16_t)DatosLeidos[8])<<8 | DatosLeidos[9]);
		Lectura_matriz[1] = (int16_t)((uint16_t)DatosLeidos[10])<<8 | DatosLeidos[11];
		Lectura_matriz[2] = (int16_t)((uint16_t)DatosLeidos[12])<<8 | DatosLeidos[13];

		//Cola para otras tareas
		xQueueOverwrite(VelLecturasCola_Handle, Lectura_matriz);

		//Quitamos el offset
		Lectura_matriz[0] -= CalibracionIMU9DOF.Media_Vel_x;
		Lectura_matriz[1] -= CalibracionIMU9DOF.Media_Vel_y;
		Lectura_matriz[2] -= CalibracionIMU9DOF.Media_Vel_z;

		//Alinear
		arm_mat_mult_q15(&CalibracionIMU9DOF.Correccion_Alineamiento_IMU,
				&Lectura, &LecturaOrientada, NULL);
		//Filtrar
		arm_biquad_cascade_df1_q15(&FiltroVelocidad[0], &LecturaOrientada_matriz[0], &LecturasIMU.x_vel, 1);
		arm_biquad_cascade_df1_q15(&FiltroVelocidad[1], &LecturaOrientada_matriz[1], &LecturasIMU.y_vel, 1);
		arm_biquad_cascade_df1_q15(&FiltroVelocidad[2], &LecturaOrientada_matriz[2], &LecturasIMU.z_vel, 1);

		//TEMPERATURA //TODO algortimo de medida de la temp
		LecturasIMU.temp = ((uint16_t)DatosLeidos[6])<<8 | DatosLeidos[7];

		EscribirLecturasIMU(&LecturasIMU);
	}
}

void IMU_TIMER_FCN(void const * argument){
	xSemaphoreGive(IMU_SMPHRHandle);
}
