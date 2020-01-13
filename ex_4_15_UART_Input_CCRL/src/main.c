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

void main(void)
{
  int a;
  HardwareSetup();                     // ハードウェア初期化
  SS0=0x000C;                          // シリアルチャネル２と３通信開始セット
  while (1)
  {
    a = 10;
    scanf("%d",&a);                    // 入力
    printf("Index = %d\n",a);          // 出力
  }

}

int putchar(int c)
{
  while ((SSR02) & (1 << 6))           // 通信動作待機待ち
  {

  }
  TXD1 = (unsigned char)c;             // 送信データ設定
  return c;
}
int getchar(void)
{
  unsigned char data;
  while (!((SSR03) & (1 << 5)))        // 受信完了待ち
  {

  }
  data = RXD1;                         // 受信データ取得
  return (int)data;  
}

