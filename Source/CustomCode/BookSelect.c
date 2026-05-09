/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*        Solutions for real time microcontroller applications        *
**********************************************************************
----------------------------------------------------------------------
File        : BookSelect.c
Purpose     : Book Selection Screen
              Draws grid, handles card selection, action buttons
---------------------------END-OF-HEADER------------------------------
*/

#include "BookSelect.h"
#include <string.h>
#include <stdio.h>

/*********************************************************************
*
*       Demo book data
*/
static BOOK_INFO _Books[] = {
    {"San Ti",           "Liu Cixin",      45, 0xFFE53935},
    {"To Live",          "Yu Hua",        100, 0xFFFF9800},
    {"Fortress Besieged","Qian Zhongshu",  12, 0xFF2196F3},
    {"One Hundred Years", "Garcia Marquez", 78, 0xFF4CAF50},
    {"Dream of Red Mansions", "Cao Xueqin", 0, 0xFF9C27B0},
    {"Camel Xiangzi",    "Lao She",        33, 0xFFFF5722},
    {"The Kite Runner",  "Khaled Hosseini", 67, 0xFF009688},
    {"Ordinary World",   "Lu Yao",         22, 0xFF3F51B5},
};
#define BOOK_COUNT (sizeof(_Books) / sizeof(_Books[0]))

static int          _SelectedIndex = 0;
static WM_HWIN      _hScreen = 0;
static BS_ACTION_CB _ActionCb = 0;

/*********************************************************************
*
*       _GetCardRect
*/
static void _GetCardRect(int index, GUI_RECT *pRect) {
    int col = index % 4;
    int row = index / 4;
    pRect->x0 = GRID_LEFT + col * (CARD_W + CARD_GAP_X);
    pRect->y0 = GRID_TOP + row * (CARD_H + CARD_GAP_Y);
    pRect->x1 = pRect->x0 + CARD_W;
    pRect->y1 = pRect->y0 + CARD_H;
}

/*********************************************************************
*
*       _DrawCard
*/
static void _DrawCard(int index) {
    GUI_RECT r;
    BOOK_INFO *bk = &_Books[index];
    int titleY, authorY, progY, cx, cy, barW, fillW;
    char letter[2], buf[16];

    _GetCardRect(index, &r);

    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawRoundedRect(r.x0, r.y0, r.x1, r.y1, 10);

    GUI_SetColor(bk->CoverColor);
    GUI_FillRoundedRect(r.x0 + 2, r.y0 + 2, r.x1 - 2, r.y0 + COVER_H, 8);

    cx = (r.x0 + r.x1) / 2;
    cy = r.y0 + COVER_H / 2;
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24B_ASCII);
    letter[0] = bk->Title[0];
    letter[1] = '\0';
    GUI_DispStringAt(letter, cx - 14, cy - 20);

    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRoundedRect(r.x0 + 2, r.y0 + COVER_H, r.x1 - 2, r.y1 - 2, 0);

    titleY = r.y0 + COVER_H + 10;
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringAt(bk->Title, r.x0 + 12, titleY);

    authorY = titleY + 24;
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font13_ASCII);
    GUI_DispStringAt(bk->Author, r.x0 + 12, authorY);

    progY = authorY + 24;
    barW = CARD_W - 24;
    GUI_SetColor(COLOR_DIVIDER);
    GUI_FillRoundedRect(r.x0 + 12, progY, r.x0 + 12 + barW, progY + 6, 3);
    if (bk->Progress > 0) {
        fillW = (barW * bk->Progress) / 100;
        if (fillW < 6) fillW = 6;
        GUI_SetColor(bk->Progress == 100 ? COLOR_SUCCESS : COLOR_PRIMARY);
        GUI_FillRoundedRect(r.x0 + 12, progY, r.x0 + 12 + fillW, progY + 6, 3);
    }

    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font13_ASCII);
    sprintf(buf, "%d%%", bk->Progress);
    GUI_DispStringAt(buf, r.x1 - 42, progY + 12);
}

/*********************************************************************
*
*       _DrawHeader
*/
static void _DrawHeader(void) {
    /* Header background */
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRect(0, 0, BOOKSELECT_WIDTH, BS_HEADER_H);
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawHLine(BS_HEADER_H - 1, 0, BOOKSELECT_WIDTH);

    /* Back button area */
    GUI_SetColor(COLOR_PRIMARY);
    GUI_FillRoundedRect(16, 10, 80, BS_HEADER_H - 10, 6);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispStringAt("Back", 30, 18);

    /* Title */
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font24B_ASCII);
    GUI_DispStringAt("My Books", (BOOKSELECT_WIDTH - 120) / 2, 12);

    /* Open button area */
    GUI_SetColor(COLOR_SUCCESS);
    GUI_FillRoundedRect(BOOKSELECT_WIDTH - 136, 10, BOOKSELECT_WIDTH - 16, BS_HEADER_H - 10, 6);
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringAt("Open", BOOKSELECT_WIDTH - 120, 18);
}

/*********************************************************************
*
*       _OnPaint
*/
static void _OnPaint(void) {
    int i;
    GUI_SetBkColor(COLOR_BACKGROUND);
    GUI_Clear();
    _DrawHeader();
    for (i = 0; i < (int)BOOK_COUNT; i++) {
        _DrawCard(i);
    }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(WM_MESSAGE *pMsg) {
    GUI_PID_STATE *pState = (GUI_PID_STATE *)pMsg->Data.p;
    int i;

    if (!pState || !pState->Pressed) return;

    /* Header - Back button */
    if (pState->y <= BS_HEADER_H) {
        if (pState->x >= 16 && pState->x <= 80) {
            if (_ActionCb) _ActionCb(1);  /* Back */
            return;
        }
        if (pState->x >= BOOKSELECT_WIDTH - 136 && pState->x <= BOOKSELECT_WIDTH - 16) {
            if (_ActionCb) _ActionCb(0);  /* Open */
            return;
        }
        return;
    }

    /* Book cards */
    for (i = 0; i < (int)BOOK_COUNT; i++) {
        GUI_RECT r;
        _GetCardRect(i, &r);
        if (pState->x >= r.x0 && pState->x <= r.x1 &&
            pState->y >= r.y0 && pState->y <= r.y1) {
            _SelectedIndex = i;
            WM_InvalidateWindow(_hScreen);
            return;
        }
    }
}

/*********************************************************************
*
*       Public code
*/

void cbBookSelect(WM_MESSAGE *pMsg) {
    switch (pMsg->MsgId) {
        case WM_PAINT:
            _OnPaint();
            break;
        case WM_TOUCH:
            _OnTouch(pMsg);
            break;
        default:
            WM_DefaultProc(pMsg);
            break;
    }
}

void BookSelect_Create(WM_HWIN hParent, BS_ACTION_CB cb) {
    _ActionCb = cb;
    if (_hScreen == 0) {
        _hScreen = WM_CreateWindowAsChild(0, 0,
            BOOKSELECT_WIDTH, BOOKSELECT_HEIGHT,
            hParent, WM_CF_SHOW | WM_CF_MEMDEV,
            cbBookSelect, 0);
    }
}

void BookSelect_Show(void) {
    if (_hScreen == 0) return;
    WM_ShowWindow(_hScreen);
    WM_BringToTop(_hScreen);
    WM_InvalidateWindow(_hScreen);
}

void BookSelect_Hide(void) {
    if (_hScreen != 0) {
        WM_HideWindow(_hScreen);
    }
}

const BOOK_INFO *BookSelect_GetSelectedBook(void) {
    if (_SelectedIndex >= 0 && _SelectedIndex < (int)BOOK_COUNT) {
        return &_Books[_SelectedIndex];
    }
    return &_Books[0];
}

int BookSelect_GetSelectedIndex(void) {
    return _SelectedIndex;
}

/*************************** End of file ****************************/
