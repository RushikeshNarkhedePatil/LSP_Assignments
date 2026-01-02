#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

long totalFiles = 0;
long totalDirs = 0;
long totalSize = 0;
char largestName[256];
long largestSize = 0;

void generate_report(char *basePath)
{
    DIR *dir = opendir(basePath);
    struct dirent *entry;
    struct stat s;
    char path[1024];

    if (!dir)
        return;
    totalDirs++; // Count directory on entry

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", basePath, entry->d_name);
        lstat(path, &s); //

        if (S_ISDIR(s.st_mode))
        {
            generate_report(path);
        }
        else if (S_ISREG(s.st_mode))
        { //
            totalFiles++;
            totalSize += s.st_size;
            if (s.st_size > largestSize)
            {
                largestSize = s.st_size;
                strcpy(largestName, entry->d_name);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;
    generate_report(argv[1]);

    // Format output as per requirements 
    printf("Files: %ld\n", totalFiles);
    printf("Dirs : %ld\n", totalDirs);
    printf("Total Size: %ld bytes\n", totalSize);
    printf("Largest: %s (%ld bytes)\n", largestName, largestSize);

    return 0;
}