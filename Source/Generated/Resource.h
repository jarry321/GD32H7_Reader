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
File        : Resource.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include "AppWizard.h"

/*********************************************************************
*
*       Text
*/
#define ID_RTEXT_1 0
#define ID_RTEXT_0 1
#define ID_RTEXT_2 2
#define ID_RTEXT_3 3
#define ID_RTEXT_4 4

extern GUI_CONST_STORAGE unsigned char acAPPW_Language_0[];

/*********************************************************************
*
*       Font data
*/
extern APPW_FONT APPW__aFont[1];

/*********************************************************************
*
*       Fonts
*/
extern GUI_CONST_STORAGE unsigned char acNotoSans_16_Normal_EXT_AA4[];

/*********************************************************************
*
*       Images
*/
extern GUI_CONST_STORAGE unsigned char acorange_ice_mint_139564_1024x600[];
extern GUI_CONST_STORAGE unsigned char accomputer[];
extern GUI_CONST_STORAGE unsigned char acmusic[];
extern GUI_CONST_STORAGE unsigned char acVideo[];
extern GUI_CONST_STORAGE unsigned char acreader[];
extern GUI_CONST_STORAGE unsigned char acheadphones_minimalism_pink_120664_1024x600[];
extern GUI_CONST_STORAGE unsigned char accat_fluffy_pet_1246095_1024x600[];
extern GUI_CONST_STORAGE unsigned char acMINIBLUE_Button_Down_105x99[];
extern GUI_CONST_STORAGE unsigned char acDARK_Button_Down_100x30[];
extern GUI_CONST_STORAGE unsigned char acDARK_Button_Up_100x30[];
extern GUI_CONST_STORAGE unsigned char ac_0210408171838_2a5a9[];
extern GUI_CONST_STORAGE unsigned char acDARK_Progbar_Tile_H_Blue_1x16[];
extern GUI_CONST_STORAGE unsigned char acDARK_Progbar_Tile_H_Gray_1x16[];

/*********************************************************************
*
*       Screens
*/
#define ID_SCREEN_00 (GUI_ID_USER + 4096)
#define ID_SCREEN_01 (GUI_ID_USER + 4097)
#define ID_SCREEN_02 (GUI_ID_USER + 4098)
#define ID_SCREEN_03 (GUI_ID_USER + 4099)
#define ID_SCREEN_04 (GUI_ID_USER + 4100)

extern APPW_ROOT_INFO ID_SCREEN_00_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_01_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_02_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_03_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_04_RootInfo;

#define APPW_INITIAL_SCREEN &ID_SCREEN_00_RootInfo

/*********************************************************************
*
*       Project path
*/
#define APPW_PROJECT_PATH "D:/Code/Reader_UI/01/NewProject1"

#endif  // RESOURCE_H

/*************************** End of file ****************************/
