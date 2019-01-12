// 广义表.cpp : 定义控制台应用程序的入口点。
//以字符串形式

#include "stdafx.h"
# include<iostream>

using namespace std;

typedef struct
{
	AtomType str[MaxLength];
	Status length;
}SString;//自定义字符串

typedef enum {ATOM,LIST}ElemTag;//ATOM=0表示原子，List=1表示子表
typedef struct GLNode
{
	ElemTag tag;//标志tag用于区分元素是原子还是子表
	union
	{
		AtomType atom;//原子结点的值域，用户自己定义的类型
		struct {
			struct GLNode *hp, *tp;//hp指向表头，tp指向表尾
		}ptr;
	};
}*GList,GLNode;

//判断是否为空字符串
Status StrEmpty(SString S)
{
	if (S.length == 0)
		return OK;
	else
		return ERROR;
}

//求串长度
Status StrLength(SString S)
{
	return S.length;
}

//串比较
Status StrCompare(SString S, SString T)
{
	int i;

	for (i = 0; i < S.length && i < T.length; ++i)
	{
		if (S.str[i] != T.str[i])
			return S.str[i] - T.str[i];//返回第一个比较不同字符的大小
	}

	return S.length - T.length;//比较结束，返回两个串差值
}

//清空串
void StrClear(SString *S)
{
	S->length = 0;
}

//串的赋值操作
void StrCopy(SString *T, SString S)
{
	int i;
	for (i = 0; i < S.length; ++i)
	{
		T->str[i] = S.str[i];
	}

	T->length = S.length;
}

//串赋值
void StrAssign(SString *S, char str[])
{
	int i;
	for (i = 0; str[i] != '\0'; ++i)
		S->str[i] = str[i];
	S->length = i;
}

//截取从pos开始的长度为len的子串
Status SubString(SString *Sub,SString S,int pos,int len)
{
	int i;

	if (pos < 0 || len < 0 || pos + len - 1 > S.length)
	{
		printf("参数不合法!\n");
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

//将串Str分离成两个部分，HeadStr为第一个逗号之前的子串，Str为逗号后的子串
void DistributeString(SString *Str,SString *HeadStr)
{
	int i, len, k;
	SString ch, ch1, ch2, ch3;
	len = StrLength(*Str);
	StrAssign(&ch1, ",");
	StrAssign(&ch2, "(");
	StrAssign(&ch3, ")");
	SubString(&ch, *Str, 1, 1);//ch保存Str的第一个字符

	for (i = 0, k = 0; i <= len && StrCompare(ch, ch1) || k != 0; ++i)
	{//搜索str的最外层的第一个括号
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
	else//只包含一个子串
	{
		StrCopy(HeadStr, *Str);
		StrClear(Str);
	}
}

//创建广义表
void CreateList(GList *L,SString S)
{
	SString Sub, HeadSub, Empty;
	GList p, q;
	StrAssign(&Empty, "()");

	if (!StrCompare(S, Empty))
		*L = NULL;//如果输入是空串，则创建一个空的广义表
	else
	{
		if (!(*L = (GList)malloc(sizeof(GLNode))))
		{
			printf("内存分配失败!\n");
			exit(OVERFLOW);
		}
		if (StrLength(S) == 1)
		{//原子类型广义表
			(*L)->atom = S.str[0];
			(*L)->tag = ATOM;
		}
		else
		{
			(*L)->tag = LIST;
			p = *L;
			SubString(&Sub, S, 2, StrLength(S) - 2);//去除外层括号
			do {
				DistributeString(&Sub, &HeadSub);//将Sub分离出表头和表尾
				CreateList(&(p->ptr.hp), HeadSub);
				q = p;
				if (!StrEmpty(Sub))
				{
					if (!(p = (GLNode *)malloc(sizeof(GLNode)))) {
						printf("内存分配失败!\n");
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

//输出广义表的串表示形式
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

//获取广义表的表头节点
Status GetHead(GList L)
{
	if (L == NULL)
	{
		printf("广义表为空!\n");
		return ERROR;
	}
	GLNode *Head = L->ptr.hp;
	if (Head->tag == ATOM)
	{
		printf("表头:%c\n",Head->atom);
	}
	else
	{
		printf("表头:");
		PrintList(Head);
		printf("\n");
	}

	return OK;
}

//获取表尾节点
Status GetTail(GList L)
{
	if (L == NULL)
	{
		printf("空表!\n");
		return ERROR;
	}

	GLNode *tail = L->ptr.tp;
	printf("表尾:");
	PrintList(tail);
	printf("\n");

	return OK;
}

//求广义表长度
Status GListLength(GList L)
{
	int length = 0;
	GLNode *p = L;
	if (p == NULL)
	{
		printf("空表\n");
		return ERROR;
	}
	else
	{
		length = GListLength(p->ptr.tp);
	}

	return length + 1;
}

//求广义表的深度
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

//赋值广义表
Status CopyGList(GList *T, GList L)
{
	if (!L)
		*T = NULL;
	else
	{
		*T = (GList)malloc(sizeof(GLNode));
		if (*T == NULL)
		{
			printf("内存分配失败!\n");
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

//求广义表原子节点的数目
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

	printf("请输入广义表：\n");
	cin >> str;
	StrAssign(&S,str);
	CreateList(&L, S);

	printf("输出广义表中的元素是:");
	PrintList(L);
	printf("\n");
	GetHead(L);
	GetTail(L);

	printf("表的长度为:%d\n",GListLength(L));
	printf("表的深度为:%d\n", GListDepth(L));
	CopyGList(&T, L);
	printf("输出广义表中的元素是:");
	PrintList(T);
	printf("输出广义表中原子节点个数:%d\n",CountAtom(L));

    return 0;
}

