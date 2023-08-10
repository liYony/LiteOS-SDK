#include "los_base.h"
#include "los_task.h"

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskCreateOnly(UINT32 *taskId, TSK_INIT_PARAM_S *initParam)
{
    rt_thread_t thread = rt_thread_create(initParam->pcName,
                                          (void (*)(void *))initParam->pfnTaskEntry,
                                          initParam->pArgs,
                                          initParam->uwStackSize,
                                          initParam->usTaskPrio,
                                          10);
    if (thread == RT_NULL)
    {
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    /* calculate priority attribute */
#if RT_THREAD_PRIORITY_MAX > 32
    thread->number = thread->current_priority >> 3; /* 5bit */
    thread->number_mask = 1L << thread->number;
    thread->high_mask = 1L << (thread->current_priority & 0x07); /* 3bit */
#else
    thread->number_mask = 1L << thread->current_priority;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

    /* change thread stat */
    thread->stat = RT_THREAD_SUSPEND;

    *taskId = (UINT32)thread;

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskCreate(UINT32 *taskId, TSK_INIT_PARAM_S *initParam)
{
    UINT32 ret;

    ret = LOS_TaskCreateOnly(taskId, initParam);
    if (ret != LOS_OK)
    {
        return ret;
    }

    if (rt_thread_resume((rt_thread_t)*taskId) != RT_EOK)
    {
        return LOS_ERRNO_TSK_NOT_SUSPENDED;
    }

    if (rt_thread_self() != RT_NULL)
    {
        /* do a scheduling */
        rt_schedule();
    }

    return LOS_OK;
}

#ifdef LOSCFG_TASK_STATIC_ALLOCATION
UINT32 LOS_TaskCreateOnlyStatic(UINT32 *taskId, TSK_INIT_PARAM_S *initParam, VOID *topStack)
{
    rt_err_t result = RT_EOK;
    rt_thread_t thread;

    thread = (struct rt_thread *)rt_malloc(sizeof(struct rt_thread));
    if (thread == RT_NULL)
    {
        return LOS_ERRNO_TSK_NO_MEMORY;
    }

    result = rt_thread_init(thread,
                            initParam->pcName,
                            (void (*)(void *))initParam->pfnTaskEntry,
                            initParam->pArgs,
                            topStack, initParam->uwStackSize,
                            initParam->usTaskPrio, 10);
    if (result != RT_EOK)
    {
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    /* calculate priority attribute */
#if RT_THREAD_PRIORITY_MAX > 32
    thread->number = thread->current_priority >> 3; /* 5bit */
    thread->number_mask = 1L << thread->number;
    thread->high_mask = 1L << (thread->current_priority & 0x07); /* 3bit */
#else
    thread->number_mask = 1L << thread->current_priority;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

    /* change thread stat */
    thread->stat = RT_THREAD_SUSPEND;

    *taskId = (UINT32)thread;

    return LOS_OK;
}

UINT32 LOS_TaskCreateStatic(UINT32 *taskId, TSK_INIT_PARAM_S *initParam, VOID *topStack)
{
    UINT32 ret;

    ret = LOS_TaskCreateOnlyStatic(taskId, initParam, topStack);
    if (ret != LOS_OK)
    {
        return ret;
    }

    if (rt_thread_resume((rt_thread_t)*taskId) != RT_EOK)
    {
        return LOS_ERRNO_TSK_NOT_SUSPENDED;
    }

    if (rt_thread_self() != RT_NULL)
    {
        /* do a scheduling */
        rt_schedule();
    }

    return LOS_OK;
}
#endif

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskDelete(UINT32 taskId)
{
    rt_thread_t thread = (rt_thread_t)taskId;

    if (rt_object_is_systemobject((rt_object_t)thread) == RT_TRUE)
    {
        rt_thread_detach(thread);
    }
#ifdef RT_USING_HEAP
    else
    {
        rt_thread_delete(thread);
    }
#endif /* RT_USING_HEAP */
    rt_schedule();

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskResume(UINT32 taskId)
{
    if (rt_thread_resume((rt_thread_t)taskId) != RT_EOK)
    {
        return LOS_ERRNO_TSK_NOT_SUSPENDED;
    }

    if (rt_thread_self() != RT_NULL)
    {
        /* do a scheduling */
        rt_schedule();
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskSuspend(UINT32 taskId)
{
    if (rt_thread_suspend((rt_thread_t)taskId) != RT_EOK)
    {
        return LOS_ERRNO_TSK_ALREADY_SUSPENDED;
    }

    if (rt_thread_self() != RT_NULL)
    {
        /* do a scheduling */
        rt_schedule();
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_TaskDelay(UINT32 tick)
{
    if (tick == 0)
    {
        rt_thread_yield();
    }
    else
    {
        rt_thread_delay(tick);
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskYield(VOID)
{
    rt_thread_yield();

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_TaskLock(VOID)
{
    // rt_enter_critical();
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_TaskUnlock(VOID)
{
    // rt_exit_critical();
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskPriSet(UINT32 taskId, UINT16 taskPrio)
{
    if ((rt_thread_t)taskId == RT_NULL)
    {
        return LOS_ERRNO_TSK_ID_INVALID;
    }
    if (taskPrio > RT_THREAD_PRIORITY_MAX)
    {
        return LOS_ERRNO_TSK_PRIOR_ERROR;
    }

    rt_thread_control((rt_thread_t)taskId, RT_THREAD_CTRL_CHANGE_PRIORITY, &taskPrio);

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_CurTaskPriSet(UINT16 taskPrio)
{
    rt_thread_t thread = rt_thread_self();

    return LOS_TaskPriSet((UINT32)thread, taskPrio);
}

LITE_OS_SEC_TEXT_MINOR UINT16 LOS_TaskPriGet(UINT32 taskId)
{
    rt_thread_t thread = (rt_thread_t)taskId;

    return thread->current_priority;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskCpuAffiSet(UINT32 taskId, UINT16 cpuAffiMask)
{
#ifdef LOSCFG_KERNEL_SMP
    rt_uint8_t cpu;

    for (int i = 0; i < 16; i++)
    {
        if ((1 << i) == cpuAffiMask)
        {
            cpu = i + 1;
            break;
        }
    }

    rt_thread_control((rt_thread_t)taskId, RT_THREAD_CTRL_BIND_CPU, cpuAffiMask);
#endif

    return LOS_OK;
}

VOID LOS_TaskResRecycle(VOID)
{
    rt_kprintf("not support\r\n");
}

LITE_OS_SEC_TEXT UINT32 LOS_CurTaskIDGet(VOID)
{
    rt_thread_t thread = rt_thread_self();

    rt_kprintf("not support\r\n");

    return (UINT32)thread;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskInfoGet(UINT32 taskId, TSK_INFO_S *taskInfo)
{
    rt_thread_t thread = (rt_thread_t)taskId;

    rt_kprintf("not support\r\n");

    return (UINT32)thread;
}

LITE_OS_SEC_TEXT_MINOR UINT16 LOS_TaskCpuAffiGet(UINT32 taskId)
{
#ifdef LOSCFG_KERNEL_SMP
    rt_thread_t thread = (rt_thread_t)taskId;

    return (1 << (thread->bind_cpu - 1));
#endif

    return LOS_OK;
}

#ifdef LOSCFG_BASE_CORE_TSK_MONITOR
LITE_OS_SEC_TEXT_MINOR VOID LOS_TaskSwitchHookReg(TSKSWITCHHOOK hook)
{
    rt_scheduler_sethook((void (*)(struct rt_thread *, struct rt_thread *))hook);
}
#endif /* LOSCFG_BASE_CORE_TSK_MONITOR */

LITE_OS_SEC_TEXT_MINOR VOID LOS_LowpowerHookReg(LOWPOWERIDLEHOOK hook)
{
    rt_kprintf("not support\r\n");
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_IdleHandlerHookReg(IDLEHANDLERHOOK hook)
{
    rt_thread_idle_sethook(hook);
}
