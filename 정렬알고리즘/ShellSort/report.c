#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {		//학생 정보 구조체
	char* name;			//이름 포인터
	int num;			//학번 정수
	char* phone;		//전화번호 포인터
}Student;

void inc_insertion_sort(Student list[], int first, int last, int gap);
void shell_sort(Student list[], int n);
void print(Student list[], int count);

int main() {
	FILE *fp;				//파일포인터
	int count = 0;			//배열의 개수
	Student *data;			//학생 데이터 포인터
	char name[20], phone[20];
	int num;
	int i;

	fp = fopen("data.txt", "r");		//파일을 읽기 형식으로 open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {				//파일 끝까지 반복하며 임시변수에 담으면서 count를 증가
		fscanf(fp, "%s%d%s", name, &num, phone);
		count++;
	}
	rewind(fp);						//파일포인터를 앞으로 옮김
	data = (Student*)malloc(sizeof(Student)*count);		//data포인터 동적할당
	for(i=0; i<count; i++) {
		fscanf(fp, "%s%d%s", name, &data[i].num, phone);	//파일로부터 데이터 입력 학번은 직접 입력받음
		data[i].name = (char*)malloc(sizeof(char)*(strlen(name) + 1));	//name포인터 동적할당
		strcpy(data[i].name, name);										//문자열 복사

		data[i].phone = (char*)malloc(sizeof(char)*(strlen(phone) + 1));	//phone포인터 동적할당
		strcpy(data[i].phone, phone);										//문자열 복사
	}
	printf("<정렬 전> \n");
	print(data, count);		//정렬 전 배열 출력

	shell_sort(data, count);	//쉘정렬 함수 호출

	printf("\n<정렬 후>\n");
	print(data, count);		//정렬 후 배열 출력
	
	for (i = 0; i < count; i++) {	//이름포인터와 phone포인터 동적할당 해제
		free(data[i].name);
		free(data[i].phone);
	}
	free(data);			//data배열 동적할당 해제
	fclose(fp);			//파일포인터 close
	return 0;
}
void inc_insertion_sort(Student list[], int first, int last, int gap) {	//일정 간격으로 떨어져 있는 요소들을 삽입
	int i, j;
	Student key;										//정렬을 하기 위해 사용
	for (i = first + gap; i <= last; i = i + gap) {		//gap만큼 이동하며 쉘끼리 비교
		key = list[i];									//
		for (j = i - gap; j >= first && key.num > list[j].num; j = j - gap) { //만약 key의 num값이 리스트[j]의 num값보다 크다면 수행
			list[j + gap] = list[j];			//list[j]의 값을 뒤로 이동
		}
		list[j + gap] = key;				//
	}
}
void shell_sort(Student list[], int n) {	//쉘 정렬 함수
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {//gap을 전체의 절반부터 간격이 1이 될때까지 간격을 줄임
		if ((gap % 2) == 0)gap++;			//만약 gap이 짝수라면 gap에서 1 증가
		for (i = 0; i < gap; i++) {			//부분리스트의 개수 gap만큼 요소삽입정렬 함수를 반복
			inc_insertion_sort(list, i, n - 1, gap);

		}
		
		printf("%d\n", gap);
		print(list, n);
	}
}
void print(Student list[], int count) {		//배열 출력 함수
	int i;
	for (i = 0; i < count; i++) {		//배열의 개수 count만큼 반복하며 배열 출력
		printf("%s %d %s\n", list[i].name, list[i].num, list[i].phone);
	}
}