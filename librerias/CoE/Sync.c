/******************************************************************************
* FileName: sync.h
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

/* ========== Inclusión de bibliotecas de código =======================*/
#include "Sync.h"

Dic_t SYNC[MAX_OBJECTS_SYNC];


/* ============ Definicion de variables globales =======================*/


/* ============= Prototipos de funciones privadas =======================*/

static void Init_sync_manager_communication_type(void);

static void Init_sync_manager_0_PDO_assignment(void);

static void Init_sync_manager_1_PDO_assignment(void);

static void Init_sync_manager_2_PDO_assignment(void);

static void Init_sync_manager_3_PDO_assignment(void);

static void Init_sync_manager_2_synchronization(void);

static void Init_sync_manager_3_synchronization(void);

static void Init_sync_manager_0(void);

static void Init_receive_pdo_communication_parameters(void);


/* ============= Implementacion de funciones publicas ====================*/

void Init_Sync(void)
{
    //Sync manager communication type
    Init_sync_manager_communication_type();

    //Sync manager 0 PDO assignment
    Init_sync_manager_0_PDO_assignment();

    //Sync manager 1 PDO assignment
    Init_sync_manager_1_PDO_assignment();

    //Sync manager 2 PDO assignment
    Init_sync_manager_2_PDO_assignment();

    //Sync manager 3 PDO assignment
    Init_sync_manager_3_PDO_assignment();

    //Sync manager 2 synchronization
    Init_sync_manager_2_synchronization();

    //Sync manager 3 synchronization
    Init_sync_manager_3_synchronization();

    //Sync manager 0
    Init_sync_manager_0();

    Init_receive_pdo_communication_parameters();

}

void Print_Sync(void)
{
    Print_Dic("SYNC", SYNC, MAX_OBJECTS_SYNC);
}

void Print_Sync_objects(uint16 slave)
{
    Read_Dic(slave, "SYNC", SYNC, MAX_OBJECTS_SYNC);
}


/* ============= Implementacion de funciones privadas ====================*/

static void Init_sync_manager_communication_type(void)
{
    Object_t SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS[5] = {};

    //Sync manager communication type
    SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS[0] = Create_object("NUMBER_OF_USED_SYNC_MANAGER", INDEX_SYNC_MANAGER_COMMUNICATION_TYPE, 0x00, uint_8);
    SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS[1] = Create_object("COMMUNICATION_TYPE_SYNC_MANAGER_0", INDEX_SYNC_MANAGER_COMMUNICATION_TYPE, 0x01, uint_8);
    SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS[2] = Create_object("COMMUNICATION_TYPE_SYNC_MANAGER_1", INDEX_SYNC_MANAGER_COMMUNICATION_TYPE, 0x02, uint_8);
    SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS[3] = Create_object("COMMUNICATION_TYPE_SYNC_MANAGER_2", INDEX_SYNC_MANAGER_COMMUNICATION_TYPE, 0x03, uint_8);
    SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS[4] = Create_object("COMMUNICATION_TYPE_SYNC_MANAGER_3", INDEX_SYNC_MANAGER_COMMUNICATION_TYPE, 0x04, uint_8);

    int longitud = sizeof(SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS)/sizeof(SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS[0]);
    SYNC[SYNC_MANAGER_COMMUNICATION_TYPE] = Create_dic("SYNC_MANAGER_COMMUNICATION_TYPE", longitud, SYNC_MANAGER_COMMUNICATION_TYPE_OBJECTS);
}

static void Init_sync_manager_0_PDO_assignment(void)
{
    Object_t SYNC_MANAGER_0_PDO_ASSIGNMENT_OBJECTS[1] = {};

    //Sync manager 0 PDO assignment
    SYNC_MANAGER_0_PDO_ASSIGNMENT_OBJECTS[0] = Create_object("NUMBER_OF_ASSIGNED_PDOs", INDEX_SYNC_MANAGER_0_PDO_ASSIGNMENT, 0x00, uint_8);

    int longitud = sizeof(SYNC_MANAGER_0_PDO_ASSIGNMENT_OBJECTS)/sizeof(SYNC_MANAGER_0_PDO_ASSIGNMENT_OBJECTS[0]);
    SYNC[SYNC_MANAGER_0_PDO_ASSIGNMENT] = Create_dic("SYNC_MANAGER_0_PDO_ASSIGNMENT", longitud, SYNC_MANAGER_0_PDO_ASSIGNMENT_OBJECTS);
}

static void Init_sync_manager_1_PDO_assignment(void)
{
    Object_t SYNC_MANAGER_1_PDO_ASSIGNMENT_OBJECTS[1] = {};

    //Sync manager 1 PDO assignment
    SYNC_MANAGER_1_PDO_ASSIGNMENT_OBJECTS[0] = Create_object("NUMBER_OF_ASSIGNED_PDOs", INDEX_SYNC_MANAGER_1_PDO_ASSIGNMENT, 0x00, uint_8);

    int longitud = sizeof(SYNC_MANAGER_1_PDO_ASSIGNMENT_OBJECTS)/sizeof(SYNC_MANAGER_1_PDO_ASSIGNMENT_OBJECTS[0]);
    SYNC[SYNC_MANAGER_1_PDO_ASSIGNMENT] = Create_dic("SYNC_MANAGER_1_PDO_ASSIGNMENT", longitud, SYNC_MANAGER_1_PDO_ASSIGNMENT_OBJECTS);
}

static void Init_sync_manager_2_PDO_assignment(void)
{
    Object_t SYNC_MANAGER_2_PDO_ASSIGNMENT_OBJECTS[2] = {};

    //Sync manager 2 PDO assignment
    SYNC_MANAGER_2_PDO_ASSIGNMENT_OBJECTS[0] = Create_object("NUMBER_OF_ASSIGNED_RxPDO", INDEX_SYNC_MANAGER_2_PDO_ASSIGNMENT, 0x00, uint_8);
    SYNC_MANAGER_2_PDO_ASSIGNMENT_OBJECTS[1] = Create_object("PDO_MAPPING_INDEX_OF_ASSIGNED_RxPDO", INDEX_SYNC_MANAGER_2_PDO_ASSIGNMENT, 0x01, uint_16);

    int longitud = sizeof(SYNC_MANAGER_2_PDO_ASSIGNMENT_OBJECTS)/sizeof(SYNC_MANAGER_2_PDO_ASSIGNMENT_OBJECTS[0]);
    SYNC[SYNC_MANAGER_2_PDO_ASSIGNMENT] = Create_dic("SYNC_MANAGER_2_PDO_ASSIGNMENT", longitud, SYNC_MANAGER_2_PDO_ASSIGNMENT_OBJECTS);
}

static void Init_sync_manager_3_PDO_assignment(void)
{
    Object_t SYNC_MANAGER_3_PDO_ASSIGNMENT_OBJECTS[2] = {};

    //Sync manager 3 PDO assignment
    SYNC_MANAGER_3_PDO_ASSIGNMENT_OBJECTS[0] = Create_object("NUMBER_OF_ASSIGNED_RxPDO", INDEX_SYNC_MANAGER_3_PDO_ASSIGNMENT, 0x00, uint_8);
    SYNC_MANAGER_3_PDO_ASSIGNMENT_OBJECTS[1] = Create_object("PDO_MAPPING_INDEX_OF_ASSIGNED_TxPDO", INDEX_SYNC_MANAGER_3_PDO_ASSIGNMENT, 0x01, uint_16);

    int longitud = sizeof(SYNC_MANAGER_3_PDO_ASSIGNMENT_OBJECTS)/sizeof(SYNC_MANAGER_3_PDO_ASSIGNMENT_OBJECTS[0]);
    SYNC[SYNC_MANAGER_3_PDO_ASSIGNMENT] = Create_dic("SYNC_MANAGER_3_PDO_ASSIGNMENT", longitud, SYNC_MANAGER_3_PDO_ASSIGNMENT_OBJECTS);
}

static void Init_sync_manager_2_synchronization(void)
{
    Object_t SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[10] = {};

    //Sync manager 2 synchronization
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[0] = Create_object("NUMBER_OF_SYNCHRONIZATION_PARAMETERS", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x00, uint_8);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[1] = Create_object("SYNCHRONIZATION_TYPE", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x01, uint_16);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[2] = Create_object("CYCLE_TIME", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x02, uint_32);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[3] = Create_object("RESERVED_1", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x03, uint_32);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[4] = Create_object("SYNCHRONIZATION_TYPE_SUPPORTED", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x04, uint_16);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[5] = Create_object("MINIMUM_CYCLE_TIME", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x05, uint_32);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[6] = Create_object("CALC_AND_COPY_TIME", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x06, uint_32);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[7] = Create_object("RESERVED_2", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x07, uint_32);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[8] = Create_object("RESERVED_3", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x08, uint_16);
    SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[9] = Create_object("DELAY_TIME", INDEX_SYNC_MANAGER_2_SYNCHRONIZATION, 0x09, uint_32);

    int longitud = sizeof(SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS)/sizeof(SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS[0]);
    SYNC[SYNC_MANAGER_2_SYNCHRONIZATION] = Create_dic("SYNC_MANAGER_2_SYNCHRONIZATION", longitud, SYNC_MANAGER_2_SYNCHRONIZATION_OBJECTS);
}

static void Init_sync_manager_3_synchronization(void)
{
    Object_t SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[10] = {};

    //Sync manager 3 synchronization
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[0] = Create_object("NUMBER_OF_SYNCHRONIZATION_PARAMETERS", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x00, uint_8);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[1] = Create_object("SYNCHRONIZATION_TYPE", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x01, uint_16);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[2] = Create_object("CYCLE_TIME", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x02, uint_32);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[3] = Create_object("RESERVED_1", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x03, uint_32);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[4] = Create_object("SYNCHRONIZATION_TYPE_SUPPORTED", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x04, uint_16);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[5] = Create_object("MINIMUM_CYCLE_TIME", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x05, uint_32);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[6] = Create_object("CALC_AND_COPY_TIME", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x06, uint_32);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[7] = Create_object("RESERVED_2", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x07, uint_32);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[8] = Create_object("RESERVED_3", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x08, uint_16);
    SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[9] = Create_object("DELAY_TIME", INDEX_SYNC_MANAGER_3_SYNCHRONIZATION, 0x09, uint_32);

    int longitud = sizeof(SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS)/sizeof(SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS[0]);
    SYNC[SYNC_MANAGER_3_SYNCHRONIZATION] = Create_dic("SYNC_MANAGER_3_SYNCHRONIZATION", longitud, SYNC_MANAGER_3_SYNCHRONIZATION_OBJECTS);
}

static void Init_sync_manager_0(void)
{
    Object_t obj[6] = {};

    obj[0] = Create_object("HIGHEST_SUB_INDEX_SUPPORTED", INDEX_SYNC_MANAGER_0, 0x00, uint_8);
    obj[1] = Create_object("COB_ID_ENCODING", INDEX_SYNC_MANAGER_0, 0x01, uint_32);
    obj[2] = Create_object("TRANSMISSION_TYPE", INDEX_SYNC_MANAGER_0, 0x02, uint_8);
    obj[3] = Create_object("INHIBIT_TIME", INDEX_SYNC_MANAGER_0, 0x03, uint_16);
    obj[4] = Create_object("RESERVED", INDEX_SYNC_MANAGER_0, 0x04, uint_8);
    obj[5] = Create_object("EVENT_TIMER", INDEX_SYNC_MANAGER_0, 0x05, uint_16);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    SYNC[SYNC_MANAGER_0] = Create_dic("SYNC_MANAGER_0", longitud, obj);
}


static void Init_receive_pdo_communication_parameters(void)
{
    Object_t obj[2] = {};

    obj[0] = Create_object("NUMBER_OF_SUB_ELEMENTS", INDEX_RECEIVE_PDO_COMMUNICATION_PARAMETERS, 0x00, uint_8);
    obj[1] = Create_object("PDO_COB_ID", INDEX_RECEIVE_PDO_COMMUNICATION_PARAMETERS, 0x01, uint_32);

    int longitud = sizeof(obj)/sizeof(obj[0]);
    SYNC[RECEIVE_PDO_COMMUNICATION_PARAMETERS] = Create_dic("RECEIVE_PDO_COMMUNICATION_PARAMETERS", longitud, obj);
}

/* ============= Implementacion de Interrupciones Publicas ================*/






