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
File        : APPW_MainTask.c
Purpose     : AppWizard application entry point with RTOS support
---------------------------END-OF-HEADER------------------------------
*/

#include "Generated/Resource.h"

#ifdef USE_FATFS
#include "FileSystem.h"
#include "Language.h"
#include "KeyHandler.h"
#endif

#ifdef USE_RTOS
#include "RTOS_Wrapper.h"
#include <stdio.h>
#include <string.h>

/*********************************************************************
*
*       FS_Test
*
*  File system test function
*/
static void FS_Test(void) {
    int result;
    RFID_Tag_t tag;
    RFID_Tag_t tags[5];
    int tagCount = 0;
    AppConfig_t config;
    char logBuf[512];

    printf("===== FatFS Test Start =====\n\n");

    /* Test 1: Save and load config */
    printf("[Test 1] Config save/load...\n");
    memset(&config, 0, sizeof(config));
    strcpy(config.Language, "zh-CN");
    config.ScreenBrightness = 75;
    config.Volume = 60;
    config.TagDisplayCount = 8;
    result = FSAPI_SaveConfig(&config);
    printf("  Save config: %s\n", result == 0 ? "PASS" : "FAIL");

    memset(&config, 0, sizeof(config));
    result = FSAPI_LoadConfig(&config);
    printf("  Load config: %s\n", result == 0 ? "PASS" : "FAIL");
    printf("  Language: %s\n", config.Language);
    printf("  Brightness: %d\n", config.ScreenBrightness);
    printf("  Volume: %d\n", config.Volume);
    printf("  TagDisplayCount: %d\n", config.TagDisplayCount);
    printf("  Config test: %s\n\n",
           (strcmp(config.Language, "zh-CN") == 0 && config.ScreenBrightness == 75) ? "PASS" : "FAIL");

    /* Test 2: Save and load tags */
    printf("[Test 2] Tag save/load...\n");

    /* Create 3 test tags */
    memset(&tag, 0, sizeof(tag));
    strcpy(tag.EPC, "E2003412BCD4567890AB");
    strcpy(tag.Type, "Asset");
    tag.Status = 0;
    strcpy(tag.Timestamp, "2024-05-08 14:30:00");
    tag.RSSI = -45;
    tag.ReadCount = 5;
    FSAPI_AppendTag(&tag);

    strcpy(tag.EPC, "E2003412AAAA56789012");
    strcpy(tag.Type, "Device");
    tag.Status = 1;
    strcpy(tag.Timestamp, "2024-05-08 14:31:00");
    tag.RSSI = -52;
    tag.ReadCount = 3;
    FSAPI_AppendTag(&tag);

    strcpy(tag.EPC, "E2003412BBBB67890123");
    strcpy(tag.Type, "Tool");
    tag.Status = 2;
    strcpy(tag.Timestamp, "2024-05-08 14:32:00");
    tag.RSSI = -38;
    tag.ReadCount = 8;
    FSAPI_AppendTag(&tag);

    printf("  Appended 3 tags\n");
    printf("  Tag count: %d\n", FSAPI_GetTagCount());

    /* Load tags back */
    result = FSAPI_LoadTags(tags, 5, &tagCount);
    printf("  Load tags: %s (loaded %d)\n", result == 0 ? "PASS" : "FAIL", tagCount);

    /* Verify tag data */
    printf("  Tag[0]: EPC=%s, Type=%s, Status=%d\n", tags[0].EPC, tags[0].Type, tags[0].Status);
    printf("  Tag[1]: EPC=%s, Type=%s, Status=%d\n", tags[1].EPC, tags[1].Type, tags[1].Status);
    printf("  Tag[2]: EPC=%s, Type=%s, Status=%d\n", tags[2].EPC, tags[2].Type, tags[2].Status);
    printf("  Tag test: %s\n\n",
           (tagCount == 3 && strcmp(tags[0].EPC, "E2003412BCD4567890AB") == 0) ? "PASS" : "FAIL");

    /* Test 3: Log write/read */
    printf("[Test 3] Log write/read...\n");
    FSAPI_ClearLog();
    FSAPI_WriteLog("System started");
    FSAPI_WriteLog("RFID scan completed: found 3 tags");
    FSAPI_WriteLog("Config saved");

    memset(logBuf, 0, sizeof(logBuf));
    result = FSAPI_ReadLog(logBuf, sizeof(logBuf));
    printf("  Read log: %s (%d bytes)\n", result >= 0 ? "PASS" : "FAIL", result);
    printf("  Log content:\n%s", logBuf);
    printf("  Log test: %s\n\n",
           (strstr(logBuf, "System started") != NULL && strstr(logBuf, "RFID scan") != NULL) ? "PASS" : "FAIL");

    /* Test 4: Storage info */
    printf("[Test 4] Storage info...\n");
    printf("  Storage used: %u bytes\n", FSAPI_GetStorageUsed());
    printf("  Storage free: %u bytes\n\n", FSAPI_GetStorageFree());

    /* Test 5: Clear tags */
    printf("[Test 5] Clear tags...\n");
    result = FSAPI_ClearTags();
    printf("  Clear tags: %s\n", result == 0 ? "PASS" : "FAIL");
    printf("  Tag count after clear: %d\n", FSAPI_GetTagCount());
    printf("  Clear test: %s\n\n", FSAPI_GetTagCount() == 0 ? "PASS" : "FAIL");

    printf("===== FatFS Test Complete =====\n\n");
}

/*********************************************************************
*
*       vCommTask
*
*  Communication task - handles RFID data
*/
static void vCommTask(void *pvParameters) {
    (void)pvParameters;
    
    printf("Communication Task: Started\n");
    
    while (1) {
        /* TODO: Add RFID data reading logic here */
        RTOS_Delay(50);
    }
}

/*********************************************************************
*
*       vIdleTask
*/
static void vIdleTask(void *pvParameters) {
    (void)pvParameters;
    
    printf("Idle Task: Started\n");
    
    while (1) {
        RTOS_Delay(100);
    }
}

/*********************************************************************
*
*       MainTask (RTOS version)
*/
void MainTask(void) {
    printf("\n========================================\n");
    printf("  RFID Reader - RTOS Version\n");
    printf("  Based on GD32H7 + FreeRTOS\n");
    printf("========================================\n\n");
    
    /* Initialize file system */
#ifdef USE_FATFS
    FSAPI_Init();
    FS_Test();  /* Run file system test */
    
    /* Initialize language system */
    LANG_Init();
    KEY_Init();  /* Initialize keyboard handler */
    
    /* Test language switching */
    printf("\n===== Language Test =====\n");
    printf("Current: %s\n", LANG_GetLanguageName(LANG_GetLanguage()));
    printf("Tag List: %s\n", LANG_GetString(STR_TAG_LIST));
    printf("Settings: %s\n", LANG_GetString(STR_SETTINGS));
    
    /* Switch to Chinese */
    LANG_SetLanguage(LANG_ZH);
    printf("\nSwitched to: %s\n", LANG_GetLanguageName(LANG_GetLanguage()));
    printf("Tag List: %s\n", LANG_GetString(STR_TAG_LIST));
    printf("Settings: %s\n", LANG_GetString(STR_SETTINGS));
    
    /* Save language setting */
    LANG_SaveConfig();
    printf("===== Language Test Complete =====\n\n");
#endif
    
    /* Initialize RTOS */
    RTOS_Init();
    
    /* Create communication task */
    RTOS_CreateTask(vCommTask, "Comm", 2048, NULL, 2);
    
    /* Create idle task */
    RTOS_CreateTask(vIdleTask, "Idle", 2048, NULL, 1);
    
    printf("RTOS: Tasks created\n");
    printf("Starting GUI...\n\n");
    
    /* Setup configuration dependent pointers */
    APPW_X_Setup();
    
    /* Initialize AppWizard */
    APPW_Init(APPW_PROJECT_PATH);
    
    /* Create all persistent screens except initial screen */
    APPW_CreatePersistentScreens();
    
    /* Create initial screen */
    APPW_CreateRoot(APPW_INITIAL_SCREEN, WM_HBKWIN);
    
    /* Keep GUI running */
    for (APPW_Run = 1; APPW_Run; ) {
        APPW_Exec();
        KEY_Process();  /* Process keyboard input */
        RTOS_Delay(5);
    }
}

#else /* !USE_RTOS */

/*********************************************************************
*
*       MainTask (Non-RTOS version)
*/
void MainTask(void) {
  //
  // Setup configuration dependent pointers
  //
  APPW_X_Setup();
  //
  // Initialize AppWizard
  //
  APPW_Init(APPW_PROJECT_PATH);
  //
  // Create all persistent screens except initial screen
  //
  APPW_CreatePersistentScreens();
  //
  // Create initial screen...
  //
  APPW_CreateRoot(APPW_INITIAL_SCREEN, WM_HBKWIN);
  //
  // ...and keep it alive
  //
  for (APPW_Run = 1; APPW_Run; ) {
    APPW_Exec();
    GUI_X_Delay(5);
  }
}

#endif /* USE_RTOS */

/*************************** End of file ****************************/
