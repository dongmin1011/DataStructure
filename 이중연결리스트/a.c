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
	struct DListNode *llink;	//왼쪽리스트
	struct DListNode *rlink;	//오른쪽리스트


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
		printf("│%6d│ %10s│ %6d│ %6d│ %6d│ %6d│ \n",
			p->data.num, p->data.name, p->data.kor, p->data.math, p->data.eng, p->data.com);
	}
	printf("└──────┴───────────┴───────┴───────┴───────┴───────┘\n");
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
	printf("┌──────┬───────────┬───────┬───────┬───────┬───────┐\n");
	printf("│  번호│    이름   │   국어│   수학│   영어│ 컴퓨터│\n");
	printf("│──────┼───────────┼───────┼───────┼───────┼───────│\n");
}
void search(DListNode *head, int num){
	DListNode *p;
	int mid=0;

	for(p=head->llink; p!=head; p=p->llink){
		if(p->data.num == num){
			subject();
			printf("│%6d│ %10s│ %6d│ %6d│ %6d│ %6d│ \n",
				p->data.num, p->data.name, p->data.kor, p->data.math, p->data.eng, p->data.com);
			printf("└──────┴───────────┴───────┴───────┴───────┴───────┘\n");
			return;
		}
	}
	printf("학생 번호가 존재하지 않습니다.\n");
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
		printf("종료(0) 학생 데이터 입력(1) 학생 검색(2) 목록 보기(3) : ");
		scanf("%d", &flag);

		switch(flag){
		case 0:
			free(tmp);			//동적 메모리 할당 해제
			exit(1);
			break;
		case 1:
			tmp = (DListNode *)malloc(sizeof(DListNode));
			printf("추가할 학생번호 : ");
			scanf("%d", &data.num);
			while(1){
			printf("이름 : ");
			scanf("%s", data.name);
				if(strlen(data.name)>8) printf("이름은 최대 4글자 까지 가능합니다.\n");
				else break;
			}
			printf("국어 성적: ");
			scanf("%d", &data.kor);
			printf("수학 성적: ");
			scanf("%d", &data.math);
			printf("영어 성적: ");
			scanf("%d", &data.eng);
			printf("컴퓨터 성적: ");
			scanf("%d", &data.com);
			tmp->data = data;
			dinsert_node(&head_node, tmp);
			break;
		case 2:
			printf("검색할 학생번호 : ");
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
