# SoalShift_Modul2_D07

### No.1

#### Penyelesaian :
Pada penyelesaian soal no 1 saya menggunakan pipe dengan mengiterasi file menggunakan find dengan argumen -name -printf. Output dari command terebut di cari basenamenya dan di pipe lagi dengan mv untuk merename file. Saya juga menggunakan xargs . Xargs merupakan proses input dan output dari pipe.

### No.2 (Belum bekerja)
Pada soal no 2 ini kami belum bisa membuat program c nya. Untuk ide penyelesaiannya adalah dengan mencari tahu mode dan owner dari file tersebut sesuai dengan yang diinginkan dan setelah itu file dihapus.

### No.3
Penyelesaian soal no 3 ini hampir sama dengan soal no 1 yaitu mempipe setiap command. Pertama proses child menjalankan unzip file. Setelah itu file tersebut diiterasi menggunakan command find dan memasukan hasilnya kedalam variable dan memasukan hasilnya kedalam file daftar.txt.

### No.4 (Belum bekerja)
Penyelesaian soal ini mencari tahu apakah file tersebut telah diakses atau tidak dengan cara command find dan argument -amin -0,5, yaitu mencek apakah ada file yang telah diakses 30 detik yang lalu. Setelah itu membuat file makan_sehat#.txt dengan # sebagai indeks angka.

### No.5 (Belum bekerja)
Penyelesaian soal no 5 ini, program membuat file pada proses child dengan isi yang didapat dari ps aux menggunakan popen setiap 1 menit. Pada proses parent dilakukan pembuatan folder dengan format date.
