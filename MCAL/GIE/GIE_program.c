

#include"Std_Types.h"
#include"Bit_Math.h"
#include"GIE_interface.h"
#include"GIE_register.h"

void GIE_voidEnable(void)
{
	Set_Bit(SREG,SREG_I);	
}
void GIE_voidDisable(void)
{
	Clr_Bit(SREG,SREG_I);	
}
