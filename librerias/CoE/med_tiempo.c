/******************************************************************************
* FileName: med_tiempo.c
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

/* ========== Inclusión de bibliotecas de código =======================*/
#include "med_tiempo.h"


/* ============ Definicion de variables globales =======================*/



/* ============= Prototipos de funciones privadas =======================*/

static int Clock_option(Clock_t opt);


/* ============= Implementacion de funciones publicas ====================*/

int cronosec(Clock_t opt)
{
    static int pre_time;
    
    int startstop = Clock_option(opt);
    if(startstop)
    {
        pre_time=time(NULL);    
    }
    else
    {
        return time(NULL)-pre_time;    
    }
    
    return 0;
}


long long cronomsec(Clock_t opt)
{
    static long long pre_time;
    struct timeval tv;
    
    int startstop = Clock_option(opt);
    if(startstop)
    {
        gettimeofday(&tv, NULL);      
        pre_time=tv.tv_sec*1000+tv.tv_usec/1000;
    }
    else
    {      
        gettimeofday(&tv, NULL);      
        return tv.tv_sec*1000+tv.tv_usec/1000 - pre_time;
    }
    
    return 0;
}


long long cronousec(Clock_t opt)
{
    static long long pre_time;
    struct timeval tv;
    
    int startstop = Clock_option(opt);
    if(startstop)
    {
        gettimeofday(&tv, NULL);      
        pre_time=tv.tv_sec*1000000+tv.tv_usec;
    }
    else
    {      
        gettimeofday(&tv, NULL);      
        return tv.tv_sec*1000000+tv.tv_usec - pre_time;
    }
    return 0;
}



unsigned long long crononsec(Clock_t opt)
{
    static unsigned long pre_time;
    static unsigned long pre_secs;
    struct timespec ts;
    
    int startstop = Clock_option(opt);
    if(startstop)
    {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        pre_time=ts.tv_nsec;
        pre_secs=ts.tv_sec;
    }
    else
    {      
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return (ts.tv_sec-pre_secs)*1000000000+ts.tv_nsec - pre_time;
    }

    return 0;
}


/* ============= Implementacion de funciones privadas ====================*/

static int Clock_option(Clock_t opt)
{      
    int res = -1;
    
    switch(opt)
    { 
        case CLOCK_ON:
            res = 1;
        break;
        case CLOCK_OFF:
            res = 0;
        break;
        default:
            printf("Opcion invalida\n");
    }
    
    return res;
}


/* ============= Implementacion de Interrupciones Publicas ================*/
