#include "stdafx.h"

//���Ա��˳���ʾ�ʹ洢�ṹ
# define YEAR 2020
# define LIST_INIT_SIZE 100//���Ա�洢�ռ�ĳ�ʼ������
# define LISTINCREMENT 10//���Ա�洢�ռ�ķ�������
# define ElemType int//������������
# define Status int
# define ERROR 0
# define OK 1
# define TRUE 1
# define FALSE 0
# define OVERFLOW -1

typedef struct
{
	ElemType *Elem;
	int Length;
	int ListSize;
}SqList;

//����һ���յ����Ա�L 
Status InitList(SqList *L)
{
	L->Elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!*L->Elem)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(OVERFLOW);
		return ERROR;
	}
	L->Length = 0;
	L->ListSize = LIST_INIT_SIZE;

	printf("���Ա���ɹ�!\n");
	return OK;
}

//����������Ա�ֵ 
Status ListAssign(SqList *L, ElemType *Array,int length)
{
	int i = 0, j = 0;

	while (j < length)
	{
		L->Elem[j++] = Array[i++];
	}

	L->Length = length;

	return OK;
}

//����Ϊ�ձ�
Status ClearList(SqList *L)
{
	int i;

	for (i = 0; i < L->Length; ++i)
		L->Elem[i] = 0;

	printf("���óɹ���\n");
	return OK;
}

//�������Ա�L
Status DestroyList(SqList *L)
{
	if (!L)
	{
		printf("���Ա����ڣ�\n");
		return ERROR;
	}

	while (!L->Elem)
		free(L->Elem);
	L->Length = 0;
	L->ListSize = 0;

	printf("ɾ���ɹ�\n");
	return OK;
}

//�ж����Ա��Ƿ�Ϊ�� 
Status ListEmpty(SqList L)
{
	if (L.Length == 0)
	{
		printf("���Ա�Ϊ�ձ�\n");
		return TRUE;
	}
	else
		return FALSE;
}

//�������Ա���
Status ListLength(SqList *L)
{
	if (!L)
	{
		printf("���Ա�����!\n");
		return ERROR;
	}
	return L->Length;
}

//���룺��L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1
Status ListInsert(SqList *L, int i, ElemType e)
{
	//�Ƿ�����λ�� 
	if (i < 1 || i > L->Length + 1)
	{
		printf("����λ�÷Ƿ�!\n");
		return ERROR;
	}

	//�������������鳤�� 
	if (L->Length == L->ListSize)
	{
		ElemType *new_base = (ElemType *)realloc(L->Elem, (L->ListSize + LISTINCREMENT) * sizeof(Status));

		if (!new_base)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			exit(OVERFLOW);
			return ERROR;
		}

		L->Elem = new_base;
		L->ListSize += LISTINCREMENT;
	}

	//�������������λ�������һ��
	if (i == L->Length + 1)
	{
		L->Elem[L->Length] = e;
	}
	else
	{
		ElemType *p = NULL;
		ElemType *q = &L->Elem[i - 1];

		for (p = &(L->Elem[L->Length - 1]); p >= q; --p)
		{
			*(p + 1) = *p;
		}

		*q = e;
	}

	L->Length++;

	return OK;
}

//ɾ�� ��ɾ����i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1
Status ListDelete(SqList *L, int i, ElemType *e)
{
	if (i < 1 || i > L->Length)
	{
		printf("�Ƿ��±�!\n");
		return ERROR;
	}

	int *p = &(L->Elem[i - 1]);
	*e = *p;
	int *q = L->Elem + L->Length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *(p);
	--L->Length;

	return OK;
}

//���ʺ���
Status visit(Status t)
{
	printf("%d ", t);//���ں궨��������ԣ��޸�Statusֵ�ǣ����ʺ�����������Ʒ���Ҫ��Ӧ���޸� 
					 /*���Է���ʧ������
					 if(t == 2)
					 return ERROR;
					 */
	return OK;
}

//���� 
Status ListTraverse(SqList L, Status(*visit)(ElemType e))
{
	if (!&L)
	{
		printf("������������!\n");
		return ERROR;
	}
	printf("��������:\n");
	int i;
	for (i = 0; i < L.Length; ++i)
	{
		if (!visit(L.Elem[i]))
		{
			printf("\nL.Elem[%d]����ʧ�ܣ�\n", i);
			return ERROR;
		}
	}

	return OK;
}

//��ȡcur_e��ֱ��ǰ��
//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��Ϊ����ǰ�����������ʧ��,pre_e�޶���   
Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e)
{
	int i;

	for (i = 0; i < L.Length; ++i)
	{
		if (L.Elem[i] == cur_e)
		{
			break;
		}
	}

	if (i == 0)
	{
		printf("cur_e�ǵ�һ��Ԫ��,û��ֱ��ǰ��!\n");
		return ERROR;
	}

	if (i == L.Length)
	{
		printf("cur_e������\n");
		return ERROR;
	}

	*pre_e = L.Elem[i - 1];

	return OK;
}

//��ȡcur_e��ֱ�Ӻ�� 
Status NextElem(SqList L, ElemType cur_e, ElemType *next_e)
{
	int i;
	for (i = 0; i < L.Length; ++i)
	{
		if (cur_e == L.Elem[i])
			break;
	}

	if (i == L.Length)
	{
		printf("������ֱ�Ӻ�̣�\n");
		return ERROR;
	}

	*next_e = L.Elem[i + 1];
	return OK;
}

//��e����L�е�i������Ԫ�ص�ֵ
Status GetElem(SqList L, int i, ElemType *e)
{
	if (ListEmpty(L))
	{
		return ERROR;
	}

	if (i < 0 || i > L.Length)
	{
		printf("position error!\n");
		return OVERFLOW;
	}
	*e = L.Elem[i - 1];
}

Status compare(ElemType a, ElemType b)
{
	if (a == b)
		return TRUE;
	else
		return FALSE;
}

//�������������е�һ������compare��ϵ��Ԫ�� 
Status LocateElem(SqList L, ElemType e, Status(*compare)(ElemType a, ElemType b))
{
	int i;

	for (i = 0; i < L.Length; ++i)
	{
		if (compare(e, L.Elem[i]))
		{
			return i + 1;
		}
	}

	return FALSE;
}

//�����������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La�� 
void reunion(SqList *La, SqList Lb)
{
	int La_len = ListLength(La);
	int Lb_len = ListLength(&Lb);
	int i, j;
	ElemType e;

	for (i = 0; i <= Lb_len; ++i)
	{
		GetElem(Lb, i, &e);
		if (!LocateElem(*La, e, compare))
			ListInsert(La, ++La_len, e);
	}
}

//��֪La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ�����
//�鲢la,lb�õ��µ����Ա�LcҲ����ֵ�ǵݼ� 
void MergeList(SqList La, SqList Lb, SqList *Lc)
{
	InitList(Lc);
	int i = 1, j = 1;
	int k = 0;
	int La_len = ListLength(&La), Lb_len = ListLength(&Lb);

	ElemType ai, bj;

	while ((i <= La_len) && (j <= Lb_len))
	{
		GetElem(La, i, &ai);
		GetElem(Lb, i, &bj);

		if (ai <= bj)
		{
			ListInsert(Lc, ++k, ai);
			++i;
		}
		else
		{
			ListInsert(Lc, ++k, bj);
			++j;
		}
	}

	while (i <= La_len)
	{
		GetElem(La, i++, &ai);
		ListInsert(Lc, ++k, ai);
	}
	while (j <= Lb_len)
	{
		GetElem(Lb, j++, &
			bj);
		ListInsert(Lc, ++k, ai);
	}
}

void MergeList_Sq(SqList La, SqList Lb, SqList *Lc)
{
	ElemType *pa = La.Elem, *pb = Lb.Elem;
	Lc->ListSize = Lc->Length = La.Length + Lb.Length;
	Lc->Elem = (ElemType *)malloc(Lc->ListSize * sizeof(ElemType));
	ElemType *pc = Lc->Elem;

	if (!Lc->Elem)
		exit(OVERFLOW);
	ElemType *pa_last = La.Elem + La.Length - 1;
	ElemType *pb_last = Lb.Elem + Lb.Length - 1;

	//�鲢 
	while (pa <= pa_last && pb <= pb_last)
	{
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}

	//����ʣ��Ԫ�� 
	while (pa <= pa_last)
		*pc++ = *pa++;
	while (pb <= pb_last)
		*pc++ = *pb++;
}


int main()
{
	SqList list;
	InitList(&list);
	ElemType m, pre_m, next_m, tmp;
	ElemType arr[5] = { 1,2,3,4,5 };

	ListAssign(&list, arr,5);
	ListTraverse(list, visit);
	
	
	/*
	GetElem(list, 4, &tmp);
	printf("��ȡ���ĵ��ĸ�Ԫ���ǣ�%d\n",tmp);
	printf("\n��һ����2����compare��ϵ���ǣ�%d\n",LocateElem(list, 2, compare));
	PriorElem(list,2,&pre_m);
	printf("%d\n",pre_m);
	NextElem(list,2,&next_m);
	printf("%d\n",next_m);
	GetElem(list,3,&tmp);
	printf("%d\n",tmp);
	//printf("%d\n",next_m);
	//printf("%d\n",pre_m);
	ListDelete(&list,4,&m);
	printf("\nɾ����Ԫ���ǣ�%d\n",m);
	ListTraverse(list,visit);
	*/

	return 0;
}