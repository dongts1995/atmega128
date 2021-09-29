/*
 * main.c
 *
 * Created: 9/28/2021 2:46:57 PM
 *  Author: tsdto
 */ 




#define F_CPU 8000000UL 
//#define DATA	PORTA.0
//#define LATCH	PORTA.2 
//#define CLOCK	PORTA.1
#include <avr/interrupt.h>
#include "avr/io.h"
#include "avr/delay.h"
#include <xc.h>
unsigned char led[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int count=0;
int i = 0;
	
void hienthi(unsigned int x)
{
	uint16_t temp, ch, dv;
	temp = x;
	dv = temp%10;
	temp=temp/10;
	ch=temp;
	
	// hien thi led 1
	PORTB=0x00; // chan B0 B1 Xuat ra 0V
	PORTB=0x01; // Chan B0 xuat ra 5V
	hc595(led[ch]);
	//PORTA=led[ch];
	_delay_ms(1);
	// hien thi led 2
	PORTB=0x00; // chan B0 B1 Xuat ra 0V
	PORTB=0x02; // Chan B1 xuat ra 5V
	hc595(led[dv]);
	//PORTA=led[dv];
	_delay_ms(1);
	
}

void clearled()
{
	// hien thi led 1
	PORTB=0x00; // chan B0 B1 Xuat ra 0V
	PORTB=0x01; // Chan B0 xuat ra 5V
	hc595(0xff);
	//PORTA=0xff;
	_delay_ms(1);
	// hien thi led 2
	PORTB=0x00; // chan B0 B1 Xuat ra 0V
	PORTB=0x02; // Chan B1 xuat ra 5V
	hc595(0xff);
	//PORTA=0xff;
	_delay_ms(1);
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
		i=i%100;
		count=0;
	}
}

int main(void)
{
	DDRB = 0xFF; // output
	DDRA = 0xFF; // output
	
	PORTA = 0xFF; // tat ca len 5V
	PORTB = 0x00;
	//hc595(0b01010101);
	
	init_intr();
	//hienthi(55);
	
    while(1)
    {	
		//PORTA = 0xfb;
		//hc595(0x01010101);
		clearled();
		hienthi(i);
    }
}

void hc595(uint8_t data)
{
	int temp;
	PORTA=0x00;
	for (int i=0; i<8 ;i++)
	{
		temp=data;//<<i;
		temp=temp&0x80;
		if (temp==0x80) PORTA |= 0x01; //DATA = 1;
		else PORTA &= 0xfe;	// DATA = 0;
		PORTA |= 0x02; //CLOCK=0;
		PORTA &= 0xfd; //CLOCK=1;
		data<<=1;
	}
	PORTA |= 0x04; //LATCH=0;
	PORTA &= 0xfb; //LATCH=1;
	//_delay_ms(1);
}
