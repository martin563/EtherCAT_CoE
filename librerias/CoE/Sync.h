/******************************************************************************
* FileName: Sync.h
* Purpose: Librería para definir los objetos de comunicacion.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 09/05/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

#ifndef _SYNC_
#define _SYNC_

#include "Type_data.h"

//Index Communication objects of Sync manger
#define MAX_OBJECTS_SYNC  9

#define INDEX_SYNC_MANAGER_COMMUNICATION_TYPE  0x1c00
#define INDEX_SYNC_MANAGER_0_PDO_ASSIGNMENT    0x1c10
#define INDEX_SYNC_MANAGER_1_PDO_ASSIGNMENT    0x1c11
#define INDEX_SYNC_MANAGER_2_PDO_ASSIGNMENT    0x1c12
#define INDEX_SYNC_MANAGER_3_PDO_ASSIGNMENT    0x1c13
#define INDEX_SYNC_MANAGER_2_SYNCHRONIZATION   0x1c32
#define INDEX_SYNC_MANAGER_3_SYNCHRONIZATION   0x1c33

#define INDEX_SYNC_MANAGER_0  0x1800
#define INDEX_RECEIVE_PDO_COMMUNICATION_PARAMETERS 0x1400


//Order of objects
#define SYNC_MANAGER_COMMUNICATION_TYPE  0
#define SYNC_MANAGER_0_PDO_ASSIGNMENT    1
#define SYNC_MANAGER_1_PDO_ASSIGNMENT    2
#define SYNC_MANAGER_2_PDO_ASSIGNMENT    3
#define SYNC_MANAGER_3_PDO_ASSIGNMENT    4
#define SYNC_MANAGER_2_SYNCHRONIZATION   5
#define SYNC_MANAGER_3_SYNCHRONIZATION   6


#define SYNC_MANAGER_0  7
#define RECEIVE_PDO_COMMUNICATION_PARAMETERS 8


#ifdef __cplusplus
extern "C"{
#endif

void Init_Sync(void);

void Print_Sync(void);

void Print_Sync_objects(uint16 slave);

#ifdef __cplusplus
}
#endif

#endif //_SYNC__
