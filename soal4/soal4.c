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
