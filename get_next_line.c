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

/* The purpose of this code is to read each line from a file descriptor and return it.

-> What is a line?
* A line is a succession of characters that end with ’\n’ or with End Of File (EOF).

> What is a file descriptor?
* A file descriptor is a non-negative integer that uniquely identifies an open file in a computer's operating system.

-> Static vs. Non-Static Variables?
* The memory for static variables is allocated once when the program starts and is retained until the program terminates.
* The memory for non-static variables is allocated every time the function is called and is released when the function ends.

-> The usage of a static buff in this project:
* The static buff will be allocated once and persist until the program ends.
* As the function reads lines from the file descriptor and stores them in the buff, it can continue reading from where it left off in the previous iteration.

-> Why the buff size impacts the performance of the program?
* The buff size is the number of bytes that the read function will read from the file descriptor at each iteration.
- A very small buff size (e.g., 1) means the function reads only one byte at a time from the file descriptor.
    This could lead to many I/O operations, making the process less efficient due to the overhead associated with each read operation.
    Additionally, processing data byte by byte can introduce complexity when dealing with multi-byte character encodings.
- A very large buff size can be efficient in terms of reading large amounts of data in one go.
    However, it might lead to excessive memory usage, particularly if lines are shorter than the buff size. Unused memory in the buff might go to waste.
- A relatively large buff size allows the function to read a substantial amount of data at once from the file descriptor.
    This can be efficient because reading larger chunks of data minimizes the number of I/O operations, reducing overhead.
    At the same time, the buff is not so large that it wastes memory when lines are shorter than the buff size.
    
-> What buff size should we use?
* The choice of buff_SIZE depends on a trade-off between efficiency and memory usage. 
* A reasonable buff size is typically in the range of a few kilobytes (e.g., 1024 or 4096 bytes).

-> Return values of get_next_line():
* correct behavior: the line that was read (including the terminating ’\n’ character, if present);
* there is nothing to read or an error occurred: NULL. */

#include "get_next_line.h"

/* Let's say that what is written in our file is: C a r o l e \n  B i a
                                                  1 2 3 4 5 6  7  8 9 10
                                                  
Suppose our buffer size is 8. 

When read is called for the first time, these are the bytes we get: "Carole\nB"

However, the line breaks with the occurrence of the newline. 

So, what do we truly want to print? "Carole\n"

What about the "B"? We shall save it somewhere, because when read is called again, the bytes read will be "ia" and "B" will be lost.

Okay, now let's move to the tricky part: the name of the function is "get NEXT line". 
In the first call of the read function, line would be NULL, meanwile the "next line" would be "Carole\n".

But what if I want to get what's next (aka the second next line)?
We take the fragment of the line that was read in the call before plus the bytes we've just read in the current call of read : "Bia".

So, after all, what the heck is this "line" variable? 
If you're trying to get your first next line, it will be initialized as NULL and then updated to the bytes read.
If you're trying to get any other next line, it will be initialized as the remainder of the last read call made and then updated to the sum of it with the bytes read. 

1 passagem: \0 + Carole\nB
2 passagem: B + ia 
*/

char    *ft_read_fd(int fd, char *unfiltered_line, int *bytes_read)
{
    char *buffer;
    char *temp;
    
    // we're reading for the fist time or the previous call didn't left behind any fragment after the newline
    if (!unfiltered_line)
        unfiltered_line = ft_calloc(1, sizeof(char));

    // allocate memory for the buffer and initialize it to zero
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    
    // itialize the "bytes read" to 1 so it executes the loop at least once
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
