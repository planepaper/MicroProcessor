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



typedef enum {
	FALSE = 0,
	TRUE  = 1
} truth_t;



int main();
short * mapper(off_t offset);
void unmapper();
void emergency_closer();
void error();
truth_t inputter();


#endif
