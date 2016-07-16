
#include "utils.h"
#include "lcd.h"
#include "keyboard.h"
#include <string.h>

Chip chip;

#define beep beep_b

static char keys[] = "_123A456B789C*0#D";
	
int main()
{
	Keyboard keyboard;
	LCD lcd;
	lcd.init();
	char text[65] = {0};
	int old_num = 0;
	int num;
	while(1)
	{
		while ((num = keyboard.keyscan()) == old_num)
			_delay_ms(5);
		if (num > 0 && strlen(text) < 64)
		{
			char *p = text;
			for (; *p; ++p);
			*p++ = keys[num];
			*p = 0;
		}
		lcd.drawText(0, 0, text);
		old_num = num;
	}
}
