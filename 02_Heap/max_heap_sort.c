#include <stdio.h>
#include <stdlib.h>

typedef struct element {	// 요소 구조체
	int key;
	// char name[20];
}element;

#define MAX_ELEMENT 20
typedef struct {	// 히프 구조체
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

// 히프 구조체 동적 할당
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// 히프의 사이즈 초기화
void init(HeapType* h) {
	h->heap_size = 0;
}

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
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
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

// 오름차순 정렬
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

// 내림차순 정렬
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
int main() {
	int i;
	element list[10] = { 3,4,6,2,6,24,9,10,73,1 };
	
	heap_sort_min(list, 10);
	for (i = 0;i < 10;i++)
		printf("%d ", list[i].key);
	printf("\n");
	return 0;
}
