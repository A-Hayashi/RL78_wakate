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
void UART1_Transmit(unsigned char data);
unsigned char UART1_Receive(void);
void UART1_Puts(char* str);
void delay_ms(int ms);

extern void HardwareSetup(void);

void main(void)
{
  HardwareSetup();                     // ハードウェア設定
  SS0=0x000C;                          // シリアルチャネル２と３通信開始セット
  while (1)
  {
    UART1_Puts("Hello, NEWTC\nHello, RL78\n");  // "Hello, NEWTC\nHello, RL78\n"送信
    delay_ms(100);                     // 100ms wait
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
    UART1_Transmit(*str);              // UART1送信データ設定
    str++;
  }
}

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
