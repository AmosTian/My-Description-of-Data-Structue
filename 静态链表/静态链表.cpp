// 静态链表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

# define MAXSIZE 1000 //链表的最大长度

typedef struct
{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];

//将一维数组space各分量链成一个备用链表，space[0].cur作为头指针
//"0"表示空指针
int InitSpace(SLinkList space)
{
	int i;

	for (i = 0; i < MAXSIZE - 1; ++i)
		space[i].cur = i + 1;
	space[MAXSIZE - 1].cur = 0;
}

//从备用链表中取第一个空闲节点，返回下标
int Malloc(SLinkList space)
{
	int i = space[0].cur;
	if (space[0].cur)
	{
		space[0].cur = space[i].cur;
	}

	return i;
}

//将下标为k的空闲节点回收到备用链表中
void Free(SLinkList space,int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

//求链表 的长度
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

//插入
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

//删除并赋值
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

//遍历输出
void ListPrint(SLinkList L)
{
	int i = L[MAXSIZE - 1].cur;//指向第一个
	
	while (i != 0)
	{
		printf("%d ", L[i].data);
		i = L[i].cur;
	}
	printf("\n");
}

//查找元素e第一次出现在L中的位置
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
	*S = Malloc(L);//S指向结果链表的头节点
	int *r = S;//尾指针：指向链表尾部
	int m, n,i,j,b,k;

	scanf_s("%d%d",&m,&n);//m，n分别表示两个集合的数量
	//输入第一个集合的元素
	for (j = 1; j <= m; ++j)
	{
		i = Malloc(L);//分配节点
		scanf_s("%d",L[i].data);
		L[*r].cur = i;//将i连接到链表
		*r = i;//将尾指针指向i
	}

	L[*r].cur = 0;//尾部设为空

	for (j = 1; j <= n; ++j)//输入第二个集合的n个元素
	{
		scanf_s("%d", &b);
		int *p = S;//p指向头指针；只是为了存在时候使用，与k同步
		k = L[*S].cur;//k从头结点开始遍历
		while (k != L[*r].cur && L[*S].data != b)//遍历条件：未到达节点尾部；元素是否存在于链表中
		{
			*p = k;
			k = L[k].cur;
		}

		//若不存在与链表中，插入
		if (k == L[*r].cur)
		{
			i = Malloc(L);
			L[i].data = b;
			L[i].cur = L[*r].cur;
			L[*r].cur = i;
		}
		else//若存在，将该元素删除
		{
			L[*p].cur = L[k].cur;
			Free(L, k);
			if (*r == k)
				r = p;//若删除的是r所指节点，则需修改尾指针
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
		printf("删除元素：%d\n",m);
	}

    return 0;
}

