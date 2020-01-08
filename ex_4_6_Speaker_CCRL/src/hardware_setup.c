/***********************************************************************/
/*                                                                     */
/*  FILE        :Hardware_setup.c                                      */
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

void HardwareSetup(void)
{
  DI();                                // ���荞�݋֎~
  TimerInit();                         // �^�C�}������
}

void TimerInit(void)
{
  TAU0EN=1;                            // �^�C�}�O�N���b�N����
  TPS0=0x0007;                         // 32MHz/2��7��=250kHz
  TMR00=0x0000;                        // CK00�I��
}

