/*
	작성자: 이예빈(20204059)
	작성일: 2021.09.15
	프로그램명: 파일 입출력과 동적 할당, 연결 리스트를 이용하여 학생 정보를 저장하고,
				리스트의 학생 데이터를 학번, 이름, 총점에 따라 정렬하는 프로그램
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 구조체
typedef struct student {
	// 학번, 이름, 총점
	int id;
	char* name; // 이름에 대한 문자열 동적 할당 받을 포인터
	int total;
}Student;

// 연결 리스트 노드 구조체
typedef struct ListNode {
	Student data;
	struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, ListNode* new_node);
ListNode* sortBy_id(ListNode* head);	// 선배 먼저 (오름차순)
ListNode* sortBy_name(ListNode* head);	// ㄱ 먼저 (오름차순)
ListNode* sortBy_total(ListNode* head);	// 높은 점수 먼저 (내림차순)
void print_list(ListNode* head);
void clear(ListNode* head);

int main() {
	FILE* fp = NULL;
	Student tmp;			// 파일로부터 읽은 학생 정보를 저장할 학생 구조체
	ListNode* head = NULL;	// 학생 정보를 담을 연결 리스트의 head 포인터
	char name[20];			// 파일에서 읽는 학생의 이름 데이터를 저장할 문자열

	// 파일 열기. (실패 코드 포함)
	fp = fopen("data.txt", "rt");
	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패");
		exit(1);
	}

	// 학생 데이터 파일에서 읽으며 동적 할당 후 리스트에 삽입
	while (!feof(fp)) {
		fscanf(fp, "%d %s %d", &tmp.id, name, &tmp.total);

		ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));	// 새로운 노드 동적 할당
		new_node->data = tmp;	// 새로운 노드의 데이터 필드에 파일에 읽은 tmp 값 저장(id, total)
		new_node->data.name = (char*)malloc(sizeof(name));	// 데이터 필드의 name 포인터에 메모리 동적 할당
		if (new_node == NULL || new_node->data.name == NULL) { // 노드, 또는 name 멤버의 동적 할당 오류시
			printf("동적 할당 오류 \n");
			exit(1);
		}
		strcpy(new_node->data.name, name); // 새로운 노드 구조체의 name 메모리 영역에 name문자열을 복사

		head = insert_first(head, new_node); // 리스트에 첫 노드로 삽입
	}
	printf("========= < student list > =========\n\n");		// 리스트 출력
	print_list(head);

	printf("\n========== < sort By id > ==========\n\n");	// 학번 오름차순 정렬 후 출력
	head = sortBy_id(head);
	print_list(head);

	printf("\n========= < sort By name > =========\n\n");	// 이름 오름차순(사전식) 정렬 후 출력
	head = sortBy_name(head);
	print_list(head);

	printf("\n========= < sort By total > =========\n\n");	// 총점 내림차순 정렬 후 출력
	head = sortBy_total(head);
	print_list(head);

	clear(head);	// 메모리 해제
	fclose(fp);		// 파일 닫기
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

	if (head == NULL) return; // 빈 리스트의 경우
	do {
		p = head;							// head 포인터에 대하여 정렬 반복
		sorted = 0;							// 정렬 여부 확인 (초깃값=0)
		while (p->link != q) {				// p의 다음 노드가 q일 때까지 반복하여 현재 노드와 다음 노드의 데이터 크기 비교
			// 다음 노드 데이터의 id값이 현재 노드의 것보다 큰 경우 두 구조체의 데이터를 교환(오름차순)
			if (p->data.id > p->link->data.id) {
				tmp = p->data;
				p->data = p->link->data;
				p->link->data = tmp;
				sorted = 1;					// 한 번이라도 정렬이 된 경우, 값을 1로 변경
			}
			p = p->link;					// 다음 노드로 이동
		}
		q = p;								// 순회를 마무리한 마무리 p 포인터 값을 q에 대입
	} while (sorted);						// sorted가 1일 때까지 반복

	return head;
}

ListNode* sortBy_name(ListNode* head) {
	ListNode* p = head, * q = NULL;
	Student tmp;
	int sorted;

	if (head == NULL) return; // 빈 리스트의 경우
	do {
		p = head;
		sorted = 0;
		while (p->link != q) {
			// strcmp 함수를 이용해 다음 노드의 문자열의 순서가 앞에 온다면 두 구조체의 데이터를 교환(사전식 오름차순)
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
			// 다음 노드 데이터의 total 멤버 값이 현재 노드의 것보다 작은 경우 두 구조체의 데이터값을 변경(내림차순)
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