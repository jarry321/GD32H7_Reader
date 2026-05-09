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
File        : Language.c
Purpose     : Multi-language support implementation
---------------------------END-OF-HEADER------------------------------
*/

#include "Language.h"
#include "FileSystem.h"
#include <stdio.h>
#include <string.h>

/*********************************************************************
*
*       Language strings table
*
**********************************************************************
*/

/* English strings */
static const char* _Strings_EN[STR_COUNT] = {
    /* Common */
    "OK", "Cancel", "Back", "Save", "Delete", "Refresh", "Search", "Settings", "About",
    /* Main Menu */
    "Sys Info", "Music", "Video", "Reader",
    /* RFID Tag List */
    "Tag List", "Total", "Type", "Status", "EPC", "Time", "RSSI", "Count",
    /* Status */
    "Normal", "Abnormal", "Unknown",
    /* Types */
    "Asset", "Device", "Tool",
    /* System Info */
    "Battery", "Signal", "Connected", "Disconnected",
    /* Messages */
    "Scan complete", "Scanning...", "No tags found", "Tag saved", "Tag deleted",
    /* Settings */
    "Language", "Brightness", "Volume", "Display Count"
};

/* Chinese strings - simplified ASCII for compatibility */
static const char* _Strings_ZH[STR_COUNT] = {
    /* Common */
    "OK", "Cancel", "Back", "Save", "Delete", "Refresh", "Search", "Settings", "About",
    /* Main Menu */
    "System", "Music", "Video", "Reader",
    /* RFID Tag List */
    "Tag List", "Total", "Type", "Status", "EPC", "Time", "RSSI", "Count",
    /* Status */
    "Normal", "Abnormal", "Unknown",
    /* Types */
    "Asset", "Device", "Tool",
    /* System Info */
    "Battery", "Signal", "Connected", "Disconnected",
    /* Messages */
    "Scan complete", "Scanning...", "No tags found", "Tag saved", "Tag deleted",
    /* Settings */
    "Language", "Brightness", "Volume", "Display Count"
};

/* Language names */
static const char* _LanguageNames[LANG_COUNT] = {
    "English", "Chinese"
};

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static LANG_ID _CurrentLanguage = LANG_EN;
static const char** _StringTables[LANG_COUNT] = {
    _Strings_EN, _Strings_ZH
};

/*********************************************************************
*
*       Initialization
*
**********************************************************************
*/
void LANG_Init(void) {
    printf("Language: Initializing...\n");
    
    /* Try to load saved language setting */
    if (LANG_LoadConfig() != 0) {
        /* Use default (English) */
        _CurrentLanguage = LANG_EN;
    }
    
    printf("Language: Current language = %s\n", LANG_GetLanguageName(_CurrentLanguage));
}

void LANG_DeInit(void) {
    /* Save current language setting */
    LANG_SaveConfig();
}

/*********************************************************************
*
*       Language management
*
**********************************************************************
*/
void LANG_SetLanguage(LANG_ID lang) {
    if (lang >= 0 && lang < LANG_COUNT) {
        _CurrentLanguage = lang;
        printf("Language: Switched to %s\n", LANG_GetLanguageName(lang));
    }
}

LANG_ID LANG_GetLanguage(void) {
    return _CurrentLanguage;
}

const char* LANG_GetLanguageName(LANG_ID lang) {
    if (lang >= 0 && lang < LANG_COUNT) {
        return _LanguageNames[lang];
    }
    return "Unknown";
}

/*********************************************************************
*
*       String access
*
**********************************************************************
*/
const char* LANG_GetString(STR_ID id) {
    if (id >= 0 && id < STR_COUNT) {
        return _StringTables[_CurrentLanguage][id];
    }
    return "";
}

/*********************************************************************
*
*       Toggle language
*
**********************************************************************
*/
void LANG_Toggle(void) {
    LANG_ID newLang = (_CurrentLanguage + 1) % LANG_COUNT;
    LANG_SetLanguage(newLang);
}

/*********************************************************************
*
*       Save/Load configuration
*
**********************************************************************
*/
int LANG_SaveConfig(void) {
    void* fp;
    
    fp = FS_Open("Data/lang.cfg", "wb");
    if (fp == NULL) {
        printf("Language: Failed to save config\n");
        return -1;
    }
    
    FS_Write(fp, &_CurrentLanguage, sizeof(LANG_ID));
    FS_Close(fp);
    
    printf("Language: Config saved (%s)\n", LANG_GetLanguageName(_CurrentLanguage));
    return 0;
}

int LANG_LoadConfig(void) {
    void* fp;
    LANG_ID savedLang;
    
    fp = FS_Open("Data/lang.cfg", "rb");
    if (fp == NULL) {
        printf("Language: No saved config, using default\n");
        return -1;
    }
    
    if (FS_Read(fp, &savedLang, sizeof(LANG_ID)) == sizeof(LANG_ID)) {
        if (savedLang >= 0 && savedLang < LANG_COUNT) {
            _CurrentLanguage = savedLang;
            printf("Language: Config loaded (%s)\n", LANG_GetLanguageName(_CurrentLanguage));
            FS_Close(fp);
            return 0;
        }
    }
    
    FS_Close(fp);
    return -1;
}

/*************************** End of file ****************************/
