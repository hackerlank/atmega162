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

	virtual void init(int baud, bool inter);

	void setTrigger(char c)
	{
		trigger = c;
	}

	virtual void sendbyte(byte c);

	void send(const char *c)
	{
		while (*c)
		{
			sendbyte(*c);
			++c;
		}
	}

	virtual byte recvbyte();

	virtual void onRXCI()
	{
		byte read = recvbyte();
		if (read == trigger)
			_triggered = true;
		add2buf(read);
		if (_loopback)
			sendbyte(read);
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
	char buf[64];
//	int len;
	char *buf_tail, *buf_end;

protected:
	bool _triggered;
	bool _loopback;
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
			UDR0 = c;
	}

	virtual byte recvbyte()
	{
		while (!(UCSR1A & (1 << RXC1)));
		return UDR0;
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