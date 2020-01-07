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
  TAU0EN=1;                            // タイマアレイユニット0クロック供給
  TPS0=0x1000;                         // 32MHｚ/2の10乗=31.25kHz
  TMR00=0x00;                          // CK00選択
  TDR00=15625-1;                       // タイマデータ設定31.25kHz/15625=2Hz
}

void InterruptInit(void)
{
  TMMK00=0;                            // タイマ00マスククリア
  EI();                                // 割り込み許可
}
