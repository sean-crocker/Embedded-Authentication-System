/*
 * lcdTask.c
 *
 *  Created on: May 21, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

//extern enum State state;		// State of the system
extern enum Command;

void display_welcome()
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	BSP_LCD_DisplayStringAt(191, 20, (uint8_t*)"WELCOME", LEFT_MODE);	// Display welcome statement

	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons

	// TODO: Input Live Camera

	BSP_LCD_DrawRect(BTN_REGISTER_X_POS, BTN_REGISTER_Y_POS, BTN_WIDTH, BTN_HEIGHT);
	BSP_LCD_DisplayStringAt((BTN_REGISTER_X_POS + BTN_REGISTER_TEXT_X_PADDING),
			(BTN_REGISTER_Y_POS + BTN_TEXT_Y_PADDING), (uint8_t*)"Register", LEFT_MODE);

	BSP_LCD_DrawRect(BTN_LOGIN_X_POS, BTN_LOGIN_Y_POS, BTN_WIDTH, BTN_HEIGHT);
	BSP_LCD_DisplayStringAt((BTN_LOGIN_X_POS + BTN_LOGIN_TEXT_X_PADDING),
			(BTN_LOGIN_Y_POS + BTN_TEXT_Y_PADDING), (uint8_t*)"Login", LEFT_MODE);
}

void display_keypad()
{
	// TODO: Change if live preview is cleared
	//for (uint16_t y = 90; y <= 230; y++) {
	//	BSP_LCD_ClearStringLine(y);
	//}

	BSP_LCD_DrawRect(KEY_DISPLAY_X_POS, KEY_DISPLAY_Y_POS, KEY_DISPLAY_WIDTH, KEY_DISPLAY_HEIGHT);
	uint16_t y_pos = KEY_BTN_Y_POS;
	uint8_t btn_number = 0;
	char key_value[1];
	for (int row = 1; row <= 3; row++) {
		uint16_t x_pos = KEY_BTN_X_POS;
		for (int column = 1; column <= 3; column++) {
			BSP_LCD_DrawRect(x_pos, y_pos, KEY_BTN_SIZE, KEY_BTN_SIZE);
			sprintf(key_value, "%d", ++btn_number);
			BSP_LCD_DisplayStringAt((x_pos + 4), (y_pos + 2), (uint8_t*)key_value, LEFT_MODE);
			x_pos += 30;
		}
		y_pos += 30;
	}
	BSP_LCD_DrawRect(230, 210, KEY_BTN_SIZE, KEY_BTN_SIZE);
	BSP_LCD_DisplayStringAt((230 + 4), (210 + 2), (uint8_t*)"0", LEFT_MODE);
}

void display_registration(bool hasTakenPhoto)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	BSP_LCD_DisplayStringAt(184, 20, (uint8_t*)"REGISTER", LEFT_MODE);			// Display register statement

	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons

	// TODO: Read SD to get user ID
	BSP_LCD_DisplayStringAt(223, 50, (uint8_t*)"000", LEFT_MODE);					// Display User ID

	// TODO: Input Live Camera

	BSP_LCD_DrawRect(BTN_CANCEL_X_POS, BTN_CANCEL_Y_POS, BTN_WIDTH, BTN_HEIGHT);
	BSP_LCD_DisplayStringAt((BTN_CANCEL_X_POS + BTN_CANCEL_TEXT_X_PADDING),
			(BTN_CANCEL_Y_POS + BTN_TEXT_Y_PADDING), (uint8_t*)"Cancel", LEFT_MODE);

	if (hasTakenPhoto)
		display_keypad();
	else {
		BSP_LCD_DrawRect(BTN_PHOTO_X_POS, BTN_PHOTO_Y_POS, BTN_WIDTH, BTN_HEIGHT);
		BSP_LCD_DisplayStringAt((BTN_PHOTO_X_POS + BTN_PHOTO_TEXT_X_PADDING),
				(BTN_PHOTO_Y_POS + BTN_TEXT_Y_PADDING), (uint8_t*)"Photo", LEFT_MODE);
	}
}

void display_login(enum Command command)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	BSP_LCD_DisplayStringAt(205, 20, (uint8_t*)"LOGIN", LEFT_MODE);				// Display login statement

	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons

	//char prompt[] = hasID ? "Enter Pin" : "Enter ID";
	//BSP_LCD_DisplayStringAt(210, 50, (uint8_t*)prompt, CENTER_MODE);

	switch (command) {
		case (LOG_ID):
			BSP_LCD_DisplayStringAt(196, 50, (uint8_t*)"Enter ID", LEFT_MODE);		// Prompt to enter user ID
			// TODO: Input Live Camera
			break;
		case (LOG_ID_ERR):
			BSP_LCD_SetTextColor(LCD_COLOR_RED);							// Set the text colour to red
			BSP_LCD_DisplayStringAt(174, 50, (uint8_t*)"ID Not Valid", LEFT_MODE);
			// TODO: Input Live Camera
			break;
		case (LOG_ID_OK):
			BSP_LCD_DisplayStringAt(190, 50, (uint8_t*)"Enter PIN", LEFT_MODE);		// Prompt to enter user PIN
			// TODO: Read photo from SD and display on screen
			break;
		case (LOG_AUTH_ERR):
			BSP_LCD_SetTextColor(LCD_COLOR_RED);							// Set the text colour to red
			BSP_LCD_DisplayStringAt(168, 50, (uint8_t*)"Access Denied", LEFT_MODE);
			// TODO: Read photo from SD and display on screen
			break;
		case (LOG_AUTH_OK):
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);							// Set the text colour to green
			BSP_LCD_DisplayStringAt(163, 50, (uint8_t*)"Access Granted", LEFT_MODE);
			// TODO: Read photo from SD and display on screen
			break;
		default:
			printf("Error displaying login screen.\n");
			break;
	}

	display_keypad();

	BSP_LCD_DrawRect(BTN_CANCEL_X_POS, BTN_CANCEL_Y_POS, BTN_WIDTH, BTN_HEIGHT);
	BSP_LCD_DisplayStringAt((BTN_CANCEL_X_POS + BTN_CANCEL_TEXT_X_PADDING),
			(BTN_CANCEL_Y_POS + BTN_TEXT_Y_PADDING), (uint8_t*)"Cancel", LEFT_MODE);
}

void StartLCDTask(void const * argument)
{
	BSP_LCD_Init();							// Initialize the LCD
	BSP_LCD_DisplayOn();					// Enable the LCD
	TouchPanel_Calibrate();					// Touch Panel configuration
	osEvent event;							// Event structure to receive message from queue
	display_welcome();
	while(1) {
		event = osMessageGet(renderQueueHandle, osWaitForever);
		if (event.status == 0x10) {
			switch (event.value.v) {
				case (FINISHED):
					display_welcome();
					break;
				case (REG_ID):
					display_registration(0);
					break;
				case (REG_PIN):
					display_registration(1);
					break;
				case (LOG_ID):
					display_login(LOG_ID);
					break;
				case (LOG_ID_ERR):
					display_login(LOG_ID_ERR);
					break;
				case (LOG_ID_OK):
					display_login(LOG_ID_OK);
					break;
				case (LOG_AUTH_ERR):
					display_login(LOG_AUTH_ERR);
					break;
				case (LOG_AUTH_OK):
					display_login(LOG_AUTH_OK);
					break;
			}
		}
		osDelay(100);
	}
}
