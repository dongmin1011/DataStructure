#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ( (t) = (x), (x)=(y), (y) = (t))	//x�� y�� �ڸ��� ��ȯ�ϴ� SWAP��ũ�� ����

int partition(int list[], int left, int right);		//����Ʈ ���� �Լ�
void quick_sort(int list[], int left, int right);	//������ �Լ�
void Print(int list[], int count);	//�迭 ����Լ�

int main() {
	FILE *fp;
	int i, tmp, count=0;
	int *ary;							//�迭�� ������ ary������ ����
		
	fp = fopen("data1.txt", "r");		//������ �б� �������� open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {				//���� ������ �ݺ��ϸ� �������� ���� ����
		fscanf(fp, "%d", &tmp);
		count++;
	}
	rewind(fp);				//���������͸� ������ �ű�
	ary = (int*)malloc(sizeof(int)*count);	//ary������ �����Ҵ�
	for (i = 0; i < count; i++) {
		fscanf(fp, "%d", &tmp);
		ary[i] = tmp;		//ary�迭�� ���� ������ �� ����
	}
	printf("< ���ĵ��� ���� ����Ʈ >\n");
	Print(ary, count);		//���� �� ary�迭 ���

	quick_sort(ary, 0, count-1);		//������ �Լ� ȣ��

	printf("\n< ���ĵ� ����Ʈ >\n");
	Print(ary, count);		//���� �� ary�迭 ���

	free(ary);				//ary�迭 �����Ҵ� ����
	fclose(fp);			//���������� close
	return 0;		
}
int partition(int list[], int left, int right) {		//����Ʈ ���� �Լ�
	int pivot, temp;
	int low, high;
	int i;
	low = left;								//low�� left�� ����
	high = right + 1;						//high�� right���� �� ����
	pivot = list[left];						//�Ǻ��� list[left]������ ����
	printf("\n-Pivot : %d-\n", pivot);
	do {
		do {
			low++;		//list[low]�� pivot���� Ŀ�������� low�� ����
		} while (list[low] < pivot);

		printf("low : ");
		for (i = left; i <= right; i++) {
			if (list[i] == list[low]) {
				printf("%d ", list[low]);		//low�� ���
				break;
			}
		}
		if (i == right + 1) {
			printf("over ");
		}
	
		do {
			high--;		//list[highj]�� pivot���� �۾ƶ����� high�� ����
		} while (list[high] > pivot);

		printf("high : %d  [", list[high]);		//high�� ���

		for (i = left; i <= right; i++) {
			printf("%d > ", list[i]);		//list�� ���� ���� ���
		}
		printf("]\n\n");

		if (low < high)SWAP(list[low], list[high], temp);	//���� high�� �� ũ�ٸ� list[low]�� list[high]�� ���� ��ȯ
	} while (low < high);
	SWAP(list[left], list[high], temp); // list[low]�� list[high]�� ���� ��ȯ
	return high; //high ����
}
void quick_sort(int list[], int left, int right) {	//������ �Լ�
	if (left < right) {
		int q = partition(list, left, right);	//pivot�� ��ġ ��ȯ ����

		quick_sort(list, left, q - 1);			//left���� �Ǻ� �ٷ� �ձ����� ������� ��ȯȣ��
		quick_sort(list, q + 1, right);			//�Ǻ� ��ġ �ٷ� �������� right���� ��ȯȣ��
	}
}
void Print(int list[], int count) {		//�迭 ����Լ�
	int i;
	for (i = 0; i < count; i++) {
		printf("%d > ", list[i]);	//�迭�� ������ŭ �ݺ��ϸ� �迭 ���
	}
}