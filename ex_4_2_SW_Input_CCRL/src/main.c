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
void main(void)
{
	//SW1 P137
	//SW2 P31
	//SW3 P140
	//LED1 P11
	//LED4 P14
	//LED7 P17

	volatile unsigned char value;
	P1 = 0xff;
	
  PM3=0x02;       // P31入力
  PM14=0x01;      // P140入力
	
	PM1=0x00;				//PM1全出力
	
  while (1)
  {
	    value = P13>>7; //SW1読み込み
			if(value==1){		//SW1 OFF
	    	P1 |= 0x01;   //LED1 消灯
			}else{					//SW1 ON
				P1 &= ~0x01;	//LED1 点灯
			}
						
	    value = P3>>1; 	//SW2読み込み
			if(value==1){		//SW2 OFF
	    	P1 |= 0x10;   //LED4 消灯
			}else{					//SW2 ON
				P1 &= ~0x10;	//LED4 点灯
			}
			
	    value = P14>>0; //SW3読み込み
			if(value==1){		//SW3 OFF
	    	P1 |= 0x80;   //LED7 消灯
			}else{					//SW3 ON
				P1 &= ~0x80;	//LED7 点灯
			}
	}
}
