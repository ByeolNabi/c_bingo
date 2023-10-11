#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

#define MAX 5

void random_non_dup1(int *arr);	// 중복없는 랜덤뽑기 (MAX종속)
void initBoard();
void printBoard();
void deleteNum(int);	// 입력한 번호를 0으로 바꿔주는 함수
int checkBoard();		// max를 이용해서 빙고 라인 갯수 체크하기

int Board[MAX][MAX];

int main() {
	srand((unsigned)time(NULL));
	int num, lines;
	initBoard();

	printBoard();

	while (1) {
		printf("체크할 숫자를 골라주세요 : ");
		scanf("%d", &num);

		deleteNum(num);
		//system("cls"); //화면 새로고침
		printBoard();

		lines = checkBoard();
		printf("빙고 갯수 : %d\n", lines);
		/*if (lines >= 2) {
			printf("Bingo!!!\n");
			break;
		}*/
	}
	return 0;
}
// 될때까지 그리는 알고리즘
void random_non_dup1(){
	int arr[MAX * MAX] = { 0 };
	// printf("random_start\n");
	int max_num = MAX*MAX;
	
	for (int i = 0; i < max_num; i++) {
		arr[i] = (rand() % max_num) + 1;
		for (int j = 0; j < i; j++) {
			if (arr[i] == arr[j]) i--;
		}
	}
	// 1부터 i*j까지 순서대로 대입
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			Board[i][j] = arr[i*MAX+j];
		}
	}
	// for(int i = 0; i < max_num; ++i){
	// 	arr[i] = rand()%max_num+1;
	// 	printf("[");
	// 	for(int idx = 0; idx < max_num; idx++){
	// 		printf("%d, ", arr[idx]);
	// 	}
	// 	printf("]\n");
	// 	printf("randNUM: %d", rand_num);
	// 	for(int j = 0; j < i; ++j){
	// 		if(arr[j] == rand_num) {
	// 			--i;
	// 			break;
	// 		}
	// 	}
	// }
}
// 일정 횟수만큼 섞는 알고리즘
void random_non_dup2() {
	// 1부터 i*j까지 순서대로 대입
	int cnt = 1;
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			Board[i][j] = cnt++; // 빙고 체크를 편하게 하기 위한 코드
		}
	}
	int mix = 10000;
	int x1, y1, x2, y2, tmp;
	for (int i = 0; i < mix; ++i) {
		x1 = rand() % MAX;
		y1 = rand() % MAX;
		x2 = rand() % MAX;
		y2 = rand() % MAX;

		tmp = Board[x2][y2];
		Board[x2][y2] = Board[x1][y1];
		Board[x1][y1] = tmp;
	}
}
void initBoard() {
	// printf("initBoard_start\n");
	random_non_dup2();
	
}
//━┃┏ ┓┗ ┛┣ ┫┳ ┻ ╋
void printBoard() {
	// 뚜껑 그리기
	printf("┏");
	for (int i = 0; i < MAX; ++i) {
		if (i != MAX-1) printf("━━┳");
		else printf("━━┓");
	}
	printf("\n");
	// MAX줄 출력을 위한 상위 for문
	for (int row = 0; row < MAX; ++row) {
		// 숫자 라인 그리기
		printf("┃");
		for (int col = 0; col < MAX; ++col) {
			if(Board[row][col] != 0)
				printf("%2d┃", Board[row][col]);
			else
				// printf(" ♥┃");	// 0(선택했다면)이면 하트로 출력 mac
				printf("♥┃");	// 0(선택했다면)이면 하트로 출력 window
		}
		printf("\n");
		// 닫는 라인 그리기
		if (row != MAX - 1) {
			printf("┣");
			for (int i = 0; i < MAX; ++i) {
				if (i != MAX - 1) printf("━━╋");
				else printf("━━┫");
			}
		}
		else {	// 마지막 줄이라면 닫기
			printf("┗");
			for (int i = 0; i < MAX; ++i) {
				if (i != MAX - 1) printf("━━┻");
				else printf("━━┛");

			}
		}
		printf("\n");
	}
//┏━━┳━━┳━━┳━━┓
//┃  ┃  ┃  ┃  ┃
//┣━━╋━━╋━━╋━━┫
//┃  ┃  ┃  ┃  ┃
//┗━━┻━━┻━━┻━━┛
}
void deleteNum(int target) {
	// 전체 탐색하면서 target을 찾으면 0으로 초기화
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			if (Board[i][j] == target) {
				Board[i][j] = 0;
				return;
			}
		}
	}
}
int checkBoard() {
	int total = 0;	// 총 라인 갯수
	int cnt = 0;	// 한 줄이 빙고인지 카운트 하기 위한 변수 MAX라면 빙고
	// 가로 스캔
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			if (Board[i][j] == 0) ++cnt;
		}
		if (cnt == MAX) ++total;
		cnt = 0;
	}
	// 세로 스캔
	for (int j = 0; j < MAX; ++j) {
		for (int i = 0; i < MAX; ++i) {
			if (Board[i][j] == 0) ++cnt;
		}
		if (cnt == MAX) ++total;
		cnt = 0;
	}
	// [\] 판단하기
	for (int i = 0; i < MAX; ++i) {
		if (Board[0+i][0+i] == 0) ++cnt;
	}
	if (cnt == MAX) ++total;
	cnt = 0;
	// [/] 판단하기
	for (int i = 0; i < MAX; ++i) {
		if (Board[(MAX-1) - i][0 + i] == 0) ++cnt;
	}
	if (cnt == MAX) ++total;

	return total;
}