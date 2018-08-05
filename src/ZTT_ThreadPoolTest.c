
#include <stdio.h>

#include "ZTT_ThreadPool.h"
#include "ZTT_Comm.h"
#include "ZTT_Cmd.h"

int taskprocess(void *arg)
{
    ZTT_Printf("aaaaaadoing tasksaaaaaaaaa\n");
    //sleep(1);
    return 0;
}
 
 
int ZTT_CmdThreadPoolTest(int argc, char *argv[])
{
    ZTT_PTHREAD_POOL_ST *pool= NULL;
    ZTT_ThreadPoolInit(&pool,3);
    ZTT_Printf("thread_num:%d\n",pool->thread_num);
    int i;
    for(i=1; i<=10; i++)
    {
        ZTT_TAST_ST *new_task = NULL;
        int iRet = ZTT_TaskInit(&new_task,i, taskprocess, NULL);
        if(ZTT_SUCCESS != iRet)
        {
                continue;
        }
        iRet= ZTT_ThreadPoolAddTask(pool,new_task);
        if(ZTT_SUCCESS != iRet)
        {
                continue;
        }
        ZTT_Printf("add task %d\n",new_task->task_id);       
    }

    sleep(10);
    //ZTT_ThreadPoolDestroy(pool);
    return 0;
}

ZTT_CMD_REG(pl,ZTT_CmdThreadPoolTest);
