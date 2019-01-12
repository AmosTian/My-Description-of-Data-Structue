// 稀疏矩阵.cpp : 定义控制台应用程序的入口点。
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
	int mu, nu, tu;//矩阵行数，列数，非零元素个数
}TSMatrix;

Status CreateSMatrix(TSMatrix *m)
{
	m = (TSMatrix *)malloc(1*sizeof(TSMatrix));

	if (!m)
	{
		printf("内存分配失败!\n");
		return TRUE;
	}

	m->mu = 0;
	m->nu = 0;
	m->tu = 0;

	return OK;
}

//销毁矩阵
Status DestorySMatrix(TSMatrix *m)
{
	if (!m)
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	m->mu = 0;
	m->nu = 0;
	m->tu = 0;

	return OK;
}

//输入矩阵的值
Status InputM(TSMatrix *m)
{
	if (!m)
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	int c;

	printf("输入矩阵的行数，列数，非零元素个数:\n");

	scanf_s("%d %d %d", &m->mu,&m->nu,&m->tu);

	printf("输入矩阵非零元素的值:\n");

	for (c = 1; c <= m->tu; c++)

	{

		scanf_s("%d", &m->data[c].i);

		scanf_s("%d", &m->data[c].j);

		scanf_s("%d", &m->data[c].e);

	}

	return OK;
}

//打印矩阵
Status PrintM(TSMatrix m)
{
	if (!(&m))
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	printf("输出矩阵:\n");

	int i, j;

	int t = 1;
	for (i = 1; i <= m.mu; ++i)
	{
		for (j = 1; j <= m.nu; ++j)
		{
			//非零元素
			if (m.data[t].i == i && m.data[t].j == j)
				printf("%d ",m.data[t++].e);
			//零元素
			else
				printf("0 ");
		}
		printf("\n");
	}

	return OK;
}

//复制矩阵
Status CopySMatrix(TSMatrix m, TSMatrix *t)
{
	if (!&m)
	{
		printf("矩阵不存在!\n");
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

//普通转置矩阵
Status TransposeSMatrix(TSMatrix m,TSMatrix *t)
{
	//普通转置，从列开始遍历，列数等于矩阵元素列时，进行转置，非零元素累加
	if (!&m)
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	if (!t)
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}

	t->mu = m.nu;
	t->nu = m.mu;
	t->tu = m.tu;
	if (t->tu)
	{
		int i = 1, j;//记录非零元素的个数

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

//快速转置
Status FastTranposeSMatrix(TSMatrix m, TSMatrix *T)
{
	T->mu = m.mu;
	T->nu = m.nu;
	T->tu = m.tu;
	int col = 1,t,q;
	int num[MAXSIZE], cpot[MAXSIZE];

	if (T->tu)
	{
		//初始化计数数组
		for (col = 1; col <= m.nu; ++col)
			num[col] = 0;
		for (t = 1; t <= m.tu; ++t)
			++num[m.data[t].j];//求m中每一列含非零元个数
		cpot[1] = 1;
		//求第cpot列中第一个非零元在b.data中的序列
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

