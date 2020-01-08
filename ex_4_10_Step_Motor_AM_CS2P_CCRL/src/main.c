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

#define MOTOR_PORTMODE PM1
#define MOTOR_PORT P1

void main(void);

void port_init(void) {
  MOTOR_PORTMODE = 0x00;                 // モータポート出力
  MOTOR_PORT = 0xf0;                     // モータポートLow
}

/* 4相モータの1-2相励磁動作 */
unsigned char Left_1step_walk(char dir) {
  static int leftStep = 0;
  char step_left[] = { 0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08 };
  if (dir) {                          // 正方向?
    leftStep++;                        // アップ
    leftStep %= 8;                       // オーバーフロー対策
  } else {
    if (leftStep == 0) {                   // 下限?
      leftStep = 7;                      // 上限値
    } else {
      leftStep--;                      // ダウン
    }
  }
  return step_left[leftStep];          // 左step値を返す

}

void delay_ms(int ms) {
  volatile int i, j;
  for (i = 0; i < ms; i++) {
    for (j = 0; j < 2963; j++) {

    }
  }
}
void main(void) {
  unsigned char stepleft = 0;

  port_init();                         // ポート初期化
  while (1) {
    stepleft = Left_1step_walk(0);     // 左1step逆方向
    delay_ms(2);                       // 2ms wait
    MOTOR_PORT = 0xf0 | stepleft;             // モータ出力
  }

}
