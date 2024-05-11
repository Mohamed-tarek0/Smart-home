

#include"Std_Types.h"
#include"Bit_Math.h"
#include"DIO_register.h"
#include"DIO_interface.h"
#define NULL 0
u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
	u8 Local_u8ErrorState=0;
	if(Copy_u8Pin<=DIO_u8PIN7)
	{
		if(Copy_u8Direction==DIO_u8PIN_LOW)
		{
			switch(Copy_u8Port){
			case DIO_u8PORTA:Clr_Bit(PORTA,Copy_u8Pin); break;
			case DIO_u8PORTB:Clr_Bit(PORTB,Copy_u8Pin); break;
			case DIO_u8PORTC:Clr_Bit(PORTC,Copy_u8Pin); break;
			case DIO_u8PORTD:Clr_Bit(PORTD,Copy_u8Pin); break;
			default: Local_u8ErrorState=1;break;
			}
		}
		else if(Copy_u8Direction==DIO_u8PIN_HIGH)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA:Set_Bit(PORTA,Copy_u8Pin); break;
			case DIO_u8PORTB:Set_Bit(PORTB,Copy_u8Pin); break;
			case DIO_u8PORTC:Set_Bit(PORTC,Copy_u8Pin); break;
			case DIO_u8PORTD:Set_Bit(PORTD,Copy_u8Pin); break;
			default: Local_u8ErrorState=1;break;
			}
		}
		else
			Local_u8ErrorState=1;
	}
	else
	{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;
}

u8 DIO_u8SetPORTValue(u8 Copy_u8Port, u8 Copy_u8Direction)
{
	u8 Local_u8ErrorState=0;
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA:PORTA = Copy_u8Direction;break;
	case DIO_u8PORTB:PORTB = Copy_u8Direction;break;
	case DIO_u8PORTC:PORTC = Copy_u8Direction;break;
	case DIO_u8PORTD:PORTD = Copy_u8Direction;break;
	default:Local_u8ErrorState=1;
	}

	return Local_u8ErrorState;
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8*Copy_pu8Value)
{
	u8 Local_u8ErrorState=0;

	if ((*Copy_pu8Value!=NULL) && (Copy_u8Pin<=DIO_u8PIN7))
	{
		switch(Copy_u8Port){
		case DIO_u8PORTA : *Copy_pu8Value = Get_Bit(PINA,Copy_u8Pin);break;
		case DIO_u8PORTB : *Copy_pu8Value = Get_Bit(PINB,Copy_u8Pin);break;
		case DIO_u8PORTC : *Copy_pu8Value = Get_Bit(PINC,Copy_u8Pin);break;
		case DIO_u8PORTD : *Copy_pu8Value = Get_Bit(PIND,Copy_u8Pin);break;
		default: Local_u8ErrorState=1;
		}
	}
	else
	{
		Local_u8ErrorState=1;
	}

	return Local_u8ErrorState;
}
u8 DIO_u8Get_PinValue (u8 Copy_u8PortNumber, u8 Copy_u8PinNumber )
{
    u8 Local_u8Variable;
    /* i/p validation */
    if ( Copy_u8PortNumber > PORTD || Copy_u8PinNumber > DIO_u8PIN7 )
    {
        // Do Nothing
    }
    else
    {
        switch(Copy_u8PortNumber)
        {
            case DIO_u8PORTA :    Local_u8Variable = Get_Bit( PINA ,Copy_u8PinNumber );   break;
            case DIO_u8PORTB :    Local_u8Variable = Get_Bit( PINB ,Copy_u8PinNumber );   break;
            case DIO_u8PORTC :    Local_u8Variable = Get_Bit( PINC ,Copy_u8PinNumber );   break;
            case DIO_u8PORTD :    Local_u8Variable = Get_Bit( PIND ,Copy_u8PinNumber );   break;
            default :                                                                   break;
        }
    }
    return Local_u8Variable ;
}


