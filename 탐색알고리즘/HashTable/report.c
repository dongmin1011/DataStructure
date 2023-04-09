/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: �ؽ����̺� ���α׷�
*/#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define MOD 7

typedef struct {
	int key;				//�ʵ� ����
}element;



void init_table(element ht[]);	//�ؽ� ���̺� �ʱ�ȭ �Լ�
int hash_function(int n);		//���� �Լ��� ����� �ؽ� �Լ�

#define empty(item)(item.key==0)		//key�� 0���� Ȯ���ϴ� ��ũ��
#define equal(item1, item2)(item.key==item2.key)	//item1�� item2�� ������ Ȯ���ϴ� ��ũ��

void hash_lp_add(element item, element ht[]);		//�ؽ����̺� �����Լ�
void hash_lp_search(element item, element ht[]);	//�ؽ����̺� Ž���Լ�
	
int main() {
	FILE *fp;
	int tmp;
	element e;
	char c;
	element hash_table[TABLE_SIZE];	//�ؽ����̺� ����
	init_table(hash_table);		//�ؽ� ���̺� �ʱ�ȭ

	fp = fopen("data1.txt", "r");		//data.txt���� ����
	if (!fp) {
		printf("file not open");
		return 0;
	}
	printf("< HashTableSize = [%d]> \n\n", TABLE_SIZE);
	while (!feof(fp)) {		//�����͸� ������ �Է¹���
		fscanf(fp, "%c", &c);
		if (c == 'i') {		//���� c�� i��� �ؽ����̺� ���Կ���
			fscanf(fp, "%d", &tmp);
			e.key = tmp;
			hash_lp_add(e, hash_table);	//hash_lp_add�Լ��� ȣ���Ͽ� ����
		}
	}
	rewind(fp);
	printf("\n< Find Data Location >\n");
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);
		if (c == 's') {
			fscanf(fp, "%d", &tmp);
			e.key = tmp;
			hash_lp_search(e, hash_table);
		}
		
	}

	fclose(fp);
	return 0;
}
void init_table(element ht[]) {	//�ؽ� ���̺� �ʱ�ȭ �Լ�
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		ht[i].key = 0;			//�ؽ� ���̺� ���� ���� 0���� �ʱ�ȭ
	}
}
int hash_function(int n) {		//���� �Լ��� ����� �ؽ� �Լ�
	return n % MOD;
}

//���� ������� �̿��Ͽ� ���̺� Ű�� �����ϰ�, ���̺��� ���� �� ���� ����
void hash_lp_add(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (!equal(item, ht[i])) {	//���� Ž�� Ű�� �ߺ��ɰ��
			printf("data = %d ���� ���� HashTable : %d ���� �浹 ���� ", item.key, i);	//�ߺ����� �޽��� ���
		}
		i = (i + 1) % MOD;	//mod7���� �ε��� ����
		printf("- index = %d�� �����Ͽ����ϴ�.\n", i);
		if (i == hash_value) {		//���̺��� ���� �� ���
			fprintf(stderr, "���̺��� ���� á���ϴ�.\n");
			exit(1);
		}
	}
	ht[i] = item;		//ht[i]�� item����
}
//���� ������� �̿��Ͽ� ���̺� ������ Ű�� Ž��
void hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) {

		if (equal(item, ht[i])) {	//�ؽ� ���̺��� key�� �˻��� ���
			printf("%d �� HashTable : %d���� �˻��Ǿ����ϴ�.\n", item.key, i);
			return;
		}

		i = (i + 1) % MOD;		//mode7���� �ε��� ����
		if (i == hash_value) {		//ã�� key�� �ؽ����̺� ���� ���
			printf("�Է��Ͻ� �� %d�� HashTable���� �˻����� �ʾҽ��ϴ�.\n", item.key);
			return;
		}
	}
	printf("�Է��Ͻ� �� %d�� HashTable���� �˻����� �ʾҽ��ϴ�.\n", item.key);
}
