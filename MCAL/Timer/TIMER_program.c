

#include"Std_Types_Moamen.h"
#include"Bit_Math_Moamen.h"

#include"TIMER_config.h"
#include"TIMER_interface.h"
#include"TIMER_private.h"
#include"TIMER_register.h"

static void (*TIMER0_pvCallBackFunc)(void) = NULL_POINTER;

/*Timer 1*/
void TIMER1_voidInit(void){
	/*Setting Fast PWM Non Inverting Mode*/
	Set_Bit(TCCR1A,TCCR1A_COM1A1);
	Clr_Bit(TCCR1A,TCCR1A_COM1A0);
	/*Setting Waveform For Fast PWM*/
	Set_Bit(TCCR1A,TCCR1A_WGM11);
	Set_Bit(TCCR1B,TCCR1B_WGM12);
	Set_Bit(TCCR1B,TCCR1B_WGM13);
	Clr_Bit(TCCR1A,TCCR1A_WGM10);
	/*Setting prescaler*/
	TCCR1B&=PRESCALER_MASK;
	TCCR1B|=DIVIDE_BY_8;

}
void Timer1_voidSetICR(u16 Copy_u16Top){
ICR1=Copy_u16Top;
}

void Timer1_voidSetChannelACompMatch(u16 Copy_u16CompareMatch){
OCR1A=Copy_u16CompareMatch;
}

/*Timer 0*/
/*void TIMER0_voidInit(void) {
	Choose CTC mode
	Set_Bit(TCCR0, TCCR0_WGM00);
	Set_Bit(TCCR0, TCCR0_WGM01);
	Output compare match interrupt enable
	Clr_Bit(TIMSK, TIMSK_OCIE0);
	Set compare match value to 125
	OCR0 = 125;
	Prescaler Division By 64
	Set_Bit(TCCR0, TCCR0_CS00);
	Set_Bit(TCCR0, TCCR0_CS01);
	Clr_Bit(TCCR0, TCCR0_CS02);
	Clear on Comare Match Set on Top
    Set_Bit(TCCR0,5);
    Clr_Bit(TCCR0,4);
}

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value){

	OCR0 = Copy_u8Value;

}*/

/*u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void)) {

	u8 Local_u8ErrorState;
	if (Copy_pvCallBackFunc != NULL_POINTER) {
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	} else {
		Local_u8ErrorState = NULL;
	}
	return Local_u8ErrorState;
}*/

void __vector_10(void) __attribute__((signal));
void __vector_10(void) {
	if (TIMER0_pvCallBackFunc != NULL_POINTER) {
		TIMER0_pvCallBackFunc();
	}
}
