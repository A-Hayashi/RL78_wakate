/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :                                                      */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "iodefine.h"

#define MOTOR_PORTMODE PM1
#define MOTOR_PORT P1

#define ON  1
#define OFF 0
#define CW  1
#define CCW 0

void main(void);
void M1B(unsigned char onoff);
void M1A(unsigned char onoff);
void M2B(unsigned char onoff);
void M2A(unsigned char onoff);
void Motor1(unsigned char CWCCW);
void Motor2(unsigned char CWCCW);
void Stop_Motor1(void);
void Stop_Motor2(void);


void M1B(unsigned char onoff)
{
  if(onoff==ON)                        // ON?
    MOTOR_PORT = MOTOR_PORT|0x01;      // モータ１PhaseB High
  else
    MOTOR_PORT = MOTOR_PORT&0xFE;      // モータ１PhaseB Low
}
void M1A(unsigned char onoff)
{
  if(onoff==ON)                        // ON?
    MOTOR_PORT = MOTOR_PORT|0x02;      // モータ１PhaseA High
  else
    MOTOR_PORT = MOTOR_PORT&0xFD;      // モータ１PhaseA Low
}

void M2B(unsigned char onoff)
{
  if(onoff==ON)                        // ON
    MOTOR_PORT = MOTOR_PORT|0x04;      // モータ２PhaseB High
  else
    MOTOR_PORT = MOTOR_PORT&0xFB;      // モータ２PhaseB Low
}

void M2A(unsigned char onoff)
{
  if(onoff==ON)                        // ON
    MOTOR_PORT = MOTOR_PORT|0x08;      // モータ２PhaseA High
  else
    MOTOR_PORT = MOTOR_PORT&0xF7;      // モータ２PhaseA Low
}

void Motor1(unsigned char CWCCW)
{
  if(CWCCW==CW)                        // CW?
  {
    M1A(OFF);                          // モータ１PhaseA OFF
    M1B(ON);                           // モータ１PhaseB ON
  }
  else
  {
    M1A(ON);                           // モータ１PhaseA ON
    M1B(OFF);                          // モータ１PhaseB OFF
  }
}
void Motor2(unsigned char CWCCW)
{
  if(CWCCW==CW)                        // CW?
  {
    M2A(OFF);                          // モータ２PhaseA OFF
    M2B(ON);                           // モータ２PhaseB ON
  }
  else
  {
    M2A(ON);                           // モータ２PhaseA ON
    M2B(OFF);                          // モータ２PhaseB OFF
  }
}
void Stop_Motor1(void)
{
  M1A(ON);                             // モータ１PhaseA ON
  M1B(ON);                             // モータ１PhaseB ON
}

void Stop_Motor2(void)
{
  M2A(ON);                             // モータ２PhaseA ON
  M2B(ON);                             // モータ２PhaseB ON
}

void delay_ms(int ms)
{
  volatile int i,j;
  for(i=0;i<ms;i++)
  {
    for(j=0;j<2963;j++)
    {

    }
  }
}

void main(void)
{
  MOTOR_PORTMODE=0x00;                 // モータポート出力設定

  while(1)
  {
    Motor1(0);                         // モータ１ CCW
    Motor2(0);                         // モータ２ CCW
    delay_ms(1000);                    // 1s wait
    Motor1(1);                         // モータ１ CW
    Motor2(1);                         // モータ２ CW
    delay_ms(1000);                    // 1s wait
  }
}
