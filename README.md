# soal-shift-sisop-modul-3-itb02-202

## Laporan Pengerjaan Modul 3 Praktikum Sistem Operasi

### Nama Anggota Kelompok

1. Rachmita Annisa Aulia 5027201032
2. Alvian Ghifari 5027201035
3. Satrio Kamil Widhiwoso 5027201051

# Soal 1

Novak adalah seorang mahasiswa biasa yang terlalu sering berselancar di internet. Pada suatu saat, Ia menemukan sebuah informasi bahwa ada suatu situs yang tidak memiliki pengguna. Ia mendownload berbagai informasi yang ada dari situs tersebut dan menemukan sebuah file dengan tulisan yang tidak jelas. Setelah diperhatikan lagi, code tersebut berformat base64. Ia lalu meminta kepada anda untuk membuat program untuk memecahkan code-code di dalam file yang Ia simpan di drive dengan cara decoding dengan base 64. Agar lebih cepat, Ia sarankan untuk menggunakan thread.

A. Download dua file zip dan unzip file zip tersebut di dua folder yang berbeda dengan nama quote untuk file zip quote.zip dan music untuk file zip music.zip. Unzip ini dilakukan dengan bersamaan menggunakan thread.

B. Decode semua file .txt yang ada dengan base 64 dan masukkan hasilnya dalam satu file .txt yang baru untuk masing-masing folder (Hasilnya nanti ada dua file .txt) pada saat yang sama dengan menggunakan thread dan dengan nama quote.txt dan music.txt. Masing-masing kalimat dipisahkan dengan newline/enter.

C. Pindahkan kedua file .txt yang berisi hasil decoding ke folder yang baru bernama hasil.

D. Folder hasil di-zip menjadi file hasil.zip dengan password 'mihinomenest[Nama user]'. (contoh password : mihinomenestnovak)

E. Karena ada yang kurang, kalian diminta untuk unzip file hasil.zip dan buat file no.txt dengan tulisan 'No' pada saat yang bersamaan, lalu zip kedua file hasil dan file no.txt menjadi hasil.zip, dengan password yang sama seperti sebelumnya.

## Penjelasan code Soal 1
Dalam soal ini, kami diminta untuk mendownload dua file yang bernama **quote.zip** dan **music.zip**. Setelah di download, kita diminta untuk mengunzip kedua file tersebut secara bersamaan menggunakan thread. Setelah di unzip, maka akan muncul dua direktori yang bernama **music** dan **quote** yang berisi file hasil encode base64 di dalam file txt. Kemudian kita diminta untuk men-decode semua file yang berada di direktori **music** ke satu file baru yang bernama **music.txt**, yang berada di direktori **quote** ke **quote.txt**. Setelah itu, kedua file txt tersebut dipindahkan ke direktori baru yang bernama **hasil**. Direktori hasil kemudian akan di zip dengan nama **hasil.zip**. Karena ada yang kurang, **hasil.zip** akan di unzip ulang dan di zip lagi bersamaan dengan sebuah file bernama **no.txt** yang berisi tulisan "no".

## A
Pada bagian ini, kita diminta untuk download dan mengunzip file **music** dan **quote** secara bersamaan menggunakan thread. Untuk codenya bisa dilihat di bawah ini :
```c
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
```
Fungsi exec ini adalah fugsi untuk membuat fork sekalian dengan parent nya, jadi kita tinggal memanggil fungsi ini untuk menggunakan execv tanpa harus membuat fork satu persatu.
```c
void* unzipmusic()
{
    char *argv[] = {"unzip", "music.zip", "-d", "/home/kali/modul3/music", NULL};
    exec("/bin/unzip", argv);
}
void* unzipquote()
{
    char *argv[] = {"unzip", "quote.zip", "-d", "/home/kali/modul3/quote", NULL};
    exec("/bin/unzip", argv);
}
```
Selanjutnya, disini kita buat fungsi untuk menjalankan unzip music dan quote menggunakan execv dan fungsi unzip dari linux. `-d` digunakan untuk menentukan mau unzip ke file mana, disini kita mengunzipnya ke direktori **music** dan **quote** yang berada di direktori **modul3**.

## B
Selanjutnya, kita diminta untuk mendecode semua file di direktori music ke file music.txt, dan file direktori quote ke quote.txt. Masing-masing dipisah oleh newline/enter. Untuk code nya bisa dilihat di bawah ini :
```c
void decode(char *dir, char *filename)
{
    chdir(dir);
    char *argv[] = {"base64", "-d", filename, NULL};
    exec("/bin/base64", argv);
}
```
Fungsi decode disini digunkan untuk mendecode file-file txt yang diminta. Caranya adalah menggunakan library base64 yang sudah ada di linux, dan digabungkan dengan  Untuk mend-decode seluruh file txt yang diminta, kita akan menggunakan code di bawah ini : 
```c
void* newline(){

  char *argv[]={"echo", "\n", NULL};
  exec("/bin/echo", argv);
}

void* decodemusic()
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
    fclose(stdout);
}

void* decodequote()
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
    fclose(stdout);
}
```
 Sesuai nama fungsinya, fungsi diatas digunakan untuk meng-decode file-file txt yang berada di direktori **music** dan **quote**. Karena diminta untuk memberikan enter di setiap baris output nya, disini kita menggunakan fungsi newline yang sudah dibuat terlebih dahulu. Command freopen disini digunakan untuk mengeprint seluruh teks yang dihasilkan di terminal ke file yang telah ditentukan. Setelah seluruh teks di terminal sudah selesai di print, maka kita akan menggunakan fclose untuk menutupnya.

 ## C
 Selanjutnya, pada bagian soal ini kita diminta untuk memindahkan file **music.txt** dan **quote.txt** ke direktori bernama hasil. Untuk code nya bisa dilihat di bawah ini :
 ```c
 void *mkhasil()
{
    char *argv[] = {"mkdir", "hasil", NULL};
    exec("/bin/mkdir", argv);
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
 ```
 Pertama-tama, kita harus membuat direktori hasilnya terlebih dahulu untuk menampung file-file yang ingin dipindahkan. Selanjutnya kita menggunakan fungsi yang saya beri nama **mvmusic** untuk memindahkan **music.txt** ke direktori **hasil**, dan fungsi **mvquote** untuk memindahkan file **quote.txt** ke direktori **hasil**. Disini menggunakan command `find` untuk menemukan file yang ingin dipindahkan, dan command `-exec mv` untuk memindahkan file yang dicari.

 ## D
 Pada soal ini, kita diminta untuk meng-zip direktori hasil, dan memberi password dengan format **"minihomenest[Nama User]"**. Untuk codenya bisa dilihat di bawah ini :
 ```c
 void* ziphasil()
{
    char *argv[] = {"zip","-P", "mihinomenestsatrio", "-r", "hasil.zip", "hasil", NULL};
    exec("/bin/zip", argv);
}
```
Untuk meng-zip, kita menggunakan command zip, `-P` digunakan untuk memberikan password ketika folder tersebut di zip dan `-r` digunakan untuk mengrekursi seluruh file/folder yang berada di direktori **hasil**.

## E
Pada soal ini, kita diminta untuk meng-unzip **hasil.zip**, dan membuat sebuah file txt bernama **no.txt** yang berisi tulisan **"no"**. Kemudian akan dibuat zip baru, masih bernama **hasil.zip** yang berisi direktori **hasil** dan file **no.txt**. Untuk codenya bisa dilihat di bawah ini :
```c
void *unziphasil()
{
    char *argv[] = {"unzip", "hasil.zip", NULL};
    exec("/bin/unzip", argv);
}
void* ziphasil2()
{
    char *argv[] = {"zip","-P", "mihinomenestsatrio", "-r", "hasil.zip", "hasil", "no.txt", NULL};
    exec("/bin/zip", argv);
}
void addno()
{
    FILE *fptr = fopen("no.txt", "w");
    fprintf(fptr, "no");
}
void* touch(char *dest, char *name)
{
    chdir(dest);
    char *argv[] = {"touch", name, NULL};
    exec("/bin/touch", argv);
}
``` 
Pertama-tama, kita akan mengunzip direktori **hasil.zip** dengan function `unziphasil()`. Kemudian, kita akan membuat file bernama **no.txt** dengan fungsi `touch()` dan menambahkan teks no menggunakan fungsi `addno()`. Setelah semua selesai, kita akan meng-zip ulang dengan fungsi `ziphasil2()`.

## Code utama
Untuk main funcitonnya bisa dilihat di bawah ini :
```c
int main()
{
    pthread_t t1, t2, t3, t4;
    mkhasil();
    pthread_create(&t1, NULL, &unzipmusic, NULL);
    pthread_create(&t2, NULL, &unzipquote, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    decodemusic();
    decodequote();
    pthread_create(&t3, NULL, &mvmusic, NULL);
    pthread_create(&t4, NULL, &mvquote, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    ziphasil();
    unziphasil();
    touch("/home/modul3/", "no.txt");
    addno();
    ziphasil2();
}
```
## Screenshot
- Direktori **Hasil**

![1](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum_3/hasil.png)
- File **music.txt**

![2](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum_3/music.png)
- File **quote.txt**

![3](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum_3/quote.png)
- File **no.txt**

![4](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum_3/no.png)
- File **hasil.zip**

![5](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum_3/hasilzip.png)

## Masalah yang ditemui
- Base64 tidak bisa langsung di input ke file
- Zip tidak bisa menemukan direktori hasil

# Soal 2
Bluemary adalah seorang Top Global 1 di salah satu platform online judge. Suatu hari Ia ingin membuat online judge nya sendiri, namun dikarenakan Ia sibuk untuk mempertahankan top global nya, maka Ia meminta kamu untuk membantunya dalam membuat online judge sederhana. Online judge sederhana akan dibuat dengan sistem client-server dengan beberapa kriteria sebagai berikut:

A. Pada saat client terhubung ke server, terdapat dua pilihan pertama yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. Data input akan disimpan ke file users.txt dengan format username:password. Jika client memilih login, server juga akan meminta client untuk input id dan passwordnya lalu server akan mencari data di users.txt yang sesuai dengan input client. Jika data yang sesuai ditemukan, maka client dapat login dan dapat menggunakan command-command yang ada pada sistem. Jika tidak maka server akan menolak login client. Username dan password memiliki kriteria sebagai berikut:
- Username unique (tidak boleh ada user yang memiliki username yang sama)
- Password minimal terdiri dari 6 huruf, terdapat angka, terdapat huruf besar dan kecil

Format users.txt:
```
username:password
username2:password2
```

B. Sistem memiliki sebuah database pada server untuk menampung problem atau soal-soal yang ada pada online judge. Database ini bernama problems.tsv yang terdiri dari judul problem dan author problem (berupa username dari author), yang dipisah dengan \t. File otomatis dibuat saat server dijalankan.

C. Client yang telah login, dapat memasukkan command yaitu ‘add’ yang berfungsi untuk menambahkan problem/soal baru pada sistem. Saat client menginputkan command tersebut, server akan meminta beberapa input yaitu:
- Judul problem (unique, tidak boleh ada yang sama dengan problem lain)
- Path file description.txt pada client (file ini berisi deskripsi atau penjelasan problem)
- Path file input.txt pada client (file ini berguna sebagai input testcase untuk menyelesaikan problem)
- Path file output.txt pada client (file ini berguna untuk melakukan pengecekan pada submission client terhadap problem)

Contoh:

Client-side
```
add
```

Server-side
```
Judul problem:
Filepath description.txt:
Filepath input.txt:
Filepath output.txt:
```

Client-side
Client-side
```
<judul-problem-1>
<Client/description.txt-1>
<Client/input.txt-1>
<Client/output.txt-1>
```
Seluruh file akan disimpan oleh server ke dalam folder dengan nama <judul-problem> yang di dalamnya terdapat file description.txt, input.txt dan output.txt. Penambahan problem oleh client juga akan mempengaruhi file problems.tsv.

D. Client yang telah login, dapat memasukkan command ‘see’ yang berguna untuk menampilkan seluruh judul problem yang ada beserta authornya(author merupakan username client yang menambahkan problem tersebut). Format yang akan ditampilkan oleh server adalah sebagai berikut:
```
<judul-problem-1> by <author1>
<judul-problem-2> by <author2>
```

E. Client yang telah login, dapat memasukkan command ‘download <judul-problem>’ yang berguna untuk mendownload file description.txt dan input.txt yang berada pada folder pada server dengan nama yang sesuai dengan argumen kedua pada command yaitu <judul-problem>. Kedua file tersebut akan disimpan ke folder dengan nama <judul-problem> di client.

F. Client yang telah login, dapat memasukkan command ‘submit <judul-problem> <path-file-output.txt>’.  Command ini berguna untuk melakukan submit jawaban dari client terhadap problem tertentu. Algoritma yang dijalankan adalah client akan mengirimkan file output.txt nya melalui argumen ke 3 pada command, lalu server akan menerima dan membandingkan isi file output.txt yang telah dikirimkan oleh client dan output.txt yang ada pada folder dengan nama yang sesuai dengan argumen ke 2 pada command. Jika file yang dibandingkan sama, maka server akan mengirimkan pesan “AC” dan jika tidak maka server akan mengeluarkan pesan “WA”.

G. Server dapat menangani multiple-connection. Dimana jika terdapat 2 atau lebih client yang terhubung ke server, maka harus menunggu sampai client pertama keluar untuk bisa melakukan login dan mengakses aplikasinya.


## Penjelasan Code Soal 2

## A
Dalam point ini kita diminta untuk membuat sebuah register/login system dengan syarat2 yang telah diberikan. Username tidak boleh sama (unique) dan password harus Alphanum, 1 Huruf besar, 1 Huruf kecil, lebih dari 6 karakter.

### Client
```c
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
        //code register
    }
    else if (strcmp(buffer, "login") == 0)
    {
        //code login
    }
```
### Server
```c
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

```

Dapat dilihat client akan dapat memilih Login atau Register ketika menjalankan program. Jika user memilih 1, maka akan masuk ke if login dan jika user memilih 2 akan masuk ke if register.

#### Register
Pada masuk register, client akan mengirimkan sinyal ke server bahwa user ingin melakukan register, sehingga program dalam server akan masuk ke if bagian register. 

Selanjutnya client akan diminta untuk memasukkan Username dan Password.Pada saat memasukkan username, Client akan mengirimkan username terlebih dahulu untuk melakukan pengecekan pada users.txt apakah username yang dimasukkan adalah unique. Jika Server mendeteksi username sama maka Client dan Server akan mengirimkan Pesan bahwa username telah ada, dan akan return 0. Jika server tidak mendekteksi username yang sama, maka pengguna akan lanjut diminta password. Setelah pengguna memasukkan password, client akan mengirimkan password tersebut ke server untuk mengecek apakah kriteria password yang dikirim telah sesuai.

```c
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
```

```c
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
```

Dapat dilihat diatas adalah pengecekan kriteria password. Untuk mengecek panjang password, digunakan strlen untuk mengukur panjang string tersebut. Untuk mengecek Alphanum dan kapital, telah dibuat sebuah fungsi yang akan mengecek apakah string tersebut Alphanum dan kapital. Dalam fungsi isalphanum itu string akan dicek karakter per karakter menggunakan ASCII. 

Jika Password yang diinputkan tidak sesuai dengan kriteria, maka program akan mengeluarkan pesan bahwa register gagal dan program akan return 0. Jika Password yang diinputkan sesuai, maka program akan memasukkan username dan password tersebut ke akun.txt dengan format `username:password`.

#### Login

Pada menu login, pengguna akan diminta untuk memasukkan Username dan Password. Setelah itu kedua string tersebut akan diconcat dengan ":" agar sesuai dengan format yang telah ada di akun.txt. Selanjutnya Client akan mengirimkan hasil concat tersebut dan akan diterima oleh server. Setelah itu Server akan melakukan pengecekan di file akun.txt dengan menggunakan strstr. Jika strstr mereturn value, maka login berhasil dan pengguna dapan mengakses command2 yang ada. Jika strstr tidak mereturn value maka program akan mengirimkan pesan bahwa login gagal dan program akan return 0.

## B
Disini kita diminta untuk membuat database server yaitu Problems.tsv yang terdiri dari judul problem dan author problem (berupa username dari author), yang dipisah dengan \t. File ini akan dibuat ketika command add dijalankan.

## C
Dalam poin ini kita diminta untuk membuat command `add` yang dimana akan digunakan user untuk memasukkan problem ke server. 

### Client
```c
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
```
```c
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
```
### Server

```c
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
```
```c
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
```

Pertama User akan diminta untuk memasukkan judul problem yang dimana judul problem ini juga akan menjadi nama folder dari problem tersebut. Dalam soal ditulis bahwa judul problem adalah unique, sehingga client perlu mengirimkan judul problem tersebut ke server untuk dicek apakah folder yang bernama judul problem telah ada atau belum, jika telah ada maka program akan mengirimkan pesan bahwa judul telah ada dan program akan return 0. Jika folder belum ada, maka program akan melanjutkan inputan dari pengguna.

3 input setelah judul adalah konten dari problem tersebut, ada desc.txt, input.txt, dan output.txt. Untuk mengirimkan ketiga file ini harus dipastikan pada folder `client` telah ada file yang ingin dikirimkan. Setelah mengirimkan nama file yang ingin upload maka client akan memanggil fungsi `send_file` untuk mengirimkan konten dari file tersebut ke server. Dan untuk menerima file dari client, pada server akan memanggil fungsi `write_file`. Dengan ini file yang ingin dikirimkan pengguna dari client akan terkirim ke dalam folder problem yang telah ada di server.

## D
Dalam point ini kita diminta membuat command `see` yang berguna untuk melihat seluruh judul problem yang ada beserta authornya dengan format `<judul-problem-1> by <author1>`. 

### Client
```c
else if (strcmp(command, "see") == 0)
{
    char *see = "see";
    send(sock, see, strlen(see), 0);
    memset(buffer, 0, sizeof(buffer));
    valread = read(sock, buffer, 1024);
    strcat(isi, buffer);
    printf("%s", isi);
}
```
### Server
```c
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
```
Dapat dilihat diatas bahwa file yang akan dibuka adalah see.tsv, yang dimana ini adalah problems.tsv yang berbeda format. Server akan membaca isi dari file see.tsv tersebut dan mengirimkannya ke client untuk diprint.

## E
Dalam poin ini kita diminta untuk membuat command `download` yang dimana berguna untuk melakukan download desc.txt dan input.txt dari sebuah problem. 

### Client

```c
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
```
```c
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
```

### Server
```c
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
```
```c
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
```

Pertama pengguna akan diminta untuk memasukkan sebuah judul problem, lalu client akan mengirimkan judul tersebut ke server. Server akan menerima judul problem tersebut dan akan memanggil fungsi `send_file` untuk mengirimkan file sesuai judul yang telah diminta Client. Selanjutnya Client akan menerima file yang telah dikirimkan Server dengan memanggil fungsi `write_file`. File2 tersebut akan disimpan di Client pada folder dengan nama judul problemnya.

## F
Pada poin ini kita diminta untuk membuat command `submit` yang berfungsi untuk melakukan submit jawaban dari client terhadap problem tertentu. 

### Client
```c
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
```

### Server

```c
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
```

Dapat dilihat diatas, algoritma yang digunakan adalah Client akan memasukkan nama file dan nama problem yang ingin disubmit. Pertama pengguna akan memasukkan judul problem dan namafile yang ingin disubmit (file harus sudah ada di folder client). Lalu Client akan membaca isi dari file yang ingin disubmit, setelah itu dikirimkan ke server untuk membandingkan.

 Pada Server jika isi dari file yang dikirimkan dari Client sama dengan isi dari output.txt problem tersebut. Maka server akan mengirimkan sinyal bahwa jawaban benar ke Client, dan Program akan print `AC`. dan jika isi dari file yang dikirimkan CLient berbeda dari isi output.txt, maka server akan mengirimkan sinyal jawaban salah ke Client, dan program akan print `WA`

## Kendala yang dihadapi
Kendala yang dihadapi adalah tidak tau cara menjadikan argumen setelah command menjadi satu line.

## Screenshot hasil soal 2

#### **HASIL SETELAH REGISTER**
![Screenshot 2022-04-16 234040](https://user-images.githubusercontent.com/83297238/163683772-2660a666-a901-4888-b240-6232047dcce7.png)

#### **HASIL SETELAH COMMAND ADD**
![Screenshot 2022-04-16 234359](https://user-images.githubusercontent.com/83297238/163683845-8436b1b6-0ef5-44f2-95ca-2486593748c1.png)
#### **ISI iniproblem**
![Screenshot 2022-04-16 234520](https://user-images.githubusercontent.com/83297238/163683887-30644d05-180a-40aa-8827-7cb1bc4e6d96.png)

#### **HASIL SETELAH COMMAND SEE**
![Screenshot 2022-04-16 234744](https://user-images.githubusercontent.com/83297238/163683951-480123ea-247d-4e82-a21f-9ff7003685f7.png)

#### **HASIL SETELAH COMMAND DOWNLOAD**
![Screenshot 2022-04-16 234927](https://user-images.githubusercontent.com/83297238/163684012-ba0e1d0d-6351-4b29-8155-67b8de0d8859.png)
![Screenshot 2022-04-16 234939](https://user-images.githubusercontent.com/83297238/163684013-088cda79-5ab5-43e9-becb-42d35506db67.png)
#### **ISI iniproblem**
![Screenshot 2022-04-16 235044](https://user-images.githubusercontent.com/83297238/163684052-6e150875-79b9-4fb5-b28a-26be88f656c0.png)

#### **HASIL SETELAH COMMAND SUBMIT**
#### **Jawaban Benar**
![Screenshot 2022-04-16 235225](https://user-images.githubusercontent.com/83297238/163684102-a83a6771-f583-4ef5-8430-b2d7628228bf.png)

#### **Jawaban Salah**
![Screenshot 2022-04-16 235411](https://user-images.githubusercontent.com/83297238/163684159-327bb13f-1cfe-4d84-b74b-aaa4e6179a3d.png)



