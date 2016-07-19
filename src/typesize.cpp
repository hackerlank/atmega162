#include "utils.h"
#include "lcd.h"
#include <stdio.h>

int main()
{
	LCD lcd;
	lcd.init();
	char s[128];
	sprintf(s, "short: %d\n int: %d\n long: %d\n ", sizeof(short), sizeof(int), sizeof(long));
	lcd.dis(s);
	while (1);
}