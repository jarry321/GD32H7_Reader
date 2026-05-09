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
File        : FileSystem.c
Purpose     : High-level file system API implementation
---------------------------END-OF-HEADER------------------------------
*/

#include "FileSystem.h"
#include "FatFS_Wrapper.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/*********************************************************************
*
*       Constants
*
**********************************************************************
*/
#define FS_DATA_PATH           "Data"
#define FS_TAG_FILE            "Data/tags.dat"
#define FS_CONFIG_FILE         "Data/config.dat"
#define FS_LOG_FILE            "Data/log.txt"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static char _LastError[256] = {0};
static int _TagCount = 0;

/*********************************************************************
*
*       Helper functions
*
**********************************************************************
*/
static void _SetError(const char* msg) {
    strncpy(_LastError, msg, sizeof(_LastError) - 1);
    _LastError[sizeof(_LastError) - 1] = 0;
}

static void _EnsureDataDir(void) {
    FS_MkDir(FS_DATA_PATH);
}

/*********************************************************************
*
*       System initialization
*
**********************************************************************
*/
int FSAPI_Init(void) {
    FS_ERROR_CODE err;
    
    err = FS_Init();
    if (err != FS_OK) {
        _SetError("Failed to initialize file system");
        return -1;
    }
    
    err = FS_Mount(0);
    if (err != FS_OK) {
        _SetError("Failed to mount drive");
        return -1;
    }
    
    // Ensure data directory exists
    _EnsureDataDir();
    
    printf("FileSystem: Initialized\n");
    return 0;
}

int FSAPI_DeInit(void) {
    FS_UnMount(0);
    FS_DeInit();
    printf("FileSystem: Deinitialized\n");
    return 0;
}

/*********************************************************************
*
*       Tag data operations
*
**********************************************************************
*/
int FSAPI_SaveTags(const RFID_Tag_t* tags, int count) {
    void* fp;
    uint32_t written;
    
    if (tags == NULL || count <= 0) {
        _SetError("Invalid input parameters");
        return -1;
    }
    
    _EnsureDataDir();
    
    fp = FS_Open(FS_TAG_FILE, "wb");
    if (fp == NULL) {
        _SetError("Failed to open tag file for writing");
        return -1;
    }
    
    // Write header
    FS_Write(fp, &count, sizeof(int));
    
    // Write tag data
    written = FS_Write(fp, tags, count * sizeof(RFID_Tag_t));
    FS_Close(fp);
    
    _TagCount = count;
    printf("FileSystem: Saved %d tags\n", count);
    return 0;
}

int FSAPI_LoadTags(RFID_Tag_t* tags, int maxCount, int* actualCount) {
    void* fp;
    int count;
    int readCount;
    
    if (tags == NULL || maxCount <= 0) {
        _SetError("Invalid input parameters");
        return -1;
    }
    
    if (actualCount) *actualCount = 0;
    
    fp = FS_Open(FS_TAG_FILE, "rb");
    if (fp == NULL) {
        // File doesn't exist, return empty
        _TagCount = 0;
        return 0;
    }
    
    // Read header
    FS_Read(fp, &count, sizeof(int));
    
    // Limit to maxCount
    readCount = (count < maxCount) ? count : maxCount;
    
    // Read tag data
    FS_Read(fp, tags, readCount * sizeof(RFID_Tag_t));
    FS_Close(fp);
    
    _TagCount = count;
    if (actualCount) *actualCount = readCount;
    
    printf("FileSystem: Loaded %d tags\n", readCount);
    return 0;
}

int FSAPI_AppendTag(const RFID_Tag_t* tag) {
    void* fp;
    RFID_Tag_t* tags;
    int count;
    int result;
    
    if (tag == NULL) {
        _SetError("Invalid tag data");
        return -1;
    }
    
    _EnsureDataDir();
    
    // Load existing tags
    count = FSAPI_GetTagCount();
    tags = (RFID_Tag_t*)malloc(sizeof(RFID_Tag_t) * (count + 1));
    if (tags == NULL) {
        _SetError("Memory allocation failed");
        return -1;
    }
    
    if (count > 0) {
        FSAPI_LoadTags(tags, count, NULL);
    }
    
    // Append new tag
    memcpy(&tags[count], tag, sizeof(RFID_Tag_t));
    
    // Save back
    result = FSAPI_SaveTags(tags, count + 1);
    
    free(tags);
    return result;
}

int FSAPI_ClearTags(void) {
    void* fp;
    
    fp = FS_Open(FS_TAG_FILE, "wb");
    if (fp == NULL) {
        return -1;
    }
    
    // Write empty count
    int zero = 0;
    FS_Write(fp, &zero, sizeof(int));
    FS_Close(fp);
    
    _TagCount = 0;
    printf("FileSystem: Cleared all tags\n");
    return 0;
}

int FSAPI_GetTagCount(void) {
    void* fp;
    int count;
    
    if (_TagCount > 0) {
        return _TagCount;
    }
    
    fp = FS_Open(FS_TAG_FILE, "rb");
    if (fp == NULL) {
        return 0;
    }
    
    FS_Read(fp, &count, sizeof(int));
    FS_Close(fp);
    
    _TagCount = count;
    return count;
}

/*********************************************************************
*
*       Configuration operations
*
**********************************************************************
*/
int FSAPI_SaveConfig(const AppConfig_t* config) {
    void* fp;
    
    if (config == NULL) {
        _SetError("Invalid config data");
        return -1;
    }
    
    _EnsureDataDir();
    
    fp = FS_Open(FS_CONFIG_FILE, "wb");
    if (fp == NULL) {
        _SetError("Failed to open config file");
        return -1;
    }
    
    FS_Write(fp, config, sizeof(AppConfig_t));
    FS_Close(fp);
    
    printf("FileSystem: Config saved\n");
    return 0;
}

int FSAPI_LoadConfig(AppConfig_t* config) {
    void* fp;
    
    if (config == NULL) {
        _SetError("Invalid config pointer");
        return -1;
    }
    
    // Set defaults
    memset(config, 0, sizeof(AppConfig_t));
    strcpy(config->Language, "en");
    config->ScreenBrightness = 80;
    config->Volume = 50;
    config->TagDisplayCount = 10;
    
    fp = FS_Open(FS_CONFIG_FILE, "rb");
    if (fp == NULL) {
        // File doesn't exist, return defaults
        printf("FileSystem: Using default config\n");
        return 0;
    }
    
    FS_Read(fp, config, sizeof(AppConfig_t));
    FS_Close(fp);
    
    printf("FileSystem: Config loaded\n");
    return 0;
}

int FSAPI_ResetConfig(void) {
    AppConfig_t config;
    
    memset(&config, 0, sizeof(AppConfig_t));
    strcpy(config.Language, "en");
    config.ScreenBrightness = 80;
    config.Volume = 50;
    config.TagDisplayCount = 10;
    
    return FSAPI_SaveConfig(&config);
}

/*********************************************************************
*
*       Log operations
*
**********************************************************************
*/
int FSAPI_WriteLog(const char* message) {
    void* fp;
    time_t now;
    struct tm* timeinfo;
    char timestamp[32];
    char line[320];
    
    if (message == NULL) {
        return -1;
    }
    
    _EnsureDataDir();
    
    fp = FS_Open(FS_LOG_FILE, "a");
    if (fp == NULL) {
        _SetError("Failed to open log file");
        return -1;
    }
    
    // Get current time
    time(&now);
    timeinfo = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Write log entry
    sprintf(line, "[%s] %s\n", timestamp, message);
    FS_Write(fp, line, strlen(line));
    
    FS_Close(fp);
    return 0;
}

int FSAPI_ReadLog(char* buffer, int maxLen) {
    void* fp;
    uint32_t bytesRead;
    
    if (buffer == NULL || maxLen <= 0) {
        return -1;
    }
    
    fp = FS_Open(FS_LOG_FILE, "r");
    if (fp == NULL) {
        buffer[0] = 0;
        return 0;
    }
    
    bytesRead = FS_Read(fp, buffer, maxLen - 1);
    buffer[bytesRead] = 0;
    
    FS_Close(fp);
    return bytesRead;
}

int FSAPI_ClearLog(void) {
    void* fp;
    
    fp = FS_Open(FS_LOG_FILE, "w");
    if (fp == NULL) {
        return -1;
    }
    
    FS_Close(fp);
    printf("FileSystem: Log cleared\n");
    return 0;
}

/*********************************************************************
*
*       Utility
*
**********************************************************************
*/
const char* FSAPI_GetLastError(void) {
    return _LastError;
}

uint32_t FSAPI_GetStorageUsed(void) {
    void* dp;
    char filename[256];
    uint32_t totalSize = 0;
    uint32_t fsize;
    uint8_t fattrib;
    
    dp = FS_OpenDir(FS_DATA_PATH);
    if (dp == NULL) {
        return 0;
    }
    
    while (FS_ReadDir(dp, filename, &fsize, &fattrib) == 0) {
        if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0) {
            totalSize += fsize;
        }
    }
    
    FS_CloseDir(dp);
    return totalSize;
}

uint32_t FSAPI_GetStorageFree(void) {
    return FS_GetFreeSpace(0);
}

/*************************** End of file ****************************/
