/*
 * OSmath.h
 *
 *  Created on: 1 de nov. de 2016
 *      Author: Ruben
 */
#ifndef OSMATH_H_
#define OSMATH_H_

#include "arm_math.h"

typedef int16_t q16_16_t;
typedef int16_t q16_4_t;
typedef int16_t q16_3_t;

void OSmath_sqrt_q16_4_t(q16_4_t in, q16_4_t* out);
#endif /* OSMATH_H_ */
