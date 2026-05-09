/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*           (C) 2000    SEGGER Microcontroller Systeme GmbH          *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

**** emWin/GSC Grafical user interface for embedded applications ****
emWin is protected by international copyright laws. Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : WinMain.c
Purpose     : Application entry point with console support
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_SIM_Win32.h"
#include "LCD_SIM.h"
#include "AppWizard.h"
#include <stdio.h>

/*********************************************************************
*
*       WinMain
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nCmdShow) {
    // Allocate console for debug output
    AllocConsole();
    
    // Redirect stdout and stderr to console
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    
    // Set console title
    SetConsoleTitle("RFID Reader - Debug Console");
    
    printf("========================================\n");
    printf("  RFID Reader - Console Enabled\n");
    printf("========================================\n\n");
    
    //
    // Set function for taking screenshots
    //
    APPW_SetScreenshotFunc(SIM_GUI_TakeScreenshot);
    //
    // Start application
    //
    int result = SIM_GUI_App(hInstance, lpCmdLine);
    
    printf("\n[Program exited with code %d]\n", result);
    
    return result;
}

/*************************** End of file ****************************/
