/******************************************************************************
* FileName: Coe.h
* Purpose: Librería para el uso de CANOpen over Ethercat para un servo basado en soem.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 22/04/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

#ifndef _COE_H_
#define _COE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

#include <unistd.h>


#include "../Servo/soem/ethercat.h"
#include <sys/time.h>
#include "servo.h"
#include "servo_2.h"
#include "pdo_def.h"
#include "drive.h"
#include "med_tiempo.h"
#include "map_pdo.h"
#include "ebox.h"


/* ==================== Definiciones Globales ======================== */

#define EC_TIMEOUTMON  2e3 //useg
#define NUMERO_DE_BITS 16

#define MAX_LENGTH 30
#define stack64k (64 * 1024)


#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')


/* ==================== Declaracion de tipo de datos ===================== */

typedef enum
{
	FREE_RUN,
	DC,

} Synchronization_Type_t;



/* ================== Prototipo de Funciones publicas ==================*/

OSAL_THREAD_FUNC ecatcheck( void *ptr );

void Read_State_Ethercat_Slave(uint16 slave);

void Write_State_Ethercat_Slave(uint16 slave, ec_state State);

void Config_Synchronization_Type(uint16 slave, Synchronization_Type_t type);

void Print_binario(uint16 num);






/* ================ Prototipo de Interrupciones publicas ==================*/




#endif  /* _COE_H_ */
