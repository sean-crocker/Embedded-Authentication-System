/*
 * Ass-03-keypadTask.c
 *
 *  Created on: May 22, 2023
 *      Author: c3307768
 */

#include "Ass-03.h"

extern enum State state;		// State of the system

void StartKeypadTask(void const * argument)
{
	uint16_t keys[4];
	uint8_t index = 0;
	osEvent event;							// Event structure to receive message from queue
	uint16_t display_text_x_pos = 0;

	while(1) {
		event = osMessageGet(keypadQueueHandle, osWaitForever);	// Wait and get message
		if (event.status == 0x10) {
			keys[index] = event.value.v;		// Get key input from message queue and add it to the array
			index++;
			char display[4] = "";
			switch (index) {
				case 1:
					display_text_x_pos = 234;
					break;
				case 2:
					display_text_x_pos = 229;
					break;
				case 3:
					display_text_x_pos = 223;
					break;
				case 4:
					display_text_x_pos = 218;
					break;
			}
			for (uint8_t i = 0; i < index; i++)
				sprintf(&display[i], "%d", keys[i]);

			// TODO: Add mutex
			BSP_LCD_DisplayStringAt(display_text_x_pos, (uint16_t)92, (uint8_t*)display, LEFT_MODE);

			if ((state == LOGIN_ID && index == 3) || ((state == REGISTER_PIN || state == LOGIN_PIN) && index == 4)) {
				for (uint8_t i = 0; i < index; i++) {
					keys[i] = 0;
			    }
			    index = 0;

			    if (state == LOGIN_ID) {
			      osMessagePut(stateQueueHandle, LOG_ID_OK, osWaitForever);
			      // TODO: Add invalid ID
			    } else {
			      osMessagePut(stateQueueHandle, WELCOME, osWaitForever);
			      // TODO: Add valid and invalid PINs
			    }
			}
		}
	}
}
