/******************************************************************************
* FileName: med_tiempo.h
* Purpose: Librería para mediciones de tiempos.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 13/06/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

#ifndef _MED_TIEMPO_H_
#define _MED_TIEMPO_H_


#include <stdio.h>	/* for printf */
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <time.h>	/* for clock_gettime */
#include <sys/time.h>
#include <unistd.h>


/* ==================== Definiciones Globales ======================== */




/* ==================== Declaracion de tipo de datos ===================== */

typedef enum
{
	CLOCK_ON,
	CLOCK_OFF,

} Clock_t;



/* ================== Prototipo de Funciones publicas ==================*/


int cronosec(Clock_t opt);
long long cronomsec(Clock_t opt);
long long cronousec(Clock_t opt);
unsigned long long crononsec(Clock_t opt);




/* ================ Prototipo de Interrupciones publicas ==================*/




#endif  /*  _MED_TIEMPO_H_ */
