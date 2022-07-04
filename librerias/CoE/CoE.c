/******************************************************************************
* FileName: Coe.h
* Purpose: Librería para el uso de CANOpen over Ethercat para un servo basado en soem.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 22/04/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

/* ========== Inclusión de bibliotecas de código =======================*/
#include "CoE.h"


/* ============ Definicion de variables globales =======================*/

int expectedWKC;
boolean needlf;
volatile int wkc;
boolean inOP;
uint8 currentgroup = 0;


/* ============= Prototipos de funciones privadas =======================*/

static void Print_State(uint16 slave, uint16 state);

//static uint8_t num_bytes(Type_t type);

/* ============= Implementacion de funciones publicas ====================*/

OSAL_THREAD_FUNC ecatcheck( void *ptr )
{
    int slave;
    (void)ptr;                  /* Not used */

    while(1)
    {
        if( inOP && ((wkc < expectedWKC) || ec_group[currentgroup].docheckstate))
        {
            if (needlf)
            {
               needlf = FALSE;
               printf("\n");
            }
            /* one ore more slaves are not responding */
            ec_group[currentgroup].docheckstate = FALSE;
            ec_readstate();
            for (slave = 1; slave <= ec_slavecount; slave++)
            {
               if ((ec_slave[slave].group == currentgroup) && (ec_slave[slave].state != EC_STATE_OPERATIONAL))
               {
                  ec_group[currentgroup].docheckstate = TRUE;
                  if (ec_slave[slave].state == (EC_STATE_SAFE_OP + EC_STATE_ERROR))
                  {
                     printf("ERROR : slave %d is in SAFE_OP + ERROR, attempting ack.\n", slave);
                     ec_slave[slave].state = (EC_STATE_SAFE_OP + EC_STATE_ACK);
                     ec_writestate(slave);
                  }
                  else if(ec_slave[slave].state == EC_STATE_SAFE_OP)
                  {
                     printf("WARNING : slave %d is in SAFE_OP, change to OPERATIONAL.\n", slave);
                     ec_slave[slave].state = EC_STATE_OPERATIONAL;
                     ec_writestate(slave);
                  }
                  else if(ec_slave[slave].state > EC_STATE_NONE)
                  {
                     if (ec_reconfig_slave(slave, EC_TIMEOUTMON))
                     {
                        ec_slave[slave].islost = FALSE;
                        printf("MESSAGE : slave %d reconfigured\n",slave);
                     }
                  }
                  else if(!ec_slave[slave].islost)
                  {
                     /* re-check state */
                     ec_statecheck(slave, EC_STATE_OPERATIONAL, EC_TIMEOUTRET);
                     if (ec_slave[slave].state == EC_STATE_NONE)
                     {
                        ec_slave[slave].islost = TRUE;
                        printf("ERROR : slave %d lost\n",slave);
                     }
                  }
               }
               if (ec_slave[slave].islost)
               {
                  if(ec_slave[slave].state == EC_STATE_NONE)
                  {
                     if (ec_recover_slave(slave, EC_TIMEOUTMON))
                     {
                        ec_slave[slave].islost = FALSE;
                        printf("MESSAGE : slave %d recovered\n",slave);
                     }
                  }
                  else
                  {
                     ec_slave[slave].islost = FALSE;
                     printf("MESSAGE : slave %d found\n",slave);
                  }
               }
            }
            if(!ec_group[currentgroup].docheckstate)
               printf("OK : all slaves resumed OPERATIONAL.\n");
        }
        osal_usleep(10000);
    }
}

void Read_State_Ethercat_Slave(uint16 slave)
{
    int res = ec_readstate();
    if(res > 0)
    {
        uint16 state = ec_slave[slave].state;
        Print_State(slave, state);
    }
    else
    {
        printf("No slave found\n");
    }
}

void Write_State_Ethercat_Slave(uint16 slave, ec_state State)
{
    ec_slave[slave].state = State;
    ec_writestate(slave);
    uint16_t res = ec_statecheck(slave, State, EC_TIMEOUTSTATE);// EC_TIMEOUTSTATE*4);

    if( res != State )
    {
        printf("Fallo al cambiar de estado\n");
    }
    /*else
    {
        ec_writestate(slave);
    }*/

}

void Config_Synchronization_Type(uint16 slave, Synchronization_Type_t type)
{
    int os, wkc_count;
    uint16_t ob;

    os = sizeof(ob);

    if(type == FREE_RUN )
    {
        ob = 0x0000;
    }
    else if(type == DC )
    {
        ob = 0x0001;
    }

    wkc_count = ec_SDOwrite(slave, 0x0980, 0x00, FALSE, os, &ob, EC_TIMEOUTSAFE);
    if (wkc_count==0)
    {
        printf("Error Synchronization_Type, %d\n", ob);
    }
}

void Print_binario(uint16 num)
{
    unsigned long long int decimal = (unsigned long long int)num;
    int contador = NUMERO_DE_BITS;
    char binario[NUMERO_DE_BITS]; // Una cadena representando el número binario

    /*
		Llenar la cadena con ceros
	*/
	for (int i = 0; i < NUMERO_DE_BITS; i++) binario[i] = '0';

	lldiv_t resultadoDeLaDivision;

	while(decimal > 0 && contador > 0 )
    {
		resultadoDeLaDivision = lldiv(decimal, 2);
		contador--;
		binario[contador] = resultadoDeLaDivision.rem == 1 ? '1' : '0';
		decimal = resultadoDeLaDivision.quot;
	}

	printf("%s\n", binario);
}

/* ============= Implementacion de funciones privadas ====================*/

static void Print_State(uint16 slave, uint16 state)
{
    printf("Slave %d - ", slave);
    uint16 STATE = state & 0x000f;
    switch(STATE)
    {
        case EC_STATE_NONE:
            printf("State: No valid state %d", state);
        break;
        case EC_STATE_INIT:
            printf("State: Init state %d", state);
        break;
        case EC_STATE_PRE_OP:
            printf("State: Pre-operational %d", state);
        break;
        case EC_STATE_BOOT:
            printf("State: Boot state %d", state);
        break;
        case EC_STATE_SAFE_OP:
            printf("State: Safe-operational %d", state);
        break;
        case EC_STATE_OPERATIONAL:
            printf("State: Operational %d", state);
        break;
        case EC_STATE_ACK:
            printf("State: Error or ACK error %d", state);
        break;
        default:
            printf("State: ");
        break;
    }
    printf("\n");

}


/*static uint8_t num_bytes(Type_t type)
{
    uint8_t res = 0;
    if(type == int_16 || type == uint_16)
    {
        res = sizeof(uint16_t);
    }
    else if(type == int_32 || type == uint_32)
    {
        res = sizeof(uint32_t);
    }

    return(res);
}*/




/* ============= Implementacion de Interrupciones Publicas ================*/
