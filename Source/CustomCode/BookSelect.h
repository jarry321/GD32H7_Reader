/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*        Solutions for real time microcontroller applications        *
**********************************************************************
----------------------------------------------------------------------
File        : BookSelect.h
Purpose     : Book Selection Screen - draws grid, handles touch
              Calls action callback for navigation (AppWizard-safe)
---------------------------END-OF-HEADER------------------------------
*/

#ifndef BOOKSELECT_H
#define BOOKSELECT_H

#include "AppWizard.h"
#include "CustomWidgets.h"

#define BOOKSELECT_WIDTH    1024
#define BOOKSELECT_HEIGHT   600     /* Full screen - action areas in header */

#define BS_HEADER_H         56
#define CARD_W              224
#define CARD_H              236
#define CARD_GAP_X          16
#define CARD_GAP_Y          16
#define GRID_LEFT           ((BOOKSELECT_WIDTH - 4 * CARD_W - 3 * CARD_GAP_X) / 2)
#define GRID_TOP            (BS_HEADER_H + 16)
#define COVER_H             150
#define MAX_BOOKS           12

typedef struct {
    const char *Title;
    const char *Author;
    uint8_t     Progress;
    GUI_COLOR   CoverColor;
} BOOK_INFO;

/* Action callback: 0 = open selected book, 1 = back to menu */
typedef void (*BS_ACTION_CB)(int action);

void BookSelect_Create(WM_HWIN hParent, BS_ACTION_CB cb);
void BookSelect_Show(void);
void BookSelect_Hide(void);
void cbBookSelect(WM_MESSAGE *pMsg);
const BOOK_INFO *BookSelect_GetSelectedBook(void);
int  BookSelect_GetSelectedIndex(void);

#endif
