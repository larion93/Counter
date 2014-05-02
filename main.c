#include <inttypes.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define __delay_cycles(n)     __builtin_avr_delay_cycles(n) 
unsigned char number[] =
   {
     0x40, //0
     0x79, //1
     0x24, //2
     0x30, //3  
     0x19, //4
     0x12, //5
     0x02, //6
     0x78, //7  
     0x00, //8
     0x10  //9   
   };
short digits[4]={0,0,0,0};
unsigned long count = 0;

void numbers_output(unsigned long count)
{
  unsigned short i=0;
  for(i=0;i<4;i++)
  {
   PORTC |= (1<<i);
   PORTD = number[digits[i]];
   _delay_us(500);
   PORTC &=~(1<<i);
  }
}
void button_checking(short number)
{
	count+=number;
	numbers_partition(count);
	_delay_ms(50);
}
void numbers_partition(unsigned long count)
{

   unsigned short i=0;
   while (count!=0)
  {
   digits[i]=count%10;
   count=count/10;
   i++;
  }
}
ISR (TIMER1_COMPA_vect)
{
	numbers_output(count);
}
int main( void )
{
  DDRD=0xff;
  PORTD=0xff;
  DDRC = 0xff;
  PORTC=0xff;
  DDRB = 0x00;
  PORTB=0xff;

  OCR1A=25000;
  TCCR1B=(1 << WGM12) | (1<<CS10);
  TIMSK|=(1<<OCIE1A);

  sei();
  while(1)
  {
	 if (bit_is_clear(PINB, PB0)) 
     {
	button_checking(1);
     }
     if (bit_is_clear(PINB, PB1)) 
     {
	 if (count-1<1000)
	 {
    button_checking(-1);
	 }
	 }
     if (bit_is_clear(PINB, PB2)) 
     {
	button_checking(15);
     }
     if (bit_is_clear(PINB, PB6)) 
     {
	 if (count-23<1000)
	 {
    button_checking(-23);
	 }
	 }
     if (count>=10000) {count=0;}
  }
  return 0;
}