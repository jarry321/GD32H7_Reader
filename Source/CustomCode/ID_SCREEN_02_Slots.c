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
Purpose     : Book selection screen - hosts BookSelect overlay
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_02.h"
#include "../Generated/ID_SCREEN_03.h"
#include "BookSelect.h"
#include <stdio.h>

/*** Begin of user code area ***/

static void _ActionCallback(int action);

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*/

void cbID_SCREEN_02(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      BookSelect_Create(pMsg->hWin, _ActionCallback);
      BookSelect_Show();
      break;
    default:
      break;
  }
}

/*********************************************************************
*
*       _ActionCallback - called from BookSelect on Back/Open touch
*/
static void _ActionCallback(int action) {
  if (action == 0) {
    /* Open: update SCREEN_03 then navigate */
    const BOOK_INFO *bk = BookSelect_GetSelectedBook();
    APPW_ROOT_INFO *pRoot03 = APPW_GetRootInfoByRootId(ID_SCREEN_03);
    WM_HWIN hReader, hItem;
    char buf[32];

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

    WM_ShowWindow(hReader);

  } else {
    /* Back: return to SCREEN_00 */
    APPW_ROOT_INFO *pRoot00 = APPW_GetRootInfoByRootId(ID_SCREEN_00);
    if (pRoot00) {
      WM_HWIN hMenu = APPW_CreateRoot(pRoot00, WM_HBKWIN);
      WM_ShowWindow(hMenu);
    }
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
