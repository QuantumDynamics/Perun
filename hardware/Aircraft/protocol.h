#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "ch.h"
#include "hal.h"

typedef void (*CommandHandler)(unsigned char* args);

enum Commands
{
	SetEngineThrottleCommand = 1,
	SetRudderAngleCommand,
	SetElevatorAngleCommand,
	SetFlightParametersCommand
};

typedef struct Command
{
	enum Commands command;
	CommandHandler commandHandler;
} Command;

void HandleCommand(unsigned char* buffer);

// Command Proxy
void SetFlightParametersCommandHandlerProxy (unsigned char* buffer);

// Command Handlers
void SetFlightParametersCommandHandler (unsigned char throttle, char rudderAngle, char elevatorAngle);

// Controls
void SetEngineThrottle (unsigned char throttle);
void SetRudderAngle (char rudderAngle);
void SetElevatorAngle (char elevatorAngle);

// Create Command
inline void CreateSetFlightParametersCommand(unsigned char* outputBuffer, unsigned char throttle, char rudderAngle, char elevatorAngle)
{
	outputBuffer[0] = SetFlightParametersCommand;
	outputBuffer[1] = throttle;
	outputBuffer[2] = rudderAngle;
	outputBuffer[3] = elevatorAngle;
}

#endif
