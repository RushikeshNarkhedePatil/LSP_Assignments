/////////////////////////////////////////////////////////////////////////////////////////////
// Problem Statement: Write a program which accepts file name and mode from user and check whether that file is accessible in that mode or not.
// File Name: FilePermision_3.c
// Description: This program checks if a specified file is accessible in user-defined mode (read,
// write, execute) and displays the result.
// Owner : Rushikesh Narkhede
// Date : 24 December 2025
/////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
int main()
{
    char filename[100];
    char Mode[20];
    int iRet = 0;
    printf("Enter File name for open : ");
    scanf("%s", filename);
    printf("Enter file permission mode (read , write or execute): ");
    scanf("%s", Mode);

    if (strcmp(Mode, "read") == 0)
    {
        iRet = access(filename, R_OK);
    }
    else if (strcmp(Mode, "write") == 0)
    {
        iRet = access(filename, W_OK);
    }
    else if (strcmp(Mode, "execute") == 0)
    {
        iRet = access(filename, X_OK);
    }
    else
    {
        printf("Invalid Mode\n");
        return -1;
    }

    //Result check
    if (iRet == 0)
    {
        printf("%s is Accessible in %s mode\n", filename, Mode);
    }
    else
    {
        perror("Not accessible");
    }

    return 0;
}