/******************************************************************************
* FileName: ecat_dc.c
* Purpose: Librería para implementar compensacion DC para ETHERCAT.
*
* Author: Oviedo Martin
* Gmail : eliasoviedo1718@gmail.com
* Fecha : 08/06/2022
*
* Copyright (C) 2022 Oviedo Martin. All rights reserved.
*
* License: Se permiten el uso y la redistribución de este código con
* modificaciones o sin ellas, siempre que se mantengan esta
* licencia y las notas de autor y copyright de arriba.
*****************************************************************************/

/* ========== Inclusión de bibliotecas de código =======================*/
#include "ecat_dc.h"


/* ============ Definicion de variables globales =======================*/

extern double     ain[2];
extern int        ainc;
extern int        streampos;
extern uint32 cyclecount;
extern pthread_mutex_t mutex;
extern pthread_cond_t  cond;
extern in_EBOX_streamt  *in_EBOX;
extern out_EBOX_streamt *out_EBOX;
extern int16 stream1[MAXSTREAM];
extern int16 stream2[MAXSTREAM];


int dorun = 0;
int64 toff, gl_delta; //toff ==> tiempo de compensacion
uint8 *digout = 0;

extern volatile int wkc;


/* ============= Prototipos de funciones privadas =======================*/

/* add ns to timespec */
static void add_timespec(struct timespec *ts, int64 addtime);

/* PI calculation to get linux time synced to DC time */
static void ec_sync(int64 reftime, int64 cycletime , int64 *offsettime);


static void double_to_fixed(double f_input, int32_t *pValue, int32_t *pBase);

/* ============= Implementacion de funciones publicas ====================*/

OSAL_THREAD_FUNC_RT ecatthread(void *ptr)
{
   struct timespec   ts;
   struct timeval    tp;
   int ht;
   int i;
   int pcounter = 0;
   int64 cycletime;

   pthread_mutex_lock(&mutex);
   gettimeofday(&tp, NULL);

    /* Convert from timeval to timespec */
   ts.tv_sec  = tp.tv_sec;
   ht = (tp.tv_usec / 1000) + 1; /* round to nearest ms */
   ts.tv_nsec = ht * 1000000;
   cycletime = *(int*)ptr * 1000; /* cycletime in ns */
   toff = 0;
   dorun = 0;
   while(1)
   {
      /* calculate next cycle start */
      add_timespec(&ts, cycletime + toff);
      /* wait to cycle start */
      pthread_cond_timedwait(&cond, &mutex, &ts);
      if (dorun>0)
      {
         gettimeofday(&tp, NULL);

         ec_send_processdata();

         ec_receive_processdata(EC_TIMEOUTRET);

         cyclecount++;


         if((in_EBOX->counter != pcounter) && (streampos < (MAXSTREAM - 1)))
         {
            // check if we have timing problems in master
            // if so, overwrite stream data so it shows up clearly in plots.
            if(in_EBOX->counter > (pcounter + 1))
            {
               for(i = 0 ; i < 50 ; i++)
               {
                  stream1[streampos]   = 20000;
                  stream2[streampos++] = -20000;
               }
            }
            else
            {
               for(i = 0 ; i < 50 ; i++)
               {
                  stream1[streampos]   = in_EBOX->stream[i * 2];
                  stream2[streampos++] = in_EBOX->stream[(i * 2) + 1];
               }
            }
            pcounter = in_EBOX->counter;
         }

         /* calulate toff to get linux time and DC synced */
         ec_sync(ec_DCtime, cycletime, &toff);
      }
   }
}

/*OSAL_THREAD_FUNC_RT ecatthread(void *ptr)
{
    struct timespec   ts, tleft;
    int ht;
    int64 cycletime;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    ht = (ts.tv_nsec / 1000000) + 1; //round to nearest ms
    ts.tv_nsec = ht * 1000000;
    if(ts.tv_nsec >= NSEC_PER_SEC)
    {
        ts.tv_sec++;
        ts.tv_nsec -= NSEC_PER_SEC;
    }
    cycletime = *(int*)ptr * 1000; //cycletime in ns
    toff = 0;
    dorun = 0;

    ec_send_processdata();
    while(1)
    {
        //calculate next cycle start
        add_timespec(&ts, cycletime + toff);
        //wait to cycle start
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, &tleft);

        if(dorun>0)
        {
            wkc = ec_receive_processdata(EC_TIMEOUTRET);

            dorun++;
            //if we have some digital output, cycle
            if( digout )
            {
                *digout = (uint8) ((dorun / 16) & 0xff);
            }

            if(ec_slave[0].hasdc)
            {
                //calulate toff to get linux time and DC synced
                //Calcule toff para sincronizar el tiempo de Linux y DC
                ec_sync(ec_DCtime, cycletime, &toff);
            }
            ec_send_processdata();

      }
   }

}*/


#define PI_SAT_VAL	50000

int32_t  _pPart=0, _iPart=0;
int32_t   _sync_err=0, _sync_pre_err=0;

//double Kp=0.1, Ki=0.0005;
double Kp=0.1, Ki=0.001;

//new style, PI compensation
long long dc_pi_sync(long long  reftime, long long  cycletime, int32_t shift_time)
{
	long long  adj_time=0;
	int32_t iKp=0, iKp_Base, iKi=0, iKi_Base;
	double_to_fixed(Kp, &iKp, &iKp_Base);
	double_to_fixed(Ki, &iKi, &iKi_Base);

	_sync_err = (reftime - shift_time) % cycletime;
	if(_sync_err> (cycletime /2)) { _sync_err= _sync_err - cycletime; }

	_pPart=_sync_err*iKp;
	_iPart+=(_sync_err+_sync_pre_err)*iKi;
	_sync_pre_err=_sync_err;

	adj_time = -(_pPart>>iKp_Base) - (_iPart>>iKi_Base);

//	if (adj_time>PI_SAT_VAL) adj_time=PI_SAT_VAL;
//	if (adj_time<-PI_SAT_VAL) adj_time=-PI_SAT_VAL;

	return adj_time;

}


/* ============= Implementacion de funciones privadas ====================*/

static void add_timespec(struct timespec *ts, int64 addtime)
{
    int64 sec, nsec;

    nsec = addtime % NSEC_PER_SEC;
    sec = (addtime - nsec) / NSEC_PER_SEC;
    ts->tv_sec += sec;
    ts->tv_nsec += nsec;
    if( ts->tv_nsec >= NSEC_PER_SEC )
    {
        nsec = ts->tv_nsec % NSEC_PER_SEC;
        ts->tv_sec += (ts->tv_nsec - nsec) / NSEC_PER_SEC;
        ts->tv_nsec = nsec;
    }
}

static void ec_sync(int64 reftime, int64 cycletime , int64 *offsettime)
{
    static int64 integral = 0;
    int64 delta;
    /* set linux sync point 50us later than DC sync, just as example */
    delta = (reftime - 50000) % cycletime;
    if(delta > (cycletime / 2))
    {
        delta = delta - cycletime;
    }

    if(delta>0)
    {
        integral++;
    }
    else if(delta<0)
    {
        integral--;
    }

    *offsettime = -(delta / 100) - (integral / 20);
    gl_delta = delta;
}


static void double_to_fixed(double f_input, int32_t *pValue, int32_t *pBase)
{
	if (f_input<1.0)
	{
		(*pBase)=15;
		(*pValue)=(int32_t) (32768.0*f_input);
	}
	else if (f_input<2.0)
	{
		(*pBase)=14;
		(*pValue)=(int32_t) (16384.0*f_input);
	}
	else if (f_input<4.0)
	{
		(*pBase)=13;
		(*pValue)=(int32_t) (8192.0*f_input);
	}
	else if (f_input<8.0)
	{
		(*pBase)=12;
		(*pValue)=(int32_t) (4096.0*f_input);
	}
	else if (f_input<16.0)
	{
		(*pBase)=11;
		(*pValue)=(int32_t) (2048.0*f_input);
	}
	else if (f_input<32.0)
	{
		(*pBase)=10;
		(*pValue)=(int32_t) (1024.0*f_input);
	}
	else if (f_input<64.0)
	{
		(*pBase)=9;
		(*pValue)=(int32_t) (512.0*f_input);
	}
	else if (f_input<128.0)
	{
		(*pBase)=8;
		(*pValue)=(int32_t) (256.0*f_input);
	}
	else if (f_input<256.0)
	{
		(*pBase)=7;
		(*pValue)=(int32_t) (128.0*f_input);
	}
	else if (f_input<512.0)
	{
		(*pBase)=6;
		(*pValue)=(int32_t) (64.0*f_input);
	}
	else if (f_input<1024.0)
	{
		(*pBase)=5;
		(*pValue)=(int32_t) (32.0*f_input);
	}
	else if (f_input<2048.0)
	{
		(*pBase)=4;
		(*pValue)=(int32_t) (16.0*f_input);
	}
	else if (f_input<4096.0)
	{
		(*pBase)=3;
		(*pValue)=(int32_t) (8.0*f_input);
	}
	else if (f_input<81928.0)
	{
		(*pBase)=2;
		(*pValue)=(int32_t) (4.0*f_input);
	}
	else if (f_input<16384.0)
	{
		(*pBase)=1;
		(*pValue)=(int32_t) (2.0*f_input);
	}
	else if (f_input<32768.0)
	{
		(*pBase)=0;
		(*pValue)=(int32_t) (1.0*f_input);
	}
}

/* ============= Implementacion de Interrupciones Publicas ================*/
