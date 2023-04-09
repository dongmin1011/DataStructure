#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *sorted;		//임시로 저장할 추가 배열

void merge(int list[], int left, int  mid, int right);	//부분 리스트 합병 함수
void merge_sort(int list[], int left, int right);		//부분 리스트 함수
void Print(int ary[], int count);		//배열 출력 함수
int main() {
	FILE *fp;
	int i, count=0, temp;
	int *ary;


	fp = fopen("data1.txt", "r");		//파일을 읽기 형식으로 open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);	//파일의 데이터를 임시 변수 temp에 담음
		count++;			//파일 데이터의 개수 증가
	}
	rewind(fp);
	ary = (int*)malloc(sizeof(int)*count);		//count로 ary와 sorted포인터 동적할당
	sorted = (int*)malloc(sizeof(int)*count);

	for (i = 0; i < count; i++) {//count만큼 반복하며 파일 데이터 입력
		fscanf(fp, "%d", &temp);
		ary[i] = temp;		//ary배열에 데이터 저장
	}
	
	printf("정렬되지 않은 리스트\n");
	Print(ary, count);			//합병 정렬 전 배열 출력

	merge_sort(ary, 0, count-1);		//합병 정렬 함수 호출

	printf("\n정렬된리스트\n");
	Print(ary, count);			//합병 정렬 후 배열 출력
	
	fclose(fp);		//파일포인터 닫음
	free(ary);		//ary포인터 해제
	free(sorted);	//sorted포인터 해제
	return 0;

}
void merge(int list[], int left, int  mid, int right) {	//부분 리스트 합병 함수
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {	//분할 정렬된 리스트 합병	
		if (list[i] <= list[j]) {		//만약 왼쪽 리스트 보다 오른쪽 리스트가 더 크다면
			sorted[k++] = list[i++];	//왼쪽 리스트의 데이터를 sorted에 담은 후 i증가
		}
		else {						//왼쪽 리스트 보다 오른쪽 리스트가 더 작다면
			sorted[k++] = list[j++];	// sorted에 오른쪽 데이터를 담은 후 j증가
		}
	}
	if (i > mid) {			//만약 i가 mid보다 더 크다면(오른쪽 리스트에 데이터가 남아있다면)
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];	//오른쪽 리스트에 남은 값을 sorted에 모두 복사
		}
	}
	else {					//만약 i가 mid보다 더 작다면(왼쪽 리스트에 데이터가 남아있다면)
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];	//왼쪽 리스트에 남은 값을 sorted에 모두 복사
		}
	}
	printf("\nleft list : ");
	for (l = left; l <= mid; l++) {		//왼쪽 리스트 출력
		printf("%d ", list[l]);
	}
	printf("\nright list : ");
	for (l = mid + 1; l <= right; l++) {	//오른쪽 리스트 출력
		printf("%d ", list[l]);
	}
	printf("\nSorted List: ");
	for (l = left; l <= right; l++) {	//합병된 리스트 출력
		printf("%d ", sorted[l]);
		list[l] = sorted[l];
	}
	printf("\n");
}
void merge_sort(int list[], int left, int right) {		//부분 리스트 함수
	int mid;

	if (left < right) {
		mid = (left + right) / 2;			//리스트의 균등 분할
		printf("%d\n", mid);
		merge_sort(list, left, mid);		//같은 크기의 2개의 부분 배열로 분할
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);	//정렬된 부분 배열을 하나의 배열에 통합
	}
}
void Print(int ary[], int count) {		//배열 출력 함수
	int i;
	for (i = 0; i < count; i++) {
		printf("<%d> ", ary[i]);		//배열의 개수 count만큼 반복하며 출력
	}
	printf("\n");
}

