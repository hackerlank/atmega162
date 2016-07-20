
#define MCUID 1

#include "command.h"
#include "blink.h"
#include "zigbee.h"
#include "flash.h"

int main()
{
	Blink blink;
	Flash flash;
	Zigbee zigbee;
	clock_begin();
	// usart1.init(0x33, true);
	usart1.init(12, true);
//	usart1.setTrigger(';');
	// usart1.setTriggerTime(60);
	_delay_ms(1000);
	blink.start(0);
	// usart1.send("zigbee_ready(a);");
	_delay_ms(50);
	while ((addr_a = zigbee.addr()) == 0xfffe)
	{
		blink.onloop();
		_delay_ms(100);
	}
	usart1.send("zigbee_ready(a);");
	// lcd.dis("Waiting...");
	flash.start(0);
	while (addr_b == 0xfffe)
	{
		flash.onloop();
		checkCmd(usart1);
		_delay_ms(100);
	}

	light(1);
	while (1)
	{
		motor.onloop();
		checkCmd(usart1);
	}
}