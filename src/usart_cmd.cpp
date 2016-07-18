
#include "utils.h"
#include "lcd.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

LCD lcd;

char tmp[32];

void checkCmd(USART& usart)
{
	if (usart.triggered())
	{
		lcd.clear();
		lcd.drawText(0, 0, usart.buf);
		usart.send(usart.buf);

		if (!strncmp(usart.buf, "beep(", 5))
		{
			int n;
			sscanf(usart.buf, "beep(%d)", &n);
			if (n < 1)
				n = 1;
			beep_b(n);
		}
		if (!strncmp(usart.buf, "dis(", 4))
		{
			sscanf(usart.buf, "dis(%s", tmp);
			tmp[ strlen(tmp) - 2 ] = 0;
			lcd.clear();
			lcd.drawText(0, 0, tmp);
		}
		if (!strncmp(usart.buf, "loopback(", 9))
		{
			int n;
			sscanf(usart.buf, "loopback(%d)", &n);
			usart.loopback(n);
		}

		usart.clear_buf();
	}
}

int main()
{
	lcd.init();
	lcd.drawText(0, 0, "Ready");
	usart0.init(0x33, true);
	usart0.setTrigger(';');
	usart1.init(0x33, true);
	usart1.setTrigger(';');
	while (1)
	{
		checkCmd(usart0);
		checkCmd(usart1);
		_delay_ms(500);
	}
}