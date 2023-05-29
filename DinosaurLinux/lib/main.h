//-------| lib/main.h |-------//
#ifndef	MAIN_H
#define	MAIN_H 


#include <stdio.h>		// printf(), scanf(), fprintf()
#include <fcntl.h>		// open()
#include <unistd.h>		// close(), off_t , usleep()
#include <sys/mman.h>	// mmap(), munmap()
#include <stdlib.h> 	// exit()
#include <string.h>		// strlen()

#include "ieb.h"
#include "led.h"
#include "dot.h"
#include "fnd.h"
#include "clcd.h"
#include "keypad.h"

typedef enum {
	FALSE = 0,
	TRUE  = 1
} truth_t;

typedef enum {
	ERROR	= -1,
	SUCCESS	= 0
} error_t;

typedef union {
	unsigned char all;
	struct {
		unsigned char  led : 1;
		unsigned char  dot : 1;
		unsigned char  fnd : 1;
		unsigned char clcd : 1;
		unsigned char exit : 1;
	};
} seclection_t;

struct Coordinate
{
    int x;
    int y;
} typedef Coordinate;

int main();
short * mapper(off_t offset, int prot);
void unmapper();
void emergency_closer();

truth_t logic();
void select_mode();
void input_mode();

void RunGame();
void ClearPixels();
void MakeCharcterJumpIfKeyDown();
void PutObjectOnPixels(truth_t paint[][3], int x, int y);
void SpawnCactus(int xPos);
void MoveCactuses(int xDiff);
void RemoveCactusesGone();
truth_t CheckCactusCollision(truth_t obstaclePaint[][3], Coordinate obstaclePos[], int obastacleCounts);
truth_t CheckObstacleCollision(truth_t paint[][3], int x, int y);
void PutCactusesOnPixels();
void PrintBoard();
void PrintPixels();
void Gotoxy(int x, int y);


#endif
