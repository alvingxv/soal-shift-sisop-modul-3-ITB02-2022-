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
void send_file(int socket, char *namafolder, char *namafile)
{

    char filepath[2048];
    memset(filepath, 0, sizeof(filepath));
    strcat(filepath, "./");
    strcat(filepath, namafolder);
    strcat(filepath, "/");
    strcat(filepath, namafile);

    char file_length[1024];
    char *file_content = (char *)malloc(sizeof(char) * 65536);

    memset(file_length, 0, sizeof(file_length));

    char *file_contents;
    file_contents = read_file(filepath);
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
    char filepath[2048];
    memset(filepath, 0, sizeof(filepath));
    strcat(filepath, folder);
    strcat(filepath, "/");
    strcat(filepath, namafile);
    printf("Filepath %s: %s\n", namafile, filepath);

    char file_isi[65535] = {0};

    memset(buffer, 0, sizeof(buffer));
    read(socket, buffer, 1024);
    strcpy(file_isi, buffer);

    FILE *fptr = fopen(filepath, "a+");
    fprintf(fptr, "%s", file_isi);
    fclose(fptr);
    memset(file_isi, 0, sizeof(file_isi));
    memset(filepath, 0, sizeof(filepath));
    memset(buffer, 0, sizeof(buffer));
}

int isalphanum(char *pass)
{

    int i = 0, k = 0, d = 0, l = 0, p;

    i = strlen(pass);

    for (int j = 0; j < i; j++)
    {
        p = pass[j];
        if (p >= 97 && p <= 122)
            k++;
        else if (p >= 65 && p <= 90)
            l++;
        else if (p == 32)
            k++;
        else if (p >= 48 && p <= 57)
            d++;
    }

    if (k > 0 && d > 0 && l > 0)
    {
        return 0;
        // printf("String is AlphaNumeric :%s", pass);
    }
    else
    {
        return 1;
        // printf("String is Not AlphaNumeric :%s", pass);
    }
}

int main(int argc, char const *argv[])
{
    socklen_t addr_size1, addr_size2, addr_size3;
    int server_fd, new_socket, valread;
    struct sockaddr_in address, new_addr1, new_addr2, new_addr3;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char buffer[1024] = {0};
    char username[1024] = {0};
    char password[1024] = {0};
    char credentials[1024] = {0};
    char judul[1024] = {0};
    char pathdesc[1024] = {0};
    char pathinput[1024] = {0};
    char pathoutput[1024] = {0};
    char cmd[1024] = {0};
    char *regis = "register";
    char *login = "login";
    char *sama;
    char kirimtsv[1024] = {0};
    char kirimsee[1024] = {0};
    char judulupload[1024] = {0};
    char judulproblem[1024] = {0};
    char file_contents[1024] = {0};
    char pathkunci[1024] = {0};
    valread = read(new_socket, buffer, 1024);

    if (strcmp(buffer, "1") == 0)
    {
        memset(buffer, 0, sizeof(buffer));
        send(new_socket, login, strlen(login), 0); // Login
        long length;
        char *buff = 0;
        FILE *akun = fopen("users.txt", "a+");

        if (akun)
        {
            fseek(akun, 0, SEEK_END);
            length = ftell(akun);
            fseek(akun, 0, SEEK_SET);
            buff = malloc(length);
            if (buff)
            {
                fread(buff, 1, length, akun);
            }
            fclose(akun);
        }
        if (buff)
        {
            valread = read(new_socket, credentials, 1024);
            sama = strstr(buff, credentials);
            if (sama)
            {
                char *adaakun = "adaakun";
                send(new_socket, adaakun, strlen(adaakun), 0);

                // masuk command
                valread = read(new_socket, cmd, 1024);
                if (strcmp(cmd, "add") == 0)
                {
                    FILE *tsv = fopen("problems.tsv", "a+");
                    FILE *see = fopen("see.tsv", "a+");

                    memset(buffer, 0, sizeof(buffer));
                    valread = read(new_socket, buffer, 1024);
                    strcpy(username, buffer);

                    memset(buffer, 0, sizeof(buffer));
                    valread = read(new_socket, buffer, 1024);
                    strcpy(judul, buffer);
                    DIR *dir = opendir(judul);
                    if (dir)
                    {
                        /* Directory exists. */
                        char *folderada = "folderada";
                        send(new_socket, folderada, strlen(folderada), 0);
                        closedir(dir);
                        return 0;
                    }
                    else
                    {
                        char *foldergada = "foldergada";
                        send(new_socket, foldergada, strlen(foldergada), 0);
                    }

                    mkdir(judul, 0777);
                    printf("Judul problem:%s\n", judul);
                    strcat(kirimtsv, username);
                    strcat(kirimtsv, "\t");
                    strcat(kirimtsv, judul);
                    strcat(kirimtsv, "\n");
                    
                    strcat(kirimsee, judul);
                    strcat(kirimsee, " by ");
                    strcat(kirimsee, username);
                    strcat(kirimsee, "\n");

                    if (tsv)
                    {
                        fputs(kirimtsv, tsv);
                    }
                    if (see)
                    {
                        fputs(kirimsee, see);
                    }

                    // receive desctxt
                    memset(buffer, 0, sizeof(buffer));
                    valread = read(new_socket, buffer, 1024);
                    strcpy(pathdesc, buffer);
                    memset(buffer, 0, sizeof(buffer));

                    write_file(new_socket, judul, pathdesc);

                    // receive input.txt
                    memset(buffer, 0, sizeof(buffer));
                    valread = read(new_socket, buffer, 1024);
                    strcpy(pathinput, buffer);
                    memset(buffer, 0, sizeof(buffer));

                    write_file(new_socket, judul, pathinput);

                    // recieve output.txt
                    memset(buffer, 0, sizeof(buffer));
                    valread = read(new_socket, buffer, 1024);
                    strcpy(pathoutput, buffer);
                    memset(buffer, 0, sizeof(buffer));

                    write_file(new_socket, judul, pathoutput);
                }
                else if (strcmp(cmd, "see") == 0)
                {
                    char *buf = 0;
                    char isi[1000] = {0};
                    long length;
                    FILE *f = fopen("see.tsv", "rb");

                    if (f)
                    {
                        fseek(f, 0, SEEK_END);
                        length = ftell(f);
                        fseek(f, 0, SEEK_SET);
                        buf = malloc(length);
                        if (buf)
                        {
                            fread(buf, 1, length, f);
                        }
                        fclose(f);
                    }

                    if (buf)
                    {
                        strcpy(isi, buf);
                        send(new_socket, isi, strlen(isi), 0);
                    }
                }
                else if (strcmp(cmd, "download") == 0)
                {
                    memset(buffer, 0, sizeof(buffer));
                    valread = read(new_socket, buffer, 1024);
                    strcpy(judulupload, buffer); // file'

                    // send desc
                    char *desctxt = "desc.txt";
                    send_file(new_socket, judulupload, desctxt);

                    // send desc
                    char *inputtxt = "input.txt";
                    send_file(new_socket, judulupload, inputtxt);
                }
                else if (strcmp(cmd, "submit") == 0)
                {
                    memset(buffer, 0, sizeof(buffer));
                    valread = read(new_socket, buffer, 1024);
                    strcpy(judulproblem, buffer);

                    memset(buffer, 0, sizeof(buffer));
                    valread = read(new_socket, buffer, 1024);
                    strcpy(file_contents, buffer);

                    strcat(pathkunci, "./");
                    strcat(pathkunci, judulproblem);
                    strcat(pathkunci, "/");
                    strcat(pathkunci, "output.txt");

                    char *kunci;
                    kunci = read_file(pathkunci);

                    if (strcmp(kunci, file_contents) == 0)
                    {
                        char *benar = "benar";
                        send(new_socket, benar, strlen(benar), 0);
                    }
                    else
                    {
                        char *salah = "salah";
                        send(new_socket, salah, strlen(salah), 0);
                    }
                }
            }
            else
            {
                char *gagallogin = "gagallogin";
                send(new_socket, gagallogin, strlen(gagallogin), 0);
            }
        }
    }

    else if (strcmp(buffer, "2") == 0)
    {
        memset(buffer, 0, sizeof(buffer));
        send(new_socket, regis, strlen(regis), 0); // Register
        valread = read(new_socket, username, 1024);
        FILE *akun = fopen("users.txt", "a+");
        char line[1024];
        while (fgets(line, sizeof(line), akun) != NULL)
        {
            char *token;
            token = strtok(line, ":");
            if (strcmp(token, username) == 0)
            {
                char *ada = "adausername";
                send(new_socket, ada, strlen(ada), 0);
                printf("err Username\n");
                return 0;
            }
        }
        char *tidakada = "tidakada";
        send(new_socket, tidakada, strlen(tidakada), 0);
        valread = read(new_socket, password, 1024);
        if (strlen(password) < 6 || isalphanum(password) == 1)
        {
            char *passsalah = "passwordsalah";
            send(new_socket, passsalah, strlen(passsalah), 0);
            printf("err Password\n");
            return 0;
        }
        char akuntxt[1024] = {0};
        strcat(akuntxt, username);
        strcat(akuntxt, ":");
        strcat(akuntxt, password);
        strcat(akuntxt, "\n");
        fputs(akuntxt, akun);
        fclose(akun);
    }

    return 0;
}