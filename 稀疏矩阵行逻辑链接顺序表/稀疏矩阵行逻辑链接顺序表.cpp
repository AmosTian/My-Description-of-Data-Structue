// ϡ��������߼�����˳���.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int rpos[MAXRC + 1];//���е�һ������Ԫ�ص�λ�ñ�
	int mu, nu, tu;//�洢����������������Ԫ����
}RLSMatrix;

//��������
Status CreateSMatrix(RLSMatrix *m)
{
	int i;
	Status k;
	Triple T;
	
	printf("�������������������� ������Ԫ������\n");
	scanf_s("%d%d%d",&m->mu,&m->nu,&m->tu);

	m->data[0].i = 0;//Ϊ��֤�����Ƿ��շǵݼ��� �Ƚ���׼��
	for (i = 1; i <= m->tu; ++i)
	{
		printf("��˳�������%d������Ԫ��������(1~%d),��(1~%d),Ԫ��ֵ��", i, m->mu, m->nu);

		do {
			printf("������Ԫ���У��У�ֵ\n");
			scanf_s("%d%d%d",&T.i,&T.j,&T.e);
			k = 0;

			if (T.i < 1 || T.i > m->mu || T.j < 1 || T.j > m->nu)
			{
				printf("�л����г�����Χ!\n");
				k = 1;
				return ERROR;
			}
			if (T.i <= m->data[i - 1].i && T.j <= m->data[i - 1].j)
			{
				printf("û�а�˳���������Ԫ��!\n");
				return ERROR;
				k = 1;
			}
		} while (k);

		m->data[i] = T;
	}

	for (i = 1; i <= m->tu; i++) // ����rpos[]
		if (m->data[i].i > m->data[i - 1].i)
			for (T.i = 0; T.i < m->data[i].i - m->data[i - 1].i; T.i++)
				m->rpos[m->data[i].i - T.i] = i;

	for (i = m->data[m->tu].i + 1; i <= m->mu; i++) // �����û�з���Ԫ�صļ��и�ֵ
		m->rpos[i] = m->tu + 1;

	return OK;
}

//���پ���
Status DestorySMatrix(RLSMatrix *m)
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

//�������
Status PrintM(RLSMatrix m)
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
				printf("%d ", m.data[t++].e);
			//��Ԫ��
			else
				printf("0 ");
		}
		printf("\n");
	}

	return OK;
}

//���ƾ���
Status CopySMatrix(RLSMatrix m, RLSMatrix *t)
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
		t->rpos[i] = m.rpos[i];
	}

	return OK;
}

//����ת��
Status TransposeSMatrix(RLSMatrix m, RLSMatrix *T)
{
	T->mu = m.mu;
	T->nu = m.nu;
	T->tu = m.tu;
	int col = 1, t, q;
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
		printf("���󲻴���!\n");
		return ERROR;
	}

	return OK;
}

//�������
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q)
{
	int arow, brow, p, q, ccol, ctemp[MAXRC + 1];

	if (M.nu != N.mu) // ����M������Ӧ�;���N���������

		return ERROR;

	Q->mu = M.mu; // Q��ʼ��

	Q->nu = N.nu;

	Q->tu = 0;

	M.rpos[M.mu + 1] = M.tu + 1; // Ϊ��������whileѭ����ʱ����

	N.rpos[N.mu + 1] = N.tu + 1;

	if (M.tu*N.tu != 0) // M��N���Ƿ������
	{
		for (arow = 1; arow <= M.mu; ++arow)
		{ //��M�ĵ�һ�п�ʼ�������һ�У�arow��M�ĵ�ǰ��
			for (ccol = 1; ccol <= Q->nu; ++ccol)
				ctemp[ccol] = 0; //Q�ĵ�ǰ�еĸ���Ԫ���ۼ�������

			Q->rpos[arow] = Q->tu + 1; //Q��ǰ�еĵ�1��Ԫ��λ����1�����1��Ԫ��֮��
			
			/*�ҵ�ÿһ���еķ���Ԫ��*/
			for (p = M.rpos[arow]; p<M.rpos[arow + 1]; ++p)
			{ // ��M��ǰ����ÿһ������Ԫ
				brow = M.data[p].j; //�ҵ���ӦԪ��N�е��к�(M��ǰԪ���к�)
				/*
				rpos[row]ָʾ����N�ĵ�row���е�һ������Ԫ��N.data�е���ţ�rpos[row+1]-1ָ��ĵ�row�����һ������Ԫ��λ��
				*/
				for (q = N.rpos[brow]; q<N.rpos[brow + 1]; ++q)
				{
					ccol = N.data[q].j; //�˻�Ԫ����Q���к�
					ctemp[ccol] += M.data[p].e*N.data[q].e;
				}//for
			} //���Q�е�arow�еķ���Ԫ

			for (ccol = 1; ccol <= Q->nu; ++ccol) //ѹ���洢���з���Ԫ
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

