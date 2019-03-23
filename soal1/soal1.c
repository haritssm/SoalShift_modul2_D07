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

	FILE *f;
	char str[100];
  while(1) {
	/*DIR *dir;
    	struct dirent *file;
    	dir = opendir("/home/zicoritonda/sisop/Modul2/SoalShiftModul2/soal1");
    	if (dir != NULL){
       		while ((file = readdir(dir)) != NULL){
          		if ((strstr(file->d_name,".txt")) != NULL){
            			char current[256];
				strcpy(current,"/home/zicoritonda/sisop/Modul2/SoalShiftModul2/soal1");
                 		char target[256];
				strcpy(target,"/home/zicoritonda/modul2/gambar");
                 		char filename[256];
            			strcpy(filename, file->d_name, strlen(file->d_name)-4);
            			strcat(filename, "_grey.txt");
				strcat(current,file->d_name);
				strcat(target,filename);
            			rename(file->d_name, filename);
          		}
        	}
    	}
    	closedir(dir);*/
	char current[256] = "/home/zicoritonda/sisop/Modul2/SoalShiftModul2/soal1";
	char target[256] = "/home/zicoritonda/modul2/gambar";
	char name[100];
	char filename[100];
	f = popen("find . -name '*.txt' -printf '%f\n'","r");
	while(fgets(str,sizeof(str),f) != NULL){
		strncpy(name,str,strlen(str)-4);
		sprintf(filename,"%s_grey.txt",name);
		strcat(current,str);
		strcat(target,filename);
		rename(str,filename);
	}
	pclose(f);
    	sleep(10);
  }
  
  exit(EXIT_SUCCESS);
}
