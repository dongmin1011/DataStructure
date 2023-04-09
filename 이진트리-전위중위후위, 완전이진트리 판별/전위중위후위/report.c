/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 이진트리에 파일을 저장하고
			 전위, 중위, 후위순으로 출력하는 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student{
	int number;										//학번
	char *name;										//이름 포인터
}Student;

typedef struct TreeNode {
	Student data;
	struct TreeNode *left, *right;					//왼쪽, 오른쪽을 가리키는 노드
}TreeNode;

TreeNode* Insert_node(TreeNode*, Student);			//노드 삽입함수
TreeNode* new_node(Player);							//새로운 노드를 생성하는 함수
void Print_Order(TreeNode*);						//전위, 중위, 후위순으로 출력하는 함수
void Preorder(TreeNode*, int);						//전위 출력함수
void Inorder(TreeNode*, int);						//중위 출력함수
void Postorder(TreeNode*, int);						//후위 출력함수
int Get_Node_Count(TreeNode*);						//노드의 개수를 리턴하는 함수
void Delete_Tree(TreeNode*);						//트리 노드 전체를 삭제하는 함수

int main() {
	FILE *fp;																	//파일포인터
	char s[10];																	//이름을 입력받을 임시포인터
	Student temp;																//파일로부터 입력받을 임시변수
	TreeNode* root = NULL;														//이진트리

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open\n");
		return 0;
	}
	while (!feof(fp)) {			
		fscanf(fp, "%d%s", &temp.number, s);						//파일로부터 입력(이름은 임시변수 s에 입력)
		temp.name = (char*)malloc(sizeof(char)*(strlen(s) + 1));	//s문자열의 길이 + \0 이므로 +1하여 동적할당
		strcpy(temp.name, s);										//문자열 s를 temp.name에 복사
		root = Insert_node(root, temp);								//이진트리에 삽입
	}
	Print_Order(root);												//노드를 전위, 중위, 후위에 맞게 전체 출력

	Delete_Tree(root);												//이진트리를 전체 삭제
	fclose(fp);														//파일포인터 닫음
	return 0;
}

TreeNode* Insert_node(TreeNode* node, Student key) {												//트리 삽입 함수
	if (node == NULL) return new_node(key);															//만약 노드가 존재하지 않으면 새로운 노드 반환

	if (key.number < node->data.number)																	//입력받은 학번이 노드의 학번보다 작다면
		node->left = Insert_node(node->left, key);													//왼쪽 노드에 저장
	else if (key.number > node->data.number)														//입력받은 학번이 노드의 학번보다 크다면
		node->right = Insert_node(node->right, key);												//오른쪽 노드에 저장
	else {																							//만약 중복된 번호를 입력받는다면 메시지 출력
		printf("번호가 중복됩니다. (번호 : %d, 이름 : %s) 삽입 불가\n", key.number, key.name);
	}
	return node;																					//변경된 루트 포인터 반환
}	
TreeNode* new_node(Student item) {																	//새로운 노드 생성 함수
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));	
	temp->data = item;
	temp->left = temp->right = NULL;																	//왼쪽 값과 오른쪽 값을 NULL로 지정하고 리턴
	return temp;	
}
void Print_Order(TreeNode*root) {												//노드를 전위, 중위, 후위에 맞게 순서대로 출력하는 함수
	int node_count = Get_Node_Count(root);										//노드의 전체 크기(개수)
	printf("전위 순회 : ");
	Preorder(root, node_count);													//전위 출력	
	printf("\n중위 순회 : ");
	Inorder(root, node_count);													//중위 출력
	printf("\n후위 순회 : ");
	Postorder(root, node_count);												//후위 출력
}
int Get_Node_Count(TreeNode*node) {												//노드의 개수를 리턴하는 함수
	int count = 0;
	if (node != NULL)															//만약 노드가 NULL이 아니라면
		count = 1 + Get_Node_Count(node->left) + Get_Node_Count(node->right);	//왼쪽 노드 개수와 오른쪽 노드 개수 더하기 자기 노드 1개 후 리턴

	return count;
}
void Preorder(TreeNode*node, int count) {										//전위 출력함수 
	static int num = 0;
	if (node != NULL) {	
		printf("%d %s ", node->data.number, node->data.name);
		num++;																	//num은 정적변수로 선언되어 이전 기억 장소를 저장하고 있음
		if (num < count) printf("-> ");											//따라서 num은 노드를 1개씩 지날때마다 1씩 증가하므로 마지막 노드 전까지만 ->출력
		Preorder(node->left, count);											//왼쪽 노드 출력 함수
		Preorder(node->right, count);											//오른쪽 노드 출력
	}

}
void Inorder(TreeNode* node, int count) {										//중위 출력함수
	static int num = 0;
	if (node != NULL) {
		Inorder(node->left, count);
		printf("%d %s ", node->data.number, node->data.name);
		num++;
		if (num < count)printf("-> ");
		Inorder(node->right, count);
	}
}
void Postorder(TreeNode* node, int count) {										//후위 출력함수
	static int num = 0;
	if (node != NULL) {
		Postorder(node->left, count);
		Postorder(node->right, count);
		printf("%d %s ", node->data.number, node->data.name);
		num++;
		if (num < count)printf("-> ");
	}
}
void Delete_Tree(TreeNode*node) {												//노드 전체를 삭제하는 함수
	if (node != NULL) {
		Delete_Tree(node->left);													//왼쪽 노드 삭제
		Delete_Tree(node->right);													//오른쪽 노드 삭제
		printf("\n삭제한 노드 : %d, %s", node->data.number, node->data.name);		//삭제한 노드 출력

		free(node);
	}
}