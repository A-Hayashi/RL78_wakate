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
#include "macrodriver.h"

unsigned char portValue = 0;
void main(void);
extern void HardwareSetup(void);

void main(void) {
  HardwareSetup();                     // ハードウェア設定

  P1 = 0xff;                             // P1全High
  PM1 = 0x00;                            // P1全出力設定

  TS0 = 0x0001;                          // タイマ00カウント開始

  while (1) {
    P1 = ~portValue;                     // 割り込みカウンタの反転出力
  }
}
