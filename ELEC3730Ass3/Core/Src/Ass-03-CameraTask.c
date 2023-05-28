/*
 * Ass-03-CameraTask.c
 *
 *  Created on: May 28, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

uint16_t camera_buffer[CAM_BUFFER_LENGTH];
uint16_t camera_buffer_all[CAM_HEIGHT/2][CAM_WIDTH];
int8_t FrameXferCplt = 0;
int8_t LineXferCplt = 0;
int16_t LineCounter = 0;
uint8_t dma_done = 1;

/*
 * Entire frame is scanned
 */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	FrameXferCplt = 1;
}

void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	FrameXferCplt = 1;
}

/*
 * Entire line is scanned
 */
void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	LineXferCplt = 1;
	LineCounter++;
}

void DMA_IT_Callback_Fn(DMA_HandleTypeDef *_hdma)
{
	//osSignalSet(cameraTaskHandle, 1);
	dma_done = 1;
}

/*
 * Saving half a frame
 */
void save()
{
	// HAL_DCMI_Start_DMA must have been called in circular DMA mode
	while(!FrameXferCplt) { }

	// Must switch to normal DMA
	switch_to_normal();
	LineXferCplt = 0;
	FrameXferCplt = 0;
	LineCounter = 0;
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS,
			(uint32_t)&camera_buffer_all[LineCounter][0], CAM_BUFFER_LENGTH/2);

	while (LineCounter < CAM_HEIGHT/2 - 1) {
		if (LineXferCplt) {
			HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS,
					(uint32_t)&camera_buffer_all[LineCounter][0], CAM_BUFFER_LENGTH/2);
			LineXferCplt = 0;
		}
	}
}

void write_to_file() {
	for (uint16_t i = 0; i < CAM_HEIGHT/2; i++) {
		res = f_write(&MyFile, &camera_buffer_all[i][0], CAM_WIDTH, (void*)&byeswritten);
		if ((byteswritten < CAM_BUFFER_LENGTH || (res != FR_OK))) {
			printf("ERROR: File Write or EOF Error: %d\r\n", res);
		}
	}
}

void read_from_file() {
	res = f_read(&MyFile, &camera_buffer_all[0][0], CAM_HEIGHT*CAM_WIDTH/2, (void*)&bytesread);
	if ((bytesread < filesize) || (res != FR_OK)) {
		printf("%s file Read or EOF Error: %d\r\n", file, res);
	}
}

/*
void StartCameraTask(void const * argument)
{
	osSemaphoreWait(startSemHandle, osWaitForever);
	//Set LCD direction
	ili9325_SetCursor(10, 10);

	// Prepare to write GRAM (0x22)
	LCD_IO_WriteReg(LCD_REG_34);

	// Start camera capture
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)camera_buffer, CAM_BUFFER_LENGTH / 2);

	// Set the window for the camera image
	ili9325_SetDisplayWindow(10, 10, CAM_HEIGHT/2, CAM_WIDTH/2);

	// Change update direction
	ili9325_WriteReg(LCD_REG_3, 0x1020);

	while (1) {
		if (osMutexWait(lcdMutexHandle, osWaitForever) == osOK) {
			// Check if line transfer has been complete
			if (LineXferCplt) {
				// Check if end of the frame, if so reset the cursor, frame complete, and line counter
				if ((LineCounter >= CAM_HEIGHT) && FrameXferCplt) {
				//if (FrameXferCplt || LineCounter >= CAM_HEIGHT) {
				//if (FrameXferCplt) {
					ili9325_SetCursor(10, 10);
					FrameXferCplt = 0;
					LineCounter = 0;
				}
				if (LineCounter < CAM_HEIGHT/2) {
					// Set start of line and get ready to write to LCD GRAM
					ili9325_SetCursor(10 + LineCounter, 10);
					LCD_IO_WriteReg(LCD_REG_34);
					// Converts uint16_t camera_buffer to uint8_t, so the actual length is BUFFER_LEN
					LCD_IO_WriteMultipleData((uint8_t *)camera_buffer, CAM_BUFFER_LENGTH);
				}
				// Converts uint16_t camera_buffer to uint32_t, so the actual length is BUFFER_LEN / 2
				HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)camera_buffer, CAM_BUFFER_LENGTH / 2);
				LineXferCplt = 0;
			}
			//osDelay(100);
			osMutexRelease(lcdMutexHandle);
		}
		osThreadYield();
	}
}
*/

void switch_to_circular()
{
	HAL_DCMI_Stop(&hdcmi);
	hdma_dcmi.Init.Mode = DMA_CIRCULAR;
	HAL_DMA_Init(&hdma_dcmi);
}

void switch_to_normal()
{
	HAL_DCMI_Stop(&hdcmi);
	hdma_dcmi.Init.Mode = DMA_NORMAL;
	HAL_DMA_Init(&hdma_dcmi);
}

void StartCameraTask(void const * argument)
{
	osSemaphoreWait(startSemHandle, osWaitForever);

	// Prepare to write GRAM (0x22)
	LCD_IO_WriteReg(LCD_REG_34);

	// Register the callback function
	HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_CPLT_CB_ID, DMA_IT_Callback_Fn);

	// Start camera capture
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)camera_buffer, CAM_BUFFER_LENGTH / 2);

	// Change update direction
	ili9325_WriteReg(LCD_REG_3, 0x1020);

	while (1) {
		if (osMutexWait(lcdMutexHandle, osWaitForever) == osOK) {
			// Check if line transfer has been complete
			if (LineXferCplt) {
				// Check if end of the frame, if so reset the cursor, frame complete, and line counter
				if (FrameXferCplt) {
					FrameXferCplt = 0;
					LineCounter = 0;
				}
				if (LineCounter < CAM_HEIGHT/2) {
					// Set start of line and get ready to write to LCD GRAM
					ili9325_SetCursor(10 + LineCounter, 10);
					LCD_IO_WriteReg(LCD_REG_34);
					// Converts uint16_t camera_buffer to uint8_t, so the actual length is BUFFER_LEN

					// 1. Old Way
					// LCD_IO_WriteMultipleData((uint8_t *)camera_buffer, CAM_BUFFER_LENGTH);

					// 2. Polling DMA
					//if (HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) camera_buffer,
					//		(uint32_t) &LCD_RAM, CAM_BUFFER_LENGTH/2) != HAL_OK)
					//	printf("Error.\n");
					//HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);

					// 3. Interrupt Mode DMA
					while (dma_done == 0) { }
					dma_done = 0;
					if (HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)camera_buffer,
							(uint32_t)&LCD_RAM, CAM_BUFFER_LENGTH/2) != HAL_OK)
						printf("Error.\n");
					osSignalWait(1, osWaitForever);		// TODO: Replace with semaphore

				}
				// Converts uint16_t camera_buffer to uint32_t, so the actual length is BUFFER_LEN / 2
				HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)camera_buffer, CAM_BUFFER_LENGTH / 2);
				LineXferCplt = 0;
			}
			//osDelay(100);
			osMutexRelease(lcdMutexHandle);
		}
		osThreadYield();
	}
}
