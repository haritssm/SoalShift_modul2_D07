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
