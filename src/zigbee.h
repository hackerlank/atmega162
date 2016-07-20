#ifndef zigbee_h
#define zigbee_h

#include "usart.h"

class Zigbee
{
public:
	void command(const byte* s)
	{
		byte check = 0;
		for (int i = 0; i < 6; ++i)
			check += s[i];
		usart1.send(s, 6);
		usart1.sendbyte(check);
	}

	void send(const char* s)
	{
		usart1.send(s);
	}

	void restart()
	{
		const byte cmd[] = {0xfc, 0x00, 0x91, 0x87, 0x6a, 0x35};
		command(cmd);
	}

	bool set_coordinator()
	{
		const byte cmd[] = {0xfc, 0x00, 0x91, 0x09, 0xa9, 0xc9};
		const byte chk[] = {0x43, 0x6f, 0x6f, 0x72, 0x64, 0x3b, 0x00, 0x19};
		command(cmd);
		while (!usart1.triggered())
			_delay_ms(2);

		const byte *p1 = chk, *end = chk + 8;
		const char *p2 = usart1.buf;

		while (p1 < end)
		{
			if (*p1++ != *p2++)
			{
				usart1.clear_buf();
				return false;
			}
		}

		usart1.clear_buf();
		return true;
	}

	bool set_router()
	{
		const byte cmd[] = {0xfc, 0x00, 0x91, 0x0a, 0xba, 0xda};
		const byte chk[] = {0x52, 0x6f, 0x75, 0x74, 0x65, 0x3b, 0x00, 0x19};
		command(cmd);
		while (!usart1.triggered())
			_delay_ms(2);

		const byte *p1 = chk, *end = chk + 8;
		const char *p2 = usart1.buf;

		while (p1 < end)
		{
			if (*p1++ != *p2++)
			{
				usart1.clear_buf();
				return false;
			}
		}

		usart1.clear_buf();
		return true;
	}

	int panid(int id)
	{
		byte cmd[] = {0xfc, 0x02, 0x91, 0x01, 0xff, 0xfe};
		cmd[4] = (id & 0xff00) >> 8;
		cmd[5] = id & 0xff;
//		*(int*)(cmd+4) = id;
		command(cmd);
		while (!usart1.triggered())
			_delay_ms(2);
		int ret = usart1.buf[0] << 8 | usart1.buf[1];
		usart1.clear_buf();
		return ret;		
	}

	int panid()
	{
		const byte cmd[] = {0xfc, 0x00, 0x91, 0x03, 0xa3, 0xb3};
		command(cmd);
		while (!usart1.triggered())
			_delay_ms(2);
		int ret = usart1.buf[0] << 8 | usart1.buf[1];
		usart1.clear_buf();
		return ret;
	}

	int addr()
	{
		const byte cmd[] = {0xfc, 0x00, 0x91, 0x04, 0xc4, 0xd4};
		command(cmd);
		while (!usart1.triggered())
			_delay_ms(2);
		int ret = usart1.buf[0] << 8 | usart1.buf[1];
		usart1.clear_buf();
		return ret;
	}

	bool set_transmit_mode(int i)
	{
		byte cmd[] = {0xfc, 0x01, 0x91, 0x64, 0x58, 0xff};
		const byte chk[] = {0x06, 0x07, 0x08, 0x09, 0x0a};
		cmd[5] = i;
		command(cmd);
		while (!usart1.triggered())
			_delay_ms(2);

		const byte *p1 = chk, *end = chk + 5;
		const char *p2 = usart1.buf;

		while (p1 < end)
		{
			if (*p1++ != *p2++)
			{
				usart1.clear_buf();
				return false;
			}
		}

		usart1.clear_buf();
		return true;
	}

	int baud(int bps)
	{
		byte cmd[] = {0xfc, 0x01, 0x91, 0x06, 0xff, 0xf6};
		cmd[4] = bps;
		command(cmd);
		while (!usart1.triggered())
			_delay_ms(2);
		int ret = 0;
		for (int i = 0; i < 6; ++i)
			ret = ret * 10 + usart1.buf[i];
		usart1.clear_buf();
		return ret;
	}

	void send_force(const char* s)
	{
		bool success = false;
		do
		{
			usart1.send(s);
			for (int i = 0; i < 5; ++i)
			{
				if (usart1.triggered())
				{
					success = true;
					break;
				}
				_delay_us(200);
			}
		} while (!success);
	}
};

#endif