///////////////////////////////////////////////////////////////////////////////////
// File Name: DisplayFileInformation_4.c
// Description: This program displays various information about a specified file
// including size, inode number, number of links, owner IDs, permissions, and timestamps.
// Owner : Rushikesh Narkhede
// Date : 24 December 2025
///////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

int main()
{
    char filename[100];
    struct stat fileStat;

    printf("Enter File name to display information: ");
    scanf("%s", filename);

    if(stat(filename, &fileStat) < 0)
    {
        perror("stat");
        return -1;
    }


    printf("File Size: \t\t%lld bytes\n", (long long)fileStat.st_size);
    printf("Inode Number: \t\t%lu\n", (unsigned long)fileStat.st_ino);
    printf("Number of Links: \t%lu\n", (unsigned long)fileStat.st_nlink);
    printf("Owner User ID: \t\t%u\n", fileStat.st_uid);
    printf("Owner Group ID: \t%u\n", fileStat.st_gid);
    printf("File Permissions: \t");

    printf("Last status change:       %s", ctime(&fileStat.st_ctime));
    printf("Last file access:         %s", ctime(&fileStat.st_atime));
    printf("Last file modification:   %s", ctime(&fileStat.st_mtime));

    return 0;
}