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
File        : ffconf.h
Purpose     : FatFS configuration file
---------------------------END-OF-HEADER------------------------------
*/

#ifndef FF_CONF_H
#define FF_CONF_H

#define FFCONF_DEF 86631    /* Revision ID */

/*---------------------------------------------------------------------------
/  Function Configurations
/---------------------------------------------------------------------------*/

/* This option specifies the availability of APIs f_mount(), f_open(), f_opendir(),
/  f_stat(), f_mkdir(), f_unlink(), f_utime(), f_truncate(), f_size(), f_mtime(),
/  f_utime(), f_read(), f_write(), f_gets(), f_putc(), f_puts(), f_printf(), and
/  f_seek(). (0:Disable, 1:Enable) */
#define FF_USE_STRFUNC          2   // 0:Disable, 1:Enable, 2:Enable with output to console

/* This option specifies the availability of APIs f_forward(). (0:Disable, 1:Enable) */
#define FF_USE_FORWARD          0

/* This option specifies the availability of APIs f_expand() and f_truncate().
/  (0:Disable, 1:Enable) */
#define FF_USE_EXPAND           0

/* This option specifies the availability of APIs f_gets() and f_puts().
/  (0:Disable, 1:Enable) */
#define FF_USE_GETS             1
#define FF_USE_PUTS             1

/* This option specifies the availability of API f_mkfs(). (0:Disable, 1:Enable) */
#define FF_USE_MKFS             0

/* This option specifies the availability of API f_fdisk(). (0:Disable, 1:Enable) */
#define FF_USE_DISKIO           1

/* This option specifies the availability of API f_findfirst() and f_findnext().
/  (0:Disable, 1:Enable) */
#define FF_USE_FIND             1

/* This option specifies the availability of API f_unlink() and f_mkdir().
/  (0:Disable, 1:Enable) */
#define FF_USE_MKUNLINK         1

/* This option specifies the availability of API f_rename() and f_getlabel().
/  (0:Disable, 1:Enable) */
#define FF_USE_RENAME           1
#define FF_USE_LGETLABEL        0

/* This option specifies the visibility of file name in the exFAT volume.
/  (0:Disable, 1:Enable) */
#define FF_USE_EXFAT            0

/* This option specifies the number of volumes (logical drives) to be used. (1-10) */
#define FF_VOLUMES              2

/* This option specifies the alignment of the file data buffer.
/  Specifies the byte offset from the start of the sector to the first byte of
/  the buffer. For optimal performance, this should be 32 or 64. */
#define FF_FS_NORTC_MAX_YEAR    2099
#define FF_NORTC_MON            1
#define FF_NORTC_MDAY           1

/*---------------------------------------------------------------------------
/  Locale and Namespace Configurations
/---------------------------------------------------------------------------*/

/* This option specifies the API encoding. (0:ANSI/OEM, 1:UTF-16, 2:UTF-8) */
#define FF_CODE_PAGE            936     // Simplified Chinese (GB2312)

/* This option specifies whether f_mkfs() creates EXFAT volume. (0:Disable, 1:Enable) */
#define FF_EXFAT                0

/* This option specifies the offset to add to the returned year of f_stat(),
/  f_getdate(), and f_gettime() to convert it to the Unix epoch. Default is 80
/  which means 1980 + 80 = 2060. Set 0 to disable offset. */
#define FF_FS_NORTC_YEAR        80

/*---------------------------------------------------------------------------
/  Character Encoding Support
/---------------------------------------------------------------------------*/

/* This option specifies the LFN API. (0:Disable, 1:Enable) */
#define FF_USE_LFN              2       // 0:Disable, 1:Enable, 2:Enable with static LFN buffer

/* Maximum LFN length. (128, 256, 512) */
#define FF_MAX_LFN              255

/* Stack working buffer for directory reads. This should be 512 bytes at minimum. */
#define FF_DIR_BUFFER_SIZE       512

/* This option switches the behavior of stack working buffer for LFN.
/  (0:Static, 1:Dynamic) */
#define FF_ALLOC_SIZE            0

/* This option specifies the maximum sector size to be supported. (512, 1024, 2048, 4096) */
#define FF_MAX_SS               512

/* This option specifies the sector size to assume. (512, 1024, 2048, 4096) */
#define FF_SS_SECTORIZE         512

/*---------------------------------------------------------------------------
/  System Configurations
/---------------------------------------------------------------------------*/

/* This option specifies the priority of persistent disk access.
/  (0:Disable, 1-8:Priority level) */
#define FF_FS_DORD              0

/* This option specifies the timeout period forFF_FS_EXFAT. (0-0xFFFF) */
#define FF_TIMEOUT_MS            5000

/* This option specifies the number of retries for failed disk accesses. (1-255) */
#define FF_RETRY_ACCESS          1

/* This option specifies the availability of path name arguments in the string
/  functions. (0:Disable, 1:Enable) */
#define FF_STR_VOLUME_ID         0
#define FF_VOLUME_STRS           "ram","sd","sd","sd","sd","sd","sd","sd","sd","sd"

/* This option enables or disables the real-time FFTASK feature. (0:Disable, 1:Enable) */
#define FF_FS_TASK_PRIO          0
#define FF_FS_TASK_STACK         2048
#define FF_FS_TASK_AFFINITY      0

/* This option specifies the hooks for custom additional functions. */
#define FF_FFLAGS                0
#define FF_FS_GDATA              0
#define FF_FS_GOBJ               0
#define FF_FS_GLOCK              0

#endif /* FF_CONF_H */
