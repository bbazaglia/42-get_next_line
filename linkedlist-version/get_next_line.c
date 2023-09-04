#include "get_next_line.h"

// Function to insert a new node at the beginning of the linked list
struct Node *insertAtBeginning(struct Node *head, const char *newData)
{
    // Allocate memory for a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    // Check if memory allocation was successful
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1); // Exit the program
    }

    // Dynamically allocate memory for the data and copy the string
    newNode->data = ft_strdup(newData);

    // Set the next pointer of the new node to the current head
    newNode->next = head;

    // Update the head to point to the new node
    return newNode;
}

// Function to free the memory used by the linked list
void freeLinkedList(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL)
    {
        struct Node *next = current->next;
        free(current->data); // Free the dynamically allocated string
        free(current);       // Free the node itself
        current = next;
    }
}

// Function to read a line from a file descriptor
char *getNextLine(int fd)
{
    char *line = NULL;     // Pointer to the line
    size_t lineSize = 0;   // Current size of the line buffer
    size_t lineLength = 0; // Current length of the line being read

    while (1)
    {
        char ch;
        // Read one byte (char) from the fd and store it in a 'ch' variable
        // The read function returns the number of bytes read (which is 1 in this case)
        ssize_t bytesRead = read(fd, &ch, 1);

        if (bytesRead == -1)
        {
            break; // Error
        }

        if (bytesRead == 0)
        {
            if (lineLength == 0)
                return NULL; // End of file and no data read
            else
                break; // End of file, data read
        }

        // If the line buffer is full, allocate a new buffer and chain it
        if (lineLength >= lineSize)
        {
            size_t newSize = lineSize + BUFFER_SIZE; // Use the defined buffer size
            char *newBuffer = (char *)malloc(newSize);

            if (newBuffer == NULL)
            {
                perror("Memory allocation failed");
                free(line);
                return NULL;
            }

            if (line != NULL)
            {
                // Copy the data from the old buffer to the new buffer
                ft_memcpy(newBuffer, line, lineLength);
                free(line); // Free the old buffer
            }

            // Update the line pointer to point to the new buffer
            line = newBuffer;

            // Update lineSize to the new size
            lineSize = newSize;
        }

        // Append the character to the line
        line[lineLength++] = ch;

        // If a newline character is encountered, terminate the line and return it
        if (ch == '\n')
        {
            line[lineLength] = '\0';
            return line;
        }
    }

    // Terminate the line and return it (if any data was read)
    if (lineLength > 0)
    {
        line[lineLength] = '\0';
        return line;
    }

    // No data read, or an error occurred
    free(line);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <start_line> <end_line>\n", argv[0]);
        return 1;
    }

    int startLine = atoi(argv[1]);
    int endLine = atoi(argv[2]);

    // Initialize an empty linked list
    struct Node *head = NULL;

    // Open the file for reading
    int fd = open("input.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }

    // Read lines from the file and insert them into the linked list
    char *line;
    int currentLine = 0;

    while ((line = getNextLine(fd)) != NULL)
    {
        currentLine++;

        if (currentLine >= startLine && currentLine <= endLine)
        {
            printf("Line %d: %s", currentLine, line);
        }

        free(line);

        if (currentLine == endLine)
        {
            break;
        }
    }

    close(fd);

    // Free the memory allocated for the linked list
    freeLinkedList(head);

    return 0;
}