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
File        : CustomWidgets.h
Purpose     : Custom widget definitions for RFID Reader UI
---------------------------END-OF-HEADER------------------------------
*/

#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <stdint.h>
#include "GUI.h"
#include "WM.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
// Color definitions - Tech Blue Theme (ARGB format)
#define COLOR_PRIMARY           0xFF1E88E5    // Main blue
#define COLOR_SECONDARY         0xFF42A5F5    // Light blue
#define COLOR_ACCENT            0xFFFF6B35    // Orange accent
#define COLOR_BACKGROUND        0xFFF5F7FA    // Page background (light gray)
#define COLOR_CARD_BG           0xFFFFFFFF    // Card background (white)
#define COLOR_TEXT_PRIMARY      0xFF212121    // Primary text (dark gray)
#define COLOR_TEXT_SECONDARY    0xFF757575    // Secondary text (gray)
#define COLOR_DIVIDER           0xFFE0E0E0    // Divider (light gray)
#define COLOR_SUCCESS           0xFF4CAF50    // Success green
#define COLOR_ERROR             0xFFF44336    // Error red
#define COLOR_WARNING           0xFFFFC107    // Warning yellow

// Widget IDs
#define ID_STATUS_BAR           (GUI_ID_USER + 100)
#define ID_TAG_CARD             (GUI_ID_USER + 101)
#define ID_PROGRESS_CARD        (GUI_ID_USER + 102)
#define ID_STAT_CARD            (GUI_ID_USER + 103)

/*********************************************************************
*
*       Structures
*
**********************************************************************
*/

// Status bar information
typedef struct {
    uint8_t Battery;        // Battery percentage (0-100)
    uint8_t Signal;         // Signal strength (0-4)
    uint8_t Connected;      // Connection status (0: disconnected, 1: connected)
    char Time[16];          // Current time string
} STATUS_BAR_INFO;

// Tag information
typedef struct {
    char EPC[24];           // EPC code
    char Type[16];          // Tag type
    uint8_t Status;         // Status (0: normal, 1: abnormal, 2: unknown)
    char Timestamp[20];     // Read timestamp
} TAG_INFO;

// Task progress information
typedef struct {
    char Name[32];          // Task name
    uint16_t Current;       // Current progress
    uint16_t Total;         // Total count
    uint8_t Status;         // Status (0: running, 1: completed, 2: paused)
    char StartTime[8];      // Start time
    char EndTime[8];        // End time
    uint8_t AbnormalCount;  // Abnormal tag count
} TASK_PROGRESS;

// Statistics card information
typedef struct {
    char Title[16];         // Stat title
    int32_t Value;          // Stat value
    char Unit[8];           // Unit string
    int8_t Trend;           // Trend percentage (can be negative)
} STAT_CARD_INFO;

/*********************************************************************
*
*       API Functions
*
**********************************************************************
*/

/*********************************************************************
*
*       Status Bar Widget
*/
WM_HWIN STATUS_BAR_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hParent);
void STATUS_BAR_Update(WM_HWIN hWin, STATUS_BAR_INFO *pInfo);
void STATUS_BAR_SetBattery(WM_HWIN hWin, uint8_t percent);
void STATUS_BAR_SetSignal(WM_HWIN hWin, uint8_t strength);
void STATUS_BAR_SetConnected(WM_HWIN hWin, uint8_t connected);
void STATUS_BAR_SetTime(WM_HWIN hWin, const char *pTime);

/*********************************************************************
*
*       Tag Card Widget
*/
WM_HWIN TAG_CARD_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Id);
void TAG_CARD_Update(WM_HWIN hWin, TAG_INFO *pTag);
void TAG_CARD_SetSelected(WM_HWIN hWin, int selected);

/*********************************************************************
*
*       Progress Card Widget
*/
WM_HWIN PROGRESS_CARD_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Id);
void PROGRESS_CARD_Update(WM_HWIN hWin, TASK_PROGRESS *pTask);

/*********************************************************************
*
*       Statistics Card Widget
*/
WM_HWIN STAT_CARD_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Id);
void STAT_CARD_Update(WM_HWIN hWin, STAT_CARD_INFO *pStat);

#endif  // CUSTOMWIDGETS_H

/*************************** End of file ****************************/
