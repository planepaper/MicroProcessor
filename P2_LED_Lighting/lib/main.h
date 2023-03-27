//-------| lib/main.h |-------//
#ifndef	MAIN_H
#define	MAIN_H 


#include <stdio.h>		// printf(), scanf(), fprintf()
#include <fcntl.h>		// open()
#include <unistd.h>		// close(), off_t
#include <sys/mman.h>	// mmap(), munmap()
#include <stdlib.h> 	// exit()


#include "ieb.h"
#include "led.h"



int main();
int menu() ;


#endif
