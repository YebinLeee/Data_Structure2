/*
	작성자 : 이예빈(20204059)
	작성일 : 2021.09.26
	프로그램명 : 파일에 저장되어 있는 학생 데이터를 읽어,
				학번을 이용해 이진 트리에 저장하고 전위/중위/후위 순으로 출력하는 프로그램
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 구조체
typedef struct Student {
	int id;		// 학번(정수값 key)
	char* name;	// 이름(문자 포인터형)
}Student;

// 트리 노드 구조체
typedef struct TreeNode {
	Student data;
	struct TreeNode* left, * right;
}TreeNode;

// 함수 원형 선언
void error(const char* message);
TreeNode* new_node(Student data);
TreeNode* insert_node(TreeNode* node, Student new_data);
void preorder(TreeNode* root);
void inorder(TreeNode* root);
void postorder(TreeNode* root);
void clear(TreeNode* root);

int main() {
	FILE* fp;
	TreeNode* root = NULL;	// 이진 탐색 트리의 루트 노드
	Student tmp;			// 학생 임시 구조체
	char name[30];			// 파일에서 이름 임시로 읽을 문자열

	// 파일 열기
	fp = fopen("data.txt", "rt");
	if (fp == NULL) error("파일 열기 실패");

	// 파일에서 데이터 읽고, 이진 트리에 삽입
	while (!feof(fp)) {
		fscanf(fp, "%d %s", &tmp.id, name);

		tmp.name = (char*)malloc(sizeof(name));	// 문자 배열 공간 메모리 동적 할당
		if (tmp.name == NULL) error("문자열 동적 할당 실패 \n");
		strcpy(tmp.name, name);	// 문자열 복사

		root = insert_node(root, tmp); // 구조체 전달하여 트리에 노드 삽입
	}
	// 전위, 주위, 후위 출력
	printf("전위 순회 :"); preorder(root); printf("\b\b  \n");
	printf("중위 순회 :"); inorder(root); printf("\b\b  \n");
	printf("후위 순회 :"); postorder(root); printf("\b\b  \n");

	clear(root);	// 메모리 해제
	fclose(fp);		// 파일 닫기
	return 0;
}

void error(const char* message) {
	fprintf(stderr, "%s \n", message);
	exit(1);
}

// 트리의 새로운 학생 노드 동적 할당
TreeNode* new_node(Student data) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL)error("동적 할당 실패 \n");
	else {
		temp->data = data;	// 학생 구조체를 노드의 데이터 필드에 대입
		temp->left = temp->right = NULL;	// 링크 필드는 모두 NULL로 대입(단말 노드)
	}
	return temp;
}

// insert_node 함수 (탐색 후 삽입)
TreeNode* insert_node(TreeNode* node, Student new_data) {
	// 삽입할 위치 탐색 후 새로운 노드의 주소 리턴
	if (node == NULL) return new_node(new_data);

	if (new_data.id < node->data.id) {	// key가 더 작은 경우 왼쪽 서브트리 탐색
		node->left = insert_node(node->left, new_data);
	}
	else if (new_data.id > node->data.id)	// key가 더 큰 경우 오른쪽 서브트리 탐색 
		node->right = insert_node(node->right, new_data);

	return node; // 변경된 루트 포인터 반환
}

// 전위 순회
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf(" %d %s ->", root->data.id, root->data.name);
		preorder(root->left);
		preorder(root->right);
	}
}
// 중위 순회
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf(" %d %s ->", root->data.id, root->data.name);
		inorder(root->right);
	}
}
// 후위 순회
void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf(" %d %s ->", root->data.id, root->data.name);
	}
}

// 후위 순회하며 노드의 메모리 해제
void clear(TreeNode* root) {
	if (root == NULL)return;
	clear(root->left);
	clear(root->right);
	free(root);
}