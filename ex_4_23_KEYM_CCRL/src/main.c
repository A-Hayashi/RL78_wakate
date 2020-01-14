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

#define KEYIN P1
#define KEYOUT P6
#define _BV(x) (1<<x)

unsigned char keystate[4][4];

void main(void);
void delay_ms(int ms);
void delay_us(register int us);
void keyscan(void);
void keyshow(void);

extern void HardwareSetup(void);

void main(void)
{
  HardwareSetup();                     // ハードウェア設定
  SS0=0x000C;                          // シリアルチャネル２と３通信開始セット
  while (1)
  {
    keyscan();                         // キースキャン
    keyshow();                         // キーデータ出力
    delay_ms(500);                     // 500ms wait
  }
}

int putchar(int data)
{
  while ((SSR02) & (1 << 6))           // 通信動作待機待ち
  {

  }
  TXD1 = (char)data;                   // 送信データ設定
  return data;
}
int getchar(void)
{
  int data;
  while (!((SSR03) & (1 << 5)))        // 受信完了待ち
  {

  }
  data = RXD1;                         // 受信データ取得
  return data;
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
void delay_us(register int us)
{
  us<<=1;
  us-=8;
  while(us)
  {
    us--;
  }
}

void keyscan(void)
{
  volatile char x,y;
  volatile unsigned char value;
  unsigned char tmp;
  for(x=0;x<4;x++)
  {
    tmp = (unsigned char)(~(_BV(x)));
    KEYIN=tmp&0x0F;                    // キースキャン出力
    delay_us(5);                       // 5us wait
    value = KEYOUT;                 // キー読み込み
    for(y=0;y<4;y++)
    {
      if((value&(_BV(y))))             // キーオン?
      {
        keystate[x][y] = 1;            // セット
      }
      else
      {
        keystate[x][y] = 0;            // クリア
      }
    }

  }
}
void keyshow(void)
{
  int x,y;
  printf("\r\n\r\n");
  for(x=0;x<4;x++)
  {
    printf("\r\n");                    // 改行出力
    for(y=0;y<4;y++)
    {
      printf(" %d", keystate[y][x]);   // キーデータ出力
    }
  }
}
