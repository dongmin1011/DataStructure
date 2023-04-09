/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과 
	이름 : 김동민 
	프로그램명 : 원형 큐를 이용한 점수 읽기 프로그램
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_QUEUE_SIZE 100							//큐 사이즈 100
typedef struct{
	char *name;										//이름 저장 문자포인터
	int num;										//학번저장
	int kor, eng, math;								//점수 저장 변수
}element;
typedef struct{
	element data[MAX_QUEUE_SIZE];					//큐 구조체 배열
	int front, rear;								//큐의 위치값
}QueueType;

void error(char *message);							//에러메시지 출력함수
void init(QueueType *q);							//큐 초기화 함수
int is_empty(QueueType *q);							//큐 공백상태 확인함수
int is_full(QueueType *q);							//큐 포화상태 확인함수
void queue_print(QueueType *q);						//큐 출력함수
void enqueue(QueueType *q, element item);			//큐에 삽입하는 enqueue함수
element dequeue(QueueType *q);						//큐를 삭제하는 dequeue함수
void input(FILE *fp,  QueueType*q);					//enqueue시 필요한 함수의 모음
void output(QueueType *q);							//dequeue시 필요한 함수의 모음
	
int main(){
	char str[20];
	QueueType q;
	FILE *fp;
	fp=fopen("data.txt", "r");						//data.txt를 읽기전용으로 open
	if(fp==NULL){
		printf("파일이 열리지 않습니다.\n");
		return 0;
	}
	init(&q);
	while(!feof(fp)){
		fscanf(fp, "%s", str);						//str은 enqueue또는 dequeue
		if(strcmp(str,"enqueue")==0){				//만약 str이 enqueue라면 0리턴
			input(fp,  &q);							//enqueue할때 필요한 input함수 호출
		}
		else if(strcmp(str, "dequeue")==0){			//만약 str이 dequeue라면 0리턴
			output(&q);								//dequeue할때 필요한 output함수 호출
		}
		else{
			error("enqueue 또는 dequeue가 아닙니다.\n");		//잘못된 입력이므로 에러메시지 출력후 강제종료
		}
		queue_print(&q);
	}
	fclose(fp);
}
void error(char *message){							//에러메시지 출력함수
	fprintf(stderr, "%s\n", message);				//stderr을 이용하여 버퍼없이 즉시 출력
	exit(1);
}
void init(QueueType *q){							//큐 초기화 함수
	q->front = q->rear = 0;							//원형큐이므로 front와 rear값을 0으로 설정
}
int is_empty(QueueType *q){							//큐 공백상태 확인 함수
	return (q->front == q->rear);					//front와 rear가 같다면 큐가 비어있는 상태이므로 같다면 1리턴 다르다면 0리턴
}
int is_full(QueueType *q){							//큐 포화상태 확인함수
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);	//rear에 1을 더하고 modulo연산 수행 후 이 값이 front와 같다면 포화상태
}
void queue_print(QueueType *q){						//큐를 출력하는 함수
	int i = q->front;								//i값은 front값으로 설정
	printf("QUEUE(front=%d rear=%d)\n", q->front, q->rear);	//현재 front와 rear값 출력
	if(!is_empty(q)){
		do{											//do while문을 이용하여 한번은 반드시 출력하도록 설정
			i = (i+1) % MAX_QUEUE_SIZE;						//원형큐이므로 i를 큐의 크기로 나머지연산 수행
			printf("%s | %d | %d | %d | %d |\n", q->data[i].name, q->data[i].num, q->data[i].kor,
				q->data[i].eng, q->data[i].math);		//큐 출력
			if(i==q->rear)break;					//만약 i가 rear값과 같다면 큐의 내용이 끝났으므로 종료
		}while(i!=q->front);						//i가 front값과 같아진다면 종료
	}
	printf("\n");
}
void enqueue(QueueType *q, element item){			//큐를 삽입하는 함수
	if(is_full(q))									//큐가 포화상태인지 확인
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;		//원형큐이므로 rear에 1을 더하고 나머지 연산수행후
	q->data[q->rear] = item;						//rear위치에 item을 대입
}
element dequeue(QueueType *q){						//큐를 삭제하는 함수
	if(is_empty(q))									//큐가 공백상태라면 큐를 삭제할 수 없으므로 오류
		error("큐가 공백상태입니다.\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;		//dequeue할땐 front값이 이동하므로 front를 나머지 연산
	return q->data[q->front];						//front위치에 있는 data를 리턴
}
void input(FILE *fp,  QueueType*q){					//data파일에서 enqueue가 입력되었을 때 수행하는 함수
	char s[20];
	element data;			
	fscanf(fp, "%s%d%d%d%d", s, &data.num, &data.kor, &data.eng, &data.math);	//파일로부터 enqueue뒤에 있는 정보들을 읽어옴
	data.name=(char *)malloc(strlen(s)+1);										//data구조체에 있는 name은 포인터이므로 동적할당 수행(입력받은 s의 길이에 \0문자 포함하여 +1)
	strcpy(data.name, s);														//strcpy함수를 이용하여 내용 복사
	enqueue(q, data);															//enqueue수행
}
void output(QueueType *q){							//data파일에서 dequeue가 입력되었을 때 수행하는 함수
	element data;
	data = dequeue(q);								//리턴받은 data값을 받아옴
	printf("삭제된 데이터: %s %d %d %d %d\n", data.name, data.num, data.kor, data.eng, data.math);	//삭제된 데이터 출력
	free(data.name);								//name은 동적할당된 상태이므로 free수행
}	
