/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: �������� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))	//�� ������ ���� �����ϴ� SWAP ����

typedef struct Data {	//�⺻ �ڷ��� ����Ÿ ����ü
	char *date;			//�⵵�� ������ date ���ڿ� ������
	int walking;		//���� Ƚ���� ������ walking����
}Data;

void selection_sort(Data list[], int n);		//���������Լ�
void Print(Data ary[], int n);		//�迭 ��� �Լ�
void Delete(Data *ary, int count);		//������ �����Լ�

int main() {
	FILE *fp;		//����������
	Data *ary;		//Data�ڷ��� ������, �������� ������ �����Ҵ�
	int count = 0;	//�������� ������ �� count����
	char str[20];	//���Ϸκ��� ���ڿ��� �ӽ÷� �Է¹��� ���ڿ� ����
	int data, i = 0;	//���� ���� �Է¹��� data

	fp = fopen("results_stpes.txt", "r");	//������ �б� �������� open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {			//���� ������ �Է�
		fscanf(fp, "%s%d", str, &data);
		count++;				//�������� ���� ����
	}
	ary = (Data*)malloc(sizeof(Data)*count);	//�������� ������ �����Ҵ�
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%s%d", str, &data);		//��¥ ���ڿ�, ������ �Է�
		//���� ��ġ�� date���ڿ��� str�� ���̷� �����Ҵ�
		ary[i].date = (char*)malloc(sizeof(char)*(strlen(str) + 1));
		strcpy(ary[i].date, str);	//str���ڿ��� date�� ����
		ary[i].walking = data;	//������ ����

		i++;	//i����
	}
	printf("** Selection Sort ���� �� ��� **\n");
	printf("=================================\n");
	Print(ary, count);		//�������� �� ���

	selection_sort(ary, count);	//�������� �Լ� ���
	printf("\n\n** Selection Sort ���� �� ��� **\n");
	printf("=================================\n");
	Print(ary, count);		//�������� �� ���

	Delete(ary, count);		//ary������ ����
	fclose(fp);				//���������� ����	
	return 0;
}
void selection_sort(Data list[], int n) {		//���������Լ�
	int i, j, high;		//i�� j�� �ݺ����� �� ����, high�� ���� ū ���� �ε���
	Data temp;
	for (i = 0; i < n - 1; i++) {
		high = i;						//���� ���� �ε����� high�� ����
		for (j = i + 1; j < n; j++) {
			if (list[j].walking > list[high].walking)high = j;		//high�� ���� ū ���� �ε��� ����
		}
		SWAP(list[i], list[high], temp);		//���� �ε����� high�ε����� ���� ����
	}
}
void Print(Data ary[], int n) {		//�迭 ��� �Լ�

	int i;
	for (i = 0; i < n; i++) {
		printf("%s %d\n", ary[i].date, ary[i].walking);	//��¥, ���� �� ������ ���
	}
}
void Delete(Data *ary, int count) {		//������ �����Լ�
	int i;
	for (i = 0; i < count; i++) {
		free(ary[i].date);	//���� ������ ���� data���ڿ� ����
	}
	free(ary);		//ary�迭 ����
}