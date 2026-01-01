///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Problem Statement : Display the contain of file in reverse order.
// Date : 01 Jan 2026
// Auther : Rushikesh dilip Narkhede
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
    int fd=0;
    int iRet = 0;
    struct stat st;

    if (argc < 2) 
    {
        printf("Usage: %s  <File1.txt>...\n", argv[0]);
        return -1;
    }

    fd = open(argv[1],O_RDONLY);
     // Dynamic allocation to handle files of any size safely
        char *buffer = malloc(st.st_size);
    if (buffer == NULL) 
    {
        perror("Memory allocation failed");
        close(fd);
        return -1;
    }
    if (fd == -1) 
    {
        printf("Unable to open source file: %s\n", argv[1]);
        return -1; // Exit if file cannot be opened
    }
    // Get file size to know how much to read
    if (fstat(fd, &st) == -1)
    {
        perror("fstat failed");
        close(fd);
        return -1; // Exit if fstat fails
    }
    // pread: reads from offset 0 without changing the file pointer
    iRet = pread(fd, buffer, st.st_size, 0);
    if (iRet < 0)
    {
        printf("Unable to read file\n");
        close(fd);
        return -1; // Exit if pread fails
    }
    // pwrite: writes reverse on console
    for (int i = iRet - 1; i >= 0; i--)
    {
        if (write(STDOUT_FILENO, &buffer[i], 1) < 0)
        {
            perror("write failed");
            free(buffer);
        }
    }
    free(buffer);
    printf("\n");
    // Close the file descriptor
    if (close(fd) == -1)
    {
        perror("close failed");
        return -1; // Exit if close fails
    }
    printf("File reversed successfully.\n");
    // Return 0 to indicate success
    return 0;
}