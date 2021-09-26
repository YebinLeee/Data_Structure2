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
  
</detils>

 
  
