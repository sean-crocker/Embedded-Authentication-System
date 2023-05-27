/*
 * touchPanelTask.c
 *
 *  Created on: May 21, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

extern enum State state;		// State of the system

bool is_btn_touched(uint16_t corr_x_pos, uint16_t corr_y_pos, uint16_t btn_x_pos, uint16_t btn_y_pos)
{
	return (corr_x_pos >= btn_x_pos && corr_x_pos <= btn_x_pos + BTN_WIDTH &&
			corr_y_pos >= btn_y_pos && corr_y_pos <= btn_y_pos + BTN_HEIGHT);
}

void touch_keypad(uint16_t x, uint16_t y)
{
	//switch (display.x) {
	switch (x) {
		case 200 ... 220:		// First Column
			//switch (display.y) {
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
			//switch (display.y) {
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
			//switch (display.y) {
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

void StartTouchPanelTask(void const * argument)
{
	while (1) {
		getDisplayPoint(&display, Read_Ads7846(), &matrix);
		switch (state) {
			case (WELCOME):
				if (is_btn_touched(display.x, display.y, BTN_REGISTER_X_POS, BTN_REGISTER_Y_POS))		// Tell Control Task that register button has been pressed
					osMessagePut(stateQueueHandle, REGISTER_ID, osWaitForever);
				else if (is_btn_touched(display.x, display.y, BTN_LOGIN_X_POS, BTN_LOGIN_Y_POS))		// Tell Control Task that login button has been pressed
					osMessagePut(stateQueueHandle, LOGIN_ID, osWaitForever);
				break;
				/*
				if (display.x >= BTN_REGISTER_X_POS && display.x <= BTN_REGISTER_X_POS + BTN_WIDTH) {
					switch (display.y) {
						case BTN_REGISTER_Y_POS ... BTN_REGISTER_Y_POS + BTN_HEIGHT:
							// Tell Control Task that register button has been pressed
							osMessagePut(stateQueueHandle, REGISTER, osWaitForever);
							break;
						case BTN_LOGIN_Y_POS ... BTN_LOGIN_Y_POS + BTN_HEIGHT:
							// Tell Control Task that login button has been pressed
							osMessagePut(stateQueueHandle, LOGIN, osWaitForever);
							break;
					}
				}
				break;
				*/
			case (REGISTER_ID):
				if (is_btn_touched(display.x, display.y, BTN_PHOTO_X_POS, BTN_PHOTO_Y_POS))				// Tell Control Task that photo button has been pressed
					osMessagePut(stateQueueHandle, REGISTER_PIN, osWaitForever);
				else if (is_btn_touched(display.x, display.y, BTN_CANCEL_X_POS, BTN_CANCEL_Y_POS))		// Tell Control Task that cancel button has been pressed
					osMessagePut(stateQueueHandle, WELCOME, osWaitForever);
				break;
				/*
				if (display.x >= BTN_PHOTO_X_POS && display.x <= BTN_PHOTO_X_POS + BTN_WIDTH &&
						display.y >= BTN_PHOTO_Y_POS && display.y <= BTN_PHOTO_Y_POS + BTN_HEIGHT) {
					// TODO: Trigger for camera to take photo
					// Tell Control Task that photo button has been pressed
					osMessagePut(stateQueueHandle, REG_KEY, osWaitForever);
				}
				else if (cancel_btn_touched) {								// Tell Control Task that cancel button has been pressed
					osMessagePut(stateQueueHandle, WELCOME, osWaitForever);
				}
				else
					break;
				break;
				*/
			case (REGISTER_PIN):
			case (LOGIN_ID):
			case (LOGIN_PIN):
				touch_keypad(display.x, display.y);
				if (is_btn_touched(display.x, display.y, BTN_CANCEL_X_POS, BTN_CANCEL_Y_POS))			// Tell Control Task that cancel button has been pressed
					osMessagePut(stateQueueHandle, WELCOME, osWaitForever);
				break;
		}
		osDelay(100);
	}
}
