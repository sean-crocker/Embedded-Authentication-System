/*
 * controlTask.c
 *
 *  Created on: May 21, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

enum State state = WELCOME;		// State of the system

void StartControlTask(void const * argument)
{
	osEvent event;												// Event structure to receive message from queue
	while(1) {
		event = osMessageGet(stateQueueHandle, osWaitForever);	// Wait and get message
		if (event.status == 0x10) {
			switch (event.value.v) {
				case (FINISHED):
					osTimerStop(messageTimerHandle);					// Stop the message timer
					osMessagePut(renderQueueHandle, FINISHED, osWaitForever);
					state = WELCOME;
					break;
				case (REG_ID):
					osMessagePut(renderQueueHandle, REG_ID, osWaitForever);
					//osMessagePut(sdQueueHandle, GET_USER_ID, osWaitForever);
					osMessagePut(fileSystemQueueHandle, 0, osWaitForever);
					state = REGISTER_ID;
					break;
				case (REG_PIN):
					osMessagePut(renderQueueHandle, REG_PIN, osWaitForever);
					state = REGISTER_PIN;
					break;
				case (LOG_ID):
					osMessagePut(renderQueueHandle, LOG_ID, osWaitForever);
					state = LOGIN_ID;
					break;
				// Display error message for id not registered and change state to welcome
				case (LOG_ID_ERR):
					osMessagePut(renderQueueHandle, LOG_ID_ERR, osWaitForever);
					osTimerStart(messageTimerHandle, 2000);			// Start the message timer
					break;
				// Display login screen with prompt to enter Pin and change state to login
				case (LOG_ID_OK):
					osMessagePut(renderQueueHandle, LOG_ID_OK, osWaitForever);
					state = LOGIN_PIN;
					break;
				// Display "Access Denied" for 2 seconds then change state to welcome
				case (LOG_AUTH_ERR):
					osMessagePut(renderQueueHandle, LOG_AUTH_ERR, osWaitForever);
					osTimerStart(messageTimerHandle, 2000);			// Start the message timer
					break;
				// Display "Access Granted" for 2 seconds then change state to welcome
				case (LOG_AUTH_OK):
					osMessagePut(renderQueueHandle, LOG_AUTH_OK, osWaitForever);
					osTimerStart(messageTimerHandle, 2000);			// Start the message timer
					break;
			}
		}
		osDelay(100);
	}
}
