/*

���� Ž�� Ʈ���� �̿��� ���� ���� ���α׷�
�� �ܾ��� �ܾ�� ���� ���
i: ����, d: ����, s: Ž��
p: ��ü ���, q:����

���Ͽ��� �о� ���� �ܾ��� ������ ����� ����, �� ������ŭ �����Ҵ��ϱ�
�ܾ��� ���̵� �����ϱ�

** �ߺ��Ǵ� �����Ͱ� ���ԵǴ� ���, �ܾ� ���� �߰��ؾ� ��
-> compare() ���� ���� ��쵵 �����ϱ�
-> �ǹ̰� ������ (����� ������ �ʵ带 ���Ḯ��Ʈ�� ���)
-> insert_first �ص� ��

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

// ���
typedef struct element {
	char* word;
	char* meaning;
}element;

// ���� ����Ʈ�� ���
typedef struct ListNode {
	element data;
	struct LisNode* link;
}ListNode;

// Ʈ���� ���
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
		// ����Ʈ�� ��� meaning ���
		printf("�ܾ�: %s, �ǹ�: ", p->key->data.word);
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
	return p; // Ž���� ������ ��� NULL �ٳ�
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
	// Ű�� ��Ʈ�� ���� ���
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			// ����Ʈ�� ��� �����ϱ�
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

		TreeNode* temp = min_value_node(root->right); // ������ ����Ʈ������ ���� ���� ��

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
	���Ϸκ��� ���� ���� �о� ���� ����
	i: Ž�� �� ����
	-> ��ġ
	-> ���� ���� ������ ���� ����Ʈ�� meaning �߰�
	s: �˻� (Ž��)
	d: Ž�� �� ����
	p: ��ü ������ ���
	q: ����
	*/

	fp = fopen("data.txt", "rt");
	if (fp == NULL) error("���� ���� ����");

	while (!feof(fp)) {
		fscanf(fp, " %c", &command);
		// printf("%c :: ", command);

		if (command == 'i') { // ����
		// ���Ͽ��� ����Ʈ ��� �Է� �ޱ�
			fscanf(fp, "%s %s", word, meaning);
			// printf("�߰� %s : %s \n", word, meaning);

			temp.word = (char*)malloc(sizeof(word));
			temp.meaning = (char*)malloc(sizeof(meaning));
			
			strcpy(temp.word, word);
			strcpy(temp.meaning, meaning);

			root = insert_node(root, temp);
		}

		// Ž��
		else if (command == 's') {
			fscanf(fp, "%s", word);
			printf("================= Ž�� %s ================== \n", word);

			p = search(root, word);
			if (p == NULL) printf("%s Ž�� ���� \n", word);
			else printf("%s %s \n", p->key->data.word, p->key->data.meaning);
		}

		// ����
		else if (command == 'd') {
			fscanf(fp, "%s", word);
			printf("=================== ���� %s ================== \n", word);
			root = delete_node(root, word);
		}

		// ���
		else if (command == 'p') {
			printf("================== ��ü ��� =================== \n");
			display(root);
		}

		else if (command == 'q') break;

	}

	// clear(root);

	fclose(fp);

	return 0;
}