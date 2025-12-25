///////////////////////////////////////////////////////////////////////////////
// Problem Statement: Write a program which copies the contents of one file to another file.
// Author : Rushikesh Dilip Narkhede
// Date : 25 December 2025
//////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
    char buffer[1024];
    int fdSrc = 0, fdDest = 0, iRet = 0;
    struct stat sobj;

    if(argc != 3) {
        printf("Usage: ./MyExe source_file dest_file\n");
        return -1;
    }

    fdSrc = open(argv[1], O_RDONLY);
    if(fdSrc == -1) 
    {
         perror("Source error"); 
         return -1; 
    }

    // O_CREAT | O_TRUNC if file is not there create new file else truncate the file
    fdDest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    
    while((iRet = read(fdSrc, buffer, sizeof(buffer))) > 0) 
    { 
        write(fdDest, buffer, iRet);
    }

    // Permissions Preserve 
    fstat(fdSrc, &sobj);
    fchmod(fdDest, sobj.st_mode);

    close(fdSrc); close(fdDest);
    printf("File copied successfully.\n");
    return 0;
}