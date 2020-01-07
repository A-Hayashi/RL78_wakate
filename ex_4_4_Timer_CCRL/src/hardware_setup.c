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
  TAU0EN=1;                            // �^�C�}�A���C���j�b�g0�N���b�N����
  TPS0=0x1000;                         // 32MH��/2��10��=31.25kHz
  TMR00=0x00;                          // CK00�I��
  TDR00=15625-1;                       // �^�C�}�f�[�^�ݒ�31.25kHz/15625=2Hz
}

void InterruptInit(void)
{
  TMMK00=0;                            // �^�C�}00�}�X�N�N���A
  EI();                                // ���荞�݋���
}
