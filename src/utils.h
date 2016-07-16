#ifndef UTILS_H
#define UTILS_H

#include "chip.h"
#include <util/delay.h>

void light(int id, bool on = true)
{
	chip.pa(id, on);
}

void _beep(ChipPort port, int idx, int count)
{
	while (count--)
	{
		(chip.*port)(idx, 1);
		_delay_ms(50);
		(chip.*port)(idx, 0);
		_delay_ms(200);
	}	
}

void beep_a(int count = 1)
{
	_beep(&Chip::pd, 3, count);
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