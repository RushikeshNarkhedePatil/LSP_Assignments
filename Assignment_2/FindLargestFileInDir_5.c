#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>

int main()
{
    char DirName[100];
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    char Path[1024];
    
    long int iMax = 0;
    char MaxFileName[100] = {0};

    printf("Enter directory name: ");
    scanf("%s", DirName);

    dp = opendir(DirName);
    if(dp == NULL)
    {
        printf("Unable to open directory\n");
        return -1;
    }

    // Check all files in directory
    while((ptr = readdir(dp)) != NULL)
    {
        // Create full file path
        sprintf(Path, "%s/%s", DirName, ptr->d_name);
        
        lstat(Path, &sobj);

        // Consider Only Reguler file and ignore directories
        if(S_ISREG(sobj.st_mode))
        {
            // Current file size is greater than max size found yet
            if(sobj.st_size > iMax)
            {
                iMax = sobj.st_size; // store new big size file size
                strcpy(MaxFileName, ptr->d_name); // store file name
            }
        }
    }

    if(iMax == 0)
    {
        printf("No regular files found in the directory.\n");
    }
    else
    {
        // Largest File details
        printf("Largest File Name: %s\n", MaxFileName);
        printf("Size in bytes: %ld\n", iMax);
    }

    closedir(dp);
    return 0;
}