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
  MOTOR_PORTMODE = 0x00;                 // ���[�^�|�[�g�o��
  MOTOR_PORT = 0xf0;                     // ���[�^�|�[�gLow
}

/* 4�����[�^��1-2���㎥���� */
unsigned char Left_1step_walk(char dir) {
  static int leftStep = 0;
  char step_left[] = { 0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08 };
  if (dir) {                          // ������?
    leftStep++;                        // �A�b�v
    leftStep %= 8;                       // �I�[�o�[�t���[�΍�
  } else {
    if (leftStep == 0) {                   // ����?
      leftStep = 7;                      // ����l
    } else {
      leftStep--;                      // �_�E��
    }
  }
  return step_left[leftStep];          // ��step�l��Ԃ�

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

  port_init();                         // �|�[�g������
  while (1) {
    stepleft = Left_1step_walk(0);     // ��1step�t����
    delay_ms(2);                       // 2ms wait
    MOTOR_PORT = 0xf0 | stepleft;             // ���[�^�o��
  }

}
