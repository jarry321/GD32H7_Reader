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
File        : TagCard.c
Purpose     : Custom tag card widget for RFID tag display
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
#define TAG_CARD_HEIGHT     80
#define TAG_CARD_MARGIN     16
#define TAG_CARD_RADIUS     12

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static TAG_INFO _TagInfo;
static int _Selected = 0;

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
        case 0: return COLOR_SUCCESS;
        case 1: return COLOR_ERROR;
        default: return COLOR_WARNING;
    }
}

/*********************************************************************
*
*       _GetStatusText
*/
static const char *_GetStatusText(uint8_t status) {
    switch (status) {
        case 0: return "Normal";
        case 1: return "Abnormal";
        default: return "Unknown";
    }
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(WM_HWIN hWin) {
    GUI_RECT Rect;
    int x, y;
    GUI_COLOR statusColor;

    WM_GetClientRectEx(hWin, &Rect);

    // Card background with selection highlight
    if (_Selected) {
        GUI_SetColor(COLOR_PRIMARY);
    } else {
        GUI_SetColor(COLOR_CARD_BG);
    }
    GUI_FillRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, TAG_CARD_RADIUS);

    // Card border
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, TAG_CARD_RADIUS);

    // EPC code (main text)
    x = Rect.x0 + TAG_CARD_MARGIN;
    y = Rect.y0 + 12;

    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringAt(_TagInfo.EPC, x, y);

    // Type label
    y += 24;
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispStringAt("Type: ", x, y);
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_DispString(_TagInfo.Type);

    // Status badge (right side)
    statusColor = _GetStatusColor(_TagInfo.Status);
    x = Rect.x1 - 100;
    y = Rect.y0 + 12;

    // Status badge background
    GUI_SetColor(statusColor);
    GUI_FillRoundedRect(x - 8, y - 2, x + 80, y + 22, 4);

    // Status text
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispStringAt(_GetStatusText(_TagInfo.Status), x, y);

    // Timestamp (bottom right)
    y = Rect.y1 - 28;
    x = Rect.x1 - TAG_CARD_MARGIN - 80;
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font13_ASCII);
    GUI_DispStringAt(_TagInfo.Timestamp, x, y);
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
        case WM_TOUCH:
            // Handle touch events for selection
            if (pMsg->Data.p) {
                GUI_PID_STATE *pState = (GUI_PID_STATE *)pMsg->Data.p;
                if (pState->Pressed) {
                    _Selected = 1;
                    WM_InvalidateWindow(pMsg->hWin);
                    WM_NotifyParent(pMsg->hWin, WM_NOTIFICATION_CLICKED);
                } else {
                    _Selected = 0;
                    WM_InvalidateWindow(pMsg->hWin);
                }
            }
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
*       TAG_CARD_Create
*/
WM_HWIN TAG_CARD_Create(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Id) {
    WM_HWIN hWin;

    hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent,
                                   WM_CF_SHOW | WM_CF_MEMDEV, _Callback, Id);
    return hWin;
}

/*********************************************************************
*
*       TAG_CARD_Update
*/
void TAG_CARD_Update(WM_HWIN hWin, TAG_INFO *pTag) {
    if (pTag) {
        memcpy(&_TagInfo, pTag, sizeof(TAG_INFO));
        WM_InvalidateWindow(hWin);
    }
}

/*********************************************************************
*
*       TAG_CARD_SetSelected
*/
void TAG_CARD_SetSelected(WM_HWIN hWin, int selected) {
    _Selected = selected ? 1 : 0;
    WM_InvalidateWindow(hWin);
}

/*************************** End of file ****************************/
