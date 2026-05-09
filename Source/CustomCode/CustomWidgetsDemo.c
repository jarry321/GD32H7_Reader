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
File        : CustomWidgetsDemo.c
Purpose     : Demo code showing how to use custom widgets
---------------------------END-OF-HEADER------------------------------
*/

#include "CustomWidgets.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static WM_HWIN _hStatusBar;
static WM_HWIN _hTagCard;
static WM_HWIN _hProgressCard;
static WM_HWIN _hStatCard;

// Demo data
static STATUS_BAR_INFO _DemoStatus = {
    .Battery = 85,
    .Signal = 3,
    .Connected = 1,
    .Time = "14:30"
};

static TAG_INFO _DemoTag = {
    .EPC = "E2003412BCD4567890AB",
    .Type = "Asset",
    .Status = 0,  // Normal
    .Timestamp = "2024-05-08 14:30"
};

static TASK_PROGRESS _DemoTask = {
    .Name = "Warehouse A Inventory",
    .Current = 90,
    .Total = 200,
    .Status = 0,  // Running
    .StartTime = "14:00",
    .EndTime = "14:30",
    .AbnormalCount = 3
};

static STAT_CARD_INFO _DemoStat = {
    .Title = "Read Count",
    .Value = 1234,
    .Unit = "",
    .Trend = 15
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       CreateCustomWidgetsDemo
*
*  Call this function from your screen callback to create demo widgets
*/
void CreateCustomWidgetsDemo(WM_HWIN hParent) {
    // Create status bar at top
    _hStatusBar = STATUS_BAR_Create(0, 0, 1024, 48, hParent);
    
    // Create tag card
    _hTagCard = TAG_CARD_Create(16, 60, 992, 80, hParent, ID_TAG_CARD);
    TAG_CARD_Update(_hTagCard, &_DemoTag);
    
    // Create progress card
    _hProgressCard = PROGRESS_CARD_Create(16, 150, 992, 120, hParent, ID_PROGRESS_CARD);
    PROGRESS_CARD_Update(_hProgressCard, &_DemoTask);
    
    // Create stat card
    _hStatCard = STAT_CARD_Create(16, 280, 300, 100, hParent, ID_STAT_CARD);
    STAT_CARD_Update(_hStatCard, &_DemoStat);
}

/*********************************************************************
*
*       UpdateDemoData
*
*  Call this periodically to update demo data
*/
void UpdateDemoData(void) {
    // Simulate battery drain
    if (_DemoStatus.Battery > 0) {
        _DemoStatus.Battery--;
    }
    
    // Simulate progress
    if (_DemoTask.Current < _DemoTask.Total) {
        _DemoTask.Current++;
    }
    
    // Update widgets
    STATUS_BAR_Update(_hStatusBar, &_DemoStatus);
    PROGRESS_CARD_Update(_hProgressCard, &_DemoTask);
}

/*************************** End of file ****************************/
