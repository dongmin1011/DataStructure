#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct element{
	int num;
	char name[20];
	int kor, math, eng, com;
}element;

typedef struct DListNode{
	element data;
	struct DListNode *llink;	//���ʸ���Ʈ
	struct DListNode *rlink;	//�����ʸ���Ʈ


}DListNode;

void init(DListNode *phead){
	phead->llink=phead;
	phead->rlink = phead;
}
void dinsert_node(DListNode *before, DListNode *new_node){
	//before->aaa
	//before->new_node->aaa
	new_node->llink = before;
	new_node->rlink = before->rlink;
	before->rlink->llink = new_node;
	before ->rlink = new_node;
}
void display(DListNode *phead){
	DListNode *p;

	for( p = phead->rlink; p!=phead; p=p->rlink){
		printf("��%6d�� %10s�� %6d�� %6d�� %6d�� %6d�� \n",
			p->data.num, p->data.name, p->data.kor, p->data.math, p->data.eng, p->data.com);
	}
	printf("��������������������������������������������������������������������������������������������������������\n");
}
void sort_dinsert(DListNode *head){
	DListNode *p, *q;
	element tmp;

	for(p=head->llink; p!=head; p=p->llink){
		for(q=p; q!=head; q=q->llink){
			if(p->data.num < q->data.num){
				tmp = p->data;
				p->data = q->data;
				q->data = tmp;			
			} 
		}
	}
}
void subject(){
	printf("��������������������������������������������������������������������������������������������������������\n");
	printf("��  ��ȣ��    �̸�   ��   ���   ���Ц�   ��� ��ǻ�ͦ�\n");
	printf("��������������������������������������������������������������������������������������������������������\n");
}
void search(DListNode *head, int num){
	DListNode *p;
	int mid=0;

	for(p=head->llink; p!=head; p=p->llink){
		if(p->data.num == num){
			subject();
			printf("��%6d�� %10s�� %6d�� %6d�� %6d�� %6d�� \n",
				p->data.num, p->data.name, p->data.kor, p->data.math, p->data.eng, p->data.com);
			printf("��������������������������������������������������������������������������������������������������������\n");
			return;
		}
	}
	printf("�л� ��ȣ�� �������� �ʽ��ϴ�.\n");
}

int main(){
	FILE *fp = NULL;
	DListNode head_node;
	DListNode *tmp;
	element data;
	int flag;
	int hak;
	init(&head_node);
	fp=fopen("data.txt","r");

	if(fp==NULL){
		printf("error\n");
		return 0;
	}
	while(!feof(fp)){
		fscanf(fp, "%d %s %d %d %d %d",
			&data.num, data.name, &data.kor, &data.math, &data.eng, &data.com);
		tmp = (DListNode *)malloc(sizeof(DListNode));
		tmp->data= data;
		dinsert_node(&head_node, tmp);
		
	}
	while(1){
		printf("����(0) �л� ������ �Է�(1) �л� �˻�(2) ��� ����(3) : ");
		scanf("%d", &flag);

		switch(flag){
		case 0:
			free(tmp);			//���� �޸� �Ҵ� ����
			exit(1);
			break;
		case 1:
			tmp = (DListNode *)malloc(sizeof(DListNode));
			printf("�߰��� �л���ȣ : ");
			scanf("%d", &data.num);
			while(1){
			printf("�̸� : ");
			scanf("%s", data.name);
				if(strlen(data.name)>8) printf("�̸��� �ִ� 4���� ���� �����մϴ�.\n");
				else break;
			}
			printf("���� ����: ");
			scanf("%d", &data.kor);
			printf("���� ����: ");
			scanf("%d", &data.math);
			printf("���� ����: ");
			scanf("%d", &data.eng);
			printf("��ǻ�� ����: ");
			scanf("%d", &data.com);
			tmp->data = data;
			dinsert_node(&head_node, tmp);
			break;
		case 2:
			printf("�˻��� �л���ȣ : ");
			scanf("%d",&hak);
			search(&head_node, hak);		
			break;
		case 3:
			sort_dinsert(&head_node);
			subject();
			display(&head_node);
			break;
		}
	}
	fclose(fp);
	return 0;
}
