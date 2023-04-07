//-------| lib/main.h |-------//
#ifndef MAIN_H
#define MAIN_H

#include <unistd.h> // close(), off_t , usleep()

typedef enum
{
	FALSE = 0,
	TRUE = 1
} truth_t;

typedef enum
{
	ERROR = -1,
	SUCCESS = 0
} error_t;

int main();
short *mapper(off_t offset);
void unmapper();
void emergency_closer();
error_t logic(int argc, char *argv[]);
void error();

#endif
