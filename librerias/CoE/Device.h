/******************************************************************************
* FileName: Device.h
* Purpose: Librería para definir los objetos de perfil del dispositivo.
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

#ifndef _DEVICE_
#define _DEVICE_

#include "Type_data.h"

#define MAX_OBJECTS_DEVICE  40

//Index Device
#define INDEX_ERROR_CODE                     0x603F
#define INDEX_CONTROLWORD                    0x6040
#define INDEX_STATUSWORD                     0x6041
#define INDEX_MODE_OF_OPERATION              0x6060
#define INDEX_MODE_OF_OPERATION_DISPLAY      0x6061
#define INDEX_POSITION_ACTUAL_INTERNAL_VALUE 0x6063
#define INDEX_POSITION_ACTUAL_VALUE          0x6064
#define INDEX_FOLLOWING_ERROR_WINDOW         0x6065
#define INDEX_FOLLOWING_ERROR_TIME_OUT       0x6066
#define INDEX_VELOCITY_ACTUAL_VALUE          0x606c
#define INDEX_TARGET_TORQUE                  0x6071
#define INDEX_MOTOR_RATED_CURRENT            0x6075
#define INDEX_TORQUE_ACTUAL_VALUE            0x6077
#define INDEX_TARGET_POSITION                0x607a
#define INDEX_HOME_OFFSET                    0x607c
#define INDEX_SOFTWARE_POSITION_LIMIT        0x607d
#define INDEX_MAXIMUN_PROFILE_VELOCITY       0x607f
#define INDEX_PROFILE_VELOCITY               0x6081
#define INDEX_PROFILE_ACCELERATION           0x6083
#define INDEX_PROFILE_DECELERATION           0x6084
#define INDEX_QUICK_STOP_DECELERATION        0x6085
#define INDEX_TORQUE_SLOPE                   0x6087
#define INDEX_HOMING_METHOD                  0x6098
#define INDEX_HOMING_SPEEDS                  0x6099
#define INDEX_HOMING_ACCELERATION            0x609a
#define INDEX_VELOCITY_OFFSET                0x60b1
#define INDEX_TORQUE_OFFSET                  0x60b2
#define INDEX_TOUCH_PROBE_FUNCTION           0x60b8
#define INDEX_TOUCH_PROBE_STATUS             0x60b9
#define INDEX_TOUCH_PROBE_1_POSITIVE_EDGE    0x60ba
#define INDEX_TOUCH_PROBE_1_NEGATIVE_EDGE    0x60bb
#define INDEX_INTERPOLATION_TIME_PERIOD      0x60c2
#define INDEX_MAX_ACCELERATION               0x60c5
#define INDEX_MAX_DECELERATION               0x60c6
#define INDEX_FOLLOWING_ERROR_ACTUAL_VALUE   0x60f4
#define INDEX_POSITION_DEMAND_INTERNAL_VALUE 0x60fc
#define INDEX_DIGITAL_INPUTS                 0x60fd
#define INDEX_DIGITAL_OUTPUTS                0x60fe
#define INDEX_TARGET_VELOCITY                0x60ff
#define INDEX_SUPPORTED_DRIVE_MODE           0x6502


//Order of objects
#define ERROR_CODE                     0
#define CONTROLWORD                    1
#define STATUSWORD                     2
#define MODE_OF_OPERATION              3
#define MODE_OF_OPERATION_DISPLAY      4
#define POSITION_ACTUAL_INTERNAL_VALUE 5
#define POSITION_ACTUAL_VALUE          6
#define FOLLOWING_ERROR_WINDOW         7
#define FOLLOWING_ERROR_TIME_OUT       8
#define VELOCITY_ACTUAL_VALUE          9
#define TARGET_TORQUE                  10
#define MOTOR_RATED_CURRENT            11
#define TORQUE_ACTUAL_VALUE            12
#define TARGET_POSITION                13
#define HOME_OFFSET                    14
#define SOFTWARE_POSITION_LIMIT        15
#define MAXIMUM_PROFILE_VELOCITY       16
#define PROFILE_VELOCITY               17
#define PROFILE_ACCELERATION           18
#define PROFILE_DECELERATION           19
#define QUICK_STOP_DECELERATION        20
#define TORQUE_SLOPE                   21
#define HOMING_METHOD                  22
#define HOMING_SPEEDS                  23
#define HOMING_ACCELERATION            24
#define VELOCITY_OFFSET                25
#define TORQUE_OFFSET                  26
#define TOUCH_PROBE_FUNCTION           27
#define TOUCH_PROBE_STATUS             28
#define TOUCH_PROBE_1_POSITIVE_EDGE    29
#define TOUCH_PROBE_1_NEGATIVE_EDGE    30
#define INTERPOLATION_TIME_PERIOD      31
#define MAX_ACCELERATION               32
#define MAX_DECELERATION               33
#define FOLLOWING_ERROR_ACTUAL_VALUE   34
#define POSITION_DEMAND_INTERNAL_VALUE 35
#define DIGITAL_INPUTS                 36
#define DIGITAL_OUTPUTS                37
#define TARGET_VELOCITY                38
#define SUPPORTED_DRIVE_MODE           39

#ifdef __cplusplus
extern "C"{
#endif

void Init_Device(void);

void Print_Device(void);

void Print_Device_objects(uint16 slave);

#ifdef __cplusplus
}
#endif

#endif //_SYNC__
