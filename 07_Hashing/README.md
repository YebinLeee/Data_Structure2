# 해싱(Hashing)

![image](https://user-images.githubusercontent.com/71310074/144989325-ff164d29-f053-4861-8c5f-78a9a21652d7.png)

- `해싱(Hashing)` : 키(key)에 산술적인 연산을 적용해 해시 테이블의 주소를 계산하여 항목에 접근하여 탐색
    - 어떤 항목의 키만을 가지고 바로 항목이 들어 있는 배열의 인덱스를 결정하는 기법
    - (키, 쌍), (key, value) 쌍의 집합
- `해시 테이블(hash table)` : 키에 대한 연산에 의해 직접 접근이 가능한 구조
- `해시 함수(hash function)` : 키를 입력으로 받아 해시 주소(hash address)를 생성하고 이 해시 주소를 해시 테이블의 인덱스로 사용
    - `키값 k`를 입력받아 해시 함수 h(k)로 연산하 결과인 해시 주소 `h(k)`를 인덱스로 사용해 해시 테이블의 항목에 접근

<br><br>

<img src =  "https://user-images.githubusercontent.com/71310074/144990758-491b4c06-c60f-47e3-9d02-4bde819584ce.png" width="400">

- 해시 테이블은 M개의 `버킷(bucket)`으로 이루어지는 테이블
- 하나의 버킷은 s개의 `슬롯(slot)`을 가질 수 있으며, 하나의 슬롯에 하나의 항목이 저장됨
- `충돌(collision)` : 서로 다른 두 개의 키 k1과 k2에 대하여 `h(k1)=h(k2)`인 경우
  - k1과 k2는 동의어(synonym)이며,
  - 충돌 발생 시 같은 버킷에 있는 다른 슬롯에 항목을 저장
  - 충돌이 자주 발생하면 버킷 내부에서의 순차 탐색 시간이 길어져 탐색 성능이 저하됨
  - 버킷에 할당된 슬롯 수보다 충돌이 많이 발생하면 오버플로우(overflow) 발생하여 더이상 항목 저장 불가능


<br><br><hr>


## 해시 함수

해시 함수의 조건
1. 충돌이 적어야 함
2. 해시 함수 값이 테이블의 주소 영역 내에서 고르게 분포되어야 함
3. 계산이 빨라야 함

<br>

### 1. 제산 함수
- 나머지 연산자(mod)를 사용해 키를 해시 테이블의 크기로 나눈 나머지를 해시 주소로 사용하는 방법
- `h(k) = k mod M`
- 해시 테이블의 크기 M은 주로 소수로 선택

<br>

### 2. 폴딩 함수
- 주로 키가 해시 테이블의 크기보다 더 큰 정수일 경우
- ex) 키는 32비트이고, 해시 테이블의 인덱스는 16비트 정수인 경우
    -> 키를 몇 개의 부분으로 나누어 이를 더하거나 비트별로 턖 qndnf dustks 
    
```C
hash index = (short)(key ^ (key>>16))
```

- 32비트 키를 2개의 16비트로 나누어 비트별로 XOR 연산

<br>

1. 이동 폴딩(shift folding) : 키를 여러 부분으로 나눈 값들을 더하여 해시 주소로 사용   
  - ex) 탐색키가 `12320324111220`인 경우 :  `123` + `203` + `241` + `112` + `20` = `699` 
<br>


2. 경계 폴딩(boundary folding) : 키의 이웃한 부분을 거꾸로 더하여 해시 주소를 얻음
  - ex) `123` + `302` + `241` + `211` + `20` = `897`

<br>


### 탐색 키가 문자열이 경우
- 일반적으로 문자의 아스키 코드값이나 유니 코드 값을 사용
- 아스키 코드 값에 위치에 기초한 값을 곱하는 방법
    - 문자열 s가 n개의 문자를 가지고 있으며, s안의 i번째 문자가 u(i)인 경우
    - `u(0)*g^(n-1) + u(1)*g^(n-2) + ... u(n-2)*g + u(n-1)`
    - 호너의 방법(Horner's method) 사용 가능
   
<br><hr>

# 개방 주소법
개방 주소법(open addressing): 충돌이 일어난 항목을 해시 테이블의 다른 위치에 저장하는 방법
- 조사(probing): 충돌 발생 시 비어있는 버킷을 찾는 것

<br>


## 선형 조사법(Linear probing)
- 충돌이 h[t]에서 발생 시, h[t+1]이 비어있는지 조사
- 테이블의 끝에 도달하게 되면 다시 테이블의 처음으로 가고, 조사를 시작했던 곳으로 되돌아오게 되면 테이블이 가득 찬 것으로 판단

<img src = "https://user-images.githubusercontent.com/71310074/144995392-c72623ee-f527-4618-952d-8c60516e5bcb.png" width="300">
<br>

- 해시 테이블 구조
```c
#define TABLE_SIZE 10	// 해싱 테이블의 크기(소수)
#define MOD 7			// 제산 함수에서 사용되는 나눗셈값

typedef struct element {
	int key;
}element;

element hash_table[TABLE_SIZE];	// 해싱 테이블
```
<br>

- 초기화
```c
// 해시 테이블의 각 요소를 0으로 초기화
void init_table(element ht[]) {
	int i;
	for (i = 0;i < TABLE_SIZE;i++)
		ht[i].key = 0;
}

// 해시 함수
int hash_function(int key) {
	return key % MOD;	// key값을 MOD(7)로 나눈 나머지 값 반환
}
```
<br>

- 해시 테이블에 선형 조사 후 삽입 
```c
#define empty(item) (item.key==0)
#define equal(item1, item2) (item1.key==item2.key)

// 선형 조사법을 이용하여 테이블의 키를 삽입하고,
// 테이블이 가득 찬 경우는 종료
void hash_lp_add(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "탐색키가 중복되었습니다. \n");
			return;
		}
		printf("data = %d 저장 도중 Hashtable : %d에서 충돌 감지 ", item.key, i);
		i = (i + 1) % TABLE_SIZE;	// 다음 버킷으로 이동
		printf("- index = %d로 증가하였습니다. \n", i);

		if (i == hash_value) {		// 시작 주소로 되돌아온 경우 
			fprintf(stderr, "테이블이 가득찼습니다. \n");
			return;
		}
	}
	ht[i] = item;
}
```
<br>
  
- 해시 테이블에서 항목 탐색 
```c
// 선형 조사법을 이용해 테이블에 저장된 키를 탐색
void hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);	// 계산된 주소

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "%-3d는 HashTable : %d 에서 검색되었습니다. \n", item.key, i);
			return;
		}
		i = (i + 1) % TABLE_SIZE;	// 다음 버킷으로 이동
		if (i == hash_value) {		// 시작 주소로 되돌아온 경우 
			fprintf(stderr, "입력하신 값 %d 은 HashTable에서 검색되지않았습니다. \n", item.key);
			return;
		}
	}
	fprintf(stderr, "입력하신 값 %d 은 HashTable에서 검색되지않았습니다. \n", item.key);
}
```
</details>

<br>



<br>

## 이차 조사법 (Quadratic Probing)
- 0부터 증가시키며, 각 수의 제곱수를 해시 함수의 값에 더하여 다음 버킷을 조사하는 방법
- `(h(k) + inc*inc) mod M for inc=0,0, ... M-1`
- h(k), h(k)+1, h(k)+4, h(k)+9,...

```c
// 이차 조사법
void hash_qp_add(element item, element ht[]) {
	int i, hash_value, inc = 0;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "탐색키가 중복되었습니다. \n");
			return;
		}
		printf("data = %d 저장 도중 Hashtable : %d에서 충돌 감지 ", item.key, i);
		i = (i + inc*inc) % TABLE_SIZE;	// 다음 버킷으로 이동
		inc = inc + 1;
		printf("- index = %d로 증가하였습니다. \n", i);

		if (i == hash_value) {		// 시작 주소로 되돌아온 경우 
			fprintf(stderr, "테이블이 가득찼습니다. \n");
			return;
		}
	}
	ht[i] = item;
}
```
<br>

## 이중 해시법(Double Hashing)
- 항목을 저장할 다음 위치를 결정할 때 원래 해시 함수와 다른 별개의 해시 함수를 이용
<br>

- `h(k)` -> `h(k) + h'(k)` -> `h(k) + 2*h'(k)` ...


1. 일반적인 해시 함수(제산 함수): `h(k) = k mod M`
2. 두번째 해시 함수: `h'(k) = C - (k mod C)` (C는 해시 테이블 크기 M보다 약간 작은 소수)

<br>

<details>
  <summary> 구현 </summary>
  
```C

// 이중 해시법
void hash_dh_add(element item, element ht[]) {
	int i, hash_value, inc;
	hash_value = i = hash_function(item.key);
	inc = hash_function2(item.key);	// 두번째 해시 함수

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "탐색키가 중복되었습니다. \n");
			return;
		}
		printf("data = %d 저장 도중 Hashtable : %d에서 충돌 감지 ", item.key, i);
		i = (i + inc) % TABLE_SIZE;	// 다음 버킷으로 이동
		printf("- index = %d로 증가하였습니다. \n", i);

		if (i == hash_value) {		// 시작 주소로 되돌아온 경우 
			fprintf(stderr, "테이블이 가득찼습니다. \n");
			return;
		}
	}
	ht[i] = item;
}
```
</details>  
  
<br>

<br>

# 체이닝(chaining)
  
- 오버플로우 문제를 연결 리스트로 해결하는 방법
- 각 버킷이 하나 이상의 값을 가질 수 있도록 고정된 슬롯을 할당하지 않고 연결 리스트를 할당
- 버킷 내에서 원하는 항목을 찾을 때에는 연결리스트 순차 탐색 이용 <br>
- 충돌 발생 시 새로운 노드 삽입
  
<details>
  <summary> 체이닝 해시 테이블 구조체 구현 </summary>
  
```c
#define TABLE_SIZE 10	// 해싱 테이블의 크기(소수)
#define MOD 7			// 제산 함수에서 사용되는 나눗셈값

typedef struct element {
	int key;
}element;

struct list {
	element item;
	struct list* link;
};
struct list* hash_table[TABLE_SIZE];// 충돌 발생 시 연결 리스트로 구현하는 해싱 테이블
```
  
</details>
<br>
  
- 체인법을 이용한 삽입
```c
// 체인법을 이용하여 테이블에 키를 삽입
void hash_chain_add(element item, struct list* ht[]) {
	int hash_value = hash_function(item.key);
	struct list* ptr;
	struct list* node_before = NULL, * node = ht[hash_value];
	for (;node;node_before = node, node = node->link) {
		if (node->item.key == item.key) {
			fprintf(stderr, "이미 탐색키가 저장되어 있음 \n");
			return;
		}
	}
	ptr = (struct list*)malloc(sizeof(struct list));
	ptr->item = item;
	ptr->link = NULL;

	if (node_before)
		node_before->link = ptr;
	else
		ht[hash_value] = ptr;
}
```
<br>
  
- 체인법을 이용한 탐색
```c
// 체인법을 이용해 테이블에 저장된 키를 탐색
void hash_chain_search(element item, struct list* ht[]) {
	struct list* node;
	int hash_value = hash_function(item.key);
	for (node = ht[hash_value];node;node = node->link) {
		if (node->item.key == item.key) {
			fprintf(stderr, "탐색 %d 성공 \n", item.key);
			return;
		}
	}
	printf("키 탐색 실패 \n");
}
```
