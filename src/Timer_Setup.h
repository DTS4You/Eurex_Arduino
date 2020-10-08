#include <Arduino.h>

void Timer_Setup()
{
  	// Timer 1 Setup
  	TCCR1A	= 0;
  	TCCR1B	= 0;
  	TCNT1		= 0;
  	OCR1A		= 31250;            					// compare match register
  	TCCR1A  |=  ( 0 << WGM10  | 0 << WGM11 ); // Waveform normal
  	TCCR1B  |=  ( 1 << WGM12 );              	// CTC mode
  	TCCR1B  |=  ( 1 << CS11 );						// Clock prescaler
	TIMSK1  &= ~( 1 << OCIE1A );					// disable timer compare interrupt
	// Timer 2 Setup
	TCCR2A	= 0;
	TCCR2B	= 0;
	TCNT2		= 0;
	OCR2A 	= 120;
  	TCCR2A 	= 	( 1 << WGM21 );               // WGM22=0 + WGM21=1 + WGM20=0 = Mode2 (CTC)
  	TCCR2B 	= 	( 1 << CS22 ) | ( 1 << CS21 ) | ( 1 << CS20 );
	TIMSK2  &= ~( 1 << OCIE2A );           	// disable timer compare interrupt
	// Timer 3 Setup
  	TCCR3A	= 0;
  	TCCR3B	= 0;
  	TCNT3 	= 0;
  	OCR3A 	= 31250;            					// compare match register
  	TCCR3A  |=  ( 0 << WGM30  | 0 << WGM31);	// Waveform normal
  	TCCR3B  |=  ( 1 << WGM32 );					// CTC mode
  	TCCR3B  |=  ( 1 << CS31 );	            	// Clock prescaler
  	TIMSK3  &= ~( 1 << OCIE3A );					// disable timer compare interrupt
  	// Timer 4 Setup
  	TCCR4A 	= 0;
  	TCCR4B 	= 0;
  	TCNT4  	= 0;
  	OCR4A 	= 31250;            					// compare match register
  	TCCR4A  |=  ( 0 << WGM40  | 0 << WGM41); 	// Waveform normal
  	TCCR4B  |=  ( 1 << WGM42 );					// CTC mode
  	TCCR4B  |=  ( 1 << CS41 );						// Clock prescaler
  	TIMSK4  &= ~( 1 << OCIE4A );					// disable timer compare interrupt
  	// Timer 5 Setup
  	TCCR5A 	= 0;
  	TCCR5B 	= 0;
  	TCNT5  	= 0;
  	OCR5A 	= 31250;            					// compare match register
  	TCCR5A  |=  ( 0 << WGM50  | 0 << WGM51); 	// Waveform normal
  	TCCR5B  |=  ( 1 << WGM52 );					// CTC mode
  	TCCR5B  |=  ( 1 << CS51 );						// Clock prescaler
  	TIMSK5  &= ~( 1 << OCIE5A );					// disable timer compare interrupt
}

// Timer-Clock 1,3,4,5
//    CSn2  CSn1  CSn0  Description
//    0     0     0     No clock source. (Timer/Counter stopped)
//    0     0     1     clk I/O /1 (No prescaling
//**  0     1     0     clk I/O /8 (From prescaler)
//    0     1     1     clk I/O /64 (From prescaler)
//    1     0     0     clk I/O /256 (From prescaler)
//    1     0     1     clk I/O /1024 (From prescaler)
//    1     1     0     External clock source on Tn pin. Clock on falling edge
//    1     1     1     External clock source on Tn pin. Clock on rising edge
// Timer-Clock 0,2
//		CS22 	CS21 	CS20 	Description
// 	0		0		0 		No clock source (Timer/Counter stopped)
//		0 		0 		1 		clk T2S /1 (No prescaling)
//		0 		1 		0 		clk T2S /8 (From prescaler)
//		0 		1 		1		clk T2S /32 (From prescaler)
//		1 		0		0		clk T2S /64 (From prescaler)
//		1 		0 		1 		clk T2S /128 (From prescaler)
//		1 		1		0		clk T 2 S /256 (From prescaler)
//		1		1		1		clk T 2 S /1024 (From prescaler)
