#ifndef usart_h
#define usart_h

#include <avr/interrupt.h>

class USART;

extern USART usart;

class USART
{
public:
	USART()
	{
		clear_buf();
		trigger = 0xff;
		_triggered = false;
		_loopback = false;
	}

	void init(int baud, bool inter)
	{
		intr_method = inter;
		UBRR0H = (uint8)(baud >> 8);
		UBRR0L = (uint8)baud;
		UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (inter ? (1 << RXCIE0) : 0);
		UCSR0C = (1 << URSEL0) | (0 << USBS0) | (3 << UCSZ00);
		if (inter)
			sei();
	}

	void setTrigger(char c)
	{
		trigger = c;
	}

	void sendbyte(uint8 c)
	{
		while (!(UCSR0A & (1 << UDRE0)));
			UDR0 = c;
	}

	void send(const char *c)
	{
		while (*c)
		{
			sendbyte(*c);
			++c;
		}
	}

	void recvbyte()
	{
		while (!(UCSR0A & (1 << RXC0)));
		uint8 read = UDR0;
		if (read == trigger)
			_triggered = true;
		add2buf(read);
		if (_loopback)
			sendbyte(read);
	}

	virtual void onRXCI()
	{
		recvbyte();
	}

	bool triggered()
	{
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
	bool intr_method;
//	char buf[10240];
	char buf[128];
//	int len;
	char *buf_tail, *buf_end;

protected:
	bool _triggered;
	bool _loopback;
};

ISR(USART0_RXC_vect)
{
	usart.onRXCI();
}

#endif