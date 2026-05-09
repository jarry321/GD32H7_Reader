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
File        : StatusBar.c
Purpose     : Custom status bar widget implementation
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
#define STATUS_BAR_HEIGHT  48

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static STATUS_BAR_INFO _StatusInfo = {
    .Battery = 85,
    .Signal = 3,
    .Connected = 1,
    .Time = "14:30"
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _DrawBatteryIcon
*/
static void _DrawBatteryIcon(int x0, int y0, uint8_t percent) {
    int width = 24;
    int height = 12;
    int fillWidth;

    // Battery outline
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_DrawRect(x0, y0, x0 + width, y0 + height);
    GUI_DrawRect(x0 + width + 2, y0 + 2, x0 + width + 4, y0 + height - 2);

    // Fill based on percentage
    if (percent > 20) {
        GUI_SetColor(COLOR_SUCCESS);
    } else if (percent > 10) {
        GUI_SetColor(COLOR_WARNING);
    } else {
        GUI_SetColor(COLOR_ERROR);
    }

    fillWidth = (width - 2) * percent / 100;
    if (fillWidth > 0) {
        GUI_FillRect(x0 + 1, y0 + 1, x0 + fillWidth, y0 + height - 1);
    }
}

/*********************************************************************
*
*       _DrawSignalIcon
*/
static void _DrawSignalIcon(int x0, int y0, uint8_t strength) {
    int i;
    int barHeights[] = {4, 7, 10, 13};
    int barWidth = 3;
    int gap = 2;

    for (i = 0; i < 4; i++) {
        if (i < strength) {
            GUI_SetColor(COLOR_PRIMARY);
        } else {
            GUI_SetColor(COLOR_DIVIDER);
        }
        GUI_FillRect(x0 + i * (barWidth + gap), y0 + 13 - barHeights[i],
                     x0 + i * (barWidth + gap) + barWidth, y0 + 13);
    }
}

/*********************************************************************
*
*       _DrawConnectionIcon
*/
static void _DrawConnectionIcon(int x0, int y0, uint8_t connected) {
    if (connected) {
        GUI_SetColor(COLOR_SUCCESS);
        GUI_DrawCircle(x0 + 6, y0 + 6, 6);
        GUI_FillCircle(x0 + 6, y0 + 6, 3);
    } else {
        GUI_SetColor(COLOR_ERROR);
        GUI_DrawCircle(x0 + 6, y0 + 6, 6);
        GUI_DrawLine(x0 + 2, y0 + 10, x0 + 10, y0 + 2);
    }
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(WM_HWIN hWin) {
    GUI_RECT Rect;
    int x, y;

    WM_GetClientRectEx(hWin, &Rect);

    // Background
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRectEx(&Rect);

    // Bottom border
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawHLine(Rect.y1, Rect.x0, Rect.x1);

    // Starting position
    x = 16;
    y = (Rect.y1 - Rect.y0 - 12) / 2 + Rect.y0;

    // Battery
    _DrawBatteryIcon(x, y, _StatusInfo.Battery);
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispDecAt(_StatusInfo.Battery, x + 28, y - 2, 3);
    GUI_DispString("%");
    x += 70;

    // Signal
    _DrawSignalIcon(x, y, _StatusInfo.Signal);
    x += 30;

    // Connection status
    _DrawConnectionIcon(x, y, _StatusInfo.Connected);
    GUI_SetColor(_StatusInfo.Connected ? COLOR_SUCCESS : COLOR_ERROR);
    GUI_DispStringAt(_StatusInfo.Connected ? " Connected" : " Disconnected", x + 16, y - 2);
    x += 120;

    // Time (right aligned)
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringAt(_StatusInfo.Time, Rect.x1 - 60, y - 2);
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
*       STATUS_BAR_Create
*/
WM_HWIN STATUS_BAR_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hParent) {
    WM_HWIN hWin;

    hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent,
                                   WM_CF_SHOW | WM_CF_MEMDEV, _Callback, 0);
    return hWin;
}

/*********************************************************************
*
*       STATUS_BAR_Update
*/
void STATUS_BAR_Update(WM_HWIN hWin, STATUS_BAR_INFO *pInfo) {
    if (pInfo) {
        memcpy(&_StatusInfo, pInfo, sizeof(STATUS_BAR_INFO));
        WM_InvalidateWindow(hWin);
    }
}

/*********************************************************************
*
*       STATUS_BAR_SetBattery
*/
void STATUS_BAR_SetBattery(WM_HWIN hWin, uint8_t percent) {
    if (percent <= 100) {
        _StatusInfo.Battery = percent;
        WM_InvalidateWindow(hWin);
    }
}

/*********************************************************************
*
*       STATUS_BAR_SetSignal
*/
void STATUS_BAR_SetSignal(WM_HWIN hWin, uint8_t strength) {
    if (strength <= 4) {
        _StatusInfo.Signal = strength;
        WM_InvalidateWindow(hWin);
    }
}

/*********************************************************************
*
*       STATUS_BAR_SetConnected
*/
void STATUS_BAR_SetConnected(WM_HWIN hWin, uint8_t connected) {
    _StatusInfo.Connected = connected ? 1 : 0;
    WM_InvalidateWindow(hWin);
}

/*********************************************************************
*
*       STATUS_BAR_SetTime
*/
void STATUS_BAR_SetTime(WM_HWIN hWin, const char *pTime) {
    if (pTime) {
        strncpy(_StatusInfo.Time, pTime, sizeof(_StatusInfo.Time) - 1);
        _StatusInfo.Time[sizeof(_StatusInfo.Time) - 1] = '\0';
        WM_InvalidateWindow(hWin);
    }
}

/*************************** End of file ****************************/
