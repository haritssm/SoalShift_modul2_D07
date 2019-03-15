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
  pid_t pid, sid, pid1;
  FILE *f,*output,*d;
  char str[100] = "log";
	char str_d[100];
  int counter = 1;

  pid = fork();
  pid1 = fork();

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
    // main program here

	//pid1 = fork();
	if(pid1 == 0){
		char num[20];
		//itoa(counter,num,10);
		num[3] = counter;
		strcat(str,num);
		strcat(str,".log");
		f = popen("ps aux","r");
		output = fopen(str,"a");
		while(fgets(str, sizeof(str), f) != NULL){
			printf("%s",str);
			fprintf(output,"%s",str);
		}
		pclose(f);
		fclose(output);
		counter++;
		sleep(60);
	}
	else{
		d = popen("date +%d:%m:%Y-%R","r");
		while(fgets(str_d, sizeof(str_d),d) != NULL){
			printf("%s",str_d);
		}
		char *argv[3] = {"mkdir",str_d,NULL};
		execv("/bun/mkdir", argv);
		sleep(1800);
	}

    //sleep(1800);
  }
  
  exit(EXIT_SUCCESS);
}
