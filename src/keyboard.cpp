
#include "utils.h"
#include "keyboard.h"

Chip chip;

#define beep beep_b

static char keys[] = "_123A456B789C*0#D";
	
int main()
{
	Keyboard keyboard;
	while(1)
	{
		int num = keyboard.keyscan();
		beep(num);
	}
}
