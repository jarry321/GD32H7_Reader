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
File        : KeyHandler.c
Purpose     : Keyboard input handler implementation
---------------------------END-OF-HEADER------------------------------
*/

#include "KeyHandler.h"
#include "Language.h"
#include <windows.h>
#include <stdio.h>

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static int _LanguageToggleFlag = 0;

/*********************************************************************
*
*       KEY_Init
*/
void KEY_Init(void) {
    printf("KeyHandler: Initialized (F1=Toggle Language)\n");
}

/*********************************************************************
*
*       KEY_Process
*
*  Check for key presses and handle them
*  Call this function periodically in the main loop
*/
void KEY_Process(void) {
    /* Check if F1 is pressed (toggle language) */
    if (GetAsyncKeyState(VK_F1) & 0x8000) {
        /* Wait for key release to avoid multiple triggers */
        while (GetAsyncKeyState(VK_F1) & 0x8000) {
            Sleep(10);
        }
        
        /* Toggle language */
        LANG_Toggle();
        _LanguageToggleFlag = 1;
        
        printf("\n>>> Language switched to: %s <<<\n", LANG_GetLanguageName(LANG_GetLanguage()));
    }
    
    /* Check if F2 is pressed (show info) */
    if (GetAsyncKeyState(VK_F2) & 0x8000) {
        while (GetAsyncKeyState(VK_F2) & 0x8000) {
            Sleep(10);
        }
        
        printf("\n=== System Info ===\n");
        printf("Current Language: %s\n", LANG_GetLanguageName(LANG_GetLanguage()));
        printf("Free Memory: Available\n");
        printf("====================\n");
    }
    
    /* Check if F3 is pressed (refresh) */
    if (GetAsyncKeyState(VK_F3) & 0x8000) {
        while (GetAsyncKeyState(VK_F3) & 0x8000) {
            Sleep(10);
        }
        
        printf("\n>>> Display Refreshed <<<\n");
    }
}

/*********************************************************************
*
*       KEY_IsLanguageToggled
*/
int KEY_IsLanguageToggled(void) {
    return _LanguageToggleFlag;
}

/*********************************************************************
*
*       KEY_ClearLanguageToggle
*/
void KEY_ClearLanguageToggle(void) {
    _LanguageToggleFlag = 0;
}

/*************************** End of file ****************************/
