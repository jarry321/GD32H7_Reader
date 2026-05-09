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
File        : ID_SCREEN_03_Slots.c
Purpose     : Reader screen - displays selected book info
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_03.h"
#include "CustomWidgets.h"
#include <stdio.h>

/*** Begin of user code area ***/

/* Book titles - must match SCREEN_02 list */
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

static int  _Selected = 0;
static char _sPageInfo[32];

/* Called by SCREEN_02 to set the selected book index */
void Reader_SetSelectedBook(int index) {
    if (index >= 0 && index < 8) _Selected = index;
}

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*/

void cbID_SCREEN_03(WM_MESSAGE * pMsg) {
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, TEXT_TITLE), _BookTitles[_Selected]);
        sprintf(_sPageInfo, "Page 1 / 10");
        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, TEXT_PAGE), _sPageInfo);
        PROGBAR_SetValue(WM_GetDialogItem(pMsg->hWin, PROGRESS_BAR), 15);
        break;
    }
}

/*********************************************************************
*
*       ID_SCREEN_03__BTN_MENU__WM_NOTIFICATION_CLICKED
*
*  Repurposed: go BACK to book list instead of SCREEN_04
*/
void ID_SCREEN_03__BTN_MENU__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  /* Prevent default (to SCREEN_04), do same as Back */
  *pResult = 1;
  /* Manually trigger back via AppWizard button */
  {
    WM_HWIN hBtnBack = WM_GetDialogItem(hScreen, BTN_BACK);
    if (hBtnBack) {
      WM_MESSAGE msg;
      msg.MsgId = WM_NOTIFY_PARENT;
      msg.Data.v = WM_NOTIFICATION_CLICKED;
      msg.hWinSrc = hBtnBack;
      WM_SendMessage(hScreen, &msg);
    }
  }
}

/*********************************************************************
*
*       ID_SCREEN_03__BTN_BACK__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_03__BTN_BACK__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  *pResult = 0;
}

/*************************** End of file ****************************/
