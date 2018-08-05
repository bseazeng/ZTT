#include "ZTT_ThreadPool.h"
#include "ZTT_Comm.h"

int ZTT_TaskInit(ZTT_TAST_ST **new_task,int task_id, TASK_FUNC task_fun, void *task_fun_args)
{
    *new_task = (ZTT_TAST_ST *)malloc(sizeof(ZTT_TAST_ST));
    if( NULL == *new_task )
    {
            printf("%s:malloc failed\n",__func__);
            return ZTT_FAIL;
    }
    
    (*new_task)->task_func = task_fun;
    (*new_task)->task_func_args = task_fun_args;
    (*new_task)->task_id = task_id;
    (*new_task)->next = NULL;
    return ZTT_SUCCESS;
}
int ZTT_TaskRelease(ZTT_TAST_ST *task)
{
        if(NULL != task )
        {
                free(task);
                task = NULL;
        }
}
void * ZTT_ThreadPoolSched(void *arg)
{
    ZTT_PTHREAD_POOL_ST *pool = (ZTT_PTHREAD_POOL_ST *)arg;
    
    while( ZTT_TRUE )
    {
        pthread_mutex_lock(&(pool->queue_mutex));
        while(0 == pool->current_task_queue_num && ZTT_FALSE == pool->is_pool_destroyed )//必须用while，防止假唤醒
        {
            printf ("thread 0x%ld is waiting\n", pthread_self ());
            pthread_cond_wait(&(pool->queue_cond),&(pool->queue_mutex));//等待的时候会解锁，唤醒后加锁
        }
 
        if(ZTT_TRUE == pool->is_pool_destroyed)
        {
            printf("thread %ld exit!!!\n",pthread_self());
            pthread_mutex_unlock(&(pool->queue_mutex));//中途退出最容易出错，注意要解锁
            pthread_exit(NULL);
        } 
        
        //从任务队列中取出任务  
        pool->current_task_queue_num--; 
        ZTT_TAST_ST *work = pool->task_queue_head;          
        pool->task_queue_head = work->next;         
        pthread_mutex_unlock(&(pool->queue_mutex));
        
 
        //回调函数        
        printf ("thread 0x%ld is starting to work[%d],current_task_queue_num=%d\n", pthread_self (),work->task_id,pool->current_task_queue_num);  
        work->task_func(work->task_func_args);
        ZTT_TaskRelease(work);   
      
       
    }
    return NULL;
}
 
 
int ZTT_ThreadPoolInit(ZTT_PTHREAD_POOL_ST **pool,int thread_pool_num)
{
    *pool = (ZTT_PTHREAD_POOL_ST *)malloc(sizeof(ZTT_PTHREAD_POOL_ST));//不要最先给线程池分配空间
 
    (*pool)->is_pool_destroyed = ZTT_FALSE;
 
    (*pool)->task_queue_head = NULL;
    (*pool)->current_task_queue_num = 0;
 
    (*pool)->thread_num = thread_pool_num;
    (*pool)->thread_queue = (pthread_t *)malloc((*pool)->thread_num * sizeof(pthread_t));
    (*pool)->idle_thread_num = 0;
 
    //创建线程
    int i, ret;
    for(i=0; i< (*pool)->thread_num; i++)
    {
        ret = pthread_create(&((*pool)->thread_queue[i]), NULL, ZTT_ThreadPoolSched, *pool);
        if(0>ret)
        {
            printf("thread create error!!!\n");
            ZTT_ThreadPoolDestroy(*pool);//注意销毁，避免内存泄漏
            return ZTT_FAIL;
        }
        (*pool)->idle_thread_num++;
    }
 
    pthread_mutex_init(&((*pool)->queue_mutex), NULL);
    pthread_cond_init(&((*pool)->queue_cond), NULL);
 
    return ZTT_SUCCESS;
}
 

int ZTT_ThreadPoolAddTask(ZTT_PTHREAD_POOL_ST *pool,ZTT_TAST_ST *new_task)
{ 
    pthread_mutex_lock(&(pool->queue_mutex));
 
    if( NULL == pool->task_queue_head )
    {
        pool->task_queue_head = new_task;
         printf("%s1:add task[%d]\n",__func__,new_task->task_id);
    }
    else
    {
         ZTT_TAST_ST *tmp = pool->task_queue_head;
         while(tmp->next)
         {
                tmp = tmp->next;
                printf("task:%d\n",tmp->task_id);
         }
         tmp->next = new_task;
         printf("%s2:add task[%d]\n",__func__,tmp->task_id);
    }
    
    pool->current_task_queue_num++;
    pthread_mutex_unlock(&(pool->queue_mutex));
 
    pthread_cond_signal(&(pool->queue_cond));
    
 
    return ZTT_SUCCESS;
}
 
 
int ZTT_ThreadPoolDestroy(ZTT_PTHREAD_POOL_ST *pool)
{
    if(ZTT_TRUE == pool->is_pool_destroyed)//防止多次销毁
        return ZTT_TRUE;
 
    pool->is_pool_destroyed = ZTT_TRUE;
 
    pthread_cond_broadcast(&(pool->queue_cond));//通知所有线程线程池销毁了
    int i;
    for(i=0; i<pool->thread_num; i++)//等待线程全部执行完
        pthread_join(pool->thread_queue[i], NULL);
 
    //销毁任务队列
    ZTT_TAST_ST *temp = NULL;
    while(pool->task_queue_head)
    {
        temp = pool->task_queue_head;
        pool->task_queue_head = temp->next;
        printf("free task:%d\n",temp->task_id);
        free(temp);
        temp = NULL;
    }
    //pool->task_queue_head = NULL；
    //pool->task_queue_end = NULL；
 
    //销毁线程队列
    free(pool->thread_queue);
    pool->thread_queue = NULL;
 
    pthread_mutex_destroy(&(pool->queue_mutex));
    pthread_cond_destroy(&(pool->queue_cond));
 
    free(pool);
    pool = NULL;
 
    return 0;
}