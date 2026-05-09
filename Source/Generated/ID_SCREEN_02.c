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
File        : ID_SCREEN_02.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_02.h"

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
    ID_SCREEN_02, 0,
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
    ID_IMAGE_00, ID_SCREEN_02,
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
    ID_BUTTON_00, ID_SCREEN_02,
    { { { DISPOSE_MODE_REL_PARENT, 108, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 88, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      106, 104, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_01, ID_SCREEN_02,
    { { { DISPOSE_MODE_REL_PARENT, 924, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      100, 30, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_IMAGE_00,  APPW_SET_PROP_SBITMAP,      { ARG_VP(0, accat_fluffy_pet_1246095_1024x600),
                                                ARG_V(57176), } },
  { ID_IMAGE_00,  APPW_SET_PROP_UNTOUCHABLE,  { ARG_V(0) } },
  { ID_IMAGE_00,  APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_IMAGE_00,  APPW_SET_PROP_OPAQUE,       { ARG_V(0) } },
  { ID_BUTTON_00, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acMINIBLUE_Button_Down_105x99),
                                                ARG_VP(0, acDARK_Button_Down_100x30), } },
  { ID_BUTTON_00, APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_01, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                ARG_VP(0, acDARK_Button_Down_100x30), } },
  { ID_BUTTON_01, APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                ARG_V(0xffc0c0c0),
                                                ARG_V(GUI_INVALID_COLOR) } },
};

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { ID_BUTTON_00, WM_NOTIFICATION_CLICKED,          0,            APPW_JOB_SHOWSCREEN,     ID_SCREEN_02__ID_BUTTON_00__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_03),
    }, 0, NULL
  },
  { ID_BUTTON_01, WM_NOTIFICATION_CLICKED,          0,            APPW_JOB_SHOWSCREEN,     ID_SCREEN_02__ID_BUTTON_01__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_00),
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
*       ID_SCREEN_02_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_02_RootInfo = {
  ID_SCREEN_02,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_02,
  0
};

/*************************** End of file ****************************/
