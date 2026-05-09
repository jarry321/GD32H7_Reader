/*********************************************************************
*                  (c) SEGGER Microcontroller GmbH                   *
*                        The Embedded Experts                        *
*                           www.segger.com                           *
**********************************************************************

----------------------------------------------------------------------
File        : GUI_CACHE.h
Purpose     : Abstract LRU cache implementation
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_CACHE_H
#define GUI_CACHE_H

#include "GUI.h"

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef GUI_HMEM GUI_CACHE_Handle;

typedef GUI_BOOLEAN (GUI_CACHE_CHECKITEM_FUNC)(void * pKey, void * pValue, void * pData);

typedef enum {
  GUI_CACHE_ITEM_OWN_DATA,   // Full data is owned, that means item is copied.
  GUI_CACHE_ITEM_OWN_PTR,    // User creates object on heap, ownership is transferred to cache.
} GUI_CACHE_ITEM_OWNERSHIP;

typedef struct {
  unsigned                 SizeOfKey;
  unsigned                 SizeOfValue;
  GUI_CACHE_ITEM_OWNERSHIP KeyOwnership;
  GUI_CACHE_ITEM_OWNERSHIP ValueOwnership;
  U32                   (* pfHash)               (const void * pKey);
  GUI_BOOLEAN           (* pfCompareKeys)        (const void * p0, const void * p1);
  void                  (* pfFreeKey)            (void * pKey);
  void                  (* pfFreeValue)          (void * pValue);
  U32                   (* pfGetKeyPayloadSize)  (void * pKey);
  U32                   (* pfGetValuePayloadSize)(void * pKey);
} GUI_CACHE_CONFIG;

/*********************************************************************
*
*       Prototypes
*
**********************************************************************
*/
void             GUI_CACHE_Cleanup    (GUI_CACHE_Handle hCache);
void             GUI_CACHE_CleanupEx  (GUI_CACHE_Handle hCache, GUI_CACHE_CHECKITEM_FUNC * cbCheckItem, void * p);
GUI_CACHE_Handle GUI_CACHE_Create     (unsigned MaxItems, unsigned MaxBytes, const GUI_CACHE_CONFIG * pConfig);
void             GUI_CACHE_Delete     (GUI_CACHE_Handle hCache);
void           * GUI_CACHE_GetItem    (GUI_CACHE_Handle hCache, void * pKey);
void           * GUI_CACHE_GetItemRef (GUI_CACHE_Handle hCache, void * pKey);
unsigned         GUI_CACHE_GetNumItems(GUI_CACHE_Handle hCache);
unsigned         GUI_CACHE_GetNumBytes(GUI_CACHE_Handle hCache);
unsigned         GUI_CACHE_GetMaxItems(GUI_CACHE_Handle hCache);
unsigned         GUI_CACHE_GetMaxBytes(GUI_CACHE_Handle hCache);
void             GUI_CACHE_SetMaxItems(GUI_CACHE_Handle hCache, unsigned MaxItems);
void             GUI_CACHE_SetMaxBytes(GUI_CACHE_Handle hCache, unsigned MaxBytes);
void             GUI_CACHE_ReleaseItem(GUI_CACHE_Handle hCache, const void * pValue);
GUI_BOOLEAN      GUI_CACHE_AddItem    (GUI_CACHE_Handle hCache, void * pKey, void * pValue);

#endif /* GUI_CACHE_H */

/*************************** End of file ****************************/
