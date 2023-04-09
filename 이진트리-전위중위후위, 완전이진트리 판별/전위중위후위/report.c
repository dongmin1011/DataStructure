/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: ����Ʈ���� ������ �����ϰ�
			 ����, ����, ���������� ����ϴ� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student{
	int number;										//�й�
	char *name;										//�̸� ������
}Student;

typedef struct TreeNode {
	Student data;
	struct TreeNode *left, *right;					//����, �������� ����Ű�� ���
}TreeNode;

TreeNode* Insert_node(TreeNode*, Student);			//��� �����Լ�
TreeNode* new_node(Player);							//���ο� ��带 �����ϴ� �Լ�
void Print_Order(TreeNode*);						//����, ����, ���������� ����ϴ� �Լ�
void Preorder(TreeNode*, int);						//���� ����Լ�
void Inorder(TreeNode*, int);						//���� ����Լ�
void Postorder(TreeNode*, int);						//���� ����Լ�
int Get_Node_Count(TreeNode*);						//����� ������ �����ϴ� �Լ�
void Delete_Tree(TreeNode*);						//Ʈ�� ��� ��ü�� �����ϴ� �Լ�

int main() {
	FILE *fp;																	//����������
	char s[10];																	//�̸��� �Է¹��� �ӽ�������
	Student temp;																//���Ϸκ��� �Է¹��� �ӽú���
	TreeNode* root = NULL;														//����Ʈ��

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open\n");
		return 0;
	}
	while (!feof(fp)) {			
		fscanf(fp, "%d%s", &temp.number, s);						//���Ϸκ��� �Է�(�̸��� �ӽú��� s�� �Է�)
		temp.name = (char*)malloc(sizeof(char)*(strlen(s) + 1));	//s���ڿ��� ���� + \0 �̹Ƿ� +1�Ͽ� �����Ҵ�
		strcpy(temp.name, s);										//���ڿ� s�� temp.name�� ����
		root = Insert_node(root, temp);								//����Ʈ���� ����
	}
	Print_Order(root);												//��带 ����, ����, ������ �°� ��ü ���

	Delete_Tree(root);												//����Ʈ���� ��ü ����
	fclose(fp);														//���������� ����
	return 0;
}

TreeNode* Insert_node(TreeNode* node, Student key) {												//Ʈ�� ���� �Լ�
	if (node == NULL) return new_node(key);															//���� ��尡 �������� ������ ���ο� ��� ��ȯ

	if (key.number < node->data.number)																	//�Է¹��� �й��� ����� �й����� �۴ٸ�
		node->left = Insert_node(node->left, key);													//���� ��忡 ����
	else if (key.number > node->data.number)														//�Է¹��� �й��� ����� �й����� ũ�ٸ�
		node->right = Insert_node(node->right, key);												//������ ��忡 ����
	else {																							//���� �ߺ��� ��ȣ�� �Է¹޴´ٸ� �޽��� ���
		printf("��ȣ�� �ߺ��˴ϴ�. (��ȣ : %d, �̸� : %s) ���� �Ұ�\n", key.number, key.name);
	}
	return node;																					//����� ��Ʈ ������ ��ȯ
}	
TreeNode* new_node(Student item) {																	//���ο� ��� ���� �Լ�
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));	
	temp->data = item;
	temp->left = temp->right = NULL;																	//���� ���� ������ ���� NULL�� �����ϰ� ����
	return temp;	
}
void Print_Order(TreeNode*root) {												//��带 ����, ����, ������ �°� ������� ����ϴ� �Լ�
	int node_count = Get_Node_Count(root);										//����� ��ü ũ��(����)
	printf("���� ��ȸ : ");
	Preorder(root, node_count);													//���� ���	
	printf("\n���� ��ȸ : ");
	Inorder(root, node_count);													//���� ���
	printf("\n���� ��ȸ : ");
	Postorder(root, node_count);												//���� ���
}
int Get_Node_Count(TreeNode*node) {												//����� ������ �����ϴ� �Լ�
	int count = 0;
	if (node != NULL)															//���� ��尡 NULL�� �ƴ϶��
		count = 1 + Get_Node_Count(node->left) + Get_Node_Count(node->right);	//���� ��� ������ ������ ��� ���� ���ϱ� �ڱ� ��� 1�� �� ����

	return count;
}
void Preorder(TreeNode*node, int count) {										//���� ����Լ� 
	static int num = 0;
	if (node != NULL) {	
		printf("%d %s ", node->data.number, node->data.name);
		num++;																	//num�� ���������� ����Ǿ� ���� ��� ��Ҹ� �����ϰ� ����
		if (num < count) printf("-> ");											//���� num�� ��带 1���� ���������� 1�� �����ϹǷ� ������ ��� �������� ->���
		Preorder(node->left, count);											//���� ��� ��� �Լ�
		Preorder(node->right, count);											//������ ��� ���
	}

}
void Inorder(TreeNode* node, int count) {										//���� ����Լ�
	static int num = 0;
	if (node != NULL) {
		Inorder(node->left, count);
		printf("%d %s ", node->data.number, node->data.name);
		num++;
		if (num < count)printf("-> ");
		Inorder(node->right, count);
	}
}
void Postorder(TreeNode* node, int count) {										//���� ����Լ�
	static int num = 0;
	if (node != NULL) {
		Postorder(node->left, count);
		Postorder(node->right, count);
		printf("%d %s ", node->data.number, node->data.name);
		num++;
		if (num < count)printf("-> ");
	}
}
void Delete_Tree(TreeNode*node) {												//��� ��ü�� �����ϴ� �Լ�
	if (node != NULL) {
		Delete_Tree(node->left);													//���� ��� ����
		Delete_Tree(node->right);													//������ ��� ����
		printf("\n������ ��� : %d, %s", node->data.number, node->data.name);		//������ ��� ���

		free(node);
	}
}