
#include "utils.h"
#include <avr/interrupt.h>

Chip chip;

ISR(INT2_vect)
{
	PORTA = 0xff;
	_delay_ms(1000);
}

void blink()
{
	int i = 0;
	while (1)
	{
		if (i & 8)
			i = 0;
		PORTA = 1 << i;
		DDRA = 1 << i;

		++i;
		_delay_ms(100);
	}
}

int main(void)
{
//	SREG |= 1 << 7;
	sei();
	GICR |= 1 << 5;
	MCUCSR &= ~(1 << 6);

	DDRA = 0xff;
	blink();
}