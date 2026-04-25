#include "kiolib.h"
#include "types.h"

int infos(uint line)
{
    uint l = line;
    l = k_printf("+---------------+", l, WHITE_TXT);
    l = k_printf("| ALEX FIRST OS |", l, WHITE_TXT);
    l = k_printf("+---------------+\n", l, WHITE_TXT);
    l = k_printf("Developed in C and NASM by Alex Xela (Alexbornovo-svg)\n", l, GREY_TXT);
    l = k_printf(" ", l, WHITE_TXT);
    l = k_printf("1. This is a blue line.", l, BLUE_TXT);
    l = k_printf("2. This is a red (error) line.", l, RED_TXT);
    return l;
}

void get_cpu_brand(char *buf)
{
    unsigned int eax, ebx, ecx, edx;
    int i, j = 0;

    unsigned int regs[3][4];
    for (i = 0; i < 3; i++)
    {
        eax = 0x80000002 + i;
        __asm__ volatile (
            "cpuid"
            : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
            : "a"(eax)
        );
        regs[i][0] = eax;
        regs[i][1] = ebx;
        regs[i][2] = ecx;
        regs[i][3] = edx;
    }

    for (i = 0; i < 3; i++)
    {
        int k;
        for (k = 0; k < 4; k++)
        {
            unsigned int r = regs[i][k];
            buf[j++] = (r      ) & 0xFF;
            buf[j++] = (r >>  8) & 0xFF;
            buf[j++] = (r >> 16) & 0xFF;
            buf[j++] = (r >> 24) & 0xFF;
        }
    }
    buf[j] = '\0';
}

void k_shell(uint line)
{
    uint line_count = line;
    char input[256];
    while (1)
    {
        line_count = k_scanf("> ", line_count, WHITE_TXT, input, 256);
        if (k_startswith(input, "echo"))
        {
            const char *arg = k_skipword(input);
            line_count = k_printf(arg, line_count, WHITE_TXT);
        }
        else if (k_startswith(input, "clear"))
        {
            k_clear_screen();
            line_count = 0;
        }
        else if (k_startswith(input, "info"))
        {
            line_count = infos(line_count);
        }
        else if (k_startswith(input, "help"))
        {
            line_count = k_printf("comandi: echo, clear, info, alexfetch, help", line_count, WHITE_TXT);
        }
        else if (k_startswith(input, "alexfetch"))
        {
            char cpu[49];
            get_cpu_brand(cpu);
            
            line_count = k_printf("OS: AlexOS 1.0 ('info' for more)", line_count, WHITE_TXT);
            line_count = k_printf("CPU: ", line_count, WHITE_TXT);
            line_count = k_printf(cpu, line_count, YELLOW_TXT);
        }
        else
        {
            line_count = k_printf("ERROR: cmd not found", line_count, RED_TXT);
        }

        if (line_count > 25)
        {
            k_clear_screen();
            line_count = 0;
        }
    }
}

void initialize_shell()
{
}