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
