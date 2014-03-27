#include "protocol.h"
#include "drivers/engine.h"

Command CommandSet[] =
{
	 { SetFlightParametersCommand, SetFlightParametersCommandHandlerProxy }
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

// Create Command
void CreateSetFlightParametersCommand(char* outputBuffer, unsigned char throttle, char rudderAngle, char elevatorAngle)
{
	outputBuffer[0] = SetFlightParametersCommand;
	outputBuffer[1] = throttle;
	outputBuffer[2] = rudderAngle;
	outputBuffer[3] = elevatorAngle;
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
}

void SetElevatorAngle (char elevatorAngle)
{
}
