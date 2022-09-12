#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
	int number;
	struct node *left;
	struct node *right;
};

void freeTree(struct node *tree){
	if (tree == NULL) {
		return;
	}
	freeTree(tree->left);
	freeTree(tree->right);
	free(tree);
}

void preorder(struct node *tree){
	if (tree == NULL) {
		return;
	}
	printf(" %d", tree->number);
	preorder(tree->left);
	preorder(tree->right);
}

void addLeftRight(struct node *tree, int value1, int value2, int value3){
	if (tree == NULL) {
		return;
	}
	struct node *leftchild = (struct node*)malloc(sizeof(struct node));
	struct node *rightchild = (struct node*)malloc(sizeof(struct node));
	leftchild->number = value2;
	rightchild->number = value3;
	leftchild->left = NULL;
	leftchild->right = NULL;
	rightchild->left = NULL;
	rightchild->right = NULL;
	if (tree->number == value1){	//	탐색 성공
		if (value2 == 0){
			tree->left = NULL;
			free(leftchild);
		}
		else{
			tree->left = leftchild;
		}
		if (value3 == 0){
			tree->right = NULL;
			free(rightchild);
		}
		else{
			tree->right = rightchild;
		}
	}
	else{
		free(leftchild);
		free(rightchild);
	}
	addLeftRight(tree->left, value1, value2, value3);	//	좌측 탐색
	addLeftRight(tree->right, value1, value2, value3);	//	우측 탐색
}

void search(struct node *root, char str[100]){
	printf(" %d", root->number);
	for (int i = 0; i < strlen(str); i++){
		if (str[i] == 'R'){
			root = root->right;
		}
		else if (str[i] == 'L'){
			root = root->left;
		}
		else{
			return;
		}
		if (root != NULL)
			printf(" %d", root->number);
		else
			printf(" *");
	}
	printf("\n");
}

void findMinNode(struct node *root){
	struct node *temp = root->right;
	
	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	printf("%d\n", temp->number);
}

void findMaxNode(struct node *root){
	struct node *temp = root->left;
	
	while (temp->right != NULL)
	{
		temp = temp->right;
	}
	printf("%d\n", temp->number);
}

int main(){
	int nodeNumber, value1, value2, value3, searchNumber;
	struct node *root, *tree = (struct node*)malloc(sizeof(struct node));
	char searchInfomation[100];
	root = tree;
	scanf("%d", &nodeNumber);
	for (int i = 0; i < nodeNumber; i++){
		scanf("%d", &value1);	//	부모노드 | 왼쪽자식 | 오른쪽 자식
		scanf("%d", &value2);
		scanf("%d", &value3);
		if (i == 0) {	//	맨 처음 노드 초기화
			struct node *leftchild = (struct node*)malloc(sizeof(struct node));
			struct node *rightchild = (struct node*)malloc(sizeof(struct node));
			tree->number = value1;
			leftchild->number = value2;
			rightchild->number = value3;
			leftchild->left = leftchild->right = NULL;
			rightchild->left = rightchild->right = NULL;
			if (value2 != 0){
				root->left = leftchild;
			}
			else{	//	0이면 free
				free(leftchild);
			}
			if (value3 != 0){
				root->right = rightchild;
			}
			else{	//	0이면 free
				free(rightchild);
			}
		}
		else {	//	평상시
			addLeftRight(root, value1, value2, value3);
		}
	}
	scanf("%d", &searchNumber);
	for (int i = 0; i < searchNumber; i++){
		getchar();
		scanf("%s", searchInfomation);
		search(root, searchInfomation);
	}
	
	freeTree(root);
}
