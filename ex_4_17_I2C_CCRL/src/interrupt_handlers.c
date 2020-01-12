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
extern unsigned char iic_send_end;     // IIC送信完了
extern unsigned char iic_read_end;     // IIC受信完了

extern void IIC00_StopCondition(void);


#pragma interrupt INT_IIC00(vect=INTIIC10)
void INT_IIC00(void)
{
  if( ( (SSR02 & 0x0002) == 0)&&( (SSR02 & 0x0001) == 0 ) ) //ACK受信オーバランエラーなし?
  {
    // send
    if( g_iic00_master_status_flag & 0x01 )    // ステータス マスタ送信中?
    {
      if( g_iic00_tx_count > 0 )
      {
        SIO10 = *gp_iic00_tx_address;  // 送信データ設定
        gp_iic00_tx_address++;         // 送信データアドレスアップ
        g_iic00_tx_count--;            // 送信バイト数カウントダウン
      } else
      {
        IIC00_StopCondition();         // ストップコンディション
        iic_send_end = 1;              // 送信完了セット
      }
    } else
    {
      if( (g_iic00_master_status_flag & 0x04) == 0x00 )  // ステータス アドレス送信?
      {
        ST0 |= 0x0004;                 // 通信動作停止
        SCR02 &= ~0xC000;              // 送受信クリア
        SCR02 |= 0x4000;               // 受信のみ行う
        SS0 |= 0x0004;                 // 通信待機セット
        g_iic00_master_status_flag |= 0x04;  // アドレス送信済みセット
        if(g_iic00_rx_length == 1)
        {
          SOE0 &= ~0x0004;             // シリアル通信出力停止
        }
        SIO10 = 0xFF;                  // ダミー送信設定
      } else
      {
        if( g_iic00_rx_count < g_iic00_rx_length )  // 未受信データあり?
        {
          *gp_iic00_rx_address = SIO10;  // 受信データ格納
          gp_iic00_rx_address++;       // 受信データ格納アドレスアップ
          g_iic00_rx_count++;          // 受信データ数アップ
          if(g_iic00_rx_count < g_iic00_rx_length - 1 )
          {
            SOE0 &= ~0x0004;           // シリアル通信出力停止
            SIO10 = 0xFF;              // ダミー送信設定
          } else if( g_iic00_rx_count == g_iic00_rx_length )
          {
            IIC00_StopCondition();	   // ストップコンディション
            iic_read_end = 1;          // 受信完了セット
          } else
          {
            SIO10 = 0xFF;              // ダミー送信設定
          }
        }
      }
    }
  }
}
