/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: AVL트리 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {	//AVL트리 정의
	int key;
	struct AVLNode *left;
	struct AVLNode *right;
}AVLNode;

AVLNode *rotate_right(AVLNode *parent);	//오른쪽으로 회전시키는 함수
AVLNode *rotate_left(AVLNode *parent);	//왼쪽으로 회전시키는 함수

int get_height(AVLNode*node);	//트리의 높이를 반환하는 함수
int get_balance(AVLNode *node);	//노드의 균형 인수를 반환
AVLNode * create_node(int key);		//새로운 노드를 생성하는 함수


AVLNode* insert(AVLNode*node, int key);	//AVL트리에 새로운 노드를 추가하는 함수
AVLNode* search(AVLNode*node, int key);	//AVL트리에서 노드를 찾는 함수

void Delete(AVLNode*node) {			//AVL트리를 삭제하는 함수
	if (node != NULL) {
		Delete(node->left);			//왼쪽 노드로 내려감
		Delete(node->right);		//오른쪽 노드로 내려감
	//	printf("%d ", node->key);
		free(node);				//현재 노드 삭제
	}
}
void preorder(AVLNode*node) {		//전위 순회 함수
	if (node != NULL) {
		printf("%d ", node->key);	//현재 노드 출력	
		preorder(node->left);	//왼쪽 노드로 순환
		preorder(node->right);	//오른쪽 노드 순환

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
		if (c == 'a') {			//만약 입력받은 문자가 a라면 삽입
			fscanf(fp, "%d", &n);
			root = insert(root, n);	//insert 삽입함수 호출
			preorder(root);
		}
		else if (c == 's') {		//입력받은 문자가 s라면 탐색
			AVLNode*tmp;
			fscanf(fp, "%d", &n);
			printf("탐색 : %d\n", n);
			tmp = search(root, n);		//search탐색함수 호출
			if (tmp != NULL) {		//tmp가 NULL이 아니면 탐색된것
				printf(" %d\n", tmp->key);
			}
			else {					//tmp가 NULL이면 탐색 불가
				printf("탐색 불가\n");
			}
		}
		
	}
	

	Delete(root);		//AVL트리 삭제
	fclose(fp);			//파일포인터 닫음
	return 0;
}

AVLNode *rotate_right(AVLNode *parent) {	//오른쪽으로 회전시키는 함수
	AVLNode*child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}
AVLNode *rotate_left(AVLNode *parent) {		//왼쪽으로 회전시키는 함수
	AVLNode*child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}
int get_height(AVLNode*node) {		//트리의 높이를 구하는 함수
	int left_count, right_count;
	if (node == NULL) return 0;		//만약 node가 NULL이면 0 리턴

	left_count = get_height(node->left);	//왼쪽 트리의 높이 반환
	right_count = get_height(node->right);	//오른쪽 트리의 높이 반환

	if (left_count > right_count)			//만약 왼쪽이 더 높이가 높다면
		return left_count + 1;				//왼쪽 높이+1 반환
	else
		return right_count + 1;				//오른쪽 높이가 더 높다면 오픈쪽 +1반환
}
int get_balance(AVLNode *node) {			//노드의 균형 인수를 반환하는 함수
	if (node == NULL)return 0;
	return get_height(node->left) - get_height(node->right);	//노드의 왼쪽 높이에서 오른쪽 높이를 뺀 값을 반환
}																//왼쪽이 더 높다면 양수, 오른쪽이 더 높다면 음수
AVLNode * create_node(int key) {				//새로운 노드를 생성하는 함수
	printf("삽입 : %d\n", key);
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));	//노드 동적할당 생성
	node->key = key;
	node->left = NULL;					//left와 right의 초기값을 NULL로 설정
	node->right = NULL;
	return node;
}

AVLNode* insert(AVLNode*node, int key) {		//avl트리에 새로운 노드를 삽입하는 함수
	int balance;
	if (node == NULL)					//만약 노드가 NULL이면 
		return create_node(key);			//새로운 노드 리턴

	if (key < node->key) {					//만약 key가 node의 key보다 작다면
		node->left = insert(node->left, key);	//왼쪽으로 내려가는 순환
	}
	else if (key > node->key) {				//만약 key가 node의 key보다 크다면
		node->right = insert(node->right, key);	//오른쪽으로 내려감
	}
	else return node;				//동일한 키는 허용x

	balance = get_balance(node);	//노드들의 균형인수 계산
	
	if (balance > 1 && key < node->left->key) {	//새로운 노드가 왼쪽 자식의 왼쪽에 추가 LL
		return rotate_right(node);
	}
	if (balance<-1 && key > node->right->key) {	//새로운 노드가 오른쪽 자식의 오른족에 추가 RR
		printf("왼쪽 회전");
		return rotate_left(node);
	}
	if (balance > 1 && key > node->left->key) {	//새로운 노드가 왼쪽 자식의 오른쪽에 추가 LR
		printf("LR회전");
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}
	if (balance < -1 && key < node->right->key) {	//새로운 노드가 오른쪽 자식의 왼쪽에 추가 RL
		printf("RL회전");
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}
AVLNode* search(AVLNode*node, int key) {			//avl트리 탐색 함수
	printf("탐색 결과 : ");
	while (node != NULL) {				//반복을 이용하여 탐색
		if (key == node->key) return node;	//만약 key와 노드의 key가 같다면 노드 리턴
		else if (key < node->key) {		//key가 노드의 key보다 작다면 왼쪽으로 내려감
			printf(" %d", node->key);
			node = node->left;
		}
		else {						//key가 노드의 key보다 크다면
			printf(" %d", node->key);		
			node = node->right;			//오른쪽으로 내려감
		}
	}
	return NULL;
}