#ifndef __ZTT_THREAD_POOL_H__
#define __ZTT_THREAD_POOL_H__
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
 
typedef  void (*TASK_FUNC)(void *args);
typedef struct ZTT_TAST_ST_
{
    TASK_FUNC  task_func;
    void       *task_func_args;//函数的参数
    int        task_id;
    struct     ZTT_TAST_ST_ *next;
}ZTT_TAST_ST;
 
typedef struct ZTT_PTHREAD_POOL_ST_
{
    ZTT_TAST_ST     *task_queue_head;        //任务队列
    int             current_task_queue_num;  //任务数
 
    pthread_t       *thread_queue;           //线程队列
    int             thread_num;
    
    int             idle_thread_num;         //空闲线程数
 
    int             is_pool_destroyed;
 
    pthread_mutex_t queue_mutex;//用来互斥访问任务队列
    pthread_cond_t  queue_cond;
}ZTT_PTHREAD_POOL_ST;
 



#ifdef __cplusplus
extern "C"{
#endif

extern int ZTT_TaskInit(ZTT_TAST_ST **new_task,int task_id, TASK_FUNC task_fun, void *task_fun_args);
extern int ZTT_TaskRelease(ZTT_TAST_ST *task);
extern int ZTT_ThreadPoolInit(ZTT_PTHREAD_POOL_ST **pool,int thread_pool_num);
extern int ZTT_ThreadPoolAddTask(ZTT_PTHREAD_POOL_ST *pool,ZTT_TAST_ST *new_task);
extern int ZTT_ThreadPoolDestroy(ZTT_PTHREAD_POOL_ST *pool);
 
void * ZTT_ThreadPoolSched(void *arg);
#ifdef __cplusplus
}
#endif
 
#endif //THREAD_POOL_H