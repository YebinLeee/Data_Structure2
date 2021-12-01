# 탐색

- 팀섹(search): 탐색키(serach key)와 데이터로 이루어진 여러 개의 항목 중에서 원하는 탐색키를 가지고 있는 항목을 찾는 것
<br>


### ▼ 정렬되지 않은 배열에서의 탐색

## 순차 탐색

- 순차 탐색(sequential search): 처음부터 마지막 항목까지 하나씩 검사하여 원하는 항목을 찾아가는 방법

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


### ▼ 정렬된 배열에서의 탐색

## 이진 탐색
- 이진 탐색 (Binary Search): 배열의 중앙값을 기준으로, 탐색의 범위를 반으로 줄이며 탐색을 반복
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
  
<br>

## 색인 순차 탐색
- 색인 순차 탐색 (Indexed Sequential Search)
- 인덱스 테이블: 주 자료 리스트에서 일정 간격으로 발췌한 자료를 저장
  
  
<br>
  
## 보간 탐색
- 보간 탐색(Interpolation Search)
  
  
