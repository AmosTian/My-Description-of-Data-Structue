// ˳��ջ������һ���ַ�����Ĵ洢��Ԫ���δ����ջ�׵�ջ��������Ԫ�أ�ͬʱ����ָ��topָ��ջ��Ԫ����˳��ջ�е�Ԫ��
//����ջ���̶�ջ�����Ԫ��������ջ��������Ϊ0�ı�ʾ
/*
struct stack
{
char data[100];
int top;
}s;
*/

#include "stdafx.h"

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

//��ʼ��
Status InitStack(SqStack *s)
{
	s->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!s)
	{
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;

	return OK;
}

//����ջ
Status DestoryStack(SqStack *s)
{
	if (!s)
	{
		printf("ջ������\n");
		return ERROR;
	}

	int len = s->stacksize,i;
	for (i = 0; i < len; ++i)
	{
		free(s->base);
		s->base++;
	}

	s->base = s->top = NULL;
	s->stacksize = 0;
	
	return OK;
}

//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(SqStack s)
{
	if (!&s)
	{
		printf("ջ������!\n");
		return ERROR;
	}
	if (s.top == s.base)
		return TRUE;
	else
		return FALSE;
}

//��ȡջ����
Status StackLength(SqStack s)
{
	if (!&s)
	{
		printf("ջ������!\n");
		return ERROR;
	}
	if (StackEmpty(s))
	{
		return 0;
	}

	SElemType *cur = s.base;
	int count = 0;
	while (cur != s.top)
	{
		count++;
		cur++;
	}

	return count;
}

//���ջ
Status ClearStack(SqStack *s)
{
	if (!s)
	{
		printf("ջ������!\n");
		return ERROR;
	}

	s->top = s->base;

	return OK;
}

//ѹջ
Status Push(SqStack *s,SElemType e)
{
	//�ж�ջ��
	if (s->top - s->base == s->stacksize)
	{
		s->base = (SElemType *)realloc(s->base, (s->stacksize + STACKINCERMENT) * sizeof(SElemType));
		if (!s)
		{
			printf("�ڴ����ʧ��!\n");
			exit(OVERFLOW);
		}

		s->top = s->base + s->stacksize;
		s->stacksize += STACKINCERMENT;
	}

	*(s->top) = e;
	s->top++;

	return OK;
}

//��ջ
Status Pop(SqStack *s, SElemType *e)
{
	if (StackEmpty(*s))
	{
		printf("��ջ\n");
		return ERROR;
	}

	*e = *--s->top;

	return OK;
}

//��ȡջ��Ԫ��
Status GetTop(SqStack s, SElemType *e)
{
	if (s.top == s.base)
	{
		printf("��ջ!\n");
		return ERROR;
	}

	*e = *(s.top - 1);

	return OK;
}

//���ʺ���
Status visit(SElemType e)
{
	printf("%d ",e);

	return OK;
}

//����ջ
Status StackTraverse(SqStack s, Status(*visit)(SElemType e))
{
	if (!&s)
	{
		printf("ջ������!\n");
		return ERROR;
	}

	if (StackEmpty(s))
	{
		printf("ջΪ��!\n");
		return ERROR;
	}
	SElemType *cur = s.base;

	while (cur != s.top)
	{
		visit(*cur);

		cur++;
	}
	printf("\n");

	return OK;
}

int main()
{
	SqStack stack;
	SElemType data;
	int n,i;

	InitStack(&stack);
	printf("����ѹջ����:\n");
	scanf_s("%d", &n);
	printf("����ջ������Ԫ��:\n");
	for (i = 1; i <= n; ++i)
	{
		scanf_s("%d", &data);
		Push(&stack, data);
	}
	printf("����ջ:\n");
	StackTraverse(stack, visit);

	/*
	if (DestoryStack(&stack))
	printf("OK\n");
	printf("����ջ��Ԫ��Ϊ:\n");
	Pop(&stack, &data);
	printf("%d\n",data);
	printf("ջ��Ԫ������Ϊ:%d\n", StackLength(stack));
	GetTop(stack, &data);
	printf("ջ��Ԫ����:%d\n",data);
	*/
    return 0;
}

