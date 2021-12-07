# 탐색

- 팀섹(search): 탐색키(serach key)와 데이터로 이루어진 여러 개의 항목 중에서 원하는 탐색키를 가지고 있는 항목을 찾는 것
<br>

정렬되지 않은 배열에서의 탐색
- [순차 탐색](https://github.com/YebinLeee/Data_Structure2/tree/main/06_Search#%EC%88%9C%EC%B0%A8-%ED%83%90%EC%83%89)

정렬된 배열에서의 탐색
- [이진 탐색](https://github.com/YebinLeee/Data_Structure2/tree/main/06_Search#%EC%9D%B4%EC%A7%84-%ED%83%90%EC%83%89)
- [색인 순차 탐색](https://github.com/YebinLeee/Data_Structure2/tree/main/06_Search#%EC%83%89%EC%9D%B8-%EC%88%9C%EC%B0%A8-%ED%83%90%EC%83%89)
- [보간 탐색](https://github.com/YebinLeee/Data_Structure2/tree/main/06_Search#%EB%B3%B4%EA%B0%84-%ED%83%90%EC%83%89)
- [AVL 트리 탐색](https://github.com/YebinLeee/Data_Structure2/tree/main/06_Search#%EB%B3%B4%EA%B0%84-%ED%83%90%EC%83%89)


<br><hr><br>



## 순차 탐색

- 순차 탐색(sequential search): 처음부터 마지막 항목까지 하나씩 검사하여 원하는 항목을 찾아가는 방법
<img src="https://user-images.githubusercontent.com/71310074/144171960-c4131936-396e-4446-8e0c-7f518d4aa932.png" width="700">
<br>


<details>
  <summary> 일반적인 순차 탐색 알고리즘 </summary>
 
```C
int seq_search(int key, int low, int high) {
	int i;
	for (i = low;i <= high;i++)
		if (list[i] == key)
			return i;
	return -1;			// 탐색에 실패한 경우 -1 반환
}
```
                            
 </details>
<br>
  
```C
// 개선된 순차 탐색
int sequential_search(int key, int low, int high) {
	int i;

	list[high + 1] = key;   // 리스트의 끝에 탐색키값을 저장
	for (i = low;list[i] != key;i++)	// 키값을 찾으면 종료
		;
	if (i == (high + 1))return -1;		// 탐색 실패
	else return i;			// 탐색 성공
}
```
- 리스트의 끝에 도달했는지 비교하는 연산 (`i<=high`)을 매번 하지 않아도 됨
  
<br>
  
### 순차 탐색의 시간 복잡도
- 탐색 성공시: 리스트에 있는 키의 위치에 따라 비교 횟수 결정 (평균 비교횟수 (n+1)/2)
- 탐색 실패시 비교 n번
- 시간 복잡도: `O(n)`
                                    

<br><hr><br>



## 이진 탐색
- 이진 탐색 (Binary Search): 배열의 중앙값을 기준으로, 탐색의 범위를 반으로 줄이며 탐색을 반복

<img src="https://user-images.githubusercontent.com/71310074/144171988-4ea1c65e-6a74-48c6-9ccb-1582c34de9c2.png" width="700">
<br>
	
1. 순환 호출
```C
// 순환호출을 이용한 이진 탐색
int search_binary(int key, int low, int high) {
	int middle;

	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])		// 탐색 성공
			return middle;
		else if (key > list[middle])	// 오른쪽 부분 배열 탐색
			return search_binary(key, middle + 1, high);
		else	// 왼쪽 부분 배열 탐색
			return search_binary(key, low, middle - 1);
	}
	return -1;	// 탐색 실패
}
```
  
<br>
  
2. 반복
```C
// 반복을 이용한 이진 탐색
int search_binary2(int key, int low, int high) {
	int middle;

	while (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}
	return -1;
}
```
 
<br>
  
### 이진 탐색 분석
- 탐색 횟수, 시간복잡도: `O(log2n)`
  
<br><br>

## 색인 순차 탐색
- 색인 순차 탐색 (Indexed Sequential Search) : 인덱스 테이블을 이용해 예상 탐색 범위 내에서만 순차 탐색을 하는  방법
- 인덱스 테이블: 주 자료 리스트에서 일정 간격으로 발췌한 자료를 저장
	- 주 자료 리스트의 데이터 개수가 n개이고 인덱스 테이블에 m개의 항목이 있을 때, 각 인덱스 항목은 주 자료 리스트의 각 n/m번째 데이터를 갖게 된다.

```C
// 인덱스 테이블 구조체
#define INDEX_SIZE 256
typedef struct {
	int key;		// 인덱스가 가리키는 곳의 키 값
	int index;		// 인덱스 값
}itable;
itable index_list[INDEX_SIZE];
```
 
<br>

<img src="https://user-images.githubusercontent.com/71310074/144174043-4cfc6d83-a6cc-4ce7-b1cd-cc2c1d88ebf4.png" width="500">
	
<br>

- 색인 순차 탐색 알고리즘 
```C
// 색인 순차 탐색 (INDEX_SIZE: 인덱스 테이블 크기, n: 전체 데이터 수)
int search_index(int key, int n) {
	int i, low, high;

	// 키 값이 리스트 범위 내의 값이 아니면 탐색 종료
	if (key<list[0] || key>list[n - 1])
		return -1;

	// 인덱스 테이블을 조사하여 해당키의 구간 결정
	for (i = 0;i < INDEX_SIZE;i++)
		if (index_list[i].key <= key && index_list[i + 1].key > key)
			break;
	if (i == INDEX_SIZE) {		// 인덱스 테이블의 끝인 경우
		low = index_list[i - 1].index;
		high = n;
	}
	else {
		low = index_list[i].index;
		high = index_list[i + 1].index;
	}
	// 예상되는 범위만 순차 탐색
	return seq_search(key, low, high);
}
```	
<br>

### 색인 순차 탐색 분석
- 인덱스 테이블 크기 m이 크면 탐색 시간 감소, 작으면 탐색 시간 증가
- 인덱스 테이블 크기 m, 주 자료 리스트 크기 n일때 -> 복잡도: `O(m+n/m)`


<br><br>
	

## 보간 탐색
- 보간 탐색(Interpolation Search) : 찾고자 하는 키값과 현재의 low, high 위치 값을 고려하여 탐색 위치를 분할하여 탐색하는 방법

```C
// 보간 탐색 알고리즘
int interpol_search(int list[], int key, int n) {
	int low, high, j;	// j: 탐색 키값의 위치

	low = 0;
	high = n - 1;
	while ((list[high] >= key) && (key > list[low])) {
		j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;
		if (key > list[j])low = j + 1;			// low 조정
		else if (key < list[j])high = j - 1;	// high 조정
		else low = j;							// 탐색 성공
	}
	if (list[low] == key) return(low);	// 탐색 성공
	else return -1;
}
```
					   
- 많은 데이터가 비교적 균등하게 분포되어 있을 경우 이진 탐색보다 우수한 방법
- 시간 복잡도: `O(log2n)`
  
  
<br>
	
## AVL 트리 탐색
- 왼쪽 서브 트리의 높이와 오른쪽 서브 트리의 높이 차이가 1 이하인 이진 탐색 트리
- 트리가 비균형 상태로 되면 스스로 노드들을 재배치 하여 균형 상태로 만듬
- 균형 트리가 항상 보자되므로 삽입, 삭제, 탐색 모두 시간 복잡도 `O(log2n)` 유지

<br>
	
### AVL 트리 구조체
```c
// AVL 트리 구조체
typedef struct AVLNode {
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
}AVLNode;
```
	
	
<br>
	
- 균형인수(balance factor): 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
	
### Rotations
![image](https://user-images.githubusercontent.com/71310074/144987816-a326597f-869c-40b2-be8b-2badb0b223e7.png)

```c
// 트리 높이 구하기
int get_height(AVLNode* node) {
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

// 노드의 균형 인수 반환
int get_balance(AVLNode* node) {
	if (node == NULL)return 0;
	return get_height(node->left) - get_height(node->right);
}
```

```c
// 오른쪽으로 회전
AVLNode* rotate_right(AVLNode* parent) {
	AVLNode* child = parent->left;	// child: 루트의 왼쪽 서브트리
	parent->left = child->right;	// 루트의 왼쪽 자식 노드 위치에 child의 오른쪽 서브트리 이동
	child->right = parent;			// child의 오른쪽 서브트리에 루트 서브트리 이동
}
// 왼쪽으로 회전
AVLNode* rotate_left(AVLNode* parent) {
	AVLNode* child = parent->right;	// child: 루트의 오른쪽 서브트리
	parent->right = child->left;	// 루트의 오른쪽 자식	노드 위치에 child의 왼쪽서브트리 이동
	child->left = parent;			// child의 왼쪽 서브트리에 루트 서브트리 이동
}
```
	
### AVL 트리의 삽입 연산
- 새로운 노드 삽입 후 불균형 상태를 확인하고, 가장 가까운 조상 노드(균형 인수가 +-2가 된 가장 가까운 조상 노드)의 서브 트리들에 대해 다시 균형을 잡아야 함
	
```C
// 노드 추가 함수
AVLNode* insert(AVLNode* node, int key) {
	int balance;

	if (node == NULL)
		return (create_node(key));

	// 노드 삽입
	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	balance = get_balance(node);	// 균형 인자 구하기

	// LL 타입 처리
	if (balance > 1 && key < node->left->key)
		return rotate_right(node);

	// RR 타입 처리
	if (balance < -1 && key >node->right->key)
		return rotate_left(node);

	// LR 타입 처리
	if (balance > 1 && key > node->left->key) {
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	// RL 타입 처리
	if (balance < -1 && key < node->right->key) {
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}
```
	
	



