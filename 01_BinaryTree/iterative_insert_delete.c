#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
}TreeNode;


TreeNode* new_node(int key) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->key = key;
	node->left = node->right = NULL;
	return node;
}

// 노드 삽입 (순환)
TreeNode* insert_recursive(TreeNode* root, int key) {
	if (root == NULL) return new_node(key);
	
	if (key > root->key)
		root->right=insert_recursive(root->right, key);
	else if (key < root->key)
		root->left=insert_recursive(root->left, key);

	return root; // 변경된 루트 반환
	
}
// 노드 삽입 (반복)
void insert_iterative(TreeNode** root, int key) {
	TreeNode* p, * t;	// p: 부모노드, t: 현재노드
	TreeNode* n;		// n: 새로운 노드

	// t: 삽입할 위치, p: 삽입할 위치의 부모 노드
	t = *root;
	p = NULL;
	// 삽입 위치 탐색 (같은 키값을 가진 노드가 이미 존재하는 경우 종료)
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
	else *root = n; // 부모 노드가 없는 경우(첫 노드인 경우) 루트에 새로운 노드 삽입
}

// 노드 탐색 (반복)
TreeNode* search_iterative(TreeNode* root, int key) {

	while (root != NULL) {
		if (key == root->key) return root;
		else if (key > root->key)
			root = root->right;
		else if (key < root->key)
			root = root->left;
	}
	return NULL;
}

// 노드 삭제 (반복)
void delete_iterative(TreeNode** root, int key) {
	// 탐색 후 삭제
	// p: 부모
	// child: 
	TreeNode* p, * child, * succ, * succ_p, * t;

	// key를 갖는 노드 t 탐색, p는 t의 부모노드
	p = NULL;
	t = *root;

	// 먼저 트리에 키 값이 있는지 탐색
	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;
	}
	// 탐색 종료, 

	// 탐색이 종료된 시점에 t가 NULL이면 탐색 실패
	if (t == NULL) {
		printf("key is not in the tree \n");
		return;
	}

	// 첫번쨰 경우: 단말 노드인 경우
	if (t->left == NULL && t->right == NULL) {
		if (p != NULL) {
			// 부모노드의 자식필드를 NULL로 변경
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else
			*root = NULL; // 부모노드가 NULL이면 삭제되는 노드가 루트
	}

	// 두번째 경우: 하나의 자식만 가지는 경우
	else if ((t->left == NULL) || t->right == NULL) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			// 부모를 자식과 연결
			if (p->left == t) p->left = child;
			else p->right = child;
		}
		else // 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = child;
	}
	// 세번째 경우: 두개의 자식을 가지는 경우
	else {
		printf("두 개 자식 \n\n");

		// 오른쪽 서브트리에서 후계자를 찾는다.
		succ_p = t;
		succ = t->right;
		// 후계자를 찾아 계속 왼쪽으로 이동
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		// 후속자의 부모와 자식 연결
		if (succ_p->left = succ)
			succ_p->left = succ->right;
		else succ_p->right = succ->right;

		// 후속자가 가진 키 값을 현재 노드에 복사
		t->key = succ->key;
		// 원래의 후속자 삭제
		t = succ;
	}
	free(t);
}

// 트리에서 가장 작은 값 탐색 (가장 왼쪽 노드)
TreeNode* min_value_node(TreeNode* root) {
	TreeNode* current = root;
	while (current->left != NULL)
		current = current->left;
	return current;
}

// 노드 삭제 (순환)
TreeNode* delete_recursive(TreeNode* root, int key) {
	TreeNode* temp;

	// 삭제하려는 노드 탐색
	if (root == NULL)return root; // 탐색 실패
	if (key > root->key)
		root->right = delete_recursive(root->right, key);
	else if (key < root->key)
		root->left = delete_recursive(root->left, key);
	else { // 탐색성공 (key == root->key)
		if (root->left == NULL) {
			printf("root->left==NULL \n");
			temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			printf("root->right==NULL \n\n");
			temp = root->left;
			free(root);
			return temp;
		}
		else { // 왼쪽, 오른쪽 서브트리 모두 존재하는 경우
			temp = min_value_node(root->right);
			printf("%d 후계 노드 삭제 필요 \n\n", temp->key);
			// 후계 노드의 데이터 복사
			root->key = temp->key;

			// 후계 노드 (temp->key를 가진 노드 삭제 : 단말 노드이므로 메모리 해제)
			root->right = delete_recursive(root->right, temp->key);
		}
	}
	return root;
}

// 전위 순회
void preorder(TreeNode* root) {
	if(root != NULL) {
		printf("%d ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

int main() {
	TreeNode* root = NULL;

	root=insert_recursive(root, 5);
	root=insert_recursive(root, 3);
	root=insert_recursive(root, 8);
	root=insert_recursive(root, 9);
	root=insert_recursive(root, 7);
	root = insert_recursive(root, 6);

	preorder(root);
	printf("\n");

	// root=delete_recursive(root, 5);
	delete_iterative(&root, 5);
	preorder(root);
	printf("\n");

}
