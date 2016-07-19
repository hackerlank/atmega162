
#include "lcd.h"

int main()
{
	LCD lcd;
	lcd.init();
	lcd.drawText(0, 0, "жпнд");
	while (1);
}