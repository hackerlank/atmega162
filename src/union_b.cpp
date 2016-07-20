
#define MCUID 2

#define DISPLAY_TEXT
char text[65] = {0};

#include "command.h"
#include "keyboard.h"
#include "clock.h"
#include "zigbee.h"

static char keys[] = "_123A456B789C*0#D";


int mode = 1;

char tmp[32];

int main()
{
	clock_begin();
	Keyboard keyboard;
	usart1.init(12, true);
	// usart1.setTriggerTime(60);
	lcd.init();
	Zigbee zigbee;
	_delay_ms(1000);
	lcd.dis("Connecting...");
//	usart1.send("zigbee_ready(b);");
	_delay_ms(50);
	while ((addr_b = zigbee.addr()) == 0xfffe)
	{
		_delay_ms(100);
	}
	lcd.dis("Waiting...");
//	usart1.send("zigbee_ready(b);");
	_delay_ms(50);
	while (addr_a == 0xfffe)
	{
		checkCmd(usart1);
		_delay_ms(100);
	}
	usart1.send("zigbee_ready(b);");
	sprintf(tmp, "Ready.\nADDR_A:%x\nADDR_B:%x", addr_a, addr_b);
	lcd.dis(tmp);
	// usart1.init(0x33, true);
//	usart1.setTrigger(';');

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
			else if (keys[keyid] == 'D')
			{
				strcat(text, ";");
				usart1.send(text);
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
					sprintf(tmp, "switch(%d);", keys[keyid]-'0');
//					usart0.send(text);
					usart1.send(tmp);
					// beep(1);
					break;
				}
			}
		}
		checkCmd(usart1);
		_delay_ms(5);
//		_delay_ms(500);
	}
}
