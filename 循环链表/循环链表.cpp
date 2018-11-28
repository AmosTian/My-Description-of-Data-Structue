// ѭ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

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
	for (target = (*list)->next; j == i-1 && target != (*list); target = target->next,++j);

	CLinkNode *node = (CLinkNode *)malloc(1 * sizeof(CLinkNode));



	return OK;
}


//ɾ��ָ��λ�õĽڵ�


int main()
{
	CLinkList list = NULL;

	InitCLinkList(&list);
	printf("��������Ԫ��:\n");
	TraverseCLinkList(list, visit);
	//printf("������Ϊ:%d\n",LengthCLinkList(list));

	int pos, data;

	printf("�������λ��:\n");
	scanf_s("%d",&pos);
	printf("�����������:\n");
	scanf_s("%d",&data);
	InsertCLinkList(&list, pos, data);

    return 0;
}

