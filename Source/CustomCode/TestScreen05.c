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
File        : TestScreen05.c
Purpose     : Test program for Screen 05 (RFID Tag List)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "WM.h"
#include "ID_SCREEN_05.h"

/*********************************************************************
*
*       MainTask
*/
// 已禁用，避免与APPW_MainTask冲突
// 如需测试，请取消下面注释
/*
void TestMainTask(void) {
    // Initialize GUI
    GUI_Init();
    
    // Set background color
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
    
    // Create and show RFID tag list screen
    ID_SCREEN_05_Create();
    ID_SCREEN_05_Show();
    
    // Main loop
    while (1) {
        GUI_Exec();
        GUI_Delay(10);
    }
}
*/

/*************************** End of file ****************************/
