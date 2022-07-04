/******************************************************************************
* FileName: servo_2.h
* Purpose: Librería servo para SOEM basada en ejemplo python.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 27/05/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

#ifndef _SERVO_2_
#define _SERVO_2_

#include "../Servo/soem/ethercat.h"
#include "pdo_def.h"
#include "drive.h"


typedef enum
{
	DRIVE_NOT_READY_TO_SWITCH_ON,
	DRIVE_SWITCH_ON_DISABLED,
	DRIVE_READY_TO_SWITCH_ON,
	DRIVE_SWITCH_ON,
	DRIVE_OPERATION_ENABLED,
	DRIVE_QUICK_STOP_ACTIVE,
    DRIVE_FAULT_REACTION_ACTIVE,
    DRIVE_FAULT,
    DRIVE_UNKOWN_STATE

} status_servo_t;

typedef enum
{
    SHUTDOWN,
    SWITCH_ON,
	ENABLE_OPERATION,
	DISABLE_OPERATION,
	FAULT_RESET,

} command_servo_t;



#ifdef __cplusplus
extern "C"{
#endif
status_servo_t servo_get_state(uint16 slave);

void servo_send_command(uint16 slave, command_servo_t cmd);

int has_servo_arrived(uint16 slave);

void servo_set_position(uint16 slave, int32 position_counts, uint32 velocity_rpm, uint32 acceleration_rpm_s);

void servo_set_position_sync(uint16 slave, uint16_t control_word);

void Print_sync(uint16 slave);

#ifdef __cplusplus
}
#endif

#endif //_SERVO_2_
