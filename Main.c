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
#define STOP 8
#define LEFT 75
#define RIGHT 77
#define UP 72
#define SPACE 32
#define ENTER 13

//게임 보드 정보 배열
int gameBoardInfo[GAME_BOARD_HEIGHT + 1][GAME_BOARD_WIDTH + 2];

int speed;	//게임 속도
int score;	//게임 점수

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


//블럭의 정보를 받고 해당 블록을 콘솔 창에 그리는 함수
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


//블록을 콘솔 창에서 지우는 함수
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


//충돌 판정 확인하는 함수  (해당 좌표에 대해 지우개 블럭이 충돌이면 0반환)  (지우개 블럭 한정)
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
	if (block_id == 28)	//지우개 블럭 예외
	{
		if (!DetectCollision_erase(curPos.X, curPos.Y + 1, blockModel[block_id]))
		{
			setErase(curPos.X, curPos.Y, blockModel[28]); //해당 위치의 블록을 지운다.
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
		//블록이 해당 방향으로 움직일 수 있는지 판별하는 조건문
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

//콘솔 창에 나타난 블럭을 회전시키는 함수
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

// 블록이 하강하여 정착하면, 해당 블록을 게임 정보를 담은 가상 배열에 1로 표기하여 게임보드를 업데이트하는 함수
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

//게임 일시 정지
void StopGame()
{
	int cnt = 0;
	COORD temp = GetCurrentCursorPos();
	SetCurrentCursorPos(60, 23);
	printf("취소하려면 백스페이스 키를 다시 누르세요\n");
	while (1)		//탈출할 때 까지 무한 정지
	{
		while (!_kbhit())
		{
			Sleep(10);
		}
		int k = _getch();

		if (k == STOP)		//백 스페이스 키 누르면 해당 반복문 탈출 -> 게임 재개
			break;
	}
	SetCurrentCursorPos(60, 23);
	printf("                                                       ");

	SetCurrentCursorPos(temp.X, temp.Y);
}

//게임이 끝났는 지 확인하는 함수
int IsGameOver()
{
	if (!DetectCollision(curPos.X, curPos.Y, blockModel[block_id]))
		return 1;

	return 0;
}

//스페이스 바 (즉시 하강)
void SpaceDown()
{
	while (MoveDown());
}

//사용자에게 키 입력을 받는 함수
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
				SpaceDown();
				break;
			case STOP:
				StopGame();
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


//다음에 나타날 블럭을 콘솔창 오른쪽에 출력하여 플레이어 눈으로 확인할 수 있게 하는 함수 
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

void ShowManual()
{
	printf("Enter : 플레이 시작");


	const char* str[7];
	int i = 1;
	str[0] = "\n\n\n                    테르리스 게임";
	str[1] = "\n\n\n                    블럭 이동 : 방향키";
	str[2] = "\n\n\n                    블럭 하강 : 스페이스 바";
	str[3] = "\n\n\n                    일시정지 : 백 스페이스";
	str[4] = "\n\n\n                    5개의 줄을 완성시키면 다음 하강하는 블럭으로 지우개 블럭이 설정됩니다.";
	str[5] = "\n\n\n                    지우개 블럭은 하강하면서 다른 블럭과 충돌 시 다른 블럭들을 삭제합니다. \n\n\n                    순발력을 발휘하여 지우개 블럭을 잘 활용해 보세요.";
	str[6] = "\n\n\n                    플레이 하시려면   엔터 키를 누르세요.";

	for (int i = 0; i < 7; i++)
	{
		printf("%s", str[i]);
	}

	while (1) {
		while (!_kbhit());
		int key = _getch();
		if (key == ENTER) {
			break;
		}

		else
			continue;
	}

}


int main()
{
	ShowManual();
	system("cls"); //콘솔창 초기화


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

		if (checkEraseBlockCnt >= 5)	//5번의 줄을 지울 때 마다 다음 블록으로 지우개 블록 설정
		{
			next_block_id = 28;
			checkEraseBlockCnt = 0;
		}
		else
		{
			next_block_id = rand() % 28;	//그 외에는 랜덤하게 블록 생성
		}
		
		ShowNextBlock();	//다음에 떨어질 블록을 오른쪽 화면에 보이게

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

				AddBlockToBoard();		//게임 블록 정보 배열에 해당 블록 추가
				RemoveFillUpLine();		//한 줄이 완성되어있는지 검사 후, 완성 되어있으면 줄 지우고 블록 최신화
				break;
			}
			InputOperationKey();	//사용자에게 키 입력 받기
		}
	}


	SetCurrentCursorPos(60, 5);
	puts("Game Over!\n");
	getchar();
	
	return 0;
}