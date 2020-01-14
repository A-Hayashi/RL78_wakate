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

#define KEYIN P1
#define KEYOUT P6
#define _BV(x) (1<<x)

unsigned char keystate[4][4];

void main(void);
void delay_ms(int ms);
void delay_us(register int us);
void keyscan(void);
void keyshow(void);

extern void HardwareSetup(void);

void main(void)
{
  HardwareSetup();                     // �n�[�h�E�F�A�ݒ�
  SS0=0x000C;                          // �V���A���`���l���Q�ƂR�ʐM�J�n�Z�b�g
  while (1)
  {
    keyscan();                         // �L�[�X�L����
    keyshow();                         // �L�[�f�[�^�o��
    delay_ms(500);                     // 500ms wait
  }
}

int putchar(int data)
{
  while ((SSR02) & (1 << 6))           // �ʐM����ҋ@�҂�
  {

  }
  TXD1 = (char)data;                   // ���M�f�[�^�ݒ�
  return data;
}
int getchar(void)
{
  int data;
  while (!((SSR03) & (1 << 5)))        // ��M�����҂�
  {

  }
  data = RXD1;                         // ��M�f�[�^�擾
  return data;
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
void delay_us(register int us)
{
  us<<=1;
  us-=8;
  while(us)
  {
    us--;
  }
}

void keyscan(void)
{
  volatile char x,y;
  volatile unsigned char value;
  unsigned char tmp;
  for(x=0;x<4;x++)
  {
    tmp = (unsigned char)(~(_BV(x)));
    KEYIN=tmp&0x0F;                    // �L�[�X�L�����o��
    delay_us(5);                       // 5us wait
    value = KEYOUT;                 // �L�[�ǂݍ���
    for(y=0;y<4;y++)
    {
      if((value&(_BV(y))))             // �L�[�I��?
      {
        keystate[x][y] = 1;            // �Z�b�g
      }
      else
      {
        keystate[x][y] = 0;            // �N���A
      }
    }

  }
}
void keyshow(void)
{
  int x,y;
  printf("\r\n\r\n");
  for(x=0;x<4;x++)
  {
    printf("\r\n");                    // ���s�o��
    for(y=0;y<4;y++)
    {
      printf(" %d", keystate[y][x]);   // �L�[�f�[�^�o��
    }
  }
}
