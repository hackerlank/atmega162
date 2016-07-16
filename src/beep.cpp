
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void beep()
{
	DDRD = 1 << 3;
	while (1)
	{
		PORTD = 1 << 3;
		_delay_ms(100);
		PORTD = 0;
		_delay_ms(100);
	}
}

int main(void)
{
	beep();
}