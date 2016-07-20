#ifndef command_h
#define command_h

// :a:b:send

#include "utils.h"
#include "lcd.h"
#include "humidity.h"
#include "usart.h"
#include "clock.h"
#include "stepmotor.h"
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

int addr_a = 0xfffe, addr_b = 0xfffe;
int got_addr = 0;

bool startswith(const char* buf, const char* str)
{
	return !strncmp(buf, str, strlen(str));
}

void checkCmd(USART& usart)
{
	// static long lasttime = 0;
	// long clk = clock();
	// if (clk - lasttime < 500)
	// 	return;

	// lasttime = clk;

	char tmp[64];
	bool received = false;
	if (usart.triggered())
	{
//		lcd.clear();
//		lcd.drawText(0, 0, pbuf);
//		usart.send(usart.buf);

		const char* pbuf = usart.buf;

		// if (usart.buf[0] == 0xfd)
		// if (usart.buf[0] == 0xfffd)
		if (usart.buf[0] & 0xfd == 0xfd)
		{
			// lcd.dis("works");
			// while (1);
			pbuf = usart.buf + 4;
		}

		if (false);
#if MCUID == 2
		else if (!strncmp(pbuf, "beep(", 5))
		{
			int n;
			sscanf(pbuf, "beep(%d)", &n);
			if (n < 1)
				n = 1;
			beep_b(n);
			received = true;
		}
		else if (!strncmp(pbuf, "dis(", 4))
		{
			const char *p = pbuf + 4;
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
		else if (!strncmp(pbuf, "#2222;", 6))
		{
			sprintf(tmp, "%ld\n%ld", clock(), clock_us());
			lcd.clear();
			lcd.dis(tmp);
		}
#elif MCUID == 1
		else if (!strncmp(pbuf, "light(", 6))
		{
			int n;
			sscanf(pbuf, "light(%d)", &n);
			light(n);
			received = true;
		}

		else if (!strncmp(pbuf, "switch(", 7))
		{
			int n;
			sscanf(pbuf, "switch(%d)", &n);
			led_switch(n);
			received = true;
		}

		else if (!strncmp(pbuf, "lightoff(", 9))
		{
			int n;
			sscanf(pbuf, "lightoff(%d)", &n);
			light(n, false);
			received = true;
		}
		else if (!strncmp(pbuf, "light_hex(", 10))
		{
			int n;
			sscanf(pbuf, "light_hex(%x)", &n);
			DDRA = 0xff;
			PORTA = n;
			received = true;
		}
		else if (!strncmp(pbuf, "#1111;", 6))
		{
			int humi, humi_m, temp, temp_m;
			humidity.read(humi, humi_m, temp, temp_m);
			sprintf(tmp, "dis(温度：%d.%d 。C\n湿度： %d.%d %%RH);", temp, temp_m, humi, humi_m);
			usart.send(tmp);
			received = true;
		}
		else if (!strncmp(pbuf, "#3333#", 6))
		{
			int us, clockwise;
			sscanf(pbuf, "#3333#%d#%d", &us, &clockwise);
			sprintf(tmp, "dis(步进电机\n速度：%d\n方向：%s);", us, clockwise ? "顺时针" : "逆时针");
			usart.send(tmp);
			motor.set(us, clockwise);
			received = true;
		}

#endif
		else if (!strncmp(pbuf, "loopback(", 9))
		{
			int n;
			sscanf(pbuf, "loopback(%d)", &n);
			usart.loopback(n);
			received = true;
		}
		else if (!strncmp(pbuf, "zigbee_ready(", 13))
		{
			int c = pbuf[13];
			if (c == 'a' && MCUID == 2 || c == 'b' && MCUID == 1)
			{
				if (MCUID == 1)
				{
					// addr_b = *(int*)(pbuf+16);
					addr_b = pbuf[16] << 8 | pbuf[17];
				}
				if (MCUID == 2)
				{
					// addr_a = *(int*)(pbuf+16);
					addr_a = pbuf[16] << 8 | pbuf[17];
				}
				received = true;
			}
		}
		else if (!strncmp(pbuf, "got(", 4))
		{
			int c = pbuf[4];
			if (c == 'a' && MCUID == 1 || c == 'b' && MCUID == 2)
			{
				got_addr = 1;
				received = true;
			}
		}

		if (received)
			usart.send(MCUID == 1 ? "a_recevied;" : "b_received");

		usart.clear_buf();
	}
}


#endif