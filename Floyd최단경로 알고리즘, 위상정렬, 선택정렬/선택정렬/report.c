/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 선택정렬 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))	//두 변수의 값을 변경하는 SWAP 정의

typedef struct Data {	//기본 자료형 데이타 구조체
	char *date;			//년도를 저장할 date 문자열 포인터
	int walking;		//걸음 횟수를 저장할 walking변수
}Data;

void selection_sort(Data list[], int n);		//선택정렬함수
void Print(Data ary[], int n);		//배열 출력 함수
void Delete(Data *ary, int count);		//데이터 삭제함수

int main() {
	FILE *fp;		//파일포인터
	Data *ary;		//Data자료형 포인터, 데이터의 개수로 동적할당
	int count = 0;	//데이터의 개수를 셀 count변수
	char str[20];	//파일로부터 문자열을 임시로 입력받을 문자열 변수
	int data, i = 0;	//걸음 수를 입력받을 data

	fp = fopen("results_stpes.txt", "r");	//파일을 읽기 형식으로 open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {			//파일 끝까지 입력
		fscanf(fp, "%s%d", str, &data);
		count++;				//데이터의 개수 증가
	}
	ary = (Data*)malloc(sizeof(Data)*count);	//데이터의 개수로 동적할당
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%s%d", str, &data);		//날짜 문자열, 걸음수 입력
		//현재 위치의 date문자열을 str의 길이로 동적할당
		ary[i].date = (char*)malloc(sizeof(char)*(strlen(str) + 1));
		strcpy(ary[i].date, str);	//str문자열을 date에 복사
		ary[i].walking = data;	//걸음수 삽입

		i++;	//i증가
	}
	printf("** Selection Sort 정렬 전 출력 **\n");
	printf("=================================\n");
	Print(ary, count);		//선택정렬 전 출력

	selection_sort(ary, count);	//선택정렬 함수 출력
	printf("\n\n** Selection Sort 정렬 후 출력 **\n");
	printf("=================================\n");
	Print(ary, count);		//선택정렬 후 출력

	Delete(ary, count);		//ary데이터 삭제
	fclose(fp);				//파일포인터 닫음	
	return 0;
}
void selection_sort(Data list[], int n) {		//선택정렬함수
	int i, j, high;		//i와 j는 반복문을 돌 변수, high는 가장 큰 값의 인덱스
	Data temp;
	for (i = 0; i < n - 1; i++) {
		high = i;						//현재 값의 인덱스를 high에 담음
		for (j = i + 1; j < n; j++) {
			if (list[j].walking > list[high].walking)high = j;		//high에 가장 큰 값의 인덱스 저장
		}
		SWAP(list[i], list[high], temp);		//현재 인덱스와 high인덱스의 값을 변경
	}
}
void Print(Data ary[], int n) {		//배열 출력 함수

	int i;
	for (i = 0; i < n; i++) {
		printf("%s %d\n", ary[i].date, ary[i].walking);	//날짜, 걸음 수 순으로 출력
	}
}
void Delete(Data *ary, int count) {		//데이터 삭제함수
	int i;
	for (i = 0; i < count; i++) {
		free(ary[i].date);	//파일 끝까지 돌며 data문자열 삭제
	}
	free(ary);		//ary배열 삭제
}