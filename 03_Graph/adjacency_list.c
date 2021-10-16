// 인접 리스트 구현

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct GraphNode { // 인접 리스트의 노드
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {	// 인접 리스트
	int n;
	GraphNode* adj_list[MAX_VERTICES]; // 인접 리스트 배열
}GraphType;

// 그래프 초기화
void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0;v < MAX_VERTICES;v++)
		g->adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정저의 개수 초과");
		return;
	}
	g->n++;
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

// 그래프의 모든 메모리 해제
void destroy_graph(GraphType* g) {
	GraphNode* p, * next;
	int v = 0;

	for (v = 0;v < g->n;v++) {
		p = g->adj_list[v];
		while (p != NULL) {
			next = p->link;
			free(p);
			p = next;
		}
	}
	free(g);
}

// 정점의 차수 계산하기
int get_degree(GraphType* g, int v) {
	int cnt = 0;
	GraphNode* p = g->adj_list[v];

	while (p != NULL) {
		p = p->link;
		cnt++;
	}
	return cnt;
}

int main() {
	GraphType* g;
	int i = 0;
	g = (GraphType*)malloc(sizeof(GraphType));

	init(g);
	for (i = 0;i < 4;i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 1);
	insert_edge(g, 1, 0);
	insert_edge(g, 0, 3);
	insert_edge(g, 3, 0);
	insert_edge(g, 1, 3);
	insert_edge(g, 3, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 3, 2);

	for (i = 0;i < 4;i++)
		printf("%d번 정점의 차수 : %d\n", i, get_degree(g, i));

	destroy_graph(g);
	return 0;
}
