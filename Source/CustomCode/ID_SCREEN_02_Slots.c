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
              Uses timer to defer UI creation (avoid message nesting)
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_02.h"
#include "../Generated/ID_SCREEN_03.h"
#include "BookSelect.h"
#include <stdio.h>

/*** Begin of user code area ***/

#define TIMER_INIT   1

static WM_HWIN _hScreen02 = 0;

static void _BtnCallback(WM_MESSAGE *pMsg) {
    int Id = WM_GetId(pMsg->hWin);

    switch (pMsg->MsgId) {
        case WM_PAINT:
            BUTTON_Callback(pMsg);
            break;

        case WM_NOTIFICATION_CLICKED:
            if (Id == GUI_ID_USER + 50) {
                /* Open Book */
                const BOOK_INFO *bk = BookSelect_GetSelectedBook();
                APPW_ROOT_INFO *pRoot = APPW_GetRootInfoByRootId(ID_SCREEN_03);
                if (pRoot && bk) {
                    WM_HWIN hReader = APPW_CreateRoot(pRoot, WM_HBKWIN);
                    WM_HWIN hItem;
                    char buf[32];

                    hItem = WM_GetDialogItem(hReader, TEXT_TITLE);
                    if (hItem) TEXT_SetText(hItem, bk->Title);

                    hItem = WM_GetDialogItem(hReader, TEXT_PAGE);
                    sprintf(buf, "Page 1 / 10");
                    if (hItem) TEXT_SetText(hItem, buf);

                    hItem = WM_GetDialogItem(hReader, PROGRESS_BAR);
                    if (hItem) PROGBAR_SetValue(hItem, bk->Progress);

                    WM_ShowWindow(hReader);
                }
            } else if (Id == GUI_ID_USER + 51) {
                /* Back to SCREEN_00 */
                APPW_ROOT_INFO *pRoot = APPW_GetRootInfoByRootId(ID_SCREEN_00);
                if (pRoot) {
                    WM_HWIN hMenu = APPW_CreateRoot(pRoot, WM_HBKWIN);
                    WM_ShowWindow(hMenu);
                }
            }
            break;

        default:
            WM_DefaultProc(pMsg);
            break;
    }
}

static void _CreateButtons(WM_HWIN hParent) {
    WM_HWIN hBtn;

    hBtn = BUTTON_CreateEx(312, 550, 180, 42, hParent,
                            WM_CF_SHOW, 0, GUI_ID_USER + 50);
    BUTTON_SetText(hBtn, "Open Book");
    BUTTON_SetFont(hBtn, &GUI_Font16B_ASCII);
    BUTTON_SetBkColor(hBtn, BUTTON_CI_UNPRESSED, COLOR_PRIMARY);
    BUTTON_SetTextColor(hBtn, BUTTON_CI_UNPRESSED, GUI_WHITE);
    WM_SetCallback(hBtn, _BtnCallback);

    hBtn = BUTTON_CreateEx(532, 550, 180, 42, hParent,
                            WM_CF_SHOW, 0, GUI_ID_USER + 51);
    BUTTON_SetText(hBtn, "Back");
    BUTTON_SetFont(hBtn, &GUI_Font16B_ASCII);
    BUTTON_SetBkColor(hBtn, BUTTON_CI_UNPRESSED, COLOR_SECONDARY);
    BUTTON_SetTextColor(hBtn, BUTTON_CI_UNPRESSED, GUI_WHITE);
    WM_SetCallback(hBtn, _BtnCallback);
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
      /* Defer UI creation to avoid message nesting in WM_INIT_DIALOG */
      WM_CreateTimer(pMsg->hWin, TIMER_INIT, 50, 0);
      break;

    case WM_TIMER:
      WM_DeleteTimer(pMsg->hWin, TIMER_INIT);
      _CreateButtons(_hScreen02);
      BookSelect_Create(_hScreen02);
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
