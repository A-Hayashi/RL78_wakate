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
  PM1=0x00;                            // P1全出力
  while (1)
  {
    for(i=0;i<2;i++)
    {
      P1=(1<<i);                       // P1設定(0-1を順番にHigh)
      delay_ms(500);                   // 500ms wait
    }
  }
}
