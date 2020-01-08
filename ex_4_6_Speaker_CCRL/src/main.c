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

#define C1 523                         //ド
#define C1_ 554
#define D1 587                         //レ
#define D1_ 622
#define E1 659                         //ミ
#define F1 699                         //ファ
#define F1_ 740
#define G1 784                         //ソ
#define G1_ 831
#define A1 880                         //ラ
#define A1_ 932
#define B1 988                         //シ

#define C2 C1*2                        //ド
#define C2_ C1_*2
#define D2 D1*2                        //レ
#define D2_ D1_*2
#define E2 E1*2                        //ミ
#define F2 F1*2                        //ファ
#define F2_ F1_*2
#define G2 G1*2                        //ソ
#define G2_ G1_*2
#define A2 A2*2                        //ラ
#define A2_ A2_*2
#define B2 B2*2                        //シ

#define DLY_1 DLY_4*4                  //全音符
#define DLY_2 DLY_4*2                  // 2分音符
#define DLY_4 400                      // 4分音符
#define DLY_8 DLY_4/2                  // 8分音符
#define DLY_16 DLY_8/2                 // 16分音符

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
void main(void)
{
  int freq = 1000, i;
  int song[42]={C1,C1,G1,G1,A1,A1,G1,
          F1,F1,E1,E1,D1,D1,C1,
          G1,G1,F1,F1,E1,E1,D1,
          G1,G1,F1,F1,E1,E1,D1,
          C1,C1,G1,G1,A1,A1,G1,          
          F1,F1,E1,E1,D1,D1,C1,};
  int length[42]={DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,};

  HardwareSetup();                     // ハードウェア設定
  PM0=0x00;                            // P0全出力
  TS0=0x0001;                          // タイマ00カウント開始

  while(1)
  {
    for(i=0;i<42;i++)
    {
      freq = song[i];                  // 周波数取得
      // TDR00 = ((1/(2*freq)) / (4/1000000));
      TDR00 = (1000000/(8*freq));      // 割り込み時間算出
      TOE0L_bit.no0 = 1;               // TO00出力許可
      delay_ms(length[i]);             // 待ち時間
      TOE0L_bit.no0 = 0;               // TO00出力禁止（休符）
      delay_ms(5);                     // 5ms wait
    }
    delay_ms(10000);                   // 10s wait
  }
}
