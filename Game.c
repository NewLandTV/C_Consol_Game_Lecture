#include "Game.h"

int score;
int currentArrow;
int nextArrow;
int timer;

void Init()
{
	srand((unsigned int)time(NULL));
	
	system("title Console Game");
	system("mode con cols=100 lines=50");
	
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	
	DrawLine();
	
	score = 0;
	currentArrow = rand() & 1 ? 1 : 0;
	nextArrow = rand() & 1 ? 1 : 0;
	timer = 5;
	
	DrawArrow();
	_beginthreadex(NULL, 0, TimerThread, 0, 0, NULL);
}

void Update()
{
	int key = Input();
	
	DrawScore();
	DrawTimer();
	CheckTimer();
	
	if (key != -2)
	{
		switch (key)
		{
		// ESC를 눌러서 게임 종료 
		case 27:
			exit(1);
			
		case 224:
			key = _getch();
			
			switch (key)
			{
			// 왼쪽 화살표 키를 입력하면 왼쪽으로 이동 
			case 75:
				Gotoxy(5, 3);
				printf("L");
				CheckInput(0);
				
				break;
				
			// 오른쪽 화살표 키를 입력하면 오른쪽으로 이동 
			case 77:
				Gotoxy(5, 3);
				printf("R");
				CheckInput(1);
				
				break;
			}
			
			break;
		}
	}
}

void DrawLine()
{
	int y;
	
	for (y = 0; y < CONSOLE_HEIGHT; y++)
	{
		Gotoxy(CONSOLE_WIDTH >> 3, y);
		printf("#");
		Gotoxy(CONSOLE_WIDTH >> 1, y);
		printf("#");
	}
}

void DrawScore()
{
	Gotoxy(CONSOLE_WIDTH - 23, 3);
	printf("SCORE : %04d", score);
}

void DrawArrow()
{
	int x;
	int y;
	
	for (y = 2; y < (CONSOLE_HEIGHT >> 1) + 5; y++)
	{
		for (x = (CONSOLE_WIDTH >> 3) + 4; x < (CONSOLE_WIDTH >> 1) - 3; x++)
		{
			Gotoxy(x, y);
			printf(" ");
		}
	}
	
	// nextArrow가 0이 아니면 (오른쪽) 
	if (nextArrow)
	{
		for (x = 0; x < 12; x++)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 3) + 5, 5);
			printf("#");
			Gotoxy(x + (CONSOLE_WIDTH >> 3) + 5, 10);
			printf("#");
		}
		
		for (y = 0; y < 6; y++)
		{
			Gotoxy((CONSOLE_WIDTH >> 3) + 4, y + 5);
			printf("#");
		}
		
		for (y = 0; y < 3; y++)
		{
			Gotoxy((CONSOLE_WIDTH >> 3) * 2 + 4, y + 2);
			printf("#");
			Gotoxy((CONSOLE_WIDTH >> 3) * 2 + 4, y + 11);
			printf("#");
		}
		
		for (x = 0, y = 0; x < 5, y < 5; x++, y++)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 3) * 2 + 5, y + 3);
			printf("#");
		}
		
		for (x = 0, y = 5; x < 5, y > 0; x++, y--)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 3) * 2 + 5, y + 7);
			printf("#");
		}
	}
	// nextArrow가 0이면 (왼쪽) 
	else
	{
		for (x = 0; x < 12; x++)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 2) + 9, 5);
			printf("#");
			Gotoxy(x + (CONSOLE_WIDTH >> 2) + 9, 10);
			printf("#");
		}
		
		for (y = 0; y < 6; y++)
		{
			Gotoxy((CONSOLE_WIDTH >> 1) - 4, y + 5);
			printf("#");
		}
		
		for (y = 0; y < 3; y++)
		{
			Gotoxy((CONSOLE_WIDTH >> 2) + 9, y + 2);
			printf("#");
			Gotoxy((CONSOLE_WIDTH >> 2) + 9, y + 11);
			printf("#");
		}
		
		for (x = 5, y = 0; x > 0, y < 5; x--, y++)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 2) + 3, y + 3);
			printf("#");
		}
		
		for (x = 5, y = 5; x > 0, y > 0; x--, y--)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 2) + 3, y + 7);
			printf("#");
		}
	}
	
	// currentArrow가 0이 아니면 (오른쪽) 
	if (currentArrow)
	{
		for (x = 0; x < 12; x++)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 3) + 5, 21);
			printf("#");
			Gotoxy(x + (CONSOLE_WIDTH >> 3) + 5, 26);
			printf("#");
		}
		
		for (y = 0; y < 6; y++)
		{
			Gotoxy((CONSOLE_WIDTH >> 3) + 4, y + 21);
			printf("#");
		}
		
		for (y = 0; y < 3; y++)
		{
			Gotoxy((CONSOLE_WIDTH >> 3) * 2 + 4, y + 18);
			printf("#");
			Gotoxy((CONSOLE_WIDTH >> 3) * 2 + 4, y + 27);
			printf("#");
		}
		
		for (x = 0, y = 0; x < 5, y < 5; x++, y++)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 3) * 2 + 5, y + 19);
			printf("#");
		}
		
		for (x = 0, y = 5; x < 5, y > 0; x++, y--)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 3) * 2 + 5, y + 23);
			printf("#");
		}
	}
	// currentArrow가 0이면 (왼쪽) 
	else
	{
		for (x = 0; x < 12; x++)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 2) + 9, 21);
			printf("#");
			Gotoxy(x + (CONSOLE_WIDTH >> 2) + 9, 26);
			printf("#");
		}
		
		for (y = 0; y < 6; y++)
		{
			Gotoxy((CONSOLE_WIDTH >> 1) - 4, y + 21);
			printf("#");
		}
		
		for (y = 0; y < 3; y++)
		{
			Gotoxy((CONSOLE_WIDTH >> 2) + 9, y + 18);
			printf("#");
			Gotoxy((CONSOLE_WIDTH >> 2) + 9, y + 27);
			printf("#");
		}
		
		for (x = 5, y = 0; x > 0, y < 5; x--, y++)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 2) + 3, y + 19);
			printf("#");
		}
		
		for (x = 5, y = 5; x > 0, y > 0; x--, y--)
		{
			Gotoxy(x + (CONSOLE_WIDTH >> 2) + 3, y + 23);
			printf("#");
		}
	}
}

void DrawTimer()
{
	Gotoxy(CONSOLE_WIDTH - 23, 7);
	printf("TIMER : %02ds", timer);
}

void CheckTimer()
{
	if (timer <= 0)
	{
		GameOver();
	}
}

void CheckInput(int direction)
{
	if (currentArrow == direction)
	{
		score++;
		currentArrow = nextArrow;
		nextArrow = rand() & 1 ? 1 : 0;
		timer++;
		
		DrawArrow();
		
		return;
	}
	
	// 게임 오버 처리 
	GameOver();
}

void GameOver()
{
	int i;
	char* overMessage = "G A M E   O V E R !";
	
	Gotoxy((CONSOLE_WIDTH >> 1) - 8, CONSOLE_HEIGHT >> 1);
	
	for (i = 0; i < strlen(overMessage); i++)
	{
		printf("%c", overMessage[i]);
		Sleep(50);
	}
	
	exit(0);
}

int Input()
{
	return _kbhit() ? _getch() : -2;
}

unsigned _stdcall TimerThread(void* arg)
{
	while (1)
	{
		if (0 < score)
		{
			timer--;
		}
		
		if (0 < score && score < 100)
		{
			Sleep(1000);
		}
		else if (100 <= score && score < 200)
		{
			Sleep(750);
		}
		else if (200 <= score && score < 300)
		{
			Sleep(500);
		}
		else if (300 <= score && score < 400)
		{
			Sleep(250);
		}
		else
		{
			Sleep(150);
		}
	}
}
