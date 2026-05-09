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
              BookSelect draws the grid. Custom std buttons at bottom
              handle navigation without AppWizard internals.
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
static WM_HWIN _hBtnOpen  = 0;
static WM_HWIN _hBtnBack  = 0;

/* Standard emWin callback for custom Open/Back buttons */
static void _BtnCallback(WM_MESSAGE *pMsg) {
    WM_HWIN hWin = pMsg->hWin;
    int Id = WM_GetId(hWin);

    switch (pMsg->MsgId) {
        case WM_PAINT:
            BUTTON_Callback(pMsg);  /* default button paint */
            break;

        case WM_NOTIFICATION_CLICKED:
            if (Id == GUI_ID_USER + 50) {
                /* Open Book: update SCREEN_03 then show it */
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

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*/

void cbID_SCREEN_02(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      _hScreen02 = pMsg->hWin;

      /* Create custom Open button at bottom */
      _hBtnOpen = BUTTON_CreateEx(312, 550, 180, 42, _hScreen02,
                                   WM_CF_SHOW, 0, GUI_ID_USER + 50);
      BUTTON_SetText(_hBtnOpen, "Open Book");
      BUTTON_SetFont(_hBtnOpen, &GUI_Font16B_ASCII);
      BUTTON_SetBkColor(_hBtnOpen, BUTTON_CI_UNPRESSED, COLOR_PRIMARY);
      BUTTON_SetTextColor(_hBtnOpen, BUTTON_CI_UNPRESSED, GUI_WHITE);
      WM_SetCallback(_hBtnOpen, _BtnCallback);

      /* Create custom Back button at bottom */
      _hBtnBack = BUTTON_CreateEx(532, 550, 180, 42, _hScreen02,
                                   WM_CF_SHOW, 0, GUI_ID_USER + 51);
      BUTTON_SetText(_hBtnBack, "Back");
      BUTTON_SetFont(_hBtnBack, &GUI_Font16B_ASCII);
      BUTTON_SetBkColor(_hBtnBack, BUTTON_CI_UNPRESSED, COLOR_SECONDARY);
      BUTTON_SetTextColor(_hBtnBack, BUTTON_CI_UNPRESSED, GUI_WHITE);
      WM_SetCallback(_hBtnBack, _BtnCallback);

      /* Create book grid overlay */
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
