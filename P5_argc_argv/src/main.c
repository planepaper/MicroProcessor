//-------| src/main.c |-------//
#include <stdio.h>	  // printf(), scanf(), fprintf()
#include <fcntl.h>	  // open()
#include <sys/mman.h> // mmap(), munmap()
#include <stdlib.h>	  // exit()
#include <string.h>

#include "ieb.h"
#include "led.h"
#include "dot.h"
#include "fnd.h"
#include "main.h"

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5};

static off_t IEB_FND[MAX_FND] = {
	IEB_FND0,
	IEB_FND1,
	IEB_FND2,
	IEB_FND3,
	IEB_FND4,
	IEB_FND5,
	IEB_FND6,
	IEB_FND7,
};

static int fd;
static int map_counter = 0;
static void *map_data[100];

int main(int argc, char *argv[])
{
	int i;
	short *led, *dot[MAX_DOT], *fnd[MAX_FND];

	fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd == -1)
	{
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}

	led = mapper(IEB_LED);
	for (i = 0; i < MAX_DOT; i++)
	{
		dot[i] = mapper(IEB_DOT[i]);
	}
	for (i = 0; i < MAX_FND; i++)
	{
		fnd[i] = mapper(IEB_FND[i]);
	}
	init_led(led);
	init_dot(dot);
	init_fnd(fnd);

	if (logic(argc, argv) == ERROR)
	{
		error();
	}
	usleep(1000000);

	unmapper();
	close(fd);
	return 0;
}

short *mapper(off_t offset)
{
	map_data[map_counter] = mmap(NULL, sizeof(short), PROT_WRITE, MAP_SHARED, fd, offset);
	if (map_data[map_counter] == MAP_FAILED)
	{
		fprintf(stderr, "Cannot do mmap()");
		emergency_closer();
	}
	return (short *)map_data[map_counter++];
}

void unmapper()
{
	int i;
	for (i = 0; i < map_counter; i++)
	{
		munmap(map_data[i], sizeof(short));
	}
	map_counter = 0;
}

void emergency_closer()
{
	unmapper();
	close(fd);
	exit(EXIT_FAILURE);
}

error_t logic(int argc, char *argv[])
{
	dot_write(argc);
	led_clear();
	if (argc == 1)
	{
		led_all();
		fnd_all();
	}
	else if (argc == 2)
	{
		int i, number = 0;

		for (i = 0; i < strlen(argv[1]); i++)
		{
			if (i >= 8)
			{
				return ERROR;
			}
			if ((argv[1][i] < '0') || (argv[1][i] > '9'))
			{
				return ERROR;
			}
		}
		fnd_hexa_number(number);
	}
	else if (argc == 3)
	{
		int i, base, number = 0;

		if ((argv[1][0] == 'b') || (argv[1][0] == 'B'))
		{
			base = 2;
		}
		else if ((argv[1][0] == 'o') || (argv[1][0] == 'O'))
		{
			base = 8;
		}
		else if ((argv[1][0] == 'd') || (argv[1][0] == 'D'))
		{
			base = 16;
		}
		else
		{
			return ERROR;
		}

		for (i = 0; i < strlen(argv[2]); i++)
		{
			if (i >= 8)
			{
				return ERROR;
			}
			if ((argv[2][i] < '0') || (argv[2][i] >= '0' + base))
			{
				return ERROR;
			}

			number *= base;
			number += argv[2][i] - '0';
		}
		fnd_hexa_number(number);
	}
	else
	{
		return ERROR;
	}

	return SUCCESS;
}

void error()
{
	dot_error();
	led_clear();
	fnd_clear();
}
