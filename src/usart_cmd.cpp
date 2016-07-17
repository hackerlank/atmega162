
#include "utils.h"
#include "lcd.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Chip chip;
LCD lcd;
USART usart;

char tmp[32];

int main()
{
	lcd.init();
	lcd.drawText(0, 0, "Ready");
	usart.init(0x33, true);
	usart.setTrigger(';');
	while (1)
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
		_delay_ms(500);
	}
}