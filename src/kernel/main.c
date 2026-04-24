#include <kiolib.h>

/* simple kernel written in C */
void k_main() 
{
	k_clear_screen();
	k_printf("Hello, world! Welcome to my kernel.\n", 0, WHITE_TXT);
	k_printf("1. This is a blue line.\n", 1, BLUE_TXT);
	k_printf("2. This is a red (error) line.\n", 2, RED_TXT);

};

/*
Black: BLACK_TXT;
Blue: BLUE_TXT;
Green: GREEN_TXT;
Cyan: CYAN_TXT;
Red: RED_TXT;
Magenta: MAGENTA_TXT;
Brown: BROWN_TXT;
White: WHITE_TXT;
Grey: GREY_TXT;
Light Blue: LIGHT_BLUE_TXT;
Light Green: LIGHT_GREEN_TXT;
Light Cyan: LIGHT_CYAN_TXT;
Light Red: LIGHT_RED_TXT;
Pink: PINK_TXT;
Yellow: YELLOW_TXT;
Bright White: BRIGHT_WHITE_TXT;
*/