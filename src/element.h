#ifndef element_h
#define element_h

#include "utils.h"
#include <stdarg.h>
#include <malloc.h>

class Element
{
public:
	Element()
		: pins(0)
		{}

	~Element()
	{
		if (pins)
			free(pins);
	}

	void connect(int n, ...)
	{
		va_list arg_ptr;
		byte* p = pins = malloc(sizeof(byte) * n);
		byte d;
		va_start(arg_ptr, n);
		while (n--)
		{
			d = va_arg(arg_ptr, int);
			*p++ = d;
		}
	}

	void pin(int id, bool val, bool output = true)
	{
		ChipPort port = 0;
		switch (pins[id] & 0xf0)
		{
			case 0xa0: port = &Chip::pa; break;
			case 0xb0: port = &Chip::pb; break;
			case 0xc0: port = &Chip::pc; break;
			case 0xd0: port = &Chip::pd; break;
			case 0xe0: port = &Chip::pe; break;
		}
		(chip.*port)(pins[id] & 0x0f, val, output);
	}

	// byte pin(int id)
	// {
	// 	if (id < 6)
	// 		return chip.pd(7 - id);
	// 	else
	// 		return chip.pb(7 - id);
	// }	


	byte* pins;
};

#endif