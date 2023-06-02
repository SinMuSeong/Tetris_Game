#pragma warning (disable:4996)
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>


//게임 보드의 가로 세로 길이
#define GAME_BOARD_WIDTH 10
#define GAME_BOARD_HEIGHT 20


//게임보드가 시작되는 좌표 위치
#define GAME_BOARD_START_X 30
#define GAME_BOARD_START_Y 2


// 좌표 위치를 담을 구조체
COORD curPos;


//현재 콘솔의 커서 위치 좌표를 반환하는 함수
COORD GetCurrentCursorPos()
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;
}
//콘솔의 커서 위치를 지정한 좌표에 지정하는 함수
void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서를 콘솔창에 안보이게 하는 함수
void RemoveCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


//게임 보드 판을 그리는 함수
void DrawGameBoard()
{
	int x, y;

	for (y = 0; y <= GAME_BOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(GAME_BOARD_START_X, GAME_BOARD_START_Y + y);
		if (y == GAME_BOARD_HEIGHT)
			printf("□");
		else
			printf("□");
	}

	for (y = 0; y <= GAME_BOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(GAME_BOARD_START_X + (GAME_BOARD_WIDTH + 1) * 2, GAME_BOARD_START_Y + y);
		if (y == GAME_BOARD_HEIGHT)
			printf("□");
		else
			printf("□");
	}

	for (x = 1; x <= GAME_BOARD_WIDTH + 1; x++)
	{
		SetCurrentCursorPos(GAME_BOARD_START_X + x * 2, GAME_BOARD_START_Y + GAME_BOARD_HEIGHT);
		printf("□");
	}
}



int main()
{
	srand((unsigned int)time(NULL));
	RemoveCursor();


	DrawGameBoard();

	
	return 0;
}