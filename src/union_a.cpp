
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
	// _delay_ms(1000);
	blink.start(0);
	usart1.send("zigbee_ready(a);");
	_delay_ms(50);
	while ((addr_a = zigbee.addr()) == 0xfffe)
	{
		blink.onloop();
		_delay_ms(100);
	}
	flash.start(0);
	while (!got_addr)
	{
		flash.onloop();
//		usart1.send("zigbee_ready(a);");
		_delay_ms(1000);
		checkCmd(usart1);
	}
	// while (addr_b == 0xfffe)
	// {
	// 	flash.onloop();
	// 	checkCmd(usart1);
	// 	_delay_ms(500);
	// }
	// usart1.send("got(a);");
	// _delay_ms(500);

	// lcd.dis("Waiting...");

//		usart1.send("zigbee_ready(a);");

	DDRA = 0xff;
	PORTA = 0x02;
	while (1)
	{
		motor.onloop();
		checkCmd(usart1);
	}
}