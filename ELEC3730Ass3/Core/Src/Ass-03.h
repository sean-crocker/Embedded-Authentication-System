/*
 * Ass-03.h
 *
 *  Created on: May 21, 2023
 *      Author: Sean Crocker
 */

#ifndef SRC_ASS_03_H_
#define SRC_ASS_03_H_

// Includes from freertos.c
#include "FreeRTOS.h"
#include "task.h"

// Includes from main.c
#include "main.h"
#include "cmsis_os.h"
#include "dcmi.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "sdio.h"
#include "spi.h"
#include "gpio.h"
#include "fsmc.h"

#include "openx07v_c_lcd.h"
#include "touch_panel.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Constants
#define BTN_HEIGHT 					30
#define BTN_WIDTH 					100
#define BTN_TEXT_Y_PADDING 			7

#define BTN_REGISTER_X_POS 			190
#define BTN_REGISTER_Y_POS 			90
#define BTN_REGISTER_TEXT_X_PADDING 6		// 190 + 6

#define BTN_LOGIN_X_POS 			190
#define BTN_LOGIN_Y_POS 			140
#define BTN_LOGIN_TEXT_X_PADDING 	22		// 190 + 22.5

#define BTN_PHOTO_X_POS 			190
#define BTN_PHOTO_Y_POS 			115
#define BTN_PHOTO_TEXT_X_PADDING 	22		// 190 + 22.5

#define BTN_CANCEL_X_POS 			20
#define BTN_CANCEL_Y_POS 			190
#define BTN_CANCEL_TEXT_X_PADDING 	17		// 20 + 17

#define KEY_DISPLAY_X_POS 			200
#define KEY_DISPLAY_Y_POS 			90
#define KEY_DISPLAY_HEIGHT 			20
#define KEY_DISPLAY_WIDTH 			80
#define KEY_BTN_SIZE 				20
#define KEY_BTN_X_POS 				200
#define KEY_BTN_Y_POS 				120

#define f_unmount(path) f_mount(0, path, 0)
#define f_size(fp) ((fp)->obj.objsize)

// Global Variables
//enum State {WELCOME, REGISTER_ID, REGISTER_PIN, LOGIN_ID, LOGIN_PIN};
enum State {WELCOME, REGISTER_ID, REGISTER_PIN, LOGIN_ID, LOGIN_PIN};
enum Command {FINISHED, REG_ID, REG_PIN, LOG_ID, LOG_ID_ERR, LOG_ID_OK, LOG_AUTH_ERR, LOG_AUTH_OK};

// Operating System Handles
extern osThreadId defaultTaskHandle;
extern osThreadId controlTaskHandle;
extern osThreadId lcdTaskHandle;
extern osThreadId touchPanelTaskHandle;
extern osThreadId keypadTaskHandle;
extern osMessageQId stateQueueHandle;
extern osMessageQId renderQueueHandle;
extern osMessageQId keypadQueueHandle;
extern osTimerId messageTimerHandle;
extern osMutexId cameraMutexHandle;
extern osMutexId sdMutexHandle;

// Functions
void StartDefaultTask(void const * argument);
void StartControlTask(void const * argument);
void StartLCDTask(void const * argument);
void StartTouchPanelTask(void const * argument);
void StartKeypadTask(void const * argument);
void StartFileSystemTask(void const * argument);
void MessageTimerCallback(void const * argument);

#endif /* SRC_ASS_03_H_ */
