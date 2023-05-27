//-------| src/main.c |-------//
#include "main.h"

#include <time.h>

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};
static off_t IEB_FND[MAX_FND] = {
	IEB_FND0,
	IEB_FND1,
	IEB_FND2,
	IEB_FND3,
	IEB_FND4,
	IEB_FND5,
	IEB_FND6,
	IEB_FND7
};

static int fd;
static int map_counter = 0;
static void * map_data[100];
static seclection_t sel; 

#define CHAR_WIDTH_PX 5
#define CHAR_HEIGHT_PX 8

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#define PIXELS_WIDTH CHAR_WIDTH_PX*LCD_WIDTH
#define PIXELS_HEIGHT CHAR_HEIGHT_PX*LCD_HEIGHT

#define JUMPING_HEIGHT 8
#define FLYING_COUNT 2

#define UPPERBIT_BASE 0x10000

struct Coordinate
{
    int x;
    int y;
} typedef Coordinate;

const truth_t character[5][3] =
{
    1, 1, 1,
    1, 1, 1,
    1, 1, 1,
    1, 1, 1,
    1, 1, 1
};

const truth_t cactus[5][3] =
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

truth_t pixels[PIXELS_HEIGHT][PIXELS_WIDTH];

int life = 3;
Coordinate characterPos = { CHAR_WIDTH_PX * 2, 0 };
int flyingFrame = 0;
CharacterJumpingState characterJumpingState = GROUND;
truth_t unstoppable = 0;

Coordinate cactusesPos[100];
int cactusesCounts = 0;


int main(int argc, char* argv[]) {
	
	int i;
	short * led, * dot[MAX_DOT], * fnd[MAX_FND];
	short * clcd_cmd, * clcd_data, * keypad_out, * keypad_in;
	
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd == -1) {
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}
	
	led = mapper(IEB_LED, PROT_WRITE);
	for( i=0; i<MAX_DOT; i++ ) {
		dot[i] = mapper(IEB_DOT[i], PROT_WRITE);
	}
	for( i=0; i<MAX_FND; i++ ) {
		fnd[i] = mapper(IEB_FND[i], PROT_WRITE);
	}
	clcd_cmd  = mapper(IEB_CLCD_CMD, PROT_WRITE);
	clcd_data = mapper(IEB_CLCD_DATA, PROT_WRITE);
	keypad_out  = mapper(IEB_KEY_W, PROT_WRITE);
	keypad_in = mapper(IEB_KEY_R, PROT_READ);
	
	init_led(led);
	init_dot(dot);
	init_fnd(fnd);
	init_clcd(clcd_cmd, clcd_data);
	init_keypad(keypad_out, keypad_in);
	
	while( logic() == TRUE ) {	}
	
	unmapper();
	close(fd);
	return 0;
}

short * mapper(off_t offset, int prot) {
	map_data[map_counter] = mmap(NULL, sizeof(short), prot, MAP_SHARED, fd, offset);
	if ( map_data[map_counter] == MAP_FAILED ) {
		fprintf(stderr, "Cannot do mmap()");
		emergency_closer();
	}
	return (short *)map_data[map_counter++];
}

void unmapper() {
	int i;
	for( i=0; i<map_counter; i++) {
		munmap(map_data[i], sizeof(short));
	}
	map_counter = 0;
}

void emergency_closer() {
	unmapper();
	close(fd);
	exit(EXIT_FAILURE);
}

truth_t logic() {
    char input;
    scanf_s("%c", &input);

    if(input == 's')
        RunGame();

    return FALSE;
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

        MakeCharcterJumpIfKeyDown();

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

        usleep(5000);
        end = clock();
        cactusTime += end - start;
        unstoppableTime += end - start;
    }
}

void ClearPixels()
{
    int i;
    for (i = 0; i < PIXELS_HEIGHT; i++)
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

void PutObjectOnPixels(truth_t paint[][3], int x, int y)
{
    int paintRow = sizeof(character[0]) / sizeof(truth_t);
    int paintColumn = sizeof(character) / sizeof(character[0]);

    int j, i;

    for (j = 0; j < paintColumn; j++)
    {
        for (i = 0; i < paintRow; i++)
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
    int i;
    for (i = 0; i < cactusesCounts; i++)
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

        int i;
        for (i = 0; i < cactusesCounts; i++)
        {
            cactusesPos[i].x = cactusesPos[i + 1].x;
        }
    }
}

truth_t CheckCactusCollision(truth_t obstaclePaint[][3], Coordinate obstaclePos[], int obastacleCounts)
{
    int i;
    for (i = 0; i < obastacleCounts; i++)
    {
        truth_t flag = CheckObstacleCollision(obstaclePaint, obstaclePos[i].x, obstaclePos[i].y);
        if (flag) return 1;
    }

    return 0;
}

truth_t CheckObstacleCollision(truth_t paint[][3], int x, int y)
{
    int paintRow = sizeof(paint[0]) / sizeof(truth_t);
    int paintColumn = sizeof(paint) / sizeof(paint[0]);

    int j, i;
    for (j = 0; j < paintColumn; j++)
    {
        for (i = 0; i < paintRow; i++)
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
    int i;
    for (i = 0; i < cactusesCounts; i++)
    {
        PutObjectOnPixels(cactus, cactusesPos[i].x, 0);
    }
}

void PrintBoard()
{
    int i, j, x, y;

    for (j = PIXELS_HEIGHT - 1; j >= 0 ; j-= CHAR_HEIGHT_PX)
    {
        int address = i * UPPERBIT_BASE;
        for(i = 0; i < PIXELS_WIDTH; i+= CHAR_WIDTH_PX)
        {
            clcd_set_CGRAM(address)
            for(y = 0; y < CHAR_HEIGHT_PX; y++)
            {
                int rowbinary = 0;
                for(x = 0; x < CHAR_WIDTH_PX; x++)
                {
                    rowbinary << 1;
                    rowbinary += pixels[j - y][i + x];
                }
                clcd_write_data(rowbinary);
            }
            address++;
        }
    }

    for (i = 0; i < LCD_HEIGHT; i++)
    {
        int address = i * UPPERBIT_BASE;
        for(j = 0; j < LCD_WIDTH; j++)
        {
            clcd_write_string(address);
            address++;
        }
    }
}