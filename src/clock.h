#ifndef clock_h
#define clock_h

#include "timer.h"

static long timer0_count = 0;

void on_timer0()
{
	++timer0_count;
}

void clock_begin()
{
	timer0.init();
	timer0.tcnt_val = 0;
	timer0.slot = on_timer0;
	timer0.reset();
}

#define clock clock_ms

long clock_ms()
{
	long passed = long(timer0.tcnt) * (1024 * (1. / (F_CPU / 1000)));
	passed += timer0_count * 0xff * (1024 * (1. / (F_CPU / 1000)));
	return passed;
}

long clock_us()
{
	long passed = long(timer0.tcnt) * (1024 * (1. / (F_CPU / 1000000)));
	passed += timer0_count * 0xff * (1024 * (1. / (F_CPU / 1000000)));
	return passed;	
}

#endif