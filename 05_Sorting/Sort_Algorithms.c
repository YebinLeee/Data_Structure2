#include <stdio.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))




// 선택 정렬 ////////////////////////////////////////////////////


void selection_sort(int list[], int n) {
	int i, j, least, temp;
	for (i = 0;i < n - 1;i++) {
		least = i;		// 최소값을 가리키는 인덱스
		for (j = i + 1;j < n;j++)	// 최소값 탐색
			if (list[j] < list[least])
				least = j;
		if(i!=least)		// 자료가 정렬되어 있지 않은 경우	
			SWAP(list[i], list[least], temp);	// i번째 요소와 교환
	}
}







// 삽입 정렬 ////////////////////////////////////////////////////


void insertion_sort(int list[], int n) {
	int i, j, key;
	for (i = 1;i < n;i++) {
		key = list[i];
		for (j = i - 1;j >= 0 && key < list[j];j--) // 왼쪽 레코드들과 비교하여 삽입 위치 탐색
			list[j + 1] = list[j];	// 레코드의 오른쪽 이동
		list[j + 1] = key;
	}
}







// 버블 정렬 ////////////////////////////////////////////////////


void buuble_sort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1;i > 0;i--) {
		for (j = 0;j < i;j++)
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}







// 쉘 정렬 ////////////////////////////////////////////////////


// first에서 last 사이의 레코드들 중 gap만큼 떨어진 요소들을 삽입 정렬
void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap;i <= last;i = i + gap) {
		key = list[i];
		for (j = i - gap;j >= first && key < list[j];j = j - gap) // 부분 리스트의 왼쪽 레코드들과 비교하여 삽입 위치 탐색
			list[j + gap] = list[j];	// 부분 리스트 레코드의 오른쪽 이동
		list[j + gap] = key; // 최종 위치에 key 삽입
	}
}

void shell_sort(int list[], int n) {
	int i, gap;
	for (gap = n / 2;gap > 0;gap = gap / 2) {
		if ((gap % 2) == 1)gap++;	 // 간격 gap이 짝수인경우 1을 더함
		for (i = 0;i < gap;i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}







// 합병 정렬 ////////////////////////////////////////////////////


#define MAX_SIZE 10000
int sorted[MAX_SIZE]; // 합병된 리스트를 임시로 저장하는 배열

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;;
	i = left;		/* 왼쪽 리스트의 첫 요소 인덱스 */
	j = mid + 1;	/* 오른쪽 리스트의 첫 요소 인덱스 */
	k = left;		/* 정렬될 리스트에 대한 인덱스 */

	/* 분할 정렬된 list의 합병 */
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];	// 왼쪽리스트의 요소
		else
			sorted[k++] = list[j++];	// 오른쪽 리스트의 요소
	}
	/* 합병 후 남아있는 레코드의 일괄 복사 */
	if (i > mid)
		for (l = j;l <= right;l++)	// 오른쪽 리스트 복사
			sorted[k++] = list[l];
	else
		for (l = i;l <= mid;l++)	// 왼쪽 리스트 복사
			sorted[k++] = list[l];
	/* 배열 sorted의 리스트를 다시 배열 list로 재복사 */
	for (l = left;l <= right;l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;			/* 리스트의 균등 분할*/
		merge_sort(list, left, mid);		/* 왼쪽 부분 리스트 정렬 */
		merge_sort(list, mid + 1, right);	/* 오른쪽 부분 리스트 정렬 */
		merge(list, left, mid, right);		/* 합병 */
	}
}







// 퀵 정렬 ////////////////////////////////////////////////////


// 피벗보다 작은 데이터는 왼쪽 부분 리스트로, 큰 데이터는 오른쪽 부분 리스트로 이동
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	/*
		low는 left에서 출발
		high는 right에서 출발
	*/
	low = left;
	high = right + 1;
	pivot = list[left];	// pivot을 리스트의 첫번째 데이터로 설정

	do {
		do
			low++;
		while (list[low] < pivot);
		do
			high--;
		while (list[high] > pivot);
		
		// 탐색이 멈추어진 위치
		if (low < high) SWAP(list[low], list[high], temp);	// low와 high가 아직 교차하지 않은 경우 멈추어진 위치의 두 요소 교환
	} while (low < high);	// low와 high가 교차하지 않은 경우에 반복문 실행

	SWAP(list[left], list[high], temp);	// 피봇과 마지막 high위치의 요소와 교환
	return high;	// 피봇의 위치 반환
}

void quick_sort(int list[], int left, int right) {
	int q;
	if (left < right) {	// 정렬할 범위가 2개 이상의 데이터인 경우
		q = partition(list, left, right);	// 피벗을 기준으로 2개의 리스트로 분할(반환값 = 피봇의 위치)
		quick_sort(list, left, q - 1);	// left에서 피봇 위치 바로 앞까지 순환 호출
		quick_sort(list, q + 1, right);	// 피봇 위치 바로 다음부터 right까지 순환 호출
	}
}






// 기수 정렬 ////////////////////////////////////////////////////


#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct {	// 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

// 오류 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 큐 초기화
void init_queue(QueueType* q) { q->front = q->rear = 0; }
// 공백 상태 검출 함수
int is_empty(QueueType* q) { return (q->front == q->rear); }
// 포화 상태 검출 함수
int is_full(QueueType* q) { return((q->rear + 1) % MAX_QUEUE_SIZE == q->front); }
// 삽입 함수
void enqueue(QueueType* q, element item) {
	if (is_full(q)) error("큐 포화 상태");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q) {
	if (is_empty(q)) error("큐 공백 상태");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

#define BUCKETS 10	// 필요한 버킷 수
#define DIGITS 2	// 자리수

// 기수 정렬
void radix_sort(int list[], int n) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS]; // BUCKETS개의 큐 선언

	for (b = 0;b < BUCKETS;b++)init_queue(&queues[b]); // 큐 초기화

	for (d = 0;d < BUCKETS;d++) {
		for(i=0;i<n;i++)	// 데이터들을 자리수에 따라 큐에 삽입
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0;b < BUCKETS;b++)	// 버킷에서 꺼내어 list로 합침
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);	// 차례대로 0번 버킷부터 list에 삽입
		factor *= 10;	// 다음 자리수로 이동
	}
}
