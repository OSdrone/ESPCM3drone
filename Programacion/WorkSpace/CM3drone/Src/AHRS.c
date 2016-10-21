/*
 * AHRS.c
 *
 *  Created on: 13 de oct. de 2016
 *      Author: DTUser
 */
/*
 * AHRS.c
 *
 *  Created on: 22/12/2015
 *      Author: Ruben
 */
#include "AHRS.h"
#include "Dispositivos/IMU.h"

void Compensacion_Sensor_magnetico(tpAHRS *AHRS, q15_t VectorMagnetico[3]){
	//Rota el eje magnetico para alinearlo con el suelo, usando la ultima referencia ROLL PITCH

	q15_t mag_x;
	q15_t mag_y;

	q15_t cos_roll;
	q15_t sin_roll;
	q15_t cos_pitch;
	q15_t sin_pitch;

	cos_roll = arm_cos_q15(AHRS->AHRS_Orientacion.Roll);
	sin_roll = arm_sin_q15(AHRS->AHRS_Orientacion.Roll);
	cos_pitch = arm_cos_q15(AHRS->AHRS_Orientacion.Pitch);
	sin_pitch = arm_sin_q15(AHRS->AHRS_Orientacion.Pitch);
	//TODO Revisar si es necesarrio desplazar los 15 bits para la multiplicacion, o si lo hace el compilador
	// Rotamos
	mag_x = (q15_t)(((VectorMagnetico[0] * cos_pitch + VectorMagnetico[1] * sin_roll)>>15 * sin_pitch) + ((VectorMagnetico[2] * cos_roll)>>15 * sin_pitch))>>15;
	mag_y = (q15_t)(VectorMagnetico[1] * cos_roll - VectorMagnetico[2] * sin_roll)>>15;
	AHRS->AHRS_Orientacion.OrientacionMagnetica = (atan2(-mag_y, mag_x));
}
/*
void Actualizar_Matriz_DCM(tpAHRS *AHRS){ //TODO
	q15_t Velocidad_Total[3] = {0, 0, 0};

	q15_t Rot_matriz[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	arm_matrix_instance_q15 Rotacion = {3, 3, (q15_t* )Rot_matriz};

	q15_t Aux_matriz[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	arm_matrix_instance_q15 Aux = {3, 3, Aux_matriz};

	Velocidad_Total[0] = (q15_t)(((q31_t)(AHRS->Vector_Velocidad_Angular[0]<<15)) / (q31_t)AHRS->SensibilidadGiroscopo) + AHRS->Correccion_Proporcional[0] + AHRS->Correccion_Integral[0];
	Velocidad_Total[1] = (q15_t)(((q31_t)(AHRS->Vector_Velocidad_Angular[1]<<15)) / (q31_t)AHRS->SensibilidadGiroscopo) + AHRS->Correccion_Proporcional[1] + AHRS->Correccion_Integral[1];
	Velocidad_Total[2] = (q15_t)(((q31_t)(AHRS->Vector_Velocidad_Angular[2]<<15)) / (q31_t)AHRS->SensibilidadGiroscopo) + AHRS->Correccion_Proporcional[2] + AHRS->Correccion_Integral[2];

	Rot_matriz[0][0] =  32767;
	Rot_matriz[0][1] = -AHRS->Periodo_Muestreo*Velocidad_Total[2];//-z
	Rot_matriz[0][2] =  AHRS->Periodo_Muestreo*Velocidad_Total[1];//y
	Rot_matriz[1][0] =  AHRS->Periodo_Muestreo*Velocidad_Total[2];//z
	Rot_matriz[1][1] =  32767;
	Rot_matriz[1][2] = -AHRS->Periodo_Muestreo*Velocidad_Total[0];//-x
	Rot_matriz[2][0] = -AHRS->Periodo_Muestreo*Velocidad_Total[1];//-y
	Rot_matriz[2][1] =  AHRS->Periodo_Muestreo*Velocidad_Total[0];//x
	Rot_matriz[2][2] =  32767;

	arm_mat_mult_q15(&AHRS->DCM, &Rotacion, &Aux, NULL);
	arm_copy_q15(Aux.pData, AHRS->DCM.pData, 9);
}
*/

void Actualizar_Matriz_DCM_V2(tpAHRS *AHRS, q15_t VelocidadAngular[3]){
	q15_t Velocidad_Total[3] = {0, 0, 0};
	q15_t Vector_Rotacion[3] = {0, 0, 0};

	q15_t VelocidadAngularTotal = 0;
	q15_t Seno = 0;
	q15_t Coseno = 0;

	q15_t Rot_matriz[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	arm_matrix_instance_q15 Rotacion = {3, 3, (q15_t *)Rot_matriz};
	q15_t Aux_matriz[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	arm_matrix_instance_q15 Aux = {3, 3, (q15_t *)Aux_matriz};

	Velocidad_Total[0] = VelocidadAngular[0] + AHRS->AHRS_Config.Correccion_Proporcional[0] + AHRS->AHRS_Config.Correccion_Integral[0];
	Velocidad_Total[1] = VelocidadAngular[1] + AHRS->AHRS_Config.Correccion_Proporcional[1] + AHRS->AHRS_Config.Correccion_Integral[1];
	Velocidad_Total[2] = VelocidadAngular[2] + AHRS->AHRS_Config.Correccion_Proporcional[2] + AHRS->AHRS_Config.Correccion_Integral[2];

	//Velocidad absoluta
	arm_sqrt_q15(((float32_t)((Velocidad_Total[0]*Velocidad_Total[0])>>15)) + ((float32_t)((Velocidad_Total[1]*Velocidad_Total[1])>>15)) +
			((float32_t)((Velocidad_Total[2]*Velocidad_Total[2])>>15)), &VelocidadAngularTotal);

	//Normalizamos vector rotacion TODO Revisar

	Vector_Rotacion[0] = (((int32_t)Velocidad_Total[0]<<15) / VelocidadAngularTotal);
	Vector_Rotacion[1] = (((int32_t)Velocidad_Total[1]<<15) / VelocidadAngularTotal);
	Vector_Rotacion[2] = (((int32_t)Velocidad_Total[2]<<15) / VelocidadAngularTotal);

	Coseno = arm_cos_f32(VelocidadAngularTotal * AHRS->AHRS_Config.Periodo_Muestreo);
	Seno   = arm_sin_f32(VelocidadAngularTotal * AHRS->AHRS_Config.Periodo_Muestreo);

	Rot_matriz[0][0] = (q15_t)32768*Coseno + (q15_t)((q15_t)(Vector_Rotacion[0]*Vector_Rotacion[0])>>15)*(1 - Coseno);
	Rot_matriz[0][1] = ((q15_t)(Vector_Rotacion[0]*Vector_Rotacion[1])>>15)*(1 - Coseno) - Vector_Rotacion[2]*Seno;
	Rot_matriz[0][2] = ((q15_t)(Vector_Rotacion[0]*Vector_Rotacion[2])>>15)*(1 - Coseno) + Vector_Rotacion[1]*Seno;
	Rot_matriz[1][0] = ((q15_t)(Vector_Rotacion[1]*Vector_Rotacion[0])>>15)*(1 - Coseno) + Vector_Rotacion[2]*Seno;
	Rot_matriz[1][1] = (q15_t)32768*Coseno + ((q15_t)(Vector_Rotacion[1]*Vector_Rotacion[1])>>15)*(1 - Coseno);
	Rot_matriz[1][2] = ((q15_t)(Vector_Rotacion[1]*Vector_Rotacion[2])>>15)*(1 - Coseno) - Vector_Rotacion[0]*Seno;
	Rot_matriz[2][0] = ((q15_t)(Vector_Rotacion[2]*Vector_Rotacion[0])>>15)*(1 - Coseno) - Vector_Rotacion[1]*Seno;
	Rot_matriz[2][1] = ((q15_t)(Vector_Rotacion[2]*Vector_Rotacion[1])>>15)*(1 - Coseno) + Vector_Rotacion[0]*Seno;
	Rot_matriz[2][2] = (q15_t)32768*Coseno + ((q15_t)(Vector_Rotacion[2]*Vector_Rotacion[2]))*(1 - Coseno);

	arm_mat_mult_q15(&AHRS->AHRS_Orientacion.DCM, &Rotacion, &Aux, NULL);
	arm_copy_q15((q15_t *)Aux_matriz, (q15_t *)&AHRS->AHRS_Orientacion.DCM_matriz, 9);
}

void Normalizar_DCM(tpAHRS *AHRS){
	q63_t error = 0;

	q15_t Vector_Aux[3] = {0, 0, 0};
	q15_t Matriz_Ortogonal[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

	arm_dot_prod_q15(&AHRS->AHRS_Orientacion.DCM_matriz[0][0], &AHRS->AHRS_Orientacion.DCM_matriz[1][0], 3, &error);
	error = error>>1;
	error = -error;

	arm_scale_q15(&AHRS->AHRS_Orientacion.DCM_matriz[1][0], error, 15,  Vector_Aux, 3);
	arm_add_q15(&AHRS->AHRS_Orientacion.DCM_matriz[0][0], Vector_Aux,  &Matriz_Ortogonal[0][0], 3); //Vector X ortogonal

	arm_scale_q15(&AHRS->AHRS_Orientacion.DCM_matriz[0][0], error, 15,  Vector_Aux, 3);
	arm_add_q15(&AHRS->AHRS_Orientacion.DCM_matriz[1][0], Vector_Aux,  &Matriz_Ortogonal[1][0], 3); //Vector Y ortogonal

	//Producto Cruz
	Matriz_Ortogonal[2][0] = ((q15_t)(Matriz_Ortogonal[0][1] * Matriz_Ortogonal[1][2])>>15) - ((q15_t)(Matriz_Ortogonal[0][2] * Matriz_Ortogonal[1][1])>>15);
	Matriz_Ortogonal[2][1] = ((q15_t)(Matriz_Ortogonal[0][2] * Matriz_Ortogonal[1][0])>>15) - ((q15_t)(Matriz_Ortogonal[0][0] * Matriz_Ortogonal[1][2])>>15);
	Matriz_Ortogonal[2][2] = ((q15_t)(Matriz_Ortogonal[0][0] * Matriz_Ortogonal[1][1])>>15) - ((q15_t)(Matriz_Ortogonal[0][1] * Matriz_Ortogonal[1][0])>>15);

	arm_dot_prod_q15(&Matriz_Ortogonal[0][0], &Matriz_Ortogonal[0][0], 3, &error);
	error = (q15_t)((error>>1)*(3 - error)>>15);
	arm_scale_q15(&Matriz_Ortogonal[0][0], error, 15, &AHRS->AHRS_Orientacion.DCM_matriz[0][0], 3);

	arm_dot_prod_q15(&Matriz_Ortogonal[1][0], &Matriz_Ortogonal[1][0], 3, &error);
	error = (q15_t)((error>>1)*(3 - error)>>15);
	arm_scale_q15(&Matriz_Ortogonal[1][0], error, 15, &AHRS->AHRS_Orientacion.DCM_matriz[1][0], 3);

	arm_dot_prod_q15(&Matriz_Ortogonal[2][0], &Matriz_Ortogonal[2][0], 3, &error);
	error = (q15_t)((error>>1)*(3 - error)>>15);
	arm_scale_q15(&Matriz_Ortogonal[2][0], error, 15, &AHRS->AHRS_Orientacion.DCM_matriz[2][0], 3);
}

void Correccion_deriva(tpAHRS *AHRS, q15_t AceleracionLineal[3]){
	q15_t error[3] = {0, 0, 0};
	q15_t Aux[3] = {0, 0, 0};

	//ROLL PITCH
	//faltaria filtrar???
	//Producto cruz
	error[0] = ((q15_t)(AceleracionLineal[1] * AHRS->AHRS_Orientacion.DCM_matriz[2][2])>>15) - ((q15_t)(AceleracionLineal[2] * AHRS->AHRS_Orientacion.DCM_matriz[2][1])>>15);
	error[1] = ((q15_t)(AceleracionLineal[2] * AHRS->AHRS_Orientacion.DCM_matriz[2][0])>>15) - ((q15_t)(AceleracionLineal[0] * AHRS->AHRS_Orientacion.DCM_matriz[2][2])>>15);
	error[2] = ((q15_t)(AceleracionLineal[0] * AHRS->AHRS_Orientacion.DCM_matriz[2][1])>>15) - ((q15_t)(AceleracionLineal[1] * AHRS->AHRS_Orientacion.DCM_matriz[2][0])>>15);

	arm_scale_q15(error, AHRS->AHRS_Config.Kp_Roll_Pitch, 15, AHRS->AHRS_Config.Correccion_Proporcional, 3);
	arm_scale_q15(error, AHRS->AHRS_Config.Ki_Roll_Pitch, 15, Aux, 3);
	arm_add_q15(Aux, AHRS->AHRS_Config.Correccion_Integral, AHRS->AHRS_Config.Correccion_Integral, 3);

	//YAW
	arm_scale_q15(&AHRS->AHRS_Orientacion.DCM_matriz[2][0], (q15_t)(AHRS->AHRS_Orientacion.DCM_matriz[0][0]*arm_sin_q15(AHRS->AHRS_Orientacion.OrientacionMagnetica))>>15 -
			(q15_t)(AHRS->AHRS_Orientacion.DCM_matriz[1][0]*arm_cos_q15(AHRS->AHRS_Orientacion.OrientacionMagnetica))>>15 , 15 , error, 3);

	arm_scale_q15(error, AHRS->AHRS_Config.Kp_Yaw, 15, Aux, 3);
	arm_add_q15(Aux, AHRS->AHRS_Config.Correccion_Proporcional, AHRS->AHRS_Config.Correccion_Proporcional, 3);

	arm_scale_q15(error, AHRS->AHRS_Config.Ki_Yaw, 15, Aux, 3);
	arm_add_q15(Aux, AHRS->AHRS_Config.Correccion_Integral, AHRS->AHRS_Config.Correccion_Integral, 3);

}

void Angulos_Euler(tpAHRS *AHRS){
	AHRS->AHRS_Orientacion.Pitch = 32767 * (-asin(AHRS->AHRS_Orientacion.DCM_matriz[2][0]))/PI;
	AHRS->AHRS_Orientacion.Roll =  32767 * ( atan2(AHRS->AHRS_Orientacion.DCM_matriz[2][1],AHRS->AHRS_Orientacion.DCM_matriz[2][2]))/PI;
	AHRS->AHRS_Orientacion.Yaw = 32767 * (atan2(AHRS->AHRS_Orientacion.DCM_matriz[1][0],AHRS->AHRS_Orientacion.DCM_matriz[0][0]))/PI;
}

void ResetDCM(){
	/*
	tpLecturas_IMU Lecturas_IMU = {0, 0, 0, 0, 0, 0, 0 };
	tpLecturas_Brujula Lecturas_Brujula = {0, 0, 0};

	float32_t DCM_matriz[3][3] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
	float32_t Roll = 0;
	float32_t Pitch = 0;
	float32_t Yaw = 0;

	float32_t sin_Roll = 0;
	float32_t cos_Roll = 0;
	float32_t sin_Pitch = 0;
	float32_t cos_Pitch = 0;
	float32_t sin_Yaw = 0;
	float32_t cos_Yaw = 0;

	Leer_servidor_Lecturas_IMU(&Lecturas_IMU);
	Leer_servidor_Lecturas_Brujula(&Lecturas_Brujula);

	Pitch = -atan2(Lecturas_IMU.Valor.x_acel, sqrt(Lecturas_IMU.Valor.y_acel * Lecturas_IMU.Valor.y_acel + Lecturas_IMU.Valor.z_acel * Lecturas_IMU.Valor.z_acel));
	Roll =   atan2(Lecturas_IMU.Valor.y_acel, sqrt(Lecturas_IMU.Valor.x_acel * Lecturas_IMU.Valor.x_acel + Lecturas_IMU.Valor.z_acel * Lecturas_IMU.Valor.z_acel));

	sin_Roll = arm_sin_f32(Roll);
	cos_Roll = arm_cos_f32(Roll);
	sin_Pitch = arm_sin_f32(Pitch);
	cos_Pitch = arm_cos_f32(Pitch);

	Yaw = -atan2( Lecturas_Brujula.Valor.Magnetismo_y * cos_Roll - Lecturas_Brujula.Valor.Magnetismo_z * sin_Roll, Lecturas_Brujula.Valor.Magnetismo_x * cos_Pitch + Lecturas_Brujula.Valor.Magnetismo_y * sin_Roll * sin_Pitch + Lecturas_Brujula.Valor.Magnetismo_z * cos_Roll * sin_Pitch);
	sin_Yaw = arm_sin_f32(Yaw);
	cos_Yaw = arm_cos_f32(Yaw);

	DCM_matriz[0][0] = cos_Pitch*cos_Yaw;
	DCM_matriz[0][1] = cos_Yaw*sin_Roll*sin_Pitch - cos_Roll*sin_Yaw;
	DCM_matriz[0][2] = sin_Roll*sin_Yaw + cos_Roll*cos_Yaw*sin_Pitch;

	DCM_matriz[1][0] = cos_Pitch*sin_Yaw;
	DCM_matriz[1][1] = cos_Roll*cos_Yaw + sin_Roll*sin_Pitch*sin_Yaw;
	DCM_matriz[1][2] = cos_Roll*sin_Pitch*sin_Yaw - cos_Yaw*sin_Roll;

	DCM_matriz[2][0] = -sin_Pitch;
	DCM_matriz[2][1] = cos_Pitch*sin_Roll;
	DCM_matriz[2][2] = cos_Roll*cos_Pitch;

	Escribir_servidor_DCM((float32_t*)DCM_matriz);
	Escribir_servidor_RPY(&Roll, &Pitch, &Yaw);
	*/
}
/*
void Algortimo_DCM(tpAHRS *AHRS){

	Compensacion_Sensor_magnetico(AHRS);
	Actualizar_Matriz_DCM_V2(AHRS);
	Normalizar_DCM(AHRS);
	Correccion_deriva(AHRS);
	Angulos_Euler(AHRS);
}
*/
