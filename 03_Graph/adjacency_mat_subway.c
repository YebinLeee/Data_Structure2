/*
	작성자 : 이예빈(20204059)
	작성일 : 2021.10.16
	프로그램명 : 인접 행렬로 표현하는 지하철 노선 그래프
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GraphType {
	int n;	// 정점의 개수
	int **adj_mat;
}GraphType;

// 그래프 초기화 (인접행렬 동적 할당)
void init(GraphType* g, int size) {
	int v, w;
	g->n = size;
	g->adj_mat = (int**)malloc(sizeof(int*)*size);
	for (v = 0;v < size;v++) {
		g->adj_mat[v] = (int*)malloc(sizeof(int)*size);
		for (w = 0;w < size;w++)
			g->adj_mat[v][w] = 0; // 배열의 모든 요소 값을 0으로 초기화
	}
}

// 간선 삽입 연산 (방향 그래프)
void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
}

void print_adj_mat(GraphType* g) {
	int r, c;
	for (r = 0;r < g->n;r++) {
		for (c = 0;c < g->n;c++)
			printf("%2d ", g->adj_mat[r][c]);
		printf("\n");
	}
}

int searchName(char** list,int size, char* key) {
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

// 그래프의 모든 메모리 해제
void destroy_graph(GraphType* g) {
	int v;
	for (v = 0;v < g->n;v++) {
		free(g->adj_mat[v]);
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
	
	// 파일 읽어 list 문자열 포인터 배열에 저장
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
	
	// (size x size)크기의 인접 행렬 동적 할당
	init(g, size);

	rewind(fp);
	// 다시 파일 읽어 인접 행렬에 저장 (인덱스 구하여 간선 삽입)
	while (!feof(fp)) {
		fscanf(fp, "%s %s", first, second);
		// first, second 문자열이 저장돼있는 list의 인덱스 start, end 구하기
		start = findIndex(list, size, first);
		end = findIndex(list, size, second);
		insert_edge(g, start, end); // 간선 (start, end) 삽입
	}

	print_adj_mat(g);	// 그래프 인접 행렬 출력
	destroy_graph(g);	// 그래프 인접 행렬 메모리 해제
	free(g);			// 그래프 메모리 해제
	fclose(fp);			// 파일 닫기
	return 0;
}
