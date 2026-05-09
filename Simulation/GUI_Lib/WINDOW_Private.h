/*********************************************************************
*                  (c) SEGGER Microcontroller GmbH                   *
*                        The Embedded Experts                        *
*                           www.segger.com                           *
**********************************************************************

----------------------------------------------------------------------
File        : WINDOW_Private.h
Purpose     : WINDOW private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef WINDOW_PRIVATE_H
#define WINDOW_PRIVATE_H

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  WM_CALLBACK * cb;
  WM_HWIN hFocusedChild;
  WM_DIALOG_STATUS * pDialogStatus;
  GUI_COLOR BkColor;
} WINDOW_OBJ;

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/

extern GUI_COLOR WINDOW__DefaultBkColor;

#endif   /* GUI_WINSUPPORT */
#endif   /* WINDOW_PRIVATE_H */

/*************************** End of file ****************************/
