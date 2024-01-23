/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:24:42 by bbazagli          #+#    #+#             */
/*   Updated: 2023/08/28 15:23:02 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_read_fd(int fd, char *unfiltered_line, int *bytes_read)
{
    char *buffer;
    char *temp;
    
    // we're reading for the fist time or the previous call didn't left behind any fragment after the newline
    if (!unfiltered_line)
        unfiltered_line = ft_calloc(1, sizeof(char));

    // allocate memory for the buffer and initialize it to zero
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    
    // itialize the 'bytes read' to 1 so it executes the loop at least once
    *bytes_read = 1;

    // keep reading as long as we don't meet with a newline character and there are still bytes to read
    while (!ft_strchr(unfiltered_line, '\n') && *bytes_read != 0)
    {
        *bytes_read = read(fd, buffer, BUFFER_SIZE);
        // if the read operation fails, return NULL
        if (*bytes_read == -1)
        {
            free(buffer);
            free(unfiltered_line);
            return (NULL);
        }
        // null terminate the buffer so we can work with this data as a string (every string is null terminated)
        buffer[*bytes_read] = '\0';
        temp = unfiltered_line;
        unfiltered_line = ft_strjoin(temp, buffer);
        free(temp);
    }
    free(buffer);
    return (unfiltered_line);
}

char    *ft_filter_line(char *unfiltered_line)
{
    int i;
    char  *filtered_line;

    i = 0;
	if (!unfiltered_line[i])
		return (NULL);
	while (unfiltered_line[i] && unfiltered_line[i] != '\n')
		i++;
	filtered_line = ft_calloc(i + 2, sizeof(char));
	if (!filtered_line)
		return (NULL);
	i = 0;
	while (unfiltered_line[i] && unfiltered_line[i] != '\n')
	{
		filtered_line[i] = unfiltered_line[i];
		i++;
	}
	if (unfiltered_line[i] == '\n')
	{
		filtered_line[i] = unfiltered_line[i];
		i++;
	}
	return (filtered_line);
} 

char	*ft_rest_unfiltered(char *unfiltered_line)
{
	int		i;
	int		j;
	char	*rest_line;

	i = 0;
	while (unfiltered_line[i] && unfiltered_line[i] != '\n')
		i++;
	if (!unfiltered_line[i])
	{
		free(unfiltered_line);
		return (NULL);
	}
	rest_line = ft_calloc(ft_strlen(unfiltered_line) - i + 1, sizeof(char));
	if (!rest_line)
		return (NULL);
	i++;
	j = 0;
	while (unfiltered_line[i])
		rest_line[j++] = unfiltered_line[i++];
	free(unfiltered_line);
	return (rest_line);
}


char	*get_next_line(int fd)
{
    char        *next_line;
    static char *unfiltered_line;
    int bytes_read;
    
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);       
	unfiltered_line = ft_read_fd(fd, unfiltered_line, &bytes_read);
	if (!unfiltered_line)
		return (NULL);
	next_line = ft_filter_line(unfiltered_line);
	unfiltered_line = ft_rest_unfiltered(unfiltered_line);
    if (next_line == NULL && bytes_read == 0)
    {
        free (unfiltered_line);
        return (NULL);
    }
	return (next_line);
}

