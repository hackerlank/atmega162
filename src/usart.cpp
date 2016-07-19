
#include "utils.h"
#include "lcd.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>

LCD lcd;
USART usart;

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
			usart.clear_buf();
		}
		_delay_ms(500);
	}
}