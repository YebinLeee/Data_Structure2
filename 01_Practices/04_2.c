/*
������ �������� �̿��� ���� Ž�� Ʈ���� �����,
				���� ��ȸ�� �ϸ� ���� ����Ž�� Ʈ������ �Ǻ��ϴ� ���α׷�
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#define FALSE 0
#define TRUE 1

typedef struct TreeNode {		// TreeNode:Ʈ���� ���
	int data;
	struct TreeNode* left, * right;
}TreeNode;

typedef TreeNode* element;		// element: Ʈ�� ��� ������
typedef struct {				// QueueType: Ʈ�� ���� �����Ϳ� ���� ť �迭
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

// �Լ� ���� ����
void error(char* message);
int is_empty(QueueType* q);
int is_full(QueueType* q);
void enqueue(QueueType* q, element item);
element dequeue(QueueType* q);
TreeNode* new_node(int item);
TreeNode* insert_node(TreeNode* node, int key);
int is_leaf(TreeNode* node);
int isComplete(TreeNode* ptr);
void clear(TreeNode* ptr);

int main() {
	FILE* fp;
	TreeNode* root = NULL;
	int tmp;

	// ���� ����
	fp = fopen("data.txt", "rt");
	if (fp == NULL) error("���� ���� ����");

	// ���Ϸκ��� ���� �о� Ʈ�� ���� �ϼ�
	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		root = insert_node(root, tmp);
	}

	// ���� ����Ž�� Ʈ������ �Ǻ�
	if (isComplete(root)) printf("\n���� ����Ž�� Ʈ���Դϴ�. \n");
	else printf("\n���� ����Ž�� Ʈ���� �ƴմϴ�. \n");

	clear(root);	// �޸� ����
	fclose(fp);		// ���� �ݱ�
	return 0;
}

void error(char* message) {
	fprintf(stderr, "%s \n", message);
	exit(1);
}
void init_queue(QueueType* q) { q->front = q->rear = 0; }
int is_empty(QueueType* q) { return (q->front == q->rear); }
int is_full(QueueType* q) { return((q->rear + 1) % MAX_QUEUE_SIZE == q->front); }

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("ť�� ��������Դϴ�.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// Ʈ���� ���ο� ��� ���� �Ҵ�
TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

// ���� Ž��Ʈ������ Ž�� �� Ư�� ��ġ�� ���ο� key�� ���� ��� ����
TreeNode* insert_node(TreeNode* node, int key) {
	// Ž���� �����Ͽ� ���ο� ����� �ּҸ� ��ȯ
	if (node == NULL) {
		printf("Inserted %d \n", key);
		return new_node(key);
	}

	// ���ο� ��带 ������ ��ġ Ž��
	if (key < node->data)
		node->left = insert_node(node->left, key);
	else if (key > node->data)
		node->right = insert_node(node->right, key);

	return node; // ����� ��Ʈ ������ ��ȯ
}

// �ܸ� ��� �Ǻ�
int is_leaf(TreeNode* node) {
	// ����/������ �ڽ� ��尡 ��� NULL�ΰ�� �ܸ����
	if (node->left == NULL && node->right == NULL) return TRUE;
	else return FALSE;
}

// ���� ��ȸ�� �ϸ� ���� ����Ž�� Ʈ������ �Ǻ�
int isComplete(TreeNode* ptr) {
	QueueType q;
	init_queue(&q);

	if (ptr == NULL) return;

	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);

		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);

		// ���� �ڽ� ��尡 ���� ���
		if (ptr->left == NULL) {
			// ���� �ڽ� ��尡 �����鼭, ������ �ڽ� ���� �ִ� ���
			if (ptr->right) return FALSE;

			// ť�� �ִ� ������ ������ �ܸ� ������� Ȯ���ϱ�
			else {
				while (!is_empty(&q)) {
					ptr = dequeue(&q);
					if (is_leaf(ptr) == FALSE) return FALSE;
				}
				return TRUE;
			}
		}
		// ���� �ڽ� ���� ������, ������ �ڽ� ��尡 ���� ���
		if (ptr->left && ptr->right == NULL) {
			// ť�� �ִ� ������ ������ �ܸ� ������� Ȯ���ϱ� 
			while (!is_empty(&q)) {
				ptr = dequeue(&q);
				if (is_leaf(ptr) == FALSE) return FALSE;
			}
			return TRUE;
		}
	}
}

// ���� ��ȸ�ϸ� ����� �޸� ����
void clear(TreeNode* root) {
	if (root == NULL)return;
	clear(root->left);
	clear(root->right);
	free(root);
}