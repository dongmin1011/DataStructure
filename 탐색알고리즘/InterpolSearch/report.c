/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 보간 정렬 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int interpol_search(int list[], int key, int n) {			//보간 탐색 함수
	int low, high, j;

	low = 0;		//low는 가장 첫 인덱스
	high = n - 1;	//high는 가장 끝 인덱스
	int count = 0;
	while ((list[high] >= key) && (key > list[low])) {		
		j = ((float)(key - list[low]) / (list[high] - list[low])*(high - low)) + low;	//탐색 위치를 구하는 공식
		count++;
		if (key > list[j])low = j + 1;
		else if (key < list[j])high = j - 1;	//key보다 list[j]가 클때 high는 j-1
		else low = j;		//key와 list[j]가 같을 때
	}
	printf("%d\n", count);
	if (list[low] == key)return low;		//탐색성공
	else return -1;							//탐색 실패
}
int main() {
	FILE *fp;
	int count, find, i = 0;	//count는 데이터의 개수, find는 찾을 정수
	int n;					//찾을 정수의 위치를 저장
	int *list;				//데이터 파일을 저장할 배열
	clock_t start, stop;	
	double duration;

	fp = fopen("data.txt", "r");		//"data.txt"파일 오픈
	if (!fp) {
		printf("file not open");
		return 0;
	}
	printf("데이터의 개수 : ");
	scanf("%d", &count);					//데이터의 개수 입력
	printf("찾고자 하는 정수를 입력하세요: ");	
	scanf("%d", &find);						//찾고싶은 정수 입력

	list = (int*)malloc(sizeof(int)*count);	//count로 list포인터 동적할당
	for(i=0; i<count; i++){
		fscanf(fp, "%d", &list[i]);			//파일 데이터를 list에 삽입
	}
	start = clock();					//시작 시간 저장
	n = interpol_search(list, find, count);	//보간 탐색 함수 호출
	stop = clock();						//끝 시간 저장
	duration = (double)(stop - start) / CLOCKS_PER_SEC;	//실행 시간 계산
	if (n == -1) {
		printf("찾을 정수가 없음\n");
	}
	else {
		printf("%d 번째에 저장되어 있음\n", n + 1);	//위치 출력
		printf("보간 탐색 실행 속도 : %lf", duration);
	}
	free(list);		//리스트 동적할당 해제
	fclose(fp);		//파일포인터 닫음
	return 0;
}