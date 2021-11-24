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

<img src="https://user-images.githubusercontent.com/71310074/143246368-ea8b416b-2bff-4792-8d5b-72f311ef1035.png" width="350">

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


## 삽입 정렬
- 삽입 정렬(Insertion Sort)

<br>

## 버블 정렬
- 버블 정렬(Bubble Sort)

<br>

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

