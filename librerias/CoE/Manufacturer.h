/******************************************************************************
* FileName: Manufacturer.h
* Purpose: Librería para definir los objetos del fabricante.
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

#ifndef _MANUFACTURER_
#define _MANUFACTURER_

#include "Type_data.h"

//Index Manufacturer defined objects
#define MAX_OBJECTS_MANUFACTURER  26

#define INDEX_MOTOR_TYPE                             0x2000
#define INDEX_INNER_ENCODER_RESOLUTION               0x2001
#define INDEX_OUTER_ENCODER_RESOLUTION               0x2002
#define INDEX_SCREW_PITCH                            0x2003
#define INDEX_ELECTRONIC_GEAR                        0x2004
#define INDEX_INPUT_FUNCTION                         0x2010
#define INDEX_INDEX_SIGNAL                           0x2020
#define INDEX_LATCHED_INDEX_POSITION                 0x2021
#define INDEX_MOTOR_ACTUAL_CURRENT                   0x2022
#define INDEX_2ND_ENCODER_OPTION                     0x2040
#define INDEX_ENABLE_SOFTWARE_POSITION_LIMIT         0x2041
#define INDEX_ENABLE_HARDWARE_LIMIT_PROTECTION       0x2042
#define INDEX_INPUT_LOGIC_INVERSION                  0x2043
#define INDEX_COMMON_GAIN                            0x2050
#define INDEX_VELOCITY_PROPORTIONAL_GAIN             0x2051
#define INDEX_PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP  0x2052
#define INDEX_INTEGRAL_GAIN_OF_THE_CURRENT_LOOP      0x2053
#define INDEX_INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP     0x2054
#define INDEX_PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP 0x2055
#define INDEX_MULTI_TURN_ENCODER_RESET_FLAG          0x2060
#define INDEX_DRIVE_ERROR_EVENTS_1                   0x2100
#define INDEX_DRIVE_ERROR_EVENTS_2                   0x2101
#define INDEX_DRIVE_WARNING_EVENTS_1                 0x2110
#define INDEX_DRIVE_WARNING_EVENTS_2                 0x2111
#define INDEX_DRIVE_WARNING_EVENTS_3                 0x2112
#define INDEX_DRIVE_WARNING_EVENTS_4                 0x2113


//Order of objects
#define MOTOR_TYPE                             0
#define INNER_ENCODER_RESOLUTION               1
#define OUTER_ENCODER_RESOLUTION               2
#define SCREW_PITCH                            3
#define ELECTRONIC_GEAR                        4
#define INPUT_FUNCTION                         5
#define INDEX_SIGNAL                           6
#define LATCHED_INDEX_POSITION                 7
#define MOTOR_ACTUAL_CURRENT                   8
#define M2ND_ENCODER_OPTION                     9
#define ENABLE_SOFTWARE_POSITION_LIMIT         10
#define ENABLE_HARDWARE_LIMIT_PROTECTION       11
#define INPUT_LOGIC_INVERSION                  12
#define COMMON_GAIN                            13
#define VELOCITY_PROPORTIONAL_GAIN             14
#define PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP  15
#define INTEGRAL_GAIN_OF_THE_CURRENT_LOOP      16
#define INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP     17
#define PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP 18
#define MULTI_TURN_ENCODER_RESET_FLAG          19
#define DRIVE_ERROR_EVENTS_1                   20
#define DRIVE_ERROR_EVENTS_2                   21
#define DRIVE_WARNING_EVENTS_1                 22
#define DRIVE_WARNING_EVENTS_2                 23
#define DRIVE_WARNING_EVENTS_3                 24
#define DRIVE_WARNING_EVENTS_4                 25


#ifdef __cplusplus
extern "C"{
#endif

void Init_Manufacturer(void);

void Print_Manufacturer(void);

void Print_Manufacturer_objects(uint16 slave);

#ifdef __cplusplus
}
#endif

#endif //_MANUFACTURER_
