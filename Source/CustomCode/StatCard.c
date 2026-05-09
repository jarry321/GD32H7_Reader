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
File        : StatCard.c
Purpose     : Custom statistics card widget for data visualization
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
#define STAT_CARD_MARGIN   12
#define STAT_CARD_RADIUS   8

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static STAT_CARD_INFO _StatInfo;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _Paint
*/
static void _Paint(WM_HWIN hWin) {
    GUI_RECT Rect;
    int x, y;
    char buf[32];

    WM_GetClientRectEx(hWin, &Rect);

    // Card background
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, STAT_CARD_RADIUS);

    // Card border
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, STAT_CARD_RADIUS);

    x = Rect.x0 + STAT_CARD_MARGIN;
    y = Rect.y0 + STAT_CARD_MARGIN;

    // Title
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font13_ASCII);
    GUI_DispStringAt(_StatInfo.Title, x, y);

    // Value (large number)
    y += 20;
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font32B_ASCII);
    GUI_DispDecAt(_StatInfo.Value, x, y, 1);

    // Unit
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispString(" ");
    GUI_DispString(_StatInfo.Unit);

    // Trend indicator
    y += 36;
    if (_StatInfo.Trend > 0) {
        GUI_SetColor(COLOR_SUCCESS);
        GUI_DispStringAt("↑ ", x, y);
    } else if (_StatInfo.Trend < 0) {
        GUI_SetColor(COLOR_ERROR);
        GUI_DispStringAt("↓ ", x, y);
    } else {
        GUI_SetColor(COLOR_TEXT_SECONDARY);
        GUI_DispStringAt("  ", x, y);
    }

    GUI_DispDec(abs(_StatInfo.Trend), 2);
    GUI_DispString("%");
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
*       STAT_CARD_Create
*/
WM_HWIN STAT_CARD_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Id) {
    WM_HWIN hWin;

    hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent,
                                   WM_CF_SHOW | WM_CF_MEMDEV, _Callback, Id);
    return hWin;
}

/*********************************************************************
*
*       STAT_CARD_Update
*/
void STAT_CARD_Update(WM_HWIN hWin, STAT_CARD_INFO *pStat) {
    if (pStat) {
        memcpy(&_StatInfo, pStat, sizeof(STAT_CARD_INFO));
        WM_InvalidateWindow(hWin);
    }
}

/*************************** End of file ****************************/
