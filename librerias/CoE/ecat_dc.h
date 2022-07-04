/******************************************************************************
* FileName: ecat_dc.h
* Purpose: Librería para implementar compensacion DC para ETHERCAT.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 08/06/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

#ifndef _ECAT_DC_H_
#define _ECAT_DC_H_

#include "CoE.h"


/* ==================== Definiciones Globales ======================== */

#define NSEC_PER_SEC 1000000000  // 1seg en nanoseg?


/* ==================== Declaracion de tipo de datos ===================== */





/* ================== Prototipo de Funciones publicas ==================*/

OSAL_THREAD_FUNC ecatthread( void *ptr );

long long dc_pi_sync(long long  reftime, long long  cycletime, int32_t shift_time);

/* ================ Prototipo de Interrupciones publicas ==================*/




#endif  /* ECAT_DC_H */
