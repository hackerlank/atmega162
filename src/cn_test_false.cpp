
#include "lcd.h"

int main()
{
	LCD lcd;
	lcd.init();
	lcd.drawText(0, 0, "中文");
	while (1);
}