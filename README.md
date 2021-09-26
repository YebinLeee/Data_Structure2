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

</details>
	
<details>
	<summary> 트리의 높이 </summary>

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
	
	
