#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct ListNode{
	char *mean;
	struct ListNode *link;
}ListNode;
typedef struct ListType {
	ListNode *head;
	ListNode *tail;
}ListType;

typedef struct Element {
	char *word;
	char *mean;
//	ListType *mean_list;
}Element;

typedef struct TreeData {
	char *word;
	ListType *mean_list;
}TreeData;
typedef struct TreeNode {
	TreeData data;
	struct TreeNode *left, *right;
}TreeNode;

void Insert_List_Node(ListType*, char*);
ListType* create();
void Print_List(ListType*);
void Delete_List(ListType*);


int compare(char *s1, char *s2);
void Print_Tree(TreeNode *, int);
TreeNode * new_node(Element);
TreeNode * Insert_Tree_Node(TreeNode*, Element);
TreeNode* delete_node(TreeNode*, char* key, int *check);
TreeNode *min_value_node(TreeNode*);
TreeNode* search(TreeNode*, char*);
int Get_Node_Count(TreeNode*);
void Delete_Tree(TreeNode*);


int main() {
	FILE *fp;
	TreeNode *root=NULL;
	TreeNode *tmp;
	char word[10], mean[10];
	char c;
	Element temp;
	int check = FALSE;

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open\n");
		return 0;
	}
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);
		
		switch (c) {
		case 'i':
			printf("%c\n", c);
			fscanf(fp, "%s%s", word, mean);
			temp.word = (char*)malloc(sizeof(char)*(strlen(word) + 1));
			temp.mean = (char*)malloc(sizeof(char)*(strlen(mean) + 1));
			strcpy(temp.word, word);
			strcpy(temp.mean, mean);
			root = Insert_Tree_Node(root, temp);
			printf("\n");
			break;
		case 'd':
			check = FALSE;
			printf("%c\n", c);
			fscanf(fp, "%s", word);
			root = delete_node(root, word, &check);
			if (!check) printf("삭제할 단어 %s가 존재하지 않습니다.\n\n", word);
			else printf("단어:%s\n\n", word);
			
			break;
		case 's':
			printf("%c\n", c);
			fscanf(fp, "%s ", word);
			
			tmp = search(root, word);
			if (tmp == NULL) {
				printf("%s 단어가 존재하지 않습니다.\n\n", word);
				break;
			}
			printf("단어: %s\n", tmp->data.word);
			printf("의미: ");
			Print_List(tmp->data.mean_list);
			printf("\n\n");
			break;
		case 'p':
			printf("%c\n", c);
			Print_Tree(root, Get_Node_Count(root));
			printf("\n\n");
			break;
		}

	}
	Delete_Tree(root);
	fclose(fp);
	return 0;
	
}
ListType* create() {
	ListType*plist = (ListType*)malloc(sizeof(ListType));
	plist->head = plist->tail = NULL;
	return plist;
}
int compare(char* s1, char *s2) {
	return strcmp(s1, s2);
}
void Print_Tree(TreeNode *node, int count) {
	static int num = 0;
	if (node != NULL) {
		Print_Tree(node->left, count);
		Print_Tree(node->right, count);
		printf("%s ", node->data.word);

		Print_List(node->data.mean_list);
		num++;
		if(num<count) printf(", ");
		else if (num == count) num = 0;
	}
}
TreeNode* new_node(Element key) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	printf("단어 : %s\n", key.word);
	printf("의미 : %s\n", key.mean);
	temp->data.word = key.word;
	temp->data.mean_list = create();
	Insert_List_Node(temp->data.mean_list, key.mean);
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode* Insert_Tree_Node(TreeNode*node, Element key) {

	if (node == NULL) return new_node(key);

	if (compare(key.word, node->data.word) < 0)
		node->left = Insert_Tree_Node(node->left, key);
	else if (compare(key.word, node->data.word) > 0)
		node->right = Insert_Tree_Node(node->right, key);
	else {
		Insert_List_Node(node->data.mean_list, key.mean);
		printf("단어 : %s\n", key.word);
		printf("의미 : %s\n", key.mean);
	}
	return node;
}
void Insert_List_Node(ListType*plist, char* key) {
	ListNode*temp = (ListNode*)malloc(sizeof(ListNode));
	temp->mean = key;
	temp->link = NULL;
	if (plist->tail == NULL)
		plist->head = plist->tail = temp;
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
}
void Print_List(ListType*plist) {
	ListNode*p = plist->head;
	while (p->link != NULL) {
		printf("%s, ", p->mean);
		p = p->link;
	}
	printf("%s", p->mean);
}

TreeNode *min_value_node(TreeNode*node) {
	TreeNode*current = node;

	while (current->left != NULL)
		current = current->left;
	return current;
}
TreeNode* delete_node(TreeNode*root, char* key, int *check) {
	if (root == NULL)return root;

	if (compare(key, root->data.word) < 0)
		root->left = delete_node(root->left, key, check);
	else if (compare(key, root->data.word) > 0)
		root->right = delete_node(root->right, key, check);
	else {
	//	printf("%s\n", key);
		if (root->left == NULL) {
			TreeNode*temp = root->right;
		
		//	Delete_List(root->data.mean_list);
		//	printf("삭제 단어 : %s\n", root->data.word);
		//	free(root->data.word);
			free(root);
			*check = TRUE;
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode*temp = root->left;
		//	Delete_List(root->data.mean_list);
		//	printf("삭제 단어 : %s\n", root->data.word);
		//	free(root->data.word);
			free(root);
			*check = TRUE;
			return temp;
		}
		TreeNode *temp = min_value_node(root->right);
		printf("%s\n", root->data.word);
		root->data = temp->data;
	//	printf("%s\n", root->data.word);
	//	Print_List(root->data.mean_list);
		root->right = delete_node(root->right, temp->data.word, check);
	}
	return root;
}

TreeNode* search(TreeNode*node, char* key) {
	TreeNode*p = node;
	while (p != NULL) {	
		if (compare(key, p->data.word) == 0)
			return p;
		else if (compare(key, p->data.word) < 0)
			p = p->left;
		else if (compare(key, p->data.word) > 0)
			p = p->right;
	}
	return p;
}
int Get_Node_Count(TreeNode*node) {
	int count = 0;
	if (node != NULL)
		count = 1 + Get_Node_Count(node->left) + Get_Node_Count(node->right);

	return count;
}
void Delete_List(ListType*plist) {
	ListNode*p, *q;
	p = q = plist->head;
	printf("삭제 리스트 : ");
	while (p != NULL) {
		q = q->link;
		printf("%s ", p->mean);
		free(p->mean);
		free(p);
		p = q;
	}
	printf("\n");
}
void Delete_Tree(TreeNode* node) {
	if (node != NULL) {
		Delete_Tree(node->left);
		Delete_Tree(node->right);
		printf("%s\n", node->data.word);
		Delete_List(node->data.mean_list);
		free(node->data.word);
		free(node);
		
	}
}


