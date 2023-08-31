#include "get_next_line.h"

/* create function to create the list
while '\n' is not present: allocate memory for the BUFFER_SIZE + 1 (null terminator) & check if operation was successful
if operations fails, return NULL

add a null terminator at the end of the variable 

call a function to add the variable to the linked list */


/* create a function to create a new node and  */

// as we don't have a return value, if we passed only a pointer, all modifications made inside this function would not make a difference in the other function (where this one was called)


char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
        

}
