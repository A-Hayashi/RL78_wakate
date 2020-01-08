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
  if(cnt<nServo_PWM)                   // �T�[�{PWM����?
  {
    P1=0xFF;                           // P1�SHigh
  }
  else
  {
    P1=0;                              // P1�SLow
  }
  if(cnt>5000)                         // �J�E���^���?
  {
    cnt=0;                             // �J�E���^�N���A
  }
  else
  {
    cnt++;                             // �J�E���^�A�b�v
  }
}
