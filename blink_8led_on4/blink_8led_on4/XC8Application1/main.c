/* 00000001
   00000011
   00000111
   00001111
   00011110
   00111100
   01111000
   11110000
   01111000
   00111100
   00011110
   00001111
   00000111
   00000011
   00000001 */

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

void led_init();
void LED_OUT(uint8_t led);
void set_timer0();
uint8_t led1 = 0x0F;
uint8_t led2= 0xF0;
uint8_t led3;
uint8_t led4=0x01;
int count=0;
int chieu_dich = 0;
int i = 0;

int main(void)
{
	led_init();
	set_timer0();
	while(1)
	{
		/*for (uint8_t i = 0; i<8; i++)
		{
			if(i < 3)
			{
				led3 = led1 >> (3-i);
			}
			else
			{
				led3 = led1 << (i-3);	
			}
			LED_OUT(led3);
			_delay_ms(500);
		}
		for (uint8_t i = 6; i > 0; i--)
		{
			led3=led2>>(7-i);
			LED_OUT(led3);
			_delay_ms(500);
		}*/
	}
}
void led_init()
{
	DDRB=0xF0;
	DDRD=0xF0;
}

void LED_OUT(uint8_t led)
{
	PORTB=led << 4;
	PORTD=led;
}

void set_timer0()
{
	TCCR0=(0<<CS2) | (1<<CS1) | (1<<CS0) ;
	TIMSK|= (1<<TOIE0);
	sei();
}

ISR(TIMER0_OVF_vect)
{
	if(count<30)
	{
		count++;
	}
	else
	{
		if(chieu_dich == 0)
		{
			if(i < 3)
			{
				led3 = led1 >> (3-i);
				i++;
			}
			else if(i < 8)
			{
				led3 = led1 << (i-3);
				i++;
			}
			else
			{
				chieu_dich = 1;
				i = 7;
			}
			
		}
		if(chieu_dich == 1)
		{
			if(i>0)
			{
				led3>>=1;
				LED_OUT(led3);
				i--;
			}
			else 
			{
				chieu_dich = 0;
				i = 0;
			}
		}
		LED_OUT(led3);
		count = 0;
	}
}