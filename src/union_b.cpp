
#define MCUID 2

#include "command.h"
#include "keyboard.h"

static char keys[] = "_123A456B789C*0#D";

char text[65] = {0};

int main()
{
	Keyboard keyboard;
	lcd.init();
	lcd.drawText(0, 0, "Ready");
	usart0.init(0x33, true);
	usart0.setTrigger(';');
	usart1.init(0x33, true);
	usart1.setTrigger(';');

	int keyid;
	while(1)
	{
		if (keyboard.triggered(keyid))
		{
#if 1
			if (strlen(text) < 64)
			{
				char *p = text;
				for (; *p; ++p);
				*p++ = keys[keyid];
				*p = 0;
				lcd.clear();
				lcd.drawText(0, 0, text);
			}
#endif
#if 0
			sprintf(text, "light(%d);", keys[keyid]-'0');
			usart0.send(text);
			usart1.send(text);
#endif
		}
		checkCmd(usart0);
		checkCmd(usart1);
		_delay_ms(5);
//		_delay_ms(500);
	}
}
