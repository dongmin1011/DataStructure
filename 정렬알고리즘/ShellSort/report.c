#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {		//�л� ���� ����ü
	char* name;			//�̸� ������
	int num;			//�й� ����
	char* phone;		//��ȭ��ȣ ������
}Student;

void inc_insertion_sort(Student list[], int first, int last, int gap);
void shell_sort(Student list[], int n);
void print(Student list[], int count);

int main() {
	FILE *fp;				//����������
	int count = 0;			//�迭�� ����
	Student *data;			//�л� ������ ������
	char name[20], phone[20];
	int num;
	int i;

	fp = fopen("data.txt", "r");		//������ �б� �������� open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {				//���� ������ �ݺ��ϸ� �ӽú����� �����鼭 count�� ����
		fscanf(fp, "%s%d%s", name, &num, phone);
		count++;
	}
	rewind(fp);						//���������͸� ������ �ű�
	data = (Student*)malloc(sizeof(Student)*count);		//data������ �����Ҵ�
	for(i=0; i<count; i++) {
		fscanf(fp, "%s%d%s", name, &data[i].num, phone);	//���Ϸκ��� ������ �Է� �й��� ���� �Է¹���
		data[i].name = (char*)malloc(sizeof(char)*(strlen(name) + 1));	//name������ �����Ҵ�
		strcpy(data[i].name, name);										//���ڿ� ����

		data[i].phone = (char*)malloc(sizeof(char)*(strlen(phone) + 1));	//phone������ �����Ҵ�
		strcpy(data[i].phone, phone);										//���ڿ� ����
	}
	printf("<���� ��> \n");
	print(data, count);		//���� �� �迭 ���

	shell_sort(data, count);	//������ �Լ� ȣ��

	printf("\n<���� ��>\n");
	print(data, count);		//���� �� �迭 ���
	
	for (i = 0; i < count; i++) {	//�̸������Ϳ� phone������ �����Ҵ� ����
		free(data[i].name);
		free(data[i].phone);
	}
	free(data);			//data�迭 �����Ҵ� ����
	fclose(fp);			//���������� close
	return 0;
}
void inc_insertion_sort(Student list[], int first, int last, int gap) {	//���� �������� ������ �ִ� ��ҵ��� ����
	int i, j;
	Student key;										//������ �ϱ� ���� ���
	for (i = first + gap; i <= last; i = i + gap) {		//gap��ŭ �̵��ϸ� ������ ��
		key = list[i];									//
		for (j = i - gap; j >= first && key.num > list[j].num; j = j - gap) { //���� key�� num���� ����Ʈ[j]�� num������ ũ�ٸ� ����
			list[j + gap] = list[j];			//list[j]�� ���� �ڷ� �̵�
		}
		list[j + gap] = key;				//
	}
}
void shell_sort(Student list[], int n) {	//�� ���� �Լ�
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {//gap�� ��ü�� ���ݺ��� ������ 1�� �ɶ����� ������ ����
		if ((gap % 2) == 0)gap++;			//���� gap�� ¦����� gap���� 1 ����
		for (i = 0; i < gap; i++) {			//�κи���Ʈ�� ���� gap��ŭ ��һ������� �Լ��� �ݺ�
			inc_insertion_sort(list, i, n - 1, gap);

		}
		
		printf("%d\n", gap);
		print(list, n);
	}
}
void print(Student list[], int count) {		//�迭 ��� �Լ�
	int i;
	for (i = 0; i < count; i++) {		//�迭�� ���� count��ŭ �ݺ��ϸ� �迭 ���
		printf("%s %d %s\n", list[i].name, list[i].num, list[i].phone);
	}
}