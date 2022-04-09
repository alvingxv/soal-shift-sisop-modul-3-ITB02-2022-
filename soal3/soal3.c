#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>

int checkFile(const char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0)
        return 1;
    else // -1
        return 0;
}

void *move(void *filename)
{
    char cwd[PATH_MAX];
    char dirname[200];
    char hidden[100];
    char hiddenname[100];
    char file[100];
    char existsfile[100];
    int i;
    strcpy(existsfile, filename);
    strcpy(hiddenname, filename);
    char *namaa = strrchr(hiddenname, '/');
    strcpy(hidden, namaa);

    if (hidden[1] == '.')
    {
        strcpy(dirname, "Hidden");
    }
    else if (strstr(filename, ".") != NULL)
    {
        strcpy(file, filename);
        strtok(file, ".");
        char *token = strtok(NULL, "");
        for (i = 0; token[i]; i++)
        {
            token[i] = tolower(token[i]);
        }
        strcpy(dirname, token);
    }
    else
    {
        strcpy(dirname, "Unknown");
    }
    int exist = checkFile(existsfile);
    if (exist)
        mkdir(dirname, 0777);

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        char *nama = strrchr(filename, '/');
        char namafile[200];
        strcpy(namafile, cwd);
        strcat(namafile, "/");
        strcat(namafile, dirname);
        strcat(namafile, nama);

        rename(filename, namafile);
    }
}

void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    struct stat buffer;
    DIR *dir = opendir(basePath);
    int n = 0;

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            if (stat(path, &buffer) == 0 && S_ISREG(buffer.st_mode))
            {
                pthread_t thread;
                int err = pthread_create(&thread, NULL, move, (void *)path);
                pthread_join(thread, NULL);
            }

            listFilesRecursively(path);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        listFilesRecursively(cwd);
    }
}
