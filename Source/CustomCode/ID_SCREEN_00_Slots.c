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
File        : ID_SCREEN_00_Slots.c
Purpose     : AppWizard managed file, function content could be changed
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_00.h"
#include "ID_SCREEN_05.h"
#include "BookSelect.h"

/*** Begin of user code area ***/
/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       cbID_SCREEN_00
*/
void cbID_SCREEN_00(WM_MESSAGE * pMsg) {
  GUI_USE_PARA(pMsg);
}

/*********************************************************************
*
*       ID_SCREEN_00__ID_BUTTON_00__WM_NOTIFICATION_CLICKED
*
*  Emitter:  ID_BUTTON_00
*  Signal:   WM_NOTIFICATION_CLICKED
*  Job:      Show RFID Tag List Screen
*/
void ID_SCREEN_00__ID_BUTTON_00__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  
  // Button 00 (Computer) - show RFID Tag List Screen 05
  ID_SCREEN_05_Create();
  ID_SCREEN_05_Show();
  
  // Prevent default action (don't show ID_SCREEN_02)
  *pResult = 1;
}

/*********************************************************************
*
*       ID_SCREEN_00__ID_BUTTON_01__WM_NOTIFICATION_CLICKED
*
*  Emitter:  ID_BUTTON_01
*  Signal:   WM_NOTIFICATION_CLICKED
*  Job:      Show Book Selection Screen
*/
void ID_SCREEN_00__ID_BUTTON_01__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);

  // Button 01 (Music icon) - show Book Selection screen
  BookSelect_Create();
  BookSelect_Show();

  // Prevent default action
  *pResult = 1;
}

/*********************************************************************
*
*       ID_SCREEN_00__ID_BUTTON_03__WM_NOTIFICATION_CLICKED
*
*  Emitter:  ID_BUTTON_03
*  Signal:   WM_NOTIFICATION_CLICKED
*  Job:      APPW_JOB_SHOWSCREEN
*/
void ID_SCREEN_00__ID_BUTTON_03__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  
  // Button 03 is "Reader" button - show RFID tag list screen
  ID_SCREEN_05_Create();
  ID_SCREEN_05_Show();
  
  *pResult = 0;
}

/*************************** End of file ****************************/
