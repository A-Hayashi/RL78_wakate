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
void delay_us(register int us)
{
  us<<=1;
  us-=8;
  while(us)
  {
    us--;
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
    UART1_Transmit(*str);              // UART1���M�f�[�^���M
    str++;
  }
}

unsigned int Generate_ADC_Value(int pinNum)
{
  unsigned int temp;
  ADS=pinNum;                          // AD�ϊ��s���ݒ�
  ADCS=1;                              // AD�ϊ��J�n
  delay_us(3);                         // 3us wait
  while(ADCS)                          // AD�ϊ���~�҂�
  {

  }
  temp=ADCR;                           // AD�ϊ��f�[�^�擾
  return temp>>6;
}

void main(void)
{
  volatile int ADC_Value[20];
  char Buffer[1000];
  int delaycount=0;
  int i;
  HardwareSetup();                     // �n�[�h�E�F�A�ݒ�
  SS0=0x000C;                          // �V���A���`���l���Q�ƂR�ʐM�J�n�Z�b�g
  while(1)
  {
    for(i=18;i<19;i++)
    {
      ADC_Value[i]=Generate_ADC_Value(i);  // AD�ϊ�(0-7)
    }
    delay_ms(1);                       // 1ms wait
    delaycount++;                      // �J�E���g�A�b�v
    if(delaycount==25)                 // �J�E���^=25?
    {
      sprintf(Buffer,"ADC[18] = %04d\n", ADC_Value[18]);
      UART1_Puts(Buffer);              // AD�ϊ�����18�o��
      delaycount=0;
    }
  }
}
