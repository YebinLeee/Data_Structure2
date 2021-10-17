# 트리 (Tree)
- 선형 구조(Linear Data Structure) - 리스트(배열, 연결 리스트), 스택, 큐
- 계층적인 구조 (Hierarchial Data Structure)
  - 트리, 이진 탐색 트리 (binary search tree)
  - 결정 트리 (decision tree)

<br>

<details>
  <summary> 트리의 용어 </summary>
  

- 트리 : 한 개 이상의 노드로 이루어진 유한 집합
- 노드(node) : 트리의 구성 요소
- 루트(root) 노드와 나머지 노드들인 서브 트리(subtree)
- 간선(edge) : 루트와 서브 트리를 연결
- 자식 노드(children node)
- 단말 노드(leaf node, terminal node) : 자식 노드가 없는 노드 / 비단말 노드(nonterminal node)

<br>

- 차수(degree) : 어떤 노드가 가지고 있는 자식 노드의 개수
- 트리의 차수 : 노드의 차수 중 가장 큰 값
- 레벨(level) : 트리의 각 층에 매기는 번호 (루트: 레벨 1)
- 높이(height) : 트리가 가지고 있는 최대 레벨

</details>

<br>

# 이진 트리(Binary Tree)
- 모든 노드가 2개의 서브트리를 가지고 있는 트리
- 최대 2개의 자식 노드 존재 가능, 모든 노드의 차수는 2 이하
- 왼쪽 서브트리와 오른쪽 서브트리로 구분 
<br>

### 이진 트리의 성질
- n개의 노드를 가진 이진 트리는 n-1 개읙 ㅏㄴ선을 가진다.
- 높이가 h인 이진트리의 경우, 최소 h개의 노드, 최대 (2^h-1)개의 노드를 가진다.
- n개의 노드를 가진 이진트리의 높이는 최대 n 또는 최소 log2(n+1) 이다. (실수인 경우, 반올림)

<br>

- 완전 이진트리(complete binary tree) : 높이가 k일때, 레벨 1부터 (k-1)까지는 노드가 모두 채워져 있으며, 마지막 레벨 k에서는 왼쪽부터 오른쪽으로 노드가 순서대로 채워져 있는 이진 트리
<br>

### 이진 트리의 표현
1. 배열 표현법
	- 저장하고자 하는 이진 트리를 완전 이진 트리라 가정하고, 이진 트리의 깊이가 k일때, (2^k-1) 개의 공간 연속적으로 할당하여 번호대로 노드들 저장
		- 부모 노드 인덱스 = (자식노드 인덱스)/2
		- 왼쪽 자식 노드인덱스 = (부모노드 인덱스)*2
		- 오른쪽 자식 노드 인덱스 = (부모노드 인덱스)*2 + 1
	- 배열의 단점: 완전 이진트리가 아닌 일반적인 이진트리의 경우 기억공간의 낭비가 심하며, 데이터의 삽입/삭제 시 비효율적
2. 링크 표현법
	- 노드 구조체 (데이터 필드, 왼쪽/오른쪽 자식 노드 링크 필드)

<br>

### 이진 트리 노드의 구조체

```C
// 이진 트리 노드 구조체
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

```
<br>

## 이진 트리의 순회
- 순회(tranversal) : 이진트리에 속하는 모든 노드를 한 번씩 방문하여 노드가 가지고 있는 데이터를 목적에 맞기 처리하는 것
- 순회의 방법 : 루트(V) 방문 왼쪽 서브트리(L)과 오른쪽 서브트리(R) 방문의 순서에 따라
	1. `전위 순회(VLR, preorder traversal)` : 루트노드 -> 왼쪽 서브트리 -> 오른쪽 서브트리 
	2. `중위 순회(VLR, inorder raversal)` : 왼쪽 서브트리 -> 루트노드 -> 오른쪽 서브트리
	3. `후위 순회(LRV, postorder traversal)` : 왼쪽 서브트리 -> 오른쪼 서브트리 -> 루트노드
<br>
<details>
  <summary> 순환을 이용한 순회 (전위, 중위, 후위) </summary>
	
- 트리의 루트를 매개변수로 하여 왼쪽 또는 오른쪽 서브트리를 방문
- 서브트리의 루트 노드 포인터를 함수의 매개변수로 전달
- 노드를 방문한다는 의미는 노드의 자료를 출력하는 것으로 정의
<br>
	
```C
// 중위 순회
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[ %2d ] ", root->data);
		inorder(root->right);
	}
}
  
// 전위 순회
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[ %2d ] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
  
// 후위 순회
void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[ %2d ] ", root->data);
	}
}
```
  
</details>
  
  
<details>
  
  <summary> 반복을 이용한 순회 -  </summary>
  
- 왼쪽 노드들이 NULL에 도달할 때까지 스택에 추가되었다가, NULL에 도달하면 스택에서 노드를 하나씩 꺼내어
- 해당 노드의 오른쪽 노드로 이동
- 오른쪽 노드들에 대하여 NULL에 도달할 때까지 왼쪽 노드들을 스택에 추가하기를 반복
<br>
	
```C
void inorder_iter(TreeNode* root) {
	while (1) {
		// NULL에 도달할 때 까지 왼쪽 노드들을 스택에 추가
		for (;root;root = root->left)
			push(root);
		// 스택에서 하나씩 삭제되어 
		root = pop();
		if (!root)break;
		// 방문한 후 오른쪽 노드로 
		printf("[%d] ", root->data);
		root = root->right;
	}
}
 ```
<br>
  
Stack의 push, pop 연산
  
```C
#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p) {
	if (top < SIZE - 1)
		stack[++top] = p;
}

TreeNode* pop() {
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}
```

	
</details>
		
<details>
  <summary> 레벨 순회 (Level Order) - 큐 구조 </summary>
 
- 레벨이 1인 루트노드부터, 각 노드를 레벨 순으로 검사
- 동일한 레벨의 경우 좌에서 우로 방문
- 큐에 있는 노드를 꺼내 방문한 다음, 그 노드의 자식 노드를 큐에 삽입하기를 반복
<br>
	
  
```C
void level_order(TreeNode* ptr) {
	QueueType q;

	init_queue(&q);

	if (ptr == NULL) return;

	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}
```
	
	
<br>
노드 큐 구조
	
```C
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

#define MAX_QUEUE_SIZE 100
typedef TreeNode* element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
```
  
</details>
		

<br>

	
	
### 수식 계산 트리 
	
<details>
	<summary> 후위 순회 (순환 구조) </summary>
	
	
```C
// 수식 계산 함수
int evaluate(TreeNode* root) {
	int op1, op2;
	
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return root->data;
	else {
		op1 = evaluate(root->left);
		op2 = evaluate(root->right);
		printf("%d %c %d 을 계산합니다. \n", op1, root->data, op2);
		switch (root->data) {
		case '+':
			return op1 + op2;
		case '-':
			return op1 - op2;
		case '*':
			return op1 * op2;
		case '/':
			return op1 / op2;
		}
	}
	return 0;
}
	
```
	
</details>
	
<br>
	
### 추가 연산
	
<details>
	<summary> 전체 노드의 개수 </summary>
	
```C
// 전체 노드의 개수 (루트 노드 + 왼쪽 서브 트리 + 오른쪽 서브트리)
int get_node_count(TreeNode* node) {
	int count = 0;

	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);

	return count;
}	
```
</details>

<details>
	<summary> 높이, 레벨 구하기 </summary>

```C
// 트리 높이 구하기 (왼쪽 서브트리, 오른쪽 서브트리 중 더 높은 값)
int get_height(TreeNode* node) {
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}
```
	
</details>
	
<details>
	<summary> 단말 노드의 개수 </summary>

```C
// 단말 노드 개수 (왼쪽/오른쪽 자식이 동시에 0인 경우)
int get_leaf_count(TreeNode* node) {
	int count = 0;

	if (node != NULL)
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_node_leaf(node->left) + get_node_leaf(node->right);

	return count;
}
```

</details>
	
	
<details>
	<summary> 파일의 용량 사이즈 구하기 (후위 순회) </summary>

```C

int calc_dir_size(TreeNode* root) {
	int left_size, right_size;
	if (root == NULL) return 0;

	left_size = calc_dir_size(root->left);
	right_size = calc_dir_size(root->right);
	return (root->data + left_size + right_size);
}
```
		
</details>
	
	
<br>
<hr>
<br>
	
## 스레드 이진 트리 (Threaded Binary Tree)
	
### 스레드 이진 트리의 구조체

```C
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
	int is_thread; // 스레드이면 True
}TreeNode;
```
	
<br>

<details>
	<summary> 스레드 중위 순회 </summary>
	

```C

// 중위 후속자를 찾는 함수
TreeNode* find_successor(TreeNode* p) {
	TreeNode* q = p->right; // p의 오른쪽 포인터
	// 오른쪽 포인터가 NUL이거나 스레드이면 오른쪽 포인터를 반환
	if (q == NULL || p->is_thread == TRUE)
		return q;

	// 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
	while (q->left != NULL)
		q = q->left;
	return q;
}

// 스레드 중위 순회
void thread_inorder(TreeNode* t) {
	TreeNode* q;

	q = t;
	while (q->left)		// 가장 왼쪽 노드로 이동
		q = q->left;
	do {
		printf("%c -> ", q->data);	// 데이터 출력
		q = find_successor(q);		// 후속자 함수 호출
	} while (q);
}

```

</details>
	
<br>
<hr>
<br>
	
# 이진 탐색 트리 (Binary Search Tree)
	
### 탐색
	
<details>
	<summary> 1. 순환적인 탐색 함수 </summary>
	
```C
// 순환적 탐색 함수
TreeNode* search(TreeNode* node, int key) {
	TreeNode* p = node;

	if (node == NULL) return NULL;  // 탐색 실패한 경우(마지막 노드까지 도달)

	if (key == node->data) return node; // 탐색 성공한 경우 해당 노드 주소 반환
	else if (key > node->data)
		search(node->right, key);
	else
		search(node->left, key);
}	
```
	
</details>
	

<details>
	<summary> 2. 반복적인 탐색 함수 </summary>

```C
// 반복적 탐색 함수
TreeNode* search2(TreeNode* node, int key) {
	while (node != NULL) {
		if (key == node->data)return node; // 탐색 성공한 경우 해당 노드 주소 반환
		else if (key < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return NULL; // 탐색에 실패한 경우 NULL반환
}
```
	
</details>

### 삽입
	
<details>
	<summary> 1. 순환적인 삽입 </summary>
	
```C
// 트리의 새로운 노드 동적 할당
TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

// 탐색 후 특정 위치에 새로운 key를 갖는 노드 삽입
TreeNode* insert_node(TreeNode* node, int key) {
	
	// 트리가 공백이면 새로운 노드를 반환
	if (node == NULL)return new_node(key);
	
	if (key < node->data)
		node->left = insert_node(node->left, key);
	else if (key > node->data)
		node->right = insert_node(node->right, key);

	// 변경된 루트 포인터 반환
	return node;
}
```
	
</details>
	
<details>
	<summary> 2. 반복적인 삽입 </summary>
	
```C
// 노드 삽입 (반복)
void insert_node_iter(TreeNode** root, int key) {
	TreeNode* p, * t;	// p: 부모노드, t: 현재노드
	TreeNode* n;		// n: 새로운 노드

	t = *root;
	p = NULL;
	while (t != NULL) {
		if (key == t->key)return;
		p = t;
		if (key < t->key)t = t->left;
		else t = t->right;
	}

	// key가 트리 안에 없으므로 삽입
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL)return;
	n->key = key;
	n->left = n->right = NULL;

	// 부모 노드와 링크 연결
	if (p != NULL)
		if (key < p->key)p->left = n;
		else p->right = n;
	else *root = n;
}
```
	
</details>
	
### 삭제

<details>	
	<summary> 탐색 후 삭제 </summary>
	
```C

// 가장 왼쪽 단말 노드 탐색
TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

// 노드 탐색 후 삭제
TreeNode* delete_node(TreeNode* root, int key) {
	if (root == NULL) return root;

	// 탐색
	if (key < root->data)
		root->left = delete_node(root->left, key);
	else if (key > root->data)
		root->right = delete_node(root->right, key);
	// 탐색 성공한 경우 (key==root->data)
	else {
		// 왼쪽 자식 노드가 없는 경우 - 오른쪽 자식 노드 연결
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		// 오른쪽 자식 노드가 없는 경우 - 왼쪽 자식 노드 연결
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// 세번째 경우
		// 오른쪽 서브트리에서 가장 왼쪽 단말 노드 탐색
		TreeNode* temp = min_value_node(root->right);

		// 중외 순회시 후계 노드 복사
		root->data = temp->data;
		// 중외 순회시 후계 노드 삭제
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}
```
	
</details>

	
