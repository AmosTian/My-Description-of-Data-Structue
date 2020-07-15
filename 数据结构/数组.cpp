#include "stdafx.h"

//线性表的顺序表示和存储结构
# define YEAR 2020
# define LIST_INIT_SIZE 100//线性表存储空间的初始分配量
# define LISTINCREMENT 10//线性表存储空间的分配增量
# define ElemType int//定义数据类型
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

//构造一个空的线性表L 
Status InitList(SqList *L)
{
	L->Elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!*L->Elem)
	{
		printf("内存分配失败！\n");
		exit(OVERFLOW);
		return ERROR;
	}
	L->Length = 0;
	L->ListSize = LIST_INIT_SIZE;

	printf("线性表构造成功!\n");
	return OK;
}

//用数组给线性表赋值 
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

//重置为空表
Status ClearList(SqList *L)
{
	int i;

	for (i = 0; i < L->Length; ++i)
		L->Elem[i] = 0;

	printf("重置成功！\n");
	return OK;
}

//销毁线性表L
Status DestroyList(SqList *L)
{
	if (!L)
	{
		printf("线性表不存在！\n");
		return ERROR;
	}

	while (!L->Elem)
		free(L->Elem);
	L->Length = 0;
	L->ListSize = 0;

	printf("删除成功\n");
	return OK;
}

//判断线性表是否为空 
Status ListEmpty(SqList L)
{
	if (L.Length == 0)
	{
		printf("线性表为空表！\n");
		return TRUE;
	}
	else
		return FALSE;
}

//返回线性表长度
Status ListLength(SqList *L)
{
	if (!L)
	{
		printf("线性表不存在!\n");
		return ERROR;
	}
	return L->Length;
}

//插入：在L中第i个位置之前插入新的数据元素e，L的长度加1
Status ListInsert(SqList *L, int i, ElemType e)
{
	//非法插入位置 
	if (i < 1 || i > L->Length + 1)
	{
		printf("插入位置非法!\n");
		return ERROR;
	}

	//若满，扩充数组长度 
	if (L->Length == L->ListSize)
	{
		ElemType *new_base = (ElemType *)realloc(L->Elem, (L->ListSize + LISTINCREMENT) * sizeof(Status));

		if (!new_base)
		{
			printf("内存分配失败！\n");
			exit(OVERFLOW);
			return ERROR;
		}

		L->Elem = new_base;
		L->ListSize += LISTINCREMENT;
	}

	//特殊情况，插入位置在最后一个
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

//删除 ：删除第i个数据元素，并用e返回其值，L的长度减1
Status ListDelete(SqList *L, int i, ElemType *e)
{
	if (i < 1 || i > L->Length)
	{
		printf("非法下标!\n");
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

//访问函数
Status visit(Status t)
{
	printf("%d ", t);//由于宏定义的特殊性，修改Status值是，访问函数的输出控制符需要相应的修改 
					 /*测试访问失败条件
					 if(t == 2)
					 return ERROR;
					 */
	return OK;
}

//遍历 
Status ListTraverse(SqList L, Status(*visit)(ElemType e))
{
	if (!&L)
	{
		printf("线性链表不存在!\n");
		return ERROR;
	}
	printf("遍历数组:\n");
	int i;
	for (i = 0; i < L.Length; ++i)
	{
		if (!visit(L.Elem[i]))
		{
			printf("\nL.Elem[%d]访问失败！\n", i);
			return ERROR;
		}
	}

	return OK;
}

//获取cur_e的直接前驱
//若cur_e是L的数据元素，且不是第一个，则用pre_e作为他的前驱，否则操作失败,pre_e无定义   
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
		printf("cur_e是第一个元素,没有直接前驱!\n");
		return ERROR;
	}

	if (i == L.Length)
	{
		printf("cur_e不存在\n");
		return ERROR;
	}

	*pre_e = L.Elem[i - 1];

	return OK;
}

//获取cur_e的直接后继 
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
		printf("不存在直接后继！\n");
		return ERROR;
	}

	*next_e = L.Elem[i + 1];
	return OK;
}

//用e返回L中第i个数据元素的值
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

//查找线性链表中第一个满足compare关系的元素 
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

//将所有在线性表Lb中但不在La中的数据元素插入到La中 
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

//已知La，Lb中的数据元素按值非递减排列
//归并la,lb得到新的线性表Lc也满足值非递减 
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

	//归并 
	while (pa <= pa_last && pb <= pb_last)
	{
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}

	//插入剩余元素 
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
	printf("获取到的第四个元素是：%d\n",tmp);
	printf("\n第一个与2满足compare关系的是：%d\n",LocateElem(list, 2, compare));
	PriorElem(list,2,&pre_m);
	printf("%d\n",pre_m);
	NextElem(list,2,&next_m);
	printf("%d\n",next_m);
	GetElem(list,3,&tmp);
	printf("%d\n",tmp);
	//printf("%d\n",next_m);
	//printf("%d\n",pre_m);
	ListDelete(&list,4,&m);
	printf("\n删除的元素是：%d\n",m);
	ListTraverse(list,visit);
	*/

	return 0;
}