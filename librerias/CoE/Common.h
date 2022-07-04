/******************************************************************************
* FileName: Common.h
* Purpose: Librería para definir los objetos comunes.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 10/05/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

#ifndef _COMMON_
#define _COMMON_

#include "Type_data.h"

//Index Common object
#define MAX_OBJECTS_COMMON  6

#define INDEX_DEVICE_TYPE        0x1000
#define INDEX_ERROR_REGISTER     0x1001
#define INDEX_STORE_PARAMETERS   0x1010
#define INDEX_IDENTITY_OBJECT    0x1018

#define INDEX_COB_ID_SYNC   0x1005
#define INDEX_COMMUNICATION_CYCLE_PERIOD  0x1006

//Order of objects
#define DEVICE_TYPE        0
#define ERROR_REGISTER     1
#define STORE_PARAMETERS   2
#define IDENTITY_OBJECT    3

#define COB_ID_SYNC   4
#define COMMUNICATION_CYCLE_PERIOD 5


#ifdef __cplusplus
extern "C"{
#endif

void Init_Common(void);

void Print_Common(void);

void Print_Common_objects(uint16 slave);

#ifdef __cplusplus
}
#endif

#endif //_COMMON__
