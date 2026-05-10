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
Purpose     : Book selection - book buttons created as children of
              SCREEN_02. Navigation via AppWizard buttons only.
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_02.h"
#include "../Generated/ID_SCREEN_03.h"
#include "CustomWidgets.h"

/*** Begin of user code area ***/

#define TIMER_INIT  1

static const char *_BookTitles[] = {
    "San Ti - Liu Cixin",
    "To Live - Yu Hua",
    "Fortress Besieged",
    "One Hundred Years",
    "Dream of Red Mansions",
    "Camel Xiangzi",
    "The Kite Runner",
    "Ordinary World",
};
#define BOOK_COUNT (sizeof(_BookTitles) / sizeof(_BookTitles[0]))

static int     _Selected = 0;
static WM_HMEM _hTimer  = 0;

/* Book button callback - only records selection, no AppWizard calls */
static void _BookBtnCb(WM_MESSAGE *pMsg) {
    int idx;
    switch (pMsg->MsgId) {
        case WM_NOTIFICATION_CLICKED:
            WM_GetUserData(pMsg->hWin, &idx, sizeof(idx));
            _Selected = idx;
            break;
        default:
            BUTTON_Callback(pMsg);
            break;
    }
}

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*/

void cbID_SCREEN_02(WM_MESSAGE * pMsg) {
  int i, col, row, x, y;
  WM_HWIN hBtn;

  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      _hTimer = WM_CreateTimer(pMsg->hWin, TIMER_INIT, 30, 0);
      break;

    case WM_TIMER:
      WM_DeleteTimer(_hTimer);
      _hTimer = 0;
      /* Create 8 book buttons as children of SCREEN_02 */
      for (i = 0; i < (int)BOOK_COUNT; i++) {
        col = i % 4;
        row = i / 4;
        x = 16 + col * 246;
        y = 220 + row * 72;
        hBtn = BUTTON_CreateEx(x, y, 230, 60, pMsg->hWin,
                                WM_CF_SHOW, 0, GUI_ID_USER + 100 + i);
        BUTTON_SetText(hBtn, _BookTitles[i]);
        BUTTON_SetFont(hBtn, &GUI_Font13_ASCII);
        WM_SetCallback(hBtn, _BookBtnCb);
        WM_SetUserData(hBtn, &i, sizeof(i));
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
*  MINIBLUE button → SCREEN_03. Set selected book before navigate.
*/
void ID_SCREEN_02__ID_BUTTON_00__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  WM_HWIN hItem;
  char buf[32];

  GUI_USE_PARA(pAction);
  GUI_USE_PARA(pMsg);

  /* This IS AppWizard slot context - safe to call AppWizard functions */
  {
    APPW_ROOT_INFO *pRoot = APPW_GetRootInfoByRootId(ID_SCREEN_03);
    if (pRoot) {
      WM_HWIN hReader = APPW_CreateRoot(pRoot, WM_HBKWIN);
      if (hReader) {
        hItem = WM_GetDialogItem(hReader, TEXT_TITLE);
        if (hItem) TEXT_SetText(hItem, _BookTitles[_Selected]);

        hItem = WM_GetDialogItem(hReader, TEXT_PAGE);
        sprintf(buf, "Page 1 / 10");
        if (hItem) TEXT_SetText(hItem, buf);

        hItem = WM_GetDialogItem(hReader, PROGRESS_BAR);
        if (hItem) PROGBAR_SetValue(hItem, 15);
      }
    }
  }

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
