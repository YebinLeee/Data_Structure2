/*
���Ͽ� ����Ǿ� �ִ� ���ڿ� �л� �����͸� ��������,
			���Ḯ��Ʈ�� �����ϰ�, ����Ʈ�� �����͸� �����ϰ�, ��ü ����� ����ϴ� ���α׷�
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �л� ����ü
typedef struct Student {
	// �й�, �̸�, ����, Ű
	int id;
	char* name;
	int total;
	double height;
}Student;

// ����Ʈ�� ��� ����ü
typedef struct ListNode {
	Student data;
	struct ListNode* link;
}ListNode;

void error(char* message);
ListNode* insert_first(ListNode* head, ListNode* new_node);
ListNode* search_delete(ListNode* head, int key);
void print_list(ListNode* head);
void clear(ListNode* head);

int main() {
	FILE* fp;
	ListNode* head = NULL, * new_node = NULL; // ����Ʈ head ������, �� ���
	Student tmp;		// �ӽ� �л� ����ü
	int id;				// �����ϰ��� �ϴ� �л��� �й�
	char name[20];		// �ӽ� ���ڿ�
	char menu;			// i: insert, d: ����, p: ����Ʈ ���

	fp = fopen("data.txt", "rt");
	if (fp == NULL) error("���� ���� ����");

	while (!feof(fp)) {
		fscanf(fp, "%c", &menu);	// ������ �޴� �� �б�

		if (menu == 'i') {			// �л� ������ ����
			fscanf(fp, "%d %s %d %lf", &tmp.id, name, &tmp.total, &tmp.height);

			ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));	// ���ο� ��� ���� �Ҵ�
			if (new_node == NULL) error("���ο� ��� ���� �Ҵ� ����");
			else {
				new_node->data = tmp;									// ������ �ʵ忡 tmp ����ü ����
				new_node->data.name = (char*)malloc(sizeof(name));		// name ������ �ʵ忡 �޸� ���� �Ҵ�
				strcpy(new_node->data.name, name);						// name ���ڿ��� name �ʵ忡 ����

				head = insert_first(head, new_node);	// ������ ���ο� ��带 ����Ʈ�� ó���� ����
			}
		}
		else if (menu == 'd') {		// �й� �˻��Ͽ� �ش� �л� ���� ����
			fscanf(fp, "%d", &id);	// Ž���� id��
			head = search_delete(head, id);
		}
		else if (menu == 'p')		// ����Ʈ ��ü ���
			print_list(head);
	}

	clear(head);	// ����Ʈ�� ��ü ��� �޸� ����
	fclose(fp);		// ���� �ݱ�
}

void error(char* message) {
	fprintf(stderr, "%s \n", message);
	exit(1);
}

// ���ο� ��带 ����Ʈ�� ó���� ����
ListNode* insert_first(ListNode* head, ListNode* new_node) {
	new_node->link = head;	// ���ο� ����� ��ũ �ʵ忡 ��� �����Ͱ� ����
	head = new_node;		// �ٽ� head���� ���ο� ����� �ּ� ����
	printf(">> %s(%d)�� �л��� ��� ������ ���ԵǾ����ϴ�, \n", new_node->data.name, new_node->data.id);
	return head;
}

void print_list(ListNode* head) {
	ListNode* p = head;
	int cnt = 1; // ����� �ε����� 1���� ����

	printf("\n============= �л� ����Ʈ ��� ============= \n");
	while (p != NULL) {
		printf("%2d %10d %20s %3d %5.1lf\n", cnt++, p->data.id, p->data.name, p->data.total, p->data.height);
		p = p->link;
	}
	printf("============================================\n\n");
}

// �й� Ž���Ͽ� ����
ListNode* search_delete(ListNode* head, int key) {
	ListNode* p = head, * prev = head;

	while (p != NULL) {
		// ��ü ��� ��ȸ�ϸ�, ����� id �������ʵ尡 key���� ������ ��츦 Ž��
		if (p->data.id == key) {
			if (p == head)	head = p->link; // ù ����� ��쿡�� head���� �ι��� ����� �ּ� ����
			else prev->link = p->link;		// ���� ��带 ���� ���� ����
			printf(">> %s(%d)�� �л��� ��� ������ �����Ǿ����ϴ�. \n", p->data.name, p->data.id);
			free(p);
			return head; // ��� ���� �� ��� ������ ��ȯ
		}
		prev = p;		// ���� ��带 ���� ���� ����
		p = p->link;	// ���� ���� �̵�
	}
	// ����Ʈ ��ü ��ȸ �� Ž�� �����ϴ� ���
	printf("�й� %d Ž�� ����\n", key);
	return head;
}

void clear(ListNode* head) {
	ListNode* p = head, * next;
	while (p != NULL) {
		next = p->link;
		free(p);
		p = next;
	}
}