/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Problem Statement : Write a program which accept file name from user and read whole file
//                     at once and showing number of bytes to read.
// Author : Rushikesh Dilip Narkhede
// Date : 18/06/2024
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    char filename[100];
    char buffer[1024];
    int fd = 0;
    int iRet = 0;
    int totalBytes = 0;

    printf("Enter file name to read data : \n");
    scanf("%s", filename);

    // Open the file in read only mode
    fd = open(filename, O_RDONLY);
    if(fd == -1)
    {
        perror("Unable to open file");
        return -1;
    }

    printf("--- File Data Reading Data Start ---\n");

    // Use a buffer loop (read() until 0)
    while((iRet = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(1, buffer, iRet); 
        //buffer clearing
        memset(buffer, 0, sizeof(buffer));
        // Show total bytes read
        totalBytes = totalBytes + iRet;
    }
    
    printf("\n--- File Data Ends  ---\n");
    printf("Total bytes read : %d\n", totalBytes);

    close(fd);
    return 0;
}
