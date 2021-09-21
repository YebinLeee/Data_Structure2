/*
	작성자: 이예빈(20204059)
	작성일: 2021.09.15
	프로그램명: 파일에 저장되어 있는 문자와 학생 데이터를 바탕으로,
			연결리스트에 저장하고, 리스트의 데이터를 삭제하고, 전체 목록을 출력하는 프로그램
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 구조체
typedef struct Student {
	// 학번, 이름, 점수, 키
	int id;
	char* name;
	int total;
	double height;
}Student;

// 리스트의 노드 구조체
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
	ListNode* head = NULL, * new_node = NULL; // 리스트 head 포인터, 새 노드
	Student tmp;		// 임시 학생 구조체
	int id;				// 삭제하고자 하는 학생의 학번
	char name[20];		// 임시 문자열
	char menu;			// i: insert, d: 삭제, p: 리스트 출력

	fp = fopen("data.txt", "rt");
	if (fp == NULL) error("파일 열기 실패");

	while (!feof(fp)) {
		fscanf(fp, "%c", &menu);	// 동작할 메뉴 값 읽기

		if (menu == 'i') {			// 학생 데이터 삽입
			fscanf(fp, "%d %s %d %lf", &tmp.id, name, &tmp.total, &tmp.height);

			ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));	// 새로운 노드 동적 할당
			if (new_node == NULL) error("새로운 노드 동적 할당 실패");
			else {
				new_node->data = tmp;									// 데이터 필드에 tmp 구조체 대입
				new_node->data.name = (char*)malloc(sizeof(name));		// name 데이터 필드에 메모리 동적 할당
				strcpy(new_node->data.name, name);						// name 문자열을 name 필드에 복사

				head = insert_first(head, new_node);	// 생성된 새로운 노드를 리스트의 처음에 삽입
			}
		}
		else if (menu == 'd') {		// 학번 검색하여 해당 학생 정보 삭제
			fscanf(fp, "%d", &id);	// 탐색할 id값
			head = search_delete(head, id);
		}
		else if (menu == 'p')		// 리스트 전체 출력
			print_list(head);
	}

	clear(head);	// 리스트의 전체 노드 메모리 해제
	fclose(fp);		// 파일 닫기
}

void error(char* message) {
	fprintf(stderr, "%s \n", message);
	exit(1);
}

// 새로운 노드를 리스트의 처음에 삽입
ListNode* insert_first(ListNode* head, ListNode* new_node) {
	new_node->link = head;	// 새로운 노드의 링크 필드에 헤드 포인터값 대입
	head = new_node;		// 다시 head에는 새로운 노드의 주소 대입
	printf(">> %s(%d)의 학생의 모든 정보가 삽입되었습니다, \n", new_node->data.name, new_node->data.id);
	return head;
}

void print_list(ListNode* head) {
	ListNode* p = head;
	int cnt = 1; // 목록의 인덱스는 1부터 시작

	printf("\n============= 학생 리스트 출력 ============= \n");
	while (p != NULL) {
		printf("%2d %10d %20s %3d %5.1lf\n", cnt++, p->data.id, p->data.name, p->data.total, p->data.height);
		p = p->link;
	}
	printf("============================================\n\n");
}

// 학번 탐색하여 삭제
ListNode* search_delete(ListNode* head, int key) {
	ListNode* p = head, * prev = head;

	while (p != NULL) {
		// 전체 노드 순회하며, 노드의 id 데이터필드가 key값과 동일한 경우를 탐색
		if (p->data.id == key) {
			if (p == head)	head = p->link; // 첫 노드인 경우에는 head에는 두번쨰 노드의 주소 삽입
			else prev->link = p->link;		// 다음 노드를 이전 노드와 연결
			printf(">> %s(%d)의 학생의 모든 정보가 삭제되었습니다. \n", p->data.name, p->data.id);
			free(p);
			return head; // 노드 삭제 후 헤드 포인터 반환
		}
		prev = p;		// 이전 노드를 현재 노드로 변경
		p = p->link;	// 다음 노드로 이동
	}
	// 리스트 전체 순회 후 탐색 실패하는 경우
	printf("학번 %d 탐색 실패\n", key);
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