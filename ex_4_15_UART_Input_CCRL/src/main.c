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

void main(void);

extern void HardwareSetup(void);

void main(void)
{
  int a;
  HardwareSetup();                     // �n�[�h�E�F�A������
  SS0=0x000C;                          // �V���A���`���l���Q�ƂR�ʐM�J�n�Z�b�g
  while (1)
  {
    a = 10;
    scanf("%d",&a);                    // ����
    printf("Index = %d\n",a);          // �o��
  }

}

int putchar(int c)
{
  while ((SSR02) & (1 << 6))           // �ʐM����ҋ@�҂�
  {

  }
  TXD1 = (unsigned char)c;             // ���M�f�[�^�ݒ�
  return c;
}
int getchar(void)
{
  unsigned char data;
  while (!((SSR03) & (1 << 5)))        // ��M�����҂�
  {

  }
  data = RXD1;                         // ��M�f�[�^�擾
  return (int)data;  
}

