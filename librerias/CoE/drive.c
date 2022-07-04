/******************************************************************************
* FileName: drive.c
* Purpose: Librería drive para SOEM basada en ejemplo python.
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

#include "drive.h"



/* ============ Definicion de variables globales =======================*/

extern Dic_t SYNC[];
extern Dic_t COMMON[];
extern Dic_t DEVICE[];
extern Dic_t MANUFACTURER[];

/* ============= Prototipos de funciones privadas =======================*/

/* ============= Implementacion de funciones publicas ====================*/

void hiwin_d2_setup(uint16 slave)
{
    int longitud;
    //uint32_t velocity_rpm, acceleration_rpm_s, acceleration_count_s2;

    Init_Sync();
    Init_Common();
    Init_Device();
    Init_Manufacturer();

    set_object(slave, DEVICE[MODE_OF_OPERATION].obj[0], ECAT_OPERATION_MODE_CYCLIC_SYNC_POSITION);
    uint8_t modo = 0;
    get_object(slave, DEVICE[MODE_OF_OPERATION_DISPLAY].obj[0], &modo);
    printf("MODO OP DISPLAY %d SLAVE\n", modo);

    //# setup PDOs
    Object_t master_to_slave_pdos[2] = {};
    master_to_slave_pdos[0] = DEVICE[CONTROLWORD].obj[0];
    master_to_slave_pdos[1] = DEVICE[TARGET_POSITION].obj[0];
    /*master_to_slave_pdos[2] = DEVICE[VELOCITY_OFFSET].obj[0];
    master_to_slave_pdos[3] = DEVICE[TORQUE_OFFSET].obj[0];
    master_to_slave_pdos[4] = DEVICE[MODE_OF_OPERATION].obj[0];
    master_to_slave_pdos[5] = DEVICE[DIGITAL_OUTPUTS].obj[0];*/
    longitud = sizeof(master_to_slave_pdos)/sizeof(master_to_slave_pdos[0]);
    map_pdo_objects(slave, MASTER_TO_SLAVE, master_to_slave_pdos, longitud);

    Object_t slave_to_master_pdos[3] = {};
    slave_to_master_pdos[0] = DEVICE[STATUSWORD].obj[0];
    slave_to_master_pdos[1] = DEVICE[POSITION_ACTUAL_VALUE].obj[0];
    slave_to_master_pdos[2] = DEVICE[FOLLOWING_ERROR_ACTUAL_VALUE].obj[0];
    /*slave_to_master_pdos[3] = DEVICE[VELOCITY_ACTUAL_VALUE].obj[0];
    slave_to_master_pdos[4] = DEVICE[TORQUE_ACTUAL_VALUE].obj[0];
    slave_to_master_pdos[5] = DEVICE[MODE_OF_OPERATION_DISPLAY].obj[0];
    slave_to_master_pdos[6] = DEVICE[DIGITAL_INPUTS].obj[0];*/

    longitud = sizeof(slave_to_master_pdos)/sizeof(slave_to_master_pdos[0]);
    map_pdo_objects(slave, SLAVE_TO_MASTER, slave_to_master_pdos, longitud);

}

uint32_t rpm_to_counts_per_s(double rpm)
{
    uint32_t res = (uint32_t) (rpm/60)*HIWIN_ENCODER_COUNTS;
    //printf("resultado rpm_to_counts_per_s = %d \n", res);
    return res;
}


void map_pdo_objects(uint16 slave, MS_t direction, Object_t objects[], int longitud)
{
    uint16_t Xx_PDO, Xx_MAPPING_START;
    uint32_t p;
    int os;

    if( direction == MASTER_TO_SLAVE)
    {
        //ECAT_RxPDO = 0x1c12
        Xx_PDO = ECAT_RxPDO;
        Xx_MAPPING_START = ECAT_RxPDO_MAPPING_START;
	}
    else if( direction == SLAVE_TO_MASTER )
    {
        //ECAT_TxPDO = 0x1c13
        Xx_PDO = ECAT_TxPDO;
        Xx_MAPPING_START = ECAT_TxPDO_MAPPING_START;
	}
    else
    {
        printf("invalid direction in map_pdo_objects\n");
	}

	p = ECAT_PDO_DISABLE_TRANSMISION;
    os = sizeof(p);
	int valor = ec_SDOwrite(slave, Xx_PDO, 0, FALSE, os, &p, EC_TIMEOUTSAFE);
    Error_wkc(valor, "1");

	valor = ec_SDOwrite(slave, Xx_MAPPING_START, 0, FALSE, os, &p, EC_TIMEOUTSAFE);
    Error_wkc(valor, "2");


    if( !(longitud > 0 && longitud < 8) )
    {
        printf("Too many mapping objects in map_pdo_objects\n");
        printf("longitud %d\n", longitud);
	}

	for(int i=0; i<longitud; i++)
    {
        p = to_pdo_mapping(objects[i]);
        os = sizeof(p);
        valor = ec_SDOwrite(slave, Xx_MAPPING_START, i+1, FALSE, os, &p, EC_TIMEOUTSAFE);
        Error_wkc(valor, "3");
	}

    //# set the number of objects mapped
    p = longitud;
	os = sizeof(p);
	valor = ec_SDOwrite(slave, Xx_MAPPING_START, 0, FALSE, os, &p, EC_TIMEOUTSAFE);
    Error_wkc(valor, "4");

    p = Xx_MAPPING_START;
	os = sizeof(p);
	valor = ec_SDOwrite(slave, Xx_PDO, 1, FALSE, os, &p, EC_TIMEOUTSAFE);
	Error_wkc(valor, "5");

	p = ECAT_PDO_ENABLE_TRANSMISION;
	os = sizeof(p);
	valor = ec_SDOwrite(slave, Xx_PDO, 0, FALSE, os, &p, EC_TIMEOUTSAFE);
	Error_wkc(valor, "6");
}


uint32_t to_pdo_mapping(Object_t object)
{
    uint32_t size_code = 0x0000;

    if(object.type == int_32 || object.type == uint_32 || object.type == real_32)
    {
        size_code = 0x0020;
    }
    else if(object.type == int_16 || object.type == uint_16)
    {
        size_code = 0x0010;
    }
    else if(object.type == int_8 || object.type == uint_8)
    {
        size_code = 0x0008;
    }
    else
    {
        printf("Unsupported type in to_pdo_mapping\n");
	}

	//printf("resultado = %X\n", (object.index << 16) + size_code);
	return( (object.index << 16) + size_code );
}


int write8(uint16 slave, uint16 index, uint8 subindex, uint8 value)
{
    int wck;
    wck = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(value), &value, EC_TIMEOUTRXM);
    printf("Write8 => Slave: %u, Index: 0x%4.4x Subindex: %u, Size %lu, Value:  0x%4.4x , wck %i\n", slave, index, subindex, sizeof(value),value, wck);
    if (wck==0)
    {
        printf("WARNING: wck equal to zero.\n");
    }
    return wck;
}


int write16(uint16 slave, uint16 index, uint8 subindex, uint16 value)
{
    int wck;
    wck = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(value), &value, EC_TIMEOUTRXM);
    printf("Write16 => Slave: %u, Index: 0x%4.4x Subindex: %u, Size %lu, Value:  0x%4.4x , wck %i\n", slave, index, subindex, sizeof(value),value, wck);
    if (wck==0)
    {
        printf("WARNING: wck equal to zero.\n");
    }
    return wck;
}


int write32(uint16 slave, uint16 index, uint8 subindex, uint32 value)
{
    int wck;
    wck = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(value), &value, EC_TIMEOUTRXM);
    printf("Write32 => Slave: %u, Index: 0x%4.4x Subindex: %u, Size %lu, Value:  0x%4.4x , wck %i\n", slave, index, subindex, sizeof(value),value, wck);
    if (wck==0)
    {
        printf("WARNING: wck equal to zero.\n");
    }
    return wck;
}

/* ============= Implementacion de funciones privadas ====================*/


/* ============= Implementacion de Interrupciones Publicas ================*/



