// 稀疏矩阵行逻辑链接顺序表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef struct
{
	ElemType e;
	int i, j;
}Triple;

typedef struct
{
	Triple data[MAXSIZE+1];
	int rpos[MAXRC + 1];//各行第一个非零元素的位置表
	int mu, nu, tu;//存储行数，列数，非零元个数
}RLSMatrix;

//创建矩阵
Status CreateSMatrix(RLSMatrix *m)
{
	int i;
	Status k;
	Triple T;
	
	printf("请输入矩阵的行数，列数 ，非零元素数：\n");
	scanf_s("%d%d%d",&m->mu,&m->nu,&m->tu);

	m->data[0].i = 0;//为验证输入是否按照非递减序 比较最准备
	for (i = 1; i <= m->tu; ++i)
	{
		printf("按顺序输入第%d个非零元素所在行(1~%d),列(1~%d),元素值：", i, m->mu, m->nu);

		do {
			printf("输入三元组行，列，值\n");
			scanf_s("%d%d%d",&T.i,&T.j,&T.e);
			k = 0;

			if (T.i < 1 || T.i > m->mu || T.j < 1 || T.j > m->nu)
			{
				printf("行或者列超出范围!\n");
				k = 1;
				return ERROR;
			}
			if (T.i <= m->data[i - 1].i && T.j <= m->data[i - 1].j)
			{
				printf("没有按顺序输入非零元素!\n");
				return ERROR;
				k = 1;
			}
		} while (k);

		m->data[i] = T;
	}

	for (i = 1; i <= m->tu; i++) // 计算rpos[]
		if (m->data[i].i > m->data[i - 1].i)
			for (T.i = 0; T.i < m->data[i].i - m->data[i - 1].i; T.i++)
				m->rpos[m->data[i].i - T.i] = i;

	for (i = m->data[m->tu].i + 1; i <= m->mu; i++) // 给最后没有非零元素的几行赋值
		m->rpos[i] = m->tu + 1;

	return OK;
}

//销毁矩阵
Status DestorySMatrix(RLSMatrix *m)
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

//输出矩阵
Status PrintM(RLSMatrix m)
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
				printf("%d ", m.data[t++].e);
			//零元素
			else
				printf("0 ");
		}
		printf("\n");
	}

	return OK;
}

//复制矩阵
Status CopySMatrix(RLSMatrix m, RLSMatrix *t)
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
		t->rpos[i] = m.rpos[i];
	}

	return OK;
}

//快速转置
Status TransposeSMatrix(RLSMatrix m, RLSMatrix *T)
{
	T->mu = m.mu;
	T->nu = m.nu;
	T->tu = m.tu;
	int col = 1, t, q;
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
		printf("矩阵不存在!\n");
		return ERROR;
	}

	return OK;
}

//矩阵相乘
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q)
{
	int arow, brow, p, q, ccol, ctemp[MAXRC + 1];

	if (M.nu != N.mu) // 矩阵M的列数应和矩阵N的行数相等

		return ERROR;

	Q->mu = M.mu; // Q初始化

	Q->nu = N.nu;

	Q->tu = 0;

	M.rpos[M.mu + 1] = M.tu + 1; // 为方便后面的while循环临时设置

	N.rpos[N.mu + 1] = N.tu + 1;

	if (M.tu*N.tu != 0) // M和N都是非零矩阵
	{
		for (arow = 1; arow <= M.mu; ++arow)
		{ //从M的第一行开始，到最后一行，arow是M的当前行
			for (ccol = 1; ccol <= Q->nu; ++ccol)
				ctemp[ccol] = 0; //Q的当前行的各列元素累加器清零

			Q->rpos[arow] = Q->tu + 1; //Q当前行的第1个元素位于上1行最后1个元素之后
			
			/*找到每一行中的非零元素*/
			for (p = M.rpos[arow]; p<M.rpos[arow + 1]; ++p)
			{ // 对M当前行中每一个非零元
				brow = M.data[p].j; //找到对应元在N中的行号(M当前元的列号)
				/*
				rpos[row]指示矩阵N的第row行中第一个非零元在N.data中的序号，rpos[row+1]-1指向的第row行最后一个非零元的位置
				*/
				for (q = N.rpos[brow]; q<N.rpos[brow + 1]; ++q)
				{
					ccol = N.data[q].j; //乘积元素在Q中列号
					ctemp[ccol] += M.data[p].e*N.data[q].e;
				}//for
			} //求得Q中第arow行的非零元

			for (ccol = 1; ccol <= Q->nu; ++ccol) //压缩存储该行非零元
				if (ctemp[ccol])
				{
					if (++Q->tu>MAXSIZE)
						return ERROR;

					Q->data[Q->tu].i = arow;
					Q->data[Q->tu].j = ccol;
					Q->data[Q->tu].e = ctemp[ccol];
				}//if
		}//for
	}//if

	return OK;
}

int main()
{
	RLSMatrix m,t,q;
	
	CreateSMatrix(&m);
	CopySMatrix(m, &t);
	PrintM(m);
	PrintM(t);
	MultSMatrix(m, t, &q);
	PrintM(q);

    return 0;
}

