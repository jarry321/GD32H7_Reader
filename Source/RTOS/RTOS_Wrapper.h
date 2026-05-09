/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2026  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : RTOS_Wrapper.h
Purpose     : RTOS abstraction layer for GUI application
---------------------------END-OF-HEADER------------------------------
*/

#ifndef RTOS_WRAPPER_H
#define RTOS_WRAPPER_H

#include <stdint.h>
#include <stdbool.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/* Task priorities */
#define TASK_PRIORITY_GUI           3
#define TASK_PRIORITY_COMM          2
#define TASK_PRIORITY_IDLE          1

/* Task stack sizes */
#define TASK_STACK_SIZE_GUI         (1024 * 4)
#define TASK_STACK_SIZE_COMM        (1024 * 2)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef void (*TaskFunction_t)(void *pvParameters);

/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/

/* RTOS initialization */
void RTOS_Init(void);
void RTOS_Start(void);

/* Task management */
int RTOS_CreateTask(TaskFunction_t pxTaskCode, const char *const pcName, 
                    const uint32_t usStackDepth, void *const pvParameters,
                    uint32_t uxPriority);
void RTOS_DeleteTask(void);
void RTOS_Delay(uint32_t ms);

/* Queue/Semaphore */
void* RTOS_CreateQueue(uint32_t uxQueueLength, uint32_t uxItemSize);
void RTOS_DeleteQueue(void* xQueue);
int RTOS_SendQueue(void* xQueue, const void *pvItemToQueue, uint32_t xTicksToWait);
int RTOS_ReceiveQueue(void* xQueue, void *pvBuffer, uint32_t xTicksToWait);

/* Mutex */
void* RTOS_CreateMutex(void);
void RTOS_DeleteMutex(void* xMutex);
int RTOS_TakeMutex(void* xMutex, uint32_t xTicksToWait);
int RTOS_GiveMutex(void* xMutex);

/* Critical section */
void RTOS_EnterCritical(void);
void RTOS_ExitCritical(void);

/* Tick count */
uint32_t RTOS_GetTickCount(void);

#endif /* RTOS_WRAPPER_H */
