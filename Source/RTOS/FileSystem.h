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
File        : FileSystem.h
Purpose     : High-level file system API for RFID Reader application
---------------------------END-OF-HEADER------------------------------
*/

#ifndef FILESYSTEM_API_H
#define FILESYSTEM_API_H

#include <stdint.h>
#include <stdbool.h>

/*********************************************************************
*
*       RFID Tag Data Structure
*
**********************************************************************
*/
typedef struct {
    char EPC[24];           // EPC code (96 bits = 12 bytes, hex string = 24 chars)
    char Type[16];          // Tag type: "Asset", "Device", "Tool"
    uint8_t Status;         // 0:Normal, 1:Abnormal, 2:Unknown
    char Timestamp[24];     // Timestamp string
    int16_t RSSI;           // Signal strength
    uint8_t ReadCount;      // Number of times read
} RFID_Tag_t;

/*********************************************************************
*
*       Configuration Structure
*
**********************************************************************
*/
typedef struct {
    char Language[8];        // "en", "zh-CN"
    uint8_t ScreenBrightness; // 0-100
    uint8_t Volume;         // 0-100
    uint32_t TagDisplayCount; // Tags per page
    char LastScanTime[24];  // Last scan timestamp
} AppConfig_t;

/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/

/* System initialization */
int FSAPI_Init(void);
int FSAPI_DeInit(void);

/* Tag data operations */
int FSAPI_SaveTags(const RFID_Tag_t* tags, int count);
int FSAPI_LoadTags(RFID_Tag_t* tags, int maxCount, int* actualCount);
int FSAPI_AppendTag(const RFID_Tag_t* tag);
int FSAPI_ClearTags(void);
int FSAPI_GetTagCount(void);

/* Configuration operations */
int FSAPI_SaveConfig(const AppConfig_t* config);
int FSAPI_LoadConfig(AppConfig_t* config);
int FSAPI_ResetConfig(void);

/* Log operations */
int FSAPI_WriteLog(const char* message);
int FSAPI_ReadLog(char* buffer, int maxLen);
int FSAPI_ClearLog(void);

/* Utility */
const char* FSAPI_GetLastError(void);
uint32_t FSAPI_GetStorageUsed(void);
uint32_t FSAPI_GetStorageFree(void);

#endif /* FILESYSTEM_API_H */
