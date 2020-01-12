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

// MCP23017
#define MCP23017_BASE_ADDRESS  0x40

#define MCP23017_IODIRA    0x00
#define MCP23017_IODIRB    0x01
#define MCP23017_GPIOA     0x12
#define MCP23017_GPIOB     0x13

#define SLAVE_ADDR         0B01000000  // slave address

unsigned char iic_send_end;            // IIC���M����
unsigned char iic_read_end;            // IIC��M����

void main(void);
void init_mcp23017(unsigned char dirA,unsigned char dirB);
void IIC_send(unsigned char *buf, unsigned char len);
void IIC_read(unsigned char *buf, unsigned char len);

extern void HardwareSetup(void);
extern void IIC00_MasterSend(unsigned char addr,unsigned char *buf,unsigned char len );
extern void IIC00_MasterReceive(unsigned char addr,unsigned char *buf,unsigned char len );

unsigned char iic_buf_read[2];
unsigned char iic_buf_write[2];
void main(void)
{
  HardwareSetup();
  init_mcp23017(0xfe,0x01);            // A:LED�o��,B�L:�[����
  iic_buf_read[0] = MCP23017_GPIOB;
  iic_buf_write[0] = MCP23017_GPIOA;

  while (1U)
  {
    IIC_send(iic_buf_read,1);               // �L�[�A�h���X��������
    IIC_read(&iic_buf_read[1],1);           // �L�[�ǂݍ���

    iic_buf_write[1] = iic_buf_read[1];

    IIC_send(iic_buf_write,2);               // LED��������
  }
}
void init_mcp23017(unsigned char dirA,unsigned char dirB)
{
  unsigned char tx_buf[2];
  // IODIRA
  tx_buf[0] = MCP23017_IODIRA;
  tx_buf[1] = dirA;
  IIC_send(tx_buf,2);                  // GPIOA�̓��o�͐ݒ�
  // IODIRB
  tx_buf[0] = MCP23017_IODIRB;
  tx_buf[1] = dirB;
  IIC_send(tx_buf,2);                  // GPIOB�̓��o�͐ݒ�
}
void IIC_send(unsigned char *buf, unsigned char len)
{
  IIC00_MasterSend(SLAVE_ADDR,buf,len);  // ���M
  while( iic_send_end == 0 );          // ���M�����҂�
  iic_send_end = 0;                    // ���M�����N���A
}
void IIC_read(unsigned char *buf, unsigned char len)
{
  IIC00_MasterReceive(SLAVE_ADDR,buf,len);  // ��M
  while( iic_read_end == 0 );          // ��M�����҂�
  iic_read_end = 0;                    // ��M�����N���A
}
