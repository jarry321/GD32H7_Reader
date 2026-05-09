/*********************************************************************
*                  (c) SEGGER Microcontroller GmbH                   *
*                        The Embedded Experts                        *
*                           www.segger.com                           *
**********************************************************************

----------------------------------------------------------------------
File        : GUI_SPY_Private.h
Purpose     : Private header file for Spy
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_SPY_PRIVATE_H
#define GUI_SPY_PRIVATE_H

#include "GUI_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#ifndef   GUI_SPY_COM_BUFFER_SIZE
  #define GUI_SPY_COM_BUFFER_SIZE 1000
#endif

#define JOB_REQUEST_STATUS  1
#define JOB_REQUEST_VERSION 2
#define JOB_REQUEST_WINDOWS 3
#define JOB_REQUEST_INPUT   4
#define JOB_REQUEST_BMP     5
#define JOB_QUIT            6

#define INPUT_PID    1
#define INPUT_KEY    2
#define INPUT_MTOUCH 3

#define TRY(x) x; if (r) return 1

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct SPY_CONTEXT SPY_CONTEXT;

struct SPY_CONTEXT{
  GUI_tSend pfSend;
  GUI_tRecv pfRecv;
  void * pConnectInfo;
  U8 acBuffer[GUI_SPY_COM_BUFFER_SIZE];
  int NumBytesInBuffer;
  int Result;
  int (* pfFlush)   (SPY_CONTEXT * pContext);
  int (* pfStoreU8) (SPY_CONTEXT * pContext,  U8 Byte);
  int (* pfStoreU16)(SPY_CONTEXT * pContext, U16 Data);
  int (* pfStoreU32)(SPY_CONTEXT * pContext, U32 Data);
  int (* pfRead)    (SPY_CONTEXT * pContext, U8 * buf, int len);
};

typedef struct {
  U16 Type;
  U32 Time;
  union {
    GUI_KEY_STATE    StateKEY;
    GUI_PID_STATE    StatePID;
    GUI_MTOUCH_STATE StateMTOUCH;
  } u;
} SPY_INPUT;



#endif // GUI_SPY_PRIVATE_H

/*************************** End of file ****************************/
