#ifndef lcd_h
#define lcd_h

#include "utils.h"

class LCD
{
public:
	void init()
	{
		DDRA = 0xff;
		PORTA = 0xff;
		rs(1);
		rw(1);
		en(1);
		_delay_ms(30);

		wcmd(0x0c, 1);
		nop();
		wcmd(0x06, 1);
		nop();
		wcmd(0x01, 1);
		nop();
	}

	void clear()
	{
		wcmd(0x34, 1);
		wcmd(0x30, 1);
		wcmd(0x01, 1);
	}

	void wcmd(uchar c, bool _wait)
	{
		if (_wait)
			wait();
		rs(0);
		rw(0);
		en(0);
		PORTA = c;
		en(1);
		en(0);
	}

	void wdata(uchar c)
	{
		wait();
		rs(1);
		rw(0);
		en(0);
		PORTA = c;
		en(1);
		en(0);
	}

	void pos(int x, int y)
	{
		static const int rows[] = {0x80, 0x90, 0x88, 0x98};
		wcmd(rows[x] + y, 1);
	}

	void show(bool _show)
	{
		wcmd(_show ? 0x0c : 0x08, 1);
	}
	

	void drawText(int x, int y, const char* str)
	{
		pos(x, y);
		for (const char *p = str; *p; ++p)
			wdata(*p);
	}

protected:
	void wait()
	{
		busy();
		rs(0);
		rw(1);
		en(1);
		while (busy());
		en(0);
		DDRA |= (1 << 7);
	}

	void rs(int val)
	{
		chip.pe(0, val);
	}
	void rw(int val)
	{
		chip.pe(1, val);
	}
	void en(int val)
	{
		chip.pe(2, val);
	}

	bool rs()
	{
		return chip.pe(0);
	}
	bool rw()
	{
		return chip.pe(1);
	}
	bool en()
	{
		return chip.pe(2);
	}
	bool busy()
	{
		return chip.pa(7);
	}
};

#endif
