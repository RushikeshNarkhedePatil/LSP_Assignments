//////////////////////////////////////////////////////////////////////////////////////////////
// Problem Statement: Write a program which accepts file name from user and open that file in read only mode
// File Name: OpenFile_1.c
// Description: This program opens a specified file in read-only mode and displays the file descriptor.
// Owner : Rushikesh Narkhede
// Date : 24 December 2025
//////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int fd =0;
    char filename[100];
    printf("Enter File Name to Open\n");
    //accept file name from user
    scanf("%s",filename);
    printf("File Name is : %s\n",filename);
    //open the file in read only mode
    fd = open(filename, O_RDONLY);
    if(fd == -1)
    {
        perror("Error opening file");
        return -1;
    }
    else
    {
        printf("File opened successfully with file descriptor: %d\n", fd);
    }
    close(fd);
    return 0;
}