#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 3

void initBoard();
void printBoard();
void deleteNum(int);	// 입력한 번호를 0으로 바꿔주는 함수
int checkBoard();		// max를 이용해서 체크하기?

int Board[MAX][MAX];

int main() {
	int num, lines;
	initBoard();
	printBoard();

	while (1) {
		printf("체크할 숫자를 골라주세요");
		scanf("%d", &num);

		deleteNum(num);
		system("cls");
		printBoard();

		lines = checkBoard();

		if (lines >= 2) {
			printf("Bingo!!!\n");
			break;
		}
	}
	return 0;
}
//━┃┏ ┓┗ ┛┣ ┫┳ ┻ ╋

void initBoard() {
	int cnt = 1;
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			Board[i][j] = cnt++;
		}
	}
}
void printBoard() {
	printf("┏");
	for (int i = 0; i < MAX; ++i) {
		if (i != MAX-1) printf("━━┳");
		else printf("━━┓");
	}
	printf("\n");
	for (int row = 0; row < MAX; ++row) {
		printf("┃");
		for (int col = 0; col < MAX; ++col) {
			if(Board[row][col] != 0)
				printf("%2d┃", Board[row][col]);
			else
				printf("♥┃", Board[row][col]);
		}
		printf("\n");
		if (row != MAX - 1) {
			printf("┣");
			for (int i = 0; i < MAX; ++i) {
				if (i != MAX - 1) printf("━━╋");
				else printf("━━┫");
			}
		}
		else {
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
	int total = 0;
	int cnt = 0;
	// 가로 스캔
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			if (Board[i][j] == 0) ++cnt;
			else cnt = 0;
		}
		if (cnt == MAX) ++total;
		cnt = 0;
	}
	// 세로 스캔
	for (int j = 0; j < MAX; ++j) {
		for (int i = 0; i < MAX; ++i) {
			if (Board[i][j] == 0) ++cnt;
			else cnt = 0;
		}
		if (cnt == MAX) ++total;
		cnt = 0;
	}
	// [\] 판단하기
	for (int i = 0; i < MAX; ++i) {
		if (Board[0+i][0+i] == 0) ++cnt;
		else cnt = 0;
	}
	if (cnt == MAX) ++total;
	cnt = 0;
	// [/] 판단하기
	for (int i = 0; i < MAX; ++i) {
		if (Board[(MAX-1) - i][0 + i] == 0) ++cnt;
		else cnt = 0;
	}
	if (cnt == MAX) ++total;

	return total;
}