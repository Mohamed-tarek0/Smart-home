
#include<util/delay.h>

#include"Std_Types.h"
#include"Bit_Math.h"

#include"DIO_interface.h"
#include"PORT_interface.h"
#include"GIE_interface.h"
#include"ADC_interface.h"
#include"TIMER_interface.h"
#include"USART_interface.h"

void ADCNotification(void);
/****************************************************************************************************************************************/
/*******************************************************Global variable declartion*******************************************************/
/****************************************************************************************************************************************/
u16 Local_u16Iterator;
u8 Local_u8ADCReading;
u8 Local_u8ADC1Reading;
u8 Local_u8Key;
u8 Arr[4];
u8 Man;
u8 key;
u8 Temp;
u8 mV;
/********************************************************************************************************************************************/
/****************************************Struct of 10 users from which the user will choose**************************************************/
/********************************************************************************************************************************************/
/************************************************Every user has its own password*************************************************************/
/********************************************************************************************************************************************/
typedef struct {
	/*Passwords:
	 * user0 :0000
	 * user1 :1111
	 * user2 :2222
	 * user3 :3333
	 * user4 :4444
	 * user5 :5555
	 * user6 :6666
	 * user7 :7777
	 * user8 :8888
	 * user9 :9999
	 */
	u16 user1[4];
	u16 user2[4];
	u16 user3[4];
	u16 user4[4];
	u16 user5[4];
	u16 user6[4];
	u16 user7[4];
	u16 user8[4];
	u16 user9[4];
	u16 user0[4];
} users;
users * ptr;
void main(void) {
	PORT_voidInit();                                    /*****Initialize the direction of pins******/
	GIE_voidEnable();                                         /****Enable Global interrupt****/
	USART_INIT();                                              /***Enable Recive and send***/
	ADC_voidInit();                                             /**Enable ADC perephiral**/
	TIMER1_voidInit();
	Timer1_voidSetICR(20000);
	USART_voidSendString("Welcome\t");
	USART_voidSendString("Please select a user: \t");
	USART_voidSendString("USER0\t");
	USART_voidSendString("USER1\t");
	USART_voidSendString("USER2\t");
	USART_voidSendString("USER3\t");
	USART_voidSendString("USER4\t");
	USART_voidSendString("USER5\t");
	USART_voidSendString("USER6\t");
	USART_voidSendString("USER7\t");
	USART_voidSendString("USER8\t");
	USART_voidSendString("USER9\t");
/********************************************************************************************************************************************/
/**************************************************************user selection****************************************************************/
/********************************************************************************************************************************************/
	key = USART_u8Recive();
	switch (key) {
	case '0':
		ptr->user0;                                                  //Pointer points to the selected user
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {			                     // for loop to loop on the password 3 times
			for (u8 i = 0; i < 4; i++) {
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '0' && Arr[1] == '0' && Arr[2] == '0'
					&& Arr[3] == '0') {                              //Password check
				break;                                               //if password is right break the loop
			} else if (j != 2) {
                                                                     //else if the password is not right the user will be given another two trials
			} else {                                                 //the user entered the password wrong 3 times in a row
				while (1) {                                          //the code will be stuck in a while loop and alarm will turn on
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '1':                                                        //Pointer points to the selected user
		ptr->user1;
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {                                 // for loop to loop on the password 3 times
			for (u8 i = 0; i < 4; i++) {
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '1' && Arr[1] == '1' && Arr[2] == '1'
					&& Arr[3] == '1') {                              //Password check
				break;                                               //if password is right break the loop
			} else if (j != 2) {
                                                                     //else if the password is not right the user will be given another two trials
			} else {                                                 //the user entered the password wrong 3 times in a row
				while (1) {                                          //the code will be stuck in a while loop and alarm will turn on
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '2':                                                        //Pointer points to the selected user
		ptr->user2;
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {                                 // for loop to loop on the password 3 times
			for (u8 i = 0; i < 4; i++) {
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '2' && Arr[1] == '2' && Arr[2] == '2'
					&& Arr[3] == '2') {                              //Password check
				break;                                               //if password is right break the loop
			} else if (j != 2) {
                                                                     //else if the password is not right the user will be given another two trials
			} else {                                                 //the user entered the password wrong 3 times in a row
				while (1) {                                          //the code will be stuck in a while loop and alarm will turn on
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '3':
		ptr->user3;                                                  //Pointer points to the selected user
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {
			for (u8 i = 0; i < 4; i++) {                             // for loop to loop on the password 3 times
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '3' && Arr[1] == '3' && Arr[2] == '3'
					&& Arr[3] == '3') {
				break;                                               //Password check
			} else if (j != 2) {                                     //if password is right break the loop

			} else {                                                 //else if the password is not right the user will be given another two trials
				while (1) {                                          //the user entered the password wrong 3 times in a row
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,       //the code will be stuck in a while loop and alarm will turn on
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '4':
		ptr->user4;                                                  //Pointer points to the selected user
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {
			for (u8 i = 0; i < 4; i++) {                             // for loop to loop on the password 3 times
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '4' && Arr[1] == '4' && Arr[2] == '4'
					&& Arr[3] == '4') {
				break;                                               //Password check
			} else if (j != 2) {                                     //if password is right break the loop

			} else {                                                 //else if the password is not right the user will be given another two trials
				while (1) {                                          //the user entered the password wrong 3 times in a row
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,       //the code will be stuck in a while loop and alarm will turn on
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '5':
		ptr->user5;                                                  //Pointer points to the selected user
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {
			for (u8 i = 0; i < 4; i++) {                             // for loop to loop on the password 3 times
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '5' && Arr[1] == '5' && Arr[2] == '5'
					&& Arr[3] == '5') {
				break;                                               //Password check
			} else if (j != 2) {                                     //if password is right break the loop

			} else {                                                 //else if the password is not right the user will be given another two trials
				while (1) {                                          //the user entered the password wrong 3 times in a row
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,       //the code will be stuck in a while loop and alarm will turn on
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '6':                                                         //Pointer points to the selected user
		ptr->user6;
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {                                  // for loop to loop on the password 3 times
			for (u8 i = 0; i < 4; i++) {
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '6' && Arr[1] == '6' && Arr[2] == '6'
					&& Arr[3] == '6') {                               //Password check
				break;                                                //if password is right break the loop
			} else if (j != 2) {
                                                                      //else if the password is not right the user will be given another two trials
			} else {                                                  //the user entered the password wrong 3 times in a row
				while (1) {                                           //the code will be stuck in a while loop and alarm will turn on
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '7':                                                          //Pointer points to the selected user
		ptr->user7;
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {                                   // for loop to loop on the password 3 times
			for (u8 i = 0; i < 4; i++) {
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '7' && Arr[1] == '7' && Arr[2] == '7'
					&& Arr[3] == '7') {                                //Password check
				break;                                                 //if password is right break the loop
			} else if (j != 2) {
                                                                       //else if the password is not right the user will be given another two trials
			} else {                                                   //the user entered the password wrong 3 times in a row
				while (1) {                                            //the code will be stuck in a while loop and alarm will turn on
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '8':
		ptr->user8;                                                   //Pointer points to the selected user
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {
			for (u8 i = 0; i < 4; i++) {                              // for loop to loop on the password 3 times
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '8' && Arr[1] == '8' && Arr[2] == '8'
					&& Arr[3] == '8') {
				break;                                                //Password check
			} else if (j != 2) {                                      //if password is right break the loop

			} else {                                                  //else if the password is not right the user will be given another two trials
				while (1) {                                           //the user entered the password wrong 3 times in a row
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,        //the code will be stuck in a while loop and alarm will turn on
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;
	case '9':
		ptr->user9;                                                   //Pointer points to the selected user
		USART_voidSendString("Please enter password\t");
		for (u8 j = 0; j < 4; j++) {
			for (u8 i = 0; i < 4; i++) {                              // for loop to loop on the password 3 times
				Local_u8Key = USART_u8Recive();
				Arr[i] = Local_u8Key;
			}
			if (Arr[0] == '9' && Arr[1] == '9' && Arr[2] == '9'
					&& Arr[3] == '9') {
				break;                                                //Password check
			} else if (j != 2) {                                      //if password is right break the loop

			} else {                                                  //else if the password is not right the user will be given another two trials
				while (1) {                                           //the user entered the password wrong 3 times in a row
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,        //the code will be stuck in a while loop and alarm will turn on
					DIO_u8PIN_HIGH);
					_delay_ms(50);
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN7,
					DIO_u8PIN_LOW);
					_delay_ms(50);
				}
			}
		}
		break;

	default:
		break;
	}
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************Interface configurations************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
	USART_voidSendString("Open Door\t");

	USART_voidSendString("Close Door\t");

	USART_voidSendString("Open Lights\t");

	USART_voidSendString("Close Lights\t");

	USART_voidSendString("Open Ac\t");

	USART_voidSendString("Close AC\t");

	USART_voidSendString("Adjust Lights\t");

	USART_voidSendString("Adjust Temp\t");
	while (1) {
		/* Configurations Check:
		 * {
		 * 1 - Open Door
		 * 2 - Close Door
		 * 3 - Open Lights
		 * 4 - Close Lights
		 * 5 - Open Ac
		 * 6 - Close Ac
		 * 7 - Adjust Lights
		 * 8 - Adjust Temp
		 * }
		 */

		Man = USART_u8Recive();
		switch (Man) {
		case '1':
			/*Open door*/
				Timer1_voidSetChannelACompMatch(750);
			break;
		case '2':
			/*Close door*/
				Timer1_voidSetChannelACompMatch(2500);
			break;
		case '3':
			/*Turn all 8 Leds on*/
			DIO_u8SetPORTValue(DIO_u8PORTC, DIO_u8PORT_HIGH);
			break;
		case '4':
			/*Turn all 8 Leds off*/
			DIO_u8SetPORTValue(DIO_u8PORTC, DIO_u8PORT_LOW);
			break;
		case '5':
			/*Turn DC Motor On*/
			DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PIN_HIGH);
			break;
		case '6':
			/*Turn DC Motor Off*/
			DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PIN_LOW);
			break;

		case '7':
			/*Read From LDR To Pin ADC0 and adjust lights acording to this reading*/
			ADC_u16ReadASynchronus(ADC0, &Local_u8ADCReading, ADCNotification);
			break;
		case '8':
			/*Read From LM35 To Pin ADC1 and adjust TEMP acording to this reading*/
			Local_u8ADC1Reading = ADC_u16ReadSynchronus(ADC1);
			mV = (u16) ((u32) Local_u8ADC1Reading * 5000UL) / 256UL;
			Temp = mV / 10;
			if (Temp >= 0) {
				DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN2,
				DIO_u8PIN_HIGH);
			} else {
				DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN2,
				DIO_u8PIN_LOW);
				break;
			}
			break;
		default:
			break;
		}
	}
}
void ADCNotification(void) {

	DIO_u8SetPORTValue(DIO_u8PORTC, Local_u8ADCReading);

}
