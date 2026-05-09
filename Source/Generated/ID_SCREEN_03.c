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
File        : ID_SCREEN_03.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_03.h"

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
    ID_SCREEN_03, 0,
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
    ID_IMAGE_00, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      1024, 600, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TEXT_Create,
    TEXT_TITLE, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      1024, 48, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TEXT_Create,
    TEXT_CONTENT, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 60, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      944, 440, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TEXT_Create,
    TEXT_PAGE, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 515, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      200, 32, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_PROGBAR_Create,
    PROGRESS_BAR, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 260, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 525, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      680, 20, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    BTN_MENU, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 954, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 515, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      60, 40, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    BTN_PREV, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 60, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      40, 440, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    BTN_NEXT, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 984, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 60, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      40, 440, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    BTN_BACK, ID_SCREEN_03,
    { { { DISPOSE_MODE_REL_PARENT, 926, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      100, 48, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_IMAGE_00,  APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_IMAGE_00,  APPW_SET_PROP_SBITMAP,      { ARG_VP(0, ac_0210408171838_2a5a9),
                                                ARG_V(18349), } },
  { TEXT_TITLE,   APPW_SET_PROP_COLOR,        { ARG_V(0xffc0c0c0) } },
  { TEXT_TITLE,   APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { TEXT_TITLE,   APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_4) } },
  { TEXT_TITLE,   APPW_SET_PROP_BKCOLOR,      { ARG_V(0xffe7e8e9) } },
  { TEXT_CONTENT, APPW_SET_PROP_COLOR,        { ARG_V(0xffc0c0c0) } },
  { TEXT_CONTENT, APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { TEXT_PAGE,    APPW_SET_PROP_COLOR,        { ARG_V(0xffc0c0c0) } },
  { TEXT_PAGE,    APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { PROGRESS_BAR, APPW_SET_PROP_RANGE,        { ARG_V(0),
                                                ARG_V(100) } },
  { PROGRESS_BAR, APPW_SET_PROP_RADIUS,       { ARG_V(5) } },
  { PROGRESS_BAR, APPW_SET_PROP_FRAME,        { ARG_V(2) } },
  { PROGRESS_BAR, APPW_SET_PROP_COLOR,        { ARG_V(0xff2c2c30) } },
  { PROGRESS_BAR, APPW_SET_PROP_VALUE,        { ARG_V(15) } },
  { PROGRESS_BAR, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Progbar_Tile_H_Blue_1x16),
                                                ARG_VP(0, acDARK_Progbar_Tile_H_Gray_1x16), } },
  { PROGRESS_BAR, APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { PROGRESS_BAR, APPW_SET_PROP_COLORS,       { ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { BTN_MENU,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                ARG_VP(0, acDARK_Button_Down_100x30), } },
  { BTN_MENU,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { BTN_PREV,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                ARG_VP(0, acDARK_Button_Down_100x30), } },
  { BTN_PREV,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { BTN_NEXT,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                ARG_VP(0, acDARK_Button_Down_100x30), } },
  { BTN_NEXT,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { BTN_BACK,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                ARG_VP(0, acDARK_Button_Down_100x30), } },
  { BTN_BACK,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
};

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { BTN_MENU,     WM_NOTIFICATION_CLICKED,          0,            APPW_JOB_SHOWSCREEN,     ID_SCREEN_03__BTN_MENU__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_04),
    }, 0, NULL
  },
  { BTN_BACK,     WM_NOTIFICATION_CLICKED,          0,            APPW_JOB_SHOWSCREEN,     ID_SCREEN_03__BTN_BACK__WM_NOTIFICATION_CLICKED,
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
*       ID_SCREEN_03_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_03_RootInfo = {
  ID_SCREEN_03,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_03,
  0
};

/*************************** End of file ****************************/
