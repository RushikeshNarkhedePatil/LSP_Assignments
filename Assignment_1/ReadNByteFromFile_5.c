///////////////////////////////////////////////////////////////////////
// Problem Statement: Write a program which accepts file name and number of bytes from user and read that number of bytes from file.
 // File Name: ReadNByteFromFile_5.c
 // Description: This program reads a specified number of bytes from a user-defined file and displays the content.
 // Owner : Rushikesh Narkhede
 // Date : 24 December 2025
 ///////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int fd =0;
    char filename[100];
    char buffer[1024];
    ssize_t bytesRead;
    int NumberOfBytes = 0;

    printf("Enter File Name to Read\n");
    scanf("%s",filename);

    printf("Number of  bytes to read :\n");
    scanf("%d",&NumberOfBytes);

    //open the file in read only mode
    fd = open(filename, O_RDONLY);
    if(fd == -1)
    {
        perror("Error opening file");
        return -1;
    }

    //read bytes from file
    bytesRead = read(fd, buffer, NumberOfBytes);
    if(bytesRead == -1)
    {
        perror("Error reading file");
        close(fd);
        return -1;
    }

    //null terminate the buffer to make it a valid string
    buffer[bytesRead] = '\0';

    //display the read content
    printf("Read %zd bytes from file:\n%s\n", bytesRead, buffer);

    close(fd);
    return 0;
}