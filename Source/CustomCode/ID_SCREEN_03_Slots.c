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
Purpose     : AppWizard managed file, function content could be changed
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_03.h"
#include "BookSelect.h"

/*** Begin of user code area ***/
static const BOOK_INFO *_pCurrentBook = 0;
static char _sPageInfo[32];
/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       cbID_SCREEN_03
*/
void cbID_SCREEN_03(WM_MESSAGE * pMsg) {
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        _pCurrentBook = BookSelect_GetSelectedBook();

        if (_pCurrentBook) {
            TEXT_SetText(WM_GetDialogItem(pMsg->hWin, TEXT_TITLE), _pCurrentBook->Title);
        }

        sprintf(_sPageInfo, "Page 1 / 10");
        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, TEXT_PAGE), _sPageInfo);

        PROGBAR_SetValue(WM_GetDialogItem(pMsg->hWin, PROGRESS_BAR),
                         _pCurrentBook ? _pCurrentBook->Progress : 0);
        break;
    }
}

/*********************************************************************
*
*       ID_SCREEN_03__BTN_MENU__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_03__BTN_MENU__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_03__BTN_BACK__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_03__BTN_BACK__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*************************** End of file ****************************/
