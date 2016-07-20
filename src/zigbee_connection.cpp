
#define MCUID 2

#include "utils.h"
#include "zigbee.h"
#include "lcd.h"
#include <stdio.h>

#define BAUD 38400
#define Coordinator 0

int main()
{
	clock_begin();
	bool success;
	LCD lcd;
	lcd.init();
#if BAUD == 9600
	usart1.init(0x33, true);
#elif BAUD == 38400
	usart1.init(12, true);
#endif
//	usart1.setTriggerTime(50);
	char tmp[32];
	lcd.dis("Zigbee Test");
//	_delay_ms(1000);
	Zigbee zigbee;

	int panid = zigbee.panid();
	// _delay_ms(500);
	int addr = zigbee.addr();
	sprintf(tmp, "PAN: %x\nADDR: %x", panid, addr);
	lcd.clear();
	lcd.dis(tmp);
	while (1);
	{
		_delay_ms(1000);
	}
}