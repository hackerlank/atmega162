#ifndef timer_h
#define timer_h

#include "utils.h"
#include <avr/interrupt.h>

typedef void (*timer_slot)(void);

class Timer
{
public:
	Timer(volatile uint8_t& _tccra, volatile uint8_t& _tccrb, volatile uint16_t& _tcnt, int _toie)
		: tccra(_tccra)
		, tccrb(_tccrb)
		, tcnt(_tcnt)
		, toie(_toie)
	{
		slot = 0;
		interval = 0xc2f6;
	}

	void init()
	{
		tcnt_val = 0xffff - interval / (1024 * (1./F_CPU));
		cli();
		tccra = 0;
		tccrb = (1 << CS12) | (1 << CS10);
		tcnt = tcnt_val;
		TIMSK = (1 << toie);
		sei();
	}

	void reset()
	{
		TCNT1 = tcnt_val;
	}

	volatile uint8_t &tccra, &tccrb;
	volatile uint16_t &tcnt;
	int toie;
	timer_slot slot;
	double interval;
	uint16_t tcnt_val;
};

Timer timer1(TCCR1A, TCCR1B, TCNT1, TOIE1);

ISR(TIMER1_OVF_vect)
{
	timer1.reset();
	if (timer1.slot)
		(*timer1.slot)();
}

void setTimer1(double interval, timer_slot slot)
{
	timer1.interval = interval;
	timer1.slot = slot;
	timer1.init();
}

#endif