// 链式栈.cpp : 定义控制台应用程序的入口点。
//单链表实现栈

#include "stdafx.h"

typedef struct LNode
{
	SElemType data;
	struct LNode *next;
}SNode, *SqStack;

//初始化栈
Status InitStack(SqStack *s)
{
	SNode *head = (SNode *)malloc(1 * sizeof(SNode));
	head->next = NULL;
	if (!head)
	{
		printf("内存分配失败!\n");
		return ERROR;
	}
	*s = head;

	return OK;
}

//清空栈
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

//销毁栈
Status DestoryStack(SqStack *s)
{
	if (!(*s))
	{
		printf("栈不存在!\n");
		return ERROR;
	}

	ClearStack(s);

	free(*s);

	return OK;
}

//获取栈中元素数量
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

//判断空栈
Status EmptyStack(SqStack s)
{
	if (s->next == NULL)
		return TRUE;
	else
		return FALSE;
}

//压栈(头插法)
Status push(SqStack *s, SElemType data)
{
	SNode *node = (SNode *)malloc(1 * sizeof(SNode));

	node->data = data;
	node->next = (*s)->next;
	(*s)->next = node;

	return OK;
}

//弹出栈
Status pop(SqStack *s, SElemType *data)
{
	if (EmptyStack(*s))
	{
		printf("空栈\n");
		return ERROR;
	}

	SNode *p = (SNode *)malloc(1 * sizeof(SNode));

	p = (*s)->next;
	(*s)->next = p->next;
	*data = p->data;
	free(p);

	return OK;
}

//访问函数
Status visit(SElemType e)
{
	printf("%d ",e);

	return OK;
}

//遍历栈
Status TraverseStack(SqStack s,Status (*visit)(SElemType e))
{
	if (!s)
	{
		printf("栈不存在!\n");
		return ERROR;
	}

	if (EmptyStack(s))
	{
		printf("空栈!\n");
		return ERROR;
	}

	SNode *target = s->next;
	for (; target; target = target->next)
	{
		visit(target->data);
	}

	return OK;
}

//返回栈顶元素
Status GetTop(SqStack s,SElemType *e)
{
	if (!s)
	{
		printf("栈不存在!\n");
		return ERROR;
	}

	if (EmptyStack(s))
	{
		printf("空栈\n");
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

	printf("输入栈的元素个数:");
	scanf_s("%d", &n);
	while (n--)
	{
		scanf_s("%d",&data);
		push(&stack, data);
	}
	
	printf("遍历栈\n");
	TraverseStack(stack, visit);

	DestoryStack(&stack);

	/*
	pop(&stack, &data);
	printf("删除的元素是:%d\n",data);
	printf("遍历栈\n");
	TraverseStack(stack, visit);
	GetTop(stack, &data);
	printf("栈顶元素为:%d\n",data);
	//printf("栈元素个数为:%d\n",LengthStack(stack));
	*/

    return 0;
}

