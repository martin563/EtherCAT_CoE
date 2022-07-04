/******************************************************************************
* FileName: Manufacturer.c
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

/* ========== Inclusión de bibliotecas de código =======================*/
#include "Manufacturer.h"

Dic_t MANUFACTURER[MAX_OBJECTS_MANUFACTURER];

/* ============ Definicion de variables globales =======================*/


/* ============= Prototipos de funciones privadas =======================*/

static void Init_motor_type(void);

static void Init_inner_encoder_resolution(void);

static void Init_Outer_encoder_resolution(void);

static void Init_Screw_pitch(void);

static void Init_Electronic_gear(void);

static void Init_Input_function(void);

static void Init_Index_signal(void);

static void Init_Latched_index_position(void);

static void Init_Motor_actual_current(void);

static void Init_2nd_encoder_option(void);

static void Init_Enable_software_position_limit(void);

static void Init_Enable_hardware_limit_protection(void);

static void Init_Input_logic_inversion(void);

static void Init_Common_gain(void);

static void Init_Velocity_proportional_gain(void);

static void Init_Proportional_gain_of_the_current_loop(void);

static void Init_Integral_gain_of_the_current_loop(void);

static void Init_Integral_gain_of_the_velocity_loop(void);

static void Init_Proportional_gain_of_the_position_loop(void);

static void Init_Multi_Turn_Encoder_Reset_Flag(void);

static void Init_Drive_error_events_1(void);

static void Init_Drive_error_events_2(void);

static void Init_Drive_Warning_Events_1(void);

static void Init_Drive_Warning_Events_2(void);

static void Init_Drive_Warning_Events_3(void);

static void Init_Drive_Warning_Events_4(void);


/* ============= Implementacion de funciones publicas ====================*/

void Init_Manufacturer(void)
{
    Init_motor_type();

    Init_inner_encoder_resolution();

    Init_Outer_encoder_resolution();

    Init_Screw_pitch();

    Init_Electronic_gear();

    Init_Input_function();

    Init_Index_signal();

    Init_Latched_index_position();

    Init_Motor_actual_current();

    Init_2nd_encoder_option();

    Init_Enable_software_position_limit();

    Init_Enable_hardware_limit_protection();

    Init_Input_logic_inversion();

    Init_Common_gain();

    Init_Velocity_proportional_gain();

    Init_Proportional_gain_of_the_current_loop();

    Init_Integral_gain_of_the_current_loop();

    Init_Integral_gain_of_the_velocity_loop();

    Init_Proportional_gain_of_the_position_loop();

    Init_Multi_Turn_Encoder_Reset_Flag();

    Init_Drive_error_events_1();

    Init_Drive_error_events_2();

    Init_Drive_Warning_Events_1();

    Init_Drive_Warning_Events_2();

    Init_Drive_Warning_Events_3();

    Init_Drive_Warning_Events_4();

}

void Print_Manufacturer(void)
{
    Print_Dic("MANUFACTURER", MANUFACTURER, MAX_OBJECTS_MANUFACTURER);
}

void Print_Manufacturer_objects(uint16 slave)
{
    Read_Dic(slave, "MANUFACTURER", MANUFACTURER, MAX_OBJECTS_MANUFACTURER);
}


/* ============= Implementacion de funciones privadas ====================*/

static void Init_motor_type(void)
{
    Object_t MOTOR_TYPE_OBJECTS[1] = {};

    MOTOR_TYPE_OBJECTS[0] = Create_object("MOTOR_TYPE", INDEX_MOTOR_TYPE, 0x00, uint_16);

    int longitud = sizeof(MOTOR_TYPE_OBJECTS)/sizeof(MOTOR_TYPE_OBJECTS[0]);
    MANUFACTURER[MOTOR_TYPE] = Create_dic("MOTOR_TYPE", longitud, MOTOR_TYPE_OBJECTS);
}

static void Init_inner_encoder_resolution(void)
{
    Object_t INNER_ENCODER_RESOLUTION_OBJECTS[1] = {};

    INNER_ENCODER_RESOLUTION_OBJECTS[0] = Create_object("INNER_ENCODER_RESOLUTION", INDEX_INNER_ENCODER_RESOLUTION, 0x00, int_32);

    int longitud = sizeof(INNER_ENCODER_RESOLUTION_OBJECTS)/sizeof(INNER_ENCODER_RESOLUTION_OBJECTS[0]);
    MANUFACTURER[INNER_ENCODER_RESOLUTION] = Create_dic("INNER_ENCODER_RESOLUTION", longitud, INNER_ENCODER_RESOLUTION_OBJECTS);
}

static void Init_Outer_encoder_resolution(void)
{
    Object_t OUTER_ENCODER_RESOLUTION_OBJECTS[1] = {};

    OUTER_ENCODER_RESOLUTION_OBJECTS[0] = Create_object("OUTER_ENCODER_RESOLUTION", INDEX_OUTER_ENCODER_RESOLUTION, 0x00, int_32);

    int longitud = sizeof(OUTER_ENCODER_RESOLUTION_OBJECTS)/sizeof(OUTER_ENCODER_RESOLUTION_OBJECTS[0]);
    MANUFACTURER[OUTER_ENCODER_RESOLUTION] = Create_dic("OUTER_ENCODER_RESOLUTION", longitud, OUTER_ENCODER_RESOLUTION_OBJECTS);
}

static void Init_Screw_pitch(void)
{
    Object_t SCREW_PITCH_OBJECTS[1] = {};

    SCREW_PITCH_OBJECTS[0] = Create_object("SCREW_PITCH", INDEX_SCREW_PITCH, 0x00, int_32);

    int longitud = sizeof(SCREW_PITCH_OBJECTS)/sizeof(SCREW_PITCH_OBJECTS[0]);
    MANUFACTURER[SCREW_PITCH] = Create_dic("SCREW_PITCH", longitud, SCREW_PITCH_OBJECTS);
}

static void Init_Electronic_gear(void)
{
    Object_t ELECTRONIC_GEAR_OBJECTS[3] = {};

    ELECTRONIC_GEAR_OBJECTS[0] = Create_object("NUMBER_OF_ENTRIES", INDEX_ELECTRONIC_GEAR, 0x00, uint_8);
    ELECTRONIC_GEAR_OBJECTS[1] = Create_object("NUMERATOR_OF_GEAR_RATIO", INDEX_ELECTRONIC_GEAR, 0x01, int_32);
    ELECTRONIC_GEAR_OBJECTS[2] = Create_object("DENOMINATOR_OF_GEAR_RATIO", INDEX_ELECTRONIC_GEAR, 0x02, int_32);

    int longitud = sizeof(ELECTRONIC_GEAR_OBJECTS)/sizeof(ELECTRONIC_GEAR_OBJECTS[0]);
    MANUFACTURER[ELECTRONIC_GEAR] = Create_dic("ELECTRONIC_GEAR", longitud, ELECTRONIC_GEAR_OBJECTS);
}

static void Init_Input_function(void)
{
    Object_t INPUT_FUNCTION_OBJECTS[1] = {};

    INPUT_FUNCTION_OBJECTS[0] = Create_object("INPUT_FUNCTION", INDEX_INPUT_FUNCTION, 0x00, uint_16);

    int longitud = sizeof(INPUT_FUNCTION_OBJECTS)/sizeof(INPUT_FUNCTION_OBJECTS[0]);
    MANUFACTURER[INPUT_FUNCTION] = Create_dic("INPUT_FUNCTION", longitud, INPUT_FUNCTION_OBJECTS);
}

static void Init_Index_signal(void)
{
    Object_t INDEX_SIGNAL_OBJECTS[1] = {};

    INDEX_SIGNAL_OBJECTS[0] = Create_object("INDEX_SIGNAL", INDEX_INDEX_SIGNAL, 0x00, int_8);

    int longitud = sizeof(INDEX_SIGNAL_OBJECTS)/sizeof(INDEX_SIGNAL_OBJECTS[0]);
    MANUFACTURER[INDEX_SIGNAL] = Create_dic("INDEX_SIGNAL", longitud, INDEX_SIGNAL_OBJECTS);
}

static void Init_Latched_index_position(void)
{
    Object_t LATCHED_INDEX_POSITION_OBJECTS[1] = {};

    LATCHED_INDEX_POSITION_OBJECTS[0] = Create_object("LATCHED_INDEX_POSITION", INDEX_LATCHED_INDEX_POSITION, 0x00, int_32);

    int longitud = sizeof(LATCHED_INDEX_POSITION_OBJECTS)/sizeof(LATCHED_INDEX_POSITION_OBJECTS[0]);
    MANUFACTURER[LATCHED_INDEX_POSITION] = Create_dic("LATCHED_INDEX_POSITION", longitud, LATCHED_INDEX_POSITION_OBJECTS);
}

static void Init_Motor_actual_current(void)
{
    Object_t MOTOR_ACTUAL_CURRENT_OBJECTS[1] = {};

    MOTOR_ACTUAL_CURRENT_OBJECTS[0] = Create_object("MOTOR_ACTUAL_CURRENT", INDEX_MOTOR_ACTUAL_CURRENT, 0x00, real_32);

    int longitud = sizeof(MOTOR_ACTUAL_CURRENT_OBJECTS)/sizeof(MOTOR_ACTUAL_CURRENT_OBJECTS[0]);
    MANUFACTURER[MOTOR_ACTUAL_CURRENT] = Create_dic("MOTOR_ACTUAL_CURRENT", longitud, MOTOR_ACTUAL_CURRENT_OBJECTS);
}

static void Init_2nd_encoder_option(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("2ND_ENCODER_OPTION", INDEX_2ND_ENCODER_OPTION, 0x00, uint_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    MANUFACTURER[M2ND_ENCODER_OPTION] = Create_dic("2ND_ENCODER_OPTION", longitud, obj);
}

static void Init_Enable_software_position_limit(void)
{
    Object_t ENABLE_SOFTWARE_POSITION_LIMIT_OBJECTS[1] = {};

    ENABLE_SOFTWARE_POSITION_LIMIT_OBJECTS[0] = Create_object("ENABLE_SOFTWARE_POSITION_LIMIT", INDEX_ENABLE_SOFTWARE_POSITION_LIMIT, 0x00, uint_16);

    int longitud = sizeof(ENABLE_SOFTWARE_POSITION_LIMIT_OBJECTS)/sizeof(ENABLE_SOFTWARE_POSITION_LIMIT_OBJECTS[0]);
    MANUFACTURER[ENABLE_SOFTWARE_POSITION_LIMIT] = Create_dic("ENABLE_SOFTWARE_POSITION_LIMIT", longitud, ENABLE_SOFTWARE_POSITION_LIMIT_OBJECTS);
}

static void Init_Enable_hardware_limit_protection(void)
{
    Object_t ENABLE_HARDWARE_LIMIT_PROTECTION_OBJECTS[1] = {};

    ENABLE_HARDWARE_LIMIT_PROTECTION_OBJECTS[0] = Create_object("ENABLE_HARDWARE_LIMIT_PROTECTION", INDEX_ENABLE_HARDWARE_LIMIT_PROTECTION, 0x00, uint_16);

    int longitud = sizeof(ENABLE_HARDWARE_LIMIT_PROTECTION_OBJECTS)/sizeof(ENABLE_HARDWARE_LIMIT_PROTECTION_OBJECTS[0]);
    MANUFACTURER[ENABLE_HARDWARE_LIMIT_PROTECTION] = Create_dic("ENABLE_HARDWARE_LIMIT_PROTECTION", longitud, ENABLE_HARDWARE_LIMIT_PROTECTION_OBJECTS);
}

static void Init_Input_logic_inversion(void)
{
    Object_t INPUT_LOGIC_INVERSION_OBJECTS[1] = {};

    INPUT_LOGIC_INVERSION_OBJECTS[0] = Create_object("INPUT_LOGIC_INVERSION", INDEX_INPUT_LOGIC_INVERSION, 0x00, int_16);

    int longitud = sizeof(INPUT_LOGIC_INVERSION_OBJECTS)/sizeof(INPUT_LOGIC_INVERSION_OBJECTS[0]);
    MANUFACTURER[INPUT_LOGIC_INVERSION] = Create_dic("INPUT_LOGIC_INVERSION", longitud, INPUT_LOGIC_INVERSION_OBJECTS);
}

static void Init_Common_gain(void)
{
    Object_t COMMON_GAIN_OBJECTS[1] = {};

    COMMON_GAIN_OBJECTS[0] = Create_object("COMMON_GAIN", INDEX_COMMON_GAIN, 0x00, real_32);

    int longitud = sizeof(COMMON_GAIN_OBJECTS)/sizeof(COMMON_GAIN_OBJECTS[0]);
    MANUFACTURER[COMMON_GAIN] = Create_dic("COMMON_GAIN", longitud, COMMON_GAIN_OBJECTS);
}

static void Init_Velocity_proportional_gain(void)
{
    Object_t VELOCITY_PROPORTIONAL_GAIN_OBJECTS[1] = {};

    VELOCITY_PROPORTIONAL_GAIN_OBJECTS[0] = Create_object("VELOCITY_PROPORTIONAL_GAIN", INDEX_VELOCITY_PROPORTIONAL_GAIN, 0x00, real_32);

    int longitud = sizeof(VELOCITY_PROPORTIONAL_GAIN_OBJECTS)/sizeof(VELOCITY_PROPORTIONAL_GAIN_OBJECTS[0]);
    MANUFACTURER[VELOCITY_PROPORTIONAL_GAIN] = Create_dic("VELOCITY_PROPORTIONAL_GAIN", longitud, VELOCITY_PROPORTIONAL_GAIN_OBJECTS);
}

static void Init_Proportional_gain_of_the_current_loop(void)
{
    Object_t PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS[1] = {};

    PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS[0] = Create_object("PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP", INDEX_PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP, 0x00, real_32);

    int longitud = sizeof(PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS)/sizeof(PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS[0]);
    MANUFACTURER[PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP] = Create_dic("PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP", longitud, PROPORTIONAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS);
}

static void Init_Integral_gain_of_the_current_loop(void)
{
    Object_t INTEGRAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS[1] = {};

    INTEGRAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS[0] = Create_object("INTEGRAL_GAIN_OF_THE_CURRENT_LOOP", INDEX_INTEGRAL_GAIN_OF_THE_CURRENT_LOOP, 0x00, real_32);

    int longitud = sizeof(INTEGRAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS)/sizeof(INTEGRAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS[0]);
    MANUFACTURER[INTEGRAL_GAIN_OF_THE_CURRENT_LOOP] = Create_dic("INTEGRAL_GAIN_OF_THE_CURRENT_LOOP", longitud, INTEGRAL_GAIN_OF_THE_CURRENT_LOOP_OBJECTS);
}

static void Init_Integral_gain_of_the_velocity_loop(void)
{
    Object_t INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP_OBJECTS[1] = {};

    INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP_OBJECTS[0] = Create_object("INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP", INDEX_INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP, 0x00, real_32);

    int longitud = sizeof(INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP_OBJECTS)/sizeof(INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP_OBJECTS[0]);
    MANUFACTURER[INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP] = Create_dic("INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP", longitud, INTEGRAL_GAIN_OF_THE_VELOCITY_LOOP_OBJECTS);
}

static void Init_Proportional_gain_of_the_position_loop(void)
{
    Object_t PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP_OBJECTS[1] = {};

    PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP_OBJECTS[0] = Create_object("PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP", INDEX_PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP, 0x00, real_32);

    int longitud = sizeof(PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP_OBJECTS)/sizeof(PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP_OBJECTS[0]);
    MANUFACTURER[PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP] = Create_dic("PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP", longitud, PROPORTIONAL_GAIN_OF_THE_POSITION_LOOP_OBJECTS);
}

static void Init_Multi_Turn_Encoder_Reset_Flag(void)
{
    Object_t MULTI_TURN_ENCODER_RESET_FLAG_OBJECTS[1] = {};

    MULTI_TURN_ENCODER_RESET_FLAG_OBJECTS[0] = Create_object("MULTI_TURN_ENCODER_RESET_FLAG", INDEX_MULTI_TURN_ENCODER_RESET_FLAG, 0x00, uint_8);

    int longitud = sizeof(MULTI_TURN_ENCODER_RESET_FLAG_OBJECTS)/sizeof(MULTI_TURN_ENCODER_RESET_FLAG_OBJECTS[0]);
    MANUFACTURER[MULTI_TURN_ENCODER_RESET_FLAG] = Create_dic("MULTI_TURN_ENCODER_RESET_FLAG", longitud, MULTI_TURN_ENCODER_RESET_FLAG_OBJECTS);
}

static void Init_Drive_error_events_1(void)
{
    Object_t DRIVE_ERROR_EVENTS_1_OBJECTS[1] = {};

    DRIVE_ERROR_EVENTS_1_OBJECTS[0] = Create_object("DRIVE_ERROR_EVENTS_1", INDEX_DRIVE_ERROR_EVENTS_1, 0x00, uint_32);

    int longitud = sizeof(DRIVE_ERROR_EVENTS_1_OBJECTS)/sizeof(DRIVE_ERROR_EVENTS_1_OBJECTS[0]);
    MANUFACTURER[DRIVE_ERROR_EVENTS_1] = Create_dic("DRIVE_ERROR_EVENTS_1", longitud, DRIVE_ERROR_EVENTS_1_OBJECTS);
}

static void Init_Drive_error_events_2(void)
{
    Object_t DRIVE_ERROR_EVENTS_2_OBJECTS[1] = {};

    DRIVE_ERROR_EVENTS_2_OBJECTS[0] = Create_object("DRIVE_ERROR_EVENTS_2", INDEX_DRIVE_ERROR_EVENTS_2, 0x00, uint_32);

    int longitud = sizeof(DRIVE_ERROR_EVENTS_2_OBJECTS)/sizeof(DRIVE_ERROR_EVENTS_2_OBJECTS[0]);
    MANUFACTURER[DRIVE_ERROR_EVENTS_2] = Create_dic("DRIVE_ERROR_EVENTS_2", longitud, DRIVE_ERROR_EVENTS_2_OBJECTS);
}

static void Init_Drive_Warning_Events_1(void)
{
    Object_t DRIVE_WARNING_EVENTS_1_OBJECTS[1] = {};

    DRIVE_WARNING_EVENTS_1_OBJECTS[0] = Create_object("DRIVE_WARNING_EVENTS_1", INDEX_DRIVE_WARNING_EVENTS_1, 0x00, uint_16);

    int longitud = sizeof(DRIVE_WARNING_EVENTS_1_OBJECTS)/sizeof(DRIVE_WARNING_EVENTS_1_OBJECTS[0]);
    MANUFACTURER[DRIVE_WARNING_EVENTS_1] = Create_dic("DRIVE_WARNING_EVENTS_1", longitud, DRIVE_WARNING_EVENTS_1_OBJECTS);
}

static void Init_Drive_Warning_Events_2(void)
{
    Object_t DRIVE_WARNING_EVENTS_2_OBJECTS[1] = {};

    DRIVE_WARNING_EVENTS_2_OBJECTS[0] = Create_object("DRIVE_WARNING_EVENTS_2", INDEX_DRIVE_WARNING_EVENTS_2, 0x00, uint_16);

    int longitud = sizeof(DRIVE_WARNING_EVENTS_2_OBJECTS)/sizeof(DRIVE_WARNING_EVENTS_2_OBJECTS[0]);
    MANUFACTURER[DRIVE_WARNING_EVENTS_2] = Create_dic("DRIVE_WARNING_EVENTS_2", longitud, DRIVE_WARNING_EVENTS_2_OBJECTS);
}

static void Init_Drive_Warning_Events_3(void)
{
    Object_t DRIVE_WARNING_EVENTS_3_OBJECTS[1] = {};

    DRIVE_WARNING_EVENTS_3_OBJECTS[0] = Create_object("DRIVE_WARNING_EVENTS_3", INDEX_DRIVE_WARNING_EVENTS_3, 0x00, uint_16);

    int longitud = sizeof(DRIVE_WARNING_EVENTS_3_OBJECTS)/sizeof(DRIVE_WARNING_EVENTS_3_OBJECTS[0]);
    MANUFACTURER[DRIVE_WARNING_EVENTS_3] = Create_dic("DRIVE_WARNING_EVENTS_3", longitud, DRIVE_WARNING_EVENTS_3_OBJECTS);
}


static void Init_Drive_Warning_Events_4(void)
{
    Object_t DRIVE_WARNING_EVENTS_4_OBJECTS[1] = {};

    DRIVE_WARNING_EVENTS_4_OBJECTS[0] = Create_object("DRIVE_WARNING_EVENTS_4", INDEX_DRIVE_WARNING_EVENTS_4, 0x00, uint_16);

    int longitud = sizeof(DRIVE_WARNING_EVENTS_4_OBJECTS)/sizeof(DRIVE_WARNING_EVENTS_4_OBJECTS[0]);
    MANUFACTURER[DRIVE_WARNING_EVENTS_4] = Create_dic("DRIVE_WARNING_EVENTS_4", longitud, DRIVE_WARNING_EVENTS_4_OBJECTS);
}


/* ============= Implementacion de Interrupciones Publicas ================*/



