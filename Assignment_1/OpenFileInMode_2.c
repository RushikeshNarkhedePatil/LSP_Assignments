/////////////////////////////////////////////////////////////////////////////////////
// Problem Statement: Write a program which accepts file name and mode from user and open that file in specified mode
// File Name: OpenFileInMode_2.c
// Description: This program opens a specified file in user-defined mode (read, write, read/write, append) and displays the file descriptor.
// Owner : Rushikesh Narkhede
// Date : 24 December 2025
/////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main() 
{
    int fd = 0;
    char filename[100];
    char mode[10];
    printf("Enter File Name to Open\n");
    // accept file name from user
    scanf("%s", filename);
    printf("Enter Mode to Open File (R for read, W for write, RW for read/write , A for Append)\n");
    // accept mode from user
    scanf("%s", mode);
    // open the file based on user specified mode
    if (strcmp(mode, "R") == 0) 
    {
        fd = open(filename, O_RDONLY);  
    }
    else if (strcmp(mode, "W") == 0) 
    {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);  
    }
    else if (strcmp(mode, "RW") == 0) 
    {
        fd = open(filename, O_RDWR | O_CREAT, 0644);  
    }   
    else if (strcmp(mode, "A") == 0) 
    {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);  
    } 
    else 
    {
        printf("Invalid mode specified\n");
        return -1;
    }

    if (fd == -1) 
    {
        perror("Error opening file");
        return -1;
    } 
    else 
    {
        printf("File opened successfully with file descriptor : %d\n", fd);
    }
    return 0;
}