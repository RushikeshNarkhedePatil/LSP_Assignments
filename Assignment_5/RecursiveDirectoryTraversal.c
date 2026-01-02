#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void run_tree(char *name, int depth)
{
    DIR *dir;
    struct dirent *entry;
    struct stat s;
    char path[1024];

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
        lstat(path, &s); // Use lstat for links 

        // Indentation based on depth 
        for (int i = 0; i < depth; i++)
            printf("  ");

        // Type markers 
        if (S_ISDIR(s.st_mode))
        {
            printf("[D] %s/\n", entry->d_name);
            run_tree(path, depth + 1); // Recurse
        }
        else if (S_ISLNK(s.st_mode))
        {
            printf("[L] %s\n", entry->d_name);
        }
        else
        {
            printf("[F] %s\n", entry->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;
    printf("%s/\n", argv[1]);
    run_tree(argv[1], 1);
    return 0;
}