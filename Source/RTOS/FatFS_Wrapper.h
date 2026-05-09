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
File        : FatFS_Wrapper.h
Purpose     : FatFS abstraction layer for GUI application
---------------------------END-OF-HEADER------------------------------
*/

#ifndef FATFS_WRAPPER_H
#define FATFS_WRAPPER_H

#include <stdint.h>
#include <stdbool.h>

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef enum {
    FS_OK = 0,
    FS_ERROR,
    FS_DISK_FULL,
    FS_FILE_NOT_FOUND,
    FS_PATH_NOT_FOUND,
    FS_INVALID_NAME,
    FS_INVALID_DRIVE,
    FS_ACCESS_DENIED,
    FS_BUSY,
    FS_TIMEOUT,
    FS_NOT_READY
} FS_ERROR_CODE;

/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/

/* File system initialization */
FS_ERROR_CODE FS_Init(void);
FS_ERROR_CODE FS_DeInit(void);

/* Volume/Drive operations */
FS_ERROR_CODE FS_Mount(uint8_t drive);
FS_ERROR_CODE FS_UnMount(uint8_t drive);
const char* FS_GetErrorString(FS_ERROR_CODE err);

/* File operations */
void* FS_Open(const char* filename, const char* mode);
void  FS_Close(void* fp);
uint32_t FS_Read(void* fp, void* buffer, uint32_t size);
uint32_t FS_Write(void* fp, const void* buffer, uint32_t size);
int  FS_Seek(void* fp, uint32_t offset);
uint32_t FS_Tell(void* fp);
uint32_t FS_GetSize(void* fp);
bool FS_EOF(void* fp);
int  FS_Flush(void* fp);

/* Directory operations */
void* FS_OpenDir(const char* dirname);
int  FS_ReadDir(void* dp, char* filename, uint32_t* fsize, uint8_t* fattrib);
void FS_CloseDir(void* dp);
int  FS_MkDir(const char* dirname);
int  FS_RmDir(const char* dirname);

/* File management */
int  FS_Delete(const char* filename);
int  FS_Rename(const char* oldname, const char* newname);
int  FS_Stat(const char* filename);

/* Utility */
bool FS_Exists(const char* filename);
uint32_t FS_GetFreeSpace(uint8_t drive);
const char* FS_GetVolumeLabel(uint8_t drive);

#endif /* FATFS_WRAPPER_H */
