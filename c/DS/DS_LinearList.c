#include <stdio.h>
#include <errno.h>

#include "DS_LinearList.h"



/*************************************************************************************************************
������    : SQListInit
��������  : ��ʼ�����Ա�
���      : ullElementLength ����Ԫ�س���;ullElementsSize Ԫ���ܸ���
����      : pstSQList����ʼ��������Ա�    :      
����ֵ    :  0,�ɹ�
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
������    : SQListDestory
��������  : �������Ա�
���      : pstSQList
����      : ��
����ֵ    :  0,�ɹ�
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
������    : SQListClear
��������  : ���Ա�����
���      : pstSQList
����      : ��
����ֵ    :  0,�ɹ�
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
������    : SQListGetElement
��������  : ��ȡԪ��
���      : pstSQList�����Ա�
            ullIndex�����Ա��е�λ��
            iElementAddress��Ԫ�ص�ַ���洢��ȡ��Ԫ��
����      : ��
����ֵ    :  0,�ɹ�
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
������    : SQListLocateElem
��������  : ��ȡԪ�������Ա��е�λ�ã�ͨ������comp�ж��洢�ڵ�ַiElementAddress�е�Ԫ���Ƿ����
���      : pstSQList�����Ա�            
            iElementAddress��Ԫ�ص�ַ
            comp,�Ƚ�Ԫ��
����      : ullIndex�����Ա��е�λ��
����ֵ    :  0,�ɹ���ȡ��-1 ��ȡʧ��
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
������    : SQListInsertEndElem
��������  : ��˳���ĩβ���Ԫ��
���      : pstSQList�����Ա�            
            iElementAddress��Ԫ�ص�ַ
            comp,�Ƚ�Ԫ��
����      : ullIndex�����Ա��е�λ��
����ֵ    :  0,�ɹ���ȡ��-1 ��ȡʧ��
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
������    :  SQListDelteElem
��������  :   ɾ��˳�����Ԫ��
���      : pstS QList�����Ա�            
            iElementAddress��Ԫ�ص�ַ
            comp,�Ƚ�Ԫ��
����      : ullIndex�����Ա��е�λ��
����ֵ    :  0,�ɹ���ȡ��-1 ��ȡʧ��
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