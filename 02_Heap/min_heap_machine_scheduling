#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;		// 기계의 번호
	int avail;	// 기계가 사용 가능하게 되는 종료 시간 (키값)
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

// 최소 히프 구현하는 삽입 함수 (작업 할당 후 기계를 다시 삽입)
void insert_min_heap(HeapType* h, element item) {
	int i;					
	i = ++(h->heap_size);

	while ((i != 1) && (item.avail < h->heap[i / 2].avail)) {
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
