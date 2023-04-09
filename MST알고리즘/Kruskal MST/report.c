/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: Kruskal�� MST�˰��� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 1000		//������ ���� �� ����
int *parent;			//�θ���

struct Edge {	//������ ��Ÿ���� ����ü
	int start, end, weight;	//����, ��, ����ġ
};
typedef struct GraphType {
	int n;		//������ ����
	struct Edge *edges;	//���� �迭
}GraphType;

void set_init(int n);	//�θ��� �ʱ�ȭ �Լ�
int set_find(int curr);	//curr�� ���ϴ� ���� ��ȯ �Լ�
void set_union(int a, int b);	//�ΰ��� ���Ұ� ���� ������ ��ġ�� �Լ� 

void Graph_init(GraphType*g, int num);		//�׷����� �ʱ�ȭ�ϴ� �Լ�
void insert_edge(GraphType*g, struct Edge e);	//������ �����ϴ� �Լ�
int compare(const void*a, const void*b);	//qsort�� ���Ǵ� �Լ�
int kruskal(GraphType*g);		//kruskal �ּ� ��� ���� Ʈ�� �Լ�
void Delete(GraphType*g);		//�׷��� ���� �Լ�
int main() {
	FILE *fp;
	struct Edge e;		//�����͸� �Է¹��� �ӽú���
	GraphType *g;		//�׷��� ����
	int cost;			//kruskal�� ���� �ּ� ���
	int count = 0;		//���� �������� ����

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open\n");
		return 0;
	}
	while (!feof(fp)) {			//������ ������ ������ ����
		fscanf(fp, "%d%d%d", &e.start, &e.end, &e.weight);	
		count++;				//������ ���� ����
	}
	g = (GraphType*)malloc(sizeof(GraphType));	//�׷��� ����
	Graph_init(g, count);			//�׷��� �ʱ�ȭ
	rewind(fp);		
	while (!feof(fp)) {
		fscanf(fp, "%d%d%d", &e.start, &e.end, &e.weight);
		insert_edge(g, e);		//�׷����� ���� ����
	}
	cost = kruskal(g);			//kruskal�� �ּ� ����� ����
	printf("�ʿ��� �ּ� ��� : %d\n", cost);	//�ּ� ��� ���
	
	Delete(g);				//�׷��� ����
	fclose(fp);				//���������� ����
	return 0;
}

void set_init(int n) {	//�θ��� �ʱ�ȭ
	int i;
	parent = (int*)malloc(sizeof(int)*n);	//�θ� ��带 n������ �����Ҵ�
	for (i = 0; i < n; i++)			
		parent[i] = -1;		//�θ��带 -1�� �ʱ�ȭ
}
int set_find(int curr) {	//curr�� ���ϴ� ������ ��ȯ
	if (parent[curr] == -1)	//���� �θ��尡 -1�̶��
		return curr;		//curr����
	while (parent[curr] != -1)curr = parent[curr];	//�θ��尡 -1�� �ɶ����� �ݺ�
	return curr;			//�θ� ����� ���� curr�� ����
}
void set_union(int a, int b) {	//�ΰ��� ���Ұ� ���� ������ ��ħ
	int root1 = set_find(a);	//��� a�� ��Ʈ�� ã��
	int root2 = set_find(b);	//��� b�� ��Ʈ�� ã��
	if (root1 != root2)			//�� ��Ʈ�� ����
		parent[root1] = root2;	
}
//////////////////////////

void Graph_init(GraphType*g, int num) {	//�׷��� �ʱ�ȭ
	int i;
	g->n = 0;
	g->edges = (struct Edge*)malloc(sizeof(struct Edge)*(num * 2));	//num���� 2��� ���� �迭 �����Ҵ�
	for (i = 0; i < num * 2; i++) {	//�ʱ�ȭ
		g->edges[i].start = 0;		
		g->edges[i].end = 0;
		g->edges[i].weight = INF;	//����ġ ���� INF�� �ʱ�ȭ
	}
}
void insert_edge(GraphType*g, struct Edge e) {	//���� ����
	int i;
	for (i = 0; i < g->n; i++) {		//�迭�� ������ �̹� �����ϴ��� Ȯ��
		if ((g->edges[i].end == e.start && g->edges[i].start == e.end) 
			|| (g->edges[i].start == e.start && g->edges[i].end == e.end)) {
			printf("���� %d - %d�� �̹� �߰��� �����Դϴ�.-- ���� \n", e.start, e.end);
			return;						//���� �����Ѵٸ� �Լ� ����
		}
	}	
	g->edges[g->n].start = e.start;		//�������� �ʴ´ٸ� ���� ����
	g->edges[g->n].end = e.end;
	g->edges[g->n].weight = e.weight;
	printf("���� %d - %d �߰��Ϸ�\n", e.start, e.end);
	g->n++;								//������ ���� ����
}
int compare(const void*a, const void*b) { //qsort�� ���Ǵ� �Լ�
	struct Edge *x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
int kruskal(GraphType*g) {	//kruskal �ּ� ��� ���� Ʈ�� �Լ�
	int edge_accepted = 0;	//������� ���õ� ������ ��
	int uset, vset;			//���� u�� ���� v�� ���� ��ȣ
	struct Edge e;			//��ȯ ���� ���� ������ ����
	int sum = 0;			//�ּ� ����� ���� ����

	set_init(g->n);			//���� �ʱ�ȭ
	
	qsort(g->edges, g->n, sizeof(struct Edge), compare);		//�� ���� �Լ�
	
	printf("\nũ�罺Į �ּ� ���� Ʈ�� �˰���\n");
	int i = 0;
	int j;
	while (edge_accepted < (g->n)) {	//���õ� ������ ���� ������ �������� �۴ٸ� �ݺ�
		e = g->edges[i];
		uset = set_find(e.start);	//���� u�� ���� ��ȣ
		vset = set_find(e.end);		//���� v�� ���� ��ȣ

		for (j = 0; j < g->n; j++) {
			printf("%d ", parent[j]);
		}

		if (uset != vset) {		//���� ���� ������ �ٸ��ٸ�
			printf("���� %d - %d : %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	//�� ������ ��ģ��.
			sum += e.weight;		//����ġ�� ����
		}
		else {		//���� ������ ����Ŭ�� �����Ѵٸ�
			edge_accepted++;
			printf("���� %d - %d : %d - ����Ŭ �������� ����\n", e.start, e.end, e.weight);
		}


		
		i++;
	}
	return sum;		//�ּ� ��� ��ȯ
}
void Delete(GraphType*g) {		//�׷��� ���� �Լ�
	free(parent);			//�θ� ��� ����
	free(g->edges);			//���� ���� ����
	free(g);				//�׷��� ���� ����
}