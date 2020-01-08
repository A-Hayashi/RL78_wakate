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

#define C1 523                         //�h
#define C1_ 554
#define D1 587                         //��
#define D1_ 622
#define E1 659                         //�~
#define F1 699                         //�t�@
#define F1_ 740
#define G1 784                         //�\
#define G1_ 831
#define A1 880                         //��
#define A1_ 932
#define B1 988                         //�V

#define C2 C1*2                        //�h
#define C2_ C1_*2
#define D2 D1*2                        //��
#define D2_ D1_*2
#define E2 E1*2                        //�~
#define F2 F1*2                        //�t�@
#define F2_ F1_*2
#define G2 G1*2                        //�\
#define G2_ G1_*2
#define A2 A2*2                        //��
#define A2_ A2_*2
#define B2 B2*2                        //�V

#define DLY_1 DLY_4*4                  //�S����
#define DLY_2 DLY_4*2                  // 2������
#define DLY_4 400                      // 4������
#define DLY_8 DLY_4/2                  // 8������
#define DLY_16 DLY_8/2                 // 16������

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
void main(void)
{
  int freq = 1000, i;
  int song[42]={C1,C1,G1,G1,A1,A1,G1,
          F1,F1,E1,E1,D1,D1,C1,
          G1,G1,F1,F1,E1,E1,D1,
          G1,G1,F1,F1,E1,E1,D1,
          C1,C1,G1,G1,A1,A1,G1,          
          F1,F1,E1,E1,D1,D1,C1,};
  int length[42]={DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,
      DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_4,DLY_2,};

  HardwareSetup();                     // �n�[�h�E�F�A�ݒ�
  PM0=0x00;                            // P0�S�o��
  TS0=0x0001;                          // �^�C�}00�J�E���g�J�n

  while(1)
  {
    for(i=0;i<42;i++)
    {
      freq = song[i];                  // ���g���擾
      // TDR00 = ((1/(2*freq)) / (4/1000000));
      TDR00 = (1000000/(8*freq));      // ���荞�ݎ��ԎZ�o
      TOE0L_bit.no0 = 1;               // TO00�o�͋���
      delay_ms(length[i]);             // �҂�����
      TOE0L_bit.no0 = 0;               // TO00�o�͋֎~�i�x���j
      delay_ms(5);                     // 5ms wait
    }
    delay_ms(10000);                   // 10s wait
  }
}
