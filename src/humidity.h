#ifndef humidity_h
#define humidity_h

#include "utils.h"

class Humidity
{
public:
	void read(int& humi, int &humi_m, int& temp, int &temp_m)
	{
		byte b4, b3, b2, b1, b0;
		byte check;
		chip.pb(0, 0);
		_delay_ms(18);
		chip.pb(0, 1);
		_delay_us(20);
		chip.pb(0, 1);
		while (chip.pb(0));
		if (!chip.pb(0))
		{
			while (!chip.pb(0));
			while (chip.pb(0));
			b4 = readbyte();
			b3 = readbyte();
			b2 = readbyte();
			b1 = readbyte();
			b0 = readbyte();
			chip.pb(0, 1);

			check = b4 + b3 + b2 + b1;
			if (check == b0)
			{
				humi = b4;
				humi_m = b3;
				temp = b2;
				temp_m = b1;
				// humi = b4 << 8 | b3;
				// temp = b2 << 8 | b1;
			}
			else
			{
				humi = 0xee;
				temp = 0x00;
			}
		}
		else
		{
			humi = 0xff;
			temp = 0;
		}
//		chip.pb(0, 0); // trigger collecting
	}

	byte readbyte()
	{
		byte b;
		for (int i = 0; i < 8; ++i)
		{
			while (!chip.pb(0));
			_delay_us(40);
			b = b << 1 | chip.pb(0);
			while (chip.pb(0));
		}
		return b;
	}
};

#endif