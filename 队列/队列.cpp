// 队列.cpp : 定义控制台应用程序的入口点。
//队列的链式存储结构

#include "stdafx.h"

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front, rear;
}LinkQueue;

//初始化队列
Status InitQueue(LinkQueue *q)
{
	if (!q)
	{
		printf("队列不存在!\n");
		return ERROR;
	}

	q->front = q->rear = (QueuePtr)malloc(1 * sizeof(QNode));

	if (!q->front)
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}

	q->front->next = NULL;

	return OK;
}

//清空队列
Status ClearQueue(LinkQueue *q)
{
	if (!q)
	{
		printf("队列不存在!\n");
		return ERROR;
	}

	QueuePtr p = q->front->next, tmp;

	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
	q->front = q->rear;

	return OK;
}

//销毁队列
Status DestoryQueue(LinkQueue *queue)
{
	if (!queue)
	{
		printf("队列不存在!\n");
		return ERROR;
	}

	while (queue->front != NULL) {
		queue->rear = queue->front->next;
		free(queue->front);
		queue->front = queue->rear;
	}

	return OK;
}

//空队列
Status QueueEmpty(LinkQueue q)
{
	if (!&q)
	{
		printf("空队列!\n");
		return ERROR;
	}

	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

//插入元素e为q的新队尾元素
Status EnQueue(LinkQueue *q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(1 * sizeof(QNode));
	if (!q)
	{
		printf("内存分配失败!\n");
		return ERROR;
	}

	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;

	return OK;
}

//出队
Status DeQueue(LinkQueue *q, QElemType *e)
{
	if (!q)
	{
		printf("队列不存在!\n");
		return ERROR;
	}

	if (QueueEmpty(*q))
	{
		printf("空队列!\n");
		return ERROR;
	}

	QueuePtr p = (*q).front->next;
	*e = p->data;
	(*q).front->next = p->next;
	if ((*q).front == (*q).rear)
	{
		(*q).rear = (*q).front;
	}
	free(p);

	return OK;
}

//队列长度
Status QueueLength(LinkQueue q)
{
	if (!&q)
	{
		printf("不存在!\n");
		return ERROR;
	}

	int len = 0;
	QueuePtr p = q.front->next;

	while (p)
	{
		len++;
		p = p->next;
	}

	return len;
}

//获取队首元素
Status GetHead(LinkQueue q, QElemType *e)
{
	if (!(&q))
	{
		printf("队列不存在!\n");
		return ERROR;
	}

	if (QueueEmpty(q))
	{
		printf("空队列!\n");
		return ERROR;
	}

	*e = q.front->next->data;

	return OK;
}

//访问函数
Status visit(QElemType e)
{
	printf("%d ",e);
	return OK;
}

//遍历队列
Status QueueTraverse(LinkQueue q, Status(*visit)(QElemType e))
{
	if (!(&q))
	{
		printf("队列不存在!\n");
		return ERROR;
	}
	if (QueueEmpty(q))
	{
		printf("队列为空!\n");
		return ERROR;
	}

	QueuePtr p = q.front->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}

	return OK;
}

int main()
{
	LinkQueue que;
	QElemType data;
	int n;

	InitQueue(&que);
	
	printf("输入队列元素数量:\n");
	scanf_s("%d", &n);
	printf("输入队列中元素:\n");
	while (n--)
	{
		scanf_s("%d",&data);
		EnQueue(&que, data);
	}

	printf("遍历队列:\n");
	QueueTraverse(que, visit);
	printf("\n");

	
	/*
	DestoryQueue(&que);

	printf("遍历队列:\n");
	QueueTraverse(que, visit);
	printf("\n");

	DeQueue(&que, &data);
	printf("队首部元素是:%d\n", data);
	printf("遍历队列:\n");
	QueueTraverse(que, visit);
	
	GetHead(que, &data);
	printf("队列首元素是:%d\n",data);
	printf("长度:%d\n", QueueLength(que));
	DeQueue(&que, &data);
	printf("%d\n", que.front->next->next->data);
	*/
    return 0;
}