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
  DI();                                // 割り込み禁止
  TimerInit();                         // タイマ初期化
  InterruptInit();                     // 割り込み初期化
}

void TimerInit(void)
{
  TAU0EN=1;                            // タイマ０クロック供給
  TPS0=0x0000;                         // 32MHz/2の0乗=32MHz
  TMR00=0x0;                           // CK00選択
  TDR00=128-1;                         // 32MHz/128=250KHz=4us
}

void InterruptInit(void)
{
  TMMK00=0;                            // タイマ00マスククリア
  EI();                                // 割り込み許可
}

