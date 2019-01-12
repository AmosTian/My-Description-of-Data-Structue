// �����.cpp : �������̨Ӧ�ó������ڵ㡣
//���ַ�����ʽ

#include "stdafx.h"
# include<iostream>

using namespace std;

typedef struct
{
	AtomType str[MaxLength];
	Status length;
}SString;//�Զ����ַ���

typedef enum {ATOM,LIST}ElemTag;//ATOM=0��ʾԭ�ӣ�List=1��ʾ�ӱ�
typedef struct GLNode
{
	ElemTag tag;//��־tag��������Ԫ����ԭ�ӻ����ӱ�
	union
	{
		AtomType atom;//ԭ�ӽ���ֵ���û��Լ����������
		struct {
			struct GLNode *hp, *tp;//hpָ���ͷ��tpָ���β
		}ptr;
	};
}*GList,GLNode;

//�ж��Ƿ�Ϊ���ַ���
Status StrEmpty(SString S)
{
	if (S.length == 0)
		return OK;
	else
		return ERROR;
}

//�󴮳���
Status StrLength(SString S)
{
	return S.length;
}

//���Ƚ�
Status StrCompare(SString S, SString T)
{
	int i;

	for (i = 0; i < S.length && i < T.length; ++i)
	{
		if (S.str[i] != T.str[i])
			return S.str[i] - T.str[i];//���ص�һ���Ƚϲ�ͬ�ַ��Ĵ�С
	}

	return S.length - T.length;//�ȽϽ�����������������ֵ
}

//��մ�
void StrClear(SString *S)
{
	S->length = 0;
}

//���ĸ�ֵ����
void StrCopy(SString *T, SString S)
{
	int i;
	for (i = 0; i < S.length; ++i)
	{
		T->str[i] = S.str[i];
	}

	T->length = S.length;
}

//����ֵ
void StrAssign(SString *S, char str[])
{
	int i;
	for (i = 0; str[i] != '\0'; ++i)
		S->str[i] = str[i];
	S->length = i;
}

//��ȡ��pos��ʼ�ĳ���Ϊlen���Ӵ�
Status SubString(SString *Sub,SString S,int pos,int len)
{
	int i;

	if (pos < 0 || len < 0 || pos + len - 1 > S.length)
	{
		printf("�������Ϸ�!\n");
		return ERROR;
	}
	else
	{
		for (i = 0; i < len; ++i)
			Sub->str[i] = S.str[i + pos - 1];
		Sub->length = len;

		return OK;
	}
}

//����Str������������֣�HeadStrΪ��һ������֮ǰ���Ӵ���StrΪ���ź���Ӵ�
void DistributeString(SString *Str,SString *HeadStr)
{
	int i, len, k;
	SString ch, ch1, ch2, ch3;
	len = StrLength(*Str);
	StrAssign(&ch1, ",");
	StrAssign(&ch2, "(");
	StrAssign(&ch3, ")");
	SubString(&ch, *Str, 1, 1);//ch����Str�ĵ�һ���ַ�

	for (i = 0, k = 0; i <= len && StrCompare(ch, ch1) || k != 0; ++i)
	{//����str�������ĵ�һ������
		SubString(&ch, *Str, i, 1);
		if (!StrCompare(ch, ch2))
			k++;
		else if (!StrCompare(ch, ch3))
			k--;
	}

	if (i <= len)
	{
		SubString(HeadStr, *Str, 1, i - 2);
		SubString(Str, *Str, i, len - i + 1);
	}
	else//ֻ����һ���Ӵ�
	{
		StrCopy(HeadStr, *Str);
		StrClear(Str);
	}
}

//���������
void CreateList(GList *L,SString S)
{
	SString Sub, HeadSub, Empty;
	GList p, q;
	StrAssign(&Empty, "()");

	if (!StrCompare(S, Empty))
		*L = NULL;//��������ǿմ����򴴽�һ���յĹ����
	else
	{
		if (!(*L = (GList)malloc(sizeof(GLNode))))
		{
			printf("�ڴ����ʧ��!\n");
			exit(OVERFLOW);
		}
		if (StrLength(S) == 1)
		{//ԭ�����͹����
			(*L)->atom = S.str[0];
			(*L)->tag = ATOM;
		}
		else
		{
			(*L)->tag = LIST;
			p = *L;
			SubString(&Sub, S, 2, StrLength(S) - 2);//ȥ���������
			do {
				DistributeString(&Sub, &HeadSub);//��Sub�������ͷ�ͱ�β
				CreateList(&(p->ptr.hp), HeadSub);
				q = p;
				if (!StrEmpty(Sub))
				{
					if (!(p = (GLNode *)malloc(sizeof(GLNode)))) {
						printf("�ڴ����ʧ��!\n");
						exit(OVERFLOW);
					}
					p->tag = LIST;
					q->ptr.tp = p;
				}
			} while (!StrEmpty(Sub));

			q->ptr.tp = NULL;
		}//else else
	}//else
}

//��������Ĵ���ʾ��ʽ
void PrintList(GList L)
{
	if (!L)
	{
		printf("()");
	}
	else
	{
		if (L->tag == ATOM)
		{
			printf("%c",L->atom);
		}
		else
		{
			printf("(");
			GLNode *p = L;
			while (p)
			{
				PrintList(p->ptr.hp);
				p = p->ptr.tp;
				if (p)
					printf(",");
			}//while
			printf(")");
		}//else else
	}//else 
}

//��ȡ�����ı�ͷ�ڵ�
Status GetHead(GList L)
{
	if (L == NULL)
	{
		printf("�����Ϊ��!\n");
		return ERROR;
	}
	GLNode *Head = L->ptr.hp;
	if (Head->tag == ATOM)
	{
		printf("��ͷ:%c\n",Head->atom);
	}
	else
	{
		printf("��ͷ:");
		PrintList(Head);
		printf("\n");
	}

	return OK;
}

//��ȡ��β�ڵ�
Status GetTail(GList L)
{
	if (L == NULL)
	{
		printf("�ձ�!\n");
		return ERROR;
	}

	GLNode *tail = L->ptr.tp;
	printf("��β:");
	PrintList(tail);
	printf("\n");

	return OK;
}

//��������
Status GListLength(GList L)
{
	int length = 0;
	GLNode *p = L;
	if (p == NULL)
	{
		printf("�ձ�\n");
		return ERROR;
	}
	else
	{
		length = GListLength(p->ptr.tp);
	}

	return length + 1;
}

//����������
Status GListDepth(GList L)
{
	int max,depth;
	GLNode *p;
	if (!L)
		return 1;
	if (L->tag == ATOM)
		return 0;
	for (max = 0, p = L; p; p = p->ptr.tp)
	{
		depth = GListDepth(p->ptr.hp);
		if (max < depth)
			max = depth;
	}

	return max + 1;
}

//��ֵ�����
Status CopyGList(GList *T, GList L)
{
	if (!L)
		*T = NULL;
	else
	{
		*T = (GList)malloc(sizeof(GLNode));
		if (*T == NULL)
		{
			printf("�ڴ����ʧ��!\n");
			exit(OVERFLOW);
		}
		(*T)->tag = L->tag;
		if (L->tag == ATOM)
			(*T)->atom = L->atom;
		else
		{
			CopyGList(&((*T)->ptr.hp), L->ptr.hp);
			CopyGList(&((*T)->ptr.tp), L->ptr.tp);
		}
	}

	return OK;
}

//������ԭ�ӽڵ����Ŀ
int CountAtom(GList L)
{
	int n1, n2;
	if (L == NULL)
		return ERROR;
	if (L->tag == ATOM)
		return 1;
	n1 = CountAtom(L->ptr.hp);
	n2 = CountAtom(L->ptr.tp);
	return n1 + n2;
}

int main()
{
	GList L, T;
	SString S;
	char str[60];

	printf("����������\n");
	cin >> str;
	StrAssign(&S,str);
	CreateList(&L, S);

	printf("���������е�Ԫ����:");
	PrintList(L);
	printf("\n");
	GetHead(L);
	GetTail(L);

	printf("��ĳ���Ϊ:%d\n",GListLength(L));
	printf("������Ϊ:%d\n", GListDepth(L));
	CopyGList(&T, L);
	printf("���������е�Ԫ����:");
	PrintList(T);
	printf("����������ԭ�ӽڵ����:%d\n",CountAtom(L));

    return 0;
}

