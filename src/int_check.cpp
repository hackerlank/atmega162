
#include "utils.h"
#include <avr/interrupt.h>

Chip chip;

ISR(INT2_vect)
{
	light(-1);
	_delay_ms(1000);
}

int main(void)
{
	sei();
	GICR |= 1 << 5;
	MCUCSR &= ~(1 << 6);

	blink();
}