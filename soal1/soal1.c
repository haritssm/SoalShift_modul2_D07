#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(char *argv[]){
	int status;
	int pipe_fd1[2];
	//int pipe_fd2[2];
	pid_t pid;

	//pipe(pipe_fd1);
	
	if(pipe(pipe_fd1) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	/*
	if(pipe(pipe_fd2) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	*/
	pid = fork();
	if(pid < 0){
		perror("fork");
		 exit(EXIT_FAILURE);
	}
	//printf("Mulai\n");
	if(pid == 0){//child
		printf("child\n");
		dup2(pipe_fd1[1],STDOUT_FILENO);
		close(pipe_fd1[0]);
		//printf("%d\n",pipe_fd1[1]);
		
		//char *argc[3] = {"ls","*.txt",NULL};
		//execv("/bin/ls",argc);

		char *argc[7] = {"find",".","-name","*.txt","-printf","%f\n",NULL};
		execv("/usr/bin/find", argc);

		//execlp("find","find",".","-name",argv[1],NULL);
		//execlp("find","find",".","-name",argv[1],"-exec","mv","{}","{}_grey",argv[2],NULL);
		// execlp("mkdir","mkdir","a",NULL);
	}
	else{
		printf("parent\n");
		dup2(pipe_fd1[0],STDIN_FILENO);
		close(pipe_fd1[1]);
		printf("%d\n",pipe_fd1[0]);
		char *argc[6] = {"xargs","-i","mv","{}","/home/zicoritonda/sisop/grey_{}",NULL};
		execv("/usr/bin/xargs",argc);
		//printf("%d\n",pipe_fd2[0]);
		//execlp("xargs","xargs","-i","mv","{}","{}_grey",NULL);
		//while((wait(&status)) > 0);
		//execlp("sort","sort",NULL);
	}

	/*
	ls_pid = fork();
	if(ls_pid == 0){//first child
		dup2(pipe_fd1[1], STDOUT_FILENO);
		close(pipe_fd1[0]);

		//char *argv[3] = {"ls","*.txt",NULL};
		//execv("/bin/ls",argv);
		execlp("ls", "ls", argv[1], NULL);
		printf("ls berhasil\n");
	}
	else if(ls_pid > 0){//parent
		dup2(pipe_fd2[0], STDIN_FILENO);
		close(pipe_fd2[1]);
		
		//while ((wait(&status)) > 0);
		//char *argv[7] = {"xargs",argv[2],"{}","mv", "{}", "new_{}", NULL};
		//execv("/bin/mv",argv);
		execlp("xargs", "xargs","-i", "mv", "{}", "new_{}",NULL);
		printf("mv berhasil\n");
	}
	else{
		 printf("Gagal\n");
	return 0;
	}
	*/
}
