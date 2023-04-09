/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: �׷��� ���� �켱 Ž�� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

#define TRUE 1
#define FALSE 0

typedef struct {					//�׷��� ����ü ����
	int n;
	int **adj_mat;					//��������� �̿��� �׷���
}GraphType;

int *visited;						//�湮�Ǿ����� Ȯ���ϴ� ����

void init(GraphType*g, int num);	//�׷��� �ʱ�ȭ �Լ�
void insert_vertex(GraphType*g, int num);	//���� ���� �Լ�
void insert_edge(GraphType* g, int start, int end);	//���� ���� �Լ�
void dfs_mat(GraphType*g, int v);	//���� �켱 Ž�� �Լ�
void Delete_Graph(GraphType*g);		//�׷��� ���� �Լ�

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
	while (!feof(fp)) {			//���ϳ����� �ݺ��ϸ� �ִ밪�� ã��
		fscanf(fp, "%c", &ctemp);
		if (ctemp == 'v') {		//v�� �Է¹޾��� �� ���� �ϳ� �� �Է¹���
			fscanf(fp, "%d", &itemp1);
			if (max < itemp1) max = itemp1;	//�Է¹��� ������ max���� Ŭ�� max�� ���� ����
		}
	}
	g = (GraphType*)malloc(sizeof(GraphType));
	max++;							//max�� 1 ������Ű�� �ʱ�ȭ�ؾ���
	init(g, max);					//�׷��� �ʱ�ȭ

	for (i = 0; i < max; i++) {		//max����ŭ ��������
		insert_vertex(g, max);		//���� ���� �Լ�ȣ��
	}
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%c", &ctemp);
		if (ctemp == 'e') {		//e�� �Է¹޾��� �� ���� ����
			fscanf(fp, "%d%d", &itemp1, &itemp2);	//���� �� ������ �Է¹ް�
			insert_edge(g, itemp1, itemp2);		//���� �׷����� ����
		}
	}
	printf("-���� �켱 �׷��� Ž�� ���-\n<");

	dfs_mat(g, 0);				//���� �켱Ž���Լ� ȣ��
	printf(">\n");
	Delete_Graph(g);			//�׷��� ����
	fclose(fp);					//���� ����
	return 0;
}
void init(GraphType*g, int num) {		//�׷��� �ʱ�ȭ �Լ�
	int r;
	g->n = 0;							//������ ������ 0���� �ʱ�ȭ
	g->adj_mat = (int**)calloc(sizeof(int*), num);	//calloc���� ����� �� �����Ҵ�
	for (r = 0; r < num; r++) {
		g->adj_mat[r] = (int*)calloc(sizeof(int), num);	//calloc���� ����� �� �����Ҵ�
	}
	visited = (int*)calloc(sizeof(int), num);//visited������ num���� �°� �����Ҵ�
}
void insert_vertex(GraphType*g, int num) {		//���� �����Լ�
	if ((g->n) + 1 > num) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;				//������ ���� ����
}
void insert_edge(GraphType* g, int start, int end) {	//����׷����� �����ϴ� �Լ�
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;			//�Է¹��� start�� end���� 1�� ����
}
void dfs_mat(GraphType*g, int v) {		//���� �켱Ž�� �Լ�
	int w;

	visited[v] = TRUE;					//���� ������ �湮�ߴٰ� ǥ��
	printf("%d ", v);
	for (w = 0; w < g->n; w++) {		//������ ������ŭ �ݺ�
		if (g->adj_mat[v][w] && !visited[w])	//adj_mat[v][w]�� 1�̰� visited[w]�� �湮���� �ʾҴٸ�
			dfs_mat(g, w);	//��ȯ�� ���� ���� w���� ���� ����
	}
}
void Delete_Graph(GraphType*g) {		//�׷����� �����ϴ� �Լ�
	int i = 0;
	for (i = 0; i < g->n; i++) {		//����� �� �޸� ����
		free(g->adj_mat[i]);
	}
	free(g->adj_mat);				//����� �� �޸�����
	free(g);					//�׷��� �޸� ����
	free(visited);				//visited���� �޸� ����
}
