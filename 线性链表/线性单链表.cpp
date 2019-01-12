// ��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList,*Position,*pNode;

//�����ڵ�
Status MakeNode(LinkList *Node, ElemType e)
{
	*Node = (LinkList)malloc(1 * sizeof(LNode));

	if (!Node)
	{
		//�ڴ����ʧ�ܣ�
		exit(OVERFLOW);
	}

	(*Node)->data = e;

	return OK;
}

//ɾ��Node��ָ��Ľڵ�
Status FreeNode(pNode p)
{
	free(p);

	return OK;
}

//��ʼ����������
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(1 * sizeof(LNode));

	if (!(*L))
		return ERROR;
	return OK;
}

//������������
Status ClearList(LinkList *L,ElemType e)
{
	if (!(*L))
	{
		printf("��������Ϊ�գ�");
		return ERROR;
	}

	LinkList p, q;
	p = *L;

	while (p)
	{
		p->data = e;
		p = p->next;
	}

	return OK;
}

//����ͷ���ָ��
Position GetHead(LinkList L)
{
	if (!L)
	{
		printf("��������!\n");
		return ERROR;
	}
	
	return L->next;
}

//����β���λ��
Position GetLast(LinkList L)
{
	if (!L)
	{
		printf("��������!\n");
		return ERROR;
	}

	Position p = NULL;
	for (p = L->next; p && p->next; p = p->next);

	return p;
}

//��h��ָ���ͷ���֮ǰ����s��ָ��Ľڵ�
Status InsFirst(LinkList *L, pNode s)
{
	Position Head = GetHead(*L);

	s->next = Head;
	
	(*L)->next = s;
	/*1 10 2 3
	s->next = Head->next;
	Head->next = s;*/
	
	return OK;
}

//ɾ��hָ���ͷ��㣬�ڵ�λ�÷��ص�qָ��
Status DelFirst(LinkList *L, pNode *q)
{
	Position Head = GetHead(*L);

	(*L)->next = Head->next;
	*q = Head;
	pNode p = (pNode)malloc(1 * sizeof(LNode));
	*p = *Head;
	FreeNode(p);

	return OK;
}

//��ָ��s��ָ��һ���ڵ�������L�����
Status Append(LinkList *L, pNode s)
{
	Position Tail = GetLast(*L);

	Tail->next = s->next;

	return OK;
}

//ɾ��β�ڵ�,����q����
Status Remove(LinkList *L, LNode *q)
{
	if (!L)
	{
		printf("��������!\n");
		return ERROR;
	}

	Position Tail = GetLast(*L);
	pNode p = *L;

	while (p && p->next != Tail)
	{
		p = p->next;
	}

	p->next = NULL;
	*q = *Tail;
	FreeNode(Tail);

	return OK;
}

//��֪pָ�������е�һ���ڵ㣬��s��ָ��Ľڵ������p��ָ�ڵ�֮ǰ
Status InsBefore(LinkList *L, pNode p, pNode s)
{
	pNode q = (*L)->next;
	
	while (q && q->next != p)
	{
		q = q->next;
	}
	s = q->next;
	q->next = s;

	return OK;
}

//��֪Pָ�������е�һ���ڵ㣬��sָ��Ľڵ��������ָ�ڵ�֮��
Status InsAfter(LinkList *L, pNode p, pNode s)
{
	s->next = p->next;
	p->next = s;

	return OK;
}

//������������
Status DestoryList(LinkList *L)
{
	if (!(*L))
		return ERROR;

	LinkList p, q;

	p = (*L)->next;

	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}

	(*L)->next = NULL;

	return OK;
}

//��λ������n��Ԫ�ص�ֵ��������ͷ�ڵ�ĵ������Ա���ͷ��㣩
Status CreateList_n(LinkList *L, int n)
{
	int i;
	LinkList p;

	*L = (LinkList)malloc( 1 * sizeof(LNode));
	if (!L)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(OVERFLOW);
	}
	(*L)->next = NULL;

	printf("�����������ݣ�\n");
	while(n--)
	{
		p = (LinkList)malloc(1 * sizeof(LNode));
		if (!p)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			exit(OVERFLOW);
		}
		scanf_s("%d",&p->data);

		p->next = (*L)->next;
		(*L)->next = p;
	}

	return OK;
}

//��λ�򴴽����Ե�����(��ͷ���)
Status CreateList_p(LinkList *L, int n)
{
	//L�������ͷָ��
	LinkList p = NULL, q = NULL;
	InitList(L);
	if (!L)
	{
		exit(OVERFLOW);
	}
	(*L)->next = NULL;
	q = *L;//ָ��ǰ�ڵ�
	ElemType e;
	for (int i = n; i>0; i--)
	{
		scanf_s("%d",&e);
		MakeNode(&p, e);
		
		q->next = p;//����Ϊq = p��Ϊ��ͷ��������
		q = q->next;
	}
	p->next = NULL;

	return OK;
}

//����������
int ListLength(LinkList L)
{
	int sum = 0;

	LinkList p = L->next;
	while (p)
	{
		sum++;
		p = p->next;
	}

	return sum;
}

//��ȡ��i���ڵ����ֵ�ֵ������e
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L;
	int j = 0;

	while (p && j < i)
	{
		p = p->next;
		j++;
	}

	if (!p || j > i)
		return ERROR;

	*e = p->data;

	return OK;
}

//���������
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList p = *L;
	int j = 0;
	while (p && j < i - 1)
	{
		p = p->next;
		j++;
	}

	if (!p || j > i - 1)
		return  ERROR;
	LinkList s = (LinkList)malloc(1 * sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}

//������ɾ��
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList p = *L;
	int j = 0;

	while (p->next && j < i - 1)
	{
		p = p->next;
		++j;
	}

	if (!(p->next) || j > i - 1)
		return ERROR;

	LinkList q = (LinkList)malloc(1 * sizeof(LNode));
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);

	return OK;
}

//��e���½ڵ���ָ��Ľڵ����ֵ,һֱp�����������е�һ�����
Status SetCurElem(LNode *p, ElemType e)
{
	p->data = e;

	return OK;
}

//���ڵ��ڹ�ϵ
Status compare(ElemType a, ElemType b)
{
	if (a >= b)
		return OK;
	else
		return ERROR;
}

//����������L�е�һ����e����compare��ϵ��Ԫ�ص�λ��
Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType a, ElemType b))
{
	Position  p = L->next;

	while (p)
	{
		if (compare(p->data, e))
			break;
		p = p->next;
	}

	if (p == NULL)
		return NULL;

	return p;
}

//���� Pָ��������е�i��λ�õĽڵ㣬������OK,���iֵ���Ϸ�������ERROR
Status LocatePos(LinkList L, int i, LNode *p)
{
	if (i >= ListLength(L) || i == 0)
	{
		printf("���������أ�\n");
		return ERROR;
	}

	int j = 0;

	LNode* q = L->next;
	while (j < i)
	{
		q = q->next;
		j++;
	}

	*p = *q;

	return OK;
}

//��֪pָ�����Ա��е�һ����㣬����ǰ�����
Position PriorPos(LinkList L, pNode p)
{
	Position Head = GetHead(L);
	if (p == Head)
	{
		printf("û��ǰ����\n");
		return NULL;
	}
	pNode q = Head;

	while (q->next != p)
	{
		q = q->next;
	}

	return q;
}

//��֪pָ�������һ���ڵ㣬����p��ָ���ֱ�Ӻ�̵�λ��
Position NextPos(LinkList L, pNode p)
{
	Position Tail = GetLast(L);

	if (p == Tail)
	{
		printf("ֱ�Ӻ�̲�����!\n");
		return NULL;
	}

	return p->next;
}

//�ж������Ƿ�Ϊ��
Status ListEmpty(LinkList L)
{
	if (ListLength(L) == 0)
	{
		return OK;
	}
	return ERROR;
}

//���ʺ���
Status visit(ElemType e)
{
	printf("%d ",e);

	return OK;
}

//��������,����visit����
Status ListTraverse(LinkList L,Status(*visit)(ElemType e))
{
	if (!L)
	{
		printf("��������!\n");
		return ERROR;
	}
	if (ListEmpty(L))
	{
		printf("������\n");
		return ERROR;
	}

	LinkList p = L->next;

	while (p)
	{
		if (!visit(p->data))
		{
			return ERROR;
		}
		p = p->next;
	}

	printf("\n");
	return OK;
}

//���ĳ��ȷ���ڵ��ֵ
Status ShowData(LinkList L,int i)
{
	if (i <= 0)
		return FALSE;
	int j;

	for (j = 0; j < i; ++j)
	{
		L = L->next;
	}

	printf("%d ",L->data);
	return OK;
}

//��������ȥ�غϳ�
void MergeList(LinkList *La, LinkList *Lb, LinkList *Lc)
{
	//��֪�������Ա�La,Lb��Ԫ�ذ�ֵ�ǵݼ���˳������
	//�鲢La��Lb�õ��µĵ������Ա�Lc,Lc��Ԫ��Ҳ����ֵ�ݼ���˳������
	LinkList pa = (*La)->next;
	LinkList pb = (*Lb)->next;
	Lc = La;
	LinkList pc = *La;

	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pc->next; 
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	pc->next = pa ? pa : pb;
	free(Lb);
}

int main()
{
	LinkList List = NULL;
	int i,m,len;
/*
	LinkList list = NULL;

	CreateList_n(&list, 3);
	printf("�����������\n");
	for(i = 0;i < 3;++i)
		ShowData(list, i+1);
*/
	printf("����������\n");
	scanf_s("%d",&len);
	printf("�������������ֵ��\n");
	CreateList_p(&List,len);
	
	printf("��������\n");
	ListTraverse(List,visit);

	
/*
	Position next = NextPos(List,GetHead(List));
	printf("�׽ڵ��ֱ�Ӻ����:\n");
	printf("%d\n",next->data);

	Position pre = PriorPos(List, GetLast(List));
	printf("β����ǰ����:\n");
	printf("%d\n",pre->data);

	LNode tail;
	Remove(&List, &tail);
	printf("ɾ����Ԫ����:%d",tail.data);
	printf("\n");

	printf("��������\n");
	ListTraverse(List, visit);

	LinkList s = NULL;
	printf("��������������:\n");
	scanf_s("%d",&len);
	printf("���������ǣ�\n");
	CreateList_p(&s, len);
	Append(&List, s);

	printf("��������\n");
	ListTraverse(List, visit);

	LNode anew;
	anew.data = 10;
	anew.next = NULL;

	InsFirst(&List, &anew);
	printf("��������\n");
	ListTraverse(List, visit);
	pNode del;
	DelFirst(&List, &del);
	printf("��������\n");
	ListTraverse(List, visit);

	Position tail = GetLast(List);
	printf("β�ڵ��ֵΪ:%d\n",tail->data);
	
	LNode p;
	LocatePos(List, 2, &p);
	printf("��2λ�����ǣ�\n%d",p.data);

	ElemType pos_data;
	printf("�����ж����ݣ�\n");
	scanf_s("%d", &pos_data);
	Position pos = LocateElem(List, pos_data, compare);
	if (pos)
		printf("%d\n", pos->data);
	else
		printf("���ݲ�����\n");

	printf("˳���������\n");
	for (i = 0; i < len; ++i)
		ShowData(List, i + 1);
	printf("\n�����ȣ�%d",ListLength(List));
	ClearList(&List, 0);
	printf("\n������飺\n");
	for (i = 0; i < 3; ++i)
		ShowData(List, i + 1);

	ListDelete(&List, 2, &m);
	printf("\nɾ����Ԫ���ǣ�%d\n",m);
	printf("ɾ��������\n");
	for (i = 0; i < 2; ++i)
		ShowData(List, i + 1);
	GetElem(List,2,&m);
	printf("%d\n",m);
	ListInsert(&List, 2, 2);
	printf("\n���������\n");
	for (i = 0; i < 4; ++i)
		ShowData(List, i + 1);
*/

	return 0;
}