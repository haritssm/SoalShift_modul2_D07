#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(char *argv[]){
	int status;
	int pipe_fd1[2];
	int pipe_fd2[2];
	pid_t pid,pid2;
	
	pipe(pipe_fd1);
	pid = fork();
	if(pid == 0){//child
		printf("child\n");
		dup2(pipe_fd1[1],STDOUT_FILENO);
		close(pipe_fd1[0]);
		

		char *argc[7] = {"find",".","-name","*.png","-printf","%f\n",NULL};
		execv("/usr/bin/find", argc);
	}
	else{
		dup2(pipe_fd1[0],STDIN_FILENO);
		close(pipe_fd1[1]);
		
		pipe(pipe_fd2);
		pid2 = fork();
		if(pid2 == 0){
			dup2(pipe_fd2[1],STDOUT_FILENO);
			close(pipe_fd2[0]);

			char *argc[] = {"xargs","-i","basename","-s",".png","{}",NULL};
			execv("/usr/bin/xargs",argc);
		}
		else{
			printf("parent\n");
			dup2(pipe_fd2[0],STDIN_FILENO);
			close(pipe_fd2[1]);

			char *argc[6] = {"xargs","-i","mv","{}.png","/home/zicoritonda/modul2/gambar/{}_grey.png",NULL};
			execv("/usr/bin/xargs",argc);
		}
	}
}
