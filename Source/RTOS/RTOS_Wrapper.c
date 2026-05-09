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
File        : RTOS_Wrapper.c
Purpose     : RTOS wrapper implementation for Windows simulator
              This is a simplified version for simulation only.
---------------------------END-OF-HEADER------------------------------
*/

#include "RTOS_Wrapper.h"
#include <windows.h>
#include <stdio.h>

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static HANDLE _hMutex = NULL;
static DWORD _StartTime = 0;

/*********************************************************************
*
*       RTOS_Init
*/
void RTOS_Init(void) {
    _StartTime = GetTickCount();
    _hMutex = CreateMutex(NULL, FALSE, NULL);
    printf("RTOS: Initialized (Simulation Mode)\n");
}

/*********************************************************************
*
*       RTOS_Start
*/
void RTOS_Start(void) {
    printf("RTOS: Scheduler started\n");
    /* In simulation mode, we don't actually start a scheduler
       because Windows handles thread scheduling */
}

/*********************************************************************
*
*       RTOS_CreateTask
*/
int RTOS_CreateTask(TaskFunction_t pxTaskCode, const char *const pcName, 
                    const uint32_t usStackDepth, void *const pvParameters,
                    uint32_t uxPriority) {
    HANDLE hThread;
    DWORD threadId;
    
    hThread = CreateThread(
        NULL,                           /* Default security attributes */
        usStackDepth,                   /* Stack size */
        (LPTHREAD_START_ROUTINE)pxTaskCode, /* Thread function */
        pvParameters,                   /* Parameter */
        0,                              /* Creation flags */
        &threadId                       /* Thread ID */
    );
    
    if (hThread == NULL) {
        printf("RTOS: Failed to create task %s\n", pcName);
        return -1;
    }
    
    /* Set thread priority */
    int winPriority = THREAD_PRIORITY_NORMAL;
    if (uxPriority >= 4) {
        winPriority = THREAD_PRIORITY_HIGHEST;
    } else if (uxPriority >= 3) {
        winPriority = THREAD_PRIORITY_ABOVE_NORMAL;
    } else if (uxPriority >= 2) {
        winPriority = THREAD_PRIORITY_NORMAL;
    } else {
        winPriority = THREAD_PRIORITY_BELOW_NORMAL;
    }
    SetThreadPriority(hThread, winPriority);
    
    printf("RTOS: Created task '%s' (Priority: %d)\n", pcName, uxPriority);
    return 0;
}

/*********************************************************************
*
*       RTOS_DeleteTask
*/
void RTOS_DeleteTask(void) {
    ExitThread(0);
}

/*********************************************************************
*
*       RTOS_Delay
*/
void RTOS_Delay(uint32_t ms) {
    Sleep(ms);
}

/*********************************************************************
*
*       RTOS_CreateQueue
*/
void* RTOS_CreateQueue(uint32_t uxQueueLength, uint32_t uxItemSize) {
    /* Simplified: return a dummy handle */
    printf("RTOS: Created queue (Length: %d, ItemSize: %d)\n", 
           (int)uxQueueLength, (int)uxItemSize);
    return (void*)1;  /* Dummy handle */
}

/*********************************************************************
*
*       RTOS_DeleteQueue
*/
void RTOS_DeleteQueue(void* xQueue) {
    (void)xQueue;
}

/*********************************************************************
*
*       RTOS_SendQueue
*/
int RTOS_SendQueue(void* xQueue, const void *pvItemToQueue, uint32_t xTicksToWait) {
    (void)xQueue;
    (void)pvItemToQueue;
    (void)xTicksToWait;
    return 0;  /* Success */
}

/*********************************************************************
*
*       RTOS_ReceiveQueue
*/
int RTOS_ReceiveQueue(void* xQueue, void *pvBuffer, uint32_t xTicksToWait) {
    (void)xQueue;
    (void)pvBuffer;
    (void)xTicksToWait;
    return 0;  /* Success */
}

/*********************************************************************
*
*       RTOS_CreateMutex
*/
void* RTOS_CreateMutex(void) {
    HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
    printf("RTOS: Created mutex\n");
    return hMutex;
}

/*********************************************************************
*
*       RTOS_DeleteMutex
*/
void RTOS_DeleteMutex(void* xMutex) {
    if (xMutex) {
        CloseHandle((HANDLE)xMutex);
    }
}

/*********************************************************************
*
*       RTOS_TakeMutex
*/
int RTOS_TakeMutex(void* xMutex, uint32_t xTicksToWait) {
    DWORD result;
    result = WaitForSingleObject((HANDLE)xMutex, xTicksToWait);
    return (result == WAIT_OBJECT_0) ? 0 : -1;
}

/*********************************************************************
*
*       RTOS_GiveMutex
*/
int RTOS_GiveMutex(void* xMutex) {
    return ReleaseMutex((HANDLE)xMutex) ? 0 : -1;
}

/*********************************************************************
*
*       RTOS_EnterCritical
*/
void RTOS_EnterCritical(void) {
    /* Simplified: not needed in simulation */
}

/*********************************************************************
*
*       RTOS_ExitCritical
*/
void RTOS_ExitCritical(void) {
    /* Simplified: not needed in simulation */
}

/*********************************************************************
*
*       RTOS_GetTickCount
*/
uint32_t RTOS_GetTickCount(void) {
    return GetTickCount() - _StartTime;
}

/*************************** End of file ****************************/
