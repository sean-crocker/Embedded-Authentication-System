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
extern char id[4];
extern char pin[5];

uint32_t Buffer_Tx[512/4], Buffer_Rx[512/4];

FRESULT res; 						// FatFs function common result code
uint32_t byteswritten, bytesread; 	// File write/read counts
//BYTE buffer[BUFFER_SIZE];         	// Working buffer
char rtext[256]; 					// File read buffer

uint32_t current_user_id = 0;

void initialise()
{
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) != 0)							// Card detection status
		printf("ERROR: No card detect\n");
	if (retSD != 0)															// SD link I/O driver link status
		printf("ERROR: Linking of SD disk I/O driver failed\n");
	if ((res = f_mount(&SDFatFs, (TCHAR const*)SDPath, 1)) != FR_OK)		// Register the file system object to the module
		printf("ERROR: Could not mount SD card (%d).\n", res);
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

void read_user()
{
	if ((res = f_stat(id, &fno)) == FR_OK) {
		osMessagePut(stateQueueHandle, LOG_ID_OK, osWaitForever);
	}
	else if ((res = f_stat(id, &fno)) == FR_NO_FILE) {
		osMessagePut(stateQueueHandle, LOG_ID_ERR, osWaitForever);
	}
	else {
		printf("Error checking file for user: %d\r\n", res);
		osMessagePut(stateQueueHandle, LOG_ID_ERR, osWaitForever);
	}
}

void read_user_pin()
{
	char info[5];
	if((res = f_open(&MyFile, id, FA_READ)) != FR_OK)
		printf("ERROR: %s file Open for read Error: %d\r\n", file, res);
	res = f_read(&MyFile, info, 4, (void *)&bytesread);
	if (res != FR_OK) {
		printf("Error reading file: %d\r\n", res);
	}
	else if (pin != info) {
		osMessagePut(stateQueueHandle, LOG_AUTH_ERR, osWaitForever);
	}
	else {
		osMessagePut(stateQueueHandle, LOG_AUTH_OK, osWaitForever);
	}
}

void set_user_pin()
{
	// Open the text file object for writing
	if ((res = f_open(&MyFile, id, FA_CREATE_ALWAYS | FA_WRITE)) != FR_OK)
		printf("ERROR: File Open for write Error: %d\r\n", res);

	// Write data to the file
	res = f_write(&MyFile, pin, sizeof(pin), (void *)&byteswritten);
	if ((byteswritten < sizeof(pin)) || (res != FR_OK))
		printf("ERROR: File Write or EOF Error: %d\r\n", res);

	// Close the open text file
	f_close(&MyFile);
}

void set_next_user()
{
	if((res = f_open(&MyFile, file, FA_READ)) != FR_OK)
		printf("ERROR: %s file Open for read Error: %d\r\n", file, res);

	// Navigate to the end of the file
	f_lseek(&MyFile, f_size(&MyFile) - 1);

	int index = 4 - 1;
	//char line[4] = {0};

	while ((res = f_read(&MyFile, rtext, 3, (void *)&bytesread)) == FR_OK) {
		if (rtext[0] == '\n')
			break;
		id[index] = rtext[0];
		index--;
	}
	f_close(&MyFile);
	//id = line;
}

/*
void get_next_user()
{
	uint16_t line_count = 0;
	// Open the text file object for reading
	if ((res = f_open(&MyFile, file, FA_READ)) != FR_OK)
		printf("ERROR: %s file Open for read Error: %d\r\n", file, res);
	// Read the file line by line
	while (f_gets(rtext, sizeof(rtext), &MyFile) != NULL)
		line_count++;
	// Close the file
	f_close(&MyFile);
	current_user_id = line_count;
	//return line_count;
}
*/

void read_image(TCHAR *file)
{
	// Open the image file object with read access
	if ((res = f_open(&MyFile, file, FA_OPEN_EXISTING | FA_READ)) != FR_OK)
		printf("ERROR: %s file Open for read Error: %d\r\n", file, res);
	// Read the image data from the file

}

void StartFileSystemTask(void const * argument)
{
	osSemaphoreWait(startSemHandle, osWaitForever);
	initialise();
	osEvent event;												// Event structure to receive message from queue

	while(1) {
		event = osMessageGet(fileSystemQueueHandle, osWaitForever);	// Wait and get message
		if (event.status == 0x10) {
			switch (event.value.v) {
			case (CHECK_REGISTER_ID):		// Get latest ID
				set_next_user();
				break;
			case (SET_REGISTER_PIN):		// Write file for PIN
				set_user_pin();
				break;
			case (CHECK_LOGIN_ID):			// Read ID
				read_user();
				break;
			case (CHECK_LOGIN_PIN):			// Read PIN
				read_user_pin();
				break;
			}
		}
		osThreadYield();
	}
}
