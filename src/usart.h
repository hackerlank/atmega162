#ifndef usart_h
#define usart_h

#include <avr/interrupt.h>
#include <string.h>
#include "clock.h"

typedef void (*RecvCallback)(byte);

class USART
{
public:
	USART()
	{
		clear_buf();
		trigger_method = 0;
		trigger_time = 5;
		trigger = 0xff;
		_triggered = false;
		_loopback = false;
		recvCallback = 0;
	}

	virtual void init(int baud, bool inter);

	void setTriggerChar(char c)
	{
		trigger_method = 1;
		trigger = c;
	}
	void setTriggerTime(int ms)
	{
		trigger_method = 0;
		trigger_time = ms;
	}

	virtual void sendbyte(byte c);

	void send(const char *c)
	{
		while (*c)
			sendbyte(*c++);
	}

	void sendword(const uint16_t d)
	{
		sendbyte((d & 0xff00) >> 8);
		sendbyte(d & 0xff);
	}

	void send(const uchar *c)
	{
		while (*c)
			sendbyte(*c++);
	}

	void send(const byte* s, int len)
	{
		for (int i = 0; i < len; ++i)
			sendbyte(s[i]);
	}

	virtual byte recvbyte();

	virtual void onRXCI()
	{
		byte read = recvbyte();
		if (trigger_method == 1 && read == trigger)
			_triggered = true;
		add2buf(read);
		if (_loopback)
			sendbyte(read);
		if (recvCallback)
			recvCallback(read);
	}

	void setOnRecvData(RecvCallback f)
	{
		recvCallback = f;
	}

	bool triggered()
	{
		if (trigger_method == 0)
		{
			static long lasttime = 0;
			long clk = clock_ms();
			if (clk - lasttime >= trigger_time)
			{
				if (buf[0] && !strcmp(old_buf, buf))
				{
					_triggered = true;
				}
				strcpy(old_buf, buf);
				lasttime = clk;
			}
		}
		if (_triggered)
		{
			_triggered = false;
			return true;
		}
		return false;
	}

	void clear_buf()
	{
		buf[0] = 0;
		buf_tail = buf;
	}

	void loopback(bool val)
	{
		_loopback = val;
	}

protected:
	void add2buf(char c)
	{
		*buf_tail++ = c;
		*buf_tail = 0;
//		buf[len++] = c;
//		buf[len] = 0;
	}

public:
	char trigger;
	int trigger_time;
	int trigger_method;
	bool intr_method;
//	char buf[10240];
	char buf[64];
	char old_buf[64];
//	int len;
	char *buf_tail, *buf_end;

public:
	bool _triggered;
	bool _loopback;
	RecvCallback recvCallback;
};

class USART0 : public USART
{
public:
	virtual void init(int baud, bool inter)
	{
		intr_method = inter;
		UBRR0H = (byte)(baud >> 8);
		UBRR0L = (byte)baud;
		UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (inter ? (1 << RXCIE0) : 0);
		UCSR0C = (1 << URSEL0) | (0 << USBS0) | (3 << UCSZ00);
		if (inter)
			sei();
	}

	virtual void sendbyte(byte c)
	{
		while (!(UCSR0A & (1 << UDRE0)));
			UDR0 = c;
	}

	virtual byte recvbyte()
	{
		while (!(UCSR0A & (1 << RXC0)));
		return UDR0;
	}
};

class USART1 : public USART
{
public:
	virtual void init(int baud, bool inter)
	{
		intr_method = inter;
		UBRR1H = (byte)(baud >> 8);
		UBRR1L = (byte)baud;
		UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (inter ? (1 << RXCIE1) : 0);
		UCSR1C = (1 << URSEL1) | (0 << USBS1) | (3 << UCSZ10);
		if (inter)
			sei();
	}

	virtual void sendbyte(byte c)
	{
		while (!(UCSR1A & (1 << UDRE1)));
			UDR1 = c;
	}

	virtual byte recvbyte()
	{
		while (!(UCSR1A & (1 << RXC1)));
		return UDR1;
	}
};

#if SINGLE_FILE
USART0 usart0;
USART1 usart1;
#else
extern USART0 usart0;
extern USART1 usart1;
#endif

ISR(USART0_RXC_vect)
{
	usart0.onRXCI();
}

ISR(USART1_RXC_vect)
{
	usart1.onRXCI();
}


#endif