#ifndef command_h
#define command_h

// :a:b:send

#include "utils.h"
#include "lcd.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if MCUID == 2
LCD lcd;
#endif

#if MCUID == 1
#define beep beep_a
#else
#define beep beep_b
#endif

void checkCmd(USART& usart)
{
	char tmp[32];
	if (usart.triggered())
	{
//		lcd.clear();
//		lcd.drawText(0, 0, usart.buf);
		usart.send(usart.buf);

#if MCUID == 2
		if (!strncmp(usart.buf, "beep(", 5))
		{
			int n;
			sscanf(usart.buf, "beep(%d)", &n);
			if (n < 1)
				n = 1;
			beep_b(n);
		}
		if (!strncmp(usart.buf, "dis(", 4))
		{
			sscanf(usart.buf, "dis(%s", tmp);
			tmp[ strlen(tmp) - 2 ] = 0;
			lcd.clear();
			lcd.drawText(0, 0, tmp);
		}
#elif MCUID == 1
		if (!strncmp(usart.buf, "light(", 6))
		{
			int n;
			sscanf(usart.buf, "light(%d)", &n);
			light(n);
		}
		if (!strncmp(usart.buf, "lightoff(", 9))
		{
			int n;
			sscanf(usart.buf, "lightoff(%d)", &n);
			light(n, false);
		}
		if (!strncmp(usart.buf, "light_hex(", 10))
		{
			int n;
			sscanf(usart.buf, "light_hex(%x)", &n);
			DDRA = 0xff;
			PORTA = n;
		}
#endif
		if (!strncmp(usart.buf, "loopback(", 9))
		{
			int n;
			sscanf(usart.buf, "loopback(%d)", &n);
			usart.loopback(n);
		}

		usart.clear_buf();
	}
}


#endif