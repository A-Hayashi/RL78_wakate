/***********************************************************************/
/*                                                                     */
/*  FILE        :interrupt_handlers.c                                  */
/*  DATE        :                                                      */
/*  DESCRIPTION :Interrupt Program                                     */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "iodefine.h"

extern int nServo_PWM;

#pragma interrupt INT_TM00(vect=INTTM00)
void INT_TM00 (void)
{
  static int cnt=0;
  if(cnt<nServo_PWM)                   // サーボPWM未満?
  {
    P1=0xFF;                           // P1全High
  }
  else
  {
    P1=0;                              // P1全Low
  }
  if(cnt>5000)                         // カウンタ上限?
  {
    cnt=0;                             // カウンタクリア
  }
  else
  {
    cnt++;                             // カウンタアップ
  }
}
