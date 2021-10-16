/*
	작성자: 이예빈(20204059)
	작성일: 2021.09.13
	프로그램명: 파일에서 정수 자료를 읽어, 동적으로 메모리를 할당 받아 연결 리스트에 저장하고,
				리스트에 저장된 정수들을 버블 정렬을 사용하여 오름차순으로 정렬하여 출력한다.
*/

#include <stdio.h>
#include <stdlib.h>

// 연결 리스트의 노드 구조체 선언
typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// 함수 원형 선언
ListNode* insert_first(ListNode* head, element value);
void print_list(ListNode* head);
void bubble_sort(ListNode* head);
void clear(ListNode* head);

int main() {
	FILE* fp;					// 파일 포인터
	ListNode* list = NULL;		// 연결 리스트의 헤드 포인터
	element tmp;				// 데이터를 임시로 저장할 element형 변수 tmp

	// 파일 열기 (오류 코드 포함)
	fp = fopen("data.txt", "rt");
	if (fp == NULL) {
		fprintf(stderr, "파일 읽기 오류");
		exit(1);
	}

	// 파일로부터 정수 자료를 하나씩 읽어 연결 리스트에 추가
	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		list = insert_first(list, tmp);
	}

	// 오름차순으로 버블 정렬 후, 연결 리스트 출력
	bubble_sort(list);
	print_list(list);

	clear(list);	// 연결 리스트의 모든 노드 해제
	fclose(fp);		// 파일 닫기
}

// 리스트의 첫번째 노드로 삽입
ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); // ListNode 노드 구조체 동적 할당

	p->data = value;	// 데이터 삽입
	p->link = head;		// 노드의 link에 head 포인터의 주소 대입
	head = p;			// head 포인터를 새로운 노드 p의 주소 대입 
	return head;		// 변경된 head 포인터 반환
}

void print_list(ListNode* head) {
	ListNode* p;
	for (p = head; p->link != NULL; p = p->link) // head부터 마지막 노드의 전 노드까지 순회하여 출력
		printf("%d -> ", p->data);
	printf("%d \n", p->data);	// 마지막 노드의 데이터는 줄바꿈과 함께 출력
}

// 버블 정렬을 이용한 오름차순 정렬
void bubble_sort(ListNode* head) {
	ListNode* p = head, * q = NULL;
	element tmp;
	int sorted;

	if (head == NULL) return; // 빈 리스트의 경우
	do {
		p = head;							// head 포인터에 대하여 정렬 반복
		sorted = 0;							// 정렬 여부 확인 (초깃값=0)
		while (p->link != q) {				// p의 다음 노드가 q일 때까지 반복하여 현재 노드와 다음 노드의 데이터 크기 비교
			if (p->data > p->link->data) {	// 다음 노드의 데이터가 현재 노드의 데이터보다 큰 경우 두 값을 변경
				tmp = p->data;
				p->data = p->link->data;
				p->link->data = tmp;
				sorted = 1;					// 한 번이라도 정렬이 된 경우, 값을 1로 변경
			}
			p = p->link;					// 다음 노드로 이동
		}
		q = p;								// 순회를 마무리한 마무리 p 포인터 값을 q에 대입
	} while (sorted);						// sorted가 1일 때까지 반복
}

// 첫 노드부터 차례대로 리스트의 모든 노드 메모리 해제 (delete_first)
void clear(ListNode* head) {
	ListNode* removed = head;	// 메모리를 해제하고자 하는 노드를 가리키는 포인터

	if (head == NULL) return;	// 빈 리스트의 경우
	while (head != NULL) {		// head 포인터부터 순회하며 차례대로 노드의 메모리 해제
		removed = head;			// 제거하고자 하는 노드의 주소는 첫 head 포인터
		head = removed->link;	// head 포인터에 제거하는 노드의 다음 노드의 주소 대입
		free(removed);			// removed 포인터가 가리키는 노드 메모리 해제
	}
}