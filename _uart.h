/*
 * _uart.h
 *
 * Created: 4/10/2017 08:58:56
 *  Author: Marley
 */


#ifndef _UART_H_
#define _UART_H_
#define F_CPU 16000000UL
#define uart_buffer_size 256

unsigned char uart_0_buffer[uart_buffer_size];
int buffer_position=0;

void set_baudrate(unsigned long baudrate){
	switch(F_CPU){
		case 8000000UL:
		switch(baudrate){
			case 9600:
			UBRR0L=51;
			UBRR0H=0;
			break;
			case 19200:
			UBRR0L=25;
			UBRR0H=0;
			break;
			case 38400:
            UBRR0L =12;
            UBRR0H=0;
            break;
			case 115200:
			UBRR0L=3;
			UBRR0H=0;
			break;
		}
		break;
		case 16000000UL:
		switch(baudrate){
			case 9600:
			UBRR0L=103;
			UBRR0H=0;
			break;
			case 19200:
			UBRR0L=51;
			UBRR0H=0;
			break;
			case 38400:
            UBRR0L =25;
            UBRR0H=0;
            break;
			case 115200:
			UBRR0L=8;
			UBRR0H=0;
			break;
		}
		break;
	}
}


void uart_0_init(unsigned long baudrate){
	UCSR0B |=(1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0C |=(1<<UCSZ00)|(1<<UCSZ01);
	set_baudrate(baudrate);
}
void uart_0_print_char(char ch){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = ch;
}
void uart_0_write_byte(uint8_t byte)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0=byte;
}
void uart_0_write(char * byte){
	for (;*byte;++byte) uart_0_print_char(*byte);

}

void send_UART_string_0(char * byte)
{
	for (;*byte;++byte) uart_0_print_char(*byte);

}

unsigned char uart_0_read_char(){
	unsigned char temp;
	temp=UDR0;
	return temp;
}

void uart_0_read(){
	//uart_0_print_char('p');
	uart_0_buffer[buffer_position]=uart_0_read_char();
	buffer_position++;
	if(buffer_position==256)buffer_position=0;
}

void uart_0_clear_buffer(void){
	int x;
	for(x=0; x<uart_buffer_size; x++)uart_0_buffer[x]=0x00; //initializing the data array to null
	buffer_position=0;
}


//UART 1 FUNCTIONS

char uart_1_buffer[uart_buffer_size];
int buffer_position_1=0;

void set_baudrate_1(unsigned long baudrate){
	switch(F_CPU){
		case 8000000UL:
		switch(baudrate){
			case 9600:
			UBRR1L=51;
			UBRR1H=0;
			break;
			case 19200:
			UBRR1L=25;
			UBRR1H=0;
			break;
			case 38400:
            UBRR1L =12;
            UBRR1H=0;
            break;
			case 115200:
			UBRR1L=3;
			UBRR1H=0;
			break;
		}
		break;
		case 16000000UL:
		switch(baudrate){
			case 9600:
			UBRR1L=103;
			UBRR1H=0;
			break;
			case 19200:
			UBRR1L=51;
			UBRR1H=0;
			break;
			case 38400:
            UBRR1L =25;
            UBRR1H=0;
            break;
			case 115200:
			UBRR1L=8;
			UBRR1H=0;
			break;
		}
		break;
	}
}


void uart_1_init(unsigned long baudrate){
	UCSR1B |=(1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
	UCSR1C |=(1<<UCSZ10)|(1<<UCSZ11);
	set_baudrate_1(baudrate);
}

void uart_1_print_char(char ch){
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = ch;
}

void uart_1_write(char * byte){
	for (;*byte;++byte) uart_1_print_char(*byte);
}


char uart_1_read_char(){
	char temp;
	temp=UDR1;
	return temp;
}

void uart_1_read(){
	uart_1_buffer[buffer_position_1]=uart_1_read_char();
	buffer_position_1++;
	if(buffer_position_1==200)buffer_position_1=0;
}

void uart_1_clear_buffer(void){
	int x;
	for(x=0; x<uart_buffer_size; x++)uart_1_buffer[x]=0x00; //initializing the data array to null
	buffer_position_1=0;
}
//UART 2 functions
char uart_2_buffer[uart_buffer_size];
int buffer_position_2=0;

void set_baudrate_2(unsigned long baudrate){
	switch(F_CPU){
		case 8000000UL:
		switch(baudrate){
			case 9600:
			UBRR2L=51;
			UBRR2H=0;
			break;
			case 19200:
			UBRR2L=25;
			UBRR2H=0;
			break;
			case 38400:
            UBRR2L =12;
            UBRR2H=0;
            break;
			case 115200:
			UBRR2L=3;
			UBRR2H=0;
			break;
		}
		break;
		case 16000000UL:
		switch(baudrate){
			case 9600:
			UBRR2L=103;
			UBRR2H=0;
			break;
			case 19200:
			UBRR2L=51;
			UBRR2H=0;
			break;
			case 38400:
            UBRR2L =25;
            UBRR2H=0;
            break;
			case 115200:
			UBRR2L=8;
			UBRR2H=0;
			break;
		}
		break;
	}
}


void uart_2_init(unsigned long baudrate){
	UCSR2B |=(1<<RXCIE2)|(1<<RXEN2)|(1<<TXEN2);
	UCSR2C |=(1<<UCSZ20)|(1<<UCSZ21);
	set_baudrate_2(baudrate);
}

void uart_2_print_char(char ch){
	while(!(UCSR2A & (1<<UDRE2)));
	UDR2 = ch;
}

void uart_2_write(char * byte){
	for (;*byte;++byte) uart_2_print_char(*byte);
}

char uart_2_read_char(){
	char temp;
	temp=UDR2;
	return temp;
}

void uart_2_read(){
	uart_2_buffer[buffer_position_2]=uart_2_read_char();
	buffer_position_2++;
	if(buffer_position_2==200)buffer_position_2=0;
}

void uart_2_clear_buffer(void){
	int x;
	for(x=0; x<uart_buffer_size; x++)uart_2_buffer[x]=0x00; //initializing the data array to null
	buffer_position_2=0;
}

//UART 3 functions
char uart_3_buffer[uart_buffer_size];
int buffer_position_3=0;

void set_baudrate_3(unsigned long baudrate){
	switch(F_CPU){
		case 8000000UL:
		switch(baudrate){
			case 9600:
			UBRR3L=51;
			UBRR3H=0;
			break;
			case 19200:
			UBRR3L=25;
			UBRR3H=0;
			break;
			case 38400:
            UBRR3L =12;
            UBRR3H=0;
            break;
			case 115200:
			UBRR3L=3;
			UBRR3H=0;
			break;
		}
		break;
		case 16000000UL:
		switch(baudrate){
			case 9600:
			UBRR3L=103;
			UBRR3H=0;
			break;
			case 19200:
			UBRR3L=51;
			UBRR3H=0;
			break;
			case 38400:
            UBRR3L =25;
            UBRR3H=0;
            break;
			case 115200:
			UBRR3L=8;
			UBRR3H=0;
			break;
		}
		break;
	}
}


void uart_3_init(unsigned long baudrate){
	UCSR3B |=(1<<RXCIE3)|(1<<RXEN3)|(1<<TXEN3);
	UCSR3C |=(1<<UCSZ30)|(1<<UCSZ31);
	set_baudrate_3(baudrate);
}

void uart_3_print_char(char ch){
	while(!(UCSR3A & (1<<UDRE3)));
	UDR3 = ch;
}

void uart_3_write(char * byte){
	for (;*byte;++byte) uart_3_print_char(*byte);
}

char uart_3_read_char(){
	char temp;
	temp=UDR3;
	return temp;
}

void uart_3_read(){
	uart_3_buffer[buffer_position_3]=uart_3_read_char();
	buffer_position_3++;
	if(buffer_position_3==200)buffer_position_3=0;
}

void uart_3_clear_buffer(void){
	int x;
	for(x=0; x<uart_buffer_size; x++)uart_3_buffer[x]=0x00; //initializing the data array to null
	buffer_position_3=0;
}

#endif /* _UART_H_ */
