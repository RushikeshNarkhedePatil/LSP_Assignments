///////////////////////////////////////////////////////////////////////////////////////////
// Problem Statement: Write a program which copies the contents of one file into another file using pread() and pwrite() system calls.
// Date: 1 January 2026
// Author: Rushikesh Dilip Narkhede
//////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int source_fd = 0,dest_fd=0;
    off_t offset=0;
    char buffer[1024];
    int iRet=0;
    struct stat st;

    source_fd =open(argv[1],O_RDONLY);
    fstat(source_fd, &st); // Get file statistics to find the total size

    if(source_fd == -1)
    {
        printf("Unable to open file\n");
        return -1;
    }
    iRet=pread(source_fd,buffer,st.st_size,0);  //read size of file bytes from offset 0
    if(iRet == -1)
    {
        printf("Unable to read file\n");
        close(source_fd);
        return -1;
    }


    dest_fd =open(argv[2],O_WRONLY |O_CREAT | O_APPEND);
    if(dest_fd == -1)
    {
        printf("Unable to open file\n");
        return -1;
    }
    printf("\n");
    pwrite(dest_fd,buffer,iRet,0);  //write size of file bytes to offset 0
    printf("\n");

    return 0;
}