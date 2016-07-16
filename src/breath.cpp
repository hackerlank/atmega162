
#include <avr/io.h>

void breath()
{
	int cycle = 400;
	int i = 0;
	int direct = 1;
	DDRA = 1 << 3;
	PORTA = 0;
	while (1)
	{
		if (i == 0)
			direct = 1;
		else if (i == cycle)
			direct = -1;
		for (int j = 0; j < cycle; ++j)
			PORTA = (j < i) << 3;
		i += direct;
	}
}

int main(void)
{
	breath();
}