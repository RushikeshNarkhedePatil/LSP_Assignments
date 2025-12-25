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

    printf("Enter directory name: ");
    scanf("%s", DirName);

    dp = opendir(DirName); // डिरेक्टरी उघडणे 
    if(dp == NULL)
    {
        printf("Unable to open directory\n");
        return -1;
    }

    printf("Files and their types:\n");

    while((ptr = readdir(dp)) != NULL)
    {
        sprintf(Path, "%s/%s", DirName, ptr->d_name);
        
        lstat(Path, &sobj);

        printf("%-20s : ", ptr->d_name);

        if(S_ISREG(sobj.st_mode))
            printf("Regular File\n");
        else if(S_ISDIR(sobj.st_mode))
            printf("Directory\n");
        else if(S_ISLNK(sobj.st_mode))
            printf("Symbolic Link\n");
        else if(S_ISFIFO(sobj.st_mode))
            printf("FIFO/Pipe\n");
        else if(S_ISSOCK(sobj.st_mode))
            printf("Socket\n");
        else if(S_ISCHR(sobj.st_mode))
            printf("Character Device\n");
        else if(S_ISBLK(sobj.st_mode))
            printf("Block Device\n");
    }

    closedir(dp);
    return 0;
}