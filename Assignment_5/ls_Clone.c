/*
Create a program ls_clone.c that takes one directory path and prints:
•Entry name
•Type ( le/dir/link/other)
•Size (bytes)
•Permissions in rwxr-xr-x format
•Last modi ed time
•Skip . and ...
•Build full path using snprintf(dir + "/" + name).

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <linux/limits.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dir_path = argv[1];
    DIR *dir = opendir(dir_path);
    if (!dir)
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue; // Skip . and ..
        }

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat sb;
        if (lstat(full_path, &sb) == -1)
        {
            perror("lstat");
            continue;
        }

        // Entry name
        printf("Name: %s\n", entry->d_name);

        // Type
        char *type;
        if (S_ISREG(sb.st_mode))
            type = "file";
        else if (S_ISDIR(sb.st_mode))
            type = "dir";
        else if (S_ISLNK(sb.st_mode))
            type = "link";
        else
            type = "other";
        printf("Type: %s\n", type);

        // Size
        printf("Size: %lld bytes\n", (long long)sb.st_size);

        // Permissions
        printf("Permissions: %d\n", sb.st_mode);

        // Last modified time
        char time_str[20];
        struct tm *tm_info = localtime(&sb.st_mtime);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
        printf("Last modified: %s\n", time_str);

        printf("\n");
    }

    closedir(dir);
    return EXIT_SUCCESS;
}