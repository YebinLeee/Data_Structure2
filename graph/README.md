# 그래프 (Graph)

- 그래프: 객체 사이의 연결 관계를 표현할 수 있는 자료구조
- 그래프의 표현
	1. 인접 행렬(adjacency matrix) : 2차원 배열 (n개의 정점에 대해, nXn 행렬)
	2. 인접 리스트(adjacency list) : 연결 리스트 (n개의 정점에 대해, n개의 연결 리스트)
- 그래프의 요소: 정점(vertex/node), 간선(edge/link)
<br>

- 그래프의 종류
  1. 무방향(undirected) 그래프: 간선을 통해서 두 정점의 양뱡향을 갈 수 있는 그래프
     - (A, B) == (B, A)
  3. 방향(directed) 그래프: 간선에 방향성이 존재하는 그래프
      - <A, B> != <B, A>
 <br>
 
- 인접 정점(adjacent vertext): 간선에 의해 직접 연결된 정점
- 정점의 차수(무방향 그래프) : 정점에 인접한 정점의 수
- (방향 그래프) 진입 차수 : 외부에서 오는 간선의 개수 / 진출 차수 : 외부로 향하는 간선의 개수


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
- n개의 정점 수에 대해, nXn의 2차원 배열로 표현
- 간선 (i,j)에 대하여 해당 배열 요소의 값(M[i][j] 또는 무방향 그래프인 경우 M[i][i]) 을 0에서 1로 변경
- 무방향 그래프의 인접 행렬은 대칭 행렬이며, 대각 성분의 값은 모두 0
- n^2 개의 메모리 공간을 필요로 하므로, 희소 그래프(sparse graph)보다는 밀집 그래프(dense grapgh)를 표현하기에 적합
<br>

시간 복잡도
- 간선 (i,j)의 존재 여부 (M[i][j]) : `O(1)`
- 정점 i의 차수 (M[i]의 모든 요소 값의 합) : `O(n)`
- 모든 간선의 개수 (행렬 M의 모든 요소 값의 합) : `O(n^2)`



<br>

### 인접 행렬의 추상 데이터 타입
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
  
  - GraphType 구조체의 n 멤버의 값을 1 증가시키는 연산
  
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

<details>
	<summary> 정점의 차수 구하기 </summary>
	
- i번째 행의 모든 요소의 값의 합 계산
	
```C
// 정점 v의 차수 구하기
int get_degree(GraphType* g, int v) {
	int i, sum = 0;
	for (i = 0;i < g->n;i++)
		sum += g->adj_mat[v][i];
	return sum;
}
```
</details>
	
<br>


## 2. 인접 리스트 
- 각각의 정점에 인접한 정점들을 연결 리스트의 노드들로 표현하는 그래프 구조
- 헤더 노드들(정점의 번호 저장)이 하나의 배열로 구성된 구조
- 정점 수 n, 간선의 수 e인 무방향 그래프 -> n개의 연결 리스트, 총 2e개의 노드 
- 간선의 개수가 적은 희소 그래프(sparse grapgh) 표현에 저합
<br>

시간 복잡도
- 정점 i의 차수, 또는 간선 (i, j)의 존재 여부 : 리스트의 노드 수만큼
- 전체 간선 수: `O(n+e)`

<br>

### 인접 리스트의 추상 데이터 타입

```C
#define MAX_VERTICES

typedef struct GraphNode { // 인접 리스트의 노드
	int vertex;
	struct GrapghNode* link;
}GraphNode;

typedef struct GraphType {	// 인접 리스트
	int n;
	GraphNode* adj_list[MAX_VERTICES]; // 인접 리스트 배열
}GraphType;
```
<br>

<details>
  <summary> 그래프 초기화</summary>

- GraphType 구조체의 멤버 n의 값을 0으로 초기화
- adj_list 포인터 배열의 요소들을 NULL 값으로 초기화
	
```C
// 그래프 초기화
void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0;v < MAX_VERTICES;v++)
		g->adj_list[v] = NULL;
}  
```
  
</details>

</details>

<details>
  <summary> 정점 삽입 연산</summary>
  
```C
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정저의 개수 초과");
		return;
	}
	g->n++;
}  
```
  
</details>

<details>
	<summary> 간선 삽입 연산</summary>

- 새로운 노드를 동적할당 받아 u번 리스트에 v의 정점을 vertex로 하는 노드를 맨 처음에 삽입
	
	
```C
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
```
</details>

<details>
	<summary> 그래프 메모리 해제 </summary>

- 그래프의 포인터 배열의 각 리스트의 모든 노드의 메모리 해제
	
```C
// 그래프의 모든 메모리 해제
void destroy_graph(GraphType* g) {
	GraphNode* p, * next;
	int v = 0;

	for (v = 0;v < g->n;v++) {
		p = g->adj_list[v];
		// 포인터 배열의 각 리스트의 모든 노드들 메모리 해제
		while (p != NULL) {
			next = p->link;
			free(p);
			p = next;
		}
	}
	free(g); // 그래프 메모리 해제
}	
```
</details>

<details>
	<summary> 정점 차수 구하기 </summary>

- 리스트의 노드 개수 계산하기
	
```C
// 정점 v의 차수 계산하기
int get_degree(GraphType* g, int v) {
	int cnt = 0;
	GraphNode* p = g->adj_list[v];
		
	// v번 리스트의 노드 개수 구하기
	while (p != NULL) {
		p = p->link;
		cnt++;
	}
	return cnt;
}	
```
</details>

<br><hr><br>
	
# 그래프의 탐색
	
## 1. 깊이 우선 탐색 (DFS: Depth First Search)

- 시작 정점에서 한 방향으로 계속 가다가 더이상 갈 수 없게 되면 다시 가장 가까운 갈림길로 돌아와서 다른 방향으로 다시 탐색을 진행하기를 반복하는 방법
- 방문 visited 플래그 표시 (배열 visited: 방문 여부 기록 (FALSE로 초기화, 방문한 경우 TRUE로 변경) )
- 방문하지 않은 정점을 선택하여 깊이 우선 탐색을 하고, 탐색이 종료되면 인접한 정점들 중 방문이 안 된 정점을 찾아 탐색 하기를 반복
- backtracking -> `순환 알고리즘` 사용
<br>
	
### 1) 인접 행렬을 이용한 DFS

### 순환 호출
- adj_mat[v][u] 값이 1이고, visited[w] 가 FALSE라면 깊이 우선 탐색 진행
	
```C
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES]; // 0(FALSE) 초기값

// 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = TRUE; // 정점 v의 방문 표시
	printf("정점 %d -> ", v);
	
	for (w = 0;w < g->n;w++)
		// v에 대해 w가 인접 정점이고, w가 방문하지 않은 노드의 경우
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w); // 정점 w에서 DFS 시작 (순환)
}

```
	
<br>
	
### 2) 인접 리스트를 이용한 DFS
- adj_list[v] 리스트의 노드를 방문하며 인접 정점을 탐색하며, 노드의 정점 w에 대해 visited[w]가 FALSE라면 깊이 우선 탐색 진행
	
```C
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES];

// 인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE;
	printf("정점 %d -> ", w);
	// 인접 정점 탐색
	for (w = g->adj_list[v];w;w = w->link)
		if (!visited[w->vertex])
			dfs_list(g, w);	// 정점 w에서 DFS 새로 시작
}
```
<br>
	
### 명시적 스택 

- 스택에 첫번째 정점을 삽입하는 것으로 시작
- 스택에서 삭제한 정점에 대해, 해당 정점과 인접한 정점들 중 방문하지 않은 정점을 스택에 모두 삽입
- 다시 스택에서 정점을 삭제하며 위 과정을 반복 
<br>
	
<details>
	<summary> 스택 구현 </summary>

```C
typedef int element;
typedef struct StackType {
	int top;
	element data[MAX_VERTICES];
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}
int is_empty(StackType* s) {
	return (s->top == -1);
}
int is_full(StackType* s) {
	return(s->top == MAX_VERTICES + 1);
}
void push(StackType* s, element item) {
	s->data[++s->top] = item;
}
element pop(StackType* s) {
	return s->data[s->top--];
}

#define TRUE 1
#define FALSE 0
element visited[MAX_VERTICES];
```
</details>
	
1) 인접 행렬
	
```C
// 명시적 스택(인접행렬)을 이용한 깊이우선 탐색
void dfs_iterative_mat(GraphType* g, element v) {
	StackType* s;
	element w;

	// 스택 생성
	s = (StackType*)malloc(sizeof(StackType));
	init_stack(s);
	
	push(s, v);
	while (!is_empty(s)) {
		v = pop(s);
		if (!visited[v]) {
			visited[v] = TRUE;
			printf("정점 %d -> ", v);
			// 정점 v에 대하여
			for (w = 0;w < g->n;w++) {
				// 인접한 모든 정점들 중 방문하지 않은 정점은 스택에 삽입
				if (g->adj_mat[v][w] && !visited[w])
					push(s, w);
			}
		}
	}
	free(s);
}
```
<br>

2. 인접 리스트
	
```C
// 명시적 스택(인접 리스트)를 이용한 깊이우선 탐색 구현
void dfs_iterative_list(GraphType* g, element v) {
	StackType* s;
	GraphNode* w;

	// 스택 생성
	s = (StackType*)malloc(sizeof(StackType));
	init_stack(s);

	push(s, v); // 첫번째 요소 삽입
	while (!is_empty(s)) {
		v = pop(s);// 
		if (!visited[v]) { // pop한 v가 방문하지 않은 정점이라면
			visited[v] = TRUE; // TRUE로 변경
			printf("정점 %d -> ", v);
			// v 정점 리스트에 대해 모든 정점들 방문하며
			for (w = g->adj_list[v];w;w = w->link)
				if (!visited[w->vertex]) // 방문하지 않은 정점을
					push(s, w->vertex); // 스택에 삽입 하여 dfs 시작
		}
	}
	free(s);
}

```
	
### 2. 넓이 우선 탐색 (BFS: Breadth First Search)
	
<details>
	<summary> </summary>

```C
	
```
</details>

<details>
	<summary> </summary>

```C
	
```
</details>



