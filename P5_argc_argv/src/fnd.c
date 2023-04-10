#include <unistd.h> // usleep()

#include "fnd.h"

static unsigned short fnd_hexadecimal[16] =
    {
        0x3F, // 0
        0x06, // 1
        0x5B, // 2
        0x4f, // 3
        0x66, // 4
        0x6d, // 5
        0x7d, // 6
        0x07, // 7
        0x7f, // 8
        0x67, // 9
        0x77, // A
        0x7c, // B
        0x39, // C
        0x5e, // D
        0x79, // E
        0x71, // F
};

static short *fnd[MAX_FND];

void init_fnd(short *address[])
{
    int i;
    for (i = 0; i < MAX_FND; i++)
    {
        fnd[i] = address[i];
    }
}

void fnd_clear()
{
    int i;
    for (i = 0; i < MAX_FND; i++)
    {
        *fnd[i] = 0;
    }
    usleep(0); // for Ximulator
}

void fnd_all()
{
    int i;
    for (i = 0; i < MAX_FND; i++)
    {
        *fnd[i] = fnd_hexadecimal[8];
    }
    usleep(0); // for Ximulator
}

void fnd_write(int hexadeciaml, int fnd_num)
{
    *fnd[fnd_num] = fnd_hexadecimal[hexadeciaml];
}

void fnd_hexa_number(unsigned long number)
{
    int i;
    for (i = 0; i < MAX_FND; i++)
    {
        fnd_write(((short)(number & 0xF)), i);
        number = number >> 4;
    }
    usleep(0); // for Ximulator
}
