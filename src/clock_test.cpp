#include "utils.h"
#include "lcd.h"
#include "timer.h"
#include <stdio.h>

int main()
{
	timer1.init();
	timer1.tcnt_val = 0;
	timer1.reset();

	LCD lcd;
	lcd.init();
	lcd.dis("waiting...");

	_delay_ms(2000);
	uint16_t count = timer1.tcnt;
	long passed = long(count) * 1000 * (1024 * (1./F_CPU));

	char tmp[64];
	// tcnt_val = 0xffff - interval / (1024 * (1./F_CPU));
	sprintf(tmp, "%ld", passed);
	lcd.clear();
	lcd.dis(tmp);
	while (1);
}