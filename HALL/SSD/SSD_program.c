
#include"Std_Types_Moamen.h"
#include"Bit_Math_Moamen.h"
#include"SSD_interface.h"
#include"DIO_interface.h"

u8 Common_Anode_Arr[16]=
        {0b11000000
		,0b11111001
		,0b10100100
		,0b10110000
		,0b10011001
		,0b10010010
		,0b10000010
		,0b11111000
		,0b10000000
		,0b10010000
		,0b10001000
		,0b10000000
		,0b11000110
		,0b11000000
		,0b10000110
		,0b10001110};

void SEGMENT_voidPrintNumber ( u8 Copy_u8PortNumber , u8 Copy_SegmentPolarity , u8 Copy_u8Number )
{
    switch ( Copy_SegmentPolarity )
    {
        case ANODE   :   switch(Copy_u8PortNumber)
                                {
                                    case DIO_u8PORTA :   DIO_u8SetPORTValue(DIO_u8PORTA,Common_Anode_Arr[Copy_u8Number]);    break;
                                    case DIO_u8PORTB :   DIO_u8SetPORTValue(DIO_u8PORTB,Common_Anode_Arr[Copy_u8Number]);    break;
                                    case DIO_u8PORTC :   DIO_u8SetPORTValue(DIO_u8PORTC,Common_Anode_Arr[Copy_u8Number]);    break;
                                    case DIO_u8PORTD :   DIO_u8SetPORTValue(DIO_u8PORTD,Common_Anode_Arr[Copy_u8Number]);    break;
                                    default    :                                                                    break;
                                }
                                break;
        case CATHODE :   switch(Copy_u8PortNumber)
                                {
                                    case DIO_u8PORTA :   DIO_u8SetPORTValue(DIO_u8PORTA,~Common_Anode_Arr[Copy_u8Number]);    break;
                                    case DIO_u8PORTB :   DIO_u8SetPORTValue(DIO_u8PORTB,~Common_Anode_Arr[Copy_u8Number]);    break;
                                    case DIO_u8PORTC :   DIO_u8SetPORTValue(DIO_u8PORTC,~Common_Anode_Arr[Copy_u8Number]);    break;
                                    case DIO_u8PORTD :   DIO_u8SetPORTValue(DIO_u8PORTD,~Common_Anode_Arr[Copy_u8Number]);    break;
                                    default    :                                                                    break;
                                }   
                                break;
        default             :   break;
    }
    
}
