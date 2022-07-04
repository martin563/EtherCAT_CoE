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

/* ========== Inclusión de bibliotecas de código =======================*/
#include "Device.h"

Dic_t DEVICE[MAX_OBJECTS_DEVICE];

/* ============ Definicion de variables globales =======================*/


/* ============= Prototipos de funciones privadas =======================*/

static void Init_error_code(void);

static void Init_controlword(void);

static void Init_statusword(void);

static void Init_mode_of_operation(void);

static void Init_mode_of_operation_display(void);

static void Init_position_actual_internal_value(void);

static void Init_position_actual_value(void);

static void Init_following_error_window(void);

static void Init_following_error_time_out(void);

static void Init_velocity_actual_value(void);

static void Init_target_torque(void);

static void Init_motor_rated_current(void);

static void Init_torque_actual_value(void);

static void Init_target_position(void);

static void Init_home_offset(void);

static void Init_software_position_limit(void);

static void Init_maximum_profile_velocity(void);

static void Init_profile_velocity(void);

static void Init_profile_acceleration(void);

static void Init_profile_deceleration(void);

static void Init_quick_stop_deceleration(void);

static void Init_torque_slope(void);

static void Init_homing_method(void);

static void Init_homing_speeds(void);

static void Init_homing_acceleration(void);

static void Init_velocity_offset(void);

static void Init_torque_offset(void);

static void Init_touch_probe_function(void);

static void Init_touch_probe_status(void);

static void Init_touch_probe_1_positive_edge(void);

static void Init_touch_probe_1_negative_edge(void);

static void Init_interpolation_time_period(void);

static void Init_max_acceleration(void);

static void Init_max_deceleration(void);

static void Init_following_error_actual_value(void);

static void Init_position_demand_internal_value(void);

static void Init_digital_inputs(void);

static void Init_digital_outputs(void);

static void Init_target_velocity(void);

static void Init_suppoted_drive_mode(void);

/* ============= Implementacion de funciones publicas ====================*/

void Init_Device(void)
{
    Init_error_code();

    Init_controlword();

    Init_statusword();

    Init_mode_of_operation();

    Init_mode_of_operation_display();

    Init_position_actual_internal_value();

    Init_position_actual_value();

    Init_following_error_window();

    Init_following_error_time_out();

    Init_velocity_actual_value();

    Init_target_torque();

    Init_motor_rated_current();

    Init_torque_actual_value();

    Init_target_position();

    Init_home_offset();

    Init_software_position_limit();

    Init_maximum_profile_velocity();

    Init_profile_velocity();

    Init_profile_acceleration();

    Init_profile_deceleration();

    Init_quick_stop_deceleration();

    Init_torque_slope();

    Init_homing_method();

    Init_homing_speeds();

    Init_homing_acceleration();

    Init_velocity_offset();

    Init_torque_offset();

    Init_touch_probe_function();

    Init_touch_probe_status();

    Init_touch_probe_1_positive_edge();

    Init_touch_probe_1_negative_edge();

    Init_interpolation_time_period();

    Init_max_acceleration();

    Init_max_deceleration();

    Init_following_error_actual_value();

    Init_position_demand_internal_value();

    Init_digital_inputs();

    Init_digital_outputs();

    Init_target_velocity();

    Init_suppoted_drive_mode();

}

void Print_Device(void)
{
    Print_Dic("DEVICE", DEVICE, MAX_OBJECTS_DEVICE);
}

void Print_Device_objects(uint16 slave)
{
    Read_Dic(slave, "DEVICE", DEVICE, MAX_OBJECTS_DEVICE);
}

/* ============= Implementacion de funciones privadas ====================*/

static void Init_error_code(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("ERROR_CODE", INDEX_ERROR_CODE, 0x00, uint_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[ERROR_CODE] = Create_dic("ERROR_CODE", longitud, obj);
}

static void Init_controlword(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("CONTROLWORD", INDEX_CONTROLWORD, 0x00, uint_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[CONTROLWORD] = Create_dic("CONTROLWORD", longitud, obj);
}

static void Init_statusword(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("STATUSWORD", INDEX_STATUSWORD, 0x00, uint_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[STATUSWORD] = Create_dic("STATUSWORD", longitud, obj);
}

static void Init_mode_of_operation(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("MODE_OF_OPERATION", INDEX_MODE_OF_OPERATION, 0x00, int_8);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[MODE_OF_OPERATION] = Create_dic("MODE_OF_OPERATION", longitud, obj);
}

static void Init_mode_of_operation_display(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("MODE_OF_OPERATION_DISPLAY", INDEX_MODE_OF_OPERATION_DISPLAY, 0x00, int_8);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[MODE_OF_OPERATION_DISPLAY] = Create_dic("MODE_OF_OPERATION_DISPLAY", longitud, obj);
}

static void Init_position_actual_internal_value(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("POSITION_ACTUAL_INTERNAL_VALUE", INDEX_POSITION_ACTUAL_INTERNAL_VALUE, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[POSITION_ACTUAL_INTERNAL_VALUE] = Create_dic("POSITION_ACTUAL_INTERNAL_VALUE", longitud, obj);
}

static void Init_position_actual_value(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("POSITION_ACTUAL_VALUE", INDEX_POSITION_ACTUAL_VALUE, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[POSITION_ACTUAL_VALUE] = Create_dic("POSITION_ACTUAL_VALUE", longitud, obj);
}

static void Init_following_error_window(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("FOLLOWING_ERROR_WINDOW", INDEX_FOLLOWING_ERROR_WINDOW, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[FOLLOWING_ERROR_WINDOW] = Create_dic("FOLLOWING_ERROR_WINDOW", longitud, obj);
}

static void Init_following_error_time_out(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("FOLLOWING_ERROR_TIME_OUT", INDEX_FOLLOWING_ERROR_TIME_OUT, 0x00, uint_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[FOLLOWING_ERROR_TIME_OUT] = Create_dic("FOLLOWING_ERROR_TIME_OUT", longitud, obj);
}

static void Init_velocity_actual_value(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("VELOCITY_ACTUAL_VALUE", INDEX_VELOCITY_ACTUAL_VALUE, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[VELOCITY_ACTUAL_VALUE] = Create_dic("VELOCITY_ACTUAL_VALUE", longitud, obj);
}

static void Init_target_torque(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TARGET_TORQUE", INDEX_TARGET_TORQUE, 0x00, int_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TARGET_TORQUE] = Create_dic("TARGET_TORQUE", longitud, obj);
}

static void Init_motor_rated_current(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("MOTOR_RATED_CURRENT", INDEX_MOTOR_RATED_CURRENT, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[MOTOR_RATED_CURRENT] = Create_dic("MOTOR_RATED_CURRENT", longitud, obj);
}

static void Init_torque_actual_value(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TORQUE_ACTUAL_VALUE", INDEX_TORQUE_ACTUAL_VALUE, 0x00, int_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TORQUE_ACTUAL_VALUE] = Create_dic("TORQUE_ACTUAL_VALUE", longitud, obj);
}

static void Init_target_position(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TARGET_POSITION", INDEX_TARGET_POSITION, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TARGET_POSITION] = Create_dic("TARGET_POSITION", longitud, obj);
}

static void Init_home_offset(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("HOME_OFFSET", INDEX_HOME_OFFSET, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[HOME_OFFSET] = Create_dic("HOME_OFFSET", longitud, obj);
}

static void Init_software_position_limit(void)
{
    Object_t obj[3] = {};

    obj[0] = Create_object("HIGHEST_SUB_INDEX_SUPPORTED", INDEX_SOFTWARE_POSITION_LIMIT, 0x00, uint_8);
    obj[1] = Create_object("MIN_SOFTWARE_POSITION_LIMIT", INDEX_SOFTWARE_POSITION_LIMIT, 0x01, int_32);
    obj[2] = Create_object("MAX_SOFTWARE_POSITION_LIMIT", INDEX_SOFTWARE_POSITION_LIMIT, 0x02, int_32);


    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[SOFTWARE_POSITION_LIMIT] = Create_dic("SOFTWARE_POSITION_LIMIT", longitud, obj);
}

static void Init_maximum_profile_velocity(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("MAXIMUN_PROFILE_VELOCITY", INDEX_MAXIMUN_PROFILE_VELOCITY, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[MAXIMUM_PROFILE_VELOCITY] = Create_dic("MAXIMUN_PROFILE_VELOCITY", longitud, obj);
}

static void Init_profile_velocity(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("PROFILE_VELOCITY", INDEX_PROFILE_VELOCITY, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[PROFILE_VELOCITY] = Create_dic("PROFILE_VELOCITY", longitud, obj);
}

static void Init_profile_acceleration(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("PROFILE_ACCELERATION", INDEX_PROFILE_ACCELERATION, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[PROFILE_ACCELERATION] = Create_dic("PROFILE_ACCELERATION", longitud, obj);
}

static void Init_profile_deceleration(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("PROFILE_DECELERATION", INDEX_PROFILE_DECELERATION, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[PROFILE_DECELERATION] = Create_dic("PROFILE_DECELERATION", longitud, obj);
}

static void Init_quick_stop_deceleration(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("QUICK_STOP_DECELERATION", INDEX_QUICK_STOP_DECELERATION, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[QUICK_STOP_DECELERATION] = Create_dic("QUICK_STOP_DECELERATION", longitud, obj);
}

static void Init_torque_slope(void)
{

    Object_t obj[1] = {};

    obj[0] = Create_object("TORQUE_SLOPE", INDEX_TORQUE_SLOPE, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TORQUE_SLOPE] = Create_dic("TORQUE_SLOPE", longitud, obj);
}
static void Init_homing_method(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("HOMING_METHOD", INDEX_HOMING_METHOD, 0x00, int_8);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[HOMING_METHOD] = Create_dic("HOMING_METHOD", longitud, obj);
}

static void Init_homing_speeds(void)
{
    Object_t obj[3] = {};

    obj[0] = Create_object("HIGHESTSUB_INDEX_SUPPORTED", INDEX_HOMING_SPEEDS, 0x00, uint_8);
    obj[1] = Create_object("SPEED_DURING_SEARCH_FOR_SWITCH", INDEX_HOMING_SPEEDS, 0x01, uint_32);
    obj[2] = Create_object("SPEED_DURING_SEARCH_FOR_ZERO", INDEX_HOMING_SPEEDS, 0x02, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[HOMING_SPEEDS] = Create_dic("HOMING_SPEEDS", longitud, obj);
}

static void Init_homing_acceleration(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("HOMING_ACCELERATION", INDEX_HOMING_ACCELERATION, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[HOMING_ACCELERATION] = Create_dic("HOMING_ACCELERATION", longitud, obj);
}

static void Init_velocity_offset(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("VELOCITY_OFFSET", INDEX_VELOCITY_OFFSET, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[VELOCITY_OFFSET] = Create_dic("VELOCITY_OFFSET", longitud, obj);
}

static void Init_torque_offset(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TORQUE_OFFSET", INDEX_TORQUE_OFFSET, 0x00, int_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TORQUE_OFFSET] = Create_dic("TORQUE_OFFSET", longitud, obj);
}

static void Init_touch_probe_function(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TOUCH_PROBE_FUNCTION", INDEX_TOUCH_PROBE_FUNCTION, 0x00, uint_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TOUCH_PROBE_FUNCTION] = Create_dic("TOUCH_PROBE_FUNCTION", longitud, obj);
}

static void Init_touch_probe_status(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TOUCH_PROBE_STATUS", INDEX_TOUCH_PROBE_STATUS, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TOUCH_PROBE_STATUS] = Create_dic("TOUCH_PROBE_STATUS", longitud, obj);
}

static void Init_touch_probe_1_positive_edge(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TOUCH_PROBE_1_POSITIVE_EDGE", INDEX_TOUCH_PROBE_1_POSITIVE_EDGE, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TOUCH_PROBE_1_POSITIVE_EDGE] = Create_dic("TOUCH_PROBE_1_POSITIVE_EDGE", longitud, obj);
}

static void Init_touch_probe_1_negative_edge(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TOUCH_PROBE_1_NEGATIVE_EDGE", INDEX_TOUCH_PROBE_1_NEGATIVE_EDGE, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TOUCH_PROBE_1_NEGATIVE_EDGE] = Create_dic("TOUCH_PROBE_1_NEGATIVE_EDGE", longitud, obj);
}

static void Init_interpolation_time_period(void)
{
    Object_t obj[3] = {};

    obj[0] = Create_object("HIGHEST_SUB_INDEX_SUPPORTED", INDEX_INTERPOLATION_TIME_PERIOD, 0x00, int_8);
    obj[1] = Create_object("INTERPOLATON_TIME_PERIOD", INDEX_INTERPOLATION_TIME_PERIOD, 0x01, uint_8);
    obj[2] = Create_object("INTERPOLATION_TIME_INDEX", INDEX_INTERPOLATION_TIME_PERIOD, 0x02, int_8);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[INTERPOLATION_TIME_PERIOD] = Create_dic("INTERPOLATION_TIME_PERIOD", longitud, obj);
}

static void Init_max_acceleration(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("MAX_ACCELERATION", INDEX_MAX_ACCELERATION, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[MAX_ACCELERATION] = Create_dic("MAX_ACCELERATION", longitud, obj);
}

static void Init_max_deceleration(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("MAX_DECELERATION", INDEX_MAX_DECELERATION, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[MAX_DECELERATION] = Create_dic("MAX_DECELERATION", longitud, obj);
}

static void Init_following_error_actual_value(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("FOLLOWING_ERROR_ACTUAL_VALUE", INDEX_FOLLOWING_ERROR_ACTUAL_VALUE, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[FOLLOWING_ERROR_ACTUAL_VALUE] = Create_dic("FOLLOWING_ERROR_ACTUAL_VALUE", longitud, obj);
}

static void Init_position_demand_internal_value(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("POSITION_DEMAND_INTERNAL_VALUE", INDEX_POSITION_DEMAND_INTERNAL_VALUE, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[POSITION_DEMAND_INTERNAL_VALUE] = Create_dic("POSITION_DEMAND_INTERNAL_VALUE", longitud, obj);
}

static void Init_digital_inputs(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("DIGITAL_INPUTS", INDEX_DIGITAL_INPUTS, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[DIGITAL_INPUTS] = Create_dic("DIGITAL_INPUTS", longitud, obj);
}

static void Init_digital_outputs(void)
{
    Object_t obj[3] = {};

    obj[0] = Create_object("HIGHEST_SUB_INDEX_SUPPORTED", INDEX_DIGITAL_OUTPUTS, 0x00, int_8);
    obj[1] = Create_object("PHYSICAL_OUTPUTS", INDEX_DIGITAL_OUTPUTS, 0x01, uint_32);
    obj[2] = Create_object("BIT_MASK", INDEX_DIGITAL_OUTPUTS, 0x02, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[DIGITAL_OUTPUTS] = Create_dic("DIGITAL_OUTPUTS", longitud, obj);
}

static void Init_target_velocity(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("TARGET_VELOCITY", INDEX_TARGET_VELOCITY, 0x00, int_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[TARGET_VELOCITY] = Create_dic("TARGET_VELOCITY", longitud, obj);
}

static void Init_suppoted_drive_mode(void)
{
    Object_t obj[1] = {};

    obj[0] = Create_object("SUPPORTED_DRIVE_MODE", INDEX_SUPPORTED_DRIVE_MODE, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    DEVICE[SUPPORTED_DRIVE_MODE] = Create_dic("SUPPORTED_DRIVE_MODE", longitud, obj);
}



/* ============= Implementacion de Interrupciones Publicas ================*/



