// 循环队列.cpp : 定义控制台应用程序的入口点。
// 牺牲一个元素的空间，队列头指针在队列尾指针的下一位置上 最为队列满的标志

#include "stdafx.h"

typedef struct
{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

//初始化队列
Status InitQueue(SqQueue *q)
{
	q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if (!q->base)
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}

	q->front = q->rear = 0;

	return OK;
}

//空队列
Status EmptyQueue(SqQueue q)
{
	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

//入队
Status EnQueue(SqQueue *q, QElemType e)
{
	if ((q->rear + 1) % MAXQSIZE == q->front)
	{
		printf("队列满!\n");
		return ERROR;
	}

	q->base[q->rear] = e;
	q->rear = (q->rear + 1) % MAXQSIZE;

	return OK;
}

//出队
Status DeQueue(SqQueue *q, QElemType *e)
{
	if (q->front == q->rear)
		return ERROR;

	*e = q->base[q->front];
	q->front = (q->front + 1) % MAXQSIZE;

	return OK;
}

//访问函数
Status visit(QElemType e)
{
	printf("%d ",e);

	return OK;
}

//遍历
Status Traverse(SqQueue q, Status(*visit)(QElemType e))
{
	if (!&q)
	{
		printf("队列不存在!\n");
		return ERROR;
	}

	QElemType *t = &q.base[q.front];

	while (t != &q.base[q.rear])
	{
		visit(*t);
		t++;
	}

	return OK;
}

//求队列长度
Status QueueLength(SqQueue q)
{
	return (q.rear - q.front + MAXQSIZE) % MAXQSIZE;
}

int main()
{
	int n;
	QElemType data;
	SqQueue q;

	InitQueue(&q);
	if (EmptyQueue(q))
	{
		printf("空队列\n");
	}

	printf("输入队列中元素个数:\n");
	scanf_s("%d",&n);
	printf("输入队列元素\n");
	while (n--)
	{
		scanf_s("%d",&data);
		EnQueue(&q, data);
	}
	printf("遍历队列!\n");
	Traverse(q, visit);
	printf("\n");
	printf("队列长度为:%d\n",QueueLength(q));

/*
	DeQueue(&q, &data);
	printf("删除的队首元素是:%d\n",data);
	printf("遍历队列!\n");
	Traverse(q, visit);
	printf("\n");
	*/
    return 0;
}

