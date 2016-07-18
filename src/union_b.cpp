
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

	int old_num = 0;
	int num;
	while(1)
	{
		if ((num = keyboard.keyscan()) != old_num)
		{
			if (num > 0 && strlen(text) < 64)
			{
				char *p = text;
				for (; *p; ++p);
				*p++ = keys[num];
				*p = 0;
				lcd.clear();
				lcd.drawText(0, 0, text);
			}
		}
		old_num = num;
		checkCmd(usart0);
		checkCmd(usart1);
		_delay_ms(5);
//		_delay_ms(500);
	}
}
