/*
 * Ass-03-messageTimer.c
 *
 *  Created on: May 22, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

void MessageTimerCallback(void const * argument)
{
	osMessagePut(stateQueueHandle, WELCOME, osWaitForever);
}
