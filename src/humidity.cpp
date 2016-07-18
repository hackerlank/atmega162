
#include "utils.h"
#include "humidity.h"
#include "usart.h"
#include "timer.h"

Humidity humidity;

int humi, temp;

void onTimer1()
{
	humidity.read(humi, temp);
	usart0.sendword(humi);
	usart0.sendword(temp);
	usart0.sendbyte(0xaa);
}


int main()
{
	usart0.init(0x33, true);
	usart0.setTrigger(';');
	usart1.init(0x33, true);
	usart1.setTrigger(';');

	setTimer1(2, onTimer1);

	while(1);
}
