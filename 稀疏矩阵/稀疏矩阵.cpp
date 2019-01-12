// ϡ�����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

typedef struct
{
	int i, j;
	ElemType e;
}Triple;

typedef struct
{
	Triple data[MAXSIZE];
	int mu, nu, tu;//��������������������Ԫ�ظ���
}TSMatrix;

Status CreateSMatrix(TSMatrix *m)
{
	m = (TSMatrix *)malloc(1*sizeof(TSMatrix));

	if (!m)
	{
		printf("�ڴ����ʧ��!\n");
		return TRUE;
	}

	m->mu = 0;
	m->nu = 0;
	m->tu = 0;

	return OK;
}

//���پ���
Status DestorySMatrix(TSMatrix *m)
{
	if (!m)
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	m->mu = 0;
	m->nu = 0;
	m->tu = 0;

	return OK;
}

//��������ֵ
Status InputM(TSMatrix *m)
{
	if (!m)
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	int c;

	printf("������������������������Ԫ�ظ���:\n");

	scanf_s("%d %d %d", &m->mu,&m->nu,&m->tu);

	printf("����������Ԫ�ص�ֵ:\n");

	for (c = 1; c <= m->tu; c++)

	{

		scanf_s("%d", &m->data[c].i);

		scanf_s("%d", &m->data[c].j);

		scanf_s("%d", &m->data[c].e);

	}

	return OK;
}

//��ӡ����
Status PrintM(TSMatrix m)
{
	if (!(&m))
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	printf("�������:\n");

	int i, j;

	int t = 1;
	for (i = 1; i <= m.mu; ++i)
	{
		for (j = 1; j <= m.nu; ++j)
		{
			//����Ԫ��
			if (m.data[t].i == i && m.data[t].j == j)
				printf("%d ",m.data[t++].e);
			//��Ԫ��
			else
				printf("0 ");
		}
		printf("\n");
	}

	return OK;
}

//���ƾ���
Status CopySMatrix(TSMatrix m, TSMatrix *t)
{
	if (!&m)
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	t->nu = m.nu;
	t->mu = m.mu;
	t->tu = m.tu;

	int i;
	for (i = 1; i <= m.tu; ++i)
	{
		t->data[i].i = m.data[i].i;
		t->data[i].j = m.data[i].j;
		t->data[i].e = m.data[i].e;
	}

	return OK;
}

//��ͨת�þ���
Status TransposeSMatrix(TSMatrix m,TSMatrix *t)
{
	//��ͨת�ã����п�ʼ�������������ھ���Ԫ����ʱ������ת�ã�����Ԫ���ۼ�
	if (!&m)
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	if (!t)
	{
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	t->mu = m.nu;
	t->nu = m.mu;
	t->tu = m.tu;
	if (t->tu)
	{
		int i = 1, j;//��¼����Ԫ�صĸ���

		for (j = 1; j <= t->nu; ++j)
		{
			for (i = 1; i <= m.tu; ++i)
			{
				if (m.data[i].j == j)
				{
					t->data[i].i = m.data[i].j;
					t->data[i].j = m.data[i].i;
					t->data[i].e = m.data[i].e;
					i++;
				}
			}
		}
	}
	
	return OK;
}

//����ת��
Status FastTranposeSMatrix(TSMatrix m, TSMatrix *T)
{
	T->mu = m.mu;
	T->nu = m.nu;
	T->tu = m.tu;
	int col = 1,t,q;
	int num[MAXSIZE], cpot[MAXSIZE];

	if (T->tu)
	{
		//��ʼ����������
		for (col = 1; col <= m.nu; ++col)
			num[col] = 0;
		for (t = 1; t <= m.tu; ++t)
			++num[m.data[t].j];//��m��ÿһ�к�����Ԫ����
		cpot[1] = 1;
		//���cpot���е�һ������Ԫ��b.data�е�����
		for (col = 2; col <= m.nu; ++col)
			cpot[col] = cpot[col - 1] + num[col - 1];

		for (t = 1; t <= m.tu; ++t)
		{
			col = m.data[t].j;
			q = cpot[col];
			T->data[q].i = m.data[t].j;
			T->data[q].j = m.data[t].i;
			T->data[q].e = m.data[t].e;
			++cpot[col];
		}
	}
	else
	{
		return ERROR;
	}

	return OK;
}

int main()
{
	TSMatrix t;
	TSMatrix m;

	CreateSMatrix(&t);
	InputM(&t);
	PrintM(t);
	FastTranposeSMatrix(t, &m);
	PrintM(m);

	/*
	TransposeSMatrix(t, &m);
	PrintM(m);
	*/
    return 0;
}

