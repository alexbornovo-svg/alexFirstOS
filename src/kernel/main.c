#include <kiolib.h>
#include "../misc/shell.h"



/* simple kernel written in C */
void k_main() 
{
	k_clear_screen();
	k_shell(0);

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