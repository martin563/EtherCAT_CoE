/******************************************************************************
* FileName: drive.h
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

#ifndef _DRIVE_
#define _DRIVE_


#include "../Servo/soem/ethercat.h"


#include "Type_data.h"
#include "CoE.h"
#include "Device.h"
#include "Common.h"
#include "Manufacturer.h"
#include "Sync.h"


#define HIWIN_ENCODER_COUNTS 10000


#define ECAT_RxPDO  0x1c12
#define ECAT_TxPDO  0x1c13
#define ECAT_RxPDO_MAPPING_START  0x1600
#define ECAT_TxPDO_MAPPING_START  0x1a00

#define ECAT_PDO_DISABLE_TRANSMISION  0
#define ECAT_PDO_ENABLE_TRANSMISION   1

#define CERO 0

/**
 * Operation mode
 */
#define ECAT_OPERATION_MODE_STAND_ALONE       0
#define ECAT_OPERATION_MODE_PROFILE_POSITION  1
#define ECAT_OPERATION_MODE_PROFILE_VELOCITY  3
#define ECAT_OPERATION_MODE_PROFILE_TORQUE	  4
#define ECAT_OPERATION_MODE_HOMING		      6
#define ECAT_OPERATION_MODE_CYCLIC_SYNC_POSITION 8
#define ECAT_OPERATION_MODE_CYCLIC_SYNC_VELOCITY 9
#define ECAT_OPERATION_MODE_CYCLIC_SYNC_TORQUE   10


typedef enum
{
	MASTER_TO_SLAVE,
	SLAVE_TO_MASTER,

} MS_t;


#ifdef __cplusplus
extern "C"{
#endif
void hiwin_d2_setup(uint16 slave);

uint32_t rpm_to_counts_per_s(double rpm);

void map_pdo_objects(uint16 slave, MS_t direction, Object_t objects[], int longitud);

uint32_t to_pdo_mapping(Object_t object);

int write8(uint16 slave, uint16 index, uint8 subindex, uint8 value);

int write16(uint16 slave, uint16 index, uint8 subindex, uint16 value);

int write32(uint16 slave, uint16 index, uint8 subindex, uint32 value);

#ifdef __cplusplus
}
#endif

#endif //_DRIVE_
