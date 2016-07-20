#ifndef blink_h
#define blink_h

#include <avr/io.h>
#include <util/delay.h>

class Blink
{
public:
	Blink()
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
				if (_i & 8)
					_i = 0;
				DDRA = 0xff;
				PORTA = 1 << _i;
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