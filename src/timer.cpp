
#define MCUID 1

#include "utils.h"
#include "timer.h"

Chip chip;

void onTimer1()
{
	beep_a();
}

int main()
{
	setTimer1(2, onTimer1);
	while (1);
}
