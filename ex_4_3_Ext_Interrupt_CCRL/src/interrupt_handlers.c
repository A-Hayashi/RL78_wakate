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

extern unsigned char flag;

#pragma interrupt INT_P0(vect=INTP0)
void INT_P0 (void)
{
  flag=!flag;                          // ƒtƒ‰ƒO”½“]
}
