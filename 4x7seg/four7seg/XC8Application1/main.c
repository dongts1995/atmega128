/*
 * main.c
 *
 * Created: 9/28/2021 2:46:57 PM
 *  Author: tsdto
 */ 


#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include "avr/io.h"
#include "avr/delay.h"
#include <xc.h>
unsigned char led[11]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};
int count=0;
int i = 0;
	
void hienthi(unsigned int x)
{
	// Gan cac chu so vao bien ng, tr, ch, dv
	uint16_t temp, ng, tr, ch, dv;
	temp = x;
	dv = temp%10;
	temp=temp/10;
	ch=temp%10;
	temp=temp/10;
	tr=temp%10;
	temp=temp/10;
	ng=temp;
	
	// hien thi led 1
	PORTB=0x00; // chan B0 B1 Xuat ra 0V
	PORTB=0x01; // Chan B0 xuat ra 5V
	PORTA=led[ng];
	_delay_ms(1);
	// hien thi led 2
	PORTB=0x02; // Chan B1 xuat ra 5V
	PORTA=led[tr];
	_delay_ms(1);
	// hien thi led 3
	PORTB=0x04; // Chan B1 xuat ra 5V
	PORTA=led[ch];
	_delay_ms(1);
	// hien thi led 4
	PORTB=0x08; // Chan B1 xuat ra 5V
	PORTA=led[dv];
	_delay_ms(1);
	
}

void clearled()
{
	// hien thi led 1
	PORTB=0x00; // chan B0 B1 Xuat ra 0V
	PORTB=0x01; // Chan B0 xuat ra 5V
	PORTA=led[10];
	// hien thi led 2
	PORTB=0x02; // Chan B1 xuat ra 5V
	PORTA=led[10];
	// hien thi led 3
	PORTB=0x04; // Chan B1 xuat ra 5V
	PORTA=led[10];
	// hien thi led 4
	PORTB=0x08; // Chan B1 xuat ra 5V
	PORTA=led[10];
}

void init_intr()
{
	TCCR0 = (0<<CS01) | (0<<CS01)| (1<<CS00);
	TIMSK=(1<<TOIE0);
	TCNT0=0;
	sei();
}

ISR(TIMER0_OVF_vect)
{
	TCNT0=0;
	count++;
	if(count > 1000)
	{
		i++;
		i=i%10000;
		count=0;
		clearled();
	}
}

int main(void)
{
	DDRB = 0xFF; // output
	DDRA = 0xFF; // output
	
	PORTA = 0xFF; // tat ca len 5V
	PORTB = 0x00;
	
	init_intr();
	
    while(1)
    {	
		hienthi(i);
    }
}
