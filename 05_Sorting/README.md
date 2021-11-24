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

```C
void insertion_sort(int list[], int n) {
	int i, j, key;
	for (i = 1;i < n;i++) {
		key = list[i];
		for (j = i - 1;j >= 0 && key < list[j];j--) // 왼쪽 레코드들과 비교하여 삽입 위치 탐색
			list[j + 1] = list[j];	// 레코드의 오른쪽 이동
		list[j + 1] = key;
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

## 쉘 정렬
- 쉘 정렬(Shell Sort)

<br>

## 합병 정렬
- 합병 정렬(Merge Sort)

<br>

## 퀵 정렬
- 퀵 정렬(Quick Sort)

<br>

## 히프 정렬
- 히프 정렬(Heap Sort)

## 기수 정렬
- 기수 정렬(Raidx Sort)

