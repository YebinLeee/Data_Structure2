# 정렬 (Sorting)

1. 단순하지만 비효율적인 방법 - [선택](https://github.com/YebinLeee/Data_Structure2/tree/main/05_Sorting#%EC%84%A0%ED%83%9D-%EC%A0%95%EB%A0%AC-selection-sort)/[삽입](https://github.com/YebinLeee/Data_Structure2/tree/main/05_Sorting#%EC%82%BD%EC%9E%85-%EC%A0%95%EB%A0%AC-insertion-sort)/[버블](https://github.com/YebinLeee/Data_Structure2/tree/main/05_Sorting#%EB%B2%84%EB%B8%94-%EC%A0%95%EB%A0%AC-bubble-sort)/[쉘](https://github.com/YebinLeee/Data_Structure2/tree/main/05_Sorting#%EC%89%98-%EC%A0%95%EB%A0%AC-shell-sort) 정렬
2. 복잡하지만 효율적인 방법 - [퀵](https://github.com/YebinLeee/Data_Structure2/tree/main/05_Sorting#%ED%80%B5-%EC%A0%95%EB%A0%AC)/[히프](https://github.com/YebinLeee/Data_Structure2/tree/main/05_Sorting#%ED%9E%88%ED%94%84-%EC%A0%95%EB%A0%AC)/[합병](https://github.com/YebinLeee/Data_Structure2/tree/main/05_Sorting#%ED%95%A9%EB%B3%91-%EC%A0%95%EB%A0%AC-merge-sort)/[기수](https://github.com/YebinLeee/Data_Structure2/tree/main/05_Sorting#%EA%B8%B0%EC%88%98-%EC%A0%95%EB%A0%AC) 정렬

<br>

## 선택 정렬 (Selection Sort)

- 두 개의 리스트 
  - 왼쪽 리스트: 초기에 비어있는 상태
  - 오른쪽 리스트: 정렬되지 않은 숫자들
- 오른쪽 리스트에서 가자 작은 숫자를 선택하여 왼쪽 리스트로 이동하는 작업을 되풀이
<br>

- 제자리 정렬(in-place sorting): 최소값을 발견하여 배열의 첫번째 요소와 교환하고, 첫번찌 요소들 중 가장 작ㅇ늑 ㅏㅄ을 선택하여 이를 두번째 요소와 교환하는 절차를 (n-1)번 되풀이

<img src="https://user-images.githubusercontent.com/71310074/143246368-ea8b416b-2bff-4792-8d5b-72f311ef1035.png" width="300">

```C
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

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
````


<br>

### 선택 정렬 분석
비교횟수
- for문 외부루프: n-1번 실행
- for문 내부루프: 0에서 n-2까지 (n-1)-i번 반복
- `O(n^2)`

교환 횟수
- 외부 루프의 실행횟수와 동일
- 한번 교환을 위해 총 3번의 이동 필요
- 전체 이동 횟수: 3(n-1)

<br> <hr>


## 삽입 정렬 (Insertion Sort)

- 각 자료가 리스트 내ㅔ서 삽입되어야 할 위치를 탐색하고, 나머지 자료들을 이동하기를 반복하는 알고리즘


```C
void insertion_sort(int list[], int n) {
	int i, j, key;
	for (i = 1;i < n;i++) {
		key = list[i];
		for (j = i - 1;j >= 0 && key < list[j];j--) // 왼쪽 레코드들과 비교하여 삽입 위치 탐색
			list[j + 1] = list[j];	// 레코드의 오른쪽 이동
		list[j + 1] = key; // 최종 위치에 key 
	}
}
```
<img src="https://user-images.githubusercontent.com/71310074/143280388-5f0428c8-46dc-4146-9008-d9ee4009558f.png" width="300">

<br>

### 삽입 정렬 분석
- 이미 정렬되어 있는 경우에 가장 빠르고 효율적
- 총 비교 횟수: (n-1)번
- 총 이동횟수: 2(n-1)번
- `O(n)` : 외부 루프가 (n-1)번, 각 단계에서 1번의 비교와 2번의 이동이 이루어짐 (삽입할 레코드, 오른쪽으로 이동하는 레코드)


<br><hr>

## 버블 정렬 (Bubble Sort)

- 인접한 2개의 레코드를 비교하여 크기가 순서대로 되어 있지 않으면 서료 고환하는 비교-교환 과정을 왼쪽 끝에서 시작하여 오른쪽 끝까지 진행하며 정렬
- 한번 완료되면 가장 큰 레코드가 리스트의 오른쪽 끝으로 이동
- 전체 숫자가 전부 정렬될 때까지 진행

```C
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void buuble_sort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1;i > 0;i--) {
		for (j = 0;j < i;j++)
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
```

<img src="https://user-images.githubusercontent.com/71310074/143281551-4f120a06-f90f-492d-9d10-37bf03c5c083.png" width="300">

### 버블 정렬 분석
- 비교 횟수: 최선, 평균, 최악의 어떠한 경우에도 항상 일정
- `O(n^2)`
- 이동 횟수: 입력 자료가 역순 정렬되어 있는 경우 발생 (비교연산 횟수*3)
- 자료의 교환 작업이 자료의 이동 작업보다 더 복잡하기 때문에 거의 쓰이지 않음



<br><hr>

## 쉘 정렬 (Shell Sort)

- 전체의 리스트를 한 번에 정렬하는 삽입 정렬을 보완한 방법
- 주어진 리스트의 각 k번째 요소를 추출하여 만든 간격(gap)에 따라 부분 리스트(sublist)를 구성하고 부분 리스트 내에서 삽입 정렬을 실행하고, 각 스텝마다 간격 k를 줄여가며 수행 과정을 반복
- 일정한 간격으로 삽입 정렬을 수행
- 간격(gap)은 처음에는 n/2(짝수인 경우에는 1증가) 하고 각 패스마다 간격을 절반으로 줄이는 방식 사용

<br>

<img src = "https://user-images.githubusercontent.com/71310074/143549725-8674af4b-f700-45b9-9ab5-54c483aeee03.png" width="400">
<br>

```C
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
````
<br>


### 쉘 정렬 분석
- 연속적이지 않은 부분 리스트에서의 자료(일정 간격을 둔 레코드)의 교환이 더 큰 거리를 이동하지만 한번에 한칸씩 이동
- 부분 리스트가 어느정도 정렬이 된 상태이므로, 부분 리스트 개수가 1이 되면 셀 정렬은 기본적으로 삽입 정렬을 수행하며 거의 정렬된 리스트가 완성되므로 빠르게 수행됨
- 최악: `O(n^2)`, 평균: `O(n^1.5)`


<br><hr>


## 합병 정렬 (Merge Sort)
- 하나의 리스트를 두 개의 균등한 크기로 분할하고, 분할된 부분 리스트를 정렬한 뒤 다시 합하여 전체가 정렬된 리스트틀 얻는 방법
- 분할 정복(divide and conquer) 기법
	- 분할(Divide): 입력 배열을 같은 크기의 2개의 부분 배열로 분할
	- 정복(Conquer): 부분 배열을 정렬 (크기가 충분히 작아질 때까지 순환 호출을 하여 다시 분할 정복 기법 적용)
	- 결합(Combine): 정렬된 부분 배열들을 하나의 배열에 통합

<br>
<img src= "https://user-images.githubusercontent.com/71310074/143554911-5ac6c2c8-91f7-4387-a668-bcb1a8049fff.png" width="300">

```C
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
```

<br>

### 합병 정렬 분석
- 순환 호출의 깊이 : `log2n`, 총 비교 연산: 최대 `nlog2n`, 총 이동 연산: `2nlog2n`
- 최악, 평균, 최선의 경우 모두 복잡도가 `O(nlog2n)`
- 장점
	- 안정적 -> 입력 데이터가 무엇이든간에 정렬 시간 동일
- 단점
	- 레코드의 크기가 큰 경우 이동 횟수가 많다는 단점 -> 연결 리스트로 구성하는 경우 링크 인덱스만 변경하면 가능
	- 임시 배열이 필요하다는 점 
<hr><br>

## 퀵 정렬 (Quick Sort)
- 분할-정복법(divide and conquer)에 근거하여 전체 리스트를 2개의 부분 리스틀 분할하여, 각각의 부분 리스트를 순환 호출하며 다시 퀵 정렬하는 방법
- 리스트의 한 요소 피벗(pivot)을 선택하여 피벗보다 작은 요소들은 모두 피벗의 왼쪽으로, 큰 요소들은 오른쪽으로 옮겨 각 리스트를 정렬하는 방법

<br>

<img src = "https://user-images.githubusercontent.com/71310074/143562316-131ebd2b-6097-4b7d-9a94-385fbd777bcb.png" width="400">

- low(left mark)는 부분 리스트의 왼쪽 끝에서 오른쪽으로, high(right mark)는 오른쪽 끝에서 왼쪽으로 이동하여 탐색하며 피벗보다 큰 데이터, 작은 데이터를 각각 찾으면 멈추고
- 탐색이 멈추어진 위치에서 low와 high 요소를 교환
- 서로 엇갈리게 되면 멈춘 위치에서 피벗을 이동시키고 나면 두 리스트로 분할하게 됨

<br>

```C
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

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
```
<br>

### 퀵 정렬 분석
- 최선/평균의 경우: 리스트의 분할이 항상 리스트의 가운데에서 이루어져, 거의 균등한 두 부분 리스트로 분할 되는 경우 (pivot 값이 나머지 값들의 중간값인 경우)
	- n이 2의 거듭제곱이라 가정할 때, `k=log2n`의 패스가 필요하고, 각각의 패스에서 전체 리스트의 대부분의 레코드를 비교해야 하므로 평균 n번의 비교가 이루어짐
	- `O(nlog2n)`

- 최악의 경우: 계속 불균형하게 나누어지는 경우 (pivot이 리스트의 끝에 위치하는 경우)
	- `O(n^2)`
- 다른 정렬 알고리즘과 비교해 가장 빠른 방법
- 불필요한 데이터의 이동을 줄이고, 먼 거리의 데이터를 교환할 뿐 아니라 한번 결정된 피벗들이 추후 연산에서 제외됨
- 피벗을 중간값(median)으로 선택하는 것이 중요
- C언어의 `qsort` 함수로 제공됨

<details>
	<summary> C언어의 qsort 함수 </summary>

```C
void qsort(
	void* base,		// 배열의 시작 주소
	size_t num,		// 배열 요소의 개수
	size_t width,	// 배열 요소 하나의 크기(바이트 단위)
	int(*compare)(const void*, const void*)
		// 포인터를 통해 두 요소를 비교하여 비교 결과를 정수로 반환
);
```
</details>

<br><hr>

## 히프 정렬
- 히프 정렬(Heap Sort)

## 기수 정렬 (Radix Sort)
- 기수(radix, 숫자의 자리수)의 값에 따라 큐 배열(버킷, bucket)을 만들어 각 자리수의 값에 따라 넣기를 반복
	- 2진법: 0과 1, 총 2개의 버킷 필요
	- 숫자인 경우: 0~9, 총 10개의 버킷 필요
	- 알파벳 문자인 경우: a~z, 총 26개의 버킷 필요
- 데이터의 자리수의 개수만큼 단계적으로 정렬을 함 (낮은 자리부터)
	- 두자리의 정수인 경우 낮은 1의 자리수부터 10의 자리수까지, 2번의 정렬 단계가 필요

<br>


```C
#define BUCKETS 10	// 필요한 버킷 수 (십진수인경우)
#define DIGITS 2	// 자리수 (두자리수인경우)

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
```
<br>

### 기수 정렬 분석
- n개의 정수, 각 정수가 d개의 자리수인 경우 -> 내부 루프 n번, 외부 루프 d번 : `O(d*n)` (d의 값이 대게 매우 작으므로 `O(n)`)
- 정렬에 사용되는 키 값이 숫자로 표현되어야만 함 

