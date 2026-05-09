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
File        : ID_SCREEN_05.h
Purpose     : RFID Tag List Screen - Header file
---------------------------END-OF-HEADER------------------------------
*/

#ifndef ID_SCREEN_05_H
#define ID_SCREEN_05_H

#include "AppWizard.h"
#include "CustomWidgets.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_SCREEN_05    (GUI_ID_USER + 200)

// Object IDs
#define ID_BUTTON_BACK      (GUI_ID_USER + 201)
#define ID_BUTTON_REFRESH   (GUI_ID_USER + 202)
#define ID_BUTTON_SEARCH    (GUI_ID_USER + 203)
#define ID_LIST_TAGS        (GUI_ID_USER + 204)
#define ID_TEXT_TITLE       (GUI_ID_USER + 205)
#define ID_TEXT_COUNT       (GUI_ID_USER + 206)

// Screen dimensions
#define SCREEN_05_WIDTH     1024
#define SCREEN_05_HEIGHT    600

// Layout constants
#define STATUS_BAR_HEIGHT   48
#define HEADER_HEIGHT       56
#define LIST_Y_POS          (STATUS_BAR_HEIGHT + HEADER_HEIGHT)
#define LIST_HEIGHT         (SCREEN_05_HEIGHT - LIST_Y_POS - 40)

/*********************************************************************
*
*       Functions
*
**********************************************************************
*/
void cbID_SCREEN_05(WM_MESSAGE *pMsg);
void ID_SCREEN_05_Create(void);
void ID_SCREEN_05_Show(void);
void ID_SCREEN_05_Hide(void);

#endif  // ID_SCREEN_05_H

/*************************** End of file ****************************/
