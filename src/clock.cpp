#include "utils.h"
#include "lcd.h"
#include "clock.h"
#include <stdio.h>

int main()
{
	clock_begin();

	LCD lcd;
	lcd.init();
	lcd.dis("waiting...");

	_delay_ms(2000);

	char tmp[64];
	sprintf(tmp, "%ld", clock());
	lcd.clear();
	lcd.dis(tmp);
	while (1)
	{
		_delay_ms(1000);
		sprintf(tmp, "%ld\n%ld", clock(), clock_us());
		lcd.clear();
		lcd.dis(tmp);
	}
}