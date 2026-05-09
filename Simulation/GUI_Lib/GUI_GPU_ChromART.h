/*********************************************************************
*                  (c) SEGGER Microcontroller GmbH                   *
*                        The Embedded Experts                        *
*                           www.segger.com                           *
**********************************************************************

----------------------------------------------------------------------
File        : GUI_GPU_ChromART.h
Purpose     : Header of ST ChromART GPU driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_GPU_CHROMART_H
#define GUI_GPU_CHROMART_H

#include "GUI.h"

#if (GUI_SUPPORT_GPU)

#include "GUI_GPU.h"

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GPU_CHROMART_CONFIG
* 
*  Description
*    Configuration structure used for ChromART driver (GUI_GPU_CHROMART)
*    during creation with GUI_GPU_Create().
*/
typedef struct {
  void              * pDMA2D;                  // ChromART peripheral base address.
  GUI_VOID_FUNCTION * pfPreExecHook;           // Hook to be called before the execution of one action.
  GUI_VOID_FUNCTION * pfPostExecHook;          // Hook to be called after the execution of one action.
  GUI_VOID_FUNCTION * pfTransferCompleteHook;  // Hook to be called from within the IRQ handler after
                                               // the transfer has been completed.
  U8                  FillAlpha : 1;           // Some ChromART devices are able to fill rectangles with
                                               // alpha blending while other devices are not able to do this.
                                               // If this flag is true, the routine for filling rectangles
                                               // will make use of this feature.
} GUI_GPU_CHROMART_CONFIG;

#endif /* GUI_SUPPORT_GPU */

#endif /* GUI_GPU_CHROMART_H */

/*************************** End of file ****************************/
