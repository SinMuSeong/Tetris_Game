#pragma warning (disable:4996)
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>


//게임 보드의 가로 세로 길이
#define GAME_BOARD_WIDTH 10
#define GAME_BOARD_HEIGHT 20


//게임보드가 시작되는 좌표 위치
#define GAME_BOARD_START_X 4
#define GAME_BOARD_START_Y 2


int block_id; //블럭의 종류를 나타낼 int 형 변수

char blockModel[][4][4] =
{
	/* 첫 번째 블록
		 ■
		 ■■■     */
	{
		{0, 0, 0, 0},
		{1, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0},
		{1, 0, 0, 0} },

		/* 두 번째 블록
				 ■
			 ■■■     */
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0} },
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0} },
		{
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 1, 0, 0},
			{0, 0, 0, 0} },
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0} },

			/* 세 번째 블록
					■
				  ■■■    */
			{
				{0, 0, 0, 0},
				{0, 1, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0} },
			{
				{0, 0, 0, 0},
				{0, 1, 0, 0},
				{1, 1, 0, 0},
				{0, 1, 0, 0} },
			{
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{1, 1, 1, 0},
				{0, 1, 0, 0} },
			{
				{0, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 1, 0},
				{0, 1, 0, 0} },

				/* 네 번째 블록

					  ■■■■   */
				{
					{0, 1, 0, 0},
					{0, 1, 0, 0},
					{0, 1, 0, 0},
					{0, 1, 0, 0} },
				{
					{0, 0, 0, 0},
					{0, 0, 0, 0},
					{1, 1, 1, 1},
					{0, 0, 0, 0} },
				{
					{0, 1, 0, 0},
					{0, 1, 0, 0},
					{0, 1, 0, 0},
					{0, 1, 0, 0} },
				{
					{0, 0, 0, 0},
					{0, 0, 0, 0},
					{1, 1, 1, 1},
					{0, 0, 0, 0} },

					/* 다섯 번째 블록

						  ■■
						  ■■      */
					{
						{1, 1, 0, 0},
						{1, 1, 0, 0},
						{0, 0, 0, 0},
						{0, 0, 0, 0} },
					{
						{1, 1, 0, 0},
						{1, 1, 0, 0},
						{0, 0, 0, 0},
						{0, 0, 0, 0} },
					{
						{1, 1, 0, 0},
						{1, 1, 0, 0},
						{0, 0, 0, 0},
						{0, 0, 0, 0} },
					{
						{1, 1, 0, 0},
						{1, 1, 0, 0},
						{0, 0, 0, 0},
						{0, 0, 0, 0} },


						/* 여섯 번째 블록
								■■
							  ■■      */
						{
							{0, 0, 0, 0},
							{0, 1, 1, 0},
							{1, 1, 0, 0},
							{0, 0, 0, 0} },
						{
							{0, 1, 0, 0},
							{0, 1, 1, 0},
							{0, 0, 1, 0},
							{0, 0, 0, 0} },
						{
							{0, 0, 0, 0},
							{0, 1, 1, 0},
							{1, 1, 0, 0},
							{0, 0, 0, 0} },
						{
							{0, 1, 0, 0},
							{0, 1, 1, 0},
							{0, 0, 1, 0},
							{0, 0, 0, 0} },

							/* 일곱 번째 블록

								  ■■
									■■    */
							{
								{0, 0, 0, 0},
								{1, 1, 0, 0},
								{0, 1, 1, 0},
								{0, 0, 0, 0} },
							{
								{0, 1, 0, 0},
								{1, 1, 0, 0},
								{1, 0, 0, 0},
								{0, 0, 0, 0} },
							{
								{0, 0, 0, 0},
								{1, 1, 0, 0},
								{0, 1, 1, 0},
								{0, 0, 0, 0} },
							{
								{0, 1, 0, 0},
								{1, 1, 0, 0},
								{1, 0, 0, 0},
								{0, 0, 0, 0} },
};


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



void ShowBlock(char blockInfo[4][4])
{
	int x, y;
	COORD curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (blockInfo[y][x] == 1)
				printf("■");
		}
	}

	SetCurrentCursorPos(curPos.X, curPos.Y);
	return 0;
}
void DeleteBlock(char blockInfo[4][4])
{
	int y, x;
	COORD curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (blockInfo[y][x] == 1)
				printf("  ");
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}


int MoveDown()
{

	DeleteBlock(blockModel[block_id]);
	curPos.Y += 1;
	SetCurrentCursorPos(curPos.X, curPos.Y);
	ShowBlock(blockModel[block_id]);

	return 1;
}
void MoveRight()
{
	DeleteBlock(blockModel[block_id]);
	curPos.X += 2;
	SetCurrentCursorPos(curPos.X, curPos.Y);
	ShowBlock(blockModel[block_id]);
}
void MoveLeft()
{

	DeleteBlock(blockModel[block_id]);
	curPos.X -= 2;
	SetCurrentCursorPos(curPos.X, curPos.Y);
	ShowBlock(blockModel[block_id]);
}

void RotateBlock()
{
	int block_origin = block_id - block_id % 4;		//회전하지 않은 원형 블럭의 배열 인덱스
	int block_rotated = block_origin + (block_id + 1) % 4;	//회전된 블럭의 배열 인덱스

	

	DeleteBlock(blockModel[block_id]);
	block_id = block_rotated;
	ShowBlock(blockModel[block_id]);
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


	curPos.X = GAME_BOARD_START_X + 10;
	curPos.Y = GAME_BOARD_START_Y + 10;

	SetCurrentCursorPos(curPos.X, curPos.Y);
	block_id = 1;
	
	while (1) 
	{
		//MoveDown();
		RotateBlock();

		Sleep(100);
	}
	
	
	return 0;
}