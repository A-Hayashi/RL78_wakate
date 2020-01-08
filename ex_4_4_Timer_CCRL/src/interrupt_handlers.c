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

extern unsigned char portValue;
#pragma interrupt INT_TM00(vect=INTTM00)
void INT_TM00(void) {
  portValue++;                         // カウントアップ
}
