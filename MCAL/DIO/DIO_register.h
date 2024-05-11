
#ifndef DIO_REGISTER_H_
#define DIO_REGISTER_H_

#define PORTA     *((volatile u8*)0x3b)
#define PORTB     *((volatile u8*)0x38)
#define PORTC     *((volatile u8*)0x35)
#define PORTD     *((volatile u8*)0x32)
#define PINA      *((volatile u8*)0x39)
#define PINB      *((volatile u8*)0x36)
#define PINC      *((volatile u8*)0x33)
#define PIND      *((volatile u8*)0x30)

#endif /* DIO_REGISTER_H_ */
