javascript:(function(e,a,g,h,f,c,b,d)%7Bif(!(f=e.jQuery)%7C%7Cg%3Ef.fn.jquery%7C%7Ch(f))%7Bc=a.createElement(%22script%22);c.type=%22text/javascript%22;c.src=%22http://ajax.googleapis.com/ajax/libs/jquery/%22+g+%22/jquery.min.js%22;c.onload=c.onreadystatechange=function()%7Bif(!b&&(!(d=this.readyState)%7C%7Cd==%22loaded%22%7C%7Cd==%22complete%22))%7Bh((f=e.jQuery).noConflict(1),b=1);f(c).remove()%7D%7D;a.documentElement.childNodes%5B0%5D.appendChild(c)%7D%7D)(window,document,%221.3.2%22,function($,L)%7B$('%23header,%20.pagehead,%20.breadcrumb,%20.commit,%20.meta,%20%23footer,%20%23footer-push,%20.wiki-actions,%20%23last-edit,%20.actions,%20.header,.site-footer,.repository-sidebar,.file-navigation,.gh-header-meta,.gh-header-actions,#wiki-rightbar,#wiki-footer').remove();%20$('%23files,%20.file').css(%7B%22background%22:%22none%22,%20%22border%22:%22none%22%7D);%20$('link').removeAttr('media');%7D); var removeMe = document.getElementsByClassName("file-header")[0]; removeMe.parentNode.removeChild(removeMe);
@jasonzio


# 우선순위 큐(Priority Queue)
- 큐의 FIFO(First In, First Out) 구조 + 데이터들의 우선 순위
- `히프(heap)` : 가장 효율적인 우선순위 큐의 구조 구현
  1. 최소 우선순위 큐 : 가장 우선 순위가 낮은 요소 삭제
  2. 최대 우선순위 큐 : 가장 우선 순위가 높은 요소 삭제



<br>

### 우선순위 큐의 추상자료형
- 객체: n개의 element형의 우선순위를 가진 요소들의 모임
- 연산
  - `create()` : 우선순위 큐 생성
  - `init(q)` : 우선순위 큐 초기화
  - `is_empty(q)` : 우선순위 큐의 공백 상태 검사
  - `is_full(q)` : 우선순위 큐의 포화 상태 검사
  - `insert(q, x)` : 우선순위 큐에 요소 x 추가
  - `delete(q)` : 우선순위 큐로부터 가장 우선순위가 높은 요소를 삭제하여 반환
  - `find(q)` : 우선순위가 가장 높은 요소 반환

<br>

<details>
	<summary> 우선순위 큐 배열/리스트 시간 복잡도 </summary>

1. 배열
    1) 정렬 되어 있지 않은 배열
     - 삽입 : `O(1)` (끝에 삽입)
      - 삭제 : `O(n)` (가장 우선순위 높은 요소 탐색)
      <br>
      
    2) 정렬 되어 있는 배열
      - 삽입 : `O(n)` (다른 요소들의 이동)
      - 삭제 : `O(1)` (맨 뒤 요소 반환)

2. 연결 리스트 
    1) 순서 없는 연결 리스트
      - 삽입 : `O(1)` (맨 처음에 삽입)
      - 삭제 : `O(n)` (탐색)
      <br>
      
    2) 정렬된 연결 리스트
      - 삽입 : `O(n)` (삽입 위치 탐색)
      - 삭제 : `O(1)` (첫번째 노드 삭제)
	
</details>
<br>

## 히프(heap)
- 완전 이진 트리의 일종으로, 가장 큰 값 또는 가장 작은 값을 빠르게 탐색하는 우선순위 큐를 위해 특별히 만들어진 자료구조
- 느슨한 정렬 상태
- 중복된 값을 허용
- 하나의 요소에 대한 삽입과 삭제의 시간 복잡도 : `O(logn)`
- 전체 요소 삽입, 삭제의 시간 복잡도 : `O(nlogn)`


<br>


### 히프의 종류
1. 최대 히프(max heap)
  - 부모 노드의 키 값이 자식 노드의 키 값보다 크거나 같음
  - `key(부모노드) >= key(자식노드)`
2. 최소 히프(min heap)
  - 부모 노드의 키 값이 자식 노드의 키 값보다 작거나 같음
  - `key(부모노드) < key(자식노드)`
<br>

### 히프의 구현
- 각 레벨의 왼쪽에서 오른쪽 순으로 차례대로, 번호를 1번(배열의 인덱스)부터 붙일 수 있음
- 왼쪽 자식 인덱스 = (부모 인덱스) * 2
- 오른쪽 자식 인덱스 = (부모 인덱스) * 2 + 1
- 부모 인덱스 = (자식 인덱스) / 2

<br>

### 히프의 정의

- 히프의 구조체
```C
typedef struct element {	// 요소 구조체
	int key;
  // char name[20];
}element;

#define MAX_ELEMENT 20
typedef struct {	// 히프 구조체
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;
```

<br>

### 히프의 연산

<details>
	<summary> 히프 구조체 생성, 초기화 </summary>

```C
// 히프 구조체 동적 할당
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// 히프의 사이즈 초기화
void init(HeapType* h) {
	h->heap_size = 0;
}
```
	
</details>
	
### 최대 히프 삽입 연산

- 새로운 노드를 히프의 마지막 노드로 삽입
- 새로운 노드를 부모 노드들과 키 값을 비교하여 교환하는 과정을 반복
- 최대 히프의 경우, 부모 노드의 키 값보다 크다면 교환하기를 반복
  
<br>
  
  
```C
// 최대 히프 구현하는 삽입 함수
void insert_max_heap(HeapType* h, element item) {
	int i;					// 히프 배열 인덱스 값
	i = ++(h->heap_size);	// 히프의 크기를 1 증가시킨 값을 i에 저장

	// 첫번째 인덱스값이 아니고, item의 키 값이 부모 노드의 키 값보다 큰 경우 
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];	// i번 인덱스의 요소(자식 노드)에 i/2번 인덱스의 요소(부모 노드) 대입 
		i /= 2;							//  i/2번 인덱스로 이동 (부모 노드)
	}
	h->heap[i] = item;	// i번 인덱스에 새로운 item 대입
}
```
	
<br>

### 최대 히프 삭제 연산 
	
- 최대 히프의 경우, 반환할 노드는 루트 노드이다.
- 빈 루트 노드에, 히프의 마지막 노드를 가져와 자식 중 더 큰 키 값을 가진 노드와 자리를 교환하기를 반복
- 마지막 노드의 키 값이 자식 노드의 키 값보다 크거나 같다면 종료 (작을 때만 교환 과정을 반복)
  
<br>
  
```C
// 최대 히프의 루트 노드부터 삭제
element delete_max_heap(HeapType* h) {
	int parent, child;	// 부모/자식 노드 인덱스
	element item, temp;	// 반환할 item, 임시 temp

	item = h->heap[1];	// 반환할 요소는 1번 인덱스의 요소
	temp = h->heap[(h->heap_size)--];	// 마지막 요소를 temp에 저장하고, 힙 크기 1 감소
	parent = 1, child = 2;	// 부모, 자식 노드 인덱스는 1,2부터 시작

	// child가 힙의 마지막 요소에 도달할 때까지 반복
	while (child <= h->heap_size) {
			
		// 오른쪽 자식 노드의 키 값이 더 크다면 child 값 1 증가
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)
			child++;	

		// temp의 키 값이 child 보다 크거나 같다면 반복문 종료
		if (temp.key >= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;		// 부모의 인덱스는 자식의 인덱스로 이동
		child *= 2;		// 왼쪽 자식 노드 인덱스로 이동
	}
	h->heap[parent] = temp;	// 최종 부모 인덱스에 마지막 요소 값을 대입
	return item;
}
```
	
<br>
	
## 히프 정렬 (Heap Sort)
- 정렬되어 있지 않은 배열을 차례대로 최대 히프에 추가하여 새로운 히프를 추가하고, 요소를 하나씩 꺼내서 배열에 차례대로, 혹은 역순으로 저장하여 정렬 완성
	1. 오름차순 정렬: 배열의 끝에서부터 저장
	2. 내림차순 정렬: 배열의 처음부터 저장
- 최대 히프를 이용한 정렬의 시간 복잡도 : `O(nlog2n)`
<br>

- 오름차순 정렬
```C
void heap_sort(element a[], int n) {
	int i;
	HeapType* h;

	h = create();
	init(h);

	for (i = 0;i < n;i++)
		insert_max_heap(h, a[i]);
	for (i = (n - 1);i >= 0;i--)
		a[i] = delete_max_heap(h);

	free(h);
}
```
<br>

- 내림차순 정렬
```C
void heap_sort_min(element a[], int n) {
	int i;
	HeapType* h;

	h = create();
	init(h);

	for (i = 0;i < n;i++)
		insert_max_heap(h, a[i]);
	for (i = 0;i<n;i++)
		a[i] = delete_max_heap(h);

	free(h);
}
```
	
<br>

## 머쉰 스케줄링 (Machine Scheduling)

### LPT(Longest Processing Time first) 알고리즘
- 동일한 기계 m, 처리해야 하는 작업 n이 있는 상황
- 모든 m개의 기계를 풀가동하여 가장 최소의 시간 안에 작업들을 모두 끝내는 알고리즘
- 각 작업들을 가장 먼저 사용 가능하게 되는 기계에 할당하는 것
- `최소 히프` 사용 : 최소의 종료 시간을 가지는 기계를 삭제하여 자업을 할당하는 알고리즘
	- 기계의 종료 시간을 최소 히프에 넣고, 최소 히프에서 기계를 꺼내어 그 기계에 작업을 할당
	- 작업을 할당한 후에는 기계의 종료 시간을 작업 시간만큼 증가시킨 후 다시 최소 히프에 삽입	

<br>

### LPT 알고리즘 구현

element 구조체
- 히프의 노드 (기계의 번호, 기계의 작업 종료 시간)

```C
typedef struct {
	int id;		// 기계의 번호
	int avail;	// 기계가 사용 가능하게 되는 종료 시간 (키값)
}element;	
```

<br>

동작 구현
```C
#define JOBS 7		// 작업 개수
#define MACHINES 3	// 기계 개수

int main() {
	int jobs[JOBS] = { 8,7,6,5,4,2,1 }; // 정렬되어 있다고 가정 (최대 히프를 이용하여 정렬 가능)
	element m = { 0,0 }; // 기계의 번호, 작업 종료 시간
	HeapType* h;
	h = create();
	init(h);

	// MACHINES 개의 기계를 히프에 삽입 (키 값 = avail)
	for (int i = 0;i < MACHINES;i++) {
		m.id = i + 1;
		m.avail = 0;
		insert_min_heap(h, m);
	}

	// 최소 히프에서 기계를 꺼내서 작업을 할당하고, 사용 가능시간을 증가 시킨 후에
	// 다시 최소 히프에 추가
	for (int i = 0;i < JOBS;i++) {
		m = delete_min_heap(h);
		printf("JOB %d를 시간=%d부터 시간=%d까지 기계 %d번에 할당 \n",
			i, m.avail, m.avail + jobs[i] - 1, m.id);
		m.avail += jobs[i];
		insert_min_heap(h, m); // 다시 최소 히프에 작업 할당한 기계 삽입
	}

	return 0;
}
```
<br>

<details>
	<summary> 최소 히프 구현 </summary>

```C
// 히프 구조체 동적 할당
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// 히프의 사이즈 초기화
void init(HeapType* h) {
	h->heap_size = 0;
}

// 최소 히프 구현하는 삽입 함수 (작업 할당 후 기계를 다시 삽입)
void insert_min_heap(HeapType* h, element item) {
	int i;					
	i = ++(h->heap_size);

	while ((i != 1) && (item.avail > h->heap[i / 2].avail)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;						
	}
	h->heap[i] = item;
}

// 최소 히프의 루트 노드부터 삭제 (최소 종료 시간을 가진 기계 삭제하여 작업할당)
element delete_min_heap(HeapType* h) {
	int parent, child;	
	element item, temp;	

	item = h->heap[1];	
	temp = h->heap[(h->heap_size)--];	
	parent = 1, child = 2;	

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].avail > h->heap[child + 1].avail))
			child++;

		if (temp.avail < h->heap[child].avail)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;		
		child *= 2;		
	}
	h->heap[parent] = temp;	
	return item;
}

```
</details>
<br>
	
	
## 허프만 코드 (Huffman Codes)
	
