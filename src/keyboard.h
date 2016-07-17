#ifndef keyboard_h
#define keyboard_h

#include "utils.h"

class Keyboard
{
public:
	int keyscan(void)
	{
		int key_num = 0;
		int cols[] = {0xe, 0xd, 0x7, 0xb};
		int rows[] = {0xe, 0xd, 0xb, 0x7};
		for (int i = 0; i < 4; ++i)
			pin(i, 0);
		for (int i = 4; i < 8; ++i)
			pin(i, 1, false);
		for (int i = 0, t = pin_col() & 0xf; i < 4; ++i)
			if (t == cols[i])
				key_num = i + 1;
		for (int i = 4; i < 8; ++i)
			pin(i, 0);
		for (int i = 0; i < 4; ++i)
			pin(i, 1, false);
		for (int i = 0, t = pin_row() & 0xf; i < 4; ++i)
			if (t == rows[i])
				key_num += i * 4;
		return key_num;
	}

private:
	void setDDR(byte bits)
	{
		DDRD |= (bits & 0xfc);
		DDRB |= (bits & 0x03);
	}

	void clrDDR(byte bits)
	{
		DDRD &= ~(bits & 0xfc);
		DDRB &= ~(bits & 0x03);
	}

	void setPort(byte bits)
	{
		PORTD |= (bits & 0xfc);
		PORTB |= (bits & 0x03);
	}

	void clrPort(byte bits)
	{
		PORTD &= ~(bits & 0xfc);
		PORTB &= ~(bits & 0x03);
	}

	int pin_row()
	{
		return pin(0) + (pin(1) << 1) + (pin(2) << 2) + (pin(3) << 3);
	}
	int pin_col()
	{
		return pin(4) | (pin(5) << 1) | (pin(6) << 2) | (pin(7) << 3);
	}

	void pin(int id, bool val, bool output = true)
	{
		if (id < 6)
			chip.pd(7 - id, val, output);
		else
			chip.pb(7 - id, val, output);
	}

	byte pin(int id)
	{
		if (id < 6)
			return chip.pd(7 - id);
		else
			return chip.pb(7 - id);
	}	
};

#endif