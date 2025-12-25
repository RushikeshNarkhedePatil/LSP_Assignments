#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<dirent.h>

int main()
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    char dirname[100];

    printf("Enter the directory name : \n");
    scanf("%s",dirname);
    printf("\n");

    dp=opendir(dirname);



    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }
    else
    {
        printf("Directory gets sucessfully open\n");
    }
    ptr = readdir(dp);

    while(ptr != NULL)
    {
        // Avoid . and ..
        if(strcmp(ptr->d_name,".") != 0 && strcmp(ptr->d_name,"..") != 0)
            printf("%s\n",ptr->d_name);
        ptr = readdir(dp);
    }
    return 0;
}