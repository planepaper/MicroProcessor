//-------| src/led.c |-------//
#include <unistd.h> // usleep()

#include "led.h"

static short *led;

void led_clear()
{
	int i;
	for (i = 1; i <= 16; i++)
	{
		*led = (short)~0x00;
	}
	usleep(0);
}

void led_all()
{
	int i;
	for (i = 1; i <= 16; i++)
	{
		*led = (short)~0xFF;
	}
	usleep(0);
}

void init_led(short *address)
{
	led = address;
}
