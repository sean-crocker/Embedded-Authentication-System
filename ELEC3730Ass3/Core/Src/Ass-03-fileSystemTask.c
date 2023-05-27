/*
 * Ass-03-fileSystemTask.c
 *
 *  Created on: May 28, 2023
 *      Author: Sean Crocker
 */

#include "Ass-03.h"

FATFS SDFatFs;						// File system object for SD card logical drive
FIL MyFile; 						// File object
DIR MyDirectory;					// Directory object
FILINFO fno;						// File information object
const TCHAR *file = "storage_file.txt";

uint32_t Buffer_Tx[512/4], Buffer_Rx[512/4];

FRESULT res; 						// FatFs function common result code
uint32_t byteswritten, bytesread; 	// File write/read counts
BYTE buffer[BUFFER_SIZE];         	// Working buffer
char rtext[256]; 					// File read buffer

void initialise()
{
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) != 0)							// Card detection status
		printf("ERROR: No card detect\n");
	if (retSD != 0)															// SD link I/O driver link status
		printf("ERROR: Linking of SD disk I/O driver failed\n");
	if ((res = f_mount(&SDFatFs, (TCHAR const*)SDPath, 1)) != FR_OK)		// Register the file system object to the module
		printf("ERROR: Could not mount SD card (%d).\n", res);
	if ((res = f_mkfs(SDPath, FM_FAT32, 4096, buffer, sizeof buffer)) != FR_OK)	// Format the drive
		printf("ERROR: Could not create FAT file system on SD card (%d).\n", res);
}

void read_user_id()
{
	// Open the text file object with read access
	if((res = f_open(&MyFile, file, FA_READ)) != FR_OK)
		printf("ERROR: %s file Open for read Error: %d\r\n", file, res);

	// Get the file size
	uint16_t filesize = f_size(&MyFile);

	// Read data from the file
	res = f_read(&MyFile, rtext, filesize, (void *)&bytesread);
	if ((bytesread < filesize) || (res != FR_OK))
		printf("%s file Read or EOF Error: %d\r\n", file, res);

	// Close the open text file
	f_close(&MyFile);

}

void write_user(TCHAR *file, TCHAR info[])
{
	// Open the text file object for writing
	if ((res = f_open(&MyFile, file, FA_CREATE_ALWAYS | FA_WRITE)) != FR_OK)
		printf("ERROR: File Open for write Error: %d\r\n", res);

	// Write data to the file
	res = f_write(&MyFile, info, sizeof(info), (void *)&byteswritten);
	if ((byteswritten < sizeof(info)) || (res != FR_OK))
		printf("ERROR: File Write or EOF Error: %d\r\n", res);

	// Close the open text file
	f_close(&MyFile);
}

uint32_t get_next_user()
{
	if((res = f_open(&MyFile, file, FA_READ)) != FR_OK)
		printf("ERROR: %s file Open for read Error: %d\r\n", file, res);

	// Navigate to the end of the file
	f_lseek(&MyFile, f_size(&MyFile) - 1);

	int index = BUFFER_SIZE - 1;
	char line[BUFFER_SIZE] = {0};

	while ((res = f_read(&MyFile, buffer, 7, (void *)&bytesread)) == FR_OK) {
		if (buffer[0] == '\n')
			break;
		line[index] = buffer[0];
		index--;
	}
	f_close(&MyFile);
	return line;
}

void StartFileSystemTask(void const * argument)
{
	initialise();
	osEvent event;												// Event structure to receive message from queue

	while(1) {
		event = osMessageGet(fileSystemQueueHandle, osWaitForever);	// Wait and get message
		if (event.status == 0x10) {
			switch (event.value.v) {
			case(0):
					get_next_user();
				break;
			}
		}
		osDelay(100);
	}
}
