
#include"Std_Types.h"
#include"Bit_Math.h"
#include"ADC_interface.h"
#include"ADC_private.h"
#include"ADC_config.h"
#include"ADC_register.h"

void (*Global_PF_Vector_16)(void) = NULL;
u8 * ADC_pu8Reading = NULL;

static u8 * ADC_pu8ChainChannelArr = NULL;
static u8 ADC_u8ChainSize;
static u16* ADC_pu16ChainResultArr = NULL;
static u8 ADC_u8ChainConversionIndex = 0;
static u8  ADC_u8ISRSource;

u16 ADC_u16Result = 0;
u8 ADC_u18BusyFlag = 0;

void ADC_voidInit(void) {
	/*       Select Reference Voltage       */
#if ( REFERENCE_VOLTAGE == AREF )
	Clr_Bit(ADMUX_REG,6);
	Clr_Bit(ADMUX_REG,7);
#elif ( REFERENCE_VOLTAGE == AVCC )
	Set_Bit(ADMUX_REG, 6);
	Clr_Bit(ADMUX_REG, 7);
#elif ( REFERENCE_VOLTAGE == INTERNAL )
	Set_Bit(ADMUX_REG,6);
	Set_Bit(ADMUX_REG,7);
#else
	Clr_Bit(ADMUX_REG,6);
	Set_Bit(ADMUX_REG,7);
#endif
	/*     Select RIGHT or LEFT Adjust      */
#if ( ADJUST == RIGHT )
	Clr_Bit(ADMUX_REG, 5);
#elif ( ADJUST == LEFT )
	Set_Bit(ADMUX_REG, 5);
#endif
	/*        ADC Enable or Disable         */
#if ( ADEN == ENABLE )
	Set_Bit(ADCSRA_REG, 7);
#elif ( ADEN == DISABLE )
	Clr_Bit(ADCSRA_REG,7);
#endif
	/*    AUTO Trigger Enable or Disable    */
#if ( ADATE == ENABLE )
	Set_Bit(ADCSRA_REG,5);
	/*       ADC Auto Trigger Source        */
#if( AUTO_TRIGGER_SOURCE == Free_Running_Mode )
	Clr_Bit(SFIOR_REG,5);
	Clr_Bit(SFIOR_REG,6);
	Clr_Bit(SFIOR_REG,7);
#elif ( AUTO_TRIGGER_SOURCE == Analog_Comparator )
	Set_Bit(SFIOR_REG,5);
	Clr_Bit(SFIOR_REG,6);
	Clr_Bit(SFIOR_REG,7);
#elif ( AUTO_TRIGGER_SOURCE == External_Interrupt_Request_0 )
	Clr_Bit(SFIOR_REG,5);
	Set_Bit(SFIOR_REG,6);
	Clr_Bit(SFIOR_REG,7);
#elif ( AUTO_TRIGGER_SOURCE == Timer_Counter0_Compare_Match )
	Set_Bit(SFIOR_REG,5);
	Set_Bit(SFIOR_REG,6);
	Clr_Bit(SFIOR_REG,7);
#elif ( AUTO_TRIGGER_SOURCE == Timer_Counter0_Overflow )
	Clr_Bit(SFIOR_REG,5);
	Clr_Bit(SFIOR_REG,6);
	Set_Bit(SFIOR_REG,7);
#elif ( AUTO_TRIGGER_SOURCE == Timer_Counter1_Compare_MatchB )
	Set_Bit(SFIOR_REG,5);
	Clr_Bit(SFIOR_REG,6);
	Set_Bit(SFIOR_REG,7);
#elif ( AUTO_TRIGGER_SOURCE == Timer_Counter1_Overflow )
	Clr_Bit(SFIOR_REG,5);
	Set_Bit(SFIOR_REG,6);
	Set_Bit(SFIOR_REG,7);
#elif ( AUTO_TRIGGER_SOURCE == Timer_Counter1_Capture_Event )
	Set_Bit(SFIOR_REG,5);
	Set_Bit(SFIOR_REG,6);
	Set_Bit(SFIOR_REG,7);
#endif

#elif ( ADATE == DISABLE )
	Clr_Bit(ADCSRA_REG, 5);
#endif
	/*    ADC Interrupt Enable or Disable   */
#if ( ADIE == ENABLE )          // work with Interrupt
	Set_Bit(ADCSRA_REG,3);
#elif ( ADIE == DISABLE )       // work with Polling
	Clr_Bit(ADCSRA_REG, 3);
#endif
	/*       ADC Prescaler Selection        */
	/*     Clear Prescaler      */
	ADCSRA_REG = ( ADCSRA_REG & 0b11111000);

#if( PRESCALER == NOT_USE_PRESCALER )
	// NOTHING
#elif ( PRESCALER == PRESCALER_DIVISION_BY_2 )
	Set_Bit(ADCSRA_REG,0);
	Clr_Bit(ADCSRA_REG,1);
	Clr_Bit(ADCSRA_REG,2);
#elif ( PRESCALER == PRESCALER_DIVISION_BY_4 )
	Clr_Bit(ADCSRA_REG,0);
	Set_Bit(ADCSRA_REG,1);
	Clr_Bit(ADCSRA_REG,2);
#elif ( PRESCALER == PRESCALER_DIVISION_BY_8 )
	Set_Bit(ADCSRA_REG,0);
	Set_Bit(ADCSRA_REG,1);
	Clr_Bit(ADCSRA_REG,2);
#elif ( PRESCALER == PRESCALER_DIVISION_BY_16 )
	Clr_Bit(ADCSRA_REG,0);
	Clr_Bit(ADCSRA_REG,1);
	Set_Bit(ADCSRA_REG,2);
#elif ( PRESCALER == PRESCALER_DIVISION_BY_32 )
	Set_Bit(ADCSRA_REG,0);
	Clr_Bit(ADCSRA_REG,1);
	Set_Bit(ADCSRA_REG,2);
#elif ( PRESCALER == PRESCALER_DIVISION_BY_64 )
	Clr_Bit(ADCSRA_REG,0);
	Set_Bit(ADCSRA_REG,1);
	Set_Bit(ADCSRA_REG,2);
#elif ( PRESCALER == PRESCALER_DIVISION_BY_128 )
	Set_Bit(ADCSRA_REG, 0);
	Set_Bit(ADCSRA_REG, 1);
	Set_Bit(ADCSRA_REG, 2);
#endif
}

u16 ADC_u16ReadSynchronus(u8 Copy_u8ChannelNumber) {
	/*     Clear MUX      */
	ADMUX_REG = ( ADMUX_REG & 0b11100000);
	/*   Select channel   */
	switch (Copy_u8ChannelNumber) {
	case ADC0:
		ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000000);
		break;
	case ADC1:
		ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000001);
		break;
	case ADC2:
		ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000010);
		break;
	case ADC3:
		ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000011);
		break;
	case ADC4:
		ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000100);
		break;
	case ADC5:
		ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000101);
		break;
	case ADC6:
		ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000110);
		break;
	case ADC7:
		ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000111);
		break;
	default:
		break;
	}
	/*    Start Conversion    */
#if ( ADATE == ENABLE )
	// Start Conversion When Triggering Occures.
#elif ( ADATE == DISABLE )
	Set_Bit(ADCSRA_REG, 6);
#endif
#if ( ADIE == ENABLE )                        // work with Interrupt
	// When ADC Finish conversion will Raising Interrupt Flag and Jump to ADC_ISR Function.
#elif ( ADIE == DISABLE )                     // work with Polling
	/* GET FLAG and Polling the Flag */
	u8 ADIF = 0;
	while (ADIF == 0) {
		ADIF = Get_Bit(ADCSRA_REG, 4); // Stuck on while untill Flag Raising 1 .
	}
#endif
#if ( ADIE == ENABLE )          // work with Interrupt
	// Interrupt Flag Will Cleared Automaticlly.
#elif ( ADIE == DISABLE )       // work with Polling
	/* Clear Flag */
	Set_Bit(ADCSRA_REG, 4);
#endif

#if ( ADJUST == RIGHT )
	return ADC_REG;
#elif ( ADJUST == LEFT )
	return ADCH_REG;
#endif

}
u16 ADC_u16ReadASynchronus(u8 Copy_u8ChannelNumber, u8 * Copy_pu8Reading,
		void (*Local_PvoidCallBackFunctionPtr)(void)) {
	u8 Local_u8ErrorState;
	if ((Copy_pu8Reading == 0) || (Local_PvoidCallBackFunctionPtr == 0)) {
		Local_u8ErrorState = NULL;
	} else {
		ADC_pu8Reading = Copy_pu8Reading;
		Global_PF_Vector_16 = Local_PvoidCallBackFunctionPtr;
		/*Make ISR Source: Single Channel Asynchronus*/
		ADC_u8ISRSource = SINGLE_CHANNEL_ASYNCH;
		/*   Make the ADC State is Busy   */
		ADC_u18BusyFlag = 0;
		/*     Clear MUX      */
		ADMUX_REG = ( ADMUX_REG & 0b11100000);
		/*   Select channel   */
		switch (Copy_u8ChannelNumber) {
		case ADC0:
			ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000000);
			break;
		case ADC1:
			ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000001);
			break;
		case ADC2:
			ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000010);
			break;
		case ADC3:
			ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000011);
			break;
		case ADC4:
			ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000100);
			break;
		case ADC5:
			ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000101);
			break;
		case ADC6:
			ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000110);
			break;
		case ADC7:
			ADMUX_REG = (( ADMUX_REG & 0b11100000) | 0b00000111);
			break;
		default:
			break;
		}
		/*    Set The Call Back Function    */
		/*    Start Conversion    */
#if ( ADATE == ENABLE )
		// Start Conversion When Triggering Occures.
#elif ( ADATE == DISABLE )
		Set_Bit(ADCSRA_REG, 6);
#endif
		/*     Enable ADIE  AD Interrupt Enable  and Interrupt Flag Will Cleared Automaticlly.       */
		Set_Bit(ADCSRA_REG, 3);
	}
	return Local_u8ErrorState;

}

u8 ADC_u8ReadChainAsynchronus(Chain_t*Copy_Chain) {
	u8 Local_u8ErrorState = OK;
	if (Copy_Chain == NULL_POINTER) {
		Local_u8ErrorState = NULL;

	} else {
		if (ADC_u18BusyFlag == IDLE) {
			/*Make ADC busy*/
			ADC_u18BusyFlag = BUSY;
			/*Make ISR SOURCE : CHAIN ASYNCHRONUS*/
			ADC_u8ISRSource = CHAIN_ASYNCH;
			/*initialize chain channel array*/
			ADC_pu8ChainChannelArr = Copy_Chain->Channel;
			/*initialize result array*/
			ADC_pu16ChainResultArr = Copy_Chain->Result;
			/*initialize chain Size*/
			ADC_u8ChainSize = Copy_Chain->Size;
			/*initialize Notification Func*/
			Global_PF_Vector_16 = Copy_Chain->NotificationFunc;
			/*initialize current conversion index*/
			ADC_u8ChainConversionIndex = 0;

			/*set required channel*/
			ADMUX_REG &= 0b11100000;
			ADMUX_REG |= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];
			/*start conversion */
			Set_Bit(ADCSRA_REG, 6);
			/*Enable conversion complete interrupt*/
			Set_Bit(ADCSRA_REG, 3);

		} else {
			Local_u8ErrorState = BUSY_FUNC;
		}
	}
	return Local_u8ErrorState;

}

void __vector_16(void) __attribute__((signal));
void __vector_16(void) {
	/*        Get Reading from 16 Bit ADC_REG  if we used RIGHT Adjust and Resoluotion 10 BIT  Return Value From { 0 -> 1023 }  */
	/*        Get Reading from 8 Bit ADCH_REG  if we used LEFT Adjust and Resoluotion  8 BIT   Return Value From { 0 -> 255  }  */

	if (ADC_u8ISRSource == SINGLE_CHANNEL_ASYNCH) {
#if ( ADJUST == RIGHT )
		*ADC_pu8Reading = ADC_REG;
#elif ( ADJUST == LEFT )
		*ADC_pu8Reading = ADCH_REG;
#endif

		/*   Make the ADC State is NOT Busy because it's Completed   */
		ADC_u18BusyFlag = 1;

		/*   Call Call Back Function br Global PTR   */
		Global_PF_Vector_16();

		/*     Disable ADIE  AD Interrupt Enable     */
		Clr_Bit(ADCSRA_REG, 3);
	} else if (ADC_u8ISRSource == CHAIN_ASYNCH) {
#if ( ADJUST == RIGHT )
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ADC_REG;
#elif ( ADJUST == LEFT )
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ADCH_REG;
#endif
		/*Increment The Chain Index*/
		ADC_u8ChainConversionIndex++;

		/*Check Chain is finished or not*/
		if (ADC_u8ChainConversionIndex == ADC_u8ChainSize) {
			/*Chain is finished*/
			/*ADC is Now IDLE*/
			ADC_u18BusyFlag = IDLE;
			/*Call Back NOTIFICATION FUNC*/
			Global_PF_Vector_16();
			/*     Disable ADIE  AD Interrupt Enable     */
			Clr_Bit(ADCSRA_REG, 3);
		} else {
			/*Chain is not finished*/
			/*Set new required channel*/
			ADMUX_REG &= 0b11100000;
			ADMUX_REG |= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];
			/*Start Conversion*/
			Set_Bit(ADCSRA_REG, 6);
		}
	}
}
