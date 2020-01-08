/***********************************************************************/
/*                                                                     */
/*  FILE        :interrupt_handlers.c                                  */
/*  DATE        :                                                      */
/*  DESCRIPTION :Interrupt Program                                     */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "iodefine.h"

extern volatile int Now_Data[2];

const unsigned char Segment_Data[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
    0x7D, 0x27, 0x7F, 0x6F };

#pragma interrupt INT_TM00(vect=INTTM00)
void INT_TM00(void) {
  static int k = 0;

  P7 = 0x00;  // �Z�O�����g�S����
  P5 = ~(1 << (k + 4));  // ���o�͍X�V
  P7 = Segment_Data[Now_Data[k]];  // �Z�O�����g�f�[�^�o��

  k++;  // ���A�b�v
  k %= 2;  // 2���̗]��
}

