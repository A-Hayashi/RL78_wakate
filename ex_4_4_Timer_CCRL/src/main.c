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

unsigned char portValue = 0;
void main(void);
extern void HardwareSetup(void);

void main(void) {
  HardwareSetup();                     // �n�[�h�E�F�A�ݒ�

  P1 = 0xff;                             // P1�SHigh
  PM1 = 0x00;                            // P1�S�o�͐ݒ�

  TS0 = 0x0001;                          // �^�C�}00�J�E���g�J�n

  while (1) {
    P1 = ~portValue;                     // ���荞�݃J�E���^�̔��]�o��
  }
}
