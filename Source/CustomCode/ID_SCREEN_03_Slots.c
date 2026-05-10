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
Purpose     : Reader screen - text display with page navigation
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_03.h"
#include <string.h>
#include <stdio.h>

/*** Begin of user code area ***/

/* Sample book content */
static const char *_SampleText =
    "Chapter 1\n\n"
    "The morning sun cast long shadows across the warehouse floor. "
    "Rows of metal shelves stretched into the distance, each one packed "
    "with boxes and equipment waiting to be catalogued.\n\n"
    "Sarah adjusted her RFID reader and began her daily inventory round. "
    "The device beeped steadily as she moved through the aisles, each "
    "tag responding with its unique identifier. Asset management had "
    "never been this efficient before the new system was installed.\n\n"
    "She paused at section B-12, where the high-value equipment was "
    "stored. The reader display showed 47 items registered, but the "
    "physical count should be 48. One item was missing.\n\n"
    "She cross-referenced the missing tag with the database on her "
    "tablet. The last scan was three days ago, at 4:32 PM. Security "
    "footage would need to be reviewed for that time window.\n\n"
    "Chapter 2\n\n"
    "The next morning brought unexpected news. The missing equipment "
    "had been transferred to another facility without updating the "
    "central database. A simple paperwork error had triggered hours "
    "of unnecessary searching.\n\n"
    "This incident highlighted the importance of real-time tracking "
    "and automated updates. The current system relied too heavily on "
    "manual data entry, creating gaps between physical reality and "
    "digital records.\n\n"
    "By the end of the week, Sarah had proposed a new protocol: every "
    "asset movement would trigger an automatic RFID scan at doorway "
    "checkpoints, eliminating the human error factor entirely.";

/* Page tracking */
static char      _sPageBuf[1024];
static int       _TotalPages = 1;
static int       _CurPage    = 0;

/* Split text into pages of ~800 chars */
static int _CalcPages(const char *text) {
    int len = (int)strlen(text);
    return (len + 799) / 800;
}

/* Get page N content into buf */
static void _GetPage(int page, char *buf, int bufSize) {
    int start = page * 800;
    int len   = (int)strlen(_SampleText);
    int copy  = len - start;
    if (copy > 800) copy = 800;
    if (copy < 0)  copy = 0;
    if (copy >= bufSize) copy = bufSize - 1;
    if (copy > 0) {
        memcpy(buf, _SampleText + start, copy);
    }
    buf[copy] = '\0';
}

/* Refresh content display */
static void _UpdateDisplay(WM_HWIN hScreen) {
    WM_HWIN hItem;
    char buf[32];

    _GetPage(_CurPage, _sPageBuf, sizeof(_sPageBuf));

    hItem = WM_GetDialogItem(hScreen, TEXT_CONTENT);
    if (hItem) TEXT_SetText(hItem, _sPageBuf);

    hItem = WM_GetDialogItem(hScreen, TEXT_PAGE);
    if (hItem) {
        sprintf(buf, "Page %d / %d", _CurPage + 1, _TotalPages);
        TEXT_SetText(hItem, buf);
    }

    hItem = WM_GetDialogItem(hScreen, PROGRESS_BAR);
    if (hItem) {
        int pct = (_TotalPages > 1) ? ((_CurPage + 1) * 100 / _TotalPages) : 100;
        PROGBAR_SetValue(hItem, pct);
    }
}

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*/

void cbID_SCREEN_03(WM_MESSAGE * pMsg) {
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        _TotalPages = _CalcPages(_SampleText);
        _CurPage = 0;
        _UpdateDisplay(pMsg->hWin);
        break;
    }
}

/*********************************************************************
*
*       ID_SCREEN_03__BTN_PREV__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_03__BTN_PREV__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(pMsg);
  if (_CurPage > 0) {
    _CurPage--;
    _UpdateDisplay(hScreen);
  }
  *pResult = 1;
}

/*********************************************************************
*
*       ID_SCREEN_03__BTN_NEXT__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_03__BTN_NEXT__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(pMsg);
  if (_CurPage < _TotalPages - 1) {
    _CurPage++;
    _UpdateDisplay(hScreen);
  }
  *pResult = 1;
}

/*********************************************************************
*
*       ID_SCREEN_03__BTN_MENU__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_03__BTN_MENU__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  *pResult = 0;
}

/*********************************************************************
*
*       ID_SCREEN_03__BTN_BACK__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_03__BTN_BACK__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  *pResult = 0;
}

/*************************** End of file ****************************/
