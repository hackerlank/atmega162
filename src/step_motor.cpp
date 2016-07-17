
#include "utils.h"
#include "stepmotor.h"

Chip chip;

int main()
{
	StepMotor motor;
	while (1)
	{
		motor.step(64 * 3 * 3 * 4, 1500, true);
		_delay_ms(1000);
		motor.step(64 * 3 * 3 * 4, 1500, false);
		_delay_ms(1000);
	}
}