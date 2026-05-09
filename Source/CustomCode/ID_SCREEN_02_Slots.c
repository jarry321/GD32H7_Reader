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
Purpose     : Book selection - hosts BookSelect overlay + action buttons
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_02.h"
#include "../Generated/ID_SCREEN_03.h"
#include "BookSelect.h"
#include <stdio.h>

/*** Begin of user code area ***/

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*/

/*********************************************************************
*
*       cbID_SCREEN_02
*/
void cbID_SCREEN_02(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG: {
      WM_HWIN hBtn00, hBtn01;

      /* Reposition Button_00 (MINIBLUE) to bottom: "Open Book" */
      hBtn00 = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_00);
      if (hBtn00) {
        WM_MoveTo(hBtn00, 362, 540);
        WM_SetSize(hBtn00, 300, 50);
        BUTTON_SetText(hBtn00, "Open Book");
      }

      /* Reposition Button_01 to top-right: "Back" */
      hBtn01 = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_01);
      if (hBtn01) {
        WM_MoveTo(hBtn01, 924, 12);
        WM_SetSize(hBtn01, 80, 32);
        BUTTON_SetText(hBtn01, "Back");
      }

      /* Create book grid overlay (does NOT cover button area at bottom) */
      BookSelect_Create(pMsg->hWin);
      BookSelect_Show();
      break;
    }

    default:
      break;
  }
}

/*********************************************************************
*
*       ID_SCREEN_02__ID_BUTTON_00__WM_NOTIFICATION_CLICKED
*
*  Emitter:  ID_BUTTON_00 (now repurposed as "Open Book")
*  Job:      Push selected book data to SCREEN_03, then navigate
*/
void ID_SCREEN_02__ID_BUTTON_00__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  const BOOK_INFO *bk;
  APPW_ROOT_INFO *pRoot03;
  WM_HWIN hReader;
  char buf[32];

  GUI_USE_PARA(pAction);
  GUI_USE_PARA(pMsg);

  bk = BookSelect_GetSelectedBook();
  pRoot03 = APPW_GetRootInfoByRootId(ID_SCREEN_03);

  if (pRoot03 && bk) {
    hReader = APPW_CreateRoot(pRoot03, WM_HBKWIN);
    TEXT_SetText(WM_GetDialogItem(hReader, TEXT_TITLE), bk->Title);
    sprintf(buf, "Page 1 / 10");
    TEXT_SetText(WM_GetDialogItem(hReader, TEXT_PAGE), buf);
    PROGBAR_SetValue(WM_GetDialogItem(hReader, PROGRESS_BAR), bk->Progress);
  }

  /* Let AppWizard handle the SCREEN_02 → SCREEN_03 transition */
  *pResult = 0;
}

/*********************************************************************
*
*       ID_SCREEN_02__ID_BUTTON_01__WM_NOTIFICATION_CLICKED
*
*  Emitter:  ID_BUTTON_01 (now repurposed as "Back")
*  Job:      Return to SCREEN_00 main menu
*/
void ID_SCREEN_02__ID_BUTTON_01__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);

  /* Let AppWizard handle SCREEN_02 → SCREEN_00 transition */
  *pResult = 0;
}

/*************************** End of file ****************************/
