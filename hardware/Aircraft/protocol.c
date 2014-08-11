#include "protocol.h"
#include "drivers/engine.h"
#include "fc_nrf.h"
#include "drivers/MPU6050.h"
#include "chprintf.h"
#include "drivers/mpu.h"

#define PackFloat(f, arr, offset) arr[offset + 0] = ((uint8_t*)&f)[0];\
								  arr[offset + 1] = ((uint8_t*)&f)[1];\
								  arr[offset + 2] = ((uint8_t*)&f)[2];\
								  arr[offset + 3] = ((uint8_t*)&f)[3];

void FetchFromBufferProxy(unsigned char* buffer)
{
	palClearPad(GPIOC, GPIOC_LED4);
}

Command CommandSet[] =
{
	 { SetFlightParametersCommand, SetFlightParametersCommandHandlerProxy },
	 { RequestStatus, RequestStatusCommandHandlerProxy },
	 { FetchFromBuffer, FetchFromBufferProxy }
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

void RequestStatusCommandHandler(unsigned char * buffer)
{
	(void)buffer;
	uint8_t output[30] = {0};

	palSetPad(GPIOC, GPIOC_LED4);

	((StatusPayload*)output)->acceleration = readAcceleration();

	fc_put_ack_payload(output);

	//palClearPad(GPIOC, GPIOC_LED4);
}

void RequestStatusCommandHandlerProxy(unsigned char * buffer)
{
	RequestStatusCommandHandler(buffer);
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
