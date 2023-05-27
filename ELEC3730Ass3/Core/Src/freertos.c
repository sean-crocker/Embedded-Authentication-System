/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId controlTaskHandle;
osThreadId lcdTaskHandle;
osThreadId touchPanelTaskHandle;
osThreadId keypadTaskHandle;
osThreadId fileSystemTaskHandle;
osMessageQId stateQueueHandle;
osMessageQId renderQueueHandle;
osMessageQId keypadQueueHandle;
osMessageQId fileSystemQueueHandle;
osTimerId messageTimerHandle;
osMutexId cameraMutexHandle;
osMutexId sdMutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartControlTask(void const * argument);
void StartLCDTask(void const * argument);
void StartTouchPanelTask(void const * argument);
void StartKeypadTask(void const * argument);
void StartFileSystemTask(void const * argument);
void MessageTimerCallback(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of cameraMutex */
  osMutexDef(cameraMutex);
  cameraMutexHandle = osMutexCreate(osMutex(cameraMutex));

  /* definition and creation of sdMutex */
  osMutexDef(sdMutex);
  sdMutexHandle = osMutexCreate(osMutex(sdMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of messageTimer */
  osTimerDef(messageTimer, MessageTimerCallback);
  messageTimerHandle = osTimerCreate(osTimer(messageTimer), osTimerOnce, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of stateQueue */
  osMessageQDef(stateQueue, 16, uint16_t);
  stateQueueHandle = osMessageCreate(osMessageQ(stateQueue), NULL);

  /* definition and creation of renderQueue */
  osMessageQDef(renderQueue, 16, uint16_t);
  renderQueueHandle = osMessageCreate(osMessageQ(renderQueue), NULL);

  /* definition and creation of keypadQueue */
  osMessageQDef(keypadQueue, 4, uint16_t);
  keypadQueueHandle = osMessageCreate(osMessageQ(keypadQueue), NULL);

  /* definition and creation of fileSystemQueue */
  osMessageQDef(fileSystemQueue, 16, uint16_t);
  fileSystemQueueHandle = osMessageCreate(osMessageQ(fileSystemQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of controlTask */
  osThreadDef(controlTask, StartControlTask, osPriorityNormal, 0, 128);
  controlTaskHandle = osThreadCreate(osThread(controlTask), NULL);

  /* definition and creation of lcdTask */
  osThreadDef(lcdTask, StartLCDTask, osPriorityNormal, 0, 128);
  lcdTaskHandle = osThreadCreate(osThread(lcdTask), NULL);

  /* definition and creation of touchPanelTask */
  osThreadDef(touchPanelTask, StartTouchPanelTask, osPriorityNormal, 0, 128);
  touchPanelTaskHandle = osThreadCreate(osThread(touchPanelTask), NULL);

  /* definition and creation of keypadTask */
  osThreadDef(keypadTask, StartKeypadTask, osPriorityNormal, 0, 128);
  keypadTaskHandle = osThreadCreate(osThread(keypadTask), NULL);

  /* definition and creation of fileSystemTask */
  osThreadDef(fileSystemTask, StartFileSystemTask, osPriorityNormal, 0, 128);
  fileSystemTaskHandle = osThreadCreate(osThread(fileSystemTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
__weak void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartControlTask */
/**
* @brief Function implementing the controlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartControlTask */
__weak void StartControlTask(void const * argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartControlTask */
}

/* USER CODE BEGIN Header_StartLCDTask */
/**
* @brief Function implementing the lcdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLCDTask */
__weak void StartLCDTask(void const * argument)
{
  /* USER CODE BEGIN StartLCDTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLCDTask */
}

/* USER CODE BEGIN Header_StartTouchPanelTask */
/**
* @brief Function implementing the touchPanelTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTouchPanelTask */
__weak void StartTouchPanelTask(void const * argument)
{
  /* USER CODE BEGIN StartTouchPanelTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTouchPanelTask */
}

/* USER CODE BEGIN Header_StartKeypadTask */
/**
* @brief Function implementing the keypadTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKeypadTask */
__weak void StartKeypadTask(void const * argument)
{
  /* USER CODE BEGIN StartKeypadTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartKeypadTask */
}

/* USER CODE BEGIN Header_StartFileSystemTask */
/**
* @brief Function implementing the fileSystemTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFileSystemTask */
__weak void StartFileSystemTask(void const * argument)
{
  /* USER CODE BEGIN StartFileSystemTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartFileSystemTask */
}

/* MessageTimerCallback function */
__weak void MessageTimerCallback(void const * argument)
{
  /* USER CODE BEGIN MessageTimerCallback */

  /* USER CODE END MessageTimerCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
