#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

char type(mode_t mode);
char *perm(mode_t mode);
void printStat(char *pathname, char *file, struct stat *st);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[PATH_MAX];

    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        return 1;
    }

    while ((d = readdir(dp)) != NULL) {

        if (snprintf(path, sizeof(path), "%s/%s", dir, d->d_name)
            >= (int)sizeof(path)) {
            fprintf(stderr, "경로가 너무 깁니다.\n");
            continue;
        }

        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st);
    }

    closedir(dp);
    return 0;
}

void printStat(char *pathname, char *file, struct stat *st)
{
    struct passwd *pw;
    struct group *gr;

    pw = getpwuid(st->st_uid);
    gr = getgrgid(st->st_gid);

    printf("%5lld ", (long long)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3lu ", (unsigned long)st->st_nlink);

    printf("%s %s ",
        pw ? pw->pw_name : "unknown",
        gr ? gr->gr_name : "unknown");

    printf("%9lld ", (long long)st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("%s\n", file);
}

char type(mode_t mode)
{
    if (S_ISREG(mode))
        return '-';
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISSOCK(mode))
        return 's';

    return '?';
}

char *perm(mode_t mode)
{
    static char perms[10] = "---------";

    strcpy(perms, "---------");

    if (mode & S_IRUSR) perms[0] = 'r';
    if (mode & S_IWUSR) perms[1] = 'w';
    if (mode & S_IXUSR) perms[2] = 'x';

    if (mode & S_IRGRP) perms[3] = 'r';
    if (mode & S_IWGRP) perms[4] = 'w';
    if (mode & S_IXGRP) perms[5] = 'x';

    if (mode & S_IROTH) perms[6] = 'r';
    if (mode & S_IWOTH) perms[7] = 'w';
    if (mode & S_IXOTH) perms[8] = 'x';

    return perms;
}
