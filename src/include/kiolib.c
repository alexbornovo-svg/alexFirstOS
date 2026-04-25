#include "kiolib.h"
#include "../drivers/kbd.h"
#include "types.h"

/* --------------------------------------------------------- */
void port_byte_out(unsigned short port, unsigned char data)
{
    __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

/* --------------------------------------------------------- */
void k_clear_screen(void)
{
    char *vidmem = VGA_MEM;
    unsigned int i = 0;
    while (i < (VGA_WIDTH * VGA_HEIGHT * 2))
    {
        vidmem[i++] = ' ';
        vidmem[i++] = 0x07;
    }
    port_byte_out(0x3D4, 14);
    port_byte_out(0x3D5, 0);
    port_byte_out(0x3D4, 15);
    port_byte_out(0x3D5, 0);
}

/* --------------------------------------------------------- */
unsigned int k_printf(const char *message, uint line, char colour)
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

uint k_scanf(const char *message, uint line, char colour, char *buf, uint buf_size)
{
    if (!buf || buf_size == 0) return 0;
    uint msg_len = 0;
    while (message[msg_len]) msg_len++;
    uint idx = 0;
    char tmp[VGA_WIDTH + 1];
    k_printf(message, line, colour);
    while (idx < buf_size - 1)
    {
        while (!(inb(0x64) & 0x01));
        uchar scancode = inb(0x60);
        if (scancode & 0x80) continue;
        char c = kbd_scancode_to_ascii(scancode);
        if (c == 0) continue;
        if (c == '\b')
        {
            if (idx > 0) idx--;
        }
        else if (c == '\n') break;
        else buf[idx++] = c;
        uint i = 0;
        for (uint j = 0; j < msg_len && i < VGA_WIDTH; j++)
            tmp[i++] = message[j];
        for (uint j = 0; j < idx && i < VGA_WIDTH; j++)
            tmp[i++] = buf[j];
        while (i < VGA_WIDTH)
            tmp[i++] = ' ';
        tmp[i] = '\0';
        k_printf(tmp, line, colour);
    }
    buf[idx] = '\0';
    return line + 1;
}

int k_startswith(const char *str, const char *prefix)
{
    int i = 0;
    while (prefix[i])
    {
        if (str[i] != prefix[i]) return 0;
        i++;
    }
    return 1;
}

const char *k_skipword(const char *str)
{
    while (*str && *str != ' ') str++;
    while (*str == ' ') str++;
    return str;
}