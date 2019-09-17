/*
 * Lab_1.c
 *
 * Created: 9/12/2019 12:31:49 PM
 * Author : pimen
 */ 

void mydelay(int x);

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


volatile int one_hz = 50;
volatile int five_hz = 10;
volatile int ten_hz = 5;
int Delay_Time;
volatile int Delay_Select = 3;
//int Flag = 0;
int On = 0;

#define Led 5
#define button 7

uint8_t portbhistory = 0xFF; 



int main(void)
{
	DDRB = 1<<Led; //set to input
	PORTB |= (1<<button); //enable pull-up
	
	PORTB &= ~(1<<Led); //turn led off
	
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT7);
	sei();
	
	Delay_Time = five_hz;
	

    while (1) 
    {		
		PORTB &= ~(1<< Led); //Turn led off
		mydelay(Delay_Time);
		PORTB |= 1 << Led; //turn led on
		mydelay(Delay_Time);
    }
}

void mydelay(int x)
{
	for(int i = 0; i < x; i++)
	{
		_delay_ms(10);
	}
	
}

ISR(PCINT0_vect)
{
	if(PINB != (PINB & ~(1<<button))) //button goes high
	{		
		if(Delay_Select == 1)
		{
			Delay_Time = one_hz;
			Delay_Select = 2;
		}
		else if (Delay_Select == 2)
		{
			Delay_Time = five_hz;
			Delay_Select = 3;
		}
		else if(Delay_Select == 3)
		{
			Delay_Time = ten_hz;
			Delay_Select = 1;
		}
	}
}


