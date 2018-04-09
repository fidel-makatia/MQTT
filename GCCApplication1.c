/*
 * GccApplication1.c
 *
 * Created: 25/03/2018 19:43:26
 *  Author: Oki
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "Timer.h"
#include "mqtt.h"
#include "_uart.h"
#include "GSM_LIBRARY.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
uint8_t mqtt_message[127];
int SetupComplete;
int sendDataComplete; 
int data_is_sending=1;
int dataTransfer = 1;
int setup_Position;
int sendDataPosition;
int connectServerComplete=0;
int connectingServer=1;
int serverConnectPosition=0;
int uart_counter=0;
int uart_counter2;
int counter_1=0;
int counter_2=0;
int counter_K=0;
int counter_subscribe=0;
int Retry_1;
int Retry_2;
int Retry_3;
void Set_Up_Connection(char *APN, char *userName, char *password, char *serverIPAddress, char *PortNumber);
char Response[10];
char Response2[10];
char Response3[10];
unsigned long datalength,checksum,rlength;
unsigned short topicLength;
unsigned short topicLength2;
unsigned short MQTTProtocolNameLength;
unsigned short MQTTClientIDLength;
unsigned short MQTTUsernameLength;
unsigned short MQTTPasswordLength;
unsigned short MQTTTopicLength;
const char *MQTTClientID = "BURUKENGE";
const char *MQTTTopic= "sambul_1";
const char *MQTTTopic2= "sambul_2";
const char *MQTTProtocolName = "MQIsdp";
const char MQTTLVL = 0x03;
const char MQTTFlags = 0xC2;
const unsigned int MQTTKeepAlive = 60;
const char *userName = "fyixwgqw";
const char *password = "gxkSJ6W-4qdd";
const char MQTTQOS = 0x00;
const char MQTTPacketID = 0x0001;
long X;
unsigned char encodedByte;
 int Counter=4;
char str[250];
unsigned char topic[30];

#define F_CPU 16000000UL
int main(void)
{
	uart_0_init(38400);

	 TCCR3A = 0;
	 TCCR3B = 0;
	 TCCR3B |= (5<<CS30);
	 TIMSK3 |= 1<<TOIE3;
	 TCNT3 = 49911;
	 
	sei();
	
    while(1)
    {
	
			sendDataComplete = 0;
			if(!SetupComplete)
			{
			
				//Set_Up_Connection("safaricom","saf","data","m11.cloudmqtt.com","19781");
				Set_Up_Connection("internet","","","m11.cloudmqtt.com","19781");
				
				if(Retry_1 == 10)
				{
					uart_0_clear_buffer();
					setup_Position=0;
					data_is_sending=1;
					Retry_1=0;
				}
			  else if(strstr(uart_0_buffer,Response)){
					//uart_0_write(uart_0_buffer);
					Retry_1=0;
					uart_0_clear_buffer();
					setup_Position++;
					data_is_sending=1;
				}
			}
			else if(!connectServerComplete)
			{
				connectMQTT();
			    if(strstr(uart_0_buffer,Response3))
				{
					Retry_3=0;
					uart_0_clear_buffer();
					serverConnectPosition++;
					//connectingServer=1;
					
				}
			}
			else if(!sendDataComplete)
			{
				publishMQTT();
				if(strstr(uart_0_buffer,Response2))
				{
					Retry_2=0;
					uart_0_clear_buffer();
					sendDataPosition++;
					//dataTransfer=1;
				}
			}
	}				  
}

ISR(TIMER3_OVF_vect)
{
	TCNT3 = 49911;
	counter_1++;
	uart_counter++;
	uart_counter2++;
	if(uart_counter == 2)
	{
		Retry_1++;
		data_is_sending =1;
	}
	if(uart_counter2 == 2)
	{
		Retry_2++;
		dataTransfer = 1;
	}
	if(counter_1==2)
	{
		Retry_3++;
		connectingServer=1;
	}
}
ISR(USART0_RX_vect)
{
	uart_0_read();
}
void publishMQTT(void)
{
	if(dataTransfer == 1)
	{
		dataTransfer=0;
		uart_counter2=0;
		if(sendDataPosition==0)
		{
			memset(str, 0, sizeof(str));
			topicLength = sprintf((char*)topic, MQTTTopic);
			datalength = sprintf((char*)str, "%s%s", topic, "Counter$$%%^&&&&**&^%$#");
			uart_0_write_byte(0x30);
			X = datalength + 2;
			do
			{
				encodedByte = X % 128;
				X = X / 128;
				// if there are more data to encode, set the top bit of this byte
				if ( X > 0 ) {
					encodedByte |= 128;
				}
				uart_0_write_byte(encodedByte);
			}
			while ( X > 0 );

			uart_0_write_byte(topicLength >> 8);
			uart_0_write_byte(topicLength & 0xFF);
			uart_0_write(str);
			uart_0_write("");
			strcpy(Response2,"SEND OK");
		}
			
		if(sendDataPosition == 1)
		{
			uart_0_clear_buffer();
			uart_0_print_char(26);
			sendDataPosition=0;
			dataTransfer=0;
			sendDataComplete=1;
		}
	}
	
}
void connectMQTT(void)
{

	if(connectingServer==1)
	{
		connectingServer=0;
		counter_1=0;
		if(serverConnectPosition==0)
		{
			Put_AT_CIPSEND();
			strcpy(Response3,">");
		}
		if(serverConnectPosition==1)
		{
			uart_0_clear_buffer();
			uart_0_write_byte(0x10);
			MQTTProtocolNameLength = strlen(MQTTProtocolName);
			MQTTClientIDLength = strlen(MQTTClientID);
			MQTTUsernameLength = strlen(userName);
			MQTTPasswordLength = strlen(password);
			datalength = MQTTProtocolNameLength + 2 + 4 + MQTTClientIDLength + 2 + MQTTUsernameLength + 2 + MQTTPasswordLength + 2;
			X = datalength;
			do
			{
				encodedByte = X % 128;
				X = X / 128;
				// if there are more data to encode, set the top bit of this byte
				if ( X > 0 ) {
					encodedByte |= 128;
				}

				uart_0_write_byte(encodedByte);
			}
			while ( X > 0 );
			uart_0_write_byte(MQTTProtocolNameLength >> 8);
			uart_0_write_byte(MQTTProtocolNameLength & 0xFF);
			uart_0_write(MQTTProtocolName);

			uart_0_write_byte(MQTTLVL); // LVL
			uart_0_write_byte(MQTTFlags); // Flags
			uart_0_write_byte(MQTTKeepAlive >> 8);
			uart_0_write_byte(MQTTKeepAlive & 0xFF);


			uart_0_write_byte(MQTTClientIDLength >> 8);
			uart_0_write_byte(MQTTClientIDLength & 0xFF);
			uart_0_write(MQTTClientID);


			uart_0_write_byte(MQTTUsernameLength >> 8);
			uart_0_write_byte(MQTTUsernameLength & 0xFF);
			uart_0_write(userName);
			uart_0_write_byte(MQTTPasswordLength >> 8);
			uart_0_write_byte(MQTTPasswordLength & 0xFF);
			uart_0_write(password);
			uart_0_write("\r");
			_delay_ms(1000);
			uart_0_print_char(26);
			strcpy(Response3,"SEND OK");
			
		}
		
		if(serverConnectPosition==2)
		{
			
			serverConnectPosition=0;
			connectServerComplete=1;
			connectingServer=0;
		}
	}
}
void Set_Up_Connection(char *APN, char *userName, char *password, char *serverIPAddress, char *PortNumber)
{
	if(data_is_sending==1)
	{
		data_is_sending = 0;
		uart_counter = 0;
		if(setup_Position == 0)
		{
			Put_AT_CIPSHUT();
			strcpy(Response,"OK");
			
		}

		if(setup_Position == 1)
		{
			Put_AT_CIPMUX();
			strcpy(Response,"OK");
		}
		if(setup_Position == 2)
		{
			Put_AT_CSTT(APN,userName,password);
			strcpy(Response,"OK");
		}
		if(setup_Position == 3)
		{
			Put_AT_CGATT();
			strcpy(Response,"OK");
		}
		if(setup_Position == 4)
		{
			Put_AT_CIICR();
			strcpy(Response,"OK");
		}
		if(setup_Position==5)
		{
			PUT_AT_CIFSR();
			strcpy(Response,".");
		}
		if(setup_Position == 6)
		{
			Put_AT_CIPSTART(serverIPAddress,PortNumber);
			strcpy(Response,"OK");
		}
		if(setup_Position ==7)
		{
			strcpy(Response,"OK");
		}
		if(setup_Position == 8)
		{
			uart_0_clear_buffer();
			setup_Position = 0;
			SetupComplete = 1;
			data_is_sending=0;
		}
	}
}
