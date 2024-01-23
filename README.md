<h1 align="center">
	📖 get_next_line
</h1>

## 💡 About the project

You must write a function that returns a line read from a file descriptor.

I've written an article that provides detailed guidance on developing this project. 

You can access it on [Medium](https://medium.com/@beatrizbazaglia/get-next-line-3872eb3189e6).

## 📝 Requirements

**Mandatory part:**

• Using repeated calls, such as through a loop, should enable the sequential reading of a text file associated with the provided file descriptor, extracting one line per iteration.

• The function should return the line that was read as its output. In cases where there are no more lines to read or an error occurs, the function should return NULL.

• The function should work correctly both when reading a file and when reading from the standard input.

• The returned line should include the terminating \n character, except if the end of file was reached and does not end with a \n character.

**Bonus part:**

• The function can manage multiple file descriptors at the same time.

## 📋 Testing

To compile, go to the project path and run:

```shell
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=xx get_next_line.c get_next_line_utils.c && ./a.out

// xx is the BUFFER_SIZE you want to test
```


Disclaimer: The main purpose of this repository is to expose my code and help other students to understand what was done in each function. Therefore, this work should be used for academic reasons, by those who aim to learn, and not merely copy.
