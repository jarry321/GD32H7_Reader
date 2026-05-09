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
              Action callback triggers AppWizard navigation
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_02.h"
#include "../Generated/ID_SCREEN_03.h"
#include "BookSelect.h"
#include <stdio.h>

/*** Begin of user code area ***/

static WM_HWIN _hScreen02 = 0;

static void _TriggerAppWizardButton(WM_HWIN hScreen, int btnId) {
    WM_HWIN hBtn = WM_GetDialogItem(hScreen, btnId);
    if (hBtn) {
        WM_MESSAGE msg;
        msg.MsgId = WM_NOTIFY_PARENT;
        msg.Data.v = WM_NOTIFICATION_CLICKED;
        msg.hWinSrc = hBtn;
        WM_SendMessage(hScreen, &msg);
    }
}

/* Called from BookSelect touch handler on Back(1) or Open(0) */
static void _ActionCallback(int action) {
    if (action == 0) {
        /* Open: set SCREEN_03 data BEFORE AppWizard transitions */
        const BOOK_INFO *bk = BookSelect_GetSelectedBook();
        APPW_ROOT_INFO *pRoot03 = APPW_GetRootInfoByRootId(ID_SCREEN_03);
        if (pRoot03 && bk) {
            WM_HWIN hReader, hItem;
            char buf[32];
            hReader = APPW_CreateRoot(pRoot03, WM_HBKWIN);
            if (hReader) {
                hItem = WM_GetDialogItem(hReader, TEXT_TITLE);
                if (hItem) TEXT_SetText(hItem, bk->Title);
                hItem = WM_GetDialogItem(hReader, TEXT_PAGE);
                sprintf(buf, "Page 1 / 10");
                if (hItem) TEXT_SetText(hItem, buf);
                hItem = WM_GetDialogItem(hReader, PROGRESS_BAR);
                if (hItem) PROGBAR_SetValue(hItem, bk->Progress);
            }
        }
        /* Let AppWizard do SCREEN_02 → SCREEN_03 transition */
        _TriggerAppWizardButton(_hScreen02, ID_BUTTON_00);
    } else {
        /* Back: let AppWizard do SCREEN_02 → SCREEN_00 transition */
        _TriggerAppWizardButton(_hScreen02, ID_BUTTON_01);
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
