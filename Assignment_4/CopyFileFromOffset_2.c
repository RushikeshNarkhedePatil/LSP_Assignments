//////////////////////////////////////////////////////////////////////////////////////////////////////////
// problem statement: Write a program which accept file name and offset from user and copy the contents of that file
//                    from that offset into another file.
// Author: Rushikesh Dilip Narkhede
// Date: 1 January 2026
// Description: This program copies the contents of a source file to a destination file starting from a specified offset using system calls.
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    off_t offset;
    char buffer[1024];

    // Open the source file for reading
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd < 0) 
    {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing (create if it doesn't exist)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (dest_fd < 0) 
    {
        perror("Error opening destination file");
        close(source_fd);
        return 1;
    }

    // Get the offset from command line argument
    offset = atoll(argv[3]);

    // Move the file pointer of source file to the specified offset
    int iRet = lseek(source_fd, offset, SEEK_SET);
    if( iRet == -1) 
    {
        perror("Error seeking in source file");
        close(source_fd);
        close(dest_fd);
        return 1;
    }

    // Copy contents from source to destination starting from the offset
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) 
    {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) 
        {
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