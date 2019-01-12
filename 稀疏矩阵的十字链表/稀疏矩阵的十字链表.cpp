// 稀疏矩阵的十字链表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef struct OLNode
{
	int i, j;
	ElemType e;
	struct OLNode *right, *down;
}OLNode,*OLink;

typedef struct
{
	OLink *rhead, *chead;//行和列链表头指针向量基址
	int mu, nu, tu;//稀疏矩阵的行数、列数和非零元素个数
}CrossList;

//创建稀疏矩阵，采用十字链表存储表示
Status CreateSMatrix(CrossList *M)
{
	OLNode *p,*q;
	int m, n, t,i,j,e;
	printf("输入矩阵行数、列数、非零元个数:\n");
	scanf_s("%d%d%d",&m,&n,&t);//输入行数列数和非零元个数

	M->mu = m; M->nu = n; M->tu = t;
	if (!(M->rhead = (OLink*)malloc((m + 1) * sizeof(OLink))))
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}
	if (!(M->chead = (OLink*)malloc((n + 1) * sizeof(OLink))))
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}

	for (i = 1; i <= m; ++i)
	{
		M->chead[i] = NULL;//初始化行列头指针向量；各行列链表为空链表
		M->rhead[i] = NULL;
	}
		

	while (1)
	{
		printf("输入点的坐标及其值:\n");
		scanf_s("%d",&i);

		if (i == 0)
		{
			printf("输入结束!\n");
			break;//以0作为输入结束标志
		}
		scanf_s("%d%d",&j,&e);
		//分配新节点
		if (!(p = (OLNode *)malloc(1 * sizeof(OLNode))))
		{
			printf("节点内存分配失败!\n");
			exit(OVERFLOW);
		}

		p->i = i; p->j = j; p->e = e;//赋值

		//行插入
		if (M->rhead[i] == NULL || M->rhead[i]->j > j)
		{
			//覆盖否指针节点,若该行没有元素或者第一个元素在该节点之后，将p赋值给头结点
			p->right = M->rhead[i];
			M->rhead[i] = p;
		}
		else
		{
			//寻找节点的插入位置
			for (q = M->rhead[i]; (q->right) && q->right->j < j; q = q->right);

			p->right = q->right;
			q->right = p;
		}

		//列插入
		if (M->chead[j] == NULL || M->chead[j]->i > i)
		{
			p->down = M->chead[j];
			M->chead[j] = p;
		}
		else
		{
			for (q = M->chead[j]; (q->down) && q->down[j].i < i; q = q->down);

			p->down = q->down;
			q->down = p;
		}
	}

	return OK;
}

//销毁十字链表
Status DestroySMatrix(CrossList *M)
{
	int i = 1;
	OLNode *p, *q;

	for (i = 1; i <= (*M).mu; ++i)
	{
		p = M->rhead[i];//遍历指针
		while (p)
		{
			q = p;
			p = p->right;
			free(q);//Q指向被释放内存的地址
		}
	}

	
	M->chead = M->rhead = NULL;
	M->mu = M->nu = M->tu = 0;

	return OK;
}

//访问函数
Status visit(ElemType e)
{
	printf("%d ",e);
	return OK;
}

//输出十字链表表示的矩阵
Status TraverseM(CrossList M,Status(*visit)(ElemType e))
{
	if (!(&M))
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	printf("输出矩阵:\n");

	int i, j;
	int t = 1;
	OLNode* p;
	for (i = 1; i <= M.mu; ++i)
	{
		p = M.rhead[i];
		if(p)
		{
			for (j = 1; j <= M.nu; ++j)
			{
				//非零元素
				if (p && p->j == j)
				{
					visit(p->e);
					p = p->right;
				}
				else
				{
					visit(0);
				}
			}
		}
		else
		{
			for (j = 1; j <= M.nu; ++j)
			{
				printf("0 ");
			}
		}
		printf("\n");
	}

	return OK;
}

//输出十字链表存储的值
Status DisplayM(CrossList M)
{
	if (!(&M))
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	printf("按行输出十字链表存储的值是:\n");
	int k;
	OLink p;
	for (k = 1; k <= M.mu; ++k)
	{
		p = M.rhead[k];
		while (p)
		{
			printf("(%d,%d) e = %d",p->i,p->j,p->e);
			p = p->right;
			printf("\n");
		}
	}

	return OK;
}

//复制矩阵
Status CopyM(CrossList M, CrossList *T)
{
	if (!M.rhead)
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	if ((T->rhead))
		DestroySMatrix(T);

	int i;
	OLNode *p, *q = NULL, *qr = NULL, *qc = NULL;

	T->mu = M.mu; T->nu = M.nu; T->tu = M.tu;
	T->rhead = (OLink *)malloc((T->mu + 1) * sizeof(OLink));
	T->chead = (OLink *)malloc((T->nu + 1) * sizeof(OLink));
	if (!T->chead || !T->rhead)
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}

	for (i = 1; i <= M.mu; i++) // 初始化矩阵T的行头指针向量;各行链表为空链表 
		(*T).rhead[i] = NULL;
	for (i = 1; i <= M.nu; i++) // 初始化矩阵T的列头指针向量;各列链表为空链表 
		(*T).chead[i] = NULL;

	
	for (i = 1; i <= M.mu; ++i)
	{
		p = M.rhead[i];
		while (p)
		{
			//因为创建链表时，已经确定其位置，所以只有两种情况
			//1、第一个位置  2、链表尾部
			q = (OLNode *)malloc(1 * sizeof(OLNode));
			if (!q)
			{
				printf("内存分配失败!\n");
				exit(OVERFLOW);
			}

			q->i = p->i;
			q->j = p->j;
			q->e = p->e;

			if (!T->rhead[i])//插在表头
			{
				T->rhead[i] = q;
				qr = q;//指向队尾
			}
			else//表尾
			{
				qr->right = q;
				qr = q;
			}

			if (!T->chead[q->j])//表头
			{
				T->chead[q->j] = q;
				q->down = NULL;
			}
			else
			{
				qc = T->chead[q->j];
				while (qc->down)
				{
					qc = qc->down;
				}
				qc->down = q;
				q->down = NULL;
			}

			p = p->right;
		}

		q->right = NULL;
	}

	return OK;
}

//矩阵取反
Status NegateM(CrossList M, CrossList *T)
{
	if (!M.rhead)
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	if ((T->rhead))
		DestroySMatrix(T);

	int i;
	OLNode *p, *q = NULL, *qr = NULL, *qc = NULL;

	T->mu = M.mu; T->nu = M.nu; T->tu = M.tu;
	T->rhead = (OLink *)malloc((T->mu + 1) * sizeof(OLink));
	T->chead = (OLink *)malloc((T->nu + 1) * sizeof(OLink));
	if (!T->chead || !T->rhead)
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}

	for (i = 1; i <= M.mu; i++) // 初始化矩阵T的行头指针向量;各行链表为空链表 
		(*T).rhead[i] = NULL;
	for (i = 1; i <= M.nu; i++) // 初始化矩阵T的列头指针向量;各列链表为空链表 
		(*T).chead[i] = NULL;


	for (i = 1; i <= M.mu; ++i)
	{
		p = M.rhead[i];
		while (p)
		{
			//因为创建链表时，已经确定其位置，所以只有两种情况
			//1、第一个位置  2、链表尾部
			q = (OLNode *)malloc(1 * sizeof(OLNode));
			if (!q)
			{
				printf("内存分配失败!\n");
				exit(OVERFLOW);
			}

			q->i = p->i;
			q->j = p->j;
			q->e = -1 * p->e;

			if (!T->rhead[i])//插在表头
			{
				T->rhead[i] = q;
				qr = q;//指向队尾
			}
			else//表尾
			{
				qr->right = q;
				qr = q;
			}

			if (!T->chead[q->j])//表头
			{
				T->chead[q->j] = q;
				q->down = NULL;
			}
			else
			{
				qc = T->chead[q->j];
				while (qc->down)
				{
					qc = qc->down;
				}
				qc->down = q;
				q->down = NULL;
			}

			p = p->right;
		}

		q->right = NULL;
	}

	return OK;
}

//矩阵相加 Q = M+N
Status AddSMatrix(CrossList M, CrossList N, CrossList *Q)
{
	if (!M.chead || !N.chead)//矩阵不存在的情况
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	if (M.mu != N.mu || M.nu != N.nu)//同类型矩阵相加
	{
		printf("两个矩阵不是同一个类型矩阵!\n");
		return ERROR;
	}

	int k, i;
	OLink *col;
	OLNode *pm, *pn, *pq = NULL, *p;

	Q->mu = M.mu; Q->nu = M.nu; Q->tu =0;//初始化变量
	Q->rhead = (OLink *)malloc((Q->mu + 1)*sizeof(OLink));//按行存储非零元素的地址
	Q->chead = (OLink *)malloc((Q->nu + 1) * sizeof(OLink));//按列存储非零元素地址
	col = (OLink *)malloc((Q->nu + 1) * sizeof(OLink));//存储每一列的最后一个非零元素地址
	if (!Q->rhead || !Q->chead || !col)
	{
		printf("内存分配失败!\n");
		return ERROR;
	}
	
	//使用指针必须初始化
	for (k = 1; k <= Q->mu; ++k)
	{
		Q->rhead[k] = NULL;
	}
	for (k = 1; k <= Q->nu; ++k)
	{
		col[k] = NULL;
		Q->chead[k] = NULL;
	}
	//遍历行
	/*
	每行矩阵相加有四种结果
	1.M矩阵元素不为0，N矩阵元素为0，
	2.M矩阵为0，N矩阵不为0
	3.M矩阵与N矩阵相加不为0
	4.相加为0
	*/
	for (i = 1; i <= M.mu; ++i)
	{
		pm = M.rhead[i];
		pn = N.rhead[i];
		while (pm && pn)
		{
			//注意循环条件是M矩阵和N矩阵元素都不为零，所以一旦有一个行元素为到头，则退出；
			//所以需要分别将MN中剩余的元素插入矩阵Q中
			if (pm->j < pn->j)//第一种情况，该行M元素不为0，N矩阵元素为0
			{
				p = (OLink)malloc(sizeof(OLNode));
				if (!p)
				{
					printf("内存分配失败!\n");
					exit(OVERFLOW);
				}
				Q->tu++;
				p->i = i;
				p->j = pm->j;
				p->e = pm->e;
				p->right = NULL;
				pm = pm->right;
			}
			else if (pm->j > pn->j)//第二种情况，N矩阵不为0，M矩阵为0
			{
				p = (OLink)malloc(sizeof(OLNode));
				if (!p)
				{
					printf("内存分配失败!\n");
					exit(OVERFLOW);
				}
				Q->tu++;
				p->i = i;
				p->j = pn->j;
				p->e = pn->e;
				p->right = NULL;
				pn = pn->right;
			}
			else if (pm->e + pn->e)
			{
				p = (OLink)malloc(sizeof(OLNode));
				if (!p)
				{
					printf("内存分配失败!\n");
					return ERROR;
				}
				Q->tu++;
				p->e = pm->e + pn->e;
				p->i = i;
				p->j = pm->j;
				p->right = NULL;
				pm = pm->right;
				pn = pn->right;
			}
			else
			{
				pm = pm->right;
				pn = pn->right;
				continue;
			}
			//前三种情况的共同操作是将p指向的元素插入到矩阵Q中，类似与创建矩阵
			if (!Q->rhead[i])
			{
				Q->rhead[i] = p;
				pq = p;
			}
			else
			{
				pq->right = p;
				pq = p;
			}
			if (!Q->chead[p->j])
			{
				Q->chead[p->j] = p;
				col[p->j] = p;//col指向该列的最后一个元素
			}
			else
			{//在列尾插入，并修改列尾指针的指向
				col[p->j]->down = p;
				col[p->j] = col[p->j]->down;
			}
		}//while(遍历行内)
		//插入M矩阵剩余元素
		while (pm)
		{
			p = (OLink)malloc(sizeof(OLNode));
			if (!p)
			{
				printf("内存分配失败!\n");
				exit(OVERFLOW);
			}
			Q->tu++;
			p->i = i;
			p->j = pm->j;
			p->e = pm->e;
			p->right = NULL;
			pm = pm->right;
			if (!Q->rhead[i])
			{
				Q->rhead[i] = p;
				pq = p;
			}
			else
			{
				pq->right = p;
				pq = p;
			}
			if (!Q->chead[p->j])
			{
				Q->chead[p->j] = p;
				col[p->j] = p;
			}
			else
			{
				col[p->j]->down = p;
				col[p->j] = col[p->j]->down;
			}
		}
		//插入N矩阵剩余元素
		while (pn)
		{
			p = (OLink)malloc(sizeof(OLNode));
			if (!p)
			{
				printf("内存分配失败!\n");
				exit(OVERFLOW);
			}
			Q->tu++;
			p->i = i;
			p->j = pn->j;
			p->e = pn->e;
			p->right = NULL;
			pn = pn->right;
			if (!Q->rhead[i])
			{
				Q->rhead[i] = p;
				pq = p;
			}
			else
			{
				pq->right = p;
				pq = p;
			}
			if (!Q->chead[p->j])
			{
				Q->chead[p->j] = p;
				col[p->j] = p;
			}
			else
			{
				col[p->j]->down = p;
				col[p->j] = col[p->j]->down;
			}
		}
	}//for(遍历每行)
	//将每一列最后一个元素的列down指针赋值
	for (k = 1; k <= Q->nu; ++k)
	{
		if (col[k])
		{
			col[k]->down = NULL;
		}
	}

	return OK;
}

//矩阵相减Q = M-N
Status SubtSMatrix(CrossList M, CrossList N, CrossList *Q)
{
	if (!M.chead || !N.chead)
	{
		printf("矩阵不存在!\n");
		return ERROR;
	}

	if (M.mu != N.mu || M.nu != N.nu)
	{
		printf("矩阵类型不一致!\n");
		return ERROR;
	}

	CrossList tmp;
	//矩阵取反
	NegateM(N,&tmp);
	AddSMatrix(M, tmp, Q);

	return OK;
}

//矩阵乘积 Q = M*N
Status MultiSM(CrossList M, CrossList N, CrossList *Q)
{
	if (!M.chead || !N.rhead)
	{//矩阵不存在
		printf("矩阵不存在!\n");
		return ERROR;
	}

	if (M.mu != N.nu)
	{//M矩阵行数不等于列数，不能相乘
		printf("M矩阵行不等于N的列数，不能相乘!\n");
		return ERROR;
	}

	if (Q->rhead)
		DestroySMatrix(Q);
	int i, k,j;
	ElemType e;
	OLink p0, q0, q, q1 = NULL, q2 = NULL;

	//初始化
	Q->mu = M.mu; Q->nu = N.nu; Q->tu = 0;
	Q->chead = (OLink *)malloc((Q->nu + 1) * sizeof(OLink));
	Q->rhead = (OLink *)malloc((Q->nu + 1) * sizeof(OLink));
	if (!Q->rhead || !Q->chead)
	{
		printf("内存分配失败!\n");
		return ERROR;
	}
	//初始化指针
	for (k = 1; k <= Q->mu; ++k)
	{
		Q->rhead[k] = NULL;
	}
	for (k = 1; k <= Q->nu; ++k)
	{
		Q->chead[k] = NULL;
	}

	for (i = 1; i <= Q->mu; ++i)
	{
		for (j = 1; j <= Q->nu; ++j)
		{
			p0 = M.rhead[i];//p0指向M中行元
			q0 = N.chead[j];//q0指向q中列元
			e = 0;
			while (p0 && q0)
			{
				if (q0->i < p0->j)//q0所在行小于p0所在列
				{
					q0 = q0->down;
				}
				else if (q0->i > p0->j)//q0所在行小于p0所在列
				{
					p0 = p0->right;
				}
				else//两元素可以相乘
				{
					e += p0->e * q0->e;
					p0 = p0->right;
					q0 = q0->down;
				}
			}

			if (e)//乘积不为0可以插入矩阵
			{
				Q->tu++;
				q = (OLink)malloc(sizeof(OLNode));
				if (!q)
				{
					printf("内存分配失败!\n");
					exit(OVERFLOW);
				}
				q->i = i;
				q->j = j;
				q->e = e;
				q->right = NULL;
				q->right = NULL;
				
				//行插入
				if (!Q->rhead[i])
				{
					Q->rhead[i] = q;
					q1 = q;
				}
				else
				{
					q1->right = q;
					q1 = q;
				}

				//列插入
				if (!Q->chead[j])
				{
					Q->chead[j] = q;
				}
				else
				{
					q2 = Q->chead[j];
					while (q2->down)
					{
						q2 = q2->down;
					}

					q2->down = q;
				}
			}//while
		}//for_j
	}//for_i

	return OK;
}

int main()
{
	CrossList m,t,n;

	printf("输入矩阵m:\n");
	CreateSMatrix(&m);
	TraverseM(m,visit);

	printf("输入矩阵n:\n");
	CreateSMatrix(&n);
	TraverseM(n, visit);
	/*
	MultiSM(m, n, &t);
	TraverseM(t,visit)
	SubtSMatrix(m, n, &t);
	TraverseM(t,visit);
	AddSMatrix(m, n, &t);
	TraverseM(t, visit);
	*/
	return 0;
}