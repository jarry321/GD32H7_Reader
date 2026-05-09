# FreeRTOS集成使用说明

## 一、已创建的文件

### 1. RTOS配置文件
- `Source/RTOS/FreeRTOSConfig.h` - FreeRTOS配置文件

### 2. RTOS抽象层
- `Source/RTOS/RTOS_Wrapper.h` - RTOS接口定义
- `Source/RTOS/RTOS_Wrapper.c` - Windows模拟器RTOS实现

### 3. GUI任务
- `Source/RTOS/GUI_Task.c` - GUI任务实现（与emWin集成）

### 4. 入口程序
- `Source/RTOS/RTOS_Main.c` - 新的主入口（使用RTOS）

---

## 二、添加到工程

### 步骤1：复制文件到工程目录

确保以下文件存在：
```
d:\Code\Reader_UI\01\NewProject1\Source\RTOS\
├── FreeRTOSConfig.h
├── RTOS_Wrapper.h
├── RTOS_Wrapper.c
├── GUI_Task.c
└── RTOS_Main.c
```

### 步骤2：在Visual Studio中添加文件到工程

1. 打开Visual Studio
2. 打开工程：`Simulation_VS2019_Lib.sln`
3. 在Solution Explorer中，右键点击项目
4. 选择 `Add` → `Existing Item`
5. 添加以下文件：
   - `RTOS_Wrapper.c`
   - `GUI_Task.c`
   - `RTOS_Main.c`

### 步骤3：修改入口点（重要！）

**方法1：使用新的RTOS入口（推荐）**

在Visual Studio中：
1. 右键点击项目 → `Properties`
2. 选择 `Linker` → `System`
3. 修改 `Entry Point` 为 `main`

或者在代码中注释掉原有的MainTask函数。

**方法2：保持原有入口，添加RTOS初始化**

修改 `Source/APPW_MainTask.c`：

```c
#include "RTOS_Wrapper.h"

void MainTask(void) {
    // 初始化RTOS
    RTOS_Init();
    
    // 创建GUI任务
    RTOS_CreateGUITask();
    
    // 原有代码...
    APPW_X_Setup();
    APPW_Init(APPW_PROJECT_PATH);
    APPW_CreatePersistentScreens();
    APPW_CreateRoot(APPW_INITIAL_SCREEN, WM_HBKWIN);
    
    // 保持运行
    for (APPW_Run = 1; APPW_Run; ) {
        APPW_Exec();
        RTOS_Delay(5);
    }
}
```

---

## 三、任务架构

### 任务列表

| 任务名 | 优先级 | 栈大小 | 功能 |
|--------|--------|--------|------|
| GUI Task | 3 (高) | 4KB | emWin界面显示 |
| Comm Task | 2 (中) | 2KB | 通信处理（RFID数据） |
| Idle Task | 1 (低) | 2KB | 空闲处理 |

### 任务通信

```
┌─────────────┐
│  GUI Task   │ ◄─── 接收队列 ───┐
│  (显示界面) │                  │
└─────────────┘                  │
                                  │
┌─────────────┐     互斥锁        │
│  Comm Task  │ ───► [数据] ───► │
│  (RFID数据) │                  │
└─────────────┘                  │
                                  │
                              ┌───► [显示]
                              │
                              └───► [存储]
```

---

## 四、添加新任务

### 示例：添加RFID读取任务

```c
#include "RTOS_Wrapper.h"

// RFID读取任务
static void vRFIDTask(void *pvParameters) {
    printf("RFID Task: Started\n");
    
    while (1) {
        // 读取RFID标签
        // RFID_ReadTags();
        
        // 发送数据到队列
        // RTOS_SendQueue(hRFIDQueue, &tagData, 100);
        
        RTOS_Delay(100);
    }
}

// 在RTOS_CreateTasks()中添加：
RTOS_CreateTask(vRFIDTask, "RFID", 1024 * 2, NULL, 2);
```

---

## 五、队列和信号量使用

### 创建队列
```c
void* hQueue = RTOS_CreateQueue(10, sizeof(RFID_TAG_DATA));
```

### 发送数据
```c
RFID_TAG_DATA tag;
tag.epc = "12345678";
RTOS_SendQueue(hQueue, &tag, 100);
```

### 接收数据
```c
RFID_TAG_DATA tag;
RTOS_ReceiveQueue(hQueue, &tag, 1000);
```

### 使用信号量保护资源
```c
void* hMutex = RTOS_CreateMutex();

// 进入临界区
RTOS_TakeMutex(hMutex, 0xFFFFFFFF);
// 访问共享资源
// ...
// 退出临界区
RTOS_GiveMutex(hMutex);
```

---

## 六、编译和运行

### 编译
```
Build → Rebuild Solution
```

### 运行
```
按 F5 或 Ctrl+F5
```

### 预期输出
```
========================================
  RFID Reader - RTOS Version
  Based on GD32H7 + FreeRTOS
========================================

RTOS: Initialized (Simulation Mode)
RTOS: Created mutex
RTOS: Created task 'GUI' (Priority: 3)
RTOS: Created task 'Comm' (Priority: 2)
RTOS: Created task 'Idle' (Priority: 1)
Starting RTOS Scheduler...

GUI Task: Started
Communication Task: Started
Idle Task: Started
```

---

## 七、真实硬件迁移

当移植到真实GD32H7硬件时，需要：

1. **替换RTOS实现**
   - 将 `RTOS_Wrapper.c` 替换为真实的FreeRTOS代码
   - 使用CMSIS-RTOS或直接调用FreeRTOS API

2. **添加FreeRTOS源码**
   - 从 https://www.freertos.org 下载
   - 包含 `task.c`, `queue.c`, `list.c`, `port.c` 等

3. **配置硬件相关**
   - 修改 `FreeRTOSConfig.h` 中的硬件配置
   - 实现滴答定时器和中断处理

---

## 八、常见问题

### Q: 编译报错找不到RTOS文件
A: 确保文件已添加到Visual Studio工程

### Q: 程序卡死或崩溃
A: 检查是否有死锁或栈溢出

### Q: 界面显示异常
A: 确保GUI任务优先级最高

---

*文档版本：v1.0*
*创建日期：2024-05-08*
*适用于：GD32 RFID智能阅读器项目*
