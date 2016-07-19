
#include "utils.h"
#include "stepmotor.h"

int main()
{
	clock_begin();
	StepMotor motor;
	motor.set(2000, true);
	while (1)
	{
		motor.onloop();
	}
}