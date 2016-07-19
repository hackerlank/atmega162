
#define MCUID 1

#include "command.h"

int main()
{
	clock_begin();
	usart1.init(0x33, true);
	usart1.setTrigger(';');
	usart1.send("mcua ready;");
	light(1);
	while (1)
	{
//		motor.onloop();
		checkCmd(usart1);
	}
}