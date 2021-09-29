/*
 * main.c
 *
 * Created: 9/28/2021 2:46:57 PM
 *  Author: tsdto
 */ 
#define F_CPU 16000000UL
#include "avr/io.h"
#include "avr/delay.h"
#include <xc.h>
unsigned char led[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

int main(void)
{
	DDRD = 0xFF; // output
	PORTD = 0xFF; // tat ca len 5V
	
    while(1)
    {	
		for (int i = 0; i < 10; i++)
		{
			PORTD = led[i];
			_delay_ms(50);
		}
        //TODO:: Please write your application code 
    }
}