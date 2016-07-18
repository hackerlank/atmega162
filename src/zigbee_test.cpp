
#include "utils.h"
#include "usart.h"

int main()
{
	usart0.init(0x33, true);
	usart0.setTrigger(';');
	usart1.init(0x33, true);
	usart1.setTrigger(';');
	while (1)
	{
		usart0.send("zigbee1 ok");
		usart1.send("zigbee1 ok");
		_delay_ms(1000);
	}
}