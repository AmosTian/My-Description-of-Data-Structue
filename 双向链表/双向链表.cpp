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
		printf("�ڴ����ʧ��!\n");
		return ERROR;
	}
	*list = head;

	ElemType data;
	DuLNode *target = head;
	target->prior = NULL;
	target->next = NULL;

	printf("�����������ݣ�0��ʾ�������\n");
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

//���ʺ���
void visit(ElemType e)
{
	printf("%d", e);
}

//��������
Status TraverseDuLinkList(DuLinkList list, void(*visit)(ElemType e))
{
	if (!list)
	{
		printf("��������!\n");
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

//���Ⱥ���
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

//ͷ�巨
Status InsertDuLinkListHead(DuLinkList *list,ElemType e)
{
	DuLNode *node = (DuLNode *)malloc(1 * sizeof(DuLNode));
	node->data = e;
	node->next = (*list)->next;
	node->prior = *list;

	(*list)->next = node;

	return OK;
}

//β�巨
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

//����ڵ�
Status InsertDuLinkList(DuLinkList *list, int i, ElemType e)
{
	if (!(*list))
	{
		printf("��������!\n");
		return ERROR;
	}

	if (i < 1 || i > LengthDuLinkList(*list) + 1)
	{
		printf("i���Ϸ�\n");
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
		printf("��������!\n");
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
		printf("�ڴ����ʧ��!\n");
		return ERROR;
	}

	node->data = e;
	node->next = target->next;
	node->prior = target;
	target->next = node;

	return OK;
}

//ɾ���ڵ�
Status DeleteDuLinkList(DuLinkList *list, int i , ElemType *e)
{
	if (!(*list))
	{
		printf("��������!\n");
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

//��ȡ��������e����compare��ϵ�ĵ�һ���ڵ��λ�á�������
Status LocateElem(DuLinkList list, int e, bool(*compare)(ElemType a, ElemType b))
{
	if (!list)
	{
		printf("��������!\n");
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
		printf("%d�������в�����\n", e);
		return ERROR;
	}

	return i;
}

//��ȡ��i���ڵ�Ϊ������
Status LocatePos(DuLinkList list, Status i, ElemType *e)
{
	if (!list)
	{
		printf("������������\n");
		return ERROR;
	}

	if (i < 1 || i > LengthDuLinkList(list))
	{
		printf("����λ�ò��Ϸ�\n");
		return ERROR;
	}

	int j = 1;
	DuLNode *target = NULL;

	//Ѱ�ҽڵ�λ��
	for (target = list->next; j < i && target->next != list; target = target->next, j++);

	*e = target->data;

	return OK;
}

int main()
{
	DuLinkList list;
	ElemType data;

	InitDuLinkList(&list);
	printf("��������\n");
	TraverseDuLinkList(list, visit);

	InsertDuLinkList(&list,4, 4);
	printf("��������\n");
	TraverseDuLinkList(list, visit);

	/*
	printf("��������:%d\n", LengthDuLinkList(list));
	LocateElem(list, 2, compare);
	DeleteDuLinkList(&list, 2, &data);
	printf("��������\n");
	TraverseDuLinkList(list, visit);
	*/

	return 0;
}