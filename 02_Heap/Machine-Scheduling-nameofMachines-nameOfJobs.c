#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* name;		// 기계의 번호
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
void insert_min_heap(HeapType* h, element *item) {
	int i;					
	i = ++(h->heap_size);

	while ((i != 1) && (item->avail < h->heap[i / 2].avail)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;						
	}
	h->heap[i] = *item;
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

// 내림 차순으로 정렬 (최소 히프에서 꺼내어 차례대로 저장)
void heap_sort(element a[], int size) {
	// 최소 히프 생성하여 삽입
	int i;
	HeapType* h;
	h = create();
	init(h);

	for (i = 0;i < size;i++)
		insert_min_heap(h, &a[i]);


	// 삭제하여 다시 배열에 저장
	for (i = size-1;i>=0;i--)
		a[i] = delete_min_heap(h);
}

#define JOBS 7		// 작업 개수
#define MACHINES 3	// 기계 개수

int main() {
	FILE* fp;
	int i, tmp;
	char name[30];
	element* job;
	int jobs[JOBS] = { 8,7,6,5,4,2,1 }; // 정렬되어 있다고 가정 (최대 히프를 이용하여 정렬 가능)
	element m = { 0,0 }; // 기계의 번호, 작업 종료 시간
	HeapType* h;
	int work;

	h = create();
	init(h);

	/* 파일에 저장된값 : 3개의 기계 , 5개의 작업 이름과 시간
	3
	Machine_1
	Machine_2
	Machine_3
	5
	A 4
	B 5
	C 2
	D 9
	E 12
	*/

	fp = fopen("data.txt", "rt");
	// 기계 개수
	fscanf(fp, "%d", &tmp);
	printf("Num of Machines : %d \n", tmp);

	// 기계 이름 읽고, 최소 히프에 삽입
	for (i = 0;i < tmp;i++) {
		fscanf(fp, "%s", name);
		m.avail = 0;
		m.name = (char*)malloc(strlen(name) + 1);
		strcpy(m.name, name);
		printf("%s ", name);
		insert_min_heap(h, &m);
	}
	printf("\n\n");

	// 작업의 이름과 작업 시간
	// 작업 개수
	fscanf(fp, "%d", &tmp);
	printf("Num of Jobs : %d \n", tmp);
	// 작업 동적 할당
	job = (element*)malloc(sizeof(element) * tmp);
	for (i = 0;i < tmp;i++) {
		fscanf(fp, "%s %d", name, &job[i].avail);
		job[i].name = (char*)malloc(strlen(name) + 1);
		strcpy(job[i].name, name);
		printf("%s : %d \n", name, job[i].avail);
	}
	printf("\n\n\n");
	heap_sort(job, tmp); // 내림차순으로 삽입

	// 최소 히프에서 기계를 꺼내서 작업을 할당하고, 사용 가능시간을 증가 시킨 후에
	// 다시 최소 히프에 추가

	for (int i = 0;i < tmp;i++) {
		m = delete_min_heap(h);
		printf("JOB %s(%d)를 시간=%d부터 시간=%d까지 기계 %s에 할당 \n",
			job[i].name, job[i].avail,  m.avail, m.avail + job[i].avail - 1, m.name);
		m.avail += job[i].avail;
		insert_min_heap(h, &m); // 다시 최소 히프에 작업 할당한 기계 삽입
	}

	fclose(fp);
	free(job);
	free(h);

	return 0;
}
