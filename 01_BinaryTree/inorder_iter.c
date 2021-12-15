#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

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

void inorder_iter(TreeNode* root) {
	while (1) {
		for (;root;root = root->left)
			push(root);
		root = pop();
		if (!root)break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}

// ��ü ����� ���� (��Ʈ ��� + ���� ���� Ʈ�� + ������ ����Ʈ��)
int get_node_count(TreeNode* node) {
	int count = 0;

	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);

	return count;
}

// �ܸ� ��� ���� (����/������ �ڽ��� ���ÿ� 0�� ���)
int get_leaf_count(TreeNode* node) {
	int count = 0;

	if (node != NULL)
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_node_leaf(node->left) + get_node_leaf(node->right);

	return count;
}

// Ʈ�� ���� ���ϱ� (���� ����Ʈ��, ������ ����Ʈ�� �� �� ���� ��)
int get_height(TreeNode* node) {
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

int main() {

	//    15
	//  4   20
	// 1   16 25

	TreeNode n1 = { 1,NULL,NULL };
	TreeNode n2 = { 4, &n1, NULL };
	TreeNode n3 = { 16, NULL,NULL };
	TreeNode n4 = { 25, NULL, NULL };
	TreeNode n5 = { 20, &n3, &n4 };
	TreeNode n6 = { 15, &n2, &n5 };
	TreeNode* root = &n6;


	printf("���� ��ȸ=");
	inorder_iter(root);
	printf("\n");
}