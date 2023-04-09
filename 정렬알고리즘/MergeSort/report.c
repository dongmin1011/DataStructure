#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *sorted;		//�ӽ÷� ������ �߰� �迭

void merge(int list[], int left, int  mid, int right);	//�κ� ����Ʈ �պ� �Լ�
void merge_sort(int list[], int left, int right);		//�κ� ����Ʈ �Լ�
void Print(int ary[], int count);		//�迭 ��� �Լ�
int main() {
	FILE *fp;
	int i, count=0, temp;
	int *ary;


	fp = fopen("data1.txt", "r");		//������ �б� �������� open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);	//������ �����͸� �ӽ� ���� temp�� ����
		count++;			//���� �������� ���� ����
	}
	rewind(fp);
	ary = (int*)malloc(sizeof(int)*count);		//count�� ary�� sorted������ �����Ҵ�
	sorted = (int*)malloc(sizeof(int)*count);

	for (i = 0; i < count; i++) {//count��ŭ �ݺ��ϸ� ���� ������ �Է�
		fscanf(fp, "%d", &temp);
		ary[i] = temp;		//ary�迭�� ������ ����
	}
	
	printf("���ĵ��� ���� ����Ʈ\n");
	Print(ary, count);			//�պ� ���� �� �迭 ���

	merge_sort(ary, 0, count-1);		//�պ� ���� �Լ� ȣ��

	printf("\n���ĵȸ���Ʈ\n");
	Print(ary, count);			//�պ� ���� �� �迭 ���
	
	fclose(fp);		//���������� ����
	free(ary);		//ary������ ����
	free(sorted);	//sorted������ ����
	return 0;

}
void merge(int list[], int left, int  mid, int right) {	//�κ� ����Ʈ �պ� �Լ�
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {	//���� ���ĵ� ����Ʈ �պ�	
		if (list[i] <= list[j]) {		//���� ���� ����Ʈ ���� ������ ����Ʈ�� �� ũ�ٸ�
			sorted[k++] = list[i++];	//���� ����Ʈ�� �����͸� sorted�� ���� �� i����
		}
		else {						//���� ����Ʈ ���� ������ ����Ʈ�� �� �۴ٸ�
			sorted[k++] = list[j++];	// sorted�� ������ �����͸� ���� �� j����
		}
	}
	if (i > mid) {			//���� i�� mid���� �� ũ�ٸ�(������ ����Ʈ�� �����Ͱ� �����ִٸ�)
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];	//������ ����Ʈ�� ���� ���� sorted�� ��� ����
		}
	}
	else {					//���� i�� mid���� �� �۴ٸ�(���� ����Ʈ�� �����Ͱ� �����ִٸ�)
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];	//���� ����Ʈ�� ���� ���� sorted�� ��� ����
		}
	}
	printf("\nleft list : ");
	for (l = left; l <= mid; l++) {		//���� ����Ʈ ���
		printf("%d ", list[l]);
	}
	printf("\nright list : ");
	for (l = mid + 1; l <= right; l++) {	//������ ����Ʈ ���
		printf("%d ", list[l]);
	}
	printf("\nSorted List: ");
	for (l = left; l <= right; l++) {	//�պ��� ����Ʈ ���
		printf("%d ", sorted[l]);
		list[l] = sorted[l];
	}
	printf("\n");
}
void merge_sort(int list[], int left, int right) {		//�κ� ����Ʈ �Լ�
	int mid;

	if (left < right) {
		mid = (left + right) / 2;			//����Ʈ�� �յ� ����
		printf("%d\n", mid);
		merge_sort(list, left, mid);		//���� ũ���� 2���� �κ� �迭�� ����
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);	//���ĵ� �κ� �迭�� �ϳ��� �迭�� ����
	}
}
void Print(int ary[], int count) {		//�迭 ��� �Լ�
	int i;
	for (i = 0; i < count; i++) {
		printf("<%d> ", ary[i]);		//�迭�� ���� count��ŭ �ݺ��ϸ� ���
	}
	printf("\n");
}

