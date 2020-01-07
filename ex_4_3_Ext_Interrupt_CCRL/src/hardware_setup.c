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

//SW1:P137(INTP0)

void HardwareSetup(void)
{
  EGP0_bit.no0=1;                      // �����オ��G�b�W
  EGN0_bit.no0=0;
  PMK0=0;                              // INT0�}�X�N�N���A
  EI();                                // ���荞�݋���
} 
