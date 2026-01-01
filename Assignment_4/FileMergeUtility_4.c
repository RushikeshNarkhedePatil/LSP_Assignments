///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Problem Statement: Write a C program that merges multiple files into a single file. The program should take the names of the files to be merged as 
// command line arguments and create a new file named "OutPutMergeFile.txt" in the current directory. The program should read the contents of 
// each file and write
// Date : 01 January 2026
// Author : Rushikesh Dilip Narkhede
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int source_fd = 0, dest_fd = 0;
    ssize_t bytesRead = 0;
    struct stat st;
    off_t current_dest_offset = 0;

    if (argc < 2) 
    {
        printf("Usage: %s Enter File Names eg File1.txt File2.txt etc ...\n", argv[0]);
        return -1;
    }

    // Open destination file once outside the loop
    dest_fd = open("OutPutMergeFile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (dest_fd == -1) {
        perror("Unable to open destination file");
        return -1;
    }

    // Start loop from index 1 (skip program name)
    for(int i = 1; i < argc; i++)
    {
        source_fd = open(argv[i], O_RDONLY);
        if (source_fd == -1) 
        {
            printf("Unable to open source file: %s\n", argv[i]);
            continue; // Skip to next file if one fails
        }

        // Get file size to know how much to read
        fstat(source_fd, &st);
        
        // Dynamic allocation to handle files of any size safely
        char *buffer = malloc(st.st_size);
        if (buffer == NULL) 
        {
            perror("Memory allocation failed");
            close(source_fd);
            break;
        }

        // pread: reads from offset 0 without changing the file pointer
        bytesRead = pread(source_fd, buffer, st.st_size, 0);
        
        if (bytesRead > 0) 
        {
            // pwrite: writes to specific offset in destination
            pwrite(dest_fd, buffer, bytesRead, current_dest_offset);
            
            // Update the offset for the next file
            current_dest_offset = current_dest_offset + bytesRead;
            printf("Merged: %s (%ld bytes)\n", argv[i], (long)bytesRead);
        }

        free(buffer);
        close(source_fd);
    }

    close(dest_fd);
    printf("\nSuccessfully created OutPutMergeFile.txt\n");
    return 0;
}