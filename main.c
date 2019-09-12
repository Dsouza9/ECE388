/*
 * Led_Flash.c
 *
 * Created: 9/10/2019 12:21:32 PM
 * Author : pimen
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int One_Sec = 3036; //65536 - Delay Cycle(62500) = 3036
int Five_Sec = 5306; //65536 - Delay Cycle(12500) = 5306
int Ten_Sec = 59286; //65536 - Delay Cycle(6250) = 59286
int Delay_Time; //initialize Delay Time variable 
#define Led 5 // Led is located on PB5 so set led to 5
int On = 0; //initialize led to on(0)


int main(void)
{
	DDRB = 0x00; //set to input
	PORTB |= 1<<Led; //turn led off
	//set TIMSKx so Timex interrupt process
	TCCR1A = (0b00<<COM0A0)|(0b00<<COM0B0)|(0b00<<WGM00); //set to normal mode
	TCCR1B= (0b0<<WGM02) | (0b100<<CS00); //256 pre scaler
	TIMSK1 = (0b1<<TOIE0); // enable interrupt
	sei ();
	Delay_Time = Five_Sec;
	TCNT1 = -Five_Sec; //set led to flash 5 times
	int Delay_Select = 2; //Skip over first delay in while loop since the freq. is at 5Hz to begin and go right to 10Hz when button is pushed

    while (1) 
    {
		if((PINB & 0x80) == 0) //when the button goes low
		{
			while((PINB & 0x80) == 0)
			{
				//what till goes high
			}
			/*
			switch(Delay_Select) //jump to the next flash rate
			{
				case 1:
					Delay_Time = Five_Sec; //Set delay time to the new Flash rate
					Delay_Select = 2; //Select the next flash rate when button is pushed
					break;
				case 2:
					Delay_Time = Ten_Sec;
					Delay_Select = 3;
					break;
				case 3:
					Delay_Time = One_Sec;
					Delay_Select = 1;
					break;
			}*/
			
			if(Delay_Select == 1)
			{
				Delay_Time = Five_Sec;
				Delay_Select = 2;
			}
			else if (Delay_Select == 2)
			{
				Delay_Time = Ten_Sec;
				Delay_Select = 3;
			}
			else if(Delay_Select == 3)
			{
				Delay_Time = One_Sec;
				Delay_Select = 1;
			}
			
			TCNT1 = -Delay_Time; //reset TCNT1 with new flash rate
		}
		
		_delay_ms(200); //button bounce
    }
}


ISR(TIMER1_OVF_vect)
{
	TCNT1 = -Delay_Time; //reset TCNT1
	if(On == 0)
	{
		PORTB &= On << Led; //Turn led on
		On = 1; //Set On to next state of led to Off
	}
	else
	{
		PORTB |= On << Led; //turn led off
		On = 0; //Set On to next state of led to On
	}
}




