/*
�迭�� ����Ͽ� ���� Ʈ�� ������ �ϼ��ϰ�,
				��Ʈ ������ ���� �ڽ� ��带 ���� ���� ����ϴ� ���α׷�
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* fp;
	int* treeArr = NULL;
	int i, tmp, cnt = 1;

	fp = fopen("data.txt", "rt");
	if (fp == NULL) {
		fprintf(stderr, "���� �б� ���� \n");
		exit(1);
	}
	// ���Ϸκ��� �о� ��ü �������� ���� ���ϱ�
	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		cnt++;
	}

	// (���� ������ ���� + 1 )��ŭ �迭 ���� �Ҵ�
	treeArr = (int*)malloc(cnt * sizeof(int));
	rewind(fp);

	// ���� �ٽ� �о� Ʈ���� ����
	for (i = 1; i < cnt; i++)
		fscanf(fp, "%d", &treeArr[i]);

	/*
		��� i�� �θ� ��� �ε��� = i / 2
		��� i�� ���� �ڽ� ��� �ε��� = 2i
		��� i�� ������ �ڽ� ��� �ε��� = 2i + 1
	*/

	// ��Ʈ���� �����Ͽ� ���� �ڽ� ���(2i)�� ��� ���󰡸� ����ϴ� ���α׷�
	for (i = 1; i < cnt; i *= 2)
		printf("%d ", treeArr[i]);

	free(treeArr);	// �޸� ����
	fclose(fp);		// ���� �ݱ�
}