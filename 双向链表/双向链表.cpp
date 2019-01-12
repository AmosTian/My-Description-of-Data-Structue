#include "stdafx.h"

typedef struct DuLNode
{
	ElemType data;
	struct DuLNode *prior, *next;
}DuLNode,*DuLinkList;

Status InitDuLinkList(DuLinkList *list)
{
	DuLNode *head = (DuLNode *)malloc(1 * sizeof(DuLNode));
	if (!head)
	{
		printf("内存分配失败!\n");
		return ERROR;
	}
	*list = head;

	ElemType data;
	DuLNode *target = head;
	target->prior = NULL;
	target->next = NULL;

	printf("输入链表数据，0表示输入结束\n");
	while (1)
	{
		scanf_s("%d",&data);

		if (data == 0)
			break;

		DuLNode *node = (DuLNode *)malloc(1 * sizeof(DuLNode));

		node->data = data;
		node->next = NULL;
		node->prior = target;
		target->next = node;

		target = node;
	}

	return OK;
}

//访问函数
void visit(ElemType e)
{
	printf("%d", e);
}

//遍历链表
Status TraverseDuLinkList(DuLinkList list, void(*visit)(ElemType e))
{
	if (!list)
	{
		printf("链表不存在!\n");
		exit(OVERFLOW);
	}

	DuLNode *target = list->next;
	for (; target != NULL; target = target->next)
	{
		visit(target->data);
		if(target->next != NULL)
		printf("<-->");
	}
	printf("\n");

	return OK;
}

//长度函数
Status LengthDuLinkList(DuLinkList list)
{
	int len = 0;

	DuLNode *target = list->next;

	while (target)
	{
		len++;
		target = target->next;
	}

	return len;
}

//头插法
Status InsertDuLinkListHead(DuLinkList *list,ElemType e)
{
	DuLNode *node = (DuLNode *)malloc(1 * sizeof(DuLNode));
	node->data = e;
	node->next = (*list)->next;
	node->prior = *list;

	(*list)->next = node;

	return OK;
}

//尾插法
Status InsertDuLinkListTail(DuLinkList *list, ElemType e)
{
	DuLNode *node = (DuLNode *)malloc(1 * sizeof(DuLNode));
	node->data = e;
	node->next = NULL;

	DuLNode* target = (*list)->next;
	while (target->next)
	{
		target = target->next;
	}

	target->next = node;
	node->prior = target;

	return OK;
}

//插入节点
Status InsertDuLinkList(DuLinkList *list, int i, ElemType e)
{
	if (!(*list))
	{
		printf("链表不存在!\n");
		return ERROR;
	}

	if (i < 1 || i > LengthDuLinkList(*list) + 1)
	{
		printf("i不合法\n");
		return ERROR;
	}

	if (i == 1)
	{
		InsertDuLinkListHead(list,e);
		return OK;
	}
	if (i == LengthDuLinkList(*list)+1 || i == LengthDuLinkList(*list))
	{
		InsertDuLinkListTail(list,e);
		return OK;
	}

	if (!(*list))
	{
		printf("链表不存在!\n");
		return ERROR;
	}

	DuLNode *target = (*list)->next;

	int j = 1;

	while (j < i - 1)
	{
		target = target->next;
	}

	DuLNode *node = (DuLNode *)malloc(1 * sizeof(DuLNode));
	if (!node)
	{
		printf("内存分配失败!\n");
		return ERROR;
	}

	node->data = e;
	node->next = target->next;
	node->prior = target;
	target->next = node;

	return OK;
}

//删除节点
Status DeleteDuLinkList(DuLinkList *list, int i , ElemType *e)
{
	if (!(*list))
	{
		printf("链表不存在!\n");
		return ERROR;
	}

	DuLNode *target = (*list)->next;

	int j = 1;
	while (j < i - 1)
	{
		target = target->next;
		j++;
	}

	DuLNode *del_node = target->next;
	*e = del_node->data;
	target->next = del_node->next;
	del_node->next->prior = target;
	free(del_node);

	return OK;
}

bool compare(ElemType a, ElemType b)
{
	return a == b;
}

//获取链表中与e满足compare关系的第一个节点的位置【索引】
Status LocateElem(DuLinkList list, int e, bool(*compare)(ElemType a, ElemType b))
{
	if (!list)
	{
		printf("链表不存在!\n");
		return ERROR;
	}

	int i = 0;
	DuLNode *target = NULL;

	for (target = list->next; target->next != list; target = target->next)
	{
		i++;
		if (compare(e, target->data))
			break;
	}

	if (i == 0)
	{
		printf("%d在链表中不存在\n", e);
		return ERROR;
	}

	return i;
}

//获取第i个节点为的数据
Status LocatePos(DuLinkList list, Status i, ElemType *e)
{
	if (!list)
	{
		printf("线性链表不存在\n");
		return ERROR;
	}

	if (i < 1 || i > LengthDuLinkList(list))
	{
		printf("输入位置不合法\n");
		return ERROR;
	}

	int j = 1;
	DuLNode *target = NULL;

	//寻找节点位置
	for (target = list->next; j < i && target->next != list; target = target->next, j++);

	*e = target->data;

	return OK;
}

int main()
{
	DuLinkList list;
	ElemType data;

	InitDuLinkList(&list);
	printf("遍历链表\n");
	TraverseDuLinkList(list, visit);

	InsertDuLinkList(&list,4, 4);
	printf("遍历链表\n");
	TraverseDuLinkList(list, visit);

	/*
	printf("链表长度是:%d\n", LengthDuLinkList(list));
	LocateElem(list, 2, compare);
	DeleteDuLinkList(&list, 2, &data);
	printf("遍历链表\n");
	TraverseDuLinkList(list, visit);
	*/

	return 0;
}