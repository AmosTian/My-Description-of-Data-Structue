// 线性链表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList,*Position,*pNode;

//创建节点
Status MakeNode(LinkList *Node, ElemType e)
{
	*Node = (LinkList)malloc(1 * sizeof(LNode));

	if (!Node)
	{
		//内存分配失败！
		exit(OVERFLOW);
	}

	(*Node)->data = e;

	return OK;
}

//删除Node所指向的节点
Status FreeNode(pNode p)
{
	free(p);

	return OK;
}

//初始化线性链表
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(1 * sizeof(LNode));

	if (!(*L))
		return ERROR;
	return OK;
}

//重置线性链表
Status ClearList(LinkList *L,ElemType e)
{
	if (!(*L))
	{
		printf("线性链表为空！");
		return ERROR;
	}

	LinkList p, q;
	p = *L;

	while (p)
	{
		p->data = e;
		p = p->next;
	}

	return OK;
}

//返回头结点指针
Position GetHead(LinkList L)
{
	if (!L)
	{
		printf("链表不存在!\n");
		return ERROR;
	}
	
	return L->next;
}

//返回尾结点位置
Position GetLast(LinkList L)
{
	if (!L)
	{
		printf("链表不存在!\n");
		return ERROR;
	}

	Position p = NULL;
	for (p = L->next; p && p->next; p = p->next);

	return p;
}

//在h所指向的头结点之前插入s所指向的节点
Status InsFirst(LinkList *L, pNode s)
{
	Position Head = GetHead(*L);

	s->next = Head;
	
	(*L)->next = s;
	/*1 10 2 3
	s->next = Head->next;
	Head->next = s;*/
	
	return OK;
}

//删除h指向的头结点，节点位置返回到q指针
Status DelFirst(LinkList *L, pNode *q)
{
	Position Head = GetHead(*L);

	(*L)->next = Head->next;
	*q = Head;
	pNode p = (pNode)malloc(1 * sizeof(LNode));
	*p = *Head;
	FreeNode(p);

	return OK;
}

//将指针s所指的一串节点链接在L的最后
Status Append(LinkList *L, pNode s)
{
	Position Tail = GetLast(*L);

	Tail->next = s->next;

	return OK;
}

//删除尾节点,并以q返回
Status Remove(LinkList *L, LNode *q)
{
	if (!L)
	{
		printf("链表不存在!\n");
		return ERROR;
	}

	Position Tail = GetLast(*L);
	pNode p = *L;

	while (p && p->next != Tail)
	{
		p = p->next;
	}

	p->next = NULL;
	*q = *Tail;
	FreeNode(Tail);

	return OK;
}

//已知p指向链表中的一个节点，将s所指向的节点插入在p所指节点之前
Status InsBefore(LinkList *L, pNode p, pNode s)
{
	pNode q = (*L)->next;
	
	while (q && q->next != p)
	{
		q = q->next;
	}
	s = q->next;
	q->next = s;

	return OK;
}

//已知P指向链表中的一个节点，将s指向的节点插入在所指节点之后
Status InsAfter(LinkList *L, pNode p, pNode s)
{
	s->next = p->next;
	p->next = s;

	return OK;
}

//销毁线性链表
Status DestoryList(LinkList *L)
{
	if (!(*L))
		return ERROR;

	LinkList p, q;

	p = (*L)->next;

	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}

	(*L)->next = NULL;

	return OK;
}

//逆位序输入n个元素的值，建立带头节点的单链线性表（带头结点）
Status CreateList_n(LinkList *L, int n)
{
	int i;
	LinkList p;

	*L = (LinkList)malloc( 1 * sizeof(LNode));
	if (!L)
	{
		printf("内存分配失败！\n");
		exit(OVERFLOW);
	}
	(*L)->next = NULL;

	printf("输入链表数据：\n");
	while(n--)
	{
		p = (LinkList)malloc(1 * sizeof(LNode));
		if (!p)
		{
			printf("内存分配失败！\n");
			exit(OVERFLOW);
		}
		scanf_s("%d",&p->data);

		p->next = (*L)->next;
		(*L)->next = p;
	}

	return OK;
}

//正位序创建线性单链表(带头结点)
Status CreateList_p(LinkList *L, int n)
{
	//L是链表的头指针
	LinkList p = NULL, q = NULL;
	InitList(L);
	if (!L)
	{
		exit(OVERFLOW);
	}
	(*L)->next = NULL;
	q = *L;//指向当前节点
	ElemType e;
	for (int i = n; i>0; i--)
	{
		scanf_s("%d",&e);
		MakeNode(&p, e);
		
		q->next = p;//若变为q = p则为无头结点的链表
		q = q->next;
	}
	p->next = NULL;

	return OK;
}

//返回链表长度
int ListLength(LinkList L)
{
	int sum = 0;

	LinkList p = L->next;
	while (p)
	{
		sum++;
		p = p->next;
	}

	return sum;
}

//获取第i个节点数字的值，赋给e
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L;
	int j = 0;

	while (p && j < i)
	{
		p = p->next;
		j++;
	}

	if (!p || j > i)
		return ERROR;

	*e = p->data;

	return OK;
}

//单链表插入
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList p = *L;
	int j = 0;
	while (p && j < i - 1)
	{
		p = p->next;
		j++;
	}

	if (!p || j > i - 1)
		return  ERROR;
	LinkList s = (LinkList)malloc(1 * sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}

//单链表删除
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList p = *L;
	int j = 0;

	while (p->next && j < i - 1)
	{
		p = p->next;
		++j;
	}

	if (!(p->next) || j > i - 1)
		return ERROR;

	LinkList q = (LinkList)malloc(1 * sizeof(LNode));
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);

	return OK;
}

//用e更新节点所指向的节点的数值,一直p是线性链表中的一个结点
Status SetCurElem(LNode *p, ElemType e)
{
	p->data = e;

	return OK;
}

//大于等于关系
Status compare(ElemType a, ElemType b)
{
	if (a >= b)
		return OK;
	else
		return ERROR;
}

//返回链表中L中第一个与e满足compare关系的元素的位置
Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType a, ElemType b))
{
	Position  p = L->next;

	while (p)
	{
		if (compare(p->data, e))
			break;
		p = p->next;
	}

	if (p == NULL)
		return NULL;

	return p;
}

//返回 P指向的链表中第i个位置的节点，并返回OK,如果i值不合法，返回ERROR
Status LocatePos(LinkList L, int i, LNode *p)
{
	if (i >= ListLength(L) || i == 0)
	{
		printf("超出合理返回！\n");
		return ERROR;
	}

	int j = 0;

	LNode* q = L->next;
	while (j < i)
	{
		q = q->next;
		j++;
	}

	*p = *q;

	return OK;
}

//已知p指向线性表中的一个结点，返回前驱结点
Position PriorPos(LinkList L, pNode p)
{
	Position Head = GetHead(L);
	if (p == Head)
	{
		printf("没有前驱！\n");
		return NULL;
	}
	pNode q = Head;

	while (q->next != p)
	{
		q = q->next;
	}

	return q;
}

//已知p指向链表的一个节点，返回p所指向的直接后继的位置
Position NextPos(LinkList L, pNode p)
{
	Position Tail = GetLast(L);

	if (p == Tail)
	{
		printf("直接后继不存在!\n");
		return NULL;
	}

	return p->next;
}

//判断数组是否为空
Status ListEmpty(LinkList L)
{
	if (ListLength(L) == 0)
	{
		return OK;
	}
	return ERROR;
}

//访问函数
Status visit(ElemType e)
{
	printf("%d ",e);

	return OK;
}

//遍历链表,访问visit函数
Status ListTraverse(LinkList L,Status(*visit)(ElemType e))
{
	if (!L)
	{
		printf("链表不存在!\n");
		return ERROR;
	}
	if (ListEmpty(L))
	{
		printf("空链表！\n");
		return ERROR;
	}

	LinkList p = L->next;

	while (p)
	{
		if (!visit(p->data))
		{
			return ERROR;
		}
		p = p->next;
	}

	printf("\n");
	return OK;
}

//输出某个确定节点的值
Status ShowData(LinkList L,int i)
{
	if (i <= 0)
		return FALSE;
	int j;

	for (j = 0; j < i; ++j)
	{
		L = L->next;
	}

	printf("%d ",L->data);
	return OK;
}

//两个链表去重合成
void MergeList(LinkList *La, LinkList *Lb, LinkList *Lc)
{
	//已知单链线性表La,Lb的元素按值非递减的顺序排列
	//归并La和Lb得到新的单链线性表Lc,Lc的元素也按照值递减的顺序排列
	LinkList pa = (*La)->next;
	LinkList pb = (*Lb)->next;
	Lc = La;
	LinkList pc = *La;

	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pc->next; 
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	pc->next = pa ? pa : pb;
	free(Lb);
}

int main()
{
	LinkList List = NULL;
	int i,m,len;
/*
	LinkList list = NULL;

	CreateList_n(&list, 3);
	printf("逆序输出链表：\n");
	for(i = 0;i < 3;++i)
		ShowData(list, i+1);
*/
	printf("输入链表长度\n");
	scanf_s("%d",&len);
	printf("输入线性链表的值：\n");
	CreateList_p(&List,len);
	
	printf("遍历链表：\n");
	ListTraverse(List,visit);

	
/*
	Position next = NextPos(List,GetHead(List));
	printf("首节点的直接后继是:\n");
	printf("%d\n",next->data);

	Position pre = PriorPos(List, GetLast(List));
	printf("尾结点的前驱是:\n");
	printf("%d\n",pre->data);

	LNode tail;
	Remove(&List, &tail);
	printf("删除的元素是:%d",tail.data);
	printf("\n");

	printf("遍历链表：\n");
	ListTraverse(List, visit);

	LinkList s = NULL;
	printf("输入新增链长度:\n");
	scanf_s("%d",&len);
	printf("新增的链是：\n");
	CreateList_p(&s, len);
	Append(&List, s);

	printf("遍历链表：\n");
	ListTraverse(List, visit);

	LNode anew;
	anew.data = 10;
	anew.next = NULL;

	InsFirst(&List, &anew);
	printf("遍历链表：\n");
	ListTraverse(List, visit);
	pNode del;
	DelFirst(&List, &del);
	printf("遍历链表：\n");
	ListTraverse(List, visit);

	Position tail = GetLast(List);
	printf("尾节点的值为:%d\n",tail->data);
	
	LNode p;
	LocatePos(List, 2, &p);
	printf("第2位数据是：\n%d",p.data);

	ElemType pos_data;
	printf("输入判断数据：\n");
	scanf_s("%d", &pos_data);
	Position pos = LocateElem(List, pos_data, compare);
	if (pos)
		printf("%d\n", pos->data);
	else
		printf("数据不存在\n");

	printf("顺序输出链表：\n");
	for (i = 0; i < len; ++i)
		ShowData(List, i + 1);
	printf("\n链表长度：%d",ListLength(List));
	ClearList(&List, 0);
	printf("\n清空数组：\n");
	for (i = 0; i < 3; ++i)
		ShowData(List, i + 1);

	ListDelete(&List, 2, &m);
	printf("\n删除的元素是：%d\n",m);
	printf("删除后链表：\n");
	for (i = 0; i < 2; ++i)
		ShowData(List, i + 1);
	GetElem(List,2,&m);
	printf("%d\n",m);
	ListInsert(&List, 2, 2);
	printf("\n插入后链表：\n");
	for (i = 0; i < 4; ++i)
		ShowData(List, i + 1);
*/

	return 0;
}