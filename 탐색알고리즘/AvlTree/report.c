/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: AVLƮ�� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {	//AVLƮ�� ����
	int key;
	struct AVLNode *left;
	struct AVLNode *right;
}AVLNode;

AVLNode *rotate_right(AVLNode *parent);	//���������� ȸ����Ű�� �Լ�
AVLNode *rotate_left(AVLNode *parent);	//�������� ȸ����Ű�� �Լ�

int get_height(AVLNode*node);	//Ʈ���� ���̸� ��ȯ�ϴ� �Լ�
int get_balance(AVLNode *node);	//����� ���� �μ��� ��ȯ
AVLNode * create_node(int key);		//���ο� ��带 �����ϴ� �Լ�


AVLNode* insert(AVLNode*node, int key);	//AVLƮ���� ���ο� ��带 �߰��ϴ� �Լ�
AVLNode* search(AVLNode*node, int key);	//AVLƮ������ ��带 ã�� �Լ�

void Delete(AVLNode*node) {			//AVLƮ���� �����ϴ� �Լ�
	if (node != NULL) {
		Delete(node->left);			//���� ���� ������
		Delete(node->right);		//������ ���� ������
	//	printf("%d ", node->key);
		free(node);				//���� ��� ����
	}
}
void preorder(AVLNode*node) {		//���� ��ȸ �Լ�
	if (node != NULL) {
		printf("%d ", node->key);	//���� ��� ���	
		preorder(node->left);	//���� ���� ��ȯ
		preorder(node->right);	//������ ��� ��ȯ

	}
}
int main() {
	FILE *fp;
	AVLNode *root = NULL;
	char c;
	int n;

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);
		if (c == 'a') {			//���� �Է¹��� ���ڰ� a��� ����
			fscanf(fp, "%d", &n);
			root = insert(root, n);	//insert �����Լ� ȣ��
			preorder(root);
		}
		else if (c == 's') {		//�Է¹��� ���ڰ� s��� Ž��
			AVLNode*tmp;
			fscanf(fp, "%d", &n);
			printf("Ž�� : %d\n", n);
			tmp = search(root, n);		//searchŽ���Լ� ȣ��
			if (tmp != NULL) {		//tmp�� NULL�� �ƴϸ� Ž���Ȱ�
				printf(" %d\n", tmp->key);
			}
			else {					//tmp�� NULL�̸� Ž�� �Ұ�
				printf("Ž�� �Ұ�\n");
			}
		}
		
	}
	

	Delete(root);		//AVLƮ�� ����
	fclose(fp);			//���������� ����
	return 0;
}

AVLNode *rotate_right(AVLNode *parent) {	//���������� ȸ����Ű�� �Լ�
	AVLNode*child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}
AVLNode *rotate_left(AVLNode *parent) {		//�������� ȸ����Ű�� �Լ�
	AVLNode*child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}
int get_height(AVLNode*node) {		//Ʈ���� ���̸� ���ϴ� �Լ�
	int left_count, right_count;
	if (node == NULL) return 0;		//���� node�� NULL�̸� 0 ����

	left_count = get_height(node->left);	//���� Ʈ���� ���� ��ȯ
	right_count = get_height(node->right);	//������ Ʈ���� ���� ��ȯ

	if (left_count > right_count)			//���� ������ �� ���̰� ���ٸ�
		return left_count + 1;				//���� ����+1 ��ȯ
	else
		return right_count + 1;				//������ ���̰� �� ���ٸ� ������ +1��ȯ
}
int get_balance(AVLNode *node) {			//����� ���� �μ��� ��ȯ�ϴ� �Լ�
	if (node == NULL)return 0;
	return get_height(node->left) - get_height(node->right);	//����� ���� ���̿��� ������ ���̸� �� ���� ��ȯ
}																//������ �� ���ٸ� ���, �������� �� ���ٸ� ����
AVLNode * create_node(int key) {				//���ο� ��带 �����ϴ� �Լ�
	printf("���� : %d\n", key);
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));	//��� �����Ҵ� ����
	node->key = key;
	node->left = NULL;					//left�� right�� �ʱⰪ�� NULL�� ����
	node->right = NULL;
	return node;
}

AVLNode* insert(AVLNode*node, int key) {		//avlƮ���� ���ο� ��带 �����ϴ� �Լ�
	int balance;
	if (node == NULL)					//���� ��尡 NULL�̸� 
		return create_node(key);			//���ο� ��� ����

	if (key < node->key) {					//���� key�� node�� key���� �۴ٸ�
		node->left = insert(node->left, key);	//�������� �������� ��ȯ
	}
	else if (key > node->key) {				//���� key�� node�� key���� ũ�ٸ�
		node->right = insert(node->right, key);	//���������� ������
	}
	else return node;				//������ Ű�� ���x

	balance = get_balance(node);	//������ �����μ� ���
	
	if (balance > 1 && key < node->left->key) {	//���ο� ��尡 ���� �ڽ��� ���ʿ� �߰� LL
		return rotate_right(node);
	}
	if (balance<-1 && key > node->right->key) {	//���ο� ��尡 ������ �ڽ��� �������� �߰� RR
		printf("���� ȸ��");
		return rotate_left(node);
	}
	if (balance > 1 && key > node->left->key) {	//���ο� ��尡 ���� �ڽ��� �����ʿ� �߰� LR
		printf("LRȸ��");
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}
	if (balance < -1 && key < node->right->key) {	//���ο� ��尡 ������ �ڽ��� ���ʿ� �߰� RL
		printf("RLȸ��");
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}
AVLNode* search(AVLNode*node, int key) {			//avlƮ�� Ž�� �Լ�
	printf("Ž�� ��� : ");
	while (node != NULL) {				//�ݺ��� �̿��Ͽ� Ž��
		if (key == node->key) return node;	//���� key�� ����� key�� ���ٸ� ��� ����
		else if (key < node->key) {		//key�� ����� key���� �۴ٸ� �������� ������
			printf(" %d", node->key);
			node = node->left;
		}
		else {						//key�� ����� key���� ũ�ٸ�
			printf(" %d", node->key);		
			node = node->right;			//���������� ������
		}
	}
	return NULL;
}