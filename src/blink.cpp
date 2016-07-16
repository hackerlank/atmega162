
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

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
	blink();
}