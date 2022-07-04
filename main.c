/*=============================================================================
 * Copyright (c) 2022, Oviedo_Martin <eliasoviedo1718@gmail.com>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2022/06/15

 Resumen:
        Codigo para operar un servo en el modo Cyclic synchronous position mode.


 ==== Referencias ====

   []


 ==== Enlaces ====

   [SOEM] https://openethercatsociety.github.io/doc/soem/tutorial_8txt.html


 *===========================================================================*/

/* ========== Inclusión de bibliotecas de código ====================== */


#include "librerias/CoE/CoE.h"
#include "librerias/CoE/ecat_dc.h"
#include "librerias/CoE/pdo_def.h"

extern Dic_t SYNC[];
extern Dic_t COMMON[];
extern Dic_t DEVICE[];
extern Dic_t MANUFACTURER[];


char IOmap[4096];
OSAL_THREAD_HANDLE thread1;
OSAL_THREAD_HANDLE thread2;

extern boolean inOP;
extern int dorun;
extern volatile int wkc;
extern int64 gl_delta;

extern double ain[2];
extern int    ainc;
extern int    streampos;
extern uint32 cyclecount;

extern in_EBOX_streamt  *in_EBOX;
extern out_EBOX_streamt *out_EBOX;


#define NUMOFMAXPOS_DRIVE	2
int expectedWKC;

//variables for pdo re-mapping (sdo write)
int os;
uint32 ob;
int16 ob2;
uint8 ob3;

void simpletest(char *ifname);


int main(int argc, char *argv[])
{
    printf("SOEM (Simple Open EtherCAT Master) - Simple test\n");
    char *Name_servo = "enp4s0";
    int ctime = 2000; //en ms

      /* create thread to handle slave error handling in OP */
    osal_thread_create_rt(&thread1, stack64k*2, &ecatthread, (void*) &ctime);
    osal_thread_create(&thread2, stack64k*4, &ecatcheck, NULL);

    /* start cyclic part */
    simpletest(Name_servo);

    printf("\nEND PROGRAM\n");
    ec_close();
    return 0;
}


void simpletest(char *ifname)
{
    int i, j, oloop, iloop, chk;

    printf("Starting simple test\n");

    // initialise SOEM, bind socket to ifname
    if (ec_init(ifname))
    {
        printf("ec_init on %s succeeded.\n",ifname);
        // find and auto-config slaves

        if ( ec_config_init(FALSE) > 0 )
        {
            if( ec_slavecount >= 1 )
            {
                printf("%d slaves found and configured.\n",ec_slavecount);
            }
            else
            {
                return;
            }

            Read_State_Ethercat_Slave(1);
            Write_State_Ethercat_Slave(0, EC_STATE_PRE_OP );
            Read_State_Ethercat_Slave(1);
            hiwin_d2_setup(1);
            Read_State_Ethercat_Slave(1);

            //configure DC options for every DC capable slave found in the list
            printf("DC capable : %d\n", ec_configdc());
            int memoria = ec_config_map(&IOmap);
            printf("Size IOmap = %d\n", memoria);

            Write_State_Ethercat_Slave(0, EC_STATE_SAFE_OP );

            si_map_sdo(1, IOmap);
            //si_map_sii(1, IOmap);
            //si_sdo(1);
            //slaveinfo(1);

            oloop = ec_slave[0].Obytes;
            printf("\noloop = %d\n", oloop);
            if( (oloop == 0) && (ec_slave[0].Obits > 0))
            {
                oloop = 1;
            }
            if (oloop > 8)
            {
                oloop = 8;
            }

            iloop = ec_slave[0].Ibytes;
            printf("iloop = %d\n", iloop);
            if ((iloop == 0) && (ec_slave[0].Ibits > 0))
            {
                iloop = 1;
            }
            if (iloop > 8)
            {
                iloop = 8;
            }

            printf("segments : %d : %d %d %d %d\n",ec_group[0].nsegments ,ec_group[0].IOsegment[0],ec_group[0].IOsegment[1],ec_group[0].IOsegment[2],ec_group[0].IOsegment[3]);

            printf("Request operational state for all slaves\n");
            expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;
            printf("Calculated workcounter %d\n", expectedWKC);
            ec_slave[1].state = EC_STATE_OPERATIONAL;
            /* send one valid process data to make outputs in slaves happy*/
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            /* request OP state for all slaves */
            ec_writestate(1);
            chk = 200;

            MAXPOS_Drive_pt PDO_slave[ec_slavecount];
            /* wait for all slaves to reach OP state */
            do
            {
                ec_send_processdata();
                ec_receive_processdata(EC_TIMEOUTRET);
                ec_statecheck(0, EC_STATE_OPERATIONAL, 50000);
            }
            while( chk-- && (ec_slave[1].state != EC_STATE_OPERATIONAL) );
            printf("state = %d, chk = %d\n", ec_slave[1].state, chk);

            //No estoy seguro de que la maquina de estados para poner el servo en Ready
            //se tenga que usar la comunicacion por SDO.
            //El problema es que trate de hacer lo mismo usando PDO, pero no pude.
            for(uint16 slave=1; slave<=ec_slavecount; slave++)
            {
                if(servo_get_state(slave) == DRIVE_FAULT)
                {
                    servo_send_command(slave, FAULT_RESET);
                }
                servo_send_command(slave, SHUTDOWN);
                servo_get_state(slave);

                servo_send_command(slave, SWITCH_ON);
                servo_get_state(slave);

                servo_send_command(slave, ENABLE_OPERATION);
                servo_get_state(slave);
            }


            for(i=1; i<=ec_slavecount; i++)
            {
                    PDO_slave[i-1].ptOutParam = (MAXPOS_DRIVE_RxPDO_t*)  		ec_slave[i].outputs;
                    PDO_slave[i-1].ptInParam  = (MAXPOS_DRIVE_TxPDO_t*)  		ec_slave[i].inputs;
                    PDO_slave[i-1].ptOutParam->ModeOfOperation = OP_MODE_CYCLIC_SYNC_POSITION;
            }

            int started[ec_slavecount], ServoState=0;
            for (i=0; i<ec_slavecount; i++)
            {
                started[i] = 0;
            }

            uint16 controlword=0;
            //servo-on
            for(i=0; i<ec_slavecount; i++)
            {
                inOP = TRUE;
                (PDO_slave[i].ptOutParam)->ModeOfOperation = 0x8;
                ec_send_processdata();
                wkc = ec_receive_processdata(EC_TIMEOUTRET);
                (PDO_slave[i].ptOutParam)->ControlWord = 0x6;
                ec_send_processdata();
                wkc = ec_receive_processdata(EC_TIMEOUTRET);
                (PDO_slave[i].ptOutParam)->ControlWord = 0x7;
                ec_send_processdata();
                wkc = ec_receive_processdata(EC_TIMEOUTRET);

                (PDO_slave[i].ptOutParam)->ControlWord = 0x0F;
                ec_send_processdata();
                wkc = ec_receive_processdata(EC_TIMEOUTRET);
                (PDO_slave[i].ptOutParam)->TargetPosition = 0x00140000;
                ec_send_processdata();
                wkc = ec_receive_processdata(EC_TIMEOUTRET);

                printf("State %d status_word %d\n\r",ec_slave[1].state, PDO_slave[i].ptInParam->StatusWord);

            }

         }
    }
}


