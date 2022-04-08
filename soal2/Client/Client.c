#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define PORT 8080
#define SIZE 1024

char *read_file(char *filename)
{
    FILE *file;

    file = fopen(filename, "r");

    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(sizeof(char) * (length + 1));
    char c;
    int i = 0;

    while ((c = fgetc(file)) != EOF)
    {
        string[i] = c;

        i++;
    }

    string[i] = '\0';

    return string;
}
void send_file(int socket, char *namafile)
{
    char file_length[1024];
    char *file_content = (char *)malloc(sizeof(char) * 65536);

    memset(file_length, 0, sizeof(file_length));

    char *file_contents;
    file_contents = read_file(namafile);
    if (file_contents == NULL)
    {
        printf("Error reading file.\n");
        return;
    }
    sleep(2);
    send(socket, file_contents, strlen(file_contents), 0);
}
void write_file(int socket, char *folder, char *namafile)
{
    char buffer[1024] = {0};
    char filepath[2048] = {0};
    strcat(filepath, "./");
    strcat(filepath, folder);
    strcat(filepath, "/");
    strcat(filepath, namafile);
    printf("Filepath %s: %s\n", namafile, filepath);
    mkdir(folder, 0777);

    char file_isi[1024] = {0};
    read(socket, buffer, 1024);
    strcpy(file_isi, buffer);
    FILE *fptr = fopen(filepath, "a+");
    fprintf(fptr, "%s", file_isi);
    fclose(fptr);
    memset(file_isi, 0, sizeof(file_isi));
    memset(filepath, 0, sizeof(filepath));
    memset(buffer, 0, sizeof(buffer));
}

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    char buffer[1024] = {0};
    char *login = "1";
    char *regis = "2";
    char username[1024];
    char password[1024];
    char judul[1024];
    int pilihan;
    char check[1024] = {0};
    char command[1024] = {0};
    char pathdesc[1024] = {0};
    char pathinput[1024] = {0};
    char pathoutput[1024] = {0};
    char juduldownload[1024] = {0};
    char judulproblem[1024];
    char pathsubmit[1024];

    char isi[1024] = {0};
    FILE *fp;
    printf("1. Login\n2. Register\nPilihan:");
    scanf("%d", &pilihan);
    if (pilihan == 1)
    {
        // login
        send(sock, login, strlen(login), 0);
    }
    else if (pilihan == 2)
    {
        // regist
        send(sock, regis, strlen(regis), 0);
    }
    valread = read(sock, buffer, 1024);

    // Register
    if (strcmp(buffer, "register") == 0)
    {
        memset(buffer, 0, sizeof(buffer));
        printf("Username: ");
        scanf("%s", username);
        send(sock, username, strlen(username), 0);

        memset(buffer, 0, sizeof(buffer));
        valread = read(sock, buffer, 1024);
        if (strcmp(buffer, "adausername") == 0)
        {
            printf("Username Exist\n");
            return 0;
        }
        else if (strcmp(buffer, "tidakada") == 0)
        {
            printf("Password : ");
            scanf("%s", password);
            send(sock, password, strlen(password), 0);

            memset(buffer, 0, sizeof(buffer));
            valread = read(sock, buffer, 1024);
            if (strcmp(buffer, "passwordsalah") == 0)
            {
                printf("-Password Minimal 6 karakter\n-Alphanumeric\n-Uppercase & Lowercase");
                return 0;
            }
        }
    }
    else if (strcmp(buffer, "login") == 0)
    {
        memset(buffer, 0, sizeof(buffer));
        memset(check, 0, sizeof(check));
        printf("Username:");
        scanf("%s", username);
        printf("Password:");
        scanf("%s", password);
        strcat(check, username);
        strcat(check, ":");
        strcat(check, password);

        send(sock, check, strlen(check), 0);

        memset(buffer, 0, sizeof(buffer));
        valread = read(sock, buffer, 1024);
        if (strcmp(buffer, "adaakun") == 0)
        {
            memset(command, 0, sizeof(command));
            printf("Selamat Datang\n");
            printf("Masukkan Command\n-add\n-see\n-download\n-submit\n");
            scanf("%s", command);
            if (strcmp(command, "add") == 0)
            {
                send(sock, command, strlen(command), 0);
                sleep(1);
                send(sock, username, strlen(username), 0);

                memset(buffer, 0, sizeof(buffer));
                bzero(buffer, sizeof(buffer));
                printf("Judul Problem:");
                scanf("%s", buffer);
                send(sock, buffer, strlen(buffer), 0);

                memset(buffer, 0, sizeof(buffer));
                valread = read(sock, buffer, 1024);
                if (strcmp(buffer, "folderada") == 0)
                {
                    printf("JUDUL PROBLEM TELAH ADA\n");
                }
                else if (strcmp(buffer, "foldergada") == 0)
                {
                    // send desc.txt
                    printf("Path file description.txt:");
                    scanf("%s", pathdesc);
                    send(sock, pathdesc, strlen(pathdesc), 0);

                    send_file(sock, pathdesc);

                    // send input.txt
                    printf("Path file input.txt:");
                    scanf("%s", pathinput);
                    send(sock, pathinput, strlen(pathinput), 0);

                    send_file(sock, pathinput);

                    // send output.txt
                    printf("Path file output.txt:");
                    scanf("%s", pathoutput);
                    send(sock, pathoutput, strlen(pathoutput), 0);

                    send_file(sock, pathoutput);
                }
            }
            else if (strcmp(command, "see") == 0)
            {
                char *see = "see";
                send(sock, see, strlen(see), 0);
                memset(buffer, 0, sizeof(buffer));
                valread = read(sock, buffer, 1024);
                strcat(isi, buffer);
                printf("%s", isi);
            }
            else if (strcmp(command, "download") == 0)
            {
                char *down = "download";
                memset(buffer, 0, sizeof(buffer));
                printf("Masukkan judul: ");
                scanf("%s", juduldownload);
                send(sock, down, strlen(down), 0);
                sleep(1);
                send(sock, juduldownload, strlen(juduldownload), 0);

                // receive desctxt
                char *desctxt = "desc.txt";
                write_file(sock, juduldownload, desctxt);
                // receive input.txt
                char *inputtxt = "input.txt";
                write_file(sock, juduldownload, inputtxt);
            }
            else if (strcmp(command, "submit") == 0)
            {
                char *submit = "submit";
                memset(buffer, 0, sizeof(buffer));
                printf("Submit:");
                scanf("%s %s", judulproblem, pathsubmit);
                send(sock, submit, strlen(submit), 0);
                sleep(1);
                send(sock, judulproblem, strlen(judulproblem), 0);
                sleep(1);
                char *file_contents;
                file_contents = read_file(pathsubmit);
                send(sock, file_contents, strlen(file_contents), 0);

                memset(buffer, 0, sizeof(buffer));
                valread = read(sock, buffer, 1024);
                if (strcmp(buffer, "benar") == 0)
                {
                    printf("AC");
                }
                else if (strcmp(buffer, "salah") == 0)
                {
                    printf("WA");
                }
            }

            else
            {
                printf("No such Command");
            }
        }
        else
        {
            printf("gagal logn\n");
        }
    }

    else
    {
        printf("Login/Register gagal");
    }

    return 0;
}