#include "kiolib.h"

/* --------------------------------------------------------- */
void k_clear_screen(void)
{
    char *vidmem = VGA_MEM;
    unsigned int i = 0;

    while (i < (VGA_WIDTH * VGA_HEIGHT * 2))
    {
        vidmem[i++] = ' ';
        vidmem[i++] = WHITE_TXT;
    }
}

/* --------------------------------------------------------- */
unsigned int k_printf(const char *message, unsigned int line, char colour)
{
    char *vidmem = VGA_MEM;
    unsigned int i = line * VGA_WIDTH * 2;

    while (*message != '\0')
    {
        if (*message == '\n')
        {
            line++;
            i = line * VGA_WIDTH * 2;
        }
        else
        {
            vidmem[i++] = *message;
            vidmem[i++] = colour;
        }
        message++;
    }

    return line + 1;
}