/*绾挎?ц〃澶存枃�?*/
#ifndef __DS_LINEARLIST_H__
#define __DS_LINEARLIST_H__

#define DS_Printf(fmt,args...) printf("[%s] " fmt "\n",__func__,##args)
#define DS_FAILED (-1)
#define DS_SUCCESS (0)
#define DS_REALLOC_NUM (10)

/*************************************************************************************************************
������    : ElementCommpare
��������  : ����ָ��
���      : iElementAddress1��iElementAddress2
����      : pstSQList����ʼ��������Ա�    :      
����ֵ    :  0,�ɹ�
***************************************************************************************************************/
typedef int (*ElementCommpare)(int iElementAddress1,int iElementAddress2);

/*********************************************
˳��洢�����Ա�
*********************************************/
typedef struct SequenceList_ST_
{
    int iElementAddress;                         /* Ԫ�ص�ַ     */
    unsigned long long ullElementLength;         /* ����Ԫ�س��� */
    unsigned long long ullElementsSize;          /* Ԫ���ܸ���   */
	unsigned long long ullElementsNum;          /* Ԫ�ص�ǰ���ڸ���*/
}ZTT_SQLIST_ST;

/*************************************************************************************************************
������    : SQListInit
��������  : ��ʼ�����Ա�
���      : ullElementLength ����Ԫ�س���;ullElementsSize Ԫ���ܸ���
����      : pstSQList����ʼ��������Ա�    :      
����ֵ    :  0,�ɹ�
***************************************************************************************************************/
int SQListInit(ZTT_SQLIST_ST *pstSQList, unsigned long long ullElementLength, unsigned long long ullElementsSize);
/*************************************************************************************************************
������    : SQListDestory
��������  : �������Ա�
���      : pstSQList
����      : ��
����ֵ    :  0,�ɹ�
***************************************************************************************************************/
int SQListDestory(ZTT_SQLIST_ST *pstSQList);

/*************************************************************************************************************
������    : SQListClear
��������  : ���Ա�����
���      : pstSQList
����      : ��
����ֵ    :  0,�ɹ�
***************************************************************************************************************/
int SQListClear(ZTT_SQLIST_ST *pstSQList);

/*************************************************************************************************************
������    : SQListClear
��������  : ���Ա�����
���      : pstSQList
����      : ��
����ֵ    :  0,�ɹ�
***************************************************************************************************************/
int SQListClear(ZTT_SQLIST_ST *pstSQList);

/*************************************************************************************************************
������    : SQListGetElement
��������  : ��ȡԪ��
���      : pstSQList�����Ա���
            ullIndex�����Ա��е�λ��
            iElementAddress��Ԫ�ص�ַ���洢��ȡ��Ԫ��
����      : ��
����ֵ    :  0,�ɹ�
***************************************************************************************************************/
int SQListGetElement(ZTT_SQLIST_ST *pstSQList, unsigned long long ullIndex, int iElementAddress );

/*************************************************************************************************************
������    : SQListLocateElem
��������  : ��ȡԪ�������Ա��е�λ�ã�ͨ������comp�ж��洢�ڵ�ַiElementAddress�е�Ԫ���Ƿ����
���      : pstSQList�����Ա���            
            iElementAddress��Ԫ�ص�ַ
            comp,�Ƚ�Ԫ��
����      : ullIndex�����Ա��е�λ��
����ֵ    :  0,�ɹ���ȡ��-1 ��ȡʧ��
***************************************************************************************************************/
int SQListLocateElem(ZTT_SQLIST_ST *pstSQList, int iElementAddress, ElementCommpare comp, unsigned long long *ullIndex );

/*************************************************************************************************************
������    : SQListInsertElem
��������  : ��ȡԪ�������Ա��е�λ�ã�ͨ������comp�ж��洢�ڵ�ַiElementAddress�е�Ԫ���Ƿ����
���      : pstSQList�����Ա���            
            iElementAddress��Ԫ�ص�ַ
            comp,�Ƚ�Ԫ��
����      : ullIndex�����Ա��е�λ��
����ֵ    :  0,�ɹ���ȡ��-1 ��ȡʧ��
***************************************************************************************************************/
int SQListInsertElem(ZTT_SQLIST_ST *pstSQList, int iElementAddress );

#endif