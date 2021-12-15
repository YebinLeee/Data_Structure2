/*
���Ͽ� ����Ǿ� �ִ� �л� �����͸� �о�,
				�й��� �̿��� ���� Ʈ���� �����ϰ� ����/����/���� ������ ����ϴ� ���α׷�
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �л� ����ü
typedef struct Student {
	int id;		// �й�(������ key)
	char* name;	// �̸�(���� ��������)
}Student;

// Ʈ�� ��� ����ü
typedef struct TreeNode {
	Student data;
	struct TreeNode* left, * right;
}TreeNode;

// �Լ� ���� ����
void error(const char* message);
TreeNode* new_node(Student data);
TreeNode* insert_node(TreeNode* node, Student new_data);
void preorder(TreeNode* root);
void inorder(TreeNode* root);
void postorder(TreeNode* root);
void clear(TreeNode* root);

int main() {
	FILE* fp;
	TreeNode* root = NULL;	// ���� Ž�� Ʈ���� ��Ʈ ���
	Student tmp;			// �л� �ӽ� ����ü
	char name[30];			// ���Ͽ��� �̸� �ӽ÷� ���� ���ڿ�

	// ���� ����
	fp = fopen("data.txt", "rt");
	if (fp == NULL) error("���� ���� ����");

	// ���Ͽ��� ������ �а�, ���� Ʈ���� ����
	while (!feof(fp)) {
		fscanf(fp, "%d %s", &tmp.id, name);

		tmp.name = (char*)malloc(sizeof(name));	// ���� �迭 ���� �޸� ���� �Ҵ�
		if (tmp.name == NULL) error("���ڿ� ���� �Ҵ� ���� \n");
		strcpy(tmp.name, name);	// ���ڿ� ����

		root = insert_node(root, tmp); // ����ü �����Ͽ� Ʈ���� ��� ����
	}
	// ����, ����, ���� ���
	printf("���� ��ȸ :"); preorder(root); printf("\b\b  \n");
	printf("���� ��ȸ :"); inorder(root); printf("\b\b  \n");
	printf("���� ��ȸ :"); postorder(root); printf("\b\b  \n");

	clear(root);	// �޸� ����
	fclose(fp);		// ���� �ݱ�
	return 0;
}

void error(const char* message) {
	fprintf(stderr, "%s \n", message);
	exit(1);
}

// Ʈ���� ���ο� �л� ��� ���� �Ҵ�
TreeNode* new_node(Student data) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL)error("���� �Ҵ� ���� \n");
	else {
		temp->data = data;	// �л� ����ü�� ����� ������ �ʵ忡 ����
		temp->left = temp->right = NULL;	// ��ũ �ʵ�� ��� NULL�� ����(�ܸ� ���)
	}
	return temp;
}

// insert_node �Լ� (Ž�� �� ����)
TreeNode* insert_node(TreeNode* node, Student new_data) {
	// ������ ��ġ Ž�� �� ���ο� ����� �ּ� ����
	if (node == NULL) return new_node(new_data);

	if (new_data.id < node->data.id) {	// key�� �� ���� ��� ���� ����Ʈ�� Ž��
		node->left = insert_node(node->left, new_data);
	}
	else if (new_data.id > node->data.id)	// key�� �� ū ��� ������ ����Ʈ�� Ž�� 
		node->right = insert_node(node->right, new_data);

	return node; // ����� ��Ʈ ������ ��ȯ
}

// ���� ��ȸ
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf(" %d %s ->", root->data.id, root->data.name);
		preorder(root->left);
		preorder(root->right);
	}
}
// ���� ��ȸ
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf(" %d %s ->", root->data.id, root->data.name);
		inorder(root->right);
	}
}
// ���� ��ȸ
void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf(" %d %s ->", root->data.id, root->data.name);
	}
}

// ���� ��ȸ�ϸ� ����� �޸� ����
void clear(TreeNode* root) {
	if (root == NULL)return;
	clear(root->left);
	clear(root->right);
	free(root);
}