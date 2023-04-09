/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: �Է°� ������ ������ �����ϰ� 
			 ������ ����� ������� ����ϴ� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name;						//�̸� ������
}Element;
typedef struct {
	Element *heap;					//�� ������
	int heap_size;					//���� ũ��
}HeapType;

HeapType* create();					//���� �����ϰ� ��ȯ�ϴ� �Լ�
void init(HeapType*, int);				//�� �ʱ�ȭ �Լ�
void insert_min_heap(HeapType*h, Element item);//���� ����� ������ heap_size�� ������ ����(�ּ� ����)
Element delete_min_heap(HeapType*h);		//������ ��Ʈ ��带 �����ϰ� ��ȯ�ϴ� �Լ�
void Print_Heap(HeapType*h);		//���� �迭 ������� ����ϴ� �Լ�
int Heap_Height(int);				//���� ���̸� ��ȯ�ϴ� �Լ�
void Delete_Heap(HeapType*);		//���� ���� �����͸� �����ϴ� �Լ�

int main() {
	FILE*fp;						//����������
	Element temp;					//�����Ҷ� ���� �Ѱ��� �ӽ� ����
	char s[10], c;					//s�� �ӽ� ���ڿ� ����, c�� i�Ǵ� o�� �Է¹��� ����
	int count=0;			//count�� i(����)�� ����
	HeapType *heap;					//�� Ÿ��
	
	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open\n");
		return 0;
	}
	while (!feof(fp)) {				//���� ������ ������ �Է�
		fscanf(fp, "%c", &c);		//i�Ǵ� o�Է�
		if (c == 'i') {				//���� i�� �ִ�� �Էµ� �� �ִ� ������ ����
			fscanf(fp, "%s", s);
			count++;				//i�� ���� ++
		}
	}
	heap = create();				//�� ����
	init(heap, Heap_Height(count));			//�� �ʱ�ȭ
	
	rewind(fp);										//���������͸� ó������ �ű�
	while (!feof(fp)) {								//count���� i�� ������ ����Ǿ� �ֱ� ������ feof�Լ��� ������ �ݺ�
		fscanf(fp, "%c", &c);						//i(����)�Ǵ� o(����) �Է¹���
		switch (c) {
		case 'i':									//���� i�� �Է¹޾Ҵٸ� ���� ���� ����
			fscanf(fp, "%s", s);					//�ӽ� ���ڿ� �迭 s�� �Է¹���
			temp.name = (char*)malloc(sizeof(char)*(strlen(s) + 1));	//s�� ���� +1�� temp�� name������ �����Ҵ�
			strcpy(temp.name, s);										//temp.name�� s���ڿ� ����
			insert_min_heap(heap, temp);								//�ּ� ������ ����
			printf(">>�մ�(%s) ����\n", temp.name);						//�Է¹��� �̸� ���
			Print_Heap(heap);											//������ ���Ŀ� �°� ���
			break;	
		case 'o':									//���� o�� �Է¹޾ҾƸ� ��Ʈ ����� ���� ���� ����
			temp = delete_min_heap(heap);			//������ ��Ʈ ��� ��ȯ����
			printf(">>�մ�(%s) ����\n", temp.name);	//������ ��� ���
			free(temp.name);						//������ �̸� ������ �޸� ����
			Print_Heap(heap);						//������ ���Ŀ� �°� ���
			break;
		}
		printf("\n");
	}
	Delete_Heap(heap);							//�����Ҵ��� ���ڿ� ������, �� �迭, �� �޸� ����			
	fclose(fp);									//���� ������ ����
	return 0;
}
HeapType* create() {							//���� �����ϰ� ��ȯ�ϴ� �Լ�
	return (HeapType*)malloc(sizeof(HeapType));	//�� Ÿ���� �ڷ����� �°� �����Ҵ�
}
void init(HeapType* h, int height) {						//���� ũ�⸦ 0���� �ʱ�ȭ
	h->heap_size = 0;
	//���� ���� ���� ���� ��Ʈ ����Ʈ ������ ���� �� �迭 �����Ҵ�.
	//	printf("���� ���� : %d\n", height);
	//	printf("(1 << (height)) : %d\n", (1 << (height)));
	h->heap = (Element*)malloc(sizeof(Element)*((1 << (height))));
}
void insert_min_heap(HeapType*h, Element item) {//���� ����� ������ heap_size h�� item�� �����Ѵ�. (���� ���� ���� ��Ʈ)
	int i;
	i = ++(h->heap_size);
	//Ʈ���� �ż��� �ö󰡸鼭 �θ� ���� ��
	while ((i != 1) && (strcmp(item.name, h->heap[i / 2].name) < 0)) {	
		//Ʈ���� ��Ʈ���� ������ ������ ���� ���� ������ �̸��� ���� ��.
		//strcmp�� �ܾ� �� (���� strcmp�Լ��� ���������̸� ���� �ܾ �� ���� ��), ���� ���� ������ �ܾ ��Ʈ ��尡 ��.
		h->heap[i] = h->heap[i / 2];					//�θ� ����� �����͸� �ڽ� ��忡 ����(���ϸ� �ϳ��� �ö�)
		i /= 2;											//�θ� ���� �̵�
	}
	h->heap[i] = item;									//���� ��ġ �ε����� item ������ ����
}
Element delete_min_heap(HeapType*h) {									//������ ��Ʈ ��带 �����ϰ� ��ȯ�ϴ� �Լ�.
	int parent, child;
	Element item, temp;

	item = h->heap[1];									//item�� ��Ʈ ��� ����
	temp = h->heap[(h->heap_size)--];					//temp�� ���� ������ ��带 �����ϰ� �ϳ��� �����ϹǷ� heap_size���� ����
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {										//child�� ���� Ʈ���� ũ�⺸�� �۴ٸ�
		//child�� heap_size���� �۰� ���� �ڽ� ��尡 ������ �ڽ� ��庸�� ������ ������ �ʰ� ���´ٸ�(���� �ڽ� ��尡 �� �۴ٸ�) child++;
		if ((child < h->heap_size) && (strcmp((h->heap[child].name), h->heap[child + 1].name) > 0)) child++;

		//������ ����� �̸����� ���� �ڽ� ��庸�� �ڽ� ��尡 �� �ʰ� ���´ٸ� ����(temp�̸��� �� �۴ٸ�)
		if (strcmp(temp.name, h->heap[child].name) <= 0)break;

		h->heap[parent] = h->heap[child];						//�ڽ� ����� �����͸� �θ� ��忡 ����
		parent = child;											//�ڽ� �ε����� �θ� �ε����� ����
		child *= 2;												//child�� 2�� ���Ͽ� ���� ���� ������
	}
	h->heap[parent] = temp;										//�θ� ��忡 temp����(��Ʈ ��忡�� ���� ���� �̸� �����)
	return item;												//��Ʈ ��� ��ȯ
}
void Print_Heap(HeapType*h) {						//���� �迭 ������ ����ϴ� �Լ�
	int i;
	printf("< ���� ��� >\n");
	for (i = 1; i <= h->heap_size; i++) {			//i�� ��Ʈ����� �ε��� 1���� ���� ũ���� heap_size���� �ݺ�
		printf("%d: %s => ", i, h->heap[i].name);	//���� ���Ŀ� �°� ���
	}
	printf("\n");
}
int Heap_Height(int count) {					//���� ���̸� ��ȯ�ϴ� �Լ� �Ű�����: ������ ������ i ����
	int i, height = 0;
	for (i = 1; i <= count; i = i * 2) {		//���� ���� ����Ʈ���̱� ������ ���� ����� ���̷� �Ǵ�
						// �迭�� * 2���ϸ� ���� ��带 ����Ű�Ƿ� �������� �̵��ϸ� count���� Ŀ�������� �ݺ�
		height++;											
	}
	return height;						//���� ��ȯ
}
void Delete_Heap(HeapType*h) {			//���� �����ϴ� �Լ�
	int i;
	for (i = 1; i <= h->heap_size; i++) {//i�� ��Ʈ����� �ε��� 1���� ���� ũ���� heap_size���� �ݺ�
	//	printf("%s\n", h->heap[i].name);	
		free(h->heap[i].name);			//�����Ҵ��� ���� �̸� ���ڿ� �����͸� ����
	}
	free(h->heap);							//�� �迭 �޸� ����
	free(h);								//�� �޸� ����
}