# 그래프 (Graph)

- 그래프: 객체 사이의 연결 관계를 표현할 수 있는 자료구조
- 그래프의 표현: 인접 행렬, 인접 리스트
- 그래프의 요소: 정점(vertex, node), 간선(edge, link)
- 그래프의 종류
  1. 무방향(undirected) 그래프: 간선을 통해서 두 정점의 양뱡향을 갈 수 있는 그래프
     - (A, B) == (B, A)
  3. 방향(directed) 그래프: 간선에 방향성이 존재하는 그래프
      - <A, B> != <B, A>
- 인접 정점(adjacent vertext): 간선에 의해 직접 연결된 정점
- 정점의 차수(무방향 그래프) : 정점에 인접한 정점의 수
- 진입 차수(방향 그래프) : 외부에서 오는 간선의 개수, 진출 차수 : 외부로 향하는 간선의 개수


<br>

## 그래프의 추상 데이터 타입
- 객체: `정점`의 집합, `간선`의 집합
- 연산
  - `create_grapgh(g)` : 그래프 생성
  - `init(g)` : 그래프 초기화
  - `insert_vertex(g)` : 정점 v 삽입
  - `insert_edge(g, u, v)` : 간선 (u,v) 삽입
  - `delete_vertex(g, v)` : 정점 v 삭제
  - `delete_edge(g, u, v)` : 간선 (u,v) 삭제
  - `is_empty(g)` : 그래프 공백 상태 여부
  - `adjacent(v)` : 정점 v에 인접한 정점들의 리스트 반환
  - `destroy_graph(g)` : 그래프 제거


<br>

## 1. 인접 행렬

### 그래프의 추상 데이터 타입 GraphType
```C
#define MAX_VERTICES 50
typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // (nXn) 인접 행렬
}GraphType;
```

<details>
  <summary> 그래프 초기화 </summary>
  
  - 정점의 개수를 0으로, 인접 행렬의 모든 요소 값을 0으로 초기화
  
  
```C
// 그래프 초기화
void init(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0;r < MAX_VERTICES;r++)
		for (c = 0;c < MAX_VERTICES;c++)
			g->adj_mat[r][c] = 0;
}
```
  
</details>

<details>
  <summary> 정점 삽입 연산 </summary>
  
  - GrapghType 구조체의 n을 1 증가시키는 연산
  
```C
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if ((g->n + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}  
```
  
</details>

</details>

<details>
  <summary> 간선 삽입 연산 </summary>
  
  - (무방향그래프) 두 정점에 대한 배열 요소 값을 1로 설정
  
```C
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
```
  
</details>

</details>

<details>
  <summary> </summary>
  
```C
  
```
  
</details>

</details>

<details>
  <summary> </summary>
  
```C
  
```
  
</details>


