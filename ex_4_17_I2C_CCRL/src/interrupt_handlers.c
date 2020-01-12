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
#include "macrodriver.h"

extern volatile uint8_t   g_iic00_master_status_flag; // iic00 start flag
extern volatile uint8_t * gp_iic00_tx_address;        // iic00 send data pointer
extern volatile uint16_t  g_iic00_tx_count;           // iic00 send data size
extern volatile uint8_t * gp_iic00_rx_address;        // iic00 receive data pointer
extern volatile uint16_t  g_iic00_rx_count;           // iic00 receive data size
extern volatile uint16_t  g_iic00_rx_length;          // iic00 receive data length
extern unsigned char iic_send_end;     // IIC���M����
extern unsigned char iic_read_end;     // IIC��M����

extern void IIC00_StopCondition(void);


#pragma interrupt INT_IIC00(vect=INTIIC10)
void INT_IIC00(void)
{
  if( ( (SSR02 & 0x0002) == 0)&&( (SSR02 & 0x0001) == 0 ) ) //ACK��M�I�[�o�����G���[�Ȃ�?
  {
    // send
    if( g_iic00_master_status_flag & 0x01 )    // �X�e�[�^�X �}�X�^���M��?
    {
      if( g_iic00_tx_count > 0 )
      {
        SIO10 = *gp_iic00_tx_address;  // ���M�f�[�^�ݒ�
        gp_iic00_tx_address++;         // ���M�f�[�^�A�h���X�A�b�v
        g_iic00_tx_count--;            // ���M�o�C�g���J�E���g�_�E��
      } else
      {
        IIC00_StopCondition();         // �X�g�b�v�R���f�B�V����
        iic_send_end = 1;              // ���M�����Z�b�g
      }
    } else
    {
      if( (g_iic00_master_status_flag & 0x04) == 0x00 )  // �X�e�[�^�X �A�h���X���M?
      {
        ST0 |= 0x0004;                 // �ʐM�����~
        SCR02 &= ~0xC000;              // ����M�N���A
        SCR02 |= 0x4000;               // ��M�̂ݍs��
        SS0 |= 0x0004;                 // �ʐM�ҋ@�Z�b�g
        g_iic00_master_status_flag |= 0x04;  // �A�h���X���M�ς݃Z�b�g
        if(g_iic00_rx_length == 1)
        {
          SOE0 &= ~0x0004;             // �V���A���ʐM�o�͒�~
        }
        SIO10 = 0xFF;                  // �_�~�[���M�ݒ�
      } else
      {
        if( g_iic00_rx_count < g_iic00_rx_length )  // ����M�f�[�^����?
        {
          *gp_iic00_rx_address = SIO10;  // ��M�f�[�^�i�[
          gp_iic00_rx_address++;       // ��M�f�[�^�i�[�A�h���X�A�b�v
          g_iic00_rx_count++;          // ��M�f�[�^���A�b�v
          if(g_iic00_rx_count < g_iic00_rx_length - 1 )
          {
            SOE0 &= ~0x0004;           // �V���A���ʐM�o�͒�~
            SIO10 = 0xFF;              // �_�~�[���M�ݒ�
          } else if( g_iic00_rx_count == g_iic00_rx_length )
          {
            IIC00_StopCondition();	   // �X�g�b�v�R���f�B�V����
            iic_read_end = 1;          // ��M�����Z�b�g
          } else
          {
            SIO10 = 0xFF;              // �_�~�[���M�ݒ�
          }
        }
      }
    }
  }
}
