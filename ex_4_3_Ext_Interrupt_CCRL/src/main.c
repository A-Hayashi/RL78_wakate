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

unsigned char flag=0;
extern void HardwareSetup(void);

//SW1:P137(INTP0)
//LED0-7:P10-P17

void delay_ms(int ms)
{
  volatile int i,j;
  for(i=0;i<ms;i++)
  {
    for(j=0;j<100;j++)
    {

    }
  }
}
void main(void)
{
    
  unsigned char P1Data;
  HardwareSetup();                     // �n�[�h�E�F�A�ݒ�
  P1=0xff;                             // P1�SHigh
	PM1=0x00;                            // P1�S�o��
  P1Data=0x01;                         // 1�ݒ�
  while (1)
  {
    P1=~P1Data;                        // ���]�o��
    if(flag)                           // �t���O�Z�b�g?
    {
      if(P1Data==0x08)                 // ���?
      {
        P1Data=0x01;                   // �����ݒ�
      }
      else
      {
        P1Data<<=1;                    // ���V�t�g
      }
    }
    else
    {
      if(P1Data==0x01)                 // ����?
      {
        P1Data=0x08;                   // ����ݒ�
      }
      else
      {
        P1Data>>=1;                    // �E�V�t�g
      }
    }
    delay_ms(100);                     // 100ms wait
  }
}