#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list
{
    char            *content;
    struct s_list   *next;
}                   t_list;

t_list *ft_lstnew(char *content);
void ft_lstadd_back(t_list **lst, t_list *new_elem);
void ft_lstdelone(t_list *elem);
void	ft_lstclear(t_list **lst, void (*del)(void *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
int read_buffer(int fd, t_list *buffer);
char *get_next_line(int fd);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

#endif