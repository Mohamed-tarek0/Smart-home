

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX_REG               *((volatile u8*)0x27)         // ADC multplexer selection register
                                                         
                                                         
#define ADCSRA_REG              *((volatile u8*)0x26)         //ADC control and status register
                                                         
                                                         
#define ADCH_REG                *((volatile u8*)0x25)        //ADC high register


#define ADCL_REG                *((volatile u8*)0x24)        //ADC Low register
#define ADC_REG                 *((volatile u16*)0x24)       // Pointer to 16 bit ADCH and ADCL to read Data From 10 BIT of ADC Data.

#define SFIOR_REG               *((volatile u8*)0x50)


#endif
