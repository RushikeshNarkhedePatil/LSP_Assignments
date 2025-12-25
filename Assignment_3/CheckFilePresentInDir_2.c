////////////////////////////////////////////////////////////////////////////////////////
// Problem Statement: Write a program which checks whether the given file is present in
//                    the specified directory or not. If the file is present then print the
//                    absolute path of that file.
// Author : Rushikesh Dilip Narkhede
// Date : 25 December 2025
////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include <limits.h>
#include<stdlib.h>

int main() {
    char DirName[100], FileName[100];
    DIR *dp = NULL;
    struct dirent *ptr = NULL;

    printf("Enter directory name: "); scanf("%s", DirName);
    printf("Enter file name to search: "); scanf("%s", FileName);

    dp = opendir(DirName);
    if(dp == NULL) 
    { 
        perror("Dir error"); 
        return -1; 
    }

    while((ptr = readdir(dp)) != NULL) 
    { 
        if(strcmp(ptr->d_name, FileName) == 0) 
        {
            printf("File found Absolute Path: %s/%s\n", realpath(DirName, NULL), FileName);
            closedir(dp); return 0;
        }
    }
    printf("File not found.\n");
    closedir(dp); 
    return 0;
}