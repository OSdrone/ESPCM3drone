/*
 * FicheroControl.c
 *
 *  Created on: 30 de sept. de 2016
 *      Author: Ruben
 */
#include "FuncionesFicheros.h"

void CONTROL_TASK() {

	//Formato 2000? -> 2^15 ?????????
	//Accion = (Kp + Ki/(1-z^-1))Error + Kd(1-z^-1)Pos

	const uint16_t Kp[4] = { 2200, 2, 2, 4 }; //Ajustar
	const uint16_t Kv[4] = { 2, 2, 2, 4 }; //Ajustar
	const uint16_t Ki[4] = { 2, 2, 2, 4 }; //Ajustar

	int16_t Accion[4] = { 0, 0, 0, 0 }; //Action by axis / accion por eje
	uint16_t PWM_Dutty[4] = { 0, 0, 0, 0 }; //Action by motor / Accion aplicada a cada motor


	int16_t Referencia[4]; //TODO inicializar
	int16_t Posicion[4][3]; //TODO inicializar
	int16_t Error[4][2]; //TODO inicializar

	while (1) {
		/* Leer Ref */
		Posicion[0][2] = Posicion[0][1];
		Posicion[0][1] = Posicion[0][0];
		Posicion[1][2] = Posicion[1][1];
		Posicion[1][1] = Posicion[1][0];
		Posicion[2][2] = Posicion[2][1];
		Posicion[2][1] = Posicion[2][0];
		Posicion[3][2] = Posicion[3][1];
		Posicion[3][1] = Posicion[3][0];

		//Leer posicion

		//Leer Altura

		//PI-D Eje 0
		Error[0][1] = Error[0][0];
		Error[0][0] = Referencia[0] - Posicion[0][0];

		Accion[0] += (Kp[0] * (Error[0][0] - Error[0][1]));
		Accion[0] += (Kv[0] * (Posicion[0][0] - ((int32_t) Posicion[0][1] << 1) + Posicion[0][2]));
		Accion[0] += (Ki[0] * Error[0][0]);

		//PI-D Eje 1
		Error[1][1] = Error[1][0];
		Error[1][0] = Referencia[1] - Posicion[1][0];

		Accion[1] += (Kp[1] * (Error[1][0] - Error[1][1]));
		Accion[1] += (Kv[1] * (Posicion[1][0] - ((int32_t) Posicion[1][1] << 1) + Posicion[1][2]));
		Accion[1] += (Ki[1] * Error[1][0]);

		//PI-D Eje 2
		Error[2][1] = Error[2][0];
		Error[2][0] = Referencia[2] - Posicion[2][0];

		Accion[2] += (Kp[2] * (Error[2][0] - Error[2][1]));
		Accion[2] += (Kv[2] * (Posicion[2][0] - ((int32_t) Posicion[2][1] << 1) + Posicion[2][2]));
		Accion[2] += (Ki[2] * Error[1][0]);

		//PI-D Eje 3
		Error[3][1] = Error[3][0];
		Error[3][0] = Referencia[3] - Posicion[3][0];

		Accion[3] += (Kp[3] * (Error[3][0] - Error[3][1]));
		Accion[3] += (Kv[3] * (Posicion[3][0] - ((int32_t) Posicion[3][1] << 1) + Posicion[3][2]));
		Accion[3] += (Ki[3] * Error[1][0]);

		PWM_Dutty[0] = Accion[0] >> 2 + Accion[1] >> 2 + Accion[2] >> 2 + Accion[3] >> 2;
		PWM_Dutty[1] = Accion[0] >> 2 - Accion[1] >> 2 - Accion[2]
				>> 2 + Accion[3] >> 2;
		PWM_Dutty[2] = -Accion[0] >> 2 - Accion[1] >> 2 + Accion[2]
				>> 2 + Accion[3] >> 2;
		PWM_Dutty[3] = -Accion[0] >> 2 + Accion[1] >> 2 - Accion[2]
				>> 2 + Accion[3] >> 2;

/*		pwm_set_duty(PWM_Dutty[0], 0);
		pwm_set_duty(PWM_Dutty[1], 1);
		pwm_set_duty(PWM_Dutty[2], 2);
		pwm_set_duty(PWM_Dutty[3], 3);
*/
	}
}
