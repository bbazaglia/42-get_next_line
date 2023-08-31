#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->buff_str = content;
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

void ft_lstclear(t_list **lst)
{
    if (!lst || !*lst)
        return;

    t_list *current = *lst;
    t_list *temp;

    while (current)
    {
        temp = current->next;
        free(current->buff_str);
        current->buff_str = NULL;
        current->next = NULL;
        free(current);
        current = temp;
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
