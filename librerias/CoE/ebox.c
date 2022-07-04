/******************************************************************************
* FileName: ebox.c
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

/* ========== Inclusión de bibliotecas de código =======================*/
#include "ebox.h"


/* ============ Definicion de variables globales =======================*/

double     ain[2];
int        ainc;
int        streampos;
uint32 cyclecount;
in_EBOX_streamt  *in_EBOX;
out_EBOX_streamt *out_EBOX;

pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int16      stream1[MAXSTREAM];
int16      stream2[MAXSTREAM];

/* ============= Prototipos de funciones privadas =======================*/



/* ============= Implementacion de funciones publicas ====================*/

int output_cvs(char *fname, int length)
{
    FILE *fp;
    int  i;

    fp = fopen(fname, "w");
    if(fp == NULL)
    {
        return 0;
    }

    for (i = 0; i < length; i++)
    {
        fprintf(fp, "%d %d %d\n", i, stream1[i], stream2[i]);
    }
    fclose(fp);

    return 1;
}



/* ============= Implementacion de funciones privadas ====================*/





/* ============= Implementacion de Interrupciones Publicas ================*/
