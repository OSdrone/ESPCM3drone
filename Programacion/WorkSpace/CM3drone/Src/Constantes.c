/*
 * Constantes.c
 *
 *  Created on: 14 de oct. de 2016
 *      Author: DTUser
 */

#include "Constantes.h"
#include "arm_math.h"

q15_t COEF_FILTRO_VEL[5*NUM_ETAPAS_FILTRO_VEL_ANG];// = COEF_FILTRO_VEL_VALUES;
q15_t COEF_FILTRO_ACEL[5*NUM_ETAPAS_FILTRO_ACEL_ANG];// = COEF_FILTRO_VEL_VALUES;
