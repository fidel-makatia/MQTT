#ifndef _TIMER_H_
#define _TIMER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
void enable16bit_timer(int Timer, long TCNT_x)
{
	
	switch(Timer)
	{
		case 1:
		 TCCR1A = 0;
		 TCCR1B = 0;
		 TCCR1B |= (5<<CS10);
		 TIMSK1 |= 1<<TOIE1;
		 TCNT1 = TCNT_x;
		 break;
		 case 3:
		 TCCR3A = 0;
		 TCCR3B = 0;
		 TCCR3B |= (5<<CS30);
		 TIMSK3 |= 1<<TOIE3;
		 TCNT3 = TCNT_x;
		 break;
		 case 4:
		 TCCR4A = 0;
		 TCCR4B = 0;
		 TCCR4B |= (5<<CS40);
		 TIMSK4 |= 1<<TOIE4;
		 TCNT4 = TCNT_x;
		 break;
		 case 5:
		 TCCR5A = 0;
		 TCCR5B = 0;
		 TCCR5B |= (5<<CS50);
		 TIMSK5 |= 1<<TOIE5;
		 TCNT5 = TCNT_x;
		 break;
	}
}
#endif /* _UART_H_ */