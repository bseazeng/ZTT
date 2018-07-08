#ifndef __ZTT_LIST_H__
#define __ZTT_LIST_H__
#include <stdio.h>
#include <string.h>

typedef struct ZTT_list_head
{
    struct ZTT_list_head *next;
    struct ZTT_list_head *prev;
}ZTT_ListHead_ST;

#define ZTT_LIST_HEAD_INIT INIT_ZTT_list_head

#define ZTT_offsetof(TYPE,MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - ZTT_offsetof(type,member) );})

static inline void INIT_ZTT_list_head(ZTT_ListHead_ST *list)
{
        list->next = list;
        list->prev = list;
}

static inline int ZTT_list_empty(ZTT_ListHead_ST *head)
{
	return head->next == head;
}

static inline void __ZTT_list_add(ZTT_ListHead_ST *new, ZTT_ListHead_ST *prev,ZTT_ListHead_ST *next)
{
        next->prev = new;
        new->next = next;
        new->prev = prev;
        prev->next = new;
}


static inline void ZTT_list_add(ZTT_ListHead_ST *new, ZTT_ListHead_ST *head)
{
        __ZTT_list_add(new, head, head->next);
}


static inline void __ZTT_list_del(ZTT_ListHead_ST * prev, ZTT_ListHead_ST * next)
{
        next->prev = prev;
        prev->next = next;
}

static inline void ZTT_list_del(ZTT_ListHead_ST *node)
{
        __ZTT_list_del(node->prev, node->next);
        node->next = NULL;
        node->prev = NULL;
}



#define prefetch(x) __builtin_prefetch(x)

#define ZTT_list_for_each(pos, head) \
         for (pos = (head)->next; prefetch(pos->next), pos != (head); \
                 pos = pos->next)
#define ZTT_list_for_each_prev(pos,head) for(pos = (head)->prev; prefetch(pos->prev),pos != (head); pos = pos->prev)

#define ZTT_list_entry(ptr, type, member) \
         container_of(ptr, type, member)
         
#define ZTT_list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#endif

