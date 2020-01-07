/***********************************************************************/
/*  																   */
/*  FILE		:Main.c 											   */
/*  DATE		:   												   */
/*  DESCRIPTION :Main Program   									   */
/*  CPU TYPE	:   												   */
/*  																   */
/*  NOTE:THIS IS A TYPICAL EXAMPLE. 								   */
/*  																   */
/***********************************************************************/
#include "iodefine.h"

void delay_ms(int ms)
{
	volatile int i;
	volatile int j;

	for(i=0;i<ms;i++){
		for(j=0;j<100;j++){

		}
	}
}


void main(void)
{
	volatile unsigned char output = 0x01;

	PM1=0x00;				// P1全出力
	P1=~output;				// P10 Low,P11-7 High

	while (1){
		if(output==0x80){	// P17のみHigh?
			output = 0x01;	// P10のみHigh
		}else{
			output = (output << 1) & 0xff;	// P1出力左シフト
		}

		P1 = ~output;
		delay_ms(100);		// 100ms wait
	}
}

