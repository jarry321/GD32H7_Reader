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
File        : ProgressCard.c
Purpose     : Custom progress card widget for inventory task display
---------------------------END-OF-HEADER------------------------------
*/

#include "CustomWidgets.h"
#include <string.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define PROGRESS_CARD_MARGIN    16
#define PROGRESS_CARD_RADIUS    12
#define PROGRESS_BAR_HEIGHT     8

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static TASK_PROGRESS _TaskInfo;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _GetStatusColor
*/
static GUI_COLOR _GetStatusColor(uint8_t status) {
    switch (status) {
        case 0: return COLOR_PRIMARY;       // Running
        case 1: return COLOR_SUCCESS;       // Completed
        default: return COLOR_WARNING;      // Paused
    }
}

/*********************************************************************
*
*       _GetStatusText
*/
static const char *_GetStatusText(uint8_t status) {
    switch (status) {
        case 0: return "Running";
        case 1: return "Completed";
        default: return "Paused";
    }
}

/*********************************************************************
*
*       _DrawProgressBar
*/
static void _DrawProgressBar(int x0, int y0, int xSize, uint8_t percent) {
    int fillWidth;

    // Background
    GUI_SetColor(COLOR_DIVIDER);
    GUI_FillRoundedRect(x0, y0, x0 + xSize, y0 + PROGRESS_BAR_HEIGHT, 4);

    // Fill
    if (percent > 0) {
        GUI_SetColor(COLOR_PRIMARY);
        fillWidth = xSize * percent / 100;
        if (fillWidth > PROGRESS_BAR_HEIGHT) {
            GUI_FillRoundedRect(x0, y0, x0 + fillWidth, y0 + PROGRESS_BAR_HEIGHT, 4);
        } else {
            GUI_FillRect(x0, y0, x0 + fillWidth, y0 + PROGRESS_BAR_HEIGHT);
        }
    }
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(WM_HWIN hWin) {
    GUI_RECT Rect;
    int x, y;
    int progressPercent;
    GUI_COLOR statusColor;

    WM_GetClientRectEx(hWin, &Rect);

    // Card background
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, PROGRESS_CARD_RADIUS);

    // Card border
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, PROGRESS_CARD_RADIUS);

    x = Rect.x0 + PROGRESS_CARD_MARGIN;
    y = Rect.y0 + 16;

    // Task name
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringAt("Task: ", x, y);
    GUI_DispString(_TaskInfo.Name);

    // Progress bar
    y += 28;
    progressPercent = (_TaskInfo.Total > 0) ? (_TaskInfo.Current * 100 / _TaskInfo.Total) : 0;
    _DrawProgressBar(x, y, Rect.x1 - x - PROGRESS_CARD_MARGIN, progressPercent);

    // Progress text
    y += 16;
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispStringAt("", x, y);
    GUI_DispDec(progressPercent, 3);
    GUI_DispString("% (");
    GUI_DispDec(_TaskInfo.Current, 5);
    GUI_DispString("/");
    GUI_DispDec(_TaskInfo.Total, 5);
    GUI_DispString(")");

    // Status info row
    y += 24;
    statusColor = _GetStatusColor(_TaskInfo.Status);

    // Status badge
    GUI_SetColor(statusColor);
    GUI_FillRoundedRect(x, y - 2, x + 70, y + 20, 4);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font13_ASCII);
    GUI_DispStringAt(_GetStatusText(_TaskInfo.Status), x + 8, y);

    // Time info
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_DispStringAt("Start: ", x + 80, y);
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_DispString(_TaskInfo.StartTime);

    if (_TaskInfo.Status == 1) { // Completed
        GUI_SetColor(COLOR_TEXT_SECONDARY);
        GUI_DispString("  End: ");
        GUI_SetColor(COLOR_TEXT_PRIMARY);
        GUI_DispString(_TaskInfo.EndTime);

        // Abnormal count
        if (_TaskInfo.AbnormalCount > 0) {
            GUI_SetColor(COLOR_ERROR);
            GUI_DispString("  Abnormal: ");
            GUI_DispDec(_TaskInfo.AbnormalCount, 3);
        }
    }
}

/*********************************************************************
*
*       _Callback
*/
static void _Callback(WM_MESSAGE *pMsg) {
    switch (pMsg->MsgId) {
        case WM_PAINT:
            _Paint(pMsg->hWin);
            break;
        default:
            WM_DefaultProc(pMsg);
            break;
    }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       PROGRESS_CARD_Create
*/
WM_HWIN PROGRESS_CARD_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Id) {
    WM_HWIN hWin;

    hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent,
                                   WM_CF_SHOW | WM_CF_MEMDEV, _Callback, Id);
    return hWin;
}

/*********************************************************************
*
*       PROGRESS_CARD_Update
*/
void PROGRESS_CARD_Update(WM_HWIN hWin, TASK_PROGRESS *pTask) {
    if (pTask) {
        memcpy(&_TaskInfo, pTask, sizeof(TASK_PROGRESS));
        WM_InvalidateWindow(hWin);
    }
}

/*************************** End of file ****************************/
