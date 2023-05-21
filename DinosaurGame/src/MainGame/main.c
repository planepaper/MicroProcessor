#include "main.h"

boolean pixels[PIXELS_HEIGHT][PIXELS_WIDTH];

int life = 3;
Coordinate characterPos = { CHAR_WIDTH_PX * 2, 0 };
int flyingFrame = 0;
CharacterJumpingState characterJumpingState = GROUND;
boolean unstoppable = 0;

Coordinate cactusesPos[100];
int cactusesCounts = 0;


int main()
{
    system("mode con cols=180 lines=25");

    char input;
    scanf_s("%c", &input);

    if(input == 's')
        RunGame();

    return 0;
}

void RunGame()
{
    clock_t start, end;
    clock_t cactusTime = 0;
    clock_t unstoppableTime = 0;

    while (1)
    {
        start = clock();

        ClearPixels();

        MakeCharcterJumpIfKeyDown(&characterJumpingState);

        if (cactusTime > 3000)
        {
            SpawnCactus(PIXELS_WIDTH);
            cactusTime = 0;
        }
        MoveCactuses(-1);
        RemoveCactusesGone();


        PutObjectOnPixels(character, characterPos.x, characterPos.y);
        if (CheckCactusCollision(cactus, cactusesPos, cactusesCounts) && !unstoppable)
        {
            life--;
            unstoppable = 1;
            unstoppableTime = 0;
        }
        PutCactusesOnPixels();

        if (unstoppable && unstoppableTime > 1000)
        {
            unstoppable = 0;
        }

        if (life <= 0)
            return;

        PrintBoard();

        Sleep(5);
        end = clock();
        cactusTime += end - start;
        unstoppableTime += end - start;
    }
}

void ClearPixels()
{
    for (int i = 0; i < PIXELS_HEIGHT; i++)
    {
        memset(pixels[i], 0, sizeof(char) * PIXELS_WIDTH);
    }
}

void MakeCharcterJumpIfKeyDown()
{
    switch (characterJumpingState)
    {
    case GROUND:
        if (GetKeyDown() == 'z' && characterJumpingState == GROUND)
        {
            characterJumpingState = ISGETTINGUP;
        }
        break;
    case ISGETTINGUP:
        if (characterPos.y < JUMPING_HEIGHT)
        {
            characterPos.y++;
        }
        else
        {
            characterJumpingState = FLYING;
        }
        break;
    case ISGETTINGDOWN:
        if (characterPos.y > 0)
        {
            characterPos.y--;
        }
        else
        {
            characterJumpingState = GROUND;
        }
        break;
    case FLYING:
        if (flyingFrame < FLYING_COUNT)
        {
            flyingFrame++;
        }
        else
        {
            flyingFrame = 0;
            characterJumpingState = ISGETTINGDOWN;
        }
        break;
    default:
        break;
    }
}

int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

void PutObjectOnPixels(boolean paint[][3], int x, int y)
{
    int paintRow = sizeof(character[0]) / sizeof(boolean);
    int paintColumn = sizeof(character) / sizeof(character[0]);

    for (int j = 0; j < paintColumn; j++)
    {
        for (int i = 0; i < paintRow; i++)
        {
            if (y + j < 0 || x + i < 0 || y + j >= PIXELS_HEIGHT || x + i >= PIXELS_WIDTH)
                continue;

            if (paint[j][i])
            {
                pixels[y + j][x + i] = 1;
            }
            else
            {
                pixels[y + j][x + i] = 0;
            }
        }
    }
}

void SpawnCactus(int xPos)
{
    int newPosX = xPos;
    cactusesPos[cactusesCounts].x = newPosX;
    cactusesPos[cactusesCounts].y = 0;
    cactusesCounts++;
}

void MoveCactuses(int xDiff)
{
    for (int i = 0; i < cactusesCounts; i++)
    {
        cactusesPos[i].x += xDiff;
    }
}

void RemoveCactusesGone()
{
    int cactusWidth = sizeof(cactus) / sizeof(cactus[0]);

    if (cactusesCounts > 0 && cactusesPos[0].x < -cactusWidth)
    {
        cactusesCounts--;

        for (int i = 0; i < cactusesCounts; i++)
        {
            cactusesPos[i].x = cactusesPos[i + 1].x;
        }
    }
}

boolean CheckCactusCollision(boolean obstaclePaint[][3], Coordinate obstaclePos[], int obastacleCounts)
{
    for (int i = 0; i < obastacleCounts; i++)
    {
        boolean flag = CheckObstacleCollision(obstaclePaint, obstaclePos[i].x, obstaclePos[i].y);
        if (flag) return 1;
    }

    return 0;
}

boolean CheckObstacleCollision(boolean paint[][3], int x, int y)
{
    int paintRow = sizeof(paint[0]) / sizeof(boolean);
    int paintColumn = sizeof(paint) / sizeof(paint[0]);

    for (int j = 0; j < paintColumn; j++)
    {
        for (int i = 0; i < paintRow; i++)
        {
            if (y + j < 0 || x + i < 0 || y + j >= PIXELS_HEIGHT || x + i >= PIXELS_WIDTH)
                continue;

            if (paint[j][i] && pixels[y + j][x + i])
            {
                return 1;
            }
        }
    }
    return 0;
}

void PutCactusesOnPixels()
{
    for (int i = 0; i < cactusesCounts; i++)
    {
        PutObjectOnPixels(cactus, cactusesPos[i].x, 0);
    }
}

void PrintBoard()
{
    Gotoxy(0, 0);
    PrintPixels();
    printf("\n");
    printf("Life : %d", life);
}

void PrintPixels()
{
    for (int j = PIXELS_HEIGHT - 1; j >= 0; j--)
    {
        for (int i = 0; i < PIXELS_WIDTH; i++)
        {
            if (pixels[j][i])
            {
                printf("бс");
            }
            else
            {
                printf("бр");
            }
        }
        printf("\n");
    }
}

void Gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}