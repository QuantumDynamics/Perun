#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

void startRemoteControl(void);
void stopRemoteControl(void);

void setFlightParameters(unsigned char throttle, unsigned char rudder, unsigned char elevator);

#endif
