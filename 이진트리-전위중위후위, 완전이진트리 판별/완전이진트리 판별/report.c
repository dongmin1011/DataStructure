/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 이진트리에 파일을 저장하고
			 완전 이진트리인지 판별하는 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int Element;

typedef struct TreeNode {										//트리 구조체
	Element data;	
	struct TreeNode *left, *right;								//트리의 왼쪽 노드와 오른쪽 노드를 가리키는 포인터
}TreeNode;

int FILEOPEN(FILE**, TreeNode**);								//파일을 오픈하고 데이터를 읽어오는 함수
TreeNode* Insert_node(TreeNode*, Element);						//트리에 노드를 삽입하는함수
TreeNode* new_node(Element);									//새로운 노드를 생성하는 함수
void Preorder(TreeNode*);									//전위 순회로 트리를 출력하는 함수
int Get_Node_Count(TreeNode*);									//노드의 개수를 반환하는 함수
int Check_Tree(TreeNode*, int, int);							//트리가 완전이진트리인지 판별하는 함수
void Delete_Tree(TreeNode*);									//트리 전체를삭제하는 함수


int main() {
	FILE *fp;										
	int n = 1;
	TreeNode*root= NULL;										//이진트리

	if (!FILEOPEN(&fp, &root))return 0;							//만약 파일이 존재하지 않는다면 종료

	printf("Preorder>>> ");
	if (!Check_Tree(root, n, Get_Node_Count(root))) {			//트리가 완전이진트리인지 판별
		printf("\n완전 이진탐색트리가 아닙니다.\n");
	}
	else {
		Preorder(root);									
		printf("\n완전 이진 탐색트리 입니다.\n");
	}
	Delete_Tree(root);											//이진트리 노드 전체를 삭제
	fclose(fp);
	return 0;
}
int FILEOPEN(FILE**fp, TreeNode**root) {						//파일을 오픈하고 읽어오는 하뭇
	int n;
	*fp = fopen("data.txt", "r");
	if (!*fp) {
		printf("file not open\n");	
		return FALSE;											//파일이 존재하지 않는다면 FALSE리턴
	}
	while (!feof(*fp)) {										//파일이 존재해서 열렸으므로 data를 읽어옴
		fscanf(*fp, "%d", &n);
		*root = Insert_node(*root, n);							//이진트리에 삽입
	}
	return TRUE;												//TRUE 리턴
}
TreeNode* Insert_node(TreeNode* node, Element key) {			//트리 삽입 함수
	if (node == NULL) return new_node(key);						//만약 노드가 존재하지 않는다면 새로운 노드 반환
	
	if (key < node->data)										//key가 노드보다 작다면 왼쪽에 저장
		node->left = Insert_node(node->left, key);
	else if (key > node->data)									//크다면 오른쪽에 저장
		node->right = Insert_node(node->right, key);
		
	return node;											//변경된 루트포인터 반환
}
TreeNode* new_node(Element item) {								//새로운 노드 생성 함수
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	printf("inserted -> %d\n", item);							//삽입되는 노드데이터 출력
	temp->data = item;
	temp->left = temp->right = NULL;										//왼쪽 값과 오른쪽 값을 NULL로 지정하고 리턴
	return temp;
}
int Get_Node_Count(TreeNode*node) {												//노드의 개수를 반환하는 함수
	int count = 0;
	if (node != NULL)															//각각의 서브트리에 대하여 순환 호출한 다음,
		count = 1 + Get_Node_Count(node->left) + Get_Node_Count(node->right);	//반환되는 값에 1을 더하여 반환

	return count;
}
void Preorder(TreeNode* tree) {													//트리를 전위 순서로 출력하는 함수
	if (tree != NULL) {
		printf("%d ", tree->data);										
		Preorder(tree->left);													//왼쪽 노드 출력
		Preorder(tree->right);													//오른쪽 노드 출력
	}
}
int Check_Tree(TreeNode*node, int index, int count) {														//트리가 완전이진트리인지 판별하는 함수
	if (node == NULL)return TRUE;																			//현재 노드가 NULL이면 완전이진트리이므로 TRUE
//	printf("node->%d  index->%d\n", node->data, index);
	if (index > count)return FALSE;																		//인덱스가 노드의 개수보다 커지면 완전이진트리가 아님

	if (Check_Tree(node->left, 2 * index, count) && Check_Tree(node->right, 2 * index + 1, count))
		return TRUE; 
	else return FALSE;																						//왼쪽 노드는 *2 오른쪽 노드는 *2+1
}
void Delete_Tree(TreeNode*node) {																			//노드 전체를 삭제하는 함수
	if (node != NULL) {
		Delete_Tree(node->left);																			//왼쪽 노드 삭제
		Delete_Tree(node->right);																			//오른쪽 노드 삭제
		printf("삭제한 노드 : %d\n", node->data);
		free(node);
	}
}