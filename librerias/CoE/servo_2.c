/******************************************************************************
* FileName: servo_2.c
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

/* ========== Inclusión de bibliotecas de código =======================*/
#include <stdio.h>

#include "servo_2.h"

extern Dic_t SYNC[];
extern Dic_t COMMON[];
extern Dic_t DEVICE[];
extern Dic_t MANUFACTURER[];


/* ============ Definicion de variables globales =======================*/


/* ============= Prototipos de funciones privadas =======================*/

static uint8_t Recortar_16_bits_a_8(uint16_t var);

static status_servo_t Maq_servo_state(uint8_t state_8);

static int16 Det_ON_OFF(uint16 bit);

/* ============= Implementacion de funciones publicas ====================*/

status_servo_t servo_get_state(uint16 slave)
{
    uint16 state;
    get_object(slave, DEVICE[STATUSWORD].obj[0], &state);

    uint8 state_8 = Recortar_16_bits_a_8(state);
    state_8 = state_8 & 0b01101111;

    status_servo_t State_servo = Maq_servo_state(state_8);

    return(State_servo);
}

void servo_send_command(uint16 slave, command_servo_t cmd)
{
    uint16 control_word = 0;
    uint16 control_word_new;
    get_object(slave, DEVICE[CONTROLWORD].obj[0], &control_word);
    printf("Control_word=0x%X)\n", control_word);

    char *string_cmd;

    switch(cmd)
    {
        case SHUTDOWN:
            control_word_new = 0b0000000000000110;
            control_word_new |= (control_word & 0b1111111101111000);
            //control_word |= 0b0000000000000110;
            //control_word &= 0b1111111101111110;
            string_cmd = "SHUTDOWN";
        break;
        case SWITCH_ON:
            control_word_new = 0b0000000000000111;
            control_word_new |= (control_word & 0b1111111101110000);
            //control_word |= 0b0000000000000111;
            //control_word &= 0b1111111101110111;
            string_cmd = "SWITCH_ON";
        break;
        case ENABLE_OPERATION:
            control_word_new = 0b0000000000001111;
            control_word_new |= (control_word & 0b1111111101110000);
            //control_word |= 0b0000000000001111;
            //control_word &= 0b1111111101111111;
            string_cmd = "ENABLE_OPERATION";
        break;
        case DISABLE_OPERATION:
            control_word_new = 0b0000000000000111;
            control_word_new |= (control_word & 0b1111111101110000);
            //control_word |= 0b0000000000000111;
            //control_word &= 0b1111111101110111;
            string_cmd = "DISABLE_OPERATION";
        break;
        case FAULT_RESET:
            control_word_new = 0b0000000010000000;
            control_word_new |= (control_word & 0b1111111101111111);
            //control_word |= 0b0000000010000000;
            string_cmd = "FAULT_RESET";
        break;
        default:
            string_cmd = "Invalid command";
    }

    printf("servo_send_command: %s (controlword=0x%X)\n", string_cmd, control_word_new);
    set_object(slave, DEVICE[CONTROLWORD].obj[0], control_word_new);

}


int has_servo_arrived(uint16 slave)
{
    int res = 0;
    uint16 status_word;
    get_object(slave, DEVICE[STATUSWORD].obj[0], &status_word);

    status_word = status_word  & (1 << 10);
    if(status_word)
    {
        res = 1;
    }

    return( res );
}


void servo_set_position(uint16 slave, int32 position_counts, uint32 velocity_rpm, uint32 acceleration_rpm_s)
{
    set_object(slave, DEVICE[TARGET_POSITION].obj[0], position_counts);
    set_object(slave, DEVICE[PROFILE_VELOCITY].obj[0], rpm_to_counts_per_s(velocity_rpm) );

    uint32 acceleration_count_s2 = rpm_to_counts_per_s(acceleration_rpm_s);
    set_object(slave, DEVICE[PROFILE_ACCELERATION].obj[0], acceleration_count_s2 );
    set_object(slave, DEVICE[MAX_ACCELERATION].obj[0], (uint32) acceleration_count_s2*1.5 );
    set_object(slave, DEVICE[PROFILE_DECELERATION].obj[0], acceleration_count_s2 );
    set_object(slave, DEVICE[MAX_DECELERATION].obj[0], (uint32) acceleration_count_s2*1.5 );

    uint16 control_word;
    get_object(slave, DEVICE[CONTROLWORD].obj[0], &control_word);


    if( control_word & (1 << 4) )
    {
        //# clear the bit4 so we can start raising it in the next round
        control_word &= 0b1111111111101111;
        set_object(slave, DEVICE[CONTROLWORD].obj[0], control_word);
    }

    //# Rising edge of bit 4 takes target position as new absolute position
    //# bit 5 = 1 -> Move to new absolute target position immediately.
    control_word |= 0b0000000000010000;
    set_object(slave, DEVICE[CONTROLWORD].obj[0], control_word);

    //# clear the bit4 so we can start raising it in the next round
    control_word &= 0b1111111111001111;
    set_object(slave, DEVICE[CONTROLWORD].obj[0], control_word);
}

void servo_set_position_sync(uint16 slave, uint16_t control_word)
{
    //set_object(slave, DEVICE[TARGET_POSITION].obj[0], position_counts);

    //uint16 control_word;
    //get_object(slave, DEVICE[CONTROLWORD].obj[0], &control_word);

    control_word &= 0b1111101110001111;

    if( control_word & (1 << 4) )
    {
        //# clear the bit4 so we can start raising it in the next round
        control_word &= 0b1111111111101111;
        //set_object(slave, DEVICE[CONTROLWORD].obj[0], control_word);
    }

    //# Rising edge of bit 4 takes target position as new absolute position
    //# bit 5 = 1 -> Move to new absolute target position immediately.
    control_word |= 0b0000000000010000;
    set_object(slave, DEVICE[CONTROLWORD].obj[0], control_word);

    //# clear the bit4 so we can start raising it in the next round
    control_word &= 0b1111111111101111;
    set_object(slave, DEVICE[CONTROLWORD].obj[0], control_word);
}


void Print_sync(uint16 slave)
{
    int32 pos, vel, error_actual;
    //uint32 error_window;
    int16 torque;
    //uint16 enable_pos_limit, error_time_out;
    //uint8 time_interpolation;


    get_object(slave, DEVICE[POSITION_DEMAND_INTERNAL_VALUE].obj[0], &pos);
    printf("Position internal value = %d counts\n", pos);
    get_object(slave, DEVICE[POSITION_ACTUAL_VALUE].obj[0], &pos);
    printf("Position actual value = %d counts\n", pos);


    get_object(slave, DEVICE[VELOCITY_ACTUAL_VALUE].obj[0], &vel);
    printf("Velocity actual = %d counts/s\n", vel);
    get_object(slave, DEVICE[TORQUE_ACTUAL_VALUE].obj[0], &torque);
    printf("Torque actual = %d counts/s2\n", torque);
    get_object(slave, DEVICE[FOLLOWING_ERROR_ACTUAL_VALUE].obj[0], &error_actual);
    printf("error actual = %d counts\n", error_actual);


    uint16 status_word, control_word, bit_10, bit_11, bit_12, bit_13;
    get_object(slave, DEVICE[STATUSWORD].obj[0], &status_word);
    bit_10 = Det_ON_OFF( status_word & ( 1 << 10 ) );
    bit_11 = Det_ON_OFF( status_word & ( 1 << 11 ) );
    bit_12 = Det_ON_OFF( status_word & ( 1 << 12 ) );
    bit_13 = Det_ON_OFF( status_word & ( 1 << 13 ) );

    get_object(slave, DEVICE[CONTROLWORD].obj[0], &control_word);

    printf("CONTROL WORD = 0x%X\n", control_word);
    printf("STATUS WORD  = 0x%X\n", status_word);
    printf("Reach target position = %d\nInternal Limit active = %d\n", bit_10, bit_11);
    printf("Ignore target position = %d\nFollowing error = %d\n", bit_12, bit_13);

}


/* ============= Implementacion de funciones privadas ====================*/

static uint8_t Recortar_16_bits_a_8(uint16_t var)
{
    uint16_t aux;

    for(int i=0; i < 8; i++)
    {
        aux += ( var & (1 << i) );
    }

    uint8_t res = (uint8_t) aux;
    return res;
}

static status_servo_t Maq_servo_state(uint8_t state_8)
{
    status_servo_t state_servo;
    char *string_state;

    if(state_8 == 0b00000000 || state_8 == 0b00100000)
    {
        state_servo = DRIVE_NOT_READY_TO_SWITCH_ON;
        string_state = "DRIVE_NOT_READY_TO_SWITCH_ON";
    }
    else if(state_8 == 0b01000000 || state_8 == 0b01100000)
    {
        state_servo = DRIVE_SWITCH_ON_DISABLED;
        string_state = "DRIVE_SWITCH_ON_DISABLED";
    }
    else if(state_8 == 0b00100001 )
    {
        state_servo = DRIVE_READY_TO_SWITCH_ON;
        string_state = "DRIVE_READY_TO_SWITCH_ON";
    }
    else if(state_8 == 0b00100011 )
    {
        state_servo = DRIVE_SWITCH_ON;
        string_state = "DRIVE_SWITCH_ON";
    }
    else if(state_8 == 0b00100111 )
    {
        state_servo = DRIVE_OPERATION_ENABLED;
        string_state = "DRIVE_OPERATION_ENABLED";
    }
    /*else if(state_8 == 0b00000111 )
    {
        state_servo = DRIVE_QUICK_STOP_ACTIVE;
        string_state = "DRIVE_QUICK_STOP_ACTIVE";
    }*/
    else if(state_8 == 0b00001111) // || state_8 == 0b00101111)
    {
        state_servo = DRIVE_FAULT_REACTION_ACTIVE;
        string_state = "DRIVE_FAULT_REACTION_ACTIVE";
    }
    else if(state_8 == 0b00101000)    //(state_8 == 0b0000 1000 || state_8 == 0b0010 1000)
    {
        state_servo = DRIVE_FAULT;
        string_state = "DRIVE_FAULT";
    }
    else
    {
        state_servo = DRIVE_UNKOWN_STATE;
        string_state = "DRIVE_UNKOWN_STATE";
    }

    printf("get_servo_state: %s (statusword=0x%X)\n", string_state, state_8);
    return(state_servo);
}


static int16 Det_ON_OFF(uint16 bit)
{
    int16 res;

    if( bit != 0 )
    {
        res = 1;
    }
    else
    {
        res = 0;
    }

    return(res);
}





/* ============= Implementacion de Interrupciones Publicas ================*/



