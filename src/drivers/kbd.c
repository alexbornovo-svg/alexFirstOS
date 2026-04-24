#include "kbd.h"
#include "types.h"

uchar inb(unsigned short port)
{
    uchar result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void keyboard_handler()
{
    uchar scancode = inb(0x60);

    if (scancode == 0x1E)
    {
        // A
    }
}

char keymap_ita[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', '-', '\b', 
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '-', '+', '\n',    
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '-', '-', '-',             
    0, '<', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, 
    '*', 0, ' ' /* Spacebar */
};

void kbd()
{
    uchar scancode = inb(0x60);

    if (scancode & 0x80) 
    {
        return;
    }

    char ascii = keymap_ita[scancode];

    if (ascii != 0) 
    {
         
    }
}