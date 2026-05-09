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
File        : ID_SCREEN_05.c
Purpose     : RFID Tag List Screen - Main implementation
---------------------------END-OF-HEADER------------------------------
*/

#include "ID_SCREEN_05.h"
#include "../RTOS/Language.h"
#include <string.h>

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static WM_HWIN _hScreen = 0;
static WM_HWIN _hStatusBar = 0;
static WM_HWIN _hTextTitle = 0;
static WM_HWIN _hTextCount = 0;
static WM_HWIN _hBtnBack = 0;
static WM_HWIN _hBtnRefresh = 0;
static WM_HWIN _hBtnSearch = 0;
static WM_HWIN _hListView = 0;
static WM_HWIN _hBtnLang = 0;  // Language toggle button

// Status bar info
static STATUS_BAR_INFO _StatusInfo = {
    .Battery = 85,
    .Signal = 3,
    .Connected = 1,
    .Time = "14:30"
};

// Demo tag data
static TAG_INFO _DemoTags[5] = {
    {"E2003412BCD4567890AB", "Asset", 0, "2024-05-08 14:30"},
    {"E2003413BCD4567890AC", "Device", 1, "2024-05-08 14:29"},
    {"E2003414BCD4567890AD", "Asset", 0, "2024-05-08 14:28"},
    {"E2003415BCD4567890AE", "Tool", 0, "2024-05-08 14:27"},
    {"E2003416BCD4567890AF", "Asset", 2, "2024-05-08 14:26"}
};

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _DrawStatusBar
*/
static void _DrawStatusBar(void) {
    GUI_RECT Rect;
    int x, y;
    char buf[32];

    // Status bar background
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRect(0, 0, SCREEN_05_WIDTH, STATUS_BAR_HEIGHT);

    // Bottom border
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawHLine(STATUS_BAR_HEIGHT - 1, 0, SCREEN_05_WIDTH);

    x = 16;
    y = (STATUS_BAR_HEIGHT - 16) / 2;

    // Battery icon and text
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispStringAt("[", x, y);
    GUI_DispDec(_StatusInfo.Battery, 2);
    GUI_DispString("%]");
    x += 60;

    // Signal icon
    GUI_DispStringAt("[Signal]", x, y);
    x += 70;

    // Connection status
    GUI_DispStringAt(_StatusInfo.Connected ? "[Connected]" : "[Disconnected]", x, y);
    x += 100;

    // Time (right aligned)
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringAt(_StatusInfo.Time, SCREEN_05_WIDTH - 80, y);

    // Language indicator (left of time)
    GUI_SetColor(COLOR_PRIMARY);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispStringAt("Lang:", SCREEN_05_WIDTH - 140, y);
}

/*********************************************************************
*
*       _DrawHeader
*/
static void _DrawHeader(void) {
    GUI_RECT Rect;
    int y = STATUS_BAR_HEIGHT;

    // Header background
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRect(0, y, SCREEN_05_WIDTH, y + HEADER_HEIGHT);

    // Title
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font24B_ASCII);
    GUI_DispStringAt("Tag List", 60, y + 14);

    // Back button text
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_SetColor(COLOR_PRIMARY);
    GUI_DispStringAt("<- Back", 16, y + 18);

    // Refresh button
    GUI_SetColor(COLOR_PRIMARY);
    GUI_DispStringAt("[Refresh]", SCREEN_05_WIDTH - 200, y + 18);

    // Search button
    GUI_DispStringAt("[Search]", SCREEN_05_WIDTH - 100, y + 18);
}

/*********************************************************************
*
*       _DrawTagList
*/
static void _DrawTagList(void) {
    int i;
    int y = LIST_Y_POS + 10;
    int cardHeight = 80;
    int cardMargin = 10;
    GUI_COLOR statusColor;
    const char *statusText;

    // List background
    GUI_SetColor(COLOR_BACKGROUND);
    GUI_FillRect(0, LIST_Y_POS, SCREEN_05_WIDTH, SCREEN_05_HEIGHT);

    // Draw each tag card
    for (i = 0; i < 5; i++) {
        int x = 16;
        int cardWidth = SCREEN_05_WIDTH - 32;

        // Card background
        GUI_SetColor(COLOR_CARD_BG);
        GUI_FillRoundedRect(x, y, x + cardWidth, y + cardHeight, 8);

        // Card border
        GUI_SetColor(COLOR_DIVIDER);
        GUI_DrawRoundedRect(x, y, x + cardWidth, y + cardHeight, 8);

        // EPC code
        GUI_SetColor(COLOR_TEXT_PRIMARY);
        GUI_SetFont(&GUI_Font16B_ASCII);
        GUI_DispStringAt(_DemoTags[i].EPC, x + 16, y + 12);

        // Type
        GUI_SetColor(COLOR_TEXT_SECONDARY);
        GUI_SetFont(&GUI_Font13_ASCII);
        GUI_DispStringAt("Type: ", x + 16, y + 38);
        GUI_SetColor(COLOR_TEXT_PRIMARY);
        GUI_DispString(_DemoTags[i].Type);

        // Status badge
        switch (_DemoTags[i].Status) {
            case 0: statusColor = COLOR_SUCCESS; statusText = "Normal"; break;
            case 1: statusColor = COLOR_ERROR; statusText = "Abnormal"; break;
            default: statusColor = COLOR_WARNING; statusText = "Unknown"; break;
        }

        GUI_SetColor(statusColor);
        GUI_FillRoundedRect(x + cardWidth - 100, y + 10, x + cardWidth - 20, y + 34, 4);
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(&GUI_Font13_ASCII);
        GUI_DispStringAt(statusText, x + cardWidth - 90, y + 16);

        // Timestamp
        GUI_SetColor(COLOR_TEXT_SECONDARY);
        GUI_DispStringAt(_DemoTags[i].Timestamp, x + cardWidth - 150, y + 58);

        y += cardHeight + cardMargin;
    }

    // Bottom info bar
    y = SCREEN_05_HEIGHT - 36;
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRect(0, y, SCREEN_05_WIDTH, SCREEN_05_HEIGHT);
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawHLine(y, 0, SCREEN_05_WIDTH);

    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font13_ASCII);
    GUI_DispStringAt("Total: 128 tags  |  Page 1/13", 16, y + 10);
}

/*********************************************************************
*
*       _OnPaint
*/
static void _OnPaint(void) {
    // Draw entire screen background first
    GUI_SetBkColor(COLOR_BACKGROUND);
    GUI_Clear();
    
    _DrawStatusBar();
    _DrawHeader();
    _DrawTagList();
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(WM_MESSAGE *pMsg) {
    GUI_PID_STATE *pState = (GUI_PID_STATE *)pMsg->Data.p;

    if (pState) {
        if (pState->Pressed) {
            int x = pState->x;
            int y = pState->y;

            // Check Back button
            if (x >= 16 && x <= 80 && y >= STATUS_BAR_HEIGHT + 10 && y <= STATUS_BAR_HEIGHT + 46) {
                // Hide current screen and show main menu
                WM_HideWindow(_hScreen);
                WM_ShowWindow(WM_HBKWIN);
            }

            // Check Refresh button
            if (x >= SCREEN_05_WIDTH - 200 && x <= SCREEN_05_WIDTH - 130 &&
                y >= STATUS_BAR_HEIGHT + 10 && y <= STATUS_BAR_HEIGHT + 46) {
                // Refresh tag list
                WM_InvalidateWindow(_hScreen);
            }
        }
    }
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/

/*********************************************************************
*
*       cbID_SCREEN_05
*/
void cbID_SCREEN_05(WM_MESSAGE *pMsg) {
    switch (pMsg->MsgId) {
        case WM_PAINT:
            _OnPaint();
            break;

        case WM_TOUCH:
            _OnTouch(pMsg);
            break;

        case WM_INIT_DIALOG:
            // Initialize screen
            break;

        case WM_NOTIFY_PARENT:
            // Handle child window notifications
            if (pMsg->Data.v == WM_NOTIFICATION_CLICKED) {
                if (pMsg->hWinSrc == _hBtnLang) {
                    // Toggle language
                    LANG_Toggle();
                    LANG_SaveConfig();
                    // Update button text
                    if (LANG_GetLanguage() == LANG_EN) {
                        BUTTON_SetText(_hBtnLang, "EN");
                    } else {
                        BUTTON_SetText(_hBtnLang, "CN");
                    }
                    // Invalidate window to refresh display
                    WM_InvalidateWindow(_hScreen);
                    printf("Language button clicked! Now: %s\n", LANG_GetLanguageName(LANG_GetLanguage()));
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
*       ID_SCREEN_05_Create
*/
void ID_SCREEN_05_Create(void) {
    if (_hScreen == 0) {
        _hScreen = WM_CreateWindowAsChild(0, 0, SCREEN_05_WIDTH, SCREEN_05_HEIGHT,
                                           WM_HBKWIN, WM_CF_SHOW | WM_CF_MEMDEV,
                                           cbID_SCREEN_05, 0);
        
        // Create language toggle button
        _hBtnLang = BUTTON_CreateEx(SCREEN_05_WIDTH - 95, 5, 80, 20, _hScreen, WM_CF_SHOW, 0, GUI_ID_USER + 100);
        BUTTON_SetFont(_hBtnLang, &GUI_Font16_ASCII);
        BUTTON_SetText(_hBtnLang, "EN");
        BUTTON_SetBkColor(_hBtnLang, BUTTON_CI_UNPRESSED, COLOR_PRIMARY);
        BUTTON_SetBkColor(_hBtnLang, BUTTON_CI_PRESSED, COLOR_SECONDARY);
        BUTTON_SetTextColor(_hBtnLang, BUTTON_CI_UNPRESSED, GUI_WHITE);
        BUTTON_SetTextColor(_hBtnLang, BUTTON_CI_PRESSED, GUI_WHITE);
    }
}

/*********************************************************************
*
*       ID_SCREEN_05_Show
*/
void ID_SCREEN_05_Show(void) {
    if (_hScreen == 0) {
        ID_SCREEN_05_Create();
    }
    WM_ShowWindow(_hScreen);
    WM_BringToTop(_hScreen);
    WM_InvalidateWindow(_hScreen);
}

/*********************************************************************
*
*       ID_SCREEN_05_Hide
*/
void ID_SCREEN_05_Hide(void) {
    if (_hScreen != 0) {
        WM_HideWindow(_hScreen);
    }
}

/*************************** End of file ****************************/
