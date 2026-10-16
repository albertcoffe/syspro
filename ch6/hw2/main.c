#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *entry;
    struct stat buf;

    char path[1024];
    char *dirname = ".";
    char option = ' ';

    int i;

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
            option = argv[i][1];
        else
            dirname = argv[i];
    }

    dp = opendir(dirname);

    if (dp == NULL)
    {
        perror("opendir");
        exit(1);
    }

    while ((entry = readdir(dp)) != NULL)
    {
        snprintf(path, sizeof(path), "%s/%s",
                 dirname, entry->d_name);

        if (lstat(path, &buf) == -1)
        {
            perror("lstat");
            continue;
        }

        if (option == 'i')
        {
            printf("%lu %s\n",
                   (unsigned long)buf.st_ino,
                   entry->d_name);
        }
        else if (option == 'p')
        {
            printf("%s", entry->d_name);

            if (S_ISDIR(buf.st_mode))
                printf("/");

            printf("\n");
        }
        else if (option == 'Q')
        {
            printf("\"%s\"\n", entry->d_name);
        }
        else
        {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);

    return 0;
}

