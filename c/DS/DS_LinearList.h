/*缁炬寧?褑銆冩径瀛樻瀮娴?*/
#ifndef __DS_LINEARLIST_H__
#define __DS_LINEARLIST_H__

#define DS_Printf(fmt,args...) printf("[%s] " fmt "\n",__func__,##args)
#define DS_FAILED (-1)
#define DS_SUCCESS (0)
#define DS_REALLOC_NUM (10)

/*************************************************************************************************************
函数名    : ElementCommpare
功能描述  : 函数指针
入参      : iElementAddress1，iElementAddress2
出参      : pstSQList，初始化后的线性表    :      
还回值    :  0,成功
***************************************************************************************************************/
typedef int (*ElementCommpare)(int iElementAddress1,int iElementAddress2);

/*********************************************
顺序存储，线性表
*********************************************/
typedef struct SequenceList_ST_
{
    int iElementAddress;                         /* 元素地址     */
    unsigned long long ullElementLength;         /* 单个元素长度 */
    unsigned long long ullElementsSize;          /* 元素总个数   */
	unsigned long long ullElementsNum;          /* 元素当前存在个数*/
}ZTT_SQLIST_ST;

/*************************************************************************************************************
函数名    : SQListInit
功能描述  : 初始化线性表
入参      : ullElementLength 单个元素长度;ullElementsSize 元素总个数
出参      : pstSQList，初始化后的线性表    :      
还回值    :  0,成功
***************************************************************************************************************/
int SQListInit(ZTT_SQLIST_ST *pstSQList, unsigned long long ullElementLength, unsigned long long ullElementsSize);
/*************************************************************************************************************
函数名    : SQListDestory
功能描述  : 销毁线性表
入参      : pstSQList
出参      : 无
还回值    :  0,成功
***************************************************************************************************************/
int SQListDestory(ZTT_SQLIST_ST *pstSQList);

/*************************************************************************************************************
函数名    : SQListClear
功能描述  : 线性表清零
入参      : pstSQList
出参      : 无
还回值    :  0,成功
***************************************************************************************************************/
int SQListClear(ZTT_SQLIST_ST *pstSQList);

/*************************************************************************************************************
函数名    : SQListClear
功能描述  : 线性表清零
入参      : pstSQList
出参      : 无
还回值    :  0,成功
***************************************************************************************************************/
int SQListClear(ZTT_SQLIST_ST *pstSQList);

/*************************************************************************************************************
函数名    : SQListGetElement
功能描述  : 获取元素
入参      : pstSQList，线性表；
            ullIndex，线性表中的位置
            iElementAddress，元素地址，存储获取的元素
出参      : 无
还回值    :  0,成功
***************************************************************************************************************/
int SQListGetElement(ZTT_SQLIST_ST *pstSQList, unsigned long long ullIndex, int iElementAddress );

/*************************************************************************************************************
函数名    : SQListLocateElem
功能描述  : 获取元素在线性表中的位置，通过函数comp判读存储在地址iElementAddress中的元素是否存在
入参      : pstSQList，线性表；            
            iElementAddress，元素地址
            comp,比较元素
出参      : ullIndex，线性表中的位置
还回值    :  0,成功获取，-1 获取失败
***************************************************************************************************************/
int SQListLocateElem(ZTT_SQLIST_ST *pstSQList, int iElementAddress, ElementCommpare comp, unsigned long long *ullIndex );

/*************************************************************************************************************
函数名    : SQListInsertElem
功能描述  : 获取元素在线性表中的位置，通过函数comp判读存储在地址iElementAddress中的元素是否存在
入参      : pstSQList，线性表；            
            iElementAddress，元素地址
            comp,比较元素
出参      : ullIndex，线性表中的位置
还回值    :  0,成功获取，-1 获取失败
***************************************************************************************************************/
int SQListInsertElem(ZTT_SQLIST_ST *pstSQList, int iElementAddress );

#endif