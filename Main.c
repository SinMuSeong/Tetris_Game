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

//방향키 아스키코드 Define
#define LEFT 75
#define RIGHT 77
#define UP 72
#define SPACE 32


//게임 보드 정보 배열
int gameBoardInfo[GAME_BOARD_HEIGHT + 1][GAME_BOARD_WIDTH + 2];

int speed;
int score;

int block_id; //블럭의 종류를 나타낼 int 형 변수
int next_block_id; //다음 블럭의 종류를 나타낼 int 형 변수

int checkEraseBlockCnt = 0;

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

									/* 지우개 번째 블록

									    □
										    */
								{
									{0, 0, 0, 0},
									{0, 1, 0, 0},
									{0, 0, 0, 0},
									{0, 0, 0, 0} }

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


//게임 정보를 담은 가상 배열에 벽으로 묘사되는 위치 인덱스 1을 할당
void setGameBoardInfo()
{
	int x, y;
	for (y = 0; y < GAME_BOARD_HEIGHT; y++)
	{
		gameBoardInfo[y][0] = 1;
		gameBoardInfo[y][GAME_BOARD_WIDTH + 1] = 1;
	}
	for (x = 0; x < GAME_BOARD_WIDTH + 2; x++)
	{
		gameBoardInfo[GAME_BOARD_HEIGHT][x] = 1;
	}
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
			if (blockInfo[y][x] == 1 && block_id != 28)
			{
				printf("■");
			}
			else if (blockInfo[y][x] == 1 && block_id == 28)
			{
				printf("□");
			}
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


//충돌 판정 확인하는 함수  (해당 좌표에 대해 특정 블럭이 충돌이면 0반환)
int DetectCollision(int posX, int posY, char blockModel[4][4])
{
	int x, y;
	int arrX = (posX - GAME_BOARD_START_X) / 2;
	int arrY = (posY - GAME_BOARD_START_Y);

	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			if (gameBoardInfo[arrY + y][arrX + x] == 1 && blockModel[y][x] == 1)
				return 0;
		}
	}
	return 1;
}


//충돌 판정 확인하는 함수  (해당 좌표에 대해 지우개 블럭이 충돌이면 0반환)
int DetectCollision_erase(int posX, int posY, char blockModel[4][4])
{
	int x, y;
	int arrX = (posX - GAME_BOARD_START_X) / 2;
	int arrY = (posY - GAME_BOARD_START_Y);

	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			if (arrY + y >= GAME_BOARD_HEIGHT && blockModel[y][x] == 1)
				return 0;
			else if (arrX + x >= GAME_BOARD_WIDTH + 1 && blockModel[y][x] == 1)
				return 0;
			else if (arrX + x <= 0 && blockModel[y][x] == 1)
				return 0;
		}
	}
	return 1;
}

//해당 위치에 특정 블럭의 모양에 대해 블럭을 지운다.
void setErase(int posX, int posY, char blockModel[4][4])
{
	int x, y;
	int arrX = (posX - GAME_BOARD_START_X) / 2;
	int arrY = (posY - GAME_BOARD_START_Y);

	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			if (gameBoardInfo[arrY + y][arrX + x] == 1 && blockModel[y][x] == 1)
				gameBoardInfo[arrY + y][arrX + x] = 0;
		}
	}

}

int MoveDown()
{
	if (block_id == 28)
	{
		if (!DetectCollision_erase(curPos.X, curPos.Y + 1, blockModel[block_id]))
		{
			setErase(curPos.X, curPos.Y, blockModel[28]);
			return 0;
		}
		setErase(curPos.X, curPos.Y, blockModel[28]);

		DeleteBlock(blockModel[block_id]);
		curPos.Y += 1;
		SetCurrentCursorPos(curPos.X, curPos.Y);
		ShowBlock(blockModel[block_id]);

		return 1;
	}
	else
	{
		if (!DetectCollision(curPos.X, curPos.Y + 1, blockModel[block_id]))
			return 0;

		DeleteBlock(blockModel[block_id]);
		curPos.Y += 1;
		SetCurrentCursorPos(curPos.X, curPos.Y);
		ShowBlock(blockModel[block_id]);

		return 1;
	}
}
void MoveRight()
{
	if (block_id == 28)
	{
		if (!DetectCollision_erase(curPos.X + 2, curPos.Y, blockModel[block_id]))
		{
			setErase(curPos.X, curPos.Y, blockModel[28]);
			return 0;
		}
		setErase(curPos.X, curPos.Y, blockModel[28]);

		DeleteBlock(blockModel[block_id]);
		curPos.X += 2;
		SetCurrentCursorPos(curPos.X, curPos.Y);
		ShowBlock(blockModel[block_id]);
	}
	else
	{
		if (!DetectCollision(curPos.X + 2, curPos.Y, blockModel[block_id]))
			return 0;

		DeleteBlock(blockModel[block_id]);
		curPos.X += 2;
		SetCurrentCursorPos(curPos.X, curPos.Y);
		ShowBlock(blockModel[block_id]);
	}
}
void MoveLeft()
{
	if (block_id == 28)
	{
		if (!DetectCollision_erase(curPos.X - 2, curPos.Y, blockModel[block_id]))
		{
			setErase(curPos.X, curPos.Y, blockModel[28]);
			return 0;
		}

		setErase(curPos.X, curPos.Y, blockModel[28]);

		DeleteBlock(blockModel[block_id]);
		curPos.X -= 2;
		SetCurrentCursorPos(curPos.X, curPos.Y);
		ShowBlock(blockModel[block_id]);
	}
	else
	{
		if (!DetectCollision(curPos.X - 2, curPos.Y, blockModel[block_id]))
			return 0;

		DeleteBlock(blockModel[block_id]);
		curPos.X -= 2;
		SetCurrentCursorPos(curPos.X, curPos.Y);
		ShowBlock(blockModel[block_id]);
	}
}

void RotateBlock()
{
	int block_origin = block_id - block_id % 4;		//회전하지 않은 원형 블럭의 배열 인덱스
	int block_rotated = block_origin + (block_id + 1) % 4;	//회전된 블럭의 배열 인덱스

	if (!DetectCollision(curPos.X, curPos.Y, blockModel[block_rotated]))
		return 0;

	DeleteBlock(blockModel[block_id]);
	block_id = block_rotated;
	ShowBlock(blockModel[block_id]);
}

void AddBlockToBoard()
{
	int x, y, arrCurX, arrCurY;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			arrCurX = (curPos.X - GAME_BOARD_START_X) / 2;
			arrCurY = curPos.Y - GAME_BOARD_START_Y;

			if (blockModel[block_id][y][x] == 1)
				gameBoardInfo[arrCurY + y][arrCurX + x] = 1;

		}
	}
}


//갱신된 게임 판 정보를 토대로 블럭들을 다시 그리는 함수
void RedrawBlocks()
{
	int x, y;
	int cursX, cursY;
	for (y = 0; y < GAME_BOARD_HEIGHT; y++)
	{
		for (x = 1; x < GAME_BOARD_WIDTH + 1; x++)
		{
			cursX = x * 2 + GAME_BOARD_START_X;
			cursY = y + GAME_BOARD_START_Y;
			SetCurrentCursorPos(cursX, cursY);
			if (gameBoardInfo[y][x] == 1)
			{
				printf("■");
			}
			else { printf("  "); }
		}
	}
}


//블럭 한 줄이 다 채워졌는지 게임 판 밑에서 부터 검사
void RemoveFillUpLine()
{
	int line, x, y;

	for (y = GAME_BOARD_HEIGHT - 1; y > 0; y--)
	{
		for (x = 1; x < GAME_BOARD_WIDTH + 1; x++)
		{
			if (gameBoardInfo[y][x] != 1)		//블럭 한 줄에 빈 칸이 있으면 종료
				break;
		}
		if (x == GAME_BOARD_WIDTH + 1)		//한 줄이 완성이 되어있으면
		{
			score += 10;
			checkEraseBlockCnt++;
			for (line = 0; y - line > 0; line++)	//완성된 아래의 줄에서 다음 윗줄 메모리 복사
			{
				memcpy(&gameBoardInfo[y - line][1], &gameBoardInfo[(y - line) - 1][1],
					GAME_BOARD_WIDTH * sizeof(int));
			}
			y++;
		}
		RedrawBlocks();
	}
}




int IsGameOver()
{
	if (!DetectCollision(curPos.X, curPos.Y, blockModel[block_id]))
		return 1;

	return 0;
}

void InputOperationKey()
{
	int i, key;
	for (i = 0; i < 20; i++)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			switch (key)
			{
			case LEFT:
				MoveLeft();
				break;
			case RIGHT:
				MoveRight();
				break;
			case UP:
				RotateBlock();
				break;
			case SPACE:
				MoveDown();
			}
		}
		Sleep(speed);
	}
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

//게임 진행 스코어를 화면에 나타내는 함수
void DrawScore()
{
	SetCurrentCursorPos(60, 20);
	printf("Score : %d", score);
}

void ShowNextBlock()
{
	COORD temp = GetCurrentCursorPos();

	SetCurrentCursorPos(60, 9);
	printf("다음에 나타날 블럭");

	SetCurrentCursorPos(60, 10);
	DeleteBlock(blockModel[block_id]);
	

	
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(60+ (x * 2), 10 + y);
			if (blockModel[next_block_id][y][x] == 1 && next_block_id != 28)
			{
				printf("■");
			}
			else if (blockModel[next_block_id][y][x] == 1 && next_block_id == 28)
			{
				printf("□");
			}
		}
	}

	SetCurrentCursorPos(temp.X, temp.Y);
}


int main()
{
	srand((unsigned int)time(NULL));
	RemoveCursor();
	DrawGameBoard();
	setGameBoardInfo();
	speed = 5;

	next_block_id = rand() % 28;  	//랜덤한 블럭 원형을 생성한다.

	

	while (1)		//전체 게임 진행을 위한 반복문
	{
		block_id = next_block_id;
		SetCurrentCursorPos(GAME_BOARD_START_X + GAME_BOARD_WIDTH, 0);
		curPos = GetCurrentCursorPos();
		DrawScore();

		if (checkEraseBlockCnt == 5)
		{
			next_block_id = 28;
			checkEraseBlockCnt = 0;
		}
		else
		{
			next_block_id = rand() % 28;
		}
		


		ShowNextBlock();


		//벽돌이 위에 더 생성될 수 없으면 GameOver
		if (IsGameOver())
			break;

		while (1)		//벽돌이 떨어지는 것을 구현한 반복문
		{
			if (MoveDown() == 0)		//MoveDown은 밑에 블럭이 있어 더 내려가지 못하면 0을 반환,
			{
				if (block_id == 28)
				{
					RedrawBlocks();
					break;
				}

				AddBlockToBoard();
				RemoveFillUpLine();
				break;
			}
			InputOperationKey();
		}
	}


	SetCurrentCursorPos(60, 5);
	puts("Game Over!\n");
	getchar();
	
	return 0;
}