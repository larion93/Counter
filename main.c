#include <inttypes.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define __delay_cycles(n)     __builtin_avr_delay_cycles(n) 

unsigned long count = 0;
void numbers_output(unsigned long count)
{

   unsigned short i=0;
   short digits[4]={0,0,0,0};
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
   while (count!=0)
  {
   digits[i]=count%10;
   count=count/10;
   i++;
  }
  for(i=0;i<4;i++)
  {
   PORTC |= (1<<i);
   PORTD = number[digits[i]];
   _delay_us(500);
   PORTC &=~(1<<i);
  }
}

int main( void )
{
  DDRD=0xff;
  PORTD=0xff;
  DDRC = 0xff;
  PORTC=0xff;
  DDRB = 0x00;
  PORTB=0xff;
  while(1)
  {

	 
	 if (bit_is_clear(PINB, PB0)) 
     {
	count++; 
	_delay_ms(100);
     }
     if (bit_is_clear(PINB, PB1)) 
     {
	count+=10; 
	_delay_ms(100);
     }
     if (bit_is_clear(PINB, PB2)) 
     {
	count+=100; 
	_delay_ms(100);
     }
     if (bit_is_clear(PINB, PB6)) 
     {
	count+=1000; 
	_delay_ms(100);
     }
	 
	 numbers_output(count);
     if (count>=10000) {count=0;}
  }
  return 0;
}