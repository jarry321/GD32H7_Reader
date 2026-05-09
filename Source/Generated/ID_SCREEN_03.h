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
File        : ID_SCREEN_03.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef ID_SCREEN_03_H
#define ID_SCREEN_03_H

#include "AppWizard.h"

/*********************************************************************
*
*       Objects
*/
#define ID_IMAGE_00  (GUI_ID_USER + 9)
#define TEXT_TITLE   (GUI_ID_USER + 1)
#define TEXT_CONTENT (GUI_ID_USER + 2)
#define TEXT_PAGE    (GUI_ID_USER + 3)
#define PROGRESS_BAR (GUI_ID_USER + 4)
#define BTN_MENU     (GUI_ID_USER + 6)
#define BTN_PREV     (GUI_ID_USER + 7)
#define BTN_NEXT     (GUI_ID_USER + 8)
#define BTN_BACK     (GUI_ID_USER + 5)

/*********************************************************************
*
*       Slots
*/
void ID_SCREEN_03__BTN_MENU__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_03__BTN_BACK__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);

/*********************************************************************
*
*       Callback
*/
void cbID_SCREEN_03(WM_MESSAGE * pMsg);

#endif  // ID_SCREEN_03_H

/*************************** End of file ****************************/
