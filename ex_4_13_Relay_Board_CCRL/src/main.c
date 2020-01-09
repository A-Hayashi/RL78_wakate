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

void main(void);

void delay_ms(int ms)
{
  volatile int i,j;
  for(i=0;i<ms;i++)
  {
    for(j=0;j<2963;j++)
    {

    }
  }
}
void main(void)
{
  int i=0;
  PM1=0x00;                            // P1‘So—Í
  while (1)
  {
    for(i=0;i<2;i++)
    {
      P1=(1<<i);                       // P1Ý’è(0-1‚ð‡”Ô‚ÉHigh)
      delay_ms(500);                   // 500ms wait
    }
  }
}
