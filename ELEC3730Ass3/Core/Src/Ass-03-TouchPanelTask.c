/*
 * touchPanelTask.c
 *
 *  Created on: May 21, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

extern enum State state;		// State of the system
extern Button btn_photo;
extern Button btn_cancel;
extern Button btn_register;
extern Button btn_login;
extern Button key_display;

bool is_btn_touched(uint16_t corr_x_pos, uint16_t corr_y_pos, Button btn)
{
	return (corr_x_pos >= btn.x_pos && corr_x_pos <= btn.x_pos + btn.width &&
			corr_y_pos >= btn.y_pos && corr_y_pos <= btn.y_pos + btn.height);
}

/*
void touch_keypad(uint16_t x, uint16_t y)
{
	switch (x) {
		case 200 ... 220:		// First Column
			switch (y) {
				case 120 ... 140:	// First Row
					// Button 1 Pressed
					osMessagePut(keypadQueueHandle, 1, osWaitForever);
					break;
				case 150 ... 170:	// Second Row
					// Button 4 Pressed
					osMessagePut(keypadQueueHandle, 4, osWaitForever);
					break;
				case 180 ... 200:	// Third Row
					// Button 7 Pressed
					osMessagePut(keypadQueueHandle, 7, osWaitForever);
					break;
			}
			break;
		case 230 ... 250:		// Second Column
			switch (y) {
				case 120 ... 140:	// First Row
					// Button 2 Pressed
					osMessagePut(keypadQueueHandle, 2, osWaitForever);
					break;
				case 150 ... 170:	// Second Row
					// Button 5 Pressed
					osMessagePut(keypadQueueHandle, 5, osWaitForever);
					break;
				case 180 ... 200:	// Third Row
					// Button 8 Pressed
					osMessagePut(keypadQueueHandle, 8, osWaitForever);
					break;
				case 210 ... 230:	// Fourth Row
					// Button 0 Pressed
					osMessagePut(keypadQueueHandle, 0, osWaitForever);
					break;
			}
			break;
		case 260 ... 280:		// Third Column
			switch (y) {
				case 120 ... 140:	// First Row
					// Button 3 Pressed
					osMessagePut(keypadQueueHandle, 3, osWaitForever);
					break;
				case 150 ... 170:	// Second Row
					// Button 6 Pressed
					osMessagePut(keypadQueueHandle, 6, osWaitForever);
					break;
				case 180 ... 200:	// Third Row
					// Button 9 Pressed
					osMessagePut(keypadQueueHandle, 9, osWaitForever);
					break;
			}
			break;
	}
}
*/

void touch_keypad(uint16_t x, uint16_t y)
{
	switch (x) {
		case 200 ... 220:		// First Column
			switch (y) {
				case 120 ... 140:	// First Row
					// Button 1 Pressed
					osMessagePut(stateQueueHandle, KEY_1, osWaitForever);
					break;
				case 150 ... 170:	// Second Row
					// Button 4 Pressed
					osMessagePut(stateQueueHandle, KEY_4, osWaitForever);
					break;
				case 180 ... 200:	// Third Row
					// Button 7 Pressed
					osMessagePut(stateQueueHandle, KEY_7, osWaitForever);
					break;
			}
			break;
		case 230 ... 250:		// Second Column
			switch (y) {
				case 120 ... 140:	// First Row
					// Button 2 Pressed
					osMessagePut(stateQueueHandle, KEY_2, osWaitForever);
					break;
				case 150 ... 170:	// Second Row
					// Button 5 Pressed
					osMessagePut(stateQueueHandle, KEY_5, osWaitForever);
					break;
				case 180 ... 200:	// Third Row
					// Button 8 Pressed
					osMessagePut(stateQueueHandle, KEY_8, osWaitForever);
					break;
				case 210 ... 230:	// Fourth Row
					// Button 0 Pressed
					osMessagePut(stateQueueHandle, KEY_0, osWaitForever);
					break;
			}
			break;
		case 260 ... 280:		// Third Column
			switch (y) {
				case 120 ... 140:	// First Row
					// Button 3 Pressed
					osMessagePut(stateQueueHandle, KEY_3, osWaitForever);
					break;
				case 150 ... 170:	// Second Row
					// Button 6 Pressed
					osMessagePut(stateQueueHandle, KEY_6, osWaitForever);
					break;
				case 180 ... 200:	// Third Row
					// Button 9 Pressed
					osMessagePut(stateQueueHandle, KEY_9, osWaitForever);
					break;
			}
			break;
	}
}

void StartTouchPanelTask(void const * argument)
{
	TouchPanel_Calibrate();					// Touch Panel configuration
	osSemaphoreRelease(startSemHandle);
	while (1) {
		getDisplayPoint(&display, Read_Ads7846(), &matrix);
		switch (state) {
			case (WELCOME):
				if (is_btn_touched(display.x, display.y, btn_register))		// Tell Control Task that register button has been pressed
					osMessagePut(stateQueueHandle, REG_ID, osWaitForever);
				else if (is_btn_touched(display.x, display.y, btn_login))		// Tell Control Task that login button has been pressed
					osMessagePut(stateQueueHandle, LOG_ID, osWaitForever);
				break;
			case (REGISTER_ID):
				if (is_btn_touched(display.x, display.y, btn_photo))				// Tell Control Task that photo button has been pressed
					osMessagePut(stateQueueHandle, REG_PIN, osWaitForever);
				else if (is_btn_touched(display.x, display.y, btn_cancel))		// Tell Control Task that cancel button has been pressed
					osMessagePut(stateQueueHandle, FINISHED, osWaitForever);
				break;
			case (REGISTER_PIN):
			case (LOGIN_ID):
			case (LOGIN_PIN):
				touch_keypad(display.x, display.y);
				if (is_btn_touched(display.x, display.y, btn_cancel))			// Tell Control Task that cancel button has been pressed
					osMessagePut(stateQueueHandle, FINISHED, osWaitForever);
				break;
		}
		osDelay(100);
	}
}
