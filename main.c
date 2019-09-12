/*
 * Lab_1_redo.c
 *
 * Created: 9/12/2019 12:31:49 PM
 * Author : pimen
 */ 

void mydelay(int x);

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>


int one_hz = 50;
int five_hz = 10;
int ten_hz = 5;
int Delay_Time;
int Delay_Select;

#define Led 5
#define button 7


int main(void)
{
	DDRB = 1<<Led; //set to input
	PORTB |= 1<<Led; //turn led off
	
	Delay_Time = five_hz;
	Delay_Select = 3;
	
    /* Replace with your application code */
    while (1) 
    {
		if((PINB & 0x80) == 0) //when the button goes low
		{
			while((PINB & (1<<button)) == 0)
			{
				//what till goes high
			}
			
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

