# Data_Structure2

## 이진 트리 (Binary Tree)

### 이진 트리 노드의 구조체

```C
// 이진 트리 노드 구조체
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

```
<details>
 
  <summary> 순환을 이용한 순회 (전위, 중위, 후위) </summary>
  
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
  
  <summary> 반복을 이용한 순회 (스택 구조) </summary>
  
```C
void inorder_iter(TreeNode* root) {
	while (1) {
		for (;root;root = root->left)
			push(root);
		root = pop();
		if (!root)break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}
 ```
  
  
Stack의 push, pop 연산
  
```C
  
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
	
  <summary> 레벨 순회 (큐 구조) </summary>
  
  
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
	
## 이진 탐색 트리 (Binary Search Tree)
	
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

	
