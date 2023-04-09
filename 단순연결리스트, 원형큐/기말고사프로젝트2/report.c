/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а� 
	�̸� : �赿�� 
	���α׷��� : ���� ť�� �̿��� ���� �б� ���α׷�
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_QUEUE_SIZE 100							//ť ������ 100
typedef struct{
	char *name;										//�̸� ���� ����������
	int num;										//�й�����
	int kor, eng, math;								//���� ���� ����
}element;
typedef struct{
	element data[MAX_QUEUE_SIZE];					//ť ����ü �迭
	int front, rear;								//ť�� ��ġ��
}QueueType;

void error(char *message);							//�����޽��� ����Լ�
void init(QueueType *q);							//ť �ʱ�ȭ �Լ�
int is_empty(QueueType *q);							//ť ������� Ȯ���Լ�
int is_full(QueueType *q);							//ť ��ȭ���� Ȯ���Լ�
void queue_print(QueueType *q);						//ť ����Լ�
void enqueue(QueueType *q, element item);			//ť�� �����ϴ� enqueue�Լ�
element dequeue(QueueType *q);						//ť�� �����ϴ� dequeue�Լ�
void input(FILE *fp,  QueueType*q);					//enqueue�� �ʿ��� �Լ��� ����
void output(QueueType *q);							//dequeue�� �ʿ��� �Լ��� ����
	
int main(){
	char str[20];
	QueueType q;
	FILE *fp;
	fp=fopen("data.txt", "r");						//data.txt�� �б��������� open
	if(fp==NULL){
		printf("������ ������ �ʽ��ϴ�.\n");
		return 0;
	}
	init(&q);
	while(!feof(fp)){
		fscanf(fp, "%s", str);						//str�� enqueue�Ǵ� dequeue
		if(strcmp(str,"enqueue")==0){				//���� str�� enqueue��� 0����
			input(fp,  &q);							//enqueue�Ҷ� �ʿ��� input�Լ� ȣ��
		}
		else if(strcmp(str, "dequeue")==0){			//���� str�� dequeue��� 0����
			output(&q);								//dequeue�Ҷ� �ʿ��� output�Լ� ȣ��
		}
		else{
			error("enqueue �Ǵ� dequeue�� �ƴմϴ�.\n");		//�߸��� �Է��̹Ƿ� �����޽��� ����� ��������
		}
		queue_print(&q);
	}
	fclose(fp);
}
void error(char *message){							//�����޽��� ����Լ�
	fprintf(stderr, "%s\n", message);				//stderr�� �̿��Ͽ� ���۾��� ��� ���
	exit(1);
}
void init(QueueType *q){							//ť �ʱ�ȭ �Լ�
	q->front = q->rear = 0;							//����ť�̹Ƿ� front�� rear���� 0���� ����
}
int is_empty(QueueType *q){							//ť ������� Ȯ�� �Լ�
	return (q->front == q->rear);					//front�� rear�� ���ٸ� ť�� ����ִ� �����̹Ƿ� ���ٸ� 1���� �ٸ��ٸ� 0����
}
int is_full(QueueType *q){							//ť ��ȭ���� Ȯ���Լ�
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);	//rear�� 1�� ���ϰ� modulo���� ���� �� �� ���� front�� ���ٸ� ��ȭ����
}
void queue_print(QueueType *q){						//ť�� ����ϴ� �Լ�
	int i = q->front;								//i���� front������ ����
	printf("QUEUE(front=%d rear=%d)\n", q->front, q->rear);	//���� front�� rear�� ���
	if(!is_empty(q)){
		do{											//do while���� �̿��Ͽ� �ѹ��� �ݵ�� ����ϵ��� ����
			i = (i+1) % MAX_QUEUE_SIZE;						//����ť�̹Ƿ� i�� ť�� ũ��� ���������� ����
			printf("%s | %d | %d | %d | %d |\n", q->data[i].name, q->data[i].num, q->data[i].kor,
				q->data[i].eng, q->data[i].math);		//ť ���
			if(i==q->rear)break;					//���� i�� rear���� ���ٸ� ť�� ������ �������Ƿ� ����
		}while(i!=q->front);						//i�� front���� �������ٸ� ����
	}
	printf("\n");
}
void enqueue(QueueType *q, element item){			//ť�� �����ϴ� �Լ�
	if(is_full(q))									//ť�� ��ȭ�������� Ȯ��
		error("ť�� ��ȭ�����Դϴ�.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;		//����ť�̹Ƿ� rear�� 1�� ���ϰ� ������ ���������
	q->data[q->rear] = item;						//rear��ġ�� item�� ����
}
element dequeue(QueueType *q){						//ť�� �����ϴ� �Լ�
	if(is_empty(q))									//ť�� ������¶�� ť�� ������ �� �����Ƿ� ����
		error("ť�� ��������Դϴ�.\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;		//dequeue�Ҷ� front���� �̵��ϹǷ� front�� ������ ����
	return q->data[q->front];						//front��ġ�� �ִ� data�� ����
}
void input(FILE *fp,  QueueType*q){					//data���Ͽ��� enqueue�� �ԷµǾ��� �� �����ϴ� �Լ�
	char s[20];
	element data;			
	fscanf(fp, "%s%d%d%d%d", s, &data.num, &data.kor, &data.eng, &data.math);	//���Ϸκ��� enqueue�ڿ� �ִ� �������� �о��
	data.name=(char *)malloc(strlen(s)+1);										//data����ü�� �ִ� name�� �������̹Ƿ� �����Ҵ� ����(�Է¹��� s�� ���̿� \0���� �����Ͽ� +1)
	strcpy(data.name, s);														//strcpy�Լ��� �̿��Ͽ� ���� ����
	enqueue(q, data);															//enqueue����
}
void output(QueueType *q){							//data���Ͽ��� dequeue�� �ԷµǾ��� �� �����ϴ� �Լ�
	element data;
	data = dequeue(q);								//���Ϲ��� data���� �޾ƿ�
	printf("������ ������: %s %d %d %d %d\n", data.name, data.num, data.kor, data.eng, data.math);	//������ ������ ���
	free(data.name);								//name�� �����Ҵ�� �����̹Ƿ� free����
}	
