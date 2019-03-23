# SoalShift_Modul2_D07

### No.1
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “namafile_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.

#### Penyelesaian :
Pertama kita menentukan apakah file tersebut ber-ekstensi .png atau bukan, jika .png, maka kita membuat blank char untuk dimasukkan format nama sesuai soal, yaitu "namafile_grey.png". Lalu kita menggunakan fungsi rename untuk mengubah nama dan memindahkan file tersebut.

#### Source Code
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    DIR *dir;
    struct dirent *file;
    dir = opendir("/home/haritssm/sisop/modul2/soal1/");
    if (dir != NULL){
       while (file = readdir(dir)){
          if (strstr(&file->d_name[strlen(file->d_name)-5], ".png")) {
            char current[256] = "/home/haritssm/sisop/modul2/soal1/",
                 target[256] = "/home/haritssm/sisop/modul2/soal1/gambar/",
                 filename[256] = "";
            strncpy(filename, file->d_name, strlen(file->d_name)-4);
            strcat(filename, "_grey.png");
            rename(strcat(current, file->d_name), strcat(target, filename));
          }
        }
    }
    closedir(dir);
    sleep(10);
  }
  
  exit(EXIT_SUCCESS);
}
```


### No.2 (Belum bekerja)
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.

#### Penyelesaian
Untuk memeriksa owner dari file tersebut digunakan sintaks<br>
&quot;Masukkan sintaks struct stat sampe struck group&quot;<br>
Setelah mengetahui owner dari file tersebut dan ternyata www-data, kita mengubah modenya dengan menggunakan &quot;chmod(&quot;elen.ku&quot;,777)&quot;. Untuk menghapus filenya menggunakan &quot;remove(&quot;elen.ku&quot;)<br>
<br>

#### Source Code
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/zicoritonda/hatiku")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
	struct stat info;
	stat("elen.ku",&info);
	struct passwd *pw = getpwuid(info.st_uid);
	struct group *gr = getgrgid(info.st_gid);
	char cmp[] = "www-data";
	if(strcmp(pw->pw_name,cmp) == 0 && strcmp(gr->gr_name,cmp) == 0){
		chmod("elen.ku",777);
		remove("elen.ku");
	}


    sleep(3);
  }

  exit(EXIT_SUCCESS);
}
```


### No.3
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat mengekstrak file zip tersebut dan menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt.

#### Penyelesaian
Untuk menyelesaikan soal ini kami menggunakan 3 proses. Pertama kami membuat child proses untuk mengunzip file campur2.zip<br>
&quot;Sintaks exec unzip&quot;<br>
<br>
Setelah itu kami membuat child proses untuk menlist file yang memiliki ekstensi .txt menggunakan ls hasil proses ini di pipe untuk proses sekanjutnya<br>
&quot;Sintax dari pid2 fork sampe exec ls&quot;<br>
<br>
Setelah itu hasil dari proses tersebut menjadi input proses ini yaitu mencari file .txt menggunakan find dan hasil nya menjadi input di proses selanjutnya yaitu membuat file dengan daftar file yg nemiliki ekstensi .txt<br>
&quot;Sintax pid3 fork sampe habis&quot;<br>
<br>

#### Source Code
```
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int status;
	pid_t pid1,pid2,pid3;
	int pipe1[2],pipe2[2];
	FILE *f;
	char str[500];

	pid1 = fork();
	if(pid1 ==0){
		char *argv[3] = {"unzip","campur2.zip",NULL};
		execv("/usr/bin/unzip",argv);
	}
	else{
		while(wait(&status) > 0);

		pid2 = fork();
		pipe(pipe1);
		pipe(pipe2);
		if(pid2 == 0){
			dup2(pipe1[1],STDOUT_FILENO);
			close(pipe1[0]);

			char *argv[3] = {"ls","/home/zicoritonda/sisop/Modul2/SoalShiftModul2/soal3/campur2",NULL};
			execv("/bin/ls",argv);
		}
		else{
			pid3 = fork();
			if(pid3 ==0){
				dup2(pipe1[0],STDIN_FILENO);
				dup2(pipe2[1],STDOUT_FILENO);
				close(pipe1[1]);
				close(pipe2[0]);

				char *argv[7] = {"find","./campur2","-name","*.txt","-printf","%f\n",NULL};
				execv("/usr/bin/find",argv);
			}
			else{
				dup2(pipe2[0],STDIN_FILENO);
				close(pipe2[1]);

				int lebar = read(pipe2[0],str,sizeof(str));
				//printf("\n");
				//printf("%.*s\n",lebar,str);
				close(pipe2[0]);
				f = fopen("daftar.txt","a");
				fprintf(f,"%.*s",lebar,str);
				fclose(f);
			}
		}
	}
}
```


### No.4 (Belum bekerja)
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik). Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

#### Penyelesaian
Untuk memnyelesaikan soal ini saya menggunakan popen untuk membuat command terminal diperlakukan seperti file yaitu dapat di baca. Saya menggunakan find untuk mencari file
"sintaks popen find"
Jika hasil yg didapat sesuai, akan membuat file dengan nama file tertentu
"sintaks strcmp sampe selesai"

#### Source Code
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
  pid_t pid, sid;
  int counter = 1;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/zicoritonda/Documents/makanan")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

	FILE *f,*file;
	char str[100];

  while(1) {
    // main program here
	f = popen("find . -name 'makan_enak.txt' -amin -0,5 -printf '%f\n'","r");
	while(fgets(str, sizeof(str),f) != NULL){
		//printf("%s\n",str);
		if(strcmp(str,"makan_enak.txt")){
			char name[20];
			sprintf(name,"makan_sehat%d.txt",counter);
			file = fopen(name,"w");
			fprintf(file,"Ayo diet\n");
			printf("Ayo diet\n");
			fclose(file);
			counter++;
		}
	}
	pclose(f);

    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
```


### No.5a (Belum bekerja)
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
dengan ketentuan :
  1. Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
  2. Per menit memasukkan log#.log ke dalam folder tersebut
     ‘#’ : increment per menit. Mulai dari 1

#### Penyelesaian
Untuk mendapatkan format jam kami menggunakan struct time dari c
"sintaks time sampai ptm"

Selanjutnya menggunkan popen grep untuk mendapatkan data dengan jam yg kita inginkan
"popen grep"

Program akan berjalan setiap 1 menit dan setiap 1 menit saya membuat variabel untuk mengingatkan sudah menjalaninya berapa kali senhingga kita dapat membuat folder jika variable tersebut jika kita modulus dengan 31 dan menghasilkan 0 akan membuat folder dengan mkdir
"sintaks if punya mkdir"

Untuk membuat file kami menggunakan cara seperti biasa yaitu fopen 
"sintaks fopen sampe selesai"

#### Source Code
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/zicoritonda/log")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

	FILE *c,*file;
	int counter = 1;
	char format[35],folder[17],fl[50],str[200];

  while(1) {
    // main program
	time_t rawtime;
	rawtime = time(NULL);
	struct tm *ptm;
	ptm = localtime(&rawtime);
	sprintf(format,"grep '%02d %02d:%02d' /var/log/syslog",ptm->tm_mday,ptm->tm_hour,ptm->tm_min);

	if(counter%16 ==0){
		sprintf(folder,"%02d:%02d:20%02d-%02d:%02d",ptm->tm_mday,ptm->tm_mon,ptm->tm_year,ptm->tm_hour,ptm->tm_min);
		mkdir(folder,0700);
		chdir(folder);
	}


	c = popen(format,"r");
	sprintf(fl,"log%d.log",counter);
	file = fopen(fl,"w");
	while(fgets(str, sizeof(str),c) != NULL){
		fprintf(file,"%s",str);
	}
	pclose(c);
	fclose(file);

	counter++;
  	sleep(2);
  }
  
  exit(EXIT_SUCCESS);
}
```


### No. 5b
Buatlah program c untuk menghentikan program nomor 5a.

#### Penyelesaian
Untuk menghentikannya kita menggunakan perintah killall, lalu menunjukkan proses yang ingin dihentikan

#### Source Code
```
#include <stdio.h>
#include <unistd.h>

int main(){

	char *argv[] = {"killall","s5",NULL};
	execv("/usr/bin/killall",argv);

	return 0;

}
```
