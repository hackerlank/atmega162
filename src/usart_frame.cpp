
#include "utils.h"
#include "lcd.h"
#include "usart.h"
#include "timer.h"
#include <string.h>
#include <stdlib.h>

LCD lcd;
USART &usart = usart0; 

char old_buf[128] = {0};

void onTimer1()
{
	if (usart.buf[0] && !strcmp(old_buf, usart.buf))
	{
		usart._triggered = true;
	}
	strcpy(old_buf, usart.buf);
}

int main()
{
	lcd.init();
	lcd.drawText(0, 0, "Ready!");
	usart.init(0x33, true);
	usart.setTrigger(';');
	usart.send("test");
	setTimer1(0.005, onTimer1);

	while (1)
	{
		if (usart.triggered())
		{
			lcd.clear();
			lcd.drawText(0, 0, usart.buf);
			if (usart.buf[0])
			{
				usart.send(usart.buf);
				usart.sendbyte(strlen(usart.buf));
				usart.clear_buf();
			}
		}
		_delay_ms(500);
	}
}