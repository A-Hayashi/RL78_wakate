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

int nServo_PWM;
void main(void);
extern void HardwareSetup(void);

void delay_ms(int ms) {
  volatile int i, j;
  for (i = 0; i < ms; i++) {
    for (j = 0; j < 2963; j++) {

    }
  }
}

int calcPWM(float angle) {
  float us = (angle * ((2.4 - 0.5) / 180) + 0.5) * 1000;

  return us / 4;
}

void main(void) {

  HardwareSetup();                     // ハードウェア設定
  PM1 = 0x00;                            // P1全出力
  TS0 = 0x0001;                          // タイマ00カウント開始
  while (1) {
    nServo_PWM = calcPWM(0);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(30);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(60);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(90);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(120);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(150);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(180);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(150);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(120);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(90);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(60);
    delay_ms(1000);                    // 1000ms wait
    nServo_PWM = calcPWM(30);
    delay_ms(1000);                    // 1000ms wait
  }
}
