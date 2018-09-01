#include <stdio.h>
#include <errno.h>

#include "DS_LinearList.h"



/*************************************************************************************************************
函数名    : SQListInit
功能描述  : 初始化线性表
入参      : ullElementLength 单个元素长度;ullElementsSize 元素总个数
出参      : pstSQList，初始化后的线性表    :      
还回值    :  0,成功
***************************************************************************************************************/
int SQListInit(ZTT_SQLIST_ST *pstSQList, unsigned long long ullElementLength, unsigned long long ullElementsSize)
{
	if(NULL == pstSQList)
	{
		DS_Printf("pstSQList is NULL\n");
		return DS_FAILED;
	}
	
    pstSQList->iElementAddress = malloc(ullElementLength*ullElementsSize);
	if(0 == pstSQList->iElementAddress)
	{
		DS_Printf("malloc failed\n");
		return DS_FAILED;
	}
	
	pstSQList->ullElementLength = ullElementLength;
	pstSQList->ullElementsSize  = ullElementsSize;
	pstSQList->ullElementsNum   = 0;
	
    return DS_SUCCESS;
}

/*************************************************************************************************************
函数名    : SQListDestory
功能描述  : 销毁线性表
入参      : pstSQList
出参      : 无
还回值    :  0,成功
***************************************************************************************************************/
int SQListDestory(ZTT_SQLIST_ST *pstSQList)
{
	if(NULL == pstSQList)
	{
		DS_Printf("pstSQList is NULL\n");
		return DS_FAILED;
	}

	free(pstSQList->iElementAddress);
	pstSQList->iElementAddress  = 0;
	pstSQList->ullElementLength = 0;
	pstSQList->ullElementsSize  = 0;
	pstSQList->ullElementsNum   = 0;
	
	return DS_SUCCESS;
}

/*************************************************************************************************************
函数名    : SQListClear
功能描述  : 线性表清零
入参      : pstSQList
出参      : 无
还回值    :  0,成功
***************************************************************************************************************/
int SQListClear(ZTT_SQLIST_ST *pstSQList)
{
	if(NULL == pstSQList)
	{
		DS_Printf("pstSQList is NULL");
		return DS_FAILED;
	}
	
	memset(pstSQList->iElementAddress,0,pstSQList->ullElementLength*pstSQList->ullElementsSize);
	pstSQList->ullElementLength = 0;
	pstSQList->ullElementsSize  = 0;
	pstSQList->ullElementsNum   = 0;
	
	return DS_SUCCESS;
}

/*************************************************************************************************************
函数名    : SQListGetElement
功能描述  : 获取元素
入参      : pstSQList，线性表；
            ullIndex，线性表中的位置
            iElementAddress，元素地址，存储获取的元素
出参      : 无
还回值    :  0,成功
***************************************************************************************************************/
int SQListGetElement(ZTT_SQLIST_ST *pstSQList, unsigned long long ullIndex, int iElementAddress )
{
	if(NULL == pstSQList)
	{
		DS_Printf("pstSQList is NULL");
		return DS_FAILED;
	}
	
	if(ullIndex == pstSQList->ullElementsSize )
	{
		DS_Printf("ullIndex should be less than ullElementsSize");
		return DS_FAILED;
	}

	memcpy(iElementAddress,&(pstSQList->iElementAddress[ullIndex]),pstSQList->ullElementLength);
	return DS_SUCCESS;
}

/*************************************************************************************************************
函数名    : SQListLocateElem
功能描述  : 获取元素在线性表中的位置，通过函数comp判读存储在地址iElementAddress中的元素是否存在
入参      : pstSQList，线性表；            
            iElementAddress，元素地址
            comp,比较元素
出参      : ullIndex，线性表中的位置
还回值    :  0,成功获取，-1 获取失败
***************************************************************************************************************/
int SQListLocateElem(ZTT_SQLIST_ST *pstSQList, int iElementAddress, ElementCommpare comp, unsigned long long *ullIndex )
{
	if(NULL == pstSQList)
	{
		DS_Printf("pstSQList is NULL");
		return DS_FAILED;
	}
	unsigned long long i = 0;
	for(i=0;i<pstSQList->ullElementsNum;i++)
	{
		if(0 == comp(iElementAddress,pstSQList->iElementAddress[i]))
		{
			*ullIndex = i;
			break;
		}
	}

	if(i == pstSQList->ullElementsNum)
	{
		DS_Printf("Element is not exist\n");
		return DS_FAILED;
	}

	return DS_SUCCESS;
}

/*************************************************************************************************************
函数名    : SQListInsertEndElem
功能描述  : 在顺序表末尾添加元素
入参      : pstSQList，线性表；            
            iElementAddress，元素地址
            comp,比较元素
出参      : ullIndex，线性表中的位置
还回值    :  0,成功获取，-1 获取失败
***************************************************************************************************************/
int SQListInsertEndElem(ZTT_SQLIST_ST *pstSQList, int iElementAddress )
{
	if(NULL == pstSQList)
	{
		DS_Printf("pstSQList is NULL");
		return DS_FAILED;
	}

	if(pstSQList->ullElementsSize == pstSQList->ullElementsNum)
	{
		pstSQList->ullElementsSize += DS_REALLOC_NUM;
		pstSQList->iElementAddress  = realloc(pstSQList->ullElementsSize*pstSQList->ullElementLength);
		if(NULL == pstSQList->iElementAddress )
		{
			DS_Printf("realloc failed,errno=%d\n",errno);
			return DS_FAILED;
		}
	}

	memcpy(&(pstSQList->iElementAddress[pstSQList->ullElementsNum]),iElementAddress,pstSQList->ullElementLength);	
	pstSQList->ullElementsNum++;
}

/*************************************************************************************************************
函数名    :  SQListDelteElem
功能描述  :   删除顺序表中元素
入参      : pstS QList，线性表；            
            iElementAddress，元素地址
            comp,比较元素
出参      : ullIndex，线性表中的位置
还回值    :  0,成功获取，-1 获取失败
***************************************************************************************************************/
int SQListDelteElem(ZTT_SQLIST_ST *pstSQList, int iElementAddress )
{
	if(NULL == pstSQList)
	{
		DS_Printf("pstSQList is NULL");
		return DS_FAILED;
	}

	return DS_SUCCESS;
}