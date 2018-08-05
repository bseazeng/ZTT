#ifndef __ZTT_COMM_H__
#define __ZTT_COMM_H__

#define ZTT_FAIL (-1)
#define ZTT_SUCCESS (0)
#define ZTT_TRUE (1)
#define ZTT_FALSE (0)
#define ZTT_FREE(p) if(NULL != (p))\
{free((p));(p)= NULL}\

#define ZTT_CHECK_RET_NULL(p) if((p) == NULL)\
        {printf("%s:%d Warning: failed.\n",\
            __func__, __LINE__); return;}

        
#define ZTT_CHECK_RET_VAL(p, ret) if((p) == NULL)\
        {printf("%s:%d Warning: failed.\n", \
            __func__, __LINE__); return (ret);}
#endif