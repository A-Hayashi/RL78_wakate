/***********************************************************************/
/*                                                                     */
/*  FILE        :hardware_setup.c                                      */
/*  DATE        :                                                      */
/*  DESCRIPTION :Hardware setup Program                                */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "iodefine.h"
#include "macrodriver.h"

void HardwareSetup(void);
void UART1Init(void);

void HardwareSetup(void)
{
  UART1Init();                         // UART1�����ݒ�
}

void UART1Init(void)
{
  SAU0EN=1;                            // �V���A���A���C�O�N���b�N����
  SPS0=0x0044;                         // 32MHz/2��4��=2MHz
  SMR02=0x0022;                        // UART���[�h,�]���������荞��
  SCR02=0x8097;                        // ���M�̂�,LSB�t�@�[�X�g,1STOP bit,�f�[�^8�r�b�g
  SDR02=0xCE00;                        // 2MHz/(CE/2+1)/2=9615Hz
  NFEN0=0x04;                          // RxD1�̃m�C�Y�t�B���^ON

  SIR03=0x07;                          // �G���[�t���O�N���A
  SMR03=0x0022;                        // UART���[�h,�]���������荞��
  SCR03=0x4097;                        // ��M�̂�,LSB�t�@�[�X�g,1STOP bit,�f�[�^8�r�b�g
  SDR03=0xCE00;                        // 2MHz/(CE/2+1)/2=9615Hz

  SO0  |= 0x04;
  SOL0 |= 0x00;                        //�ʐM�f�[�^�����̂܂܏o��(���]���Ȃ�)
  SOE0 |= 0x04;                        // �`�����l���Q�V���A���ʐM�ɂ��o�͋���

  //RxD1�s���ݒ�
  PMC0 &= ~0x08;
  PM0 |= 0x08;

  //TxD1�s���ݒ�
  PMC0 &= ~0x04;
  P0 |= 0x04;
  PM0 &= ~0x04;
}
