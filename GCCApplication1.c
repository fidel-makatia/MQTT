/*
 * GccApplication1.c
 *
 * Created: 25/03/2018 19:43:26
 *  Author: Oki
 */ 


#include <avr/io.h>
#include "mqtt.h"
#include "_uart.h"
#include "GSM_LIBRARY.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
uint8_t encodedbyte;
uint8_t mqtt_message[127];
int mqttMessageLength = 0;
int SetupComplete;
int sendDataComplete; 
int data_is_sending=1;
int dataTransfer = 1;
int setup_Position;
int sendDataPosition;
int connectServerComplete;
int connectingServer=1;
int serverConnectPosition;
int uart_counter=0;
int uart_counter2;
int counter_1=0;
int counter_2=0;
int counter_K=0;
int Retry_1;
int Retry_2;
int Retry_3;
void Set_Up_Connection(char *APN, char *userName, char *password, char *serverIPAddress, char *PortNumber);
char Response[10];
char Response2[10];
char Response3[10];
const char MQTTClientID[20]="Mala";
const char MQTTTopic[30]="Burukenge";
const char MQTTProtocolName[10]="MQIsdp";
const char MQTTLVL = 0x03;
const char MQTTFlags = 0xC2;
const unsigned int MQTTKeepAlive=60;
const char MQTTUsername[30]="fyixwgqw";
const char MQTTPassword[35]="gxkSJ6W-4qdd";
const char MQTTQOS = 0x00;
const char MQTTPacketID = 0x0001;
int MQTTProtocolNameLength;
int MQTTClientIDLength;
int MQTTUsernameLength;
int MQTTPasswordLength;
int datalength;
int X;
int topicLength;
unsigned int Counter;
char str[250];
unsigned char topic[30];

#define F_CPU 16000000UL
int main(void)
{
	uart_0_init(38400);
	//uart_2_init(38400);
	//uart_3_init(115200);
	 TCCR1A = 0;
	 TCCR1B = 0;
     TCCR1B |= (5<<CS10);
	 TIMSK1 |= 1<<TOIE1;
	 TCNT1 = 49911; 
	 TCCR3A = 0;
	 TCCR3B = 0;
	 TCCR3B |= (5<<CS30);
	 TIMSK3 |= 1<<TOIE3;
	 TCNT3 = 49911;
	 
	 TCCR5A = 0;
	 TCCR5B = 0;
     TCCR5B |= (5<<CS50);
	 TIMSK5 |= 1<<TOIE5;
	 TCNT5 = 49911;
	sei();
	
    while(1)
    {
	
			sendDataComplete = 0;
			if(!SetupComplete)
			{
			
				Set_Up_Connection("safaricom","saf","data","m11.cloudmqtt.com","19781");
				if(Retry_1 == 10)
				{
					
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
			else if(!connectingServer)
			{
				connectMqqt();
				if(Retry_3 == 10)
				{
					serverConnectPosition=0;
					connectingServer=1;
					Retry_3=0;
				}
				else if(strstr(uart_0_buffer,Response3))
				{
					Retry_3=0;
					uart_0_clear_buffer();
					serverConnectPosition++;
					connectingServer=1;
					
				}
			}
			else if(!sendDataComplete)
			{
				Send_Data();
				if(Retry_2 == 10)
				{
					sendDataPosition=0;
					dataTransfer=1;
					Retry_2=0;
				}
				else if(strstr(uart_0_buffer,Response2))
				{
					Retry_2=0;
					uart_0_clear_buffer();
					sendDataPosition++;
					dataTransfer=1;
				}
			}
	}				  
}
ISR(TIMER1_OVF_vect)
{
	TCNT1 = 49911;
	counter_K++;
}
ISR(TIMER3_OVF_vect)
{
	TCNT3 = 49911;
	counter_1++;
	uart_counter++;
	uart_counter2++;
	if(uart_counter == 3)
	{
		Retry_1++;
		data_is_sending =1;
	}
	if(uart_counter2 == 3)
	{
		Retry_2++;
		dataTransfer = 1;
	}
	if(counter_1==3)
	{
		Retry_3++;
		connectingServer=1;
	}
}
ISR(TIMER5_OVF_vect)
{
	TCNT5 = 49911;
	uart_counter2++;
	if(uart_counter2 == 2)
	{
		dataTransfer = 1;
	}
	
}
ISR(USART0_RX_vect)
{
	uart_0_read();
	//uart_0_write("inu\n");
}
/*void Set_Up_Connection(char *APN, char *userName, char *password, char *serverIPAddress, char *PortNumber)
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
}*/
void connectMqqt(void)
{	
	MQTTProtocolNameLength=strlen(MQTTProtocolName);
	MQTTClientIDLength=strlen(MQTTClientID);
	MQTTUsernameLength=strlen(MQTTUsername);
	MQTTPasswordLength=strlen(MQTTPassword);
	datalength=MQTTProtocolNameLength+2+4+MQTTClientIDLength+2+MQTTUsernameLength+2+MQTTPasswordLength;
	X=datalength;
	
	
	if(connectingServer==1)
	{
		counter_1=0;
		connectingServer=0;
		if(serverConnectPosition==0)
		{
			Put_AT_CIPSEND();
			strcpy(Response3,">");
			
		}
		if(serverConnectPosition==1)
		{
			
			do
			{
				encodedbyte = X%128;
				X=X/128;
				if(X>0)(encodedbyte |= 128 );
				uart_0_write_byte(encodedbyte);
			}
			while(X>0);
			uart_0_write_byte(MQTTProtocolNameLength >> 8);
			uart_0_write_byte(MQTTProtocolNameLength & 0xFF);
			uart_0_write(MQTTProtocolName);
			
			uart_0_write_byte(MQTTLVL);
			uart_0_write_byte(MQTTFlags);
			uart_0_write_byte(MQTTKeepAlive >> 8);
			uart_0_write_byte(MQTTKeepAlive & 0xFF);
			
			uart_0_write_byte(MQTTClientIDLength >> 8);
			uart_0_write_byte(MQTTClientIDLength & 0xFF);
			uart_0_write(MQTTClientID);
			
			uart_0_write_byte(MQTTUsernameLength >> 8);
			uart_0_write_byte(MQTTUsernameLength & 0xFF);
			uart_0_write(MQTTUsername);
			
			uart_0_write_byte(MQTTPasswordLength >> 8);
			uart_0_write_byte(MQTTPasswordLength & 0xFF);
			uart_0_write(MQTTPassword);
			
			uart_0_print_char(26);
			strcpy(Response3,"SEND OK");
			
		}
		if(serverConnectPosition==2)
		{
			uart_0_clear_buffer();
			connectServerComplete=1;
			serverConnectPosition=0;
		}
	}
}

void Send_Data(void)
{
	memset(str,0,250);
	topicLength = sprintf((char*)topic,MQTTTopic);
	datalength = sprintf((char*)str,"%s%u",topic,Counter);
	if(dataTransfer==1)
	{
		dataTransfer=0;
		uart_counter2 = 0;
		if(sendDataPosition == 0)
		{
			Put_AT_CIPSEND();
			strcpy(Response2,">");
			
		}
		if(sendDataPosition == 1)
		{
			
			X=datalength+2;
			do
			{
				encodedbyte = X%128;
				X=X/128;
				if(X>0)(encodedbyte |= 128);
				uart_0_write_byte(encodedbyte);
			}
			while(X>0);
			uart_0_write_byte(topicLength >> 8);
			uart_0_write_byte(topicLength & 0xFF);
			uart_0_write(str);
			uart_0_print_char(26);
			/*uart_0_write_byte(0x30);
			uart_0_write_byte(0x13);
			uart_0_write_byte(0x00);
			uart_0_write_byte(0x08);
			uart_0_write_byte(0x76);
			uart_0_write_byte(0x61);
			uart_0_write_byte(0x6C);
			uart_0_write_byte(0x65);
			uart_0_write_byte(0x74);
			uart_0_write_byte(0x72);
			uart_0_write_byte(0x6F);
			uart_0_write_byte(0x6E);
			uart_0_write_byte(0x00);*/
			strcpy(Response2,"SEND OK");
		}
		
		if(sendDataPosition==2)
		{
			uart_0_clear_buffer();
			sendDataComplete=1;
			//SetupComplete=0;
			sendDataPosition=0;
		}
	}
}