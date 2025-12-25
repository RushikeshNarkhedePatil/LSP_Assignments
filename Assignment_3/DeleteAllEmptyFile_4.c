/////////////////////////////////////////////////////////////////////////////////
// Problem Statement :- Remove empty reguler file.
// author :- Rushikesh Dilip Narkhede
// Date   :- 25 December 2025
////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>

int main() {
    char DirName[100], Path[1024];
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    int count = 0;

    printf("Enter directory name: "); 
    scanf("%s", DirName);

    dp = opendir(DirName);
    while((ptr = readdir(dp)) != NULL) 
    {
        sprintf(Path, "%s/%s", DirName, ptr->d_name);
        stat(Path, &sobj);

        if(S_ISREG(sobj.st_mode) && sobj.st_size == 0) 
        {
            printf("Deleting empty file: %s\n", ptr->d_name);
            unlink(Path);
            count++;
        }
    }
    printf("Total empty files deleted: %d\n", count);
    closedir(dp); 
    return 0;
}