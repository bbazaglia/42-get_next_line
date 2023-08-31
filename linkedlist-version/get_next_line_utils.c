#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void ft_lstadd_back(t_list **lst, t_list *new_elem)
{
    if (!lst || !new_elem)
        return;
    if (!*lst)
    {
        *lst = new_elem;
        return;
    }
    t_list *last = *lst;
    while (last->next)
        last = last->next;
    last->next = new_elem;
}

// void ft_lstclear(t_list **lst)
// {
//     if (!lst || !*lst)
//         return;

//     t_list *current = *lst;
//     t_list *temp;

//     while (current)
//     {
//         temp = current->next;
//         free(current->content);
//         current->content = NULL;
//         current->next = NULL;
//         free(current);
//         current = temp;
//     }
//     *lst = NULL;
// }

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new;
	unsigned int	newlen;
	unsigned int	s1len;
	unsigned int	s2len;
	int				i;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newlen = s1len + s2len;
	new = (char *)malloc(sizeof(char) * (newlen + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	i = -1;
	while (s2[++i])
		new[i + s1len] = s2[i];
	new[newlen] = '\0';
	return (new);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	if (*ptr == (unsigned char)c)
		return (ptr);
	return (NULL);
}
