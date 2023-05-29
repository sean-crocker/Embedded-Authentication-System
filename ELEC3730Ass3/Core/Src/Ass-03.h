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
#include "dcmi_ov7670.h"
#include "touch_panel.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Constants
#define CAM_HEIGHT 240
#define CAM_WIDTH 320
#define CAM_BUFFER_LENGTH 320

#define LCD_X_CENTRE 240
#define TITLE_Y_POS 20
#define PROMPT_Y_POS 50

#define f_unmount(path) f_mount(0, path, 0)
#define f_size(fp) ((fp)->obj.objsize)

// TODO: Remove const keyword maybe
typedef struct {
	uint16_t x_pos;
	uint16_t y_pos;
	uint16_t width;
	uint16_t height;
	const char* text;
} Button;

// Global Variables
enum State {WELCOME, REGISTER_ID, REGISTER_PIN, LOGIN_ID, LOGIN_PIN};
//enum State {WELCOME, REGISTER, LOGIN};
enum Command {
	FINISHED,
	REG_ID,
	REG_PIN,
	LOG_ID,
	LOG_ID_ERR,
	LOG_ID_OK,
	LOG_AUTH_ERR,
	LOG_AUTH_OK,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
};

enum SDCommand {CHECK_LOGIN_ID, CHECK_LOGIN_PIN, CHECK_REGISTER_ID, SET_REGISTER_PIN};

enum Result {ID_OK, ID_ERR, PIN_OK, PIN_ERR};

struct command_object {
	enum Command command;
	enum Result result;
	enum State state;
	uint32_t key_value;
};

// Operating System Handles
extern osThreadId defaultTaskHandle;
extern osThreadId controlTaskHandle;
extern osThreadId lcdTaskHandle;
extern osThreadId touchPanelTaskHandle;
extern osThreadId keypadTaskHandle;
extern osThreadId fileSystemTaskHandle;
extern osThreadId cameraTaskHandle;
extern osMessageQId stateQueueHandle;
extern osMessageQId renderQueueHandle;
extern osMessageQId keypadQueueHandle;
extern osMessageQId fileSystemQueueHandle;
extern osTimerId messageTimerHandle;
extern osMutexId lcdMutexHandle;
extern osMutexId sdMutexHandle;
extern osSemaphoreId startSemHandle;

// Functions
void StartDefaultTask(void const * argument);
void StartControlTask(void const * argument);
void StartLCDTask(void const * argument);
void StartTouchPanelTask(void const * argument);
void StartKeypadTask(void const * argument);
void StartFileSystemTask(void const * argument);
void StartCameraTask(void const * argument);
void MessageTimerCallback(void const * argument);

#endif /* SRC_ASS_03_H_ */
