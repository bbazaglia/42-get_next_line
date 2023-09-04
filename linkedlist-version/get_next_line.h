#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

// Define the buffer size based on the compilation flag, or use a default value if not specified
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100 // default buffer size
#endif

// Define the structure for a Node
struct Node
{
    char *data; // Pointer to dynamically allocated string
    struct Node *next;
};

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);


#endif