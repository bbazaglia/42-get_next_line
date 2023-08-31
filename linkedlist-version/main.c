#include "get_next_line.h"

int main()
{
    int fd = open("test.txt", O_RDONLY);
    while (1)
    {
        char *next_line = get_next_line(fd);
        if (next_line == NULL)
            break;
        printf("%s", next_line);
        free(next_line);
    }
}