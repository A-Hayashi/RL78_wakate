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
  DI();                                // 割り込み禁止
  TimerInit();                         // タイマ初期化
}

void TimerInit(void)
{
  TAU0EN=1;                            // タイマ０クロック供給
  TPS0=0x0007;                         // 32MHz/2の7乗=250kHz
  TMR00=0x0000;                        // CK00選択
}

