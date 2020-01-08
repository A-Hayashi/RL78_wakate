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
#include "macrodriver.h"

void main(void);
volatile int Now_Data[2];
extern void HardwareSetup(void);

void delay_ms(int ms) {
  volatile int i, j;
  for (i = 0; i < ms; i++) {
    for (j = 0; j < 2963; j++) {

    }
  }
}

void main(void) {
  int i;

  HardwareSetup();  // �n�[�h�E�F�A�ݒ�

  P5 = 0xff;
  P7 = 0x00;

  PM5 = 0x00;  // P5�S�o�͐ݒ�
  PM7 = 0x00;  // P7�S�o�͐ݒ�

  TS0 = 0x0001;  // �^�C�}00�J�E���g�J�n
  while (1) {
    for (i = 0; i < 99; i++) {
      DI();
      Now_Data[0] = i % 10;  // ��ʐݒ�
      Now_Data[1] = i / 10;  // �\�ʐݒ�
      EI();
      delay_ms(100);  // 100ms wait
    }
  }
}
