#ifndef UTILS_H
#define UTILS_H

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned char byte;

#include "chip.h"
#include <util/delay.h>

#define nop() asm("nop")

void light(int id, bool on = true)
{
	if (id >= 0)
		chip.pa(id, on);
	else
	{
		DDRA = 0xff;
		PORTA = on ? 0xff : 0x00;
	}
}

void _beep(ChipPort port, int idx, int count)
{
	while (count--)
	{
		(chip.*port)(idx, 1, true);
		_delay_ms(50);
		(chip.*port)(idx, 0, true);
		_delay_ms(200);
	}	
}

void beep_a(int count = 1)
{
	_beep(&Chip::pd, 3, count);
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

void beep_b(int count = 1)
{
#if 0
	while (count--)
	{
		chip.pb(4, 1);
		_delay_ms(50);
		chip.pb(4, 0);
		_delay_ms(200);
	}
#else
	_beep(&Chip::pb, 4, count);
#endif
}

void delay_us(int us)
{
	while (us--)
		_delay_us(1);
}

void delay_ms(int ms)
{
	while (ms--)
		_delay_ms(1);
}

#endif