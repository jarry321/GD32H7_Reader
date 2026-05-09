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
File        : ID_SCREEN_00.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_00.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _aCreate
*/
static APPW_CREATE_ITEM _aCreate[] = {
  { WM_OBJECT_WINDOW_Create,
    ID_SCREEN_00, 0,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_00, ID_SCREEN_00,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      1024, 600, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_00, ID_SCREEN_00,
    { { { DISPOSE_MODE_REL_PARENT, 50, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 55, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      80, 90, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_01, ID_SCREEN_00,
    { { { DISPOSE_MODE_REL_PARENT, 150, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 55, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      80, 90, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_02, ID_SCREEN_00,
    { { { DISPOSE_MODE_REL_PARENT, 250, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 55, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      80, 90, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_03, ID_SCREEN_00,
    { { { DISPOSE_MODE_REL_PARENT, 350, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 55, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      80, 90, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_SCREEN_00, APPW_SET_PROP_MOTIONH,      { ARG_VP(APPW_SWIPE_REPLACE, &ID_SCREEN_01_RootInfo),
                                                ARG_VP(APPW_SWIPE_REPLACE, &ID_SCREEN_01_RootInfo),
                                                ARG_V(200) } },
  { ID_IMAGE_00,  APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_IMAGE_00,  APPW_SET_PROP_SBITMAP,      { ARG_VP(0, acorange_ice_mint_139564_1024x600),
                                                ARG_V(63534), } },
  { ID_BUTTON_00, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, accomputer), } },
  { ID_BUTTON_00, APPW_SET_PROP_COLORS,       { ARG_V(GUI_WHITE),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_00, APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_TOP),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_BUTTON_00, APPW_SET_PROP_COLORS2,      { ARG_V(GUI_WHITE),
                                                ARG_V(GUI_WHITE),
                                                ARG_V(GUI_WHITE) } },
  { ID_BUTTON_00, APPW_SET_PROP_REPEAT,       { ARG_V(500),
                                                ARG_V(100) } },
  { ID_BUTTON_00, APPW_SET_PROP_BKCOLORS,     { ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_00, APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_1) } },
  { ID_BUTTON_00, APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_BUTTON_00, APPW_SET_PROP_FOCUSABLE,    { ARG_V(0) } },
  { ID_BUTTON_00, APPW_SET_PROP_RADIUS,       { ARG_V(0) } },
  { ID_BUTTON_00, APPW_SET_PROP_FRAME,        { ARG_V(1) } },
  { ID_BUTTON_00, APPW_SET_PROP_FONT,         { ARG_VPF(0, acNotoSans_16_Normal_EXT_AA4, &APPW__aFont[0]) } },
  { ID_BUTTON_01, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acmusic), } },
  { ID_BUTTON_01, APPW_SET_PROP_COLORS,       { ARG_V(GUI_WHITE),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_01, APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_TOP),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_BUTTON_01, APPW_SET_PROP_COLORS2,      { ARG_V(GUI_WHITE),
                                                ARG_V(GUI_WHITE),
                                                ARG_V(GUI_WHITE) } },
  { ID_BUTTON_01, APPW_SET_PROP_REPEAT,       { ARG_V(500),
                                                ARG_V(100) } },
  { ID_BUTTON_01, APPW_SET_PROP_BKCOLORS,     { ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_01, APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_0) } },
  { ID_BUTTON_01, APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_BUTTON_01, APPW_SET_PROP_FOCUSABLE,    { ARG_V(0) } },
  { ID_BUTTON_01, APPW_SET_PROP_RADIUS,       { ARG_V(0) } },
  { ID_BUTTON_01, APPW_SET_PROP_FRAME,        { ARG_V(1) } },
  { ID_BUTTON_01, APPW_SET_PROP_FONT,         { ARG_VPF(0, acNotoSans_16_Normal_EXT_AA4, &APPW__aFont[0]) } },
  { ID_BUTTON_02, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acVideo), } },
  { ID_BUTTON_02, APPW_SET_PROP_COLORS,       { ARG_V(GUI_WHITE),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_02, APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_TOP),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_BUTTON_02, APPW_SET_PROP_COLORS2,      { ARG_V(GUI_WHITE),
                                                ARG_V(GUI_WHITE),
                                                ARG_V(GUI_WHITE) } },
  { ID_BUTTON_02, APPW_SET_PROP_REPEAT,       { ARG_V(500),
                                                ARG_V(100) } },
  { ID_BUTTON_02, APPW_SET_PROP_BKCOLORS,     { ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_02, APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_2) } },
  { ID_BUTTON_02, APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_BUTTON_02, APPW_SET_PROP_FOCUSABLE,    { ARG_V(0) } },
  { ID_BUTTON_02, APPW_SET_PROP_RADIUS,       { ARG_V(0) } },
  { ID_BUTTON_02, APPW_SET_PROP_FRAME,        { ARG_V(1) } },
  { ID_BUTTON_02, APPW_SET_PROP_FONT,         { ARG_VPF(0, acNotoSans_16_Normal_EXT_AA4, &APPW__aFont[0]) } },
  { ID_BUTTON_03, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acreader), } },
  { ID_BUTTON_03, APPW_SET_PROP_COLORS,       { ARG_V(GUI_WHITE),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_03, APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_TOP),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_BUTTON_03, APPW_SET_PROP_COLORS2,      { ARG_V(GUI_WHITE),
                                                ARG_V(GUI_WHITE),
                                                ARG_V(GUI_WHITE) } },
  { ID_BUTTON_03, APPW_SET_PROP_REPEAT,       { ARG_V(500),
                                                ARG_V(100) } },
  { ID_BUTTON_03, APPW_SET_PROP_BKCOLORS,     { ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_03, APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_3) } },
  { ID_BUTTON_03, APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_BUTTON_03, APPW_SET_PROP_FOCUSABLE,    { ARG_V(0) } },
  { ID_BUTTON_03, APPW_SET_PROP_RADIUS,       { ARG_V(0) } },
  { ID_BUTTON_03, APPW_SET_PROP_FRAME,        { ARG_V(1) } },
  { ID_BUTTON_03, APPW_SET_PROP_FONT,         { ARG_VPF(0, acNotoSans_16_Normal_EXT_AA4, &APPW__aFont[0]) } },
};

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { ID_BUTTON_00, WM_NOTIFICATION_CLICKED,          0,            APPW_JOB_SHOWSCREEN,     ID_SCREEN_00__ID_BUTTON_00__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_02),
    }, 0, NULL
  },
  { ID_BUTTON_01, WM_NOTIFICATION_CLICKED,          0,            APPW_JOB_SHOWSCREEN,     ID_SCREEN_00__ID_BUTTON_01__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_02),
    }, 0, NULL
  },
  { ID_BUTTON_03, WM_NOTIFICATION_CLICKED,          0,            APPW_JOB_SHOWSCREEN,     ID_SCREEN_00__ID_BUTTON_03__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_02),
    }, 0, NULL
  },
};

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       ID_SCREEN_00_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_00_RootInfo = {
  ID_SCREEN_00,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_00,
  0
};

/*************************** End of file ****************************/
