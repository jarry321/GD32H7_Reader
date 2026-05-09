/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*        Solutions for real time microcontroller applications        *
**********************************************************************
----------------------------------------------------------------------
File        : BookSelect.c
Purpose     : Book Selection Screen - Custom drawn screen showing
              a grid of book cards for user selection
---------------------------END-OF-HEADER------------------------------
*/

#include "BookSelect.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_03.h"
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

static int _SelectedIndex = -1;

/*********************************************************************
*
*       Static data
*/
static WM_HWIN _hScreen = 0;

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
    int titleY, authorY, progY;

    _GetCardRect(index, &r);

    /* Card shadow / border */
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawRoundedRect(r.x0, r.y0, r.x1, r.y1, 10);

    /* Cover area */
    GUI_SetColor(bk->CoverColor);
    GUI_FillRoundedRect(r.x0 + 2, r.y0 + 2, r.x1 - 2, r.y0 + COVER_H, 8);

    /* Cover decoration - diagonal stripes */
    {
        int cx = (r.x0 + r.x1) / 2;
        int cy = r.y0 + COVER_H / 2;
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(&GUI_Font24B_ASCII);
        /* Draw first letter of title as icon */
        char letter[2] = {bk->Title[0], '\0'};
        GUI_DispStringAt(letter, cx - 14, cy - 20);
    }

    /* Card body background */
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRoundedRect(r.x0 + 2, r.y0 + COVER_H, r.x1 - 2, r.y1 - 2, 0);

    /* Title */
    titleY = r.y0 + COVER_H + 10;
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringAt(bk->Title, r.x0 + 12, titleY);

    /* Author */
    authorY = titleY + 24;
    GUI_SetColor(COLOR_TEXT_SECONDARY);
    GUI_SetFont(&GUI_Font13_ASCII);
    GUI_DispStringAt(bk->Author, r.x0 + 12, authorY);

    /* Progress bar */
    progY = authorY + 24;
    {
        int barW = CARD_W - 24;
        GUI_SetColor(COLOR_DIVIDER);
        GUI_FillRoundedRect(r.x0 + 12, progY, r.x0 + 12 + barW, progY + 6, 3);
        if (bk->Progress > 0) {
            int fillW = (barW * bk->Progress) / 100;
            if (fillW < 6) fillW = 6;
            GUI_SetColor(bk->Progress == 100 ? COLOR_SUCCESS : COLOR_PRIMARY);
            GUI_FillRoundedRect(r.x0 + 12, progY, r.x0 + 12 + fillW, progY + 6, 3);
        }
    }

    /* Progress text */
    {
        char buf[16];
        GUI_SetColor(COLOR_TEXT_SECONDARY);
        GUI_SetFont(&GUI_Font13_ASCII);
        sprintf(buf, "%d%%", bk->Progress);
        GUI_DispStringAt(buf, r.x1 - 42, progY + 12);
    }
}

/*********************************************************************
*
*       _DrawHeader
*/
static void _DrawHeader(void) {
    /* Header background */
    GUI_SetColor(COLOR_CARD_BG);
    GUI_FillRect(0, 0, BOOKSELECT_WIDTH, BS_HEADER_H);

    /* Bottom border */
    GUI_SetColor(COLOR_DIVIDER);
    GUI_DrawHLine(BS_HEADER_H - 1, 0, BOOKSELECT_WIDTH);

    /* Back button hint */
    GUI_SetColor(COLOR_PRIMARY);
    GUI_SetFont(&GUI_Font16_ASCII);
    GUI_DispStringAt("<- Back", 16, 18);

    /* Title */
    GUI_SetColor(COLOR_TEXT_PRIMARY);
    GUI_SetFont(&GUI_Font24B_ASCII);
    GUI_DispStringAt("My Books", (BOOKSELECT_WIDTH - 120) / 2, 12);
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

    /* Selected highlight */
    if (_SelectedIndex >= 0) {
        GUI_RECT r;
        _GetCardRect(_SelectedIndex, &r);
        GUI_SetColor(COLOR_PRIMARY);
        GUI_SetPenSize(3);
        GUI_DrawRoundedRect(r.x0 - 1, r.y0 - 1, r.x1 + 1, r.y1 + 1, 10);
        GUI_SetPenSize(1);
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

    /* Check Back button */
    if (pState->x >= 0 && pState->x <= 100 &&
        pState->y >= 0 && pState->y <= BS_HEADER_H) {
        BookSelect_Hide();
        WM_ShowWindow(WM_HBKWIN);
        return;
    }

    /* Check each book card */
    for (i = 0; i < (int)BOOK_COUNT; i++) {
        GUI_RECT r;
        _GetCardRect(i, &r);
        if (pState->x >= r.x0 && pState->x <= r.x1 &&
            pState->y >= r.y0 && pState->y <= r.y1) {
            _SelectedIndex = i;
            WM_InvalidateWindow(_hScreen);
            /* Navigate to reader, push selected book data to SCREEN_03 */
            BookSelect_Hide();
            {
                APPW_ROOT_INFO *pRoot = APPW_GetRootInfoByRootId(ID_SCREEN_03);
                if (pRoot) {
                    WM_HWIN hRoot;
                    char buf[32];
                    BOOK_INFO *bk = &_Books[_SelectedIndex];

                    hRoot = APPW_CreateRoot(pRoot, WM_HBKWIN);

                    /* Update title */
                    TEXT_SetText(WM_GetDialogItem(hRoot, TEXT_TITLE), bk->Title);

                    /* Update page info */
                    sprintf(buf, "Page 1 / 10");
                    TEXT_SetText(WM_GetDialogItem(hRoot, TEXT_PAGE), buf);

                    /* Update progress bar */
                    PROGBAR_SetValue(WM_GetDialogItem(hRoot, PROGRESS_BAR), bk->Progress);

                    WM_ShowWindow(hRoot);
                }
            }
            return;
        }
    }
}

/*********************************************************************
*
*       Public code
*/

/*********************************************************************
*
*       cbBookSelect
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

/*********************************************************************
*
*       BookSelect_Create
*/
void BookSelect_Create(void) {
    if (_hScreen == 0) {
        _hScreen = WM_CreateWindowAsChild(0, 0,
            BOOKSELECT_WIDTH, BOOKSELECT_HEIGHT,
            WM_HBKWIN, WM_CF_SHOW | WM_CF_MEMDEV,
            cbBookSelect, 0);
    }
}

/*********************************************************************
*
*       BookSelect_Show
*/
void BookSelect_Show(void) {
    if (_hScreen == 0) {
        BookSelect_Create();
    }
    WM_ShowWindow(_hScreen);
    WM_BringToTop(_hScreen);
    WM_InvalidateWindow(_hScreen);
}

/*********************************************************************
*
*       BookSelect_Hide
*/
void BookSelect_Hide(void) {
    if (_hScreen != 0) {
        WM_HideWindow(_hScreen);
    }
}

/*********************************************************************
*
*       BookSelect_GetSelectedBook
*/
const BOOK_INFO *BookSelect_GetSelectedBook(void) {
    if (_SelectedIndex >= 0 && _SelectedIndex < (int)BOOK_COUNT) {
        return &_Books[_SelectedIndex];
    }
    return &_Books[0];
}

/*************************** End of file ****************************/
