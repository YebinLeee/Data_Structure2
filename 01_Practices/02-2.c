/*
���Ϸκ��� �л��� �������� �о� ����ü�� ���� �Ҵ��� �̿��� ���� ����Ʈ�� �����ϰ�,
				����ڷκ��� �Է� �޴� �޴��� ���� �۵��ϴ� �л� ���� ���� ���α׷�
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// �л� ����ü
typedef struct Student {
	int id;
	char name[9]; // �̸��� 4���ڱ��� ����
	int math, kor, eng;
	int sum;
	double avg;
}Student;

// ���� ����Ʈ ��� ����ü
typedef struct ListNode {
	Student data;
	struct ListNode* link;
}ListNode;

// �Լ� ����
void print_menu();
void insert_last(ListNode** head, ListNode** prev, Student new_data);
void print_list(ListNode* head);
Student add_data();
void search(ListNode* head);
void clear(ListNode* head);

int main() {
	FILE* fp;				// ���� ������
	ListNode* head = NULL, * last = NULL;	// �л� ���� ���� ����Ʈ�� head������
	Student tmp;			// ���Ϸκ��� �д� �л� ������ �����ϴ� �ӽ� ����ü
	int getMenu;			// �޴�-�Է� �޴� ����

	// ���� �б� ���� �б�
	fp = fopen("data.txt", "rt");
	if (fp == NULL) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}

	// ���Ͽ��� ���� �л� ������ ����Ʈ�� �������� �����ϱ�
	while (!feof(fp)) {
		fscanf(fp, "%d %s %d %d %d", &tmp.id, tmp.name, &tmp.math, &tmp.eng, &tmp.kor);
		tmp.sum = tmp.math + tmp.eng + tmp.kor;
		tmp.avg = tmp.sum / 3.0;
		insert_last(&head, &last, tmp);
	}
	printf("<<���� ���� ���α׷�>>");

	// 0�� �޴� �Է¹��� ������ �ݺ��Ͽ� ���� ���� ���α׷� ����
	while (1) {
		print_menu();
		scanf("%d", &getMenu);
		if (getMenu == 0) break;
		switch (getMenu) {
		case 1:search(head); break;
		case 2:print_list(head); break;
		case 3:
			tmp = add_data(); // �л� �����͸� ���� �޾� tmp�� ����
			insert_last(&head, &last, tmp); // head ����������, ������ ��� last ����������
			break;
		default:break;
		}
	}
	clear(head); // ����Ʈ�� ��� ��� ����
	fclose(fp); // ���� �ݱ�
}

void print_menu() {
	printf("\n>> -0- ����\n");
	printf(">> -1- �˻�\n");
	printf(">> -2- ���\n");
	printf(">> -3- �߰�\n\n");
}

// ����Ʈ�� ���� ���ο� �л� ������ ��带 �߰�
void insert_last(ListNode** head, ListNode** prev, Student new_data) {
	// ���ο� ��� ���� �Ҵ� �� �л� ������ ����
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->data = new_data;
	new_node->link = NULL;

	if (*head == NULL)				// �� ����Ʈ�� ���
		*head = new_node;			// ù ��� �����Ϳ� ���ο� ����� �ּ� ����
	else							// �� ����Ʈ�� �ƴ� ���
		(*prev)->link = new_node;	// ���� ������ ����� link�� ���� ����� �ּ� ����

	*prev = new_node; // �߰��� ���ο� ��� �ּҸ� ������ ����� �����͸� ����Ű�� prev ���� �����Ϳ� ����
}

// ����Ʈ�� �����ϰ��� �ϴ� �л� ������ �Է¹ޱ�
Student add_data() {
	Student tmp;	// �Է¹޴� �������� ������ �ӽ� ����ü
	char name[9];	// �л��� �̸��� �ӽ÷� ������ ���ڹ迭 

	// ����ڿ��� �л� ���� �Է¹޾� tmp����ü�� ����
	printf("�߰��� �л� �̸� : ");
	scanf("%s", name);
	strcpy(tmp.name, name); // ����ü�� name ����� ���ڿ� ����

	printf("�й� : "); scanf("%d", &tmp.id);
	printf("���� ���� : "); scanf("%d", &tmp.math);
	printf("���� ���� : "); scanf("%d", &tmp.eng);
	printf("���� ���� : "); scanf("%d", &tmp.kor);

	tmp.sum = tmp.math + tmp.eng + tmp.kor;
	tmp.avg = tmp.sum / 3.0;

	return tmp;
}

void print_list(ListNode* head) {
	ListNode* p = head;

	printf("|=======================================|\n");
	printf("| ��   �� |  �� �� | ���� | ���� | ���� | \n");
	printf("|=======================================|\n");

	while (p != NULL) {
		printf("| %d|  %s| %3d  | %3d  | %3d  |\n", p->data.id, p->data.name,
			p->data.math, p->data.eng, p->data.kor);
		p = p->link;
	}
	printf("|=======================================|\n\n");
}

// �й� �˻��Ͽ� �л� ���� ���
void search(ListNode* head) {
	ListNode* p = head;
	int id;

	printf("�˻��� �й� : ");
	scanf("%d", &id);

	while (p != NULL) {
		if (p->data.id == id) { // �Է¹��� id�� ������ ����� id�� �����Ѵٸ� ���
			printf(" < �̸� : %s > \n", p->data.name);
			printf(" < ���� : %3d�� > \n", p->data.math);
			printf(" < ���� : %3d�� > \n", p->data.eng);
			printf(" < ���� : %3d�� > \n", p->data.kor);
			printf(" < ���� : %3d�� > \n", p->data.sum);
			printf(" < ��� : %3d�� > \n\n", (int)p->data.avg);
			return;
		}
		p = p->link;
	}
	printf("�й� %d �˻� ����\n\n", id);
}

// ����Ʈ�� ��� ��� �޸� ����
void clear(ListNode* head) {
	ListNode* p, * next;	// �޸𸮸� ������ ��带 ����Ű�� ������ p�� ���� ��带 ����Ű�� ������ next

	p = head;				// p�� head���� null���� ��带 ��ȸ�ϸ� �޸� ����
	while (p != NULL) {		// p�� null �� �ƴ� ������ �ݺ�
		next = p->link;		// ���� ��� �ּҸ� next�� ����
		free(p);			// p�� ����Ű�� ����� �޸� ����
		p = next;			// ������ ���� ��� �ּҸ� p�� ������ ����
	}
}