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
		uart_0_write("AT+CIPSHUT");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void PUT_AT_CIPMODE(void)
{
	uart_0_write("AT+CIPMODE=1");
	uart_3_print_char(13);
	uart_0_write("\n");
}
void Put_AT_CIPMUX(void)
{
		uart_0_write("AT+CIPMUX=0");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void Put_AT_CGATT(void)
{
		uart_0_write("AT+CGATT=1");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void PUT_ATT_HTPPINIT()
{
	uart_0_write("AT+HTTPINIT");
	uart_0_print_char(13);
	uart_0_write("\n");
}
void PUT_ATT_HTTPARA()
{

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
		
		uart_0_write("AT+CIICR");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void Put_AT_CIPSTART(char *IP_ADDRESS, char *PORT_NUMBER)
{
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
void Put_AT_CIPSEND(void)
{
		uart_0_write("AT+CIPSEND");
		uart_0_print_char(13);
		uart_0_write("\n");
}
void PUT_AT_CIFSR(void)
{
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
/*********************************************************************************************************************************************/

/*									SMS COMMANDS	
											