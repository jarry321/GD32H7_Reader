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
Purpose     : AppWizard managed file, function content could be changed
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_02.h"
#include "../Generated/ID_SCREEN_03.h"
#include "BookSelect.h"

/*** Begin of user code area ***/

#define WM_BACK_TO_MENU  (WM_USER + 0x11)

/* Forward the AppWizard transition to SCREEN_03 via Button_00 */
static void _NavigateToReader(WM_HWIN hScreen02) {
    WM_HWIN hBtn = WM_GetDialogItem(hScreen02, ID_BUTTON_00);
    if (hBtn) {
        WM_MESSAGE msg;
        msg.MsgId = WM_NOTIFY_PARENT;
        msg.Data.v = WM_NOTIFICATION_CLICKED;
        msg.hWinSrc = hBtn;
        WM_SendMessage(hScreen02, &msg);
    }
}

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       cbID_SCREEN_02
*/
void cbID_SCREEN_02(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      BookSelect_Create(pMsg->hWin);
      BookSelect_Show();
      break;

    case WM_BOOK_SELECTED:
      /* Book was chosen → update SCREEN_03 widgets, then navigate */
      {
        const BOOK_INFO *bk = BookSelect_GetSelectedBook();
        APPW_ROOT_INFO *pRoot03 = APPW_GetRootInfoByRootId(ID_SCREEN_03);
        char buf[32];

        if (pRoot03 && bk) {
          WM_HWIN hReader = APPW_CreateRoot(pRoot03, WM_HBKWIN);
          TEXT_SetText(WM_GetDialogItem(hReader, TEXT_TITLE), bk->Title);
          sprintf(buf, "Page 1 / 10");
          TEXT_SetText(WM_GetDialogItem(hReader, TEXT_PAGE), buf);
          PROGBAR_SetValue(WM_GetDialogItem(hReader, PROGRESS_BAR), bk->Progress);
        }
        _NavigateToReader(pMsg->hWin);
      }
      break;

    case WM_BACK_TO_MENU:
      /* BookSelect back → trigger SCREEN_02 Button_01 (goes to SCREEN_00) */
      {
        WM_HWIN hBtn = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_01);
        if (hBtn) {
          WM_MESSAGE msg;
          msg.MsgId = WM_NOTIFY_PARENT;
          msg.Data.v = WM_NOTIFICATION_CLICKED;
          msg.hWinSrc = hBtn;
          WM_SendMessage(pMsg->hWin, &msg);
        }
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
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_02__ID_BUTTON_01__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_02__ID_BUTTON_01__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*************************** End of file ****************************/
