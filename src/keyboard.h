#ifndef keyboard_h
#define keyboard_h

#include "utils.h"

class Keyboard
{
public:
	int keyscan(void)
	{
		int key_num = 0;
		for (int i = 0; i < 4; ++i)
			pin(i, 0);
		for (int i = 4; i < 8; ++i)
			pin(i, 1, false);
		_delay_ms(1);

		switch (pin_col() & 0xf)
		{
			case 0xe: key_num = 1; break;
			case 0xd: key_num = 2; break;
			case 0xb: key_num = 4; break;
			case 0x7: key_num = 3; break;
		}

		for (int i = 4; i < 8; ++i)
			pin(i, 0);
		for (int i = 0; i < 4; ++i)
			pin(i, 1, false);
		_delay_ms(1);
		switch(pin_row() & 0xf)
		{
			case 0xe: key_num += 0; break;
			case 0xd: key_num += 4; break;
			case 0xb: key_num += 8; break;
			case 0x7: key_num += 12; break;
		}
		return key_num;
	}

private:
	void setDDR(uint8 bits)
	{
		DDRD |= (bits & 0xfc);
		DDRB |= (bits & 0x03);
	}

	void clrDDR(uint8 bits)
	{
		DDRD &= ~(bits & 0xfc);
		DDRB &= ~(bits & 0x03);
	}

	void setPort(uint8 bits)
	{
		PORTD |= (bits & 0xfc);
		PORTB |= (bits & 0x03);
	}

	void clrPort(uint8 bits)
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

	uint8 pin(int id)
	{
		if (id < 6)
			return chip.pd(7 - id);
		else
			return chip.pb(7 - id);
	}	
};

#endif