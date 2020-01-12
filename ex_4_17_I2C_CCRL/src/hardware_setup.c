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
  IIC00_Create();                      // IIC00生成
  EI();                                // 割り込み許可
} 
void IIC00_Create(void)
{
  volatile unsigned char w_count;

  SAU0EN = 1;                          // シリアルアレイクロック供給
  NOP();
  NOP();
  NOP();
  NOP();
  SPS0 = 0x0000;                       // 32MHz選択
  SMR02 = 0x0024;                      // CK00選択,簡易I2Cモード,転完了割り込み
  SCR02 = 0x0017;                      // データ長8ビット
  SDR02 = 0x4E00;                      // 32MHz/80=400kHz
  SO0 = 0x0404;                        // クロックとデータHigh出力

  POM0 |= 0x18;                        // Nchオープンドレイン出力
  PMC0 &= ~0x18;
  P0 |= 0x18;
  PM0 &= ~0x18;                        // クロックとデータポートHigh出力

}
void IIC00_MasterSend(unsigned char addr,unsigned char *buf,unsigned char len )
{
  g_iic00_master_status_flag = 0;      // ステータスクリア
  addr &= 0xFE;                        // 送信セット
  g_iic00_master_status_flag = 1;      // ステータス 送信モード設定
  SCR02 &= ~0xC000;                    // 送受信クリア
  SCR02 |= 0x8000;                     // 送信のみ行う
  g_iic00_tx_count =len;               // 送信バイト数保存
  gp_iic00_tx_address = buf;           // 送信アドレス保存
  IIC00_StartCondition();              // スタートコンディション
  IICIF10 = 0;                         // IIC00割り込み要求クリア
  IICMK10 = 0;                         // IIC00割り込みマスククリア
  SIO10 = addr;                        // スレーブアドレス設定
}
void IIC00_MasterReceive(unsigned char addr,unsigned char *buf,unsigned char len )
{
  g_iic00_master_status_flag = 0;      // ステータスクリア
  addr |= 0x01;                        // 受信セット
  g_iic00_master_status_flag = 2;      // ステータス 受信モード設定
  SCR02 &= ~0xC000;                    // 送受信クリア
  SCR02 |= 0x8000;                     // 送信のみ行う
  g_iic00_rx_length = len;             // 受信バイト数保存
  g_iic00_rx_count =0;                 // 受信カウンタクリア
  gp_iic00_rx_address = buf;           // 受信アドレス保存
  IIC00_StartCondition();              // スタートコンディション
  IICIF10 = 0;                         // IIC00割り込み要求クリア
  IICMK10 = 0;                         // IIC00割り込みマスククリア
  SIO10 = addr;                        // スレーブアドレス設定
}
void IIC00_Stop(void)
{
  IICMK10 = 1;                         // IIC00マスクセット
  ST0 |= 0x0004;                       // IIC00通信動作停止
  IICIF10 = 0;                         // IIC00割り込み要求クリア
}
void IIC00_StartCondition(void)
{
  volatile unsigned char w_count;
  
  SO0 &= ~0x0004;                      // データLow出力
  for (w_count = 0U; w_count <= IIC00_WAITTIME; w_count++)
  {
    NOP();
  }
  SO0 &= ~0x0400;                      // クロックLow出力
  SOE0 |= 0x0004;                      // シリアル通信出力許可
  SS0 |= 0x0004;                       // 通信待機状態セット
}
void IIC00_StopCondition(void)
{
  volatile unsigned char w_count;

  ST0 |= 0x0004;                       // IIC00通信動作停止
  SOE0 &= ~0x0004;                     // シリアル通信出力禁止
  SO0 &= ~0x0004;                      // データLow出力
  SO0 |= 0x0400;                       // クロックHigh出力
  for (w_count = 0U; w_count <= IIC00_WAITTIME; w_count++)
  {
    NOP();
  }
  SO0 |= 0x0004;                       // データHigh出力
}
