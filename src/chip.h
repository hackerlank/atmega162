#ifndef CHIP_H
#define CHIP_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>

class Chip;

typedef void (Chip::*ChipPort) (int id, bool val, bool output);

class Chip
{
public:
	void pa(int id, bool val, bool output = true)
	{
/*		DDRA |= 1 << id;
		if (val)
			PORTA |= 1 << id;
		else
			PORTA &= ~(1 << id);*/
		_p(DDRA, PORTA, id, val, output);
	}
	void pb(int id, bool val, bool output = true)
	{
		_p(DDRB, PORTB, id, val, output);
	}
	void pc(int id, bool val, bool output = true)
	{
		_p(DDRC, PORTC, id, val, output);
	}
	void pd(int id, bool val, bool output = true)
	{
		_p(DDRD, PORTD, id, val, output);
	}
	void pe(int id, bool val, bool output = true)
	{
		_p(DDRE, PORTE, id, val, output);
	}
	
	bool pa(int id)
	{
		return _p(DDRA, PINA, id);
	}
	bool pb(int id)
	{
		return _p(DDRB, PINB, id);
	}
	bool pc(int id)
	{
		return _p(DDRC, PINC, id);
	}
	bool pd(int id)
	{
		return _p(DDRD, PIND, id);
	}
	bool pe(int id)
	{
		return _p(DDRE, PINE, id);
	}
	
private:
	void _p(volatile uint8_t& dd, volatile uint8_t& port, int id, bool val, bool output)
	{
		if (output)
			dd |= 1 << id;
		else
			dd &= ~(1 << id);
		if (val)
			port |= 1 << id;
		else
			port &= ~(1 << id);
	}
	bool _p(volatile uint8_t& dd, volatile uint8_t& pin, int id)
	{
		dd &= ~(1 << id);
		return pin & (1 << id);
	}
	
};

extern Chip chip;

#endif