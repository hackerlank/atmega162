
#define MCUID 1

#include "utils.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>

Chip chip;

int main()
{
	beep_a();

	cli();
	wdt_disable();
	wdt_enable(WDTO_2S);

	while (1)
	{
#if 0
		wdt_reset();
#endif
	}
}