#ifndef CHIP_H
#define CHIP_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>

class Chip;

typedef void (Chip::*ChipPort) (int id, bool val);

class Chip
{
public:
	void pa(int id, bool val)
	{
/*		DDRA |= 1 << id;
		if (val)
			PORTA |= 1 << id;
		else
			PORTA &= ~(1 << id);*/
		_p(DDRA, PORTA, id, val);
	}
	void pb(int id, bool val)
	{
		_p(DDRB, PORTB, id, val);
	}
	void pc(int id, bool val)
	{
		_p(DDRC, PORTC, id, val);
	}
	void pd(int id, bool val)
	{
		_p(DDRD, PORTD, id, val);
	}
	void pe(int id, bool val)
	{
		_p(DDRE, PORTE, id, val);
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
	void _p(volatile uint8_t& dd, volatile uint8_t& port, int id, bool val)
	{
		dd |= 1 << id;
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