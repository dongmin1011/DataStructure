#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ( (t) = (x), (x)=(y), (y) = (t))	//x와 y의 자리를 교환하는 SWAP매크로 정의

int partition(int list[], int left, int right);		//리스트 분할 함수
void quick_sort(int list[], int left, int right);	//퀵정렬 함수
void Print(int list[], int count);	//배열 출력함수

int main() {
	FILE *fp;
	int i, tmp, count=0;
	int *ary;							//배열을 저장할 ary포인터 선언
		
	fp = fopen("data1.txt", "r");		//파일을 읽기 형식으로 open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {				//파일 끝까지 반복하며 데이터의 개수 증가
		fscanf(fp, "%d", &tmp);
		count++;
	}
	rewind(fp);				//파일포인터를 앞으로 옮김
	ary = (int*)malloc(sizeof(int)*count);	//ary포인터 동적할당
	for (i = 0; i < count; i++) {
		fscanf(fp, "%d", &tmp);
		ary[i] = tmp;		//ary배열에 파일 데이터 값 삽입
	}
	printf("< 정렬되지 않은 리스트 >\n");
	Print(ary, count);		//정렬 전 ary배열 출력

	quick_sort(ary, 0, count-1);		//퀵정렬 함수 호출

	printf("\n< 정렬된 리스트 >\n");
	Print(ary, count);		//정렬 후 ary배열 출력

	free(ary);				//ary배열 동적할당 해제
	fclose(fp);			//파일포인터 close
	return 0;		
}
int partition(int list[], int left, int right) {		//리스트 분할 함수
	int pivot, temp;
	int low, high;
	int i;
	low = left;								//low에 left값 저장
	high = right + 1;						//high에 right다음 값 저장
	pivot = list[left];						//피봇을 list[left]값으로 설정
	printf("\n-Pivot : %d-\n", pivot);
	do {
		do {
			low++;		//list[low]가 pivot보다 커질때까지 low를 증가
		} while (list[low] < pivot);

		printf("low : ");
		for (i = left; i <= right; i++) {
			if (list[i] == list[low]) {
				printf("%d ", list[low]);		//low값 출력
				break;
			}
		}
		if (i == right + 1) {
			printf("over ");
		}
	
		do {
			high--;		//list[highj]가 pivot보다 작아때까지 high를 감소
		} while (list[high] > pivot);

		printf("high : %d  [", list[high]);		//high값 출력

		for (i = left; i <= right; i++) {
			printf("%d > ", list[i]);		//list의 정렬 과정 출력
		}
		printf("]\n\n");

		if (low < high)SWAP(list[low], list[high], temp);	//만약 high가 더 크다면 list[low]와 list[high]의 값을 교환
	} while (low < high);
	SWAP(list[left], list[high], temp); // list[low]와 list[high]의 값을 교환
	return high; //high 리턴
}
void quick_sort(int list[], int left, int right) {	//퀵정렬 함수
	if (left < right) {
		int q = partition(list, left, right);	//pivot의 위치 반환 받음

		quick_sort(list, left, q - 1);			//left에서 피봇 바로 앞까지를 대상으로 순환호출
		quick_sort(list, q + 1, right);			//피봇 위치 바로 다음부터 right까지 순환호출
	}
}
void Print(int list[], int count) {		//배열 출력함수
	int i;
	for (i = 0; i < count; i++) {
		printf("%d > ", list[i]);	//배열의 개수만큼 반복하며 배열 출력
	}
}