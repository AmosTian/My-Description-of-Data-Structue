// ϡ������ʮ������.cpp : �������̨Ӧ�ó������ڵ㡣
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
	OLink *rhead, *chead;//�к�������ͷָ��������ַ
	int mu, nu, tu;//ϡ�����������������ͷ���Ԫ�ظ���
}CrossList;

//����ϡ����󣬲���ʮ������洢��ʾ
Status CreateSMatrix(CrossList *M)
{
	OLNode *p,*q;
	int m, n, t,i,j,e;
	printf("�����������������������Ԫ����:\n");
	scanf_s("%d%d%d",&m,&n,&t);//�������������ͷ���Ԫ����

	M->mu = m; M->nu = n; M->tu = t;
	if (!(M->rhead = (OLink*)malloc((m + 1) * sizeof(OLink))))
	{
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}
	if (!(M->chead = (OLink*)malloc((n + 1) * sizeof(OLink))))
	{
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	for (i = 1; i <= m; ++i)
	{
		M->chead[i] = NULL;//��ʼ������ͷָ������������������Ϊ������
		M->rhead[i] = NULL;
	}
		

	while (1)
	{
		printf("���������꼰��ֵ:\n");
		scanf_s("%d",&i);

		if (i == 0)
		{
			printf("�������!\n");
			break;//��0��Ϊ���������־
		}
		scanf_s("%d%d",&j,&e);
		//�����½ڵ�
		if (!(p = (OLNode *)malloc(1 * sizeof(OLNode))))
		{
			printf("�ڵ��ڴ����ʧ��!\n");
			exit(OVERFLOW);
		}

		p->i = i; p->j = j; p->e = e;//��ֵ

		//�в���
		if (M->rhead[i] == NULL || M->rhead[i]->j > j)
		{
			//���Ƿ�ָ��ڵ�,������û��Ԫ�ػ��ߵ�һ��Ԫ���ڸýڵ�֮�󣬽�p��ֵ��ͷ���
			p->right = M->rhead[i];
			M->rhead[i] = p;
		}
		else
		{
			//Ѱ�ҽڵ�Ĳ���λ��
			for (q = M->rhead[i]; (q->right) && q->right->j < j; q = q->right);

			p->right = q->right;
			q->right = p;
		}

		//�в���
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

//����ʮ������
Status DestroySMatrix(CrossList *M)
{
	int i = 1;
	OLNode *p, *q;

	for (i = 1; i <= (*M).mu; ++i)
	{
		p = M->rhead[i];//����ָ��
		while (p)
		{
			q = p;
			p = p->right;
			free(q);//Qָ���ͷ��ڴ�ĵ�ַ
		}
	}

	
	M->chead = M->rhead = NULL;
	M->mu = M->nu = M->tu = 0;

	return OK;
}

//���ʺ���
Status visit(ElemType e)
{
	printf("%d ",e);
	return OK;
}

//���ʮ�������ʾ�ľ���
Status TraverseM(CrossList M,Status(*visit)(ElemType e))
{
	if (!(&M))
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	printf("�������:\n");

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
				//����Ԫ��
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

//���ʮ������洢��ֵ
Status DisplayM(CrossList M)
{
	if (!(&M))
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	printf("�������ʮ������洢��ֵ��:\n");
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

//���ƾ���
Status CopyM(CrossList M, CrossList *T)
{
	if (!M.rhead)
	{
		printf("���󲻴���!\n");
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
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	for (i = 1; i <= M.mu; i++) // ��ʼ������T����ͷָ������;��������Ϊ������ 
		(*T).rhead[i] = NULL;
	for (i = 1; i <= M.nu; i++) // ��ʼ������T����ͷָ������;��������Ϊ������ 
		(*T).chead[i] = NULL;

	
	for (i = 1; i <= M.mu; ++i)
	{
		p = M.rhead[i];
		while (p)
		{
			//��Ϊ��������ʱ���Ѿ�ȷ����λ�ã�����ֻ���������
			//1����һ��λ��  2������β��
			q = (OLNode *)malloc(1 * sizeof(OLNode));
			if (!q)
			{
				printf("�ڴ����ʧ��!\n");
				exit(OVERFLOW);
			}

			q->i = p->i;
			q->j = p->j;
			q->e = p->e;

			if (!T->rhead[i])//���ڱ�ͷ
			{
				T->rhead[i] = q;
				qr = q;//ָ���β
			}
			else//��β
			{
				qr->right = q;
				qr = q;
			}

			if (!T->chead[q->j])//��ͷ
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

//����ȡ��
Status NegateM(CrossList M, CrossList *T)
{
	if (!M.rhead)
	{
		printf("���󲻴���!\n");
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
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	for (i = 1; i <= M.mu; i++) // ��ʼ������T����ͷָ������;��������Ϊ������ 
		(*T).rhead[i] = NULL;
	for (i = 1; i <= M.nu; i++) // ��ʼ������T����ͷָ������;��������Ϊ������ 
		(*T).chead[i] = NULL;


	for (i = 1; i <= M.mu; ++i)
	{
		p = M.rhead[i];
		while (p)
		{
			//��Ϊ��������ʱ���Ѿ�ȷ����λ�ã�����ֻ���������
			//1����һ��λ��  2������β��
			q = (OLNode *)malloc(1 * sizeof(OLNode));
			if (!q)
			{
				printf("�ڴ����ʧ��!\n");
				exit(OVERFLOW);
			}

			q->i = p->i;
			q->j = p->j;
			q->e = -1 * p->e;

			if (!T->rhead[i])//���ڱ�ͷ
			{
				T->rhead[i] = q;
				qr = q;//ָ���β
			}
			else//��β
			{
				qr->right = q;
				qr = q;
			}

			if (!T->chead[q->j])//��ͷ
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

//������� Q = M+N
Status AddSMatrix(CrossList M, CrossList N, CrossList *Q)
{
	if (!M.chead || !N.chead)//���󲻴��ڵ����
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	if (M.mu != N.mu || M.nu != N.nu)//ͬ���;������
	{
		printf("����������ͬһ�����;���!\n");
		return ERROR;
	}

	int k, i;
	OLink *col;
	OLNode *pm, *pn, *pq = NULL, *p;

	Q->mu = M.mu; Q->nu = M.nu; Q->tu =0;//��ʼ������
	Q->rhead = (OLink *)malloc((Q->mu + 1)*sizeof(OLink));//���д洢����Ԫ�صĵ�ַ
	Q->chead = (OLink *)malloc((Q->nu + 1) * sizeof(OLink));//���д洢����Ԫ�ص�ַ
	col = (OLink *)malloc((Q->nu + 1) * sizeof(OLink));//�洢ÿһ�е����һ������Ԫ�ص�ַ
	if (!Q->rhead || !Q->chead || !col)
	{
		printf("�ڴ����ʧ��!\n");
		return ERROR;
	}
	
	//ʹ��ָ������ʼ��
	for (k = 1; k <= Q->mu; ++k)
	{
		Q->rhead[k] = NULL;
	}
	for (k = 1; k <= Q->nu; ++k)
	{
		col[k] = NULL;
		Q->chead[k] = NULL;
	}
	//������
	/*
	ÿ�о�����������ֽ��
	1.M����Ԫ�ز�Ϊ0��N����Ԫ��Ϊ0��
	2.M����Ϊ0��N����Ϊ0
	3.M������N������Ӳ�Ϊ0
	4.���Ϊ0
	*/
	for (i = 1; i <= M.mu; ++i)
	{
		pm = M.rhead[i];
		pn = N.rhead[i];
		while (pm && pn)
		{
			//ע��ѭ��������M�����N����Ԫ�ض���Ϊ�㣬����һ����һ����Ԫ��Ϊ��ͷ�����˳���
			//������Ҫ�ֱ�MN��ʣ���Ԫ�ز������Q��
			if (pm->j < pn->j)//��һ�����������MԪ�ز�Ϊ0��N����Ԫ��Ϊ0
			{
				p = (OLink)malloc(sizeof(OLNode));
				if (!p)
				{
					printf("�ڴ����ʧ��!\n");
					exit(OVERFLOW);
				}
				Q->tu++;
				p->i = i;
				p->j = pm->j;
				p->e = pm->e;
				p->right = NULL;
				pm = pm->right;
			}
			else if (pm->j > pn->j)//�ڶ��������N����Ϊ0��M����Ϊ0
			{
				p = (OLink)malloc(sizeof(OLNode));
				if (!p)
				{
					printf("�ڴ����ʧ��!\n");
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
					printf("�ڴ����ʧ��!\n");
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
			//ǰ��������Ĺ�ͬ�����ǽ�pָ���Ԫ�ز��뵽����Q�У������봴������
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
				col[p->j] = p;//colָ����е����һ��Ԫ��
			}
			else
			{//����β���룬���޸���βָ���ָ��
				col[p->j]->down = p;
				col[p->j] = col[p->j]->down;
			}
		}//while(��������)
		//����M����ʣ��Ԫ��
		while (pm)
		{
			p = (OLink)malloc(sizeof(OLNode));
			if (!p)
			{
				printf("�ڴ����ʧ��!\n");
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
		//����N����ʣ��Ԫ��
		while (pn)
		{
			p = (OLink)malloc(sizeof(OLNode));
			if (!p)
			{
				printf("�ڴ����ʧ��!\n");
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
	}//for(����ÿ��)
	//��ÿһ�����һ��Ԫ�ص���downָ�븳ֵ
	for (k = 1; k <= Q->nu; ++k)
	{
		if (col[k])
		{
			col[k]->down = NULL;
		}
	}

	return OK;
}

//�������Q = M-N
Status SubtSMatrix(CrossList M, CrossList N, CrossList *Q)
{
	if (!M.chead || !N.chead)
	{
		printf("���󲻴���!\n");
		return ERROR;
	}

	if (M.mu != N.mu || M.nu != N.nu)
	{
		printf("�������Ͳ�һ��!\n");
		return ERROR;
	}

	CrossList tmp;
	//����ȡ��
	NegateM(N,&tmp);
	AddSMatrix(M, tmp, Q);

	return OK;
}

//����˻� Q = M*N
Status MultiSM(CrossList M, CrossList N, CrossList *Q)
{
	if (!M.chead || !N.rhead)
	{//���󲻴���
		printf("���󲻴���!\n");
		return ERROR;
	}

	if (M.mu != N.nu)
	{//M���������������������������
		printf("M�����в�����N���������������!\n");
		return ERROR;
	}

	if (Q->rhead)
		DestroySMatrix(Q);
	int i, k,j;
	ElemType e;
	OLink p0, q0, q, q1 = NULL, q2 = NULL;

	//��ʼ��
	Q->mu = M.mu; Q->nu = N.nu; Q->tu = 0;
	Q->chead = (OLink *)malloc((Q->nu + 1) * sizeof(OLink));
	Q->rhead = (OLink *)malloc((Q->nu + 1) * sizeof(OLink));
	if (!Q->rhead || !Q->chead)
	{
		printf("�ڴ����ʧ��!\n");
		return ERROR;
	}
	//��ʼ��ָ��
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
			p0 = M.rhead[i];//p0ָ��M����Ԫ
			q0 = N.chead[j];//q0ָ��q����Ԫ
			e = 0;
			while (p0 && q0)
			{
				if (q0->i < p0->j)//q0������С��p0������
				{
					q0 = q0->down;
				}
				else if (q0->i > p0->j)//q0������С��p0������
				{
					p0 = p0->right;
				}
				else//��Ԫ�ؿ������
				{
					e += p0->e * q0->e;
					p0 = p0->right;
					q0 = q0->down;
				}
			}

			if (e)//�˻���Ϊ0���Բ������
			{
				Q->tu++;
				q = (OLink)malloc(sizeof(OLNode));
				if (!q)
				{
					printf("�ڴ����ʧ��!\n");
					exit(OVERFLOW);
				}
				q->i = i;
				q->j = j;
				q->e = e;
				q->right = NULL;
				q->right = NULL;
				
				//�в���
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

				//�в���
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

	printf("�������m:\n");
	CreateSMatrix(&m);
	TraverseM(m,visit);

	printf("�������n:\n");
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