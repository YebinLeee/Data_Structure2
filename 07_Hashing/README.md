# 해싱(Hashing)

- 해싱(Hashing)
- 해시 테이블(hash table)
- 해시 함수(hash function)
- 해시 주소(hash address)

<br>

- 버킷(bucket)
- 슬롯(slot)
- 동의어(synonym)
- 충돌(collision)
- 오버플로우(overflow)

<br>

## 해시 함수

해시 함수의 조건
1. 충돌이 적어야 함
2. 해시 함수 값이 테이블의 주소 영역 내에서 고르게 분포되어야 함
3. 계산이 빨라야 함

<br>

### 제산 함수
- 나머지 연산자(mod)를 사용해 키를 해시 테이블의 크기로 나눈 나머지를 해시 주소로 사용하는 방법
- `h(k) = k mod M`
- 해시 테이블의 크기 M은 주로 소수로 선택
<br>

### 폴딩 함수
- 이동 폴딩(shift folding)
- 경계 폴딩(boundary folding)


### 탐색 키가 문자열이 녁ㅇ우

<br>

# 개방 주소법
- 개방 주소법(open addressing): 충돌이 일어난 항목을 해시 테이블의 다른 위치에 저장

## 선형 조사법

<br>

## 이차 조사법

<br>

## 이중 해시법

<br>

## 임의 조사법

<br>

<br>

# 체이닝

