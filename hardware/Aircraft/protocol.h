#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef void (*CommandHandler)(char* args);

enum Commands
{
	SetEngineThrottle = 1,
	SetRudderAngle,
	SetElevatorAngle
};

typedef struct Command
{
	enum Commands command;
	CommandHandler commandHandler;
} Command;

void InitProtocol ();
void HandleCommand(char* buffer);

#endif
