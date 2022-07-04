/******************************************************************************
* FileName: Type_data.con
* Purpose: Librería para definir tipo de datos en comun con otros modulos.
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
#include "Type_data.h"

/* ============ Definicion de variables globales =======================*/


/* ============= Prototipos de funciones privadas =======================*/

static case_type_t Type_data_object(Object_t object);

static uint8_t num_bytes(Object_t obj);

static void msj_error_type_data_object(void);

static char *msj_type_t(Type_t type);

static void value_object(uint16 slave, Object_t obj);

/* ============= Implementacion de funciones publicas ====================*/

Object_t Create_object(char name[], uint16_t index, uint8_t sub_index, Type_t type)
{
    Object_t obj;

    obj.name = name;
    obj.index = index;
    obj.sub_index = sub_index;
    obj.type = type;
    obj.size = num_bytes(obj);

    return obj;
}

Dic_t Create_dic(char name[], int N_obj, Object_t obj[])
{
    Dic_t reg;

    reg.name = name;
    reg.N_obj = N_obj;

    for(int i=0; i<N_obj; i++)
    {
        reg.obj[i] = obj[i];
    }

    return reg;
}

void set_object(uint16 slave, Object_t object, float value)
{
    int8 p_8;
    int16 p_16;
    int32 p_32;
    uint8 up_8;
    uint16 up_16;
    uint32 up_32;
    float f_32;
    int os, cont;
    case_type_t type;

    type = Type_data_object(object);
    switch(type)
    {
        case int_8_bits:
            p_8 = (int8) value;
            os = sizeof(p_8);
            cont = ec_SDOwrite(slave, object.index, object.sub_index, FALSE, os, &p_8, EC_TIMEOUTSAFE);
        break;
        case int_16_bits:
            p_16 = (int16) value;
            os = sizeof(p_16);
            cont = ec_SDOwrite(slave, object.index, object.sub_index, FALSE, os, &p_16, EC_TIMEOUTSAFE);
        break;
        case int_32_bits:
            p_32 = (int32) value;
            os = sizeof(p_32);
            cont = ec_SDOwrite(slave, object.index, object.sub_index, FALSE, os, &p_32, EC_TIMEOUTSAFE);
        break;
        case uint_8_bits:
            up_8 = (uint8) value;
            os = sizeof(up_8);
            cont = ec_SDOwrite(slave, object.index, object.sub_index, FALSE, os, &up_8, EC_TIMEOUTSAFE);
        break;
        case uint_16_bits:
            up_16 = (uint16) value;
            os = sizeof(up_16);
            cont = ec_SDOwrite(slave, object.index, object.sub_index, FALSE, os, &up_16, EC_TIMEOUTSAFE);
        break;
        case uint_32_bits:
            up_32 = (uint32) value;
            os = sizeof(up_32);
            cont = ec_SDOwrite(slave, object.index, object.sub_index, FALSE, os, &up_32, EC_TIMEOUTSAFE);
        break;
        case real_32_bits:
            f_32 = value;
            os = sizeof(f_32);
            cont = ec_SDOwrite(slave, object.index, object.sub_index, FALSE, os, &f_32, EC_TIMEOUTSAFE);
        break;
        default:
            msj_error_type_data_object();
    }

    char buffer[100];
    strcat(strcpy(buffer, "set_element "), object.name);
    Error_wkc(cont, buffer);
}

void get_object(uint16 slave, Object_t object, void *value)
{
    int8 *p_8;
    int16 *p_16;
    int32 *p_32;
    uint8 *up_8;
    uint16 *up_16;
    uint32 *up_32;
    float *f_32;
    int os, cont;
    case_type_t type;

    type = Type_data_object(object);
    switch(type)
    {
        case int_8_bits:
            p_8 = value;
            os = sizeof(*p_8);
            cont = ec_SDOread(slave, object.index, object.sub_index, FALSE, &os, p_8, EC_TIMEOUTSAFE);
        break;
        case int_16_bits:
            p_16 = value;
            os = sizeof(*p_16);
            cont = ec_SDOread(slave, object.index, object.sub_index, FALSE, &os, p_16, EC_TIMEOUTSAFE);
        break;
        case int_32_bits:
            p_32 = value;
            os = sizeof(*p_32);
            cont = ec_SDOread(slave, object.index, object.sub_index, FALSE, &os, p_32, EC_TIMEOUTSAFE);
        break;
        case uint_8_bits:
            up_8 = value;
            os = sizeof(*up_8);
            cont = ec_SDOread(slave, object.index, object.sub_index, FALSE, &os, up_8, EC_TIMEOUTSAFE);
        break;
        case uint_16_bits:
            up_16 = value;
            os = sizeof(*up_16);
            cont = ec_SDOread(slave, object.index, object.sub_index, FALSE, &os, up_16, EC_TIMEOUTSAFE);
        break;
        case uint_32_bits:
            up_32 = value;
            os = sizeof(*up_32);
            cont = ec_SDOread(slave, object.index, object.sub_index, FALSE, &os, up_32, EC_TIMEOUTSAFE);
        break;
        case real_32_bits:
            f_32 = value;
            os = sizeof(*f_32);
            cont = ec_SDOread(slave, object.index, object.sub_index, FALSE, &os, f_32, EC_TIMEOUTSAFE);
        break;
        default:
            msj_error_type_data_object();
    }

    char buffer[100];
    strcat(strcpy(buffer, "get_element "), object.name);
    Error_wkc(cont, buffer);
}

void Print_Dic(char *name_dic ,Dic_t dic[], int max_obj)
{
    Object_t objetos;

    printf("================== Diccionario %s ==================\n", name_dic);
    for(int i=0; i<max_obj; i++)
    {
        printf("%s %d:\n", name_dic, i);
        printf("--- name = %s\n", dic[i].name);
        printf("--- N_obj = %d\n", dic[i].N_obj);
        printf("--- Objetos:\n");

        for(int j=0; j<dic[i].N_obj ; j++)
        {
            printf("    N° %d:\n", j+1);
            objetos = dic[i].obj[j];
            printf("        name = %s\n", objetos.name );
            printf("        index = 0x%X\n", objetos.index );
            printf("        sub_index = 0x%X\n", objetos.sub_index );
            printf("        type = %s\n", msj_type_t(objetos.type) );
            printf("        size = %d bytes\n", objetos.size );
        }
        printf("\n");
    }
}

void Read_Dic(uint16 slave, char *name_dic, Dic_t dic[], int max_obj)
{
    Object_t objetos;

    printf("================== Diccionario %s ==================\n", name_dic);
    for(int i=0; i<max_obj; i++)
    {
        printf("%s %d:\n", name_dic, i);
        printf("--- name = %s\n", dic[i].name);
        printf("--- N_obj = %d\n", dic[i].N_obj);
        printf("--- Objetos:\n");

        for(int j=0; j<dic[i].N_obj ; j++)
        {
            printf("    N° %d:\n", j+1);
            objetos = dic[i].obj[j];
            printf("        name = %s\n", objetos.name );
            printf("        index = 0x%X\n", objetos.index );
            printf("        sub_index = 0x%X\n", objetos.sub_index );
            printf("        type = %s\n", msj_type_t(objetos.type) );
            printf("        size = %d bytes\n", objetos.size );
            value_object(slave, objetos);
        }
        printf("\n");
    }
}


void Error_wkc(int wkc, char msj[])
{
    if(wkc == 0)
    {
        printf("Fallo en %s \n", msj);
	}
}

/* ============= Implementacion de funciones privadas ====================*/

static case_type_t Type_data_object(Object_t object)
{
    case_type_t res;

    switch(object.type)
    {
        case int_8:
            res = int_8_bits;
        break;
        case int_16:
            res = int_16_bits;
        break;
        case int_32:
            res = int_32_bits;
        break;
        case uint_8:
            res = uint_8_bits;
        break;
        case uint_16:
            res = uint_16_bits;
        break;
        case uint_32:
            res = int_32_bits;
        break;
        case real_32:
            res = real_32_bits;
        break;
    }

    return res;
}

static uint8_t num_bytes(Object_t object)
{
    uint8_t res = 0;
    case_type_t type;

    type = Type_data_object(object);
    switch(type)
    {
        case int_8_bits:
            res = sizeof(int8);
        break;
        case int_16_bits:
            res = sizeof(int16);
        break;
        case int_32_bits:
            res = sizeof(int32);
        break;
        case uint_8_bits:
            res = sizeof(uint8);
        break;
        case uint_16_bits:
            res = sizeof(uint16);
        break;
        case uint_32_bits:
            res = sizeof(uint32);
        break;
        case real_32_bits:
            res = sizeof(float);
        break;
        default:
            msj_error_type_data_object();
    }

    return(res);
}

static void msj_error_type_data_object(void)
{
    printf("ERROR in type_data_object\n");
}

static char *msj_type_t(Type_t type)
{
    char *msj;

    switch(type)
    {
        case int_8:
            msj = "int_8";
        break;

        case int_16:
            msj = "int_16";
        break;

        case int_32:
            msj = "int_32";
        break;

        case uint_8:
            msj = "uint_8";
        break;

        case uint_16:
            msj = "uint_16";
        break;

        case uint_32:
            msj = "uint_32";
        break;

        case real_32:
            msj = "real_32";
        break;
    }

    return msj;
}

static void value_object(uint16 slave, Object_t obj)
{
    int8 p_8;
    int16 p_16;
    int32 p_32;
    uint8 up_8;
    uint16 up_16;
    uint32 up_32;
    float f_32;
    case_type_t type;

    type = Type_data_object(obj);
    printf("        value : ");
    switch(type)
    {
        case int_8_bits:
            get_object(slave, obj, &p_8);
            printf("%d\n", p_8);
        break;
        case int_16_bits:
            get_object(slave, obj, &p_16);
            printf("0x%X\n", p_16);
        break;
        case int_32_bits:
            get_object(slave, obj, &p_32);
            printf("0x%X\n", p_32);
        break;
        case uint_8_bits:
            get_object(slave, obj, &up_8);
            printf("%d\n", up_8);
        break;
        case uint_16_bits:
            get_object(slave, obj, &up_16);
            printf("0x%X\n", up_16);
        break;
        case uint_32_bits:
            get_object(slave, obj, &up_32);
            printf("0x%X\n", up_32);
        break;
        case real_32_bits:
            get_object(slave, obj, &f_32);
            printf("%f\n", f_32);
        break;
        default:
            msj_error_type_data_object();
    }
}


/* ============= Implementacion de Interrupciones Publicas ================*/



