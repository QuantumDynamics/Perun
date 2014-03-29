#include "protocol.h"
#include "drivers/engine.h"

Command CommandSet[] =
{
	 { SetFlightParametersCommand, SetFlightParametersCommandHandlerProxy },
	 { RequestStatus, SetFlightParametersCommandHandlerProxy }
};

void HandleCommand(unsigned char* buffer)
{
	unsigned int i;

	for(i = 0; i < sizeof(CommandSet)/sizeof(Command); i++)
	{
		if(CommandSet[i].command == buffer[0])
		{
			CommandSet[i].commandHandler(++buffer);
			break;
		}
	}
}

// Command Proxy
void SetFlightParametersCommandHandlerProxy (unsigned char* buffer)
{
	unsigned char throttle = ((unsigned char*)buffer)[0];
	char rudderAngle = ((char*)buffer)[1];
	char elevatorAngle = ((char*)buffer)[2];

	SetFlightParametersCommandHandler(throttle, rudderAngle, elevatorAngle);
}

// Command Handler
void SetFlightParametersCommandHandler (unsigned char throttle, char rudderAngle, char elevatorAngle)
{

	SetEngineThrottle(throttle);
	SetRudderAngle(rudderAngle);
	SetElevatorAngle(elevatorAngle);
}

void SetEngineThrottle (unsigned char throttle)
{
	engineThrottle(throttle);
}

void SetRudderAngle (char rudderAngle)
{
	pwmEnableChannel(&ENGINE_PWM, 2, PWM_FRACTION_TO_WIDTH(&ENGINE_PWM, 20, 0) + rudderAngle);
}

void SetElevatorAngle (char elevatorAngle)
{
	pwmEnableChannel(&ENGINE_PWM, 1, PWM_FRACTION_TO_WIDTH(&ENGINE_PWM, 20, 0) + elevatorAngle);
}
