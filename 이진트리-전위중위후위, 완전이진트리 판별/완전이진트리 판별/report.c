/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: ����Ʈ���� ������ �����ϰ�
			 ���� ����Ʈ������ �Ǻ��ϴ� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int Element;

typedef struct TreeNode {										//Ʈ�� ����ü
	Element data;	
	struct TreeNode *left, *right;								//Ʈ���� ���� ���� ������ ��带 ����Ű�� ������
}TreeNode;

int FILEOPEN(FILE**, TreeNode**);								//������ �����ϰ� �����͸� �о���� �Լ�
TreeNode* Insert_node(TreeNode*, Element);						//Ʈ���� ��带 �����ϴ��Լ�
TreeNode* new_node(Element);									//���ο� ��带 �����ϴ� �Լ�
void Preorder(TreeNode*);									//���� ��ȸ�� Ʈ���� ����ϴ� �Լ�
int Get_Node_Count(TreeNode*);									//����� ������ ��ȯ�ϴ� �Լ�
int Check_Tree(TreeNode*, int, int);							//Ʈ���� ��������Ʈ������ �Ǻ��ϴ� �Լ�
void Delete_Tree(TreeNode*);									//Ʈ�� ��ü�������ϴ� �Լ�


int main() {
	FILE *fp;										
	int n = 1;
	TreeNode*root= NULL;										//����Ʈ��

	if (!FILEOPEN(&fp, &root))return 0;							//���� ������ �������� �ʴ´ٸ� ����

	printf("Preorder>>> ");
	if (!Check_Tree(root, n, Get_Node_Count(root))) {			//Ʈ���� ��������Ʈ������ �Ǻ�
		printf("\n���� ����Ž��Ʈ���� �ƴմϴ�.\n");
	}
	else {
		Preorder(root);									
		printf("\n���� ���� Ž��Ʈ�� �Դϴ�.\n");
	}
	Delete_Tree(root);											//����Ʈ�� ��� ��ü�� ����
	fclose(fp);
	return 0;
}
int FILEOPEN(FILE**fp, TreeNode**root) {						//������ �����ϰ� �о���� �Ϲ�
	int n;
	*fp = fopen("data.txt", "r");
	if (!*fp) {
		printf("file not open\n");	
		return FALSE;											//������ �������� �ʴ´ٸ� FALSE����
	}
	while (!feof(*fp)) {										//������ �����ؼ� �������Ƿ� data�� �о��
		fscanf(*fp, "%d", &n);
		*root = Insert_node(*root, n);							//����Ʈ���� ����
	}
	return TRUE;												//TRUE ����
}
TreeNode* Insert_node(TreeNode* node, Element key) {			//Ʈ�� ���� �Լ�
	if (node == NULL) return new_node(key);						//���� ��尡 �������� �ʴ´ٸ� ���ο� ��� ��ȯ
	
	if (key < node->data)										//key�� ��庸�� �۴ٸ� ���ʿ� ����
		node->left = Insert_node(node->left, key);
	else if (key > node->data)									//ũ�ٸ� �����ʿ� ����
		node->right = Insert_node(node->right, key);
		
	return node;											//����� ��Ʈ������ ��ȯ
}
TreeNode* new_node(Element item) {								//���ο� ��� ���� �Լ�
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	printf("inserted -> %d\n", item);							//���ԵǴ� ��嵥���� ���
	temp->data = item;
	temp->left = temp->right = NULL;										//���� ���� ������ ���� NULL�� �����ϰ� ����
	return temp;
}
int Get_Node_Count(TreeNode*node) {												//����� ������ ��ȯ�ϴ� �Լ�
	int count = 0;
	if (node != NULL)															//������ ����Ʈ���� ���Ͽ� ��ȯ ȣ���� ����,
		count = 1 + Get_Node_Count(node->left) + Get_Node_Count(node->right);	//��ȯ�Ǵ� ���� 1�� ���Ͽ� ��ȯ

	return count;
}
void Preorder(TreeNode* tree) {													//Ʈ���� ���� ������ ����ϴ� �Լ�
	if (tree != NULL) {
		printf("%d ", tree->data);										
		Preorder(tree->left);													//���� ��� ���
		Preorder(tree->right);													//������ ��� ���
	}
}
int Check_Tree(TreeNode*node, int index, int count) {														//Ʈ���� ��������Ʈ������ �Ǻ��ϴ� �Լ�
	if (node == NULL)return TRUE;																			//���� ��尡 NULL�̸� ��������Ʈ���̹Ƿ� TRUE
//	printf("node->%d  index->%d\n", node->data, index);
	if (index > count)return FALSE;																		//�ε����� ����� �������� Ŀ���� ��������Ʈ���� �ƴ�

	if (Check_Tree(node->left, 2 * index, count) && Check_Tree(node->right, 2 * index + 1, count))
		return TRUE; 
	else return FALSE;																						//���� ���� *2 ������ ���� *2+1
}
void Delete_Tree(TreeNode*node) {																			//��� ��ü�� �����ϴ� �Լ�
	if (node != NULL) {
		Delete_Tree(node->left);																			//���� ��� ����
		Delete_Tree(node->right);																			//������ ��� ����
		printf("������ ��� : %d\n", node->data);
		free(node);
	}
}