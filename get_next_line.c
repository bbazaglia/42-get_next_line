/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:24:42 by bbazagli          #+#    #+#             */
/*   Updated: 2023/08/10 10:41:50 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The purpose of this code is to read each line from a file descriptor and return it.

-> What is a line?
* A line is a succession of characters that end with ’\n’ or with End Of File (EOF).

> What is a file descriptor?
* A file descriptor is a non-negative integer that uniquely identifies an open file in a computer's operating system.

-> How can we read from a file descriptor?
* We can use the read() function to read the data previously written to a file.
* The read() function returns the number of bytes actually read, or -1 if an error occurred.

-> What is a buffer?
* A buffer is a temporary storage area that stores data while it is being transferred from one place to another.
* In this program, the buffer is used to temporarily hold data read from the file descriptor until complete lines can be extracted.

-> Static vs. Non-Static Variables
* The memory for static variables is allocated once when the program starts and is retained until the program terminates.
* The memory for non-static variables is allocated every time the function is called and is released when the function ends.

-> The usage of a static buffer in this project:
* The static buffer will be allocated once and persist until the program ends.
* As the function reads lines from the file descriptor and stores them in the buffer, it can continue reading from where it left off in the previous iteration.

-> Note: attention to concurrency issues.
* If multiple threads or parts of the program access the same static buffer simultaneously, it can lead to unexpected behavior or data corruption.

-> Why the buffer size impacts the performance of the program?
* The buffer size is the number of bytes that the read() function will read from the file descriptor at each iteration.
- A very small buffer size (e.g., 1) means the function reads only one byte at a time from the file descriptor.
    This could lead to many I/O operations, making the process less efficient due to the overhead associated with each read operation.
    Additionally, processing data byte by byte can introduce complexity when dealing with multi-byte character encodings.
- A very large buffer size can be efficient in terms of reading large amounts of data in one go.
    However, it might lead to excessive memory usage, particularly if lines are shorter than the buffer size. Unused memory in the buffer might go to waste.
- A relatively large buffer size allows the function to read a substantial amount of data at once from the file descriptor.
    This can be efficient because reading larger chunks of data minimizes the number of I/O operations, reducing overhead.
    At the same time, the buffer is not so large that it wastes memory when lines are shorter than the buffer size.
    
-> What buffer size should we use?
* The choice of BUFFER_SIZE depends on a trade-off between efficiency and memory usage. 
* A reasonable buffer size is typically in the range of a few kilobytes (e.g., 1024 or 4096 bytes).

-> Return values of get_next_line():
* correct behavior: the line that was read (including the terminating ’\n’ character, if present);
* there is nothing to read or an error occurred: NULL. */

char *get_next_line(int fd)
{
}

