/*
 * lcdTask.c
 *
 *  Created on: May 21, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

//extern enum State state;		// State of the system
//extern enum Command;

uint16_t get_string_width(const char* str)
{
	uint16_t charCount = 0;
	for (const char* p = str; *p != '\0'; p++) {
		charCount++;
	}
	return charCount * BSP_LCD_GetFont()->Width;
}

void drawButtonBeveled(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const char* text) {
	ili9325_WriteReg(LCD_REG_3, 0x1028);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);  // Set the button color

	// Draw the button body
	BSP_LCD_FillRect(x, y, width, height);

	// Draw the top bevel
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_DrawLine(x, y, x + width - 1, y);
	BSP_LCD_DrawLine(x, y + 1, x + width - 2, y + 1);

	// Draw the left bevel
	BSP_LCD_DrawLine(x, y, x, y + height - 1);
	BSP_LCD_DrawLine(x + 1, y, x + 1, y + height - 2);

	// Draw the bottom bevel
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawLine(x, y + height - 1, x + width - 1, y + height - 1);
	BSP_LCD_DrawLine(x, y + height - 2, x + width - 2, y + height - 2);

	// Draw the right bevel
	BSP_LCD_DrawLine(x + width - 1, y, x + width - 1, y + height - 1);
	BSP_LCD_DrawLine(x + width - 2, y, x + width - 2, y + height - 2);

	// Add the text
	BSP_LCD_DisplayStringAt(x + BTN_WIDTH/2 - get_string_width(text)/2, y + BTN_HEIGHT/2 - BSP_LCD_GetFont()->Height/2, (uint8_t *)text, LEFT_MODE);
}

void draw_button(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, const char* text) {
    ili9325_WriteReg(LCD_REG_3, 0x1028);
	BSP_LCD_FillCircle(x + radius, y + radius, radius);
    BSP_LCD_FillCircle(x + radius, y + height - radius - 1, radius);
    BSP_LCD_FillCircle(x + width - radius - 1, y + radius, radius);
    BSP_LCD_FillCircle(x + width - radius - 1, y + height - radius - 1, radius);

    BSP_LCD_FillRect(x + radius, y, width - 2 * radius, height);
    BSP_LCD_FillRect(x, y + radius, width, height - 2 * radius);

    // Add the text
	BSP_LCD_DisplayStringAt(x + BTN_WIDTH/2 - get_string_width(text)/2, y + BTN_HEIGHT/2 - BSP_LCD_GetFont()->Height/2, (uint8_t *)text, LEFT_MODE);
}

void display_welcome()
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	BSP_LCD_DisplayStringAt(191, 20, (uint8_t*)"WELCOME", LEFT_MODE);	// Display welcome statement

	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons

	drawButtonBeveled(BTN_REGISTER_X_POS, BTN_REGISTER_Y_POS, BTN_WIDTH, BTN_HEIGHT, "Register");
	drawButtonBeveled(BTN_LOGIN_X_POS, BTN_LOGIN_Y_POS, BTN_WIDTH, BTN_HEIGHT, "Login");
}

void display_keypad()
{
	draw_button(KEY_DISPLAY_X_POS, KEY_DISPLAY_Y_POS, KEY_DISPLAY_WIDTH, KEY_DISPLAY_HEIGHT, 5, "");
	uint16_t y_pos = KEY_BTN_Y_POS;
	char btn_number = 0;
	for (int row = 1; row <= 3; row++) {
		uint16_t x_pos = KEY_BTN_X_POS;
		for (int column = 1; column <= 3; column++) {
			draw_button(x_pos, y_pos, KEY_BTN_SIZE, KEY_BTN_SIZE, 2, ++btn_number);
			x_pos += 30;
		}
		y_pos += 30;
	}
	draw_button(230, 210, KEY_BTN_SIZE, KEY_BTN_SIZE, 2, '0');
}

uint16_t get_next_user()
{
	uint16_t line_count = 0;
	char rtext[256]; 					// File read buffer
	FIL MyFile; 						// File object
	FRESULT res; 						// FatFs function common result code
	// Open the text file object for reading
	if ((res = f_open(&MyFile, "storage_file.txt", FA_READ)) != FR_OK)
		printf("ERROR: %s file Open for read Error: %d\r\n", "storage_file.txt", res);
	// Read the file line by line
	while (f_gets(rtext, sizeof(rtext), &MyFile) != NULL)
		line_count++;
	// Close the file
	f_close(&MyFile);
	return line_count;
}

void display_registration(bool hasTakenPhoto)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	BSP_LCD_DisplayStringAt(184, 20, (uint8_t*)"REGISTER", LEFT_MODE);			// Display register statement

	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons

	// TODO: Read SD to get user ID
	char id[4];
	sprintf(id, "%03d", get_next_user());
	BSP_LCD_DisplayStringAt(240 - get_string_width(id)/2, 50, (uint8_t*)id, LEFT_MODE);			// Display User ID

	draw_button(BTN_CANCEL_X_POS, BTN_CANCEL_Y_POS, BTN_WIDTH, BTN_HEIGHT, 5, "Cancel");

	if (hasTakenPhoto)
		display_keypad();
	else
		draw_button(BTN_PHOTO_X_POS, BTN_PHOTO_Y_POS, BTN_WIDTH, BTN_HEIGHT, 5, "Photo");
}

void display_login(const char* text)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	BSP_LCD_DisplayStringAt(205, 20, (uint8_t*)"LOGIN", LEFT_MODE);		// Display login statement

	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons
	BSP_LCD_DisplayStringAt(240 - get_string_width(text)/2, 50, (uint8_t*)text, LEFT_MODE);
	display_keypad();
	draw_button(BTN_CANCEL_X_POS, BTN_CANCEL_Y_POS, BTN_WIDTH, BTN_HEIGHT, 5, "Cancel");
}

void update_display(enum State state)
{
	switch (state) {
		case (WELCOME):
			display_welcome();
			break;
		case (REGISTER_ID):
			display_registration(0);
			break;
		case (REGISTER_PIN):
			display_registration(1);
			break;
		case (LOGIN_ID):
			display_login("Enter ID:");
			break;
		case (LOGIN_PIN):
			display_login("Enter PIN:");
			break;
	}

}

void StartLCDTask(void const * argument)
{
	BSP_LCD_Init();							// Initialize the LCD
	BSP_LCD_DisplayOn();					// Enable the LCD
	osEvent event;							// Event structure to receive message from queue
	osSemaphoreWait(startSemHandle, osWaitForever);
	display_welcome();
	while(1) {
		event = osMessageGet(renderQueueHandle, osWaitForever);
		if (event.status == 0x10) {
			if (osMutexWait(lcdMutexHandle, osWaitForever) == osOK) {
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
						display_login("Enter ID:");
						break;
					case (LOG_ID_ERR):
						display_login("Invalid ID");
						break;
					case (LOG_ID_OK):
						display_login("Enter Prompt:");
						break;
					case (LOG_AUTH_ERR):
						display_login("Access Denied");
						break;
					case (LOG_AUTH_OK):
						display_login("Access Granted");
						break;
				}
			osMutexRelease(lcdMutexHandle);
			}
		}
		osDelay(100);
	}
}
