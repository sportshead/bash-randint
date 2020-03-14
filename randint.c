#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define BUFSIZE 128

#ifdef DEBUG
#define DEBUG_MSG(...) { printf("**DEBUG** "); printf(__VA_ARGS__);}
#else
#define DEBUG_MSG(...) do {} while(0)
#endif

int main(int argc, char const *argv[])
{
    char *out = ( char* ) malloc(10 * sizeof(char));

    char *cmd = "xxd -l 8 -p /dev/urandom";

    char buf[BUFSIZE];
    FILE *fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    while (fgets(buf, BUFSIZE, fp) != NULL) {
        strcat(out, buf);
    }

    if (pclose(fp))  {
        printf("Command not found or exited with error status\n");
        return -1;
    }

    /*int debug;

    char *argv3;

    if (argc > 3) {
        strcpy(argv3, argv[3]);
        int i;

        for (i = 0; argv3[i] != '\0'; i++)
        {
            if (argv3[i] >= 'A' && argv3[i] <= 'Z')
            {
                argv3[i] = argv3[i] + 32;
            }
        }

        debug = strcmp(argv3, "-d") || strcmp(argv3, "--debug") || strcmp(argv3, "-debug");
    } else
    {
        debug = 0;
    }*/

    unsigned long long num = strtoull(out, NULL, 16);
    DEBUG_MSG("out var: %s", out);
    DEBUG_MSG("num var: %llu\n", num);

    unsigned long long max;
    unsigned long long min;

    DEBUG_MSG("argc var: %d\n", argc);

    switch (argc) {
    case 1:
        printf("%llu\n", num);
        return 0;

    case 2:
        printf("%llu\n", num % strtoull(argv[1], NULL, 10));
        return 0;

    default:
        /*
            min argv[2], max argv[1]

            DOES NOT WORK: (num - min) % max
            DOES NOT WORK: ((num - min) % max)+min
            WORKS: (num % (max - min)) + min

            min 15, max 25, num 150

        */
        max = strtoull(argv[1], NULL, 10);
        min = strtoull(argv[2], NULL, 10);
        printf("%llu\n", (num % (max - min)) + min);
        return 0;
    }

    return 1;
}