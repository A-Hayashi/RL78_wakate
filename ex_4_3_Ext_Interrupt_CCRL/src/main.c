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

unsigned char flag=0;
extern void HardwareSetup(void);

//SW1:P137(INTP0)
//LED0-7:P10-P17

void delay_ms(int ms)
{
  volatile int i,j;
  for(i=0;i<ms;i++)
  {
    for(j=0;j<100;j++)
    {

    }
  }
}
void main(void)
{
    
  unsigned char P1Data;
  HardwareSetup();                     // ハードウェア設定
  P1=0xff;                             // P1全High
	PM1=0x00;                            // P1全出力
  P1Data=0x01;                         // 1設定
  while (1)
  {
    P1=~P1Data;                        // 反転出力
    if(flag)                           // フラグセット?
    {
      if(P1Data==0x08)                 // 上限?
      {
        P1Data=0x01;                   // 下限設定
      }
      else
      {
        P1Data<<=1;                    // 左シフト
      }
    }
    else
    {
      if(P1Data==0x01)                 // 下限?
      {
        P1Data=0x08;                   // 上限設定
      }
      else
      {
        P1Data>>=1;                    // 右シフト
      }
    }
    delay_ms(100);                     // 100ms wait
  }
}