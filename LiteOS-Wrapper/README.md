# liteOs兼容层

## Task 兼容情况

| 接口名                   | 描述                                                         | 支持情况 | 原因 | 是否验证 |
| ------------------------ | ------------------------------------------------------------ | -------- | ---- | -------- |
| LOS_TaskCreateOnly       | 创建任务，并使该任务进入suspend状态，不对该任务进行调度。如果需要调度，可以调用LOS_TaskResume使该任务进入ready状态 | 支持     |      | 是       |
| LOS_TaskCreate           | 创建任务，并使该任务进入ready状态，如果就绪队列中没有更高优先级的任务，则运行该任务 | 支持     |      |          |
| LOS_TaskCreateOnlyStatic | 创建任务，任务栈由用户传入，并使该任务进入suspend状态，不对该任务进行调度。如果需要调度，可以调用LOS_TaskResume使该任务进入ready状态 | 支持     |      |          |
| LOS_TaskCreateStatic     | 创建任务，任务栈由用户传入，并使该任务进入ready状态，如果就绪队列中没有更高优先级的任务，则运行该任务 | 支持     |      |          |
| LOS_TaskDelete           | 删除指定的任务                                               | 支持     |      |          |
| LOS_TaskResume           | 恢复挂起的任务，使该任务进入ready状态                        | 支持     |      |          |
| LOS_TaskSuspend          | 挂起指定的任务，然后切换任务                                 | 支持     |      |          |
| LOS_TaskDelay            | 任务延时等待，释放CPU，等待时间到期后该任务会重新进入ready状态 | 支持     |      |          |
| LOS_TaskYield            | 当前任务释放CPU，并将其移到具有相同优先级的就绪任务队列的末尾 | 支持     |      |          |
| LOS_TaskLock             | 锁任务调度，但任务仍可被中断打断                             | 不支持   |      |          |
| LOS_TaskUnlock           | 解锁任务调度                                                 | 不支持   |      |          |
| LOS_CurTaskPriSet        | 设置当前任务的优先级                                         | 支持     |      |          |
| LOS_TaskPriSet           | 设置指定任务的优先级                                         | 支持     |      |          |
| LOS_TaskPriGet           | 获取指定任务的优先级                                         | 支持     |      |          |
| LOS_TaskCpuAffiSet       | 设置指定任务的运行cpu集合（该函数仅在SMP模式下支持）         | 支持     |      |          |
| LOS_TaskResRecycle       | 回收所有待回收的任务栈资源                                   |          |      |          |
| LOS_CurTaskIDGet         | 获取当前任务的ID                                             | 支持     |      |          |
| LOS_TaskInfoGet          | 获取指定任务的信息，包括任务状态、优先级、任务栈大小、栈顶指针SP、任务入口函数、已使用的任务栈大小等 |          |      |          |
| LOS_TaskCpuAffiGet       | 获取指定任务的运行cpu集合（该函数仅在SMP模式下支持）         | 支持     |      |          |
| LOS_TaskSwitchHookReg    | 注册任务上下文切换的钩子函数。只有开启LOSCFG_BASE_CORE_TSK_MONITOR宏开关后，这个钩子函数才会在任务发生上下文切换时被调用 | 支持     |      |          |
| LOS_IdleHandlerHookReg   | 注册空闲任务钩子函数，当系统空闲时调用                       | 支持     |      |          |

