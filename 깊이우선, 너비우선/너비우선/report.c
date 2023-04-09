/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: �׷��� �ʺ� �켱 Ž�� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
	int Qsize;					//ť�� ũ��
	int *queue;					//ť �迭
	int front, rear;			//ť�� ó���� ��
}QueueType;

void error(char*message) {		//���� ��� �Լ�
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void queue_init(QueueType *q, int num) {	//ť �ʱ�ȭ �Լ�
	q->Qsize = num;							//ť�� ũ�⿡ num����
	q->queue = (int*)malloc(sizeof(int)*num);	//ť�� num������ �����Ҵ�
	q->front = q->rear = 0;					//front�� rear�� 0���� ����
}
int is_empty(QueueType *q) {	//ť�� ������� Ȯ���ϴ� �Լ�
	return (q->front == q->rear);	//������ 1, �ٸ��� 0 ��ȯ
}
int is_full(QueueType *q) {		//ť�� ��� ���ִ��� Ȯ��
	return ((q->rear + 1) % q->Qsize == q->front);	//rear+1�� ť�� ũ��� modulo����
}
void enqueue(QueueType *q, int item) {		//ť�� �����ϴ� �Լ�
	if (is_full(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
	}
	q->rear = (q->rear + 1) % q->Qsize;		//rear+1�� modulo�����Ͽ� ����
	q->queue[q->rear] = item;
}
int dequeue(QueueType*q) {			//ť�� ���� ���� ��ȯ�ϴ� �Լ�
	if (is_empty(q))
		error("ť�� ��������Դϴ�.");
	q->front = (q->front + 1) % q->Qsize;	//front+1�� modulo�����Ͽ� ��ȯ
	return q->queue[q->front];
}

typedef struct {		//�׷��� ����ü ����
	int n;				//������ ����
	int **adj_mat;		//���������� ���
}GraphType;

int *visited;			//������ �湮�Ǿ����� Ȯ���ϴ� ����
	
void init(GraphType*g, int num);		//�׷����� �ʱ�ȭ�ϴ� �Լ�
void insert_vertex(GraphType*g, int num);	//���� �����Լ�
void insert_edge(GraphType* g, int start, int end);	//���������Լ�
void bfs_mat(GraphType*g, int v, int);		//�ʺ� �켱 Ž���Լ�
void Delete_Graph(GraphType*g);			//�׷��� ���� �Լ�

int main() {
	FILE *fp;
	int max = INT_MIN;			//max�� int�� ���� ���� �� ����
	char ctemp;					//���ڸ� �Է¹޴� �ӽú���
	int itemp1, itemp2, i;			//������ �Է¹޴� �ӽú���2��
	GraphType *g;				//�׷��� ����
	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {		//���ϳ����� �ݺ��ϸ� �ִ밪�� ã��
		fscanf(fp, "%c", &ctemp);
		if (ctemp == 'v') {	//v�� �Է¹޾��� �� ���� �ϳ� �� �Է¹���
			fscanf(fp, "%d", &itemp1);
			if (max < itemp1) max = itemp1;	//�Է¹��� ������ max���� Ŭ�� max�� ���� ����
		}
	}
	g = (GraphType*)malloc(sizeof(GraphType));
	max++;	
	init(g, max);					//max�� 1 ������Ű�� �׷��� �ʱ�ȭ
	for(i=0; i<max; i++){
		insert_vertex(g, max);		//�׷����� ������ ����
	}
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%c", &ctemp);
		if (ctemp == 'e') {	//e�� �Է¹޾��� �� ���� ����
			fscanf(fp, "%d%d", &itemp1, &itemp2);	//���� 2���� �Է¹ް�
			insert_edge(g, itemp1, itemp2);	//������ �׷����� ����
		}
	}
	printf("�ʺ� �켱 Ž�� : ");

	bfs_mat(g, 0, max);			//�ʺ� �켱 Ž�� �Լ� ȣ��
	Delete_Graph(g);		//�׷��� ���� �Լ�
	fclose(fp);			//���������� ����
	return 0;
}
void init(GraphType*g, int num) {			//�׷����� �ʱ�ȭ �ϴ� �Լ�
	int r;
	g->n = 0;
	g->adj_mat = (int**)calloc(sizeof(int*), num);	//calloc�� �̿��Ͽ� �� �ʱ�ȭ
	for (r = 0; r < num; r++) {
		g->adj_mat[r] = (int*)calloc(sizeof(int), num);	//calloc�� �̿��ؿ� �� �ʱ�ȭ
	}
	visited = (int*)calloc(sizeof(int), num);		//visited������ num���� �°� �ʱ�ȭ
}
void insert_vertex(GraphType*g, int num) {	//������ �����ϴ� �Լ�
	if ((g->n) + 1 > num) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;		//������ ���� ����
}
void insert_edge(GraphType* g, int start, int end) {//������ �׷����� ������ �����ϴ�  �Լ�
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;		//������ �׷����̱� ������ start�� end��
	g->adj_mat[end][start] = 1;		//end�� start�� �� �� ����
}
void bfs_mat(GraphType*g, int v, int num) {	//�ʺ� �켱 Ž�� �Լ�
	int w;
	QueueType q;					//ť ����

	queue_init(&q, num);			//ť �ʱ�ȭ
	visited[v] = TRUE;
	printf("%d ", v);
	enqueue(&q, v);			//ť�� ���� ���� ����
	while (!is_empty(&q)) {			//ť�� �������� �ݺ�
		v = dequeue(&q);		//ť ���� �տ� �ִ� ���� dequeue
		for (w = 0; w < g->n; w++) {
			if (g->adj_mat[v][w] && !visited[w]) {	//�������� ���� ���� �ְ� �湮�Ǿ� ���� �ʴٸ�
				visited[w] = TRUE;	//���� ������ �湮�Ǿ��ٰ� ǥ��
				printf("%d ", w);	//������ ���
				enqueue(&q, w);		//������ ť�� ����
			}
		}
	}
	printf("\n");
}
void Delete_Graph(GraphType*g) {	//�׷����� �����ϴ� �Լ�
	int i = 0;
	for (i = 0; i < g->n; i++) {	//�׷����� �� �޸� ����
		free(g->adj_mat[i]);
	}
	free(g->adj_mat);			//�׷����� �� �޸� ����
	free(g);			//�׷��� �޸� ����
	free(visited);		//visited���� �޸� ����
}
