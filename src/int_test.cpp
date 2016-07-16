
#include "utils.h"

Chip chip;

int main(void)
{
	int old_pe0 = -1;
	DDRA = 0xff;
	PORTA = 0;
	while (1)
	{
		int pe = chip.pe(0);
		if (pe == old_pe0)
		{
			if (pe)
				PORTA = 0;
			else
				PORTA = 0xff;
		}
		old_pe0 = pe;
		_delay_ms(5);
	}
}