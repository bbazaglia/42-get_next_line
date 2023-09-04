#include "get_next_line.h"

int	ft_read_fd(int fd, t_list **head, int *bytes_read)
{
	char	*buffer;

	// WATCH OUT!!!!!!!
	if (*head == NULL)
	{
		*head = ft_lstnew(NULL);
		// head = malloc(sizeof(t_list));
		// head->content = ft_calloc(1, sizeof(char));
		// head->next = NULL;
	}

	t_list	*current = *head;

	*bytes_read = 1;
	while (!ft_strchr(current->content, '\n') && *bytes_read != 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		*bytes_read = read(fd, current->content, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			ft_lstclear(head, free);
			// free(buffer->content);
			// free(buffer);
			// free(head->content);
			// free(head);
			free(buffer);
			return (-1);
		}
		buffer[*bytes_read] = '\0';

		ft_lstadd_back(head, ft_lstnew(buffer));

		current = current->next;
	}
	return (0);
}

// WATCH OUT!!!!!!!!!!!!!!
char	*ft_filter_line(t_list *head, t_list *rest)
{
	char	*filtered_line;
	t_list	*current = head;

	int i = 0;

	if (!head || !head->content[i])
		return (NULL);

	int line_len = 0;

	
	while (current->content[i] != '\n')
	{
		if (current->content[i] == '\0')
		{
			current = current->next;
			i = 0;
		}
		else 
		{
			i++;
			line_len++;
		}
		if (current->content[i] == '\n')
		{
			line_len++;
		}
	}
	
	filtered_line = malloc(line_len + 1);
	
	rest = ft_lstnew(ft_strdup(current->content[line_len]));
	
	while (current && current->content[i] && current->content[i] != '\n')
	{
		filtered_line[i] = current->content[i];
		i++;
		if (current->content[i] == '\0')
		{
			current = current->next;
			i = 0;
		}
	}
	if (current != NULL && current->content[i] == '\n')
	{
		filtered_line[i] = current->content[i];
		i++;
	}
	ft_lstclear(&head, free);
	return (filtered_line);
}


t_list	*ft_rest_unfiltered(t_list *head)
{
	int		i;
	t_list	*current;
	t_list	*rest_line;

	i = 0;
	current = head;
	while (current != NULL && current->content[i] && current->content[i] != '\n')
		i++;
	if (current == NULL || !current->content[i])
	{
		free(head);
		return (NULL);
	}
	rest_line = malloc(sizeof(t_list));
	rest_line->content = ft_calloc(ft_strlen(current->content) - i + 1, sizeof(char));
	if (!rest_line->content)
		return (NULL);
	i++;
	while (current != NULL)
	{
		int j = 0;
		while (current->content[i] != '\0')
			rest_line->content[j++] = current->content[i++];
		current = current->next;
		i = 0;
	}
	free(head);
	return (rest_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static t_list	*head;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || ft_read_fd(fd, head, &bytes_read) < 0)
		return (NULL);

	next_line = ft_filter_line(head);
	head = ft_rest_unfiltered(head);
	if (next_line == NULL && bytes_read == 0)
	{
		free(head);
		return (NULL);
	}
	return (next_line);
}