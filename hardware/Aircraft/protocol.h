#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "ch.h"
#include "hal.h"
#include "stm32f10x.h"

typedef void (*CommandHandler)(char* args);

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

void HandleCommand(char* buffer);

// Create Command
void CreateSetFlightParametersCommand(char* outputBuffer, unsigned char throttle, char rudderAngle, char elevatorAngle);

// Command Proxy
void SetFlightParametersCommandHandlerProxy (char* buffer);

// Command Handlers
void SetFlightParametersCommandHandler (unsigned char throttle, char rudderAngle, char elevatorAngle);

// Controls
void SetEngineThrottle (unsigned char throttle);
void SetRudderAngle (char rudderAngle);
void SetElevatorAngle (char elevatorAngle);

#endif
