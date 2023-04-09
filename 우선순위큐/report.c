/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 입력과 퇴장을 히프에 적용하고 
			 히프에 저장된 순서대로 출력하는 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name;						//이름 포인터
}Element;
typedef struct {
	Element *heap;					//힙 포인터
	int heap_size;					//힙의 크기
}HeapType;

HeapType* create();					//힙을 생성하고 반환하는 함수
void init(HeapType*, int);				//힙 초기화 함수
void insert_min_heap(HeapType*h, Element item);//힙의 요소의 개수가 heap_size인 히프에 삽입(최소 히프)
Element delete_min_heap(HeapType*h);		//힙에서 루트 노드를 삭제하고 반환하는 함수
void Print_Heap(HeapType*h);		//힙을 배열 순서대로 출력하는 함수
int Heap_Height(int);				//힙의 높이를 반환하는 함수
void Delete_Heap(HeapType*);		//힙과 힙의 포인터를 해제하는 함수

int main() {
	FILE*fp;						//파일포인터
	Element temp;					//삽입할때 값을 넘겨줄 임시 변수
	char s[10], c;					//s는 임시 문자열 변수, c는 i또는 o를 입력받을 변수
	int count=0;			//count는 i(삽입)의 개수
	HeapType *heap;					//힙 타입
	
	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open\n");
		return 0;
	}
	while (!feof(fp)) {				//파일 끝까지 데이터 입력
		fscanf(fp, "%c", &c);		//i또는 o입력
		if (c == 'i') {				//만약 i면 최대로 입력될 수 있는 개수를 구함
			fscanf(fp, "%s", s);
			count++;				//i의 개수 ++
		}
	}
	heap = create();				//힙 생성
	init(heap, Heap_Height(count));			//힙 초기화
	
	rewind(fp);										//파일포인터를 처음으로 옮김
	while (!feof(fp)) {								//count에는 i의 개수만 저장되어 있기 때문에 feof함수로 끝까지 반복
		fscanf(fp, "%c", &c);						//i(삽입)또는 o(삭제) 입력받음
		switch (c) {
		case 'i':									//만약 i를 입력받았다면 삽입 연산 수행
			fscanf(fp, "%s", s);					//임시 문자열 배열 s에 입력받음
			temp.name = (char*)malloc(sizeof(char)*(strlen(s) + 1));	//s의 길이 +1로 temp의 name포인터 동적할당
			strcpy(temp.name, s);										//temp.name에 s문자열 복사
			insert_min_heap(heap, temp);								//최소 히프에 삽입
			printf(">>손님(%s) 입장\n", temp.name);						//입력받은 이름 출력
			Print_Heap(heap);											//히프를 형식에 맞게 출력
			break;	
		case 'o':									//만약 o를 입력받았아면 루트 노드의 삭제 연산 수행
			temp = delete_min_heap(heap);			//삭제된 루트 노드 반환받음
			printf(">>손님(%s) 퇴장\n", temp.name);	//삭제된 노드 출력
			free(temp.name);						//삭제한 이름 포인터 메모리 해제
			Print_Heap(heap);						//히프를 형식에 맞게 출력
			break;
		}
		printf("\n");
	}
	Delete_Heap(heap);							//동적할당한 문자열 포인터, 힙 배열, 힙 메모리 해제			
	fclose(fp);									//파일 포인터 닫음
	return 0;
}
HeapType* create() {							//힙을 생성하고 반환하는 함수
	return (HeapType*)malloc(sizeof(HeapType));	//힙 타입을 자료형에 맞게 동적할당
}
void init(HeapType* h, int height) {						//힙의 크기를 0으로 초기화
	h->heap_size = 0;
	//힙의 높이 값에 따라 비트 시프트 연산을 통해 힙 배열 동적할당.
	//	printf("힙의 높이 : %d\n", height);
	//	printf("(1 << (height)) : %d\n", (1 << (height)));
	h->heap = (Element*)malloc(sizeof(Element)*((1 << (height))));
}
void insert_min_heap(HeapType*h, Element item) {//현재 요소의 개수가 heap_size h에 item을 삽입한다. (가장 작은 값이 루트)
	int i;
	i = ++(h->heap_size);
	//트리를 거술러 올라가면서 부모 노드와 비교
	while ((i != 1) && (strcmp(item.name, h->heap[i / 2].name) < 0)) {	
		//트리의 루트에는 가나다 순으로 가장 빨리 나오는 이름이 들어가야 함.
		//strcmp로 단어 비교 (만약 strcmp함수가 음수리턴이면 앞의 단어가 더 빠른 것), 가장 빨리 나오는 단어가 루트 노드가 됨.
		h->heap[i] = h->heap[i / 2];					//부모 노드의 데이터를 자식 노드에 저장(비교하며 하나씩 올라감)
		i /= 2;											//부모 노드로 이동
	}
	h->heap[i] = item;									//현재 위치 인덱스에 item 데이터 저장
}
Element delete_min_heap(HeapType*h) {									//힙에서 루트 노드를 삭제하고 반환하는 함수.
	int parent, child;
	Element item, temp;

	item = h->heap[1];									//item에 루트 노드 저장
	temp = h->heap[(h->heap_size)--];					//temp는 가장 마지막 노드를 저장하고 하나를 삭제하므로 heap_size개수 줄음
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {										//child가 히프 트리의 크기보다 작다면
		//child가 heap_size보다 작고 왼쪽 자식 노드가 오른족 자식 노드보다 가나다 순으로 늦게 나온다면(다음 자식 노드가 더 작다면) child++;
		if ((child < h->heap_size) && (strcmp((h->heap[child].name), h->heap[child + 1].name) > 0)) child++;

		//마지막 노드의 이름보다 현재 자식 노드보다 자식 노드가 더 늦게 나온다면 종료(temp이름이 더 작다면)
		if (strcmp(temp.name, h->heap[child].name) <= 0)break;

		h->heap[parent] = h->heap[child];						//자식 노드의 데이터를 부모 노드에 저장
		parent = child;											//자식 인덱스를 부모 인덱스로 저장
		child *= 2;												//child에 2를 곱하여 왼쪽 노드로 내려감
	}
	h->heap[parent] = temp;										//부모 노드에 temp저장(루트 노드에는 가장 작은 이름 저장됨)
	return item;												//루트 노드 반환
}
void Print_Heap(HeapType*h) {						//힙을 배열 순서로 출력하는 함수
	int i;
	printf("< 히프 출력 >\n");
	for (i = 1; i <= h->heap_size; i++) {			//i를 루트노드인 인덱스 1부터 힙의 크기인 heap_size까지 반복
		printf("%d: %s => ", i, h->heap[i].name);	//힙을 형식에 맞게 출력
	}
	printf("\n");
}
int Heap_Height(int count) {					//힙의 높이를 반환하는 함수 매개변수: 데이터 파일의 i 개수
	int i, height = 0;
	for (i = 1; i <= count; i = i * 2) {		//힙은 완전 이진트리이기 때문에 왼쪽 노드의 길이로 판단
						// 배열에 * 2를하면 왼쪽 노드를 가리키므로 왼쪽으로 이동하며 count보다 커질때까지 반복
		height++;											
	}
	return height;						//높이 반환
}
void Delete_Heap(HeapType*h) {			//힙을 삭제하는 함수
	int i;
	for (i = 1; i <= h->heap_size; i++) {//i를 루트노드인 인덱스 1부터 힙의 크기인 heap_size까지 반복
	//	printf("%s\n", h->heap[i].name);	
		free(h->heap[i].name);			//동적할당한 힙의 이름 문자열 포인터를 해제
	}
	free(h->heap);							//힙 배열 메모리 해제
	free(h);								//힙 메모리 해제
}