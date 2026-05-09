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
File        : Language.h
Purpose     : Multi-language support definitions
---------------------------END-OF-HEADER------------------------------
*/

#ifndef LANGUAGE_H
#define LANGUAGE_H

/*********************************************************************
*
*       Language IDs
*
**********************************************************************
*/
typedef enum {
    LANG_EN = 0,    // English
    LANG_ZH,        // Chinese (Simplified)
    LANG_COUNT      // Total language count
} LANG_ID;

/*********************************************************************
*
*       String IDs
*
**********************************************************************
*/
typedef enum {
    // Common
    STR_OK = 0,
    STR_CANCEL,
    STR_BACK,
    STR_SAVE,
    STR_DELETE,
    STR_REFRESH,
    STR_SEARCH,
    STR_SETTINGS,
    STR_ABOUT,
    
    // Main Menu
    STR_SYS_INFO,
    STR_MUSIC,
    STR_VIDEO,
    STR_READER,
    
    // RFID Tag List
    STR_TAG_LIST,
    STR_TAG_COUNT,
    STR_TAG_TYPE,
    STR_TAG_STATUS,
    STR_TAG_EPC,
    STR_TAG_TIMESTAMP,
    STR_TAG_RSSI,
    STR_TAG_READ_COUNT,
    
    // Status
    STR_STATUS_NORMAL,
    STR_STATUS_ABNORMAL,
    STR_STATUS_UNKNOWN,
    
    // Types
    STR_TYPE_ASSET,
    STR_TYPE_DEVICE,
    STR_TYPE_TOOL,
    
    // System Info
    STR_BATTERY,
    STR_SIGNAL,
    STR_CONNECTED,
    STR_DISCONNECTED,
    
    // Messages
    STR_SCAN_COMPLETE,
    STR_SCANNING,
    STR_NO_TAGS,
    STR_TAG_SAVED,
    STR_TAG_DELETED,
    
    // Settings
    STR_LANGUAGE,
    STR_BRIGHTNESS,
    STR_VOLUME,
    STR_DISPLAY_COUNT,
    
    STR_COUNT  // Total string count
} STR_ID;

/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/

/* Initialize language system */
void LANG_Init(void);
void LANG_DeInit(void);

/* Language management */
void LANG_SetLanguage(LANG_ID lang);
LANG_ID LANG_GetLanguage(void);
const char* LANG_GetLanguageName(LANG_ID lang);

/* Get localized string */
const char* LANG_GetString(STR_ID id);

/* Toggle language (en <-> zh) */
void LANG_Toggle(void);

/* Save/Load language setting */
int LANG_SaveConfig(void);
int LANG_LoadConfig(void);

#endif /* LANGUAGE_H */
