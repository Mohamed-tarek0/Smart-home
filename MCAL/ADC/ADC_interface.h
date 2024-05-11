

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define     ADC0                    0
#define     ADC1                    1
#define     ADC2                    2
#define     ADC3                    3
#define     ADC4                    4
#define     ADC5                    5
#define     ADC6                    6
#define     ADC7                    7

typedef struct{
	u8* Channel;
	u16* Result;
	u8     Size;
    void(*NotificationFunc)(void);
}Chain_t;

void ADC_voidInit (void);

u16 ADC_u16ReadSynchronus ( u8 Copy_u8ChannelNumber ) ;

u16 ADC_u16ReadASynchronus(u8 Copy_u8ChannelNumber, u8 * Copy_pu8Reading,void (*Local_PvoidCallBackFunctionPtr)(void));

u8 ADC_u8ReadChainAsynchronus(Chain_t*Copy_Chain);

#endif
