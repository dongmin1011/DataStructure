/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: ���� ���� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int interpol_search(int list[], int key, int n) {			//���� Ž�� �Լ�
	int low, high, j;

	low = 0;		//low�� ���� ù �ε���
	high = n - 1;	//high�� ���� �� �ε���
	int count = 0;
	while ((list[high] >= key) && (key > list[low])) {		
		j = ((float)(key - list[low]) / (list[high] - list[low])*(high - low)) + low;	//Ž�� ��ġ�� ���ϴ� ����
		count++;
		if (key > list[j])low = j + 1;
		else if (key < list[j])high = j - 1;	//key���� list[j]�� Ŭ�� high�� j-1
		else low = j;		//key�� list[j]�� ���� ��
	}
	printf("%d\n", count);
	if (list[low] == key)return low;		//Ž������
	else return -1;							//Ž�� ����
}
int main() {
	FILE *fp;
	int count, find, i = 0;	//count�� �������� ����, find�� ã�� ����
	int n;					//ã�� ������ ��ġ�� ����
	int *list;				//������ ������ ������ �迭
	clock_t start, stop;	
	double duration;

	fp = fopen("data.txt", "r");		//"data.txt"���� ����
	if (!fp) {
		printf("file not open");
		return 0;
	}
	printf("�������� ���� : ");
	scanf("%d", &count);					//�������� ���� �Է�
	printf("ã���� �ϴ� ������ �Է��ϼ���: ");	
	scanf("%d", &find);						//ã����� ���� �Է�

	list = (int*)malloc(sizeof(int)*count);	//count�� list������ �����Ҵ�
	for(i=0; i<count; i++){
		fscanf(fp, "%d", &list[i]);			//���� �����͸� list�� ����
	}
	start = clock();					//���� �ð� ����
	n = interpol_search(list, find, count);	//���� Ž�� �Լ� ȣ��
	stop = clock();						//�� �ð� ����
	duration = (double)(stop - start) / CLOCKS_PER_SEC;	//���� �ð� ���
	if (n == -1) {
		printf("ã�� ������ ����\n");
	}
	else {
		printf("%d ��°�� ����Ǿ� ����\n", n + 1);	//��ġ ���
		printf("���� Ž�� ���� �ӵ� : %lf", duration);
	}
	free(list);		//����Ʈ �����Ҵ� ����
	fclose(fp);		//���������� ����
	return 0;
}