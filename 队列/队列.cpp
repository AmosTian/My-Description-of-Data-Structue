// ����.cpp : �������̨Ӧ�ó������ڵ㡣
//���е���ʽ�洢�ṹ

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

//��ʼ������
Status InitQueue(LinkQueue *q)
{
	if (!q)
	{
		printf("���в�����!\n");
		return ERROR;
	}

	q->front = q->rear = (QueuePtr)malloc(1 * sizeof(QNode));

	if (!q->front)
	{
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	q->front->next = NULL;

	return OK;
}

//��ն���
Status ClearQueue(LinkQueue *q)
{
	if (!q)
	{
		printf("���в�����!\n");
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

//���ٶ���
Status DestoryQueue(LinkQueue *queue)
{
	if (!queue)
	{
		printf("���в�����!\n");
		return ERROR;
	}

	while (queue->front != NULL) {
		queue->rear = queue->front->next;
		free(queue->front);
		queue->front = queue->rear;
	}

	return OK;
}

//�ն���
Status QueueEmpty(LinkQueue q)
{
	if (!&q)
	{
		printf("�ն���!\n");
		return ERROR;
	}

	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

//����Ԫ��eΪq���¶�βԪ��
Status EnQueue(LinkQueue *q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(1 * sizeof(QNode));
	if (!q)
	{
		printf("�ڴ����ʧ��!\n");
		return ERROR;
	}

	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;

	return OK;
}

//����
Status DeQueue(LinkQueue *q, QElemType *e)
{
	if (!q)
	{
		printf("���в�����!\n");
		return ERROR;
	}

	if (QueueEmpty(*q))
	{
		printf("�ն���!\n");
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

//���г���
Status QueueLength(LinkQueue q)
{
	if (!&q)
	{
		printf("������!\n");
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

//��ȡ����Ԫ��
Status GetHead(LinkQueue q, QElemType *e)
{
	if (!(&q))
	{
		printf("���в�����!\n");
		return ERROR;
	}

	if (QueueEmpty(q))
	{
		printf("�ն���!\n");
		return ERROR;
	}

	*e = q.front->next->data;

	return OK;
}

//���ʺ���
Status visit(QElemType e)
{
	printf("%d ",e);
	return OK;
}

//��������
Status QueueTraverse(LinkQueue q, Status(*visit)(QElemType e))
{
	if (!(&q))
	{
		printf("���в�����!\n");
		return ERROR;
	}
	if (QueueEmpty(q))
	{
		printf("����Ϊ��!\n");
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
	
	printf("�������Ԫ������:\n");
	scanf_s("%d", &n);
	printf("���������Ԫ��:\n");
	while (n--)
	{
		scanf_s("%d",&data);
		EnQueue(&que, data);
	}

	printf("��������:\n");
	QueueTraverse(que, visit);
	printf("\n");

	
	/*
	DestoryQueue(&que);

	printf("��������:\n");
	QueueTraverse(que, visit);
	printf("\n");

	DeQueue(&que, &data);
	printf("���ײ�Ԫ����:%d\n", data);
	printf("��������:\n");
	QueueTraverse(que, visit);
	
	GetHead(que, &data);
	printf("������Ԫ����:%d\n",data);
	printf("����:%d\n", QueueLength(que));
	DeQueue(&que, &data);
	printf("%d\n", que.front->next->next->data);
	*/
    return 0;
}