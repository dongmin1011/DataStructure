/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: Floyd�� �ִ� ��� �˰���
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 1000

typedef struct GraphType {
	int n;						//������ ����
	int **weight;				//����ġ �׷���
}GraphType;
typedef struct Floyd {
	int A;						//����ġ�� ���� ����
	int check;					//������ ���� ����� TRUE
}Floyd;
Floyd **data;			//Floyd�� ���������͸� �ִܰ�� �迭�� ���

void Init(GraphType *g, int n); //�׷��� �ʱ�ȭ �Լ�
void insert_vertex(GraphType*g, int num);	//������ �����ϴ� �Լ�
void insert_edge(GraphType* g, int start, int end, int weight);		//������ �׷����� ������ �����ϴ�  �Լ�
void printA(GraphType *g);		//data�迭�� ���Ŀ� �°� ����ϴ� �Լ�
void floyd(GraphType*g);			//Floyd �˰��� �Լ�
void Delete(GraphType*g);			//�׷��� �����Լ�

int main() {
	GraphType *g;		//�׷��� ����
	FILE *fp;			//����������
	int max = -1;		//���� ū ������ ���� max����
	int temp1, temp2, weight, i;	//���Ϸκ��� ���� �Է¹��� temp�� weight
	char c;				//� ������ ���� ���Ϸκ��� �Է¹��� ���� c

	fp = fopen("data.txt", "r");		//data������ �б� �������� open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	g = (GraphType*)malloc(sizeof(GraphType));	//�׷��� �����Ҵ� ����
	while (!feof(fp)) {					//���� ������ ���� �Է�
		fscanf(fp, "%c", &c);			
		if (c == 'v') {					//�Է¹��� ���ڰ� v��� ���� ���� ����
			fscanf(fp, "%d", &temp1);
			if (max < temp1) max = temp1;	//�����߿� ���� ū ���� ã��
		}
	}
	max++;				//���� ū������ 1����	
	Init(g, max);		//max������ �׷��� �ʱ�ȭ
	rewind(fp);			//���������͸� �ٽ� ������ �ű�
	for (i = 0; i < max; i++) {
		insert_vertex(g, max);		//���� ����
	}
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);
		if (c == 'e') {				//�Է¹��� ���ڰ� e��� ���� ���� ����
			fscanf(fp, "%d%d%d", &temp1, &temp2, &weight);	//���۰� ����, ����ġ ���� �Է�
			insert_edge(g, temp1, temp2, weight);		//���� ����
		}
	}
	floyd(g);			//floyd�Լ� ȣ��
	Delete(g);			//�׷��� ����
	fclose(fp);			//���������� ����
	return 0;
}
void Init(GraphType *g, int n) {
	int i, j;
	g->n = 0;				//������ ���� �ʱ�ȭ
	g->weight = (int **)malloc(sizeof(int*)*n);	//����ġ �׷��� n������ �����Ҵ�
	for (i = 0; i < n; i++) {
		g->weight[i] = (int*)malloc(sizeof(int)*n);
		for (j = 0; j < n; j++) {
			g->weight[i][j] = INF;		//����ġ �׷����� INF�� �ʱ�ȭ
		}
	}
	data = (Floyd **)malloc(sizeof(Floyd*)*n);	//data���������͸� �����Ҵ�
	for (i = 0; i < n; i++) {
		data[i] = (Floyd*)malloc(sizeof(Floyd)*n);
	}
}
void insert_vertex(GraphType*g, int num) {	//������ �����ϴ� �Լ�
	if ((g->n) + 1 > num) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;		//������ ���� ����
}
void insert_edge(GraphType* g, int start, int end, int weight) {//������ �׷����� ������ �����ϴ�  �Լ�
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->weight[start][end] = weight;		//������ �׷����̱� ������ start�� end��
//	g->weight[end][start] = weight;		//end�� start�� �� �� ����
	g->weight[start][start] = g->weight[end][end] = 0;	//�ڱ� �ڽ��� 0���� �ʱ�ȭ
	data[start][end].check = data[end][start].check = TRUE;	//���Ӱ� ���� ������ check���� TRUE
//	data[start][start].check = data[end][end].check = TRUE;	//���Ӱ� ���� ������ check���� TRUE
}
void printA(GraphType *g) {			//data�迭�� ���Ŀ� �°� ����ϴ� �Լ�
	int i, j;
	printf("  ");
	for (i = 0; i < g->n; i++) printf(" %3d ", i);	//���� ��Ÿ���� ���� ���
	printf("\n");
	printf("---------------------------------------\n");
	for (i = 0; i < g->n; i++) {
		printf(" %d |", i);		//���� ��Ÿ���� ���� ���
		for (j = 0; j < g->n; j++) {
			if (data[i][j].A == INF) {		//���� ������ �������� �ʴ´ٸ�
				printf("%3c |", 'x');		//x���
			}
			else {							//������ �����Ѵٸ�
				if (data[i][j].check) {		//���Ӱ� ���� �����̶�� *���
					printf("*%2d |", data[i][j].A);
					data[i][j].check = FALSE;	//check���� �ٽ� FALSE�� �ٲ���
				}
				else printf("%3d |", data[i][j].A);	//���� �ִ� �����̶�� �׳� ���
			}
		}
		printf("\n");
	}
	printf("---------------------------------------\n\n");
}

void floyd(GraphType*g) {			//Floyd �˰��� �Լ�
	int i, j, k;
	for (i = 0; i < g->n; i++) {		//data�� �ʱⰪ�� ����ġ ����� weight���� ����
		for (j = 0; j < g->n; j++) {
			data[i][j].A = g->weight[i][j];
		}
	}
	printf("< �ʱ� ���� >\n");			//�ʱ���� ���
	printA(g);
	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++) {
			for (j = 0; j < g->n; j++) {
				//���� i���� j�� �ٷ� ���� �溸�� k�� ���İ��� ���� �� �����ٸ�
				if (data[i][k].A + data[k][j].A < data[i][j].A) {
					data[i][j].A = data[i][k].A + data[k][j].A;	//i���� k, k���� j�� ���� ���� ���� ��� ����
					data[i][j].check = TRUE;		//���ο� ���� �������Ƿ� check���� TRUE
				}
				//k�� ���İ��� �ʴ� ���� �״��
			}
		}
		printf("< %d�� ���� ���� >\n", k);			//��� ������ �������� ���
		printA(g);							//floyd�׷��� ���
	}
}

void Delete(GraphType*g) {			//�׷��� �����Լ�
	int i;
	for (i = 0; i < g->n; i++) {
		free(data[i]);			//floyd �׷��� data ����
		free(g->weight[i]);		//����ġ �׷��� weight���� ����
	}
	free(data);		//data�� weight ����
	free(g->weight);
	free(g);		//�׷��� ����
}
