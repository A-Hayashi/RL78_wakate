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
#include <stdio.h>

void main(void);
extern void HardwareSetup(void);

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
void delay_us(register int us)
{
  us<<=1;
  us-=8;
  while(us)
  {
    us--;
  }
}
void UART1_Transmit(unsigned char data)
{
  while ((SSR02) & (1 << 6))           // 通信動作待機待ち
  {

  }
  TXD1 = data;                         // 送信データ設定
}

unsigned char UART1_Receive(void)
{
  unsigned char data;
  while (!((SSR03) & (1 << 5)))        // 受信完了待ち
  {

  }
  data = RXD1;                         // 受信データ取得
  return data;
}
void UART1_Puts(char* str)
{
  while (*str)                         // NULLまで繰り返す
  {
    UART1_Transmit(*str);              // UART1送信データ送信
    str++;
  }
}

unsigned int Generate_ADC_Value(int pinNum)
{
  unsigned int temp;
  ADS=pinNum;                          // AD変換ピン設定
  ADCS=1;                              // AD変換開始
  delay_us(3);                         // 3us wait
  while(ADCS)                          // AD変換停止待ち
  {

  }
  temp=ADCR;                           // AD変換データ取得
  return temp>>6;
}

void main(void)
{
  volatile int ADC_Value[20];
  char Buffer[1000];
  int delaycount=0;
  int i;
  HardwareSetup();                     // ハードウェア設定
  SS0=0x000C;                          // シリアルチャネル２と３通信開始セット
  while(1)
  {
    for(i=18;i<19;i++)
    {
      ADC_Value[i]=Generate_ADC_Value(i);  // AD変換(0-7)
    }
    delay_ms(1);                       // 1ms wait
    delaycount++;                      // カウントアップ
    if(delaycount==25)                 // カウンタ=25?
    {
      sprintf(Buffer,"ADC[18] = %04d\n", ADC_Value[18]);
      UART1_Puts(Buffer);              // AD変換結果18出力
      delaycount=0;
    }
  }
}
