/////////////////////////////////////////////////////////////////////////////////////////
//  Problem statement :- Move files one directory to another directory only reguler file
// Author : Rushikesh Dilip Narkhede
// Date   : 25 December 2025
////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <dirent.h>
#include<errno.h>
#include <sys/stat.h>

int main()
{
    char srcDir[100], destDir[100], oldPath[1024], newPath[1024];
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    int count = 0;
    int iRet = 0;

    printf("Source Dir: ");
    scanf("%s", srcDir);
    printf("\n");

    printf("Destination Dir: ");
    scanf("%s", destDir);
    printf("\n");

    // Check Destination directory available or not
    dp = opendir(destDir);
    if(dp != NULL)
    {
        closedir(dp);
    }
    else
    {
        if (errno == ENOENT) 
        {
            printf("Directory does not exist.\n");
        } 
        else if (errno == ENOTDIR) 
        {
            printf("The name exists but it is not a directory.\n");
        } 
        else 
        {
            perror("Error");
        }
         closedir(dp);
    }


    dp = opendir(srcDir);

    if (dp != NULL)
    {
        while ((ptr = readdir(dp)) != NULL)
        {
            sprintf(oldPath, "%s/%s", srcDir, ptr->d_name);
            stat(oldPath, &sobj);

            if (S_ISREG(sobj.st_mode))
            {
                sprintf(newPath, "%s/%s", destDir, ptr->d_name);
                if (rename(oldPath, newPath) == 0)
                {
                    count++;
                }
            }
        }
    }
    else
    {
        if (errno == ENOENT) 
        {
            printf("Directory does not exist.\n");
        } 
        else if (errno == ENOTDIR) 
        {
            printf("The name exists but it is not a directory.\n");
        } 
        else 
        {
            perror("Error");
        }
    }
    printf("Total files moved: %d\n", count);
    closedir(dp);
    return 0;
}