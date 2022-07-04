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

/* ========== Inclusión de bibliotecas de código =======================*/

#include "Common.h"


Dic_t COMMON[MAX_OBJECTS_COMMON];

/* ============ Definicion de variables globales =======================*/


/* ============= Prototipos de funciones privadas =======================*/

static void Init_device_type(void);

static void Init_error_register(void);

static void Init_store_parameters(void);

static void Init_identity_object(void);

static void Init_cob_id_sync(void);

static void Init_communication_cycle_period(void);

/* ============= Implementacion de funciones publicas ====================*/

void Init_Common(void)
{
    //Device type
    Init_device_type();

    //Error register
    Init_error_register();

    //Store parameters
    Init_store_parameters();

    //Identity object
    Init_identity_object();


    Init_cob_id_sync();

    Init_communication_cycle_period();

}

void Print_Common(void)
{
    Print_Dic("COMMON", COMMON, MAX_OBJECTS_COMMON);
}

void Print_Common_objects(uint16 slave)
{
    Read_Dic(slave, "COMMON", COMMON, MAX_OBJECTS_COMMON);
}

/* ============= Implementacion de funciones privadas ====================*/



static void Init_device_type(void)
{
    Object_t DEVICE_TYPE_OBJECTS[1] = {};

    //Device type
    DEVICE_TYPE_OBJECTS[0] = Create_object("DEVICE_TYPE", INDEX_DEVICE_TYPE, 0x00, uint_32);

    int longitud = sizeof(DEVICE_TYPE_OBJECTS)/sizeof(DEVICE_TYPE_OBJECTS[0]);
    COMMON[DEVICE_TYPE] = Create_dic("DEVICE_TYPE", longitud, DEVICE_TYPE_OBJECTS);
}

static void Init_error_register(void)
{
    Object_t ERROR_REGISTER_OBJECTS[1] = {};

    //Error register
    ERROR_REGISTER_OBJECTS[0] = Create_object("ERROR_REGISTER", INDEX_ERROR_REGISTER, 0x00, uint_8);

    int longitud = sizeof(ERROR_REGISTER_OBJECTS)/sizeof(ERROR_REGISTER_OBJECTS[0]);
    COMMON[ERROR_REGISTER] = Create_dic("ERROR_REGISTER", longitud, ERROR_REGISTER_OBJECTS);
}

static void Init_store_parameters(void)
{
    Object_t STORE_PARAMETERS_OBJECTS[2] = {};

    //Store parameters
    STORE_PARAMETERS_OBJECTS[0] = Create_object("NUMBER_OF_ENTRIES", INDEX_STORE_PARAMETERS, 0x00, uint_8);
    STORE_PARAMETERS_OBJECTS[1] = Create_object("SAVE_ALL_PARAMETERS", INDEX_STORE_PARAMETERS, 0x01, uint_32);

    int longitud = sizeof(STORE_PARAMETERS_OBJECTS)/sizeof(STORE_PARAMETERS_OBJECTS[0]);
    COMMON[STORE_PARAMETERS] = Create_dic("STORE_PARAMETERS", longitud, STORE_PARAMETERS_OBJECTS);
}

static void Init_identity_object(void)
{
    Object_t IDENTITY_OBJECT_OBJECTS[5] = {};

    //Identity object
    IDENTITY_OBJECT_OBJECTS[0] = Create_object("NUMBER_OF_ENTRIES", INDEX_IDENTITY_OBJECT, 0x00, uint_8);
    IDENTITY_OBJECT_OBJECTS[1] = Create_object("VENDOR_ID", INDEX_IDENTITY_OBJECT, 0x01, uint_32);
    IDENTITY_OBJECT_OBJECTS[2] = Create_object("PRODUCT_CODE", INDEX_IDENTITY_OBJECT, 0x02, uint_32);
    IDENTITY_OBJECT_OBJECTS[3] = Create_object("REVISION_NUMBER", INDEX_IDENTITY_OBJECT, 0x03, uint_32);
    IDENTITY_OBJECT_OBJECTS[4] = Create_object("SERIAL_NUMBER", INDEX_IDENTITY_OBJECT, 0x04, uint_32);

    int longitud = sizeof(IDENTITY_OBJECT_OBJECTS)/sizeof(IDENTITY_OBJECT_OBJECTS[0]);
    COMMON[IDENTITY_OBJECT] = Create_dic("IDENTITY_OBJECT", longitud, IDENTITY_OBJECT_OBJECTS);
}


static void Init_cob_id_sync(void)
{
    Object_t obj[1] = {};

    //Identity object
    obj[0] = Create_object("COB_ID_SYNC", INDEX_COB_ID_SYNC, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    COMMON[COB_ID_SYNC] = Create_dic("COB_ID_SYNC", longitud, obj);
}

static void Init_communication_cycle_period(void)
{
    Object_t obj[1] = {};

    //Identity object
    obj[0] = Create_object("COMMUNICATION_CYCLE_PERIOD", INDEX_COMMUNICATION_CYCLE_PERIOD, 0x00, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    COMMON[COMMUNICATION_CYCLE_PERIOD] = Create_dic("COMMUNICATION_CYCLE_PERIOD", longitud, obj);
}



/* ============= Implementacion de Interrupciones Publicas ================*/






