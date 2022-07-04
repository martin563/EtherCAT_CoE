/******************************************************************************
* FileName: Type_data.h
* Purpose: Librería para definir tipo de datos en comun con otros modulos.
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

#ifndef _TYPE_DATA_
#define _TYPE_DATA_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Servo/soem/ethercat.h"


#define MAX_OBJECTS 50

#define bits_8  8
#define bits_16 16
#define bits_32 32


typedef enum
{
    int_8_bits,
    int_16_bits,
    int_32_bits,
    uint_8_bits,
    uint_16_bits,
    uint_32_bits,
    real_32_bits,

} case_type_t;


typedef enum
{
    int_8,
    int_16,
	int_32,
	uint_8,
	uint_16,
	uint_32,
	real_32,

} Type_t;

typedef struct
{
	char *name;

	uint16_t index;
	uint8_t sub_index;
	Type_t type;
	uint8_t size;

} Object_t;


typedef struct
{
	char *name;

	int N_obj;
	Object_t obj[MAX_OBJECTS];

} Dic_t;


#ifdef __cplusplus
extern "C"{
#endif

Object_t Create_object(char name[], uint16_t index, uint8_t sub_index, Type_t type);

Dic_t Create_dic(char name[], int N_obj, Object_t obj[]);

void set_object(uint16 slave, Object_t object, float value);

void get_object(uint16 slave, Object_t object, void *value);

void Print_Dic(char *name_dic ,Dic_t dic[], int max_obj);

void Read_Dic(uint16 slave, char *name_dic ,Dic_t dic[], int max_obj);

void Error_wkc(int wkc, char msj[]);

#ifdef __cplusplus
}
#endif

#endif //_TYPE_DATA_
