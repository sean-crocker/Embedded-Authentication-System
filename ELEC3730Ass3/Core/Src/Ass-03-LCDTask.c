/*
 * lcdTask.c
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
//extern enum Command;
char id[4];
char pin[5];
uint8_t counter;

uint16_t get_text_pos(const char* str)
{
	uint16_t charCount = 0;
	for (const char* p = str; *p != '\0'; p++)
		charCount++;
	return LCD_X_CENTRE - (charCount * BSP_LCD_GetFont()->Width) / 2;
}

uint16_t get_btntext_pos(const char* str, uint16_t position, uint16_t dimension, uint16_t font_size)
{
	uint16_t charCount = 0;
	for (const char* p = str; *p != '\0'; p++)
		charCount++;
	return (position + dimension) / 2 - (charCount * font_size) / 2;
}

/*
void draw_button_bev(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const char* text) {
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
	BSP_LCD_DisplayStringAt(get_btntext_pos(text, x, width, BSP_LCD_GetFont()->Width), get_btntext_pos(text, y, height, BSP_LCD_GetFont()->Height), (uint8_t *)text, LEFT_MODE);
	//BSP_LCD_DisplayStringAt(x + BTN_WIDTH/2 - get_string_width(text)/2, y + BTN_HEIGHT/2 - BSP_LCD_GetFont()->Height/2, (uint8_t *)text, LEFT_MODE);
}
*/

void draw_button_bev(Button btn) {
	ili9325_WriteReg(LCD_REG_3, 0x1028);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);  // Set the button color

	// Draw the button body
	BSP_LCD_FillRect(btn.x_pos , btn.y_pos, btn.width, btn.height);

	// Draw the top bevel
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_DrawLine(btn.x_pos , btn.y_pos, btn.x_pos  + btn.width - 1, btn.y_pos);
	BSP_LCD_DrawLine(btn.x_pos , btn.y_pos + 1, btn.x_pos  + btn.width - 2, btn.y_pos + 1);

	// Draw the left bevel
	BSP_LCD_DrawLine(btn.x_pos , btn.y_pos, btn.x_pos , btn.y_pos + btn.height - 1);
	BSP_LCD_DrawLine(btn.x_pos  + 1, btn.y_pos, btn.x_pos  + 1, btn.y_pos + btn.height - 2);

	// Draw the bottom bevel
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawLine(btn.x_pos , btn.y_pos + btn.height - 1, btn.x_pos  + btn.width - 1, btn.y_pos + btn.height - 1);
	BSP_LCD_DrawLine(btn.x_pos , btn.y_pos + btn.height - 2, btn.x_pos  + btn.width - 2, btn.y_pos + btn.height - 2);

	// Draw the right bevel
	BSP_LCD_DrawLine(btn.x_pos  + btn.width - 1, btn.y_pos, btn.x_pos  + btn.width - 1, btn.y_pos + btn.height - 1);
	BSP_LCD_DrawLine(btn.x_pos  + btn.width - 2, btn.y_pos, btn.x_pos  + btn.width - 2, btn.y_pos + btn.height - 2);

	// Add the text
	BSP_LCD_DisplayStringAt(get_btntext_pos(btn.text, btn.x_pos , btn.width, BSP_LCD_GetFont()->Width), get_btntext_pos(btn.text, btn.y_pos, btn.height, BSP_LCD_GetFont()->Height), (uint8_t *)btn.text, LEFT_MODE);
	//BSP_LCD_DisplayStringAt(x + BTN_WIDTH/2 - get_string_width(text)/2, y + BTN_HEIGHT/2 - BSP_LCD_GetFont()->Height/2, (uint8_t *)text, LEFT_MODE);
}

void draw_button(Button btn, uint16_t radius) {
    ili9325_WriteReg(LCD_REG_3, 0x1028);
	BSP_LCD_FillCircle(btn.x_pos + radius, btn.y_pos + radius, radius);
    BSP_LCD_FillCircle(btn.x_pos + radius, btn.y_pos + btn.height - radius - 1, radius);
    BSP_LCD_FillCircle(btn.x_pos + btn.width - radius - 1, btn.y_pos + radius, radius);
    BSP_LCD_FillCircle(btn.x_pos + btn.width - radius - 1, btn.y_pos + btn.height - radius - 1, radius);

    BSP_LCD_FillRect(btn.x_pos + radius, btn.y_pos, btn.width - 2 * radius, btn.height);
    BSP_LCD_FillRect(btn.x_pos, btn.y_pos + radius, btn.width, btn.height - 2 * radius);

    // Add the text
	BSP_LCD_DisplayStringAt(get_btntext_pos(btn.text, btn.x_pos, btn.width, BSP_LCD_GetFont()->Width), get_btntext_pos(btn.text, btn.y_pos, btn.height, BSP_LCD_GetFont()->Height), (uint8_t *)btn.text, LEFT_MODE);
	//BSP_LCD_DisplayStringAt(btn.x_pos + BTN_WIDTH/2 - get_string_width(text)/2, btn.y_pos + BTN_HEIGHT/2 - BSP_LCD_GetFont()->Height/2, (uint8_t *)text, LEFT_MODE);
}

void display_welcome(Button btn_register, Button btn_login)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	//BSP_LCD_DisplayStringAt(191, 20, (uint8_t*)"WELCOME", LEFT_MODE);	// Display welcome statement
	BSP_LCD_DisplayStringAt(get_text_pos("WELCOME"), TITLE_Y_POS, (uint8_t*)"WELCOME", LEFT_MODE);	// Display welcome statement


	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons

	//draw_button_bev(BTN_REGISTER_X_POS, BTN_REGISTER_Y_POS, BTN_WIDTH, BTN_HEIGHT, "Register");
	//draw_button_bev(BTN_LOGIN_X_POS, BTN_LOGIN_Y_POS, BTN_WIDTH, BTN_HEIGHT, "Login");
	draw_button_bev(btn_register);
	draw_button_bev(btn_login);


}

void display_keypad(Button key_display)
{
	//draw_button(KEY_DISPLAY_X_POS, KEY_DISPLAY_Y_POS, KEY_DISPLAY_WIDTH, KEY_DISPLAY_HEIGHT, 5, "");
	draw_button(key_display, 5);

	//uint16_t y_pos = KEY_BTN_Y_POS;
	uint16_t y_pos = key_display.y_pos;
	char btn_number = 0;
	for (int row = 1; row <= 3; row++) {
		//uint16_t x_pos = KEY_BTN_X_POS;
		uint16_t x_pos = key_display.x_pos;
		for (int column = 1; column <= 3; column++) {
			Button key = {x_pos, y_pos, 20, 20, ++btn_number};
			//draw_button(x_pos, y_pos, KEY_BTN_SIZE, KEY_BTN_SIZE, 2, ++btn_number);
			draw_button(key, 2);
			x_pos += 30;
		}
		y_pos += 30;
	}
	Button key = {230, 210, 20, 20, '0'};
	draw_button(key, 2);
}

void update_keypad(Button key_display, char number)
{
	switch (state) {
	case (LOGIN_ID):
		id[counter] = number;
		counter++;
		key_display.text = id;
		BSP_LCD_DisplayStringAt(get_btntext_pos(key_display.text, key_display.x_pos, key_display.width, BSP_LCD_GetFont()->Width), get_btntext_pos(key_display.text, key_display.y_pos, key_display.height, BSP_LCD_GetFont()->Height), (uint8_t*)key_display.text, LEFT_MODE);
		if (counter == 3) {
			counter = 0;
			// Check if ID exists
			osMessagePut(fileSystemQueueHandle, CHECK_LOGIN_ID, osWaitForever);
		}
		break;
	case (REGISTER_PIN):
		pin[counter] = number;
		counter++;
//		int index;
//		for (index = 0; pin[i] != '\0'; i++) { }
//		pin[index] = number;

		key_display.text = pin;
		BSP_LCD_DisplayStringAt(get_btntext_pos(key_display.text, key_display.x_pos, key_display.width, BSP_LCD_GetFont()->Width), get_btntext_pos(key_display.text, key_display.y_pos, key_display.height, BSP_LCD_GetFont()->Height), (uint8_t*)key_display.text, LEFT_MODE);
		if (counter == 4) {
			// Assign current ID with PIN
			osMessagePut(fileSystemQueueHandle, SET_REGISTER_PIN, osWaitForever);

			// Clear array and display text
			memset(pin, '\0', sizeOf(pin));
			counter = 0;

//			for (uint8_t i = 0; i < counter; i++) {
//				pin[i] = 0;
//			}
//			counter = 0;

			key_display.text = "";
		}
		break;
	case (LOGIN_PIN):
		pin[counter] = number;
		counter++;
		key_display.text = pin;
		BSP_LCD_DisplayStringAt(get_btntext_pos(key_display.text, key_display.x_pos, key_display.width, BSP_LCD_GetFont()->Width), get_btntext_pos(key_display.text, key_display.y_pos, key_display.height, BSP_LCD_GetFont()->Height), (uint8_t*)key_display.text, LEFT_MODE);
		if (counter == 4) {
			// Check if PIN exists for ID
			osMessagePut(fileSystemQueueHandle, CHECK_LOGIN_PIN, osWaitForever);
			memset(id, '\0', sizeOf(id));
			memset(pin, '\0', sizeOf(pin));
			counter = 0;
		}
		break;
	default:
		printf("Error: Incorrect state\n");
	}
}

/*
 * TODO: Move to SDTask
 */
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

void display_registration(bool hasTakenPhoto, Button btn_photo, Button btn_cancel, Button key_display)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	//BSP_LCD_DisplayStringAt(184, 20, (uint8_t*)"REGISTER", LEFT_MODE);			// Display register statement
	BSP_LCD_DisplayStringAt(get_text_pos("REGISTER"), TITLE_Y_POS, (uint8_t*)"REGISTER", LEFT_MODE);	// Display welcome statement


	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons

	// TODO: Read SD to get user ID
	char id[4];
	sprintf(id, "%03d", get_next_user());
	//BSP_LCD_DisplayStringAt(240 - get_string_width(id)/2, 50, (uint8_t*)id, LEFT_MODE);			// Display User ID
	BSP_LCD_DisplayStringAt(get_text_pos(id), PROMPT_Y_POS, (uint8_t*)id, LEFT_MODE);			// Display User ID

	//draw_button(BTN_CANCEL_X_POS, BTN_CANCEL_Y_POS, BTN_WIDTH, BTN_HEIGHT, 5, "Cancel");
	draw_button(btn_cancel, 5);


	if (hasTakenPhoto)
		display_keypad(key_display);
	else
		//draw_button(BTN_PHOTO_X_POS, BTN_PHOTO_Y_POS, BTN_WIDTH, BTN_HEIGHT, 5, "Photo");
		draw_button(btn_photo, 5);

}

void display_login(const char* text, Button btn_cancel, Button key_display)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);										// Clear the LCD and set background to white
	BSP_LCD_SetFont(&Font20);											// Set the font to be used
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);								// Set the text colour to black
	//BSP_LCD_DisplayStringAt(205, 20, (uint8_t*)"LOGIN", LEFT_MODE);		// Display login statement
	BSP_LCD_DisplayStringAt(get_text_pos("LOGIN"), TITLE_Y_POS, (uint8_t*)"LOGIN", LEFT_MODE);		// Display login statement


	BSP_LCD_SetFont(&Font16);											// Set the font to be used for buttons
	//BSP_LCD_DisplayStringAt(240 - get_string_width(text)/2, 50, (uint8_t*)text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(get_text_pos(text), PROMPT_Y_POS, (uint8_t*)text, LEFT_MODE);
	display_keypad(key_display);
	//draw_button(BTN_CANCEL_X_POS, BTN_CANCEL_Y_POS, BTN_WIDTH, BTN_HEIGHT, 5, "Cancel");
	draw_button(btn_cancel, 5);
}

void StartLCDTask(void const * argument)
{
	BSP_LCD_Init();							// Initialize the LCD
	BSP_LCD_DisplayOn();					// Enable the LCD
	osEvent event;							// Event structure to receive message from queue
	osSemaphoreWait(startSemHandle, osWaitForever);
	display_welcome(btn_register, btn_login);
	while(1) {
		event = osMessageGet(renderQueueHandle, osWaitForever);
		if (event.status == 0x10) {
			if (osMutexWait(lcdMutexHandle, osWaitForever) == osOK) {
				switch (event.value.v) {
					case (FINISHED):
						display_welcome(btn_register, btn_login);
						break;
					case (REG_ID):
						display_registration(0, btn_cancel, btn_photo, key_display);
						break;
					case (REG_PIN):
						display_registration(1, btn_cancel, btn_photo, key_display);
						break;
					case (LOG_ID):
						display_login("Enter ID:", btn_cancel, key_display);
						break;
					case (LOG_ID_ERR):
						display_login("Invalid ID", btn_cancel, key_display);
						break;
					case (LOG_ID_OK):
						display_login("Enter PIN:", btn_cancel, key_display);
						break;
					case (LOG_AUTH_ERR):
						display_login("Access Denied", btn_cancel, key_display);
						break;
					case (LOG_AUTH_OK):
						display_login("Access Granted", btn_cancel, key_display);
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
			osMutexRelease(lcdMutexHandle);
			}
		}
		osDelay(100);
	}
}
