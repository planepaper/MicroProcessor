#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define CHAR_WIDTH_PX 5
#define CHAR_HEIGHT_PX 10

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#define PIXELS_WIDTH CHAR_WIDTH_PX*LCD_WIDTH
#define PIXELS_HEIGHT CHAR_HEIGHT_PX*LCD_HEIGHT

#define JUMPING_HEIGHT 8
#define FLYING_COUNT 2

struct Coordinate
{
    int x;
    int y;
} typedef Coordinate;

const boolean character[5][3] =
{
    1, 1, 1,
    1, 1, 1,
    1, 1, 1,
    1, 1, 1,
    1, 1, 1
};

const boolean cactus[5][3] =
{
    1, 1, 1,
    1, 1, 1,
    1, 1, 1,
    1, 1, 1,
    1, 1, 1
};

enum CharacterJumpingState
{
    GROUND = 0,
    ISGETTINGUP,
    FLYING,
    ISGETTINGDOWN
} typedef CharacterJumpingState;


void RunGame();
void ClearPixels();
void MakeCharcterJumpIfKeyDown();
int GetKeyDown();
void PutObjectOnPixels(boolean paint[][3], int x, int y);
void SpawnCactus(int xPos);
void MoveCactuses(int xDiff);
void RemoveCactusesGone();
boolean CheckCactusCollision(boolean obstaclePaint[][3], Coordinate obstaclePos[], int obastacleCounts);
boolean CheckObstacleCollision(boolean paint[][3], int x, int y);
void PutCactusesOnPixels();
void PrintBoard();
void PrintPixels();
void Gotoxy(int x, int y);
