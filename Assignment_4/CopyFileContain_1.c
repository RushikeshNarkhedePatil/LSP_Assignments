//////////////////////////////////////////////////////////////////////////////////////////////////
// Problem Statement: Write a C program to copy the contents of one file to another file.
// Name: CopyFileContain_1.c
// Author: Rushikesh Dilip Narkhede
// Date: 31 December 2025
// Description: This program copies the contents of a source file to a destination file using system calls.
//////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main(int argc, char *argv[]) 
{
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[1024];

    // Open the source file for reading
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing (create if it doesn't exist)
    // provide permissions rw-r--r--
    
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0777);
    if (dest_fd < 0) 
    {
        perror("Error opening destination file");
        close(source_fd);
        return 1;
    }

    // Copy contents from source to destination
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) 
    {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    if(bytes_read < 0) 
    {
        perror("Error reading from source file");
    }

    // Close the file descriptors
    close(source_fd);
    close(dest_fd);

    return 0;
}   