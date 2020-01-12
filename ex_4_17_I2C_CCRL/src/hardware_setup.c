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

#define IIC00_WAITTIME      (160U)             // change the waiting time according to the system

volatile uint8_t   g_iic00_master_status_flag; // iic00 start flag
volatile uint8_t * gp_iic00_tx_address;        // iic00 send data pointer
volatile uint16_t  g_iic00_tx_count;           // iic00 send data size
volatile uint8_t * gp_iic00_rx_address;        // iic00 receive data pointer
volatile uint16_t  g_iic00_rx_count;           // iic00 receive data size
volatile uint16_t  g_iic00_rx_length;          // iic00 receive data length

void HardwareSetup(void);
void IIC00_Create(void);
void IIC00_Stop(void);
void IIC00_StartCondition(void);
void IIC00_StopCondition(void);

void HardwareSetup(void)
{
  IIC00_Create();                      // IIC00����
  EI();                                // ���荞�݋���
} 
void IIC00_Create(void)
{
  volatile unsigned char w_count;

  SAU0EN = 1;                          // �V���A���A���C�N���b�N����
  NOP();
  NOP();
  NOP();
  NOP();
  SPS0 = 0x0000;                       // 32MHz�I��
  SMR02 = 0x0024;                      // CK00�I��,�Ȉ�I2C���[�h,�]�������荞��
  SCR02 = 0x0017;                      // �f�[�^��8�r�b�g
  SDR02 = 0x4E00;                      // 32MHz/80=400kHz
  SO0 = 0x0404;                        // �N���b�N�ƃf�[�^High�o��

  POM0 |= 0x18;                        // Nch�I�[�v���h���C���o��
  PMC0 &= ~0x18;
  P0 |= 0x18;
  PM0 &= ~0x18;                        // �N���b�N�ƃf�[�^�|�[�gHigh�o��

}
void IIC00_MasterSend(unsigned char addr,unsigned char *buf,unsigned char len )
{
  g_iic00_master_status_flag = 0;      // �X�e�[�^�X�N���A
  addr &= 0xFE;                        // ���M�Z�b�g
  g_iic00_master_status_flag = 1;      // �X�e�[�^�X ���M���[�h�ݒ�
  SCR02 &= ~0xC000;                    // ����M�N���A
  SCR02 |= 0x8000;                     // ���M�̂ݍs��
  g_iic00_tx_count =len;               // ���M�o�C�g���ۑ�
  gp_iic00_tx_address = buf;           // ���M�A�h���X�ۑ�
  IIC00_StartCondition();              // �X�^�[�g�R���f�B�V����
  IICIF10 = 0;                         // IIC00���荞�ݗv���N���A
  IICMK10 = 0;                         // IIC00���荞�݃}�X�N�N���A
  SIO10 = addr;                        // �X���[�u�A�h���X�ݒ�
}
void IIC00_MasterReceive(unsigned char addr,unsigned char *buf,unsigned char len )
{
  g_iic00_master_status_flag = 0;      // �X�e�[�^�X�N���A
  addr |= 0x01;                        // ��M�Z�b�g
  g_iic00_master_status_flag = 2;      // �X�e�[�^�X ��M���[�h�ݒ�
  SCR02 &= ~0xC000;                    // ����M�N���A
  SCR02 |= 0x8000;                     // ���M�̂ݍs��
  g_iic00_rx_length = len;             // ��M�o�C�g���ۑ�
  g_iic00_rx_count =0;                 // ��M�J�E���^�N���A
  gp_iic00_rx_address = buf;           // ��M�A�h���X�ۑ�
  IIC00_StartCondition();              // �X�^�[�g�R���f�B�V����
  IICIF10 = 0;                         // IIC00���荞�ݗv���N���A
  IICMK10 = 0;                         // IIC00���荞�݃}�X�N�N���A
  SIO10 = addr;                        // �X���[�u�A�h���X�ݒ�
}
void IIC00_Stop(void)
{
  IICMK10 = 1;                         // IIC00�}�X�N�Z�b�g
  ST0 |= 0x0004;                       // IIC00�ʐM�����~
  IICIF10 = 0;                         // IIC00���荞�ݗv���N���A
}
void IIC00_StartCondition(void)
{
  volatile unsigned char w_count;
  
  SO0 &= ~0x0004;                      // �f�[�^Low�o��
  for (w_count = 0U; w_count <= IIC00_WAITTIME; w_count++)
  {
    NOP();
  }
  SO0 &= ~0x0400;                      // �N���b�NLow�o��
  SOE0 |= 0x0004;                      // �V���A���ʐM�o�͋���
  SS0 |= 0x0004;                       // �ʐM�ҋ@��ԃZ�b�g
}
void IIC00_StopCondition(void)
{
  volatile unsigned char w_count;

  ST0 |= 0x0004;                       // IIC00�ʐM�����~
  SOE0 &= ~0x0004;                     // �V���A���ʐM�o�͋֎~
  SO0 &= ~0x0004;                      // �f�[�^Low�o��
  SO0 |= 0x0400;                       // �N���b�NHigh�o��
  for (w_count = 0U; w_count <= IIC00_WAITTIME; w_count++)
  {
    NOP();
  }
  SO0 |= 0x0004;                       // �f�[�^High�o��
}
