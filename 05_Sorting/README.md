# 정렬 (Sorting)

1. 단순하지만 비효율저긴 방법 - 삽입/선택/버블 정렬
2. 복잡하지만 효율적인 방법 - 퀵/히프/합병/기수 정렬

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
	/*
	i: 정렬된 왼쪽 리스트에 대한 인덱스
	j: 정렬된 오른쪽 리스트에 대한 인덱스
	k: 정렬될 리스트에 대한 인덱스
	*/
	int i, j, k, l;;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)
		for (l = j;l <= right;l++)
			sorted[k++] = list[l];
	else
		for (l = i;l <= mid;l++)
			sorted[k++] = list[l];
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

## 퀵 정렬
- 퀵 정렬(Quick Sort)

<br>

## 히프 정렬
- 히프 정렬(Heap Sort)

## 기수 정렬
- 기수 정렬(Raidx Sort)

