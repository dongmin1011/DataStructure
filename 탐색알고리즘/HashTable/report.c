/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 해시테이블 프로그램
*/#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define MOD 7

typedef struct {
	int key;				//필드 선언
}element;



void init_table(element ht[]);	//해시 테이블 초기화 함수
int hash_function(int n);		//제산 함수를 사용한 해싱 함수

#define empty(item)(item.key==0)		//key가 0인지 확인하는 매크로
#define equal(item1, item2)(item.key==item2.key)	//item1과 item2가 같은지 확인하는 매크로

void hash_lp_add(element item, element ht[]);		//해시테이블 삽입함수
void hash_lp_search(element item, element ht[]);	//해시테이블 탐색함수
	
int main() {
	FILE *fp;
	int tmp;
	element e;
	char c;
	element hash_table[TABLE_SIZE];	//해시테이블 선언
	init_table(hash_table);		//해시 테이블 초기화

	fp = fopen("data1.txt", "r");		//data.txt파일 오픈
	if (!fp) {
		printf("file not open");
		return 0;
	}
	printf("< HashTableSize = [%d]> \n\n", TABLE_SIZE);
	while (!feof(fp)) {		//데이터를 끝까지 입력받음
		fscanf(fp, "%c", &c);
		if (c == 'i') {		//만약 c가 i라면 해시테이블에 삽입연산
			fscanf(fp, "%d", &tmp);
			e.key = tmp;
			hash_lp_add(e, hash_table);	//hash_lp_add함수를 호출하여 삽입
		}
	}
	rewind(fp);
	printf("\n< Find Data Location >\n");
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);
		if (c == 's') {
			fscanf(fp, "%d", &tmp);
			e.key = tmp;
			hash_lp_search(e, hash_table);
		}
		
	}

	fclose(fp);
	return 0;
}
void init_table(element ht[]) {	//해시 테이블 초기화 함수
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		ht[i].key = 0;			//해시 테이블 내의 값을 0으로 초기화
	}
}
int hash_function(int n) {		//제산 함수를 사용한 해싱 함수
	return n % MOD;
}

//선형 조사법을 이용하여 테이블에 키를 삽입하고, 테이블이 가득 찬 경우는 종료
void hash_lp_add(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (!equal(item, ht[i])) {	//만약 탐색 키가 중복될경우
			printf("data = %d 저장 도중 HashTable : %d 에서 충돌 감지 ", item.key, i);	//중복감지 메시지 출력
		}
		i = (i + 1) % MOD;	//mod7연산 인덱스 증가
		printf("- index = %d로 증가하였습니다.\n", i);
		if (i == hash_value) {		//테이블이 가득 찬 경우
			fprintf(stderr, "테이블이 가득 찼습니다.\n");
			exit(1);
		}
	}
	ht[i] = item;		//ht[i]에 item삽입
}
//선형 조사법을 이용하여 테이블에 지정된 키를 탐색
void hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) {

		if (equal(item, ht[i])) {	//해시 테이블에서 key가 검색된 경우
			printf("%d 는 HashTable : %d에서 검색되었습니다.\n", item.key, i);
			return;
		}

		i = (i + 1) % MOD;		//mode7연산 인덱스 증가
		if (i == hash_value) {		//찾는 key가 해시테이블에 없는 경우
			printf("입력하신 값 %d는 HashTable에서 검색되지 않았습니다.\n", item.key);
			return;
		}
	}
	printf("입력하신 값 %d는 HashTable에서 검색되지 않았습니다.\n", item.key);
}
