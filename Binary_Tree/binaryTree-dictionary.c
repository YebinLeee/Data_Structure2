/*

이진 탐색 트리를 이용한 영어 사전 프로그램
두 단어의 단어와 뜻을 출력
i: 삽입, d: 삭제, s: 탐색
p: 전체 출력, q:종료

파일에서 읽어 먼저 단어의 개수가 몇개인지 세고, 그 개수만큼 동적할당하기
단어의 길이도 고려하기

** 중복되는 데이터가 삽입되는 경우, 단어 뜻이 추가해야 함
-> compare() 값이 같은 경우도 포함하기
-> 의미가 가변적 (노드의 데이터 필드를 연결리스트로 사용)
-> insert_first 해도 됨

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

// 요소
typedef struct element {
	char* word;
	char* meaning;
}element;

// 연결 리스트의 노드
typedef struct ListNode {
	element data;
	struct LisNode* link;
}ListNode;

// 트리의 노드
typedef struct TreeNode {
	ListNode *key;
	struct TreeNode* left, * right;
}TreeNode;



void error(char* message) {
	fprintf(stderr, "%s \n", message);
	exit(1);
}

int compare(char* e1, char* e2) {
	return strcmp(e1, e2);
}

void display(TreeNode* p) {
	ListNode* q;

	if (p != NULL) {
		display(p->left);
		// 리스트의 모든 meaning 출력
		printf("단어: %s, 의미: ", p->key->data.word);
		q = p->key;
		while (q != NULL) {
			printf("%s, ", q->data.meaning);
			q = q->link;
		}
		printf("\b\b  \n\n");
		display(p->right);
	}
}

TreeNode* search(TreeNode* root, char* word) {
	TreeNode* p = root;

	while (p != NULL) {
		if (compare(word, p->key->data.word) == 0)
			return p;
		else if (compare(word, p->key->data.word) < 0)
			p = p->left;
		else if (compare(word, p->key->data.word) > 0)
			p = p->right;
	}
	return p; // 탐색에 실패한 경우 NULL 바놘
}

ListNode* insert_first(ListNode* head, element new_data) {
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));

	new_node->data = new_data;
	new_node->link = head;

	head = new_node;
	return head;
}

TreeNode* new_node(element item) {
	TreeNode* temp = (TreeNode*)malloc((sizeof(TreeNode)));
	temp->key = NULL;
	temp->key = insert_first(temp->key, item);
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, element new_word) {
	if (node == NULL) return new_node(new_word);

	if (compare(new_word.word, node->key->data.word) < 0)
		node->left = insert_node(node->left, new_word);
	else if (compare(new_word.word, node->key->data.word) > 0)
		node->right = insert_node(node->right, new_word);
	else if (compare(new_word.word, node->key->data.word)==0) {
		node->key = insert_first(node->key, new_word);
	}

	return node;
}

TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;
	while (current != NULL)
		current = current->left;
	return current;
}
TreeNode* delete_node(TreeNode* root, char word) {
	ListNode* q, * next;
	if (root == NULL) return root;

	if (compare(word, root->key->data.word) < 0)
		root->left = delete_node(root->left, word);
	if (compare(word, root->key->data.word) > 0)
		root->right = delete_node(root->right, word);
	// 키가 루트와 같은 경우
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			// 리스트도 모두 삭제하기
			q = root->key;
			while (q != NULL) {
				next = q->link;
				free(q->data.word);
				free(q->data.meaning);
				q = next;
			}
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			q = root->key;
			while (q != NULL) {
				next = q->link;
				free(q->data.word);
				free(q->data.meaning);
				q = next;
			}
			free(root);
			return temp;
		}

		TreeNode* temp = min_value_node(root->right); // 오른쪽 서브트리에서 가장 작은 갑

		root->key = temp->key;
		root->right = delete_node(root->right, word);
	}
	return root;
}

int main() {
	FILE* fp;
	TreeNode* root = NULL;
	TreeNode* p = NULL;

	char word[100], meaning[200];

	int wordCount = 0;

	element temp;
	// ListNode nodeTmp;

	char command;

	/*
	파일로부터 먼저 문자 읽어 명령 수행
	i: 탐색 후 삽입
	-> 위치
	-> 같은 것이 나오면 연결 리스트에 meaning 추가
	s: 검색 (탐색)
	d: 탐색 후 삭제
	p: 전체 데이터 출력
	q: 종료
	*/

	fp = fopen("data.txt", "rt");
	if (fp == NULL) error("파일 열기 실패");

	while (!feof(fp)) {
		fscanf(fp, " %c", &command);
		// printf("%c :: ", command);

		if (command == 'i') { // 삽입
		// 파일에서 리스트 노드 입력 받기
			fscanf(fp, "%s %s", word, meaning);
			// printf("추가 %s : %s \n", word, meaning);

			temp.word = (char*)malloc(sizeof(word));
			temp.meaning = (char*)malloc(sizeof(meaning));
			
			strcpy(temp.word, word);
			strcpy(temp.meaning, meaning);

			root = insert_node(root, temp);
		}

		// 탐색
		else if (command == 's') {
			fscanf(fp, "%s", word);
			printf("================= 탐색 %s ================== \n", word);

			p = search(root, word);
			if (p == NULL) printf("%s 탐색 실패 \n", word);
			else printf("%s %s \n", p->key->data.word, p->key->data.meaning);
		}

		// 삭제
		else if (command == 'd') {
			fscanf(fp, "%s", word);
			printf("=================== 삭제 %s ================== \n", word);
			root = delete_node(root, word);
		}

		// 출력
		else if (command == 'p') {
			printf("================== 전체 출력 =================== \n");
			display(root);
		}

		else if (command == 'q') break;

	}

	// clear(root);

	fclose(fp);

	return 0;
}
