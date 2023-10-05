#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 6

void initBoard();
void printBoard();
void deleteNum(int);	// 입력한 번호를 0으로 바꿔주는 함수
int checkBoard();		// max를 이용해서 빙고 라인 갯수 체크하기

int Board[MAX][MAX];

int main() {
	int num, lines;
	initBoard();
	printBoard();

	while (1) {
		printf("체크할 숫자를 골라주세요 : ");
		scanf("%d", &num);

		deleteNum(num);
		system("cls"); //화면 새로고침
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
//━┃┏ ┓┗ ┛┣ ┫┳ ┻ ╋

void initBoard() {
	int cnt = 1;
	// 1부터 i*j까지 순서대로 대입
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			//Board[i][j] = cnt++;
			Board[i][j] = 1; // 빙고 체크를 편하게 하기 위한 코드
		}
	}
}
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
				printf("♥┃", Board[row][col]);	// 0(선택했다면)이면 하트로 출력
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