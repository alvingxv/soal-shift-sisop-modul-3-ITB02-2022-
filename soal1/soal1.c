#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>
#include <pwd.h>
#include <pthread.h>

void exec(char *cmd, char *argv[])
{
    pid_t child_id;
    child_id = fork();
    int status;

    if (child_id == 0)
    {
        execv(cmd, argv);
    }

    else
    {
        while (wait(&status) > 0)
            ;
    }
}

void *unziphasil()
{
    char *argv[] = {"unzip", "hasil.zip", NULL};
    exec("/bin/unzip", argv);
}

void *unzipmusic()
{
    char *argv[] = {"unzip", "music.zip", "-d", "/home/kali/modul3/music", NULL};
    exec("/bin/unzip", argv);
}

void *unzipquote()
{
    char *argv[] = {"unzip", "quote.zip", "-d", "/home/kali/modul3/quote", NULL};
    exec("/bin/unzip", argv);
}

void decode(char *dir, char *filename)
{
    chdir(dir);
    char *argv[] = {"base64", "-d", filename, NULL};
    exec("/bin/base64", argv);
}

void *mvmusic()
{
    char *argv[] = {"find", "/home/kali/modul3/", "-name", "music.txt", "-exec", "mv", "-t", "/home/kali/modul3/hasil", "{}", "+", NULL};
    exec("/bin/find", argv);
}

void *mvquote()
{
    char *argv[] = {"find", "/home/kali/modul3/", "-name", "quote.txt", "-exec", "mv", "-t", "/home/kali/modul3/hasil", "{}", "+", NULL};
    exec("/bin/find", argv);
}

void *mkhasil()
{
    char *argv[] = {"mkdir", "hasil", NULL};
    exec("/bin/mkdir", argv);
}

void *ziphasil()
{
    char *argv[] = {"zip", "-re", "hasil.zip", "hasil/", NULL};
    exec("/bin/zip", argv);
}

void *ziphasil2()
{
    char *argv[] = {"zip", "-re", "hasil.zip", "hasil", "no.txt", NULL};
    exec("/bin/zip", argv);
}

void *touchno()
{
    char *argv[] = {"echo", "no", ">>", "no.txt", NULL};
    exec("/bin/echo", argv);
}
void addno()
{
    FILE *fptr = fopen("no.txt", "w");
    fprintf(fptr, "no");
}

void *touch(char *dest, char *name)
{
    chdir(dest);
    char *argv[] = {"touch", name, NULL};
    exec("/bin/touch", argv);
}

void *newline()
{

    char *argv[] = {"echo", "\n", NULL};
    exec("/bin/echo", argv);
}

void *decodemusic()
{
    freopen("music.txt", "w", stdout);
    decode("/home/kali/modul3/music", "m1.txt");
    newline();
    decode("/home/kali/modul3/music", "m2.txt");
    newline();
    decode("/home/kali/modul3/music", "m3.txt");
    newline();
    decode("/home/kali/modul3/music", "m4.txt");
    newline();
    decode("/home/kali/modul3/music", "m5.txt");
    newline();
    decode("/home/kali/modul3/music", "m6.txt");
    newline();
    decode("/home/kali/modul3/music", "m7.txt");
    newline();
    decode("/home/kali/modul3/music", "m8.txt");
    newline();
    decode("/home/kali/modul3/music", "m9.txt");
}

void *decodequote()
{
    freopen("quote.txt", "w", stdout);
    decode("/home/kali/modul3/quote", "q1.txt");
    newline();
    decode("/home/kali/modul3/quote", "q2.txt");
    newline();
    decode("/home/kali/modul3/quote", "q3.txt");
    newline();
    decode("/home/kali/modul3/quote", "q4.txt");
    newline();
    decode("/home/kali/modul3/quote", "q5.txt");
    newline();
    decode("/home/kali/modul3/quote", "q6.txt");
    newline();
    decode("/home/kali/modul3/quote", "q7.txt");
    newline();
    decode("/home/kali/modul3/quote", "q8.txt");
    newline();
    decode("/home/kali/modul3/quote", "q9.txt");
}

void *outputmusic()
{
    decodemusic();
}
void *outputquote()
{
    freopen("quote.txt", "w", stdout);
    decodequote();
}

int main()
{
    pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
    mkhasil();
    pthread_join(t8, NULL);
    pthread_create(&t1, NULL, &unzipmusic, NULL);
    pthread_create(&t2, NULL, &unzipquote, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    freopen("music.txt", "w", stdout);
    decodemusic();
    fclose(stdout);
    freopen("quote.txt", "w", stdout);
    decodequote();
    fclose(stdout);
    pthread_create(&t5, NULL, &mvmusic, NULL);
    pthread_create(&t6, NULL, &mvquote, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    ziphasil();
    unziphasil();
    touch("/home/modul3/", "no.txt");
    addno();
    ziphasil2();
}
