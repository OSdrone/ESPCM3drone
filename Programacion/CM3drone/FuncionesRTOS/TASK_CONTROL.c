/*
 * TASK_CONTROL.c
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */

#include "TASK_CONTROL.h"

void CONTROL_TASK_FCN(void const * argument){
	//Accion = (Kp + Ki/(1-z^-1))Error + Kd(1-z^-1)Pos
	// o
	//Accion = (Kp + Ki/(1-z^-1))Error + Kd(Vel)

	//TODO Constantes desde memoria FLASH para poder ser ajustada sin reflashear
	q15_t Kp[4] = {2200, 2, 2, 4}; //Ajustar
	q15_t Kd[4] = {2, 2, 2, 4}; //Ajustar
	q15_t Ki[4] = {2, 2, 2, 4}; //Ajustar

	//q15_t Accion[4] = { 0, 0, 0, 0};
	uint16_t Accion[4] = { 0, 0, 0, 0};

	q15_t Referencia[4];
	q15_t Posicion[4][3];
	q15_t Error[4][2];

	arm_fill_q15(0, Referencia, sizeof(Referencia));
	arm_fill_q15(0, (q15_t *)Posicion, sizeof(Posicion));
	arm_fill_q15(0, (q15_t *)Error, sizeof(Error));

	while(1){
		xSemaphoreTake(CONTROL_SMPHRHandle, portMAX_DELAY);

		/* Leer Ref */
		LeerReferencia(Referencia, 4);

		//Posicion Anterior
		Posicion[0][2] = Posicion[0][1];
		Posicion[0][1] = Posicion[0][0];
		Posicion[1][2] = Posicion[1][1];
		Posicion[1][1] = Posicion[1][0];
		Posicion[2][2] = Posicion[2][1];
		Posicion[2][1] = Posicion[2][0];
		Posicion[3][2] = Posicion[3][1];
		Posicion[3][1] = Posicion[3][0];

		//TODO Leer posicion
		LeerRollPitchYaw(Posicion[0][0], Posicion[1][0], Posicion[2][0]);

		//TODO Leer Altura

		//PI-D Eje 0
		Error[0][1] = Error[0][0];
		Error[0][0] = Referencia[0] - Posicion[0][0];

		Accion[0] = ((int32_t)Kp[0] * (Error[0][0] - Error[0][1]))>>(15-SHIFT_K_CONTROL);
		Accion[0] +=((int32_t)Kd[0] *
				((int32_t)Posicion[0][0] - ((int32_t)Posicion[0][1] << 1) + Posicion[0][2]))>>(15-SHIFT_K_CONTROL);
		Accion[0] += ((int32_t)Ki[0] * Error[0][0])>>(15-SHIFT_K_CONTROL);

		//PI-D Eje 1
		Error[1][1] = Error[1][0];
		Error[1][0] = Referencia[1] - Posicion[1][0];

		Accion[1] = ((int32_t)Kp[1] * (Error[1][0] - Error[1][1]))>>(15-SHIFT_K_CONTROL);
		Accion[1] +=((int32_t)Kd[1] *
				((int32_t)Posicion[1][0] - ((int32_t)Posicion[1][1] << 1) + Posicion[1][2]))>>(15-SHIFT_K_CONTROL);
		Accion[1] += ((int32_t)Ki[1] * Error[1][0])>>(15-SHIFT_K_CONTROL);

		//PI-D Eje 2
		Error[2][1] = Error[2][0];
		Error[2][0] = Referencia[2] - Posicion[2][0];

		Accion[2] = ((int32_t)Kp[2] * (Error[2][0] - Error[2][1]))>>(15-SHIFT_K_CONTROL);
		Accion[2] +=((int32_t)Kd[2] *
				((int32_t)Posicion[2][0] - ((int32_t)Posicion[2][1] << 1) + Posicion[2][2]))>>(15-SHIFT_K_CONTROL);
		Accion[2] += ((int32_t)Ki[2] * Error[2][0])>>(15-SHIFT_K_CONTROL);

		//PI-D Eje 3
		Error[3][1] = Error[3][0];
		Error[3][0] = Referencia[3] - Posicion[3][0];

		Accion[3] = ((int32_t)Kp[3] * (Error[3][0] - Error[3][1]))>>(15-SHIFT_K_CONTROL);
		Accion[3] +=((int32_t)Kd[3] *
				((int32_t)Posicion[3][0] - ((int32_t)Posicion[3][1] << 1) + Posicion[3][2]))>>(15-SHIFT_K_CONTROL);
		Accion[3] += ((int32_t)Ki[3] * Error[3][0])>>(15-SHIFT_K_CONTROL);

		htim3.Instance->CCR1 = ((Accion[0]>>2) + (Accion[1]>>2) + (Accion[2]>>2) + (Accion[3]>>2));
		htim3.Instance->CCR2 = ((Accion[0]>>2) - (Accion[1]>>2) - (Accion[2]>>2) + (Accion[3]>>2));
		htim3.Instance->CCR3 = ((Accion[0]>>2) + (Accion[1]>>2) + (Accion[2]>>2) + (Accion[3]>>2));
		htim3.Instance->CCR4 = ((Accion[0]>>2) + (Accion[1]>>2) + (Accion[2]>>2) + (Accion[3]>>2));
		/*
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, ((Accion[0]>>2) + (Accion[1]>>2) + (Accion[2]>>2) + (Accion[3]>>2)));
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, ((Accion[0]>>2) - (Accion[1]>>2) - (Accion[2]>>2) + (Accion[3]>>2)));
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, ((Accion[0]>>2) + (Accion[1]>>2) + (Accion[2]>>2) + (Accion[3]>>2)));
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, ((Accion[0]>>2) + (Accion[1]>>2) + (Accion[2]>>2) + (Accion[3]>>2)));
	*/
	}
}

void CONTROL_TIMER_FCN(void const * argument){
	xSemaphoreGive(CONTROL_SMPHRHandle);
}
