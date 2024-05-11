

#include "Std_Types_Moamen.h"
#include "Bit_Math_Moamen.h"

#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_register.h"

void USART_INIT(void) {
    u8 Local_u8UCSRCValue=0;
	Set_Bit(Local_u8UCSRCValue, UBRRH_URSEL);

	/*8 Data bits*/
	Set_Bit(Local_u8UCSRCValue, UCSRC_UCSZ0);
	Set_Bit(Local_u8UCSRCValue, UCSRC_UCSZ1);


	UCSRC=Local_u8UCSRCValue;
	/*9600 Baud Rate*/
	UBRRL = 51;

	Set_Bit(UCSRB,UCSRB_TXEN);
	Set_Bit(UCSRB,UCSRB_RXEN);

}

void USART_voidSendString(const char* Copy_pcString) {
	u8 Local_u8Counter = 0;
	while (Copy_pcString[Local_u8Counter] != '\0') {
		USART_voidSend(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void USART_voidSend(u32 Copy_u8data) {
while (Get_Bit(UCSRA,UCSRA_UDRE)==0);
      UDR = Copy_u8data;

}

u8 USART_u8Recive(void) {
	while (Get_Bit(UCSRA,UCSRA_RXC)==0);
	return UDR;
}
