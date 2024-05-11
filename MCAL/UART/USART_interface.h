
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void USART_INIT(void);

void USART_voidSend(u32 data);

u8   USART_u8Recive(void);

void USART_voidSendString(const char* Copy_pcString);


#endif
