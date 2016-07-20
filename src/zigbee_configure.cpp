
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
	char tmp[32];
	lcd.dis("Zigbee Conf");
	_delay_ms(1000);
	Zigbee zigbee;
	lcd.dis("Zigbee module restart...");
	zigbee.restart();
	_delay_ms(1000);
#if Coordinator
	lcd.dis("Setting to coordinator...");
	_delay_ms(1000);
	success = zigbee.set_coordinator();
#else
	lcd.dis("Setting to routor...");
	_delay_ms(1000);
	success = zigbee.set_router();	
#endif
	lcd.dis(success ? "Successed." : "Failed.");
	if (!success)
		while (1);
	_delay_ms(1000);
	lcd.dis("Setting PANID...");
	_delay_ms(1000);
	int panid = zigbee.panid(0x2016);
	sprintf(tmp, "PANID set to %x", panid);
	lcd.dis(tmp);
	_delay_ms(1000);
	lcd.dis("Setting baud...");
	_delay_ms(1000);
	int baud = zigbee.baud(3); // restart required;
	success = baud == 38400;
	lcd.dis(success ? "Successed." : "Failed.");
	if (!success)
		while (1);


//	zigbee.restart();
//	_delay_ms(1000);
//	int panid = zigbee.panid(0x2016);
	// int panid = zigbee.panid();
	// _delay_ms(500);
	// int addr = zigbee.addr();
	// sprintf(tmp, "PAN: %x\nADDR: %x", panid, addr);
	// lcd.clear();
	// lcd.dis(tmp);
	while (1);
	{
		_delay_ms(1000);
	}
}