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
File        : ID_SCREEN_02_Slots.c
Purpose     : Book selection - pure AppWizard: book buttons + slot nav
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_02.h"
#include "../Generated/ID_SCREEN_03.h"
#include "CustomWidgets.h"
#include <string.h>
#include <stdio.h>

/*** Begin of user code area ***/

#define TIMER_INIT  1

/* Book data (titles only for button labels) */
static const char *_BookTitles[] = {
    "San Ti - Liu Cixin",
    "To Live - Yu Hua",
    "Fortress Besieged - Qian Zhongshu",
    "One Hundred Years - Garcia Marquez",
    "Dream of Red Mansions - Cao Xueqin",
    "Camel Xiangzi - Lao She",
    "The Kite Runner - Khaled Hosseini",
    "Ordinary World - Lu Yao",
};
#define BOOK_COUNT (sizeof(_BookTitles) / sizeof(_BookTitles[0]))

static int     _Selected = 0;
static WM_HMEM _hTimer  = 0;

/* Custom callback for book buttons - records selection, forwards rest */
static void _BookBtnCb(WM_MESSAGE *pMsg) {
    switch (pMsg->MsgId) {
        case WM_NOTIFICATION_CLICKED:
            {
                int idx;
                WM_GetUserData(pMsg->hWin, &idx, sizeof(idx));
                _Selected = idx;
            }
            break;
        default:
            BUTTON_Callback(pMsg);
            break;
    }
}

static WM_HWIN _hScreen02 = 0;

/* From ID_SCREEN_03_Slots.c */
extern void Reader_SetSelectedBook(int index);

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*/

void cbID_SCREEN_02(WM_MESSAGE * pMsg) {
  int i;
  int col, row, x, y;
  WM_HWIN hBtn;

  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      _hScreen02 = pMsg->hWin;
      _hTimer = WM_CreateTimer(_hScreen02, TIMER_INIT, 30, 0);
      break;

    case WM_TIMER:
      WM_DeleteTimer(_hTimer);
      _hTimer = 0;
      /* Create book selection buttons in 4x2 grid below MINIBLUE (y=210) */
      for (i = 0; i < (int)BOOK_COUNT; i++) {
        col = i % 4;
        row = i / 4;
        x = 16 + col * 248;
        y = 210 + row * 86;
        hBtn = BUTTON_CreateEx(x, y, 232, 72, _hScreen02,
                                WM_CF_SHOW, 0, GUI_ID_USER + 100 + i);
        BUTTON_SetText(hBtn, _BookTitles[i]);
        BUTTON_SetFont(hBtn, &GUI_Font16_ASCII);
        BUTTON_SetBkColor(hBtn, BUTTON_CI_UNPRESSED, COLOR_CARD_BG);
        BUTTON_SetBkColor(hBtn, BUTTON_CI_PRESSED, COLOR_PRIMARY);
        BUTTON_SetTextColor(hBtn, BUTTON_CI_UNPRESSED, COLOR_TEXT_PRIMARY);
        BUTTON_SetTextColor(hBtn, BUTTON_CI_PRESSED, GUI_WHITE);
        WM_SetCallback(hBtn, _BookBtnCb);
        WM_SetUserData(hBtn, &i, sizeof(i));
      }
      /* Update existing AppWizard buttons - only text, NO repositioning */
      hBtn = WM_GetDialogItem(_hScreen02, ID_BUTTON_00);
      if (hBtn) {
        BUTTON_SetText(hBtn, "Read");
      }
      hBtn = WM_GetDialogItem(_hScreen02, ID_BUTTON_01);
      if (hBtn) {
        BUTTON_SetText(hBtn, "Back");
      }
      break;

    default:
      break;
  }
}

/*********************************************************************
*
*       ID_SCREEN_02__ID_BUTTON_00__WM_NOTIFICATION_CLICKED
*
*  Emitter:  ID_BUTTON_00 (now "Read Selected Book")
*  Job:      Update SCREEN_03 with selected book, then navigate
*/
void ID_SCREEN_02__ID_BUTTON_00__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(pMsg);

  /* Tell SCREEN_03 which book was selected */
  Reader_SetSelectedBook(_Selected);

  /* Let AppWizard handle SCREEN_02 → SCREEN_03 transition */
  *pResult = 0;
}

/*********************************************************************
*
*       ID_SCREEN_02__ID_BUTTON_01__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_02__ID_BUTTON_01__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  *pResult = 0;
}

/*************************** End of file ****************************/
