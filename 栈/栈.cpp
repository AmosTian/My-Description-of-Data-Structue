// 顺序栈：利用一组地址连续的存储单元依次存放自栈底到栈顶的数据元素，同时附设指针top指向栈顶元素在顺序栈中的元素
//数组栈：固定栈的最大元素数量，栈底用索引为0的表示
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

//初始化
Status InitStack(SqStack *s)
{
	s->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!s)
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}

	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;

	return OK;
}

//销毁栈
Status DestoryStack(SqStack *s)
{
	if (!s)
	{
		printf("栈不存在\n");
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

//判断栈是否为空
Status StackEmpty(SqStack s)
{
	if (!&s)
	{
		printf("栈不存在!\n");
		return ERROR;
	}
	if (s.top == s.base)
		return TRUE;
	else
		return FALSE;
}

//获取栈长度
Status StackLength(SqStack s)
{
	if (!&s)
	{
		printf("栈不存在!\n");
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

//清空栈
Status ClearStack(SqStack *s)
{
	if (!s)
	{
		printf("栈不存在!\n");
		return ERROR;
	}

	s->top = s->base;

	return OK;
}

//压栈
Status Push(SqStack *s,SElemType e)
{
	//判断栈满
	if (s->top - s->base == s->stacksize)
	{
		s->base = (SElemType *)realloc(s->base, (s->stacksize + STACKINCERMENT) * sizeof(SElemType));
		if (!s)
		{
			printf("内存分配失败!\n");
			exit(OVERFLOW);
		}

		s->top = s->base + s->stacksize;
		s->stacksize += STACKINCERMENT;
	}

	*(s->top) = e;
	s->top++;

	return OK;
}

//出栈
Status Pop(SqStack *s, SElemType *e)
{
	if (StackEmpty(*s))
	{
		printf("空栈\n");
		return ERROR;
	}

	*e = *--s->top;

	return OK;
}

//获取栈顶元素
Status GetTop(SqStack s, SElemType *e)
{
	if (s.top == s.base)
	{
		printf("空栈!\n");
		return ERROR;
	}

	*e = *(s.top - 1);

	return OK;
}

//访问函数
Status visit(SElemType e)
{
	printf("%d ",e);

	return OK;
}

//遍历栈
Status StackTraverse(SqStack s, Status(*visit)(SElemType e))
{
	if (!&s)
	{
		printf("栈不存在!\n");
		return ERROR;
	}

	if (StackEmpty(s))
	{
		printf("栈为空!\n");
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
	printf("输入压栈次数:\n");
	scanf_s("%d", &n);
	printf("输入栈中数据元素:\n");
	for (i = 1; i <= n; ++i)
	{
		scanf_s("%d", &data);
		Push(&stack, data);
	}
	printf("遍历栈:\n");
	StackTraverse(stack, visit);

	/*
	if (DestoryStack(&stack))
	printf("OK\n");
	printf("弹出栈顶元素为:\n");
	Pop(&stack, &data);
	printf("%d\n",data);
	printf("栈中元素数量为:%d\n", StackLength(stack));
	GetTop(stack, &data);
	printf("栈顶元素是:%d\n",data);
	*/
    return 0;
}

