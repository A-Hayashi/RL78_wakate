/***********************************************************************/
/*                                                                     */
/*  FILE        :hardware_setup.c                                      */
/*  DATE        :                                                      */
/*  DESCRIPTION :Hardware setup Program                                */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "iodefine.h"
#include "macrodriver.h"

void HardwareSetup(void);
void TimerInit(void);
void InterruptInit(void);


void HardwareSetup(void)
{
  DI();                                // ���荞�݋֎~
  TimerInit();                         // �^�C�}������
  InterruptInit();                     // ���荞�ݏ�����
}

void TimerInit(void)
{
  TAU0EN=1;                            // �^�C�}�O�N���b�N����
  TPS0=0x0000;                         // 32MHz/2��0��=32MHz
  TMR00=0x0;                           // CK00�I��
  TDR00=128-1;                         // 32MHz/128=250KHz=4us
}

void InterruptInit(void)
{
  TMMK00=0;                            // �^�C�}00�}�X�N�N���A
  EI();                                // ���荞�݋���
}

