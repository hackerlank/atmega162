
#include "utils.h"
#include "lcd.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

LCD lcd;
USART &usart = usart1;

char tmp[64];

int main()
{
	clock_begin();
	lcd.init();
	lcd.drawText(0, 0, "Ready");
	usart.init(12, true);
	// usart.init(0x33, true);
//	usart.setTrigger(';');
	_delay_ms(1000);
	usart1.send("zigbee_ready(b);");
	while (1)
	{
		if (usart.triggered())
		{
			sprintf(tmp, "[%02x %02x %02x %02x %s", usart.buf[0], usart.buf[1], usart.buf[2], usart.buf[3], usart.buf+4);
			// lcd.clear();
			// lcd.drawText(0, 0, usart.buf);
			// usart.send(usart.buf);
			lcd.dis(tmp);
			usart.clear_buf();
		}
		_delay_ms(500);
	}
}