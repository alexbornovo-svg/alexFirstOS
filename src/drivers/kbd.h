#ifndef KBD_H
#define KBD_H

#include "types.h"

uchar inb(unsigned short port);
char  kbd_scancode_to_ascii(uchar scancode);
char  kbd_poll(void);
char  kbd_char_input(void);
void  kbd_update(void);

#endif