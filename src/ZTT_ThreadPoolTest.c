#include "ZTT_ThreadPool.h"
#include "ZTT_Comm.h"
#include <stdio.h>
#define CHECK_PARAM(x) do{if(NULL == x) return NULL;}while(0)
void *taskprocess(void *arg)
{
    CHECK_PARAM(arg);
    printf("aaaaaadoing tasksaaaaaaaaa\n");
    sleep(1);
    return NULL;
}
 
 
int main(int argc, char *argv[])
{
    ZTT_PTHREAD_POOL_ST *pool= NULL;
    ZTT_ThreadPoolInit(&pool,5);
    printf("thread_num:%d\n",pool->thread_num);
    int i;
    for(i=1; i<=10; i++)
    {
        ZTT_TAST_ST *new_task=NULL;
        int iRet = ZTT_TaskInit(&new_task,i, (void*)taskprocess, NULL);
        if(ZTT_SUCCESS != iRet)
        {
                continue;
        }
        printf("will add task %d\n",i);
        iRet= ZTT_ThreadPoolAddTask(pool,new_task);
        if(ZTT_SUCCESS != iRet)
        {
                continue;
        }
        printf("add task %d\n",i);
        usleep(1000);
    }
    sleep(5);
    ZTT_ThreadPoolDestroy(pool);
    return 0;
}