/*
 * GSM_LIBRARY.h
 *
 * Created: 25/03/2018 19:43:26
 *  Author: Oki
 */ 
#include "_uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <string.h>

#define F_CPU 16000000UL
bool Get_AT_Response(const char * response)
{
	if (strstr_P(uart_0_buffer, response)) //If string is found, would return pointer value so becomes true
	return 1;
	else
	return 0;
}
/*											TCP-IP COMMANDS 																	*/
void Put_AT_CIPSHUT(void)
{
		uart_0_clear_buffer();
		uart_0_write("AT+CIPSHUT");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void PUT_AT_CIPMODE(void)
{
	uart_0_clear_buffer();
	uart_0_write("AT+CIPMODE=1");
	uart_0_print_char(13);
	uart_0_write("\n");
}
void Put_AT_CIPMUX(void)
{
		uart_0_clear_buffer();
		uart_0_write("AT+CIPMUX=0");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void PUT_AT_CIPMUX_MULTI(void)
{
	uart_0_clear_buffer();
	uart_0_write("AT+CIPMUX=1");
	uart_0_print_char(13);
	uart_0_write("\n");
}
void Put_AT_CGATT(void)
{
		uart_0_clear_buffer();
		uart_0_write("AT+CGATT=1");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void PUT_ATT_HTPPINIT()
{
	uart_0_clear_buffer();
	uart_0_write("AT+HTTPINIT");
	uart_0_print_char(13);
	uart_0_write("\n");
}
void PUT_ATT_HTTPARA()
{

	uart_0_clear_buffer();
	uart_0_write("AT+HTTPPARA=");
	uart_0_print_char(34);
	uart_0_write("CID");
	uart_0_print_char(34);
	uart_0_print_char(44);
	uart_0_write("1");
	uart_0_print_char(13);
	uart_0_write("\n");
}

void Put_AT_CSTT(char *APN, char *userName, char *password)
{
		uart_0_clear_buffer();
		uart_0_write("AT+CSTT=");
		uart_0_print_char(34);  //QUOTATION MARK "
		uart_0_write(APN);
		uart_0_print_char(34);// QUOTATION MARK  "
		uart_0_print_char(44);  //comma ,
		uart_0_print_char(34);// QUOTATION MARK  "
		uart_0_write(userName);
		uart_0_print_char(34);  // quotation mark "
		uart_0_print_char(44);  //comma ,
		uart_0_print_char(34);  // quotation mark "
		uart_0_write(password);
		uart_0_print_char(34);  // quotation mark "
		uart_0_print_char(13);  // carriage return
		uart_0_write("\n");
}
void Put_AT_CIICR(void)
{
		uart_0_clear_buffer();
		uart_0_write("AT+CIICR");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void Put_AT_CIPSTART(char *IP_ADDRESS, char *PORT_NUMBER)
{
		uart_0_clear_buffer();
		uart_0_write("AT+CIPSTART=");
		uart_0_print_char(34); //quotation mark "
		uart_0_write("TCP");
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44); // ,
		uart_0_print_char(34);  //"
		uart_0_write(IP_ADDRESS);
		uart_0_print_char(34); //"
		uart_0_print_char(44); // ,
		uart_0_print_char(34);
		uart_0_write(PORT_NUMBER);
		uart_0_print_char(34);
		uart_0_print_char(13); //cr
		uart_0_write("\n");
}
void PUT_AT_CIPSTART_MULTIPLE(int connection, char *IP_ADDRESS, char *PORT_NUMBER)
{
	switch(connection)
	{
		case(0):
		uart_0_clear_buffer();
		uart_0_write("AT+CIPSTART=0");
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write("TCP");
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write(IP_ADDRESS);
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write(PORT_NUMBER);
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(13); //cr
		uart_0_write("\n");
		break;
		case(1):
		uart_0_clear_buffer();
		uart_0_write("AT+CIPSTART=1");
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write("TCP");
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write(IP_ADDRESS);
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write(PORT_NUMBER);
		uart_0_print_char(34);//quotation mark
		uart_0_print_char(13); //cr
		uart_0_write("\n");
		break;
		case(2):
		uart_0_clear_buffer();
		uart_0_write("AT+CIPSTART=2");
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write("TCP");
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write(IP_ADDRESS);
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44);  //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write(PORT_NUMBER);
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(13);
		uart_0_write("\n");
		break;
		case(3):
		uart_0_clear_buffer();
		uart_0_write("AT+CIPSTART=3");
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_write("TCP");
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write(IP_ADDRESS):
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(44); //comma
		uart_0_print_char(34); //quotation mark
		uart_0_write(PORT_NUMBER);
		uart_0_print_char(34); //quotation mark
		uart_0_print_char(13);
		uart_0_write("\n"):
		break;
		case(4):
		uart_0_clear_buffer();
		uart_0_write("AT+CIPSTART=4");
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_write("TCP");
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_0_write(IP_ADDRESS):
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_0_write(PORT_NUMBER);
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(13);
                uart_0_write("\n"):
                break;
		case(5):
                uart_0_clear_buffer();
                uart_0_write("AT+CIPSTART=5");
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_write("TCP");
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_0_write(IP_ADDRESS):
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_0_write(PORT_NUMBER);
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(13);
                uart_0_write("\n"):
                break;
		case(6):
                uart_0_clear_buffer();
                uart_0_write("AT+CIPSTART=6");
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_write("TCP");
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_0_write(IP_ADDRESS):
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_0_write(PORT_NUMBER);
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(13);
                uart_0_write("\n"):
                break;
                case(7):
                uart_0_clear_buffer();
                uart_0_write("AT+CIPSTART=7");
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_write("TCP");
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_0_write(IP_ADDRESS):
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(44); //comma
                uart_0_print_char(34); //quotation mark
                uart_0_write(PORT_NUMBER);
                uart_0_print_char(34); //quotation mark
                uart_0_print_char(13);
                uart_0_write("\n"):
                break;


	}
}
void PUT_AT_CIPEND_MULTI(int connection)
{
	switch(connection)
		{
		case(0):
                   uart_0_clear_buffer();
		   uart_0_write("AT+CIPSEND=0");
		   uart_0_print_char(13);
		   uart_0_write("\n");
		break;
		case(1):
		  uart_0_clear_buffer();
		  uart_0_write("AT+CIPSEND=1");
		  uart_0_print_char(13);
		  uart_0_write("\n"):
		break;
		case(2):
		  uart_0_clear_buffer();
		  uart_0_write("AT+CIPSEND=2");
		  uart_0_print_char(13);
		  uart_0_write("\n"):
		break;
		case(3):
		  uart_0_clear_buffer();
		  uart_0_write("AT+CIPSEND=3");
		  uart_0_print_char(13);
		  uart_0_write("\n"):
		break;
		case(4):
		  uart_0_clear_buffer();
		  uart_0_write("AT+CIPSEND=4");
		  uart_0_print_char(13);
		  uart_0_write("\n"):
		break;
		case(5):
		  uart_0_clear_buffer();
		  uart_0_write("AT+CIPSEND=5");
		  uart_0_print_char(13);
		  uart_0_write("\n"):
		break;
		case(6):
		  uart_0_clear_buffer();
		  uart_0_write("AT+CIPSEND=6");
		  uart_0_print_char(13);
		  uart_0_write("\n"):
		break;
		case(7):
		  uart_0_clear_buffer();
		  uart_0_write("AT+CIPSEND=7");
		  uart_0_print_char(13);
		  uart_0_write("\n"):
		break;
		}
}
void Put_AT_CIPSEND(void)
{
		uart_0_clear_buffer();
		uart_0_write("AT+CIPSEND");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void PUT_AT_CIFSR(void)
{
	uart_0_clear_buffer();
	uart_0_write("AT+CIFSR");
	uart_0_print_char(13);
	uart_0_write("\n");
}
void Send_Data_TCP_IP( int position, char *data)
{
	if(position == 0)
	{
		Put_AT_CIPSEND();
	}
	if(position ==1 )
	{
		uart_0_write(data);
		uart_0_print_char(26);
	}		
}
void Return_AT_Mode(void)
{
	uart_0_write("+++");
	uart_0_print_char(13);
	uart_0_write("\n");
	
}
/*********************************************************************************************************************************************/


											