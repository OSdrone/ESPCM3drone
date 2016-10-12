#include "Funciones_RTOS.h"
#include "../ServidoresVariables.h"

void CONTROL_TASK_FCN(void const * argument){

	//Accion = (Kp + Ki/(1-z^-1))Error + Kd(1-z^-1)Pos



	//TODO Constantes desde memoria FLASH para poder ser ajustada sin reflashear
	q15_t Kp[4] = {2200, 2, 2, 4}; //Ajustar
	q15_t Kv[4] = {2, 2, 2, 4}; //Ajustar
	q15_t Ki[4] = {2, 2, 2, 4}; //Ajustar

	q15_t Accion[4] = { 0, 0, 0, 0};
	//uint16_t AccionMotor[4] = { 0, 0, 0, 0};

	q15_t Referencia[4] = { 0, 0, 0, 0};
	q15_t Posicion[4][3] = { 0, 0, 0, 0};
	q15_t Error[4][2];

	q15_t VariablesEstado[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	while(1){
		xSemaphoreTake(CONTROL_SMPHRHandle, portMAX_DELAY);

		/* Leer Ref */
		Posicion[0][2] = Posicion[0][1];
		Posicion[0][1] = Posicion[0][0];
		Posicion[1][2] = Posicion[1][1];
		Posicion[1][1] = Posicion[1][0];
		Posicion[2][2] = Posicion[2][1];
		Posicion[2][1] = Posicion[2][0];
		Posicion[3][2] = Posicion[3][1];
		Posicion[3][1] = Posicion[3][0];

		//TODO Leer posicion
		LeerVariablesEstado_Q16(VariablesEstado);
		Posicion[0][0] = VariablesEstado[1];
		Posicion[1][0] = VariablesEstado[3];
		Posicion[2][0] = VariablesEstado[5];

		//TODO Leer Altura

		//PI-D Eje 0

		Error[0][1] = Error[0][0];
		Error[0][0] = Referencia[0] - Posicion[0][0];

		Accion[0] += (Kp[0] * (Error[0][0] - Error[0][1]));
		Accion[0] += (Kv[0] * (Posicion[0][0] - ((int32_t)Posicion[0][1] << 1) + Posicion[0][2]));
		Accion[0] += (Ki[0] * Error[0][0]);

		//PI-D Eje 1

		Error[1][1] = Error[1][0];
		Error[1][0] = Referencia[1] - Posicion[1][0];

		Accion[1] += (Kp[1] * (Error[1][0] - Error[1][1]));
		Accion[1] += (Kv[1] * (Posicion[1][0] - ((int32_t)Posicion[1][1] << 1) + Posicion[1][2]));
		Accion[1] += (Ki[1] * Error[1][0]);

		//PI-D Eje 2

		Error[2][1] = Error[2][0];
		Error[2][0] = Referencia[2] - Posicion[2][0];

		Accion[2] += (Kp[2] * (Error[2][0] - Error[2][1]));
		Accion[2] += (Kv[2] * (Posicion[2][0] - ((int32_t)Posicion[2][1] << 1) + Posicion[2][2]));
		Accion[2] += (Ki[2] * Error[1][0]);

		//PI-D Eje 3

		Error[3][1] = Error[3][0];
		Error[3][0] = Referencia[3] - Posicion[3][0];

		Accion[3] += (Kp[3] * (Error[3][0] - Error[3][1]));
		Accion[3] += (Kv[3] * (Posicion[3][0] - ((int32_t)Posicion[3][1] << 1) + Posicion[3][2]));
		Accion[3] += (Ki[3] * Error[1][0]);


		__HAL_TIM_SetCompare(htim3, TIM_CHANNEL_1, (Accion[0]>>2 + Accion[1]>>2 + Accion[2]>>2 + Accion[3]>>2));
		__HAL_TIM_SetCompare(htim3, TIM_CHANNEL_2, (Accion[0]>>2 - Accion[1]>>2 - Accion[2]>>2 + Accion[3]>>2));
		__HAL_TIM_SetCompare(htim3, TIM_CHANNEL_3, (Accion[0]>>2 + Accion[1]>>2 + Accion[2]>>2 + Accion[3]>>2));
		__HAL_TIM_SetCompare(htim3, TIM_CHANNEL_4, (Accion[0]>>2 + Accion[1]>>2 + Accion[2]>>2 + Accion[3]>>2));

		/*
		PWM_Dutty[0] =  Accion[0] >> 2 + Accion[1] >> 2 + Accion[2] >> 2 + Accion[3] >> 2;
		PWM_Dutty[1] =  Accion[0] >> 2 - Accion[1] >> 2 - Accion[2] >> 2 + Accion[3] >> 2;
		PWM_Dutty[2] = -Accion[0] >> 2 - Accion[1] >> 2 + Accion[2] >> 2 + Accion[3] >> 2;
		PWM_Dutty[3] = -Accion[0] >> 2 + Accion[1] >> 2 - Accion[2] >> 2 + Accion[3] >> 2;
		 */
	}
}

void CONTROL_TIMER_FCN(void const * argument){
		xSemaphoreGive(CONTROL_SMPHRHandle);
	}