/******************************************************************************
* FileName: ebox.h
* Purpose: Librería para prueba con SYNC0.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 16/06/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

#ifndef _EBOX_H_
#define _EBOX_H_

#include <stdio.h>
#include <stdlib.h>
#include "servo.h"

/* ==================== Definiciones Globales ======================== */

#define NSEC_PER_SEC 1000000000

// total samples to capture
#define MAXSTREAM 200000
// sample interval in ns, here 8us -> 125kHz
// maximum data rate for E/BOX v1.0.1 is around 150kHz
#define SYNC0TIME 8000

/* ==================== Declaracion de tipo de datos ===================== */

typedef struct PACKED
{
   uint8         status;
   uint8         counter;
   uint8         din;
   int32         ain[2];
   uint32        tsain;
   int32         enc[2];
} in_EBOXt;

typedef struct PACKED
{
   uint8         counter;
   int16         stream[100];
} in_EBOX_streamt;

typedef struct PACKED
{
   uint8         control;
   uint8         dout;
   int16         aout[2];
   uint16        pwmout[2];
} out_EBOXt;

typedef struct PACKED
{
   uint8         control;
} out_EBOX_streamt;





/* ================== Prototipo de Funciones publicas ==================*/

int output_cvs(char *fname, int length);





/* ================ Prototipo de Interrupciones publicas ==================*/




#endif  /* _EBOX_H_ */
