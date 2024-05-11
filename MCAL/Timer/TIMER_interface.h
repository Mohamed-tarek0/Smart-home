

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


void TIMER1_voidInit(void);

void TIMER0_voidInit(void);

void Timer1_voidSetICR(u16 Copy_u16Top);

void Timer1_voidSetChannelACompMatch(u16 Copy_u16CompareMatch);

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value);


#endif
