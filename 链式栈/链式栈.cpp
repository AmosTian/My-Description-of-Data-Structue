// ��ʽջ.cpp : �������̨Ӧ�ó������ڵ㡣
//������ʵ��ջ

#include "stdafx.h"

typedef struct LNode
{
	SElemType data;
	struct LNode *next;
}SNode, *SqStack;

//��ʼ��ջ
Status InitStack(SqStack *s)
{
	SNode *head = (SNode *)malloc(1 * sizeof(SNode));
	head->next = NULL;
	if (!head)
	{
		printf("�ڴ����ʧ��!\n");
		return ERROR;
	}
	*s = head;

	return OK;
}

//���ջ
Status ClearStack(SqStack *s)
{
	SNode *p, *q;

	p = (*s)->next;

	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}

	return OK;
}

//����ջ
Status DestoryStack(SqStack *s)
{
	if (!(*s))
	{
		printf("ջ������!\n");
		return ERROR;
	}

	ClearStack(s);

	free(*s);

	return OK;
}

//��ȡջ��Ԫ������
Status LengthStack(SqStack s)
{
	int len = 0;

	SNode *target = s->next;

	while (target)
	{
		len++;
		target = target->next;
	}

	return len;
}

//�жϿ�ջ
Status EmptyStack(SqStack s)
{
	if (s->next == NULL)
		return TRUE;
	else
		return FALSE;
}

//ѹջ(ͷ�巨)
Status push(SqStack *s, SElemType data)
{
	SNode *node = (SNode *)malloc(1 * sizeof(SNode));

	node->data = data;
	node->next = (*s)->next;
	(*s)->next = node;

	return OK;
}

//����ջ
Status pop(SqStack *s, SElemType *data)
{
	if (EmptyStack(*s))
	{
		printf("��ջ\n");
		return ERROR;
	}

	SNode *p = (SNode *)malloc(1 * sizeof(SNode));

	p = (*s)->next;
	(*s)->next = p->next;
	*data = p->data;
	free(p);

	return OK;
}

//���ʺ���
Status visit(SElemType e)
{
	printf("%d ",e);

	return OK;
}

//����ջ
Status TraverseStack(SqStack s,Status (*visit)(SElemType e))
{
	if (!s)
	{
		printf("ջ������!\n");
		return ERROR;
	}

	if (EmptyStack(s))
	{
		printf("��ջ!\n");
		return ERROR;
	}

	SNode *target = s->next;
	for (; target; target = target->next)
	{
		visit(target->data);
	}

	return OK;
}

//����ջ��Ԫ��
Status GetTop(SqStack s,SElemType *e)
{
	if (!s)
	{
		printf("ջ������!\n");
		return ERROR;
	}

	if (EmptyStack(s))
	{
		printf("��ջ\n");
		return ERROR;
	}

	*e = s->next->data;

	return OK;
}

int main()
{
	SqStack stack;
	int n;
	SElemType data;

	InitStack(&stack);

	printf("����ջ��Ԫ�ظ���:");
	scanf_s("%d", &n);
	while (n--)
	{
		scanf_s("%d",&data);
		push(&stack, data);
	}
	
	printf("����ջ\n");
	TraverseStack(stack, visit);

	DestoryStack(&stack);

	/*
	pop(&stack, &data);
	printf("ɾ����Ԫ����:%d\n",data);
	printf("����ջ\n");
	TraverseStack(stack, visit);
	GetTop(stack, &data);
	printf("ջ��Ԫ��Ϊ:%d\n",data);
	//printf("ջԪ�ظ���Ϊ:%d\n",LengthStack(stack));
	*/

    return 0;
}

