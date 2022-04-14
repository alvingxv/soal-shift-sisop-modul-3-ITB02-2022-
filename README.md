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


