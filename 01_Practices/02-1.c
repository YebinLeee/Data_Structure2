/*
���Ͽ��� ���� �ڷḦ �о�, �������� �޸𸮸� �Ҵ� �޾� ���� ����Ʈ�� �����ϰ�,
				����Ʈ�� ����� �������� ���� ������ ����Ͽ� ������������ �����Ͽ� ����Ѵ�.
*/

#include <stdio.h>
#include <stdlib.h>

// ���� ����Ʈ�� ��� ����ü ����
typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// �Լ� ���� ����
ListNode* insert_first(ListNode* head, element value);
void print_list(ListNode* head);
void bubble_sort(ListNode* head);
void clear(ListNode* head);

int main() {
	FILE* fp;					// ���� ������
	ListNode* list = NULL;		// ���� ����Ʈ�� ��� ������
	element tmp;				// �����͸� �ӽ÷� ������ element�� ���� tmp

	// ���� ���� (���� �ڵ� ����)
	fp = fopen("data.txt", "rt");
	if (fp == NULL) {
		fprintf(stderr, "���� �б� ����");
		exit(1);
	}

	// ���Ϸκ��� ���� �ڷḦ �ϳ��� �о� ���� ����Ʈ�� �߰�
	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		list = insert_first(list, tmp);
	}

	// ������������ ���� ���� ��, ���� ����Ʈ ���
	bubble_sort(list);
	print_list(list);

	clear(list);	// ���� ����Ʈ�� ��� ��� ����
	fclose(fp);		// ���� �ݱ�
}

// ����Ʈ�� ù��° ���� ����
ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); // ListNode ��� ����ü ���� �Ҵ�

	p->data = value;	// ������ ����
	p->link = head;		// ����� link�� head �������� �ּ� ����
	head = p;			// head �����͸� ���ο� ��� p�� �ּ� ���� 
	return head;		// ����� head ������ ��ȯ
}

void print_list(ListNode* head) {
	ListNode* p;
	for (p = head; p->link != NULL; p = p->link) // head���� ������ ����� �� ������ ��ȸ�Ͽ� ���
		printf("%d -> ", p->data);
	printf("%d \n", p->data);	// ������ ����� �����ʹ� �ٹٲް� �Բ� ���
}

// ���� ������ �̿��� �������� ����
void bubble_sort(ListNode* head) {
	ListNode* p = head, * q = NULL;
	element tmp;
	int sorted;

	if (head == NULL) return; // �� ����Ʈ�� ���
	do {
		p = head;							// head �����Ϳ� ���Ͽ� ���� �ݺ�
		sorted = 0;							// ���� ���� Ȯ�� (�ʱ갪=0)
		while (p->link != q) {				// p�� ���� ��尡 q�� ������ �ݺ��Ͽ� ���� ���� ���� ����� ������ ũ�� ��
			if (p->data > p->link->data) {	// ���� ����� �����Ͱ� ���� ����� �����ͺ��� ū ��� �� ���� ����
				tmp = p->data;
				p->data = p->link->data;
				p->link->data = tmp;
				sorted = 1;					// �� ���̶� ������ �� ���, ���� 1�� ����
			}
			p = p->link;					// ���� ���� �̵�
		}
		q = p;								// ��ȸ�� �������� ������ p ������ ���� q�� ����
	} while (sorted);						// sorted�� 1�� ������ �ݺ�
}

// ù ������ ���ʴ�� ����Ʈ�� ��� ��� �޸� ���� (delete_first)
void clear(ListNode* head) {
	ListNode* removed = head;	// �޸𸮸� �����ϰ��� �ϴ� ��带 ����Ű�� ������

	if (head == NULL) return;	// �� ����Ʈ�� ���
	while (head != NULL) {		// head �����ͺ��� ��ȸ�ϸ� ���ʴ�� ����� �޸� ����
		removed = head;			// �����ϰ��� �ϴ� ����� �ּҴ� ù head ������
		head = removed->link;	// head �����Ϳ� �����ϴ� ����� ���� ����� �ּ� ����
		free(removed);			// removed �����Ͱ� ����Ű�� ��� �޸� ����
	}
}