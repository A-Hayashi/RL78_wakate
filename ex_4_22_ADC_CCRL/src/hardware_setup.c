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

void HardwareSetup(void);
void UART1Init(void);
void ADCInit(void);

void HardwareSetup(void)
{
  DI();                                // 割り込み禁止
  UART1Init();                         // UART1初期化
  ADCInit();                           // ADC初期化
}
void ADCInit(void)
{
  ADPC=0x00;                           // A/Dポート全アナログ設定

  PM14=0x80;                            // P2全入力設定

  ADCEN=1;                             // ADCクロック供給
  ADM0=0B00110010;                     // 変換時間2.125us
  ADM1=0B00100000;                     // ソフトウェアトリガ,ワンショット変換モード
  ADM2=0B00000000;                     // 10ビット分解能
  ADCE=1;                              // 変換許可
}

void UART1Init(void)
{
  SAU0EN=1;                            // シリアルアレイ０クロック供給
  SPS0=0x0044;                         // 32MHz/2の4乗=2MHz
  SMR02=0x0022;                        // UARTモード,転送完了割り込み
  SCR02=0x8097;                        // 送信のみ,LSBファースト,1STOP bit,データ8ビット
  SDR02=0xCE00;                        // 2MHz/(CE/2+1)/2=9615Hz
  NFEN0=0x04;                          // RxD1のノイズフィルタON

  SIR03=0x07;                          // エラーフラグクリア
  SMR03=0x0122;                        // UARTモード,転送完了割り込み
  SCR03=0x4097;                        // 受信のみ,LSBファースト,1STOP bit,データ8ビット
  SDR03=0xCE00;                        // 2MHz/(CE/2+1)/2=9615Hz

  SO0  |= 0x04;
  SOL0 |= 0x00;                        //通信データをそのまま出力(反転しない)
  SOE0 |= 0x04;                        // チャンネル２シリアル通信による出力許可

  //RxD1ピン設定
  PMC0 &= ~0x08;
  PM0 |= 0x08;

  //TxD1ピン設定
  PMC0 &= ~0x04;
  P0 |= 0x04;
  PM0 &= ~0x04;
}
