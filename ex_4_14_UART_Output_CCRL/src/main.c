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

void main(void);
void UART1_Transmit(unsigned char data);
unsigned char UART1_Receive(void);
void UART1_Puts(char* str);
void delay_ms(int ms);

extern void HardwareSetup(void);

void main(void)
{
  HardwareSetup();                     // �n�[�h�E�F�A�ݒ�
  SS0=0x000C;                          // �V���A���`���l���Q�ƂR�ʐM�J�n�Z�b�g
  while (1)
  {
    UART1_Puts("Hello, NEWTC\nHello, RL78\n");  // "Hello, NEWTC\nHello, RL78\n"���M
    delay_ms(100);                     // 100ms wait
  }

}
void UART1_Transmit(unsigned char data)
{
  while ((SSR02) & (1 << 6))           // �ʐM����ҋ@�҂�
  {

  }
  TXD1 = data;                         // ���M�f�[�^�ݒ�
}
unsigned char UART1_Receive(void)
{
  unsigned char data;
  while (!((SSR03) & (1 << 5)))        // ��M�����҂�
  {

  }
  data = RXD1;                         // ��M�f�[�^�擾
  return data;
}
void UART1_Puts(char* str)
{
  while (*str)                         // NULL�܂ŌJ��Ԃ�
  {
    UART1_Transmit(*str);              // UART1���M�f�[�^�ݒ�
    str++;
  }
}

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
