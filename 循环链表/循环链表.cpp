// 循环链表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef struct CLinkNode
{
	ElemType data;
	struct CLinkNode *next;
}CLinkNode,*CLinkList;

//初始化循环链表
Status InitCLinkList(CLinkList *list)
{
	if (list == NULL)
		return ERROR;

	int data;
	CLinkNode *target = NULL;//寻找尾结点位置
	CLinkNode *head_node = NULL;//存储头结点位置
	
	printf("输入链表的值，0表示结束初始化:\n");

	while (1)
	{
		scanf_s("%d", &data);

		//判断是否为初始化结束标志
		if (data == 0)
			break;

		//判断list是否为空链表
		//若为空，创建头指针指向的头结点
		//不为空，找到尾结点，插入到 尾结点之后，并将其指向头节点
		if (*list == NULL)
		{
			//创建头指针
			CLinkNode *head = (CLinkNode *)malloc(1 * sizeof(CLinkNode));
			if (head == NULL)
			{
				printf("内存分配失败!\n");
				exit(OVERFLOW);
			}

			*list = head;
			
			//创建头结点
			CLinkNode *node = (CLinkNode *)malloc(1 * sizeof(CLinkNode));
			if (node == NULL)
			{
				printf("内存分配失败!\n");
				exit(OVERFLOW);
			}

			node->data = data;
			node->next = head;//头结点指向头指针
			head->next = node;//头指针指向头节点
		}
		else
		{
			//找到尾结点位置，插入到尾结点之后
			for (target = (*list)->next; target->next != *list; target = target->next);
			head_node = target->next;

			CLinkNode *node = (CLinkNode*)malloc(1 * sizeof(CLinkNode));
			if (!node)
			{
				printf("内存分配失败!\n");
				exit(OVERFLOW);
			}


			node->data = data;
			node->next = head_node;

			target->next = node;
		}
	}

	return OK;
}

//访问函数
void visit(ElemType e)
{
	printf("%d ",e);
}

//遍历链表
Status TraverseCLinkList(CLinkList list, void(*visit)(ElemType e))
{
	if (list == NULL)
	{
		printf("链表不存在!\n");
		exit(OVERFLOW);
	}

	CLinkNode *target = NULL;
	for (target = list->next; target->next != list; target = target->next)
	{
		visit(target->data);
	}
	visit(target->data);
	printf("\n");

	return OK;
}

//获取链表长度
Status LengthCLinkList(CLinkList list)
{
	int len = 0;

	CLinkNode *target = NULL;

	for (target = list->next; target != list; target = target->next)
	{
		len++;
	}

	return len;
}

//在指定位置插入节点
Status InsertCLinkList(CLinkList *list, int i, ElemType e)
{
	if (i < 1 || i - 1 > LengthCLinkList(*list))
	{
		printf("输入位置不合法!\n");
		return ERROR;
	}

	int j = 1;
	CLinkNode *target = NULL;

	//寻找插入位置的前一个节点
	for (target = (*list)->next; j == i-1 && target != (*list); target = target->next,++j);

	CLinkNode *node = (CLinkNode *)malloc(1 * sizeof(CLinkNode));



	return OK;
}


//删除指定位置的节点


int main()
{
	CLinkList list = NULL;

	InitCLinkList(&list);
	printf("遍历链表元素:\n");
	TraverseCLinkList(list, visit);
	//printf("链表长度为:%d\n",LengthCLinkList(list));

	int pos, data;

	printf("输入插入位置:\n");
	scanf_s("%d",&pos);
	printf("输入插入数据:\n");
	scanf_s("%d",&data);
	InsertCLinkList(&list, pos, data);

    return 0;
}

