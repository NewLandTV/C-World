#include <stdio.h>
#include <Windows.h>

#define CONSOLE_WIDTH 190
#define CONSOLE_HEIGHT 46
#define MAP_WIDTH 256
#define MAP_HEIGHT 256

typedef struct _Player
{
	int x;
	int y;
} Player;

char* map;

Player player;

void Init();
void Update();
void PlayerControl();
void DrawPlayer();
void DrawMap();
void DrawUI();
void FillMap(char c);
void Gotoxy(int x, int y);

int main(void)
{
	Init();
	
	while (1)
	{
		Update();
	}
	
	return 0;
}

void Init()
{
	system("title Test World");
	system("mode con cols=190 lines=46");
	
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	
	map = (char*)malloc(MAP_WIDTH * MAP_HEIGHT);
	
	FillMap('.');
	
	player.x = CONSOLE_WIDTH >> 1;
	player.y = CONSOLE_HEIGHT >> 1;
	
	DrawMap();
	
	Gotoxy(player.x, player.y);
	printf("@");
}

void Update()
{	
	if (GetAsyncKeyState('Q') & 0x8001)
	{
		free(map);
		exit(1);
	}
	
	PlayerControl();
	DrawUI();
	
	Sleep(8);
}

void PlayerControl()
{
	if (GetAsyncKeyState('W') & 0x8001 && player.y - 1 >= 0)
	{
		DrawPlayer(0, -1);
	}
	if (GetAsyncKeyState('A') & 0x8001 && player.x - 1 >= 0)
	{
		DrawPlayer(-1, 0);
	}
	if (GetAsyncKeyState('S') & 0x8001 && player.y + 1 < MAP_HEIGHT)
	{
		DrawPlayer(0, 1);
	}
	if (GetAsyncKeyState('D') & 0x8001 && player.x + 1 < MAP_WIDTH)
	{
		DrawPlayer(1, 0);
	}
}

void DrawPlayer(int directionX, int directionY)
{
	Gotoxy(player.x, player.y);
	printf(" ");
	
	player.x += directionX;
	player.y += directionY;
	
	DrawMap();
}

void DrawMap()
{
	int x;
	int y;
	
	for (y = player.y - (CONSOLE_HEIGHT >> 1); y < player.y - (CONSOLE_HEIGHT >> 1) + CONSOLE_HEIGHT; y++)
	{
		for (x = player.x - (CONSOLE_WIDTH >> 1); x < player.x - (CONSOLE_WIDTH >> 1) + CONSOLE_WIDTH; x++)
		{
			if (y < 0 || x < 0)
			{
				Gotoxy(player.x, player.y);
				printf("@");
				
				return 1;
			}
			else if (player.y > MAP_HEIGHT - (CONSOLE_HEIGHT >> 1) || player.x > MAP_WIDTH - (CONSOLE_WIDTH >> 1))
			{
				Gotoxy(player.x - MAP_WIDTH, player.y - MAP_HEIGHT);
				printf("@");
				
				return 1;
			}
			
			Gotoxy(x, y);
			printf("%c", map[x + MAP_WIDTH * y]);
			Gotoxy(CONSOLE_WIDTH >> 1, CONSOLE_HEIGHT >> 1);
			printf("@");
		}
	}
	
	return 0;
}

void DrawUI()
{
	Gotoxy(0, 0);
	printf("Position [%03d, %03d]", player.x, player.y);
}

void FillMap(char c)
{
	int i;
	
	for (i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		map[i] = c;
	}
}

void Gotoxy(int x, int y)
{
	COORD position = { x, y };
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
