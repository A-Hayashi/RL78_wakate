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
void InterruptInit(void);
void TimerInit(void);

void HardwareSetup(void) {
  DI();  // 割り込み禁止
  TimerInit();  // タイマ初期化
  InterruptInit();  // 割り込み初期化
}

void TimerInit(void) {
  TAU0EN = 1;		// タイマ0クロック供給
  TPS0 = 0x000a;	// 32MHz/2の10乗=31.25kHz
  TMR00 = 0x00;  // CK00選択
  TDR00 = 5 - 1;	// タイマデータ設定31.25kHz/5=6250Hz
}

void InterruptInit(void) {
  TMMK00 = 0;  // タイマ00マスククリア
  EI();  // 割り込み許可
}
