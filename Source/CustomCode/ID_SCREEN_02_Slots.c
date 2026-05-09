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
Purpose     : Book selection screen
              Action flag set by BookSelect, navigation via timer
              in SCREEN_02 callback (safe AppWizard context).
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_02.h"
#include "../Generated/ID_SCREEN_03.h"
#include "BookSelect.h"
#include <stdio.h>

/*** Begin of user code area ***/

#define TIMER_ACTION  10

static WM_HWIN _hScreen02 = 0;
static WM_HMEM _hTimer    = 0;
static int    _gAction    = 0;

static void _DoOpen(void) {
    const BOOK_INFO *bk;
    APPW_ROOT_INFO *pRoot03;
    WM_HWIN hReader, hItem;
    char buf[32];

    bk = BookSelect_GetSelectedBook();
    pRoot03 = APPW_GetRootInfoByRootId(ID_SCREEN_03);
    if (!pRoot03 || !bk) return;

    hReader = APPW_CreateRoot(pRoot03, WM_HBKWIN);
    if (!hReader) return;

    hItem = WM_GetDialogItem(hReader, TEXT_TITLE);
    if (hItem) TEXT_SetText(hItem, bk->Title);

    hItem = WM_GetDialogItem(hReader, TEXT_PAGE);
    sprintf(buf, "Page 1 / 10");
    if (hItem) TEXT_SetText(hItem, buf);

    hItem = WM_GetDialogItem(hReader, PROGRESS_BAR);
    if (hItem) PROGBAR_SetValue(hItem, bk->Progress);

    /* Trigger AppWizard SCREEN_02 → SCREEN_03 */
    {
        WM_HWIN hBtn = WM_GetDialogItem(_hScreen02, ID_BUTTON_00);
        if (hBtn) {
            WM_MESSAGE msg;
            msg.MsgId = WM_NOTIFY_PARENT;
            msg.Data.v = WM_NOTIFICATION_CLICKED;
            msg.hWinSrc = hBtn;
            WM_SendMessage(_hScreen02, &msg);
        }
    }
}

static void _DoBack(void) {
    WM_HWIN hBtn = WM_GetDialogItem(_hScreen02, ID_BUTTON_01);
    if (hBtn) {
        WM_MESSAGE msg;
        msg.MsgId = WM_NOTIFY_PARENT;
        msg.Data.v = WM_NOTIFICATION_CLICKED;
        msg.hWinSrc = hBtn;
        WM_SendMessage(_hScreen02, &msg);
    }
}

/* Called from BookSelect touch handler - sets flag, starts timer */
static void _ActionCallback(int action) {
    _gAction = action;
    if (_hTimer == 0) {
        _hTimer = WM_CreateTimer(_hScreen02, TIMER_ACTION, 50, 0);
    }
}

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*/

void cbID_SCREEN_02(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      _hScreen02 = pMsg->hWin;
      BookSelect_Create(_hScreen02, _ActionCallback);
      BookSelect_Show();
      break;

    case WM_TIMER:
      WM_DeleteTimer(_hTimer);
      _hTimer = 0;
      if (_gAction == 1) {
        _gAction = 0;
        _DoOpen();
      } else if (_gAction == 2) {
        _gAction = 0;
        _DoBack();
      }
      break;

    default:
      break;
  }
}

/*********************************************************************
*
*       ID_SCREEN_02__ID_BUTTON_00__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_02__ID_BUTTON_00__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
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
