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
    MOTOR_PORT = MOTOR_PORT|0x01;      // ���[�^�PPhaseB High
  else
    MOTOR_PORT = MOTOR_PORT&0xFE;      // ���[�^�PPhaseB Low
}
void M1A(unsigned char onoff)
{
  if(onoff==ON)                        // ON?
    MOTOR_PORT = MOTOR_PORT|0x02;      // ���[�^�PPhaseA High
  else
    MOTOR_PORT = MOTOR_PORT&0xFD;      // ���[�^�PPhaseA Low
}

void M2B(unsigned char onoff)
{
  if(onoff==ON)                        // ON
    MOTOR_PORT = MOTOR_PORT|0x04;      // ���[�^�QPhaseB High
  else
    MOTOR_PORT = MOTOR_PORT&0xFB;      // ���[�^�QPhaseB Low
}

void M2A(unsigned char onoff)
{
  if(onoff==ON)                        // ON
    MOTOR_PORT = MOTOR_PORT|0x08;      // ���[�^�QPhaseA High
  else
    MOTOR_PORT = MOTOR_PORT&0xF7;      // ���[�^�QPhaseA Low
}

void Motor1(unsigned char CWCCW)
{
  if(CWCCW==CW)                        // CW?
  {
    M1A(OFF);                          // ���[�^�PPhaseA OFF
    M1B(ON);                           // ���[�^�PPhaseB ON
  }
  else
  {
    M1A(ON);                           // ���[�^�PPhaseA ON
    M1B(OFF);                          // ���[�^�PPhaseB OFF
  }
}
void Motor2(unsigned char CWCCW)
{
  if(CWCCW==CW)                        // CW?
  {
    M2A(OFF);                          // ���[�^�QPhaseA OFF
    M2B(ON);                           // ���[�^�QPhaseB ON
  }
  else
  {
    M2A(ON);                           // ���[�^�QPhaseA ON
    M2B(OFF);                          // ���[�^�QPhaseB OFF
  }
}
void Stop_Motor1(void)
{
  M1A(ON);                             // ���[�^�PPhaseA ON
  M1B(ON);                             // ���[�^�PPhaseB ON
}

void Stop_Motor2(void)
{
  M2A(ON);                             // ���[�^�QPhaseA ON
  M2B(ON);                             // ���[�^�QPhaseB ON
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
  MOTOR_PORTMODE=0x00;                 // ���[�^�|�[�g�o�͐ݒ�

  while(1)
  {
    Motor1(0);                         // ���[�^�P CCW
    Motor2(0);                         // ���[�^�Q CCW
    delay_ms(1000);                    // 1s wait
    Motor1(1);                         // ���[�^�P CW
    Motor2(1);                         // ���[�^�Q CW
    delay_ms(1000);                    // 1s wait
  }
}
