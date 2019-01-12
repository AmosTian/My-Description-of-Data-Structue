// ѭ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
ѭ������Ľṹ�͵�����ṹһ��
������β����ָ���ɿ�ָ���Ϊָ��ͷ��㣬��ʹ�����������γ�һ������
����ͷβ��ӵĵ������Ϊѭ�����������ѭ������
*/

typedef struct CLinkNode
{
	ElemType data;
	struct CLinkNode *next;
}CLinkNode,*CLinkList;

//��ʼ��ѭ������
Status InitCLinkList(CLinkList *list)
{
	if (list == NULL)
		return ERROR;

	int data;
	CLinkNode *target = NULL;//Ѱ��β���λ��
	CLinkNode *head_node = NULL;//�洢ͷ���λ��
	
	printf("���������ֵ��0��ʾ������ʼ��:\n");

	while (1)
	{
		scanf_s("%d", &data);

		//�ж��Ƿ�Ϊ��ʼ��������־
		if (data == 0)
			break;

		//�ж�list�Ƿ�Ϊ������
		//��Ϊ�գ�����ͷָ��ָ���ͷ���
		//��Ϊ�գ��ҵ�β��㣬���뵽 β���֮�󣬲�����ָ��ͷ�ڵ�
		if (*list == NULL)
		{
			//����ͷָ��
			CLinkNode *head = (CLinkNode *)malloc(1 * sizeof(CLinkNode));
			if (head == NULL)
			{
				printf("�ڴ����ʧ��!\n");
				exit(OVERFLOW);
			}

			*list = head;
			
			//����ͷ���
			CLinkNode *node = (CLinkNode *)malloc(1 * sizeof(CLinkNode));
			if (node == NULL)
			{
				printf("�ڴ����ʧ��!\n");
				exit(OVERFLOW);
			}

			node->data = data;
			node->next = head;//ͷ���ָ��ͷָ��
			head->next = node;//ͷָ��ָ��ͷ�ڵ�
		}
		else
		{
			//�ҵ�β���λ�ã����뵽β���֮��
			for (target = (*list)->next; target->next != *list; target = target->next);
			head_node = target->next;

			CLinkNode *node = (CLinkNode*)malloc(1 * sizeof(CLinkNode));
			if (!node)
			{
				printf("�ڴ����ʧ��!\n");
				exit(OVERFLOW);
			}


			node->data = data;
			node->next = head_node;

			target->next = node;
		}
	}

	return OK;
}

//���ʺ���
void visit(ElemType e)
{
	printf("%d ",e);
}

//��������
Status TraverseCLinkList(CLinkList list, void(*visit)(ElemType e))
{
	if (list == NULL)
	{
		printf("��������!\n");
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

//��ȡ������
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

//��ָ��λ�ò���ڵ�
Status InsertCLinkList(CLinkList *list, int i, ElemType e)
{
	if (i < 1 || i - 1 > LengthCLinkList(*list))
	{
		printf("����λ�ò��Ϸ�!\n");
		return ERROR;
	}

	int j = 1;
	CLinkNode *target = NULL;

	//Ѱ�Ҳ���λ�õ�ǰһ���ڵ�
	for (target = (*list)->next; j < i-1 && target != (*list); target = target->next,++j);

	CLinkNode *node = (CLinkNode *)malloc(1 * sizeof(CLinkNode));
	if (!node)
	{
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	node->data = e;
	node->next = target->next;
	target->next = node;

	return OK;
}

//ɾ��ָ��λ�õĽڵ�
Status DeleteCLinkList(CLinkList list, int i, ElemType *e)
{
	if (!list)
	{
		printf("��������!\n");
		return ERROR;
	}
	if (i < 0 || i > LengthCLinkList(list))
	{
		printf("����λ�ò��Ϸ�\n");
		return ERROR;
	}

	CLinkNode *target = NULL;
	int j = 1;

	//�ҵ�ɾ���ڵ��ǰһ��λ��
	for (target = list->next; j < i-1 && target != list; target = target->next, ++j);

	CLinkNode *del_node = target->next;
	*e = del_node->data;
	target->next = del_node->next;
	free(del_node);//����ֱ���ͷ�ָ�������нڵ��ָ�룬ֻ���ͷ�ָ��ڵ��ָ��

	return OK;
}

//compare()����
bool compare(ElemType a, ElemType b)
{
	return a ==b;
}

//��ȡ��������e����compare��ϵ�ĵ�һ���ڵ��λ�á�������
Status LocateElem(CLinkList list, int e, bool(*compare)(ElemType a, ElemType b))
{
	if (!list)
	{
		printf("��������!\n");
		return ERROR;
	}

	int i = 0;
	CLinkNode *target = NULL;

	for (target = list->next; target->next != list; target = target->next)
	{
		i++;
		if (compare(e, target->data))
			break;
	}

	if (i == 0)
	{
		printf("%d�������в�����\n",e);
		return ERROR;
	}

	return i;
}

//��ȡ��i���ڵ�Ϊ������
Status LocatePos(CLinkList list, Status i,ElemType *e)
{
	if (!list)
	{
		printf("������������\n");
		return ERROR;
	}

	if (i < 1 || i > LengthCLinkList(list))
	{
		printf("����λ�ò��Ϸ�\n");
		return ERROR;
	}

	int j = 1;
	CLinkNode *target = NULL;

	//Ѱ�ҽڵ�λ��
	for (target = list->next; j < i && target->next != list; target = target->next,j++);

	*e = target->data;

	return OK;
}

int main()
{
	CLinkList list = NULL;

	InitCLinkList(&list);
	printf("��������Ԫ��:\n");
	TraverseCLinkList(list, visit);
	/*
	ElemType data;
	LocatePos(list, 2, &data);
	printf("�ڶ����ڵ��������:%d\n",data);
	
	int data;
	scanf_s("%d",&data);
	printf("%d��λ����:%d\n",data,LocateElem(list,data,compare));
	//printf("������Ϊ:%d\n",LengthCLinkList(list));

	int pos, data;

	printf("�������λ��:\n");
	scanf_s("%d",&pos);
	printf("�����������:\n");
	scanf_s("%d",&data);
	InsertCLinkList(&list, pos, data);

	printf("��������Ԫ��:\n");
	TraverseCLinkList(list, visit);
	
	printf("����ɾ��λ��:\n");
	scanf_s("%d", &pos);
	DeleteCLinkList(list, pos, &data);
	printf("ɾ��Ԫ����:%d\n",data);

	printf("��������Ԫ��:\n");
	TraverseCLinkList(list, visit);
	*/
    return 0;
}

