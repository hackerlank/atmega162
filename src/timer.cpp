
#define MCUID 1

#include "utils.h"
#include "timer.h"

void onTimer1()
{
//	beep_a();
	led_switch(0);
}

int main()
{
	setTimer1(0.5, onTimer1);
//	setTimer1(2, onTimer1);
	while (1);
}
