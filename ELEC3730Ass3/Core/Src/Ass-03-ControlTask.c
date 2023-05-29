/*
 * controlTask.c
 *
 *  Created on: May 21, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

enum State state = WELCOME;		// State of the system
Button btn_photo = {190, 115, 100, 30, "Photo"};
Button btn_cancel = {20, 190, 100, 30, "Cancel"};
Button btn_register = {190, 90, 100, 30, "Register"};
Button btn_login = {190, 140, 100, 30, "Login"};
Button key_display = {200, 90, 80, 20, ""};

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
					osMessagePut(fileSystemQueueHandle, CHECK_REGISTER_ID, osWaitForever);
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
				case (KEY_0):
					osMessagePut(renderQueueHandle, KEY_0, osWaitForever);
					break;
				case (KEY_1):
					osMessagePut(renderQueueHandle, KEY_1, osWaitForever);
					break;
				case (KEY_2):
					osMessagePut(renderQueueHandle, KEY_2, osWaitForever);
					break;
				case (KEY_3):
					osMessagePut(renderQueueHandle, KEY_3, osWaitForever);
					break;
				case (KEY_4):
					osMessagePut(renderQueueHandle, KEY_4, osWaitForever);
					break;
				case (KEY_5):
					osMessagePut(renderQueueHandle, KEY_5, osWaitForever);
					break;
				case (KEY_6):
					osMessagePut(renderQueueHandle, KEY_6, osWaitForever);
					break;
				case (KEY_7):
					osMessagePut(renderQueueHandle, KEY_7, osWaitForever);
					break;
				case (KEY_8):
					osMessagePut(renderQueueHandle, KEY_8, osWaitForever);
					break;
				case (KEY_9):
					osMessagePut(renderQueueHandle, KEY_9, osWaitForever);
					break;
			}
		}
		osDelay(100);
	}
}
