/******************************************************************************
* FileName: map_pdo.h
* Purpose: Librería para imprimir mapeo PDO.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 14/06/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

#ifndef _MAP_PDO_H_
#define _MAP_PDO_H_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "../Servo/soem/ethercat.h"


/* ==================== Definiciones Globales ======================== */

#define OTYPE_VAR               0x0007
#define OTYPE_ARRAY             0x0008
#define OTYPE_RECORD            0x0009

#define ATYPE_Rpre              0x01
#define ATYPE_Rsafe             0x02
#define ATYPE_Rop               0x04
#define ATYPE_Wpre              0x08
#define ATYPE_Wsafe             0x10
#define ATYPE_Wop               0x20

/* ==================== Declaracion de tipo de datos ===================== */



/* ================== Prototipo de Funciones publicas ==================*/

int si_map_sdo(int slave, char IOmap[]);

int si_map_sii(int slave, char IOmap[]);

void si_sdo(int cnt);

void slaveinfo(int slave);

/* ================ Prototipo de Interrupciones publicas ==================*/




#endif  /*  _MAP_PDO_H_ */
