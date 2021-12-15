/*
���� ����°� ���� �Ҵ�, ���� ����Ʈ�� �̿��Ͽ� �л� ������ �����ϰ�,
				����Ʈ�� �л� �����͸� �й�, �̸�, ������ ���� �����ϴ� ���α׷�
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �л� ����ü
typedef struct student {
	// �й�, �̸�, ����
	int id;
	char* name; // �̸��� ���� ���ڿ� ���� �Ҵ� ���� ������
	int total;
}Student;

// ���� ����Ʈ ��� ����ü
typedef struct ListNode {
	Student data;
	struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, ListNode* new_node);
ListNode* sortBy_id(ListNode* head);	// ���� ���� (��������)
ListNode* sortBy_name(ListNode* head);	// �� ���� (��������)
ListNode* sortBy_total(ListNode* head);	// ���� ���� ���� (��������)
void print_list(ListNode* head);
void clear(ListNode* head);

int main() {
	FILE* fp = NULL;
	Student tmp;			// ���Ϸκ��� ���� �л� ������ ������ �л� ����ü
	ListNode* head = NULL;	// �л� ������ ���� ���� ����Ʈ�� head ������
	char name[20];			// ���Ͽ��� �д� �л��� �̸� �����͸� ������ ���ڿ�

	// ���� ����. (���� �ڵ� ����)
	fp = fopen("data.txt", "rt");
	if (fp == NULL) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}

	// �л� ������ ���Ͽ��� ������ ���� �Ҵ� �� ����Ʈ�� ����
	while (!feof(fp)) {
		fscanf(fp, "%d %s %d", &tmp.id, name, &tmp.total);

		ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));	// ���ο� ��� ���� �Ҵ�
		new_node->data = tmp;	// ���ο� ����� ������ �ʵ忡 ���Ͽ� ���� tmp �� ����(id, total)
		new_node->data.name = (char*)malloc(sizeof(name));	// ������ �ʵ��� name �����Ϳ� �޸� ���� �Ҵ�
		if (new_node == NULL || new_node->data.name == NULL) { // ���, �Ǵ� name ����� ���� �Ҵ� ������
			printf("���� �Ҵ� ���� \n");
			exit(1);
		}
		strcpy(new_node->data.name, name); // ���ο� ��� ����ü�� name �޸� ������ name���ڿ��� ����

		head = insert_first(head, new_node); // ����Ʈ�� ù ���� ����
	}
	printf("========= < student list > =========\n\n");		// ����Ʈ ���
	print_list(head);

	printf("\n========== < sort By id > ==========\n\n");	// �й� �������� ���� �� ���
	head = sortBy_id(head);
	print_list(head);

	printf("\n========= < sort By name > =========\n\n");	// �̸� ��������(������) ���� �� ���
	head = sortBy_name(head);
	print_list(head);

	printf("\n========= < sort By total > =========\n\n");	// ���� �������� ���� �� ���
	head = sortBy_total(head);
	print_list(head);

	clear(head);	// �޸� ����
	fclose(fp);		// ���� �ݱ�
}

ListNode* insert_first(ListNode* head, ListNode* new_node) {
	new_node->link = head;
	head = new_node;
	return head;
}

ListNode* sortBy_id(ListNode* head) {
	ListNode* p = head, * q = NULL;
	Student tmp;
	int sorted;

	if (head == NULL) return; // �� ����Ʈ�� ���
	do {
		p = head;							// head �����Ϳ� ���Ͽ� ���� �ݺ�
		sorted = 0;							// ���� ���� Ȯ�� (�ʱ갪=0)
		while (p->link != q) {				// p�� ���� ��尡 q�� ������ �ݺ��Ͽ� ���� ���� ���� ����� ������ ũ�� ��
			// ���� ��� �������� id���� ���� ����� �ͺ��� ū ��� �� ����ü�� �����͸� ��ȯ(��������)
			if (p->data.id > p->link->data.id) {
				tmp = p->data;
				p->data = p->link->data;
				p->link->data = tmp;
				sorted = 1;					// �� ���̶� ������ �� ���, ���� 1�� ����
			}
			p = p->link;					// ���� ���� �̵�
		}
		q = p;								// ��ȸ�� �������� ������ p ������ ���� q�� ����
	} while (sorted);						// sorted�� 1�� ������ �ݺ�

	return head;
}

ListNode* sortBy_name(ListNode* head) {
	ListNode* p = head, * q = NULL;
	Student tmp;
	int sorted;

	if (head == NULL) return; // �� ����Ʈ�� ���
	do {
		p = head;
		sorted = 0;
		while (p->link != q) {
			// strcmp �Լ��� �̿��� ���� ����� ���ڿ��� ������ �տ� �´ٸ� �� ����ü�� �����͸� ��ȯ(������ ��������)
			if (strcmp(p->data.name, p->link->data.name) > 0) {
				tmp = p->data;
				p->data = p->link->data;
				p->link->data = tmp;
				sorted = 1;
			}
			p = p->link;
		}
		q = p;
	} while (sorted);

	return head;
}
ListNode* sortBy_total(ListNode* head) {
	ListNode* p = head, * q = NULL;
	Student tmp;
	int sorted;

	if (head == NULL) return;
	do {
		p = head;
		sorted = 0;
		while (p->link != q) {
			// ���� ��� �������� total ��� ���� ���� ����� �ͺ��� ���� ��� �� ����ü�� �����Ͱ��� ����(��������)
			if (p->data.total < p->link->data.total) {
				tmp = p->data;
				p->data = p->link->data;
				p->link->data = tmp;
				sorted = 1;
			}
			p = p->link;
		}
		q = p;
	} while (sorted);
	return head;
}

void print_list(ListNode* head) {
	ListNode* p = head;
	while (p != NULL) {
		printf("%d %s %d\n", p->data.id, p->data.name, p->data.total);
		p = p->link;
	}
}

void clear(ListNode* head) {
	ListNode* p, * next;

	p = head;
	while (p != NULL) {
		next = p->link;
		free(p);
		p = next;
	}
}