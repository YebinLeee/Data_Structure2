#include <stdio.h>
#include <stdlib.h>

// ���� Ʈ�� ��� ����ü
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

//    15
//  4    20
// 1   16  25
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

// ���� ��ȸ
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[ %2d ] ", root->data);
		inorder(root->right);
	}
}
// ���� ��ȸ
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[ %2d ] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
// ���� ��ȸ
void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[ %2d ] ", root->data);
	}
}

#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p) {
	if (top < SIZE - 1)
		stack[++top] = p;
}
TreeNode* pop() {
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

// ���� ������ ����� �ݺ��� ��ȸ(����)
void inorder_iter(TreeNode* root) {
	while (1) {
		for (;root;root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("[ %2d ] ", root->data);
		root = root->right;
	}
}

int main() {
	printf("���� ��ȸ= ");
	preorder(root);
	printf("\n");

	printf("���� ��ȸ= ");
	inorder(root);
	printf("\n");

	printf("���� ��ȸ= ");
	postorder(root);
	printf("\n");

	printf("���ð� �ݺ��� �̿��� ���� ��ȸ= ");
	inorder_iter(root);
	printf("\n\n");
}