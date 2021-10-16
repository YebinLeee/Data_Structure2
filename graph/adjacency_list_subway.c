/*
	작성자 : 이예빈(20204059)
	작성일 : 2021.10.16
	프로그램명 : 인접 리스트로 표현하는 지하철 노선 그래프
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GraphNode { // 인접 리스트의 노드
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {	// 인접 리스트
	int n;
	GraphNode** adj_list; // 인접 리스트 배열
}GraphType;

// 그래프 초기화 (인접리스트 동적 할당)
void init(GraphType* g, int size) {
	int i;
	g->n = size;
	// size 크기의 포인터 배열 할당 (GraphNode를 가리키는 포인터)
	g->adj_list = (GraphNode**)malloc(sizeof(GraphNode*)*size);
	for (i = 0;i < size;i++) // NULL값으로 초기화
		g->adj_list[i] = NULL;
}

// 간선(u,v) 삽입 연산
void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	// 리스트의 맨 처음에 삽입
	node->link = g->adj_list[u]; // 노드의 링크 필드에 u번째 리스트 주소 삽입
	g->adj_list[u] = node; // u번째 리스트의 헤더에 node 주소 삽입
}

int searchName(char** list, int size, char* key) {
	int i;
	for (i = 0;i < size;i++)
		if (strcmp(list[i], key) == 0)return 1;
	return 0;
}

int findIndex(char** list, int size, char* key) {
	int i;
	for (i = 0;i < size;i++) {
		if (strcmp(list[i], key) == 0) return i;
	}
	return 0;
}

void print_adj_list(GraphType* g, char**list) {
	GraphNode* v;
	int i = 0;
	for (i = 0;i < g->n;i++) {
		// 정점 list[i] 에 대하여
		printf("[%s] -> ", list[i]);
		v = g->adj_list[i];
		while (v != NULL) {
			printf("%s -> ", list[v->vertex]); // vertex에 해당하는 문자열 출력
			v = v->link;
		}
		printf("\b\b\b   \n");
	}
}

// 그래프의 모든 메모리 해제
void destroy_graph(GraphType* g) {
	GraphNode* p, * next;
	int v = 0;

	for (v = 0;v < g->n;v++) {
		p = g->adj_list[v];
		while (p != NULL) { // 각 노드 해제
			next = p->link;
			free(p);
			p = next;
		}
	}
}

int main() {
	FILE* fp;
	GraphType* g;
	char* list[100];
	int size = 0;
	char first[20], second[20];
	int start, end;

	g = (GraphType*)malloc(sizeof(GraphType));

	// 파일 읽어 char* 배열에 저장
	fp = fopen("data.txt", "rt");
	while (!feof(fp)) {
		fscanf(fp, "%s %s", first, second);
		if (searchName(list, size, first) == 0) {
			list[size] = (char*)malloc(strlen(first) + 1);
			strcpy(list[size++], first);
		}
		if (searchName(list, size, second) == 0) {
			list[size] = (char*)malloc(strlen(second) + 1);
			strcpy(list[size++], second);
		}
	}

	// size x size 의 인접 리스트 동적 할당(포인터 배열 공간 할당)
	init(g, size);

	rewind(fp);
	// 다시 파일 읽어 인접 리스트에 저장 (인덱스 구하여 간선 삽입)
	while (!feof(fp)) {
		fscanf(fp, "%s %s", first, second);
		// first, second 문자열이 저장돼있는 list의 인덱스 start, end 구하기
		start = findIndex(list, size, first);
		end = findIndex(list, size, second);
		insert_edge(g, start, end); // 간선 (start, end) 삽입
	}

	print_adj_list(g, list);	// 리스트 출력
	destroy_graph(g);			// 그래프 인접 리스트 메모리 해제
	free(g);					// 그래프 메모리 해제
	fclose(fp);					// 파일 닫기
	return 0;
}
