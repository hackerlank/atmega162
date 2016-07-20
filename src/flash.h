#ifndef flash_h
#define flash_h

#include <avr/io.h>
#include <util/delay.h>

class Flash
{
public:
	Flash()
	{
		_run = false;
		_interval = 100;
	}

	void start(int interval)
	{
		_run = true;
		_i = 0;
		_interval = interval;
	}

	void stop()
	{
		_run = false;
	}

	void onloop()
	{
		if (_run)
		{
			static long lasttime = 0;
			long clk = clock();
			if (clk - lasttime >= _interval)
			{
				DDRA = 0xff;
				PORTA = _i % 2 ? 0xff : 0x00;
				++_i;
				lasttime = clk;
			}
		}
	}

	bool _run;
	int _interval;
	int _i;
};

#endif