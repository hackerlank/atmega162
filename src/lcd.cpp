
#include "utils.h"
#include "lcd.h"

Chip chip;

#define beep beep_b

const char texts[][32] = {
	"Zhang",
	"Ri",
	"Yue",
	"Ming",
};

int main(void)
{    
	LCD lcd;
	lcd.init();
	while (1)
	{
		lcd.drawText(0, 0, texts[0]);
		lcd.drawText(1, 0, texts[1]);
		lcd.drawText(2, 0, texts[2]);
		lcd.drawText(3, 0, texts[3]);
	}
}
