
#define MCUID 2

#define DISPLAY_TEXT
char text[65] = {0};

#include "command.h"
#include "keyboard.h"

static char keys[] = "_123A456B789C*0#D";


int mode = 1;

//char tmp

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
			if (keys[keyid] == 'A')
			{
				mode = 1;
			}
			else if (keys[keyid] == 'B')
			{
				mode = 2;
			}
			else if (keys[keyid] == 'C')
			{
				text[0] = 0;
				lcd.clear();
			}
			else
			{
				switch (mode)
				{
				case 1:
					if (strlen(text) < 64)
					{
						char *p = text;
						for (; *p; ++p);
						*p++ = keys[keyid];
						*p = 0;
						lcd.clear();
						lcd.drawText(0, 0, text);
					}
					break;
				case 2:
					sprintf(text, "light(%d);", keys[keyid]-'0');
//					usart0.send(text);
					usart1.send(text);
					beep(1);
					break;
				}
			}
		}
		checkCmd(usart0);
		checkCmd(usart1);
		_delay_ms(5);
//		_delay_ms(500);
	}
}
