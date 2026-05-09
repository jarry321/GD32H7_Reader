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

/*** Begin of user code area ***/
// Sample book title for display
static const char* _sBookTitle = "Sample Book Title";

// Sample book content for display
static const char* _sBookContent = 
    "This is a sample book content.\n\n"
    "It contains multiple paragraphs and some text.\n\n"
    "The content is designed to simulate a real e-book reader interface.\n\n"
    "You can add more text here as needed.";

// Page information string
static const char* _sPageInfo = "Page 1 / 10";
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
        // Set the book title text
        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, TEXT_TITLE), _sBookTitle);
        
        // Set the book content text
        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, TEXT_CONTENT), _sBookContent);
        
        // Set the page info text
        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, TEXT_PAGE), _sPageInfo);
        
        // Set the progress bar value with error checking

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
