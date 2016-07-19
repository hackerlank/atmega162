#ifndef command_h
#define command_h

// :a:b:send

#include "utils.h"
#include "lcd.h"
#include "humidity.h"
#include "usart.h"
#include "clock.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if MCUID == 2
LCD lcd;
#elif MCUID == 1
Humidity humidity;
#endif

#if MCUID == 1
#define beep beep_a
#else
#define beep beep_b
#endif

bool startswith(const char* buf, const char* str)
{
	return !strncmp(buf, str, strlen(str));
}

void checkCmd(USART& usart)
{
	char tmp[64];
	bool received = false;
	if (usart.triggered())
	{
//		lcd.clear();
//		lcd.drawText(0, 0, usart.buf);
//		usart.send(usart.buf);
		if (false);
#if MCUID == 2
		else if (!strncmp(usart.buf, "beep(", 5))
		{
			int n;
			sscanf(usart.buf, "beep(%d)", &n);
			if (n < 1)
				n = 1;
			beep_b(n);
			received = true;
		}
		else if (!strncmp(usart.buf, "dis(", 4))
		{
			const char *p = usart.buf + 4;
#ifndef DISPLAY_TEXT
			char *pt = tmp;
			while (*p && *p != ')')
			{
				*pt++ = *p++;				
			}
			*pt = 0;
			lcd.clear();
			lcd.dis(tmp);
#else
			char *pt = text;
			while (*p && *p != ')')
			{
				*pt++ = *p++;				
			}
			*pt = 0;
			lcd.clear();
			lcd.dis(text);
			text[0] = 0;
#endif
			received = true;
		}
		else if (!strncmp(usart.buf, "#2222;", 6))
		{
			sprintf(tmp, "%ld\n%ld", clock(), clock_us());
			lcd.clear();
			lcd.dis(tmp);
		}
#elif MCUID == 1
		else if (!strncmp(usart.buf, "light(", 6))
		{
			int n;
			sscanf(usart.buf, "light(%d)", &n);
			light(n);
			received = true;
		}

		else if (!strncmp(usart.buf, "switch(", 7))
		{
			int n;
			sscanf(usart.buf, "switch(%d)", &n);
			led_switch(n);
			received = true;
		}

		else if (!strncmp(usart.buf, "lightoff(", 9))
		{
			int n;
			sscanf(usart.buf, "lightoff(%d)", &n);
			light(n, false);
			received = true;
		}
		else if (!strncmp(usart.buf, "light_hex(", 10))
		{
			int n;
			sscanf(usart.buf, "light_hex(%x)", &n);
			DDRA = 0xff;
			PORTA = n;
			received = true;
		}
		else if (!strncmp(usart.buf, "#1111;", 6))
		{
			int humi, humi_m, temp, temp_m;
			humidity.read(humi, humi_m, temp, temp_m);
			sprintf(tmp, "dis(ÎÂ¶È£º%d.%d ¡£C\nÊª¶È£º %d.%d %%RH);", temp, temp_m, humi, humi_m);
			usart.send(tmp);
			received = true;
		}
#endif
		else if (!strncmp(usart.buf, "loopback(", 9))
		{
			int n;
			sscanf(usart.buf, "loopback(%d)", &n);
			usart.loopback(n);
			received = true;
		}

		if (received)
			usart.send(MCUID == 1 ? "a_recevied;" : "b_received");

		usart.clear_buf();
	}
}


#endif