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
File        : KeyHandler.h
Purpose     : Keyboard input handler for runtime language switching
---------------------------END-OF-HEADER------------------------------
*/

#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include <stdint.h>

/*********************************************************************
*
*       Key definitions for runtime control
*
**********************************************************************
*/
/* Keyboard shortcuts:
 *   F1      - Toggle language (English/Chinese)
 *   F2      - Show system info
 *   F3      - Refresh display
 */

/* Initialize keyboard handler */
void KEY_Init(void);

/* Process keyboard input - call this in main loop */
void KEY_Process(void);

/* Check if language was toggled (for GUI to react) */
int KEY_IsLanguageToggled(void);
void KEY_ClearLanguageToggle(void);

#endif /* KEY_HANDLER_H */
