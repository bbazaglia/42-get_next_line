#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

typedef struct s_list
{
    char *content;
    struct s_list *next;
} t_list;

int main()
{
    int fd;
    char *line;

    fd = open("the_little_prince.txt", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
        printf("%s", line);
        free(line);
    }
}

char *get_next_line(int fd)
{
    static t_list *stash = NULL;
    char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    bytes_read = 1;
    line = NULL;
    read_and_stash(&stash, &bytes_read);
    return (line);
}

void    read_and_stash(int fd, t_list  **stash, int *read_ptr)
{
    char *buff;
    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (buff == NULL)
        return (NULL);
    while
    *read_ptr = read(fd, buff, BUFFER_SIZE);
    buff[*read_ptr] = '\0';
}