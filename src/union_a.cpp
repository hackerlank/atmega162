
#define MCUID 1

#include "command.h"

int main()
{
	usart0.init(0x33, true);
	usart0.setTrigger(';');
	usart1.init(0x33, true);
	usart1.setTrigger(';');
	light(1);
	while (1)
	{
		checkCmd(usart0);
		checkCmd(usart1);
		_delay_ms(500);
	}
}