/*
 * _spi.h
 *
 * Created: 06/05/2018 08:58:56
 *  Author: Oki
 */

#ifndef _SPI_H_
#define _SPI_H_
#define F_CPU 16000000UL
#define spi_buffer_size 256

char spi_buffer[spi_buffer_size];
int buffer_position=0;
void USART_Init_Master(void)
{
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK); //SET MOSI AND SCK OUTPUT AND ALL OTHERS INPUT
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //ENABLE SPI MASTER, SET CLOCK RATE TO fck/16
}
void SPI_Transmit_Char(char data)
{
	SPDR= data;
	while(!(SPSR & (1<<SPIF))) //Wait for transmission to complete
	;
}
void SPI_Slave_Init(void)
{
	DDR_SPI = (1<<DD_MISO); //MISO OUTPUT THE REST INPUT
	SPCR = (1<<SPIE); // Enable SPI interrupt
	SPCR = (1<<SPE);  //ENABLE SPI
}
unsigned char SPI_SlaveReceive(void)
{
	char temp;
	temp = SPDR;
	return temp;
}
void SPI_Write(char * byte){
	for (;*byte;++byte) SPI_Transmit_Char(*byte);
}
void SPI_Read(void)
{
	spi_buffer[buffer_position]=SPI_SlaveReceive();
	buffer_position++;
	if(buffer_position==200)buffer_position=0;
}
void SPI_Clear_Buffer(void)
{
		int x;
		for(x=0; x<spi_buffer_size; x++)spi_buffer[x]=0x00; //initializing the data array to null
		buffer_position=0;
}
void USART_SPI_Initialize_0(unsigned long baudrate) //to use USART in SPI mode
{
		UBRR0 = 0;
		XCK0_DDR |= (1<<XCK0); /* Setting the XCKn port pin as output, enables master mode. */
		UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(0<<UCPHA0)|(0<<UCPOL0); /* Set MSPI mode of operation and SPI data mode 0. */
		UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); /* Enable receiver and transmitter AND INTERRUPTS*/
	
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
void USART_SPI_Initialize_1(unsigned long baudrate)
{
		UBRR1 = 0;
		XCK1_DDR |= (1<<XCK1); /* Setting the XCKn port pin as output, enables master mode. */
		UCSR1C = (1<<UMSEL11)|(1<<UMSEL10)|(0<<UCPHA1)|(0<<UCPOL1); /* Set MSPI mode of operation and SPI data mode 0. */
		UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1); /* Enable receiver and transmitter. */
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
void USART_SPI_Initialize_2(unsigned long baudrate)
{
		UBRR2 = 0;
		XCK2_DDR |= (1<<XCK2); /* Setting the XCKn port pin as output, enables master mode. */
		UCSR2C = (1<<UMSEL21)|(1<<UMSEL20)|(0<<UCPHA2)|(0<<UCPOL2); /* Set MSPI mode of operation and SPI data mode 0. */
		UCSR2B = (1<<RXEN2)|(1<<TXEN2)|(1<<RXCIE2); /* Enable receiver and transmitter. */
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
void USART_SPI_Initialize_3(unsigned long baudrate)
{
	UBRR3 = 0;
	XCK3_DDR |= (1<<XCK3); /* Setting the XCKn port pin as output, enables master mode. */
	UCSR3C = (1<<UMSEL31)|(1<<UMSEL30)|(0<<UCPHA3)|(0<<UCPOL3); /* Set MSPI mode of operation and SPI data mode 0. */
	UCSR3B = (1<<RXEN3)|(1<<TXEN3)|(1<<RXCIE3); /* Enable receiver and transmitter. */
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
unsigned char USART_Receive_SPI_0( void )
{
	char temp;
	temp = UDR0;
	return temp;
}
unsigned char USART_Receive_1( void )
{
	char temp;
	temp = UDR1;
	return temp;
}
unsigned char USART_Receive_2( void )
{
	char temp;
	temp = UDR2;
	return temp;
}
unsigned char USART_Receive_3( void )
{
	char temp;
	temp = UDR3;
	return temp;
}
#endif /* _SPI_H_ */