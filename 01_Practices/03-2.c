/*
	작성자: 이예빈(20204059)
	작성일: 2021.09.15
	프로그램명: 배열을 사용하여 이진 트리 구조를 완성하고,
				루트 노드부터 왼쪽 자식 노드를 따라 가며 출력하는 프로그램
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* fp;
	int* treeArr = NULL;
	int i, tmp, cnt = 1;

	fp = fopen("data.txt", "rt");
	if (fp == NULL) {
		fprintf(stderr, "파일 읽기 실패 \n");
		exit(1);
	}
	// 파일로부터 읽어 전체 데이터의 개수 구하기
	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		cnt++;
	}

	// (정수 데이터 개수 + 1 )만큼 배열 동적 할당
	treeArr = (int*)malloc(cnt * sizeof(int));
	rewind(fp);

	// 파일 다시 읽어 트리에 저장
	for (i = 1; i < cnt; i++)
		fscanf(fp, "%d", &treeArr[i]);

	/*
		노드 i의 부모 노드 인덱스 = i / 2
		노드 i의 왼쪽 자식 노드 인덱스 = 2i
		노드 i의 오른쪽 자식 노드 인덱스 = 2i + 1
	*/

	// 루트부터 시작하여 왼쪽 자식 노드(2i)를 계속 따라가며 출력하는 프로그램
	for (i = 1; i < cnt; i *= 2)
		printf("%d ", treeArr[i]);

	free(treeArr);	// 메모리 해제
	fclose(fp);		// 파일 닫기
}