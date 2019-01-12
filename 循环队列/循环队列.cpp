// ѭ������.cpp : �������̨Ӧ�ó������ڵ㡣
// ����һ��Ԫ�صĿռ䣬����ͷָ���ڶ���βָ�����һλ���� ��Ϊ�������ı�־

#include "stdafx.h"

typedef struct
{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

//��ʼ������
Status InitQueue(SqQueue *q)
{
	q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if (!q->base)
	{
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	q->front = q->rear = 0;

	return OK;
}

//�ն���
Status EmptyQueue(SqQueue q)
{
	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

//���
Status EnQueue(SqQueue *q, QElemType e)
{
	if ((q->rear + 1) % MAXQSIZE == q->front)
	{
		printf("������!\n");
		return ERROR;
	}

	q->base[q->rear] = e;
	q->rear = (q->rear + 1) % MAXQSIZE;

	return OK;
}

//����
Status DeQueue(SqQueue *q, QElemType *e)
{
	if (q->front == q->rear)
		return ERROR;

	*e = q->base[q->front];
	q->front = (q->front + 1) % MAXQSIZE;

	return OK;
}

//���ʺ���
Status visit(QElemType e)
{
	printf("%d ",e);

	return OK;
}

//����
Status Traverse(SqQueue q, Status(*visit)(QElemType e))
{
	if (!&q)
	{
		printf("���в�����!\n");
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

//����г���
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
		printf("�ն���\n");
	}

	printf("���������Ԫ�ظ���:\n");
	scanf_s("%d",&n);
	printf("�������Ԫ��\n");
	while (n--)
	{
		scanf_s("%d",&data);
		EnQueue(&q, data);
	}
	printf("��������!\n");
	Traverse(q, visit);
	printf("\n");
	printf("���г���Ϊ:%d\n",QueueLength(q));

/*
	DeQueue(&q, &data);
	printf("ɾ���Ķ���Ԫ����:%d\n",data);
	printf("��������!\n");
	Traverse(q, visit);
	printf("\n");
	*/
    return 0;
}

