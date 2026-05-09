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
File        : FatFS_Wrapper.c
Purpose     : FatFS wrapper implementation for Windows simulator
              This is a simplified version using stdio for simulation.
---------------------------END-OF-HEADER------------------------------
*/

#include "FatFS_Wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/*********************************************************************
*
*       FatFS attribute constants (for simulation)
*
**********************************************************************
*/
#define AM_RDO  0x01    // Read only
#define AM_HID  0x02    // Hidden
#define AM_SYS  0x04    // System
#define AM_DIR  0x10    // Directory

/*********************************************************************
*
*       Directory structure for simulation
*
**********************************************************************
*/
typedef struct {
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    char path[256];
    int first;
} FS_DIR_SIM;

/*********************************************************************
*
*       File system initialization
*/
FS_ERROR_CODE FS_Init(void) {
    printf("FatFS: Initialized (Simulation Mode)\n");
    return FS_OK;
}

FS_ERROR_CODE FS_DeInit(void) {
    return FS_OK;
}

/*********************************************************************
*
*       Volume/Drive operations
*/
FS_ERROR_CODE FS_Mount(uint8_t drive) {
    printf("FatFS: Mounting drive %d:\n", drive);
    return FS_OK;
}

FS_ERROR_CODE FS_UnMount(uint8_t drive) {
    printf("FatFS: Unmounting drive %d:\n", drive);
    return FS_OK;
}

const char* FS_GetErrorString(FS_ERROR_CODE err) {
    switch (err) {
        case FS_OK:              return "OK";
        case FS_ERROR:           return "Error";
        case FS_DISK_FULL:       return "Disk full";
        case FS_FILE_NOT_FOUND:  return "File not found";
        case FS_PATH_NOT_FOUND:  return "Path not found";
        case FS_INVALID_NAME:    return "Invalid name";
        case FS_INVALID_DRIVE:    return "Invalid drive";
        case FS_ACCESS_DENIED:   return "Access denied";
        case FS_BUSY:            return "Busy";
        case FS_TIMEOUT:         return "Timeout";
        case FS_NOT_READY:       return "Not ready";
        default:                  return "Unknown error";
    }
}

/*********************************************************************
*
*       File operations
*/
void* FS_Open(const char* filename, const char* mode) {
    FILE* fp;
    
    fp = fopen(filename, mode);
    if (fp == NULL) {
        printf("FatFS: Failed to open file '%s'\n", filename);
        return NULL;
    }
    
    printf("FatFS: Opened file '%s' (mode: %s)\n", filename, mode);
    return (void*)fp;
}

void FS_Close(void* fp) {
    if (fp) {
        fclose((FILE*)fp);
        printf("FatFS: File closed\n");
    }
}

uint32_t FS_Read(void* fp, void* buffer, uint32_t size) {
    uint32_t bytes;
    
    if (fp == NULL) return 0;
    
    bytes = fread(buffer, 1, size, (FILE*)fp);
    return bytes;
}

uint32_t FS_Write(void* fp, const void* buffer, uint32_t size) {
    uint32_t bytes;
    
    if (fp == NULL) return 0;
    
    bytes = fwrite(buffer, 1, size, (FILE*)fp);
    return bytes;
}

int FS_Seek(void* fp, uint32_t offset) {
    if (fp == NULL) return -1;
    
    return fseek((FILE*)fp, offset, SEEK_SET);
}

uint32_t FS_Tell(void* fp) {
    if (fp == NULL) return 0;
    
    return ftell((FILE*)fp);
}

uint32_t FS_GetSize(void* fp) {
    uint32_t size;
    long pos;
    FILE* file = (FILE*)fp;
    
    if (fp == NULL) return 0;
    
    pos = ftell(file);
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, pos, SEEK_SET);
    
    return size;
}

bool FS_EOF(void* fp) {
    if (fp == NULL) return true;
    
    return feof((FILE*)fp) != 0;
}

int FS_Flush(void* fp) {
    if (fp == NULL) return -1;
    
    return fflush((FILE*)fp);
}

/*********************************************************************
*
*       Directory operations
*/
void* FS_OpenDir(const char* dirname) {
    FS_DIR_SIM* pDir;
    char searchPath[280];
    
    pDir = (FS_DIR_SIM*)malloc(sizeof(FS_DIR_SIM));
    if (pDir == NULL) return NULL;
    
    memset(pDir, 0, sizeof(FS_DIR_SIM));
    strcpy(pDir->path, dirname);
    
    sprintf(searchPath, "%s/*", dirname);
    pDir->hFind = FindFirstFile(searchPath, &pDir->findData);
    
    if (pDir->hFind == INVALID_HANDLE_VALUE) {
        free(pDir);
        return NULL;
    }
    
    pDir->first = 1;
    printf("FatFS: Opened directory '%s'\n", dirname);
    return (void*)pDir;
}

int FS_ReadDir(void* dp, char* filename, uint32_t* fsize, uint8_t* fattrib) {
    FS_DIR_SIM* pDir = (FS_DIR_SIM*)dp;
    
    if (dp == NULL) return -1;
    
    if (pDir->first) {
        pDir->first = 0;
    } else {
        if (!FindNextFile(pDir->hFind, &pDir->findData)) {
            return -1;  // No more files
        }
    }
    
    strcpy(filename, pDir->findData.cFileName);
    
    if (fsize) {
        *fsize = pDir->findData.nFileSizeLow;
    }
    
    if (fattrib) {
        *fattrib = 0;
        if (pDir->findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            *fattrib |= AM_DIR;
        }
        if (pDir->findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
            *fattrib |= AM_RDO;
        }
        if (pDir->findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
            *fattrib |= AM_HID;
        }
        if (pDir->findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) {
            *fattrib |= AM_SYS;
        }
    }
    
    return 0;
}

void FS_CloseDir(void* dp) {
    FS_DIR_SIM* pDir = (FS_DIR_SIM*)dp;
    
    if (dp == NULL) return;
    
    if (pDir->hFind != INVALID_HANDLE_VALUE) {
        FindClose(pDir->hFind);
    }
    free(pDir);
    printf("FatFS: Directory closed\n");
}

int FS_MkDir(const char* dirname) {
    int result;
    
    result = CreateDirectory(dirname, NULL);
    if (result) {
        printf("FatFS: Created directory '%s'\n", dirname);
    }
    return result ? 0 : -1;
}

int FS_RmDir(const char* dirname) {
    int result;
    
    result = RemoveDirectory(dirname);
    if (result) {
        printf("FatFS: Removed directory '%s'\n", dirname);
    }
    return result ? 0 : -1;
}

/*********************************************************************
*
*       File management
*/
int FS_Delete(const char* filename) {
    int result;
    
    result = DeleteFile(filename);
    if (result) {
        printf("FatFS: Deleted file '%s'\n", filename);
    }
    return result ? 0 : -1;
}

int FS_Rename(const char* oldname, const char* newname) {
    int result;
    
    result = rename(oldname, newname);
    if (result == 0) {
        printf("FatFS: Renamed '%s' to '%s'\n", oldname, newname);
    }
    return result;
}

int FS_Stat(const char* filename) {
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    
    hFind = FindFirstFile(filename, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return -1;
    }
    
    FindClose(hFind);
    return 0;
}

/*********************************************************************
*
*       Utility
*/
bool FS_Exists(const char* filename) {
    return FS_Stat(filename) == 0;
}

uint32_t FS_GetFreeSpace(uint8_t drive) {
    ULARGE_INTEGER freeBytes, totalBytes, totalFreeBytes;
    
    (void)drive;  // unused in simulation
    
    if (GetDiskFreeSpaceEx(NULL, &freeBytes, &totalBytes, &totalFreeBytes)) {
        return (uint32_t)totalFreeBytes.QuadPart;
    }
    
    return 0;
}

const char* FS_GetVolumeLabel(uint8_t drive) {
    static char volumeName[MAX_PATH];
    char rootPath[4];
    BOOL result;
    
    sprintf(rootPath, "%c:\\", 'A' + drive);
    
    result = GetVolumeInformation(
        rootPath,
        volumeName,
        MAX_PATH,
        NULL,
        NULL,
        NULL,
        NULL,
        0
    );
    
    if (result) {
        return volumeName;
    }
    
    return "NoLabel";
}

/*************************** End of file ****************************/
