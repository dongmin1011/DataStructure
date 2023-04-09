/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а� 
	�̸� : �赿�� 
	���α׷��� : �ܼ����Ḯ��Ʈ�� ���� ���α׷�
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct{
	int coef;									//��
	int expon;									//����
}element;
typedef struct ListNode{
	element data;								//�ذ� ���� ����ü
	struct ListNode *link;				
}ListNode;
typedef struct ListType{
	int size;
	ListNode *head;								//ó���� ����Ű�� head������
	ListNode *tail;								//���� ����Ű�� tail������
}ListType;

void error(char *message);												//�����޽��� ��� �Լ�
ListType* create();														//���Ḯ��Ʈ ���� �Լ�
void insert_last(ListType* plist, int coef, int expon);					//����Ʈ�� �������� ����Ʈ�� �߰��ϴ� �Լ�
void poly_print(ListType *plist, const char* formula);					//���׽��� ����ϴ� �Լ�
void sort(ListType *plist);												//���׽��� �������� �����ϴ� �Լ�
void delete_zero(ListType* plist);										//���� ��꿡�� ���� 0�϶��� ����Ʈ�� �����ϴ� �Լ�
void poly_mul(ListType* plist1, ListType* plist2, ListType* plist3);	//������� �Լ�
void get_result(char *result, char*poly1, char *poly2);					//��� ���׽��� �̸��� �����ϴ� �Լ�

int main(){
	FILE *fp;
	ListType *list1, *list2, *list3;
	int tmp1, tmp2;
	char ch;
	char poly1[20], poly2[20], result[20];

	list1 = create();												//���׽�1����
	list2 = create();												//���׽�2����
	list3 = create();												//���׽�3����

	fp=fopen("data.txt", "r");										//data�� �б� �������� ����
	if(fp==NULL){
		error("������ ������ �ʽ��ϴ�.\n");
	}
	fscanf(fp, "%s", poly1);										//data�κ��� ���׽� 1�� �̸� ����
	while(!feof(fp)){
		fscanf(fp, "%d%d", &tmp1, &tmp2);						//data�κ��� �ӽú���1,2�� ���� �޾ƿ�
		fscanf(fp, "%c", &ch);							//���� ch�� ���鹮���̸� ��� �Է��� �޴´ٴ� ��ȣ�̰� �ٹٲ� �����̸� ���׽� �Է��� �����ٴ� �ǹ�
		insert_last(list1, tmp1, tmp2);				//tmp1���� tmp2���� ù��° ���׽� ����Ʈ�� ����
		if(ch == '\n')break;						//ch�� �ٹٲ� �����̸� �ݺ��� ����
	}
	fscanf(fp, "%s", poly2);						//data�κ��� ���׽� 2�� �̸� ����
	while(!feof(fp)){
		fscanf(fp, "%d%d", &tmp1, &tmp2);
		fscanf(fp, "%c", &ch);
		insert_last(list2, tmp1, tmp2);
		if(ch == '\n')break;
	}
	poly_mul(list1, list2, list3);					//���׽��� ���� �Լ�
	get_result(result, poly1, poly2);				//poly1�� poly2�� ���Ͽ� result���ڿ��� �����ϴ� �Լ�

	poly_print(list1,  poly1);						//list1���׽� ��� ���׽��� �̸��� poly1�� ����
	poly_print(list2,  poly2);						//list2���׽� ��� ���׽��� �̸��� poly2�� ����
	poly_print(list3, result);						//list3���׽� ��� ���׽��� �̸��� result�� ����
	
	free(list1); free(list2); free(list3);
	fclose(fp); return 0;
}
void error(char *message){										//�����޽��� ����Լ�
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListType* create(){												//����Ʈ ��� ���� �Լ�
	ListType *plist= (ListType*) malloc(sizeof(ListType));		//ListType�� �����Ҵ� ����
	plist->size = 0;											
	plist->head = plist->tail = NULL;							//����Ʈ�� ������� ���� ���� NULL�� ����
	return plist;												//�����Ҵ��� ���� ����
}
void insert_last(ListType* plist, int coef, int expon){			//����Ʈ�� �� ���� �����ϴ� �Լ�
	ListNode *temp = (ListNode*) malloc(sizeof(ListNode));		//����Ʈ ��� �����Ҵ�
	if(temp==NULL) error("�޸� �Ҵ� ����");
	temp->data.coef = coef;										//temp�� �� ����
	temp->data.expon = expon;
	temp->link = NULL;
	if(plist->tail == NULL)										//���� tail�� NULL�̶�� ���� ó�� ���� ��Ÿ��.
		plist->head = plist->tail = temp;						//����Ʈ�� ���� ���Ͽ� temp�� ����
	else{
		plist->tail->link = temp;								//���� ó�� ���� �ƴ϶��
		plist->tail = temp;										//tail�� temp����
	}
	plist->size++;
}

void poly_print(ListType *plist, const char* formula){			//���׽��� ����ϴ� �Լ� �Ű������� ���Ḯ��Ʈ�� ����� ����Ű�� �����Ϳ� ���׽��� �̸�
	ListNode *p = plist->head;

	printf("%s = ", formula);									//���׽��� �̸� ���
	for(; p; p = p->link){
		if(p->data.coef>0){										//���� ���� ���� 0�̻��̸� �����
			if(p!=plist->head) printf(" + ");					//���� p�� head���� ���ٸ� ���� ù ������ ���ϹǷ� head���� �ٸ����� +���
			if(p->data.expon==0)								//����(expon)���� 0�̶�� ������� ��Ÿ���Ƿ� �ظ� ���
				printf("%d", p->data.coef);
			else 
				printf("%dX^%d", p->data.coef, p->data.expon);	//������ 0�� �ƴ϶�� ��X^���� ���·� ���
		}
		else{													//���� ���� ����� �ƴϹǷ� �������� ��Ÿ��
			printf(" - ");										//���� p�� head���� ���ٸ� ���� ù ������ ���ϹǷ� head���� �ٸ����� -���
			if(p->data.expon==0)
				printf("%d", -p->data.coef);					//-�� ������ ����߰�, ��(coef)�� -�� �ٿ� ��������� ���, ������ 0�̹Ƿ� �ظ� ���
			else 
				printf("%dX^%d", -p->data.coef, p->data.expon); //��(coef)�� -�� �ٿ� ��������� ���, ������ 0�� �ƴϹǷ� -��X^���� ���·� ���
		}
		
	}
	printf("\n");
}
void sort(ListType *plist){									//���׽��� �����ϴ� �Լ�
	ListNode *p, *q;										//ListNode �ڷ������� 2���� �����ͺ��� ����
	element temp;											//�����Ҷ� ����ϴ� element�� �ӽ� ����
	for(p=plist->head; p!=NULL; p=p->link){
		for(q=p; q!=NULL; q=q->link){
			if(p->data.expon < q->data.expon){				//���� p�� �������� q�� �������� ũ�ٸ�
				temp = q->data;								//q�� ������ ���� �ӽú����� ����
				q->data = p->data;							//p�� ������ ���� q�� ������ ���� ����
				p->data = temp;								//temp�� ���� p�� ������ ���� ���� 
			}												//���� �Ϸ�
		}
	}
}
void delete_zero(ListType* plist){							//��� ���׽Ŀ��� ���� 0�϶��� �����ϴ� �Լ�
	ListNode *p = plist->head;
	ListNode *remove;										//������ ����Ʈ�� ���� ����
	while(p!=NULL){											//p�� null�� ���������� �ݺ�
		if(p->link->data.coef == 0){						//p�� ���� ����� ���� 0�̶�� ����
			remove = p->link;								//remove�� p�� ��ũ ����
			p->link = remove->link;							//p�� ��ũ�� remove�� ��ũ ����(p�� ������� �������)
			plist->size--;
			free(remove);									//remove����
		}	
		p = p->link;										//p�� �������� �̵�
		if(p->link == NULL)break;							//p�� ������尡 NULL�̶�� �ݺ� ����
	}
}
void poly_mul(ListType* plist1, ListType* plist2, ListType* plist3){									//���׽� ����Ʈ�� ���� �Լ�
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	ListNode* c;
	while(a!=NULL){
		b=plist2->head;																					//���� �ٱ��� �ݺ����� �������� b�� ���� head�� �ʱ�ȭ
		while(b!=NULL){
			c=plist3->head;																				//���� �ٱ��� �ݺ����� �������� c�� ���� head�� �ʱ�ȭ
			while(c!=NULL){
				if(c->data.expon == a->data.expon + b->data.expon){										//���� c�� �ݺ����� ���� ���� �������� �������� ������ �Ǹ�
					c->data.coef += a->data.coef * b->data.coef;										//���� ���������� ����ϰ� �ݺ� ����
					break;
				}
				c=c->link;																				//���� ���� �̵�
			}	
			if(c==NULL) insert_last(plist3, a->data.coef*b->data.coef, a->data.expon + b->data.expon);	//���� c�� NULL�̸� ���� �������� ������ ���� ��츦 ��Ÿ��																								//���� ������ ������ ���Ͽ����Ƿ� ����Ʈ�� �������� ����
			b = b->link;
		}
		a = a->link;
	}
	delete_zero(plist3);																				//��������� �ϸ� �߰��� ���� 0�̵Ǵ� ��찡 ����. �� �κ��� ����Ʈ���� �����ϴ� �Լ�
	sort(plist3);																						//������ ũ�⿡ ���� �������� �����ϴ� �Լ�
}
void get_result(char *result, char*poly1, char *poly2){						//������� �̸��� �����ϴ� �Լ�
	strcpy(result, poly1);													//result���ڹ迭�� poly1�� ���ڿ� ����
	strcat(result, " * ");													//result���ڿ��� * �߰� strcat�� 2���� ���ڿ��� ���̴� �Լ�
	strcat(result, poly2);													//result���ڿ��� poly2���ڿ� ���� 
}

