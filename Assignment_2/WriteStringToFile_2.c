#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    char filename[100];
    char str[1024];
    int fd = 0;
    int iRet = 0;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter the string you want to write: ");
    scanf(" %[^\n]s", str);
    //printf("\n");

    // Open the file in write only mode, append if exists, create if not
    fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777); 

    if(fd == -1)
    {
        perror("Unable to open file");
        return -1;
    }

    // Write string using write() 
    iRet = write(fd, str, strlen(str));

    if(iRet == -1)
    {
        perror("Unable to write");
    }
    else
    {
        // Print number of bytes written 
        printf("Successfully written %d bytes to the file.\n", iRet);
    }

    close(fd);
    return 0;
}