/*
	작성자 : 이예빈(20204059)
	작성일 : 2021.09.27
	프로그램명 : 파일의 정수들을 이용해 이진 탐색 트리를 만들고,
				레벨 순회를 하며 완전 이진탐색 트리인지 판별하는 프로그램
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#define FALSE 0
#define TRUE 1

typedef struct TreeNode {		// TreeNode:트리의 노드
	int data;
	struct TreeNode* left, * right;
}TreeNode;

typedef TreeNode* element;		// element: 트리 노드 포인터
typedef struct {				// QueueType: 트니 도드 포인터에 대한 큐 배열
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

// 함수 원형 선언
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

	// 파일 열기
	fp = fopen("data.txt", "rt");
	if (fp == NULL) error("파일 열기 실패");

	// 파일로부터 정수 읽어 트리 구조 완성
	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		root = insert_node(root, tmp);
	}

	// 완전 이진탐색 트리인지 판별
	if (isComplete(root)) printf("\n완전 이진탐색 트리입니다. \n");
	else printf("\n완전 이진탐색 트리가 아닙니다. \n");

	clear(root);	// 메모리 해제
	fclose(fp);		// 파일 닫기
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
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 트리의 새로운 노드 동적 할당
TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

// 이진 탐색트리에서 탐색 후 특정 위치에 새로운 key를 갖는 노드 삽입
TreeNode* insert_node(TreeNode* node, int key) {
	// 탐색에 성공하여 새로운 노드의 주소를 반환
	if (node == NULL) {
		printf("Inserted %d \n", key);
		return new_node(key);
	}

	// 새로운 노드를 삽입할 위치 탐색
	if (key < node->data)
		node->left = insert_node(node->left, key);
	else if (key > node->data)
		node->right = insert_node(node->right, key);

	return node; // 변경된 루트 포인터 반환
}

// 단말 노드 판별
int is_leaf(TreeNode* node) {
	// 왼쪽/오른쪽 자식 노드가 모두 NULL인경우 단말노드
	if (node->left == NULL && node->right == NULL) return TRUE;
	else return FALSE;
}

// 레벨 순회를 하며 완전 이진탐색 트리인지 판별
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

		// 왼쪽 자식 노드가 없는 경우
		if (ptr->left == NULL) {
			// 왼쪽 자식 노드가 없으면서, 오른쪽 자식 노드는 있는 경우
			if (ptr->right) return FALSE;

			// 큐에 있는 나머지 노드들이 단말 노드인지 확인하기
			else {
				while (!is_empty(&q)) {
					ptr = dequeue(&q);
					if (is_leaf(ptr) == FALSE) return FALSE;
				}
				return TRUE;
			}
		}
		// 왼쪽 자식 노드는 있지만, 오른쪽 자식 노드가 없는 경우
		if (ptr->left && ptr->right == NULL) {
			// 큐에 있는 나머지 노드들이 단말 노드인지 확인하기 
			while (!is_empty(&q)) {
				ptr = dequeue(&q);
				if (is_leaf(ptr) == FALSE) return FALSE;
			}
			return TRUE;
		}
	}
}

// 후위 순회하며 노드의 메모리 해제
void clear(TreeNode* root) {
	if (root == NULL)return;
	clear(root->left);
	clear(root->right);
	free(root);
}