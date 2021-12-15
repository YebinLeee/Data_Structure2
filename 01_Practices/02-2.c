/*
	작성자: 이예빈(20204059)
	작성일: 2021.09.13
	프로그램명: 파일로부터 학생의 정보들을 읽어 구조체와 동적 할당을 이용해 연결 리스트에 저장하고,
				사용자로부터 입력 받는 메뉴에 따라 작동하는 학생 성적 관리 프로그램
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 학생 구조체
typedef struct Student {
	int id;
	char name[9]; // 이름은 4글자까지 가능
	int math, kor, eng;
	int sum;
	double avg;
}Student;

// 연결 리스트 노드 구조체
typedef struct ListNode {
	Student data;
	struct ListNode* link;
}ListNode;

// 함수 원형
void print_menu();
void insert_last(ListNode** head, ListNode** prev, Student new_data);
void print_list(ListNode* head);
Student add_data();
void search(ListNode* head);
void clear(ListNode* head);

int main() {
	FILE* fp;				// 파일 포인터
	ListNode* head = NULL, * last = NULL;	// 학생 정보 연결 리스트의 head포인터
	Student tmp;			// 파일로부터 읽는 학생 데이터 저장하는 임시 구조체
	int getMenu;			// 메뉴-입력 받는 정수

	// 파일 읽기 모드로 읽기
	fp = fopen("data.txt", "rt");
	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}

	// 파일에서 읽은 학생 데이터 리스트의 마지막에 삽입하기
	while (!feof(fp)) {
		fscanf(fp, "%d %s %d %d %d", &tmp.id, tmp.name, &tmp.math, &tmp.eng, &tmp.kor);
		tmp.sum = tmp.math + tmp.eng + tmp.kor;
		tmp.avg = tmp.sum / 3.0;
		insert_last(&head, &last, tmp);
	}
	printf("<<성적 관리 프로그램>>");

	// 0번 메뉴 입력받을 때까지 반복하여 성적 관리 프로그램 실행
	while (1) {
		print_menu();
		scanf("%d", &getMenu);
		if (getMenu == 0) break;
		switch (getMenu) {
		case 1:search(head); break;
		case 2:print_list(head); break;
		case 3:
			tmp = add_data(); // 학생 데이터를 전달 받아 tmp에 저장
			insert_last(&head, &last, tmp); // head 이중포인터, 마지막 노드 last 이중포인터
			break;
		default:break;
		}
	}
	clear(head); // 리스트의 모든 노드 해제
	fclose(fp); // 파일 닫기
}

void print_menu() {
	printf("\n>> -0- 종료\n");
	printf(">> -1- 검색\n");
	printf(">> -2- 목록\n");
	printf(">> -3- 추가\n\n");
}

// 리스트의 끝에 새로운 학생 데이터 노드를 추가
void insert_last(ListNode** head, ListNode** prev, Student new_data) {
	// 새로운 노드 동적 할당 후 학생 데이터 저장
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->data = new_data;
	new_node->link = NULL;

	if (*head == NULL)				// 빈 리스트인 경우
		*head = new_node;			// 첫 헤드 포인터에 새로운 노드의 주소 저장
	else							// 빈 리스트가 아닌 경우
		(*prev)->link = new_node;	// 가장 마지막 노드의 link에 현재 노드의 주소 저장

	*prev = new_node; // 추가된 새로운 노드 주소를 마지막 노드의 포인터를 가리키는 prev 이중 포인터에 저장
}

// 리스트에 삽입하고자 하는 학생 데이터 입력받기
Student add_data() {
	Student tmp;	// 입력받는 정보들을 저장할 임시 구조체
	char name[9];	// 학생의 이름을 임시로 저장할 문자배열 

	// 사용자에게 학생 정보 입력받아 tmp구조체에 저장
	printf("추가할 학생 이름 : ");
	scanf("%s", name);
	strcpy(tmp.name, name); // 구조체의 name 멤버에 문자열 복사

	printf("학번 : "); scanf("%d", &tmp.id);
	printf("수학 점수 : "); scanf("%d", &tmp.math);
	printf("영어 점수 : "); scanf("%d", &tmp.eng);
	printf("국어 점수 : "); scanf("%d", &tmp.kor);

	tmp.sum = tmp.math + tmp.eng + tmp.kor;
	tmp.avg = tmp.sum / 3.0;

	return tmp;
}

void print_list(ListNode* head) {
	ListNode* p = head;

	printf("|=======================================|\n");
	printf("| 학   번 |  이 름 | 수학 | 영어 | 국어 | \n");
	printf("|=======================================|\n");

	while (p != NULL) {
		printf("| %d|  %s| %3d  | %3d  | %3d  |\n", p->data.id, p->data.name,
			p->data.math, p->data.eng, p->data.kor);
		p = p->link;
	}
	printf("|=======================================|\n\n");
}

// 학번 검색하여 학생 정보 출력
void search(ListNode* head) {
	ListNode* p = head;
	int id;

	printf("검색할 학번 : ");
	scanf("%d", &id);

	while (p != NULL) {
		if (p->data.id == id) { // 입력받은 id와 동일한 노드의 id가 존재한다면 출력
			printf(" < 이름 : %s > \n", p->data.name);
			printf(" < 수학 : %3d점 > \n", p->data.math);
			printf(" < 영어 : %3d점 > \n", p->data.eng);
			printf(" < 국어 : %3d점 > \n", p->data.kor);
			printf(" < 총점 : %3d점 > \n", p->data.sum);
			printf(" < 평균 : %3d점 > \n\n", (int)p->data.avg);
			return;
		}
		p = p->link;
	}
	printf("학번 %d 검색 실패\n\n", id);
}

// 리스트의 모든 노드 메모리 해제
void clear(ListNode* head) {
	ListNode* p, * next;	// 메모리를 해제할 노드를 가리키는 포인터 p와 다음 노드를 가리키는 포인터 next

	p = head;				// p가 head부터 null까지 노드를 순회하며 메모리 해제
	while (p != NULL) {		// p가 null 이 아닐 때까지 반복
		next = p->link;		// 다음 노드 주소를 next에 저장
		free(p);			// p가 가리키는 노드의 메모리 해제
		p = next;			// 삭제될 다음 노드 주소를 p의 값으로 변경
	}
}