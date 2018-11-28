// ��̬����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

# define MAXSIZE 1000 //�������󳤶�

typedef struct
{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];

//��һά����space����������һ����������space[0].cur��Ϊͷָ��
//"0"��ʾ��ָ��
int InitSpace(SLinkList space)
{
	int i;

	for (i = 0; i < MAXSIZE - 1; ++i)
		space[i].cur = i + 1;
	space[MAXSIZE - 1].cur = 0;
}

//�ӱ���������ȡ��һ�����нڵ㣬�����±�
int Malloc(SLinkList space)
{
	int i = space[0].cur;
	if (space[0].cur)
	{
		space[0].cur = space[i].cur;
	}

	return i;
}

//���±�Ϊk�Ŀ��нڵ���յ�����������
void Free(SLinkList space,int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

//������ �ĳ���
int ListLength(SLinkList space)
{
	int amount = 0,i = 0;

	while (space[i].cur)
	{
		i = space[i].cur;
		++amount;
	}

	return amount;
}

//����
Status ListInsert(SLinkList L, int i, ElemType e)
{
	int j,k,l;
	k = MAXSIZE - 1;//L[k].cur = 1
	
	if (i < 1 || i > ListLength(L) + 1)
		return ERROR;

	j = Malloc(L);

	if (j)
	{
		L[j].data = e;
		for (l = 1; l <= i - 1; ++l)
		{
			k = L[k].cur;//1->i-1
		}

		L[j].cur = L[k].cur;
		L[k].cur = j;

		return OK;
	}
	else
		return ERROR;
}

//ɾ������ֵ
Status ListDelete(SLinkList L, int i, ElemType *e)
{
	int j, k;

	if (i < 1 || i > ListLength(L))
		return ERROR;

	k = MAXSIZE - 1;
	for (j = 1; j <= i - 1; ++j)
	{
		k = L[k].cur;//0->i-1
	}
	j = L[k].cur;
	L[k].cur = L[j].cur;
	*e = L[j].data;
	Free(L, j);

	return OK;
}

//�������
void ListPrint(SLinkList L)
{
	int i = L[MAXSIZE - 1].cur;//ָ���һ��
	
	while (i != 0)
	{
		printf("%d ", L[i].data);
		i = L[i].cur;
	}
	printf("\n");
}

//����Ԫ��e��һ�γ�����L�е�λ��
int LocateElem(SLinkList L, ElemType e)
{
	int i = L[0].cur;

	while (i && L[i].data != e)
	{
		i = L[i].cur;
	}

	return i;
}

void difference(SLinkList L, int *S)
{
	InitSpace(L);
	*S = Malloc(L);//Sָ���������ͷ�ڵ�
	int *r = S;//βָ�룺ָ������β��
	int m, n,i,j,b,k;

	scanf_s("%d%d",&m,&n);//m��n�ֱ��ʾ�������ϵ�����
	//�����һ�����ϵ�Ԫ��
	for (j = 1; j <= m; ++j)
	{
		i = Malloc(L);//����ڵ�
		scanf_s("%d",L[i].data);
		L[*r].cur = i;//��i���ӵ�����
		*r = i;//��βָ��ָ��i
	}

	L[*r].cur = 0;//β����Ϊ��

	for (j = 1; j <= n; ++j)//����ڶ������ϵ�n��Ԫ��
	{
		scanf_s("%d", &b);
		int *p = S;//pָ��ͷָ�룻ֻ��Ϊ�˴���ʱ��ʹ�ã���kͬ��
		k = L[*S].cur;//k��ͷ��㿪ʼ����
		while (k != L[*r].cur && L[*S].data != b)//����������δ����ڵ�β����Ԫ���Ƿ������������
		{
			*p = k;
			k = L[k].cur;
		}

		//���������������У�����
		if (k == L[*r].cur)
		{
			i = Malloc(L);
			L[i].data = b;
			L[i].cur = L[*r].cur;
			L[*r].cur = i;
		}
		else//�����ڣ�����Ԫ��ɾ��
		{
			L[*p].cur = L[k].cur;
			Free(L, k);
			if (*r == k)
				r = p;//��ɾ������r��ָ�ڵ㣬�����޸�βָ��
		}
	}
}

int main()
{
	SLinkList list;
	ElemType m;

	InitSpace(list);
	ListPrint(list);
	int i;
	for (i = 0; i <= 3; ++i)
	{
		ListInsert(list,i,i*10);
	}
	ListPrint(list);

	printf("%d\n",LocateElem(list,20));
	for (i = 1; i <= 3; ++i)
	{
		ListDelete(list, 1, &m);
		printf("ɾ��Ԫ�أ�%d\n",m);
	}

    return 0;
}

